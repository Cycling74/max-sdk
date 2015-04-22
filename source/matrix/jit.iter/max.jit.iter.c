/*
	Copyright 2001 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

// revised at some point by jb to include 2nd mode (necessary for particles)

#include "jit.common.h"

typedef struct _max_jit_iter
{
	t_object			ob;
	void				*obex;
	void 				*valout;
	void 				*coordout;
	//outputmode: 0=no output, 1=calc, 2=input(no calc)(irrelevant), 3=output(no calc)
	char				mode;
} t_max_jit_iter;

void *max_jit_iter_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_iter_free(t_max_jit_iter *x);
void max_jit_iter_assist(t_max_jit_iter *x, void *b, long m, long a, char *s);
void max_jit_iter_jit_matrix(t_max_jit_iter *x, t_symbol *s, long argc, t_atom *argv);
void max_jit_iter_calculate_ndim(t_max_jit_iter *x, long dimcount, long *dim, t_atom *a_coord, t_jit_matrix_info *in_minfo, char *bip);

t_messlist *max_jit_iter_class;

t_symbol *ps_done;

void ext_main(void *r)
{
	long attrflags;
	void *p,*attr;

	setup(&max_jit_iter_class, max_jit_iter_new, (method)max_jit_iter_free, (short)sizeof(t_max_jit_iter),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_iter,obex));

	//at beginning of messlist for speed
	addmess((method)max_jit_iter_jit_matrix,		"jit_matrix",		A_GIMME,0);

	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW ;

	attr = jit_object_new(_jit_sym_jit_attr_offset,"mode",_jit_sym_char,attrflags,
						  (method)0,(method)0,calcoffset(t_max_jit_iter,mode));
	object_addattr_parse(attr,"category",_jit_sym_symbol,0,"Behavior");
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Iteration Mode\"");
	object_addattr_parse(attr,"basic",_jit_sym_long,0,"1");
	object_addattr_parse(attr,"style",_jit_sym_symbol,0,"enumindex");
	object_addattr_parse(attr,"enumvals",_jit_sym_symbol,0,"\"Horizontal Traversal\" \"Vertical Traversal\"");
	max_jit_classex_addattr(p,attr);

	max_jit_classex_standard_wrap(p,NULL,0);
	addmess((method)max_jit_iter_assist,			"assist",			A_CANT,0);

	ps_done = gensym("done");

}


void max_jit_iter_jit_matrix(t_max_jit_iter *x, t_symbol *s, long argc, t_atom *argv)
{
	void *matrix;
	long err,i,dimcount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	long in_savelock;
	t_jit_matrix_info in_minfo;
	char *in_bp;
	t_atom a_coord[JIT_MATRIX_MAX_DIMCOUNT];

	if (argc&&argv) {
		//find matrix
		matrix = jit_object_findregistered(jit_atom_getsym(argv));
		if (matrix&&jit_object_method(matrix, _jit_sym_class_jit_matrix)) {
			//calculate
			in_savelock = (long) jit_object_method(matrix,_jit_sym_lock,1);
			jit_object_method(matrix,_jit_sym_getinfo,&in_minfo);
			jit_object_method(matrix,_jit_sym_getdata,&in_bp);

			if (!in_bp) {
				jit_error_sym(x,_jit_sym_err_calculate);
				jit_object_method(matrix,_jit_sym_lock,in_savelock);
				goto out;
			}

			//get dimensions/planecount
			dimcount = in_minfo.dimcount;
			for (i=0; i<dimcount; i++) {
				dim[i] = in_minfo.dim[i];
			}

			//calculate
			max_jit_iter_calculate_ndim(x, dimcount, dim, a_coord, &in_minfo, in_bp);

			jit_object_method(matrix,_jit_sym_lock,in_savelock);
			max_jit_obex_dumpout(x,ps_done,0,0L);
		} else {
			jit_error_sym(x,_jit_sym_err_calculate);
		}
	}
out:
	return;
}

//recursive function to handle higher dimension matrices, by processing 2D sections at a time
void max_jit_iter_calculate_ndim(t_max_jit_iter *x, long dimcount, long *dim, t_atom *a_coord, t_jit_matrix_info *in_minfo, char *bip)
{
	t_atom a_val[JIT_MATRIX_MAX_PLANECOUNT];
	long i,j,k,n,maxsize;
	long rowstride;
	uchar *ip;


	if (dimcount<1) return; //safety

	switch(dimcount) {
	case 1:
		dim[1] = 1;
	case 2:
		n = dim[0];
		switch(x->mode) {
		case 1:
			if (in_minfo->type==_jit_sym_char) {
				rowstride = in_minfo->dimstride[1];
				for (j=0; j<dim[0]; j++) {
					ip = bip + j * in_minfo->dimstride[0];
					jit_atom_setlong(&(a_coord[0]),j);
					for (i=0; i<dim[1]; i++) {
						jit_atom_setlong(&(a_coord[1]),i);
						for (k=0; k<in_minfo->planecount; k++) {
							jit_atom_setlong(&(a_val[k]),((uchar *)ip)[k]);
						}
						if (in_minfo->dimcount>1)
							outlet_anything(x->coordout,_jit_sym_list,in_minfo->dimcount,a_coord);
						else
							outlet_int(x->coordout,a_coord[0].a_w.w_long);
						if (in_minfo->planecount>1)
							outlet_anything(x->valout,_jit_sym_list,in_minfo->planecount,a_val);
						else
							outlet_int(x->valout,a_val[0].a_w.w_long);
						ip += rowstride;
					}
				}
			} else if (in_minfo->type==_jit_sym_long) {
				rowstride = in_minfo->dimstride[1];// >> 2L;
				for (j=0; j<dim[0]; j++) {
					ip = bip + j * in_minfo->dimstride[0];
					jit_atom_setlong(&(a_coord[0]),j);
					for (i=0; i<dim[1]; i++) {
						jit_atom_setlong(&(a_coord[1]),i);
						for (k=0; k<in_minfo->planecount; k++) {
							jit_atom_setlong(&(a_val[k]),((t_int32 *)ip)[k]);
						}
						if (in_minfo->dimcount>1)
							outlet_anything(x->coordout,_jit_sym_list,in_minfo->dimcount,a_coord);
						else
							outlet_int(x->coordout,a_coord[0].a_w.w_long);
						if (in_minfo->planecount>1)
							outlet_anything(x->valout,_jit_sym_list,in_minfo->planecount,a_val);
						else
							outlet_int(x->valout,a_val[0].a_w.w_long);
						ip += rowstride;
					}
				}
			} else if (in_minfo->type==_jit_sym_float32) {
				rowstride = in_minfo->dimstride[1];// >> 2L;
				for (j=0; j<dim[0]; j++) {
					ip = bip + j * in_minfo->dimstride[0];
					jit_atom_setlong(&(a_coord[0]),j);
					for (i=0; i<dim[1]; i++) {
						jit_atom_setlong(&(a_coord[1]),i);
						for (k=0; k<in_minfo->planecount; k++) {
							jit_atom_setfloat(&(a_val[k]),((float *)ip)[k]);
						}
						if (in_minfo->dimcount>1)
							outlet_anything(x->coordout,_jit_sym_list,in_minfo->dimcount,a_coord);
						else
							outlet_int(x->coordout,a_coord[0].a_w.w_long);
						if (in_minfo->planecount>1)
							outlet_anything(x->valout,_jit_sym_list,in_minfo->planecount,a_val);
						else
							outlet_float(x->valout,a_val[0].a_w.w_float);
						ip += rowstride;
					}
				}
			} else if (in_minfo->type==_jit_sym_float64) {
				rowstride = in_minfo->dimstride[1];// >> 3L;
				for (j=0; j<dim[0]; j++) {
					ip = bip + j * in_minfo->dimstride[0];
					jit_atom_setlong(&(a_coord[0]),j);
					for (i=0; i<dim[1]; i++) {
						jit_atom_setlong(&(a_coord[1]),i);
						for (k=0; k<in_minfo->planecount; k++) {
							jit_atom_setfloat(&(a_val[k]),((double *)ip)[k]);
						}
						if (in_minfo->dimcount>1)
							outlet_anything(x->coordout,_jit_sym_list,in_minfo->dimcount,a_coord);
						else
							outlet_int(x->coordout,a_coord[0].a_w.w_long);
						if (in_minfo->planecount>1)
							outlet_anything(x->valout,_jit_sym_list,in_minfo->planecount,a_val);
						else
							outlet_float(x->valout,a_val[0].a_w.w_float);
						ip += rowstride;
					}
				}
			}
			break;
		case 0:
		default:
			if (in_minfo->type==_jit_sym_char) {
				for (i=0; i<dim[1]; i++) {
					ip = bip + i*in_minfo->dimstride[1];
					jit_atom_setlong(&(a_coord[1]),i);
					for (j=0; j<dim[0]; j++) {
						jit_atom_setlong(&(a_coord[0]),j);
						for (k=0; k<in_minfo->planecount; k++) {
							jit_atom_setlong(&(a_val[k]),((uchar *)ip)[(j*in_minfo->planecount)+k]);
						}
						if (in_minfo->dimcount>1)
							outlet_anything(x->coordout,_jit_sym_list,in_minfo->dimcount,a_coord);
						else
							outlet_int(x->coordout,a_coord[0].a_w.w_long);
						if (in_minfo->planecount>1)
							outlet_anything(x->valout,_jit_sym_list,in_minfo->planecount,a_val);
						else
							outlet_int(x->valout,a_val[0].a_w.w_long);
					}
				}
			} else if (in_minfo->type==_jit_sym_long) {
				for (i=0; i<dim[1]; i++) {
					ip = bip + i*in_minfo->dimstride[1];
					jit_atom_setlong(&(a_coord[1]),i);
					for (j=0; j<dim[0]; j++) {
						jit_atom_setlong(&(a_coord[0]),j);
						for (k=0; k<in_minfo->planecount; k++) {
							jit_atom_setlong(&(a_val[k]),((t_int32 *)ip)[(j*in_minfo->planecount)+k]);
						}
						if (in_minfo->dimcount>1)
							outlet_anything(x->coordout,_jit_sym_list,in_minfo->dimcount,a_coord);
						else
							outlet_int(x->coordout,a_coord[0].a_w.w_long);
						if (in_minfo->planecount>1)
							outlet_anything(x->valout,_jit_sym_list,in_minfo->planecount,a_val);
						else
							outlet_int(x->valout,a_val[0].a_w.w_long);
					}
				}
			} else if (in_minfo->type==_jit_sym_float32) {
				for (i=0; i<dim[1]; i++) {
					ip = bip + i*in_minfo->dimstride[1];
					jit_atom_setlong(&(a_coord[1]),i);
					for (j=0; j<dim[0]; j++) {
						jit_atom_setlong(&(a_coord[0]),j);
						for (k=0; k<in_minfo->planecount; k++) {
							jit_atom_setfloat(&(a_val[k]),((float *)ip)[(j*in_minfo->planecount)+k]);
						}
						if (in_minfo->dimcount>1)
							outlet_anything(x->coordout,_jit_sym_list,in_minfo->dimcount,a_coord);
						else
							outlet_int(x->coordout,a_coord[0].a_w.w_long);
						if (in_minfo->planecount>1)
							outlet_anything(x->valout,_jit_sym_list,in_minfo->planecount,a_val);
						else
							outlet_float(x->valout,a_val[0].a_w.w_float);
					}
				}
			} else if (in_minfo->type==_jit_sym_float64) {
				for (i=0; i<dim[1]; i++) {
					ip = bip + i*in_minfo->dimstride[1];
					jit_atom_setlong(&(a_coord[1]),i);
					for (j=0; j<dim[0]; j++) {
						jit_atom_setlong(&(a_coord[0]),j);
						for (k=0; k<in_minfo->planecount; k++) {
							jit_atom_setfloat(&(a_val[k]),((double *)ip)[(j*in_minfo->planecount)+k]);
						}
						if (in_minfo->dimcount>1)
							outlet_anything(x->coordout,_jit_sym_list,in_minfo->dimcount,a_coord);
						else
							outlet_int(x->coordout,a_coord[0].a_w.w_long);
						if (in_minfo->planecount>1)
							outlet_anything(x->valout,_jit_sym_list,in_minfo->planecount,a_val);
						else
							outlet_float(x->valout,a_val[0].a_w.w_float);
					}
				}
			}
			break;
		}
		break;
	default:
		for	(i=0; i<dim[dimcount-1]; i++) {
			ip = bip + i*in_minfo->dimstride[dimcount-1];
			jit_atom_setlong(&(a_coord[dimcount-1]),i);
			max_jit_iter_calculate_ndim(x,dimcount-1,dim,a_coord,in_minfo,ip);
		}
	}
}

void max_jit_iter_assist(t_max_jit_iter *x, void *b, long m, long a, char *s)
{
	if (m == 1) { //input
		sprintf(s,"(matrix) in");
	} else { //output
		switch (a) {
		case 0:
			sprintf(s,"(list) values");
			break;
		case 1:
			sprintf(s,"(list) coordinates");
			break;
		case 2:
			sprintf(s,"dumpout");
			break;
		}
	}
}

void max_jit_iter_free(t_max_jit_iter *x)
{
	//only max object, no jit object
	max_jit_obex_free(x);
}

void *max_jit_iter_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_iter *x;

	if (x = (t_max_jit_iter *)max_jit_obex_new(max_jit_iter_class,NULL)) { //only max object, no jit object
		max_jit_obex_dumpout_set(x,outlet_new(x,NULL));
		x->coordout = outlet_new(x,0L);
		x->valout 	= outlet_new(x,0L);

		x->mode = 0;

		//no normal args, no matrices
		max_jit_attr_args(x,argc,argv); //handle attribute args
	}
	return (x);
}