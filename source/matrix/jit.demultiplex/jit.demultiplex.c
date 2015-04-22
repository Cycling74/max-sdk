/*
	jit.demultiplex
	Copyright 2001-2005 - Cycling '74
	Jeremy Bernstein jeremy@bootsquad.com
*/

#include "jit.common.h"
#include "ext_strings.h"

typedef struct _jit_demultiplex
{
	t_object	ob;
	char		demultiplexdim;
	long		scan_a;
	long		scan_b;
	char		autoclear;
} t_jit_demultiplex;

void *_jit_demultiplex_class;

t_jit_err jit_demultiplex_init(void);
t_jit_demultiplex *jit_demultiplex_new(void);
void jit_demultiplex_free(t_jit_demultiplex *x);
t_jit_err jit_demultiplex_matrix_calc(t_jit_demultiplex *x, void *inputs, void *outputs);
t_jit_err jit_demultiplex_calc_out_matrix(t_jit_demultiplex *x, t_jit_matrix_info *in_minfo, void *in_matrix,
		t_jit_matrix_info *out2_minfo, void *out2_matrix, t_jit_matrix_info *out_minfo, void *out_matrix);

t_jit_err jit_demultiplex_init(void)
{
	long attrflags=0;
	t_jit_object *attr;
	t_jit_object *mop, *o;

	_jit_demultiplex_class = jit_class_new("jit_demultiplex",(method)jit_demultiplex_new,(method)jit_demultiplex_free,
										   sizeof(t_jit_demultiplex),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,2);
	jit_mop_output_nolink(mop,1);
	jit_mop_output_nolink(mop,2);

	jit_class_addadornment(_jit_demultiplex_class,mop);
	//add methods
	jit_class_addmethod(_jit_demultiplex_class, (method)jit_demultiplex_matrix_calc, "matrix_calc", A_CANT, 0L);

	CLASS_STICKY_CATEGORY(_jit_demultiplex_class,0,"Behavior");
	CLASS_STICKY_ATTR(_jit_demultiplex_class,"basic",0,"1");

	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"demultiplexdim",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_demultiplex,demultiplexdim));
	jit_class_addattr(_jit_demultiplex_class,attr);
	CLASS_ATTR_LABEL(_jit_demultiplex_class,"demultiplexdim",0,"Dimension to Demultiplex");
	CLASS_ATTR_ENUM(_jit_demultiplex_class,"demultiplexdim",0,"0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"autoclear",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_demultiplex,autoclear));
	jit_class_addattr(_jit_demultiplex_class,attr);
	CLASS_ATTR_STYLE_LABEL(_jit_demultiplex_class,"autoclear",0,"onoff","Auto-Clear");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"scan_a",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_demultiplex,scan_a));
	jit_class_addattr(_jit_demultiplex_class,attr);
	CLASS_ATTR_LABEL(_jit_demultiplex_class,"scan_a",0,"Scanline Count (Left)");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"scan_b",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_demultiplex,scan_b));
	jit_class_addattr(_jit_demultiplex_class,attr);
	CLASS_ATTR_LABEL(_jit_demultiplex_class,"scan_b",0,"Scanline Count (Right)");

	CLASS_STICKY_CATEGORY_CLEAR(_jit_demultiplex_class);
	CLASS_STICKY_ATTR_CLEAR(_jit_demultiplex_class, "basic");

	jit_class_register(_jit_demultiplex_class);

	return JIT_ERR_NONE;
}

t_jit_err jit_demultiplex_matrix_calc(t_jit_demultiplex *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	t_jit_matrix_info in_minfo,out_minfo,out2_minfo;
	long i;
	t_matrix_conv_info conv, conv2;
	char demultiplexdim = CLAMP(x->demultiplexdim,0,JIT_MATRIX_MAX_DIMCOUNT);
	t_jit_matrix_info *a_minfo,*b_minfo;
	void *a_matrix,*b_matrix;
	long tmpsize, tmp, mod, a_start, b_start, c_start, plexsize;
	long offset, offset2;
	long scan_a = x->scan_a;
	long scan_b = x->scan_b;
	void *in_matrix,*out_matrix,*out2_matrix;

	in_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);
	out_matrix 	= jit_object_method(outputs,_jit_sym_getindex,0);
	out2_matrix 	= jit_object_method(outputs,_jit_sym_getindex,1);


	if (x && in_matrix && out_matrix && out2_matrix) {
		jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
		jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);
		jit_object_method(out2_matrix,_jit_sym_getinfo,&out2_minfo);

		if (jit_demultiplex_calc_out_matrix(x, &in_minfo, in_matrix, &out_minfo, out_matrix, &out2_minfo, out2_matrix)) {
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

		// need to set these first, and only copy in the while tmp-- loop
		for (i = 0; i < in_minfo.dimcount; i++) {
			conv.srcdimstart[i] = conv2.srcdimstart[i] = 0;
			conv.srcdimend[i] = conv2.srcdimend[i] = in_minfo.dim[i] - 1;
			conv.dstdimstart[i] = conv2.dstdimstart[i] = 0;
			conv.dstdimend[i] = conv2.dstdimend[i] = in_minfo.dim[i] - 1;
		}

		i = demultiplexdim;
		CLIP_ASSIGN(scan_a, 0, in_minfo.dim[i]);
		CLIP_ASSIGN(scan_b, 0, in_minfo.dim[i]);
		plexsize = CLAMP(scan_a + scan_b, 0, in_minfo.dim[i]);

		tmpsize = in_minfo.dim[i];
		tmp = (tmpsize / plexsize);
		mod = (tmpsize % plexsize);
		a_start = 0;
		b_start = 0;
		c_start = 0;
		if (scan_b == 0) {
			conv.srcdimstart[i] = CLAMP(a_start, 0, in_minfo.dim[i] - 1);
			conv.srcdimend[i] = CLAMP(a_start + (scan_a - 1), 0, in_minfo.dim[i] - 1);
			conv.dstdimstart[i] = CLAMP(b_start, 0, out_minfo.dim[i] - 1);
			conv.dstdimend[i] = CLAMP(b_start + (scan_a - 1), 0, out_minfo.dim[i] - 1);
			jit_object_method(out_matrix, _jit_sym_frommatrix, in_matrix, &conv);
			goto out;
		}
		else if (scan_a == 0) {
			conv2.srcdimstart[i] = CLAMP(a_start, 0, in_minfo.dim[i] - 1);
			conv2.srcdimend[i] = CLAMP(a_start + (scan_b - 1), 0, in_minfo.dim[i] - 1);
			conv2.dstdimstart[i] = CLAMP(c_start, 0, out2_minfo.dim[i] - 1);
			conv2.dstdimend[i] = CLAMP(c_start + (scan_b - 1), 0, out2_minfo.dim[i] - 1);
			jit_object_method(out2_matrix, _jit_sym_frommatrix, in_matrix, &conv2);
			goto out;
		}
		else while (tmp--) {
				conv.srcdimstart[i] = CLAMP(a_start, 0, in_minfo.dim[i] - 1);
				conv.srcdimend[i] = CLAMP(a_start + (scan_a - 1), 0, in_minfo.dim[i] - 1);
				conv.dstdimstart[i] = CLAMP(b_start, 0, out_minfo.dim[i] - 1);
				conv.dstdimend[i] = CLAMP(b_start + (scan_a - 1), 0, out_minfo.dim[i] - 1);
				a_start += scan_a;
				b_start += scan_a;
				conv2.srcdimstart[i] = CLAMP(a_start, 0, in_minfo.dim[i] - 1);
				conv2.srcdimend[i] = CLAMP(a_start + (scan_b - 1), 0, in_minfo.dim[i] - 1);
				conv2.dstdimstart[i] = CLAMP(c_start, 0, out2_minfo.dim[i] - 1);
				conv2.dstdimend[i] = CLAMP(c_start + (scan_b - 1), 0, out2_minfo.dim[i] - 1);
				a_start += scan_b;
				c_start += scan_b;
				jit_object_method(out_matrix, _jit_sym_frommatrix, in_matrix, &conv);
				jit_object_method(out2_matrix, _jit_sym_frommatrix, in_matrix, &conv2);
			}
		if (mod) {
			offset = (mod < scan_a) ? mod : scan_a;
			offset2 = (mod - scan_a <= 0) ? 0 : mod - scan_a;
			conv.srcdimstart[i] = CLAMP(a_start, 0, in_minfo.dim[i] - 1);
			conv.srcdimend[i] = CLAMP(a_start + (offset - 1), 0, in_minfo.dim[i] - 1);
			conv.dstdimstart[i] = CLAMP(b_start, 0, out_minfo.dim[i] - 1);
			conv.dstdimend[i] = CLAMP(b_start + (offset - 1), 0, out_minfo.dim[i] - 1);
			a_start += offset;
			b_start += offset;
			if (a_start > in_minfo.dim[i] - 1) {
				jit_object_method(out_matrix, _jit_sym_frommatrix, in_matrix, &conv);
				goto out;
			}
			conv2.srcdimstart[i] = CLAMP(a_start, 0, in_minfo.dim[i] - 1);
			conv2.srcdimend[i] = CLAMP(a_start + (offset2 - 1), 0, in_minfo.dim[i] - 1);
			conv2.dstdimstart[i] = CLAMP(c_start, 0, out2_minfo.dim[i] - 1);
			conv2.dstdimend[i] = CLAMP(c_start + (offset2 - 1), 0, out2_minfo.dim[i] - 1);
			jit_object_method(out_matrix, _jit_sym_frommatrix, in_matrix, &conv);
			jit_object_method(out2_matrix, _jit_sym_frommatrix, in_matrix, &conv2);
		}
	}
	else return JIT_ERR_INVALID_PTR;

out:
	return err;
}

t_jit_err jit_demultiplex_calc_out_matrix(t_jit_demultiplex *x, t_jit_matrix_info *in_minfo, void *in_matrix,
		t_jit_matrix_info *out_minfo, void *out_matrix, t_jit_matrix_info *out2_minfo, void *out2_matrix)
{
	t_jit_matrix_info temp_minfo, temp2_minfo;
	long i,dimcount;
	char demultiplexdim = CLAMP(x->demultiplexdim,0,JIT_MATRIX_MAX_DIMCOUNT);
	long tmpsize, tmp, mod, plexsize, offset, offset2;
	long scan_a = x->scan_a;
	long scan_b = x->scan_b;

	jit_object_method(out_matrix, _jit_sym_getinfo, &temp_minfo);
	jit_object_method(out2_matrix, _jit_sym_getinfo, &temp2_minfo);

	// later handle demultiplexdim -1(planes)
	out_minfo->planecount = out2_minfo->planecount = in_minfo->planecount;
	out_minfo->type = out2_minfo->type = in_minfo->type;
	out_minfo->dimcount = out2_minfo->dimcount = in_minfo->dimcount;

	for (i = 0; i < in_minfo->dimcount; i++) {
		out_minfo->dim[i] = out2_minfo->dim[i] = in_minfo->dim[i];
	}

	i = demultiplexdim;
	CLIP_ASSIGN(scan_a, 0, in_minfo->dim[i]);
	CLIP_ASSIGN(scan_b, 0, in_minfo->dim[i]);
	plexsize = CLAMP(scan_a + scan_b, 0, in_minfo->dim[i]);
	if (scan_b == 0) {
		out_minfo->dim[i] = scan_a;
		out2_minfo->dim[i] = 0;
	}
	else if (scan_a == 0) {
		out2_minfo->dim[i] = scan_b;
		out_minfo->dim[i] = 0;
	}
	else {
		tmpsize = in_minfo->dim[i];
		tmp = (tmpsize / plexsize);
		mod = (tmpsize % plexsize);
		if (mod) {
			offset = (mod < scan_a) ? mod : scan_a;
			offset2 = (mod - scan_a <= 0) ? 0 : mod - scan_a;
		}
		else offset = offset2 = 0;
		out_minfo->dim[i] = scan_a * tmp + offset;
		out2_minfo->dim[i] = scan_b * tmp + offset2;
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


t_jit_demultiplex *jit_demultiplex_new(void)
{
	t_jit_demultiplex *x;
	t_jit_matrix_info info;
	long i;

	if (x=(t_jit_demultiplex *)jit_object_alloc(_jit_demultiplex_class)) {
		x->demultiplexdim = 0;
		x->scan_a = 1;
		x->scan_b = 1;
		x->autoclear = 1;
	} else {
		x = NULL;
	}
	return x;
}

void jit_demultiplex_free(t_jit_demultiplex *x)
{
	;//nada
}
