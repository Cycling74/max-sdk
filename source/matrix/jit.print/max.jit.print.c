/*
	Copyright 2001-2005 - Cycling '74
	Jeremy Bernstein jeremy@bootsquad.com
*/

#include "jit.common.h"

typedef struct _max_jit_print
{
	t_object		ob;
	void			*obex;
	void			*dumpout;
	void			*matrixout;
} t_max_jit_print;

t_jit_err jit_print_init(void);

void *max_jit_print_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_print_jit_matrix(t_max_jit_print *x, t_symbol *s, long argc, t_atom *argv);
void max_jit_print_assist(t_max_jit_print *x, void *b, long m, long a, char *s);
void max_jit_print_free(t_max_jit_print *x);

t_jit_err jit_print_matrix_calc(void *x, void *in_matrix);

t_messlist *max_jit_print_class;

void ext_main(void *r)
{
	void *p,*q;

	jit_print_init();
	setup(&max_jit_print_class, max_jit_print_new, (method)max_jit_print_free, (short)sizeof(t_max_jit_print),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_print,obex));
	q = jit_class_findbyname(gensym("jit_print"));
	max_jit_classex_standard_wrap(p,q,0);
	addmess((method)max_jit_print_jit_matrix, "jit_matrix", A_GIMME,0);
	addmess((method)max_jit_print_assist, "assist", A_CANT,0);
}

void max_jit_print_jit_matrix(t_max_jit_print *x, t_symbol *s, long argc, t_atom *argv)
{
	void *matrix;
	t_atom a;
	long err;

	if (argc&&argv) {
		//find matrix
		matrix = jit_object_findregistered(jit_atom_getsym(argv));
		if (matrix&&jit_object_method(matrix, _jit_sym_class_jit_matrix)) {
			if (err = jit_print_matrix_calc(max_jit_obex_jitob_get(x), matrix)) {
				jit_object_post((t_object *)x,"err: %d", err);
				jit_error_code(x,err);
			}
			jit_atom_setsym(&a,jit_atom_getsym(argv));
		}
		else {
			jit_error_code(x,JIT_ERR_MATRIX_UNKNOWN);
		}
		outlet_anything(x->matrixout,s,1,&a);
	}
	else return;
out:
	return;
}

void max_jit_print_assist(t_max_jit_print *x, void *b, long m, long a, char *s)
{
	if (m == 1) { //input
		sprintf(s, "(matrix) in");
	}
	else { //output
		switch (a) {
		case 0:
			sprintf(s,"(matrix) out");
			break;
		case 1:
			sprintf(s,"dumpout");
			break;
		}
	}
}

void max_jit_print_free(t_max_jit_print *x)
{
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_print_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_print *x;
	void *o;

	if (x = (t_max_jit_print *)max_jit_obex_new(max_jit_print_class,gensym("jit_print"))) {
		max_jit_obex_dumpout_set(x,outlet_new(x,NULL));
		x->matrixout = outlet_new(x,"jit_matrix");

		if (o = jit_object_new(gensym("jit_print"))) {
			max_jit_obex_jitob_set(x,o);
			max_jit_attr_args(x,argc,argv);
		}
		else {
			jit_object_error((t_object *)x,"jit.print: could not allocate object");
			freeobject((t_object *) x);
			x=NULL;
		}
	}
	return (x);
}