/**
	@page chapter_jit_ob3ddetails OB3D Details

The purpose of this chapter is to fill in additional details of Jitter OpenGL, which we refer to as OB3Ds. We will show how to disable and/or override default OB3D attributes and methods, how to support matrix input and output, and manage resources such as textures, display lists, and shaders. This chapter assumes familiarity with the OpenGL API and the OB3D Quick Start chapter. It is out of the scope of our documentation to cover the OpenGL API, so for information on the OpenGL API we recommend consulting the OpenGL Red Book and the many online tutorials.


@section chapter_jit_ob3ddetails_classdef Defining the OB3D Jitter Class

As covered in the OB3D Quick Start, Jitter OB3Ds have a large number of default attributes and methods, and require some specific methods to be defined. This section seeks to clarify these common attributes and methods and how to achieve custom behavior where necessary.

@section chapter_jit_ob3ddetails_draw Declaring a Draw Method

All Jitter OB3Ds must define a method bound to the symbol ob3d_draw. This method takes no arguments in addition to the object struct, and should be defined with the private #A_CANT type signature. The private ob3d_draw method will be called by the standard draw, and drawraw methods that are added to every OB3D. The draw method will set up OpenGL state associated with the default OB3D attributes before calling ob3d_draw, while the drawraw method will not.


@section chapter_jit_ob3ddetails_geom Declaring Destination and Geometry Related Methods

It is possible for attributes of a Jitter OB3D or your render destination to change, requiring resources to be freed or rebuilt. There are three methods used to communicate to an OB3D which such events happen so that the OB3D can manage resources accordingly. They are: dest_closing, which informs an OB3D that the destination is being freed, and any context dependent resources such as textures, display lists, and shaders should be freed; dest_changed, which informs an OB3D that the destination has been rebuilt, and new resources can be allocated; and rebuild_geometry, which informs an OB3D of a change in texture units or some other attribute which affects jit_gl_drawinfo_setup() and other #t_jit_gl_drawinfo related functions, such as jit_gl_texcoord, requiring geometry that uses such functions to be rebuilt. These methods take no arguments in addition to the object struct. The dest_closing and dest_changed methods should be defined with the private #A_CANT type signature, and the rebuild_geometry method is typically defined as typed, but without arguments, so that users have the ability to explicitly call, if deemed necessary. The jit.gl.gridshape SDK project is a good example of these methods as it needs to free and allocate a display list as the render destination changes, and also makes use of jit_gl_texcoord to support multi-texturing, requiring geometry to be rebuilt as the number of texture units or other attributes change.


@section chapter_jit_ob3ddetails_reg Declaring a Register Method

Since all Jitter OB3D objects are named to support reference by name in jit.gl.sketch, and other objects, it is necessary to add the default registration method, jit_object_register(). Object registration and notification are covered in detail in a future chapter.


@section chapter_jit_ob3ddetails_rot Overriding Rotation and Scale Related Attributes

By default, each Jitter OB3D has rotate, rotatexyz, scale, and viewalign attributes added to the class by jit_ob3d_setup(), and these attributes are used in the ob3d_draw_preamble() function to set up OpenGL state prior to calling your object's draw method. These attributes can be disabled by using the #JIT_OB3D_NO_ROTATION_SCALE flag. You can override these attributes by defining your own attributes of the same name, however, you will need to manage any necessary OpenGL state inside of your own draw method with the appropriate calls to glMatrixMode, glTranslate, glRotate, and glScale.


@section chapter_jit_ob3ddetails_color Overriding Color Related Attributes

By default, each Jitter OB3D has color, aux_color, and smooth_shading attributes added to the class by jit_ob3d_setup(), and these attributes are used in the ob3d_draw_preamble function prior to calling your object's draw method. These attributes can be disabled by using the #JIT_OB3D_NO_COLOR flag. You can override these attributes by defining your own attributes of the same name, however, you will need to manage any necessary OpenGL state inside of your own draw method with the appropriate calls to glColor and glShadeModel.


@section chapter_jit_ob3ddetails_texture Overriding Texture Related Attributes

By default, each Jitter OB3D has texture, capture, tex_map, tex_plane_s, and tex_plane_t attributes added to the class by jit_ob3d_setup(), and these attributes are used in the ob3d_draw_preamble() function prior to calling your object's draw method. These attributes can be disabled by using the #JIT_OB3D_NO_TEXTURE flag. You can override these attributes by defining your own attributes of the same name, however, you will need to manage any necessary OpenGL state inside of your own draw method with the appropriate calls to glEnable, glTexGen, jit_gl_bindtexture, jit_gl_unbindtexture, jit_gl_begincapture, and jit_gl_endcapture.


@section chapter_jit_ob3ddetails_lighting Overriding Lighting and Material Related Attributes

By default, each Jitter OB3D has lighting_enable, auto_material, shininess, mat_ambient, mat_diffuse, mat_specular, and mat_emission attributes added to the class by jit_ob3d_setup(), and these attributes are used in the ob3d_draw_preamble function prior to calling your object's draw method. These attributes can be disabled by using the #JIT_OB3D_NO_LIGHTING_MATERIAL flag. You can override these attributes by defining your own attributes of the same name, however, you will need to manage any necessary OpenGL state inside of your own draw method with the appropriate calls to glEnable, glLight, glLightModel, and glMaterial.


@section chapter_jit_ob3ddetails_fog Overriding Fog Related Attributes

By default, each Jitter OB3D has fog and fog_params attributes added to the class by jit_ob3d_setup(), and these attributes are used in the ob3d_draw_preamble function prior to calling your object's draw method. These attributes can be disabled by using the #JIT_OB3D_NO_FOG flag. You can override these attributes by defining your own attributes of the same name, however, you will need to manage any necessary OpenGL state inside of your own draw method with the appropriate calls to glEnable, glHint, and glFog.


@section chapter_jit_ob3ddetails_poly Overriding Polygon Variable Related Attributes

By default, each Jitter OB3D has poly_mode, cull_face, point_size, and line_width attributes added to the class by jit_ob3d_setup(), and these attributes are used in the ob3d_draw_preamble function prior to calling your object's draw method. These attributes can be disabled by using the #JIT_OB3D_NO_POLY_VARS flag. You can override these attributes by defining your own attributes of the same name, however, you will need to manage any necessary OpenGL state inside of your own draw method with the appropriate calls to glPolygonMode, glEnable, glCullFace, glPointSize, and glLineWidth.


@section chapter_jit_ob3ddetails_blend Overriding Blending Related Attributes

By default, each Jitter OB3D has blend_mode and blend_enable attributes added to the class by jit_ob3d_setup(), and these attributes are used in the ob3d_draw_preamble function prior to calling your object's draw method. These attributes can be disabled by using the #JIT_OB3D_NO_BLEND flag. You can override these attributes by defining your own attributes of the same name, however, you will need to manage any necessary OpenGL state inside of your own draw method with the appropriate calls to glEnable and glBlendFunc.


@section chapter_jit_ob3ddetails_aa Overriding Depth Buffer and Antialiasing Related Attributes

By default, each Jitter OB3D has depth_enable and antialias attributes added to the class by jit_ob3d_setup(), and these attributes are used in your ob3d_draw_preamble function prior to calling your object's draw method. These attributes can be disabled by using the #JIT_OB3D_NO_DEPTH and #JIT_OB3D_NO_ANTIALIAS flags, respectively. You can override these attributes by defining your own attributes of the same name, however, you will need to manage any necessary OpenGL state inside of your own draw method with the appropriate calls to glEnable and glHint.


@section chapter_jit_ob3ddetails_matout Overriding Matrixoutput and Automatic Attributes

By default, each Jitter OB3D has matrixoutput and automatic attributes added to the class by jit_ob3d_setup(), and these attributes are used in the ob3d_draw_preamble function prior to calling your object's draw method. These attributes can be disabled by using the #JIT_OB3D_NO_MATRIXOUTPUT and #JIT_OB3D_AUTO_ONLY flags, respectively. You can override these attributes by defining your own attributes of the same name.


@section chapter_jit_ob3ddetails_ui Declaring a User Interface Object

It is possible to declare a user interface OB3D, such as jit.gl.handle. To do so, you must use the #JIT_OB3D_DOES_UI flag to jit_ob3d_setup(), and define a method bound to the symbol ob3d_ui, with the private #A_CANT type signature and prototype similar to the following example from jit.gl.handle:

@code
t_jit_err jit_gl_handle_ui(t_jit_gl_handle *x,
   t_line_3d *p_line, t_wind_mouse_info *p_mouse);
@endcode


@section chapter_jit_ob3ddetails_jitclassctor The Jitter Class Constructor and Destructor

Inside your Jitter class constructor, you must call jit_ob3d_new() with a pointer to your newly allocated object, and your render destination name. The jit_ob3d_new() function allocates an opaque structure that stores the standard OB3D attributes and some additional OB3D state, initializing them to default values, and then setting the pointer at the byte offset specified when calling the jit_ob3d_setup() function in your class definition. If your object supports matrix output or simply uses the #t_jit_glchunk structure when drawing, you should typically allocate your initial #t_jit_glchunk in your constructor using the jit_glchunk_new() or jit_glchunk_grid_new() functions. Use of the #t_jit_glchunk structure and matrix output is described later in this chapter. Similarly, your OB3D Jitter class destructor must call jit_ob3d_free() to free the opaque structure used for common OB3D state, free any allocated instances of #t_jit_glchunk with jit_glchunk_free(), and free any other resources allocated such as display lists or textures.


@section chapter_jit_ob3ddetails_ob3ddraw The OB3D Draw Method

The ob3d_draw method is where all the drawing in your object should take place. It is also where you should typically allocate context dependent resources or query the context state, since you know that your context is valid and has been set. For the most part, the drawing you will perform in your ob3d_draw method will be pure and simple OpenGL, though there are a few caveats which we will cover.


@section chapter_jit_ob3ddetails_glstruct The t_jit_glchunk Structure and Matrix Output

Since Jitter is a general purpose matrix processing framework, it makes sense that you would have the ability to pass geometry information through a Jitter network as matrices if your geometry is well suited to a matrix representation. The cells of your matrix can hold vertex information such as position, texture coordinates, normal vectors, color, and edge flags, and are documented in the "Geometry Under The Hood" Jitter Tutorial. You also have the option of specifying a connections matrix to reference the connectivity of the vertices if it is not implicit in the matrix representation, and a drawing primitive to use when drawing the vertices.

All this information, and whether or not the geometry matrix should be rendered immediately or sent through the Jitter network is managed with the #t_jit_glchunk. An SDK example which demonstrates the use of t_jit_glchunk is jit.gl.gridshape. The t_jit_glchunk structure along with the vertex matrix it contains is allocated by the jit_glchunk_new() or jit_glchunk_grid_new() functions, freed with the jit_glchunk_delete() function, and drawn with the jit_ob3d_draw_chunk() function. For reference, the #t_jit_glchunk structure and relevant chunk flags are provided below:

@code
// jit_glchunk is a public structure to store one
// gl-command's-worth of data, in a format which
// can be passed easily to glDrawRangeElements.

typedef struct _jit_glchunk
{
   t_symbol   *prim;         // GL_TRI_STRIP, GL_TRIANGLES, etc.
   t_jit_object *m_vertex;      // jit_matrix of xyzst... data.
   t_symbol    *m_vertex_name;   // vertex matrix name
   t_jit_object *m_index;      // optional 1d connection matrix
   t_symbol    *m_index_name;   // connection matrix name
   unsigned long m_flags;      // special flags
   void      *next_chunk;      // singly linked list, typically NULL
} t_jit_glchunk;

// flags for chunk creation
#define JIT_GL_CHUNK_IGNORE_TEXTURES      1 << 0
#define JIT_GL_CHUNK_IGNORE_NORMALS      1 << 1
#define JIT_GL_CHUNK_IGNORE_COLORS      1 << 2
#define JIT_GL_CHUNK_IGNORE_EDGES      1 << 3
@endcode


@section chapter_jit_ob3ddetails_caveats OB3D OpenGL Caveats

While you can use any standard Open GL calls inside of your ob3d_draw method. There are a few things worth noting to follow Jitter conventions. The first of which is the binding of texture coordinates. Since Jitter OB3Ds support multi-texturing by default, it is not necessarily satisfactory to submit only one texture coordinate with glTexCoord. Jitter provides some utility routines to set the texture coordinates for as many texture units which are bound, jit_gl_texcoord(1/2/3)(f/fv). Determining how many texture units have been bound by the default OB3D attributes requires some overhead, so rather than perform this overhead with every jit_gl_texcoord call, the jit_gl_texcoord functions take a #t_jit_gl_drawinfo struct as an argument. This struct can be setup once before rendering many vertices with the jit_gl_drawinfo_setup function. Example use of jit_gl_texcoord and jit_gl_drawinfo_setup is in the jit.gl.videoplane SDK project. Another Jitter specific mechanism is the means to bind textures using named instances of jit.gl.texture. It is possible to create and bind your own textures in an OB3D, but you must then perform all maintenance instead of relying on jit.gl.texture to handle this work for you. To bind and unbind an instance of jit.gl.texture, you should call the jit_gl_bindtexture and jit_gl_unbindtexture functions, which take a #t_jit_gl_drawinfo argument, a symbol with the name of the jit.gl.texture instance, and an integer for which texture unit to bind. Unlike binding ordinary textures in OpenGL, it is important to unbind instances of jit.gl.texture, or else problems may arise.


@section chapter_jit_ob3ddetails_attrinfo Getting Information About the OB3D Attributes

Though the default OB3D attributes are typically relevant to the code which is automatically handled for your object prior to calling the ob3d_draw method, it is sometimes necessary to access these values. Since the default OB3D attributes are stored in an opaque ob3d struct member, they are not accessible by your object with a simple struct pointer dereference. Instead, you need to use the jit_attr_get* functions to access these attributes. You should pass in your object struct as the first argument to these functions rather than your ob3d struct member. For example:

@code
   float pos[3];
   jit_attr_getfloat_array(x,gensym("position"),3,pos);
@endcode

Note that if you are acquiring this value often, it is preferable to generate the symbol in advance rather than generate the symbol for every call.


@section chapter_jit_ob3ddetails_context Getting Information About the Context

From within the ob3d_draw, dest_closing, and dest_changed methods, the rendering context has always been set, and you can get a handle to the native context using either the aglGetCurrentContext or wglGetCurrentContext functions. One can also in these methods use standard OpenGL glGet* functions to determine the context's OpenGL state, such as the viewport, transformation matrix. It is not recommended to try and acquire the native context from other methods, or query the OpenGL state as it may not be valid.


@section chapter_jit_ob3ddetails_play Playing Well with Others

It is important to recognize that OpenGL state is persistent, and that there may be objects which rely on OpenGL state that are drawn after your object draws itself. If your object makes any changes to OpenGL state that might affect objects that follow, you should restore the OpenGL state to whatever it was before your routine was called. For example, if your object changes the texture transformation matrix, you should push and pop the texture transformation matrix with glMatrixMode, glPushMatrix, and glPopMatrix, to prevent any problems with other objects.


@section chapter_jit_ob3ddetails_wrapdef Defining the OB3D Max Wrapper Class

As mentioned in the OB3D Quick Start, in your Max wrapper class definition, you need only add a call to the max_ob3d_setup() function to add your standard drawing methods, and the max_jit_ob3d_assist() function as your assist method, unless you wish to define your own custom assist method. Everything else is similar to the standard technique of wrapping a Jitter Class demonstrated in the Max Wrapper Class chapter. Please consult the OB3D Quick Start chapter and the jit.gl.simple SDK project for all necessary information related to the OB3D Max wrapper class.


@section chapter_jit_ob3ddetails_matin Matrix Input

Sometimes it is desirable for an OB3D also support incoming matrices as is the case with jit.gl.videoplane or jit.gl.mesh. It is not recommended to mix and match OB3Ds with MOPs. Conflicts arise with respect to arguments, standard inlets and outlets. Instead, if you wish to support matrix input in your OB3D, you should simply add to your Jitter class a method bound to the symbol jit_matrix, and handle the incoming matrix data according to your needs - for example as texture data in the case of jit.gl.videoplane, or geometry data in the case of jit.gl.mesh. The jit.gl.videoplane SDK project provides an example of an OB3D which also supports matrix input. When it is necessary to have multiple input matrices, this is typically managed by either declaring alternately named methods for each input, or exposing an attribute that specifies which input the jit_matrix method assumes it is being called with. Note that this requires additional logic within the Max wrapper class to map to inlets, as it is not handled automatically.

*/
