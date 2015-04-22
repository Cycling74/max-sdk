/*
	Copyright 2001 - Cycling '74
	R. Luke DuBois luke@music.columbia.edu
*/

// 12/15 jb readability update, plus a little faster

/*
 * jit.keyscreen performs a three-source 'choke' chromakey.  any of the three input matrices can be
 * designated as the 'key' image (from which the image mask is created), the 'target' image (which the mask
 * is overlaid onto), or the 'mask' image (which is placed on top of the 'target' in the shape of the 'key').
 *
 * jit.keyscreen takes a color and a tolerance range for the keying.  it can work by cell or by plane (set via
 * the 'mode' attribute).
 *
 */

#include "jit.common.h"

typedef struct _jit_keyscreen
{
	t_object				ob;
	long					key, target, mask,mode;
	float					alpha, red, green, blue, alphatol, redtol, greentol, bluetol;
} t_jit_keyscreen;

void *_jit_keyscreen_class;

t_jit_keyscreen *jit_keyscreen_new(void);
void jit_keyscreen_free(t_jit_keyscreen *x);
t_jit_err jit_keyscreen_matrix_calc(t_jit_keyscreen *x, void *inputs, void *outputs);
void jit_keyscreen_calculate_ndim(t_jit_keyscreen *x, long dimcount, long *dim, long planecount,
								  t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *in2_minfo, char *bip2, t_jit_matrix_info *in3_minfo, char *bip3, t_jit_matrix_info *out_minfo, char *bop);
t_jit_err jit_keyscreen_init(void);


t_jit_err jit_keyscreen_init(void)
{
	long attrflags=0;
	t_jit_object *attr, *mop;

	_jit_keyscreen_class = jit_class_new("jit_keyscreen",(method)jit_keyscreen_new,(method)jit_keyscreen_free,
										 sizeof(t_jit_keyscreen),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,3,1);
	jit_mop_single_type(mop,_jit_sym_char);
	jit_mop_single_planecount(mop,4);
	jit_class_addadornment(_jit_keyscreen_class,mop);

	//add methods
	jit_class_addmethod(_jit_keyscreen_class, (method)jit_keyscreen_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);


	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;

	CLASS_STICKY_CATEGORY(_jit_keyscreen_class,0,"Behavior");
	CLASS_STICKY_ATTR(_jit_keyscreen_class,"basic",0,"1");

	// mode -- switches keying states
	attr = jit_object_new(_jit_sym_jit_attr_offset,"mode",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_keyscreen,mode));
	jit_class_addattr(_jit_keyscreen_class,attr);
	CLASS_ATTR_LABEL(_jit_keyscreen_class,"mode",0,"Keying Mode");
	CLASS_ATTR_ENUMINDEX3(_jit_keyscreen_class, "mode", 0, "Wrap", "Clip", "Fold");

	// key,target,mask -- switches who gets keyed with whom by whom
	attr = jit_object_new(_jit_sym_jit_attr_offset,"key",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_keyscreen,key));
	jit_class_addattr(_jit_keyscreen_class,attr);
	CLASS_ATTR_LABEL(_jit_keyscreen_class,"key",0,"Key Input");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"target",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_keyscreen,target));
	jit_class_addattr(_jit_keyscreen_class,attr);
	CLASS_ATTR_LABEL(_jit_keyscreen_class,"target",0,"Target Input");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"mask",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_keyscreen,mask));
	jit_class_addattr(_jit_keyscreen_class,attr);
	CLASS_ATTR_LABEL(_jit_keyscreen_class,"mask",0,"Mask Input");

	// red, green, blue, tols -- changes colors and tolerances of the key
	attr = jit_object_new(_jit_sym_jit_attr_offset,"alpha",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_keyscreen,alpha));
	jit_class_addattr(_jit_keyscreen_class,attr);
	CLASS_ATTR_LABEL(_jit_keyscreen_class,"alpha",0,"Alpha");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"red",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_keyscreen,red));
	jit_class_addattr(_jit_keyscreen_class,attr);
	CLASS_ATTR_LABEL(_jit_keyscreen_class,"red",0,"Red");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"green",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_keyscreen,green));
	jit_class_addattr(_jit_keyscreen_class,attr);
	CLASS_ATTR_LABEL(_jit_keyscreen_class,"green",0,"Green");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"blue",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_keyscreen,blue));
	jit_class_addattr(_jit_keyscreen_class,attr);
	CLASS_ATTR_LABEL(_jit_keyscreen_class,"blue",0,"Blue");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"alphatol",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_keyscreen,alphatol));
	jit_class_addattr(_jit_keyscreen_class,attr);
	CLASS_ATTR_LABEL(_jit_keyscreen_class,"alphatol",0,"Alpha Tolerance");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"redtol",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_keyscreen,redtol));
	jit_class_addattr(_jit_keyscreen_class,attr);
	CLASS_ATTR_LABEL(_jit_keyscreen_class,"redtol",0,"Red Tolerance");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"greentol",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_keyscreen,greentol));
	jit_class_addattr(_jit_keyscreen_class,attr);
	CLASS_ATTR_LABEL(_jit_keyscreen_class,"greentol",0,"Green Tolerance");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"bluetol",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_keyscreen,bluetol));
	jit_class_addattr(_jit_keyscreen_class,attr);
	CLASS_ATTR_LABEL(_jit_keyscreen_class,"bluetol",0,"Blue Tolerance");

	CLASS_STICKY_CATEGORY_CLEAR(_jit_keyscreen_class);
	CLASS_STICKY_ATTR_CLEAR(_jit_keyscreen_class, "basic");

	jit_class_register(_jit_keyscreen_class);

	return JIT_ERR_NONE;
}


t_jit_err jit_keyscreen_matrix_calc(t_jit_keyscreen *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock,in2_savelock,in3_savelock,out_savelock;
	t_jit_matrix_info in_minfo,in2_minfo,in3_minfo,out_minfo;
	char *in_bp,*in2_bp,*in3_bp,*out_bp;
	long i,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	void *in_matrix, *in2_matrix, *in3_matrix, *out_matrix;

	in_matrix = jit_object_method(inputs, _jit_sym_getindex, 0);
	in2_matrix = jit_object_method(inputs, _jit_sym_getindex, 1);
	in3_matrix = jit_object_method(inputs, _jit_sym_getindex, 2);
	out_matrix = jit_object_method(outputs,_jit_sym_getindex, 0);

	if (x&&in_matrix&&in2_matrix&&in3_matrix&&out_matrix) {

		in_savelock = (long) jit_object_method(in_matrix,_jit_sym_lock,1);
		in2_savelock = (long) jit_object_method(in2_matrix,_jit_sym_lock,1);
		in3_savelock = (long) jit_object_method(in3_matrix,_jit_sym_lock,1);
		out_savelock = (long) jit_object_method(out_matrix,_jit_sym_lock,1);

		jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
		jit_object_method(in2_matrix,_jit_sym_getinfo,&in2_minfo);
		jit_object_method(in3_matrix,_jit_sym_getinfo,&in3_minfo);
		jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);

		jit_object_method(in_matrix,_jit_sym_getdata,&in_bp);
		jit_object_method(in2_matrix,_jit_sym_getdata,&in2_bp);
		jit_object_method(in3_matrix,_jit_sym_getdata,&in3_bp);
		jit_object_method(out_matrix,_jit_sym_getdata,&out_bp);

		if (!in_bp||!in2_bp||!in3_bp||!out_bp) { err=JIT_ERR_GENERIC; goto out;}

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

		//compatible types?
		if ((in2_minfo.type!=_jit_sym_char)||(in2_minfo.type!=out_minfo.type)) {
			err=JIT_ERR_MISMATCH_TYPE;
			jit_object_post((t_object *)x,"type not ok");
			goto out;
		}

		//compatible planes?
		if ((in2_minfo.planecount!=4)) {
			err=JIT_ERR_MISMATCH_PLANE;
			jit_object_post((t_object *)x,"planes not ok");
			goto out;
		}

		//compatible types?
		if ((in3_minfo.type!=_jit_sym_char)||(in3_minfo.type!=out_minfo.type)) {
			err=JIT_ERR_MISMATCH_TYPE;
			jit_object_post((t_object *)x,"type not ok");
			goto out;
		}

		//compatible planes?
		if ((in3_minfo.planecount!=4)) {
			err=JIT_ERR_MISMATCH_PLANE;
			jit_object_post((t_object *)x,"planes not ok");
			goto out;
		}

		//get dimensions/planecount
		dimcount   = out_minfo.dimcount;
		planecount = out_minfo.planecount;
		for (i=0; i<dimcount; i++) {
			dim[i] = MIN(in_minfo.dim[i],out_minfo.dim[i]);
			dim[i] = MIN(dim[i],in2_minfo.dim[i]);
			dim[i] = MIN(dim[i],in3_minfo.dim[i]);
		}

		//calculate
		jit_parallel_ndim_simplecalc4((method)jit_keyscreen_calculate_ndim,
									  x, dimcount, dim, planecount, &in_minfo, in_bp, &in2_minfo, in2_bp,
									  &in3_minfo, in3_bp, &out_minfo, out_bp,
									  0 /* flags1 */, 0 /* flags2 */, 0 /* flags2 */, 0 /* flags4 */);

	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(out_matrix,_jit_sym_lock,out_savelock);
	jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	jit_object_method(in2_matrix,_jit_sym_lock,in2_savelock);
	jit_object_method(in3_matrix,_jit_sym_lock,in3_savelock);
	return err;
}

//recursive function to handle higher dimension matrices, by processing 2D sections at a time
void jit_keyscreen_calculate_ndim(t_jit_keyscreen *x, long dimcount, long *dim, long planecount,
								  t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *in2_minfo, char *bip2,
								  t_jit_matrix_info *in3_minfo, char *bip3, t_jit_matrix_info *out_minfo, char *bop)
{
	long i,j,i1,j1,width,height, rowoffset, coloffset, rowstep, colstep;
	uchar *ip,*ip2,*ip3,*op,*src3,*src2,*src,*dst,*ksrc,*tsrc,*msrc;
	long kstride,tstride,mstride,ostride;
	long alpha, red, green, blue, af, rf, gf, bf, mode, key, target, mask, check=0;
	long aMf, aPf, rMf, rPf, gMf, gPf, bMf, bPf;

	// get all the struct variables into locals and scale them into integers

	mode = x->mode;

	alpha = x->alpha*255.;
	red = x->red*255.;
	green = x->green*255.;
	blue = x->blue*255.;
	af = x->alphatol*255.;
	rf = x->redtol*255.;
	gf = x->greentol*255.;
	bf = x->bluetol*255.;

	key = x->key;
	target = x->target;
	mask = x->mask;

	aMf = alpha - af;
	aPf = alpha + af;
	rMf = red - rf;
	rPf = red + rf;
	gMf = green - gf;
	gPf = green + gf;
	bMf = blue - bf;
	bPf = blue + bf;


	if (dimcount<1) return; //safety

	switch(dimcount) {
	case 1:
		dim[1]=1;
	case 2:
		width  = dim[0];
		height = dim[1];

		// map the input sources to the right pointers and rowstrides

		ksrc = (key==1) ? bip3 : (key==2) ? bip2 : bip;
		tsrc = (target==0) ? bip : (target==2) ? bip2 : bip3;
		msrc = (mask==0) ? bip : (mask==1) ? bip3 : bip2;

		kstride = (key==1) ? in3_minfo->dimstride[1] : (key==2) ? in2_minfo->dimstride[1] : in_minfo->dimstride[1];
		tstride = (target==0) ? in_minfo->dimstride[1] : (target==2) ? in2_minfo->dimstride[1] : in3_minfo->dimstride[1];
		mstride = (mask==1) ? in_minfo->dimstride[1] : (mask==1) ? in3_minfo->dimstride[1] : in2_minfo->dimstride[1];

		ostride=out_minfo->dimstride[1];

		// which mode of keying?
		switch(mode) {
		case(1): 	// plane-by-plane
			for (i=0; i<height; i++) {
				ip = ksrc + i*kstride;
				ip2 = tsrc + i*tstride;
				ip3 = msrc + i*mstride;
				op = bop + i*ostride;

				for (j=0; j<width; j++,ip+=4,ip2+=4,ip3+=4) { // to key or not to key
					*op++ = (*(ip)>=aMf&&*(ip)<=aPf) ? *ip3 : *ip2;
					*op++ = (*(ip+1)>=rMf&&*(ip+1)<=rPf) ? *(ip3+1) : *(ip2+1);
					*op++ = (*(ip+2)>=gMf&&*(ip+2)<=gPf) ? *(ip3+2) : *(ip2+2);
					*op++ = (*(ip+3)>=bMf&&*(ip+3)<=bPf) ? *(ip3+3) : *(ip2+3);
				}
			}
			break;
		case(0): // cell-by-cell
		default:
			for (i=0; i<height; i++) {
				t_uint32 *op32;

				ip = ksrc + i * kstride;
				ip2 = tsrc + i * tstride;
				ip3 = msrc + i * mstride;
				op = bop + i*ostride;
				op32 = (t_uint32 *)op;

				for (j=0; j<width; j++, ip+=4, ip2+=4,ip3+=4) {
					// see if any of the planes fail any of the criteria, and key accordingly
					*op32++ = (*ip<aMf) ? *((t_uint32 *)ip2) : (*ip>aPf) ? *((t_uint32 *)ip2) : (*(ip+1)<rMf) ? *((t_uint32 *)ip2) : (*(ip+1)>rPf) ? *((t_uint32 *)ip2) : (*(ip+2)<gMf) ? *((t_uint32 *)ip2) : (*(ip+2)>gPf) ? *((t_uint32 *)ip2) : (*(ip+3)<bMf) ? *((t_uint32 *)ip2) : (*(ip+3)>bPf) ? *((t_uint32 *)ip2) : *((t_uint32 *)ip3);
				}
			}
			break;
		}
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			ip = bip + i * in_minfo->dimstride[dimcount-1];
			ip2 = bip2 + i * in2_minfo->dimstride[dimcount-1];
			ip3 = bip3 + i * in3_minfo->dimstride[dimcount-1];
			op = bop + i * out_minfo->dimstride[dimcount-1];
			jit_keyscreen_calculate_ndim(x,dimcount-1,dim,planecount,in_minfo,ip,in2_minfo,ip2,in3_minfo,ip3,out_minfo,op);
		}
	}
}

t_jit_keyscreen *jit_keyscreen_new(void)
{
	t_jit_keyscreen *x;
	short i;

	if (x=(t_jit_keyscreen *)jit_object_alloc(_jit_keyscreen_class)) {
		x->alpha = x->red = x->green = x->blue = x->alphatol = x->redtol = x->greentol = x->bluetol = 0.;
		x->mode = 0;
		x->key = 0;
		x->target = 1;
		x->mask = 2;


	} else {
		x = NULL;
	}
	return x;
}

void jit_keyscreen_free(t_jit_keyscreen *x)
{
	//nada
}


