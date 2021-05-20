/**
	@file
	minimum - output the minimum of a group of numbers

	updated 3/22/09 ajm: new API

	@ingroup	examples
*/

#include "ext.h"
#include "ext_obex.h"
#include "ext_systhread.h"

typedef struct _minimum
{
	struct object m_ob;
	t_atom *m_args;
	long m_count;
	long m_incount;
	long m_outtype;
	void *m_out2;
	void *m_out;
	t_systhread_mutex m_mutex;
} t_minimum;

static t_class *s_minimum_class;

void minimum_compare(t_atom *max, t_atom *newone, long *i, long *minIndex);
void minimum_bang(t_minimum *x);
void minimum_int(t_minimum *x, t_atom_long n);
void minimum_in1(t_minimum *x, t_atom_long n);
void minimum_float(t_minimum *x, double f);
void minimum_ft1(t_minimum *x, double f);
void minimum_list(t_minimum *x, t_symbol *s, long ac, t_atom *av);
void minimum_assist(t_minimum *x, void *b, long m, long a, char *s);
void minimum_inletinfo(t_minimum *x, void *b, long a, char *t);
void *minimum_new(t_symbol *s, long ac, t_atom *av);
void minimum_free(t_minimum *x);
void minimum_resize(t_minimum *x, long size);


C74_EXPORT void ext_main(void *r)
{
	t_class *c;
	
	c = class_new("minimum", (method)minimum_new, (method)minimum_free, (short)sizeof(t_minimum), 0L, A_GIMME, 0);
	class_addmethod(c, (method)minimum_bang, "bang", 0);
	class_addmethod(c, (method)minimum_int, "int", A_LONG, 0);
	class_addmethod(c, (method)minimum_in1, "in1", A_LONG, 0);
	class_addmethod(c, (method)minimum_float, "float", A_FLOAT, 0);
	class_addmethod(c, (method)minimum_ft1, "ft1", A_FLOAT, 0);
	class_addmethod(c, (method)minimum_list,"list",A_GIMME,0);
	class_addmethod(c, (method)minimum_assist,"assist",A_CANT,0);
	class_addmethod(c, (method)minimum_inletinfo, "inletinfo", A_CANT, 0);
	class_register(CLASS_BOX, c);
	s_minimum_class = c;
}

void minimum_compare(t_atom *min, t_atom *newone, long *i, long *minIndex)
{
	double fa, fb;
	t_atom_long ia, ib;
	long typea, typeb;
	
	if (atom_gettype(min) == A_NOTHING) {
		if (atom_gettype(newone) == A_LONG)
			atom_setlong(min, atom_getlong(newone));
		else if (atom_gettype(newone) == A_FLOAT)
			atom_setfloat(min, atom_getfloat(newone));
		else
			atom_setlong(min, 0);
		return;
	}
	if (min->a_type == A_FLOAT) {
		fa = atom_getfloat(min);
		typea = A_FLOAT;
	} else {
		ia = atom_getlong(min);
		fa = (double)ia;
		typea = A_LONG;
	}
	
	if (atom_gettype(newone) == A_FLOAT) {
		fb = atom_getfloat(newone);
		typeb = A_FLOAT;
	} else {
		ib = atom_getlong(newone);
		fb = (double)ib;
		typeb = A_LONG;
	}
	
	if (typea == A_LONG && typeb == A_LONG) {
		if (ia <= ib)
			atom_setlong(min, ia);
		else {
			*minIndex = *i;
			atom_setlong(min, ib);
		}
	} else {	// compare as floats but output the minimum's type
		if (fa <= fb) {
			if (typea == A_LONG)
				atom_setlong(min, ia);
			else
				atom_setfloat(min, fa);
		} else {
			*minIndex = *i;
			if (typeb == A_LONG)
				atom_setlong(min, ib);
			else
				atom_setfloat(min, fb);
		}
	}
}

void minimum_bang(t_minimum *x)
{
	long i;
	t_atom theMin;
	long minIndex;
	t_atom_long res;
	double fres;
	
	minIndex = 0;
	theMin.a_type = A_NOTHING;
	
	systhread_mutex_lock(x->m_mutex);
	for (i=0; i < x->m_count; i++)
		minimum_compare(&theMin,x->m_args+i, &i, &minIndex);
	systhread_mutex_unlock(x->m_mutex);
	
	outlet_int(x->m_out2, minIndex);
	if (x->m_outtype==A_LONG) {
		if (atom_gettype(&theMin)==A_LONG)
			res = atom_getlong(&theMin);
		else
			res = (t_atom_long)atom_getfloat(&theMin);
		outlet_int(x->m_out, res);
	} else {
		if (atom_gettype(&theMin)==A_FLOAT)
			fres = atom_getfloat(&theMin);
		else
			fres = (double)atom_getlong(&theMin);
		outlet_float(x->m_out, fres);
	}
}

void minimum_int(t_minimum *x, t_atom_long n)
{
	systhread_mutex_lock(x->m_mutex);
	atom_setlong(x->m_args, n);
	systhread_mutex_unlock(x->m_mutex);
	minimum_bang(x);
}

void minimum_in1(t_minimum *x, t_atom_long n)
{
	t_atom tmp = x->m_args[0];
	
	systhread_mutex_lock(x->m_mutex);
	minimum_resize(x,2);
	x->m_args[0] = tmp;
	atom_setlong(x->m_args + 1, n);
	x->m_count = 2;
	systhread_mutex_unlock(x->m_mutex);
}


void minimum_float(t_minimum *x, double f)
{
	systhread_mutex_lock(x->m_mutex);
	atom_setfloat(x->m_args,f);
	systhread_mutex_unlock(x->m_mutex);
	minimum_bang(x);
}

void minimum_ft1(t_minimum *x, double f)
{
	t_atom tmp = x->m_args[0];
	
	systhread_mutex_lock(x->m_mutex);
	minimum_resize(x,2);
	x->m_args[0] = tmp;
	atom_setfloat(x->m_args+1,f);
	x->m_count = 2;
	systhread_mutex_unlock(x->m_mutex);
}

void minimum_list(t_minimum *x, t_symbol *s, long ac, t_atom *av)
{
	long i;
	
	systhread_mutex_lock(x->m_mutex);
	minimum_resize(x,ac);
	for (i=0; i < ac; i++,av++) {
		if (atom_gettype(av)==A_LONG)
			atom_setlong(x->m_args+i,atom_getlong(av));
		else if (atom_gettype(av)==A_FLOAT)
			atom_setfloat(x->m_args+i,atom_getfloat(av));
	}
	x->m_count = ac;
	systhread_mutex_unlock(x->m_mutex);
	minimum_bang(x);
}

void minimum_inletinfo(t_minimum *x, void *b, long a, char *t)
{
	if (a)
		*t = 1;
}

void minimum_assist(t_minimum *x, void *b, long m, long a, char *s)
{
	if (m==ASSIST_INLET) {
		switch (a) {
			case 0: sprintf(s,"Compares Left and Right Inlets"); break;
			case 1: sprintf(s,"Value to be Compared"); break;
		}
	}
	else {
		if (a == 0)
			sprintf(s,"Minimum Value");
		if (a == 1)
			sprintf(s,"Index of the Minimum Value");
	}
}

void *minimum_new(t_symbol *s, long ac, t_atom *av)
{
	t_minimum *x;
	
	x = object_alloc(s_minimum_class);
	systhread_mutex_new(&x->m_mutex, 0);
	x->m_count = 0;
	x->m_args = NULL;
	minimum_resize(x,2);
	x->m_out2 = intout(x);
	if (ac) {
		x->m_args[1] = *av;
		if (atom_gettype(av)==A_LONG) {
			x->m_args[0].a_type = x->m_outtype = A_LONG;
			x->m_out = intout(x);
			x->m_args[0].a_w.w_long = 0;
			intin(x,1);
		} else if (atom_gettype(av)==A_FLOAT) {
			x->m_args[0].a_type = x->m_outtype = A_FLOAT;
			x->m_out = floatout(x);
			x->m_args[0].a_w.w_float = 0;
			floatin(x,1);
		} else {
			x->m_outtype = A_LONG;
			intin(x,1);
			x->m_out = intout(x);
			atom_setlong(x->m_args+1,0L);
			atom_setlong(x->m_args,0L);
		}
	} else {
		x->m_outtype = A_LONG;
		intin(x,1);
		x->m_out = intout(x);
		atom_setlong(x->m_args+1,0L);
		atom_setlong(x->m_args,0L);
	}
	return x;
}

void minimum_free(t_minimum *x)
{
	if (x->m_args)
		sysmem_freeptr(x->m_args);
	systhread_mutex_free(x->m_mutex);
}

// thread protection for resizing is handled by this function's caller
void minimum_resize(t_minimum *x, long size)
{
	if (size!=x->m_count) {
		if (x->m_args)
			sysmem_freeptr(x->m_args);
		if (size)
			x->m_args = (t_atom *)sysmem_newptr(size*sizeof(t_atom));
		else
			x->m_args = NULL;
		x->m_count = size;
	}
}
