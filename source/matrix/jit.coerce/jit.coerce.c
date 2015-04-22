/*
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"

typedef struct _jit_coerce
{
	t_object				ob;
	t_symbol				*type;
	long					planecount;
} t_jit_coerce;

void *_jit_coerce_class;

t_jit_err jit_coerce_init(void);
t_jit_coerce *jit_coerce_new(void);
void jit_coerce_free(t_jit_coerce *x);
t_jit_err jit_coerce_matrix_calc(t_jit_coerce *x, void *inputs, void *outputs);


t_jit_err jit_coerce_init(void)
{
	long attrflags=0;
	t_jit_object *attr,*mop,*o;

	_jit_coerce_class = jit_class_new("jit_coerce",(method)jit_coerce_new,(method)jit_coerce_free,
									  sizeof(t_jit_coerce),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,1); //#inputs,#outputs
	jit_mop_output_nolink(mop,1);
	jit_class_addadornment(_jit_coerce_class,mop);
	//add methods
	jit_class_addmethod(_jit_coerce_class, (method)jit_coerce_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);
	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"type",_jit_sym_symbol,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_coerce,type));
	object_addattr_parse(attr,"category",_jit_sym_symbol,0,"MOP");
	object_addattr_parse(attr,"basic",_jit_sym_long,0,"1");
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Type");
	jit_class_addattr(_jit_coerce_class,attr);
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"planecount",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_coerce,planecount));
	object_addattr_parse(attr,"category",_jit_sym_symbol,0,"MOP");
	object_addattr_parse(attr,"basic",_jit_sym_long,0,"1");
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Planecount");
	jit_class_addattr(_jit_coerce_class,attr);

	jit_class_register(_jit_coerce_class);

	return JIT_ERR_NONE;
}

t_jit_err jit_coerce_matrix_calc(t_jit_coerce *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock;
	t_jit_matrix_info in_minfo,out_minfo;
	char *in_bp;
	long i,size;
	void *in_matrix,*out_matrix;

	in_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);
	out_matrix 	= jit_object_method(outputs,_jit_sym_getindex,0);

	if (x&&in_matrix&&out_matrix) {
		in_savelock = (long) jit_object_method(in_matrix,_jit_sym_lock,1);

		jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
		jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);

		jit_object_method(in_matrix,_jit_sym_getdata,&in_bp);

		if (!in_bp) { err=JIT_ERR_INVALID_INPUT; goto out; }
		if (!(out_minfo.flags&JIT_MATRIX_DATA_REFERENCE))
		{ err=JIT_ERR_INVALID_OUTPUT; goto out; }

		CLIP_ASSIGN(x->planecount,1,32);
		if (x->type == _jit_sym_long) {
			size = 4;
		} else if (x->type == _jit_sym_float32) {
			size = 4;
		} else if (x->type == _jit_sym_float64) {
			size = 8;
		} else {
			x->type = _jit_sym_char;
			size = 1;
		}

		out_minfo.type = x->type;
		out_minfo.planecount = x->planecount;
		out_minfo.dimcount = in_minfo.dimcount;
		out_minfo.size = in_minfo.size;
		out_minfo.dimstride[0] = size * x->planecount;
		out_minfo.dim[0] = (in_minfo.dim[0]*in_minfo.dimstride[0])/out_minfo.dimstride[0];

		if (out_minfo.dim[0]==0) { err=JIT_ERR_GENERIC; goto out; }

		for (i=1; i<in_minfo.dimcount; i++) {
			out_minfo.dimstride[i] = in_minfo.dimstride[i];
			out_minfo.dim[i] = in_minfo.dim[i];
		}

		jit_object_method(out_matrix,_jit_sym_setinfo_ex,&out_minfo);
		jit_object_method(out_matrix,_jit_sym_data,in_bp);

	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	return err;
}

t_jit_coerce *jit_coerce_new(void)
{
	t_jit_coerce *x;

	if (x=(t_jit_coerce *)jit_object_alloc(_jit_coerce_class)) {
		x->type = _jit_sym_char;
		x->planecount = 4;
	} else {
		x = NULL;
	}
	return x;
}

void jit_coerce_free(t_jit_coerce *x)
{
	//nada
}
