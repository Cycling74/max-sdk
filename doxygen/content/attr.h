/**

	@defgroup attr Attributes

	An attribute of an object is a setting or property that tells the object how to do its job.
	For example, the metro object has an interval attribute that tells it how fast to run.

	Attributes are similar to methods, except that the attributes have a state.
	Attributes are themselves objects, and they share a common interface for getting and setting values.

	An attribute is most typically added to the class definition of another object during it's class
	initialization or ext_main() function.
	Most typically, this attribute's value will be stored in an instance's struct,
	and thus it will serve as a property of that instance of the object.

	Attributes can, however, be declared as 'class static'.
	This means that the property is shared by all instances of the class,
	and the value is stored as a shared (static) variable.

	Additionally, Max 5 has introduced the notion of 'instance attributes' (also called 'object attributes').
	Instance attributes are the creation of an attribute object, and then adding it to one specific
	instance of another class.

	Finally, because attributes themselves are Max objects they too can possess attributes.
	These 'attributes of attributes' are used in Max to do things like specify a range of values for an attribute,
	give an attribute human friendly caption,
	or determine to what category an attribute should belong in the inspector.

	The easiest and most common way of working with attributes is to use the provided macros.
	These macros simplify the process of creating a new attribute object, setting any attributes of the attribute,
	and binding it to an object class or an object instance.


	@section attribute_accessors Setting and Getting Attribute Values

	By default, Max provides standard attribute accessors.
	These are the functions the get or set the attribute value in the object's struct.
	If you need to define a custom accessor, you can specify this information using the #CLASS_ATTR_ACCESSORS macro.


	@subsection attribute_accessors_getter Writing a custom Attribute Getter

	If you need to define a custom accessor, it should have a prototype and form comparable to the following custom getter:

	@code
	t_max_err foo_myval_get(t_foo *x, void *attr, long *ac, t_atom **av)
	{
	   if ((*ac)&&(*av)) {
	      //memory passed in, use it
	   } else {
	      //otherwise allocate memory
	      *ac = 1;
	      if (!(*av = getbytes(sizeof(t_atom)*(*ac)))) {
	         *ac = 0;
	         return MAX_ERR_OUT_OF_MEM;
	      }
	   }
	   atom_setfloat(*av,x->myval);

	   return MAX_ERR_NONE;
	}
	@endcode

	Note that getters require memory to be allocated, if there is not memory passed into the getter.
	Also the attr argument is the class' attribute object and can be queried using
	object_method for things like the attribute flags, names, filters, etc..


	@subsection attribute_accessors_setter Writing a custom Attribute Setter

	If you need to define a custom accessor, it should have a prototype and form comparable to the following custom setter:

	@code
	t_max_err foo_myval_set(t_foo *x, void *attr, long ac, t_atom *av)
	{
	   if (ac&&av) {
	      x->myval = atom_getfloat(av);
	   } else {
	      // no args, set to zero
	      x->myval = 0;
	   }
	   return MAX_ERR_NONE;
	}
	@endcode


	@section attribute_change_notification Attribute Notificaton

	Although the subject of object registration and notification is covered elsewhere,
	it bears noting that attributes of all types will, if registered,
	automatically send notifications to all attached client objects each time the attribute's value is set.

*/
