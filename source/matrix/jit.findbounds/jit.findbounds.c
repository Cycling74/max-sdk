/*
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"

typedef struct _jit_findbounds_vecdata_char
{
	long				boundmin[JIT_MATRIX_MAX_DIMCOUNT];
	long 				boundmax[JIT_MATRIX_MAX_DIMCOUNT];
	long				min[JIT_MATRIX_MAX_PLANECOUNT];
	long				max[JIT_MATRIX_MAX_PLANECOUNT];
} t_jit_findbounds_vecdata_char;

typedef struct _jit_findbounds_vecdata_long
{
	long				boundmin[JIT_MATRIX_MAX_DIMCOUNT];
	long 				boundmax[JIT_MATRIX_MAX_DIMCOUNT];
	long				min[JIT_MATRIX_MAX_PLANECOUNT];
	long				max[JIT_MATRIX_MAX_PLANECOUNT];
} t_jit_findbounds_vecdata_long;

typedef struct _jit_findbounds_vecdata_float32
{
	long				boundmin[JIT_MATRIX_MAX_DIMCOUNT];
	long 				boundmax[JIT_MATRIX_MAX_DIMCOUNT];
	float				min[JIT_MATRIX_MAX_PLANECOUNT];
	float				max[JIT_MATRIX_MAX_PLANECOUNT];
} t_jit_findbounds_vecdata_float32;

typedef struct _jit_findbounds_vecdata_float64
{
	long				boundmin[JIT_MATRIX_MAX_DIMCOUNT];
	long 				boundmax[JIT_MATRIX_MAX_DIMCOUNT];
	double				min[JIT_MATRIX_MAX_PLANECOUNT];
	double				max[JIT_MATRIX_MAX_PLANECOUNT];
} t_jit_findbounds_vecdata_float64;

typedef union _jit_findbounds_vecdata
{
	t_jit_findbounds_vecdata_char 		v_char;
	t_jit_findbounds_vecdata_long 		v_long;
	t_jit_findbounds_vecdata_float32 	v_float32;
	t_jit_findbounds_vecdata_float64 	v_float64;
} t_jit_findbounds_vecdata;

typedef struct _jit_findbounds
{
	t_object	ob;
	long		mincount;
	double		min[JIT_MATRIX_MAX_PLANECOUNT];
	long		maxcount;
	double		max[JIT_MATRIX_MAX_PLANECOUNT];
	long		boundmincount;
	long		boundmin[JIT_MATRIX_MAX_DIMCOUNT];
	long		boundmaxcount;
	long		boundmax[JIT_MATRIX_MAX_DIMCOUNT];
} t_jit_findbounds;

t_jit_err jit_findbounds_init(void);
t_jit_err jit_findbounds_matrix_calc(t_jit_findbounds *x, void *inputs, void *outputs);

void *_jit_findbounds_class;

t_jit_findbounds *jit_findbounds_new(void);
void jit_findbounds_free(t_jit_findbounds *x);
void jit_findbounds_precalc(t_jit_findbounds *x, t_jit_findbounds_vecdata *vecdata, t_jit_matrix_info *in_minfo);
void jit_findbounds_postcalc(t_jit_findbounds *x, t_jit_findbounds_vecdata *vecdata, t_jit_matrix_info *in_minfo);
long jit_findbounds_calculate_ndim(t_jit_findbounds *x, long dimcount, long *dim, t_jit_findbounds_vecdata *vecdata,
								   t_jit_matrix_info *in_minfo, char *bip);
long jit_findbounds_calc2d_char_plane0(t_jit_findbounds *x, long dimcount, long *dim, t_jit_findbounds_vecdata *vecdata,
									   t_jit_matrix_info *in_minfo, char *bip);
long jit_findbounds_calc2d_char_plane4(t_jit_findbounds *x, long dimcount, long *dim, t_jit_findbounds_vecdata *vecdata,
									   t_jit_matrix_info *in_minfo, char *bip);
long jit_findbounds_calc2d_char(t_jit_findbounds *x, long dimcount, long *dim, t_jit_findbounds_vecdata *vecdata,
								t_jit_matrix_info *in_minfo, char *bip);
long jit_findbounds_calc2d_long(t_jit_findbounds *x, long dimcount, long *dim, t_jit_findbounds_vecdata *vecdata,
								t_jit_matrix_info *in_minfo, char *bip);
long jit_findbounds_calc2d_float32(t_jit_findbounds *x, long dimcount, long *dim, t_jit_findbounds_vecdata *vecdata,
								   t_jit_matrix_info *in_minfo, char *bip);
long jit_findbounds_calc2d_float64(t_jit_findbounds *x, long dimcount, long *dim, t_jit_findbounds_vecdata *vecdata,
								   t_jit_matrix_info *in_minfo, char *bip);

t_jit_err jit_findbounds_init(void)
{
	long attrflags=0;
	t_jit_object *attr,*mop;

	_jit_findbounds_class = jit_class_new("jit_findbounds",(method)jit_findbounds_new,(method)jit_findbounds_free,
										  sizeof(t_jit_findbounds),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,0);
	jit_class_addadornment(_jit_findbounds_class,mop);
	//add methods
	jit_class_addmethod(_jit_findbounds_class, (method)jit_findbounds_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);
	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;

	CLASS_STICKY_CATEGORY(_jit_findbounds_class,0,"Behavior");
	CLASS_STICKY_ATTR(_jit_findbounds_class,"basic",0,"1");

	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"min",_jit_sym_float64,JIT_MATRIX_MAX_PLANECOUNT,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_findbounds, mincount),calcoffset(t_jit_findbounds,min));
	jit_class_addattr(_jit_findbounds_class,attr);
	CLASS_ATTR_LABEL(_jit_findbounds_class,"min",0,"Minimum");

	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"max",_jit_sym_float64,JIT_MATRIX_MAX_PLANECOUNT,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_findbounds, maxcount),calcoffset(t_jit_findbounds,max));
	jit_class_addattr(_jit_findbounds_class,attr);
	CLASS_ATTR_LABEL(_jit_findbounds_class,"max",0,"Maximum");

	CLASS_STICKY_ATTR_CLEAR(_jit_findbounds_class, "basic");

	CLASS_STICKY_CATEGORY(_jit_findbounds_class,0,"Value");

	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_OPAQUE_USER;
	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"boundmin",_jit_sym_long,JIT_MATRIX_MAX_DIMCOUNT,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_findbounds, boundmincount),calcoffset(t_jit_findbounds,boundmin));
	jit_class_addattr(_jit_findbounds_class,attr);
	CLASS_ATTR_LABEL(_jit_findbounds_class,"boundmin",0,"Bounding Box Minimum");

	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"boundmax",_jit_sym_long,JIT_MATRIX_MAX_DIMCOUNT,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_findbounds, boundmaxcount),calcoffset(t_jit_findbounds,boundmax));
	jit_class_addattr(_jit_findbounds_class,attr);
	CLASS_ATTR_LABEL(_jit_findbounds_class,"boundmax",0,"Bounding Box Maximum");

	CLASS_STICKY_CATEGORY_CLEAR(_jit_findbounds_class);

	jit_class_register(_jit_findbounds_class);

	return JIT_ERR_NONE;
}

t_jit_err jit_findbounds_matrix_calc(t_jit_findbounds *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock;
	t_jit_matrix_info in_minfo;
	char *in_bp;
	long i,dim[JIT_MATRIX_MAX_DIMCOUNT];
	t_jit_findbounds_vecdata vd;
	void *in_matrix;

	in_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);

	if (x&&in_matrix) {

		in_savelock = (long) jit_object_method(in_matrix,_jit_sym_lock,1);
		jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
		jit_object_method(in_matrix,_jit_sym_getdata,&in_bp);

		if (!in_bp) { err=JIT_ERR_INVALID_INPUT; goto out;}

		//get dimensions
		//findbounds does this a bit different than how it happens for most other objects
		for (i=0; i<in_minfo.dimcount; i++) {
			dim[i] = in_minfo.dim[i];
		}

		//calculate
		jit_findbounds_precalc(x, &vd, &in_minfo);
		jit_findbounds_calculate_ndim(x, in_minfo.dimcount, dim, &vd, &in_minfo, in_bp);
		jit_findbounds_postcalc(x, &vd, &in_minfo);
	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	return err;
}

void jit_findbounds_precalc(t_jit_findbounds *x, t_jit_findbounds_vecdata *vecdata, t_jit_matrix_info *in_minfo)
{
	long i;

	for (i=0; i<in_minfo->dimcount; i++) { //works for all types
		vecdata->v_char.boundmin[i] = -1;
		vecdata->v_char.boundmax[i] = -1;
	}
	if (in_minfo->type==_jit_sym_char) {
		for (i=0; i<in_minfo->planecount; i++) {
			vecdata->v_char.min[i] = (i>x->mincount) ? 0 : CLAMP(x->min[i]*255.,0,255);
			vecdata->v_char.max[i] = (i>x->maxcount) ? 0 : CLAMP(x->max[i]*255.,0,255);
		}
	} else if (in_minfo->type==_jit_sym_long) {
		for (i=0; i<in_minfo->planecount; i++) {
			vecdata->v_long.min[i] = (i>x->mincount) ? 0 : x->min[i];
			vecdata->v_long.max[i] = (i>x->maxcount) ? 0 : x->max[i];
		}
	} else if (in_minfo->type==_jit_sym_float32) {
		for (i=0; i<in_minfo->planecount; i++) {
			vecdata->v_float32.min[i] = (i>x->mincount) ? 0 : x->min[i];
			vecdata->v_float32.max[i] = (i>x->maxcount) ? 0 : x->max[i];
		}
	} else if (in_minfo->type==_jit_sym_float64) {
		for (i=0; i<in_minfo->planecount; i++) {
			vecdata->v_float64.min[i] = (i>x->mincount) ? 0 : x->min[i];
			vecdata->v_float64.max[i] = (i>x->maxcount) ? 0 : x->max[i];
		}
	}
}

void jit_findbounds_postcalc(t_jit_findbounds *x, t_jit_findbounds_vecdata *vecdata, t_jit_matrix_info *in_minfo)
{
	long i;

	x->boundmincount = x->boundmaxcount = in_minfo->dimcount;
	for (i=0; i<in_minfo->dimcount; i++) { //works for all types
		x->boundmin[i] = vecdata->v_char.boundmin[i];
		x->boundmax[i] = vecdata->v_char.boundmax[i];
	}
}


//recursive function to handle higher dimension matrices, by processing 2D sections at a time
long jit_findbounds_calculate_ndim(t_jit_findbounds *x, long dimcount, long *dim, t_jit_findbounds_vecdata *vecdata,
								   t_jit_matrix_info *in_minfo, char *bip)
{
	long i,n;
	long boundmin,boundmax,inrange0=FALSE,inrange=FALSE;
	uchar *ip;

	if (dimcount<1) return FALSE; //safety

	switch(dimcount) {
	case 1:
		dim[1] = 1;
	case 2:
		if (in_minfo->type==_jit_sym_char) {
			switch(in_minfo->planecount) {
			case 0:
				inrange = jit_findbounds_calc2d_char_plane0(x,dimcount,dim,vecdata,in_minfo,bip);
				break;
			case 4:
				inrange = jit_findbounds_calc2d_char_plane4(x,dimcount,dim,vecdata,in_minfo,bip);
				break;
			default:
				inrange = jit_findbounds_calc2d_char(x,dimcount,dim,vecdata,in_minfo,bip);
				break;
			}
		} else if (in_minfo->type==_jit_sym_long) {
			inrange = jit_findbounds_calc2d_long(x,dimcount,dim,vecdata,in_minfo,bip);
		} else if (in_minfo->type==_jit_sym_float32) {
			inrange = jit_findbounds_calc2d_float32(x,dimcount,dim,vecdata,in_minfo,bip);
		} else if (in_minfo->type==_jit_sym_float64) {
			inrange = jit_findbounds_calc2d_float64(x,dimcount,dim,vecdata,in_minfo,bip);
		}
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			ip = bip + i*in_minfo->dimstride[dimcount-1];
			inrange0 = jit_findbounds_calculate_ndim(x,dimcount-1,dim,vecdata,in_minfo,ip);
			//exploiting the union
			if (inrange0) {
				inrange = TRUE;
				if ((vecdata->v_char.boundmin[dimcount-1]==-1)||
						(i<vecdata->v_char.boundmin[dimcount-1]))
					vecdata->v_char.boundmin[dimcount-1] = i;
				else if (i>vecdata->v_char.boundmax[dimcount-1])
					vecdata->v_char.boundmax[dimcount-1] = i;
			}
		}

	}
	return inrange;
}

long jit_findbounds_calc2d_char_plane0(t_jit_findbounds *x, long dimcount, long *dim, t_jit_findbounds_vecdata *vecdata,
									   t_jit_matrix_info *in_minfo, char *bip)
{
	long i,j,n,cmin,cmax;
	long min0,min1,max0,max1,inrange0,inrange1,inrange2;
	uchar *ip;

	inrange2 = FALSE;

	n = dim[0];
	cmin = vecdata->v_char.min[0];
	cmax = vecdata->v_char.max[0];
	min0 = min1 = 0x7FFFFFFF;
	max0 = max1 = -1;
	for (i=0; i<dim[1]; i++) {
		ip = bip + i*in_minfo->dimstride[1];
		inrange1 = FALSE;
		for (j=0; j<n; j++) {
			inrange0 = TRUE;
			if (*ip<cmin) inrange0 = FALSE;
			else if (*ip>cmax) inrange0 = FALSE;
			ip++;
			if (inrange0) {
				inrange1 = TRUE;
				if (j<min0) min0 = j;
				if (j>max0) max0 = j;
			}
		}
		if (inrange1) {
			inrange2 = TRUE;
			if (i<min1) min1 = i;
			if (i>max1) max1 = i;
		}
	}
	if (min0<0x7FFFFFFF) vecdata->v_char.boundmin[0] = min0;
	if (min1<0x7FFFFFFF) vecdata->v_char.boundmin[1] = min1;
	if (max0>-1) vecdata->v_char.boundmax[0] = max0;
	else vecdata->v_char.boundmax[0] = vecdata->v_char.boundmin[0];
	if (max1>-1) vecdata->v_char.boundmax[1] = max1;
	else vecdata->v_char.boundmax[1] = vecdata->v_char.boundmin[1];

	return inrange2;
}

long jit_findbounds_calc2d_char_plane4(t_jit_findbounds *x, long dimcount, long *dim, t_jit_findbounds_vecdata *vecdata,
									   t_jit_matrix_info *in_minfo, char *bip)
{
	long i,j,n,cmin0,cmax0,cmin1,cmax1,cmin2,cmax2,cmin3,cmax3;
	long min0,min1,max0,max1,inrange0,inrange1,inrange2;
	uchar *ip;

	inrange2 = FALSE;

	n = dim[0];
	cmin0 = vecdata->v_char.min[0];
	cmax0 = vecdata->v_char.max[0];
	cmin1 = vecdata->v_char.min[1];
	cmax1 = vecdata->v_char.max[1];
	cmin2 = vecdata->v_char.min[2];
	cmax2 = vecdata->v_char.max[2];
	cmin3 = vecdata->v_char.min[3];
	cmax3 = vecdata->v_char.max[3];
	min0 = min1 = 0x7FFFFFFF;
	max0 = max1 = -1;
	for (i=0; i<dim[1]; i++) {
		ip = bip + i*in_minfo->dimstride[1];
		inrange1 = FALSE;
		for (j=0; j<n; j++) {
			inrange0 = TRUE;
			if (*ip<cmin0) inrange0 = FALSE;
			else if (*ip>cmax0) inrange0 = FALSE;
			ip++;
			if (*ip<cmin1) inrange0 = FALSE;
			else if (*ip>cmax1) inrange0 = FALSE;
			ip++;
			if (*ip<cmin2) inrange0 = FALSE;
			else if (*ip>cmax2) inrange0 = FALSE;
			ip++;
			if (*ip<cmin3) inrange0 = FALSE;
			else if (*ip>cmax3) inrange0 = FALSE;
			ip++;
			if (inrange0) {
				inrange1 = TRUE;
				if (j<min0) min0 = j;
				if (j>max0) max0 = j;
			}
		}
		if (inrange1) {
			inrange2 = TRUE;
			if (i<min1) min1 = i;
			if (i>max1) max1 = i;
		}
	}
	if (min0<0x7FFFFFFF) vecdata->v_char.boundmin[0] = min0;
	if (min1<0x7FFFFFFF) vecdata->v_char.boundmin[1] = min1;
	if (max0>-1) vecdata->v_char.boundmax[0] = max0;
	else vecdata->v_char.boundmax[0] = vecdata->v_char.boundmin[0];
	if (max1>-1) vecdata->v_char.boundmax[1] = max1;
	else vecdata->v_char.boundmax[1] = vecdata->v_char.boundmin[1];

	return inrange2;
}


long jit_findbounds_calc2d_char(t_jit_findbounds *x, long dimcount, long *dim, t_jit_findbounds_vecdata *vecdata,
								t_jit_matrix_info *in_minfo, char *bip)
{
	long i,j,k,planecount,n;
	long min0,min1,max0,max1,inrange0,inrange1,inrange2;
	uchar *ip;
	long *cmin,*cmax;


	inrange2 = FALSE;

	n = dim[0];
	planecount = in_minfo->planecount;
	min0 = min1 = 0x7FFFFFFF;
	max0 = max1 = -1;
	cmin = vecdata->v_char.min;
	cmax = vecdata->v_char.max;
	for (i=0; i<dim[1]; i++) {
		ip = bip + i*in_minfo->dimstride[1];
		inrange1 = FALSE;
		for (j=0; j<n; j++) {
			inrange0 = TRUE;
			for (k=0; k<planecount; k++) {
				if (*ip<cmin[k]) inrange0 = FALSE;
				else if (*ip>cmax[k]) inrange0 = FALSE;
				ip++;
			}
			if (inrange0) {
				inrange1 = TRUE;
				if (j<min0) min0 = j;
				if (j>max0) max0 = j;
			}
		}
		if (inrange1) {
			inrange2 = TRUE;
			if (i<min1) min1 = i;
			if (i>max1) max1 = i;
		}
	}
	if (min0<0x7FFFFFFF) vecdata->v_char.boundmin[0] = min0;
	if (min1<0x7FFFFFFF) vecdata->v_char.boundmin[1] = min1;
	if (max0>-1) vecdata->v_char.boundmax[0] = max0;
	else vecdata->v_char.boundmax[0] = vecdata->v_char.boundmin[0];
	if (max1>-1) vecdata->v_char.boundmax[1] = max1;
	else vecdata->v_char.boundmax[1] = vecdata->v_char.boundmin[1];

	return inrange2;
}


long jit_findbounds_calc2d_long(t_jit_findbounds *x, long dimcount, long *dim, t_jit_findbounds_vecdata *vecdata,
								t_jit_matrix_info *in_minfo, char *bip)
{
	long i,j,k,planecount,n;
	long min0,min1,max0,max1,inrange0,inrange1,inrange2;
	t_int32 *ip;
	long *cmin,*cmax;


	inrange2 = FALSE;

	n = dim[0];
	planecount = in_minfo->planecount;
	min0 = min1 = 0x7FFFFFFF;
	max0 = max1 = -1;
	cmin = vecdata->v_long.min;
	cmax = vecdata->v_long.max;
	for (i=0; i<dim[1]; i++) {
		ip = (t_int32 *)(bip + i*in_minfo->dimstride[1]);
		inrange1 = FALSE;
		for (j=0; j<n; j++) {
			inrange0 = TRUE;
			for (k=0; k<planecount; k++) {
				if (*ip<cmin[k]) inrange0 = FALSE;
				else if (*ip>cmax[k]) inrange0 = FALSE;
				ip++;
			}
			if (inrange0) {
				inrange1 = TRUE;
				if (j<min0) min0 = j;
				if (j>max0) max0 = j;
			}
		}
		if (inrange1) {
			inrange2 = TRUE;
			if (i<min1) min1 = i;
			if (i>max1) max1 = i;
		}
	}
	if (min0<0x7FFFFFFF) vecdata->v_long.boundmin[0] = min0;
	if (min1<0x7FFFFFFF) vecdata->v_long.boundmin[1] = min1;
	if (max0>-1) vecdata->v_long.boundmax[0] = max0;
	else vecdata->v_long.boundmax[0] = vecdata->v_long.boundmin[0];
	if (max1>-1) vecdata->v_long.boundmax[1] = max1;
	else vecdata->v_long.boundmax[1] = vecdata->v_long.boundmin[1];

	return inrange2;
}

long jit_findbounds_calc2d_float32(t_jit_findbounds *x, long dimcount, long *dim, t_jit_findbounds_vecdata *vecdata,
								   t_jit_matrix_info *in_minfo, char *bip)
{
	long i,j,k,planecount,n;
	long min0,min1,max0,max1,inrange0,inrange1,inrange2;
	float *ip;
	float *cmin,*cmax;

	inrange2 = FALSE;

	n = dim[0];
	planecount = in_minfo->planecount;
	min0 = min1 = 0x7FFFFFFF;
	max0 = max1 = -1;
	cmin = vecdata->v_float32.min;
	cmax = vecdata->v_float32.max;
	for (i=0; i<dim[1]; i++) {
		ip = (float *) (bip + i*in_minfo->dimstride[1]);
		inrange1 = FALSE;
		for (j=0; j<n; j++) {
			inrange0 = TRUE;
			for (k=0; k<planecount; k++) {
				if (*ip<cmin[k]) inrange0 = FALSE;
				else if (*ip>cmax[k]) inrange0 = FALSE;
				ip++;
			}
			if (inrange0) {
				inrange1 = TRUE;
				if (j<min0) min0 = j;
				if (j>max0) max0 = j;
			}
		}
		if (inrange1) {
			inrange2 = TRUE;
			if (i<min1) min1 = i;
			if (i>max1) max1 = i;
		}
	}
	if (min0<0x7FFFFFFF) vecdata->v_float32.boundmin[0] = min0;
	if (min1<0x7FFFFFFF) vecdata->v_float32.boundmin[1] = min1;
	if (max0>-1) vecdata->v_float32.boundmax[0] = max0;
	else vecdata->v_float32.boundmax[0] = vecdata->v_float32.boundmin[0];
	if (max1>-1) vecdata->v_float32.boundmax[1] = max1;
	else vecdata->v_float32.boundmax[1] = vecdata->v_float32.boundmin[1];

	return inrange2;
}

long jit_findbounds_calc2d_float64(t_jit_findbounds *x, long dimcount, long *dim, t_jit_findbounds_vecdata *vecdata,
								   t_jit_matrix_info *in_minfo, char *bip)
{
	long i,j,k,planecount,n;
	long min0,min1,max0,max1,inrange0,inrange1,inrange2;
	double *ip;
	double *cmin,*cmax;

	inrange2 = FALSE;

	n = dim[0];
	planecount = in_minfo->planecount;
	min0 = min1 = 0x7FFFFFFF;
	max0 = max1 = -1;
	cmin = vecdata->v_float64.min;
	cmax = vecdata->v_float64.max;
	for (i=0; i<dim[1]; i++) {
		ip = (double *) (bip + i*in_minfo->dimstride[1]);
		inrange1 = FALSE;
		for (j=0; j<n; j++) {
			inrange0 = TRUE;
			for (k=0; k<planecount; k++) {
				if (*ip<cmin[k]) inrange0 = FALSE;
				else if (*ip>cmax[k]) inrange0 = FALSE;
				ip++;
			}
			if (inrange0) {
				inrange1 = TRUE;
				if (j<min0) min0 = j;
				if (j>max0) max0 = j;
			}
		}
		if (inrange1) {
			inrange2 = TRUE;
			if (i<min1) min1 = i;
			if (i>max1) max1 = i;
		}
	}
	if (min0<0x7FFFFFFF) vecdata->v_float64.boundmin[0] = min0;
	if (min1<0x7FFFFFFF) vecdata->v_float64.boundmin[1] = min1;
	if (max0>-1) vecdata->v_float64.boundmax[0] = max0;
	else vecdata->v_float64.boundmax[0] = vecdata->v_float64.boundmin[0];
	if (max1>-1) vecdata->v_float64.boundmax[1] = max1;
	else vecdata->v_float64.boundmax[1] = vecdata->v_float64.boundmin[1];

	return inrange2;
}

t_jit_findbounds *jit_findbounds_new(void)
{
	t_jit_findbounds *x;
	long i;

	if (x=(t_jit_findbounds *)jit_object_alloc(_jit_findbounds_class)) {
		x->mincount = 4;
		x->maxcount = 4;
		for (i=0; i<JIT_MATRIX_MAX_PLANECOUNT; i++)
			x->min[i] = x->max[i] = 0;
		x->boundmincount = 0;
		x->boundmaxcount = 0;
		for (i=0; i<JIT_MATRIX_MAX_DIMCOUNT; i++)
			x->boundmin[i] = x->boundmax[i] = -1;
	} else {
		x = NULL;
	}
	return x;
}

void jit_findbounds_free(t_jit_findbounds *x)
{
	//nada
}
