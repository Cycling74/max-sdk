/*
	Copyright 2001 - Cycling '74
	R. Luke DuBois luke@music.columbia.edu
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_glue
{
	t_object		ob;
	void			*obex;
	long			maxn, syncinlet;
} t_max_jit_glue;

t_jit_err jit_glue_init(void);

void *max_jit_glue_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_glue_free(t_max_jit_glue *x);
void max_jit_glue_assist(t_max_jit_glue *x, void *b, long m, long a, char *s);
t_jit_err max_jit_glue_jit_matrix(t_max_jit_glue *x, t_symbol *s, long argc, t_atom *argv);

t_messlist     *max_jit_glue_class;

t_symbol *ps_input,*ps_rows,*ps_columns;

void ext_main(void *r)
{
	void *p,*q,*attr;
	long attrflags;

	jit_glue_init();
	setup(&max_jit_glue_class, max_jit_glue_new, (method)max_jit_glue_free, (short)sizeof(t_max_jit_glue),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_glue,obex));
	q = jit_class_findbyname(gensym("jit_glue"));
	addmess((method)max_jit_glue_jit_matrix, "jit_matrix", A_GIMME,0); //place at beginning for speed
	max_jit_classex_mop_wrap(p,q,MAX_JIT_MOP_FLAGS_OWN_JIT_MATRIX);
	max_jit_classex_standard_wrap(p,q,0);
	addmess((method)max_jit_glue_assist, "assist", A_CANT,0);

	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW ;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"syncinlet",_jit_sym_long,attrflags,
						  (method)0,(method)0,calcoffset(t_max_jit_glue,syncinlet));
	max_jit_classex_addattr(p,attr);

	ps_input 	= gensym("input");
	ps_rows 	= gensym("rows");
	ps_columns	= gensym("columns");
}

void max_jit_glue_assist(t_max_jit_glue *x, void *b, long m, long a, char *s)
{
	void *mop,*p;

	if (!(mop=max_jit_obex_adornment_get(x,_jit_sym_jit_mop)))
		return;

	if (m == 1) { //input
		sprintf(s,"(matrix) in");
		if (a>0)
			sprintf(s,"%s%d",s,a+1);
	} else {	//output
		max_jit_mop_assist(x,b,m,a,s);
	}
}

t_jit_err max_jit_glue_jit_matrix(t_max_jit_glue *x, t_symbol *s, long argc, t_atom *argv)
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
			inlet=max_jit_obex_inletnumber_get(x);
			x->syncinlet = CLAMP(x->syncinlet,-1,x->maxn-1);
			//calculate
			switch (jit_attr_getlong(mop,_jit_sym_outputmode)) {
			case 0: //nada
				break;
			case 2: //input(no calc)
				//pass input through leftmost output
				if ((inlet==0) &&
						(p=jit_object_method(mop,_jit_sym_getoutput,1)) &&
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
				if ((inlet==0)&&jit_attr_getlong(mop,_jit_sym_adapt))
					max_jit_mop_adapt_matrix_all(x,matrix);
				//stuff any one into 1st matrix input
				p = jit_object_method(mop,_jit_sym_getinput,1);
				jit_object_method(p,_jit_sym_matrix,matrix);
				jit_attr_setsym(p,_jit_sym_matrixname,matrixname);
				//set jitob's plane attribute + call matrixcalc
				o = max_jit_obex_jitob_get(x);
				jit_attr_setlong(o,ps_input,inlet);
				if (err=(t_jit_err) jit_object_method(
							o,
							_jit_sym_matrix_calc,
							jit_object_method(mop,_jit_sym_getinputlist),
							jit_object_method(mop,_jit_sym_getoutputlist)))
				{
					jit_error_code(x,err);
				} else {
					if (inlet==x->syncinlet||-1==x->syncinlet)
						max_jit_mop_outputmatrix(x);
				}
				break;
			}
		} else {
			jit_error_code(x,JIT_ERR_MATRIX_UNKNOWN);
		}
	}

	return err;
}

void max_jit_glue_free(t_max_jit_glue *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_glue_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_glue *x;
	void *o,*m,*mop;
	t_jit_matrix_info info;
	long i;

	if (x=(t_max_jit_glue *)max_jit_obex_new(max_jit_glue_class,gensym("jit_glue"))) {
		if (o=jit_object_new(gensym("jit_glue"))) {
			x->syncinlet=0;
			max_jit_obex_jitob_set(x,o);
			max_jit_obex_dumpout_set(x,outlet_new(x,NULL));
			max_jit_mop_setup(x);
			max_jit_mop_variable_addinputs(x,1);//only used to fake out the matrix calc method
			max_jit_mop_inputs(x);
			max_jit_mop_outputs(x);
			max_jit_mop_matrix_args(x,argc,argv);
			max_jit_attr_args(x,argc,argv); //handle attribute args

			x->maxn=jit_attr_getlong(o,ps_rows)*jit_attr_getlong(o,ps_columns);

			for (i=0; i<(x->maxn-1); i++) //add inlets
				max_jit_obex_proxy_new(x,(x->maxn-1)-i);

		} else {
			jit_object_error((t_object *)x,"jit.glue: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}
