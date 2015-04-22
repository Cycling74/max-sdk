/*
	Copyright 2001 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"

typedef struct _jit_unpack
{
	t_object	ob;
	long		offset[JIT_MATRIX_MAX_PLANECOUNT];
	long		offsetcount;
	long		jump[JIT_MATRIX_MAX_PLANECOUNT];
	long		jumpcount;
} t_jit_unpack;

void *_jit_unpack_class;

t_jit_err jit_unpack_init(void);
t_jit_unpack *jit_unpack_new(void);
void jit_unpack_free(t_jit_unpack *x);
t_jit_err jit_unpack_matrix_calc(t_jit_unpack *x, void *inputs, void *outputs);
void jit_unpack_calculate_ndim(long dimcount, long *dim, long planecount, long offset,
							   t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop);

t_jit_err jit_unpack_init(void)
{
	long attrflags;
	void *mop, *attr;

	_jit_unpack_class = jit_class_new("jit_unpack",(method)jit_unpack_new,(method)jit_unpack_free,
									  sizeof(t_jit_unpack),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,-1); //#inputs,#outputs(variable)
	jit_class_addadornment(_jit_unpack_class,mop);
	//add methods
	jit_class_addmethod(_jit_unpack_class, (method)jit_unpack_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);

	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;

	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"offset",_jit_sym_long,JIT_MATRIX_MAX_PLANECOUNT,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_unpack,offsetcount), calcoffset(t_jit_unpack,offset));
	jit_class_addattr(_jit_unpack_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Offset");

	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"jump",_jit_sym_long,JIT_MATRIX_MAX_PLANECOUNT,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_unpack,jumpcount), calcoffset(t_jit_unpack,jump));
	jit_class_addattr(_jit_unpack_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Jump");
	
	jit_class_register(_jit_unpack_class);

	return JIT_ERR_NONE;
}

t_jit_err jit_unpack_matrix_calc(t_jit_unpack *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock,out_savelock[JIT_MATRIX_MAX_PLANECOUNT];
	t_jit_matrix_info in_minfo,out_minfo[JIT_MATRIX_MAX_PLANECOUNT],outx_minfo;
	char *in_bp,*out_bp[JIT_MATRIX_MAX_PLANECOUNT];
	long i,j,out_count,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	void *in_matrix,*out_matrix[JIT_MATRIX_MAX_PLANECOUNT];

	in_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);
	out_count	= (long) jit_object_method(outputs,_jit_sym_getsize);
	for (i=0; i<out_count; i++)
		out_matrix[i] = jit_object_method(outputs,_jit_sym_getindex,i);

	if (x&&in_matrix&&out_matrix&&out_matrix[0]) {
		in_savelock = (long) jit_object_method(in_matrix,_jit_sym_lock,1);
		jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
		jit_object_method(in_matrix,_jit_sym_getdata,&in_bp);

		if (!in_bp) { err=JIT_ERR_INVALID_INPUT; goto out;}

		for (i=0; i<out_count; i++) {
			if (out_matrix[i]) {
				jit_object_method(out_matrix[i],_jit_sym_getinfo,&out_minfo[i]);
				out_savelock[i] = (long) jit_object_method(out_matrix[i],_jit_sym_lock,1);
				jit_object_method(out_matrix[i],_jit_sym_getdata,&out_bp[i]);
				if (!out_bp[i]) err=JIT_ERR_INVALID_OUTPUT;
			} else {
				err = JIT_ERR_GENERIC;
			}
		}
		if (err) goto out;

		for (i=0; i<out_count; i++) {
			//compatible types?
			if ((in_minfo.type!=out_minfo[i].type)) {
				err=JIT_ERR_MISMATCH_TYPE;
				goto out;
			}

			//jit_object_method(out_matrix[i],_jit_sym_getinfo,&outx_minfo);
			if ((in_minfo.type!=out_minfo[i].type)) {
				err=JIT_ERR_MISMATCH_TYPE;
				goto out;
			}
			if ((in_minfo.dimcount!=out_minfo[i].dimcount)) {
				err=JIT_ERR_MISMATCH_DIM;
				goto out;
			}
			for (j=0; j<out_minfo[i].dimcount; j++) {
				if ((in_minfo.dim[j]!=out_minfo[i].dim[j])) {
					err=JIT_ERR_MISMATCH_DIM;
					goto out;
				}
			}
		}

		for (i=0; i<out_count; i++) {
			//get dimensions/planecount
			dimcount   = out_minfo[i].dimcount;
			planecount = MIN(in_minfo.planecount,out_minfo[i].planecount);

			for (j=0; j<dimcount; j++) {
				//if dimsize is 1, treat as infinite domain across that dimension.
				//otherwise truncate if less than the output dimsize
				dim[j] = out_minfo[i].dim[j];
				if ((in_minfo.dim[j]<dim[j])&&in_minfo.dim[j]>1) {
					dim[j] = in_minfo.dim[j];
				}
			}

			jit_unpack_calculate_ndim(dimcount, dim, planecount, x->offset[i], &in_minfo, in_bp, out_minfo + i, out_bp[i]);
		}
	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	for (i=out_count-1; i>=0; i--) {
		if (out_matrix[i]) {
			jit_object_method(out_matrix[i],_jit_sym_lock,out_savelock[i]);
		}
	}
	jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	return err;
}


void jit_unpack_calculate_ndim(long dimcount, long *dim, long planecount, long offset,
							   t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop)
{
	long i,j,n;
	char *ip,*op;
	t_jit_op_info in_opinfo,out_opinfo;

	if (dimcount<1) return; //safety

	switch(dimcount) {
	case 1:
		dim[1]=1;
	case 2:
		//if planecount the same, flatten planes - treat as single plane data for speed
		n = dim[0];
		in_opinfo.stride = in_minfo->dim[0]>1?in_minfo->planecount:0;
		out_opinfo.stride = out_minfo->dim[0]>1?out_minfo->planecount:0;
		if (in_minfo->type==_jit_sym_char) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in_opinfo.p  = bip + i*in_minfo->dimstride[1] + (j+offset)%in_minfo->planecount;
					out_opinfo.p = bop + i*out_minfo->dimstride[1] + j;
					jit_op_vector_pass_char(n, NULL, &in_opinfo, NULL, &out_opinfo);
				}
			}
		} else if (in_minfo->type==_jit_sym_long) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in_opinfo.p  = bip + i*in_minfo->dimstride[1] + ((j+offset)%in_minfo->planecount)*4;
					out_opinfo.p = bop + i*out_minfo->dimstride[1] + j*4;
					jit_op_vector_pass_long(n, NULL, &in_opinfo, NULL, &out_opinfo);
				}
			}
		} else if (in_minfo->type==_jit_sym_float32) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in_opinfo.p  = bip + i*in_minfo->dimstride[1] + ((j+offset)%in_minfo->planecount)*4;
					out_opinfo.p = bop + i*out_minfo->dimstride[1] + j*4;
					jit_op_vector_pass_float32(n, NULL, &in_opinfo, NULL, &out_opinfo);
				}
			}
		} else if (in_minfo->type==_jit_sym_float64) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in_opinfo.p  = bip + i*in_minfo->dimstride[1] + ((j+offset)%in_minfo->planecount)*8;
					out_opinfo.p = bop + i*out_minfo->dimstride[1] + j*8;
					jit_op_vector_pass_float64(n, NULL, &in_opinfo, NULL, &out_opinfo);
				}
			}
		}
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			ip = bip + i*in_minfo->dimstride[dimcount-1];
			for (j=0; j<planecount; j++) {
				op = bop + i*out_minfo->dimstride[dimcount-1];
			}
			jit_unpack_calculate_ndim(dimcount-1,dim,planecount,offset,in_minfo,ip,out_minfo,op);
		}
	}
}

t_jit_unpack *jit_unpack_new(void)
{
	t_jit_unpack *x;
	long i;

	if (x=(t_jit_unpack *)jit_object_alloc(_jit_unpack_class)) {
		x->offsetcount = JIT_MATRIX_MAX_PLANECOUNT; // else won't work for the general case
		x->jumpcount = JIT_MATRIX_MAX_PLANECOUNT; // else won't work for the general case

		for(i=0; i < JIT_MATRIX_MAX_PLANECOUNT; i++) {
			x->offset[i] = i;
			x->jump[i] = 1;
		}
	} else {
		x = NULL;
	}
	return x;
}

void jit_unpack_free(t_jit_unpack *x)
{
	//nada
}
