#include "jit.common.h"

/*
	jit.change
	Copyright 2001-2005 - Cycling '74
	Jeremy Bernstein jeremy@bootsquad.com
*/

typedef struct _jit_change_vecdata_char
{
	long					planecount;
	long					thresh;
} t_jit_change_vecdata_char;

typedef struct _jit_change_vecdata_long
{
	long					planecount;
	long					thresh;
} t_jit_change_vecdata_long;

typedef struct _jit_change_vecdata_float32
{
	long					planecount;
	long					thresh;
} t_jit_change_vecdata_float32;

typedef struct _jit_change_vecdata_float64
{
	long					planecount;
	long					thresh;
} t_jit_change_vecdata_float64;

typedef struct _jit_change
{
	t_object				ob;
	long					thresh;
	long					change;
	char					mode;
} t_jit_change;

typedef union _jit_change_vecdata
{
	t_jit_change_vecdata_char 		v_char;
	t_jit_change_vecdata_long 		v_long;
	t_jit_change_vecdata_float32 	v_float32;
	t_jit_change_vecdata_float64 	v_float64;
} t_jit_change_vecdata;

void *_jit_change_class;

t_jit_change *jit_change_new(void);
void jit_change_free(t_jit_change *x);
t_jit_err jit_change_matrix_calc(t_jit_change *x, void *inputs, void *outputs);
t_jit_err jit_change_calculate_ndim(long dim, long *dimsize, long planecount,
									t_jit_change_vecdata *vecdata, t_jit_matrix_info *in_minfo, char *bip,
									t_jit_matrix_info *out_minfo, char *bop, char mode);
t_jit_err jit_change_getvecdata_char		(t_jit_change *x, t_jit_change_vecdata_char *vd, long planecount);
t_jit_err jit_change_getvecdata_long(t_jit_change *x, t_jit_change_vecdata_long *vd, long planecount);
t_jit_err jit_change_getvecdata_float32(t_jit_change *x, t_jit_change_vecdata_float32 *vd, long planecount);
t_jit_err jit_change_getvecdata_float64(t_jit_change *x, t_jit_change_vecdata_float64 *vd, long planecount);
t_jit_err jit_change_vector_char_plane4		(long n, t_jit_change_vecdata_char *vecdata, t_jit_op_info *in, t_jit_op_info *out);
t_jit_err jit_change_vector_char_plane1		(long n, t_jit_change_vecdata_char *vecdata, t_jit_op_info *in, t_jit_op_info *out);
t_jit_err jit_change_vector_char		(long n, t_jit_change_vecdata_char *vecdata, t_jit_op_info *in, t_jit_op_info *out);
t_jit_err jit_change_vector_long		(long n, t_jit_change_vecdata_long *vecdata, t_jit_op_info *in, t_jit_op_info *out);
t_jit_err jit_change_vector_float32		(long n, t_jit_change_vecdata_float32 *vecdata, t_jit_op_info *in, t_jit_op_info *out);
t_jit_err jit_change_vector_float64		(long n, t_jit_change_vecdata_float64 *vecdata, t_jit_op_info *in, t_jit_op_info *out);

t_jit_err jit_change_init(void);
//t_symbol *ps_change;

t_jit_err jit_change_init(void)
{
	long attrflags=0;
	t_jit_object *attr;
	t_jit_object *mop;

	_jit_change_class = jit_class_new("jit_change",(method)jit_change_new,(method)jit_change_free,
									  sizeof(t_jit_change),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,1);
	jit_class_addadornment(_jit_change_class,mop);
	//add methods
	jit_class_addmethod(_jit_change_class, (method)jit_change_matrix_calc, "matrix_calc", A_CANT, 0L);
	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;

	CLASS_STICKY_CATEGORY(_jit_change_class,0,"Behavior");
	CLASS_STICKY_ATTR(_jit_change_class,"basic",0,"1");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"thresh",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_change,thresh));
	jit_class_addattr(_jit_change_class,attr);
	CLASS_ATTR_LABEL(_jit_change_class,"thresh",0,"Threshold");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"mode",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_change,mode));
	jit_class_addattr(_jit_change_class,attr);
	CLASS_ATTR_LABEL(_jit_change_class,"mode",0,"Pass Mode");
	CLASS_ATTR_ENUMINDEX2(_jit_change_class, "mode", 0, "More-Than-Threshold", "Less-Than-Threshold");

	CLASS_STICKY_CATEGORY_CLEAR(_jit_change_class);
	CLASS_STICKY_ATTR_CLEAR(_jit_change_class, "basic");

	attrflags = JIT_ATTR_GET_OPAQUE_USER | JIT_ATTR_SET_OPAQUE_USER;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"change",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_change,change));
	jit_class_addattr(_jit_change_class,attr);

	jit_class_register(_jit_change_class);

//	ps_change = gensym("change");

	return JIT_ERR_NONE;
}

t_jit_err jit_change_getvecdata_char(t_jit_change *x, t_jit_change_vecdata_char *vd, long planecount)
{
	long i;

	if (x&&vd) {
		vd->thresh			= (x->thresh < 0) ? 0 : x->thresh;
		vd->planecount		= planecount;
		return JIT_ERR_NONE;
	} else {
		return JIT_ERR_INVALID_PTR;
	}
}

t_jit_err jit_change_getvecdata_long(t_jit_change *x, t_jit_change_vecdata_long *vd, long planecount)
{
	long i;

	if (x&&vd) {
		vd->thresh			= (x->thresh < 0) ? 0 : x->thresh;
		vd->planecount		= planecount;
		return JIT_ERR_NONE;
	} else {
		return JIT_ERR_INVALID_PTR;
	}
}

t_jit_err jit_change_getvecdata_float32(t_jit_change *x, t_jit_change_vecdata_float32 *vd, long planecount)
{
	long i;

	if (x&&vd) {
		vd->thresh			= (x->thresh < 0) ? 0 : x->thresh;
		vd->planecount		= planecount;
		return JIT_ERR_NONE;
	} else {
		return JIT_ERR_INVALID_PTR;
	}
}

t_jit_err jit_change_getvecdata_float64(t_jit_change *x, t_jit_change_vecdata_float64 *vd, long planecount)
{
	long i;

	if (x&&vd) {
		vd->thresh			= (x->thresh < 0) ? 0 : x->thresh;
		vd->planecount		= planecount;
		return JIT_ERR_NONE;
	} else {
		return JIT_ERR_INVALID_PTR;
	}
}

t_jit_err jit_change_matrix_calc(t_jit_change *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock,out_savelock;
	t_jit_matrix_info in_minfo,out_minfo;
	char *in_bp,*out_bp;
	long i,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	t_jit_change_vecdata	vecdata;
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

		//compatible planes?
		if (in_minfo.planecount!=out_minfo.planecount) {
			err=JIT_ERR_MISMATCH_PLANE;
			goto out;
		}

		if (x->thresh < 0) {
			x->change = 1;
			goto out;
		}

		//get dimensions/planecount
		dimcount   = out_minfo.dimcount;
		planecount = out_minfo.planecount;
		for (i=0; i<dimcount; i++) {
			dim[i] = MIN(in_minfo.dim[i],out_minfo.dim[i]);
		}

		if (in_minfo.type == _jit_sym_char)
			jit_change_getvecdata_char(x,&vecdata.v_char,planecount);
		else if (in_minfo.type == _jit_sym_long)
			jit_change_getvecdata_long(x,&vecdata.v_long,planecount);
		else if (in_minfo.type == _jit_sym_float32)
			jit_change_getvecdata_float32(x,&vecdata.v_float32,planecount);
		else if (in_minfo.type == _jit_sym_float64)
			jit_change_getvecdata_float64(x,&vecdata.v_float64,planecount);

		//calculate
		if (jit_change_calculate_ndim(dimcount, dim, planecount, &vecdata, &in_minfo, in_bp, &out_minfo, out_bp, x->mode)) {
			x->change = 1;
		}
	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(out_matrix,_jit_sym_lock,out_savelock);
	jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	return err;
}

//recursive function to handle higher dimension matrices, by processing 2D sections at a time
t_jit_err jit_change_calculate_ndim(long dimcount, long *dim, long planecount,
									t_jit_change_vecdata *vecdata, t_jit_matrix_info *in_minfo, char *bip,
									t_jit_matrix_info *out_minfo, char *bop, char mode)
{
	long i,j,n;
	char *ip=bip, *op=bop;
	t_jit_op_info in_opinfo, out_opinfo;

	if (dimcount<1) return 0; //safety

	switch(dimcount) {
	case 1:
		dim[1]=1;
	case 2:
		switch(mode) {
		case 1:
			n = dim[0];
			in_opinfo.stride = in_minfo->dim[0]>1?in_minfo->planecount:0;
			out_opinfo.stride = out_minfo->dim[0]>1?out_minfo->planecount:0;
			if (in_minfo->type==_jit_sym_char) {
				switch (planecount) {
				case 1:
					for (i=0; i<dim[1]; i++) {
						in_opinfo.p = bip + i*in_minfo->dimstride[1];
						out_opinfo.p = bop  + i*out_minfo->dimstride[1];
						if (jit_change_vector_char_plane1(n,&(vecdata->v_char),&in_opinfo,&out_opinfo)) {
							return 0;
						}
					}
					return 1;
					break;
				case 4:
					for (i=0; i<dim[1]; i++) {
						in_opinfo.p = bip + i*in_minfo->dimstride[1];
						out_opinfo.p = bop  + i*out_minfo->dimstride[1];
						if (jit_change_vector_char_plane4(n,&(vecdata->v_char),&in_opinfo,&out_opinfo)) {
							return 0;
						}
					}
					return 1;
					break;
				default:
					for (i=0; i<dim[1]; i++) {
						in_opinfo.p = bip + i*in_minfo->dimstride[1];
						out_opinfo.p = bop  + i*out_minfo->dimstride[1];
						if (jit_change_vector_char(n,&(vecdata->v_char),&in_opinfo,&out_opinfo)) {
							return 0;
						}
					}
					return 1;
					break;
				}
			}
			else if (in_minfo->type==_jit_sym_long) {
				for (i=0; i<dim[1]; i++) {
					in_opinfo.p = bip + i*in_minfo->dimstride[1];
					out_opinfo.p = bop  + i*out_minfo->dimstride[1];
					if (jit_change_vector_long(n,&(vecdata->v_long),&in_opinfo,&out_opinfo)) {
						return 0;
					}
				}
				return 1;
			}
			else if (in_minfo->type==_jit_sym_float32) {
				for (i=0; i<dim[1]; i++) {
					in_opinfo.p = bip + i*in_minfo->dimstride[1];
					out_opinfo.p = bop  + i*out_minfo->dimstride[1];
					if (jit_change_vector_float32(n,&(vecdata->v_float32),&in_opinfo,&out_opinfo)) {
						return 0;
					}
				}
				return 1;
			}
			else if (in_minfo->type==_jit_sym_float64) {
				for (i=0; i<dim[1]; i++) {
					in_opinfo.p = bip + i*in_minfo->dimstride[1];
					out_opinfo.p = bop  + i*out_minfo->dimstride[1];
					if (jit_change_vector_float64(n,&(vecdata->v_float64),&in_opinfo,&out_opinfo)) {
						return 0;
					}
				}
				return 1;
			}
			break;
		case 0:
		default:
			n = dim[0];
			in_opinfo.stride = in_minfo->dim[0]>1?in_minfo->planecount:0;
			out_opinfo.stride = out_minfo->dim[0]>1?out_minfo->planecount:0;
			if (in_minfo->type==_jit_sym_char) {
				switch (planecount) {
				case 1:
					for (i=0; i<dim[1]; i++) {
						in_opinfo.p = bip + i*in_minfo->dimstride[1];
						out_opinfo.p = bop  + i*out_minfo->dimstride[1];
						if (jit_change_vector_char_plane1(n,&(vecdata->v_char),&in_opinfo,&out_opinfo)) {
							return 1;
						}
					}
					break;
				case 4:
					for (i=0; i<dim[1]; i++) {
						in_opinfo.p = bip + i*in_minfo->dimstride[1];
						out_opinfo.p = bop  + i*out_minfo->dimstride[1];
						if (jit_change_vector_char_plane4(n,&(vecdata->v_char),&in_opinfo,&out_opinfo)) {
							return 1;
						}
					}
					break;
				default:
					for (i=0; i<dim[1]; i++) {
						in_opinfo.p = bip + i*in_minfo->dimstride[1];
						out_opinfo.p = bop  + i*out_minfo->dimstride[1];
						if (jit_change_vector_char(n,&(vecdata->v_char),&in_opinfo,&out_opinfo)) {
							return 1;
						}
					}
					break;
				}
			}
			else if (in_minfo->type==_jit_sym_long) {
				for (i=0; i<dim[1]; i++) {
					in_opinfo.p = bip + i*in_minfo->dimstride[1];
					out_opinfo.p = bop  + i*out_minfo->dimstride[1];
					if (jit_change_vector_long(n,&(vecdata->v_long),&in_opinfo,&out_opinfo)) {
						return 1;
					}
				}
			}
			else if (in_minfo->type==_jit_sym_float32) {
				for (i=0; i<dim[1]; i++) {
					in_opinfo.p = bip + i*in_minfo->dimstride[1];
					out_opinfo.p = bop  + i*out_minfo->dimstride[1];
					if (jit_change_vector_float32(n,&(vecdata->v_float32),&in_opinfo,&out_opinfo)) {
						return 1;
					}
				}
			}
			else if (in_minfo->type==_jit_sym_float64) {
				for (i=0; i<dim[1]; i++) {
					in_opinfo.p = bip + i*in_minfo->dimstride[1];
					out_opinfo.p = bop  + i*out_minfo->dimstride[1];
					if (jit_change_vector_float64(n,&(vecdata->v_float64),&in_opinfo,&out_opinfo)) {
						return 1;
					}
				}
			}
			break;
		}
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			ip = bip + i*in_minfo->dimstride[dimcount-1];
			op = bop + i*out_minfo->dimstride[dimcount-1];
			jit_change_calculate_ndim(dimcount-1,dim,planecount,vecdata,in_minfo,ip,out_minfo,op, mode);
		}
	}
	return 0;
}

t_jit_err jit_change_vector_char_plane4(long n, t_jit_change_vecdata_char *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	long thresh;
	t_uint32 *ip,*op;

	ip = ((t_uint32 *)in->p);
	op  = ((t_uint32 *)out->p);

	thresh = vecdata->thresh;

	++n; ++thresh; --op; --ip;
	while (--n) {
		if (*++ip != *++op) {
			if (!(--thresh)) return 1;
		}
	}

	vecdata->thresh = thresh - 1;
	return 0;
}

t_jit_err jit_change_vector_char_plane1(long n, t_jit_change_vecdata_char *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	long thresh;
	uchar *ip,*op;

	ip = ((uchar *)in->p);
	op  = ((uchar *)out->p);

	thresh = vecdata->thresh;

	++n; ++thresh; --op; --ip;
	while (--n) {
		if (*++ip != *++op) {
			if (!(--thresh)) return 1;
		}
	}

	vecdata->thresh = thresh - 1;
	return 0;
}

t_jit_err jit_change_vector_char(long n, t_jit_change_vecdata_char *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	long thresh, planecount, k;
	uchar *ip,*op;

	ip = ((uchar *)in->p);
	op  = ((uchar *)out->p);

	thresh = vecdata->thresh;
	planecount = vecdata->planecount;

	++n; ++thresh; //--op;--ip;
	while (--n) {
		for (k = 0; k < planecount; k++) {
			if (*(ip + k) != *(op + k)) {
				if (!(--thresh)) return 1;
				else {
					ip += planecount;
					op += planecount;
					break;
				}
			}
		}
		ip += planecount;
		op += planecount;
	}

	vecdata->thresh = thresh - 1;
	return 0;
}

t_jit_err jit_change_vector_long(long n, t_jit_change_vecdata_long *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	long thresh, planecount, k;
	t_int32 *ip,*op;

	ip = ((t_int32 *)in->p);
	op  = ((t_int32 *)out->p);

	thresh = vecdata->thresh;
	planecount = vecdata->planecount;

	++n; ++thresh; //--op;--ip;
	while (--n) {
		for (k = 0; k < planecount; k++) {
			if (*(ip + k) != *(op + k)) {
				if (!(--thresh)) return 1;
				else {
					ip += planecount;
					op += planecount;
					break;
				}
			}
		}
		ip += planecount;
		op += planecount;
	}

	vecdata->thresh = thresh - 1;
	return 0;
}

t_jit_err jit_change_vector_float32(long n, t_jit_change_vecdata_float32 *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	long thresh, planecount, k;
	float *ip,*op;

	ip = ((float *)in->p);
	op  = ((float *)out->p);

	thresh = vecdata->thresh;
	planecount = vecdata->planecount;

	++n; ++thresh; //--op;--ip;
	while (--n) {
		for (k = 0; k < planecount; k++) {
			if (*(ip + k) != *(op + k)) {
				if (!(--thresh)) return 1;
				else {
					ip += planecount;
					op += planecount;
					break;
				}
			}
		}
		ip += planecount;
		op += planecount;
	}

	vecdata->thresh = thresh - 1;
	return 0;
}

t_jit_err jit_change_vector_float64(long n, t_jit_change_vecdata_float64 *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	long thresh, planecount, k;
	double *ip,*op;

	ip = ((double *)in->p);
	op  = ((double *)out->p);

	thresh = vecdata->thresh;
	planecount = vecdata->planecount;

	++n; ++thresh; //--op;--ip;
	while (--n) {
		for (k = 0; k < planecount; k++) {
			if (*(ip + k) != *(op + k)) {
				if (!(--thresh)) return 1;
				else {
					ip += planecount;
					op += planecount;
					break;
				}
			}
		}
		ip += planecount;
		op += planecount;
	}

	vecdata->thresh = thresh - 1;
	return 0;
}

t_jit_change *jit_change_new(void)
{
	t_jit_change *x;
	long i;

	if (x=(t_jit_change *)jit_object_alloc(_jit_change_class)) {
		x->thresh = 0;
		x->change = 0;
		x->mode = 0;
	} else {
		x = NULL;
	}
	return x;
}

void jit_change_free(t_jit_change *x)
{
	//nada
}
