/**
 @file
 iter - sequential list unpacking

 updated 3/22/09 ajm: new API

 @ingroup	examples
 */

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"

typedef struct iter {
	t_object i_ob;
	t_atom *i_av;
	long i_ac;
} t_iter;

static t_class *s_iter_class;

void iter_assist(t_iter *x, void *b, long m, long a, char *s);
void iter_int(t_iter *x, t_atom_long n);
void iter_float(t_iter *x, double f);
void iter_bang(t_iter *x);
void iter_list(t_iter *x, t_symbol *s, long ac, t_atom *av);
void iter_anything(t_iter *x, t_symbol *s, long ac, t_atom *av);
void *iter_new(long dummy);
void iter_free(t_iter *x);
void iter_resize(t_iter *x, long size);

C74_EXPORT void ext_main(void *r)
{
	t_class *c;

	c = class_new("iter", (method)iter_new, (method)iter_free, (short)sizeof(t_iter), 0L, A_DEFLONG, 0);
	class_addmethod(c, (method)iter_int, "int", A_LONG, 0);
	class_addmethod(c, (method)iter_bang, "bang", 0);
	class_addmethod(c, (method)iter_list, "list", A_GIMME, 0);
	class_addmethod(c, (method)iter_anything, "anything", A_GIMME, 0);
	class_addmethod(c, (method)iter_assist, "assist", A_CANT, 0);
	class_addmethod(c, (method)iter_float, "float", A_FLOAT, 0);
	class_register(CLASS_BOX, c);
	s_iter_class = c;
}

void iter_assist(t_iter *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s,"list to be Unraveled");
	else
		sprintf(s,"Sequential Output of Incoming list");
}

void iter_int(t_iter *x, t_atom_long n)
{
	iter_resize(x, 1);
	x->i_ac = 1;
	atom_setlong(x->i_av, n);
	outlet_int(x->i_ob.o_outlet, n);
}

void iter_float(t_iter *x, double f)
{
	iter_resize(x, 1);
	x->i_ac = 1;
	atom_setfloat(x->i_av, f);
	outlet_float(x->i_ob.o_outlet, f);
}

void iter_bang(t_iter *x)
{
	long i;
	t_atom *av;

	for (i=0, av = x->i_av; i < x->i_ac; i++,av++) {
		if (atom_gettype(av) == A_LONG)
			outlet_int(x->i_ob.o_outlet, atom_getlong(av));
		else if (atom_gettype(av) == A_FLOAT)
			outlet_float(x->i_ob.o_outlet, atom_getfloat(av));
		else if (atom_gettype(av) == A_SYM)
			outlet_anything(x->i_ob.o_outlet, atom_getsym(av), 0, 0);
	}
}

void iter_list(t_iter *x, t_symbol *s, long ac, t_atom *av)
{
	long i;

	iter_resize(x, ac);
	
	for (i = 0; i < ac; i++,av++) {
		x->i_av[i] = *av;
		if (atom_gettype(av)==A_LONG)
			outlet_int(x->i_ob.o_outlet, atom_getlong(av));
		else if (atom_gettype(av)==A_FLOAT)
			outlet_float(x->i_ob.o_outlet, atom_getfloat(av));
		else if (atom_gettype(av)==A_SYM)
			outlet_anything(x->i_ob.o_outlet, atom_getsym(av),0,0);
	}
	x->i_ac = ac;
}

void iter_anything(t_iter *x, t_symbol *s, long ac, t_atom *av)
{
	short i;

	iter_resize(x, ac+1);
	outlet_anything(x->i_ob.o_outlet, s, 0, 0);
	atom_setsym(x->i_av + 0, s);

	for (i = 0; i < ac; i++,av++) {
		x->i_av[i + 1] = *av;
		if (atom_gettype(av)==A_LONG)
			outlet_int(x->i_ob.o_outlet, atom_getlong(av));
		else if (atom_gettype(av)==A_FLOAT)
			outlet_float(x->i_ob.o_outlet, atom_getfloat(av));
		else if (atom_gettype(av)==A_SYM)
			outlet_anything(x->i_ob.o_outlet, atom_getsym(av), 0, 0);
	}
	x->i_ac = ac+1;
}

void *iter_new(long dummy)
{
	t_iter *x;

	x = object_alloc(s_iter_class);
	x->i_ac = 0;
	x->i_av = NULL;
	outlet_new(x, NULL);
	return x;
}

void iter_free(t_iter *x)
{
	if (x->i_av)
		sysmem_freeptr(x->i_av);
}

void iter_resize(t_iter *x, long size)
{
	if (size != x->i_ac) {
		if (x->i_av)
			sysmem_freeptr(x->i_av);
		if (size)
			x->i_av = (t_atom *)sysmem_newptr(size * sizeof(t_atom));
		else
			x->i_av = NULL;
		x->i_ac = size;
	}
}
