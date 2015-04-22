/*
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_pack
{
	t_object		ob;
	void			*obex;
	long			inlets;
} t_max_jit_pack;

t_jit_err jit_pack_init(void);

void *max_jit_pack_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_pack_free(t_max_jit_pack *x);
t_jit_err max_jit_pack_assist(t_max_jit_pack *x, void *b, long m, long a, char *s);
t_jit_err max_jit_pack_jit_matrix(t_max_jit_pack *x, t_symbol *s, long argc, t_atom *argv);
void setOutputPlanes(t_max_jit_pack *x);


t_messlist *max_jit_pack_class;

void ext_main(void *r)
{
	void *p,*q;
//	long attrflags;
//	void *attr;

	jit_pack_init();
	setup(&max_jit_pack_class, max_jit_pack_new, (method)max_jit_pack_free, (short)sizeof(t_max_jit_pack),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_pack,obex));
	q = jit_class_findbyname(gensym("jit_pack"));
	addmess((method)max_jit_pack_jit_matrix, "jit_matrix", A_GIMME,0); //place at beginning for speed
	max_jit_classex_mop_wrap(p,q,MAX_JIT_MOP_FLAGS_OWN_JIT_MATRIX);
	max_jit_classex_standard_wrap(p,q,0);
	addmess((method)max_jit_pack_assist, "assist", A_CANT,0);  //customize

	/*	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW ;
		attr = jit_object_new(_jit_sym_jit_attr_offset_array,"jump",_jit_sym_long,JIT_MATRIX_MAX_PLANECOUNT,attrflags,
			(method)0L,(method)max_jit_pack_jump,calcoffset(t_max_jit_pack,jumpcount), calcoffset(t_max_jit_pack,jump));
		max_jit_classex_addattr(p,attr);*/
}

t_jit_err max_jit_pack_assist(t_max_jit_pack *x, void *b, long m, long a, char *s)
{
	void *mop;

	if (!(mop=max_jit_obex_adornment_get(x,_jit_sym_jit_mop)))
		return JIT_ERR_GENERIC;

	if (m == 1) { //input
		sprintf(s,"(matrix) in");
		if (a>0)
			sprintf(s,"%s%d",s,a+1);
	} else {	//output
		max_jit_mop_assist(x,b,m,a,s);
	}

	return JIT_ERR_NONE;
}

/*t_jit_err max_jit_pack_jump(t_max_jit_pack *x, t_symbol *s, long argc, t_atom *argv)
{
	long i, totalPlanes=0;
	void *m;

	for (i=0; i < MIN(argc, x->inlets); i++) {
		x->jump[i] = MAX( jit_atom_getlong(argv + i), 1);
		x->cumjump[i] = totalPlanes;
		totalPlanes += x->jump[i];
	}

	//handles case where jump list is less than number of inlets
	//set to default jump value
	while(i < x->inlets) {
		x->jump[i] = 1;
		x->cumjump[i] = totalPlanes;
		totalPlanes += 1;
		i++;
	}

	m = max_jit_mop_getoutput(x,1);
	jit_attr_setlong(m,_jit_sym_planecount,totalPlanes);

	x->jumpcount = i;

	return JIT_ERR_NONE;
}*/

void setOutputPlanes(t_max_jit_pack *x)
{
	long i, outputPlanes=0;
	t_atom_long jump[JIT_MATRIX_MAX_PLANECOUNT];
	void *o;

	o = max_jit_obex_jitob_get(x);
	jit_attr_getlong_array(o, gensym("jump"), JIT_MATRIX_MAX_PLANECOUNT, jump);

	for(i=0; i < x->inlets; i++) {
		outputPlanes += jump[i];
	}

	o = max_jit_mop_getoutput(x,1);
	jit_attr_setlong(o,_jit_sym_planecount,outputPlanes);
}

t_jit_err max_jit_pack_jit_matrix(t_max_jit_pack *x, t_symbol *s, long argc, t_atom *argv)
{
	void *matrix,*matrixout,*mop,*o,*p,*m;
	t_atom a;
	t_symbol *matrixname;
	long err=JIT_ERR_NONE,inlet,i,poffset,*offset;
	method ioproc,mproc;

	if (!(mop=max_jit_obex_adornment_get(x,_jit_sym_jit_mop)))
		return JIT_ERR_GENERIC;

	setOutputPlanes(x);

	if (argc&&argv) {
		//find matrix
		matrixname = jit_atom_getsym(argv);
		matrix = jit_object_findregistered(matrixname);
		if (matrix&&jit_object_method(matrix, _jit_sym_class_jit_matrix)) {
			inlet=max_jit_obex_inletnumber_get(x);
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
				if (jit_attr_getlong(mop,_jit_sym_adapt))
					max_jit_mop_adapt_matrix_all(x,matrix);
				//stuff any one into 1st matrix input
				p = jit_object_method(mop,_jit_sym_getinput,1);
				jit_object_method(p,_jit_sym_matrix,matrix);
				jit_attr_setsym(p,_jit_sym_matrixname,matrixname);
				//set jitob's plane, jump and inlet attribute + call matrixcalc
				o = max_jit_obex_jitob_get(x);
				jit_attr_setlong(o,_jit_sym_plane,inlet);

				if (err=(t_jit_err) jit_object_method(
							o,
							_jit_sym_matrix_calc,
							jit_object_method(mop,_jit_sym_getinputlist),
							jit_object_method(mop,_jit_sym_getoutputlist)))
				{
					jit_error_code(x,err);
				}

				if (inlet==0)
					max_jit_mop_outputmatrix(x);
				break;
			}
		} else {
			jit_error_code(x,JIT_ERR_MATRIX_UNKNOWN);
		}
	}

	return err;
}

void max_jit_pack_free(t_max_jit_pack *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_pack_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_pack *x;
	void *o,*m,*mop;
	t_jit_matrix_info info;
	long i,n;

	if (x=(t_max_jit_pack *)max_jit_obex_new(max_jit_pack_class,gensym("jit_pack"))) {
		if (o=jit_object_new(gensym("jit_pack"))) {
			max_jit_obex_jitob_set(x,o);
			max_jit_obex_dumpout_set(x,outlet_new(x,NULL));
			max_jit_mop_setup(x);
			//add fake inputs + one real input
			if (argc&&(n=jit_atom_getlong(argv))) {
				CLIP_ASSIGN(n,1,JIT_MATRIX_MAX_PLANECOUNT);
			} else {
				n=4;
			}

			x->inlets = n;

			for (i=n; i>1; i--) {
				max_jit_obex_proxy_new(x,i-1); //right to left
			}
			max_jit_mop_variable_addinputs(x,1);//only used to fake out the matrix calc method
			max_jit_mop_inputs(x);
			max_jit_mop_outputs(x);
			max_jit_mop_matrix_args(x,argc,argv);
			//set planecount since it is not linked.
			m = max_jit_mop_getoutput(x,1);
			jit_attr_setlong(m,_jit_sym_planecount,n);
			//set adapt true if only plane argument(should come after matrix_args call)
			if ((max_jit_attr_args_offset(argc,argv)<=1) &&
					(mop=max_jit_obex_adornment_get(x,_jit_sym_jit_mop)))
			{
				jit_attr_setlong(mop,_jit_sym_adapt,1);
			}

			max_jit_attr_args(x,argc,argv);
		} else {
			jit_object_error((t_object *)x,"jit.pack: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}
