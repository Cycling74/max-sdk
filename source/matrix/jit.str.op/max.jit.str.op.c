/*
	Copyright 2001-2005 - Cycling '74
	Jeremy Bernstein jeremy@bootsquad.com
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_str_op
{
	t_object		ob;
	void			*obex;
} t_max_jit_str_op;

t_jit_err jit_str_op_init(void);

void *max_jit_str_op_new(t_symbol *s, long argc, t_atom *argv);
t_jit_err max_jit_str_op_jit_matrix(void *x, t_symbol *s, long argc, t_atom *argv);
void max_jit_str_op_mproc(t_max_jit_str_op *x, void *mop);
void max_jit_str_op_free(t_max_jit_str_op *x);
t_messlist *max_jit_str_op_class;

void ext_main(void *r)
{
	void *p,*q;

	jit_str_op_init();
	setup(&max_jit_str_op_class, max_jit_str_op_new, (method)max_jit_str_op_free, (short)sizeof(t_max_jit_str_op),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_str_op,obex));
	q = jit_class_findbyname(gensym("jit_str_op"));
	max_jit_classex_mop_wrap(p,q,MAX_JIT_MOP_FLAGS_OWN_JIT_MATRIX);
	max_jit_classex_mop_mproc(p,q,max_jit_str_op_mproc);
	max_jit_classex_standard_wrap(p,q,0);

	addmess((method)max_jit_str_op_jit_matrix, "jit_matrix", A_GIMME,0);
	addmess((method)max_jit_mop_assist, "assist", A_CANT,0);
}


void max_jit_str_op_mproc(t_max_jit_str_op *x, void *mop)
{
	long err;
	void *o;
	long ac = 1;
	t_atom a[2];
	t_symbol *s;

	o = max_jit_obex_jitob_get(x);

	jit_attr_setlong(o, gensym("adaptflag"), jit_attr_getlong(mop, _jit_sym_adapt));

	if (err=(t_jit_err) jit_object_method(
				max_jit_obex_jitob_get(x),
				_jit_sym_matrix_calc,
				jit_object_method(mop,_jit_sym_getinputlist),
				jit_object_method(mop,_jit_sym_getoutputlist)))
	{
		jit_error_code(x,err);
	} else {
		s = jit_attr_getsym(o, gensym("op"));
		switch(jit_attr_getlong(o, gensym("outmode"))) {
		case 0:
			max_jit_mop_outputmatrix(x);
			break;
		case 2:
			ac = 2;
			jit_atom_setlong(&a[1], jit_attr_getlong(o, gensym("outlong2")));
		case 1:
			jit_atom_setlong(&a[0], jit_attr_getlong(o, gensym("outlong")));
			max_jit_obex_dumpout(x, s, ac, a);
			break;
		}
	}
}

t_jit_err max_jit_str_op_jit_matrix(void *x, t_symbol *s, long argc, t_atom *argv)
{
	void *matrix,*matrixout,*mop,*o,*p,*m;
	t_atom a;
	t_symbol *matrixname;
	long err=JIT_ERR_NONE,inlet,i;
	method ioproc,mproc;

	if (!(mop=max_jit_obex_adornment_get(x,_jit_sym_jit_mop)))
		return JIT_ERR_GENERIC;

	if (argc&&argv) {
		//find matrix
		matrixname = jit_atom_getsym(argv);
		matrix = jit_object_findregistered(matrixname);
		if (matrix&&jit_object_method(matrix, _jit_sym_class_jit_matrix)) {
			if (inlet=max_jit_obex_inletnumber_get(x)) {
				//right inputs
				if ((p=jit_object_method(mop,_jit_sym_getinput,inlet+1)) &&
						(m=jit_object_method(p,_jit_sym_getmatrix)))
				{
					if (ioproc=(method)jit_object_method(p,_jit_sym_getioproc))
						(*ioproc)(mop,p,matrix);
					else
						jit_object_method(m,_jit_sym_frommatrix,matrix,NULL);
				} else {
					err=JIT_ERR_GENERIC;
				}
			} else {
				//calculate
				switch (jit_attr_getlong(mop,_jit_sym_outputmode)) {
				case 0: //nada
					break;
				case 2: //input(no calc)
					//pass input through leftmost output
					if ((p=jit_object_method(mop,_jit_sym_getoutput,1)) &&
							(o=max_jit_mop_io_getoutlet(p)))
					{
						outlet_anything(o,_jit_sym_jit_matrix,1,argv);
					}
					break;
				case 3: //output(no calc)
					max_jit_mop_outputmatrix(x);
					break;
				default: //calc
					//if adapt, resize
//					if (jit_attr_getlong(mop,_jit_sym_adapt))
//						max_jit_mop_adapt_matrix_all(x,matrix);
					if ((p=jit_object_method(mop,_jit_sym_getoutput,1))&&
							(ioproc=(method)jit_object_method(p,_jit_sym_getioproc)))
					{
						(*ioproc)(mop,p,matrix);
					}
					p = jit_object_method(mop,_jit_sym_getinput,1);
					jit_object_method(p,_jit_sym_matrix,matrix);
					jit_attr_setsym(p,_jit_sym_matrixname,matrixname);
//					if (mproc=(method)max_jit_mop_getmproc(mop)) {
					max_jit_str_op_mproc(x,mop);
					/*					} else {
											if (err=(t_jit_err) jit_object_method(
												max_jit_obex_jitob_get(x),
												_jit_sym_matrix_calc,
												jit_object_method(mop,_jit_sym_getinputlist),
												jit_object_method(mop,_jit_sym_getoutputlist)))
											{
												jit_error_code(x,err);
											} else {
												max_jit_mop_outputmatrix(x);
											}
										}*/
					break;
				}
			}
		} else {
			jit_error_code(x,JIT_ERR_MATRIX_UNKNOWN);
		}
	}

	return err;
}

void max_jit_str_op_free(t_max_jit_str_op *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_str_op_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_str_op *x;
	void *o, *m;
	t_jit_matrix_info info;

	if (x=(t_max_jit_str_op *)max_jit_obex_new(max_jit_str_op_class,gensym("jit_str_op"))) {
		if (o=jit_object_new(gensym("jit_str_op"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);
			m = max_jit_mop_getinput(x, 2);
			jit_object_method(m, _jit_sym_getinfo, &info);
			info.type = _jit_sym_char;
			info.planecount = 1;
			info.dimcount = 1;
			info.dim[0] = 1;
			jit_object_method(m, _jit_sym_setinfo, &info);
			max_jit_attr_args(x,argc,argv);
		} else {
			jit_object_error((t_object *)x,"jit.str.op: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}