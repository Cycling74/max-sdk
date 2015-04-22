/* 
	max.jit.mop.h

	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
	
*/

#ifndef __MAX_JIT_MOP_H__
#define __MAX_JIT_MOP_H__
//flags for greater control
#define MAX_JIT_MOP_FLAGS_NONE					0x00000000            ///< mop flag @ingroup jitter
#define MAX_JIT_MOP_FLAGS_OWN_ALL				0x0FFFFFFF            ///< mop flag @ingroup jitter
                                                                     
#define MAX_JIT_MOP_FLAGS_OWN_JIT_MATRIX		0x00000001            ///< mop flag @ingroup jitter
#define MAX_JIT_MOP_FLAGS_OWN_BANG				0x00000002            ///< mop flag @ingroup jitter
#define MAX_JIT_MOP_FLAGS_OWN_OUTPUTMATRIX		0x00000004            ///< mop flag @ingroup jitter
#define MAX_JIT_MOP_FLAGS_OWN_NAME				0x00000008            ///< mop flag @ingroup jitter
#define MAX_JIT_MOP_FLAGS_OWN_TYPE				0x00000010            ///< mop flag @ingroup jitter
#define MAX_JIT_MOP_FLAGS_OWN_DIM				0x00000020            ///< mop flag @ingroup jitter
#define MAX_JIT_MOP_FLAGS_OWN_PLANECOUNT		0x00000040            ///< mop flag @ingroup jitter
#define MAX_JIT_MOP_FLAGS_OWN_CLEAR				0x00000080            ///< mop flag @ingroup jitter
#define MAX_JIT_MOP_FLAGS_OWN_NOTIFY			0x00000100            ///< mop flag @ingroup jitter
#define MAX_JIT_MOP_FLAGS_OWN_ADAPT				0x00000200            ///< mop flag @ingroup jitter
#define MAX_JIT_MOP_FLAGS_OWN_OUTPUTMODE		0x00000400            ///< mop flag @ingroup jitter

#define MAX_JIT_MOP_FLAGS_ONLY_MATRIX_PROBE 	0x10000000            ///< mop flag @ingroup jitter
                                                                 
#define JIT_MOP_INPUT 	1                                         ///< mop flag @ingroup jitter
#define JIT_MOP_OUTPUT	2                                         ///< mop flag @ingroup jitter

//outputmode: 0=no output, 1=calc, 2=input(no calc), 3=output(no calc)

#ifdef __cplusplus
extern "C" {
#endif

t_jit_err max_jit_classex_mop_wrap(void *mclass, void *jclass, long flags);		// legacy api
t_jit_err max_jit_class_mop_wrap(t_class *mclass, t_class *jclass, long flags);	// new api
t_jit_err max_jit_classex_mop_mproc(void *mclass, void *jclass, void *mproc); //mproc should be method(void *x, void *mop)
t_jit_err max_jit_object_mop_wrap(t_object *mob, t_object *job, long flags);
t_jit_err max_jit_object_mop_mproc(void *mob, void *job, void *mproc);

t_jit_err max_jit_mop_setup(void *x);
t_jit_err max_jit_mop_inputs(void *x);
t_jit_err max_jit_mop_inputs_resize(void *x, long count);
t_jit_err max_jit_mop_outputs(void *x);
t_jit_err max_jit_mop_outputs_resize(void *x, long count);
t_jit_err max_jit_mop_matrix_args(void *x, long argc, t_atom *argv);
t_jit_err max_jit_mop_jit_matrix(void *x, t_symbol *s, long argc, t_atom *argv);
t_jit_err max_jit_mop_assist(void *x, void *b, long m, long a, char *s);
t_jit_err max_jit_mop_bang(void *x);
t_jit_err max_jit_mop_outputmatrix(void *x);
t_jit_err max_jit_mop_matrixout_new(void *x, long c);
void max_jit_mop_clear(void *x);
t_jit_err max_jit_mop_notify(void *x, t_symbol *s, t_symbol *msg);
void max_jit_mop_free(void *x);
t_jit_err max_jit_mop_name(void *x, void *attr, long argc, t_atom *argv);
t_jit_err max_jit_mop_getname(void *x, void *attr, long *argc, t_atom **argv);
t_jit_err max_jit_mop_type(void *x, void *attr, long argc, t_atom *argv);
t_jit_err max_jit_mop_gettype(void *x, void *attr, long *argc, t_atom **argv);
t_jit_err max_jit_mop_dim(void *x, void *attr, long argc, t_atom *argv);
t_jit_err max_jit_mop_getdim(void *x, void *attr, long *argc, t_atom **argv);
t_jit_err max_jit_mop_planecount(void *x, void *attr, long argc, t_atom *argv);
t_jit_err max_jit_mop_getplanecount(void *x, void *attr, long *argc, t_atom **argv);
t_jit_err max_jit_mop_parse_name(t_symbol *name, long *type, long *idx);
t_jit_err max_jit_mop_restrict_info(void *x, void *p, t_jit_matrix_info *info);
void *max_jit_mop_get_io_by_name(void *x, t_symbol *s);
t_jit_err max_jit_mop_outputmode(void *x, void *attr, long argc, t_atom *argv);
t_jit_err max_jit_mop_getoutputmode_attr(void *x, void *attr, long *argc, t_atom **argv);
t_jit_err max_jit_mop_adapt(void *x, void *attr, long argc, t_atom *argv);
t_jit_err max_jit_mop_getadapt(void *x, void *attr, long *argc, t_atom **argv);
void *max_jit_mop_getinput(void *x, long c);
void *max_jit_mop_getoutput(void *x, long c);
long max_jit_mop_getoutputmode(void *x);
void *max_jit_mop_io_getoutlet(void *mop_io);
t_jit_err max_jit_mop_io_setoutlet(void *mop_io, void *o);
void *max_jit_mop_getmproc(void *mop);
t_jit_err max_jit_mop_adapt_matrix_all(void *x, void *y);
t_jit_err max_jit_mop_variable_parse_sym(t_symbol *name, t_symbol **msg, long *set);
t_jit_err max_jit_mop_variable_anything(void *x, t_symbol *s, long argc, t_atom *argv);
t_jit_err max_jit_mop_variable_addinputs(void *x, long c);
t_jit_err max_jit_mop_variable_addoutputs(void *x, long c);

t_jit_err max_jit_mop_setup_simple(void *x, void *o, long argc, t_atom *argv);
/* max_jit_mop_setup_simple is equivalent to :

	max_jit_obex_jitob_set(x,o);
	max_jit_obex_dumpout_set(x,outlet_new(x,NULL));
	max_jit_mop_setup(x);
	max_jit_mop_inputs(x);
	max_jit_mop_outputs(x);
	max_jit_mop_matrix_args(x,argc,argv);
	
	NOTICE: REMOVED max_jit_attr_args from max_jit_mop_setup_simple

	max_jit_mop_classex_mproc 

*/

#ifdef __cplusplus
}
#endif

#endif //__MAX_JIT_MOP_H__
