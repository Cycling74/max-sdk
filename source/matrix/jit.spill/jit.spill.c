/*
	jit.spill
	Copyright 2001 - Cycling '74
	Jeremy Bernstein jeremy@bootsquad.com
*/

#include "jit.common.h"
#define MAX_OUT 16384
#define DEF_OUT	256

typedef struct _jit_spill
{
	t_object				ob;
	long					listlength;
	char					plane;
	long					offset[JIT_MATRIX_MAX_DIMCOUNT];
	long					offsetcount;
	t_atom					*spill;
	long					spillcount;
} t_jit_spill;

void *_jit_spill_class;

t_jit_spill *jit_spill_new(void);
void jit_spill_free(t_jit_spill *x);
t_jit_err jit_spill_matrix_calc(t_jit_spill *x, void *inputs, void *outputs);
void jit_spill_calculate_ndim(t_jit_spill *x, long dimcount, long *dim, long planecount,
							  t_jit_matrix_info *in_minfo, char *bip);
void jit_spill_calculate_2d_char(t_jit_spill *x, long dimcount, long *dim, long planecount,
								 t_jit_matrix_info *in_minfo, char *bip);
void jit_spill_calculate_2d_long(t_jit_spill *x, long dimcount, long *dim, long planecount,
								 t_jit_matrix_info *in_minfo, char *bip);
void jit_spill_calculate_2d_float32(t_jit_spill *x, long dimcount, long *dim, long planecount,
									t_jit_matrix_info *in_minfo, char *bip);
void jit_spill_calculate_2d_float64(t_jit_spill *x, long dimcount, long *dim, long planecount,
									t_jit_matrix_info *in_minfo, char *bip);
t_jit_err jit_spill_init(void);
t_jit_err jit_spill_getspill(t_jit_spill *x, void *attr, long *ac, t_atom **av);


t_jit_err jit_spill_init(void)
{
	long attrflags=0;
	t_jit_object *attr;
	t_jit_object *mop;

	_jit_spill_class = jit_class_new("jit_spill",(method)jit_spill_new,(method)jit_spill_free,
									 sizeof(t_jit_spill),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,0);
	jit_class_addadornment(_jit_spill_class,mop);
	//add methods
	jit_class_addmethod(_jit_spill_class, (method)jit_spill_matrix_calc, "matrix_calc", A_CANT, 0L);

	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"listlength",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_spill,listlength));
	jit_class_addattr(_jit_spill_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"List Length\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"plane",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_spill,plane));
	jit_class_addattr(_jit_spill_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Plane");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"offset",_jit_sym_long,JIT_MATRIX_MAX_DIMCOUNT, attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_spill,offsetcount), calcoffset(t_jit_spill, offset));
	jit_class_addattr(_jit_spill_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Offset");
	
	attrflags = JIT_ATTR_GET_OPAQUE_USER | JIT_ATTR_SET_OPAQUE_USER;
	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"spill",_jit_sym_atom,MAX_OUT,attrflags,
						  (method)jit_spill_getspill,(method)0L,calcoffset(t_jit_spill,spillcount), calcoffset(t_jit_spill, spill));
	jit_class_addattr(_jit_spill_class,attr);
	//add methods

	jit_class_register(_jit_spill_class);

	return JIT_ERR_NONE;
}

t_jit_err jit_spill_matrix_calc(t_jit_spill *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock;
	t_jit_matrix_info in_minfo;
	char *in_bp;
	long i,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	void *in_matrix;

	in_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);

	if (x&&in_matrix) {
		in_savelock = (long) jit_object_method(in_matrix,_jit_sym_lock,1);
		jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
		jit_object_method(in_matrix,_jit_sym_getdata,&in_bp);
		if (!in_bp) { err=JIT_ERR_INVALID_INPUT; goto out;}

		//get dimensions/planecount
		dimcount   = in_minfo.dimcount;
		planecount = in_minfo.planecount;
		for (i=0; i<dimcount; i++) {
			dim[i] = in_minfo.dim[i];
		}

		//calculate
		jit_spill_calculate_ndim(x, dimcount, dim, planecount, &in_minfo, in_bp);

	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	return err;
}

//recursive function to handle higher dimension matrices, by processing 2D sections at a time
void jit_spill_calculate_ndim(t_jit_spill *x, long dimcount, long *dim, long planecount,
							  t_jit_matrix_info *in_minfo, char *bip)
{
	if (dimcount<1) return; //safety

	switch(dimcount) {
	case 1:
		dim[1]=1;
	case 2:
	default:
		if (in_minfo->type==_jit_sym_char)
			jit_spill_calculate_2d_char(x,dimcount,dim,planecount,in_minfo,bip);
		else if (in_minfo->type==_jit_sym_long)
			jit_spill_calculate_2d_long(x,dimcount,dim,planecount,in_minfo,bip);
		else if (in_minfo->type==_jit_sym_float32)
			jit_spill_calculate_2d_float32(x,dimcount,dim,planecount,in_minfo,bip);
		else if (in_minfo->type==_jit_sym_float64)
			jit_spill_calculate_2d_float64(x,dimcount,dim,planecount,in_minfo,bip);
		break;
	}
}

void jit_spill_calculate_2d_char(t_jit_spill *x, long dimcount, long *dim, long planecount,
								 t_jit_matrix_info *in_minfo, char *bip)
{
	long i,j,width,height;
	char *tmp;
	uchar *ip;
	long offtmp;
	char plane = CLAMP(x->plane, 0, planecount - 1);
	long listlength = x->listlength, templength = 0;

	width  = dim[0];
	height = dim[1];
	CLIP_ASSIGN(listlength, 0, MAX_OUT);

	tmp = (char *)bip;
	for (i = 2; i < dimcount; i++) {
		offtmp = CLAMP(x->offset[i], 0, in_minfo->dim[i] - 1);
		tmp += offtmp * in_minfo->dimstride[i];
	}

	i = CLAMP(x->offset[1], 0, height - 1);
	j = CLAMP(x->offset[0], 0, width - 1);

	ip = (uchar *)(tmp + i * in_minfo->dimstride[1] + j * in_minfo->dimstride[0]);

	if (i < height && templength < listlength) {
		for ( ; j < width && templength < listlength; j++) {
			jit_atom_setlong(&x->spill[templength++], *(ip + plane));
			ip += planecount;
		}
	}
	i++;
	for ( ; i < height && templength < listlength; i++) {
		ip = (uchar *)(tmp + i * in_minfo->dimstride[1]);
		for (j = 0; j < width && templength < listlength; j++) {
			jit_atom_setlong(&x->spill[templength++], *(ip + plane));
			ip += planecount;
		}
	}

	if (templength < listlength) listlength = templength;

	x->spillcount = listlength;
}

void jit_spill_calculate_2d_long(t_jit_spill *x, long dimcount, long *dim, long planecount,
								 t_jit_matrix_info *in_minfo, char *bip)
{
	long i,j,width,height;
	char *tmp;
	t_int32 *ip;
	long offtmp;
	char plane = x->plane;
	long listlength = x->listlength, templength = 0;

	width  = dim[0];
	height = dim[1];
	CLIP_ASSIGN(listlength, 0, MAX_OUT);

	tmp = (char *)bip;
	for (i = 2; i < dimcount; i++) {
		offtmp = CLAMP(x->offset[i], 0, in_minfo->dim[i] - 1);
		tmp += offtmp * in_minfo->dimstride[i];
	}

	i = CLAMP(x->offset[1], 0, height - 1);
	j = CLAMP(x->offset[0], 0, width - 1);

	ip = (t_int32 *)(tmp + i * in_minfo->dimstride[1] + j * in_minfo->dimstride[0]);

	if (i < height && templength < listlength) {
		for ( ; j < width && templength < listlength; j++) {
			jit_atom_setlong(&x->spill[templength++], *(ip + plane));
			ip += planecount;
		}
	}
	i++;
	for ( ; i < height && templength < listlength; i++) {
		ip = (t_int32 *)(tmp + i * in_minfo->dimstride[1]);
		for (j = 0; j < width && templength < listlength; j++) {
			jit_atom_setlong(&x->spill[templength++], *(ip + plane));
			ip += planecount;
		}
	}

	if (templength < listlength) listlength = templength;

	x->spillcount = listlength;
}

void jit_spill_calculate_2d_float32(t_jit_spill *x, long dimcount, long *dim, long planecount,
									t_jit_matrix_info *in_minfo, char *bip)
{
	long i,j,width,height;
	char *tmp;
	float *ip;
	long offtmp;
	char plane = x->plane;
	long listlength = x->listlength, templength = 0;

	width  = dim[0];
	height = dim[1];
	CLIP_ASSIGN(listlength, 0, MAX_OUT);

	tmp = (char *)bip;
	for (i = 2; i < dimcount; i++) {
		offtmp = CLAMP(x->offset[i], 0, in_minfo->dim[i] - 1);
		tmp += offtmp * in_minfo->dimstride[i];
	}

	i = CLAMP(x->offset[1], 0, height - 1);
	j = CLAMP(x->offset[0], 0, width - 1);

	ip = (float *)(tmp + i * in_minfo->dimstride[1] + j * in_minfo->dimstride[0]);

	if (i < height && templength < listlength) {
		for ( ; j < width && templength < listlength; j++) {
			jit_atom_setfloat(&x->spill[templength++], *(ip + plane));
			ip += planecount;
		}
	}
	i++;
	for ( ; i < height && templength < listlength; i++) {
		ip = (float *)(tmp + i * in_minfo->dimstride[1]);
		for (j = 0; j < width && templength < listlength; j++) {
			jit_atom_setfloat(&x->spill[templength++], *(ip + plane));
			ip += planecount;
		}
	}

	if (templength < listlength) listlength = templength;

	x->spillcount = listlength;
}

void jit_spill_calculate_2d_float64(t_jit_spill *x, long dimcount, long *dim, long planecount,
									t_jit_matrix_info *in_minfo, char *bip)
{
	long i,j,width,height;
	char *tmp;
	double *ip;
	long offtmp;
	char plane = x->plane;
	long listlength = x->listlength, templength = 0;

	width  = dim[0];
	height = dim[1];
	CLIP_ASSIGN(listlength, 0, MAX_OUT);

	tmp = (char *)bip;
	for (i = 2; i < dimcount; i++) {
		offtmp = CLAMP(x->offset[i], 0, in_minfo->dim[i] - 1);
		tmp += offtmp * in_minfo->dimstride[i];
	}

	i = CLAMP(x->offset[1], 0, height - 1);
	j = CLAMP(x->offset[0], 0, width - 1);

	ip = (double *)(tmp + i * in_minfo->dimstride[1] + j * in_minfo->dimstride[0]);

	if (i < height && templength < listlength) {
		for ( ; j < width && templength < listlength; j++) {
			jit_atom_setfloat(&x->spill[templength++], *(ip + plane));
			ip += planecount;
		}
	}
	i++;
	for ( ; i < height && templength < listlength; i++) {
		ip = (double *)(tmp + i * in_minfo->dimstride[1]);
		for (j = 0; j < width && templength < listlength; j++) {
			jit_atom_setfloat(&x->spill[templength++], *(ip + plane));
			ip += planecount;
		}
	}

	if (templength < listlength) listlength = templength;

	x->spillcount = listlength;
}


t_jit_err jit_spill_getspill(t_jit_spill *x, void *attr, long *ac, t_atom **av)
{
	long i;
	if ((*ac)&&(*av)) {
		//memory passed in, use it
	} else {
		//otherwise allocate memory
		*ac = x->spillcount;
		if (!(*av = jit_getbytes(sizeof(t_atom)*(*ac)))) {
			*ac = 0;
			return JIT_ERR_OUT_OF_MEM;
		}
	}
	*ac = MIN(*ac,x->spillcount);
	for (i=0; i<(*ac); i++)
	{
		(*av)[i] = x->spill[i];
	}

	return JIT_ERR_NONE;
}

t_jit_spill *jit_spill_new(void)
{
	t_jit_spill *x;
	long i;

	if (x=(t_jit_spill *)jit_object_alloc(_jit_spill_class)) {
		x->spill = (t_atom *) sysmem_newptr(MAX_OUT*sizeof(t_atom));
		x->plane = 0;
		x->listlength = DEF_OUT;
		for (i = 0; i < JIT_MATRIX_MAX_DIMCOUNT; i++) {
			x->offset[i] = 0;
		}
		x->offsetcount = 2;
		x->spillcount = 0;
	} else {
		x = NULL;
	}
	return x;
}

void jit_spill_free(t_jit_spill *x)
{
	//nada
	if (x->spill)
		sysmem_freeptr((char *)x->spill);
}
