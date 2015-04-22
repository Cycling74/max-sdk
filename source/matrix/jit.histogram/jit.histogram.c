/*
	Copyright 2001 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"

typedef struct _jit_histogram
{
	t_object	ob;
	long		normval;
	//flags
	char		autoclear;
	char		normalize;
} t_jit_histogram;

void *_jit_histogram_class;

t_jit_err jit_histogram_init(void);
t_jit_histogram *jit_histogram_new(void);
void jit_histogram_free(t_jit_histogram *x);
t_jit_err jit_histogram_matrix_calc(t_jit_histogram *x, void *inputs, void *outputs);
void jit_histogram_calculate_ndim(t_jit_histogram *x, long dimcount, long *dim, long planecount,
								  t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop);
void jit_histogram_vector_char(long n, long maxsize, t_jit_op_info *in1, t_jit_op_info *out);
void jit_histogram_vector_long(long n, long maxsize, t_jit_op_info *in1, t_jit_op_info *out);
void jit_histogram_normalize( t_jit_matrix_info *out_minfo, char *bop, long normval);
void jit_histogram_normalize2(t_jit_matrix_info *out_minfo, char *bop, long normval);

t_jit_err jit_histogram_init(void)
{
	long attrflags=0;
	t_jit_object *attr,*mop,*o;
	t_atom a[2];

	_jit_histogram_class = jit_class_new("jit_histogram",(method)jit_histogram_new,(method)jit_histogram_free,
										 sizeof(t_jit_histogram),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,1);
	o = jit_object_method(mop,_jit_sym_getoutput,1);
	jit_attr_setlong(o,_jit_sym_dimlink,0);
	jit_attr_setlong(o,_jit_sym_typelink,0);
	jit_atom_setlong(a,256);
	jit_object_method(o,_jit_sym_mindim,1,a);
	jit_atom_setsym(a,_jit_sym_long); //default
	jit_atom_setsym(a+1,_jit_sym_char);
	jit_object_method(o,_jit_sym_types,2,a);
	jit_class_addadornment(_jit_histogram_class,mop);
	//add methods
	jit_class_addmethod(_jit_histogram_class, (method)jit_histogram_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);

	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;

	CLASS_STICKY_CATEGORY(_jit_histogram_class,0,"Behavior");
	CLASS_STICKY_ATTR(_jit_histogram_class,"basic",0,"1");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"normval",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_histogram,normval));
	jit_class_addattr(_jit_histogram_class,attr);
	CLASS_ATTR_LABEL(_jit_histogram_class,"normval",0,"Normalization Value");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"autoclear",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_histogram,autoclear));
	jit_class_addattr(_jit_histogram_class,attr);
	CLASS_ATTR_STYLE_LABEL(_jit_histogram_class,"autoclear",0,"onoff","Auto-Clear");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"normalize",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_histogram,normalize));
	jit_class_addattr(_jit_histogram_class,attr);
	CLASS_ATTR_STYLE_LABEL(_jit_histogram_class,"normalize",0,"onoff","Normalize Histogram");

	CLASS_STICKY_CATEGORY_CLEAR(_jit_histogram_class);
	CLASS_STICKY_ATTR_CLEAR(_jit_histogram_class, "basic");

	jit_class_register(_jit_histogram_class);

	return JIT_ERR_NONE;
}

t_jit_err jit_histogram_matrix_calc(t_jit_histogram *x, void *inputs, void *outputs)
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
		if (((in_minfo.type!=_jit_sym_char)&&(in_minfo.type!=_jit_sym_long))||(out_minfo.type!=_jit_sym_long)) {
			err=JIT_ERR_MISMATCH_TYPE;
			goto out;
		}

		//compatible dimensions?
		if (out_minfo.dim[0]<256) {
			err=JIT_ERR_MISMATCH_DIM;
			goto out;
		}

		//get dimensions/planecount
		//histo does this a bit different than how it happens for most other objects
		dimcount   = in_minfo.dimcount;
		planecount = out_minfo.planecount;
		for (i=0; i<dimcount; i++) {
			dim[i] = in_minfo.dim[i];
		}

		if (x->autoclear) jit_object_method(out_matrix,gensym("clear"));
		//calculate
		jit_histogram_calculate_ndim(x, dimcount, dim, planecount, &in_minfo, in_bp, &out_minfo, out_bp);
		switch (x->normalize)  {
		case 0: 	break;
		case 2:		jit_histogram_normalize2(&out_minfo, out_bp, x->normval);	break;
		default:	jit_histogram_normalize(&out_minfo, out_bp, x->normval);	break;
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
void jit_histogram_calculate_ndim(t_jit_histogram *x, long dimcount, long *dim, long planecount,
								  t_jit_matrix_info *in1_minfo, char *bip1, t_jit_matrix_info *out_minfo, char *bop)
{
	long i,j,n,maxsize;
	uchar *ip1,*op;
	t_jit_op_info in1_opinfo,out_opinfo;

	if (dimcount<1) return; //safety

	switch(dimcount) {
	case 1:
		dim[1] = 1;
	case 2:
		n = dim[0];
		maxsize = out_minfo->dim[0];
		in1_opinfo.stride = in1_minfo->dim[0]>1?in1_minfo->planecount:0;
		out_opinfo.stride = out_minfo->dim[0]>1?out_minfo->planecount:0;
		if (in1_minfo->type==_jit_sym_char) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in1_opinfo.p = bip1 + i*in1_minfo->dimstride[1] + j%in1_minfo->planecount;
					out_opinfo.p = bop  + (j%out_minfo->planecount)*4; //out always long
					jit_histogram_vector_char(n,maxsize,&in1_opinfo,&out_opinfo);
				}
			}
		} else if (in1_minfo->type==_jit_sym_long) {
			for (i=0; i<dim[1]; i++) {
				for (j=0; j<planecount; j++) {
					in1_opinfo.p = bip1 + i*in1_minfo->dimstride[1] + (j%in1_minfo->planecount)*4;
					out_opinfo.p = bop  + j*4;
					jit_histogram_vector_long(n,maxsize,&in1_opinfo,&out_opinfo);
				}
			}
		}
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			ip1 = (uchar *)(bip1 + i*in1_minfo->dimstride[dimcount-1]);
			op = (uchar *)(bop + i*out_minfo->dimstride[dimcount-1]);
			jit_histogram_calculate_ndim(x,dimcount-1,dim,planecount,in1_minfo,(char *)ip1,out_minfo,(char *)op);
		}
	}
}

//outmatrix is guaranteed to be no smaller than 256 elements so no need to test ip1 for 0-maxsize
void jit_histogram_vector_char(long n, long maxsize, t_jit_op_info *in1, t_jit_op_info *out)
{
	uchar *ip1;
	t_int32 *op,is1,os;

	ip1 = ((uchar *)in1->p);
	op  = ((t_int32 *)out->p);
	is1 = in1->stride;
	os  = out->stride;

	++n;
	while (--n) {
		op[(*ip1)*os] += 1; ip1 += is1;
	}
}

void jit_histogram_vector_long(long n, long maxsize, t_jit_op_info *in1, t_jit_op_info *out)
{
	t_int32 *ip1,*op,is1,os,c;

	ip1 = ((t_int32 *)in1->p);
	op  = ((t_int32 *)out->p);
	is1 = in1->stride;
	os  = out->stride;

	++n;
	while (--n) {
		c = *ip1;
		if ((c>=0)&&(c<maxsize)) op[c*os] += 1;
		ip1 += is1;
	}
}

void jit_histogram_normalize(t_jit_matrix_info *out_minfo, char *bop, long normval)
{
	long j,n,os,max;
	t_int32 *op;
	double scale;

	os = out_minfo->planecount;
	normval = ABS(normval);

	for (j=0; j<out_minfo->planecount; j++) {
		n 	= out_minfo->dim[0] + 1;
		op 	= (t_int32 *) (bop + j*4);
		max = 0;
		while (--n) { max = MAX(max,ABS(*op)); op += os; }
		n 	= out_minfo->dim[0] + 1;
		op 	= (t_int32 *) (bop + j*4);
		if (max&&normval) {
			scale = (double)normval/(double)max;
			while (--n) { *op = (long)(((double)(*op))*scale); op += os; }
		} else {
			while (--n) { *op = 0; op += os; }
		}

	}
}

void jit_histogram_normalize2(t_jit_matrix_info *out_minfo, char *bop, long normval)
{
	long n,max=0;
	t_int32 *op;
	double scale;

	normval = ABS(normval);

	n 	= (out_minfo->dim[0]*out_minfo->planecount) + 1;
	op 	= (t_int32 *) bop;
	while (--n) { max = MAX(max,ABS(*op)); op++; }
	n 	= (out_minfo->dim[0]*out_minfo->planecount) + 1;
	op 	= (t_int32 *) bop;
	if (max&&normval) {
		scale = (double)normval/(double)max;
		while (--n) { *op = (long)(((double)(*op))*scale); op++; }
	} else {
		while (--n) { *op = 0; op++; }
	}

}


t_jit_histogram *jit_histogram_new(void)
{
	t_jit_histogram *x;

	if (x=(t_jit_histogram *)jit_object_alloc(_jit_histogram_class)) {

	} else {
		x = NULL;
	}
	return x;
}

void jit_histogram_free(t_jit_histogram *x)
{
	//nada
}
