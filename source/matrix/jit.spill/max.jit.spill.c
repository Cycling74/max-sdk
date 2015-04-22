/*
	Copyright 2001-2005 - Cycling '74
	Jeremy Bernstein jeremy@bootsquad.com
*/

#include "jit.common.h"
#include "max.jit.mop.h"
#define MAX_OUT 16384

typedef struct _max_jit_spill
{
	t_object		ob;
	void			*obex;
	void			*spill_out;
	t_atom			*out_spill;
} t_max_jit_spill;

t_jit_err jit_spill_init(void);

void *max_jit_spill_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_spill_mproc(t_max_jit_spill *x, void *mop);
void max_jit_spill_bang(t_max_jit_spill *x);
void max_jit_spill_assist(t_max_jit_spill *x, void *b, long m, long a, char *s);
void max_jit_spill_free(t_max_jit_spill *x);
t_messlist *max_jit_spill_class;

t_symbol *ps_getspill;

void ext_main(void *r)
{
	void *p,*q;

	jit_spill_init();
	setup(&max_jit_spill_class, max_jit_spill_new, (method)max_jit_spill_free, (short)sizeof(t_max_jit_spill),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_spill,obex));
	q = jit_class_findbyname(gensym("jit_spill"));
	max_jit_classex_mop_wrap(p,q,MAX_JIT_MOP_FLAGS_OWN_BANG|MAX_JIT_MOP_FLAGS_OWN_OUTPUTMATRIX);
	max_jit_classex_mop_mproc(p,q,max_jit_spill_mproc); 	//custom mproc
	max_jit_classex_standard_wrap(p,q,0);
	addmess((method)max_jit_spill_assist, "assist", A_CANT,0);
	addbang((method)max_jit_spill_bang);

	ps_getspill = gensym("getspill");
}

void max_jit_spill_bang(t_max_jit_spill *x)
{
	void *o;
	long ac = MAX_OUT;

//	if (max_jit_mop_getoutputmode(x)&&x->av) {
	o=max_jit_obex_jitob_get(x);
	jit_object_method(o, ps_getspill, &ac, &(x->out_spill));
	if (ac==1) {
		if (x->out_spill->a_type==A_FLOAT)
			outlet_float(x->spill_out, jit_atom_getfloat(x->out_spill));
		else
			outlet_int(x->spill_out, jit_atom_getlong(x->out_spill));
	} else
		outlet_anything(x->spill_out, _jit_sym_list, ac, x->out_spill);
//	}
}

void max_jit_spill_mproc(t_max_jit_spill *x, void *mop)
{
	t_jit_err err;

	if (err=(t_jit_err) jit_object_method(
				max_jit_obex_jitob_get(x),
				_jit_sym_matrix_calc,
				jit_object_method(mop,_jit_sym_getinputlist),
				jit_object_method(mop,_jit_sym_getoutputlist)))
	{
		jit_error_code(x,err);
	} else {
		max_jit_spill_bang(x);
	}
}

void max_jit_spill_assist(t_max_jit_spill *x, void *b, long m, long a, char *s)
{
	if (m == 1) { //input
		max_jit_mop_assist(x,b,m,a,s);
	} else { //output
		sprintf(s,"(list) spill");
	}
}

void max_jit_spill_free(t_max_jit_spill *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	if (x->out_spill)
		jit_freebytes(x->out_spill,sizeof(t_atom)*MAX_OUT);
	max_jit_obex_free(x);
}

void *max_jit_spill_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_spill *x;
	void *o;

	if (x=(t_max_jit_spill *)max_jit_obex_new(max_jit_spill_class,gensym("jit_spill"))) {
		x->out_spill = NULL;
		if (o=jit_object_new(gensym("jit_spill"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);
			x->spill_out = outlet_new(x, 0L);
			x->out_spill = jit_getbytes(sizeof(t_atom)*MAX_OUT);
			max_jit_attr_args(x,argc,argv);
		} else {
			jit_object_error((t_object *)x,"jit.spill: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}