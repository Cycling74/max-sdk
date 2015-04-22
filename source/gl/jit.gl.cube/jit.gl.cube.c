// jit.gl.cube.c
// sample GL group object which draws a cube.
//
// author: randall jones
// © 2002 cycling '74


#include "jit.common.h"
#include "jit.gl.h"

typedef struct _jit_gl_cube
{
	// Max object
	t_object			ob;
	// 3d object extension.  This is what all objects in the GL group have in common.
	void				*ob3d;
	// stores one chunk of GL geometry.
	t_jit_glchunk		*chunk;
} t_jit_gl_cube;

void *_jit_gl_cube_class;

t_jit_err jit_gl_cube_init(void);
t_jit_gl_cube *jit_gl_cube_new(t_symbol *dest_name);
void jit_gl_cube_free(t_jit_gl_cube *x);

t_jit_err jit_gl_cube_draw(t_jit_gl_cube *x);
t_jit_err jit_gl_cube_dest_changed(t_jit_gl_cube *x);
t_jit_err build_cube_chunk(t_jit_gl_cube *x);


// --------------------------------------------------------------------------------

t_jit_err jit_gl_cube_init(void)
{
	long ob3d_flags=0;
	void *ob3d;

	_jit_gl_cube_class = jit_class_new("jit_gl_cube", (method)jit_gl_cube_new, (method)jit_gl_cube_free,
									   sizeof(t_jit_gl_cube),A_CANT,0L); //A_CANT = untyped

	// set up object extension for 3d object, customized with flags
	ob3d = jit_ob3d_setup(_jit_gl_cube_class, calcoffset(t_jit_gl_cube, ob3d), ob3d_flags);

	// handle draw method.  called in automatic mode by jit.gl.render, or otherwise through ob3d when banged.
	// this is A_CANT because draw setup needs to happen in the ob3d beforehand.
	jit_class_addmethod(_jit_gl_cube_class, (method)jit_gl_cube_draw, "ob3d_draw", A_CANT, 0L);

	// handle dest_changed method.
	// this method is called by jit.render when the destination context changes: for example,
	// when the user moves the window from one monitor to another.  Anything your object keeps
	// in the OpenGL machine -- textures, display lists, vertex shaders, etc. -- will need to
	// be rebuilt here.
	jit_class_addmethod(_jit_gl_cube_class, (method)jit_gl_cube_dest_changed, "dest_changed", A_CANT, 0L);

	// must register for ob3d use.
	jit_class_addmethod(_jit_gl_cube_class, (method)jit_object_register, 	"register",	A_CANT, 0L);

	jit_class_register(_jit_gl_cube_class);

	return JIT_ERR_NONE;
}


t_jit_gl_cube *jit_gl_cube_new(t_symbol *dest_name)
{
	t_jit_gl_cube *x;

	// make jit object
	if ((x = (t_jit_gl_cube *)jit_object_alloc(_jit_gl_cube_class)))
	{
		// create and attach ob3d.
		jit_ob3d_new(x, dest_name);

		// set instance variable defaults
		x->chunk = 0;

		// build gl geometry chunk containing cube data.
		if (build_cube_chunk(x) != JIT_ERR_NONE)
		{
			error ("jit.gl.cube: couldn't make chunk!");
		}
	}
	else
	{
		x = NULL;
	}
	return x;
}


void jit_gl_cube_free(t_jit_gl_cube *x)
{
	if (x->chunk)
		jit_glchunk_delete(x->chunk);
	jit_ob3d_free(x);
}


t_jit_err jit_gl_cube_draw(t_jit_gl_cube *x)
{
	t_jit_err result = JIT_ERR_NONE;

	// draw our chunk of OpenGL geometry.
	// if the ob3d is in matrixoutput mode, the matrix output is done
	// in jit_ob3d_draw_chunk.  otherwise OpenGL draws the chunk directly.
	result = jit_ob3d_draw_chunk(x->ob3d, x->chunk);

	return result;
}

t_jit_err jit_gl_cube_dest_changed(t_jit_gl_cube *x)
{
	// nothing in this object to update.
	return JIT_ERR_NONE;
}


#pragma mark -

// --------------------------------------------------------------------------------
// cube geometry

// texture map coordinates
#define X1	0.0
#define X2	0.25
#define X3	0.5
#define X4	0.75
#define X5	1.0
#define Y1	0.125
#define Y2	0.375
#define Y3	0.625
#define Y4	0.875
// edge flags with padding for intermediate planes
#define E0	0, 0, 0, 0, 0, 0, 0, 0
#define E1	0, 0, 0, 0, 0, 0, 0, 1

static float cube_v[13*12*3] =
{
	-1, 1, 1,  X2, Y3, 	E1,//3
	-1, 1, -1,  X2, Y4, E1,//2
	1, 1, -1,  X3, Y4, 	E0,//6

	1, 1, -1,  X3, Y4, 	E1,//6
	1, 1, 1, 	X3, Y3, E1,//7
	-1, 1, 1,  X2, Y3, 	E0,//3

	-1, -1, -1, X1, Y2, E1,//0
	-1, 1, -1,  X1, Y3, E1,//2
	-1, 1, 1,  X2, Y3, 	E0,//3

	-1, 1, 1,  X2, Y3, 	E1,//3
	-1, -1, 1,  X2, Y2, E1,//1
	-1, -1, -1, X1, Y2, E0,//0

	-1, -1, 1,  X2, Y2, E1,//1
	-1, 1, 1,  X2, Y3, 	E1,//3
	1, 1, 1, 	X3, Y3, E0,//7

	1, 1, 1, 	X3, Y3, E1,//7
	1, -1, 1,  X3, Y2, 	E1,//5
	-1, -1, 1,  X2, Y2, E0,//1

	1, -1, 1,  X3, Y2, 	E1,//5
	1, 1, 1, 	X3, Y3, E1,//7
	1, 1, -1,  X4, Y3, 	E0,//6

	1, 1, -1,  X4, Y3, 	E1,//6
	1, -1, -1,  X4, Y2, E1,//4
	1, -1, 1,  X3, Y2, 	E0,//5

	1, -1, -1,  X4, Y2, E1,//4
	1, 1, -1,  X4, Y3, 	E1,//6
	-1, 1, -1,  X5, Y3, E0,//2

	-1, 1, -1,  X5, Y3, E1,//2
	-1, -1, -1, X5, Y2, E1,//0
	1, -1, -1,  X4, Y2, E0,//4

	-1, -1, -1, X2, Y1, E1,//0
	-1, -1, 1,  X2, Y2, E1,//1
	1, -1, 1,  X3, Y2, 	E0,//5

	1, -1, 1,  X3, Y2, 	E1,//5
	1, -1, -1,  X3, Y1, E1,//4
	-1, -1, -1, X2, Y1, E0//0

};

#undef X1
#undef X2
#undef X3
#undef X4
#undef X5
#undef Y1
#undef Y2
#undef Y3
#undef Y4
#undef E0
#undef E1


// build a jit_glchunk structure containing the cube data.
t_jit_err build_cube_chunk(t_jit_gl_cube *x)
{
	float *pv;
	int vertices, planes;
	t_jit_err result = JIT_ERR_NONE;

	// delete existing chunk if present
	if (x->chunk)
		jit_glchunk_delete(x->chunk);

	vertices = 12*3;	// 6 side * 2 triangles/side * 3 vertices/triangle
	planes = 13;		// all of them, because edge flags are used.

	// make a new chunk and allocate data for the number of planes, vertices, and
	// edge connections specified.  This chunk will have 13 planes, 12*3 vertices,
	// and no edge connections.
	if ((x->chunk = jit_glchunk_new(_jit_sym_gl_triangles, planes, vertices, 0)))
	{
		// renderer to ignore the color plane and vertex plane.
		// we are not making normals in this object.  the jit.gl.render object
		// wil auto_generate them.
		x->chunk->m_flags = JIT_GL_CHUNK_IGNORE_COLORS | JIT_GL_CHUNK_IGNORE_NORMALS;

		// get a ptr to the data in the chunk's vertex matrix.
		jit_object_method(x->chunk->m_vertex, gensym("getdata"), &pv);

		// copy static vertex and texture coord data into chunk
		jit_copy_bytes(pv, cube_v, planes * vertices * sizeof(float));
	}
	else
		result = JIT_ERR_OUT_OF_MEM;


	return result;
}

