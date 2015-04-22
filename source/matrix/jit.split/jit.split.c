/*
	jit.split
	Copyright 2001-2005 - Cycling '74
	Jeremy Bernstein jeremy@bootsquad.com
*/

#include "jit.common.h"
#include "ext_strings.h"

typedef struct _jit_split
{
	t_object	ob;
	char		splitdim;
	long		splitpoint;
	char		autoclear;
} t_jit_split;

void *_jit_split_class;

t_jit_split *jit_split_new(void);
void jit_split_free(t_jit_split *x);
t_jit_err jit_split_matrix_calc(t_jit_split *x, void *inputs, void *outputs);
t_jit_err jit_split_init(void);
t_jit_err jit_split_calc_out_matrix(t_jit_split *x, t_jit_matrix_info *in_minfo, void *in_matrix,
									t_jit_matrix_info *out2_minfo, void *out2_matrix, t_jit_matrix_info *out_minfo, void *out_matrix);

t_jit_err jit_split_init(void)
{
	long attrflags=0;
	t_jit_object *attr;
	t_jit_object *mop;

	_jit_split_class = jit_class_new("jit_split",(method)jit_split_new,(method)jit_split_free,
									 sizeof(t_jit_split),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,2);
	jit_mop_output_nolink(mop,1);
	jit_mop_output_nolink(mop,2);
	jit_class_addadornment(_jit_split_class,mop);
	//add methods
	jit_class_addmethod(_jit_split_class, (method)jit_split_matrix_calc, "matrix_calc", A_CANT, 0L);

	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"splitdim",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_split,splitdim));
	jit_class_addattr(_jit_split_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Split Dim\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"autoclear",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_split,autoclear));
	jit_class_addattr(_jit_split_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Auto Clear\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"splitpoint",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_split,splitpoint));
	jit_class_addattr(_jit_split_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Split Point\"");

	//add methods

	jit_class_register(_jit_split_class);

	return JIT_ERR_NONE;
}

t_jit_err jit_split_matrix_calc(t_jit_split *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	t_jit_matrix_info in_minfo,out_minfo,out2_minfo;
	long i;
	t_matrix_conv_info conv, conv2;
	char splitdim = CLAMP(x->splitdim,0,JIT_MATRIX_MAX_DIMCOUNT);
	long splitpoint = x->splitpoint;
	t_jit_matrix_info *a_minfo,*b_minfo;
	void *a_matrix,*b_matrix;
	void *in_matrix, *out_matrix, *out2_matrix;

	in_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);
	out_matrix 	= jit_object_method(outputs,_jit_sym_getindex,0);
	out2_matrix = jit_object_method(outputs,_jit_sym_getindex,1);

	if (x && in_matrix && out_matrix && out2_matrix) {
		jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
		jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);
		jit_object_method(out2_matrix,_jit_sym_getinfo,&out2_minfo);

		if (jit_split_calc_out_matrix(x, &in_minfo, in_matrix, &out_minfo, out_matrix, &out2_minfo, out2_matrix)) {
			err=JIT_ERR_GENERIC;
			goto out;
		}

		//double check
		//compatible types?
		if ((in_minfo.type != out2_minfo.type) && (in_minfo.type != out_minfo.type)) {
			err=JIT_ERR_MISMATCH_TYPE;
			goto out;
		}

		//allow any planes, will simply wrap. i think that's okay  - jkc

		memset(&conv,0,sizeof(t_matrix_conv_info));
		memset(&conv2,0,sizeof(t_matrix_conv_info));
		for (i=0; i<JIT_MATRIX_MAX_PLANECOUNT; i++) {
			conv.planemap[i] = i;
			conv2.planemap[i] = i;
		}
		conv.flags = conv2.flags = JIT_MATRIX_CONVERT_SRCDIM | JIT_MATRIX_CONVERT_DSTDIM;


		// just for ease and later expandability
		a_minfo = &out_minfo;
		a_matrix = out_matrix;
		b_minfo = &out2_minfo;
		b_matrix = out2_matrix;

		for (i = 0; i < in_minfo.dimcount; i++) {
			if (i == splitdim) {
				conv.srcdimstart[i] = 0;
				conv.srcdimend[i] = CLAMP(splitpoint - 1, 0, in_minfo.dim[i] - 1);
				conv.dstdimstart[i] = 0;
				conv.dstdimend[i] = a_minfo->dim[i] - 1;

				conv2.srcdimstart[i] = CLAMP(splitpoint, 0, in_minfo.dim[i] - 1);
				conv2.srcdimend[i] = in_minfo.dim[i] - 1;
				conv2.dstdimstart[i] = 0;
				conv2.dstdimend[i] = b_minfo->dim[i] - 1;
			}
			else {
				conv.srcdimstart[i] = conv2.srcdimstart[i] = 0;
				conv.srcdimend[i] = conv2.srcdimend[i] = in_minfo.dim[i] - 1;
				conv.dstdimstart[i] = conv2.dstdimstart[i] = 0;
				conv.dstdimend[i] = conv2.dstdimend[i] = in_minfo.dim[i] - 1;
			}
		}

		jit_object_method(out_matrix, _jit_sym_frommatrix, in_matrix, &conv);
		jit_object_method(out2_matrix, _jit_sym_frommatrix, in_matrix, &conv2);
	}
	else return JIT_ERR_INVALID_PTR;

out:
	return err;
}

t_jit_err jit_split_calc_out_matrix(t_jit_split *x, t_jit_matrix_info *in_minfo, void *in_matrix,
									t_jit_matrix_info *out_minfo, void *out_matrix, t_jit_matrix_info *out2_minfo, void *out2_matrix)
{
	t_jit_matrix_info temp_minfo, temp2_minfo;
	long i,dimcount;
	char splitdim = CLAMP(x->splitdim,0,JIT_MATRIX_MAX_DIMCOUNT);
	long splitpoint = x->splitpoint;

	jit_object_method(out_matrix, _jit_sym_getinfo, &temp_minfo);
	jit_object_method(out2_matrix, _jit_sym_getinfo, &temp2_minfo);

	// later handle splitdim -1(planes)

	out_minfo->planecount = out2_minfo->planecount = in_minfo->planecount;
	out_minfo->type = out2_minfo->type = in_minfo->type;
	out_minfo->dimcount = out2_minfo->dimcount = in_minfo->dimcount;
	for (i = 0; i < in_minfo->dimcount; i++) {
		if (i==splitdim) {
			out_minfo->dim[i] = CLAMP(splitpoint, 0, in_minfo->dim[i]);
			out2_minfo->dim[i] = CLAMP(in_minfo->dim[i] - splitpoint, 0, in_minfo->dim[i]);
		} else {
			out_minfo->dim[i] = out2_minfo->dim[i] = in_minfo->dim[i];
		}
	}

	// check and change if necessary

	if ((out_minfo->type != temp_minfo.type) || (out2_minfo->type != temp2_minfo.type)) {
		if (jit_object_method(out_matrix, _jit_sym_setinfo, out_minfo) || jit_object_method(out2_matrix, _jit_sym_setinfo, out2_minfo))
			goto err;
		goto out;
	}
	if ((out_minfo->planecount != temp_minfo.planecount) || (out2_minfo->planecount != temp2_minfo.planecount)) {
		if (jit_object_method(out_matrix, _jit_sym_setinfo, out_minfo) || jit_object_method(out2_matrix, _jit_sym_setinfo, out2_minfo))
			goto err;
		goto out;
	}
	if ((out_minfo->dimcount != temp_minfo.dimcount) || (out2_minfo->dimcount != temp2_minfo.dimcount)) {
		if (jit_object_method(out_matrix, _jit_sym_setinfo, out_minfo) || jit_object_method(out2_matrix, _jit_sym_setinfo, out2_minfo))
			goto err;
		goto out;
	}
	for (i = 0; i < in_minfo->dimcount; i++) {
		if ((out_minfo->dim[i] != temp_minfo.dim[i]) || (out2_minfo->dim[i] != temp2_minfo.dim[i])) {
			if (jit_object_method(out_matrix, _jit_sym_setinfo, out_minfo) || jit_object_method(out2_matrix, _jit_sym_setinfo, out2_minfo))
				goto err;
			goto out;
		}
	}

out:
	if (x->autoclear) {
		jit_object_method(out_matrix, _jit_sym_clear);
		jit_object_method(out2_matrix, _jit_sym_clear);
	}
	return 0;

err:
	return 1;
}


t_jit_split *jit_split_new(void)
{
	t_jit_split *x;
	t_jit_matrix_info info;
	long i;

	if (x=(t_jit_split *)jit_object_alloc(_jit_split_class)) {
		x->splitdim = 0;
		x->splitpoint = 1;
		x->autoclear = 1;
	} else {
		x = NULL;
	}
	return x;
}

void jit_split_free(t_jit_split *x)
{
	//nada
}
