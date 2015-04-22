/*
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_histogram
{
	t_object		ob;
	void			*obex;
} t_max_jit_histogram;

t_jit_err jit_histogram_init(void);

void *max_jit_histogram_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_histogram_free(t_max_jit_histogram *x);
t_messlist *max_jit_histogram_class;

void ext_main(void *r)
{
	void *p,*q;

	jit_histogram_init();
	setup(&max_jit_histogram_class, max_jit_histogram_new, (method)max_jit_histogram_free, (short)sizeof(t_max_jit_histogram),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_histogram,obex));
	q = jit_class_findbyname(gensym("jit_histogram"));
	max_jit_classex_mop_wrap(p,q,0);
	max_jit_classex_standard_wrap(p,q,0);
	addmess((method)max_jit_mop_assist, "assist", A_CANT,0);
}

void max_jit_histogram_free(t_max_jit_histogram *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_histogram_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_histogram *x;
	void *o,*m;
	t_jit_matrix_info info;
	long dim=256;
	t_symbol *type=_jit_sym_long;

	if (x=(t_max_jit_histogram *)max_jit_obex_new(max_jit_histogram_class,gensym("jit_histogram"))) {
		if (o=jit_object_new(gensym("jit_histogram"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);
			//default long 256 output(plane is linked)
			if (argc>=3) {
				if ((argv[0].a_type==A_LONG)&&(argv[1].a_type==A_SYM)&&(argv[2].a_type==A_LONG)) {
					type = jit_atom_getsym(argv+1);
					if (type!=_jit_sym_char)
						type = _jit_sym_long;
					dim = jit_atom_getlong(argv+2);
				}
			}
			m = max_jit_mop_getoutput(x,1);
			jit_object_method(m,_jit_sym_getinfo,&info);
			info.type 		= type;
			info.dimcount 	= 1;
			info.dim[0] 	= dim;
			jit_object_method(m,_jit_sym_setinfo,&info);
			max_jit_attr_args(x,argc,argv);
		} else {
			jit_object_error((t_object *)x,"jit.histogram: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}
