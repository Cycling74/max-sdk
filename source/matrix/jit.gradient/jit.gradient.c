/*
	Copyright 2001 - Cycling '74
	R. Luke DuBois luke@music.columbia.edu
*/

#include "jit.common.h"
#include "math.h"

typedef struct _jit_gradient
{
	t_object				ob;
	long					startcount, endcount, chebycount;
	double					start[4], end[4], cheby[64];
} t_jit_gradient;

void *_jit_gradient_class;

t_jit_gradient *jit_gradient_new(void);
void jit_gradient_free(t_jit_gradient *x);
t_jit_err jit_gradient_matrix_calc(t_jit_gradient *x, void *inputs, void *outputs);
void jit_gradient_calculate_ndim(t_jit_gradient *x, long dimcount, long *dim, long planecount,
								 t_jit_matrix_info *out_minfo, char *bop);
t_jit_err jit_gradient_init(void);


t_jit_err jit_gradient_init(void)
{
	long attrflags=0;
	t_jit_object *attr;
	t_jit_object *mop;

	_jit_gradient_class = jit_class_new("jit_gradient",(method)jit_gradient_new,(method)jit_gradient_free,
										sizeof(t_jit_gradient),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,1);
	jit_mop_single_type(mop, _jit_sym_char);
	jit_mop_single_planecount(mop, 4);
	jit_class_addadornment(_jit_gradient_class,mop);
	//add methods
	jit_class_addmethod(_jit_gradient_class, (method)jit_gradient_matrix_calc, "matrix_calc", A_CANT, 0L);

	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;

	CLASS_STICKY_CATEGORY(_jit_gradient_class,0,"Behavior");
	CLASS_STICKY_ATTR(_jit_gradient_class,"basic",0,"1");

	// start - beginning gradient cell
	attr = jit_object_new(_jit_sym_jit_attr_offset_array, "start", _jit_sym_float64, 4,
						  attrflags, (method)0L, (method)0L, calcoffset(t_jit_gradient, startcount),
						  calcoffset(t_jit_gradient,start));
	jit_class_addattr(_jit_gradient_class,attr);
	CLASS_ATTR_LABEL(_jit_gradient_class,"start",0,"Start");

	attr = jit_object_new(_jit_sym_jit_attr_offset_array, "end", _jit_sym_float64, 4,
						  attrflags, (method)0L, (method)0L, calcoffset(t_jit_gradient, endcount),
						  calcoffset(t_jit_gradient,end));
	jit_class_addattr(_jit_gradient_class,attr);
	CLASS_ATTR_LABEL(_jit_gradient_class,"end",0,"End");

	attr = jit_object_new(_jit_sym_jit_attr_offset_array, "cheby", _jit_sym_float64, 64,
						  attrflags, (method)0L, (method)0L, calcoffset(t_jit_gradient, chebycount),
						  calcoffset(t_jit_gradient,cheby));
	jit_class_addattr(_jit_gradient_class,attr);
	CLASS_ATTR_LABEL(_jit_gradient_class,"cheby",0,"Chebyshev Coefficients");

	CLASS_STICKY_CATEGORY_CLEAR(_jit_gradient_class);
	CLASS_STICKY_ATTR_CLEAR(_jit_gradient_class, "basic");

	jit_class_register(_jit_gradient_class);

	return JIT_ERR_NONE;
}


t_jit_err jit_gradient_matrix_calc(t_jit_gradient *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long out_savelock, dimmode;
	t_jit_matrix_info out_minfo;
	char *out_bp;
	long i,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	void *out_matrix;

	out_matrix 	= jit_object_method(outputs,_jit_sym_getindex,0);

	if (x && out_matrix) {

		out_savelock = (long) jit_object_method(out_matrix,_jit_sym_lock,1);
		jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);
		jit_object_method(out_matrix,_jit_sym_getdata,&out_bp);

		if (!out_bp) { err=JIT_ERR_INVALID_OUTPUT; goto out;}

		//get dimensions/planecount
		dimcount   = out_minfo.dimcount;
		planecount = out_minfo.planecount;
		for (i=0; i<dimcount; i++) {
			dim[i] = out_minfo.dim[i];
		}

		//calculate

		jit_gradient_calculate_ndim(x, dimcount, dim, planecount, &out_minfo, out_bp);

	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(out_matrix,_jit_sym_lock,out_savelock);
	return err;
}

//
//recursive functions to handle higher dimension matrices, by processing 2D sections at a time
//

// jit_gradient_calculate_ndim() -- when x->dimmode==-1, sorts both dimensions together
void jit_gradient_calculate_ndim(t_jit_gradient *x, long dimcount, long *dim, long planecount,
								 t_jit_matrix_info *out_minfo, char *bop)
{
	long i,j,width,height, index;
	long start[4], end[4], chebycount;
	float indperc;
	double cheby[64], *table=NULL;
	float Tn, Tn1, Tn2, v,d;
	float wmax, xmax=0.0;
	uchar *op;
	t_uint32 *lp1,*lp2;

	start[0] = x->start[0]*255.;
	start[1] = x->start[1]*255.;
	start[2] = x->start[2]*255.;
	start[3] = x->start[3]*255.;
	end[0] = x->end[0]*255.;
	end[1] = x->end[1]*255.;
	end[2] = x->end[2]*255.;
	end[3] = x->end[3]*255.;

	chebycount = x->chebycount;
	for(i=0; i<chebycount; i++) {
		cheby[i] = x->cheby[i];
	}

	if (dimcount<1) return; //safety

	switch(dimcount) {
	case 1:
		dim[1]=1;
	case 2:

		width  = dim[0];
		height = dim[1];
        table = (double *)sysmem_newptr(width*sizeof(double));
            
		// compute the transfer function using the chebyshev equation...
		d=(float)(width/2-.5);
		for(i=0; i<width; i++) {
			v=(i/d-1.);
			table[i]=0.;
			Tn1=1;
			Tn=v;
			for(j=0; j<chebycount; j++) {
				table[i]=cheby[j]*Tn+table[i];
				Tn2=Tn1;
				Tn1=Tn;
				Tn=2*v*Tn1-Tn2;
			}
			if ((wmax = fabs(table[i])) > xmax) xmax = wmax;
		}

		for(j = 0; j < width; j++) {
			table[j] /= xmax;
			table[j] = ((table[j]+1.)/2.);
		}


		for (i=0; i<height; i++) {
			op = bop + i*out_minfo->dimstride[1];
			if (i>0) {
				lp1 = (t_uint32 *) bop;
				lp2 = (t_uint32 *) op;
				for (j=0; j<width; j++) {
					*lp2++ = *lp1++;
				}
			} else {
				for (j=0; j<width; j++) {

					if(start[0]<end[0]) {
						*op++ = (table[j]*(end[0]-start[0]))+start[0];
					}
					else {
						*op++ = ((1.-table[j])*(start[0]-end[0]))+end[0];
					}
					if(start[1]<end[1]) {
						*op++ = (table[j]*(end[1]-start[1]))+start[1];
					}
					else {
						*op++ = ((1.-table[j])*(start[1]-end[1]))+end[1];
					}
					if(start[2]<end[2]) {
						*op++ = (table[j]*(end[2]-start[2]))+start[2];
					}
					else {
						*op++ = ((1.-table[j])*(start[2]-end[2]))+end[2];
					}
					if(start[3]<end[3]) {
						*op++ = (table[j]*(end[3]-start[3]))+start[3];
					}
					else {
						*op++ = ((1.-table[j])*(start[3]-end[3]))+end[3];
					}

ick1:
					;

				}
			}
		}
        if (table)
            sysmem_freeptr((void *)table);
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			op = bop + i*out_minfo->dimstride[dimcount-1];
			jit_gradient_calculate_ndim(x,dimcount-1,dim,planecount,out_minfo,op);
		}
	}

}


t_jit_gradient *jit_gradient_new(void)
{
	t_jit_gradient *x;
	short i;

	if (x=(t_jit_gradient *)jit_object_alloc(_jit_gradient_class)) {
		x->start[0] = 0.;
		x->start[1] = 0.;
		x->start[2] = 0.;
		x->start[3] = 0.; // defaults to black
		x->startcount = 4;
		x->end[0] = 1.;
		x->end[1] = 1.;
		x->end[2] = 1.;
		x->end[3] = 1.; // defaults to white
		x->endcount = 4;
		x->chebycount = 1;
		x->cheby[0] = 1.;
		for(i=1; i<64; i++) {
			x->cheby[i] = 0.;
		}
	} else {
		x = NULL;
	}
	return x;
}

void jit_gradient_free(t_jit_gradient *x)
{
	//nada
}

