/**
	@page chapter_msgattached Sending Messages, Calling Methods

	Max objects, such as the one you write, are C data structures in which methods are dynamically bound to functions. Your object's methods are called by Max, but your object can also call methods itself. When you call a method, it is essential to know whether the method you are calling is <strong>typed</strong> or not.

	Calling a typed method requires passing arguments as an array of atoms. Calling an untyped method requires that you know the exact arguments of the C function implementing the method. In both cases, you supply a symbol that names the method.

	In the typed method case, Max will take the array of atoms and pass the arguments to the object according to the method's argument type specifier list. For example, if the method is declared to have an argument type specifier list of #A_LONG, 0, the first atom in the array you pass will be converted to an int and passed to the function on the stack. If there are no arguments supplied, invoking a typed method that has #A_LONG, 0 as an argument type specifier will fail. To make typed method calls, use object_method_typed() or typedmess().

	In the untyped method case, Max merely does a lookup of the symbol in the object, and, if a matching function is found, calls the function with the arguments you pass.

	Certain methods you write for your object, such as the assist method for describing your object and the DSP method in audio objects, are declared as untyped using the #A_CANT argument type specifier. This means that Max will not typecheck the arguments you pass to these methods, but, most importantly, a user cannot hook up a message box to your object and send it a message to invoke an untyped method. (Try this for yourself -- send the assist message to a standard Max object.)

	When you use an outlet, you're effectively making a typed method call on any objects connected to the outlet.


	@section chapter_msgattached_attrs Attributes

	Attributes are descriptions of data in your object. The standardization of these descriptions permits Max to provide a rich interface to object data, including the pattr system, inspectors, the quick reference menu, @ arguments, etc.

	It is essential that you have some understanding of attributes if you are going to write a UI object. But non-UI objects can make use of attributes as well. The discussion below is not specific to UI objects. It does however, use the recently introduced system of macros in ext_obex_util.h (included in ext_obex.h) for defining attributes, as well as describing them using attributes of attributes (attr attrs). You can read more detailed descriptions of the underlying attribute definition mechanisms on a per-function basis in the @ref attr reference.


	@subsection chapter_msgattached_attr_basics Attribute Basics

	While attributes can be defined for a specific instance of an object, it's much more common to define an attribute for a class. In such a case, each instance of the class will have the attribute description, but the value will be instance specific. The discussion here focuses only on class attributes.

	When an attribute is declared and is made user-settable, a user can send a message to your object consisting of the attribute name and arguments that represent the new value of the attribute. For example, if you declare an attribute called trackcount, the message trackcount 20 will set it to 20. You don't need to do anything special to obtain this behavior. In addition, user-settable attributes will appear when the user opens the inspector on your object.

	If you define your attribute as an offset attribute, you describe its location (and size) within your object's C data structure. Max can then read and write the data directly. You can also define custom getter and setter routines if the attribute's value is more complex than simply a stored number. As a theoretical example, you could have an object with an attribute representing the Earth's population. If this value was not able to be stored inside your object, your custom getter routine could initiate a global census before returning the result. A custom setter for the earth's population might do something nasty if the value was set to zero. If you are not a misanthrope, you can take advantage of the ability to set such an attribute to be read-only.


	@subsection chapter_msgattached_attr_def Defining Attributes

	Attributes are defined when you are defining methods in your initialization routine. You can define your attributes before your methods if you like, but by convention, they are typically defined after the methods. For each definition, you'll specify the name, size, and offset of the corresponding member in your object's data structure that will hold the data. For example, let's say we have an object defined as follows:

@code
	typedef struct _myobject {
		t_object m_ob;
		long m_targetaddress;
		t_symbol *m_shipname;
		char m_compatmode;
	} t_myobject;
@endcode

	We want to create attributes for m_targetaddress, m_shipname, and m_compatmode. For each data type (and a few others), there are macros in ext_obex_util.h that will save a fair amount of typing. So, for example, we can define an attribute for m_targetaddress that uses CLASS_ATTR_LONG. Here are attribute definitions for all of the members of our data structure above.

@code
	CLASS_ATTR_LONG(c, "targetaddress", 0, t_myobject, m_targetaddress);
	CLASS_ATTR_SYM(c, "shipname", 0, t_myobject, m_shipname);
	CLASS_ATTR_CHAR(c, "compatibilitymode", 0, t_myobject, m_compatmode);
@endcode

 @subsection chapter_msgattached_attr_custom Attributes With Custom Getters and Setters

	In some cases, it is not enough to have Max read and write data in your object directly. In some cases (as in the world population example above) you may have data you need to calculate before it can be returned as a value. In other cases, you may need to do something to update other object state when an attribute value changes. To handle these challenges, you can define custom attribute getter and setter routines. The getter will be called when the value of your attribute is accessed. The setter will be called when someone changes the value of your attribute.

	As an example, suppose we have an object that holds onto an array of numbers, and we want to create an attribute for the size of the array. Since we'll want to resize the array when the attribute value changes, we will define a custom setter for our attribute. The default getter is adequate if we store the array size in our object, but since we want to illustrate how to write an attribute getter, we'll write the code so that the array size is computed from the size of the memory pointer we allocate. First, here is our object's data structure:

@code
	typedef struct _myobject {
		t_object m_ob;
		long *m_data;
	} t_myobject;
@endcode

We also have prototypes for our custom attribute setter and getter:

@code
	t_max_err myobject_size_get(t_myobject *x, t_object *attr, long *argc, t_atom **argv);
	t_max_err myobject_size_set(t_myobject *x, t_object *attr, long argc, t_atom *argv);
@endcode

Here is how we define our attribute using #CLASS_ATTR_ACCESSORS macro to define the custom setter and getter. Because we aren't really using an "offset" due to the custom setter and getter, we can pass any data structure member as a dummy. (Only the default attribute getter and setter will use this offset, and they are out of the picture.)

@code
	CLASS_ATTR_LONG(c, "size", 0, t_myobject, m_ob);
	CLASS_ATTR_ACCESSORS(c, "size", myobject_size_get, myobject_size_set);
@endcode

Now, here is an implementation of the custom setter for the array size. For the setter, we use the handy Max API function sysmem_resizeptr so we can effectively "resize" our array and copy the data into it in one step. The setter uses atoms, so we have to obtain the value from the first item in the argv array.

@code
	t_max_err myobject_size_set(t_myobject *x, t_object *attr, long argc, t_atom *argv)
	{
		long size = atom_getlong(argv);

		if (size < 0)		// bad size, don't change anything
			return 0;

		if (x->m_data)
			x->m_data = (long *)sysmem_resizeptr((char *)x->m_data, size * sizeof(long));
		else	// first time alloc
			x->m_data = (long *)sysmem_newptr(size * sizeof(long));
		return 0;
	}
 @endcode

 The getter also uses atoms for access, but we are returning a pointer to an array of atoms. The caller of the getter has the option to pre-allocate the memory (passing in the length in argc and the pointer to the memory in argv) or pass in 0 for argc and set the contents of argv to NULL and have the getter allocate the memory. The easiest way to handle this case is to call the utility function atom_alloc, which will figure out what was passed in and allocate memory for a returned atom if necessary.

@code
	t_max_err myobject_size_get(t_myobject *x, t_object *attr, long *argc, t_atom **argv)
	{
		char alloc;
		long size = 0;

		atom_alloc(argc, argv, &alloc);		// allocate return atom

		if (x->m_data)
			size = sysmem_ptrsize((char *)x->m_data) / sizeof(long);	// calculate array size based on ptr size

		atom_setlong(*argv, size);
		return 0;
	}
 @endcode

	@section chapter_msgattached_receiving Receiving Notifications

	As an alternative to writing a custom setter, you can take advantage of the fact that objects receive a "notify" message whenever one of their attributes is changed. The prototype for a notify method is as follows:

@code
	t_max_err myobject_notify(t_myobject *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
@endcode

	Add the following to your class initialization so your notification method will be called:

@code
	class_addmethod(c, (method)myobject_notify, "notify", A_CANT, 0);
@endcode

	The notify method can handle a variety of notifications (more documentation on this is coming soon!), but the one we're interested in is "attr_modified" -- the notification type is passed to the notify method in the msg argument. Here is an example of a notify method that prints out the name of the attribute that has been modified. You could take any action instead. To obtain the name, we interpret the data argument to the notify method as an attribute object. As an attribute is a regular Max object, we can use object_method to send it a message. In the case we are sending the message getname to the attribute object to obtain its name.

@code
	t_max_err myobject_notify(t_myobject *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
	{
		t_symbol *attrname;

		if (msg == gensym("attr_modified")) {		// check notification type
			attrname = (t_symbol *)object_method((t_object *)data, gensym("getname"));		// ask attribute object for name
			object_post((t_object *)x, "changed attr name is %s",attrname->s_name);
		}
		return 0;
	}
@endcode


*/
