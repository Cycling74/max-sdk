/*
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"
#include "jit.fixmath.h"

typedef struct _jit_map_vecdata
{
	long 				clip;
	double 				scale;
	double 				bias;
	long				cscale;
	long				cbias;
	double 				min;
	double 				max;
	long				lmin;
	long				lmax;
	long				cmin;
	long				cmax;
} t_jit_map_vecdata;

typedef struct _jit_map
{
	t_object				ob;
	double					map[4];
	long					clip;
} t_jit_map;

void *_jit_map_class;

t_jit_err jit_map_init(void);
t_jit_map *jit_map_new(void);
void jit_map_free(t_jit_map *x);
t_jit_err jit_map_getvecdata(t_jit_map *x, t_jit_map_vecdata *vd);
t_jit_err jit_map_matrix_calc(t_jit_map *x, void *inputs, void *outputs);

void jit_map_calculate_ndim(t_jit_map_vecdata *vecdata, long dim, long *dimsize, long planecount, t_jit_matrix_info *in_minfo, char *bip,
							t_jit_matrix_info *out_minfo, char *bop);
void jit_map_vector_char			(long n, t_jit_map_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out);
void jit_map_vector_long			(long n, t_jit_map_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out);
void jit_map_vector_float32			(long n, t_jit_map_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out);
void jit_map_vector_float64			(long n, t_jit_map_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out);
void jit_map_vector_char_clip		(long n, t_jit_map_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out);
void jit_map_vector_long_clip		(long n, t_jit_map_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out);
void jit_map_vector_float32_clip	(long n, t_jit_map_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out);
void jit_map_vector_float64_clip	(long n, t_jit_map_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out);

t_jit_err jit_map_init(void)
{
	long attrflags=0;
	t_jit_object *attr,*mop;

	_jit_map_class = jit_class_new("jit_map",(method)jit_map_new,(method)jit_map_free,
								   sizeof(t_jit_map),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,1); //#inputs,#outputs
	jit_class_addadornment(_jit_map_class,mop);
	//add methods
	jit_class_addmethod(_jit_map_class, (method)jit_map_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);
	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;

	CLASS_STICKY_CATEGORY(_jit_map_class,0,"Behavior");
	CLASS_STICKY_ATTR(_jit_map_class,"basic",0,"1");

	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"map",_jit_sym_float64,4,attrflags,
						  (method)0L,(method)0L,0/*fix*/,calcoffset(t_jit_map,map));
	jit_class_addattr(_jit_map_class,attr);
	CLASS_ATTR_LABEL(_jit_map_class,"map",0,"Input to Output Map");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"clip",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_map,clip));
	jit_class_addattr(_jit_map_class,attr);
	CLASS_ATTR_STYLE_LABEL(_jit_map_class,"clip",0,"onoff","Clip Values");

	CLASS_STICKY_CATEGORY_CLEAR(_jit_map_class);
	CLASS_STICKY_ATTR_CLEAR(_jit_map_class, "basic");

	jit_class_register(_jit_map_class);

	return JIT_ERR_NONE;
}

t_jit_err jit_map_getvecdata(t_jit_map *x, t_jit_map_vecdata *vd)
{
	if (x&&vd) {
		vd->clip		= x->clip;
		vd->scale 		= (x->map[3] - x->map[2])/(x->map[1] - x->map[0]);
		vd->bias 		= x->map[2] - (x->map[0]*vd->scale);
		vd->cscale		= (long)(vd->scale*(double)fixed1);
		vd->cbias		= (long)(vd->bias*255.*(double)fixed1);
		vd->min 		= x->map[2];
		vd->max 		= x->map[3];
		vd->lmin 		= vd->min;
		vd->lmax 		= vd->max;
		vd->cmin 		= vd->min*255.;
		vd->cmax 		= vd->max*255.;
		CLIP_ASSIGN(vd->cmin,0,255);
		CLIP_ASSIGN(vd->cmax,0,255);

		return JIT_ERR_NONE;
	} else {
		return JIT_ERR_INVALID_PTR;
	}
}

t_jit_err jit_map_matrix_calc(t_jit_map *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock,in2_savelock,out_savelock;
	t_jit_matrix_info in_minfo,out_minfo;
	char *in_bp,*out_bp;
	long i,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	t_jit_map_vecdata	vecdata;
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
		if (in_minfo.type!=out_minfo.type) {
			err=JIT_ERR_MISMATCH_TYPE;
			goto out;
		}

		//get dimensions/planecount
		dimcount   = out_minfo.dimcount;
		planecount = out_minfo.planecount;

		for (i=0; i<dimcount; i++) {
			//if dimsize is 1, treat as infinite domain across that dimension.
			//otherwise truncate if less than the output dimsize
			dim[i] = out_minfo.dim[i];
			if ((in_minfo.dim[i]<dim[i])&&in_minfo.dim[i]>1) {
				dim[i] = in_minfo.dim[i];
			}
		}

		jit_map_getvecdata(x,&vecdata);
		jit_parallel_ndim_simplecalc2((method)jit_map_calculate_ndim,
									  &vecdata, dimcount, dim, planecount, &in_minfo, in_bp, &out_minfo, out_bp,
									  0 /* flags1 */, 0 /* flags2 */);
	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(out_matrix,_jit_sym_lock,out_savelock);
	jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	return err;
}


void jit_map_calculate_ndim(t_jit_map_vecdata *vecdata, long dimcount, long *dim, long planecount, t_jit_matrix_info *in_minfo, char *bip,
							t_jit_matrix_info *out_minfo, char *bop)
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
		if ((in_minfo->dim[0]>1)&&(out_minfo->dim[0]>1)&&
				(in_minfo->planecount==out_minfo->planecount)) {
			in_opinfo.stride = 1;
			out_opinfo.stride = 1;
			n *= planecount;
			planecount = 1;
		} else {
			in_opinfo.stride = in_minfo->dim[0]>1?in_minfo->planecount:0;
			out_opinfo.stride = out_minfo->dim[0]>1?out_minfo->planecount:0;
		}
		if (in_minfo->type==_jit_sym_char) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in_opinfo.p  = bip + i*in_minfo->dimstride[1] + j%in_minfo->planecount;
					out_opinfo.p = bop + i*out_minfo->dimstride[1] + j%out_minfo->planecount;
					if (vecdata->clip)
						jit_map_vector_char_clip(n,vecdata,&in_opinfo,&out_opinfo);
					else
						jit_map_vector_char(n,vecdata,&in_opinfo,&out_opinfo);
				}
			}
		} else if (in_minfo->type==_jit_sym_long) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in_opinfo.p  = bip + i*in_minfo->dimstride[1] + (j%in_minfo->planecount)*4;
					out_opinfo.p = bop + i*out_minfo->dimstride[1] + (j%out_minfo->planecount)*4;
					if (vecdata->clip)
						jit_map_vector_long_clip(n,vecdata,&in_opinfo,&out_opinfo);
					else
						jit_map_vector_long(n,vecdata,&in_opinfo,&out_opinfo);
				}
			}
		} else if (in_minfo->type==_jit_sym_float32) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in_opinfo.p  = bip + i*in_minfo->dimstride[1] + (j%in_minfo->planecount)*4;
					out_opinfo.p = bop + i*out_minfo->dimstride[1] + (j%out_minfo->planecount)*4;
					if (vecdata->clip)
						jit_map_vector_float32_clip(n,vecdata,&in_opinfo,&out_opinfo);
					else
						jit_map_vector_float32(n,vecdata,&in_opinfo,&out_opinfo);
				}
			}
		} else if (in_minfo->type==_jit_sym_float64) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in_opinfo.p  = bip + i*in_minfo->dimstride[1] + (j%in_minfo->planecount)*8;
					out_opinfo.p = bop + i*out_minfo->dimstride[1] + (j%out_minfo->planecount)*8;
					if (vecdata->clip)
						jit_map_vector_float64_clip(n,vecdata,&in_opinfo,&out_opinfo);
					else
						jit_map_vector_float64(n,vecdata,&in_opinfo,&out_opinfo);
				}
			}
		}
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			ip = bip + i*in_minfo->dimstride[dimcount-1];
			op = bop + i*out_minfo->dimstride[dimcount-1];
			jit_map_calculate_ndim(vecdata,dimcount-1,dim,planecount,in_minfo,ip,out_minfo,op);
		}
	}
}

void jit_map_vector_char(long n, t_jit_map_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	long scale=vecdata->cscale;
	long bias=vecdata->cbias;
	uchar *ip,*op;
	long is,os;

	ip = ((uchar *)in->p);
	op = ((uchar *)out->p);
	is = in->stride;
	os = out->stride;

	if ((is==1)&&(os==1)) {
		++n; --op; --ip;
		while (--n) {
			*++op = (((long)(*++ip)*scale)+bias)>>16L;
		}
	} else {
		while (n--) {
			*op = (((long)(*ip)*scale)+bias)>>16L;
			ip+=is; op+=os;
		}
	}
}

void jit_map_vector_long(long n, t_jit_map_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	double scale=vecdata->scale;
	double bias=vecdata->bias;
	t_int32 *ip,*op;
	long is,os;

	ip = ((t_int32 *)in->p);
	op = ((t_int32 *)out->p);
	is = in->stride;
	os = out->stride;

	if ((is==1)&&(os==1)) {
		++n; --op; --ip;
		while (--n) {
			*++op = ((*++ip)*scale)+bias;
		}
	} else {
		while (n--) {
			*op = ((*ip)*scale)+bias;
			ip+=is; op+=os;
		}
	}
}

void jit_map_vector_float32(long n, t_jit_map_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	float scale=vecdata->scale;
	float bias=vecdata->bias;
	float *ip,*op;
	long is,os;

	ip = ((float *)in->p);
	op = ((float *)out->p);
	is = in->stride;
	os = out->stride;

	if ((is==1)&&(os==1)) {
		++n; --op; --ip;
		while (--n) {
			*++op = ((*++ip)*scale)+bias;
		}
	} else {
		while (n--) {
			*op = ((*ip)*scale)+bias;
			ip+=is; op+=os;
		}
	}
}

void jit_map_vector_float64(long n, t_jit_map_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	double scale=vecdata->scale;
	double bias=vecdata->bias;
	double *ip,*op;
	long is,os;

	ip = ((double *)in->p);
	op  = ((double *)out->p);
	is = in->stride;
	os  = out->stride;

	if ((is==1)&&(os==1)) {
		++n; --op; --ip;
		while (--n) {
			*++op = ((*++ip)*scale)+bias;
		}
	} else {
		while (n--) {
			*op = ((*ip)*scale)+bias;
			ip+=is; op+=os;
		}
	}
}

void jit_map_vector_char_clip(long n, t_jit_map_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	long min=vecdata->cmin;
	long max=vecdata->cmax;
	long scale=vecdata->cscale;
	long bias=vecdata->cbias;
	uchar *ip,*op;
	long is,os;
	long tmp;

	ip = ((uchar *)in->p);
	op = ((uchar *)out->p);
	is = in->stride;
	os = out->stride;

	if ((is==1)&&(os==1)) {
		++n; --op; --ip;
		while (--n) {
			tmp = (((long)(*++ip)*scale)+bias)>>16L;
			*++op = tmp>max?max:tmp<min?min:tmp;
		}
	} else {
		while (n--) {
			tmp = (((long)(*ip)*scale)+bias)>>16L;
			*op = tmp>max?max:tmp<min?min:tmp;
			ip+=is; op+=os;
		}
	}
}

void jit_map_vector_long_clip(long n, t_jit_map_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	long min=vecdata->lmin;
	long max=vecdata->lmax;
	double scale=vecdata->scale;
	double bias=vecdata->bias;
	t_int32 *ip,*op;
	long is,os;
	long tmp;

	ip = ((t_int32 *)in->p);
	op = ((t_int32 *)out->p);
	is = in->stride;
	os = out->stride;

	if ((is==1)&&(os==1)) {
		++n; --op; --ip;
		while (--n) {
			tmp = ((*++ip)*scale)+bias;
			*++op = tmp>max?max:tmp<min?min:tmp;
		}
	} else {
		while (n--) {
			tmp = ((*ip)*scale)+bias;
			*op = tmp>max?max:tmp<min?min:tmp;
			ip+=is; op+=os;
		}
	}
}

void jit_map_vector_float32_clip(long n, t_jit_map_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	float min=vecdata->min;
	float max=vecdata->max;
	float scale=vecdata->scale;
	float bias=vecdata->bias;
	float *ip,*op;
	long is,os;
	float tmp;

	ip = ((float *)in->p);
	op = ((float *)out->p);
	is = in->stride;
	os = out->stride;

	if ((is==1)&&(os==1)) {
		++n; --op; --ip;
		while (--n) {
			tmp = ((*++ip)*scale)+bias;
			*++op = tmp>max?max:tmp<min?min:tmp;
		}
	} else {
		while (n--) {
			tmp = ((*ip)*scale)+bias;
			*op = tmp>max?max:tmp<min?min:tmp;
			ip+=is; op+=os;
		}
	}
}

void jit_map_vector_float64_clip(long n, t_jit_map_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	double min=vecdata->min;
	double max=vecdata->max;
	double scale=vecdata->scale;
	double bias=vecdata->bias;
	double *ip,*op;
	long is,os;
	double tmp;

	ip = ((double *)in->p);
	op  = ((double *)out->p);
	is = in->stride;
	os  = out->stride;

	if ((is==1)&&(os==1)) {
		++n; --op; --ip;
		while (--n) {
			tmp = ((*++ip)*scale)+bias;
			*++op = tmp>max?max:tmp<min?min:tmp;
		}
	} else {
		while (n--) {
			tmp = ((*ip)*scale)+bias;
			*op = tmp>max?max:tmp<min?min:tmp;
			ip+=is; op+=os;
		}
	}
}

t_jit_map *jit_map_new(void)
{
	t_jit_map *x;

	if (x=(t_jit_map *)jit_object_alloc(_jit_map_class)) {
		x->map[0] = 0.;
		x->map[1] = 1.;
		x->map[2] = 0.;
		x->map[3] = 1.;
		x->clip = 1;
	} else {
		x = NULL;
	}
	return x;
}

void jit_map_free(t_jit_map *x)
{
	//nada
}
