/*
	Copyright 2001-2005 - Cycling '74
	Luke DuBois luke@music.columbia.edu
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_gradient
{
	t_object		ob;
	void			*obex;
} t_max_jit_gradient;

t_jit_err jit_gradient_init(void);

void *max_jit_gradient_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_gradient_free(t_max_jit_gradient *x);
t_jit_err max_jit_gradient_outputmatrix(t_max_jit_gradient *x);
t_messlist *max_jit_gradient_class;

void ext_main(void *r)
{
	void *p,*q;

	jit_gradient_init();
	setup(&max_jit_gradient_class, max_jit_gradient_new, (method)max_jit_gradient_free, (short)sizeof(t_max_jit_gradient),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_gradient,obex));
	q = jit_class_findbyname(gensym("jit_gradient"));
	max_jit_classex_mop_wrap(p,q,MAX_JIT_MOP_FLAGS_OWN_JIT_MATRIX | MAX_JIT_MOP_FLAGS_OWN_OUTPUTMATRIX);
	max_jit_classex_standard_wrap(p,q,0);
	addmess((method)max_jit_mop_assist, "assist", A_CANT,0);
	max_addmethod_usurp_low((method)max_jit_gradient_outputmatrix, "outputmatrix");
}

void max_jit_gradient_free(t_max_jit_gradient *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_gradient_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_gradient *x,*o;

	if (x=(t_max_jit_gradient *)max_jit_obex_new(max_jit_gradient_class,gensym("jit_gradient"))) {
		if (o=jit_object_new(gensym("jit_gradient"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);
			max_jit_attr_args(x,argc,argv);
		} else {
			jit_object_error((t_object *)x,"jit.gradient: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}

t_jit_err max_jit_gradient_outputmatrix(t_max_jit_gradient *x)
{
	void *mop,*o,*p;
	long err=JIT_ERR_NONE;
	t_atom a;

	if (!(mop=max_jit_obex_adornment_get(x,_jit_sym_jit_mop)))
		return JIT_ERR_GENERIC;
	if (jit_attr_getlong(mop,_jit_sym_outputmode)) {
		if (err=(t_jit_err) jit_object_method(
					max_jit_obex_jitob_get(x),
					_jit_sym_matrix_calc,
					jit_object_method(mop,_jit_sym_getinputlist),
					jit_object_method(mop,_jit_sym_getoutputlist)))
		{
			jit_error_code(x,err);
		} else {

			if ((p=jit_object_method(mop,_jit_sym_getoutput,1)) &&
					(o=max_jit_mop_io_getoutlet(p)))
			{
				jit_atom_setsym(&a,jit_attr_getsym(p,_jit_sym_matrixname));
				outlet_anything(o,_jit_sym_jit_matrix,1,&a);
			}
		}
	}
	return err;
}