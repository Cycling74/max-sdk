#include "jit.common.h"

typedef struct _jit_charmap
{
	t_object				ob;
} t_jit_charmap;

void *_jit_charmap_class;

t_jit_err jit_charmap_init(void);
t_jit_charmap *jit_charmap_new(void);
void jit_charmap_free(t_jit_charmap *x);
t_jit_err jit_charmap_matrix_calc(t_jit_charmap *x, void *inputs, void *outputs);

void jit_charmap_calculate_ndim(void *vecdata, long dimcount, long *dim, long planecount, t_jit_matrix_info *in1_minfo, char *bip1,
								t_jit_matrix_info *in2_minfo, char *bip2, t_jit_matrix_info *out_minfo, char *bop);
void jit_charmap_vector_char		(long n, void *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out);
void jit_charmap_vector_char_4plane	(long n, void *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out);

t_jit_err jit_charmap_init(void)
{
	t_atom a;
	void *o,*mop;

	_jit_charmap_class = jit_class_new("jit_charmap",(method)jit_charmap_new,(method)jit_charmap_free,
									   sizeof(t_jit_charmap),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,2,1);
	jit_mop_single_type(mop,_jit_sym_char);
	o = jit_object_method(mop,_jit_sym_getinput,2);
	jit_attr_setlong(o,_jit_sym_dimlink,0);
	jit_atom_setlong(&a,256);
	jit_object_method(o,_jit_sym_mindim,1,&a);
	jit_object_method(o,_jit_sym_maxdim,1,&a);
	jit_class_addadornment(_jit_charmap_class,mop);
	//add methods
	jit_class_addmethod(_jit_charmap_class, (method)jit_charmap_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);

	jit_class_register(_jit_charmap_class);

	return JIT_ERR_NONE;
}

t_jit_err jit_charmap_matrix_calc(t_jit_charmap *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in1_savelock,in2_savelock,out_savelock;
	t_jit_matrix_info in1_minfo,in2_minfo,out_minfo;
	char *in1_bp,*in2_bp,*out_bp;
	long i,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	void *in1_matrix,*in2_matrix,*out_matrix;

	in1_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);
	in2_matrix 	= jit_object_method(inputs,_jit_sym_getindex,1);
	out_matrix 	= jit_object_method(outputs,_jit_sym_getindex,0);

	if (x&&in1_matrix&&in2_matrix&&out_matrix) {
		in1_savelock = (long) jit_object_method(in1_matrix,_jit_sym_lock,1);
		in2_savelock = (long) jit_object_method(in2_matrix,_jit_sym_lock,1);
		out_savelock = (long) jit_object_method(out_matrix,_jit_sym_lock,1);

		jit_object_method(in1_matrix,_jit_sym_getinfo,&in1_minfo);
		jit_object_method(in2_matrix,_jit_sym_getinfo,&in2_minfo);
		jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);

		jit_object_method(in1_matrix,_jit_sym_getdata,&in1_bp);
		jit_object_method(in2_matrix,_jit_sym_getdata,&in2_bp);
		jit_object_method(out_matrix,_jit_sym_getdata,&out_bp);

		if (!in1_bp) { err=JIT_ERR_INVALID_INPUT; goto out;}
		if (!in2_bp) { err=JIT_ERR_INVALID_INPUT; goto out;}
		if (!out_bp) { err=JIT_ERR_INVALID_OUTPUT; goto out;}

		//compatible types?
		if ((in1_minfo.type!=in2_minfo.type)||(in1_minfo.type!=out_minfo.type)) {
			err=JIT_ERR_MISMATCH_TYPE;
			goto out;
		}

		//get dimensions/planecount
		dimcount   = out_minfo.dimcount;
		planecount = out_minfo.planecount;

		if (in2_minfo.dim[0]<256) {
			err=JIT_ERR_MISMATCH_DIM;
		}

		for (i=0; i<dimcount; i++) {
			//if dimsize is 1, treat as infinite domain across that dimension.
			//otherwise truncate if less than the output dimsize
			dim[i] = out_minfo.dim[i];
			if ((in1_minfo.dim[i]<dim[i])&&in1_minfo.dim[i]>1) {
				dim[i] = in1_minfo.dim[i];
			}
		}

		jit_parallel_ndim_simplecalc3((method)jit_charmap_calculate_ndim,
									  NULL, dimcount, dim, planecount, &in1_minfo, in1_bp, &in2_minfo, in2_bp, &out_minfo, out_bp,
									  0 /* flags1 */, JIT_PARALLEL_NDIM_FLAGS_FULL_MATRIX /* flags2 */, 0 /*flags3*/);

	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(out_matrix,_jit_sym_lock,out_savelock);
	jit_object_method(in2_matrix,_jit_sym_lock,in2_savelock);
	jit_object_method(in1_matrix,_jit_sym_lock,in1_savelock);
	return err;
}


void jit_charmap_calculate_ndim(void *vecdata, long dimcount, long *dim, long planecount, t_jit_matrix_info *in1_minfo, char *bip1,
								t_jit_matrix_info *in2_minfo, char *bip2, t_jit_matrix_info *out_minfo, char *bop)
{
	long i,j,n;
	char *ip1=bip1,*ip2=bip2,*op=bop;
	t_jit_op_info in1_opinfo,in2_opinfo,out_opinfo;

	if (dimcount<1) return; //safety

	switch(dimcount) {
	case 1:
		dim[1] = 1;
	case 2:
		//if planecount the same, flatten planes - treat as single plane data for speed
		n = dim[0];
		in1_opinfo.stride = in1_minfo->dim[0]>1?in1_minfo->planecount:0;
		in2_opinfo.stride = in2_minfo->dim[0]>1?in2_minfo->planecount:0;
		out_opinfo.stride = out_minfo->dim[0]>1?out_minfo->planecount:0;
		if (in1_minfo->type==_jit_sym_char) {
			if ((in1_opinfo.stride==4)&&(in2_opinfo.stride==4)&&(in2_opinfo.stride==4)) {
				in2_opinfo.p = bip2;
				for (i=0; i<dim[1]; i++) {
					in1_opinfo.p = bip1 + i*in1_minfo->dimstride[1];
					out_opinfo.p = bop  + i*out_minfo->dimstride[1];
					jit_charmap_vector_char_4plane(n,vecdata,&in1_opinfo,&in2_opinfo,&out_opinfo);
				}
			} else {
				for (i=0; i<dim[1]; i++) {
					for (j=0; j<planecount; j++) {
						in1_opinfo.p = bip1 + i*in1_minfo->dimstride[1] + j%in1_minfo->planecount;
						in2_opinfo.p = bip2 + j%in2_minfo->planecount;
						out_opinfo.p = bop  + i*out_minfo->dimstride[1] + j%out_minfo->planecount;
						jit_charmap_vector_char(n,vecdata,&in1_opinfo,&in2_opinfo,&out_opinfo);
					}
				}
			}
		}
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			ip1 = bip1 + i*in1_minfo->dimstride[dimcount-1];
			op  = bop  + i*out_minfo->dimstride[dimcount-1];
			jit_charmap_calculate_ndim(vecdata,dimcount-1,dim,planecount,in1_minfo,ip1,in2_minfo,bip2,out_minfo,op);
		}
	}
}

void jit_charmap_vector_char(long n, void *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out)
{
	uchar *ip1,*ip2,*op;
	long is1,is2,os;

	ip1 = ((uchar *)in1->p);
	ip2 = ((uchar *)in2->p);
	op  = ((uchar *)out->p);
	is1 = in1->stride;
	is2 = in2->stride;
	os  = out->stride;

	++n;
	while (--n) {
		*op = ip2[(*ip1)*is2];
		op += os; ip1 += is1;
	}

}

void jit_charmap_vector_char_4plane(long n, void *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out)
{
	uchar *ip1,*ip2,*op;
	uchar *p0,*p1,*p2,*p3;

	ip1 = ((uchar *)in1->p);
	op  = ((uchar *)out->p);
	p0  = ((uchar *)in2->p);
	p1  = p0 + 1;
	p2  = p0 + 2;
	p3  = p0 + 3;

	++n; --op; --ip1;
	while (--n) {
		*++op = p0[(*++ip1)*4];
		*++op = p1[(*++ip1)*4];
		*++op = p2[(*++ip1)*4];
		*++op = p3[(*++ip1)*4];
	}
}

t_jit_charmap *jit_charmap_new(void)
{
	t_jit_charmap *x;

	if (x=(t_jit_charmap *)jit_object_alloc(_jit_charmap_class)) {
		//nada
	} else {
		x = NULL;
	}
	return x;
}

void jit_charmap_free(t_jit_charmap *x)
{
	//nada
}
