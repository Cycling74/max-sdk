/*
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_la_diagproduct
{
	t_object			ob;
	void				*obex;
	void 				*valout;
} t_max_jit_la_diagproduct;

t_jit_err jit_la_diagproduct_init(void);

void *max_jit_la_diagproduct_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_la_diagproduct_free(t_max_jit_la_diagproduct *x);
void max_jit_la_diagproduct_assist(t_max_jit_la_diagproduct *x, void *b, long m, long a, char *s);
void max_jit_la_diagproduct_bang(t_max_jit_la_diagproduct *x);
void max_jit_la_diagproduct_mproc(t_max_jit_la_diagproduct *x, void *mop);
t_messlist *max_jit_la_diagproduct_class;

t_symbol *ps_getresult;

void ext_main(void *r)
{
	void *p,*q;

	setup(&max_jit_la_diagproduct_class, max_jit_la_diagproduct_new, (method)max_jit_la_diagproduct_free, (short)sizeof(t_max_jit_la_diagproduct),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_la_diagproduct,obex));
	q = jit_class_findbyname(gensym("jit_la_diagproduct"));
	max_jit_classex_mop_wrap(p,q,MAX_JIT_MOP_FLAGS_OWN_BANG|MAX_JIT_MOP_FLAGS_OWN_OUTPUTMATRIX); //custom bang/outputmatrix
	max_jit_classex_mop_mproc(p,q,max_jit_la_diagproduct_mproc); 	//custom mproc
	max_jit_classex_standard_wrap(p,q,0);
	addmess((method)max_jit_la_diagproduct_assist,			"assist",			A_CANT,0);

	ps_getresult	= gensym("getresult");
}

void max_jit_la_diagproduct_mproc(t_max_jit_la_diagproduct *x, void *mop)
{
	t_jit_err err;
	long ac;
	t_atom *av=NULL;
	void *o;

	o=max_jit_obex_jitob_get(x);
	if (err=(t_jit_err) jit_object_method(
				o,
				_jit_sym_matrix_calc,
				jit_object_method(mop,_jit_sym_getinputlist),
				jit_object_method(mop,_jit_sym_getoutputlist)))
	{
		jit_error_code(x,err);
	} else {
		jit_object_method(o,ps_getresult,&ac,&av);
		switch(ac) {
		case 1:
			outlet_float(x->valout,jit_atom_getfloat(av));
			break;
		case 2:
			outlet_anything(x->valout,_jit_sym_list,2,av);
			break;
		}
		if (av) jit_freebytes(av,(ac)*sizeof(t_atom));
	}
}

void max_jit_la_diagproduct_assist(t_max_jit_la_diagproduct *x, void *b, long m, long a, char *s)
{
	if (m == 1) { //input
		max_jit_mop_assist(x,b,m,a,s);
	} else { //output
		switch (a) {
		case 0:
			sprintf(s,"(float/list) diagproduct");
			break;
		case 1:
			sprintf(s,"dumpout");
			break;
		}
	}
}

void max_jit_la_diagproduct_free(t_max_jit_la_diagproduct *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_la_diagproduct_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_la_diagproduct *x;
	void *o;

	if (x=(t_max_jit_la_diagproduct *)max_jit_obex_new(max_jit_la_diagproduct_class,gensym("jit_la_diagproduct"))) {
		if (o=jit_object_new(gensym("jit_la_diagproduct"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);
			//add additional non-matrix output
			x->valout 	= outlet_new(x,0L);
			max_jit_attr_args(x,argc,argv);
		} else {
			jit_object_error((t_object *)x,"jit.la.diagproduct: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}

