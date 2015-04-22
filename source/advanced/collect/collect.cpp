/**
	@file
	collect - collect numbers and operate on them.
			- demonstrates use of C++ and the STL in a Max external
			- also demonstrates use of a mutex for thread safety
			- on Windows, demonstrate project setup for static linking to the Microsoft Runtime

	@ingroup	examples

	Copyright 2009 - Cycling '74
	Timothy Place, tim@cycling74.com
*/

#include "ext.h"
#include "ext_obex.h"
#include "ext_strings.h"
#include "ext_common.h"
#include "ext_systhread.h"

#include <vector>
using namespace std;

// a wrapper for cpost() only called for debug builds on Windows
// to see these console posts, run the DbgView program (part of the SysInternals package distributed by Microsoft)
#if defined( NDEBUG ) || defined( MAC_VERSION )
#define DPOST
#else
#define DPOST cpost
#endif


// a c++ class representing a number, and types for a vector of those numbers
class number {
private:
	double value;
public:
	number(double &newValue)
	{
		value = newValue;
	}

	void setValue(const double &newValue)
	{
		value = newValue;
	}

	void getValue(double &retrievedValue)
	{
		retrievedValue = value;
	}
};
typedef std::vector<number>		numberVector;
typedef numberVector::iterator	numberIterator;


// max object instance data
typedef struct _collect {
	t_object			c_box;
	numberVector		*c_vector;	// note: you must store this as a pointer and not directly as a member of the object's struct
	void				*c_outlet;
	t_systhread_mutex	c_mutex;
} t_collect;


// prototypes
void	*collect_new(t_symbol *s, long argc, t_atom *argv);
void	collect_free(t_collect *x);
void	collect_assist(t_collect *x, void *b, long m, long a, char *s);
void	collect_bang(t_collect *x);
void	collect_count(t_collect *x);
void	collect_int(t_collect *x, long value);
void	collect_float(t_collect *x, double value);
void	collect_list(t_collect *x, t_symbol *msg, long argc, t_atom *argv);
void	collect_clear(t_collect *x);


// globals
static t_class	*s_collect_class = NULL;

/************************************************************************************/

void ext_main(void *r)
{
	t_class	*c = class_new("collect",
						   (method)collect_new,
						   (method)collect_free,
						   sizeof(t_collect),
						   (method)NULL,
						   A_GIMME,
						   0);

	class_addmethod(c, (method)collect_bang,	"bang",			0);
	class_addmethod(c, (method)collect_int,		"int",			A_LONG,	0);
	class_addmethod(c, (method)collect_float,	"float",		A_FLOAT,0);
	class_addmethod(c, (method)collect_list,	"list",			A_GIMME,0);
	class_addmethod(c, (method)collect_clear,	"clear",		0);
	class_addmethod(c, (method)collect_count,	"count",		0);
	class_addmethod(c, (method)collect_assist,	"assist",		A_CANT, 0);
	class_addmethod(c, (method)stdinletinfo,	"inletinfo",	A_CANT, 0);

	class_register(CLASS_BOX, c);
	s_collect_class = c;
}


/************************************************************************************/
// Object Creation Method

void *collect_new(t_symbol *s, long argc, t_atom *argv)
{
	t_collect	*x;

	x = (t_collect *)object_alloc(s_collect_class);
	if (x) {
		systhread_mutex_new(&x->c_mutex, 0);
		x->c_outlet = outlet_new(x, NULL);
		x->c_vector = new numberVector;
		x->c_vector->reserve(10);
		collect_list(x, gensym("list"), argc, argv);
	}
	return(x);
}


void collect_free(t_collect *x)
{
	systhread_mutex_free(x->c_mutex);
	delete x->c_vector;
}


/************************************************************************************/
// Methods bound to input/inlets

void collect_assist(t_collect *x, void *b, long msg, long arg, char *dst)
{
	if (msg==1)
		strcpy(dst, "input");
	else if (msg==2)
		strcpy(dst, "output");
}


void collect_bang(t_collect *x)
{
	numberIterator iter, begin, end;
	int i = 0;
	long ac = 0;
	t_atom *av = NULL;
	double value;

	DPOST("head\n");
	systhread_mutex_lock(x->c_mutex);
	ac = x->c_vector->size();

	DPOST("ac=%ld\n", ac);
	if (ac)
		av = new t_atom[ac];

	if (ac && av) {
		DPOST("assigning begin and end\n");
		begin = x->c_vector->begin();
		end = x->c_vector->end();

		DPOST("assigning iter\n");
		iter = begin;

		DPOST("entering for\n", ac);
		for (;;) {
			DPOST("i=%i\n", i);
			(*iter).getValue(value);
			atom_setfloat(av+i, value);

			DPOST("incrementing\n");
			i++;
			iter++;

			DPOST("comparing\n");
			if (iter == end)
				break;
		}
		systhread_mutex_unlock(x->c_mutex);	// must unlock before calling _clear() or we will deadlock

		DPOST("about to clear\n", ac);
		collect_clear(x);

		DPOST("about to outlet\n", ac);
		outlet_anything(x->c_outlet, gensym("list"), ac, av); // don't want to call outlets in mutexes either

		DPOST("about to delete\n", ac);
		delete[] av;
	}
	else
		systhread_mutex_unlock(x->c_mutex);
}


void collect_count(t_collect *x)
{
	outlet_int(x->c_outlet, x->c_vector->size());
}


void collect_int(t_collect *x, long value)
{
	collect_float(x, value);
}


void collect_float(t_collect *x, double value)
{
	systhread_mutex_lock(x->c_mutex);
	x->c_vector->push_back(value);
	systhread_mutex_unlock(x->c_mutex);
}


void collect_list(t_collect *x, t_symbol *msg, long argc, t_atom *argv)
{
	systhread_mutex_lock(x->c_mutex);
	for (int i=0; i<argc; i++) {
		double value = atom_getfloat(argv+i);
		x->c_vector->push_back(value);
	}
	systhread_mutex_unlock(x->c_mutex);
}


void collect_clear(t_collect *x)
{
	systhread_mutex_lock(x->c_mutex);
	x->c_vector->clear();
	systhread_mutex_unlock(x->c_mutex);
}

