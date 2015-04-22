/**
 @file
 plussz~ - a very simple example of a basic MSP object

 updated 3/22/09 ajm: new API

 @ingroup	examples
 */

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

void *plussz_class;


typedef struct _plussz {
	t_pxobject	x_obj;
	double		x_val;
	long		x_connected;
} t_plussz;


void *plussz_new(double val);
void plussz_float(t_plussz *x, double f);
void plussz_int(t_plussz *x, long n);
void plussz_dsp64(t_plussz *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void plussz_assist(t_plussz *x, void *b, long m, long a, char *s);


void ext_main(void *r)
{
	t_class *c = class_new("plussz~", (method)plussz_new, (method)dsp_free, sizeof(t_plussz), NULL, A_DEFFLOAT, 0);

	class_addmethod(c, (method)plussz_dsp64, "dsp64", A_CANT, 0); 	// respond to the dsp message
	class_addmethod(c, (method)plussz_float, "float", A_FLOAT, 0);
	class_addmethod(c, (method)plussz_int, "int", A_LONG, 0);
	class_addmethod(c, (method)plussz_assist,"assist",A_CANT,0);
	class_dspinit(c);												// must call this function for MSP object classes

	class_register(CLASS_BOX, c);
	plussz_class = c;
}


void *plussz_new(double val)
{
	t_plussz *x = object_alloc(plussz_class);
	dsp_setup((t_pxobject *)x,2);					// set up DSP for the instance and create signal inlets
	outlet_new((t_pxobject *)x, "signal");			// signal outlets are created like this
	x->x_val = val;
	return (x);
}


void plussz_assist(t_plussz *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
		case 0:
			sprintf(s,"(Signal) This + Right Inlet");
			break;
		case 1:
			sprintf(s,"(Signal) Left Inlet + This");
			break;
		}
	}
	else
		sprintf(s,"(Signal) Addition Result");
}


// the float and int routines cover both inlets.  It doesn't matter which one is involved
void plussz_float(t_plussz *x, double f)
{
	x->x_val = f;
}


void plussz_int(t_plussz *x, long n)
{
	x->x_val = n;
}


// our perform method if one signal inlet is connected
void plussz_offset_perform64(t_plussz *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double	*in = ins[x->x_connected];
	t_double	*out = outs[0];
	double		val = x->x_val;

	while (sampleframes--)
		*out++ = val + *in++;
}


// our perform method if both signal inlets are connected
void plussz_perform64(t_plussz *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double *in1 = ins[0];
	t_double *in2 = ins[1];
	t_double *out = outs[0];

	while (sampleframes--)
		*out++ = *in1++ + *in2++;
}


// method called when dsp is turned on
void plussz_dsp64(t_plussz *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	if (!count[0]) {
		x->x_connected = 1;
		object_method(dsp64, gensym("dsp_add64"), x, plussz_offset_perform64, 0, NULL);
	}
	else if (!count[1]) {
		x->x_connected = 0;
		object_method(dsp64, gensym("dsp_add64"), x, plussz_offset_perform64, 0, NULL);
	}
	else
		object_method(dsp64, gensym("dsp_add64"), x, plussz_perform64, 0, NULL);
}

