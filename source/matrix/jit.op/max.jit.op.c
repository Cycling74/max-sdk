/*
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"
#include "ext_obex.h"
#include "max.jit.mop.h"

#define OP_LAST_MATRIX	0
#define OP_LAST_VAL		1


typedef struct _max_jit_op
{
	t_object			ob;
	void				*obex;
	long				valcount;
	t_atom				val[JIT_MATRIX_MAX_PLANECOUNT];
	long 				last;
	t_jit_matrix_info	lastinfo;
} t_max_jit_op;

t_jit_err jit_op_init(void);

void *max_jit_op_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_op_free(t_max_jit_op *x);
void max_jit_op_int(t_max_jit_op *x, long c);
void max_jit_op_float(t_max_jit_op *x, double f);
void max_jit_op_list(t_max_jit_op *x, t_symbol *s, short argc, t_atom *argv);
void max_jit_op_val(t_max_jit_op *x, void *attr, short argc, t_atom *argv);
void max_jit_op_jit_matrix(t_max_jit_op *x, t_symbol *s, short argc, t_atom *argv);
void max_jit_op_mproc(t_max_jit_op *x, void *mop);

t_messlist *max_jit_op_class;

void ext_main(void *r)
{
	void *p,*q,*attr;
	long attrflags;

	setup(&max_jit_op_class, max_jit_op_new, (method)max_jit_op_free, (short)sizeof(t_max_jit_op),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_op,obex));
	q = jit_class_findbyname(gensym("jit_op"));

	addmess((method)max_jit_op_jit_matrix, "jit_matrix", A_GIMME, 0);
	max_jit_classex_mop_wrap(p,q,MAX_JIT_MOP_FLAGS_OWN_JIT_MATRIX);
	max_jit_classex_mop_mproc(p,q,max_jit_op_mproc); 	//custom mproc
	max_jit_classex_standard_wrap(p,q,0);

	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW ;
	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"val",_jit_sym_atom,JIT_MATRIX_MAX_PLANECOUNT,attrflags,
						  (method)0,(method)max_jit_op_val,calcoffset(t_max_jit_op,valcount),calcoffset(t_max_jit_op,val));
	max_jit_classex_addattr(p,attr);

	addint((method)max_jit_op_int);
	addfloat((method)max_jit_op_float);
	addmess((method)max_jit_op_list, "list", A_GIMME, 0);
	addmess((method)max_jit_mop_assist, "assist", A_CANT,0);
}

void max_jit_op_int(t_max_jit_op *x, long c)
{
	t_atom a;

	jit_atom_setlong(&a,c);
	typedmess((t_object *) x,_jit_sym_val,1,&a);
}

void max_jit_op_float(t_max_jit_op *x, double f)
{
	t_atom a;

	jit_atom_setfloat(&a,f);
	typedmess((t_object *) x,_jit_sym_val,1,&a);
}

void max_jit_op_list(t_max_jit_op *x, t_symbol *s, short argc, t_atom *argv)
{
	typedmess((t_object *) x,_jit_sym_val,argc,argv);
}

void max_jit_op_val(t_max_jit_op *x, void *attr, short argc, t_atom *argv)
{
	void *o;
	long i;

	if (o=max_jit_mop_getinput(x,2)) {
		jit_object_method(o,_jit_sym_getinfo,&x->lastinfo);
		jit_object_method(o,_jit_sym_setall,0L,(long)argc,argv);
		x->last = OP_LAST_VAL;
		x->valcount = MIN(argc,JIT_MATRIX_MAX_PLANECOUNT);
		for (i=0; i<x->valcount; i++)
			x->val[i] = argv[i];
	}
}

void max_jit_op_jit_matrix(t_max_jit_op *x, t_symbol *s, short argc, t_atom *argv)
{
	if (max_jit_obex_inletnumber_get(x)) {
		x->last = OP_LAST_MATRIX;
	}
	max_jit_mop_jit_matrix(x,s,argc,argv);
}

void max_jit_op_mproc(t_max_jit_op *x, void *mop)
{
	t_jit_err err;
	t_jit_matrix_info tmpinfo;
	void *o;
	long changed=0,i;

	if (x->last==OP_LAST_VAL) {
		tmpinfo = x->lastinfo;
		o = max_jit_mop_getinput(x,2);
		jit_object_method(o,_jit_sym_getinfo,&x->lastinfo);
		if (tmpinfo.type!=x->lastinfo.type)
			changed = TRUE;
		else if (tmpinfo.planecount!=x->lastinfo.planecount)
			changed = TRUE;
		/* Already handled by resampling
		else if (tmpinfo.dimcount!=x->lastinfo.dimcount)
			changed = TRUE;
		else {
			for (i=0;i<tmpinfo.dimcount;i++) {
				if (tmpinfo.dim[i]!=x->lastinfo.dim[i])
					changed=TRUE;
			}
		}
		*/
		if (changed)
			jit_object_method(o,_jit_sym_setall,0L,x->valcount,x->val);
	}

	if (err=(t_jit_err) jit_object_method(
				max_jit_obex_jitob_get(x),
				_jit_sym_matrix_calc,
				jit_object_method(mop,_jit_sym_getinputlist),
				jit_object_method(mop,_jit_sym_getoutputlist)))
	{
		jit_error_code(x,err);
	} else {
		max_jit_mop_outputmatrix(x);
	}
}

void max_jit_op_free(t_max_jit_op *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_op_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_op *x;
	void *o;
	long i;
	t_symbol *override=_jit_sym_nothing;
	char *tmp;

	if (s!=gensym("jit.op")) {
		tmp = s->s_name;
		if (tmp[0] == 'j' &&
				tmp[1] == 'i' &&
				tmp[2] == 't' &&
				tmp[3] == '.')
		{
			override = gensym(tmp+4);
		}
	}

	if (x=(t_max_jit_op *)max_jit_obex_new(max_jit_op_class,gensym("jit_op"))) {
		if (o=jit_object_new(gensym("jit_op"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);
			x->last = OP_LAST_MATRIX;
			x->valcount = 0;
			for (i=0; i<JIT_MATRIX_MAX_PLANECOUNT; i++)
				jit_atom_setlong(&x->val[i],0);
			max_jit_attr_args(x,argc,argv);
			if (override!=_jit_sym_nothing) {
				object_attr_setsym((t_object *)o,gensym("op"),override);
				//object_post((t_object *)x,"override: %s",override->s_name);
			}
		} else {
			jit_object_error((t_object *)x,"jit.op: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}
