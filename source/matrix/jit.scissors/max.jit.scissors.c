/*
	Copyright 2001 - Cycling '74
	R. Luke DuBois luke@music.columbia.edu
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_scissors
{
	t_object		ob;
	void			*obex;
	long			maxn;
} t_max_jit_scissors;

t_jit_err jit_scissors_init(void);

void *max_jit_scissors_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_scissors_free(t_max_jit_scissors *x);
void max_jit_scissors_assist(t_max_jit_scissors *x, void *b, long m, long a, char *s);
void max_jit_scissors_mproc(t_max_jit_scissors *x, void *mop);

t_messlist *max_jit_scissors_class;

t_symbol *ps_output, *ps_rows, *ps_columns;

void ext_main(void *r)
{
	void *p, *q;

	jit_scissors_init();
	setup(&max_jit_scissors_class, max_jit_scissors_new, (method)max_jit_scissors_free, (short)sizeof(t_max_jit_scissors),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_scissors, obex));
	q = jit_class_findbyname(gensym("jit_scissors"));
	max_jit_classex_mop_wrap(p, q, MAX_JIT_MOP_FLAGS_OWN_BANG|MAX_JIT_MOP_FLAGS_OWN_OUTPUTMATRIX); //no bang/outputmatrix...doesn't make sense for this object
	max_jit_classex_standard_wrap(p, q, 0);
	addmess((method)max_jit_scissors_assist, "assist", A_CANT, 0);
	addmess((method)max_jit_mop_variable_anything, "anything", A_GIMME, 0);

	ps_rows 	= gensym("rows");
	ps_columns	= gensym("columns");

}

void max_jit_scissors_free(t_max_jit_scissors *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void max_jit_scissors_assist(t_max_jit_scissors *x, void *b, long m, long a, char *s)
{
	void *mop, *p;

	if (!(mop=max_jit_obex_adornment_get(x, _jit_sym_jit_mop)))
		return;

	if (m == 1) { 	//input
		max_jit_mop_assist(x, b, m, a, s);
	} else { 		//output
		if (a<(x->maxn)) {
			sprintf(s, "(matrix) out");
			if (a>0)
				sprintf(s, "%s%d", s, a+1);
		} else {
			sprintf(s, "dumpout");
		}
	}
}

void *max_jit_scissors_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_scissors *x;
	void *o, *p, *mop;
	t_jit_matrix_info info;
	long i;

	if (x=(t_max_jit_scissors *)max_jit_obex_new(max_jit_scissors_class, gensym("jit_scissors"))) {
		if (o=jit_object_new(gensym("jit_scissors"))) {
			max_jit_obex_jitob_set(x, o);
			max_jit_obex_dumpout_set(x, outlet_new(x, NULL));
			max_jit_mop_setup(x);
			max_jit_mop_inputs(x);

			max_jit_attr_args(x, argc, argv); // get attr args to know rows and cols
			x->maxn = jit_attr_getlong(o, ps_rows) * jit_attr_getlong(o, ps_columns);
			max_jit_mop_variable_addoutputs(x, x->maxn);
			max_jit_mop_outputs(x);
			// don't forget the nolink!
			mop = max_jit_obex_adornment_get(x, _jit_sym_jit_mop);
			for (i = 1; i <= x->maxn; i++)
				jit_mop_output_nolink(mop, i);

			jit_attr_setlong(o, gensym("max"), x->maxn);
			max_jit_mop_matrix_args(x, argc, argv); // now set matrix info
		} else {
			jit_object_error((t_object *)x,"jit.scissors: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}
