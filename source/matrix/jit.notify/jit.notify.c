/*
	Copyright 2001-2002 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"

typedef struct _jit_notify_vecdata
{
	double 				min;
	double 				max;
	long				lmin;
	long				lmax;
	long				cmin;
	long				cmax;
} t_jit_notify_vecdata;

typedef struct _jit_notify
{
	t_object				ob;
	double					min;
	double					max;
} t_jit_notify;

void *_jit_notify_class;

t_jit_err jit_notify_init(void);
t_jit_notify *jit_notify_new(void);
void jit_notify_free(t_jit_notify *x);
t_jit_err jit_notify_getvecdata(t_jit_notify *x, t_jit_notify_vecdata *vd);
t_jit_err jit_notify_matrix_calc(t_jit_notify *x, void *inputs, void *outputs);

void jit_notify_calculate_ndim(long dim, long *dimsize, long planecount, t_jit_notify_vecdata *vecdata, t_jit_matrix_info *in_minfo, char *bip,
							   t_jit_matrix_info *out_minfo, char *bop);
void jit_notify_vector_char		(long n, t_jit_notify_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out);
void jit_notify_vector_long		(long n, t_jit_notify_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out);
void jit_notify_vector_float32	(long n, t_jit_notify_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out);
void jit_notify_vector_float64	(long n, t_jit_notify_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out);

t_jit_err jit_notify_init(void)
{
	long attrflags=0;
	t_jit_object *attr,*mop;

	_jit_notify_class = jit_class_new("jit_notify",(method)jit_notify_new,(method)jit_notify_free,
									  sizeof(t_jit_notify),A_CANT,0L); //A_CANT = untyped

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,1); //#inputs,#outputs
	jit_class_addadornment(_jit_notify_class,mop);
	//add methods
	jit_class_addmethod(_jit_notify_class, (method)jit_notify_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);
	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"min",_jit_sym_float64,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_notify,min));
	jit_class_addattr(_jit_notify_class,attr);
	attr = jit_object_new(_jit_sym_jit_attr_offset,"max",_jit_sym_float64,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_notify,max));
	jit_class_addattr(_jit_notify_class,attr);

	//NOTIFY EXAMPLE: WE NEED A "REGISTER" METHOD SO THAT CLIENTS CAN ATTACH TO US
	jit_class_addmethod(_jit_notify_class, (method)jit_object_register, 	"register",			A_CANT, 0L); // can register

	jit_class_register(_jit_notify_class);

	return JIT_ERR_NONE;
}

t_jit_err jit_notify_getvecdata(t_jit_notify *x, t_jit_notify_vecdata *vd)
{
	if (x&&vd) {
		vd->min 		= x->min;
		vd->max 		= x->max;
		vd->lmin 		= x->min;
		vd->lmax 		= x->max;
		vd->cmin 		= x->min*255.;
		vd->cmax 		= x->max*255.;
		CLIP_ASSIGN(vd->cmin,0,255);
		CLIP_ASSIGN(vd->cmax,0,255);
		return JIT_ERR_NONE;
	} else {
		return JIT_ERR_INVALID_PTR;
	}
}

t_jit_err jit_notify_matrix_calc(t_jit_notify *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock,out_savelock;
	t_jit_matrix_info in_minfo,out_minfo;
	char *in_bp,*out_bp;
	long i,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	t_jit_notify_vecdata	vecdata;
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

		jit_notify_getvecdata(x,&vecdata);
		jit_notify_calculate_ndim(dimcount, dim, planecount, &vecdata, &in_minfo, in_bp, &out_minfo, out_bp);
		//NOTIFY EXAMPLE: HERE WE'RE SENDING SOME BOGUS INFO TO ALL OUR CLIENTS
		{
			t_atom foo[3];

			jit_atom_setlong(&foo[0],1);
			jit_atom_setlong(&foo[1],2);
			jit_atom_setlong(&foo[2],3);
			jit_object_notify(x,gensym("splat"), foo); //the last pointer argument could be anything.
		}
	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(out_matrix,gensym("lock"),out_savelock);
	jit_object_method(in_matrix,gensym("lock"),in_savelock);
	return err;
}


void jit_notify_calculate_ndim(long dimcount, long *dim, long planecount, t_jit_notify_vecdata *vecdata, t_jit_matrix_info *in_minfo, char *bip,
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
					jit_notify_vector_char(n,vecdata,&in_opinfo,&out_opinfo);
				}
			}
		} else if (in_minfo->type==_jit_sym_long) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in_opinfo.p  = bip + i*in_minfo->dimstride[1] + (j%in_minfo->planecount)*4;
					out_opinfo.p = bop + i*out_minfo->dimstride[1] + (j%out_minfo->planecount)*4;
					jit_notify_vector_long(n,vecdata,&in_opinfo,&out_opinfo);
				}
			}
		} else if (in_minfo->type==_jit_sym_float32) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in_opinfo.p  = bip + i*in_minfo->dimstride[1] + (j%in_minfo->planecount)*4;
					out_opinfo.p = bop + i*out_minfo->dimstride[1] + (j%out_minfo->planecount)*4;
					jit_notify_vector_float32(n,vecdata,&in_opinfo,&out_opinfo);
				}
			}
		} else if (in_minfo->type==_jit_sym_float64) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in_opinfo.p  = bip + i*in_minfo->dimstride[1] + (j%in_minfo->planecount)*8;
					out_opinfo.p = bop + i*out_minfo->dimstride[1] + (j%out_minfo->planecount)*8;
					jit_notify_vector_float64(n,vecdata,&in_opinfo,&out_opinfo);
				}
			}
		}
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			ip = bip + i*in_minfo->dimstride[dimcount-1];
			op = bop + i*out_minfo->dimstride[dimcount-1];
			jit_notify_calculate_ndim(dimcount-1,dim,planecount,vecdata,in_minfo,ip,out_minfo,op);
		}
	}
}

void jit_notify_vector_char(long n, t_jit_notify_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	long min=vecdata->cmin;
	long max=vecdata->cmax;
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
			tmp = *++ip;
			*++op = tmp>max?max:tmp<min?min:tmp;
		}
	} else {
		while (n--) {
			tmp = *ip;
			*op = tmp>max?max:tmp<min?min:tmp;
			ip+=is; op+=os;
		}
	}
}

void jit_notify_vector_long(long n, t_jit_notify_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	long min=vecdata->lmin;
	long max=vecdata->lmax;
	long *ip,*op;
	long is,os;
	long tmp;

	ip = ((long *)in->p);
	op = ((long *)out->p);
	is = in->stride;
	os = out->stride;

	if ((is==1)&&(os==1)) {
		++n; --op; --ip;
		while (--n) {
			tmp = *++ip;
			*++op = tmp>max?max:tmp<min?min:tmp;
		}
	} else {
		while (n--) {
			tmp = *ip;
			*op = tmp>max?max:tmp<min?min:tmp;
			ip+=is; op+=os;
		}
	}
}

void jit_notify_vector_float32(long n, t_jit_notify_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	float min=vecdata->min;
	float max=vecdata->max;
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
			tmp = *++ip;
			*++op = tmp>max?max:tmp<min?min:tmp;
		}
	} else {
		while (n--) {
			tmp = *ip;
			*op = tmp>max?max:tmp<min?min:tmp;
			ip+=is; op+=os;
		}
	}
}

void jit_notify_vector_float64(long n, t_jit_notify_vecdata *vecdata, t_jit_op_info *in, t_jit_op_info *out)
{
	double min=vecdata->min;
	double max=vecdata->max;
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
			tmp = *++ip;
			*++op = tmp>max?max:tmp<min?min:tmp;
		}
	} else {
		while (n--) {
			tmp = *ip;
			*op = tmp>max?max:tmp<min?min:tmp;
			ip+=is; op+=os;
		}
	}
}

t_jit_notify *jit_notify_new(void)
{
	t_jit_notify *x;

	if ((x=(t_jit_notify *)jit_object_alloc(_jit_notify_class))) {
		x->min = 0.;
		x->max = 1.;
	} else {
		x = NULL;
	}
	return x;
}

void jit_notify_free(t_jit_notify *x)
{
	//nada
}
