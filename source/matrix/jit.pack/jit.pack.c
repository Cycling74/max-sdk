/*
	Copyright 2001 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"

typedef struct _jit_pack
{
	t_object	ob;
	long		index;
	long		offset[JIT_MATRIX_MAX_PLANECOUNT];
	long		offsetcount;
	long		jump[JIT_MATRIX_MAX_PLANECOUNT];
	long		jumpcount;
} t_jit_pack;

void *_jit_pack_class;

t_jit_err jit_pack_init(void);
t_jit_pack *jit_pack_new(void);
void jit_pack_free(t_jit_pack *x);
t_jit_err jit_pack_matrix_calc(t_jit_pack *x, void *inputs, void *outputs);
void jit_pack_calculate_ndim(long dimcount, long *dim, long plane, long offset,
							 t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop);

t_jit_err jit_pack_offset(t_jit_pack *x, t_symbol *s, long argc, t_atom *argv);
t_jit_err jit_pack_jump(t_jit_pack *x, t_symbol *s, long argc, t_atom *argv);

t_jit_err jit_pack_init(void)
{
	long attrflags;
	void *mop,*o,*attr;

	_jit_pack_class = jit_class_new("jit_pack",(method)jit_pack_new,(method)jit_pack_free,
									sizeof(t_jit_pack),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,-1,1); //#inputs,#outputs(variable)
	o = jit_object_method(mop,_jit_sym_getoutput,1);
	jit_attr_setlong(o,_jit_sym_planelink,0);
	jit_class_addadornment(_jit_pack_class,mop);
	//add methods
	jit_class_addmethod(_jit_pack_class, (method)jit_pack_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);
	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;

	//alias for backward compatibility
	attr = jit_object_new(_jit_sym_jit_attr_offset,"plane",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_pack,index));
	jit_class_addattr(_jit_pack_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Plane");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"index",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_pack,index));
	jit_class_addattr(_jit_pack_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Index");

	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"offset",_jit_sym_long,JIT_MATRIX_MAX_PLANECOUNT,attrflags,
						  (method)0L,(method)jit_pack_offset,calcoffset(t_jit_pack,offsetcount), calcoffset(t_jit_pack,offset));
	jit_class_addattr(_jit_pack_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Offset");

	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"jump",_jit_sym_long,JIT_MATRIX_MAX_PLANECOUNT,attrflags,
						  (method)0L,(method)jit_pack_jump,calcoffset(t_jit_pack,jumpcount), calcoffset(t_jit_pack,jump));
	jit_class_addattr(_jit_pack_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Jump");

	jit_class_register(_jit_pack_class);

	return JIT_ERR_NONE;
}

t_jit_err jit_pack_offset(t_jit_pack *x, t_symbol *s, long argc, t_atom *argv)
{
	long i;

	for (i=0; i < argc; i++) {
		x->offset[i] = MAX( jit_atom_getlong(argv + i), 0);
	}

	while(i < JIT_MATRIX_MAX_PLANECOUNT) {
		x->offset[i] = 0;
		i++;
	}

	return JIT_ERR_NONE;
}

t_jit_err jit_pack_jump(t_jit_pack *x, t_symbol *s, long argc, t_atom *argv)
{
	long i;

	for (i=0; i < argc; i++) {
		x->jump[i] = MAX( jit_atom_getlong(argv + i), 1);
	}

	while(i < JIT_MATRIX_MAX_PLANECOUNT) {
		x->jump[i] = 1;
		i++;
	}

	return JIT_ERR_NONE;
}

t_jit_err jit_pack_matrix_calc(t_jit_pack *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock,out_savelock;
	t_jit_matrix_info in_minfo,out_minfo;
	char *in_bp,*out_bp;
	long i,j,dimcount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	void *in_matrix,*out_matrix;
	long in_count,in_idx,in_plane,out_plane,k,n;

	in_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);
	out_matrix 	= jit_object_method(outputs,_jit_sym_getindex,0);
	in_count	= (long) jit_object_method(inputs,_jit_sym_getsize);
	if (in_count<=0)
		in_count = 1;

	in_idx = x->index;

	for (j=0; j<in_count; j++) {
		//handles case where jit.pack is used in JS
		if (in_count>1) {
			in_matrix = jit_object_method(inputs,_jit_sym_getindex,j);
			in_idx = j;
		}

		if (x&&in_matrix&&out_matrix) {
			in_savelock = (long) jit_object_method(in_matrix,_jit_sym_lock,1);
			out_savelock = (long) jit_object_method(out_matrix,_jit_sym_lock,1);
			jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
			jit_object_method(in_matrix,_jit_sym_getdata,&in_bp);
			jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);
			jit_object_method(out_matrix,_jit_sym_getdata,&out_bp);

			if (!in_bp) { err=JIT_ERR_INVALID_INPUT; goto out;}
			if (!out_bp) { err=JIT_ERR_INVALID_OUTPUT; goto out;}

			//compatible types?
			if ((in_minfo.type!=out_minfo.type)) {
				err=JIT_ERR_MISMATCH_TYPE;
				goto out;
			}

			//get dimensions/planecount
			dimcount = out_minfo.dimcount;
			if (in_idx>=out_minfo.planecount) {
				err=JIT_ERR_MISMATCH_PLANE;
				goto out;
			}

			for (i=0; i<dimcount; i++) {
				//if dimsize is 1, treat as infinite domain across that dimension.
				//otherwise truncate if less than the output dimsize
				dim[i] = out_minfo.dim[i];
				if ((in_minfo.dim[i]<dim[i])&&in_minfo.dim[i]>1) {
					dim[i] = in_minfo.dim[i];
				}
			}

			// use up to N planes of input from the jump attribute
			for (k=0; k<x->jump[in_idx]; k++) {
				in_plane = ABS(x->offset[in_idx]) + k;

				//increment output plane offset to sum of preceding jumps
				out_plane = k;
				for (n=0; n<(in_idx); n++)
					out_plane += ABS(x->jump[n]);

				//only copy if within input and output planecount range
				if ((out_plane>=0)&&(out_plane<out_minfo.planecount)&&
						(in_plane>=0)&&(in_plane<in_minfo.planecount))
				{
					//jit_object_post((t_object *)x,"copying in_plane=%d to out_plane%d for in_idx=%d",in_plane,out_plane,in_idx);
					jit_pack_calculate_ndim(dimcount, dim, out_plane, in_plane, &in_minfo, in_bp, &out_minfo, out_bp);
				} else {
					//jit_object_post((t_object *)x,"out of range in_plane=%d to out_plane%d for in_idx=%d",in_plane,out_plane,in_idx);
				}
			}
		} else {
			return JIT_ERR_INVALID_PTR;
		}

out:
		jit_object_method(out_matrix,_jit_sym_lock,out_savelock);
		jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	}
	return err;
}


void jit_pack_calculate_ndim(long dimcount, long *dim, long plane, long offset,
							 t_jit_matrix_info *in_minfo, char *bip, t_jit_matrix_info *out_minfo, char *bop)
{
	long i,j,n;
	char *ip,*op;
	t_jit_op_info in_opinfo,out_opinfo;

	if (dimcount<1) return; //safety

	switch(dimcount) {
	case 1:
		dim[1]=1;
	case 2:
		//if planecount the same, flatten planes - treat as single plane data for speed
		n = dim[0];
		in_opinfo.stride = in_minfo->dim[0]>1?in_minfo->planecount:0;
		out_opinfo.stride = out_minfo->dim[0]>1?out_minfo->planecount:0;
		if (in_minfo->type==_jit_sym_char) {
			for (i=0; i<dim[1]; i++) {
				in_opinfo.p  = bip + i*in_minfo->dimstride[1] + offset;
				out_opinfo.p = bop + i*out_minfo->dimstride[1] + plane;
				jit_op_vector_pass_char(n, NULL, &in_opinfo, NULL, &out_opinfo);
			}
		} else if (in_minfo->type==_jit_sym_long) {
			for (i=0; i<dim[1]; i++) {
				in_opinfo.p  = bip + i*in_minfo->dimstride[1] + offset*4;
				out_opinfo.p = bop + i*out_minfo->dimstride[1] + plane*4;
				jit_op_vector_pass_long(n, NULL, &in_opinfo, NULL, &out_opinfo);
			}
		} else if (in_minfo->type==_jit_sym_float32) {
			for (i=0; i<dim[1]; i++) {
				in_opinfo.p  = bip + i*in_minfo->dimstride[1] + offset*4;
				out_opinfo.p = bop + i*out_minfo->dimstride[1] + plane*4;
				jit_op_vector_pass_float32(n, NULL, &in_opinfo, NULL, &out_opinfo);
			}
		} else if (in_minfo->type==_jit_sym_float64) {
			for (i=0; i<dim[1]; i++) {
				in_opinfo.p  = bip + i*in_minfo->dimstride[1] + offset*8;
				out_opinfo.p = bop + i*out_minfo->dimstride[1] + plane*8;
				jit_op_vector_pass_float64(n, NULL, &in_opinfo, NULL, &out_opinfo);
			}
		}
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			ip = bip + i*in_minfo->dimstride[dimcount-1];
			op = bop + i*out_minfo->dimstride[dimcount-1];
			jit_pack_calculate_ndim(dimcount-1,dim,plane,offset,in_minfo,ip,out_minfo,op);
		}
	}
}

t_jit_pack *jit_pack_new(void)
{
	t_jit_pack *x;
	long i;

	if (x=(t_jit_pack *)jit_object_alloc(_jit_pack_class)) {
		x->index = 0;
		x->offsetcount = JIT_MATRIX_MAX_PLANECOUNT; // else won't work for the general case
		x->jumpcount = JIT_MATRIX_MAX_PLANECOUNT; // else won't work for the general case

		for(i=0; i < JIT_MATRIX_MAX_PLANECOUNT; i++) {
			x->offset[i] = 0;
			x->jump[i] = 1;
		}

	} else {
		x = NULL;
	}
	return x;
}

void jit_pack_free(t_jit_pack *x)
{
	//nada
}
