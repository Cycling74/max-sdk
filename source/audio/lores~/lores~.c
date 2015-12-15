/**
 @file
 lores - A low pass controllable with freq and res

 updated 3/22/09 ajm: new API

 @ingroup	examples
 */

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include <math.h>

#define SMOOTHING_VERSION 0

void *lores_class;

typedef struct _lores
{
	t_pxobject l_obj;
	double l_freq;			// stored cutoff frequency in Hz
	double l_r;				// stored resonance (0-1)
	double l_a1;				// computed coefficient
	double l_a2;				// computer coefficient
	double l_a1p;			// previous computed coefficient
	double l_a2p;			// previous computer coefficient
	double l_ym1;			// previous output sample
	double l_ym2;			// previous to previous output sample
	double l_fqterm;			// computed frequency term
	double l_resterm;		// computer resonance term
	double l_2pidsr;			// stored value of 2 pi over the sampling rate
	short l_rcon;			// is a signal connected to the resonance inlet
	short l_fcon;			// is a signal connected to the frequency inlet
} t_lores;

void lores_dsp(t_lores *x, t_signal **sp, short *count);
void lores_dsp64(t_lores *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
t_int *lores_perform(t_int *w);
void lores_perform64(t_lores *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
t_int *lores_perform_unroll(t_int *w);
void lores_perform_unroll64(t_lores *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
t_int *lores_perform_unroll_smooth(t_int *w);
void lores_perform_unroll_smooth64(t_lores *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void lores_int(t_lores *x, long n);
void lores_float(t_lores *x, double f);
void lores_calc(t_lores *x);
void lores_clear(t_lores *x);
void lores_assist(t_lores *x, void *b, long m, long a, char *s);
void *lores_new(double freq, double reso);

void ext_main(void *r)
{
	t_class *c;

	c = class_new("lores~",(method)lores_new, (method)dsp_free,
				  sizeof(t_lores), 0L, A_DEFFLOAT, A_DEFFLOAT, 0);
	class_addmethod(c, (method)lores_dsp, "dsp", A_CANT, 0);
	class_addmethod(c, (method)lores_dsp64, "dsp64", A_CANT, 0);
	class_addmethod(c, (method)lores_assist, "assist", A_CANT, 0);
	class_addmethod(c, (method)lores_clear, "clear", 0);
	class_addmethod(c, (method)lores_int, "int", A_LONG, 0);
	class_addmethod(c, (method)lores_float, "float", A_FLOAT, 0);
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	lores_class = c;

	return 0;
}

void lores_dsp(t_lores *x, t_signal **sp, short *count)
{
	x->l_2pidsr = (2. * PI) / sp[0]->s_sr;
	lores_calc(x);
	x->l_a1p = x->l_a1;		// store prev coefs
	x->l_a2p = x->l_a2;
	x->l_fcon = count[1];	// signal connected to the frequency inlet?
	x->l_rcon = count[2];	// signal connected to the resonance inlet?
	lores_clear(x);

	if (sp[0]->s_n >= 4) {
#if SMOOTHING_VERSION
		dsp_add(lores_perform_unroll_smooth, 6, sp[0]->s_vec, sp[3]->s_vec, x, sp[1]->s_vec, sp[2]->s_vec, (sp[0]->s_n/4));
#else
		dsp_add(lores_perform_unroll, 6, sp[0]->s_vec, sp[3]->s_vec, x, sp[1]->s_vec, sp[2]->s_vec, (sp[0]->s_n/4));
#endif
	}
	else
		dsp_add(lores_perform, 6, sp[0]->s_vec, sp[3]->s_vec, x, sp[1]->s_vec, sp[2]->s_vec, sp[0]->s_n);
}


void lores_dsp64(t_lores *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->l_2pidsr = (2.0 * PI) / samplerate;
	lores_calc(x);
	x->l_a1p = x->l_a1;		// store prev coefs
	x->l_a2p = x->l_a2;
	x->l_fcon = count[1];	// signal connected to the frequency inlet?
	x->l_rcon = count[2];	// signal connected to the resonance inlet?
	lores_clear(x);

	if (maxvectorsize >= 4) {
#if SMOOTHING_VERSION
		dsp_add64(dsp64, (t_object *)x, (t_perfroutine64)lores_perform_unroll_smooth64, 0, NULL);
#else
		dsp_add64(dsp64, (t_object *)x, (t_perfroutine64)lores_perform_unroll64, 0, NULL);
#endif
	}
	else
		dsp_add64(dsp64, (t_object *)x, (t_perfroutine64)lores_perform64, 0, NULL);
}


t_int *lores_perform(t_int *w)
{
	// assign from parameters
	t_float *in = (t_float *)(w[1]);
	t_float *out = (t_float *)(w[2]);
	t_lores *x = (t_lores *)(w[3]);
	t_float freq = x->l_fcon? *(t_float *)(w[4]) : x->l_freq;
	t_float resonance = x->l_rcon? *(t_float *)(w[5]) : x->l_r;
	int n = (int)(w[6]);
	float a1 = x->l_a1,a2 = x->l_a2, ym1 = x->l_ym1, ym2 = x->l_ym2;
	float val,scale,temp,resterm;

	if (x->l_obj.z_disabled)
		goto out;

	// constrain resonance value

	if (resonance >= 1.)
		resonance = 1. - 1E-20;
	else if (resonance < 0.)
		resonance = 0.;

	// do we need to recompute coefficients?

	if (freq != x->l_freq || resonance != x->l_r) {
		if (resonance != x->l_r)
			resterm = x->l_resterm = exp(resonance * 0.125) * .882497;
		else
			resterm = x->l_resterm;
		if (freq != x->l_freq)
			x->l_fqterm = cos(x->l_2pidsr * freq);
		x->l_a1 = a1 = -2. * resterm * x->l_fqterm;
		x->l_a2 = a2 = resterm * resterm;
		x->l_r = resonance;
		x->l_freq = freq;
	}

	scale = 1. + a1 + a2;

	// DSP loop

	while (n--) {
		val = *in++;
		temp = ym1;
		ym1 = scale * val - a1 * ym1 - a2 * ym2;
#ifdef DENORM_WANT_FIX
		if (IS_DENORM_NAN_FLOAT(ym1)) ym1 = temp = 0;
#endif
		ym2 = temp;
		*out++ = ym1;
	}
	x->l_ym1 = ym1;
	x->l_ym2 = ym2;
out:
	return (w+7);
}


void lores_perform64(t_lores *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double	*in = ins[0];
	t_double	*out = outs[0];
	t_double	freq = x->l_fcon ? *ins[1] : x->l_freq;
	t_double	resonance = x->l_rcon ? *ins[2] : x->l_r;
	double		a1 = x->l_a1;
	double		a2 = x->l_a2;
	double		ym1 = x->l_ym1;
	double		ym2 = x->l_ym2;
	double		val, scale, temp, resterm;

	// constrain resonance value
	if (resonance >= 1.0)
		resonance = 1.0 - 1E-20;
	else if (resonance < 0.0)
		resonance = 0.0;

	// do we need to recompute coefficients?
	if (freq != x->l_freq || resonance != x->l_r) {
		if (resonance != x->l_r)
			resterm = x->l_resterm = exp(resonance * 0.125) * 0.882497;
		else
			resterm = x->l_resterm;
		if (freq != x->l_freq)
			x->l_fqterm = cos(x->l_2pidsr * freq);
		x->l_a1 = a1 = -2. * resterm * x->l_fqterm;
		x->l_a2 = a2 = resterm * resterm;
		x->l_r = resonance;
		x->l_freq = freq;
	}

	scale = 1.0 + a1 + a2;

	while (sampleframes--) {
		val = *in++;
		temp = ym1;
		ym1 = scale * val - a1 * ym1 - a2 * ym2;
#ifdef DENORM_WANT_FIX
		if (IS_DENORM_NAN_DOUBLE(ym1))
			ym1 = temp = 0;
#endif
		ym2 = temp;
		*out++ = ym1;
	}
	x->l_ym1 = ym1;
	x->l_ym2 = ym2;
}


t_int *lores_perform_unroll(t_int *w)
{
	t_float *in = (t_float *)(w[1]);
	t_float *out = (t_float *)(w[2]);
	t_lores *x = (t_lores *)(w[3]);
	t_float freq = x->l_fcon? *(t_float *)(w[4]) : x->l_freq;
	t_float resonance = x->l_rcon? *(t_float *)(w[5]) : x->l_r;
	int n = (int)(w[6]); // n=VS/4+1
	float a1 = x->l_a1,a2 = x->l_a2;
	float yna = x->l_ym2, ynb = x->l_ym1;
	float val,scale,resterm;

	if (x->l_obj.z_disabled)
		goto out;

	// constrain resonance value
	if (resonance >= 1.)
		resonance = 1. - 1E-20;
	else if (resonance < 0.)
		resonance = 0.;

	// do we need to recompute coefficients?
	if (freq != x->l_freq || resonance != x->l_r) {
		if (resonance != x->l_r)
			resterm = x->l_resterm = exp(resonance * 0.125) * 0.882497;
		else
			resterm = x->l_resterm;
		if (freq != x->l_freq)
			x->l_fqterm = cos(x->l_2pidsr * freq);
		x->l_a1 = a1 = -2.0 * resterm * x->l_fqterm;
		x->l_a2 = a2 = resterm * resterm;
		x->l_r = resonance;
		x->l_freq = freq;
	}

	scale = 1.0 + a1 + a2;

	while (n--) { //n=VS/4
		*out++ = yna = scale * (val = *in++) - a1 * ynb - a2 * yna;
#ifdef DENORM_WANT_FIX
		if (IS_DENORM_NAN_FLOAT(yna))
			yna = ynb = *out = 0;
#endif
		*out++ = ynb = scale * (val = *in++) - a1 * yna - a2 * ynb;
#ifdef DENORM_WANT_FIX
		if (IS_DENORM_NAN_FLOAT(ynb))
			yna = ynb = *out = 0;
#endif
		*out++ = yna = scale * (val = *in++) - a1 * ynb - a2 * yna;
#ifdef DENORM_WANT_FIX
		if (IS_DENORM_NAN_FLOAT(yna))
			yna = ynb = *out = 0;
#endif
		*out++ = ynb = scale * (val = *in++) - a1 * yna - a2 * ynb;
#ifdef DENORM_WANT_FIX
		if (IS_DENORM_NAN_FLOAT(ynb))
			yna = ynb = *out = 0;
#endif
	}
	x->l_ym1 = ynb;
	x->l_ym2 = yna;
out:
	return (w+7);
}


void lores_perform_unroll64(t_lores *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double *in = ins[0];
	t_double *out = outs[0];
	t_double freq = x->l_fcon? *ins[1] : x->l_freq;
	t_double resonance = x->l_rcon? *ins[2] : x->l_r;
	int n = sampleframes / 4;
	double a1 = x->l_a1;
	double a2 = x->l_a2;
	double yna = x->l_ym2;
	double ynb = x->l_ym1;
	double val, scale, resterm;

	// constrain resonance value
	if (resonance >= 1.0)
		resonance = 1.0 - 1E-20;
	else if (resonance < 0.0)
		resonance = 0.0;

	// do we need to recompute coefficients?
	if (freq != x->l_freq || resonance != x->l_r) {
		if (resonance != x->l_r)
			resterm = x->l_resterm = exp(resonance * 0.125) * 0.882497;
		else
			resterm = x->l_resterm;
		if (freq != x->l_freq)
			x->l_fqterm = cos(x->l_2pidsr * freq);
		x->l_a1 = a1 = -2.0 * resterm * x->l_fqterm;
		x->l_a2 = a2 = resterm * resterm;
		x->l_r = resonance;
		x->l_freq = freq;
	}

	scale = 1.0 + a1 + a2;

	while (n--) {
		*out++ = yna = scale * (val = *in++) - a1 * ynb - a2 * yna;
#ifdef DENORM_WANT_FIX
		if (IS_DENORM_NAN_DOUBLE(yna))
			yna = ynb = *out = 0;
#endif
		*out++ = ynb = scale * (val = *in++) - a1 * yna - a2 * ynb;
#ifdef DENORM_WANT_FIX
		if (IS_DENORM_NAN_DOUBLE(ynb))
			yna = ynb = *out = 0;
#endif
		*out++ = yna = scale * (val = *in++) - a1 * ynb - a2 * yna;
#ifdef DENORM_WANT_FIX
		if (IS_DENORM_NAN_DOUBLE(yna))
			yna = ynb = *out = 0;
#endif
		*out++ = ynb = scale * (val = *in++) - a1 * yna - a2 * ynb;
#ifdef DENORM_WANT_FIX
		if (IS_DENORM_NAN_DOUBLE(ynb))
			yna = ynb = *out = 0;
#endif
	}
	x->l_ym1 = ynb;
	x->l_ym2 = yna;
}


t_int *lores_perform_unroll_smooth(t_int *w)
{
	// assign from parameters
	t_float *in = (t_float *)(w[1]);
	t_float *out = (t_float *)(w[2]);
	t_lores *x = (t_lores *)(w[3]);
	t_float freq = x->l_fcon? *(t_float *)(w[4]) : x->l_freq;
	t_float resonance = x->l_rcon? *(t_float *)(w[5]) : x->l_r;
	int n = (int)(w[6]); // vs/4
	float a1 = x->l_a1,a2 = x->l_a2;
	float yna = x->l_ym2, ynb = x->l_ym1;
	float val,scale, scalep, scalei,resterm;
	float mult, a1i, a2i;

	if (x->l_obj.z_disabled)
		goto out;

	// constrain resonance value

	if (resonance >= 1.)
		resonance = 1. - 1E-20;
	else if (resonance < 0.)
		resonance = 0.;

	// do we need to recompute coefficients?

	if (freq != x->l_freq || resonance != x->l_r) {
		if (resonance != x->l_r)
			resterm = x->l_resterm = exp(resonance * 0.125) * .882497;
		else
			resterm = x->l_resterm;
		if (freq != x->l_freq)
			x->l_fqterm = cos(x->l_2pidsr * freq);
		x->l_a1 = a1 = -2. * resterm * x->l_fqterm;
		x->l_a2 = a2 = resterm * resterm;
		x->l_r = resonance;
		x->l_freq = freq;
	}

	a1 = x->l_a1p;
	a2 = x->l_a2p;

	scalep = 1. + a1 + a2;
	scale = 1. + x->l_a1 + x->l_a2;

	mult = 0.25/n; // 0.25 because n = vs/4
	a1i = (x->l_a1-a1) * mult;
	a2i = (x->l_a2-a2) * mult;
	scalei = (scale-scalep) * mult;

	while (n--) { //n=VS/4
		scale+=scalei; a1+=a1i; a2+=a2i;
		*out++ = yna = scale * (val = *in++) - a1 * ynb - a2 * yna;
#ifdef DENORM_WANT_FIX
		if (IS_DENORM_NAN_FLOAT(yna)) yna = ynb = *out = 0;
#endif
		scale+=scalei; a1+=a1i; a2+=a2i;
		*out++ = ynb = scale * (val = *in++) - a1 * yna - a2 * ynb;
#ifdef DENORM_WANT_FIX
		if (IS_DENORM_NAN_FLOAT(ynb)) yna = ynb = *out = 0;
#endif
		scale+=scalei; a1+=a1i; a2+=a2i;
		*out++ = yna = scale * (val = *in++) - a1 * ynb - a2 * yna;
#ifdef DENORM_WANT_FIX
		if (IS_DENORM_NAN_FLOAT(yna)) yna = ynb = *out = 0;
#endif
		scale+=scalei; a1+=a1i; a2+=a2i;
		*out++ = ynb = scale * (val = *in++) - a1 * yna - a2 * ynb;
#ifdef DENORM_WANT_FIX
		if (IS_DENORM_NAN_FLOAT(ynb)) yna = ynb = *out = 0;
#endif
	}
	x->l_ym1 = ynb;
	x->l_ym2 = yna;

	// store prev coefs
	x->l_a1p = x->l_a1;
	x->l_a2p = x->l_a2;

out:
	return (w+7);
}


void lores_int(t_lores *x, long n)
{
	lores_float(x,(double)n);
}

void lores_float(t_lores *x, double f)
{
	long in = proxy_getinlet((t_object *)x);

	if (in == 1) {
		x->l_freq = f;
		lores_calc(x);
	} else if (in == 2) {
		x->l_r = f >= 1.0 ? 1 - 1E-20 : f;
		lores_calc(x);
	}
}

void lores_clear(t_lores *x)
{
	x->l_ym1 = x->l_ym2 = 0.;		// clear sample memory to recover from blowup
}

void lores_calc(t_lores *x)
{
	double resterm;

	// calculate filter coefficients from frequency and resonance

	resterm = exp(x->l_r * 0.125) * 0.882497;
	x->l_fqterm = cos(x->l_2pidsr * x->l_freq);
	x->l_a1 = -2. * resterm * x->l_fqterm;
	x->l_a2 = resterm * resterm;
	x->l_resterm = resterm;
}

void lores_assist(t_lores *x, void *b, long m, long a, char *s)
{
	if (m == 2)
		sprintf(s,"(signal) Output");
	else {
		switch (a) {
		case 0: sprintf(s,"(signal) Input"); break;
		case 1: sprintf(s,"(signal/float) Cutoff Frequency"); break;
		case 2: sprintf(s,"(signal/float) Resonance Control (0-1)"); break;
		}
	}
}

void *lores_new(double val, double reso)
{
	t_lores *x = object_alloc(lores_class);
	dsp_setup((t_pxobject *)x,3);

	// three signal inlets

	x->l_freq = val;
	x->l_r = reso >= 1.0 ? 1. - 1E-20 : reso;
	x->l_2pidsr = (2. * PI) / sys_getsr();
	lores_calc(x);

	x->l_a1p = x->l_a1;
	x->l_a2p = x->l_a2;

	// one signal outlet

	outlet_new((t_object *)x, "signal");

	return (x);
}
