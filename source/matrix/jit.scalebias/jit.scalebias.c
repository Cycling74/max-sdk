/*
	Copyright 2001 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"

typedef struct _jit_scalebias
{
	t_object				ob;
	long					mode;
	float					scale;
	float					bias;
	float					ascale;
	float					rscale;
	float					gscale;
	float					bscale;
	float					abias;
	float					rbias;
	float					gbias;
	float					bbias;
} t_jit_scalebias;

void *_jit_scalebias_class;

t_jit_err jit_scalebias_init(void);
t_jit_scalebias *jit_scalebias_new(void);
void jit_scalebias_free(t_jit_scalebias *x);
t_jit_err jit_scalebias_matrix_calc(t_jit_scalebias *x, void *inputs, void *outputs);
void jit_scalebias_calculate_ndim(t_jit_scalebias *x, long dimcount, long *dim, long planecount,
								  t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop);
void jit_scalebias_scale(t_jit_scalebias *x, t_symbol *s, long argc, t_atom *argv);
void jit_scalebias_bias(t_jit_scalebias *x, t_symbol *s, long argc, t_atom *argv);

t_jit_err jit_scalebias_init(void)
{
	long attrflags=0;
	t_jit_object *attr,*mop;

	// create our class
	_jit_scalebias_class = jit_class_new("jit_scalebias",(method)jit_scalebias_new,(method)jit_scalebias_free,
										 sizeof(t_jit_scalebias),0L);

	// create a new instance of jit_mop with 1 input, and 1 output
	mop = jit_object_new(_jit_sym_jit_mop,1,1);

	// enforce a single type for all inputs and outputs
	jit_mop_single_type(mop,_jit_sym_char);

	// enforce a single plane count for all inputs and outputs
	jit_mop_single_planecount(mop,4);

	// add our jit_mop object as an adornment to our class
	jit_class_addadornment(_jit_scalebias_class,mop);

	// add methods to our class
	jit_class_addmethod(_jit_scalebias_class, (method)jit_scalebias_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);

	// add attributes to our class
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"mode",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_scalebias,mode));
	jit_attr_addfilterset_clip(attr,0,1,TRUE,TRUE);	//clip to 0-1
	jit_class_addattr(_jit_scalebias_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Mode");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"ascale",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_scalebias,ascale));
	jit_class_addattr(_jit_scalebias_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Alpha Scale\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"rscale",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_scalebias,rscale));
	jit_class_addattr(_jit_scalebias_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Red Scale\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"gscale",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_scalebias,gscale));
	jit_class_addattr(_jit_scalebias_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Green Scale\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"bscale",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_scalebias,bscale));
	jit_class_addattr(_jit_scalebias_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Blue Scale\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"abias",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_scalebias,abias));
	jit_class_addattr(_jit_scalebias_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Alpha Bias\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"rbias",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_scalebias,rbias));
	jit_class_addattr(_jit_scalebias_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Red Scale\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"gbias",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_scalebias,gbias));
	jit_class_addattr(_jit_scalebias_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Green Scale\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"bbias",_jit_sym_float32,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_scalebias,bbias));
	jit_class_addattr(_jit_scalebias_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Blue Scale\"");

	// these attributes set all the channels at once, and are only settable
	attrflags = JIT_ATTR_GET_OPAQUE_USER | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"scale",_jit_sym_float32,attrflags,
						  (method)0L,(method)jit_scalebias_scale,calcoffset(t_jit_scalebias,scale));
	jit_class_addattr(_jit_scalebias_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Scale");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"bias",_jit_sym_float32,attrflags,
						  (method)0L,(method)jit_scalebias_bias,calcoffset(t_jit_scalebias,bias));
	jit_class_addattr(_jit_scalebias_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Bias");
	
	// register our class
	jit_class_register(_jit_scalebias_class);

	return JIT_ERR_NONE;
}

void jit_scalebias_scale(t_jit_scalebias *x, t_symbol *s, long argc, t_atom *argv)
{
	float f;

	f = jit_atom_getfloat(argv);
	x->ascale = f;
	x->rscale = f;
	x->gscale = f;
	x->bscale = f;
}

void jit_scalebias_bias(t_jit_scalebias *x, t_symbol *s, long argc, t_atom *argv)
{
	float f;

	f = jit_atom_getfloat(argv);
	x->abias  = f;
	x->rbias  = f;
	x->gbias  = f;
	x->bbias  = f;
}

t_jit_err jit_scalebias_matrix_calc(t_jit_scalebias *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock,out_savelock;
	t_jit_matrix_info in_minfo,out_minfo;
	char *in_bp,*out_bp;
	long i,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	void *in_matrix,*out_matrix;

	// get the zeroth index input and output from the
	// corresponding input and output lists
	in_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);
	out_matrix 	= jit_object_method(outputs,_jit_sym_getindex,0);

	// if our object and both our input and output matrices
	// are valid, then process, else return an error
	if (x&&in_matrix&&out_matrix)
	{
		// lock our input and output matrices
		in_savelock = (long) jit_object_method(in_matrix,_jit_sym_lock,1);
		out_savelock = (long) jit_object_method(out_matrix,_jit_sym_lock,1);

		// fill out our matrix info structs for our input and output
		jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
		jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);

		// get our matrix data pointers
		jit_object_method(in_matrix,_jit_sym_getdata,&in_bp);
		jit_object_method(out_matrix,_jit_sym_getdata,&out_bp);

		// if our data pointers are invalid, set error, and cleanup
		if (!in_bp) { err=JIT_ERR_INVALID_INPUT; goto out;}
		if (!out_bp) { err=JIT_ERR_INVALID_OUTPUT; goto out;}

		// enforce compatible types
		if ((in_minfo.type!=_jit_sym_char)||(in_minfo.type!=out_minfo.type)) {
			err=JIT_ERR_MISMATCH_TYPE;
			goto out;
		}

		// enforce compatible planecount
		if ((in_minfo.planecount!=4)||(out_minfo.planecount!=4)) {
			err=JIT_ERR_MISMATCH_PLANE;
			goto out;
		}

		// get dimensions/planecount
		dimcount   = out_minfo.dimcount;
		planecount = out_minfo.planecount;
		for (i=0; i<dimcount; i++)
		{
			// if input and output are not matched in
			// size, use the intersection of the two
			dim[i] = MIN(in_minfo.dim[i],out_minfo.dim[i]);
		}

		// calculate, using the parallel utility function to
		// call our calculate_ndim function in multiple
		// threads if there are multiple processors available
		jit_parallel_ndim_simplecalc2((method)jit_scalebias_calculate_ndim,
									  x, dimcount, dim, planecount, &in_minfo, in_bp, &out_minfo, out_bp,
									  0 /* flags1 */, 0 /* flags2 */);

	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	// restore matrix lock state to previous value
	jit_object_method(out_matrix,_jit_sym_lock,out_savelock);
	jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	return err;
}

//recursive function to handle higher dimension matrices, by processing 2D sections at a time
void jit_scalebias_calculate_ndim(t_jit_scalebias *x, long dimcount, long *dim, long planecount,
								  t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop)
{
	long i,j,width,height;
	uchar *ip,*op;
	long ascale,rscale,gscale,bscale;
	long abias,rbias,gbias,bbias,sumbias;
	long tmp;

	if (dimcount<1) return; //safety

	switch(dimcount)
	{
	case 1:
		// if only 1D, interperet as 2D, falling through to 2D case
		dim[1]=1;
	case 2:
		// convert our floating point scale factors to a fixed point int
		ascale = x->ascale*256.;
		rscale = x->rscale*256.;
		gscale = x->gscale*256.;
		bscale = x->bscale*256.;

		// convert our floating point bias values to a fixed point int
		abias  = x->abias*256.;
		rbias  = x->rbias*256.;
		gbias  = x->gbias*256.;
		bbias  = x->bbias*256.;

		// for effiency in sum mode (1), make a single bias value
		sumbias = (x->abias+x->rbias+x->gbias+x->bbias)*256.;

		width  = dim[0];
		height = dim[1];

		// for each row
		for (i=0; i<height; i++)
		{
			// increment our data pointers according to byte stride
			ip = bip + i*in_minfo->dimstride[1];
			op = bop + i*out_minfo->dimstride[1];

			// depending on our
			switch (x->mode) {
			case 1:
				// sum together, clamping to the range 0-255
				// and set all output planes
				for (j=0; j<width; j++) {
					tmp  = (long)(*ip++)*ascale;
					tmp += (long)(*ip++)*rscale;
					tmp += (long)(*ip++)*gscale;
					tmp += (long)(*ip++)*bscale;
					tmp  = (tmp>>8L) + sumbias;
					tmp  = (tmp>255)?255:((tmp<0)?0:tmp);
					*op++ = tmp;
					*op++ = tmp;
					*op++ = tmp;
					*op++ = tmp;
				}
				break;
			default:
				// apply to each plane individually
				// clamping to the range 0-255
				for (j=0; j<width; j++) {
					tmp = (((long)(*ip++)*ascale)>>8L)+abias;
					*op++ = (tmp>255)?255:((tmp<0)?0:tmp);
					tmp = (((long)(*ip++)*rscale)>>8L)+rbias;
					*op++ = (tmp>255)?255:((tmp<0)?0:tmp);
					tmp = (((long)(*ip++)*gscale)>>8L)+gbias;
					*op++ = (tmp>255)?255:((tmp<0)?0:tmp);
					tmp = (((long)(*ip++)*bscale)>>8L)+bbias;
					*op++ = (tmp>255)?255:((tmp<0)?0:tmp);
				}
				break;
			}
		}
		break;
	default:
		// if we are processing higher dimension than 2D,
		// for each lower dimensioned slice, set our
		// base pointer and recursively call this function
		// with decremented dimcount and new base pointers
		for	(i=0; i<dim[dimcount-1]; i++)
		{
			ip = bip + i*in_minfo->dimstride[dimcount-1];
			op = bop + i*out_minfo->dimstride[dimcount-1];
			jit_scalebias_calculate_ndim(x,dimcount-1,dim,planecount,in_minfo,ip,out_minfo,op);
		}
	}
}

t_jit_scalebias *jit_scalebias_new(void)
{
	t_jit_scalebias *x;

	if (x=(t_jit_scalebias *)jit_object_alloc(_jit_scalebias_class)) {
		x->mode   = 0;
		x->ascale = 1.;
		x->rscale = 1.;
		x->gscale = 1.;
		x->bscale = 1.;
		x->abias  = 0.;
		x->rbias  = 0.;
		x->gbias  = 0.;
		x->bbias  = 0.;
	} else {
		x = NULL;
	}
	return x;
}

void jit_scalebias_free(t_jit_scalebias *x)
{
	//nada
}
