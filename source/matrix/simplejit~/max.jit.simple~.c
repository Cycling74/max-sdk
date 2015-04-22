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
#include "max.jit.mop.h"
#include "z_dsp.h"
#include "ext_obex.h"


// Max object instance data
// Note: most instance data is in the Jitter object which we will wrap
typedef struct _max_jit_simple {
	t_pxobject	ob;
	void		*obex;
	t_object	*simple;
} t_max_jit_simple;


// prototypes
BEGIN_USING_C_LINKAGE
t_jit_err	jit_simple_init(void);
void		*max_jit_simple_new(t_symbol *s, long argc, t_atom *argv);
void		max_jit_simple_free(t_max_jit_simple *x);
void		max_jit_simple_dsp64(t_max_jit_simple *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
END_USING_C_LINKAGE

// globals
static void		*s_max_jit_simple_class = NULL;
static t_symbol	*ps_gain = NULL;


/************************************************************************************/

void ext_main(void *r)
{
	t_class *p, *q;

	jit_simple_init();
	p = class_new("jit.simple~", (method)max_jit_simple_new, (method)max_jit_simple_free, sizeof(t_max_jit_simple), NULL, A_GIMME, 0);

	max_jit_class_obex_setup(p, calcoffset(t_max_jit_simple, obex));
	q = jit_class_findbyname(gensym("jit_simple~"));
	max_jit_class_mop_wrap(p, q, 0);			// attrs & methods for name, type, dim, planecount, bang, outputmatrix, etc
	max_jit_class_wrap_standard(p, q, 0);		// attrs & methods for getattributes, dumpout, maxjitclassaddmethods, etc

	class_addmethod(p, (method)max_jit_mop_assist,		"assist", A_CANT, 0);	// standard matrix-operator (mop) assist fn
	class_addmethod(p, (method)max_jit_simple_dsp64,	"dsp64", A_CANT, 0);

	class_dspinit(p);
	class_register(CLASS_BOX, p);
	s_max_jit_simple_class = p;

	ps_gain = gensym("gain");
}


/************************************************************************************/
// Object Life Cycle

void *max_jit_simple_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_simple *x;

	x = (t_max_jit_simple *)max_jit_object_alloc(s_max_jit_simple_class, gensym("jit_simple~"));
	if (x) {
		x->simple = (t_object *)jit_object_new(gensym("jit_simple~"));
		if (x->simple) {
			max_jit_mop_setup_simple(x, x->simple, argc, argv);
			max_jit_attr_args(x, argc, argv);
		}
		else {
			jit_object_error((t_object *)x, "jit.simple~: could not allocate object");
			freeobject((t_object *)x);
			x = NULL;
		}
		dsp_setup((t_pxobject *)x, 1);
	}
	return (x);
}


void max_jit_simple_free(t_max_jit_simple *x)
{
	dsp_free((t_pxobject *)x);
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_object_free(x);
}


void max_jit_simple_perform64(t_max_jit_simple *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	double	*in = ins[0];
	long	n = sampleframes;

	while (n--)
		object_method_float(x->simple, ps_gain, *in++, NULL);
}


void max_jit_simple_dsp64(t_max_jit_simple *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	object_method(dsp64, gensym("dsp_add64"), x, max_jit_simple_perform64, 0, NULL);
}
