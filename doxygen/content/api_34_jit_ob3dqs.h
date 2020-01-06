/**
	@page chapter_jit_ob3dqs OB3D QuickStart

The purpose of this chapter is to give a quick and high level overview of how to develop a simple Jitter OpenGL object which draws geometry within a named rendering context - we refer to such an object as an OB3D. For this task, we will use the jit.gl.simple SDK example. More details such as how to make an OpenGL object which deals with resources such as display lists and textures, wishes to support matrix input/output, or needs greater access to OpenGL state will appear in the following chapter. This chapter assumes familiarity with Jitter's OpenGL object suite used from the Max patcher, as discussed in the Jitter Tutorial, and the preceding chapters on the Jitter object model and Max wrapper classes.

@section chapter_jit_ob3dqs_classdef Defining the OB3D Jitter Class

Jitter OB3Ds typically are defined to have all or most of the common OB3D attributes and methods discussed in the Group-OB3D section of the Jitter HTML object reference. These include attributes and methods to set the rendering destination name, object name, color, lighting, texturing, modelview transform, depth buffering, polygon mode, and several other common tasks. These common attributes and methods are added by the call to the jit_ob3d_setup() function in your Jitter class definition, after calling jit_class_new, but typically prior to defining other methods and attributes. For an OB3D, Jitter needs to store additional information in your object. This information is stored in an opaque pointer in your object struct, typically named ob3d. The byte offset to your OB3D data pointer is passed into jit_ob3d_setup(). You can override any default attributes and methods added by jit_ob3d_setup() with the following flags:

@code
#define JIT_OB3D_NO_ROTATION_SCALE      1 << 0
#define JIT_OB3D_NO_POLY_VARS         1 << 1
#define JIT_OB3D_NO_BLEND              1 << 2
#define JIT_OB3D_NO_TEXTURE         1 << 3
#define JIT_OB3D_NO_MATRIXOUTPUT      1 << 4
#define JIT_OB3D_AUTO_ONLY         1 << 5
#define JIT_OB3D_DOES_UI         1 << 6
#define JIT_OB3D_NO_DEPTH         1 << 7
#define JIT_OB3D_NO_ANTIALIAS         1 << 8
#define JIT_OB3D_NO_FOG            1 << 9
#define JIT_OB3D_NO_LIGHTING_MATERIAL      1 << 10
#define JIT_OB3D_HAS_LIGHTS         1 << 11
#define JIT_OB3D_HAS_CAMERA         1 << 12
#define JIT_OB3D_IS_RENDERER         1 << 13
#define JIT_OB3D_NO_COLOR         1 << 14
@endcode

Aside from the attributes and methods added to your class by jit_ob3d_setup(), you need to define a private, untyped method bound to the symbol ob3d_draw. This method is where your object does all its drawing. It is called by the standard OB3D draw and drawraw methods. The OB3D draw method sets up all of the OpenGL state associated with the common OB3D attributes before calling your private ob3d_draw method. The drawraw method simply sets the context before calling your private ob3d_draw method. Because OB3Ds support being named for use within jit.gl.sketch*'s drawobject command, you must also add a private, untyped "register" method associated with the jit_object_register() function. Let's examine the *jit.gl.simple SDK project as an example:

@code
t_jit_err jit_gl_simple_init(void)
{
   long ob3d_flags = JIT_OB3D_NO_MATRIXOUTPUT; // no matrix output
   void *ob3d;

   _jit_gl_simple_class = jit_class_new("jit_gl_simple",
      (method)jit_gl_simple_new, (method)jit_gl_simple_free,
      sizeof(t_jit_gl_simple),0L);

   // set up object extension for 3d object, customized with flags
   ob3d = jit_ob3d_setup(_jit_gl_simple_class,
            calcoffset(t_jit_gl_simple, ob3d),
            ob3d_flags);

   // define the OB3D draw method.  called in automatic mode by
   // jit.gl.render or otherwise through ob3d when banged. this
   // method is A_CANT because our draw setup needs to happen
   // in the ob3d beforehand to initialize OpenGL state
   jit_class_addmethod(_jit_gl_simple_class,
      (method)jit_gl_simple_draw, "ob3d_draw", A_CANT, 0L);

   // define the dest_closing and dest_changed methods.
   // these methods are called by jit.gl.render when the
   // destination context closes or changes: for example, when
   // the user moves the window from one monitor to another. Any
   // resources your object keeps in the OpenGL machine
   // (e.g. textures, display lists, vertex shaders, etc.)
   // will need to be freed when closing, and rebuilt when it has
   // changed. In this object, these functions do nothing, and
   // could be omitted.
   jit_class_addmethod(_jit_gl_simple_class,
      (method)jit_gl_simple_dest_closing, "dest_closing", A_CANT, 0L);
   jit_class_addmethod(_jit_gl_simple_class,
      (method)jit_gl_simple_dest_changed, "dest_changed", A_CANT, 0L);

   // must register for ob3d use
   jit_class_addmethod(_jit_gl_simple_class,
      (method)jit_object_register, "register", A_CANT, 0L);

   jit_class_register(_jit_gl_simple_class);

   return JIT_ERR_NONE;
}
@endcode


@section chapter_jit_ob3dqs_ctordtor The Jitter Class Constructor/Destructor

In your OB3D Jitter Class constructor, you need to pass in your rendering destination name as the first argument. You should call the jit_ob3d_new() function with your destination name argument to initialize the OB3D data pointer, associating it with your rendering destination. In your destructor, you need to free your OB3D data pointer with jit_ob3d_free(). The jit.gl.simple constructor and destructors are below as an example.

@code
t_jit_gl_simple *jit_gl_simple_new(t_symbol *dest_name)
{
   t_jit_gl_simple *x;

   // make jit object
   if (x = (t_jit_gl_simple *)jit_object_alloc(_jit_gl_simple_class))
   {
      // create and attach ob3d
      jit_ob3d_new(x, dest_name);
   }
   else
   {
      x = NULL;
   }
   return x;
}


void jit_gl_simple_free(t_jit_gl_simple *x)
{
   // free ob3d data
   jit_ob3d_free(x);
}
@endcode


@section chapter_jit_ob3dqs_draw The OB3D draw Method

Your OB3D draw method, bound to the ob3d_draw symbol, is where all of your drawing code takes place. It is called automatically when your associated jit.gl.render object receives a bang, if your automatic and enabled attributes are turned on, as they are by default. It is also called if your Max wrapper object receives a bang, or the draw or drawraw messages. With the exception of the drawraw message, all of the standard OB3D object state is setup prior to calling your ob3d_draw method, so you needn't setup things like the modelview transform, color, lighting properties, texture information, if your object doesn't have special needs. The following example from jit.gl.simple, just draws a simple quadrilateral.

@code
t_jit_err jit_gl_simple_draw(t_jit_gl_simple *x)
{
   t_jit_err result = JIT_ERR_NONE;

   // draw our OpenGL geometry.
   glBegin(GL_QUADS);
   glVertex3f(-1,-1,0);
   glVertex3f(-1,1,0);
   glVertex3f(1,1,0);
   glVertex3f(1,-1,0);
   glEnd();

   return result;
}
@endcode

Since this example is meant only to show a minimal object which draws geometry with standard OpenGL calls, there is no texture information or vertex normals specified. However, all standard OpenGL calls should work within the ob3d_draw method. This example also doesn't show matrix output, as accomplished by jit_ob3d_draw_chunk(), which will be discussed in the following chapter on OB3D details.


@section chapter_jit_ob3dqs_maxwrap Defining the OB3D Max Wrapper Class

For OB3Ds, the Max wrapper class has less extra work than for MOPs. In your Max wrapper class definition, you need only add a call to the max_ob3d_setup() function to add your standard drawing methods, and the max_jit_ob3d_assist() function as your assist method, unless you wish to define your own custom assist method. Everything else is similar to the standard technique of wrapping a Jitter Class demonstrated in the Max Wrapper Class chapter.

@code
void ext_main(void *r)
{
   void *classex, *jitclass;

   // initialize Jitter class
   jit_gl_simple_init();

   // create Max class
   setup((t_messlist **)&max_jit_gl_simple_class,
      (method)max_jit_gl_simple_new, (method)max_jit_gl_simple_free,
      (short)sizeof(t_max_jit_gl_simple), 0L, A_GIMME, 0);

   // specify a byte offset to keep additional information about our object
   classex = max_jit_classex_setup(calcoffset(t_max_jit_gl_simple, obex));

   // look up Jitter class in the class registry
   jitclass = jit_class_findbyname(gensym("jit_gl_simple"));

   // wrap Jitter class with the standard methods for Jitter objects
   max_jit_classex_standard_wrap(classex, jitclass, 0);

      // use standard ob3d assist method
   addmess((method)max_jit_ob3d_assist, "assist", A_CANT,0);

   // add methods for 3d drawing
   max_ob3d_setup();
}
@endcode


@section chapter_jit_ob3dqs_wrapctor The Max Class Constructor/Destructor

Your Max class' constructor should be similar to the standard Max wrapper constructor, but the differences worth noting are that you should pass your first normal argument, which is the rendering destination, on to your Jitter OB3D constructor, and create a second outlet for matrix output, attached to your object's OB3D data. For your destructor, there is nothing additional you need to do for OB3D. The jit.gl.simple Max class' constructor and destructor are provided as examples.

@code
void *max_jit_gl_simple_new(t_symbol *s, long argc, t_atom *argv)
{
   t_max_jit_gl_simple *x;
   void *jit_ob;
   long attrstart;
   t_symbol *dest_name_sym = _jit_sym_nothing;

   if (x = (t_max_jit_gl_simple *) max_jit_obex_new(
      max_jit_gl_simple_class, gensym("jit_gl_simple")))
   {
      // get first normal arg, the destination name
      attrstart = max_jit_attr_args_offset(argc,argv);
      if (attrstart&&argv)
      {
         jit_atom_arg_getsym(&dest_name_sym, 0, attrstart, argv);
      }

      // instantiate Jitter object with dest_name arg
      if (jit_ob = jit_object_new(
         gensym("jit_gl_simple"), dest_name_sym))
      {
         // set internal jitter object instance
         max_jit_obex_jitob_set(x, jit_ob);

         // add a general purpose outlet (rightmost)
         max_jit_obex_dumpout_set(x, outlet_new(x,NULL));

         // process attribute arguments
         max_jit_attr_args(x, argc, argv);

         // attach the jit object's ob3d to a new outlet
         // this outlet is used in matrixoutput mode
         max_jit_ob3d_attach(x, jit_ob, outlet_new(x, "jit_matrix"));
      }
      else
      {
         error("jit.gl.simple: could not allocate object");
         freeobject((t_object *)x);
         x = NULL;
      }
   }
   return (x);
}

void max_jit_gl_simple_free(t_max_jit_gl_simple *x)
{
   // lookup our internal Jitter object instance and free
   jit_object_free(max_jit_obex_jitob_get(x));

   // free resources associated with our obex entry
   max_jit_obex_free(x);
}
@endcode

*/
