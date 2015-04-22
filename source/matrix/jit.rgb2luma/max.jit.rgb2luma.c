/*
	Copyright 2001-2005 - Cycling '74
	R. Luke DuBois luke@cycling74.com
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_rgb2luma
{
	t_object		ob;
	void			*obex;
} t_max_jit_rgb2luma;

t_jit_err jit_rgb2luma_init(void);

void *max_jit_rgb2luma_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_rgb2luma_free(t_max_jit_rgb2luma *x);
t_messlist *max_jit_rgb2luma_class;

void ext_main(void *r)
{
	void *p,*q;

	jit_rgb2luma_init();
	setup(&max_jit_rgb2luma_class, max_jit_rgb2luma_new, (method)max_jit_rgb2luma_free, (short)sizeof(t_max_jit_rgb2luma),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_rgb2luma,obex));
	q = jit_class_findbyname(gensym("jit_rgb2luma"));
	max_jit_classex_mop_wrap(p,q,0); 		//name/type/dim/planecount/bang/outputmatrix/etc
	max_jit_classex_standard_wrap(p,q,0); 	//getattributes/dumpout/maxjitclassaddmethods/etc
	addmess((method)max_jit_mop_assist, "assist", A_CANT,0);  //standard mop assist fn
}

void max_jit_rgb2luma_free(t_max_jit_rgb2luma *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_rgb2luma_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_rgb2luma *x;
	void *o,*m;
	t_jit_matrix_info info;

	if (x=(t_max_jit_rgb2luma *)max_jit_obex_new(max_jit_rgb2luma_class,gensym("jit_rgb2luma"))) {
		if (o=jit_object_new(gensym("jit_rgb2luma"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);
			//1-plane char out
			m = max_jit_mop_getoutput(x,1);
			jit_object_method(m,_jit_sym_getinfo,&info);
			info.type 		= _jit_sym_char;
			info.planecount = 1;
			info.dimcount 	= 2;
//			info.dim[0] 	= 160;
//			info.dim[1] 	= 120;
			jit_object_method(m,_jit_sym_setinfo,&info);
			max_jit_attr_args(x,argc,argv);
		} else {
			jit_object_error((t_object *)x,"jit.rgb2luma: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}
