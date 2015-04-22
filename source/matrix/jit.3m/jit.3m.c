/*
	Copyright 2001-2011 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"
#include "ext_systhread.h"

typedef struct _jit_3m_vecdata_char
{
	long				min[JIT_MATRIX_MAX_PLANECOUNT];
	long 				mean[JIT_MATRIX_MAX_PLANECOUNT];
	long 				max[JIT_MATRIX_MAX_PLANECOUNT];
} t_jit_3m_vecdata_char;

typedef struct _jit_3m_vecdata_long
{
	long				min[JIT_MATRIX_MAX_PLANECOUNT];
	double 				mean[JIT_MATRIX_MAX_PLANECOUNT];
	long				max[JIT_MATRIX_MAX_PLANECOUNT];
} t_jit_3m_vecdata_long;

typedef struct _jit_3m_vecdata_float32
{
	float				min[JIT_MATRIX_MAX_PLANECOUNT];
	float 				mean[JIT_MATRIX_MAX_PLANECOUNT];
	float				max[JIT_MATRIX_MAX_PLANECOUNT];
} t_jit_3m_vecdata_float32;

typedef struct _jit_3m_vecdata_float64
{
	double				min[JIT_MATRIX_MAX_PLANECOUNT];
	double 				mean[JIT_MATRIX_MAX_PLANECOUNT];
	double				max[JIT_MATRIX_MAX_PLANECOUNT];
} t_jit_3m_vecdata_float64;

typedef struct _jit_3m_vecdata
{
	t_jit_3m_vecdata_char 		v_char;
	t_jit_3m_vecdata_long 		v_long;
	t_jit_3m_vecdata_float32 	v_float32;
	t_jit_3m_vecdata_float64 	v_float64;
} t_jit_3m_vecdata;

typedef struct _jit_3m
{
	t_object	ob;
	long		planecount;
	t_atom		min[JIT_MATRIX_MAX_PLANECOUNT];
	t_atom		mean[JIT_MATRIX_MAX_PLANECOUNT];
	t_atom		max[JIT_MATRIX_MAX_PLANECOUNT];
	t_jit_3m_vecdata vd;
	t_systhread_mutex mutex;
} t_jit_3m;

t_jit_err jit_3m_init(void);
t_jit_err jit_3m_matrix_calc(t_jit_3m *x, void *inputs, void *outputs);

void *_jit_3m_class;

t_jit_3m *jit_3m_new(void);
void jit_3m_free(t_jit_3m *x);
void jit_3m_precalc(t_jit_3m_vecdata *vecdata, t_jit_matrix_info *in1_minfo, char *bip1);
void jit_3m_postcalc(t_jit_3m *x, t_jit_3m_vecdata *vecdata, t_jit_matrix_info *in1_minfo);
void jit_3m_mean(t_jit_3m_vecdata *vecdata, t_jit_matrix_info *in1_minfo);
void jit_3m_calculate_ndim(t_jit_3m *x, long dimcount, long *dim, long planecount,
						   t_jit_matrix_info *in1_minfo, char *bip1);
void jit_3m_vector_char(long n, t_jit_op_info *in1, long *min, long *mean, long *max);
void jit_3m_vector_long(long n, t_jit_op_info *in1, long *min, double *mean, long *max);
void jit_3m_vector_float32(long n, t_jit_op_info *in1, float *min, float *mean, float *max);
void jit_3m_vector_float64(long n, t_jit_op_info *in1, double *min, double *mean, double *max);;

t_jit_err jit_3m_init(void)
{
	long attrflags=0;
	t_jit_object *attr,*mop;

	_jit_3m_class = jit_class_new("jit_3m",(method)jit_3m_new,(method)jit_3m_free,
								  sizeof(t_jit_3m),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,0);
	jit_class_addadornment(_jit_3m_class,mop);
	//add methods
	jit_class_addmethod(_jit_3m_class, (method)jit_3m_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);
	//add attributes
	attrflags = JIT_ATTR_SET_OPAQUE_USER | JIT_ATTR_GET_DEFER_LOW;

	CLASS_STICKY_CATEGORY(_jit_3m_class,0,"Value");

	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"min",_jit_sym_atom,JIT_MATRIX_MAX_PLANECOUNT,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_3m,planecount),calcoffset(t_jit_3m,min));
	jit_class_addattr(_jit_3m_class,attr);
	CLASS_ATTR_BASIC(_jit_3m_class,"min",0);
	CLASS_ATTR_LABEL(_jit_3m_class,"min",0,"Minimum");

	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"mean",_jit_sym_atom,JIT_MATRIX_MAX_PLANECOUNT,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_3m,planecount),calcoffset(t_jit_3m,mean));
	jit_class_addattr(_jit_3m_class,attr);
	CLASS_ATTR_BASIC(_jit_3m_class,"mean",0);
	CLASS_ATTR_LABEL(_jit_3m_class,"mean",0,"Mean");

	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"max",_jit_sym_atom,JIT_MATRIX_MAX_PLANECOUNT,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_3m,planecount),calcoffset(t_jit_3m,max));
	jit_class_addattr(_jit_3m_class,attr);
	CLASS_ATTR_BASIC(_jit_3m_class,"max",0);
	CLASS_ATTR_LABEL(_jit_3m_class,"max",0,"Maximum");

	CLASS_STICKY_CATEGORY_CLEAR(_jit_3m_class);

	jit_class_register(_jit_3m_class);

	return JIT_ERR_NONE;
}

t_jit_err jit_3m_matrix_calc(t_jit_3m *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock;
	t_jit_matrix_info in_minfo;
	char *in_bp;
	long i,dimcount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	void *in_matrix;

	in_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);

	if (x&&in_matrix) {

		in_savelock = (long) jit_object_method(in_matrix,_jit_sym_lock,1);
		jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
		jit_object_method(in_matrix,_jit_sym_getdata,&in_bp);

		if (!in_bp) { err=JIT_ERR_INVALID_INPUT; 	x->planecount = 0; goto out;}

		//get dimensions/planecount
		//3m does this a bit different than how it happens for most other objects
		dimcount    = in_minfo.dimcount;
		for (i=0; i<dimcount; i++) {
			dim[i] = in_minfo.dim[i];
		}

		//calculate
		jit_3m_precalc(&x->vd, &in_minfo, in_bp);
		jit_parallel_ndim_simplecalc1((method)jit_3m_calculate_ndim,
									  x, dimcount, dim, in_minfo.planecount, &in_minfo, in_bp,
									  0 /* flags1 */);
		jit_3m_mean(&x->vd, &in_minfo);
		jit_3m_postcalc(x, &x->vd, &in_minfo);

	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	return err;
}

void jit_3m_precalc(t_jit_3m_vecdata *vecdata, t_jit_matrix_info *in1_minfo, char *bip1)
{
	long i;

	if (in1_minfo->type==_jit_sym_char) {
		for (i=0; i<in1_minfo->planecount; i++) {
			vecdata->v_char.min[i]  = ((uchar *)bip1)[i];
			vecdata->v_char.max[i]  = ((uchar *)bip1)[i];
			vecdata->v_char.mean[i] = 0;
		}
	} else if (in1_minfo->type==_jit_sym_long) {
		for (i=0; i<in1_minfo->planecount; i++) {
			vecdata->v_long.min[i]  = ((t_int32 *)bip1)[i];
			vecdata->v_long.max[i]  = ((t_int32 *)bip1)[i];
			vecdata->v_long.mean[i] = 0;
		}
	} else if (in1_minfo->type==_jit_sym_float32) {
		for (i=0; i<in1_minfo->planecount; i++) {
			vecdata->v_float32.min[i]  = ((float *)bip1)[i];
			vecdata->v_float32.max[i]  = ((float *)bip1)[i];
			vecdata->v_float32.mean[i] = 0;
		}
	} else if (in1_minfo->type==_jit_sym_float64) {
		for (i=0; i<in1_minfo->planecount; i++) {
			vecdata->v_float64.min[i]  = ((double *)bip1)[i];
			vecdata->v_float64.max[i]  = ((double *)bip1)[i];
			vecdata->v_float64.mean[i] = 0;
		}
	}
}

void jit_3m_postcalc(t_jit_3m *x, t_jit_3m_vecdata *vecdata, t_jit_matrix_info *in1_minfo)
{
	long i;

	x->planecount = in1_minfo->planecount;

	if (in1_minfo->type==_jit_sym_char) {
		for (i=0; i<x->planecount; i++) {
			jit_atom_setlong(&(x->min[i]),vecdata->v_char.min[i]);
			jit_atom_setfloat(&(x->mean[i]),vecdata->v_long.mean[i]); //(hack) use v_long's float mean
			jit_atom_setlong(&(x->max[i]),vecdata->v_char.max[i]);
		}
	} else if (in1_minfo->type==_jit_sym_long) {
		for (i=0; i<x->planecount; i++) {
			jit_atom_setlong(&(x->min[i]),vecdata->v_long.min[i]);
			jit_atom_setfloat(&(x->mean[i]),vecdata->v_long.mean[i]);
			jit_atom_setlong(&(x->max[i]),vecdata->v_long.max[i]);
		}
	} else if (in1_minfo->type==_jit_sym_float32) {
		for (i=0; i<x->planecount; i++) {
			jit_atom_setfloat(&(x->min[i]),vecdata->v_float32.min[i]);
			jit_atom_setfloat(&(x->mean[i]),vecdata->v_float32.mean[i]);
			jit_atom_setfloat(&(x->max[i]),vecdata->v_float32.max[i]);
		}
	} else if (in1_minfo->type==_jit_sym_float64) {
		for (i=0; i<x->planecount; i++) {
			jit_atom_setfloat(&(x->min[i]),vecdata->v_float64.min[i]);
			jit_atom_setfloat(&(x->mean[i]),vecdata->v_float64.mean[i]);
			jit_atom_setfloat(&(x->max[i]),vecdata->v_float64.max[i]);
		}
	}
}

void jit_3m_mean(t_jit_3m_vecdata *vecdata, t_jit_matrix_info *in1_minfo)
{
	long count=1;
	long i;

	for (i=0; i<in1_minfo->dimcount; i++) {
		count *= in1_minfo->dim[i];
	}

	if (in1_minfo->type==_jit_sym_char) {
		for (i=0; i<in1_minfo->planecount; i++) {
			vecdata->v_long.mean[i] = ((double)(vecdata->v_char.mean[i]))/(double)count; //(hack) use v_long's float mean
		}
	} else if (in1_minfo->type==_jit_sym_long) {
		for (i=0; i<in1_minfo->planecount; i++) {
			vecdata->v_long.mean[i] = ((double)(vecdata->v_long.mean[i]))/(double)count;
		}
	} else if (in1_minfo->type==_jit_sym_float32) {
		for (i=0; i<in1_minfo->planecount; i++) {
			vecdata->v_float32.mean[i] = ((double)(vecdata->v_float32.mean[i]))/(double)count;
		}
	} else if (in1_minfo->type==_jit_sym_float64) {
		for (i=0; i<in1_minfo->planecount; i++) {
			vecdata->v_float64.mean[i] = ((double)(vecdata->v_float64.mean[i]))/(double)count;
		}
	}
}


//recursive function to handle higher dimension matrices, by processing 2D sections at a time
void jit_3m_calculate_ndim(t_jit_3m *x, long dimcount, long *dim, long planecount,
						   t_jit_matrix_info *in1_minfo, char *bip1)
{
	long i,j,n;
	char *ip1;
	t_jit_op_info in1_opinfo;
	t_jit_3m_vecdata vecdata;

	if (dimcount<1) return; //safety

	switch(dimcount) {
	case 1:
		dim[1] = 1;
	case 2:
		jit_3m_precalc(&vecdata,in1_minfo,bip1); //parallel moved thread local
		n = dim[0];
		in1_opinfo.stride = in1_minfo->dim[0]>1?planecount:0;
		if (in1_minfo->type==_jit_sym_char) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in1_opinfo.p = bip1 + i*in1_minfo->dimstride[1] + j;
					jit_3m_vector_char(n,&in1_opinfo,&(vecdata.v_char.min[j]),
									   &(vecdata.v_char.mean[j]),&(vecdata.v_char.max[j]));
				}
			}
			//parallel: protect access to global vecdata write
			systhread_mutex_lock(x->mutex);
			for (j=0; j<planecount; j++) {
				if (vecdata.v_char.min[j]<x->vd.v_char.min[j])
					x->vd.v_char.min[j] = vecdata.v_char.min[j];
				if (vecdata.v_char.max[j]>x->vd.v_char.max[j])
					x->vd.v_char.max[j] = vecdata.v_char.max[j];
				x->vd.v_char.mean[j] += vecdata.v_char.mean[j];
			}
			systhread_mutex_unlock(x->mutex);
		} else if (in1_minfo->type==_jit_sym_long) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in1_opinfo.p = bip1 + i*in1_minfo->dimstride[1] + j*4;
					jit_3m_vector_long(n,&in1_opinfo,&(vecdata.v_long.min[j]),
									   &(vecdata.v_long.mean[j]),&(vecdata.v_long.max[j]));
				}
			}
			//parallel: protect access to global vecdata write
			systhread_mutex_lock(x->mutex);
			for (j=0; j<planecount; j++) {
				if (vecdata.v_long.min[j]<x->vd.v_long.min[j])
					x->vd.v_long.min[j] = vecdata.v_long.min[j];
				if (vecdata.v_long.max[j]>x->vd.v_long.max[j])
					x->vd.v_long.max[j] = vecdata.v_long.max[j];
				x->vd.v_long.mean[j] += vecdata.v_long.mean[j];
			}
			systhread_mutex_unlock(x->mutex);
		} else if (in1_minfo->type==_jit_sym_float32) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in1_opinfo.p = bip1 + i*in1_minfo->dimstride[1] + j*4;
					jit_3m_vector_float32(n,&in1_opinfo,&(vecdata.v_float32.min[j]),
										  &(vecdata.v_float32.mean[j]),&(vecdata.v_float32.max[j]));
				}
			}
			//parallel: protect access to global vecdata write
			systhread_mutex_lock(x->mutex);
			for (j=0; j<planecount; j++) {
				if (vecdata.v_float32.min[j]<x->vd.v_float32.min[j])
					x->vd.v_float32.min[j] = vecdata.v_float32.min[j];
				if (vecdata.v_float32.max[j]>x->vd.v_float32.max[j])
					x->vd.v_float32.max[j] = vecdata.v_float32.max[j];
				x->vd.v_float32.mean[j] += vecdata.v_float32.mean[j];
			}
			systhread_mutex_unlock(x->mutex);
		} else if (in1_minfo->type==_jit_sym_float64) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in1_opinfo.p = bip1 + i*in1_minfo->dimstride[1] + j*8;
					jit_3m_vector_float64(n,&in1_opinfo,&(vecdata.v_float64.min[j]),
										  &(vecdata.v_float64.mean[j]),&(vecdata.v_float64.max[j]));
				}
			}
			//parallel: protect access to global vecdata write
			systhread_mutex_lock(x->mutex);
			for (j=0; j<planecount; j++) {
				if (vecdata.v_float64.min[j]<x->vd.v_float64.min[j])
					x->vd.v_float64.min[j] = vecdata.v_float64.min[j];
				if (vecdata.v_float64.max[j]>x->vd.v_float64.max[j])
					x->vd.v_float64.max[j] = vecdata.v_float64.max[j];
				x->vd.v_float64.mean[j] += vecdata.v_float64.mean[j];
			}
			systhread_mutex_unlock(x->mutex);
		}
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			ip1 = bip1 + i*in1_minfo->dimstride[dimcount-1];
			jit_3m_calculate_ndim(x,dimcount-1,dim,planecount,in1_minfo,ip1);
		}
	}
}

//outmatrix is guaranteed to be no smaller than 256 elements so no need to test ip1 for 0-maxsize
void jit_3m_vector_char(long n, t_jit_op_info *in1, long *min, long *mean, long *max)
{
	uchar *ip1;
	long tmp;
	long is1;

	ip1 = ((uchar *)in1->p);
	is1 = in1->stride;

	++n;
	while (--n) {
		tmp = *ip1;
		if (tmp<(*min)) *min = tmp;
		if (tmp>(*max)) *max = tmp;
		*mean += tmp;
		ip1 += is1;
	}
}

void jit_3m_vector_long(long n, t_jit_op_info *in1, long *min, double *mean, long *max)
{
	t_int32 *ip1,tmp;
	long is1;

	ip1 = ((t_int32 *)in1->p);
	is1 = in1->stride;

	++n;
	while (--n) {
		tmp = *ip1;
		if (tmp<(*min)) *min = tmp;
		if (tmp>(*max)) *max = tmp;
		*mean += tmp;
		ip1 += is1;
	}
}

void jit_3m_vector_float32(long n, t_jit_op_info *in1, float *min, float *mean, float *max)
{
	float *ip1,tmp;
	long is1;

	ip1 = ((float *)in1->p);
	is1 = in1->stride;

	++n;
	while (--n) {
		tmp = *ip1;
		if (tmp<(*min)) *min = tmp;
		if (tmp>(*max)) *max = tmp;
		*mean += tmp;
		ip1 += is1;
	}
}

void jit_3m_vector_float64(long n, t_jit_op_info *in1, double *min, double *mean, double *max)
{
	double *ip1,tmp;
	long is1;

	ip1 = ((double *)in1->p);
	is1 = in1->stride;

	++n;
	while (--n) {
		tmp = *ip1;
		if (tmp<(*min)) *min = tmp;
		if (tmp>(*max)) *max = tmp;
		*mean += tmp;
		ip1 += is1;
	}
}

t_jit_3m *jit_3m_new(void)
{
	t_jit_3m *x;

	if (x=(t_jit_3m *)jit_object_alloc(_jit_3m_class)) {
		x->planecount = 0;
		systhread_mutex_new(&x->mutex,0);
	} else {
		x = NULL;
	}
	return x;
}

void jit_3m_free(t_jit_3m *x)
{
	systhread_mutex_free(x->mutex);
}
