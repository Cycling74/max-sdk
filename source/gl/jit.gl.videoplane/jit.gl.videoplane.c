// jit.gl.videoplane.c
// draw 3d videoplanes.
//
// author: jkc
// Copyright 2002-2005 - Cycling '74
//
// SDK NOTE: On Windows you will need to have the QuickTime SDK installed
// and the paths configured appropriately for this project to build.


#include "jit.common.h"
#include "jit.gl.h"
#include "ext_obex.h"
#ifdef MAC_VERSION
#if TARGET_RT_MAC_MACHO
#include <OpenGL/glext.h>
#else
#include "glext.h"
#endif
#endif
#include "ext_strings.h"
#if !TARGET_RT_MAC_MACHO
#include <math.h>
#ifdef C74_USING_QUICKTIME
#include "ImageCompression.h"
#endif
#endif

#ifdef MAC_VERSION
#define PLATFORM_DYNAMIC_TEX	1
#endif

#ifdef WIN_VERSION
#define PLATFORM_DYNAMIC_TEX	0 	// currently use static methods as default on PC
#endif

typedef struct _jit_gl_videoplane
{
	t_object			ob;
	void				*ob3d;
	t_jit_glchunk		*chunk;
	long				recalc;
	long				dim[2];
	char				gridmode;
	char				displaylist;
	GLuint				dlref;
	void				*texture;
	t_symbol			*texturename;
	long				interp;
	float				nudge;
	float				tex_offset_x;
	float				tex_offset_y;
	float				tex_scale_x;
	float				tex_scale_y;
	long				rect_tex;
	long				client_storage;
	t_symbol			*colormode;
} t_jit_gl_videoplane;

void *_jit_gl_videoplane_class;

t_jit_err jit_gl_videoplane_init(void) ;
t_jit_gl_videoplane *jit_gl_videoplane_new(t_symbol *dest_name);
void jit_gl_videoplane_free(t_jit_gl_videoplane *x);

t_jit_err jit_gl_videoplane_dim(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_videoplane_client_storage(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_videoplane_colormode(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_videoplane_interp(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_videoplane_rect_tex(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_videoplane_texturename(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_videoplane_displaylist(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_videoplane_attr_rebuild(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_videoplane_draw(t_jit_gl_videoplane *x);
t_jit_err jit_gl_videoplane_dest_closing(t_jit_gl_videoplane *x);
t_jit_err jit_gl_videoplane_dest_changed(t_jit_gl_videoplane *x);
t_jit_err jit_gl_videoplane_rebuild_geometry(t_jit_gl_videoplane *x);
void jit_gl_videoplane_get_color(t_jit_gl_videoplane *x, float *red, float *green, float *blue, float *alpha);
void jit_gl_videoplane_jit_matrix(t_jit_gl_videoplane *x, t_symbol *s, int argc, t_atom *argv);
void jit_gl_videoplane_sendtexture(t_jit_gl_videoplane *x, t_symbol *s, int argc, t_atom *argv);

t_jit_err jit_gl_videoplane_drawto_filter(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_videoplane_recalc(t_jit_gl_videoplane *x);

void calc_plane(t_jit_gl_videoplane *x);
void color_surface(t_jit_gl_videoplane *x);
void draw_grid(t_jit_gl_videoplane *x, t_jit_object *matrix, GLenum mode);

t_symbol *ps_bind,*ps_unbind,*ps_jit_gl_texture,*ps_rectangle,*ps_colormode,*ps_mode,*ps_static,*ps_dynamic,*ps_drawto,*ps_texture;
t_symbol *ps_filter,*ps_linear,*ps_nearest;
t_symbol *ps_gridmode,*ps_nudge,*ps_tex_offset_x,*ps_tex_offset_y,*ps_tex_scale_x,*ps_tex_scale_y;


// --------------------------------------------------------------------------------
//

t_jit_err jit_gl_videoplane_init(void)
{
	long attrflags=0;
	long ob3d_flags=0;
	t_jit_object *attr;
	void *ob3d;

	_jit_gl_videoplane_class = jit_class_new("jit_gl_videoplane", (method)jit_gl_videoplane_new, (method)jit_gl_videoplane_free,
							   sizeof(t_jit_gl_videoplane),A_DEFSYM,0L);

	jit_class_addmethod(_jit_gl_videoplane_class, (method)jit_gl_videoplane_jit_matrix,		"jit_matrix", 			A_USURP_LOW, 0);
	jit_class_addmethod(_jit_gl_videoplane_class, (method)jit_gl_videoplane_sendtexture,	"sendtexture", 			A_DEFER_LOW, 0);

	// set up object extension for 3d object, customized with flags
	ob3d = jit_ob3d_setup(_jit_gl_videoplane_class, calcoffset(t_jit_gl_videoplane, ob3d), ob3d_flags);

	// add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"dim",_jit_sym_long,2,attrflags,
						  (method)0L,(method)jit_gl_videoplane_dim,0/*fix*/,calcoffset(t_jit_gl_videoplane,dim));
	jit_attr_addfilterset_clip(attr,2,0,TRUE,FALSE);
	jit_class_addattr(_jit_gl_videoplane_class,attr);
	attr = jit_object_new(_jit_sym_jit_attr_offset,"displaylist",_jit_sym_char,attrflags,
						  (method)0L,(method)jit_gl_videoplane_displaylist,calcoffset(t_jit_gl_videoplane, displaylist));
	jit_class_addattr(_jit_gl_videoplane_class,attr);
	object_addattr_parse(attr,"style",_jit_sym_symbol,0,"onoff");
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Displaylist");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"gridmode",_jit_sym_char,attrflags,
						  (method)0L,(method)jit_gl_videoplane_attr_rebuild,calcoffset(t_jit_gl_videoplane, gridmode));
	jit_class_addattr(_jit_gl_videoplane_class,attr);
	CLASS_ATTR_ENUM(_jit_gl_videoplane_class,"gridmode",0,"trigrid quadgrid");
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Grid Mode\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"interp",_jit_sym_long,attrflags,
						  (method)0L,(method)jit_gl_videoplane_interp,calcoffset(t_jit_gl_videoplane, interp));
	jit_class_addattr(_jit_gl_videoplane_class,attr);
	object_addattr_parse(attr,"style",_jit_sym_symbol,0,"onoff");
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Interp");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"nudge",_jit_sym_float32,attrflags,
						  (method)0L,(method)jit_gl_videoplane_attr_rebuild,calcoffset(t_jit_gl_videoplane, nudge));
	jit_class_addattr(_jit_gl_videoplane_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Nudge");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"tex_offset_x",_jit_sym_float32,attrflags,
						  (method)0L,(method)jit_gl_videoplane_attr_rebuild,calcoffset(t_jit_gl_videoplane, tex_offset_x));
	jit_class_addattr(_jit_gl_videoplane_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Tex Offset X\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"tex_offset_y",_jit_sym_float32,attrflags,
						  (method)0L,(method)jit_gl_videoplane_attr_rebuild,calcoffset(t_jit_gl_videoplane, tex_offset_y));
	jit_class_addattr(_jit_gl_videoplane_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Tex Offset Y\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"tex_scale_x",_jit_sym_float32,attrflags,
						  (method)0L,(method)jit_gl_videoplane_attr_rebuild,calcoffset(t_jit_gl_videoplane, tex_scale_x));
	jit_class_addattr(_jit_gl_videoplane_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Tex Scale X\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"tex_scale_y",_jit_sym_float32,attrflags,
						  (method)0L,(method)jit_gl_videoplane_attr_rebuild,calcoffset(t_jit_gl_videoplane, tex_scale_y));
	jit_class_addattr(_jit_gl_videoplane_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Tex Scale Y\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"rect_tex",_jit_sym_long,attrflags,
						  (method)0L,(method)jit_gl_videoplane_rect_tex,calcoffset(t_jit_gl_videoplane, rect_tex));
	jit_class_addattr(_jit_gl_videoplane_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Rect Tex\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"client_storage",_jit_sym_long,attrflags,
						  (method)0L,(method)jit_gl_videoplane_client_storage,calcoffset(t_jit_gl_videoplane, client_storage));
	jit_class_addattr(_jit_gl_videoplane_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Client Storage\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"colormode",_jit_sym_symbol,attrflags,
						  (method)0L,(method)jit_gl_videoplane_colormode,calcoffset(t_jit_gl_videoplane, colormode));
	jit_class_addattr(_jit_gl_videoplane_class,attr);
	CLASS_ATTR_ENUM(_jit_gl_videoplane_class,"colormode",0,"argb uyvy");
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Colormode");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"texturename",_jit_sym_symbol,attrflags,
						  (method)0L,(method)jit_gl_videoplane_texturename,calcoffset(t_jit_gl_videoplane, texturename));
	jit_class_addattr(_jit_gl_videoplane_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Texture Name\"");

	// define our OB3D draw method.  called in automatic mode by
	// jit.gl.render or otherwise through ob3d when banged. this
	// method is A_CANT because our draw setup needs to happen
	// in the ob3d beforehand to initialize OpenGL state
	jit_class_addmethod(_jit_gl_videoplane_class, (method)jit_gl_videoplane_draw, "ob3d_draw", A_CANT, 0L);

	// define our dest_closing and dest_changed methods.
	// these methods are called by jit.gl.render when the
	// destination context closes or changes: for example, when
	// the user moves the window from one monitor to another. Any
	// resources your object keeps in the OpenGL machine
	// (e.g. textures, display lists, vertex shaders, etc.)
	// will need to be freed when closing, and rebuilt when it has
	// changed.
	jit_class_addmethod(_jit_gl_videoplane_class, (method)jit_gl_videoplane_dest_changed, "dest_changed",	A_CANT, 0L);
	jit_class_addmethod(_jit_gl_videoplane_class, (method)jit_gl_videoplane_dest_closing, "dest_closing",	A_CANT, 0L);

	// rebuild_geometry is called if texture units or other
	// attributes change requiring a rebuild
	jit_class_addmethod(_jit_gl_videoplane_class, (method)jit_gl_videoplane_rebuild_geometry, "rebuild_geometry", 0L);

	// must register for ob3d
	jit_class_addmethod(_jit_gl_videoplane_class, (method)jit_object_register, 				"register",		A_CANT, 0L);

	jit_attr_addfilterset_proc(jit_class_attr_get(_jit_gl_videoplane_class,gensym("drawto")),(method)jit_gl_videoplane_drawto_filter);

	jit_class_register(_jit_gl_videoplane_class);

	ps_bind				= gensym("bind");
	ps_unbind			= gensym("unbind");
	ps_jit_gl_texture	= gensym("jit_gl_texture");
	ps_rectangle		= gensym("rectangle");
	ps_colormode		= gensym("colormode");
	ps_mode				= gensym("mode");
	ps_static			= gensym("static");
	ps_dynamic			= gensym("dynamic");
	ps_drawto			= gensym("drawto");
	ps_texture			= gensym("texture");
	ps_filter			= gensym("filter");
	ps_linear			= gensym("linear");
	ps_nearest			= gensym("nearest");

	ps_gridmode			= gensym("gridmode");
	ps_nudge			= gensym("nudge");
	ps_tex_offset_x		= gensym("tex_offset_x");
	ps_tex_offset_y		= gensym("tex_offset_y");
	ps_tex_scale_x		= gensym("tex_scale_x");
	ps_tex_scale_y		= gensym("tex_scale_y");


	return JIT_ERR_NONE;
}

t_jit_gl_videoplane *jit_gl_videoplane_new(t_symbol *dest_name)
{
	t_jit_gl_videoplane *x;
	t_atom rav[4];
	t_atom *av=rav;

	// make jit object
	if (x = (t_jit_gl_videoplane *)jit_object_alloc(_jit_gl_videoplane_class))
	{
		// create and attach ob3d
		jit_ob3d_new(x, dest_name);

		// set instance variable defaults
		x->dim[0] = 20;
		x->dim[1] = 20;
		x->chunk = jit_glchunk_grid_new(_jit_sym_gl_quad_grid, 12, x->dim[0], x->dim[1]);
		x->recalc = 1;
		x->displaylist = 0;
		x->dlref = 0;
		x->gridmode = 0;

		x->interp = 1;
		x->tex_offset_x = 0.;
		x->tex_offset_y = 0.;
		x->tex_scale_x = 1.;
		x->tex_scale_y = 1.;

		x->nudge = 0.0001;	// hack for edges

		x->rect_tex = 1;
		x->client_storage = PLATFORM_DYNAMIC_TEX;
		x->colormode = gensym("argb");

		jit_atom_setfloat(av,1.);
		jit_atom_setfloat(av+1,1.);
		jit_atom_setfloat(av+2,1.);
		jit_atom_setfloat(av+3,1.);

		jit_object_method(x,gensym("color"),4,av);

		x->texture = jit_object_new(ps_jit_gl_texture,jit_attr_getsym(x,ps_drawto));
		if (x->texture) {
			x->texturename = jit_symbol_unique();
			jit_attr_setsym(x->texture,_jit_sym_name,x->texturename);
			jit_attr_setsym(x->texture,gensym("defaultimage"),gensym("black"));
			jit_attr_setlong(x->texture,ps_rectangle,x->rect_tex);
			jit_attr_setsym(x->texture,ps_mode,x->client_storage?ps_dynamic:ps_static);
			jit_attr_setsym(x,ps_texture,x->texturename);
		} else {
			jit_object_error((t_object *)x,"jit.gl.videoplane: could not create texture");
			x->texturename = _jit_sym_nothing;
		}
	}
	else
	{
		x = NULL;
	}
	return x;
}

t_jit_err jit_gl_videoplane_drawto_filter(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv) {
	if(argc && argv && x->texture) {
		jit_attr_setsym(x->texture,ps_drawto, jit_atom_getsym(argv));
	}
	return JIT_ERR_NONE;
}

t_jit_err jit_gl_videoplane_dim(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv)
{
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

t_jit_err jit_gl_videoplane_client_storage(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv)
{
	long c=jit_atom_getlong(argv);

	x->client_storage = c;
	if (x->texture)
		jit_attr_setsym(x->texture,ps_mode,(c!=0)?ps_dynamic:ps_static);
	return JIT_ERR_NONE;
}

t_jit_err jit_gl_videoplane_colormode(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv)
{
	t_symbol *s=jit_atom_getsym(argv);

	x->colormode = s;
	if (x->texture)
		jit_attr_setsym(x->texture,ps_colormode,s);
	return JIT_ERR_NONE;
}

t_jit_err jit_gl_videoplane_interp(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv)
{
	long c=jit_atom_getlong(argv);

	x->interp = c;
	if (x->texture)
		jit_attr_setsym(x->texture,ps_filter,x->interp?ps_linear:ps_nearest);
	return JIT_ERR_NONE;
}

t_jit_err jit_gl_videoplane_rect_tex(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv)
{
	long c=jit_atom_getlong(argv);

	x->rect_tex = c;
	if (x->texture)
		jit_attr_setlong(x->texture,ps_rectangle,c);
	return JIT_ERR_NONE;
}

t_jit_err jit_gl_videoplane_texturename(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv)
{
	t_symbol *s=jit_atom_getsym(argv);

	x->texturename = s;
	if (x->texture)
		jit_attr_setsym(x->texture,_jit_sym_name,s);
	jit_attr_setsym(x,ps_texture,s);
	return JIT_ERR_NONE;
}

t_jit_err jit_gl_videoplane_displaylist(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv)
{
	if (argc&&argv) {
		x->displaylist = jit_atom_getlong(argv);
		x->recalc = 1;
	}

	return JIT_ERR_NONE;
}

t_jit_err jit_gl_videoplane_attr_rebuild(t_jit_gl_videoplane *x, void *attr, long argc, t_atom *argv)
{
	t_symbol *name = object_method(attr,_jit_sym_getname);

	if (argc&&argv) {
		if (name==ps_gridmode) {
			x->gridmode = (char)jit_atom_getlong(argv);
		} else if (name==ps_nudge) {
			x->nudge = jit_atom_getfloat(argv);
		} else if (name==ps_tex_offset_x) {
			x->tex_offset_x = jit_atom_getfloat(argv);
		} else if (name==ps_tex_offset_y) {
			x->tex_offset_y = jit_atom_getfloat(argv);
		} else if (name==ps_tex_scale_x) {
			x->tex_scale_x = jit_atom_getfloat(argv);
		} else if (name==ps_tex_scale_y) {
			x->tex_scale_y = jit_atom_getfloat(argv);
		}
		x->recalc = 1;
	}

	return JIT_ERR_NONE;
}



t_jit_err jit_gl_videoplane_recalc(t_jit_gl_videoplane *x)
{
	if (x->chunk&&x->chunk->m_vertex) {
		calc_plane(x);
	}

	return JIT_ERR_NONE;
}

void jit_gl_videoplane_free(t_jit_gl_videoplane *x)
{

	if (x->chunk)
		jit_glchunk_delete(x->chunk);
	if (jit_ob3d_set_context(x)==JIT_ERR_NONE) {
		if (x->dlref) {
			glDeleteLists(x->dlref,1);
		}
	}
	if(x->texture) {
		jit_object_free(x->texture);
	}

	jit_ob3d_free(x);
}

void jit_gl_videoplane_jit_matrix(t_jit_gl_videoplane *x, t_symbol *s, int argc, t_atom *argv)
{
	t_symbol *name;
	void *m;
	t_jit_matrix_info info;
	t_atom_long dim[2];

	if ((name=jit_atom_getsym(argv)) != _jit_sym_nothing) {
		m = jit_object_findregistered(name);
		if (!m) {
			jit_object_error((t_object *)x,"jit.gl.videoplane: couldn't get matrix object!");
			return;
		}
	}

	if (x->texture) {
		jit_object_method(m, _jit_sym_getinfo, &info);
		jit_attr_getlong_array(x->texture,_jit_sym_dim,2,dim);
		jit_object_method(x->texture,s,s,argc,argv);
		// switch back to matrix input
		jit_attr_setsym(x,ps_texture,x->texturename);
	}
}

void jit_gl_videoplane_sendtexture(t_jit_gl_videoplane *x, t_symbol *s, int argc, t_atom *argv)
{
	if (x->texture) {
		s = jit_atom_getsym(argv);
		argc--;
		if (argc)
			argv++;
		else
			argv = NULL;
		object_method_typed(x->texture,s,argc,argv,NULL);
	}
}

t_jit_err jit_gl_videoplane_draw(t_jit_gl_videoplane *x)
{
	t_jit_err result = JIT_ERR_NONE;
	GLenum prim;

	CLIP_ASSIGN (x->nudge,0.,0.5);
	prim = (x->gridmode) ? GL_TRIANGLE_STRIP : GL_QUAD_STRIP;

	if (x->recalc) {
		jit_gl_videoplane_recalc(x);
		if (x->displaylist)
		{
			t_jit_gl_context ctx;

			// cache/restore context in case in capture mode
			ctx = jit_gl_get_context();
			jit_ob3d_set_context(x);

			if (x->dlref) {
				glDeleteLists(x->dlref,1);
				x->dlref = 0;
			}
			if (x->dlref=glGenLists(1)) {
				glNewList(x->dlref, GL_COMPILE);
				if (x->chunk&&x->chunk->m_vertex)
					draw_grid(x,x->chunk->m_vertex, prim);
				glEndList();
			}

			jit_gl_set_context(ctx);
		}
		x->recalc = 0;
	}

	// draw our chunk of OpenGL geometry.
	if (x->chunk&&x->chunk->m_vertex) {
		if (!jit_attr_getlong(x,gensym("matrixoutput"))) {
			if (x->displaylist&&x->dlref)
				glCallList(x->dlref);
			else
				draw_grid(x,x->chunk->m_vertex, prim);
			if(jit_attr_getlong(x, _jit_sym_boundcalc))
				jit_object_method(x, gensym("calcbounds"), x->chunk, NULL);
		} else {
			color_surface(x);
			result = jit_ob3d_draw_chunk(x->ob3d, x->chunk); //output matrix
		}
	}

	return result;
}

t_jit_err jit_gl_videoplane_dest_closing(t_jit_gl_videoplane *x)
{
	// destination is closing, free our context dependent resources
	if (x->dlref) {
		glDeleteLists(x->dlref,1);
		x->dlref=NULL;
		x->recalc=1;
	}
	return JIT_ERR_NONE;
}

t_jit_err jit_gl_videoplane_dest_changed(t_jit_gl_videoplane *x)
{
	// destination has changed, requires rebuilding context dependent resources
	if (x->displaylist) x->recalc=1;
	// set our internal texture's drawing destination, too
	//if (x->texture)
	//	jit_attr_setsym(x->texture,ps_drawto,jit_attr_getsym(x,ps_drawto));
	return JIT_ERR_NONE;
}

t_jit_err jit_gl_videoplane_rebuild_geometry(t_jit_gl_videoplane *x)
{
	// some attribute has changed which requires recomputing geometry
	x->recalc=1;
	return JIT_ERR_NONE;
}

void jit_gl_videoplane_get_color(t_jit_gl_videoplane *x, float *red, float *green, float *blue, float *alpha)
{
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

void calc_plane(t_jit_gl_videoplane *x)
{
	int nummajor = x->dim[1]-1;
	int numminor = x->dim[0]-1;
	double majorstep = (2.0/(double)nummajor);
	double minorstep = (2.0/(double)numminor);
	double nummajor_inv = 1./(double)nummajor;
	double numminor_inv = 1./(double)numminor;
	double ratiomajor = 1.;
	double ratiominor = 1.;
	double lominor = (x->nudge*ratiominor);
	double lomajor = (x->nudge*ratiomajor);
	double himinor = (ratiominor-lominor);
	double himajor = (ratiomajor-lomajor);
	double tex_nummajor_inv = (himajor-lomajor)/(double)nummajor;
	double tex_numminor_inv = (himinor-lomajor)/(double)numminor;
	double tx,ty,tx_off,ty_off;
	float *p;
	char *bp=NULL;
	void *m;
	int i,j,rowstride,texwidth;
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

	jit_gl_videoplane_get_color(x,&red,&green,&blue,&alpha);

	tx 		= (x->tex_scale_x==0.)?0.:1./x->tex_scale_x;
	ty 		= (x->tex_scale_y==0.)?0.:1./x->tex_scale_y;
	tx_off 	= x->tex_offset_x;
	ty_off 	= x->tex_offset_y;

	for (i=0; i<=nummajor; i++) {
		double xx,y,tmp;
		y = i*majorstep-1.;

		p = (float *)(bp + i*rowstride);

		for (j=0; j<=numminor; j++) {
			xx = 1.-j*minorstep;

			//vertex
			*p++ = xx;
			*p++ = y;
			*p++ = 0;
			//texture
			//tmp = 1.-((lominor + (numminor-j)*tex_numminor_inv)*tx - tx_off); //flip orientation
			tmp = ((lominor + (numminor-j)*tex_numminor_inv)*tx - tx_off); // don't flip x-orientation
			*p++ = CLAMP(tmp,lominor,himinor);
			tmp = 1.-((lomajor + (nummajor-i)*tex_nummajor_inv)*ty - ty_off); //flip orientation
			*p++ = CLAMP(tmp,lomajor,himajor);
			//normals
			*p++ = 0;
			*p++ = 0;
			*p++ = 1;
			//color rgba
			*p++ = red;
			*p++ = green;
			*p++ = blue;
			*p++ = alpha;
		}
	}
}

void color_surface(t_jit_gl_videoplane *x)
{
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

	jit_gl_videoplane_get_color(x,&red,&green,&blue,&alpha);

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

void draw_grid(t_jit_gl_videoplane *x,t_jit_object *matrix, GLenum mode)
{
	float *p,*p2;
	char *bp=NULL;
	long i,j,rowstride,width,height,planecount,up=0;
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
