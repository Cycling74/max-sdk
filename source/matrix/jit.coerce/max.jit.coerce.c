/*
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_coerce
{
	t_object		ob;
	void			*obex;
} t_max_jit_coerce;

t_jit_err jit_coerce_init(void);

void *max_jit_coerce_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_coerce_free(t_max_jit_coerce *x);
void max_jit_coerce_mproc(t_max_jit_coerce *x, void *mop);

t_messlist *max_jit_coerce_class;

void ext_main(void *r)
{
	void *p,*q;

	jit_coerce_init();
	setup(&max_jit_coerce_class, max_jit_coerce_new, (method)max_jit_coerce_free, (short)sizeof(t_max_jit_coerce),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_coerce,obex));
	q = jit_class_findbyname(gensym("jit_coerce"));
	max_jit_classex_mop_wrap(p,q,MAX_JIT_MOP_FLAGS_OWN_ALL & ~MAX_JIT_MOP_FLAGS_OWN_JIT_MATRIX);
	max_jit_classex_mop_mproc(p,q,max_jit_coerce_mproc); 	//custom mproc
	max_jit_classex_standard_wrap(p,q,0); 	//getattributes/dumpout/maxjitclassaddmethods/etc
	addmess((method)max_jit_mop_assist, "assist", A_CANT,0);  //standard mop assist fn
}

void max_jit_coerce_mproc(t_max_jit_coerce *x, void *mop)
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
		jit_object_method(max_jit_mop_getoutput(x,1),gensym("data"),NULL);
	}
}

void max_jit_coerce_free(t_max_jit_coerce *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_coerce_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_coerce *x;
	void *o,*m,*mop,*p;
	t_jit_matrix_info info;
	long attrstart;
	t_atom_long planecount=4;
	t_symbol *type=_jit_sym_char;

	if (x=(t_max_jit_coerce *)max_jit_obex_new(max_jit_coerce_class,gensym("jit_coerce"))) {
		if (o=jit_object_new(gensym("jit_coerce"))) {
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
			attrstart = max_jit_attr_args_offset(argc,argv);
			if (attrstart&&argv) {
				jit_atom_arg_getlong(&planecount, 0, attrstart, argv);
				jit_atom_arg_getsym(&type, 1, attrstart, argv);
				jit_attr_setlong(o,_jit_sym_planecount,planecount);
				jit_attr_setsym(o,_jit_sym_type,type);
			}
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
			jit_object_error((t_object *)x,"jit.coerce: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}
