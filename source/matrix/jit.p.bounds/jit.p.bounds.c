/*
	jit.p.bounds
	Copyright 2001-2005 - Cycling '74
	Jeremy Bernstein jeremy@bootsquad.com
*/

#include "jit.common.h"
#include "math.h"

/* This is sort of half set-up to support > 3 dimensional particle geometries, but
I didn't fully implement it, due to > 3 dimensional rotation issues. Will readdress
at some point. */

#define MAX_RANDOM 4294967294

typedef struct _jit_p_bounds
{
	t_object				ob;
	double					squish[JIT_MATRIX_MAX_PLANECOUNT - 2];
	double					squish_var[JIT_MATRIX_MAX_PLANECOUNT - 2];
	double					bounds_hi[JIT_MATRIX_MAX_PLANECOUNT - 2];
	double					bounds_lo[JIT_MATRIX_MAX_PLANECOUNT - 2];
	char					bounds_enable_hi[JIT_MATRIX_MAX_PLANECOUNT - 2];
	char					bounds_enable_lo[JIT_MATRIX_MAX_PLANECOUNT - 2];
	long					boundscount_hi;
	long					boundscount_lo;
	long					squishcount;
	long					squish_varcount;
	t_int32					random;
	char					mode; // 0 = bounce, 1 = torus, 2 = kill
} t_jit_p_bounds;

void *_jit_p_bounds_class;

t_jit_p_bounds *jit_p_bounds_new(void);
void jit_p_bounds_free(t_jit_p_bounds *x);
t_jit_err jit_p_bounds_matrix_calc(t_jit_p_bounds *x, void *inputs, void *outputs);
void jit_p_bounds_calculate_ndim(t_jit_p_bounds *x, long dimcount, long *dim, long planecount,
								 t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop);
void jit_p_bounds_calculate_2d_float32(t_jit_p_bounds *x, long dimcount, long *dim, long planecount,
									   t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop);
void jit_p_bounds_calculate_2d_float64(t_jit_p_bounds *x, long dimcount, long *dim, long planecount,
									   t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop);
void jit_p_bounds_bounds_hi(t_jit_p_bounds *x, void *attr, long ac, t_atom *av);
t_jit_err jit_p_bounds_getbounds_hi(t_jit_p_bounds *x, void *attr, long *ac, t_atom **av);
void jit_p_bounds_bounds_lo(t_jit_p_bounds *x, void *attr, long ac, t_atom *av);
t_jit_err jit_p_bounds_getbounds_lo(t_jit_p_bounds *x, void *attr, long *ac, t_atom **av);

float jit_p_bounds_random_num(t_jit_p_bounds *x);
void jit_p_bounds_rotation_to_direction(float pitch, float yaw, float *direction);
t_jit_err jit_p_bounds_init(void);

const long HALF_RAND = (MAX_RANDOM / 2);

t_jit_err jit_p_bounds_init(void)
{
	long attrflags=0;
	t_jit_object *attr;
	t_jit_object *mop;
	void *o;
	t_atom a[2], a2;

	_jit_p_bounds_class = jit_class_new("jit_p_bounds",(method)jit_p_bounds_new,(method)jit_p_bounds_free,
										sizeof(t_jit_p_bounds),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,1);
	jit_atom_setsym(&a[0], _jit_sym_float32);
	jit_atom_setsym(&a[1], _jit_sym_float64);
	jit_atom_setlong(&a2, 2);
	o = jit_object_method(mop, _jit_sym_getinput, 1);
	jit_object_method(o, gensym("types"), 2, a);
	jit_object_method(o, gensym("minplanecount"), 1, &a2);
	jit_object_method(o, gensym("mindimcount"), 1, &a2);
	o = jit_object_method(mop, _jit_sym_getoutput, 1);
	jit_object_method(o, gensym("types"), 2, a);
	jit_object_method(o, gensym("minplanecount"), 1, &a2);
	jit_object_method(o, gensym("mindimcount"), 1, &a2);
	jit_class_addadornment(_jit_p_bounds_class,mop);
	//add methods
	jit_class_addmethod(_jit_p_bounds_class, (method)jit_p_bounds_matrix_calc, "matrix_calc", A_CANT, 0L);

	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset_array, "bounds_hi", _jit_sym_float64, JIT_MATRIX_MAX_PLANECOUNT - 2,
						  attrflags, (method)jit_p_bounds_getbounds_hi, (method)jit_p_bounds_bounds_hi, calcoffset(t_jit_p_bounds, boundscount_hi), calcoffset(t_jit_p_bounds, bounds_hi));
	jit_class_addattr(_jit_p_bounds_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Bounds High\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset_array, "bounds_lo", _jit_sym_float64, JIT_MATRIX_MAX_PLANECOUNT - 2,
						  attrflags, (method)jit_p_bounds_getbounds_lo, (method)jit_p_bounds_bounds_lo, calcoffset(t_jit_p_bounds, boundscount_lo), calcoffset(t_jit_p_bounds, bounds_lo));
	jit_class_addattr(_jit_p_bounds_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Bounds Low\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset_array, "squish", _jit_sym_float64, JIT_MATRIX_MAX_PLANECOUNT - 2, attrflags,
						  (method)0L, (method)0L, calcoffset(t_jit_p_bounds, squishcount), calcoffset(t_jit_p_bounds, squish));
	jit_class_addattr(_jit_p_bounds_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Squish");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset_array, "squish_var", _jit_sym_float64, JIT_MATRIX_MAX_PLANECOUNT - 2, attrflags,
						  (method)0L, (method)0L, calcoffset(t_jit_p_bounds, squish_varcount), calcoffset(t_jit_p_bounds, squish_var));
	jit_class_addattr(_jit_p_bounds_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Squish Var\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset, "mode", _jit_sym_char, attrflags,
						  (method)0L, (method)0L, calcoffset(t_jit_p_bounds, mode));
	jit_class_addattr(_jit_p_bounds_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Mode");

//	jit_class_addmethod(_jit_p_bounds_class, (method)jit_p_bounds_reset, "reset", A_DEFER_LOW, 0);

	jit_class_register(_jit_p_bounds_class);

	return JIT_ERR_NONE;
}

void jit_p_bounds_bounds_hi(t_jit_p_bounds *x, void *attr, long ac, t_atom *av)
{
	long i = 0;
	t_symbol *sname = _jit_sym_nothing;

	if (ac && av) {
		for (i = 0; i < ac; i++) {
			sname = _jit_sym_nothing;
			jit_atom_arg_getsym(&sname, i, ac, av);
			if (sname != _jit_sym_nothing)
				x->bounds_enable_hi[i] = 0;
			else {
				x->bounds_hi[i] = jit_atom_getfloat(av + i);
				x->bounds_enable_hi[i] = 1;
			}
		}
	}
	x->boundscount_hi = ac;
}

t_jit_err jit_p_bounds_getbounds_hi(t_jit_p_bounds *x, void *attr, long *ac, t_atom **av)
{
	long i;

	if ((*ac)&&(*av)) {
		//memory passed in, use it
	} else {
		//otherwise allocate memory
		*ac = x->boundscount_hi;
		if (!(*av = jit_getbytes(sizeof(t_atom)*(*ac)))) {
			*ac = 0;
			return JIT_ERR_OUT_OF_MEM;
		}
	}

	for (i = 0; i < x->boundscount_hi; i++) {
		if (x->bounds_enable_hi[i])
			jit_atom_setfloat(*av + i, x->bounds_hi[i]);
		else
			jit_atom_setsym(*av + i, gensym("x"));
	}
	return JIT_ERR_NONE;

}

void jit_p_bounds_bounds_lo(t_jit_p_bounds *x, void *attr, long ac, t_atom *av)
{
	long i = 0;
	t_symbol *sname = _jit_sym_nothing;

	if (ac && av) {
		for (i = 0; i < ac; i++) {
			sname = _jit_sym_nothing;
			jit_atom_arg_getsym(&sname, i, ac, av);
			if (sname != _jit_sym_nothing)
				x->bounds_enable_lo[i] = 0;
			else {
				x->bounds_lo[i] = jit_atom_getfloat(av + i);
				x->bounds_enable_lo[i] = 1;
			}
		}
	}
	x->boundscount_lo = ac;
}

t_jit_err jit_p_bounds_getbounds_lo(t_jit_p_bounds *x, void *attr, long *ac, t_atom **av)
{
	long i;

	if ((*ac)&&(*av)) {
		//memory passed in, use it
	} else {
		//otherwise allocate memory
		*ac = x->boundscount_lo;
		if (!(*av = jit_getbytes(sizeof(t_atom)*(*ac)))) {
			*ac = 0;
			return JIT_ERR_OUT_OF_MEM;
		}
	}

	for (i = 0; i < x->boundscount_lo; i++) {
		if (x->bounds_enable_lo[i])
			jit_atom_setfloat(*av + i, x->bounds_lo[i]);
		else
			jit_atom_setsym(*av + i, gensym("x"));
	}
	return JIT_ERR_NONE;
}


t_jit_err jit_p_bounds_matrix_calc(t_jit_p_bounds *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock,out_savelock;
	t_jit_matrix_info in_minfo,out_minfo;
	char *in_bp,*out_bp;
	long i,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	long dimflag = 0;
	t_atom a[JIT_MATRIX_MAX_DIMCOUNT];
	void *in_matrix, *out_matrix;

	in_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);
	out_matrix 	= jit_object_method(outputs,_jit_sym_getindex,0);

	if (x && in_matrix && out_matrix) {
		jit_object_method(in_matrix, _jit_sym_getinfo, &in_minfo);
		jit_object_method(out_matrix, _jit_sym_getinfo, &out_minfo);

		if (in_minfo.type != out_minfo.type) {
			jit_atom_setsym(&a[0], in_minfo.type);
			jit_object_method(out_matrix, _jit_sym_type, 1, &a[0]);
		}

		if (in_minfo.planecount != out_minfo.planecount) {
			jit_atom_setlong(&a[0], in_minfo.planecount);
			jit_object_method(out_matrix, _jit_sym_planecount, 1, &a[0]);
		}

		planecount = in_minfo.planecount;

		dimcount = in_minfo.dimcount;
		for (i = 0; i < dimcount; i++) {
			dim[i] = in_minfo.dim[i];
			jit_atom_setlong(&a[i], dim[i]);
			if (out_minfo.dim[i] != dim[i])
				dimflag = 1;
		}

		if (dimflag) {
			jit_object_method(out_matrix, _jit_sym_dim, dimcount, a);
		}

		in_savelock = (long) jit_object_method(in_matrix,_jit_sym_lock,1);
		out_savelock = (long) jit_object_method(out_matrix,_jit_sym_lock,1);

		jit_object_method(out_matrix,_jit_sym_clear);

		jit_object_method(in_matrix, _jit_sym_getdata, &in_bp);
		jit_object_method(out_matrix, _jit_sym_getdata, &out_bp);

		if (!in_bp) {
			err=JIT_ERR_INVALID_INPUT;
			goto out;
		}

		if (!out_bp) {
			err=JIT_ERR_INVALID_OUTPUT;
			goto out;
		}

		//compatible types?
		if (in_minfo.type != _jit_sym_float32 && in_minfo.type != _jit_sym_float64) {
			err=JIT_ERR_MISMATCH_TYPE;
			goto out;
		}

		if (in_minfo.dim[1] != 2 || out_minfo.dim[1] != 2) {
			err = JIT_ERR_MISMATCH_DIM;
			goto out;
		}

		jit_p_bounds_calculate_ndim(x, dimcount, dim, planecount, &in_minfo, in_bp, &out_minfo, out_bp);

	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(out_matrix,_jit_sym_lock,out_savelock);
	jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	return err;
}

//recursive function to handle higher dimension matrices, by processing 2D sections at a time
void jit_p_bounds_calculate_ndim(t_jit_p_bounds *x, long dimcount, long *dim, long planecount,
								 t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop)
{
	long i;
	uchar *ip,*op;

	if (dimcount<1) return; //safety

	switch(dimcount) {
	case 1:
		dim[1]=1;
	case 2:
		if (in_minfo->type==_jit_sym_float32)
			jit_p_bounds_calculate_2d_float32(x,dimcount,dim,planecount,in_minfo,bip,out_minfo,bop);
		else if (in_minfo->type==_jit_sym_float64)
			jit_p_bounds_calculate_2d_float64(x,dimcount,dim,planecount,in_minfo,bip,out_minfo,bop);
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			ip = (uchar *)(bip + i*in_minfo->dimstride[dimcount-1]);
			op = (uchar *)(bop + i*out_minfo->dimstride[dimcount-1]);
			jit_p_bounds_calculate_ndim(x,dimcount-1,dim,planecount,in_minfo,(char *)ip,out_minfo,(char *)op);
		}
	}
}

float jit_p_bounds_random_num(t_jit_p_bounds *x)
{
	t_int32 rn = x->random;

	rn = 1664525L * rn + 1013904223L;
	x->random = rn;

	return ((float)(rn - HALF_RAND) / (float)HALF_RAND);
}

void jit_p_bounds_rotation_to_direction(float pitch, float yaw, float *direction)
{
	*direction = (float)(-jit_math_sin(yaw) * jit_math_cos(pitch));
	*(direction + 1) = (float)jit_math_sin(pitch);
	*(direction + 2) = (float)(jit_math_cos(pitch) * jit_math_cos(yaw));
}

void jit_p_bounds_calculate_2d_float32(t_jit_p_bounds *x, long dimcount, long *dim, long planecount,
									   t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop)
{
	long j, k, n;
	long width, rowstride;
	float *ip, *op, *ip2, *op2, *kill;
	float tmp;
	float squish[JIT_MATRIX_MAX_PLANECOUNT - 2];
	float squish_var[JIT_MATRIX_MAX_PLANECOUNT - 2];
	float newsquish[JIT_MATRIX_MAX_PLANECOUNT - 2];
	float bounds_hi[JIT_MATRIX_MAX_PLANECOUNT - 2];
	float bounds_lo[JIT_MATRIX_MAX_PLANECOUNT - 2];
	char bounds_enable_hi[JIT_MATRIX_MAX_PLANECOUNT - 2];
	char bounds_enable_lo[JIT_MATRIX_MAX_PLANECOUNT - 2];
	char killflag;

	x->random = jit_rand();

	width = dim[0];
	rowstride = in_minfo->dimstride[1] / 4;

	for (j = 0; j < JIT_MATRIX_MAX_PLANECOUNT - 2; j++) {
		bounds_hi[j] = x->bounds_hi[j];
		bounds_lo[j] = x->bounds_lo[j];
		bounds_enable_hi[j] = x->bounds_enable_hi[j];
		bounds_enable_lo[j] = x->bounds_enable_lo[j];
		squish[j] = x->squish[j];
		squish_var[j] = x->squish_var[j];
	}

//	squish = x->squish;
//	squish_var = x->squish_var;

	ip = (float *)(bip);
	op = (float *)(bop);
	ip2 = ip + rowstride;
	op2 = op + rowstride;
	n = width;
//	newsquish = squish;

	switch(x->mode) {
	case 3: //clip
		switch(planecount) {
		case 5:
			while (n-- && *ip) {
				*op++ = *ip++;			//id
				*op2++ = *ip2++;

				*op++ = *ip++;			//life
				*op2++ = *ip2++;

				if (bounds_enable_lo[0] && (*ip < bounds_lo[0])) {
					*op2++ = *ip2++;
					*op++ = bounds_lo[0];
					ip++;
				}
				else if (bounds_enable_hi[0] && (*ip > bounds_hi[0])) {
					*op2++ = *ip2++;
					*op++ = bounds_hi[0];
					ip++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if (bounds_enable_lo[1] && (*ip < bounds_lo[1])) {
					*op2++ = *ip2++;
					*op++ = bounds_lo[1];
					ip++;
				}
				else if (bounds_enable_hi[1] && (*ip > bounds_hi[1])) {
					*op2++ = *ip2++;
					*op++ = bounds_hi[1];
					ip++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if (bounds_enable_lo[2] && (*ip < bounds_lo[2])) {
					*op2++ = *ip2++;
					*op++ = bounds_lo[2];
					ip++;
				}
				else if (bounds_enable_hi[2] && (*ip > bounds_hi[2])) {
					*op2++ = *ip2++;
					*op++ = bounds_hi[2];
					ip++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}
			}
			break;
		default:
			while (n-- && *ip) {
				*op++ = *ip++;			//id
				*op2++ = *ip2++;

				*op++ = *ip++;			//life
				*op2++ = *ip2++;

				for (k = 0; k < planecount - 2; k++) {
					if (bounds_enable_lo[k] && (*ip < bounds_lo[k])) {
						*op2++ = *ip2++;
						*op++ = bounds_lo[k];
						ip++;
					}
					else if (bounds_enable_hi[k] && (*ip > bounds_hi[k])) {
						*op2++ = *ip2++;
						*op++ = bounds_hi[k];
						ip++;
					}
					else {
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}
			}
			break;
		}
		break;
	case 2: // torus
		switch(planecount) {
		case 5:
			while (n-- && *ip) {
				*op++ = *ip++;			//id
				*op2++ = *ip2++;

				kill = op;
				killflag = 0;

				*op++ = *ip++;			//life
				*op2++ = *ip2++;

				if ((bounds_enable_hi[0] && (*ip > bounds_hi[0]))) {
					if (bounds_enable_lo[0]) {
						*op2++ = bounds_lo[0];
						*op++ = bounds_lo[0] + (*ip++ - *ip2++);
					}
					else {
						killflag = 1;
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}
				else if ((bounds_enable_lo[0] && (*ip < bounds_lo[0]))) {
					if (bounds_enable_hi[0]) {
						*op2++ = bounds_hi[0];
						*op++ = bounds_hi[0] + (*ip++ - *ip2++);
					}
					else {
						killflag = 1;
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if ((bounds_enable_hi[1] && (*ip > bounds_hi[1]))) {
					if (bounds_enable_lo[1]) {
						*op2++ = bounds_lo[1];
						*op++ = bounds_lo[1] + (*ip++ - *ip2++);
					}
					else {
						killflag = 1;
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}
				else if ((bounds_enable_lo[1] && (*ip < bounds_lo[1]))) {
					if (bounds_enable_hi[1]) {
						*op2++ = bounds_hi[1];
						*op++ = bounds_hi[1] + (*ip++ - *ip2++);
					}
					else {
						killflag = 1;
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if ((bounds_enable_hi[2] && (*ip > bounds_hi[2]))) {
					if (bounds_enable_lo[2]) {
						*op2++ = bounds_lo[2];
						*op++ = bounds_lo[2] + (*ip++ - *ip2++);
					}
					else {
						killflag = 1;
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}
				else if ((bounds_enable_lo[2] && (*ip < bounds_lo[2]))) {
					if (bounds_enable_hi[2]) {
						*op2++ = bounds_hi[2];
						*op++ = bounds_hi[2] + (*ip++ - *ip2++);
					}
					else {
						killflag = 1;
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if (killflag)
					*kill = 0;
			}
			break;
		default:
			while (n-- && *ip) {
				*op++ = *ip++;			//id
				*op2++ = *ip2++;

				kill = op;
				killflag = 0;

				*op++ = *ip++;			//life
				*op2++ = *ip2++;

				for (k = 0; k < planecount - 2; k++) {
					if ((bounds_enable_hi[k] && (*ip > bounds_hi[k]))) {
						if (bounds_enable_lo[k]) {
							*op2++ = bounds_lo[k];
							*op++ = bounds_lo[k] + (*ip++ - *ip2++);
						}
						else {
							killflag = 1;
							*op2++ = *ip2++;
							*op++ = *ip++;
						}
					}
					else if ((bounds_enable_lo[k] && (*ip < bounds_lo[k]))) {
						if (bounds_enable_hi[k]) {
							*op2++ = bounds_hi[k];
							*op++ = bounds_hi[k] + (*ip++ - *ip2++);
						}
						else {
							killflag = 1;
							*op2++ = *ip2++;
							*op++ = *ip++;
						}
					}
					else {
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}

				if (killflag)
					*kill = 0;
			}
			break;
		}
		break;
	case 1: //kill
		switch(planecount) {
		case 5:
			while (n-- && *ip) {
				*op++ = *ip++;			//id
				*op2++ = *ip2++;

				kill = op;
				killflag = 0;

				*op++ = *ip++;			//life
				*op2++ = *ip2++;

				if (bounds_enable_lo[0] && (*ip < bounds_lo[0])) {
					killflag = 1;
					*op2++ = *ip2++;
					*op++ = bounds_lo[0];
					ip++;
				}
				else if (bounds_enable_hi[0] && (*ip > bounds_hi[0])) {
					killflag = 1;
					*op2++ = *ip2++;
					*op++ = bounds_hi[0];
					ip++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if (bounds_enable_lo[1] && (*ip < bounds_lo[1])) {
					killflag = 1;
					*op2++ = *ip2++;
					*op++ = bounds_lo[1];
					ip++;
				}
				else if (bounds_enable_hi[1] && (*ip > bounds_hi[1])) {
					killflag = 1;
					*op2++ = *ip2++;
					*op++ = bounds_hi[1];
					ip++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if (bounds_enable_lo[2] && (*ip < bounds_lo[2])) {
					killflag = 1;
					*op2++ = *ip2++;
					*op++ = bounds_lo[2];
					ip++;
				}
				else if (bounds_enable_hi[2] && (*ip > bounds_hi[2])) {
					killflag = 1;
					*op2++ = *ip2++;
					*op++ = bounds_hi[2];
					ip++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if (killflag)
					*kill = 0;
			}
			break;
		default:
			while (n-- && *ip) {
				*op++ = *ip++;			//id
				*op2++ = *ip2++;

				kill = op;
				killflag = 0;

				*op++ = *ip++;			//life
				*op2++ = *ip2++;

				for (k = 0; k < planecount - 2; k++) {
					if (bounds_enable_lo[k] && (*ip < bounds_lo[k])) {
						killflag = 1;
						*op2++ = *ip2++;
						*op++ = bounds_lo[k];
						ip++;
					}
					else if (bounds_enable_hi[k] && (*ip > bounds_hi[k])) {
						killflag = 1;
						*op2++ = *ip2++;
						*op++ = bounds_hi[k];
						ip++;
					}
					else {
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}

				if (killflag)
					*kill = 0;
			}
			break;
		}
		break;
	case 0:
	default: // bounce
		switch(planecount) {
		case 5:
			while (n-- && *ip) {

				for (j = 0; j < 3; j++)
					newsquish[j] = squish[j] + (squish_var[j] * jit_p_bounds_random_num(x));

				*op++ = *ip++;			//id
				*op2++ = *ip2++;
				*op++ = *ip++;			//life
				*op2++ = *ip2++;

				if ((bounds_enable_lo[0] && bounds_enable_hi[0]) && ((*ip < bounds_lo[0]) || (*ip > bounds_hi[0]))) {
					*op2++ = tmp = CLAMP(*ip, bounds_lo[0], bounds_hi[0]);
					*op++ = CLAMP(tmp + (-(tmp - *ip2) * newsquish[0]), bounds_lo[0], bounds_hi[0]);
					ip++; ip2++;
				}
				else if (bounds_enable_lo[0] && (*ip < bounds_lo[0])) {
					*op2++ = tmp = MAX(*ip, bounds_lo[0]);
					*op++ = MAX(tmp + (-(tmp - *ip2) * newsquish[0]), bounds_lo[0]);
					ip++; ip2++;
				}
				else if (bounds_enable_hi[0] && (*ip > bounds_hi[0])) {
					*op2++ = tmp = MIN(*ip, bounds_hi[0]);
					*op++ = MIN(tmp + (-(tmp - *ip2) * newsquish[0]), bounds_hi[0]);
					ip++; ip2++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if ((bounds_enable_lo[1] && bounds_enable_hi[1]) && ((*ip < bounds_lo[1]) || (*ip > bounds_hi[1]))) {
					*op2++ = tmp = CLAMP(*ip, bounds_lo[1], bounds_hi[1]);
					*op++ = CLAMP(tmp + (-(tmp - *ip2) * newsquish[1]), bounds_lo[1], bounds_hi[1]);
					ip++; ip2++;
				}
				else if (bounds_enable_lo[1] && (*ip < bounds_lo[1])) {
					*op2++ = tmp = MAX(*ip, bounds_lo[1]);
					*op++ = MAX(tmp + (-(tmp - *ip2) * newsquish[1]), bounds_lo[1]);
					ip++; ip2++;
				}
				else if (bounds_enable_hi[1] && (*ip > bounds_hi[1])) {
					*op2++ = tmp = MIN(*ip, bounds_hi[1]);
					*op++ = MIN(tmp + (-(tmp - *ip2) * newsquish[1]), bounds_hi[1]);
					ip++; ip2++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if ((bounds_enable_lo[2] && bounds_enable_hi[2]) && ((*ip < bounds_lo[2]) || (*ip > bounds_hi[2]))) {
					*op2++ = tmp = CLAMP(*ip, bounds_lo[2], bounds_hi[2]);
					*op++ = CLAMP(tmp + (-(tmp - *ip2) * newsquish[2]), bounds_lo[2], bounds_hi[2]);
					ip++; ip2++;
				}
				else if (bounds_enable_lo[2] && (*ip < bounds_lo[2])) {
					*op2++ = tmp = MAX(*ip, bounds_lo[2]);
					*op++ = MAX(tmp + (-(tmp - *ip2) * newsquish[2]), bounds_lo[2]);
					ip++; ip2++;
				}
				else if (bounds_enable_hi[2] && (*ip > bounds_hi[2])) {
					*op2++ = tmp = MIN(*ip, bounds_hi[2]);
					*op++ = MIN(tmp + (-(tmp - *ip2) * newsquish[2]), bounds_hi[2]);
					ip++; ip2++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}
			}
			break;
		default:
			while (n-- && *ip) {
				for (j = 0; j < planecount - 2; j++)
					newsquish[j] = squish[j] + (squish_var[j] * jit_p_bounds_random_num(x));

				*op++ = *ip++;			//id
				*op2++ = *ip2++;
				*op++ = *ip++;			//life
				*op2++ = *ip2++;

				for (k = 0; k < planecount - 2; k++) {
					if ((bounds_enable_lo[k] && bounds_enable_hi[k]) && ((*ip < bounds_lo[k]) || (*ip > bounds_hi[k]))) {
						*op2++ = tmp = CLAMP(*ip, bounds_lo[k], bounds_hi[k]);
						*op++ = CLAMP(tmp + (-(tmp - *ip2) * newsquish[k]), bounds_lo[k], bounds_hi[k]);
						ip++; ip2++;
					}
					else if (bounds_enable_lo[k] && (*ip < bounds_lo[k])) {
						*op2++ = tmp = MAX(*ip, bounds_lo[k]);
						*op++ = MAX(tmp + (-(tmp - *ip2) * newsquish[k]), bounds_lo[k]);
						ip++; ip2++;
					}
					else if (bounds_enable_hi[k] && (*ip > bounds_hi[k])) {
						*op2++ = tmp = MIN(*ip, bounds_hi[k]);
						*op++ = MIN(tmp + (-(tmp - *ip2) * newsquish[k]), bounds_hi[k]);
						ip++; ip2++;
					}
					else {
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}
			}
			break;
		}
		break;
	}
}

void jit_p_bounds_calculate_2d_float64(t_jit_p_bounds *x, long dimcount, long *dim, long planecount,
									   t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop)
{
	long j, k, n;
	long width, rowstride;
	double *ip, *op, *ip2, *op2, *kill;
	double squish[JIT_MATRIX_MAX_PLANECOUNT - 2];
	double squish_var[JIT_MATRIX_MAX_PLANECOUNT - 2];
	double newsquish[JIT_MATRIX_MAX_PLANECOUNT - 2];
	double bounds_hi[JIT_MATRIX_MAX_PLANECOUNT - 2];
	double bounds_lo[JIT_MATRIX_MAX_PLANECOUNT - 2];
	double tmp;
	char bounds_enable_hi[JIT_MATRIX_MAX_PLANECOUNT - 2];
	char bounds_enable_lo[JIT_MATRIX_MAX_PLANECOUNT - 2];
	char killflag;

	x->random = jit_rand();

	width = dim[0];
	rowstride = in_minfo->dimstride[1] / 8;

	for (j = 0; j < JIT_MATRIX_MAX_PLANECOUNT - 2; j++) {
		bounds_hi[j] = x->bounds_hi[j];
		bounds_lo[j] = x->bounds_lo[j];
		bounds_enable_hi[j] = x->bounds_enable_hi[j];
		bounds_enable_lo[j] = x->bounds_enable_lo[j];
		squish[j] = x->squish[j];
		squish_var[j] = x->squish_var[j];
	}

//	squish = x->squish;
//	squish_var = x->squish_var;

	ip = (double *)(bip);
	op = (double *)(bop);
	ip2 = ip + rowstride;
	op2 = op + rowstride;
	n = width;
//	newsquish = squish;

	switch(x->mode) {
	case 3: //clip
		switch(planecount) {
		case 5:
			while (n-- && *ip) {
				*op++ = *ip++;			//id
				*op2++ = *ip2++;

				*op++ = *ip++;			//life
				*op2++ = *ip2++;

				if (bounds_enable_lo[0] && (*ip < bounds_lo[0])) {
					*op2++ = *ip2++;
					*op++ = bounds_lo[0];
					ip++;
				}
				else if (bounds_enable_hi[0] && (*ip > bounds_hi[0])) {
					*op2++ = *ip2++;
					*op++ = bounds_hi[0];
					ip++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if (bounds_enable_lo[1] && (*ip < bounds_lo[1])) {
					*op2++ = *ip2++;
					*op++ = bounds_lo[1];
					ip++;
				}
				else if (bounds_enable_hi[1] && (*ip > bounds_hi[1])) {
					*op2++ = *ip2++;
					*op++ = bounds_hi[1];
					ip++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if (bounds_enable_lo[2] && (*ip < bounds_lo[2])) {
					*op2++ = *ip2++;
					*op++ = bounds_lo[2];
					ip++;
				}
				else if (bounds_enable_hi[2] && (*ip > bounds_hi[2])) {
					*op2++ = *ip2++;
					*op++ = bounds_hi[2];
					ip++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}
			}
			break;
		default:
			while (n-- && *ip) {
				*op++ = *ip++;			//id
				*op2++ = *ip2++;

				*op++ = *ip++;			//life
				*op2++ = *ip2++;

				for (k = 0; k < planecount - 2; k++) {
					if (bounds_enable_lo[k] && (*ip < bounds_lo[k])) {
						*op2++ = *ip2++;
						*op++ = bounds_lo[k];
						ip++;
					}
					else if (bounds_enable_hi[k] && (*ip > bounds_hi[k])) {
						*op2++ = *ip2++;
						*op++ = bounds_hi[k];
						ip++;
					}
					else {
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}
			}
			break;
		}
		break;
	case 2: // torus
		switch(planecount) {
		case 5:
			while (n-- && *ip) {
				*op++ = *ip++;			//id
				*op2++ = *ip2++;

				kill = op;
				killflag = 0;

				*op++ = *ip++;			//life
				*op2++ = *ip2++;

				if ((bounds_enable_hi[0] && (*ip > bounds_hi[0]))) {
					if (bounds_enable_lo[0]) {
						*op2++ = bounds_lo[0];
						*op++ = bounds_lo[0] + (*ip++ - *ip2++);
					}
					else {
						killflag = 1;
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}
				else if ((bounds_enable_lo[0] && (*ip < bounds_lo[0]))) {
					if (bounds_enable_hi[0]) {
						*op2++ = bounds_hi[0];
						*op++ = bounds_hi[0] + (*ip++ - *ip2++);
					}
					else {
						killflag = 1;
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if ((bounds_enable_hi[1] && (*ip > bounds_hi[1]))) {
					if (bounds_enable_lo[1]) {
						*op2++ = bounds_lo[1];
						*op++ = bounds_lo[1] + (*ip++ - *ip2++);
					}
					else {
						killflag = 1;
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}
				else if ((bounds_enable_lo[1] && (*ip < bounds_lo[1]))) {
					if (bounds_enable_hi[1]) {
						*op2++ = bounds_hi[1];
						*op++ = bounds_hi[1] + (*ip++ - *ip2++);
					}
					else {
						killflag = 1;
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if ((bounds_enable_hi[2] && (*ip > bounds_hi[2]))) {
					if (bounds_enable_lo[2]) {
						*op2++ = bounds_lo[2];
						*op++ = bounds_lo[2] + (*ip++ - *ip2++);
					}
					else {
						killflag = 1;
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}
				else if ((bounds_enable_lo[2] && (*ip < bounds_lo[2]))) {
					if (bounds_enable_hi[2]) {
						*op2++ = bounds_hi[2];
						*op++ = bounds_hi[2] + (*ip++ - *ip2++);
					}
					else {
						killflag = 1;
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if (killflag)
					*kill = 0;
			}
			break;
		default:
			while (n-- && *ip) {
				*op++ = *ip++;			//id
				*op2++ = *ip2++;

				kill = op;
				killflag = 0;

				*op++ = *ip++;			//life
				*op2++ = *ip2++;

				for (k = 0; k < planecount - 2; k++) {
					if ((bounds_enable_hi[k] && (*ip > bounds_hi[k]))) {
						if (bounds_enable_lo[k]) {
							*op2++ = bounds_lo[k];
							*op++ = bounds_lo[k] + (*ip++ - *ip2++);
						}
						else {
							killflag = 1;
							*op2++ = *ip2++;
							*op++ = *ip++;
						}
					}
					else if ((bounds_enable_lo[k] && (*ip < bounds_lo[k]))) {
						if (bounds_enable_hi[k]) {
							*op2++ = bounds_hi[k];
							*op++ = bounds_hi[k] + (*ip++ - *ip2++);
						}
						else {
							killflag = 1;
							*op2++ = *ip2++;
							*op++ = *ip++;
						}
					}
					else {
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}

				if (killflag)
					*kill = 0;
			}
			break;
		}
		break;
	case 1: //kill
		switch(planecount) {
		case 5:
			while (n-- && *ip) {
				*op++ = *ip++;			//id
				*op2++ = *ip2++;

				kill = op;
				killflag = 0;

				*op++ = *ip++;			//life
				*op2++ = *ip2++;

				if (bounds_enable_lo[0] && (*ip < bounds_lo[0])) {
					killflag = 1;
					*op2++ = *ip2++;
					*op++ = bounds_lo[0];
					ip++;
				}
				else if (bounds_enable_hi[0] && (*ip > bounds_hi[0])) {
					killflag = 1;
					*op2++ = *ip2++;
					*op++ = bounds_hi[0];
					ip++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if (bounds_enable_lo[1] && (*ip < bounds_lo[1])) {
					killflag = 1;
					*op2++ = *ip2++;
					*op++ = bounds_lo[1];
					ip++;
				}
				else if (bounds_enable_hi[1] && (*ip > bounds_hi[1])) {
					killflag = 1;
					*op2++ = *ip2++;
					*op++ = bounds_hi[1];
					ip++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if (bounds_enable_lo[2] && (*ip < bounds_lo[2])) {
					killflag = 1;
					*op2++ = *ip2++;
					*op++ = bounds_lo[2];
					ip++;
				}
				else if (bounds_enable_hi[2] && (*ip > bounds_hi[2])) {
					killflag = 1;
					*op2++ = *ip2++;
					*op++ = bounds_hi[2];
					ip++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if (killflag)
					*kill = 0;
			}
			break;
		default:
			while (n-- && *ip) {
				*op++ = *ip++;			//id
				*op2++ = *ip2++;

				kill = op;
				killflag = 0;

				*op++ = *ip++;			//life
				*op2++ = *ip2++;

				for (k = 0; k < planecount - 2; k++) {
					if (bounds_enable_lo[k] && (*ip < bounds_lo[k])) {
						killflag = 1;
						*op2++ = *ip2++;
						*op++ = bounds_lo[k];
						ip++;
					}
					else if (bounds_enable_hi[k] && (*ip > bounds_hi[k])) {
						killflag = 1;
						*op2++ = *ip2++;
						*op++ = bounds_hi[k];
						ip++;
					}
					else {
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}

				if (killflag)
					*kill = 0;
			}
			break;
		}
		break;
	case 0:
	default: // bounce
		switch(planecount) {
		case 5:
			while (n-- && *ip) {
				for (j = 0; j < 3; j++)
					newsquish[j] = squish[j] + (squish_var[j] * jit_p_bounds_random_num(x));

				*op++ = *ip++;			//id
				*op2++ = *ip2++;
				*op++ = *ip++;			//life
				*op2++ = *ip2++;

				if ((bounds_enable_lo[0] && bounds_enable_hi[0]) && ((*ip < bounds_lo[0]) || (*ip > bounds_hi[0]))) {
					*op2++ = tmp = CLAMP(*ip, bounds_lo[0], bounds_hi[0]);
					*op++ = CLAMP(tmp + (-(tmp - *ip2) * newsquish[0]), bounds_lo[0], bounds_hi[0]);
					ip++; ip2++;
				}
				else if (bounds_enable_lo[0] && (*ip < bounds_lo[0])) {
					*op2++ = tmp = MAX(*ip, bounds_lo[0]);
					*op++ = MAX(tmp + (-(tmp - *ip2) * newsquish[0]), bounds_lo[0]);
					ip++; ip2++;
				}
				else if (bounds_enable_hi[0] && (*ip > bounds_hi[0])) {
					*op2++ = tmp = MIN(*ip, bounds_hi[0]);
					*op++ = MIN(tmp + (-(tmp - *ip2) * newsquish[0]), bounds_hi[0]);
					ip++; ip2++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if ((bounds_enable_lo[1] && bounds_enable_hi[1]) && ((*ip < bounds_lo[1]) || (*ip > bounds_hi[1]))) {
					*op2++ = tmp = CLAMP(*ip, bounds_lo[1], bounds_hi[1]);
					*op++ = CLAMP(tmp + (-(tmp - *ip2) * newsquish[1]), bounds_lo[1], bounds_hi[1]);
					ip++; ip2++;
				}
				else if (bounds_enable_lo[1] && (*ip < bounds_lo[1])) {
					*op2++ = tmp = MAX(*ip, bounds_lo[1]);
					*op++ = MAX(tmp + (-(tmp - *ip2) * newsquish[1]), bounds_lo[1]);
					ip++; ip2++;
				}
				else if (bounds_enable_hi[1] && (*ip > bounds_hi[1])) {
					*op2++ = tmp = MIN(*ip, bounds_hi[1]);
					*op++ = MIN(tmp + (-(tmp - *ip2) * newsquish[1]), bounds_hi[1]);
					ip++; ip2++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}

				if ((bounds_enable_lo[2] && bounds_enable_hi[2]) && ((*ip < bounds_lo[2]) || (*ip > bounds_hi[2]))) {
					*op2++ = tmp = CLAMP(*ip, bounds_lo[2], bounds_hi[2]);
					*op++ = CLAMP(tmp + (-(tmp - *ip2) * newsquish[2]), bounds_lo[2], bounds_hi[2]);
					ip++; ip2++;
				}
				else if (bounds_enable_lo[2] && (*ip < bounds_lo[2])) {
					*op2++ = tmp = MAX(*ip, bounds_lo[2]);
					*op++ = MAX(tmp + (-(tmp - *ip2) * newsquish[2]), bounds_lo[2]);
					ip++; ip2++;
				}
				else if (bounds_enable_hi[2] && (*ip > bounds_hi[2])) {
					*op2++ = tmp = MIN(*ip, bounds_hi[2]);
					*op++ = MIN(tmp + (-(tmp - *ip2) * newsquish[2]), bounds_hi[2]);
					ip++; ip2++;
				}
				else {
					*op2++ = *ip2++;
					*op++ = *ip++;
				}
			}
			break;
		default:
			while (n-- && *ip) {
				for (j = 0; j < planecount - 2; j++)
					newsquish[j] = squish[j] + (squish_var[j] * jit_p_bounds_random_num(x));

				*op++ = *ip++;			//id
				*op2++ = *ip2++;
				*op++ = *ip++;			//life
				*op2++ = *ip2++;

				for (k = 0; k < planecount - 2; k++) {
					if ((bounds_enable_lo[k] && bounds_enable_hi[k]) && ((*ip < bounds_lo[k]) || (*ip > bounds_hi[k]))) {
						*op2++ = tmp = CLAMP(*ip, bounds_lo[k], bounds_hi[k]);
						*op++ = CLAMP(tmp + (-(tmp - *ip2) * newsquish[k]), bounds_lo[k], bounds_hi[k]);
						ip++; ip2++;
					}
					else if (bounds_enable_lo[k] && (*ip < bounds_lo[k])) {
						*op2++ = tmp = MAX(*ip, bounds_lo[k]);
						*op++ = MAX(tmp + (-(tmp - *ip2) * newsquish[k]), bounds_lo[k]);
						ip++; ip2++;
					}
					else if (bounds_enable_hi[k] && (*ip > bounds_hi[k])) {
						*op2++ = tmp = MIN(*ip, bounds_hi[k]);
						*op++ = MIN(tmp + (-(tmp - *ip2) * newsquish[k]), bounds_hi[k]);
						ip++; ip2++;
					}
					else {
						*op2++ = *ip2++;
						*op++ = *ip++;
					}
				}
			}
			break;
		}
		break;
	}
}

t_jit_p_bounds *jit_p_bounds_new(void)
{
	t_jit_p_bounds *x;
	long i;

	if (x=(t_jit_p_bounds *)jit_object_alloc(_jit_p_bounds_class)) {
		jit_rand_setseed(0);

		for (i = 0; i < JIT_MATRIX_MAX_PLANECOUNT - 2; i++) {
			x->bounds_hi[i] = 1.;
			x->bounds_lo[i] = -1.;
			x->bounds_enable_hi[i] = 0;
			x->bounds_enable_lo[i] = 0;
			x->squish[i] = 1.;
			x->squish_var[i] = 0;
		}

		x->boundscount_hi = x->boundscount_lo = 0.;
		x->mode = 0;
	}
	else {
		x = NULL;
	}
	return x;
}

void jit_p_bounds_free(t_jit_p_bounds *x)
{
	//nada
}