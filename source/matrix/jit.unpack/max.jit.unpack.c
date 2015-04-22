/*
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_unpack
{
	t_object		ob;
	void			*obex;
	long			outlets;
} t_max_jit_unpack;

t_jit_err jit_unpack_init(void);

void *max_jit_unpack_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_unpack_free(t_max_jit_unpack *x);
t_messlist *max_jit_unpack_class;
void max_jit_unpack_jit_matrix(t_max_jit_unpack *x, t_symbol *s, long argc, t_atom *argv);

void ext_main(void *r)
{
	void *p,*q,*attr;
	long attrflags;

	jit_unpack_init();
	setup(&max_jit_unpack_class, max_jit_unpack_new, (method)max_jit_unpack_free, (short)sizeof(t_max_jit_unpack),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_unpack,obex));
	q = jit_class_findbyname(gensym("jit_unpack"));

	addmess((method)max_jit_unpack_jit_matrix, "jit_matrix", A_GIMME,0); //place at beginning for speed
	max_jit_classex_mop_wrap(p,q,MAX_JIT_MOP_FLAGS_OWN_JIT_MATRIX);
//	max_jit_classex_mop_wrap(p,q,0);
	max_jit_classex_standard_wrap(p,q,0);

	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"type",_jit_sym_symbol,attrflags,
						  (method)max_jit_mop_gettype,(method)max_jit_mop_type,0/*custom*/);
	object_addattr_parse(attr,"category",_jit_sym_symbol,0,"MOP");
	max_jit_classex_addattr(p,attr);
	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"dim",_jit_sym_long,JIT_MATRIX_MAX_DIMCOUNT,attrflags,
						  (method)max_jit_mop_getdim,(method)max_jit_mop_dim,0/*custom*/);
	object_addattr_parse(attr,"category",_jit_sym_symbol,0,"MOP");
	max_jit_classex_addattr(p,attr);

	addmess((method)max_jit_mop_assist, "assist", A_CANT,0);
	addmess((method)max_jit_mop_variable_anything, "anything", A_GIMME, 0);

}

void max_jit_unpack_jit_matrix(t_max_jit_unpack *x, t_symbol *s, long argc, t_atom *argv)
{
	long i;
	t_atom_long jump[JIT_MATRIX_MAX_PLANECOUNT];
	void *o, *p;

	o = max_jit_obex_jitob_get(x);
	jit_attr_getlong_array(o, gensym("jump"), JIT_MATRIX_MAX_PLANECOUNT, jump);

	for(i=0; i < x->outlets; i++) {
		p=max_jit_mop_getoutput(x,i+1);
		jit_attr_setlong(p,gensym("minplanecount"),jump[i]);
		jit_attr_setlong(p,gensym("maxplanecount"),jump[i]);
	}

	max_jit_mop_jit_matrix(x,s,argc,argv);
}

void max_jit_unpack_free(t_max_jit_unpack *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_unpack_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_unpack *x;
	void *o,*m,*p,*mop;
	t_jit_matrix_info info;
	long i;

	if (x=(t_max_jit_unpack *)max_jit_obex_new(max_jit_unpack_class,gensym("jit_unpack"))) {
		if (o=jit_object_new(gensym("jit_unpack"))) {
			max_jit_obex_jitob_set(x,o);
			max_jit_obex_dumpout_set(x,outlet_new(x,NULL));
			max_jit_mop_setup(x);
			max_jit_mop_inputs(x);

			if (argc&&(i=jit_atom_getlong(argv))) {
				CLIP_ASSIGN(i,1,JIT_MATRIX_MAX_PLANECOUNT);
			} else {
				i=4;
			}

			x->outlets = i;
			max_jit_mop_variable_addoutputs(x,i);

			while (i) {
				p=max_jit_mop_getoutput(x,i);
				jit_attr_setlong(p,gensym("minplanecount"),1);
				jit_attr_setlong(p,gensym("maxplanecount"),1);
				i--;
			}

			max_jit_mop_outputs(x);
			max_jit_mop_matrix_args(x,argc,argv);
			//set adapt true if only plane argument(should come after matrix_args call)
			if ((max_jit_attr_args_offset(argc,argv)<=1) &&
					(mop=max_jit_obex_adornment_get(x,_jit_sym_jit_mop)))
			{
				jit_attr_setlong(mop,_jit_sym_adapt,1);
			}

			max_jit_attr_args(x,argc,argv);
		} else {
			jit_object_error((t_object *)x,"jit.unpack: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}