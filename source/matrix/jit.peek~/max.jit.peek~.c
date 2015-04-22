/*
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/


// 03.08.05 -- added normalize attribute.  rld.

#include "jit.common.h"
#include "ext_atomic.h"
#include "z_dsp.h"

typedef struct _max_jit_peek
{
	t_pxobject			ob;
	void				*obex;
	t_symbol			*matrix_name;
	long				dimcount;
	long				plane;
	long				interp;
	float				*vectors[JIT_MATRIX_MAX_DIMCOUNT+1];
	t_int32_atomic		inperform;
	long				mvalid;
	char				*mdata;
	long				normalize;
	t_jit_matrix_info	minfo;
} t_max_jit_peek;

void *max_jit_peek_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_peek_free(t_max_jit_peek *x);
void max_jit_peek_assist(t_max_jit_peek *x, void *b, long m, long a, char *s);
void max_jit_peek_notify(t_max_jit_peek *x, t_symbol *s, t_symbol *msg, void *ob, void *data);
void max_jit_peek_matrix_name(t_max_jit_peek *x, void *attr, long argc, t_atom *argv);
void max_jit_peek_update(t_max_jit_peek *x);
void max_jit_peek_dsp(t_max_jit_peek *x, t_signal **sp, short *count);
void max_jit_peek_dsp64(t_max_jit_peek *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
t_int *max_jit_peek_perform(t_int *w);

float recursive_interp(char *bp, long dimcount, t_jit_matrix_info *minfo, long *dim_int, float *dim_frak);

void *max_jit_peek_class;

t_symbol *ps_done;

void ext_main(void *r)
{
	long attrflags;
	void *p,*attr;

	setup((t_messlist **)&max_jit_peek_class, (method)max_jit_peek_new, (method)max_jit_peek_free, (short)sizeof(t_max_jit_peek),
		  0L, A_GIMME, 0);

	addmess((method)max_jit_peek_dsp, "dsp", A_CANT, 0);
	addmess((method)max_jit_peek_dsp64, "dsp64", A_CANT, 0);
	dsp_initclass();

	p = max_jit_classex_setup(calcoffset(t_max_jit_peek,obex));

	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW ;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"matrix_name",_jit_sym_symbol,attrflags,
						  (method)0L,(method)max_jit_peek_matrix_name,calcoffset(t_max_jit_peek,matrix_name));
	max_jit_classex_addattr(p,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Matrix Name\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"plane",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_max_jit_peek,plane));
	max_jit_classex_addattr(p,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Plane");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"interp",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_max_jit_peek,interp));
	max_jit_classex_addattr(p,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Interp");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"normalize",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_max_jit_peek,normalize));
	max_jit_classex_addattr(p,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Normalize");

	// because it is not safe to call jitter methods inside the perform routine,
	// we need notify message to find out when our matrix data is changing
	addmess((method)max_jit_peek_notify, "notify", A_CANT,0);

	max_jit_classex_standard_wrap(p,NULL,0);
	addmess((method)max_jit_peek_assist, "assist", A_CANT,0);
	return 0;
}

t_int *max_jit_peek_perform(t_int *w)
{
	t_max_jit_peek *x = (t_max_jit_peek *)(w[1]);
	long n = (int)(w[2]);
	long i,j,dimcount;
	char *bp,*p;
	float *out_val=x->vectors[0];
	float **in_dim=x->vectors+1;
	long tmp,outofbounds,typesize;
	long dim_int[JIT_MATRIX_MAX_DIMCOUNT];
	float dim_frak[JIT_MATRIX_MAX_DIMCOUNT];
	long mult[JIT_MATRIX_MAX_DIMCOUNT]; // added to perform routine for normalization

	ATOMIC_INCREMENT(&x->inperform);

	if (x->ob.z_disabled)
		goto out;

	if (x->mvalid&&x->mdata) {

		bp = x->mdata;

		if ((!bp)||(x->plane>=x->minfo.planecount)||(x->plane<0)) {
			goto zero;
		}

		dimcount = MIN(x->dimcount,x->minfo.dimcount);

		if (x->normalize) // set the multiplication factor for the input vectors to the matrix dim if 'normalize' is 1
		{
			for(j=0; j<dimcount; j++)
			{
				mult[j]=(x->minfo.dim[j]-1);
			}

		}
		else
		{
			for(j=0; j<dimcount; j++)
			{
				mult[j] = 1;
			}
		}


		if (x->interp) {
			if (x->minfo.type==_jit_sym_char) {
				typesize = 1;
			} else if (x->minfo.type==_jit_sym_long) {
				typesize = 4;
			} else if (x->minfo.type==_jit_sym_float32) {
				typesize = 4;
			} else if (x->minfo.type==_jit_sym_float64) {
				typesize = 8;
			}
			bp += x->plane*typesize;


			for (i=0; i<n; i++) {
				for (j=0; j<dimcount; j++) {
					dim_int[j] = in_dim[j][i]*mult[j];
					dim_frak[j] = in_dim[j][i]*mult[j] - (float) dim_int[j];
					dim_int[j] = dim_int[j]%x->minfo.dim[j];
				}

				*out_val++ = recursive_interp(bp,dimcount,&x->minfo,dim_int,dim_frak);

			}

		}
		else {
			if (x->minfo.type==_jit_sym_char) {
				bp += x->plane;
				for (i=0; i<n; i++) {
					p = bp;
					outofbounds = FALSE;
					for (j=0; j<dimcount; j++) {
						tmp = in_dim[j][i]*mult[j];
						if ((tmp<0)||(tmp>=x->minfo.dim[j])) {
							outofbounds = TRUE;
						}
						p += tmp * x->minfo.dimstride[j];
					}
					if (outofbounds) {
						*out_val++ = 0.;
					} else {
						*out_val++ = (float)(*((uchar *)p)) * (1./255.);
					}
				}
			} else if (x->minfo.type==_jit_sym_long) {
				bp += x->plane*4;
				for (i=0; i<n; i++) {
					p = bp;
					outofbounds = FALSE;
					for (j=0; j<dimcount; j++) {
						tmp = in_dim[j][i]*mult[j];
						if ((tmp<0)||(tmp>=x->minfo.dim[j])) {
							outofbounds = TRUE;
						}
						p += tmp * x->minfo.dimstride[j];
					}
					if (outofbounds) {
						*out_val++ = 0.;
					} else {
						*out_val++ = (float)(*((t_int32 *)p));
					}
				}
			} else if (x->minfo.type==_jit_sym_float32) {
				bp += x->plane*4;
				for (i=0; i<n; i++) {
					p = bp;
					outofbounds = FALSE;
					for (j=0; j<dimcount; j++) {
						tmp = in_dim[j][i]*mult[j];
						if ((tmp<0)||(tmp>=x->minfo.dim[j])) {
							outofbounds = TRUE;
						}
						p += tmp * x->minfo.dimstride[j];
					}
					if (outofbounds) {
						*out_val++ = 0.;
					} else {
						*out_val++ = (*((float *)p));
					}
				}
			} else if (x->minfo.type==_jit_sym_float64) {
				bp += x->plane*8;
				for (i=0; i<n; i++) {
					p = bp;
					outofbounds = FALSE;
					for (j=0; j<dimcount; j++) {
						tmp = in_dim[j][i]*mult[j];
						if ((tmp<0)||(tmp>=x->minfo.dim[j])) {
							outofbounds = TRUE;
						}
						p += tmp * x->minfo.dimstride[j];
					}
					if (outofbounds) {
						*out_val++ = 0.;
					} else {
						*out_val++ = (float)(*((double *)p));
					}
				}
			}

		}
	}

out:
	ATOMIC_DECREMENT(&x->inperform);
	return (w+3);

zero:
	while (n--) *out_val++ = 0.;
	ATOMIC_DECREMENT(&x->inperform);
	return (w+3);
}

void max_jit_peek_perform64(t_max_jit_peek *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	long n = sampleframes;
	long i,j,dimcount;
	char *bp,*p;
	//float *out_val=x->vectors[0];
	double *out_val = outs[0];
	//float **in_dim=x->vectors+1;
	double **in_dim = ins;
	long tmp,outofbounds,typesize;
	long dim_int[JIT_MATRIX_MAX_DIMCOUNT];
	float dim_frak[JIT_MATRIX_MAX_DIMCOUNT];
	long mult[JIT_MATRIX_MAX_DIMCOUNT]; // added to perform routine for normalization

	ATOMIC_INCREMENT(&x->inperform);

	if (x->mvalid&&x->mdata) {

		bp = x->mdata;

		if ((!bp)||(x->plane>=x->minfo.planecount)||(x->plane<0)) {
			goto zero;
		}

		dimcount = MIN(x->dimcount,x->minfo.dimcount);

		if (x->normalize) // set the multiplication factor for the input vectors to the matrix dim if 'normalize' is 1
		{
			for(j=0; j<dimcount; j++)
			{
				mult[j]=(x->minfo.dim[j]-1);
			}

		}
		else
		{
			for(j=0; j<dimcount; j++)
			{
				mult[j] = 1;
			}
		}


		if (x->interp) {
			if (x->minfo.type==_jit_sym_char) {
				typesize = 1;
			} else if (x->minfo.type==_jit_sym_long) {
				typesize = 4;
			} else if (x->minfo.type==_jit_sym_float32) {
				typesize = 4;
			} else if (x->minfo.type==_jit_sym_float64) {
				typesize = 8;
			}
			bp += x->plane*typesize;


			for (i=0; i<n; i++) {
				for (j=0; j<dimcount; j++) {
					dim_int[j] = in_dim[j][i]*mult[j];
					dim_frak[j] = in_dim[j][i]*mult[j] - (float) dim_int[j];
					dim_int[j] = dim_int[j]%x->minfo.dim[j];
				}

				*out_val++ = recursive_interp(bp,dimcount,&x->minfo,dim_int,dim_frak);

			}

		}
		else {
			if (x->minfo.type==_jit_sym_char) {
				bp += x->plane;
				for (i=0; i<n; i++) {
					p = bp;
					outofbounds = FALSE;
					for (j=0; j<dimcount; j++) {
						tmp = in_dim[j][i]*mult[j];
						if ((tmp<0)||(tmp>=x->minfo.dim[j])) {
							outofbounds = TRUE;
						}
						p += tmp * x->minfo.dimstride[j];
					}
					if (outofbounds) {
						*out_val++ = 0.;
					} else {
						*out_val++ = (float)(*((uchar *)p)) * (1./255.);
					}
				}
			} else if (x->minfo.type==_jit_sym_long) {
				bp += x->plane*4;
				for (i=0; i<n; i++) {
					p = bp;
					outofbounds = FALSE;
					for (j=0; j<dimcount; j++) {
						tmp = in_dim[j][i]*mult[j];
						if ((tmp<0)||(tmp>=x->minfo.dim[j])) {
							outofbounds = TRUE;
						}
						p += tmp * x->minfo.dimstride[j];
					}
					if (outofbounds) {
						*out_val++ = 0.;
					} else {
						*out_val++ = (float)(*((t_int32 *)p));
					}
				}
			} else if (x->minfo.type==_jit_sym_float32) {
				bp += x->plane*4;
				for (i=0; i<n; i++) {
					p = bp;
					outofbounds = FALSE;
					for (j=0; j<dimcount; j++) {
						tmp = in_dim[j][i]*mult[j];
						if ((tmp<0)||(tmp>=x->minfo.dim[j])) {
							outofbounds = TRUE;
						}
						p += tmp * x->minfo.dimstride[j];
					}
					if (outofbounds) {
						*out_val++ = 0.;
					} else {
						*out_val++ = (*((float *)p));
					}
				}
			} else if (x->minfo.type==_jit_sym_float64) {
				bp += x->plane*8;
				for (i=0; i<n; i++) {
					p = bp;
					outofbounds = FALSE;
					for (j=0; j<dimcount; j++) {
						tmp = in_dim[j][i]*mult[j];
						if ((tmp<0)||(tmp>=x->minfo.dim[j])) {
							outofbounds = TRUE;
						}
						p += tmp * x->minfo.dimstride[j];
					}
					if (outofbounds) {
						*out_val++ = 0.;
					} else {
						*out_val++ = (float)(*((double *)p));
					}
				}
			}

		}
	}

	ATOMIC_DECREMENT(&x->inperform);
	return;

zero:
	while (n--)
		*out_val++ = 0.;
	ATOMIC_DECREMENT(&x->inperform);
}

// n-dimensional linear interpolation
float recursive_interp(char *bp, long dimcount, t_jit_matrix_info *minfo, long *dim_int, float *dim_frak)
{
	float f,x0,x1;
	long i;
	char *bp0,*bp1;

	CLIP_ASSIGN(dimcount,1,JIT_MATRIX_MAX_DIMCOUNT);
	i = dimcount-1;

	bp0 = bp + dim_int[i]*minfo->dimstride[i];
	bp1 = bp + ((dim_int[i]+1)%minfo->dim[i])*minfo->dimstride[i];

	if (dimcount==1) {
		if (minfo->type==_jit_sym_char) {
			x0 = (float)(*((uchar *)bp0))*(1./255.);
			x1 = (float)(*((uchar *)bp1))*(1./255.);
		} else if (minfo->type==_jit_sym_long) {
			x0 = *((t_int32 *)bp0);
			x1 = *((t_int32 *)bp1);
		} else if (minfo->type==_jit_sym_float32) {
			x0 = *((float *)bp0);
			x1 = *((float *)bp1);
		} else if (minfo->type==_jit_sym_float64) {
			x0 = *((double *)bp0);
			x1 = *((double *)bp1);
		}
	} else {
		x0 = recursive_interp(bp0,i,minfo,dim_int,dim_frak);
		x1 = recursive_interp(bp1,i,minfo,dim_int,dim_frak);
	}

	f = (x0 * (1.-dim_frak[i])) + (x1 * dim_frak[i]);
	return f;
}

void max_jit_peek_assist(t_max_jit_peek *x, void *b, long m, long a, char *s)
{
	if (m == 1) { //input
		sprintf(s,"(signal) dim[%ld]",a);
	} else { //output
		switch (a) {
		case 0:
			sprintf(s,"(signal) value");
			break;
		case 1:
			sprintf(s,"dumpout");
			break;
		}
	}
}

void max_jit_peek_dsp(t_max_jit_peek *x, t_signal **sp, short *count)
{
	long i;
	t_atom a;

	if (!x->mdata) // matrix may haven been initialized after jit.peek~ object. try again.
	{
		jit_atom_setsym(&a,x->matrix_name);
		max_jit_peek_matrix_name(x,NULL,1,&a);
	}

	x->vectors[0] = (t_float *)sp[x->dimcount]->s_vec;
	for (i=0; i<(x->dimcount); i++)
		x->vectors[i+1] = (t_float *)sp[i]->s_vec;

	dsp_add(max_jit_peek_perform, 2, x, sp[0]->s_n);
}

void max_jit_peek_dsp64(t_max_jit_peek *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
//	long i;
	t_atom a;

	if (!x->mdata) // matrix may haven been initialized after jit.peek~ object. try again.
	{
		jit_atom_setsym(&a,x->matrix_name);
		max_jit_peek_matrix_name(x,NULL,1,&a);
	}

//	x->vectors[0] = (t_float*)sp[x->dimcount]->s_vec;
//	for (i=0;i<(x->dimcount);i++)
//		x->vectors[i+1] = (t_float*)sp[i]->s_vec;

	dsp_add64(dsp64, (t_object *)x, (t_perfroutine64)max_jit_peek_perform64, 0, NULL);
}

void max_jit_peek_notify(t_max_jit_peek *x, t_symbol *s, t_symbol *msg, void *ob, void *data)
{
	if (s==x->matrix_name) 					// is sender our matrix?
	{
		if (msg==_jit_sym_rebuilding) 		// matrix data is about to change
		{
			while (x->inperform) ; 			// lightweight spinwait
			x->mvalid = 0;					// mark invalid for perform loop
		}
		else if (msg==_jit_sym_modified)	// matrix data has changed
		{
			max_jit_peek_update(x);
			while (x->inperform) ; 			// lightweight spinwait
			x->mvalid = 1;					// mark valid for perform loop
		}
		else if (msg==_jit_sym_free) 		// matrix data is being freed
		{
			while (x->inperform) ; 			// lightweight spinwait
			x->mvalid = 0;					// mark invalid for perform loop
			x->mdata = NULL;
		}

	}
}

void max_jit_peek_matrix_name(t_max_jit_peek *x, void *attr, long argc, t_atom *argv)
{
	t_symbol *name=_jit_sym_nothing;
	void *p;

	if (argc&&argv) {
		name = jit_atom_getsym(argv);
	}

	//if already something registered with this name, check class_jit_matrix, and handle accordingly
	if (p=jit_object_findregistered(name)) {
		if (!jit_object_method(p,_jit_sym_class_jit_matrix)) {
			jit_object_error((t_object *)x,"jit.peek~: %s exists and is not a matrix");
			while (x->inperform) ; 	// lightweight spinwait
			x->mvalid = 0;			// mark invalid for perform loop
			if (x->matrix_name!=_jit_sym_nothing)
				jit_object_detach(x->matrix_name, x);
			x->matrix_name = _jit_sym_nothing;
			x->mdata = NULL;
			return;
		}
	}

	while (x->inperform) ; 	// lightweight spinwait
	x->mvalid = 0;			// mark invalid for perform loop

	jit_object_detach(x->matrix_name, x);
	x->matrix_name = name;
	jit_object_attach(x->matrix_name, x);

	max_jit_peek_update(x);

	while (x->inperform) ; 	// lightweight spinwait
	x->mvalid = 1;			// mark valid for perform loop

}

void max_jit_peek_update(t_max_jit_peek *x)
{
	void *matrix;

	x->mdata = NULL;
	matrix = jit_object_findregistered(x->matrix_name);
	if (matrix&&jit_object_method(matrix, _jit_sym_class_jit_matrix)) {
		//should not call savelock, since this will lock the handle if the matrix is a handle
		//which is not interrupt safe, most matrices are not handles, so this call is not needed
		jit_object_method(matrix,_jit_sym_getinfo,&x->minfo);
		if ((x->minfo.flags&&JIT_MATRIX_DATA_HANDLE)||(x->minfo.flags&&JIT_MATRIX_DATA_REFERENCE)) {
			// do not allow handle or reference data
			return;
		}
		jit_object_method(matrix,_jit_sym_getdata,&x->mdata); //data ptr serves as valid flag
	}
}

void max_jit_peek_free(t_max_jit_peek *x)
{
	dsp_free((t_pxobject *)x);
	while (x->inperform) ; 	// lightweight spinwait
	x->mvalid = 0;			// mark invalid for perform loop
	x->mdata = NULL;

	if (x->matrix_name!=_jit_sym_nothing)
		jit_object_detach(x->matrix_name, x);

	//only max object, no jit object
	max_jit_obex_free(x);
}

void *max_jit_peek_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_peek *x;
	long attrstart,i;
	t_atom a;

	if (x = (t_max_jit_peek *)max_jit_obex_new(max_jit_peek_class,NULL)) { //only max object, no jit object
		for (i=0; i<=JIT_MATRIX_MAX_DIMCOUNT+1; i++)
			x->vectors[i] = NULL;

		x->matrix_name = _jit_sym_nothing;
		x->dimcount = 2;
		x->plane = 0;
		x->interp = 0;
		x->normalize = 0;

		x->inperform = 0;
		x->mvalid = 0;
		x->mdata = 0;

		attrstart = max_jit_attr_args_offset(argc,argv);
		if (attrstart&&argv) {
			t_atom_long al;
			jit_atom_arg_getsym(&x->matrix_name, 0, attrstart, argv);
			if (!jit_atom_arg_getlong(&al, 1, attrstart, argv)) {
				C74_ASSERT_FITS_LONG(al);
				x->dimcount = (long) al;
			}
			if (!jit_atom_arg_getlong(&al, 2, attrstart, argv)) {
				C74_ASSERT_FITS_LONG(al);
				x->plane = (long) al;
			}
			jit_atom_setsym(&a,x->matrix_name);
			max_jit_peek_matrix_name(x,NULL,1,&a);
		}

		CLIP_ASSIGN(x->dimcount,0,JIT_MATRIX_MAX_DIMCOUNT);
		CLIP_ASSIGN(x->dimcount,0,32); //maximum signal inputs

		max_jit_attr_args(x,argc,argv); //handle attribute args

		dsp_setup((t_pxobject *)x,x->dimcount);
		max_jit_obex_dumpout_set(x, outlet_new(x,0L)); //general purpose outlet(rightmost)
		outlet_new((t_object *)x, "signal"); //signal output
	}
	return (x);
}
