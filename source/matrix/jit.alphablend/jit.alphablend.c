/*
	Copyright 2001 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"

typedef struct _jit_alphablend
{
	t_object				ob;
	long					mode;
} t_jit_alphablend;

void *_jit_alphablend_class;

t_jit_err jit_alphablend_init(void);
t_jit_alphablend *jit_alphablend_new(void);
void jit_alphablend_free(t_jit_alphablend *x);
t_jit_err jit_alphablend_matrix_calc(t_jit_alphablend *x, void *inputs, void *outputs);

void jit_alphablend_calculate_ndim(t_jit_alphablend *x, long dimcount, long *dim, long planecount, t_jit_matrix_info *in1_minfo, char *bip1,
								   t_jit_matrix_info *in2_minfo, char *bip2, t_jit_matrix_info *out_minfo, char *bop);

t_jit_err jit_alphablend_init(void)
{
	long attrflags=0;
	t_jit_object *attr,*mop,*o;
	t_symbol *atsym;
	t_atom a[3];

	atsym = gensym("jit_attr_offset");

	_jit_alphablend_class = jit_class_new("jit_alphablend",(method)jit_alphablend_new,(method)jit_alphablend_free,
										  sizeof(t_jit_alphablend),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,2,1);
//	jit_mop_single_planecount(mop,4);
	jit_atom_setsym(a,_jit_sym_char);
	jit_atom_setsym(a+1,_jit_sym_float32);
	jit_atom_setsym(a+2,_jit_sym_float64);
	o = jit_object_method(mop,_jit_sym_getinput,2);
	jit_object_method(o,_jit_sym_types,3,a);
	o = jit_object_method(mop,_jit_sym_getoutput,1);
	jit_object_method(o,_jit_sym_types,3,a);

	jit_class_addadornment(_jit_alphablend_class,mop);
	//add methods
	jit_class_addmethod(_jit_alphablend_class, (method)jit_alphablend_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);

	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(atsym,"mode",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_alphablend,mode));
	jit_class_addattr(_jit_alphablend_class,attr);
	CLASS_ATTR_BASIC(_jit_alphablend_class,"mode",0);
	CLASS_ATTR_LABEL(_jit_alphablend_class,"mode",0,"Crossfade Mode");
	CLASS_ATTR_ENUMINDEX2(_jit_alphablend_class, "mode", 0, "Left-to-Right", "Right-to-Left");
	CLASS_ATTR_CATEGORY(_jit_alphablend_class, "mode", 0, "Mode");

	jit_class_register(_jit_alphablend_class);

	return JIT_ERR_NONE;
}

t_jit_err jit_alphablend_matrix_calc(t_jit_alphablend *x, void *inputs, void *outputs)
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
		if (((in1_minfo.type!=_jit_sym_char)&&(in1_minfo.type!=_jit_sym_float32)&&(in1_minfo.type!=_jit_sym_float64))||
				(in1_minfo.type!=in2_minfo.type)||(in1_minfo.type!=out_minfo.type)) {
			err=JIT_ERR_MISMATCH_TYPE;
			goto out;
		}
		//compatible planes?
		if ((in1_minfo.planecount!=in2_minfo.planecount)||(in1_minfo.planecount!=out_minfo.planecount)) {
			err=JIT_ERR_MISMATCH_PLANE;
			goto out;
		}

		//get dimensions/planecount
		dimcount   = out_minfo.dimcount;
		planecount = out_minfo.planecount;

		for (i=0; i<dimcount; i++) {
			dim[i] = out_minfo.dim[i];
			if ((in1_minfo.dim[i]<dim[i])) dim[i] = in1_minfo.dim[i];
			if ((in2_minfo.dim[i]<dim[i])&&in2_minfo.dim[i]>1) {
				dim[i] = in2_minfo.dim[i];
			}
		}

		jit_parallel_ndim_simplecalc3((method)jit_alphablend_calculate_ndim,
									  x, dimcount, dim, planecount, &in1_minfo, in1_bp, &in2_minfo, in2_bp, &out_minfo, out_bp,
									  0 /* flags1 */, 0 /* flags2 */, 0 /* flags3 */);
	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(out_matrix,_jit_sym_lock,out_savelock);
	jit_object_method(in2_matrix,_jit_sym_lock,in2_savelock);
	jit_object_method(in1_matrix,_jit_sym_lock,in1_savelock);
	return err;
}


void jit_alphablend_calculate_ndim(t_jit_alphablend *x, long dimcount, long *dim, long planecount, t_jit_matrix_info *in1_minfo, char *bip1,
								   t_jit_matrix_info *in2_minfo, char *bip2, t_jit_matrix_info *out_minfo, char *bop)
{
	long i,j,k;
	uchar *cip1,*cip2,*cop;
	float *fip1,*fip2,*fop;
	double *dip1,*dip2,*dop;
	long calpha,calpha_inv;
	float falpha,falpha_inv;
	float dalpha,dalpha_inv;
	float default_alpha = 1.0;
	uchar cdefault_alpha = (uchar)(default_alpha * 255.);
	long height,width;

	if (dimcount<1) return; //safety

	switch(dimcount) {
	case 1:
		dim[1]=1;
	case 2:
		width  = dim[0];
		height = dim[1];
		if (in1_minfo->type==_jit_sym_char) {
			switch(planecount) {
			case 4:
				for (i=0; i<height; i++) {
					cip1 = (uchar *) bip1 + i*in1_minfo->dimstride[1];
					cip2 = (uchar *) bip2 + i*in2_minfo->dimstride[1];
					cop  = (uchar *) bop  + i*out_minfo->dimstride[1];

					switch (x->mode) {
					case 1:	//inverse
						for (j=0; j<width; j++) {
							calpha_inv 	= (long)(*cip1++);
							calpha		= 256 - calpha_inv;
							*cop++		= cdefault_alpha;
							cip2++; //ignore other alpha channels
							*cop++ = (((long)(*cip1++)*calpha)+((long)(*cip2++)*calpha_inv))>>8L;
							*cop++ = (((long)(*cip1++)*calpha)+((long)(*cip2++)*calpha_inv))>>8L;
							*cop++ = (((long)(*cip1++)*calpha)+((long)(*cip2++)*calpha_inv))>>8L;
						}
						break;
					default:
						for (j=0; j<width; j++) {
							calpha 		= (long)(*cip1++);
							calpha_inv	= 256 - calpha;
							*cop++		= cdefault_alpha;
							cip2++; //ignore other alpha channels
							*cop++ = (((long)(*cip1++)*calpha)+((long)(*cip2++)*calpha_inv))>>8L;
							*cop++ = (((long)(*cip1++)*calpha)+((long)(*cip2++)*calpha_inv))>>8L;
							*cop++ = (((long)(*cip1++)*calpha)+((long)(*cip2++)*calpha_inv))>>8L;
						}
						break;
					}
				}
				break;
			default:
				for (i=0; i<height; i++) {
					cip1 = (uchar *) bip1 + i*in1_minfo->dimstride[1];
					cip2 = (uchar *) bip2 + i*in2_minfo->dimstride[1];
					cop  = (uchar *) bop  + i*out_minfo->dimstride[1];

					switch (x->mode) {
					case 1:	//inverse
						for (j=0; j<width; j++) {
							calpha_inv 	= (long)(*cip1);
							calpha		= 256 - calpha_inv;
							cop[0]		= cdefault_alpha;
							for (k = 1; k < planecount; k++) {
								cop[k] = (((long)(cip1[k])*calpha)+((long)(cip2[k])*calpha_inv))>>8L;
							}
							cop += planecount;
							cip1 += planecount;
							cip2 += planecount;
						}
						break;
					default:
						for (j=0; j<width; j++) {
							calpha 		= (long)(*cip1);
							calpha_inv	= 256 - calpha;
							cop[0] = cdefault_alpha;
							for (k = 1; k < planecount; k++) {
								cop[k] = (((long)(cip1[k])*calpha)+((long)(cip2[k])*calpha_inv))>>8L;
							}
							cop += planecount;
							cip1 += planecount;
							cip2 += planecount;
						}
						break;
					}
				}
				break;
			}
		} else if (in1_minfo->type==_jit_sym_float32) {
			switch (planecount) {
			case 4:
				for (i=0; i<height; i++) {
					fip1 = (float *) (bip1 + i*in1_minfo->dimstride[1]);
					fip2 = (float *) (bip2 + i*in2_minfo->dimstride[1]);
					fop  = (float *) (bop  + i*out_minfo->dimstride[1]);

					switch (x->mode) {
					case 1:	//inverse
						for (j=0; j<width; j++) {
							falpha_inv 	= *fip1++;
							CLIP_ASSIGN(falpha_inv,0.,1.);
							falpha		= 1. - falpha_inv;
							*fop++		= default_alpha;
							fip2++; //ignore other alpha channels
							*fop++ = ((*fip1++)*falpha)+((*fip2++)*falpha_inv);
							*fop++ = ((*fip1++)*falpha)+((*fip2++)*falpha_inv);
							*fop++ = ((*fip1++)*falpha)+((*fip2++)*falpha_inv);
						}
						break;
					default:
						for (j=0; j<width; j++) {
							falpha 		= *fip1++;
							CLIP_ASSIGN(falpha,0.,1.);
							falpha_inv	= 1. - falpha;
							*fop++		= default_alpha;
							fip2++; //ignore other alpha channels
							*fop++ = ((*fip1++)*falpha)+((*fip2++)*falpha_inv);
							*fop++ = ((*fip1++)*falpha)+((*fip2++)*falpha_inv);
							*fop++ = ((*fip1++)*falpha)+((*fip2++)*falpha_inv);
						}
						break;
					}
				}
				break;
			default:
				for (i=0; i<height; i++) {
					fip1 = (float *) (bip1 + i*in1_minfo->dimstride[1]);
					fip2 = (float *) (bip2 + i*in2_minfo->dimstride[1]);
					fop  = (float *) (bop  + i*out_minfo->dimstride[1]);

					switch (x->mode) {
					case 1:	//inverse
						for (j=0; j<width; j++) {
							falpha_inv 	= *fip1;
							CLIP_ASSIGN(falpha_inv,0.,1.);
							falpha		= 1. - falpha_inv;
							fop[0]		= default_alpha;
							for (k = 1; k < planecount; k++) {
								fop[k] = ((fip1[k])*falpha)+((fip2[k])*falpha_inv);
							}
							fop += planecount;
							fip1 += planecount;
							fip2 += planecount;
						}
						break;
					default:
						for (j=0; j<width; j++) {
							falpha 		= *fip1;
							CLIP_ASSIGN(falpha,0.,1.);
							falpha_inv	= 1. - falpha;
							fop[0]		= default_alpha;
							for (k = 1; k < planecount; k++) {
								fop[k] = ((fip1[k])*falpha)+((fip2[k])*falpha_inv);
							}
							fop += planecount;
							fip1 += planecount;
							fip2 += planecount;
						}
						break;
					}
				}
				break;
			}
		} else if (in1_minfo->type==_jit_sym_float64) {
			switch (planecount) {
			case 4:
				for (i=0; i<height; i++) {
					dip1 = (double *) (bip1 + i*in1_minfo->dimstride[1]);
					dip2 = (double *) (bip2 + i*in2_minfo->dimstride[1]);
					dop  = (double *) (bop  + i*out_minfo->dimstride[1]);

					switch (x->mode) {
					case 1:	//inverse
						for (j=0; j<width; j++) {
							dalpha_inv 	= *dip1++;
							CLIP_ASSIGN(dalpha_inv,0.,1.);
							dalpha		= 1. - dalpha_inv;
							*dop++		= default_alpha;
							dip2++; //ignore other alpha channels
							*dop++ = ((*dip1++)*dalpha)+((*dip2++)*dalpha_inv);
							*dop++ = ((*dip1++)*dalpha)+((*dip2++)*dalpha_inv);
							*dop++ = ((*dip1++)*dalpha)+((*dip2++)*dalpha_inv);
						}
						break;
					default:
						for (j=0; j<width; j++) {
							dalpha 		= *dip1++;
							CLIP_ASSIGN(dalpha,0.,1.);
							dalpha_inv	= 1. - dalpha;
							*dop++		= default_alpha;
							dip2++; //ignore other alpha channels
							*dop++ = ((*dip1++)*dalpha)+((*dip2++)*dalpha_inv);
							*dop++ = ((*dip1++)*dalpha)+((*dip2++)*dalpha_inv);
							*dop++ = ((*dip1++)*dalpha)+((*dip2++)*dalpha_inv);
						}
						break;
					}
				}
				break;
			default:
				for (i=0; i<height; i++) {
					dip1 = (double *) (bip1 + i*in1_minfo->dimstride[1]);
					dip2 = (double *) (bip2 + i*in2_minfo->dimstride[1]);
					dop  = (double *) (bop  + i*out_minfo->dimstride[1]);

					switch (x->mode) {
					case 1:	//inverse
						for (j=0; j<width; j++) {
							dalpha_inv 	= *dip1;
							CLIP_ASSIGN(dalpha_inv,0.,1.);
							dalpha		= 1. - dalpha_inv;
							dop[0] 		= default_alpha;
							for (k = 1; k < planecount; k++) {
								dop[k] = ((dip1[k])*dalpha)+((dip2[k])*dalpha_inv);
							}
							dop += planecount;
							dip1 += planecount;
							dip2 += planecount;
						}
						break;
					default:
						for (j=0; j<width; j++) {
							dalpha 		= *dip1;
							CLIP_ASSIGN(dalpha,0.,1.);
							dalpha_inv	= 1. - dalpha;
							dop[0] 		= default_alpha;
							for (k = 1; k < planecount; k++) {
								dop[k] = ((dip1[k])*dalpha)+((dip2[k])*dalpha_inv);
							}
							dop += planecount;
							dip1 += planecount;
							dip2 += planecount;
						}
						break;
					}
				}
				break;
			}
		}
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			cip1 = (uchar *) bip1 + i*in1_minfo->dimstride[dimcount-1];
			cip2 = (uchar *) bip2 + i*in2_minfo->dimstride[dimcount-1];
			cop  = (uchar *) bop  + i*out_minfo->dimstride[dimcount-1];
			jit_alphablend_calculate_ndim(x,dimcount-1,dim,planecount,in1_minfo,(char *)cip1,in2_minfo,(char *)cip2,out_minfo,(char *)cop);
		}
	}
}

t_jit_alphablend *jit_alphablend_new(void)
{
	t_jit_alphablend *x;

	if (x=(t_jit_alphablend *)jit_object_alloc(_jit_alphablend_class)) {
		x->mode = 0;
	} else {
		x = NULL;
	}
	return x;
}

void jit_alphablend_free(t_jit_alphablend *x)
{
	//nada
}
