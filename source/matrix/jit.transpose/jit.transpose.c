/*
	Copyright 2001 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"

typedef struct _jit_transpose
{
	t_object				ob;
} t_jit_transpose;

void *_jit_transpose_class;

t_jit_err jit_transpose_init(void);
t_jit_transpose *jit_transpose_new(void);
void jit_transpose_free(t_jit_transpose *x);
t_jit_err jit_transpose_output_adapt(void *mop, void *mop_io, void *matrix);
t_jit_err jit_transpose_matrix_calc(t_jit_transpose *x, void *inputs, void *outputs);

void jit_transpose_calculate_ndim(long dim, long *dimsize, long planecount, void *vecdata, t_jit_matrix_info *in_minfo, char *bip,
								  t_jit_matrix_info *out_minfo, char *bop);

t_jit_err jit_transpose_init(void)
{
	long attrflags=0;
	t_jit_object *attr,*mop,*o;
	t_symbol *atsym;

	atsym = gensym("jit_attr_offset");

	_jit_transpose_class = jit_class_new("jit_transpose",(method)jit_transpose_new,(method)jit_transpose_free,
										 sizeof(t_jit_transpose),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,1);
	//jit_mop_output_nolink(mop,1);
	jit_class_addadornment(_jit_transpose_class,mop);
	o = jit_object_method(mop,_jit_sym_getoutput,1);
	jit_object_method(o,_jit_sym_ioproc,jit_transpose_output_adapt);
	//add methods
	jit_class_addmethod(_jit_transpose_class, (method)jit_transpose_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);

	jit_class_register(_jit_transpose_class);

	return JIT_ERR_NONE;
}

t_jit_err jit_transpose_output_adapt(void *mop, void *mop_io, void *matrix)
{
	void *m;
	t_jit_matrix_info info;
	long tmp;

	if (matrix&&(m=jit_object_method(mop_io,_jit_sym_getmatrix))&&
			jit_attr_getlong(mop,_jit_sym_adapt))
	{
		jit_object_method(matrix,_jit_sym_getinfo,&info);
		tmp = info.dim[0];
		info.dim[0] = info.dim[1];
		info.dim[1] = tmp;
		info.dimcount = 2;
		jit_object_method(m,_jit_sym_setinfo,&info);
		jit_object_method(m,_jit_sym_frommatrix,matrix,NULL);
	}

	return JIT_ERR_NONE;
}

t_jit_err jit_transpose_matrix_calc(t_jit_transpose *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock,out_savelock;
	t_jit_matrix_info in_minfo,out_minfo;
	char *in_bp,*out_bp;
	long i,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	void *in_matrix,*out_matrix;

	in_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);
	out_matrix 	= jit_object_method(outputs,_jit_sym_getindex,0);

	if (x&&in_matrix&&out_matrix) {
		in_savelock = (long) jit_object_method(in_matrix,_jit_sym_lock,1);
		out_savelock = (long) jit_object_method(out_matrix,_jit_sym_lock,1);

		jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
		jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);

		jit_object_method(in_matrix,_jit_sym_getdata,&in_bp);
		jit_object_method(out_matrix,_jit_sym_getdata,&out_bp);

		if (!in_bp) { err=JIT_ERR_INVALID_INPUT; goto out;}
		if (!out_bp) { err=JIT_ERR_INVALID_OUTPUT; goto out;}

		//compatible types?
		if ((in_minfo.type!=out_minfo.type)) {
			err=JIT_ERR_MISMATCH_TYPE;
			goto out;
		}

		//get dimensions/planecount
		dimcount   = out_minfo.dimcount;
		planecount = out_minfo.planecount;

		//this is different than usual...swapin dimension 0 and 1 for input matrix
		dim[0] = out_minfo.dim[0];
		if ((in_minfo.dim[1]<dim[0])&&in_minfo.dim[1]>1) {
			dim[0] = in_minfo.dim[1];
		}
		dim[1] = out_minfo.dim[1];
		if ((in_minfo.dim[0]<dim[1])&&in_minfo.dim[0]>1) {
			dim[1] = in_minfo.dim[0];
		}
		for (i=2; i<dimcount; i++) {
			//if dimsize is 1, treat as infinite domain across that dimension.
			//otherwise truncate if less than the output dimsize
			dim[i] = out_minfo.dim[i];
			if ((in_minfo.dim[i]<dim[i])&&in_minfo.dim[i]>1) {
				dim[i] = in_minfo.dim[i];
			}
		}

		jit_transpose_calculate_ndim(dimcount, dim, planecount, NULL, &in_minfo, in_bp, &out_minfo, out_bp);
	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(out_matrix,_jit_sym_lock,out_savelock);
	jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	return err;
}


void jit_transpose_calculate_ndim(long dimcount, long *dim, long planecount, void *vecdata, t_jit_matrix_info *in_minfo, char *bip,
								  t_jit_matrix_info *out_minfo, char *bop)
{
	long i,j,n;
	char *ip=bip,*op=bop;
	t_jit_op_info in_opinfo,out_opinfo;

	if (dimcount<1) return; //safety

	switch(dimcount) {
	case 1:
		dim[1] = 1;
	case 2:
		n = dim[0];
		//using vertical stride for input
		in_opinfo.stride = in_minfo->dim[1]>1?in_minfo->dimstride[1]/jit_matrix_info_typesize(in_minfo):0;
		out_opinfo.stride = out_minfo->dim[0]>1?out_minfo->planecount:0;
		if (in_minfo->type==_jit_sym_char) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in_opinfo.p  = bip + i*in_minfo->dimstride[0] + j%in_minfo->planecount;
					out_opinfo.p = bop + i*out_minfo->dimstride[1] + j%out_minfo->planecount;
					jit_op_vector_pass_char(n,NULL,&in_opinfo,NULL,&out_opinfo);
				}
			}
		} else if (in_minfo->type==_jit_sym_long) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in_opinfo.p  = bip + i*in_minfo->dimstride[0] + (j%in_minfo->planecount)*4;
					out_opinfo.p = bop + i*out_minfo->dimstride[1] + (j%out_minfo->planecount)*4;
					jit_op_vector_pass_long(n,NULL,&in_opinfo,NULL,&out_opinfo);
				}
			}
		} else if (in_minfo->type==_jit_sym_float32) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in_opinfo.p  = bip + i*in_minfo->dimstride[0] + (j%in_minfo->planecount)*4;
					out_opinfo.p = bop + i*out_minfo->dimstride[1] + (j%out_minfo->planecount)*4;
					jit_op_vector_pass_float32(n,NULL,&in_opinfo,NULL,&out_opinfo);
				}
			}
		} else if (in_minfo->type==_jit_sym_float64) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in_opinfo.p  = bip + i*in_minfo->dimstride[0] + (j%in_minfo->planecount)*8;
					out_opinfo.p = bop + i*out_minfo->dimstride[1] + (j%out_minfo->planecount)*8;
					jit_op_vector_pass_float64(n,NULL,&in_opinfo,NULL,&out_opinfo);
				}
			}
		}
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			ip = bip + i*in_minfo->dimstride[dimcount-1];
			op  = bop  + i*out_minfo->dimstride[dimcount-1];
			jit_transpose_calculate_ndim(dimcount-1,dim,planecount,vecdata,in_minfo,ip,out_minfo,op);
		}
	}
}

t_jit_transpose *jit_transpose_new(void)
{
	t_jit_transpose *x;

	if (x=(t_jit_transpose *)jit_object_alloc(_jit_transpose_class)) {

	} else {
		x = NULL;
	}
	return x;
}

void jit_transpose_free(t_jit_transpose *x)
{
	//nada
}
