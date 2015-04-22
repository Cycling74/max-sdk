/*
	Copyright 2001 - Cycling '74
	R. Luke DuBois luke@music.columbia.edu
*/

#include "jit.common.h"

typedef struct _jit_glue
{
	t_object				ob;
	long					rows;
	long					cols;
	long					input;

} t_jit_glue;

void *_jit_glue_class;


t_jit_glue *jit_glue_new(void);
void jit_glue_free(t_jit_glue *x);
t_jit_err jit_glue_matrix_calc(t_jit_glue *x, void *inputs, void *outputs);
t_jit_err jit_glue_init(void);


t_jit_err jit_glue_init(void)
{
	long attrflags=0;
	void *attr,*mop,*o;

	_jit_glue_class = jit_class_new("jit_glue",(method)jit_glue_new,(method)jit_glue_free,
									sizeof(t_jit_glue),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,-1,1); //#inputs,#outputs(variable)
	o = jit_object_method(mop,_jit_sym_getoutput,1);
	jit_attr_setlong(o,_jit_sym_dimlink,0);
	jit_class_addadornment(_jit_glue_class,mop);
	//add methods
	jit_class_addmethod(_jit_glue_class, (method)jit_glue_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);

	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;

	CLASS_STICKY_CATEGORY(_jit_glue_class,0,"Behavior");
	CLASS_STICKY_ATTR(_jit_glue_class,"basic",0,"1");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"rows",_jit_sym_long,attrflags,
						  (method)0,(method)0,calcoffset(t_jit_glue,rows));
	jit_attr_addfilterset_clip(attr,1,16,1,1);
	jit_class_addattr(_jit_glue_class,attr);
	CLASS_ATTR_LABEL(_jit_glue_class,"rows",0,"Rows");

	attr = jit_object_new(_jit_sym_jit_attr_offset,"columns",_jit_sym_long,attrflags,
						  (method)0,(method)0,calcoffset(t_jit_glue,cols));
	jit_attr_addfilterset_clip(attr,1,16,1,1);
	jit_class_addattr(_jit_glue_class,attr);
	CLASS_ATTR_LABEL(_jit_glue_class,"columns",0,"Columns");

	CLASS_STICKY_CATEGORY_CLEAR(_jit_glue_class);
	CLASS_STICKY_ATTR_CLEAR(_jit_glue_class, "basic");

	attrflags = JIT_ATTR_GET_OPAQUE_USER | JIT_ATTR_SET_OPAQUE_USER;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"input",_jit_sym_long,attrflags,
						  (method)0,(method)0,calcoffset(t_jit_glue,input));
	jit_class_addattr(_jit_glue_class,attr);

	jit_class_register(_jit_glue_class);

	return JIT_ERR_NONE;
}


t_jit_err jit_glue_matrix_calc(t_jit_glue *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in_savelock,out_savelock, dimmode;
	t_jit_matrix_info in_minfo,out_minfo;
	char *in_bp,*out_bp;
	long i,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	t_atom a[2];
	t_matrix_conv_info conv;
	long rows=x->rows,cols=x->cols,n=x->input;
	void *in_matrix,*out_matrix;

	in_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);
	out_matrix 	= jit_object_method(outputs,_jit_sym_getindex,0);

	if (x&&in_matrix&&out_matrix) {

		in_savelock = (long) jit_object_method(in_matrix,_jit_sym_lock,1);
		out_savelock = (long) jit_object_method(out_matrix,_jit_sym_lock,1);

		jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
		jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);

		jit_object_method(in_matrix,_jit_sym_getdata,&in_bp);
		jit_object_method(out_matrix,_jit_sym_getdata,&out_bp);

		if (!in_bp) { err=JIT_ERR_INVALID_INPUT; goto out;}
		if (!out_bp) { err=JIT_ERR_INVALID_OUTPUT; goto out;}

		//compatible types?
		if (in_minfo.type!=out_minfo.type) {
			err=JIT_ERR_MISMATCH_TYPE;
			goto out;
		}

		//compatible planes?
		if ((in_minfo.planecount!=out_minfo.planecount)) {
			err=JIT_ERR_MISMATCH_PLANE;
			goto out;
		}

		//compatible dims?
		if ((in_minfo.dimcount!=2)||(out_minfo.dimcount!=2)) {
			err=JIT_ERR_MISMATCH_DIM;
			goto out;
		}

		//get dimensions/planecount

		if (rows<1) rows=1;
		if (rows>16) rows=16;
		if (cols<1) cols=1;
		if (cols>16) cols=16;

		if (n>=(rows*cols)) goto out;

		dimcount   = out_minfo.dimcount;
		planecount = out_minfo.planecount;
		dim[0] = in_minfo.dim[0]*cols;
		dim[1] = in_minfo.dim[1]*rows;

		if((out_minfo.dim[0]!=dim[0]) || (out_minfo.dim[1]!=dim[1])) {
			jit_atom_setlong(&a[0], dim[0]);
			jit_atom_setlong(&a[1], dim[1]);
			jit_object_method(out_matrix, _jit_sym_dim, 2, a);

		}

		memset(&conv,0,sizeof(t_matrix_conv_info));
		for(i=0; i<JIT_MATRIX_MAX_PLANECOUNT; i++) {
			conv.planemap[i] = i;
		}

		conv.flags = JIT_MATRIX_CONVERT_SRCDIM | JIT_MATRIX_CONVERT_DSTDIM;

		conv.srcdimstart[0] = 0;
		conv.srcdimstart[1] = 0;
		conv.srcdimend[0] = in_minfo.dim[0]-1;
		conv.srcdimend[1] = in_minfo.dim[1]-1;

		conv.dstdimstart[0] = in_minfo.dim[0]*(n%cols);
		conv.dstdimstart[1] = (in_minfo.dim[1]*(n/cols));
		conv.dstdimend[0] = conv.dstdimstart[0]+in_minfo.dim[0]-1;
		conv.dstdimend[1] = conv.dstdimstart[1]+in_minfo.dim[1]-1;

//		jit_object_post((t_object *)x,"compositing %i from %i %i %i %i to %i %i %i %i", n, conv.srcdimstart[0], conv.srcdimstart[1], conv.srcdimend[0], conv.srcdimend[1], conv.dstdimstart[0], conv.dstdimstart[1], conv.dstdimend[0], conv.dstdimend[1]);

		jit_object_method(out_matrix, _jit_sym_frommatrix, in_matrix, &conv);

	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(out_matrix,_jit_sym_lock,out_savelock);
	jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	return err;
}


t_jit_glue *jit_glue_new(void)
{
	t_jit_glue *x;
	short i;

	if (x=(t_jit_glue *)jit_object_alloc(_jit_glue_class)) {
		x->rows=1;
		x->cols=1;
	} else {
		x = NULL;
	}
	return x;
}

void jit_glue_free(t_jit_glue *x)
{
	//nada
}

