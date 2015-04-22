// jit.gl.gridshape.c
// draw 3d gridshapes.
//
// author: jkc
// Copyright 2002-2005 - Cycling '74


#include "jit.common.h"
#include "jit.gl.h"
#include "jit.gl.cache.h"
#include "jit.vecmath.h"
#include "ext_strings.h"
#include "ext_obex.h"
#include <math.h>
#ifndef M_PI
#define M_PI	3.14159265358979323846
#endif

typedef struct _jit_gl_gridshape {
	t_object			ob;
	void				*ob3d;
	t_jit_glchunk		*chunk;
	long				recalc;
	t_symbol			*shape;
	long				dim[2];
	float				rad_minor; // for torus
	char				gridmode;
	long				displaylist;
	long				usetangents;
	void				*mesh;
	void				*tangents;
	t_symbol			*cache_mode;
	GLuint				dlref;
	long				multdraw;
	long				dobounds;
} t_jit_gl_gridshape;

void *_jit_gl_gridshape_class;

t_jit_err jit_gl_gridshape_init(void) ;
t_jit_gl_gridshape *jit_gl_gridshape_new(t_symbol *dest_name);
void jit_gl_gridshape_free(t_jit_gl_gridshape *x);

t_jit_gl_cache *jit_gl_gridshape_get_cache(t_jit_gl_gridshape *x, t_symbol *buffer);
t_jit_err jit_gl_gridshape_drawto_filter(t_jit_gl_gridshape *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_gridshape_shape(t_jit_gl_gridshape *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_gridshape_dim(t_jit_gl_gridshape *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_gridshape_rad_minor(t_jit_gl_gridshape *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_gridshape_displaylist(t_jit_gl_gridshape *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_gridshape_cache_mode_set(t_jit_gl_gridshape *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_gridshape_gridmode(t_jit_gl_gridshape *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_gridshape_rebuild(t_jit_gl_gridshape *x);
t_jit_err jit_gl_gridshape_rebuild_geometry(t_jit_gl_gridshape *x);
t_jit_err jit_gl_gridshape_draw(t_jit_gl_gridshape *x);
t_jit_err jit_gl_gridshape_dest_changed(t_jit_gl_gridshape *x);
void jit_gl_gridshape_get_color(t_jit_gl_gridshape *x, float *red, float *green, float *blue, float *alpha);

t_jit_err jit_gl_gridshape_attr_getcolor(t_jit_gl_gridshape *x, void *attr, long *ac, t_atom **av);
//t_jit_err jit_gl_gridshape_attr_setcolor(t_jit_gl_gridshape *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_gridshape_color_filter(t_jit_gl_gridshape *x, void *attr, long argc, t_atom *argv);

t_jit_err jit_gl_gridshape_recalc(t_jit_gl_gridshape *x);
t_jit_err jit_gl_gridshape_dest_closing(t_jit_gl_gridshape *x);

t_jit_err jit_gl_gridshape_multiple_draw_begin(t_jit_gl_gridshape *x);
t_jit_err jit_gl_gridshape_multiple_draw_end(t_jit_gl_gridshape *x);

void calc_sphere(t_jit_gl_gridshape *x);
void calc_cylinder(t_jit_gl_gridshape *x);
void calc_torus(t_jit_gl_gridshape *x);
void calc_opencylinder(t_jit_gl_gridshape *x);
void calc_circle(t_jit_gl_gridshape *x);
void calc_cube(t_jit_gl_gridshape *x);
void calc_opencube(t_jit_gl_gridshape *x);
void calc_plane(t_jit_gl_gridshape *x);
void calc_capsule(t_jit_gl_gridshape *x);
void calc_cone(t_jit_gl_gridshape *x);

void color_surface(t_jit_gl_gridshape *x);

void draw_grid(t_jit_gl_gridshape *x, t_jit_object *matrix, GLenum mode);

t_symbol *ps_circle,*ps_sphere,*ps_torus,*ps_cylinder,*ps_opencylinder,*ps_cube,*ps_opencube,*ps_plane, *ps_capsule, *ps_cone;
t_symbol *ps_matrixoutput, *ps_immediate;
t_symbol *ps_texunits;
t_symbol *ps_drawraw;

// --------------------------------------------------------------------------------
//

t_jit_err jit_gl_gridshape_init(void) {
	long attrflags=0;
	long ob3d_flags=0;
	t_jit_object *attr;
	void *ob3d;

	_jit_gl_gridshape_class = jit_class_new("jit_gl_gridshape", (method)jit_gl_gridshape_new, (method)jit_gl_gridshape_free,
											sizeof(t_jit_gl_gridshape),A_DEFSYM,0L);

	// set up object extension for 3d object, customized with flags
	ob3d = jit_ob3d_setup(_jit_gl_gridshape_class, calcoffset(t_jit_gl_gridshape, ob3d), ob3d_flags);

	// add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	// shape
	attr = jit_object_new(_jit_sym_jit_attr_offset,"shape",_jit_sym_symbol,attrflags,
						  (method)0L,(method)jit_gl_gridshape_shape,calcoffset(t_jit_gl_gridshape, shape));
	jit_class_addattr(_jit_gl_gridshape_class,attr);
	CLASS_ATTR_ENUM(_jit_gl_gridshape_class,"shape",0,"sphere torus cylinder opencylinder cube opencube plane circle cone capsule");
	CLASS_ATTR_BASIC(_jit_gl_gridshape_class,"shape",0);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Shape");

	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"dim",_jit_sym_long,2,attrflags,
						  (method)0L,(method)jit_gl_gridshape_dim,0/*fix*/,calcoffset(t_jit_gl_gridshape,dim));
	jit_attr_addfilterset_clip(attr,2,0,TRUE,FALSE);
	jit_class_addattr(_jit_gl_gridshape_class,attr);
	CLASS_ATTR_BASIC(_jit_gl_gridshape_class,"dim",0);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Dim");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"rad_minor",_jit_sym_float32,attrflags,
						  (method)0L,(method)jit_gl_gridshape_rad_minor,calcoffset(t_jit_gl_gridshape, rad_minor));
	jit_class_addattr(_jit_gl_gridshape_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Radius Minor\"");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"displaylist",_jit_sym_long,attrflags,
						  (method)0L,(method)jit_gl_gridshape_displaylist,calcoffset(t_jit_gl_gridshape, displaylist));
	object_addattr_parse(attr,"style",_jit_sym_symbol,0,"onoff");
	jit_class_addattr(_jit_gl_gridshape_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Displaylist");

	attr = jit_object_new(_jit_sym_jit_attr_offset, "cache_mode", _jit_sym_symbol, attrflags,
						  (method)0L, (method)jit_gl_gridshape_cache_mode_set, calcoffset(t_jit_gl_gridshape, cache_mode));
	jit_class_addattr(_jit_gl_gridshape_class, (t_jit_object *)attr);
	CLASS_ATTR_ENUM(_jit_gl_gridshape_class,"cache_mode",0,"immediate vertexarray vertexbuffer");
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Cache Mode\"");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"gridmode",_jit_sym_char,attrflags,
						  (method)0L,(method)jit_gl_gridshape_gridmode,calcoffset(t_jit_gl_gridshape, gridmode));
	object_addattr_parse(attr,"style",_jit_sym_symbol,0,"onoff");
	jit_class_addattr(_jit_gl_gridshape_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Grid Mode\"");

	//attr = jit_object_new(_jit_sym_jit_attr_offset_array,"color",_jit_sym_float32,4,attrflags,
	//					  (method)jit_gl_gridshape_attr_getcolor,(method)jit_gl_gridshape_attr_setcolor,0/*fix*/,0);
	//jit_class_addattr(_jit_gl_gridshape_class,attr);
	//object_addattr_parse(attr,"style",_jit_sym_symbol,0,"rgba");
	//object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Color");

	// define our OB3D draw method.  called in automatic mode by
	// jit.gl.render or otherwise through ob3d when banged. this
	// method is A_CANT because our draw setup needs to happen
	// in the ob3d beforehand to initialize OpenGL state
	jit_class_addmethod(_jit_gl_gridshape_class, (method)jit_gl_gridshape_draw, "ob3d_draw", A_CANT, 0L);

	// define our dest_closing and dest_changed methods.
	// these methods are called by jit.gl.render when the
	// destination context closes or changes: for example, when
	// the user moves the window from one monitor to another. Any
	// resources your object keeps in the OpenGL machine
	// (e.g. textures, display lists, vertex shaders, etc.)
	// will need to be freed when closing, and rebuilt when it has
	// changed.
	jit_class_addmethod(_jit_gl_gridshape_class, (method)jit_gl_gridshape_dest_closing, "dest_closing",	A_CANT, 0L);
	jit_class_addmethod(_jit_gl_gridshape_class, (method)jit_gl_gridshape_dest_changed, "dest_changed", A_CANT, 0L);

	// rebuild_geometry is called if texture units or other
	// attributes change requiring a rebuild
	jit_class_addmethod(_jit_gl_gridshape_class, (method)jit_gl_gridshape_rebuild, "rebuild", 0L);
	CLASS_METHOD_ATTR_PARSE(_jit_gl_gridshape_class,"rebuild","undocumented",gensym("long"),0L,"1");
	jit_class_addmethod(_jit_gl_gridshape_class, (method)jit_gl_gridshape_rebuild_geometry, "rebuild_geometry", 0L);

	// must register for ob3d
	jit_class_addmethod(_jit_gl_gridshape_class, (method)jit_object_register, 			"register",		A_CANT, 0L);
	jit_class_addmethod(_jit_gl_gridshape_class, (method)jit_gl_gridshape_get_cache,	"get_cache",	A_CANT, 0L);

	// when drawing from gl.multiple, these are called before and after iterating
	jit_class_addmethod(_jit_gl_gridshape_class, (method)jit_gl_gridshape_multiple_draw_begin, "multiple_draw_begin", A_CANT, 0L);
	jit_class_addmethod(_jit_gl_gridshape_class, (method)jit_gl_gridshape_multiple_draw_end, "multiple_draw_end", A_CANT, 0L);

	jit_attr_addfilterset_proc(jit_class_attr_get(_jit_gl_gridshape_class,gensym("drawto")),(method)jit_gl_gridshape_drawto_filter);
	jit_attr_addfilterset_proc(jit_class_attr_get(_jit_gl_gridshape_class,gensym("color")),(method)jit_gl_gridshape_color_filter);
	
	jit_class_register(_jit_gl_gridshape_class);

	ps_circle 			= gensym("circle");
	ps_sphere 			= gensym("sphere");
	ps_torus 			= gensym("torus");
	ps_cylinder 		= gensym("cylinder");
	ps_opencylinder 	= gensym("opencylinder");
	ps_cube 			= gensym("cube");
	ps_opencube 		= gensym("opencube");
	ps_plane 			= gensym("plane");
	ps_matrixoutput 	= gensym("matrixoutput");
	ps_capsule			= gensym("capsule");
	ps_cone				= gensym("cone");
	ps_immediate		= gensym("immediate");
	ps_texunits			= gensym("texunits");
	ps_drawraw			= gensym("drawraw");

	return JIT_ERR_NONE;
}


t_jit_gl_gridshape *jit_gl_gridshape_new(t_symbol *dest_name) {
	t_jit_gl_gridshape *x = NULL;

	// make jit object
	if (x = (t_jit_gl_gridshape *)jit_object_alloc(_jit_gl_gridshape_class))
	{
		t_jit_matrix_info minfo;

		// create and attach ob3d
		jit_ob3d_new(x, dest_name);

		// set instance variable defaults
		x->shape = ps_sphere;
		x->dim[0] = 20;
		x->dim[1] = 20;
		x->rad_minor = 0.5;
		x->recalc = 1;
		x->displaylist = 0;
		x->gridmode = 0;

		jit_matrix_info_default(&minfo);
		minfo.type = _jit_sym_float32;
		minfo.planecount = 3;
		minfo.dimcount = 2;
		minfo.dim[0] = x->dim[0];
		minfo.dim[1] = x->dim[1];
		x->tangents = jit_object_new(_jit_sym_jit_matrix, &minfo);
		x->mesh = jit_object_new(gensym("jit_gl_mesh"), dest_name);
		jit_attr_setlong(x->mesh, gensym("automatic"), 0);
		jit_attr_setsym(x->mesh, gensym("draw_mode"), gensym("quad_grid"));
		jit_attr_setlong(x->mesh, gensym("use_color"), 0);

		// allocate glchunk matrix used to store and draw geometry
		x->chunk = jit_glchunk_grid_new(_jit_sym_gl_quad_grid, 12, x->dim[0], x->dim[1]);
		x->cache_mode = gensym("vertexarray");
		x->dlref = 0;
		x->multdraw = 0;
		x->dobounds = 0;
	}

	return x;
}

void jit_gl_gridshape_free(t_jit_gl_gridshape *x) {

	if(x->dlref) {
		if(jit_ob3d_set_context(x)==JIT_ERR_NONE) {
			glDeleteLists(x->dlref,1);
		}
	}

	if (x->chunk) {
		jit_glchunk_delete(x->chunk);
	}

	if(x->tangents) {
		jit_object_free(x->tangents);
		x->tangents = 0;
	}

	if(x->mesh) {
		jit_object_free(x->mesh);
		x->mesh = 0;
	}

	jit_ob3d_free(x);
}

t_jit_gl_cache *jit_gl_gridshape_get_cache(t_jit_gl_gridshape *x, t_symbol *buffer) {
	return (t_jit_gl_cache *)jit_object_method(x->mesh, gensym("get_cache"), buffer);
}

t_jit_err jit_gl_gridshape_drawto_filter(t_jit_gl_gridshape *x, void *attr, long argc, t_atom *argv) {
	if(argc && argv) {
		jit_attr_setsym(x->mesh, gensym("drawto"), jit_atom_getsym(argv));
	}
	return JIT_ERR_NONE;
}

t_jit_err jit_gl_gridshape_shape(t_jit_gl_gridshape *x, void *attr, long argc, t_atom *argv) {
	if (argc&&argv) {
		x->shape = jit_atom_getsym(argv);
		x->recalc = 1;
	}
	return JIT_ERR_NONE;
}


t_jit_err jit_gl_gridshape_dim(t_jit_gl_gridshape *x, void *attr, long argc, t_atom *argv) {
	if (argc&&argv&&x->chunk&&x->chunk->m_vertex) {
		t_jit_matrix_info info;

		jit_object_method(x->chunk->m_vertex,_jit_sym_dim, argc, argv);
		jit_object_method(x->chunk->m_vertex,_jit_sym_getinfo,&info);
		x->dim[0] = info.dim[0];
		x->dim[1] = info.dim[1];
		x->recalc = 1;
	}
	return JIT_ERR_NONE;
}

t_jit_err jit_gl_gridshape_rad_minor(t_jit_gl_gridshape *x, void *attr, long argc, t_atom *argv) {
	if (argc&&argv) {
		x->rad_minor = jit_atom_getfloat(argv);
		if (x->shape==ps_torus)
			x->recalc = 1;
	}
	return JIT_ERR_NONE;
}

t_jit_err jit_gl_gridshape_displaylist(t_jit_gl_gridshape *x, void *attr, long argc, t_atom *argv) {
	if (argc&&argv) {
		x->displaylist = jit_atom_getlong(argv);
		x->recalc = 1;
		if(x->cache_mode!=ps_immediate) {
			if(x->displaylist) {
				jit_attr_setsym(x->mesh, gensym("cache_mode"), gensym("displaylist"));
			}
			else {
				jit_attr_setsym(x->mesh, gensym("cache_mode"), x->cache_mode);
			}
		}
	}
	return JIT_ERR_NONE;
}

t_jit_err jit_gl_gridshape_cache_mode_set(t_jit_gl_gridshape *x, void *attr, long argc, t_atom *argv)
{
	t_jit_err err = JIT_ERR_NONE;
	t_symbol *v;
	if(!x||!argc||!argv) return JIT_ERR_INVALID_PTR;
	v = jit_atom_getsym(argv);
	if (x->cache_mode != v) {
		x->cache_mode = v;
		x->recalc = 1;
		if(x->cache_mode!=ps_immediate) {
			if(x->displaylist) {
				jit_attr_setsym(x->mesh, gensym("cache_mode"), gensym("displaylist"));
			}
			else {
				jit_attr_setsym(x->mesh, gensym("cache_mode"), x->cache_mode);
			}
		}
	}
	return err;
}

t_jit_err jit_gl_gridshape_gridmode(t_jit_gl_gridshape *x, void *attr, long argc, t_atom *argv) {
	if (argc&&argv) {
		x->gridmode = jit_atom_getlong(argv);
		if(x->gridmode) {
			jit_attr_setsym(x->mesh, gensym("draw_mode"), gensym("tri_grid"));
		}
		else {
			jit_attr_setsym(x->mesh, gensym("draw_mode"), gensym("quad_grid"));
		}
	}
	return JIT_ERR_NONE;
}

void jit_gl_gridshape_resubmit(t_jit_gl_gridshape *x) {
	t_atom a[1];
	jit_atom_setobj(a, x->tangents);
	jit_object_method(x->mesh, gensym("tangent_matrix"), gensym("tangent_matrix"), 1, a);

	jit_atom_setobj(a, x->chunk->m_vertex);
	jit_attr_setlong(x->mesh, gensym("input_type"), 0);
	jit_object_method(x->mesh, gensym("jit_matrix"), gensym("jit_matrix"), 1, a);
}

t_jit_err jit_gl_gridshape_recalc(t_jit_gl_gridshape *x) {
	if(x->chunk && x->chunk->m_vertex) {
		if (x->shape==ps_plane) {
			calc_plane(x);
		} else if (x->shape==ps_cube) {
			calc_cube(x);
		} else if (x->shape==ps_opencube) {
			calc_opencube(x);
		} else if (x->shape==ps_circle) {
			calc_circle(x);
		} else if (x->shape==ps_opencylinder) {
			calc_opencylinder(x);
		} else if (x->shape==ps_torus) {
			calc_torus(x);
		} else if (x->shape==ps_cylinder) {
			calc_cylinder(x);
		} else if (x->shape==ps_capsule) {
			calc_capsule(x);
		} else if (x->shape==ps_cone) {
			calc_cone(x);
		} else {
			calc_sphere(x);
		}

		jit_gl_gridshape_resubmit(x);
	}

	return JIT_ERR_NONE;
}

t_jit_err jit_gl_gridshape_dest_closing(t_jit_gl_gridshape *x) {
	// destination is closing, free our context dependent resources
	if (x->dlref) {
		glDeleteLists(x->dlref,1);
		x->dlref=0;
		x->recalc=1;
	}

	return JIT_ERR_NONE;
}

t_jit_err jit_gl_gridshape_dest_changed(t_jit_gl_gridshape *x) {
	// destination has changed, requires rebuilding context dependent resources
	jit_attr_setsym(x->mesh, gensym("drawto"), jit_attr_getsym(x, gensym("drawto")));
	if(x->displaylist) {
		x->recalc = 1;
	}

	return JIT_ERR_NONE;
}

t_jit_err jit_gl_gridshape_rebuild(t_jit_gl_gridshape *x) {
	long boundcalc = jit_attr_getlong(x, _jit_sym_boundcalc);
	jit_gl_gridshape_recalc(x);
	if(boundcalc) {
		float bounds[6];
		jit_attr_getfloat_array(x->mesh, _jit_sym_bounds, 6, bounds);
		jit_attr_setfloat_array(x, _jit_sym_bounds, 6, bounds);
	}
	jit_object_method(x->mesh, gensym("rebuild"));
	x->recalc = 0;
	return JIT_ERR_NONE;
}

t_jit_err jit_gl_gridshape_rebuild_geometry(t_jit_gl_gridshape *x) {
	// some attribute has changed which requires recomputing geometry
	x->recalc = 1;
	return JIT_ERR_NONE;
}

void jit_gl_gridshape_draw_begin(t_jit_gl_gridshape *x)
{
	void *ob3d = jit_ob3d_get(x);
	long ntextures = ob3d_texture_count(ob3d);
	long boundcalc = jit_attr_getlong(x, _jit_sym_boundcalc);

	jit_attr_setlong(x->mesh, ps_texunits, ntextures);

	if (x->recalc) {
		jit_gl_gridshape_recalc(x);

		if (x->displaylist&&x->cache_mode==ps_immediate) {
			// cache/restore context in case in capture mode
			t_jit_gl_context ctx = jit_gl_get_context();
			jit_ob3d_set_context(x);

			if (x->dlref) {
				glDeleteLists(x->dlref,1);
				x->dlref = 0;
			}
			if (x->dlref=glGenLists(1)) {
				GLenum prim = (x->gridmode) ? GL_TRIANGLE_STRIP : GL_QUAD_STRIP;
				glNewList(x->dlref, GL_COMPILE);
				if (x->chunk&&x->chunk->m_vertex)
					draw_grid(x,x->chunk->m_vertex, prim);
				glEndList();
			}
			jit_gl_set_context(ctx);
		}
	}

	if(boundcalc != jit_attr_getlong(x->mesh, _jit_sym_boundcalc))
		jit_attr_setlong(x->mesh, _jit_sym_boundcalc, boundcalc);

	if(x->recalc && boundcalc)
		x->dobounds = 1;
}

t_jit_err jit_gl_gridshape_multiple_draw_begin(t_jit_gl_gridshape *x)
{
	x->multdraw = 1;
	jit_gl_gridshape_draw_begin(x);
	return JIT_ERR_NONE;
}

t_jit_err jit_gl_gridshape_multiple_draw_end(t_jit_gl_gridshape *x)
{
	x->multdraw = 0;
	return JIT_ERR_NONE;
}

t_jit_err jit_gl_gridshape_draw(t_jit_gl_gridshape *x) {
	t_jit_err result = JIT_ERR_NONE;

	if(!x->multdraw || x->recalc)
		jit_gl_gridshape_draw_begin(x);

	if (x->chunk&&x->chunk->m_vertex) {
		if (!jit_attr_getlong(x,ps_matrixoutput)) {
			if(x->cache_mode!=ps_immediate) {
				jit_object_method(x->mesh, ps_drawraw);
				glEnable(GL_COLOR_MATERIAL);
			}
			else if (x->displaylist&&x->dlref) {
				glCallList(x->dlref);
			}
			else {
				GLenum prim = (x->gridmode) ? GL_TRIANGLE_STRIP : GL_QUAD_STRIP;
				draw_grid(x,x->chunk->m_vertex, prim);
			}
		} else {
			color_surface(x);
			result = jit_ob3d_draw_chunk(x->ob3d, x->chunk); //output matrix
		}
	}

	if(x->dobounds) {
		float bounds[6];
		jit_attr_getfloat_array(x->mesh, _jit_sym_bounds, 6, bounds);
		jit_attr_setfloat_array(x, _jit_sym_bounds, 6, bounds);
		x->dobounds = 0;
	}

	x->recalc = 0;
	return result;
}

void jit_gl_gridshape_get_color(t_jit_gl_gridshape *x, float *red, float *green, float *blue, float *alpha) {
	long ac=0;
	t_atom *av=NULL;

	jit_object_method(x,gensym("getcolor"),&ac,&av);
	if ((ac==4)&&av) {
		*red 	= jit_atom_getfloat(av);
		*green 	= jit_atom_getfloat(av+1);
		*blue 	= jit_atom_getfloat(av+2);
		*alpha 	= jit_atom_getfloat(av+3);
		jit_freebytes(av,ac*sizeof(t_atom));
	}
}

t_jit_err jit_gl_gridshape_attr_getcolor(t_jit_gl_gridshape *x, void *attr, long *ac, t_atom **av) {
	float color[4];
	void *ob3d = jit_ob3d_get(x);
	long i=0;

	if (*ac && *av) { ; }
	else {
		*ac = 4;
		if (!(*av = jit_getbytes(sizeof(t_atom) **ac))) {
			*ac = 0;
			return JIT_ERR_OUT_OF_MEM;
		}
	}

	ob3d_get_color(ob3d, color);
	for(i=0; i < 4; i++) {
		jit_atom_setfloat((*av)+i, color[i]);
	}

	return JIT_ERR_NONE;
}

t_jit_err jit_gl_gridshape_color_filter(t_jit_gl_gridshape *x, void *attr, long argc, t_atom *argv) {
	float color[4];
	void *ob3d = jit_ob3d_get(x);
	long i=0;

	ob3d_get_color(ob3d, color);
	if (argc>4) argc=4;
	for(i=0; i < argc; i++) {
		color[i] = jit_atom_getfloat(argv+i);
	}

	ob3d_set_color(ob3d, color);
	color_surface(x);
	jit_gl_gridshape_resubmit(x);

	return JIT_ERR_NONE;
}

void jit_gl_gridshape_resize_tangents(t_jit_gl_gridshape *x) {
	t_jit_matrix_info minfo;
	jit_matrix_info_default(&minfo);
	minfo.type = _jit_sym_float32;
	minfo.planecount = 3;
	minfo.dimcount = 2;
	minfo.dim[0] = x->dim[0];
	minfo.dim[1] = x->dim[1];
	jit_object_method(x->tangents, _jit_sym_setinfo, &minfo);
	jit_object_method(x->tangents, _jit_sym_getinfo, &minfo);
}

void calc_sphere(t_jit_gl_gridshape *x) {
	int nummajor = x->dim[1]-1;
	int numminor = x->dim[0]-1;
	double majorstep = (M_PI/(double)nummajor);
	double minorstep = (2.0*M_PI/(double)numminor);
	double nummajor_inv = 1./(double)nummajor;
	double numminor_inv = 1./(double)numminor;
	float *p;
	char *bp=NULL;
	void *m;
	int i,j,rowstride;
	t_jit_matrix_info info;
	float red,green,blue,alpha;
	char *bt=NULL;
	t_jit_matrix_info tinfo;
	float *ptangent = 0;

	if (!x->chunk) {
		return;
	}

	if (!(m=x->chunk->m_vertex)) {
		return;
	}

	jit_object_method(m, _jit_sym_getinfo, &info);
	jit_object_method(m, _jit_sym_getdata, &bp);

	jit_gl_gridshape_resize_tangents(x);
	jit_object_method(x->tangents, _jit_sym_getinfo, &tinfo);
	jit_object_method(x->tangents, _jit_sym_getdata, &bt);

	if(!bp || !bt) {
		return;
	}


	rowstride = info.dimstride[1];

	jit_gl_gridshape_get_color(x,&red,&green,&blue,&alpha);

	for (i=0; i<=nummajor; i++) {
		double a = i*majorstep;	// phi
		double r = jit_math_sin(a);
		double z = jit_math_cos(a);
		double c,x,y;

		p = (float *)(bp + i*rowstride);
		ptangent = (float *)(bt + i*tinfo.dimstride[1]);

		for (j=0; j<=numminor; j++) {
			c = j*minorstep;	// theta
			x = r*jit_math_cos(c);
			y = r*jit_math_sin(c);

			//vertex
			*p++ = x;
			*p++ = y;
			*p++ = z;
			//texture
			*p++ = j*numminor_inv;
			*p++ = i*nummajor_inv;
			//normals
			*p++ = x;
			*p++ = y;
			*p++ = z;
			//color rgba
			*p++ = red;
			*p++ = green;
			*p++ = blue;
			*p++ = alpha;


			*ptangent++ = jit_math_cos(c+M_PI/4)*jit_math_sin(a);
			*ptangent++ = jit_math_sin(c+M_PI/4)*jit_math_sin(a);
			*ptangent++ = jit_math_cos(a);
		}
	}
}

void calc_opencylinder(t_jit_gl_gridshape *x) {
	int nummajor = x->dim[1]-1;
	int numminor = x->dim[0]-1;
	double majorstep = (2./(double)nummajor);
	double minorstep = (2.0*M_PI/(double)numminor);
	double nummajor_inv = 1./(double)nummajor;
	double numminor_inv = 1./(double)numminor;
	float *p;
	char *bp=NULL;
	void *m;
	int i,j,rowstride;
	t_jit_matrix_info info;
	float red,green,blue,alpha;
	char *bt=NULL;
	t_jit_matrix_info tinfo;
	float *ptangent = 0;

	if (!x->chunk)
		return;

	if (!(m=x->chunk->m_vertex))
		return;

	jit_object_method(m,_jit_sym_getinfo,&info);
	jit_object_method(m,_jit_sym_getdata,&bp);

	jit_gl_gridshape_resize_tangents(x);
	jit_object_method(x->tangents, _jit_sym_getinfo, &tinfo);
	jit_object_method(x->tangents, _jit_sym_getdata, &bt);

	if(!bp || !bt) {
		return;
	}

	rowstride = info.dimstride[1];

	jit_gl_gridshape_get_color(x,&red,&green,&blue,&alpha);

	for (i=0; i<=nummajor; i++) {
		double z = 1. - i*majorstep;
		double c,x,y;

		p = (float *)(bp + i*rowstride);
		ptangent = (float *)(bt + i*tinfo.dimstride[1]);

		for (j=0; j<=numminor; j++) {
			c = j*minorstep;
			x = jit_math_cos(c);
			y = jit_math_sin(c);

			//vertex
			*p++ = x;
			*p++ = y;
			*p++ = z;
			//texture
			*p++ = j*numminor_inv;
			*p++ = i*nummajor_inv;
			//normals
			*p++ = x;
			*p++ = y;
			*p++ = 0.;
			//color rgba
			*p++ = red;
			*p++ = green;
			*p++ = blue;
			*p++ = alpha;

			*ptangent++ = jit_math_cos(c+M_PI/4);
			*ptangent++ = jit_math_sin(c+M_PI/4);
			*ptangent++ = 0.;
		}
	}
}

void calc_cylinder(t_jit_gl_gridshape *x) {
	int nummajor = x->dim[1]-3;
	int numminor = x->dim[0]-1;
	double majorstep = (2./(double)nummajor);
	double minorstep = (2.0*M_PI/(double)numminor);
	double nummajor_inv = 1./(double)nummajor;
	double numminor_inv = 1./(double)numminor;
	float *p;
	char *bp=NULL;
	void *m;
	int i,j,rowstride;
	t_jit_matrix_info info;
	float red,green,blue,alpha;
	char *bt=NULL;
	t_jit_matrix_info tinfo;
	float *ptangent = 0;

	if (!x->chunk)
		return;

	if (!(m=x->chunk->m_vertex))
		return;

	jit_object_method(m,_jit_sym_getinfo,&info);
	jit_object_method(m,_jit_sym_getdata,&bp);

	jit_gl_gridshape_resize_tangents(x);
	jit_object_method(x->tangents, _jit_sym_getinfo, &tinfo);
	jit_object_method(x->tangents, _jit_sym_getdata, &bt);

	if(!bp || !bt) {
		return;
	}

	if (x->dim[1]<3)
		return;

	rowstride = info.dimstride[1];

	jit_gl_gridshape_get_color(x,&red,&green,&blue,&alpha);

	p = (float *)bp;
	ptangent = (float *)(bt);

	//top
	for (j=0; j<=numminor; j++) {
		//vertex
		*p++ = 0;
		*p++ = 0;
		*p++ = 1;
		//texture
		*p++ = j*numminor_inv;
		*p++ = 0;
		//normals
		*p++ = 0;
		*p++ = 0;
		*p++ = 1;
		//color rgba
		*p++ = red;
		*p++ = green;
		*p++ = blue;
		*p++ = alpha;

		*ptangent++ = 1.;
		*ptangent++ = 0.;
		*ptangent++ = 0.;
	}
	//body
	for (i=0; i<=nummajor; i++) {
		double z = 1. - i*majorstep;
		double c,x,y;

		p = (float *)(bp + (i+1)*rowstride);
		ptangent = (float *)(bt + (i+1)*tinfo.dimstride[1]);

		for (j=0; j<=numminor; j++) {
			c = j*minorstep;
			x = jit_math_cos(c);
			y = jit_math_sin(c);

			//vertex
			*p++ = x;
			*p++ = y;
			*p++ = z;
			//texture
			*p++ = j*numminor_inv;
			*p++ = i*nummajor_inv;
			//normals
			*p++ = x;
			*p++ = y;
			*p++ = 0.;
			//color rgba
			*p++ = red;
			*p++ = green;
			*p++ = blue;
			*p++ = alpha;

			*ptangent++ = jit_math_cos(c+M_PI/4);
			*ptangent++ = jit_math_sin(c+M_PI/4);
			*ptangent++ = 0.;
		}
	}
	//bottom
	p = (float *)(bp + (nummajor+2)*rowstride);
	ptangent = (float *)(bt + (nummajor+2)*tinfo.dimstride[1]);

	for (j=0; j<=numminor; j++) {
		//vertex
		*p++ = 0;
		*p++ = 0;
		*p++ = -1;
		//texture
		*p++ = j*numminor_inv;
		*p++ = 1;
		//normals
		*p++ = 0;
		*p++ = 0;
		*p++ = -1;
		//color rgba
		*p++ = red;
		*p++ = green;
		*p++ = blue;
		*p++ = alpha;

		*ptangent++ = -1.;
		*ptangent++ = 0.;
		*ptangent++ = 0.;
	}
}

void calc_cube(t_jit_gl_gridshape *x) {
	int nummajor = x->dim[1]-5;
	int numminor = x->dim[0];
	double majorstep = (2./(double)nummajor);
	double nummajor_inv = 1./(double)nummajor;
	float *p;
	char *bp=NULL;
	void *m;
	int i,j,rowstride;
	t_jit_matrix_info info;
	float red,green,blue,alpha;
	double tx,ty,vx,vy,nx,ny;
	long numface0,numface1,numface2,numface3;
	long tface0,tface1,tface2;
	char *bt=NULL;
	t_jit_matrix_info tinfo;
	float *ptangent = 0;

	if (!x->chunk)
		return;

	if (!(m=x->chunk->m_vertex))
		return;

	jit_object_method(m,_jit_sym_getinfo,&info);
	jit_object_method(m,_jit_sym_getdata,&bp);

	jit_gl_gridshape_resize_tangents(x);
	jit_object_method(x->tangents, _jit_sym_getinfo, &tinfo);
	jit_object_method(x->tangents, _jit_sym_getdata, &bt);

	if(!bp || !bt) {
		return;
	}

	if (x->dim[1]<3)
		return;

	rowstride = info.dimstride[1];

	jit_gl_gridshape_get_color(x,&red,&green,&blue,&alpha);

	numface0 = numminor/4;
	tface0 = numface0;

	numface1 = numminor/2 - tface0;
	tface1 = tface0+numface1;

	numface2 = (3*numminor)/4 - tface1;
	tface2 = tface1+numface2;

	numface3 = numminor - tface2;


	p = (float *)bp;
	ptangent = (float *)(bt);

	//top
	for (j=0; j<numminor; j++) {
		//vertex
		*p++ = 0;
		*p++ = 0;
		*p++ = 1;
		//texture
		*p++ = 0.5;
		*p++ = 0.5;
		//normals
		*p++ = 0;
		*p++ = 0;
		*p++ = 1;
		//color rgba
		*p++ = red;
		*p++ = green;
		*p++ = blue;
		*p++ = alpha;

		*ptangent++ = 1.;
		*ptangent++ = 0.;
		*ptangent++ = 0.;
	}
	p = (float *)(bp + rowstride);
	ptangent = (float *)(bt + tinfo.dimstride[1]);

	for (j=0; j<numminor; j++) {
		if (j<tface0) {
			tx=(float)j/(float)(numface0-1);
			vx=1;
			vy=(2.*tx)-1.;
			ty=1-tx; //swap
			tx=1;
		} else if (j<tface1) {
			tx=(float)(j-tface0)/(float)(numface1-1);
			vx=1.-(2.*tx);
			vy=1;
			tx=1-tx;
			ty=0;
		} else if (j<tface2) {
			tx=(float)(j-tface1)/(float)(numface2-1);
			vx=-1;
			vy=1.-(2.*tx);
			ty=tx; //swap
			tx=0;
		} else {
			tx=(float)(j-tface2)/(float)(numface3-1);
			vx=(2.*tx)-1.;
			vy=-1;
			ty=1;
		}
		//vertex
		*p++ = vx;
		*p++ = vy;
		*p++ = 1;
		//texture
		*p++ = tx;
		*p++ = ty;
		//normals
		*p++ = 0;
		*p++ = 0;
		*p++ = 1;
		//color rgba
		*p++ = red;
		*p++ = green;
		*p++ = blue;
		*p++ = alpha;

		*ptangent++ = 1.;
		*ptangent++ = 0.;
		*ptangent++ = 0.;
	}

	//body
	for (i=0; i<=nummajor; i++) {
		double vz = 1. - i*majorstep;

		p = (float *)(bp + (i+2)*rowstride);
		ptangent = (float *)(bt + (i+2)*tinfo.dimstride[1]);

		for (j=0; j<numminor; j++) {
			float tangx, tangy;
			if (j<tface0) {
				tx=(float)j/(float)(numface0-1);
				vx=1;
				vy=(2.*tx)-1.;
				nx=1;
				ny=0;
				tangx = 0;
				tangy = -1;
			} else if (j<tface1) {
				tx=(float)(j-tface0)/(float)(numface1-1);
				vx=1.-(2.*tx);
				vy=1;
				nx=0;
				ny=1;
				tangx = 1;
				tangy = 0;
			} else if (j<tface2) {
				tx=(float)(j-tface1)/(float)(numface2-1);
				vx=-1;
				vy=1.-(2.*tx);
				nx=-1;
				ny=0;
				tangx = 0;
				tangy = 1;
			} else {
				tx=(float)(j-tface2)/(float)(numface3-1);
				vx=(2.*tx)-1.;
				vy=-1;
				nx=0;
				ny=-1;
				tangx = -1;
				tangy = 0;
			}
			//vertex
			*p++ = vx;
			*p++ = vy;
			*p++ = vz;
			//texture
			//*p++ = j*numminor_inv;
			*p++ = tx;
			*p++ = i*nummajor_inv;
			//normals
			*p++ = nx;
			*p++ = ny;
			*p++ = 0;
			//color rgba
			*p++ = red;
			*p++ = green;
			*p++ = blue;
			*p++ = alpha;

			*ptangent++ = tangx;
			*ptangent++ = tangy;
			*ptangent++ = 0.;
		}
	}

	//bottom
	p = (float *)(bp + (nummajor+3)*rowstride);
	ptangent = (float *)(bt + (nummajor+3)*tinfo.dimstride[1]);

	for (j=0; j<numminor; j++) {
		if (j<tface0) {
			tx=(float)j/(float)(numface0-1);
			vx=1;
			vy=(2.*tx)-1.;
			ty=1-tx; //swap
			tx=1;
		} else if (j<tface1) {
			tx=(float)(j-tface0)/(float)(numface1-1);
			vx=1.-(2.*tx);
			vy=1;
			tx=1-tx;
			ty=0;
		} else if (j<tface2) {
			tx=(float)(j-tface1)/(float)(numface2-1);
			vx=-1;
			vy=1.-(2.*tx);
			ty=tx; //swap
			tx=0;
		} else {
			tx=(float)(j-tface2)/(float)(numface3-1);
			vx=(2.*tx)-1.;
			vy=-1;
			ty=1;
		}
		//vertex
		*p++ = vx;
		*p++ = vy;
		*p++ = -1;
		//texture
		*p++ = tx;
		*p++ = ty;
		//normals
		*p++ = 0;
		*p++ = 0;
		*p++ = -1;
		//color rgba
		*p++ = red;
		*p++ = green;
		*p++ = blue;
		*p++ = alpha;

		*ptangent++ = -1.;
		*ptangent++ = 0.;
		*ptangent++ = 0.;
	}
	p = (float *)(bp + (nummajor+4)*rowstride);
	ptangent = (float *)(bt + (nummajor+4)*tinfo.dimstride[1]);

	for (j=0; j<numminor; j++) {
		//vertex
		*p++ = 0;
		*p++ = 0;
		*p++ = -1;
		//texture
		*p++ = 0.5;
		*p++ = 0.5;
		//normals
		*p++ = 0;
		*p++ = 0;
		*p++ = -1;
		//color rgba
		*p++ = red;
		*p++ = green;
		*p++ = blue;
		*p++ = alpha;

		*ptangent++ = -1.;
		*ptangent++ = 0.;
		*ptangent++ = 0.;
	}
}

void calc_opencube(t_jit_gl_gridshape *x) {
	int nummajor = x->dim[1]-1;
	int numminor = x->dim[0];
	double majorstep = (2./(double)nummajor);
	double nummajor_inv = 1./(double)nummajor;
	float *p;
	char *bp=NULL;
	void *m;
	int i,j,rowstride;
	t_jit_matrix_info info;
	float red,green,blue,alpha;
	double tx,vx,vy,nx,ny;
	long numface0,numface1,numface2,numface3;
	long tface0,tface1,tface2;
	char *bt=NULL;
	t_jit_matrix_info tinfo;
	float *ptangent = 0;

	if (!x->chunk)
		return;

	if (!(m=x->chunk->m_vertex))
		return;

	jit_object_method(m,_jit_sym_getinfo,&info);
	jit_object_method(m,_jit_sym_getdata,&bp);

	jit_gl_gridshape_resize_tangents(x);
	jit_object_method(x->tangents, _jit_sym_getinfo, &tinfo);
	jit_object_method(x->tangents, _jit_sym_getdata, &bt);

	if(!bp || !bt) {
		return;
	}

	if (x->dim[1]<3)
		return;

	rowstride = info.dimstride[1];

	jit_gl_gridshape_get_color(x,&red,&green,&blue,&alpha);

	numface0 = numminor/4;
	tface0 = numface0;

	numface1 = numminor/2 - tface0;
	tface1 = tface0+numface1;

	numface2 = (3*numminor)/4 - tface1;
	tface2 = tface1+numface2;

	numface3 = numminor - tface2;


	p = (float *)bp;

	//body
	for (i=0; i<=nummajor; i++) {
		double vz = 1. - i*majorstep;

		p = (float *)(bp + i*rowstride);
		ptangent = (float *)(bt + i*tinfo.dimstride[1]);

		for (j=0; j<numminor; j++) {
			float tangx, tangy;
			if (j<tface0) {
				tx=(float)j/(float)(numface0-1);
				vx=1;
				vy=(2.*tx)-1.;
				nx=1;
				ny=0;
				tangx = 0;
				tangy = -1;
			} else if (j<tface1) {
				tx=(float)(j-tface0)/(float)(numface1-1);
				vx=1.-(2.*tx);
				vy=1;
				nx=0;
				ny=1;
				tangx = 1;
				tangy = 0;
			} else if (j<tface2) {
				tx=(float)(j-tface1)/(float)(numface2-1);
				vx=-1;
				vy=1.-(2.*tx);
				nx=-1;
				ny=0;
				tangx = 0;
				tangy = 1;
			} else {
				tx=(float)(j-tface2)/(float)(numface3-1);
				vx=(2.*tx)-1.;
				vy=-1;
				nx=0;
				ny=-1;
				tangx = -1;
				tangy = 0;
			}
			//vertex
			*p++ = vx;
			*p++ = vy;
			*p++ = vz;
			//texture
			*p++ = tx;
			*p++ = i*nummajor_inv;
			//normals
			*p++ = nx;
			*p++ = ny;
			*p++ = 0;
			//color rgba
			*p++ = red;
			*p++ = green;
			*p++ = blue;
			*p++ = alpha;

			*ptangent++ = tangx;
			*ptangent++ = tangy;
			*ptangent++ = 0.;
		}
	}
}

void calc_circle(t_jit_gl_gridshape *x) {
	int nummajor = x->dim[1]-1;
	int numminor = x->dim[0]-1;
	double majorstep = (1./(double)nummajor);
	double minorstep = (2.0*M_PI/(double)numminor);
	double nummajor_inv = 1./(double)nummajor;
	double numminor_inv = 1./(double)numminor;
	float *p;
	char *bp=NULL;
	void *m;
	int i,j,rowstride;
	t_jit_matrix_info info;
	float red,green,blue,alpha;
	char *bt=NULL;
	t_jit_matrix_info tinfo;
	float *ptangent = 0;

	if (!x->chunk)
		return;

	if (!(m=x->chunk->m_vertex))
		return;

	jit_object_method(m,_jit_sym_getinfo,&info);
	jit_object_method(m,_jit_sym_getdata,&bp);

	jit_gl_gridshape_resize_tangents(x);
	jit_object_method(x->tangents, _jit_sym_getinfo, &tinfo);
	jit_object_method(x->tangents, _jit_sym_getdata, &bt);

	if(!bp || !bt) {
		return;
	}

	rowstride = info.dimstride[1];

	jit_gl_gridshape_get_color(x,&red,&green,&blue,&alpha);

	for (i=0; i<=nummajor; i++) {
		double r = 1. - i*majorstep;

		p = (float *)(bp + i*rowstride);
		ptangent = (float *)(bt + i*tinfo.dimstride[1]);

		for (j=0; j<=numminor; j++) {
			double c = 2.0*M_PI - j*minorstep;
			double c2 = 2.0*M_PI - (j+1)*minorstep;
			double x = r*jit_math_cos(c);
			double y = r*jit_math_sin(c);
			double x2 = r*jit_math_cos(c2);
			double y2 = r*jit_math_sin(c2);

			//vertex
			*p++ = x;
			*p++ = y;
			*p++ = 0;
			//texture
			*p++ = j*numminor_inv;
			*p++ = i*nummajor_inv;
			//normals
			*p++ = 0;
			*p++ = 0;
			*p++ = 1;
			//color rgba
			*p++ = red;
			*p++ = green;
			*p++ = blue;
			*p++ = alpha;


			ptangent[0] = x2-x;
			ptangent[1] = y2-y;
			ptangent[2] = 0.;
			JIT_VEC3_NORMALIZE(ptangent);
			ptangent += 3;
		}
	}
}

void calc_plane(t_jit_gl_gridshape *x) {
	int nummajor = x->dim[1]-1;
	int numminor = x->dim[0]-1;
	double majorstep = (2.0/(double)nummajor);
	double minorstep = (2.0/(double)numminor);
	double nummajor_inv = 1./(double)nummajor;
	double numminor_inv = 1./(double)numminor;
	float *p;
	char *bp=NULL;
	void *m;
	int i,j,rowstride;
	t_jit_matrix_info info;
	float red,green,blue,alpha;
	char *bt=NULL;
	t_jit_matrix_info tinfo;
	float *ptangent = 0;

	if (!x->chunk)
		return;

	if (!(m=x->chunk->m_vertex))
		return;

	jit_object_method(m,_jit_sym_getinfo,&info);
	jit_object_method(m,_jit_sym_getdata,&bp);

	jit_gl_gridshape_resize_tangents(x);
	jit_object_method(x->tangents, _jit_sym_getinfo, &tinfo);
	jit_object_method(x->tangents, _jit_sym_getdata, &bt);

	if(!bp || !bt) {
		return;
	}

	rowstride = info.dimstride[1];

	jit_gl_gridshape_get_color(x,&red,&green,&blue,&alpha);

	for (i=0; i<=nummajor; i++) {
		double x,y;
		y = i*majorstep-1.;

		p = (float *)(bp + i*rowstride);
		ptangent = (float *)(bt + i*tinfo.dimstride[1]);

		for (j=0; j<=numminor; j++) {
			x = 1.-j*minorstep;

			//vertex
			*p++ = x;
			*p++ = y;
			*p++ = 0;
			//texture
			*p++ = 1.-j*numminor_inv;
			*p++ = i*nummajor_inv;
			//normals
			*p++ = 0;
			*p++ = 0;
			*p++ = 1;
			//color rgba
			*p++ = red;
			*p++ = green;
			*p++ = blue;
			*p++ = alpha;

			*ptangent++ = 1;
			*ptangent++ = 0;
			*ptangent++ = 0.;
		}
	}
}

void calc_torus(t_jit_gl_gridshape *x) {
	int nummajor = x->dim[1]-1;
	int numminor = x->dim[0]-1;
	double majorstep = (2.0*M_PI/(double)nummajor);
	double minorstep = (2.0*M_PI/(double)numminor);
	double nummajor_inv = 1./(double)nummajor;
	double numminor_inv = 1./(double)numminor;
	float *p;
	char *bp=NULL;
	void *m;
	int i,j,rowstride;
	t_jit_matrix_info info;
	float red,green,blue,alpha;
	double radminor=x->rad_minor;
	char *bt=NULL;
	t_jit_matrix_info tinfo;
	float *ptangent = 0;

	if (!x->chunk)
		return;

	if (!(m=x->chunk->m_vertex))
		return;

	jit_object_method(m,_jit_sym_getinfo,&info);
	jit_object_method(m,_jit_sym_getdata,&bp);

	jit_gl_gridshape_resize_tangents(x);
	jit_object_method(x->tangents, _jit_sym_getinfo, &tinfo);
	jit_object_method(x->tangents, _jit_sym_getdata, &bt);

	if(!bp || !bt) {
		return;
	}

	rowstride = info.dimstride[1];

	jit_gl_gridshape_get_color(x,&red,&green,&blue,&alpha);

	for (i=0; i<=nummajor; i++) {
		double a = i*majorstep;
		double x = jit_math_cos(a);
		double y = jit_math_sin(a);
		double c,b,r,z;

		p = (float *)(bp + i*rowstride);
		ptangent = (float *)(bt + i*tinfo.dimstride[1]);

		for (j=0; j<=numminor; j++) {
			b = j*minorstep;
			c = jit_math_cos(b);
			r = radminor*c + 1.;
			z = jit_math_sin(b);

			//vertex
			*p++ = x*r;
			*p++ = y*r;
			*p++ = z*radminor;
			//texture
			*p++ = j*numminor_inv;
			*p++ = i*nummajor_inv;
			//normals
			*p++ = x*c;
			*p++ = y*c;
			*p++ = z;
			//color rgba
			*p++ = red;
			*p++ = green;
			*p++ = blue;
			*p++ = alpha;

			*ptangent++ = -(1+radminor*c)*y;
			*ptangent++ = (1+radminor*c)*x;
			*ptangent++ = 0.;
		}
	}
}

void calc_capsule(t_jit_gl_gridshape *x) {
	int nummajor = x->dim[1]-1;
	int numminor = x->dim[0]-1;
	double majorstep = (M_PI/(double)nummajor);
	double minorstep = (2.0*M_PI/(double)numminor);
	double nummajor_inv = 1./(double)nummajor;
	double numminor_inv = 1./(double)numminor;
	float *p;
	char *bp=NULL;
	void *m;
	int i,j,rowstride;
	t_jit_matrix_info info;
	float red,green,blue,alpha;
	char *bt=NULL;
	t_jit_matrix_info tinfo;
	float *ptangent = 0;

	if (!x->chunk)
		return;

	if (!(m=x->chunk->m_vertex))
		return;

	jit_object_method(m,_jit_sym_getinfo,&info);
	jit_object_method(m,_jit_sym_getdata,&bp);

	jit_gl_gridshape_resize_tangents(x);
	jit_object_method(x->tangents, _jit_sym_getinfo, &tinfo);
	jit_object_method(x->tangents, _jit_sym_getdata, &bt);

	if(!bp || !bt) {
		return;
	}

	rowstride = info.dimstride[1];

	jit_gl_gridshape_get_color(x,&red,&green,&blue,&alpha);

	for (i=0; i<=nummajor; i++) {
		double a = i*majorstep;
		double r = jit_math_sin(a);
		double znorm = jit_math_cos(a);
		double z = (znorm>0 ? znorm+0.5 : znorm-0.5);
		double c,x,y;

		p = (float *)(bp + i*rowstride);
		ptangent = (float *)(bt + i*tinfo.dimstride[1]);

		for (j=0; j<=numminor; j++) {
			c = j*minorstep;
			x = r*jit_math_cos(c);
			y = r*jit_math_sin(c);

			//vertex
			*p++ = x;
			*p++ = y;
			*p++ = z;
			//texture
			*p++ = j*numminor_inv;
			*p++ = i*nummajor_inv;
			//normals
			*p++ = x;
			*p++ = y;
			*p++ = znorm;
			//color rgba
			*p++ = red;
			*p++ = green;
			*p++ = blue;
			*p++ = alpha;

			*ptangent++ = jit_math_cos(c+M_PI/4)*jit_math_sin(a);
			*ptangent++ = jit_math_sin(c+M_PI/4)*jit_math_sin(a);
			*ptangent++ = jit_math_cos(a);
		}
	}
}

void calc_cone(t_jit_gl_gridshape *x) {
	int nummajor = x->dim[1]-2;
	int numminor = x->dim[0]-1;
	double majorstep = (2./(double)nummajor);
	double minorstep = (2.0*M_PI/(double)numminor);
	double nummajor_inv = 1./(double)nummajor;
	double numminor_inv = 1./(double)numminor;
	float *p;
	char *bp=NULL;
	void *m;
	int i,j,rowstride;
	t_jit_matrix_info info;
	float red,green,blue,alpha;
	char *bt=NULL;
	t_jit_matrix_info tinfo;
	float *ptangent = 0;

	if (!x->chunk)
		return;

	if (!(m=x->chunk->m_vertex))
		return;

	jit_object_method(m,_jit_sym_getinfo,&info);
	jit_object_method(m,_jit_sym_getdata,&bp);

	jit_gl_gridshape_resize_tangents(x);
	jit_object_method(x->tangents, _jit_sym_getinfo, &tinfo);
	jit_object_method(x->tangents, _jit_sym_getdata, &bt);

	if(!bp || !bt) {
		return;
	}

	if (x->dim[1]<3)
		return;

	rowstride = info.dimstride[1];

	jit_gl_gridshape_get_color(x,&red,&green,&blue,&alpha);

	//body
	for (i=0; i<=nummajor; i++) {
		double z = 0.5 - i*majorstep*0.5;
		double c,x,y;
		double scaler = i*majorstep*0.5;

		p = (float *)(bp + i*rowstride);
		ptangent = (float *)(bt + i*tinfo.dimstride[1]);

		for (j=0; j<=numminor; j++) {
			c = j*minorstep;
			x = jit_math_cos(c)*scaler;
			y = jit_math_sin(c)*scaler;

			//vertex
			*p++ = x;
			*p++ = y;
			*p++ = z;
			//texture
			*p++ = j*numminor_inv;
			*p++ = i*nummajor_inv;
			//normals
			*p++ = x;
			*p++ = y;
			*p++ = 0.;
			//color rgba
			*p++ = red;
			*p++ = green;
			*p++ = blue;
			*p++ = alpha;

			*ptangent++ = jit_math_cos(c+M_PI/4)*0.70710678118655;
			*ptangent++ = jit_math_sin(c+M_PI/4)*0.70710678118655;
			*ptangent++ = 0.70710678118655;
		}
	}

	p = (float *)(bp + (nummajor+1)*rowstride);
	ptangent = (float *)(bt + (nummajor+1)*tinfo.dimstride[1]);
	//top
	for (j=0; j<=numminor; j++) {
		//vertex
		*p++ = 0;
		*p++ = 0;
		*p++ = -0.5;
		//texture
		*p++ = j*numminor_inv;
		*p++ = 0;
		//normals
		*p++ = 0;
		*p++ = 0;
		*p++ = 1;
		//color rgba
		*p++ = red;
		*p++ = green;
		*p++ = blue;
		*p++ = alpha;

		*ptangent++ = 1.;
		*ptangent++ = 0.;
		*ptangent++ = 0.;
	}
}

void color_surface(t_jit_gl_gridshape *x) {
	float *p;
	char *bp=NULL;
	void *m;
	int i,j,rowstride;
	t_jit_matrix_info info;
	float red,green,blue,alpha;

	if (!x->chunk)
		return;

	if (!(m=x->chunk->m_vertex))
		return;

	jit_object_method(m,_jit_sym_getinfo,&info);
	jit_object_method(m,_jit_sym_getdata,&bp);

	if (!bp)
		return;

	rowstride = info.dimstride[1];

	jit_gl_gridshape_get_color(x,&red,&green,&blue,&alpha);

	p = (float *)bp;
	if ((p[8]==red)&&(p[9]==green)&&(p[10]==blue)&&(p[11]==alpha))
		return;
	for (i=0; i<info.dim[1]; i++) {
		p = (float *)(bp + i*rowstride);
		for (j=0; j<info.dim[0]; j++) {
			p += 8;
			//color rgba
			*p++ = red;
			*p++ = green;
			*p++ = blue;
			*p++ = alpha;

		}
	}
}


//_____________________________________________________
// util

#define _I_X	0
#define _I_Y	1
#define _I_Z	2
#define _I_S	3
#define _I_T	4
#define _I_NX	5
#define _I_NY	6
#define _I_NZ	7
#define _I_R	8
#define _I_G	9
#define _I_B	10
#define _I_A	11

//not drawing per vertex color in this object

void draw_grid(t_jit_gl_gridshape *x,t_jit_object *matrix, GLenum mode)
{
	float *p,*p2;
	char *bp=NULL;
	long i,j,rowstride,width,height,planecount;
	t_jit_matrix_info info;
	t_jit_gl_drawinfo drawinfo;

	if(jit_gl_drawinfo_setup(x,&drawinfo)) return;

	if (!matrix) return;

	jit_object_method(matrix,_jit_sym_getinfo,&info);
	jit_object_method(matrix,_jit_sym_getdata,&bp);

	if (!bp) return;

	planecount	= info.planecount;
	rowstride 	= info.dimstride[1];
	height 		= info.dim[1]-1;
	width 		= info.dim[0];

	for (i=0; i<height; i++) {
		p = (float *)(bp + i*rowstride);
		p2 = (float *)(bp + (i+1)*rowstride);

		glBegin(mode);
		switch (planecount) {
		case 16:
		case 15:
		case 14:
		case 13:
		case 12:
			for (j=0; j<width; j++) {

				glNormal3f(p[_I_NX],p[_I_NY],p[_I_NZ]);
//				glColor4f(p[_I_R],p[_I_G],p[_I_B],p[_I_A]);
				jit_gl_texcoord2f(&drawinfo,p[_I_S],p[_I_T]);
				glVertex3f(p[_I_X],p[_I_Y],p[_I_Z]);

				glNormal3f(p2[_I_NX],p2[_I_NY],p2[_I_NZ]);
//				glColor4f(p2[_I_R],p2[_I_G],p2[_I_B],p2[_I_A]);
				jit_gl_texcoord2f(&drawinfo,p2[_I_S],p2[_I_T]);
				glVertex3f(p2[_I_X],p2[_I_Y],p2[_I_Z]);

				p+=planecount;
				p2+=planecount;
			}
			break;
		case 11:
		case 10:
		case 9:
		case 8:
			for (j=0; j<width; j++) {

				glNormal3f(p[_I_NX],p[_I_NY],p[_I_NZ]);
				jit_gl_texcoord2f(&drawinfo,p[_I_S],p[_I_T]);
				glVertex3f(p[_I_X],p[_I_Y],p[_I_Z]);

				glNormal3f(p2[_I_NX],p2[_I_NY],p2[_I_NZ]);
				glTexCoord2f(p2[_I_S],p2[_I_T]);
				jit_gl_texcoord2f(&drawinfo,p2[_I_S],p2[_I_T]);
				glVertex3f(p2[_I_X],p2[_I_Y],p2[_I_Z]);

				p+=planecount;
				p2+=planecount;
			}
			break;
		case 7:
		case 6:
		case 5:
			for (j=0; j<width; j++) {

				jit_gl_texcoord2f(&drawinfo,p[_I_S],p[_I_T]);
				glVertex3f(p[_I_X],p[_I_Y],p[_I_Z]);

				glTexCoord2f(p2[_I_S],p2[_I_T]);
				jit_gl_texcoord2f(&drawinfo,p2[_I_S],p2[_I_T]);
				glVertex3f(p2[_I_X],p2[_I_Y],p2[_I_Z]);

				p+=planecount;
				p2+=planecount;
			}
			break;
		case 4:
		case 3:
			for (j=0; j<width; j++) {

				glVertex3f(p[_I_X],p[_I_Y],p[_I_Z]);

				glVertex3f(p2[_I_X],p2[_I_Y],p2[_I_Z]);

				p+=planecount;
				p2+=planecount;
			}
			break;
		}
		glEnd();
	}
}
