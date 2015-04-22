/*
	Copyright 2000-2001 - Cycling '74 / The Trustees of Columbia University in the City of New York
	R. Luke DuBois luke@music.columbia.edu
*/

// updated for new architecture by rld, 2/23/02

/*
 * jit.eclipse does two-source meta-imaging using an algorithm developed at the Computer Music Center,
 * Columbia University by R. Luke DuBois and Mark McNamara.  simply put, it divides an image (in this
 * case, a 4-plane char matrix sent into the left inlet) into a grid with a specified number of rows and
 * columns.  each box in the grid contains a representation of the overall image.  each box is then tinted
 * so that the overall image resembles a second image (sent into the right inlet as a matrix).  if the
 * same image is used in both inputs, the result is a self-similar (or meta-) image.
 *
 * additional features such as threshold inversion, scalar tinting, and a choice of additive (the default)
 * or multiplicative tinting are supported.  there are also four modes which switch between color and
 * monochrome treatment of the two matrices.
 *
 * thanks are due to Jeremy Bernstein for helping me sort out boundary conditions for the object.
 *
 */

#include "jit.common.h"

typedef struct _jit_eclipse
{
	t_object				ob;
	long					mode, tint, inv, rows, columns, oper;
	float					red, green, blue, thresh;
} t_jit_eclipse;

void *_jit_eclipse_class;

t_jit_eclipse *jit_eclipse_new(void);
void jit_eclipse_free(t_jit_eclipse *x);
t_jit_err jit_eclipse_matrix_calc(t_jit_eclipse *x, void *inputs, void *outputs);
void jit_eclipse_calculate_ndim(t_jit_eclipse *x, long dimcount, long *dim, long planecount,
								t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *in2_minfo, char *bip2, t_jit_matrix_info *out_minfo, char *bop);
t_jit_err jit_eclipse_init(void);


t_jit_err jit_eclipse_init(void)
{
	long attrflags=0;
	t_jit_object *attr, *mop;

	_jit_eclipse_class = jit_class_new("jit_eclipse",(method)jit_eclipse_new,(method)jit_eclipse_free,
									   sizeof(t_jit_eclipse),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,2,1);
	jit_mop_single_type(mop,_jit_sym_char);
	jit_mop_single_planecount(mop,4);
	jit_class_addadornment(_jit_eclipse_class,mop);

	//add methods
	jit_class_addmethod(_jit_eclipse_class, (method)jit_eclipse_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);

	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;

	CLASS_STICKY_CATEGORY(_jit_eclipse_class,0,"Behavior");
	CLASS_STICKY_ATTR(_jit_eclipse_class,"basic",0,"1");

	// mode -- switches eclipsing states
	attr = jit_object_new(_jit_sym_jit_attr_offset,"mode",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_eclipse,mode));
	jit_class_addattr(_jit_eclipse_class,attr);
	CLASS_ATTR_LABEL(_jit_eclipse_class,"mode",0,"Eclipse Mode");
	CLASS_ATTR_ENUMINDEX4(_jit_eclipse_class, "mode", 0, "Color Tint Color Frames", "Color Tint Monochrome Frames", "Monochrome Tint Color Frames", "Monochrome Tint Monochrome Frames");

	// rows, columns -- changes eclipse resolution
	attr = jit_object_new(_jit_sym_jit_attr_offset,"rows",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_eclipse,rows));
	jit_class_addattr(_jit_eclipse_class,attr);
	CLASS_ATTR_LABEL(_jit_eclipse_class,"rows",0,"Rows");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"columns",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_eclipse,columns));
	jit_class_addattr(_jit_eclipse_class,attr);
	CLASS_ATTR_LABEL(_jit_eclipse_class,"columns",0,"Columns");

	// red, green, blue, thresh -- changes eclipse behavior within the state
	attr = jit_object_new(_jit_sym_jit_attr_offset,"red",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_eclipse,red));
	jit_class_addattr(_jit_eclipse_class,attr);
	CLASS_ATTR_LABEL(_jit_eclipse_class,"red",0,"Red Tinting");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"green",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_eclipse,green));
	jit_class_addattr(_jit_eclipse_class,attr);
	CLASS_ATTR_LABEL(_jit_eclipse_class,"green",0,"Green Tinting");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"blue",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_eclipse,blue));
	jit_class_addattr(_jit_eclipse_class,attr);
	CLASS_ATTR_LABEL(_jit_eclipse_class,"blue",0,"Blue Tinting");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"thresh",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_eclipse,thresh));
	jit_class_addattr(_jit_eclipse_class,attr);
	CLASS_ATTR_LABEL(_jit_eclipse_class,"thresh",0,"Threshold");

	// tint, inv -- whether eclipse tints and inverts or not
	attr = jit_object_new(_jit_sym_jit_attr_offset,"tint",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_eclipse,tint));
	jit_class_addattr(_jit_eclipse_class,attr);
	CLASS_ATTR_STYLE_LABEL(_jit_eclipse_class,"tint",0,"onoff","Tint");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"inv",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_eclipse,inv));
	jit_class_addattr(_jit_eclipse_class,attr);
	CLASS_ATTR_STYLE_LABEL(_jit_eclipse_class,"inv",0,"onoff","Invert");

	// op -- 0 is add, 1 is multiply
	attr = jit_object_new(_jit_sym_jit_attr_offset,"op",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_eclipse,oper));
	jit_class_addattr(_jit_eclipse_class,attr);
	CLASS_ATTR_LABEL(_jit_eclipse_class,"op",0,"Operator");
	CLASS_ATTR_ENUMINDEX2(_jit_eclipse_class, "op", 0, "Add", "Multiply");

	CLASS_STICKY_CATEGORY_CLEAR(_jit_eclipse_class);
	CLASS_STICKY_ATTR_CLEAR(_jit_eclipse_class, "basic");

	jit_class_register(_jit_eclipse_class);

	return JIT_ERR_NONE;
}


t_jit_err jit_eclipse_matrix_calc(t_jit_eclipse *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock,in2_savelock,out_savelock;
	t_jit_matrix_info in_minfo,in2_minfo,out_minfo;
	char *in_bp,*in2_bp,*out_bp;
	long i,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	void *in_matrix, *in2_matrix, *out_matrix;

	in_matrix = jit_object_method(inputs, _jit_sym_getindex, 0);
	in2_matrix = jit_object_method(inputs, _jit_sym_getindex, 1);
	out_matrix = jit_object_method(outputs,_jit_sym_getindex, 0);

	if (x&&in_matrix&&in2_matrix&&out_matrix) {

		in_savelock = (long) jit_object_method(in_matrix,_jit_sym_lock,1);
		in2_savelock = (long) jit_object_method(in2_matrix,_jit_sym_lock,1);
		out_savelock = (long) jit_object_method(out_matrix,_jit_sym_lock,1);

		jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
		jit_object_method(in2_matrix,_jit_sym_getinfo,&in2_minfo);
		jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);

		jit_object_method(in_matrix,_jit_sym_getdata,&in_bp);
		jit_object_method(in2_matrix,_jit_sym_getdata,&in2_bp);
		jit_object_method(out_matrix,_jit_sym_getdata,&out_bp);

		if (!in_bp) { err=JIT_ERR_GENERIC; goto out;}
		if (!in2_bp) { err=JIT_ERR_GENERIC; goto out;}
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


		//get dimensions/planecount
		dimcount   = out_minfo.dimcount;
		planecount = out_minfo.planecount;
		for (i=0; i<dimcount; i++) {
			dim[i] = MIN(in_minfo.dim[i],out_minfo.dim[i]);
		}

		//calculate
		jit_eclipse_calculate_ndim(x, dimcount, dim, planecount, &in_minfo, in_bp, &in2_minfo, in2_bp, &out_minfo, out_bp);

	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(out_matrix,_jit_sym_lock,out_savelock);
	jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	jit_object_method(in2_matrix,_jit_sym_lock,in2_savelock);
	return err;
}

//recursive function to handle higher dimension matrices, by processing 2D sections at a time
void jit_eclipse_calculate_ndim(t_jit_eclipse *x, long dimcount, long *dim, long planecount,
								t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *in2_minfo, char *bip2, t_jit_matrix_info *out_minfo, char *bop)
{
	long i,j,i1,j1,width,height, c, r, redpix, bluepix, greenpix, r2, b2, g2, rowoffset, coloffset, cut=0, flip=0, rowstep, colstep, pixavg;
	uchar *ip,*ip2,*op,*src2,*src,*dst;
	long tmp;
	long red, green, blue, thresh, mode, tint, inv, rows, columns, oper, eek;

	// get all the struct variables into locals and scale them into integers
	mode = x->mode;
	red = x->red*255.;
	green = x->green*255.;
	blue = x->blue*255.;
	thresh = x->thresh*255.;
	tint = x->tint;
	inv = x->inv;
	eek = x->rows;
	rows = CLAMP(eek, 1, dim[1]);
	eek = x->columns;
	columns = CLAMP(eek, 1, dim[0]);
	oper = x->oper;

	if (dimcount<1) return; //safety

	switch(dimcount) {
	case 1:
		dim[1]=1;
	case 2:

		width  = dim[0];
		height = dim[1];

		// sort out the row/column offset shit

		// fixed round-off bug... 10/4/03 -- rld
		rowstep = (((float)height/rows)+.5);
		colstep = (((float)width/columns)+.5);

		if ( rows > (height * .1) )
			rowoffset = rows - (height * .1);
		else
			rowoffset = 1;

		if ( columns > (width * .1) )
			coloffset = columns - (width * .1);
		else
			coloffset = 1;


		// do we flip?
		if (thresh<0) flip = 1; else flip = 0;
		if(thresh<0) thresh=thresh*-1;


		for (r = 0; r <= ( rows + rowoffset ); r++ )
		{
			for(i = 0, i1 = ( r * rowstep ); i < height; i+=rows, i1++)
			{
				ip = bip + i*in_minfo->dimstride[1];
				ip2 = bip2 + i*in2_minfo->dimstride[1];
				op = bop + i1*out_minfo->dimstride[1];

				for ( c = 0; c <= columns+coloffset; c++ )
				{
					cut = 0;
					src2 = bip2 + (in2_minfo->dimstride[1] * r * rowstep) + (c*colstep*4);
					if(mode==0 || mode==1) { // color tints
						r2 = *(src2+1); // red, green, blue
						g2 = *(src2+2);
						b2 = *(src2+3);
					}
					else { // monochrome tints
						r2 = g2 = b2 = (*(src2+1) + *(src2+2) + *(src2+3))/3;
					}
					if (((r2+g2+b2)/3)>=thresh) cut = 1;
					if (!tint) r2=g2=b2=0;

					for(j = 0, j1 = c * colstep; j < width; j+=columns, j1++)
					{
						if ( j1 >= width )
							goto dink;

						if ( i1 >= height )
							goto yoink;

						src = ip + ( 4 * j );
						dst = op + ( 4 * j1 );
						pixavg = (*(src+1) + *(src+2) + *(src+3))/3;
						if (mode==0 || mode==2) { // color pixels
							if ((cut && !flip) || (!cut && flip)) {
								if (!oper) {
									redpix = *(src+1) + r2 + red;
									greenpix = *(src+2) + g2 + green;
									bluepix = *(src+3) + + b2 + blue;
								}
								else {
									redpix = ((*(src+1) * (r2+red))>>8L);
									greenpix = ((*(src+2) * (g2+green))>>8L);
									bluepix = ((*(src+3) * + (b2+blue))>>8L);
								}
							}
							else {
								if (!inv) {
									if (!oper) {
										redpix = 255 - *(src+1) + r2 + red;
										greenpix = 255 - *(src+2) + g2 + green;
										bluepix = 255 - *(src+3) + b2 + blue;
									}
									else {
										redpix = (((255 - *(src+1)) * (r2+red))>>8L);
										greenpix = (((255 - *(src+2)) * (g2+green))>>8L);
										bluepix = (((255 - *(src+3)) * (b2+blue))>>8L);
									}
								}
								else {
									if (!oper) {
										redpix = 255 - *(src+1) + r2 - red;
										greenpix = 255 - *(src+2) + g2 - green;
										bluepix = 255 - *(src+3) + b2 - blue;
									}
									else {
										redpix = (((255 - *(src+1)) * (r2-red))>>8L);
										greenpix = (((255 - *(src+2)) * (g2-green))>>8L);
										bluepix = (((255 - *(src+3)) * (b2-blue))>>8L);
									}
								}
							}
						}
						else { // monochrome pixels
							if ((cut && !flip) || (!cut && flip)) {
								if (!oper) {
									redpix = pixavg + r2 + red;
									greenpix = pixavg + g2 + green;
									bluepix = pixavg + + b2 + blue;
								}
								else {
									redpix = ((pixavg * (r2+red))>>8L);
									greenpix = ((pixavg * (g2+green))>>8L);
									bluepix = ((pixavg * + (b2+blue))>>8L);
								}
							}
							else {
								if (!inv) {
									if (!oper) {
										redpix = 255 - pixavg + r2 + red;
										greenpix = 255 - pixavg + g2 + green;
										bluepix = 255 - pixavg + + b2 + blue;
									}
									else {
										redpix = (((255 - pixavg) * (r2+red))>>8L);
										greenpix = (((255 - pixavg) * (g2+green))>>8L);
										bluepix = (((255 - pixavg) * (b2+blue))>>8L);
									}
								}
								else {
									if (!oper) {
										redpix = 255 - pixavg + r2 - red;
										greenpix = 255 - pixavg + g2 - green;
										bluepix = 255 - pixavg + b2 - blue;
									}
									else {
										redpix = (((255 - pixavg) * (r2-red))>>8L);
										greenpix = (((255 - pixavg) * (g2-green))>>8L);
										bluepix = (((255 - pixavg) * (b2-blue))>>8L);
									}
								}
							}
						}
						*dst = *ip;
						*++dst = CLAMP(redpix,0,255);
						*++dst = CLAMP(greenpix,0,255);
						*++dst = CLAMP(bluepix,0,255);

					}
				}
dink:
				;
			}
		}

yoink:
		;

		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			ip = bip + i*in_minfo->dimstride[dimcount-1];
			op = bop + i*out_minfo->dimstride[dimcount-1];
			jit_eclipse_calculate_ndim(x,dimcount-1,dim,planecount,in_minfo,ip,in2_minfo,bip2,out_minfo,op);
		}
	}
}

t_jit_eclipse *jit_eclipse_new(void)
{
	t_jit_eclipse *x;
	short i;

	if (x=(t_jit_eclipse *)jit_object_alloc(_jit_eclipse_class)) {
		x->red = x->green = x->blue = 0.;
		x->thresh = -1.01;
		x->rows = 1;
		x->columns=1;
		x->inv = 0;
		x->tint = 1; // fixed -- 6/8/02
		x->mode = 0;
		x->oper = 0;



	} else {
		x = NULL;
	}
	return x;
}

void jit_eclipse_free(t_jit_eclipse *x)
{
	//nada
}


