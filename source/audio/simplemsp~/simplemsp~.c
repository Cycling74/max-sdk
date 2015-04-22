/**
	@file
	simplemsp~: a simple audio object for Max
	original by: jeremy bernstein, jeremy@bootsquad.com
	@ingroup examples
*/

#include "ext.h"			// standard Max include, always required (except in Jitter)
#include "ext_obex.h"		// required for "new" style objects
#include "z_dsp.h"			// required for MSP objects


// struct to represent the object's state
typedef struct _simplemsp {
	t_pxobject		ob;			// the object itself (t_pxobject in MSP instead of t_object)
	double			offset; 	// the value of a property of our object
} t_simplemsp;


// method prototypes
void *simplemsp_new(t_symbol *s, long argc, t_atom *argv);
void simplemsp_free(t_simplemsp *x);
void simplemsp_assist(t_simplemsp *x, void *b, long m, long a, char *s);
void simplemsp_float(t_simplemsp *x, double f);
void simplemsp_dsp64(t_simplemsp *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void simplemsp_perform64(t_simplemsp *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);


// global class pointer variable
static t_class *simplemsp_class = NULL;


//***********************************************************************************************

void ext_main(void *r)
{
	// object initialization, note the use of dsp_free for the freemethod, which is required
	// unless you need to free allocated memory, in which case you should call dsp_free from
	// your custom free function.

	t_class *c = class_new("simplemsp~", (method)simplemsp_new, (method)dsp_free, (long)sizeof(t_simplemsp), 0L, A_GIMME, 0);

	class_addmethod(c, (method)simplemsp_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)simplemsp_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)simplemsp_assist,	"assist",	A_CANT, 0);

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	simplemsp_class = c;
}


void *simplemsp_new(t_symbol *s, long argc, t_atom *argv)
{
	t_simplemsp *x = (t_simplemsp *)object_alloc(simplemsp_class);

	if (x) {
		dsp_setup((t_pxobject *)x, 1);	// MSP inlets: arg is # of inlets and is REQUIRED!
		// use 0 if you don't need inlets
		outlet_new(x, "signal"); 		// signal outlet (note "signal" rather than NULL)
		x->offset = 0.0;
	}
	return (x);
}


// NOT CALLED!, we use dsp_free for a generic free function
void simplemsp_free(t_simplemsp *x)
{
	;
}


void simplemsp_assist(t_simplemsp *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { //inlet
		sprintf(s, "I am inlet %ld", a);
	}
	else {	// outlet
		sprintf(s, "I am outlet %ld", a);
	}
}


void simplemsp_float(t_simplemsp *x, double f)
{
	x->offset = f;
}


// registers a function for the signal chain in Max
void simplemsp_dsp64(t_simplemsp *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	post("my sample rate is: %f", samplerate);

	// instead of calling dsp_add(), we send the "dsp_add64" message to the object representing the dsp chain
	// the arguments passed are:
	// 1: the dsp64 object passed-in by the calling function
	// 2: the symbol of the "dsp_add64" message we are sending
	// 3: a pointer to your object
	// 4: a pointer to your 64-bit perform method
	// 5: flags to alter how the signal chain handles your object -- just pass 0
	// 6: a generic pointer that you can use to pass any additional data to your perform method

	object_method(dsp64, gensym("dsp_add64"), x, simplemsp_perform64, 0, NULL);
}


// this is the 64-bit perform method audio vectors
void simplemsp_perform64(t_simplemsp *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double *inL = ins[0];		// we get audio for each inlet of the object from the **ins argument
	t_double *outL = outs[0];	// we get audio for each outlet of the object from the **outs argument
	int n = sampleframes;

	// this perform method simply copies the input to the output, offsetting the value
	while (n--)
		*outL++ = *inL++ + x->offset;
}

