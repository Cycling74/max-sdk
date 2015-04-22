/**
 @file
 dspstress~ - very simple msp object that does nothing except eat up a specified % of processor time

 updated 6/5/09 rbs: initial

 @ingroup	examples
 */

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

void *dspstress_class;


typedef struct _dspstress {
	t_pxobject	x_obj;
	double		x_cpuusagetarget;	// how much cpu to burn (0 - 100)
	double		x_svtime_ms;		// how long one signal vector takes in ms
} t_dspstress;


void *dspstress_new(double val);
void dspstress_perform64(t_dspstress *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void dspstress_float(t_dspstress *x, double f);
void dspstress_int(t_dspstress *x, long n);
void dspstress_dsp64(t_dspstress *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void dspstress_assist(t_dspstress *x, void *b, long m, long a, char *s);

void ext_main(void *r)
{
	t_class *c;

	c = class_new("dspstress~", (method)dspstress_new, (method)dsp_free, (short)sizeof(t_dspstress), 0L, A_DEFFLOAT, 0);

	class_addmethod(c, (method)dspstress_dsp64, "dsp64", A_CANT, 0); 	// respond to the dsp message
	// (sent to MSP objects when audio is turned on/off)
	class_addmethod(c, (method)dspstress_float, "float", A_FLOAT, 0);
	class_addmethod(c, (method)dspstress_int, "int", A_LONG, 0);
	class_addmethod(c, (method)dspstress_assist,"assist",A_CANT,0);
	class_dspinit(c);													// must call this function for MSP object classes

	class_register(CLASS_BOX, c);
	dspstress_class = c;
}

void dspstress_assist(t_dspstress *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
		case 0:
			strcpy(s,"Specify cpu usage % here");
			break;
		}
	}
}

void *dspstress_new(double val)
{
	t_dspstress *x = object_alloc(dspstress_class);
	dsp_setup((t_pxobject *)x,1);					// set up DSP for the instance and create signal inlet
	dspstress_float(x, val);
	return x;
}

void dspstress_float(t_dspstress *x, double f)				// the float and int routines cover both inlets.
{	// It doesn't matter which one is involved
	x->x_cpuusagetarget = f;
}

void dspstress_int(t_dspstress *x, long n)
{
	dspstress_float(x, (double) n);
}

void dspstress_perform64(t_dspstress *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	double spintime;
	double intime;
	double outtime;
	unsigned long spincounter = 0;

	spintime = x->x_svtime_ms * x->x_cpuusagetarget / 100.;
	intime = systimer_gettime();
	outtime = intime + spintime;

	while (systimer_gettime() < outtime) {
		// tra la la
		spincounter++;  // how high can we count?
	}
}


void dspstress_dsp64(t_dspstress *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->x_svtime_ms = maxvectorsize / samplerate * 1000.0;
	object_method(dsp64, gensym("dsp_add64"), x, dspstress_perform64, 0, NULL);
}
