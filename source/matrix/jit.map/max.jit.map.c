/*
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_map
{
	t_object		ob;
	void			*obex;
} t_max_jit_map;

t_jit_err jit_map_init(void);

void *max_jit_map_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_map_free(t_max_jit_map *x);
t_messlist *max_jit_map_class;

void ext_main(void *r)
{
	void *p,*q;

	jit_map_init();
	setup(&max_jit_map_class, max_jit_map_new, (method)max_jit_map_free, (short)sizeof(t_max_jit_map),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_map,obex));
	q = jit_class_findbyname(gensym("jit_map"));
	max_jit_classex_mop_wrap(p,q,0); 		//name/type/dim/planecount/bang/outputmatrix/etc
	max_jit_classex_standard_wrap(p,q,0); 	//getattributes/dumpout/maxjitclassaddmethods/etc
	addmess((method)max_jit_mop_assist, "assist", A_CANT,0);  //standard mop assist fn
}

void max_jit_map_free(t_max_jit_map *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_map_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_map *x;
	void *o;

	if (x=(t_max_jit_map *)max_jit_obex_new(max_jit_map_class,gensym("jit_map"))) {
		if (o=jit_object_new(gensym("jit_map"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);
			max_jit_attr_args(x,argc,argv);
		} else {
			jit_object_error((t_object *)x,"jit.map: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}
