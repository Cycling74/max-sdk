/**
	@file
	plussz.c - one of the simplest max objects you can make -rdd 2001
	(plussz is/was the name of a Hungarian vitamin C tablet-drink from the early 90s)

	this example is provided for musicians who want to learn to write their own Max externals but who only
	have rudimentary computer programming skills and feel somewhat overwhelmed by the other examples in the Max SDK

	this object has 2 inlets and one outlet
	it responds to ints in its inlets and the 'bang' message in the left inlet
	it responds to the 'assistance' message sent by Max when the mouse is positioned over an inlet or outlet
		(including an assistance method is optional, but strongly sugggested)
	it adds its input values together and outputs their sum

	@ingroup	examples
*/

#include "ext.h"			// you must include this - it contains the external object's link to available Max functions
#include "ext_obex.h"		// this is required for all objects using the newer style for writing objects.

typedef struct _plussz {	// defines our object's internal variables for each instance in a patch
	t_object p_ob;			// object header - ALL objects MUST begin with this...
	long p_value0;			// int value - received from the left inlet and stored internally for each object instance
	long p_value1;			// int value - received from the right inlet and stored internally for each object instance
	void *p_outlet;			// outlet creation - inlets are automatic, but objects must "own" their own outlets
} t_plussz;


// these are prototypes for the methods that are defined below
void plussz_bang(t_plussz *x);
void plussz_int(t_plussz *x, long n);
void plussz_in1(t_plussz *x, long n);
void plussz_assist(t_plussz *x, void *b, long m, long a, char *s);
void *plussz_new(long n);


t_class *plussz_class;		// global pointer to the object class - so max can reference the object


//--------------------------------------------------------------------------

void ext_main(void *r)
{
	t_class *c;

	c = class_new("plussz", (method)plussz_new, (method)NULL, sizeof(t_plussz), 0L, A_DEFLONG, 0);
	// class_new() loads our external's class into Max's memory so it can be used in a patch
	// plussz_new = object creation method defined below

	class_addmethod(c, (method)plussz_bang,		"bang",		0);			// the method it uses when it gets a bang in the left inlet
	class_addmethod(c, (method)plussz_int,		"int",		A_LONG, 0);	// the method for an int in the left inlet (inlet 0)
	class_addmethod(c, (method)plussz_in1,		"in1",		A_LONG, 0);	// the method for an int in the right inlet (inlet 1)
	// "ft1" is the special message for floats
	class_addmethod(c, (method)plussz_assist,	"assist",	A_CANT, 0);	// (optional) assistance method needs to be declared like this

	class_register(CLASS_BOX, c);
	plussz_class = c;

	post("plussz object loaded...",0);	// post any important info to the max window when our class is loaded
}


//--------------------------------------------------------------------------

void *plussz_new(long n)		// n = int argument typed into object box (A_DEFLONG) -- defaults to 0 if no args are typed
{
	t_plussz *x;				// local variable (pointer to a t_plussz data structure)

	x = (t_plussz *)object_alloc(plussz_class); // create a new instance of this object

	intin(x,1);					// create a second int inlet (leftmost inlet is automatic - all objects have one inlet by default)
	x->p_outlet = intout(x);	// create an int outlet and assign it to our outlet variable in the instance's data structure

	x->p_value0	= 0;			// set initial (default) left operand value in the instance's data structure
	x->p_value1	= n;			// set initial (default) right operand value (n = variable passed to plussz_new)

	post(" new plussz object instance added to patch...",0); // post important info to the max window when new instance is created

	return(x);					// return a reference to the object instance
}


//--------------------------------------------------------------------------

void plussz_assist(t_plussz *x, void *b, long m, long a, char *s) // 4 final arguments are always the same for the assistance method
{
	if (m == ASSIST_OUTLET)
		sprintf(s,"Sum of Left and Right Inlets");
	else {
		switch (a) {
		case 0:
			sprintf(s,"Inlet %ld: Left Operand (Causes Output)", a);
			break;
		case 1:
			sprintf(s,"Inlet %ld: Right Operand (Added to Left)", a);
			break;
		}
	}
}


void plussz_bang(t_plussz *x)			// x = reference to this instance of the object
{
	long sum;							// local variable for this method

	sum = x->p_value0+x->p_value1;		// add left and right operands
	outlet_int(x->p_outlet, sum);		// send out the sum on bang
}


void plussz_int(t_plussz *x, long n)	// x = the instance of the object; n = the int received in the left inlet
{
	x->p_value0 = n;					// store left operand value in instance's data structure
	plussz_bang(x);						// ... call the bang method to sum and send out our outlet
}


void plussz_in1(t_plussz *x, long n)	// x = the instance of the object, n = the int received in the right inlet
{
	x->p_value1 = n;					// just store right operand value in instance's data structure and do nothing else
}


