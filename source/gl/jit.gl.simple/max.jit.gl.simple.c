// max.jit.gl.simple.c
// sample GL group object which draws a simple quadrilateral. no matrixoutput.
// Copyright 2002-2005 - Cycling '74

#include "jit.common.h"
#include "jit.gl.h"


typedef struct _max_jit_gl_simple
{
	t_object		ob;
	void			*obex;
} t_max_jit_gl_simple;

t_jit_err jit_gl_simple_init(void);

void *max_jit_gl_simple_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_gl_simple_free(t_max_jit_gl_simple *x);
t_class *max_jit_gl_simple_class;


void ext_main(void *r)
{
	t_class *maxclass, *jitclass;

	// initialize our Jitter class
	jit_gl_simple_init();

	// create our Max class
	maxclass = class_new("jit.gl.simple", (method)max_jit_gl_simple_new, (method)max_jit_gl_simple_free, sizeof(t_max_jit_gl_simple), NULL, A_GIMME, 0);

	// specify a byte offset to keep additional information about our object
	max_jit_class_obex_setup(maxclass, calcoffset(t_max_jit_gl_simple, obex));

	// look up our Jitter class in the class registry
	jitclass = jit_class_findbyname(gensym("jit_gl_simple"));

	// wrap our Jitter class with the standard methods for Jitter objects
	max_jit_class_wrap_standard(maxclass, jitclass, 0);

	// use standard ob3d assist method
	class_addmethod(maxclass, (method)max_jit_ob3d_assist, "assist", A_CANT, 0);

	// add methods for 3d drawing
	max_jit_class_ob3d_wrap(maxclass);

	// register our class with max
	class_register(CLASS_BOX, maxclass);
	max_jit_gl_simple_class = maxclass;
}

void max_jit_gl_simple_free(t_max_jit_gl_simple *x)
{
	// lookup our internal Jitter object instance and free
	jit_object_free(max_jit_obex_jitob_get(x));

	// free resources associated with our obex entry
	max_jit_object_free(x);
}

void *max_jit_gl_simple_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_gl_simple *x;
	void *jit_ob;
	long attrstart;
	t_symbol *dest_name_sym = _jit_sym_nothing;

	if ((x = (t_max_jit_gl_simple *)max_jit_object_alloc(max_jit_gl_simple_class, gensym("jit_gl_simple"))))
	{
		// get first normal arg, the destination name
		attrstart = max_jit_attr_args_offset(argc,argv);
		if (attrstart&&argv)
		{
			jit_atom_arg_getsym(&dest_name_sym, 0, attrstart, argv);
		}

		// instantiate Jitter object with dest_name arg
		if ((jit_ob = jit_object_new(gensym("jit_gl_simple"), dest_name_sym)))
		{
			// set internal jitter object instance
			max_jit_obex_jitob_set(x, jit_ob);

			// add a general purpose outlet (rightmost)
			max_jit_obex_dumpout_set(x, outlet_new(x,NULL));

			// process attribute arguments
			max_jit_attr_args(x, argc, argv);

			// attach the jit object's ob3d to a new outlet
			// this outlet is used in matrixoutput mode
			max_jit_ob3d_attach(x, jit_ob, outlet_new(x, "jit_matrix"));
		}
		else
		{
			error("jit.gl.simple: could not allocate object");
			freeobject((t_object *)x);
			x = NULL;
		}
	}
	return (x);
}


