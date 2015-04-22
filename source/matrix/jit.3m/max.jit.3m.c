/*
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_3m
{
	t_object			ob;
	void				*obex;
	void 				*minout;
	void 				*meanout;
	void 				*maxout;
	t_atom				*av;
} t_max_jit_3m;

t_jit_err jit_3m_init(void);

void *max_jit_3m_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_3m_free(t_max_jit_3m *x);
void max_jit_3m_assist(t_max_jit_3m *x, void *b, long m, long a, char *s);
void max_jit_3m_bang(t_max_jit_3m *x);
void max_jit_3m_mproc(t_max_jit_3m *x, void *mop);
void *max_jit_3m_class;

t_symbol *ps_getmin,*ps_getmean,*ps_getmax;

void ext_main(void *r)
{
	void *p,*q;

	jit_3m_init();
	setup((t_messlist **)&max_jit_3m_class, (method)max_jit_3m_new, (method)max_jit_3m_free, (short)sizeof(t_max_jit_3m),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_3m,obex));
	q = jit_class_findbyname(gensym("jit_3m"));
	max_jit_classex_mop_wrap(p,q,MAX_JIT_MOP_FLAGS_OWN_BANG|MAX_JIT_MOP_FLAGS_OWN_OUTPUTMATRIX); //custom bang/outputmatrix
	max_jit_classex_mop_mproc(p,q,max_jit_3m_mproc); 	//custom mproc
	max_jit_classex_standard_wrap(p,q,0);
	addmess((method)max_jit_3m_assist,			"assist",			A_CANT,0);
	addbang((method)max_jit_3m_bang);

	ps_getmin	= gensym("getmin");
	ps_getmean	= gensym("getmean");
	ps_getmax	= gensym("getmax");
}

void max_jit_3m_bang(t_max_jit_3m *x)
{
	long ac;
	void *o;

	if (max_jit_mop_getoutputmode(x)&&x->av) {
		o=max_jit_obex_jitob_get(x);
		//passing in memory to attr function. be sure object knows how to handle this
		ac=JIT_MATRIX_MAX_PLANECOUNT;
		jit_object_method(o,ps_getmax,&ac,&(x->av));
		if (ac>1)
			outlet_anything(x->maxout,_jit_sym_list,ac,x->av);
		else {
			if (x->av->a_type==A_FLOAT)
				outlet_float(x->maxout,jit_atom_getfloat(x->av));
			else
				outlet_int(x->maxout,jit_atom_getlong(x->av));
		}
		ac=JIT_MATRIX_MAX_PLANECOUNT;
		jit_object_method(o,ps_getmean,&ac,&(x->av));
		if (ac>1)
			outlet_anything(x->meanout,_jit_sym_list,ac,x->av);
		else {
			if (x->av->a_type==A_FLOAT)
				outlet_float(x->meanout,jit_atom_getfloat(x->av));
			else
				outlet_int(x->meanout,jit_atom_getlong(x->av));
		}
		ac=JIT_MATRIX_MAX_PLANECOUNT;
		jit_object_method(o,ps_getmin,&ac,&(x->av));
		if (ac>1)
			outlet_anything(x->minout,_jit_sym_list,ac,x->av);
		else {
			if (x->av->a_type==A_FLOAT)
				outlet_float(x->minout,jit_atom_getfloat(x->av));
			else
				outlet_int(x->minout,jit_atom_getlong(x->av));
		}
	}
}

void max_jit_3m_mproc(t_max_jit_3m *x, void *mop)
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
		max_jit_3m_bang(x);
	}
}

void max_jit_3m_assist(t_max_jit_3m *x, void *b, long m, long a, char *s)
{
	if (m == 1) { //input
		max_jit_mop_assist(x,b,m,a,s);
	} else { //output
		switch (a) {
		case 0:
			sprintf(s,"(list) min");
			break;
		case 1:
			sprintf(s,"(list) mean");
			break;
		case 2:
			sprintf(s,"(list) max");
			break;
		case 3:
			sprintf(s,"dumpout");
			break;
		}
	}
}

void max_jit_3m_free(t_max_jit_3m *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	if (x->av)
		jit_freebytes(x->av,sizeof(t_atom)*JIT_MATRIX_MAX_PLANECOUNT);
	max_jit_obex_free(x);
}

void *max_jit_3m_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_3m *x;
	void *o;

	if (x=(t_max_jit_3m *)max_jit_obex_new(max_jit_3m_class,gensym("jit_3m"))) {
		x->av = NULL;
		if (o=jit_object_new(gensym("jit_3m"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);
			//add additional non-matrix outputs
			x->maxout 	= outlet_new(x,0L);
			x->meanout 	= outlet_new(x,0L);
			x->minout 	= outlet_new(x,0L);
			x->av		= jit_getbytes(sizeof(t_atom)*JIT_MATRIX_MAX_PLANECOUNT);
			max_jit_attr_args(x,argc,argv);
		} else {
			jit_object_error((t_object *)x,"jit.3m: could not allocate object");
			freeobject((t_object *)x);
			x=NULL;
		}
	}
	return (x);
}

