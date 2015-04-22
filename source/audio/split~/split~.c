/*
	split~: An audio version of the Max 'split' object
	Originally known as tap.split~, from Tap.Tools by Timothy Place
	Copyright 2011 Cycling '74
*/

#include "ext.h"		// standard Max include
#include "ext_obex.h"	// required for "new" (Max 4.5 and later) style objects
#include "z_dsp.h"		// required for audio objects


// struct to represent the object's state
typedef struct _split {
	t_pxobject	s_ob;			// audio object "base class"
	float		s_low;			// low bound of the range
	float		s_high;			// high bound of the range
	char		s_connected[3];	// array of bools indicating which inlets have audio signals
} t_split;


// method prototypes
void *split_new(t_symbol *msg, long argc, t_atom *argv);
void split_assist(t_split *x, void *b, long m, long a, char *s);
void split_int(t_split *x, long n);
void split_float(t_split *x, double val);
// (we can skip the prototypes for the perform methods; we'll define them in the body above the point where they are called)
void split_dsp64(t_split *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);


// global class pointer variable
static t_class *s_split_class = NULL;


//***********************************************************************************************

void ext_main(void *r)
{
	t_class *c = class_new("split~", (method)split_new, (method)dsp_free, sizeof(t_split), NULL, A_GIMME, 0);

	class_addmethod(c, (method)split_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)split_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)split_dsp64,		"dsp64",	A_CANT, 0);		// New 64-bit MSP dsp chain compilation for Max 6
	class_addmethod(c, (method)split_assist,	"assist",	A_CANT, 0);

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	s_split_class = c;
}


void *split_new(t_symbol *s, long argc, t_atom *argv)
{
	t_split *x = (t_split *)object_alloc(s_split_class);

	if (x) {
		dsp_setup((t_pxobject *)x, 3);				// 3 inlets (input, low-value, high-value)
		outlet_new((t_object *)x, "signal");		// last outlet: true/false
		outlet_new((t_object *)x, "signal");		// middle outlet: values out-of-range
		outlet_new((t_object *)x, "signal");		// first outlet: values w/in range

		atom_arg_getfloat(&x->s_low, 0, argc, argv);	// get typed in args
		atom_arg_getfloat(&x->s_high, 1, argc, argv);	// ...
	}
	return x;
}


//***********************************************************************************************

void split_assist(t_split *x, void *b, long msg, long arg, char *dst)
{
	if (msg == ASSIST_INLET) {
		switch (arg) {
		case 0: strcpy(dst, "(signal) Value to be sent to one of the 2 outlets"); break;
		case 1: strcpy(dst, "(signal/float) Set lower limit for left outlet"); break;
		case 2: strcpy(dst, "(signal/float) Set upper limit for left outlet"); break;
		}
	}
	else if (msg == ASSIST_OUTLET) {
		switch (arg) {
		case 0: strcpy(dst, "(signal) Input if within limits"); break;
		case 1: strcpy(dst, "(signal) Input if not within limits"); break;
		case 2: strcpy(dst, "(signal) Comparison result (1 or 0)"); break;
		}
	}
}


void split_float(t_split *x, double value)
{
	long inlet_number = proxy_getinlet((t_object *)x);

	if (inlet_number == 1)
		x->s_low = value;
	else if (inlet_number == 2)
		x->s_high = value;
	else
		object_error((t_object *)x, "oops -- maybe you sent a number to the wrong inlet?");
}


void split_int(t_split *x, long value)
{
	split_float(x, value);
}


//***********************************************************************************************

// We have 2 perform methods:
// One of the perform methods is for all 3 audio signals connected.
// The other perform method is optimized for the case where only the first audio signal is connected.


// Perform (signal) Method for 3 input signals, 64-bit MSP
void split_perform364(t_split *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double	*in1 = ins[0];		// Input 1
	t_double	*out1 = outs[0];	// Output 1
	t_double	*out2 = outs[1];	// Output 2
	t_double	*out3 = outs[2];	// Output 3
	int			n = sampleframes;
	t_double	value, low, high;

	// low and high only updated at the vector-rate, for efficiency
	// (cpu was in short supply on the G3 PowerBook when this object was written)
	low  = x->s_connected[1]? *ins[1] : x->s_low;
	high = x->s_connected[2]? *ins[2] : x->s_high;

	while (n--) {
		value = *in1++;
		if ((value >= low) && (value <= high)) {
			*out1++ = value;
			*out2++ = 0;
			*out3++ = 1;
		}
		else {
			*out1++ = 0;
			*out2++ = value;
			*out3++ = 0;
		}
	}
}


// Perform (signal) Method for 1 input signal, 64-bit MSP
void split_perform164(t_split *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double	*in1 = ins[0];		// Input 1
	t_double	*out1 = outs[0];		// Output 1
	t_double	*out2 = outs[1];		// Output 2
	t_double	*out3 = outs[2];		// Output 3
	int			n = sampleframes;
	t_double	value;
	t_double	low = x->s_low;		// cache struct object members locally to keep them in registers on the processor
	t_double	high = x->s_high;	// ... thus improving performance.

	while (n--) {
		value = *in1++;
		if ((value >= low) && (value <= high)) {
			*out1++ = value;
			*out2++ = 0;
			*out3++ = 1;
		}
		else {
			*out1++ = 0;
			*out2++ = value;
			*out3++ = 0;
		}
	}
}


//***********************************************************************************************

void split_dsp64(t_split *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	short i;

	for (i=0; i<6; i++)
		x->s_connected[i] = count[i];

	if (count[1] || count[2])	// IF the 2nd or 3rd inlet has a signal connected to it...
		object_method(dsp64, gensym("dsp_add64"), x, split_perform364, 0, NULL);
	else
		object_method(dsp64, gensym("dsp_add64"), x, split_perform164, 0, NULL);
}

