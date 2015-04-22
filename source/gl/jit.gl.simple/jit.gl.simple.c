// jit.gl.simple.c
// sample GL group object which draws a simple quadrilateral. no matrixoutput.
// Copyright 2002-2005 - Cycling '74


#include "jit.common.h"
#include "jit.gl.h"

typedef struct _jit_gl_simple
{
	// Max object
	t_object			ob;
	// 3d object extension.  This is what all objects in the GL group have in common.
	void				*ob3d;
} t_jit_gl_simple;

void *_jit_gl_simple_class;

t_jit_err jit_gl_simple_init(void);
t_jit_gl_simple *jit_gl_simple_new(t_symbol *dest_name);
void jit_gl_simple_free(t_jit_gl_simple *x);

t_jit_err jit_gl_simple_draw(t_jit_gl_simple *x);
t_jit_err jit_gl_simple_dest_closing(t_jit_gl_simple *x);
t_jit_err jit_gl_simple_dest_changed(t_jit_gl_simple *x);
t_jit_err build_simple_chunk(t_jit_gl_simple *x);


// --------------------------------------------------------------------------------

t_jit_err jit_gl_simple_init(void)
{
	long ob3d_flags = JIT_OB3D_NO_MATRIXOUTPUT; // no matrix output
	void *ob3d;

	_jit_gl_simple_class = jit_class_new("jit_gl_simple",
										 (method)jit_gl_simple_new, (method)jit_gl_simple_free,
										 sizeof(t_jit_gl_simple),A_DEFSYM,0L);

	// set up object extension for 3d object, customized with flags
	ob3d = jit_ob3d_setup(_jit_gl_simple_class,
						  calcoffset(t_jit_gl_simple, ob3d),
						  ob3d_flags);

	// define our OB3D draw method.  called in automatic mode by
	// jit.gl.render or otherwise through ob3d when banged. this
	// method is A_CANT because our draw setup needs to happen
	// in the ob3d beforehand to initialize OpenGL state
	jit_class_addmethod(_jit_gl_simple_class,
						(method)jit_gl_simple_draw, "ob3d_draw", A_CANT, 0L);

	// define our dest_closing and dest_changed methods.
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


t_jit_gl_simple *jit_gl_simple_new(t_symbol *dest_name)
{
	t_jit_gl_simple *x;

	// make jit object
	if ((x = (t_jit_gl_simple *)jit_object_alloc(_jit_gl_simple_class)))
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
	// free our ob3d data
	jit_ob3d_free(x);
}


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

t_jit_err jit_gl_simple_dest_closing(t_jit_gl_simple *x)
{
	// nothing in this object to free.
	return JIT_ERR_NONE;
}

t_jit_err jit_gl_simple_dest_changed(t_jit_gl_simple *x)
{
	// nothing in this object to update.
	return JIT_ERR_NONE;
}


