/*
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"

typedef struct _jit_submatrix
{
	t_object				ob;
	long					dimcount;
	long					dim[JIT_MATRIX_MAX_DIMCOUNT];
	long					offsetcount;
	long					offset[JIT_MATRIX_MAX_DIMCOUNT];
} t_jit_submatrix;

void *_jit_submatrix_class;

t_jit_err jit_submatrix_init(void);
t_jit_submatrix *jit_submatrix_new(void);
void jit_submatrix_free(t_jit_submatrix *x);
t_jit_err jit_submatrix_matrix_calc(t_jit_submatrix *x, void *inputs, void *outputs);


t_jit_err jit_submatrix_init(void)
{
	long attrflags=0;
	t_jit_object *attr,*mop,*o;

	_jit_submatrix_class = jit_class_new("jit_submatrix",(method)jit_submatrix_new,(method)jit_submatrix_free,
										 sizeof(t_jit_submatrix),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,1); //#inputs,#outputs
	jit_mop_output_nolink(mop,1);
	jit_class_addadornment(_jit_submatrix_class,mop);
	//add methods
	jit_class_addmethod(_jit_submatrix_class, (method)jit_submatrix_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);
	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"dim",_jit_sym_long,JIT_MATRIX_MAX_DIMCOUNT,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_submatrix,dimcount),calcoffset(t_jit_submatrix,dim));
	object_addattr_parse(attr,"category",_jit_sym_symbol,0,"MOP");
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Dim");
	
	jit_class_addattr(_jit_submatrix_class,attr);
	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"offset",_jit_sym_long,JIT_MATRIX_MAX_DIMCOUNT,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_submatrix,offsetcount),calcoffset(t_jit_submatrix,offset));
	jit_class_addattr(_jit_submatrix_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Offset");

	jit_class_register(_jit_submatrix_class);

	return JIT_ERR_NONE;
}

t_jit_err jit_submatrix_matrix_calc(t_jit_submatrix *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock;
	t_jit_matrix_info in_minfo,out_minfo;
	char *in_bp;
	long i,c;
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

		CLIP_ASSIGN(x->dimcount,1,JIT_MATRIX_MAX_DIMCOUNT);
		out_minfo.type = in_minfo.type;
		out_minfo.planecount = in_minfo.planecount;
		out_minfo.dimcount = x->dimcount;
		out_minfo.size = out_minfo.size;

		for (i=0; i<x->offsetcount; i++) {
			CLIP_ASSIGN(x->offset[i], 0, in_minfo.dim[i] - 1);
//			x->offset[i] = MAX(x->offset[i],0);
		}

		for (; i<JIT_MATRIX_MAX_DIMCOUNT; i++) {
			x->offset[i] = 0;
		}

		for (i=0; i<x->dimcount; i++) {
			x->dim[i] = MAX(x->dim[i],1);
			out_minfo.dim[i] = x->dim[i];
			c = MAX(in_minfo.dim[i]-x->offset[i],1);
			CLIP_ASSIGN(out_minfo.dim[i],1,c);
		}

		for (; i<JIT_MATRIX_MAX_DIMCOUNT; i++) {
			out_minfo.dim[i] = 1;
		}

		for (i=0; i<in_minfo.dimcount; i++) {
			out_minfo.dimstride[i] = in_minfo.dimstride[i];
		}

		for (; i<JIT_MATRIX_MAX_DIMCOUNT; i++) {
			out_minfo.dimstride[i] = 0;
		}

		c = MIN(in_minfo.dimcount,x->offsetcount);
		for (i=0; i<c; i++) {
			in_bp += x->offset[i]*in_minfo.dimstride[i];
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

t_jit_submatrix *jit_submatrix_new(void)
{
	t_jit_submatrix *x;

	if (x=(t_jit_submatrix *)jit_object_alloc(_jit_submatrix_class)) {
		x->dimcount = 1;
		x->dim[0] = 1;
		x->offsetcount = 1;
		x->offset[0] = 0;
	} else {
		x = NULL;
	}
	return x;
}

void jit_submatrix_free(t_jit_submatrix *x)
{
	//nada
}
