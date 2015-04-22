/*
	Copyright 2001-2005 - Cycling '74 / The Trustees of Columbia University in the City of New York.
	R. Luke Dubois luke@cycling74.com
*/

// updated for new architecture by rld, 2/23/02

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_eclipse
{
	t_object		ob;
	void			*obex;
} t_max_jit_eclipse;

t_jit_err jit_eclipse_init(void);

void *max_jit_eclipse_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_eclipse_free(t_max_jit_eclipse *x);
t_messlist *max_jit_eclipse_class;

void ext_main(void *r)
{
	void *p,*q;

	jit_eclipse_init();
	setup(&max_jit_eclipse_class, max_jit_eclipse_new, (method)max_jit_eclipse_free, (short)sizeof(t_max_jit_eclipse),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_eclipse,obex));
	q = jit_class_findbyname(gensym("jit_eclipse"));
	max_jit_classex_mop_wrap(p,q,0);
	max_jit_classex_standard_wrap(p,q,0);
	addmess((method)max_jit_mop_assist, "assist", A_CANT,0);

	post("Eclipse, by R. Luke DuBois / Mark McNamara");
	post("Copyright (c) 2002 The Trustees of Columbia University in the City of New York / Cycling'74.");
	post("All rights reserved.");
}

void max_jit_eclipse_free(t_max_jit_eclipse *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_eclipse_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_eclipse *x,*o;

	if (x=(t_max_jit_eclipse *)max_jit_obex_new(max_jit_eclipse_class,gensym("jit_eclipse"))) {
		if (o=jit_object_new(gensym("jit_eclipse"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);
			max_jit_attr_args(x,argc,argv);
		} else {
			jit_object_error((t_object *)x,"jit.eclipse: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}