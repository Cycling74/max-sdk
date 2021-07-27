
#include "jit.gl.common.h"


typedef struct _max_jit_gl_gridshape
{
	t_object		ob;
	void			*obex;
} t_max_jit_gl_gridshape;

void *max_jit_gl_gridshape_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_gl_gridshape_free(t_max_jit_gl_gridshape *x);
t_class *max_jit_gl_gridshape_class;


C74_EXPORT void ext_main(void *r)
{
	t_class *maxclass, *jitclass;
	
	maxclass = class_new("jit.gl.gridshape", (method)max_jit_gl_gridshape_new, (method)max_jit_gl_gridshape_free, sizeof(t_max_jit_gl_gridshape), NULL, A_GIMME, 0);
	max_jit_class_obex_setup(maxclass, calcoffset(t_max_jit_gl_gridshape, obex));
	jitclass = jit_class_findbyname(gensym("jit_gl_gridshape"));
	max_jit_class_wrap_ob3d_inletinfo(maxclass, jitclass, 0);
	
	class_addmethod(maxclass, (method)max_jit_ob3d_assist, "assist", A_CANT, 0);
	class_addmethod(maxclass, (method)max_jit_ob3d_acceptsdrag, "acceptsdrag_unlocked", A_CANT, 0);
	class_addmethod(maxclass, (method)max_jit_ob3d_acceptsdrag, "acceptsdrag_locked", A_CANT, 0);

	// add methods for 3d drawing
	max_jit_class_ob3d_wrap(maxclass);
	
	// register our class with max
	class_register(CLASS_BOX, maxclass);
	max_jit_gl_gridshape_class = maxclass;

}

void max_jit_gl_gridshape_free(t_max_jit_gl_gridshape *x)
{
	max_jit_ob3d_detach(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_object_free(x);
}

void *max_jit_gl_gridshape_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_gl_gridshape *x;
	void *jit_ob;
	long attrstart;
	t_symbol *dest_name_sym = _jit_sym_nothing;

	if ((x = (t_max_jit_gl_gridshape *)max_jit_object_alloc(max_jit_gl_gridshape_class, gensym("jit_gl_gridshape"))))
	{
		//get normal args
		attrstart = max_jit_attr_args_offset(argc,argv);
		if (attrstart&&argv)
		{
			jit_atom_arg_getsym(&dest_name_sym, 0, attrstart, argv);
		}

		if ((jit_ob = jit_object_new(gensym("jit_gl_gridshape"), dest_name_sym)))
		{
			max_jit_obex_jitob_set(x, jit_ob);
			max_jit_obex_dumpout_set(x, outlet_new(x,NULL));
			max_jit_attr_args(x, argc, argv);

			// attach the jit object's ob3d to a new outlet for sending drawing messages.
			max_jit_ob3d_attach(x, jit_ob, outlet_new(x, "jit_matrix"));
		}
		else
		{
			jit_object_error((t_object *)x,"jit.gl.gridshape: could not allocate object");
			freeobject((t_object *)x);
			x = NULL;
		}
	}
	return (x);
}


