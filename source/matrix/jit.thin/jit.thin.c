/*
	Copyright 2001 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"

typedef struct _jit_thin
{
	t_object				ob;
} t_jit_thin;

void *_jit_thin_class;

t_jit_err jit_thin_init(void);
t_jit_thin *jit_thin_new(void);
void jit_thin_free(t_jit_thin *x);
t_jit_err jit_thin_matrix_calc(t_jit_thin *x, void *inputs, void *outputs);
t_jit_err jit_thin_map(t_jit_thin *x, void *attr, long argc, t_atom *argv);

void jit_thin_calculate_ndim(long dim, long *dimsize, long planecount, void *vecdata, t_jit_matrix_info *in_minfo, char *bip,
							 t_jit_matrix_info *out_minfo, char *bop);

t_jit_err jit_thin_init(void)
{
	long attrflags=0;
	t_jit_object *attr,*mop,*o;
	t_symbol *atsym;

	atsym = gensym("jit_attr_offset");

	_jit_thin_class = jit_class_new("jit_thin",(method)jit_thin_new,(method)jit_thin_free,
									sizeof(t_jit_thin),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,1);
	jit_mop_output_nolink(mop,1);
	jit_class_addadornment(_jit_thin_class,mop);
	o = jit_object_method(mop,_jit_sym_getoutput,1);
	//add methods
	jit_class_addmethod(_jit_thin_class, (method)jit_thin_matrix_calc, "matrix_calc", A_CANT, 0L);

	jit_class_register(_jit_thin_class);

	return JIT_ERR_NONE;
}

t_jit_err jit_thin_matrix_calc(t_jit_thin *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long i,dimcount,in_savelock;
	char *in_bp;
	t_jit_matrix_info in_minfo,out_minfo,tmp_minfo;
	void *in_matrix,*out_matrix,*tmp_matrix=NULL;

	in_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);
	out_matrix 	= jit_object_method(outputs,_jit_sym_getindex,0);

	if (x&&in_matrix&&out_matrix) {
		in_savelock = (long) jit_object_method(in_matrix,_jit_sym_lock,1);
		jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
		jit_object_method(in_matrix,_jit_sym_getdata,&in_bp);

		if (!in_bp) { err = JIT_ERR_INVALID_INPUT; goto out; }

		tmp_minfo = in_minfo;
		tmp_minfo.flags = JIT_MATRIX_DATA_REFERENCE|JIT_MATRIX_DATA_FLAGS_USE;

		dimcount = 0;
		for (i=0; i<in_minfo.dimcount; i++) {
			if (in_minfo.dim[i]>1) {
				tmp_minfo.dim[dimcount] = in_minfo.dim[i];
				tmp_minfo.dimstride[dimcount] = in_minfo.dimstride[i];
				dimcount++;
			}
		}
		if (dimcount==0) {
			dimcount = 1;
			tmp_minfo.dim[0] = 1;
			tmp_minfo.dimstride[0] = 0;
		}
		tmp_minfo.dimcount = dimcount;

		tmp_matrix = jit_object_new(_jit_sym_jit_matrix,&tmp_minfo);

		if (!tmp_matrix) { err = JIT_ERR_OUT_OF_MEM; goto out; }

		jit_object_method(tmp_matrix,gensym("data"),in_bp);

		out_minfo = tmp_minfo;
		out_minfo.flags = 0;
		err = (t_jit_err) jit_object_method(out_matrix,_jit_sym_setinfo,&out_minfo);

		if (err) goto out;

		jit_object_method(out_matrix,_jit_sym_frommatrix,tmp_matrix,NULL);

	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	if (tmp_matrix) jit_object_free(tmp_matrix);
	jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	return err;

}

t_jit_thin *jit_thin_new(void)
{
	t_jit_thin *x;
	long i;

	if (x=(t_jit_thin *)jit_object_alloc(_jit_thin_class)) {

	} else {
		x = NULL;
	}
	return x;
}

void jit_thin_free(t_jit_thin *x)
{
	//nada
}
