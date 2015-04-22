/*
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_findbounds
{
	t_object			ob;
	void				*obex;
	void 				*maxout;
	void 				*minout;
} t_max_jit_findbounds;

t_jit_err jit_findbounds_init(void);

void *max_jit_findbounds_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_findbounds_free(t_max_jit_findbounds *x);
void max_jit_findbounds_assist(t_max_jit_findbounds *x, void *b, long m, long a, char *s);
void max_jit_findbounds_mproc(t_max_jit_findbounds *x, void *mop);
t_messlist *max_jit_findbounds_class;

t_symbol *ps_getboundmin,*ps_getboundmax;

void ext_main(void *r)
{
	void *p,*q;

	jit_findbounds_init();
	setup(&max_jit_findbounds_class, max_jit_findbounds_new, (method)max_jit_findbounds_free, (short)sizeof(t_max_jit_findbounds),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_findbounds,obex));
	q = jit_class_findbyname(gensym("jit_findbounds"));
	max_jit_classex_mop_wrap(p,q,MAX_JIT_MOP_FLAGS_OWN_BANG|MAX_JIT_MOP_FLAGS_OWN_OUTPUTMATRIX); //custom bang/outputmatrix
	max_jit_classex_mop_mproc(p,q,max_jit_findbounds_mproc); 	//custom mproc
	max_jit_classex_standard_wrap(p,q,0);
	addmess((method)max_jit_findbounds_assist,			"assist",			A_CANT,0);

	ps_getboundmin	= gensym("getboundmin");
	ps_getboundmax	= gensym("getboundmax");
}

void max_jit_findbounds_mproc(t_max_jit_findbounds *x, void *mop)
{
	t_jit_err err;
	long ac=0;
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
		jit_object_method(o,ps_getboundmax,&ac,&av);
		switch(ac) {
		case 1:
			outlet_float(x->maxout,jit_atom_getfloat(av));
			break;
		default:
			outlet_anything(x->maxout,_jit_sym_list,ac,av);
			break;
		}
		if (av) jit_freebytes(av,(ac)*sizeof(t_atom));
		av=NULL; ac=0;
		jit_object_method(o,ps_getboundmin,&ac,&av);
		switch(ac) {
		case 1:
			outlet_float(x->minout,jit_atom_getfloat(av));
			break;
		default:
			outlet_anything(x->minout,_jit_sym_list,ac,av);
			break;
		}
		if (av) jit_freebytes(av,(ac)*sizeof(t_atom));
	}
}

void max_jit_findbounds_assist(t_max_jit_findbounds *x, void *b, long m, long a, char *s)
{
	if (m == 1) { //input
		max_jit_mop_assist(x,b,m,a,s);
	} else { //output
		switch (a) {
		case 0:
			sprintf(s,"(list) min bounds");
			break;
		case 1:
			sprintf(s,"(list) max bounds");
			break;
		case 2:
			sprintf(s,"dumpout");
			break;
		}
	}
}

void max_jit_findbounds_free(t_max_jit_findbounds *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_findbounds_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_findbounds *x;
	void *o;

	if (x=(t_max_jit_findbounds *)max_jit_obex_new(max_jit_findbounds_class,gensym("jit_findbounds"))) {
		if (o=jit_object_new(gensym("jit_findbounds"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);
			//add additional non-matrix output
			x->maxout 	= outlet_new(x,0L);
			x->minout 	= outlet_new(x,0L);
			max_jit_attr_args(x,argc,argv);
		} else {
			jit_object_error((t_object *)x,"jit.findbounds: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}

