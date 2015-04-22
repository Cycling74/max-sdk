/**
	@file
	plussz2.c - a version of plussz2 that demonstrates the use of proxy inlets.
	see plussz.c for more comments and information.

	@ingroup	examples
*/

#include "ext.h"				// you must include this - it contains the external object's link to available Max functions
#include "ext_obex.h"			// this is required for all objects using the newer style for writing objects.

typedef struct _plussz2 {		// defines our object's internal variables for each instance in a patch
	t_object	ob;				// object header - ALL objects MUST begin with this...
	t_atom		l;				// stored value from left inlet
	t_atom		r;				// stored value from right inlet
	void		*outlet;		// outlet creation - inlets are automatic, but objects must "own" their own outlets
	void		*proxy;			// proxy inlet
	long		proxy_inletnum;	// # of inlet currently in use
} t_plussz2;


// these are prototypes for the methods that are defined below
void *plussz2_new(long n);
void plussz2_free(t_plussz2 *x);
void plussz2_assist(t_plussz2 *x, void *b, long m, long a, char *s);
void plussz2_bang(t_plussz2 *x);
void plussz2_int(t_plussz2 *x, long n);
void plussz2_float(t_plussz2 *x, double f);


t_class *plussz2_class;		// global pointer to the object class - so max can reference the object


//--------------------------------------------------------------------------

void ext_main(void *r)
{
	t_class *c;

	c = class_new("plussz2", (method)plussz2_new, (method)plussz2_free, sizeof(t_plussz2), 0L, A_GIMME, 0);

	class_addmethod(c, (method)plussz2_bang,	"bang",		0);				// the method it uses when it gets a bang in the left inlet
	class_addmethod(c, (method)plussz2_int,		"int",		A_LONG, 0);		// the method for ints in any inlet
	class_addmethod(c, (method)plussz2_float,	"float",	A_FLOAT, 0);	// the method for floats in any inlet
	class_addmethod(c, (method)plussz2_assist,	"assist",	A_CANT, 0);		// (optional) assistance method needs to be declared like this

	class_register(CLASS_BOX, c);
	plussz2_class = c;

	post("plussz2 object loaded...",0);	// post any important info to the max window when our class is loaded
}


//--------------------------------------------------------------------------

void *plussz2_new(long n)		// n = int argument typed into object box (A_DEFLONG) -- defaults to 0 if no args are typed
{
	t_plussz2 *x;				// local variable (pointer to a t_plussz2 data structure)

	x = (t_plussz2 *)object_alloc(plussz2_class); // create a new instance of this object
	if(x) {
		x->proxy = proxy_new(x, 1, &x->proxy_inletnum);	// fully-flexible inlet for any type
		x->outlet = outlet_new(x, NULL);				// fully-flexible outlet for any type

		// initialize L and R inlet atoms to (int)0
		atom_setlong(&x->l, 0);
		atom_setlong(&x->r, 0);

		post(" new plussz2 object instance added to patch...",0); // post important info to the max window when new instance is created
	}
	return(x);					// return a reference to the object instance
}


void plussz2_free(t_plussz2 *x)
{
	object_free(x->proxy);		// frees all resources associated with the proxy
}


//--------------------------------------------------------------------------

void plussz2_assist(t_plussz2 *x, void *b, long m, long a, char *s) // 4 final arguments are always the same for the assistance method
{
	if (m == ASSIST_INLET) {
		switch (a) {
		case 0:
			sprintf(s,"Inlet %ld: Left Operand (Causes Output)", a);
			break;
		case 1:
			sprintf(s,"Inlet %ld: Right Operand (Added to Left)", a);
			break;
		}
	} else
		sprintf(s,"Sum of Left and Right Inlets");
}


void plussz2_bang(t_plussz2 *x)
{
	long lop;
	float fop;

	// if both L and R are INTEGER, OUTPUT AN INT
	if (x->l.a_type == A_LONG && x->r.a_type == A_LONG) {
		lop = atom_getlong(&x->l) + atom_getlong(&x->r);
		outlet_int(x->outlet, lop);
	}
	else { // OUTPUT A FLOAT
		fop = atom_getfloat(&x->l) + atom_getfloat(&x->r);
		outlet_float(x->outlet, fop);
	}
}


void plussz2_int(t_plussz2 *x, long n)
{
	long inlet = proxy_getinlet((t_object *)x); // what inlet did this message come in through?

	post("int came in via inlet %ld", inlet);

	if (inlet == 1) { // RIGHT INLET
		atom_setlong(&x->r, n); // SET INT VAL
	}
	else { // LEFT INLET
		atom_setlong(&x->l, n);
		plussz2_bang(x); // bang for left inlet, trigger calculation
	}
}


void plussz2_float(t_plussz2 *x, double f)
{
	long inlet = proxy_getinlet((t_object *)x); // what inlet did this message come in through?

	post("float came in via inlet %ld", inlet);

	if (inlet == 1) { // RIGHT INLET
		atom_setfloat(&x->r, f); // SET FLOAT VAL
	}
	else { // LEFT INLET
		atom_setfloat(&x->l, f);
		plussz2_bang(x); // bang for left inlet, trigger calculation
	}
}


