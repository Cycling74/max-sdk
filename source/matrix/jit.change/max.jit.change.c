/*
	Copyright 2001-2005 - Cycling '74
	Jeremy Bernstein jeremy@bootsquad.com
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_change
{
	t_object		ob;
	void			*obex;
	char			report;
} t_max_jit_change;

t_jit_err jit_change_init(void);

void *max_jit_change_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_change_mproc(t_max_jit_change *x, void *mop);
void max_jit_change_free(t_max_jit_change *x);
t_messlist *max_jit_change_class;

t_symbol *ps_change;

void ext_main(void *r)
{
	long attrflags;
	void *p, *q, *attr;

	jit_change_init();
	setup(&max_jit_change_class, max_jit_change_new, (method)max_jit_change_free, (short)sizeof(t_max_jit_change),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_change,obex));
	q = jit_class_findbyname(gensym("jit_change"));
	max_jit_classex_mop_wrap(p,q,MAX_JIT_MOP_FLAGS_OWN_OUTPUTMATRIX);
	max_jit_classex_mop_mproc(p,q,max_jit_change_mproc); 	//custom mproc
	max_jit_classex_standard_wrap(p,q,0);

	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"report",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_max_jit_change, report));
	max_jit_classex_addattr(p,attr);

	addmess((method)max_jit_mop_assist, "assist", A_CANT,0);

	ps_change = gensym("change");
}

void max_jit_change_mproc(t_max_jit_change *x, void *mop)
{
	void *o, *p, *r;
	t_jit_err err;

	if (err=(t_jit_err) jit_object_method(
				o=max_jit_obex_jitob_get(x),
				_jit_sym_matrix_calc,
				jit_object_method(mop,_jit_sym_getinputlist),
				jit_object_method(mop,_jit_sym_getoutputlist)))
	{
		jit_error_code(x,err);
	} else {
		if (jit_attr_getlong(o,ps_change)) {
			jit_attr_setlong(o,ps_change,0);
			p=jit_object_method(jit_object_method(mop,_jit_sym_getinputlist),_jit_sym_getindex,0);;
			r=jit_object_method(jit_object_method(mop,_jit_sym_getoutputlist),_jit_sym_getindex,0);;
			jit_object_method(r,_jit_sym_frommatrix,p,NULL);
			max_jit_mop_outputmatrix(x);
			if (x->report) { // matrices are _not_ equal
				t_atom a;

				jit_atom_setlong(&a, 0);
				max_jit_obex_dumpout(x, gensym("report"), 1, &a);
			}
		}
		else {
			if (x->report) { // matrices are equal
				t_atom a;

				jit_atom_setlong(&a, 1);
				max_jit_obex_dumpout(x, gensym("report"), 1, &a);
			}
		}
	}
}

void max_jit_change_free(t_max_jit_change *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_change_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_change *x;
	void *o;

	if (x=(t_max_jit_change *)max_jit_obex_new(max_jit_change_class,gensym("jit_change"))) {
		if (o=jit_object_new(gensym("jit_change"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);
			x->report = 0;
			max_jit_attr_args(x,argc,argv);
		} else {
			jit_object_error((t_object *)x,"jit.change: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}