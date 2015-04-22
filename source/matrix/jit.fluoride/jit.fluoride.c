/*
	Copyright 2002-2005 - Cycling '74
	R. Luke DuBois luke@cycling74.com
*/

// updated for new architecture by rld 2/25/02

/*
 * jit.fluoride does a cheap approximation of a neon glow effect.  as cell values approach
 * a luminance value they fade into a specified color.  above that luminance they fade to
 * black (0).  values outside of a tolerance boundary are passed.  jit.fluoride can work
 * in an input matrix in either greyscale (mode 0) or color (mode 1).
 *
 */

#include "jit.common.h"
#include "ext_obex.h"

typedef struct _jit_fluoride
{
	t_object				ob;
	long					glowcount,mode;
	double					glow[3], lum, tol;
} t_jit_fluoride;

void *_jit_fluoride_class;

t_jit_fluoride *jit_fluoride_new(void);
void jit_fluoride_free(t_jit_fluoride *x);
t_jit_err jit_fluoride_matrix_calc(t_jit_fluoride *x, void *inputs, void *outputs);
void jit_fluoride_calculate_ndim(t_jit_fluoride *x, long dimcount, long *dim, long planecount,
								 t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop);
t_jit_err jit_fluoride_init(void);


t_jit_err jit_fluoride_init(void)
{
	long attrflags=0;
	t_jit_object *attr, *mop;

	_jit_fluoride_class = jit_class_new("jit_fluoride",(method)jit_fluoride_new,(method)jit_fluoride_free,
										sizeof(t_jit_fluoride),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,1); //#inputs,#outputs
	jit_mop_single_type(mop,_jit_sym_char);
	jit_mop_single_planecount(mop,4);
	jit_class_addadornment(_jit_fluoride_class,mop);

	//add methods
	jit_class_addmethod(_jit_fluoride_class, (method)jit_fluoride_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);

	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;

	CLASS_STICKY_CATEGORY(_jit_fluoride_class,0,"Behavior");
	CLASS_STICKY_ATTR(_jit_fluoride_class,"basic",0,"1");

	// glow -- sets color for neon effect
	attr = jit_object_new(_jit_sym_jit_attr_offset_array, "glow", _jit_sym_float64, 3,
						  attrflags, (method)0L, (method)0L, calcoffset(t_jit_fluoride, glowcount),
						  calcoffset(t_jit_fluoride,glow));
	jit_class_addattr(_jit_fluoride_class,attr);
	CLASS_ATTR_STYLE_LABEL(_jit_fluoride_class,"glow",0,"rgb","Glow Color");

	// lum -- moves center luminosity
	attr = jit_object_new(_jit_sym_jit_attr_offset,"lum",_jit_sym_float64,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_fluoride,lum));
	jit_class_addattr(_jit_fluoride_class,attr);
	CLASS_ATTR_LABEL(_jit_fluoride_class,"lum",0,"Luminosity");

	// tol -- width of neon tolerance
	attr = jit_object_new(_jit_sym_jit_attr_offset,"tol",_jit_sym_float64,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_fluoride,tol));
	jit_class_addattr(_jit_fluoride_class,attr);
	CLASS_ATTR_LABEL(_jit_fluoride_class,"tol",0,"Tolerance");

	// mode -- b/w (0) or color (1)
	attr = jit_object_new(_jit_sym_jit_attr_offset,"mode",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_fluoride,mode));
	jit_class_addattr(_jit_fluoride_class,attr);
	CLASS_ATTR_LABEL(_jit_fluoride_class,"mode",0,"Color Mode");
	CLASS_ATTR_ENUMINDEX(_jit_fluoride_class, "mode", 0, "\"Black and White\" Color");

	CLASS_STICKY_CATEGORY_CLEAR(_jit_fluoride_class);
	CLASS_STICKY_ATTR_CLEAR(_jit_fluoride_class, "basic");

	jit_class_register(_jit_fluoride_class);

	return JIT_ERR_NONE;
}


t_jit_err jit_fluoride_matrix_calc(t_jit_fluoride *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock,out_savelock, dimmode;
	t_jit_matrix_info in_minfo,out_minfo;
	char *in_bp,*out_bp;
	long i,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	void *in_matrix, *out_matrix;

	in_matrix = jit_object_method(inputs, _jit_sym_getindex, 0);
	out_matrix = jit_object_method(outputs, _jit_sym_getindex, 0);

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
		if ((in_minfo.planecount!=4)||(out_minfo.planecount!=4)) {
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
		jit_parallel_ndim_simplecalc2((method)jit_fluoride_calculate_ndim,
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

// jit_fluoride_calculate_ndim() -- when x->dimmode==-1, sorts both dimensions together
void jit_fluoride_calculate_ndim(t_jit_fluoride *x, long dimcount, long *dim, long planecount,
								 t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop)
{
	long i,j,width,height, index;
	long glow[3], outpix, lum, tol, bw, tmax, temp, mode;
	float indperc;
	uchar *ip,*op;

	glow[0] = x->glow[0]*255.;
	glow[1] = x->glow[1]*255.;
	glow[2] = x->glow[2]*255.;
	lum = x->lum*255.;
	tol = x->tol*255.;
	bw = MAX(1,lum-tol);
	tmax = MIN(255,(lum+tol));
	mode = CLIP_ASSIGN(x->mode,0,1);

	if (dimcount<1) return; //safety

	switch(dimcount) {
	case 1:
		dim[1]=1;
	case 2:

		width  = dim[0];
		height = dim[1];
		switch(mode) {
		case 1: // color
			for (i=0; i<height; i++) {
				ip = bip + i*in_minfo->dimstride[1];
				op = bop + i*out_minfo->dimstride[1];

				for (j=0; j<width; j++) {
					index = (float)(*(ip+1)*.299)+(float)(*(ip+2)*.587)+(float)(*(ip+3)*.114);
					if(index<bw) {
						*op++ = *ip;
						*op++ = *(ip+1);
						*op++ = *(ip+2);
						*op++ = *(ip+3);
						goto ick1;
					}
					if(index<(lum+1)) {
						indperc=((float)(lum-index)*(1./tol));
						*op++ = *ip;
						outpix = (float)(*(ip+1))*(indperc);
						temp = ((float)(glow[0])*(1.-indperc))+outpix;
						*op++ = CLAMP(temp,0,255);
						outpix = (float)(*(ip+2))*(indperc);
						temp = ((float)(glow[1])*(1.-indperc))+outpix;
						*op++ = CLAMP(temp,0,255);
						outpix = (float)(*(ip+3))*(indperc);
						temp = ((float)(glow[2])*(1.-indperc))+outpix;
						*op++ = CLAMP(temp,0,255);
					}
					else {
						indperc=((float)(255-index)*(1./(tmax-lum)));
						*op++ = *ip;
						temp = ((float)(glow[0])*indperc);
						*op++ = CLAMP(temp,0,255);
						temp = ((float)(glow[1])*indperc);
						*op++ = CLAMP(temp,0,255);
						temp = ((float)(glow[2])*indperc);
						*op++ = CLAMP(temp,0,255);
					}

ick1:
					;
					ip+=4;

				}
			}
			break;
		case 0: // b/w
		default:
			for (i=0; i<height; i++) {
				ip = bip + i*in_minfo->dimstride[1];
				op = bop + i*out_minfo->dimstride[1];

				for (j=0; j<width; j++) {
					index = (float)(*(ip+1)*.299)+(float)(*(ip+2)*.587)+(float)(*(ip+3)*.114);
					if(index<bw) {
						*op++ = *ip;
						*op++ = index;
						*op++ = index;
						*op++ = index;
						goto ick;
					}
					if(index<(lum+1)) {
						indperc=((float)(lum-index)*(1./tol));
						outpix = (float)(index)*(indperc);
						*op++ = *ip;
						temp = ((float)(glow[0])*(1.-indperc))+outpix;
						*op++ = CLAMP(temp,0,255);
						temp = ((float)(glow[1])*(1.-indperc))+outpix;
						*op++ = CLAMP(temp,0,255);
						temp = ((float)(glow[2])*(1.-indperc))+outpix;
						*op++ = CLAMP(temp,0,255);
					}
					else {
						indperc=((float)(255-index)*(1./(tmax-lum)));
						*op++ = *ip;
						temp = ((float)(glow[0])*indperc);
						*op++ = CLAMP(temp,0,255);
						temp = ((float)(glow[1])*indperc);
						*op++ = CLAMP(temp,0,255);
						temp = ((float)(glow[2])*indperc);
						*op++ = CLAMP(temp,0,255);

					}

ick:
					;
					ip+=4;

				}
			}
			break;
		}
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			ip = bip + i*in_minfo->dimstride[dimcount-1];
			op = bop + i*out_minfo->dimstride[dimcount-1];
			jit_fluoride_calculate_ndim(x,dimcount-1,dim,planecount,in_minfo,ip,out_minfo,op);
		}
	}
}


t_jit_fluoride *jit_fluoride_new(void)
{
	t_jit_fluoride *x;
	short i;

	if (x=(t_jit_fluoride *)jit_object_alloc(_jit_fluoride_class)) {
		x->glow[0] = 0.;
		x->glow[1] = 1.;
		x->glow[2] = 0.; // defaults to bright green
		x->glowcount = 3;
		x->lum = 0.88;
		x->tol = 0.2;
		x->mode = 0;
	} else {
		x = NULL;
	}
	return x;
}

void jit_fluoride_free(t_jit_fluoride *x)
{
	//nada
}

