// max.jit.gl.videoplane.c
// draw 3d videoplanes.
//
// author: jkc
// Copyright 2002-2005 - Cycling '74


#include "jit.common.h"
#include "jit.gl.common.h"


typedef struct _max_jit_gl_videoplane
{
	t_object		ob;
	void			*obex;
} t_max_jit_gl_videoplane;


void *max_jit_gl_videoplane_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_gl_videoplane_free(t_max_jit_gl_videoplane *x);
t_class *max_jit_gl_videoplane_class;


C74_EXPORT void ext_main(void *r)
{
	t_class *maxclass, *jitclass;
	
	maxclass = class_new("jit.gl.videoplane", (method)max_jit_gl_videoplane_new, (method)max_jit_gl_videoplane_free, sizeof(t_max_jit_gl_videoplane), NULL, A_GIMME, 0);
	max_jit_class_obex_setup(maxclass, calcoffset(t_max_jit_gl_videoplane, obex));
	jitclass = jit_class_findbyname(gensym("jit_gl_videoplane"));
	max_jit_class_wrap_ob3d_inletinfo(maxclass, jitclass, 0);

	class_addmethod(maxclass, (method)max_jit_ob3d_assist, "assist", A_CANT, 0);

	max_jit_class_ob3d_wrap(maxclass);
	class_register(CLASS_BOX, maxclass);
	max_jit_gl_videoplane_class = maxclass;

}

void max_jit_gl_videoplane_free(t_max_jit_gl_videoplane *x)
{
	max_jit_ob3d_detach(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_object_free(x);
}

void *max_jit_gl_videoplane_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_gl_videoplane *x;
	void *jit_ob;
	long attrstart;
	t_symbol *dest_name_sym = _jit_sym_nothing;

	if ((x = (t_max_jit_gl_videoplane *)max_jit_object_alloc(max_jit_gl_videoplane_class, gensym("jit_gl_videoplane"))))
	{
		//get normal args
		attrstart = max_jit_attr_args_offset(argc,argv);
		if (attrstart&&argv)
		{
			jit_atom_arg_getsym(&dest_name_sym, 0, attrstart, argv);
		}

		if ((jit_ob = jit_object_new(gensym("jit_gl_videoplane"), dest_name_sym)))
		{
			max_jit_obex_jitob_set(x, jit_ob);
			max_jit_obex_dumpout_set(x, outlet_new(x,NULL));
			if(s == gensym("jit.gl.layer")) {
				jit_object_method(jit_ob, gensym("make_layer"));
			}
			max_jit_attr_args(x, argc, argv);

			// attach the jit object's ob3d to a new outlet for sending drawing messages.
			max_jit_ob3d_attach(x, jit_ob, outlet_new(x, "jit_matrix"));
		}
		else
		{
			jit_object_error((t_object *)x,"jit.gl.videoplane: could not allocate object");
			freeobject((t_object *)x);
			x = NULL;
		}
	}
	return (x);
}


