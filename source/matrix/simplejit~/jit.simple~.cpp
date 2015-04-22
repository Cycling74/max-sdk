/**
	@file
	max.jit.simple~ - simple example of an MSP+Jitter combination external.
	+ multiplies an incoming matrix by a constant, which can be set using an audio signal.

	@ingroup	examples
	@see		jit.simple
	@see		max.jit.simple

	Copyright 2009 - Cycling '74
	Timothy Place, tim@cycling74.com
*/

#include "jit.common.h"


// Our Jitter object instance data
typedef struct _jit_simple {
	t_object	ob;
	double		gain;	// our attribute (multiplied against each cell in the matrix)
} t_jit_simple;


// prototypes
BEGIN_USING_C_LINKAGE
t_jit_err		jit_simple_init				(void);
t_jit_simple	*jit_simple_new				(void);
void			jit_simple_free				(t_jit_simple *x);
t_jit_err		jit_simple_matrix_calc		(t_jit_simple *x, void *inputs, void *outputs);
void			jit_simple_calculate_ndim	(t_jit_simple *x, long dim, long *dimsize, long planecount, t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop);
END_USING_C_LINKAGE


// globals
static void *s_jit_simple_class = NULL;


/************************************************************************************/

t_jit_err jit_simple_init(void)
{
	long			attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	t_jit_object	*attr;
	t_jit_object	*mop;

	s_jit_simple_class = jit_class_new("jit_simple~", (method)jit_simple_new, (method)jit_simple_free, sizeof(t_jit_simple), 0);

	// add matrix operator (mop)
	mop = (t_jit_object *)jit_object_new(_jit_sym_jit_mop, 1, 1); // args are  num inputs and num outputs
	jit_class_addadornment(s_jit_simple_class, mop);

	// add method(s)
	jit_class_addmethod(s_jit_simple_class, (method)jit_simple_matrix_calc, "matrix_calc", A_CANT, 0);

	// add attribute(s)
	attr = (t_jit_object *)jit_object_new(_jit_sym_jit_attr_offset,
										  "gain",
										  _jit_sym_float64,
										  attrflags,
										  (method)NULL, (method)NULL,
										  calcoffset(t_jit_simple, gain));
	jit_class_addattr(s_jit_simple_class, attr);

	// finalize class
	jit_class_register(s_jit_simple_class);
	return JIT_ERR_NONE;
}


/************************************************************************************/
// Object Life Cycle

t_jit_simple *jit_simple_new(void)
{
	t_jit_simple	*x = NULL;

	x = (t_jit_simple *)jit_object_alloc(s_jit_simple_class);
	if (x) {
		x->gain = 0.0;
	}
	return x;
}


void jit_simple_free(t_jit_simple *x)
{
	;	// nothing to free for our simple object
}


/************************************************************************************/
// Methods bound to input/inlets

t_jit_err jit_simple_matrix_calc(t_jit_simple *x, void *inputs, void *outputs)
{
	t_jit_err			err = JIT_ERR_NONE;
	long				in_savelock;
	long				out_savelock;
	t_jit_matrix_info	in_minfo;
	t_jit_matrix_info	out_minfo;
	char				*in_bp;
	char				*out_bp;
	long				i;
	long				dimcount;
	long				planecount;
	long				dim[JIT_MATRIX_MAX_DIMCOUNT];
	void				*in_matrix;
	void				*out_matrix;

	in_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);
	out_matrix 	= jit_object_method(outputs,_jit_sym_getindex,0);

	if (x && in_matrix && out_matrix) {
		in_savelock = (long) jit_object_method(in_matrix, _jit_sym_lock, 1);
		out_savelock = (long) jit_object_method(out_matrix, _jit_sym_lock, 1);

		jit_object_method(in_matrix, _jit_sym_getinfo, &in_minfo);
		jit_object_method(out_matrix, _jit_sym_getinfo, &out_minfo);

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
		if (in_minfo.type != out_minfo.type) {
			err = JIT_ERR_MISMATCH_TYPE;
			goto out;
		}

		//get dimensions/planecount
		dimcount   = out_minfo.dimcount;
		planecount = out_minfo.planecount;

		for (i=0; i<dimcount; i++) {
			//if dimsize is 1, treat as infinite domain across that dimension.
			//otherwise truncate if less than the output dimsize
			dim[i] = out_minfo.dim[i];
			if ((in_minfo.dim[i]<dim[i]) && in_minfo.dim[i]>1) {
				dim[i] = in_minfo.dim[i];
			}
		}

		jit_parallel_ndim_simplecalc2((method)jit_simple_calculate_ndim,
									  x, dimcount, dim, planecount, &in_minfo, in_bp, &out_minfo, out_bp,
									  0 /* flags1 */, 0 /* flags2 */);

	}
	else
		return JIT_ERR_INVALID_PTR;

out:
	jit_object_method(out_matrix,_jit_sym_lock,out_savelock);
	jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	return err;
}


// We are using a C++ template to process a vector of the matrix for any of the given types.
// Thus, we don't need to duplicate the code for each datatype.
template<typename T>
void jit_simple_vector(t_jit_simple *x, long n, t_jit_op_info *in, t_jit_op_info *out)
{
	double	gain = x->gain;
	T		*ip;
	T		*op;
	long	is,
			os;
	long	tmp;

	ip = ((T *)in->p);
	op = ((T *)out->p);
	is = in->stride;
	os = out->stride;

	if ((is==1) && (os==1)) {
		++n;
		--op;
		--ip;
		while (--n) {
			tmp = *++ip;
			*++op = tmp * gain;
		}
	}
	else {
		while (n--) {
			tmp = *ip;
			*op = tmp * gain;
			ip += is;
			op += os;
		}
	}
}


// We also use a C+ template for the loop that wraps the call to jit_simple_vector(),
// further reducing code duplication in jit_simple_calculate_ndim().
// The calls into these templates should be inlined by the compiler, eliminating concern about any added function call overhead.
template<typename T>
void jit_simple_loop(t_jit_simple *x, long n, t_jit_op_info *in_opinfo, t_jit_op_info *out_opinfo, t_jit_matrix_info *in_minfo, t_jit_matrix_info *out_minfo, char *bip, char *bop, long *dim, long planecount, long datasize)
{
	long	i;
	long	j;

	for (i=0; i<dim[1]; i++) {
		for (j=0; j<planecount; j++) {
			in_opinfo->p  = bip + i * in_minfo->dimstride[1]  + (j % in_minfo->planecount) * datasize;
			out_opinfo->p = bop + i * out_minfo->dimstride[1] + (j % out_minfo->planecount) * datasize;
			jit_simple_vector<T>(x, n, in_opinfo, out_opinfo);
		}
	}
}


void jit_simple_calculate_ndim(t_jit_simple *x, long dimcount, long *dim, long planecount, t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop)
{
	long			i;
	long			n;
	char			*ip;
	char			*op;
	t_jit_op_info	in_opinfo;
	t_jit_op_info	out_opinfo;

	if (dimcount < 1)
		return; // safety

	switch (dimcount) {
	case 1:
		dim[1]=1;
		// (fall-through to next case is intentional)
	case 2:
		// if planecount is the same then flatten planes - treat as single plane data for speed
		n = dim[0];
		if ((in_minfo->dim[0] > 1) && (out_minfo->dim[0] > 1) && (in_minfo->planecount == out_minfo->planecount)) {
			in_opinfo.stride = 1;
			out_opinfo.stride = 1;
			n *= planecount;
			planecount = 1;
		}
		else {
			in_opinfo.stride =  in_minfo->dim[0]>1  ? in_minfo->planecount  : 0;
			out_opinfo.stride = out_minfo->dim[0]>1 ? out_minfo->planecount : 0;
		}

		if (in_minfo->type == _jit_sym_char)
			jit_simple_loop<uchar>(x, n, &in_opinfo, &out_opinfo, in_minfo, out_minfo, bip, bop, dim, planecount, 1);
		else if (in_minfo->type == _jit_sym_long)
			jit_simple_loop<long>(x, n, &in_opinfo, &out_opinfo, in_minfo, out_minfo, bip, bop, dim, planecount, 4);
		else if (in_minfo->type == _jit_sym_float32)
			jit_simple_loop<float>(x, n, &in_opinfo, &out_opinfo, in_minfo, out_minfo, bip, bop, dim, planecount, 4);
		else if (in_minfo->type == _jit_sym_float64)
			jit_simple_loop<double>(x, n, &in_opinfo, &out_opinfo, in_minfo, out_minfo, bip, bop, dim, planecount, 8);
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			ip = bip + i * in_minfo->dimstride[dimcount-1];
			op = bop + i * out_minfo->dimstride[dimcount-1];
			jit_simple_calculate_ndim(x, dimcount-1, dim, planecount, in_minfo, ip, out_minfo, op);
		}
	}
}
