/*
	Copyright 2001 - Cycling '74
	R. Luke DuBois luke@music.columbia.edu
*/

#include "jit.common.h"

typedef struct _jit_rgb2luma
{
	t_object				ob;
	double					ascale;
	double					rscale;
	double					gscale;
	double					bscale;
} t_jit_rgb2luma;

void *_jit_rgb2luma_class;

t_jit_rgb2luma *jit_rgb2luma_new(void);
void jit_rgb2luma_free(t_jit_rgb2luma *x);
t_jit_err jit_rgb2luma_matrix_calc(t_jit_rgb2luma *x, void *inputs, void *outputs);
void jit_rgb2luma_calculate_ndim(t_jit_rgb2luma *x, long dimcount, long *dim, long planecount,
								 t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop);
t_jit_err jit_rgb2luma_init(void);


t_jit_err jit_rgb2luma_init(void)
{
	long attrflags=0;
	t_jit_object *attr, *mop, *o;

	_jit_rgb2luma_class = jit_class_new("jit_rgb2luma",(method)jit_rgb2luma_new,(method)jit_rgb2luma_free,
										sizeof(t_jit_rgb2luma),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,1); //#inputs,#outputs
	jit_mop_single_planecount(mop, 1);
	jit_mop_single_type(mop, _jit_sym_char);
	o=jit_object_method(mop,_jit_sym_getoutput,1);
	jit_attr_setlong(o,_jit_sym_planelink,0);
	jit_class_addadornment(_jit_rgb2luma_class,mop);

	//add methods
	jit_class_addmethod(_jit_rgb2luma_class, (method)jit_rgb2luma_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);

	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"ascale",_jit_sym_float64,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_rgb2luma,ascale));
	jit_class_addattr(_jit_rgb2luma_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Alpha Scale\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"rscale",_jit_sym_float64,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_rgb2luma,rscale));
	jit_class_addattr(_jit_rgb2luma_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Red Scale\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"gscale",_jit_sym_float64,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_rgb2luma,gscale));
	jit_class_addattr(_jit_rgb2luma_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Green Scale\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"bscale",_jit_sym_float64,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_rgb2luma,bscale));
	jit_class_addattr(_jit_rgb2luma_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Blue Scale\"");

	jit_class_register(_jit_rgb2luma_class);

	return JIT_ERR_NONE;
}


t_jit_err jit_rgb2luma_matrix_calc(t_jit_rgb2luma *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock,out_savelock, dimmode;
	t_jit_matrix_info in_minfo,out_minfo;
	char *in_bp,*out_bp;
	long i,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	void *in_matrix, *out_matrix;

	in_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);
	out_matrix 	= jit_object_method(outputs,_jit_sym_getindex,0);

	if (x&&in_matrix&&out_matrix) {

		in_savelock = (long) jit_object_method(in_matrix,_jit_sym_lock,1);
		out_savelock = (long) jit_object_method(out_matrix,_jit_sym_lock,1);

		jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
		jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);

		jit_object_method(in_matrix,_jit_sym_getdata,&in_bp);
		jit_object_method(out_matrix,_jit_sym_getdata,&out_bp);

		if (!in_bp) { err=JIT_ERR_GENERIC; goto out;}
		if (!out_bp) { err=JIT_ERR_GENERIC; goto out;}

		//compatible types?
		if ((in_minfo.type!=_jit_sym_char)||(in_minfo.type!=out_minfo.type)) {
			err=JIT_ERR_MISMATCH_TYPE;
			goto out;
		}

		//compatible planes?
		if ((in_minfo.planecount!=4)||(out_minfo.planecount!=1)) {
			err=JIT_ERR_MISMATCH_PLANE;
			goto out;
		}

		//get dimensions/planecount
		dimcount   = out_minfo.dimcount;
		planecount = out_minfo.planecount;
		for (i=0; i<dimcount; i++) {
			dim[i] = MIN(in_minfo.dim[i],out_minfo.dim[i]);
		}

		//calculate
		jit_parallel_ndim_simplecalc2((method)jit_rgb2luma_calculate_ndim,
									  x, dimcount, dim, planecount, &in_minfo, in_bp, &out_minfo, out_bp,
									  0 /* flags1 */, 0 /* flags2 */);

	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(out_matrix,_jit_sym_lock,out_savelock);
	jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	return err;
}

//
//recursive functions to handle higher dimension matrices, by processing 2D sections at a time
//


void jit_rgb2luma_calculate_ndim(t_jit_rgb2luma *x, long dimcount, long *dim, long planecount,
								 t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop)
{
	long i,j,width,height;
	uchar *ip,*op;
	long tmp,safe,total;
	long ascale = x->ascale * 65536.;
	long rscale = x->rscale * 65536.;
	long gscale = x->gscale * 65536.;
	long bscale = x->bscale * 65536.;

	if (dimcount<1) return; //safety


	switch(dimcount) {
	case 1:
		dim[1]=1;
	case 2:
		safe = (((ascale+rscale+gscale+bscale)<=65536)&&(ascale>=0)&&(rscale>=0)&&(gscale>=0)&&(bscale>=0));

		width  = dim[0];
		height = dim[1];
		if (safe) {
			for (i=0; i<height; i++) {
				ip = bip + i*in_minfo->dimstride[1];
				op = bop + i*out_minfo->dimstride[1];

				for (j=0; j<width; j++) {
					*op++ = ((*(ip) * ascale) + (*(ip + 1) * rscale) + (*(ip + 2) * gscale) + (*(ip + 3) * bscale)) >> 16L;
					ip+=4;
				}
			}
		} else {
			for (i=0; i<height; i++) {
				ip = bip + i*in_minfo->dimstride[1];
				op = bop + i*out_minfo->dimstride[1];

				for (j=0; j<width; j++) {
					tmp = ((*(ip) * ascale) + (*(ip + 1) * rscale) + (*(ip + 2) * gscale) + (*(ip + 3) * bscale)) >> 16L;
					*op++ = CLAMP(tmp, 0, 255);
					ip+=4;
				}
			}
		}
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			ip = bip + i*in_minfo->dimstride[dimcount-1];
			op = bop + i*out_minfo->dimstride[dimcount-1];
			jit_rgb2luma_calculate_ndim(x,dimcount-1,dim,planecount,in_minfo,ip,out_minfo,op);
		}
	}
}

t_jit_rgb2luma *jit_rgb2luma_new(void)
{
	t_jit_rgb2luma *x;
	short i;

	if (x=(t_jit_rgb2luma *)jit_object_alloc(_jit_rgb2luma_class)) {
		x->ascale = 0.;
		x->rscale = 0.299;
		x->gscale = 0.587;
		x->bscale = 0.114;
	} else {
		x = NULL;
	}
	return x;
}

void jit_rgb2luma_free(t_jit_rgb2luma *x)
{
	//nada
}

