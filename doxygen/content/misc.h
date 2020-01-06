/**
	@defgroup misc Miscellaneous




	@defgroup console Console
	@ingroup misc




	@defgroup byteorder Byte Ordering
	@ingroup misc

	Utilities for swapping the order of bytes to match the Endianness of the required platform.
	An introduction to the issue of endianness can be found at http://en.wikipedia.org/wiki/Endianness.

	Of particular relevance is that a Macintosh with a PPC processor uses a Big-endian byte ordering,
	whereas an Intel processor in a Mac or Windows machine will use a Little-endian byte ordering.

	These utilities are defined to assist with cases where byte ordering needs to be manipulated for floats or ints.
	Note that floats are subject to the same byte ordering rules as integers.
	While the IEEE defines the bits, the machine still defines how the bits are arranged with regard to bytes.



	@defgroup expr Extending expr
	@ingroup misc

	If you want to use C-like variable expressions that are entered by a user
	of your object, you can use the "guts" of Max’s expr object in your
	object. For example, the if object uses expr routines for evaluating a
	conditional expression, so it can decide whether to send the message
	after the words then or else. The following functions provide an
	interface to expr.



	@defgroup tables Table Access
	@ingroup misc

	You can use these functions to access named table objects. Tables have
	names when the user creates a table with an argument.

	The scenario for knowing the name of a table but not the object itself is
	if you were passed a #t_symbol, either as an argument to your creation
	function or in some message, with the implication being "do your
	thing with the data in the table named norris."



	@defgroup texteditors Text Editor Windows
	@ingroup misc

	Max has a simple built-in text editor object that can display and
	edit text in conjunction with your object. The routines described here
	let you create a text editor.

	When the editor window is about to be closed, your object could
	receive as many as three messages. The first one, okclose, will be sent if
	the user has changed the text in the window. This is the standard
	okclose message that is sent to all "dirty" windows when they are about
	to be closed, but the text editor window object passes it on to you
	instead of doing anything itself. Refer to the section on Window
	Messages for a description of how to write a method for the okclose
	message. It’s not required that you write one—if you don’t, the
	behavior of the window will be determined by the setting of the
	window’s w_scratch bit. If it’s set, no
	confirmation will be asked when a dirty window is closed (and no
	okclose message will be sent to the text editor either). The second
	message, edclose, requires a method that should be added to your
	object at initialization time. The third message, edSave, allows you to
	gain access to the text before it is saved, or save it yourself.

	@see @ref chapter_enhancements_ed


	@defgroup presets Presets
	@ingroup misc

	Max contains a preset object that has the ability to send preset messages
	to some or all of the objects (clients) in a Patcher window. The preset
	message, sent when the user is storing a preset, is just a request for your
	object to tell the preset object how to restore your internal state to what
	it is now. Later, when the user executes a preset, the preset object will
	send you back the message you had previously said you wanted.

	The dialog goes something like this:

	- During a store…preset object to Client object(s): hello, this is the preset message—tell me how to restore your stateClient object to preset object: send me int 34 (for example)
	- During an execute…preset object to Client object: int 34

	The client object won’t know the difference between receiving int 34
	from a preset object and receiving a 34 in its leftmost inlet.

	It’s not mandatory for your object to respond to the preset message,
	but it is something that will make users happy. All Max user interface
	objects currently respond to preset messages. Note that if your object is
	not a user interface object and implements a preset method, the user
	will need to connect the outlet of the preset object to its leftmost inlet
	in order for it to be sent a preset message when the user stores a preset.

	Here’s an example of using preset_store() that specifies that the
	object would like to receive a set message. We assume it has one field,
	myvalue, which it would like to save and restore.

	@code
	void myobject_preset(myobject *x)
	{
		preset_store("ossl",x,ob_sym(x),gensym("set"),x->myvalue);
	}
	@endcode

	When this preset is executed, the object will receive a set message
	whose argument will be the value of myvalue. Note that the same
	thing can be accomplished more easily with preset_set() and
	preset_int().

	Don’t pass more than 12 items to preset_store(). If you want to store
	a huge amount of data in a preset, use binbuf_insert().

	The following example locates the Binbuf into which the preset data is
	being collected, then calls binbuf_insert() on a previously prepared
	array of Atoms. It assumes that the state of your object can be restored
	with a set message.

	@code
	void myobject_preset(myObject *x)
	{
		void *preset_buf;// Binbuf that stores the preset
		short atomCount; // number of atoms you’re storing
		t_atom atomArray[SOMESIZE];// array of atoms to be stored

		// 1. prepare the preset "header" information
		atom_setobj(atomArray,x);
		atom_setsym(atomArray+1,ob_sym(x));
		atom_setsym(atomArray+2,gensym("set"));
		// fill atomArray+3 with object's state here and set atomCount

		// 2. find the Binbuf
		preset_buf = gensym("_preset")->s_thing;

		// 3. store the data
		if (preset_buf) {
			binbuf_insert(preset_buf,NIL,atomCount,atomArray);
		}
	}
	@endcode




	@defgroup loading_max_files Loading Max Files
	@ingroup misc

	Several high-level functions permit you to load patcher files. These can
	be used in sophisticated objects that use Patcher objects to perform
	specific tasks.



	@defgroup jmonitor Monitors and Displays
	@ingroup misc

	Functions for finding our information about the environment.



	@defgroup jwind Windows
	@ingroup misc



	@defgroup jmouse Mouse and Keyboard
	@ingroup misc


*/
