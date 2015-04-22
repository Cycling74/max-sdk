/*
	Copyright 2001 - Cycling '74
	R. Luke DuBois luke@music.columbia.edu
*/

#include "jit.common.h"

typedef struct _jit_scissors
{
	t_object				ob;
	long					rows;
	long					cols;
	long					max;
} t_jit_scissors;

void *_jit_scissors_class;


t_jit_scissors *jit_scissors_new(void);
void jit_scissors_free(t_jit_scissors *x);
t_jit_err jit_scissors_matrix_calc(t_jit_scissors *x, void *inputs, void *outputs);
t_jit_err jit_scissors_init(void);


t_jit_err jit_scissors_init(void)
{
	long attrflags=0;
	void *attr, *mop;

	_jit_scissors_class = jit_class_new("jit_scissors", (method)jit_scissors_new, (method)jit_scissors_free,
										sizeof(t_jit_scissors), 0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop, 1, -1); //#inputs, #outputs(variable)
	jit_class_addadornment(_jit_scissors_class, mop);
	//add methods
	jit_class_addmethod(_jit_scissors_class, (method)jit_scissors_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);
	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset, "rows", _jit_sym_long, attrflags,
						  (method)0, (method)0, calcoffset(t_jit_scissors, rows));
	jit_attr_addfilterset_clip(attr, 1, 16, 1, 1);
	jit_class_addattr(_jit_scissors_class, attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Rows");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset, "columns", _jit_sym_long, attrflags,
						  (method)0, (method)0, calcoffset(t_jit_scissors, cols));
	jit_attr_addfilterset_clip(attr, 1, 16, 1, 1);
	jit_class_addattr(_jit_scissors_class, attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Columns");

	attrflags = JIT_ATTR_GET_OPAQUE_USER | JIT_ATTR_SET_OPAQUE_USER;
	attr = jit_object_new(_jit_sym_jit_attr_offset, "max", _jit_sym_long, attrflags,
						  (method)0, (method)0, calcoffset(t_jit_scissors, max));
	jit_class_addattr(_jit_scissors_class, attr);

	jit_class_register(_jit_scissors_class);

	return JIT_ERR_NONE;
}


t_jit_err jit_scissors_matrix_calc(t_jit_scissors *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock, out_savelock, dimmode;
	t_jit_matrix_info in_minfo, out_minfo;
	char *in_bp, *out_bp;
	long i, dimcount, planecount, dim[JIT_MATRIX_MAX_DIMCOUNT];
	t_atom a[2];
	t_matrix_conv_info conv;
	long rows = x->rows, cols = x->cols;
	void *in_matrix, *out_matrix;
	long maxn = rows * cols;

	if (x->max == -1) { // we are not in a Max box
		long i = 1;
		void *test;

		do { // make sure we start at a valid matrix
			test = jit_object_method(outputs, _jit_sym_getindex, maxn - i);
			if (test) {
				maxn -= (i - 1);
			}
			i++;
		} while (!test && (maxn - i >= 0));
		if (!test)
			return JIT_ERR_INVALID_OUTPUT;
	} else
		CLIP_ASSIGN(maxn, 0, x->max);

	in_matrix 	= jit_object_method(inputs, _jit_sym_getindex, 0);
	out_matrix 	= jit_object_method(outputs, _jit_sym_getindex, --maxn);

	if (x && in_matrix) {
		in_savelock = (long) jit_object_method(in_matrix, _jit_sym_lock, 1);
		jit_object_method(in_matrix, _jit_sym_getinfo, &in_minfo);
		jit_object_method(in_matrix, _jit_sym_getdata, &in_bp);
		if (!in_bp) { err=JIT_ERR_INVALID_INPUT; goto out; }

		dim[0] = in_minfo.dim[0] / cols;
		dim[1] = in_minfo.dim[1] / rows;

		memset(&conv, 0, sizeof(t_matrix_conv_info));
		for (i = 0; i < JIT_MATRIX_MAX_PLANECOUNT; i++) {
			conv.planemap[i] = i;
		}

		conv.flags = JIT_MATRIX_CONVERT_SRCDIM;

		while (out_matrix) {
			out_savelock = (long) jit_object_method(out_matrix, _jit_sym_lock, 1);
			jit_object_method(out_matrix, _jit_sym_getinfo, &out_minfo);

			// safe to always set. only reallocs matrix if necessary
			out_minfo.dim[0] = dim[0];
			out_minfo.dim[1] = dim[1];
			out_minfo.type = in_minfo.type;
			out_minfo.planecount = in_minfo.planecount;
			jit_object_method(out_matrix, _jit_sym_setinfo, &out_minfo);
			jit_object_method(out_matrix, _jit_sym_getinfo, &out_minfo);

			// need to get base pointer *after* modifying
			jit_object_method(out_matrix, _jit_sym_getdata, &out_bp);
			if (!out_bp) { err=JIT_ERR_INVALID_OUTPUT; goto out;}

			if ((in_minfo.dimcount!=2)||(out_minfo.dimcount!=2)) {
				err=JIT_ERR_MISMATCH_DIM;
				goto out;
			}

			dimcount = out_minfo.dimcount;
			planecount = out_minfo.planecount;

			conv.srcdimstart[0] = dim[0] * (maxn % cols);
			conv.srcdimstart[1] = dim[1] * (maxn / cols);
			conv.srcdimend[0] = conv.srcdimstart[0] + dim[0] - 1;
			conv.srcdimend[1] = conv.srcdimstart[1] + dim[1] - 1;

			jit_object_method(out_matrix, _jit_sym_frommatrix, in_matrix, &conv);
			jit_object_method(out_matrix, _jit_sym_lock, out_savelock);

			out_matrix 	= jit_object_method(outputs, _jit_sym_getindex, --maxn);
		}
	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	if (out_matrix)
		jit_object_method(out_matrix, _jit_sym_lock, out_savelock);
	jit_object_method(in_matrix, _jit_sym_lock, in_savelock);
	return err;
}


t_jit_scissors *jit_scissors_new(void)
{
	t_jit_scissors *x;
	short i;

	if (x=(t_jit_scissors *)jit_object_alloc(_jit_scissors_class)) {
		x->rows 	= 1;
		x->cols 	= 1;
		x->max 	= -1;
	} else {
		x = NULL;
	}
	return x;
}

void jit_scissors_free(t_jit_scissors *x)
{
	//nada
}

