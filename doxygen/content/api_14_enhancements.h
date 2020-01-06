/**
	@page chapter_enhancements Enhancements to Objects


	@section chapter_enhancements_presets Preset Support

	Presets are a simple state-saving mechanism. Your object receives a preset message when state is being saved. You respond by creating a message that will be sent back to your object when the preset is recalled.

	For more powerful and general state-saving, use the pattr system described below.

	To support saving a single integer in a preset, you can use the preset_int() convenience function. The preset_int() function records an int message with the value you pass it in the preset, to be sent back to your object at a later time.

@code
	class_addmethod(c, (method)myobject_preset, "preset", 0);

	void myobject_preset(t_myobject *x)
	{
		preset_int(x, x->m_currentvalue);
	}
@endcode

	More generally, you can use preset_store(). Here is an example of storing two values (m_xvalue and m_yvalue) in a list.
@code
		preset_store("ossll", x, ob_sym(x), gensym("list"), x->m_xvalue, x->m_yvalue);
@endcode


	@section chapter_enhancements_pattr Pattr Support

	In most cases, you need only to define your object's state using @ref chapter_msgattached_attrs and it will be ready for use with Max's pattr system.
	For more complex scenarios you may also wish to investigate object_notify(), object_attach(), and the section on @ref chapter_msgattached_receiving.


	@section chapter_enhancements_assistance Assistance

	To show descriptions of your object's inlets and outlets while editing a patcher, your object can respond to the assist message with a function that copies the text to a string.

@code
	class_addmethod(c, (method)myobject_assist, "assist", A_CANT, 0);
@endcode

	The function below has two inlets and one outlet. The io argument will be 1 for inlets, 2 for outlets. The index argument will be 0 for the leftmost inlet or outlet. You can copy a maximum of 512 characters to the output string s. You can use strncpy_zero() to copy the string, or if you want to format the assistance string based on a current value in the object, you could use snprintf_zero().

@code
	void myobject_assist(t_myobject *x, void *b, long io, long index, char *s)
	{
		switch (io) {
			case 1:
				switch (index) {
					case 0:
						strncpy_zero(s, "This is a description of the leftmost inlet", 512);
						break;
					case 1:
						strncpy_zero(s, "This is a description of the rightmost inlet", 512);
						break;
				}
				break;
			case 2:
				strncpy_zero(s, "This is a description of the outlet", 512);
				break;
		}
	}
@endcode


	@section chapter_enhancements_hotness Hot and Cold Inlets

	Objects such as operators (+, -, etc.) and the int object have inlets that merely store values rather than performing an operation and producing output. These inlets are labeled with a blue color to indicate they are "cold" rather than action-producing "hot" inlets. To implement this labeling, your object can respond to the inletinfo message.

@code
		class_addmethod(c, (method)myobject_inletinfo, "inletinfo", A_CANT, 0);
@endcode

	If all of your object's non-left inlets are "cold" you can use the function stdinletinfo() instead of writing your own, as shown below:
@code
		class_addmethod(c, (method)stdinletinfo, "inletinfo", A_CANT, 0);
@endcode

	To write your own function, just look at the index argument (which is 0 for the left inlet). This example turns the third inlet cold. You don't need to do anything for "hot" inlets.

@code
	void myobject_inletinfo(t_myobject *x, void *b, long index, char *t)
	{
		if (index == 2)
			*t = 1;
	}
@endcode


	@section chapter_enhancements_ed Showing a Text Editor

	Objects such as coll and text display a text editor window when you double-click. Users can edit the contents of the objects and save the updated data (or not). Here's how to do the same thing in your object.

	First, if you want to support double-clicking on a non-UI object, you can respond to the dblclick message.

@code
	class_addmethod(c, (method)myobject_dblclick, "dblclick", A_CANT, 0);

	void myobject_dblclick(t_myobject *x)
	{
		// open editor here
	}
@endcode

	You'll need to add a #t_object pointer to your object's data structure to hold the editor.

@code
	typedef struct _myobject
	{
		t_object m_obj;
		t_object *m_editor;
	} t_myobject;
@endcode

	Initialize the m_editor field to NULL in your new instance routine. Then implement the dblclick method as follows:
@code
		if (!x->m_editor)
			x->m_editor = object_new(CLASS_NOBOX, gensym("jed"), (t_object *)x, 0);
		else
			object_attr_setchar(x->m_editor, gensym("visible"), 1);
@endcode

	The code above does the following: If the editor does not exist, we create one by making a "jed" object and passing our object as an argument. This permits the editor to tell our object when the window is closed.

	If the editor does exist, we set its visible attribute to 1, which brings the text editor window to the front.

	To set the text of the edit window, we can send our jed object the settext message with a zero-terminated buffer of text. We also provide a symbol specifying how the text is encoded. For best results, the text should be encoded as UTF-8. Here is an example where we set a string to contain "Some text to edit" then pass it to the editor.

@code
			char text[512];

			strcpy(text,"Some text to edit");
			object_method(x->m_editor, gensym("settext"), text, gensym("utf-8"));
@endcode

	The title attribute sets the window title of the text editor.
@code
			object_attr_setsym(x->m_editor, gensym("title"), gensym("crazytext"));
@endcode

	When the user closes the text window, your object (or the object you passed as an argument when creating the editor) will be sent the edclose message.
@code
			class_addmethod(c, (method)myobject_edclose, "edclose", A_CANT, 0);
@endcode

	The edclose method is responsible for doing something with the text. It should also zero the reference to the editor stored in the object, because it will be freed. A pointer to the text pointer is passed, along with its size. The encoding of the text is always UTF-8.

@code
	void myobject_edclose(t_myobject *x, char **ht, long size)
	{
		// do something with the text
		x->m_editor = NULL;
	}
@endcode

	If your object will be showing the contents of a text file, you are still responsible for setting the initial text, but you can assign a file so that the editor will save the text data when the user chooses Save from the File menu. To assign a file, use the filename message, assuming you have a filename and path ID.

@code
		object_method(x->m_editor, gensym("filename"), x->m_myfilename, x->m_mypath);
@endcode

	The filename message will set the title of the text editor window, but you can use the title attribute to override the simple filename. For example, you might want the name of your object to precede the filename:
@code
		char titlename[512];

		sprintf(titlename, "myobject: %s", x->m_myfilename);
		object_attr_setsym(x->m_editor, gensym("title"), gensym(titlename));
@endcode

	Each time the user chooses Save, your object will receive an edsave message. 
	If you return zero from your edsave method, the editor will proceed with saving the text in a file. 
	If you return non-zero, the editor assumes you have taken care of saving the text. 
	The general idea is that when the user wants to save the text, it is either updated inside your object, updated in a file, or both. 
	As an example, the js object uses its edsave message to trigger a recompile of the Javascript code. 
	But it also returns 0 from its edsave method so that the text editor will update the script file. 
	Except for the return value, the prototype of the edsave method is identical to the edclose method.

@code
	class_addmethod(c, (method)myobject_edsave, "edsave", A_CANT, 0);

	long myobject_edsave(t_myobject *x, char **ht, long size)
	{
		// do something with the text
		return 0;		// tell editor it can save the text
	}
@endcode


	@section chapter_enhancements_tables Accessing Data in table Objects

	Table objects can be given names as arguments. If a table object has a name, you can access the data using table_get(). Supply a symbol, as well as a place to assign a pointer to the data and the length. The following example accesses a table called foo, and, if found, posts all its values.

@code
	long **data = NULL;
	long i, size;

		if (!table_get(gensym("foo"), &data, &size)) {
			for (i = 0;  i < size; i++) {
				post("%ld: %ld",i,(*data)[i]);
			}
		}
@endcode

	You can also write data into the table. If you would like the table editor to redraw after doing so, use table_dirty(). Here's an example where we set all values in the table to zero, then notify the table to redraw.

@code
	long **data = NULL;
	long i, size;

		if (!table_get(gensym("foo"), &data, &size)) {
			for (i = 0;  i < size; i++) {
				(*data)[i]  = 0;
			}
			table_dirty(gensym("foo"));
		}
@endcode


*/
