/*
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

// 03.08.05 -- added normalize attribute.  rld.

#include "jit.common.h"
#include "z_dsp.h"
#include "ext_atomic.h"

typedef struct _max_jit_poke
{
	t_pxobject			ob;
	void				*obex;
	t_symbol			*matrix_name;
	long				dimcount;
	long				plane;
	float				*vectors[JIT_MATRIX_MAX_DIMCOUNT+1];
	t_int32_atomic		inperform;
	long				mvalid;
	char				*mdata;
	long				normalize;
	t_jit_matrix_info	minfo;
} t_max_jit_poke;

void *max_jit_poke_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_poke_free(t_max_jit_poke *x);
void max_jit_poke_assist(t_max_jit_poke *x, void *b, long m, long a, char *s);
void max_jit_poke_notify(t_max_jit_poke *x, t_symbol *s, t_symbol *msg, void *ob, void *data);
void max_jit_poke_matrix_name(t_max_jit_poke *x, void *attr, long argc, t_atom *argv);
void max_jit_poke_update(t_max_jit_poke *x);
void max_jit_poke_dsp(t_max_jit_poke *x, t_signal **sp, short *count);
void max_jit_poke_dsp64(t_max_jit_poke *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
t_int *max_jit_poke_perform(t_int *w);

void *max_jit_poke_class;

t_symbol *ps_done;

void ext_main(void *r)
{
	long attrflags;
	void *p,*attr;

	setup((t_messlist **)&max_jit_poke_class, (method)max_jit_poke_new, (method)max_jit_poke_free, (short)sizeof(t_max_jit_poke),
		  0L, A_GIMME, 0);

	addmess((method)max_jit_poke_dsp, "dsp", A_CANT, 0);
	addmess((method)max_jit_poke_dsp64, "dsp64", A_CANT, 0);
	dsp_initclass();

	p = max_jit_classex_setup(calcoffset(t_max_jit_poke,obex));

	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW ;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"matrix_name",_jit_sym_symbol,attrflags,
						  (method)0L,(method)max_jit_poke_matrix_name,calcoffset(t_max_jit_poke,matrix_name));
	max_jit_classex_addattr(p,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Matrix Name\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"plane",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_max_jit_poke,plane));
	max_jit_classex_addattr(p,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Plane");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"normalize",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_max_jit_poke,normalize));
	max_jit_classex_addattr(p,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Normalize");

	// because it is not safe to call jitter methods inside the perform routine,
	// we need notify message to find out when our matrix data is changing
	addmess((method)max_jit_poke_notify, "notify", A_CANT,0);

	max_jit_classex_standard_wrap(p,NULL,0);
	addmess((method)max_jit_poke_assist,			"assist",			A_CANT,0);
}

t_int *max_jit_poke_perform(t_int *w)
{
	t_max_jit_poke *x = (t_max_jit_poke *)(w[1]);
	long n = (int)(w[2]);
	long i,j,dimcount;
	char *bp,*p;
	float *in_val=x->vectors[0];
	float **in_dim=x->vectors+1;
	long tmp,outofbounds;
	long mult[JIT_MATRIX_MAX_DIMCOUNT]; // added to perform routine for normalization

	ATOMIC_INCREMENT(&x->inperform);

	if (x->ob.z_disabled)
		goto out;

	if (x->mvalid&&x->mdata) {

		bp = x->mdata;

		if ((!bp)||(x->plane>=x->minfo.planecount)||(x->plane<0)) {
			goto out;
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
					in_val++;
				} else {
					tmp = (*in_val++) * 255.;
					*((uchar *)p) = tmp>255?255:tmp<0?0:tmp;
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
					in_val++;
				} else {
					*((t_int32 *)p) = (t_int32)(*in_val++);
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
					in_val++;
				} else {
					*((float *)p) = *in_val++;
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
					in_val++;
				} else {
					*((double *)p) = (double)(*in_val++);
				}
			}
		}
	}

out:
	ATOMIC_DECREMENT(&x->inperform);
	return (w+3);
}

void max_jit_poke_perform64(t_max_jit_poke *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	long n = sampleframes;
	long i,j,dimcount;
	char *bp,*p;
	double *in_val = ins[0];
	double *in_dim[JIT_MATRIX_MAX_DIMCOUNT];
	long tmp,outofbounds;
	long mult[JIT_MATRIX_MAX_DIMCOUNT]; // added to perform routine for normalization

	ATOMIC_INCREMENT(&x->inperform);

	if (x->mvalid&&x->mdata) {

		for (i=1; i<numins; i++)
			in_dim[i-1] = ins[i];

		bp = x->mdata;

		if ((!bp)||(x->plane>=x->minfo.planecount)||(x->plane<0)) {
			goto out;
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
					in_val++;
				} else {
					tmp = (*in_val++) * 255.;
					*((uchar *)p) = tmp>255?255:tmp<0?0:tmp;
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
					in_val++;
				} else {
					*((t_int32 *)p) = (t_int32)(*in_val++);
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
					in_val++;
				} else {
					*((float *)p) = *in_val++;
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
					in_val++;
				} else {
					*((double *)p) = (double)(*in_val++);
				}
			}
		}
	}

out:
	ATOMIC_DECREMENT(&x->inperform);
}

void max_jit_poke_assist(t_max_jit_poke *x, void *b, long m, long a, char *s)
{
	if (m == 1) { //input
		switch (a) {
		case 0:
			sprintf(s,"(signal) value");
			break;
		default:
			sprintf(s,"(signal) dim[%ld]",a-1);
		}
	} else { //output
		sprintf(s,"dumpout");
	}
}

void max_jit_poke_dsp(t_max_jit_poke *x, t_signal **sp, short *count)
{
	long i;
	t_atom a;

	if (!x->mdata) // matrix may haven been initialized after jit.poke~ object. try again.
	{
		jit_atom_setsym(&a,x->matrix_name);
		max_jit_poke_matrix_name(x,NULL,1,&a);
	}

	for (i=0; i<(x->dimcount+1); i++)
		x->vectors[i] = (t_float *)sp[i]->s_vec;

	dsp_add(max_jit_poke_perform, 2, x, sp[0]->s_n);
}

void max_jit_poke_dsp64(t_max_jit_poke *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	t_atom a;

	if (!x->mdata) // matrix may haven been initialized after jit.poke~ object. try again.
	{
		jit_atom_setsym(&a,x->matrix_name);
		max_jit_poke_matrix_name(x,NULL,1,&a);
	}

//	The following moved to the perform routine for MSP64
//	for (i=0;i<(x->dimcount+1);i++)
//		x->vectors[i] = (t_float*)sp[i]->s_vec;

	dsp_add64(dsp64, (t_object *)x, (t_perfroutine64)max_jit_poke_perform64, 0, NULL);
}

void max_jit_poke_notify(t_max_jit_poke *x, t_symbol *s, t_symbol *msg, void *ob, void *data)
{
	if (s==x->matrix_name) 					// is sender our matrix?
	{
		if (msg==_jit_sym_rebuilding) 		// matrix data is about to change
		{
			while (x->inperform) ; 			// lightweight spinwait
			x->mvalid = 0;					// mark invalid for perform loop
			x->mdata = NULL;
		}
		else if (msg==_jit_sym_modified)	// matrix data has changed
		{
			max_jit_poke_update(x);
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

void max_jit_poke_matrix_name(t_max_jit_poke *x, void *attr, long argc, t_atom *argv)
{
	t_symbol *name=_jit_sym_nothing;
	void *p;

	if (argc&&argv) {
		name = jit_atom_getsym(argv);
	}

	//if already something registered with this name, check class_jit_matrix, and handle accordingly
	if (p=jit_object_findregistered(name)) {
		if (!jit_object_method(p,_jit_sym_class_jit_matrix)) {
			jit_object_error((t_object *)x,"jit.poke~: %s exists and is not a matrix");
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

	max_jit_poke_update(x);

	while (x->inperform) ; 	// lightweight spinwait
	x->mvalid = 1;			// mark valid for perform loop
}

void max_jit_poke_update(t_max_jit_poke *x)
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

void max_jit_poke_free(t_max_jit_poke *x)
{
	dsp_free((void *)x);
	while (x->inperform) ; 	// lightweight spinwait
	x->mvalid = 0;			// mark invalid for perform loop
	x->mdata = NULL;

	if (x->matrix_name!=_jit_sym_nothing)
		jit_object_detach(x->matrix_name, x);

	//only max object, no jit object
	max_jit_obex_free(x);
}

void *max_jit_poke_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_poke *x;
	long attrstart,i;
	t_atom a;

	if (x = (t_max_jit_poke *)max_jit_obex_new(max_jit_poke_class,NULL)) { //only max object, no jit object
		for (i=0; i<=JIT_MATRIX_MAX_DIMCOUNT+1; i++)
			x->vectors[i] = NULL;

		x->matrix_name = _jit_sym_nothing;
		x->dimcount = 2;
		x->plane = 0;
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
			max_jit_poke_matrix_name(x,NULL,1,&a);
		}

		CLIP_ASSIGN(x->dimcount,0,JIT_MATRIX_MAX_DIMCOUNT);
		CLIP_ASSIGN(x->dimcount,0,31); //maximum signal inputs - 1

		max_jit_attr_args(x,argc,argv); //handle attribute args

		dsp_setup((t_pxobject *)x,x->dimcount+1);
		max_jit_obex_dumpout_set(x, outlet_new(x,0L)); //general purpose outlet(rightmost)
	}
	return (x);
}
