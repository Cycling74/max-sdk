/**
 @file
 past - triggering after numbers get "past" a certain point

 updated 3/22/09 ajm: new API

 @ingroup	examples
 */

#include "ext.h"
#include "ext_obex.h"

typedef struct past
{
	t_object p_ob;
	t_atom p_vector[8];
	short p_size;
	short p_set;
	void *p_out;
} t_past;

void past_int(t_past *x, long n);
void past_float(t_past *x, double f);
void past_list(t_past *x, t_symbol *s, short ac, t_atom *av);
void past_clear(t_past *x);
void past_set(t_past *x, t_symbol *s, short ac, t_atom *av);
void past_assist(t_past *x, void *b, long m, long a, char *s);
void *past_new(t_symbol *s, short ac, t_atom *av);
void past_assign(t_past *x, short ac, t_atom *av);
short past_compare(t_past *x, t_atom *a, long index);

void *past_class;

void ext_main(void *r)
{
	t_class *c;

	c = class_new("past", (method)past_new, 0L, sizeof(t_past), 0L, A_GIMME, 0);
	class_addmethod(c, (method)past_int,	"int",		A_LONG, 0);
	class_addmethod(c, (method)past_float,	"float",	A_FLOAT, 0);
	class_addmethod(c, (method)past_list,	"list",		A_GIMME,0);
	class_addmethod(c, (method)past_clear,	"clear", 	0);
	class_addmethod(c, (method)past_assist,	"assist",	A_CANT,0);
	class_addmethod(c, (method)past_set,	"set",		A_GIMME,0);
	class_register(CLASS_BOX, c);
	past_class = c;

	return 0;
}

void past_int(t_past *x, long n)
{
	t_atom a;

	atom_setlong(&a, n);
	if (x->p_size==1) {
		if (past_compare(x,&a,0) > 0) {
			if (!x->p_set) {
				x->p_set = 1;
				outlet_bang(x->p_out);
			}
		} else {
			x->p_set = 0;
		}
	} else {
		if (past_compare(x,&a,0) < 0)
			x->p_set = 0;
	}
}

void past_float(t_past *x, double f)
{
	t_atom a;

	atom_setfloat(&a, f);
	if (x->p_size==1) {
		if (past_compare(x,&a,0) > 0) {
			if (!x->p_set) {
				x->p_set = 1;
				outlet_bang(x->p_out);
			}
		} else {
			x->p_set = 0;
		}
	} else {
		if (past_compare(x,&a,0) < 0)
			x->p_set = 0;
	}
}

void past_list(t_past *x, t_symbol *s, short ac, t_atom *av)
{
	short i;
	short canfail,result;

	canfail = false;
	if (ac <= x->p_size) {
		result = past_compare(x,av,0);
		if (result >= 0) {
			if (result == 0)
				canfail = true;
			for (i=1; i < ac; i++) {
				result = past_compare(x,av+i,i);
				if (result < 0) {
					if (canfail) {
						x->p_set = 0;
						return;	/* move this inside bracket 7/8/92 */
					}
				}
				if (canfail && result == 0)
					canfail = 1;
				else
					canfail = 0;
			}
			if (!x->p_set) {
				x->p_set = 1;
				outlet_bang(x->p_out);
			}
		} else {
			x->p_set = 0;
		}
	}
}

void past_clear(t_past *x)
{
	x->p_set = 0;
}

void past_set(t_past *x, t_symbol *s, short ac, t_atom *av)
{
	if (ac)
		past_assign(x,ac,av);
}

void past_assist(t_past *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s,"Input to be Synchronized");
	else
		sprintf(s,"bang When Numbers Rise Above Specified Value");
}

void *past_new(t_symbol *s, short ac, t_atom *av)
{
	t_past *x;

	x = object_alloc(past_class);
	x->p_out = bangout((t_object *)x);
	past_assign(x,ac,av);
	x->p_set = 0;
	return x;
}

void past_assign(t_past *x, short ac, t_atom *av)
{
	short i;

	if (ac > 8)
		ac = 8;
	for (i = 0; i < ac; i++,av++)
		x->p_vector[i] = *av;
	x->p_size = ac;
}

short past_compare(t_past *x, t_atom *a, long index)
{
	t_atom *b;
	float temp1;

	b = x->p_vector + index;
	if (atom_gettype(a) == A_LONG) {
		if (atom_gettype(b) == A_LONG) {
			if (atom_getlong(a) > atom_getlong(b))
				return 1;
			else if (atom_getlong(a) == atom_getlong(b))
				return 0;
			else
				return -1;
		} else if (atom_gettype(b) == A_FLOAT) {
			temp1 = (float)atom_getlong(a);
			if (temp1 > atom_getfloat(b))
				return 1;
			else if (temp1 == atom_getfloat(b))
				return 0;
			else
				return -1;
		} else {
			if (atom_getlong(a) > 0)
				return 1;
			else if (atom_getlong(a) == 0)
				return 0;
			else
				return -1;
		}
	} else if (atom_gettype(a) == A_FLOAT) {
		if (atom_gettype(b) == A_LONG) {
			temp1 = (float)atom_getlong(b);
			if (atom_getfloat(a) > temp1)
				return 1;
			else if (atom_getfloat(a) == temp1)
				return 0;
			else
				return -1;
		} else if (atom_gettype(b) == A_FLOAT) {
			if (atom_getfloat(a) > atom_getfloat(b))
				return 1;
			else if (atom_getfloat(a) == atom_getfloat(b))
				return 0;
			else
				return -1;
		} else {
			if (atom_getfloat(a) > 0.)
				return 1;
			else if (atom_getfloat(a) == 0.)
				return 0;
			else
				return -1;
		}
	}
	return -1;
	// return -1 when in doubt.
	// if someone is trying to compare a t_symbol you just say it's less than that with which you are comparing.
	// in theory this should never happen with the past object.
}
