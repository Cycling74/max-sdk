/*
	jit.concat
	Copyright 2001 - Cycling '74
	Jeremy Bernstein jeremy@bootsquad.com
*/

#include "jit.common.h"
#include "ext_strings.h"

typedef struct _jit_concat
{
	t_object	ob;
	char		concatdim;
	char		mode;
	char		autoclear;
	char		truncate;
} t_jit_concat;

void *_jit_concat_class;

t_jit_concat *jit_concat_new(void);
void jit_concat_free(t_jit_concat *x);
t_jit_err jit_concat_matrix_calc(t_jit_concat *x, void *inputs, void *outputs);
t_jit_err jit_concat_init(void);
void jit_concat_clear_conv(t_matrix_conv_info *conv);
t_jit_err jit_concat_calc_out_matrix(t_jit_concat *x, t_jit_matrix_info *in_minfo, void *in_matrix,
									 t_jit_matrix_info *in2_minfo, void *in2_matrix, t_jit_matrix_info *out_minfo, void *out_matrix);

t_jit_err jit_concat_init(void)
{
	long attrflags=0;
	t_jit_object *attr;
	t_jit_object *mop, *o;

	_jit_concat_class = jit_class_new("jit_concat",(method)jit_concat_new,(method)jit_concat_free,
									  sizeof(t_jit_concat),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,2,1);
	jit_mop_input_nolink(mop,2);
	jit_mop_output_nolink(mop,1);
	o = jit_object_method(mop,_jit_sym_getinput,2);
	jit_object_method(o,_jit_sym_ioproc,jit_mop_ioproc_copy_adapt);

	jit_class_addadornment(_jit_concat_class,mop);
	//add methods
	jit_class_addmethod(_jit_concat_class, (method)jit_concat_matrix_calc, "matrix_calc", A_CANT, 0L);
	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;

	CLASS_STICKY_CATEGORY(_jit_concat_class,0,"Behavior");
	CLASS_STICKY_ATTR(_jit_concat_class,"basic",0,"1");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"mode",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_concat,mode));
	jit_class_addattr(_jit_concat_class,attr);
	CLASS_ATTR_LABEL(_jit_concat_class,"mode",0,"Concatenation Order Mode");
	CLASS_ATTR_ENUMINDEX2(_jit_concat_class, "mode", 0, "Append Right to Left", "Append Left to Right");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"concatdim",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_concat,concatdim));
	jit_class_addattr(_jit_concat_class,attr);
	CLASS_ATTR_LABEL(_jit_concat_class,"concatdim",0,"Dimension to Concatenate");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"autoclear",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_concat,autoclear));
	jit_class_addattr(_jit_concat_class,attr);
	CLASS_ATTR_STYLE_LABEL(_jit_concat_class,"autoclear",0,"onoff","Automatically Clear");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"truncate",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_concat,truncate));
	jit_class_addattr(_jit_concat_class,attr);
	CLASS_ATTR_STYLE_LABEL(_jit_concat_class,"truncate",0,"onoff","Truncate");

	CLASS_STICKY_CATEGORY_CLEAR(_jit_concat_class);
	CLASS_STICKY_ATTR_CLEAR(_jit_concat_class, "basic");

	jit_class_register(_jit_concat_class);

	return JIT_ERR_NONE;
}

t_jit_err jit_concat_matrix_calc(t_jit_concat *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	t_jit_matrix_info in_minfo,in2_minfo,out_minfo;
	long i;
	t_matrix_conv_info conv;
	char concatdim = CLAMP(x->concatdim,0,JIT_MATRIX_MAX_DIMCOUNT);
	t_jit_matrix_info *a_minfo,*b_minfo;
	void *a_matrix,*b_matrix;
	void *in_matrix,*in2_matrix,*out_matrix;

	in_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);
	in2_matrix 	= jit_object_method(inputs,_jit_sym_getindex,1);
	out_matrix 	= jit_object_method(outputs,_jit_sym_getindex,0);


	if (x && in_matrix && in2_matrix && out_matrix) {
		jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
		jit_object_method(in2_matrix,_jit_sym_getinfo,&in2_minfo);
		jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);

		if (x->truncate) {
			//overwrite in2_minfo with the minimum dim, except for concatdim
			for (i = 0; i < in2_minfo.dimcount; i++) {
				if (i!=concatdim) {
					in2_minfo.dim[i] = MIN(in_minfo.dim[i],in2_minfo.dim[i]);
				}
			}
		}

		if (jit_concat_calc_out_matrix(x, &in_minfo, in_matrix, &in2_minfo, in2_matrix, &out_minfo, out_matrix)) {
			err=JIT_ERR_GENERIC;
			goto out;
		}

		//double check
		//compatible types?
		if ((in_minfo.type != in2_minfo.type) && (in_minfo.type != out_minfo.type)) {
			err=JIT_ERR_MISMATCH_TYPE;
			goto out;
		}

		memset(&conv,0,sizeof(t_matrix_conv_info));
		for (i=0; i<JIT_MATRIX_MAX_PLANECOUNT; i++) conv.planemap[i] = i;
		conv.flags |= JIT_MATRIX_CONVERT_SRCDIM;
		conv.flags |= JIT_MATRIX_CONVERT_DSTDIM;

		if (x->mode) { //mode L<->R
			a_minfo = &in2_minfo;
			a_matrix = in2_matrix;
			b_minfo = &in_minfo;
			b_matrix = in_matrix;
		} else {
			a_minfo = &in_minfo;
			a_matrix = in_matrix;
			b_minfo = &in2_minfo;
			b_matrix = in2_matrix;
		}

		for (i = 0; i < out_minfo.dimcount; i++) {
			conv.srcdimstart[i] = 0;
			conv.srcdimend[i] = a_minfo->dim[i] - 1;
			conv.dstdimstart[i] = 0;
			conv.dstdimend[i] = a_minfo->dim[i] - 1;
		}
		jit_object_method(out_matrix, _jit_sym_frommatrix, a_matrix, &conv);
		for (i = 0; i < out_minfo.dimcount; i++) {
			if (i==concatdim) {
				conv.srcdimstart[i] = 0;
				conv.srcdimend[i] = b_minfo->dim[i] - 1;
				conv.dstdimstart[i] = a_minfo->dim[i];
				conv.dstdimend[i] = a_minfo->dim[i] + b_minfo->dim[i] - 1;
			} else {
				conv.srcdimstart[i] = 0;
				conv.srcdimend[i] = b_minfo->dim[i] - 1;
				conv.dstdimstart[i] = 0;
				conv.dstdimend[i] = b_minfo->dim[i] - 1;
			}
		}
		jit_object_method(out_matrix, _jit_sym_frommatrix, b_matrix, &conv);

	}
	else return JIT_ERR_INVALID_PTR;

out:
	return err;
}

t_jit_err jit_concat_calc_out_matrix(t_jit_concat *x, t_jit_matrix_info *in_minfo, void *in_matrix,
									 t_jit_matrix_info *in2_minfo, void *in2_matrix, t_jit_matrix_info *out_minfo, void *out_matrix)
{
	t_jit_matrix_info temp_minfo;
	long i,dimcount;
	char concatdim = CLAMP(x->concatdim,0,JIT_MATRIX_MAX_DIMCOUNT);

	jit_object_method(out_matrix, _jit_sym_getinfo, &temp_minfo);

	// later handle concatdim -1(planes)

	out_minfo->planecount = MAX(in_minfo->planecount, in2_minfo->planecount);
	out_minfo->type = in_minfo->type;
	out_minfo->dimcount = MAX(MAX(in_minfo->dimcount,in2_minfo->dimcount),concatdim+1);
	for (i = 0; i < out_minfo->dimcount; i++) {
		if (i==concatdim) {
			out_minfo->dim[i] = in_minfo->dim[i] + in2_minfo->dim[i];
		} else {
			out_minfo->dim[i] = MAX(in_minfo->dim[i], in2_minfo->dim[i]);
		}
	}

	// check and change if necessary

	if (out_minfo->planecount != temp_minfo.planecount) {
		if (jit_object_method(out_matrix, _jit_sym_setinfo, out_minfo))
			goto err;//goto out;
		goto out;
	}
	if (out_minfo->dimcount != temp_minfo.dimcount) {
		if (jit_object_method(out_matrix, _jit_sym_setinfo, out_minfo))
			goto err;//goto out;
		goto out;
	}
	for (i = 0; i < out_minfo->dimcount; i++) {
		if (out_minfo->dim[i] != temp_minfo.dim[i]) {
			if (jit_object_method(out_matrix, _jit_sym_setinfo, out_minfo))
				goto err;//goto out;
			goto out;
		}
	}

out:
	if (x->autoclear) {
		jit_object_method(out_matrix, _jit_sym_clear);
	}
	return 0;

err:
	return 1;
}


void jit_concat_clear_conv(t_matrix_conv_info *conv)
{
	long i;

	for (i = 0; i < JIT_MATRIX_MAX_DIMCOUNT; i++) {
		conv->srcdimstart[i] = 0;
		conv->srcdimend[i] = 0;
		conv->dstdimstart[i] = 0;
		conv->dstdimend[i] = 0;
	}
}

t_jit_concat *jit_concat_new(void)
{
	t_jit_concat *x;
	t_jit_matrix_info info;
	long i;

	if (x=(t_jit_concat *)jit_object_alloc(_jit_concat_class)) {
		x->mode = 0;
		x->concatdim = 0;
		x->autoclear = 1;
		x->truncate = 1;
	} else {
		x = NULL;
	}
	return x;
}

void jit_concat_free(t_jit_concat *x)
{
	//nada
}
