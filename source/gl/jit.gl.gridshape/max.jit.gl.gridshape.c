// max.jit.gl.gridshape.c
// draw 3d gridshapes.
//
// author: jkc
// Copyright 2002-2005 - Cycling '74


#include "jit.common.h"
#include "jit.gl.h"


typedef struct _max_jit_gl_gridshape
{
	t_object		ob;
	void			*obex;
} t_max_jit_gl_gridshape;

t_jit_err jit_gl_gridshape_init(void);

void *max_jit_gl_gridshape_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_gl_gridshape_free(t_max_jit_gl_gridshape *x);
t_class *max_jit_gl_gridshape_class;


void ext_main(void *r)
{
	void *classex, *jitclass;

	jit_gl_gridshape_init();
	setup((t_messlist **)&max_jit_gl_gridshape_class, (method)max_jit_gl_gridshape_new, (method)max_jit_gl_gridshape_free, (short)sizeof(t_max_jit_gl_gridshape),
		  0L, A_GIMME, 0);

	classex = max_jit_classex_setup(calcoffset(t_max_jit_gl_gridshape, obex));
	jitclass = jit_class_findbyname(gensym("jit_gl_gridshape"));
	max_jit_classex_standard_wrap(classex, jitclass, 0); 				// getattributes/dumpout/maxjitclassaddmethods/etc
	addmess((method)max_jit_ob3d_assist, "assist", A_CANT,0);
	addmess((method)max_jit_ob3d_acceptsdrag, "acceptsdrag_unlocked", A_CANT, 0);
	addmess((method)max_jit_ob3d_acceptsdrag, "acceptsdrag_locked", A_CANT, 0);

	// add methods for 3d drawing
	max_ob3d_setup();

}

void max_jit_gl_gridshape_free(t_max_jit_gl_gridshape *x)
{
	max_jit_ob3d_detach(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_gl_gridshape_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_gl_gridshape *x;
	void *jit_ob;
	long attrstart;
	t_symbol *dest_name_sym = _jit_sym_nothing;

	if (x = (t_max_jit_gl_gridshape *)max_jit_obex_new(max_jit_gl_gridshape_class, gensym("jit_gl_gridshape")))
	{
		//get normal args
		attrstart = max_jit_attr_args_offset(argc,argv);
		if (attrstart&&argv)
		{
			jit_atom_arg_getsym(&dest_name_sym, 0, attrstart, argv);
		}

		if (jit_ob = jit_object_new(gensym("jit_gl_gridshape"), dest_name_sym))
		{
			max_jit_obex_jitob_set(x, jit_ob);
			max_jit_obex_dumpout_set(x, outlet_new(x,NULL));
			max_jit_attr_args(x, argc, argv);

			// attach the jit object's ob3d to a new outlet for sending drawing messages.
			max_jit_ob3d_attach(x, jit_ob, outlet_new(x, "jit_matrix"));
		}
		else
		{
			jit_object_error((t_object *)x,"jit.gl.gridshape: could not allocate object");
			freeobject((t_object *)x);
			x = NULL;
		}
	}
	return (x);
}


