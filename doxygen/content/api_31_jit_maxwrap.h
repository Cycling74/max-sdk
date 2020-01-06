/**
	@page chapter_jit_maxwrappers Jitter Max Wrappers

@section chapter_jit_maxwrappers_classes Max Wrapper Classes

In order to expose the Jitter object to the Max patcher, a Max "wrapper" class must be defined. For simple classes, this is largely facilitated by a handful of utility functions that take a Jitter class and create the appropriate wrapper class with default functionality. However, there are occasions which warrant additional intervention to achieve special behavior, such as the use of additional inlets and outlets, integrating with MSP, converting matrix information to and from Max lists, etc. The first Max wrapper class we'll demonstrate won't have any extra complication beyond simply containing a basic Jitter class.

In general it is preferable to design the Jitter class so that it knows nothing about the Max patcher, and that any logic necessary to communicate with the patcher is maintained in the Max wrapper class. In situations where this might seem difficult, this can typically be accomplished by making special methods in the Jitter class that are only meant to be called by the Max wrapper, or by using Jitter's object notification mechanism, which we'll discuss in a future chapter. Below is the minimal Max wrapper class for the minimal Jitter class shown in the last chapter.

@code
typedef struct _max_jit_foo
{
   t_object       ob;
   void         *obex;
} t_max_jit_foo;

void *class_max_jit_foo;

void ext_main(void *r)
{
   void *p,*q;

   // initialize the Jitter class
   jit_foo_init();

   // create the Max class as documented in Writing Max Externals
   setup(&class_max_jit_foo,
      (method) max_jit_foo_new,
      (method) max_jit_foo_free,
      (short)sizeof(t_max_jit_foo),
      0L, A_GIMME, 0);

   // specify a byte offset to keep additional information
   p = max_jit_classex_setup(calcoffset(t_max_jit_foo, obex));

   // look up the Jitter class in the class registry
   q = jit_class_findbyname(gensym("jit_foo"));

   // wrap the Jitter class with the standard methods for Jitter objects
   max_jit_classex_standard_wrap(p, q, 0);

   // add an inlet/outlet assistance method
   addmess((method)max_jit_foo_assist, "assist", A_CANT,0);
}

void max_jit_foo_assist(t_max_jit_foo *x, void *b, long m, long a, char *s)
{
   // no inlet/outlet assistance
}

void max_jit_foo_free(t_max_jit_foo *x)
{
   // lookup the internal Jitter object instance and free
   jit_object_free(max_jit_obex_jitob_get(x));

   // free resources associated with the obex entry
   max_jit_obex_free(x);
}

void *max_jit_foo_new(t_symbol *s, long argc, t_atom *argv)
{
   t_max_jit_foo *x;
   long attrstart;
   void *o;

   // create the wrapper object instance based on the
   // max wrapper class, and the jitter class
   if (x = (t_max_jit_foo *)max_jit_obex_new(class_max_jit_foo,
         gensym("jit_foo")))
   {
      // add a general purpose outlet (rightmost)
      max_jit_obex_dumpout_set(x, outlet_new(x,0L));

      // get normal args if necessary
      attrstart = max_jit_attr_args_offset(argc,argv);

      // instantiate Jitter object
      if (o = jit_object_new(gensym("jit_foo")))
      {
         // set internal jitter object instance
         max_jit_obex_jitob_set(x,o);

         // process attribute arguments
         max_jit_attr_args(x,argc,argv);
      }
      else
      {
         // couldn't instantiate, clean up and report an error
         freeobject((void *)x);
         x = NULL;
         error("jit.foo: out of memory");
      }
   }

   return (x);
}
@endcode


@section chapter_jit_maxwrappers_struct Object Struct

The first thing you must do is define your Max class object struct. As is typical, for standard Max objects the first entry of the object struct must be of type #t_object; for UI objects, it must be of type #t_jbox; for MSP objects, it must be of type #t_pxobject; and for MSP UI objects, it must be of type #t_pxjbox. For more information on these different Max object types, please consult the Max developer documentation. Jitter objects can be wrapped within any of these object types.

You also need to define a pointer to point to extra information and resources needed to effectively wrap your Jitter class. This is typically referred to as the "obex" data, and it is where Jitter stores things like attribute information, the general purpose "dumpout", the internal Jitter object instance, Matrix Operator resources for inlets/outlets, and other auxiliary object information that is not required in a simple Max object. As of Max 4.5 there is also the facility for making use of such additional object information for ordinary Max objects. At the time of this writing, such information is provided in the Pattr developer documentation, as it is relevant to the definition of object attributes, which may be stored and operated upon by the patcher attribute suite of objects.


@section chapter_jit_maxwrappers_classdef Defining Your Max Class

In your Max class registration, which takes place in your external's ext_main() function, you should begin by calling your Jitter class's registration function, typically named something like your_object_name_init(). Then you should proceed to define the Max class's constructor, destructor, object struct size, and typed arguments as is typically accomplished for Max objects via the setup function. In order for your wrapper class to be able to find the obex data, you need to specify a byte offset where this pointer is located within each object instance and allocate the resource in which this is stored in your Max class. This is accomplished with the max_jit_classex_setup() function. You should then look up the Jitter class via jit_class_findbyname(), and wrap it via the max_jit_classex_standard_wrap() function. The max_jit_classex_standard_wrap() function will add all typed methods defined in the Jitter class, as well getter and setter methods for attributes that are not opaque (i.e. private), and all the methods that are common to Jitter objects like getattributes, getstate, summary, importattrs, exportattrs, etc.

Now that you have wrapped the Jitter class, you can add any additional methods that you wish, such as your inlet/outlet assistance method, or something specific to the Max object. Like Jitter objects, you can also add methods which have defer or usurp wrappers, and these should be added via the max_addmethod_defer_low() or max_addmethod_usurp_low() functions, rather than simply using the traditional addmess() function. C


@section chapter_jit_maxwrappers_ctor Constructor

Inside the Max object constructor, there are a few things which are different than building an ordinary Max external. If your object is to respond to attribute arguments, the constructor must be defined to take variable number of typed atom arguments, accomplished with the #A_GIMME signature. You allocate your Max object with the max_jit_obex_new() function, instead of the traditional newobject function. You need to pass your Jitter class name to the max_jit_obex_new() function, which also allocates and initializes your obex data. If successful, you should proceed to add your general purpose "dumpout" outlet, used for returning attribute queries and other methods that provide information like *jit.movie*'s framedump method's frame number or read method success code, with the max_jit_object_dumpout_set() function. If your object is a Matrix Operator that calls max_jit_mop_setup_simple() you will not need to explicitly call max_jit_object_dumpout_set(), as max_jit_mop_setup_simple() calls max_jit_object_dumpout_set() internally.

You then allocate your Jitter object with jit_object_new(), and store it in your obex data via max_jit_obex_jitob_set(). Note that this Jitter object instance can always be found with the function max_jit_obex_jitob_get(). If you wish, prior to allocating your Jitter object, you can look at your non-attribute arguments first — those arguments up to the location returned by max_jit_attr_args_offset() — and make use of them in your Jitter object constructor. It is typical to process attribute arguments after you've allocated both the Max and Jitter object instances, with max_jit_attr_args(), which is passed the Max object instance. If you wanted to use the attribute arguments somehow in your Jitter object constructor, you would need to parse the attribute arguments yourself. If you are not able to allocate your Jitter object (as is the case if you have run out of memory or if Jitter is present but not authorized), it is important that you clean up your Max wrapper object, and return NULL.


@section chapter_jit_maxwrappers_dtor Destructor

In your Max object destructor, you additionally need to free your internal Jitter object with jit_object_free(), and free any additional obex data with max_jit_obex_free(). Matrix operators will typically require that max_jit_mop_free() is called, to free the resources allocated for matrix inputs and outputs. If your object has attached to a registered object for notification via jit_object_attach(), you should detach from that object in your destructor using jit_object_detach() to prevent invalid memory accesses as the registered object might attempt to notify the memory of a now freed object. Object registration and notification is discussed in further detail in following chapters.


@section chapter_jit_maxwrappers_dumpout Dumpout

The general purpose outlet, also known as "dumpout", is automatically used by the Max wrapper object when calling attribute getters and several of the standard methods like summary, or getattributes. It is also available for use in any other Max method you want, most easily accessed with the max_jit_obex_dumpout() function that operates similar to outlet_anything(), but uses the max object pointer rather than the outlet pointer as the first argument. The outlet pointer which has been set in your constructor can be queried with the max_jit_obex_dumpout_get() function, and used in the standard outlet calls. However, it is recommended for routing purposes that any output through the dumpout outlet is a message beginning with a symbol, rather than simply a bang, int, or float. Therefore, outlet_anything() makes the most sense to use.


@section chapter_jit_maxwrappers_inout Additional inlets/outlets

To add additional inlets and outlets to your Max external, a few things should be noted. First, if your object is a Matrix Operator, matrix inlets and outlets will be added either through either the high level max_jit_mop_setup_simple(), or lower level max_jit_mop_inputs() or max_jit_mop_outputs() calls. These Matrix Operator functions will be covered in the chapter on Matrix Operators. Secondly, if your object is an MSP object, all signal inlets and outlets must be leftmost, and all non-signal inlets and outlets must be to the right of any single inlets or outlets—i.e. they cannot be intermixed. Lastly, additional inlets should use proxies (covered in detail in the Max developer documentation) so that your object knows which inlet a message has been received. This is accomplished with the max_jit_obex_proxy_new() function. The inlet number is zero based, and you do not need to create a proxy for the leftmost inlet. Inside any methods which need to know which inlet the triggering message has been received, you can use the max_jit_obex_inletnumber_get() function.


@section chapter_jit_maxwrappers_attrs Max Wrapper Attributes

Sometimes you will need additional attributes which are specific to the Max wrapper class, but are not part of the internal Jitter class. Attributes objects for the Max wrapper class are defined in the same way as those for the Jitter class, documented in the previous chapter. However, these attributes are not added to the Max class with the jit_class_addattr() function, but instead with the max_jit_classex_addattr() function, which takes the classex pointer returned from max_jit_classex_setup(). Attribute flags, and custom getter and setter methods should be defined exactly as they would for the Jitter class.

*/
