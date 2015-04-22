/*
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_submatrix
{
	t_object		ob;
	void			*obex;
} t_max_jit_submatrix;

t_jit_err jit_submatrix_init(void);

void *max_jit_submatrix_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_submatrix_free(t_max_jit_submatrix *x);
void max_jit_submatrix_mproc(t_max_jit_submatrix *x, void *mop);

t_messlist *max_jit_submatrix_class;

void ext_main(void *r)
{
	void *p,*q;

	jit_submatrix_init();
	setup(&max_jit_submatrix_class, max_jit_submatrix_new, (method)max_jit_submatrix_free, (short)sizeof(t_max_jit_submatrix),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_submatrix,obex));
	q = jit_class_findbyname(gensym("jit_submatrix"));
	max_jit_classex_mop_wrap(p,q,MAX_JIT_MOP_FLAGS_OWN_ALL & ~MAX_JIT_MOP_FLAGS_OWN_JIT_MATRIX);
	max_jit_classex_mop_mproc(p,q,max_jit_submatrix_mproc); 	//custom mproc
	max_jit_classex_standard_wrap(p,q,0); 	//getattributes/dumpout/maxjitclassaddmethods/etc
	addmess((method)max_jit_mop_assist, "assist", A_CANT,0);  //standard mop assist fn
}

void max_jit_submatrix_mproc(t_max_jit_submatrix *x, void *mop)
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
		max_jit_mop_outputmatrix(x);
		jit_object_method(max_jit_mop_getoutput(x,1),_jit_sym_data,NULL);
	}
}

void max_jit_submatrix_free(t_max_jit_submatrix *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_submatrix_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_submatrix *x;
	void *o,*m,*mop,*p;
	t_jit_matrix_info info;

	if (x=(t_max_jit_submatrix *)max_jit_obex_new(max_jit_submatrix_class,gensym("jit_submatrix"))) {
		if (o=jit_object_new(gensym("jit_submatrix"))) {
			max_jit_obex_jitob_set(x,o);
			max_jit_obex_dumpout_set(x,outlet_new(x,NULL));
			max_jit_mop_setup(x);
			max_jit_mop_inputs(x);
			max_jit_mop_outputs(x);
			mop=max_jit_obex_adornment_get(x,_jit_sym_jit_mop);
			jit_attr_setlong(mop,gensym("adapt"),0);
			jit_attr_setlong(mop,gensym("caninplace"),0);
			jit_attr_setlong(mop,gensym("outputmode"),1);
			//make the output matrix a data reference w/NULL data pointer
			m = max_jit_mop_getoutput(x,1);
			jit_object_method(m,_jit_sym_getinfo,&info);
			jit_object_method(m,gensym("freedata"));
			info.flags = JIT_MATRIX_DATA_REFERENCE;
			info.size = 0;
			p = NULL;
			jit_object_method(m,_jit_sym_setinfo_ex,&info);
			jit_object_method(m,_jit_sym_data,p);
			max_jit_attr_args(x,argc,argv);
		} else {
			jit_object_error((t_object *)x,"jit.submatrix: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}
