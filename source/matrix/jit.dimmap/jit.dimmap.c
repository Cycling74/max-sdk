/*
	Copyright 2001 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"

typedef struct _jit_dimmap
{
	t_object				ob;
	long					mapcount;
	long					map[JIT_MATRIX_MAX_DIMCOUNT];
	long					invertcount;
	long					invert[JIT_MATRIX_MAX_DIMCOUNT];
} t_jit_dimmap;

void *_jit_dimmap_class;

t_jit_err jit_dimmap_init(void);
t_jit_dimmap *jit_dimmap_new(void);
void jit_dimmap_free(t_jit_dimmap *x);
t_jit_err jit_dimmap_matrix_calc(t_jit_dimmap *x, void *inputs, void *outputs);
t_jit_err jit_dimmap_map(t_jit_dimmap *x, void *attr, long argc, t_atom *argv);

void jit_dimmap_calculate_ndim(long dim, long *dimsize, long planecount, void *vecdata, t_jit_matrix_info *in_minfo, char *bip,
							   t_jit_matrix_info *out_minfo, char *bop);

t_jit_err jit_dimmap_init(void)
{
	long attrflags=0;
	t_jit_object *attr,*mop,*o;
	t_symbol *atsym;

	atsym = gensym("jit_attr_offset");

	_jit_dimmap_class = jit_class_new("jit_dimmap",(method)jit_dimmap_new,(method)jit_dimmap_free,
									  sizeof(t_jit_dimmap),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,1);
	jit_mop_output_nolink(mop,1);
	jit_class_addadornment(_jit_dimmap_class,mop);
	o = jit_object_method(mop,_jit_sym_getoutput,1);
	//add methods
	jit_class_addmethod(_jit_dimmap_class, (method)jit_dimmap_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);
	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;

	CLASS_STICKY_CATEGORY(_jit_dimmap_class,0,"Behavior");
	CLASS_STICKY_ATTR(_jit_dimmap_class,"basic",0,"1");

	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"map",_jit_sym_long,JIT_MATRIX_MAX_DIMCOUNT,attrflags,
						  (method)0L,(method)jit_dimmap_map,calcoffset(t_jit_dimmap,mapcount),calcoffset(t_jit_dimmap,map));
	jit_class_addattr(_jit_dimmap_class,attr);
	CLASS_ATTR_LABEL(_jit_dimmap_class,"map",0,"Dimension Map");

	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"invert",_jit_sym_long,JIT_MATRIX_MAX_DIMCOUNT,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_dimmap,invertcount),calcoffset(t_jit_dimmap,invert));
	jit_class_addattr(_jit_dimmap_class,attr);
	CLASS_ATTR_LABEL(_jit_dimmap_class,"invert",0,"Dimension Invert");

	CLASS_STICKY_ATTR_CLEAR(_jit_dimmap_class, "basic");
	CLASS_STICKY_CATEGORY_CLEAR(_jit_dimmap_class);

	jit_class_register(_jit_dimmap_class);

	return JIT_ERR_NONE;
}


t_jit_err jit_dimmap_map(t_jit_dimmap *x, void *attr, long argc, t_atom *argv)
{
	long map[JIT_MATRIX_MAX_DIMCOUNT];
	long i,j;

	for (i=0; i<argc; i++)
		map[i] = jit_atom_getlong(argv+i);

	for (i=0; i<argc; i++) {
		for (j=i+1; j<argc; j++) {
			if ((map[i]==map[j])&&((map[i]>=0)&&(map[i]<JIT_MATRIX_MAX_DIMCOUNT))) {
				jit_object_error((t_object *)x,"jit.dimmap: map entries cannot be duplicates");
				return JIT_ERR_GENERIC;
			}
		}
	}

	for (i=0; i<argc; i++)
		x->map[i] = map[i];

	if (argc<1) {
		argc = 1;
		x->map[i] = 0;
	}

	x->mapcount = argc;

	return JIT_ERR_NONE;		// $rbs$ -- fix for warning
}

t_jit_err jit_dimmap_matrix_calc(t_jit_dimmap *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long i,in_savelock;
	char *in_bp;
	t_jit_matrix_info in_minfo,out_minfo,tmp_minfo;
	void *in_matrix,*out_matrix,*tmp_matrix=NULL;
	t_matrix_conv_info mcinfo;

	in_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);
	out_matrix 	= jit_object_method(outputs,_jit_sym_getindex,0);

	if (x&&in_matrix&&out_matrix) {
		in_savelock = (long) jit_object_method(in_matrix,_jit_sym_lock,1);
		jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
		jit_object_method(in_matrix,_jit_sym_getdata,&in_bp);

		if (!in_bp) { err = JIT_ERR_INVALID_INPUT; goto out; }

		tmp_minfo = in_minfo;
		tmp_minfo.flags = JIT_MATRIX_DATA_REFERENCE|JIT_MATRIX_DATA_FLAGS_USE;

		mcinfo.flags = JIT_MATRIX_CONVERT_SRCDIM;
		for (i=0; i<tmp_minfo.planecount; i++)
			mcinfo.planemap[i] = i;

		tmp_minfo.dimcount = x->mapcount;
		for (i=0; i<x->mapcount; i++) {
			if ((x->map[i]>=in_minfo.dimcount)||(x->map[i]<0)) {
				tmp_minfo.dim[i] 		= 1;
				tmp_minfo.dimstride[i] 	= (i>0)	? tmp_minfo.dimstride[i-1] : in_minfo.dimstride[0];
				mcinfo.srcdimstart[i] 	= 0;
				mcinfo.srcdimend[i] 	= 0;
			} else {
				tmp_minfo.dim[i] = in_minfo.dim[x->map[i]];
				tmp_minfo.dimstride[i] = in_minfo.dimstride[x->map[i]];
				if ((i<x->invertcount)&&x->invert[i]) {
					mcinfo.srcdimstart[i] 	= tmp_minfo.dim[i]-1;
					mcinfo.srcdimend[i] 	= 0;
				} else {
					mcinfo.srcdimstart[i] 	= 0;
					mcinfo.srcdimend[i] 	= tmp_minfo.dim[i]-1;
				}
			}
		}

		tmp_matrix = jit_object_new(_jit_sym_jit_matrix,&tmp_minfo);

		if (!tmp_matrix) { err = JIT_ERR_OUT_OF_MEM; goto out; }

		jit_object_method(tmp_matrix,gensym("data"),in_bp);

		out_minfo = tmp_minfo;
		out_minfo.flags = 0;
		err = (t_jit_err) jit_object_method(out_matrix,_jit_sym_setinfo,&out_minfo);

		if (err) goto out;

		jit_object_method(out_matrix,_jit_sym_frommatrix,tmp_matrix,&mcinfo);

	} else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	if (tmp_matrix) jit_object_free(tmp_matrix);
	jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
	return err;

}

t_jit_dimmap *jit_dimmap_new(void)
{
	t_jit_dimmap *x;
	long i;

	if (x=(t_jit_dimmap *)jit_object_alloc(_jit_dimmap_class)) {
		x->mapcount 	= 2;
		x->invertcount 	= 2;
		for (i=0; i<JIT_MATRIX_MAX_DIMCOUNT; i++) {
			x->map[i] 		= i;
			x->invert[i] 	= 0;
		}
	} else {
		x = NULL;
	}
	return x;
}

void jit_dimmap_free(t_jit_dimmap *x)
{
	//nada
}
