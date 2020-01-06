/**
	@page chapter_jit_objectmodel Jitter Object Model


@section chapter_jit_objectmodel_basics Jitter Object Model Basics

Jitter objects use an object model which is somewhat different than the one traditionally used for developing Max external objects. The first big difference between Jitter objects and traditional Max external objects is that Jitter objects don't have any notion of the patcher themselves. This allows for the flexible instantiation and use of Jitter objects from C, Java, JavaScript, as well as in the Max patcher. The use of these Jitter objects is exposed to the patcher with a Max "wrapper" object, which will be discussed in the following chapter.

In this chapter we'll restrict our discussion to the fundamentals of defining the Jitter object which can be used in any of these languages. While Jitter's primary focus is matrix processing and real-time graphics, these tasks are unrelated to the object model, and will be covered in later chapters on developing Matrix Operator (MOP) and OB3D objects.
Like Max objects, Jitter objects are typically written in C. While C++ can be used to develop Jitter objects, none of the object oriented language features will be used to define your object as far as Jitter is concerned. Similar to C++ or Java objects, Jitter objects are defined by a class with methods and member variables - we will refer to the member variables as "attributes". Unlike C++ or Java, there are no language facilities that manage class definition, class inheritance, or making use of class instances. In Jitter this must all be managed with sets of standard C function calls that will define your class, exercise methods, and get and set object attributes.

Max and Jitter implement their object models by maintaining a registry of ordinary C functions and struct members that map to methods and attributes associated with names. When some other code wishes to make use of these methods or attributes, it asks the Jitter object to look up the method or attribute in its registry based on a name. This is called dynamic binding, and is similar to Smalltalk or Objective C's object model. C++ and Java typically make use of static binding — i.e. methods and member variables are resolved at compile time rather than being dynamically looked up at run time.


@section chapter_jit_objectmodel_classdef Defining a Jitter Class

A Jitter class is typically defined in a C function named something like your_object_name_init(). Class definition begins with a call to jit_class_new(), which creates a new class associated with a specified name, constructor, destructor, and size in bytes of the object as stored in a C structure. This is followed by calls to jit_class_addmethod() and jit_class_addattr(), which register methods and attributes with their corresponding names in the class. The class is finally registered with a call to jit_class_register(). A minimal example class definition is shown below:

@code
typedef struct _jit_foo
{
   t_jit_object    ob;
   float          myval;
} t_jit_foo;

static t_jit_class *_jit_foo_class=NULL;

t_jit_err jit_foo_init(void)
{
   long attrflags=0;
   t_jit_object *attr;

   // create new class named "jit_foo" with constructor + destructor
   _jit_foo_class = jit_class_new("jit_foo",(method)jit_foo_new,
      (method)jit_foo_free, sizeof(t_jit_foo), 0L);

   // add method to class
   jit_class_addmethod(jit_foo_scream, "scream", A_DEFLONG, 0L);

   // define attribute
   attr = jit_object_new(      // instantiate an object
      _jit_sym_jit_attr_offset,   // of class jit_attr_offset
      "myval",         // with name "myval"
      _jit_sym_float32,       // type float32
      attrflags,         // default flags
      (method)0L,         // default getter accessor
      (method)0L,         // default setter accessor
      calcoffset(t_jit_foo,myval)); // byte offset to struct member

   // add attribute object to class
   jit_class_addattr(_jit_foo_class, attr);

   // register class
   jit_class_register(_jit_foo_class);

   return JIT_ERR_NONE;
}

// constructor
t_jit_foo *jit_foo_new(void)
{
   t_jit_foo *x;

   // allocate object
   if (x=jit_object_alloc(_jit_foo_class))
   {
      // if successful, perform any initialization
      x->myval = 0;
   }
   return x;
}

// destructor
void jit_foo_free(t_jit_foo *x)
{
   // would free any necessary resources here
}

// scream method
void jit_foo_scream(t_jit_foo *x, long i)
{
   post("MY VALUE IS %f! AND MY ARGUMENT IS %d", x->myval, i);
}
@endcode

The above example has a constructor, jit_foo_new(); a destructor, jit_foo_free(); one 32 bit floating point attribute, myval, a member of the object struct accessed with default accessor methods; and a method jit_foo_scream(), which posts the current value of myval to the Max window.


@section chapter_jit_objectmodel_struct Object Struct

Each instance of an object occupies some region of organized memory. The C structure that defines this organization of memory is typically referred to as the "object struct". It is important that the object struct always begin with an entry of type #t_jit_object. It is within the #t_jit_object where special information about the class is kept. The C structure can contain additional information, either exposed as attributes or not, but it is important that the size of the object struct does not exceed 16384 bytes. This means that it is not safe to define a large array as a struct entry if it will cause the size of the object struct to be larger than this limit. If additional memory is required, the object struct should contain a pointer to memory allocated from within the constructor, and freed within the destructor.

The class registration in the above code makes use of the object struct both to record in the class how large each object instance should be—i.e. sizeof(t_jit_foo) ; and at what byte offset in the object struct an attribute is located—i.e. calcoffset(t_jit_foo, myval) . When methods of an object are called, the instance of the object struct is passed as the first argument to the C functions which define the object methods. This instance may be thought of as similar to the "this" keyword used in C++ and Java - actually the C++ and Java underlying implementation works quite similarly to what has been implemented here in pure C. Object struct entries may be thought of as similar to object member variables, but methods must be called via functions rather than simply dereferencing instances of the class as you might do in C++ or Java. The list of object methods and other class information is referenced by your object's #t_jit_object entry.


@section chapter_jit_objectmodel_ctordtor Constructor/Destructor

The two most important methods that are required for all objects are the constructor and the destructor. These are typically named your_object_name_new(), and your_object_name_free(), respectively. It is the constructor's responsibility to allocate and initialize the object struct and any additional resources the object instance requires. The object struct is allocated via jit_object_alloc(), which also initializes the #t_jit_object struct entry to point at your relevant class information. The class information resides in your global class variable, e.g. _jit_foo_class, which you pass as an argument to jit_object_alloc(). This allocation does not, however initialize the other struct entries, such as "myval", which you must explicitly initialize if your allocation is successful. Note that because the constructor allocates the object instance, no object instance is passed as the first argument to the function which defines the constructor, unlike other object methods.

The constructor also has the option of having a typed argument signature with the same types as defined in the Writing Max Externals documentation—i.e. #A_LONG, #A_FLOAT, #A_SYM, #A_GIMME, etc. Typically, Jitter object constructors either have no arguments or use the #A_GIMME typed argument signature.

In earlier versions of Jitter, the constructors were often specified as private and "untyped" using the #A_CANT type signature. While this obsolete style of an untyped constructor will work for the exposure of a Jitter class to the patcher and C, it is now discouraged, as there must be a valid type signature for exposure of a class to Javascript or Java, though that signature may be the empty list.

It is the destructor's responsibility to free any resources allocated, with the exception of the object struct itself. The object struct is freed for you after your destructor exits.


@section chapter_jit_objectmodel_methods Methods

You can define additional methods using the jit_class_addmethod() function. This example defines the scream method associated with the function jit_foo_scream(), with no additional arguments aside from the standard first argument of a pointer to the object struct. Just like methods for ordinary Max objects, these methods could have a typed argument signature with the same types as defined in the Writing Max Externals documentation — i.e. #A_LONG, #A_FLOAT, #A_SYM, #A_GIMME. Typically in Jitter objects, public methods are specified either without arguments, or use #A_GIMME, or the low priority variants, #A_DEFER_LOW, or #A_USURP_LOW, which will be discussed in following chapters. Private methods, just like their Max equivalent should be defined as untyped, using the #A_CANT type signature.
Object methods can be called from C either by calling the C function directly, or by using jit_object_method() or jit_object_method_typed(). For example, the following calls that relate to the above jit_foo example are equivalent:

@code
// call scream method directly
jit_foo_scream(x, 74);

// dynamically resolve and call scream method
jit_object_method(x, gensym("scream"), 74);

// dynamically resolve and call scream method with typed atom arguments
t_atom a[1];
jit_atom_setlong(a, 74);
jit_object_method_typed(x, gensym("scream"), 1, a, NULL);
@endcode

What the jit_object_method() and jit_object_method_typed() functions do is look up the provided method symbol in the object's class information, and then calls the corresponding C function associated with the provided symbol. The difference between jit_object_method() and jit_object_method_typed() is that jit_object_method() will not require that the method is typed and public, and blindly pass all of the arguments following the method symbol on to the corresponding method. For this reason, it is required that you know the signature of the method you are calling, and pass the correct arguments. This is not type checked at compile time, so you must be extremely attentive to the arguments you pass via jit_object_method(). It is also possible for you to define methods which have a typed return value with the #A_GIMMEBACK type signature. When calling such methods, the final argument to jit_object_method_typed(), should point to a #t_atom to be filled in by the callee. This and the subject of "typed wrappers" for exposing otherwise private methods to language bindings that require typed methods (e.g. Java/!JavaScript) will be covered in a later chapter.


@section chapter_jit_objectmodel_attrs Attributes

You can add attributes to the class with jit_class_addattr(). Attributes themselves are Jitter objects which share a common interface for getting and setting values. While any class which conforms to the attribute interface could be used to define attributes of a given class, there are a few common classes which are currently used: jit_attr_offset(), which specifies a scalar attribute of a specific type (char, long, float32, float64, symbol, or atom) at some byte offset in the object struct; jit_attr_offset_array() which specifies an array (vector) attribute of a specific type (char, long, float32, float64, symbol, or atom) at some byte offset in the object struct; and jit_attribute, which is a more generic attribute object that can be instantiated on a per object basis. We will not document the usage of jit_attribute at this time. The constructor for the class jit_attr_offset() has the following prototype:

@code
t_jit_object *jit_attr_offset_new(char *name, t_symbol *type, long flags,
   method mget, method mset, long offset);
@endcode

When this constructor is called via jit_object_new(), additionally the class name, #_jit_sym_jit_attr_offset (a global variable equivalent to gensym("jit_attr_offset") ) must be passed as the first parameter, followed by the above arguments, which are passed on to the constructor. The name argument specifies the attribute name as a null terminated C string. The type argument specifies the attribute type, which may be one of the following symbols: #_jit_sym_char, #_jit_sym_long, #_jit_sym_float32, #_jit_sym_float64, #_jit_sym_symbol, #_jit_sym_atom, #_jit_sym_object, or #_jit_sym_pointer. The latter two are only useful for private attributes as these types are not exposed to, or converted from Max message atom values.

The flags argument specifies the attribute flags, which may be a bitwise combination of the following constants:

@code
#define JIT_ATTR_GET_OPAQUE           0x00000001 // cannot query
#define JIT_ATTR_SET_OPAQUE           0x00000002 // cannot set
#define JIT_ATTR_GET_OPAQUE_USER      0x00000100 // user cannot query
#define JIT_ATTR_SET_OPAQUE_USER      0x00000200 // user cannot set
#define JIT_ATTR_GET_DEFER            0x00010000 // (deprecated)
#define JIT_ATTR_GET_USURP            0x00020000 // (deprecated)
#define JIT_ATTR_GET_DEFER_LOW        0x00040000 // query in low priority
#define JIT_ATTR_GET_USURP_LOW        0x00080000 // query in low, usurping
#define JIT_ATTR_SET_DEFER            0x01000000 // (deprecated)
#define JIT_ATTR_SET_USURP            0x02000000 // (deprecated)
#define JIT_ATTR_SET_DEFER_LOW        0x04000000 // set at low priority
#define JIT_ATTR_SET_USURP_LOW        0x08000000 // set at low, usurping
@endcode

Typically attributes in Jitter are defined with flags #JIT_ATTR_GET_DEFER_LOW, and #JIT_ATTR_SET_USURP_LOW. This means that multiple queries from the patcher will generate a response for each query, and that multiple attempts to set the value at high priority will collapse into a single call with the last received value. For more information on defer and usurp, see the chapter on Jitter scheduling issues.

The mget argument specifies the attribute "getter" accessor method, used to query the attribute value. If this argument is zero (NULL), then the default getter accessor will be used. If you need to define a custom accessor, it should have a prototype and form comparable to the following custom getter:

@code
t_jit_err jit_foo_myval_get(t_jit_foo *x, void *attr, long *ac, t_atom **av)
{
   if ((*ac)&&(*av)) {
      //memory passed in, use it
   } else {
      //otherwise allocate memory
      *ac = 1;
      if (!(*av = jit_getbytes(sizeof(t_atom)*(*ac)))) {
         *ac = 0;
         return JIT_ERR_OUT_OF_MEM;
      }
   }
   jit_atom_setfloat(*av,x->myval);

   return JIT_ERR_NONE;
}
@endcode

Note that getters require memory to be allocated, if there is not memory passed into the getter. Also the attr argument is the class' attribute object and can be queried using jit_object_method() for things like the attribute flags, names, filters, etc..
The mset argument specifies the attribute "setter" accessor method, used to set the attribute value. If this argument is zero (NULL), then the default setter accessor will be used. If we need to define a custom accessor, it should have a prototype and form comparable to the following custom setter:

@code
t_jit_err jit_foo_myval_set(t_jit_foo *x, void *attr, long ac, t_atom *av)
{
   if (ac&&av) {
      x->myval = jit_atom_getfloat(av);
   } else {
      // no args, set to zero
      x->myval = 0;
   }
   return JIT_ERR_NONE;
}
@endcode

The offset argument specifies the attribute's byte offset in the object struct, used by default getters and setters to automatically query and set the attribute's value. If you have both custom accessors, this value is ignored. This can be a useful strategy to employ if you wish to have an object attribute that does not correspond to any actual entry in your object struct. For example, this is how we implement the time attribute of jit.movie — i.e. it uses a custom getter and setter which make QuickTime API calls to query and set the current movie time, rather than manipulating the object struct itself, where no information about movie time is actually stored. In such an instance, you should set this offset to zero.

After creating the attribute, it must be added to the Jitter class using the jit_class_addattr() function:

@code
t_jit_err jit_class_addattr(void *c, t_jit_object *attr);
@endcode

To put it all together: to define a jit_attribute_offset() with the custom getter and setter functions defined above, you'd make the following call:

@code
long attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
t_jit_object *attr = jit_object_new(_jit_sym_jit_attr_offset, "myval", _jit_sym_float32, attrflags,
   (method)jit_foo_myval_get, (method)jit_foo_myval_set, NULL);
jit_class_addattr(_jit_foo_class, attr);
@endcode

And to define a completely standard jit_attribute_offset(), using the default getter and setter methods:

@code
long attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
t_jit_object *attr = jit_object_new(_jit_sym_jit_attr_offset, "myval", _jit_sym_float32, attrflags,
   (method)NULL, (method)NULL, calcoffset(t_jit_foo, myval));
jit_class_addattr(_jit_foo_class, attr);
@endcode


@section chapter_jit_objectmodel_arrayattrs Array Attributes

Attributes can, in addition to referencing single values, also refer to arrays of data. The class jit_attribute_offset_array is used in this instance. The constructor for the class jit_attr_offset_array() has the following prototype:

@code
t_jit_object *jit_attr_offset_array_new(char *name, t_symbol *type, long size,
   long flags, method mget, method mset, long offsetcount, long offset);
@endcode

When this constructor is called via jit_object_new(), additionally the class name, _jit_sym_jit_attr_offset_array() (a global variable equivalent to gensym("jit_attr_offset_array") ) must be passed as the first parameter, followed by the above arguments, which are passed on to the constructor.

The name, type, flags, mget, mset and offset arguments are identical to those specified above.

The size argument specifies the maximum length of the array (the allocated size of the array in the Jitter object struct). The offsetcount specifies the byte offset in the object struct, where the actual length of the array can be queried/set. This value should be specified as a long. This value is used by default getters and setters when querying and setting the attribute's value. As with the jit_attr_offset object, if you have both custom accessors, this value is ignored.

The following sample listing demonstrates the creation of a simple instance of the jit_attr_offset_array() class for an object defined as:

@code
typedef struct _jit_foo
{
   t_jit_object     ob;
   long             myarray[10]; // max of 10 entries in this array
   long             myarraycount; // actual number being used
} t_jit_foo;

long attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
t_jit_object *attr = jit_object_new(_jit_sym_jit_attr_offset_array, "myarray",
   _jit_sym_long, 10, attrflags, (method)0L, (method)0L,
   calcoffset(t_jit_foo, myarraycount), calcoffset(t_jit_foo, myarray));
jit_class_addattr(_jit_foo_class, attr);
@endcode


@section chapter_jit_objectmodel_attrnotifications Attribute Notification

Although the subject of object registration and notification will be covered in greater depth in a forthcoming chapter, it bears noting that attributes of all types (e.g. jit_attr_offset, jit_attr_offset_array and jit_attribute) will, if registered, automatically send notifications to all attached client objects, each time the attribute's value is set.

*/
