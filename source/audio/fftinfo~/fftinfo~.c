/**
 @file
 fftinfo~.c - communicate fft size and hop, etc... to the contents of a pfft~ subpatch

 revised August 2001
 updated 3/22/09 ajm: new API

 @ingroup	examples
*/

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "r_pfft.h"		// public pfft struct in r_pfft.h

typedef struct _fftinfo
{
	t_pxobject x_obj;
	t_pfftpub *x_pfft;	// pointer to owning fftpatcher struct

	long x_fftsize;		// size of input fft (in samples)
	long x_ffthop;		// hop size for window advance
	long x_n;			// vector size (half of fft size if fullspect = 0)
	int x_fullspect;	// if full spectra are used

	void *x_out[4];		// array of outlets

} t_fftinfo;

void fftinfo_bang(t_fftinfo *x);
void fftinfo_dsp(t_fftinfo *x, t_signal **sp, short *count);
void fftinfo_dsp64(t_fftinfo *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void fftinfo_assist(t_fftinfo *x, void *b, long m, long a, char *s);
void *fftinfo_new(t_symbol *s, short ac, t_atom *av);

t_symbol *ps_spfft;

void *fftinfo_class;

int fftinfo_warning;	// so it only posts a warning once to the Max window if not inside a pfft


void ext_main(void *r)
{
	t_class *c;

	c = class_new("fftinfo~", (method)fftinfo_new, (method)dsp_free, sizeof(t_fftinfo), 0L, A_GIMME, 0);
	class_addmethod(c, (method)fftinfo_assist, "assist", A_CANT, 0);
	class_addmethod(c, (method)fftinfo_dsp, "dsp", A_CANT, 0);
	class_addmethod(c, (method)fftinfo_dsp64, "dsp64", A_CANT, 0);
	class_addmethod(c, (method)fftinfo_bang, "bang", 0);

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	fftinfo_class = c;

	ps_spfft = gensym("__pfft~__");	// owning pfft~ is bound to this while patch is loaded
	fftinfo_warning = 1;

	return 0;
}

void fftinfo_bang(t_fftinfo *x)
{
	if (x->x_pfft) {
		// just output current values
		outlet_int(x->x_out[3], x->x_fullspect); // fullspect flag
		outlet_int(x->x_out[2], x->x_ffthop);
		outlet_int(x->x_out[1], x->x_n);
		outlet_int(x->x_out[0], x->x_fftsize);
	}
	else if (fftinfo_warning) {
		object_warn((t_object *)x, "fftinfo~ only functions inside a pfft~",0);
		fftinfo_warning = 0;
	}
}

void fftinfo_dsp(t_fftinfo *x, t_signal **sp, short *count)
{
	if (!x->x_pfft) {
		x->x_pfft = (t_pfftpub *)ps_spfft->s_thing;
	}
	if (x->x_pfft) {
		outlet_int(x->x_out[3], (x->x_fullspect = (x->x_pfft->x_fullspect)?1:0));
		outlet_int(x->x_out[2], (x->x_ffthop = x->x_pfft->x_ffthop));
		outlet_int(x->x_out[1], (x->x_n = sp[0]->s_n));
		outlet_int(x->x_out[0], (x->x_fftsize = x->x_pfft->x_fftsize));
	}
	else if (fftinfo_warning) {
		object_warn((t_object *)x, "fftinfo~ only functions inside a pfft~",0);
		fftinfo_warning = 0;
	}
}

void fftinfo_dsp64(t_fftinfo *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	if (!x->x_pfft) {
		x->x_pfft = (t_pfftpub *)ps_spfft->s_thing;
	}
	if (x->x_pfft) {
		x->x_fullspect = x->x_pfft->x_fullspect ? 1 : 0;
		x->x_ffthop = x->x_pfft->x_ffthop;
		x->x_n = maxvectorsize;
		x->x_fftsize = x->x_pfft->x_fftsize;

		outlet_int(x->x_out[3], x->x_fullspect);
		outlet_int(x->x_out[2], x->x_ffthop);
		outlet_int(x->x_out[1], x->x_n);
		outlet_int(x->x_out[0], x->x_fftsize);
	}
	else if (fftinfo_warning) {
		object_warn((t_object *)x, "fftinfo~ only functions inside a pfft~", 0);
		fftinfo_warning = 0;
	}
}


void fftinfo_assist(t_fftinfo *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s,"(signal) Dummy");
	else {
		switch (a) {
		case 0:	sprintf(s,"(int) FFT Frame Size");	break;
		case 1:	sprintf(s,"(int) Spectral Frame Size");	break;
		case 2:	sprintf(s,"(int) FFT Hop Size");	break;
		case 3:	sprintf(s,"(int) Full Spectrum Flag (0/1)");	break;
		}
	}
}

void *fftinfo_new(t_symbol *s, short ac, t_atom *av)
{
	t_fftinfo *x;

	x = object_alloc(fftinfo_class);
	dsp_setup((t_pxobject *)x,1);

	x->x_out[3] = intout(x); // fullspect flag
	x->x_out[2] = intout(x);
	x->x_out[1] = intout(x);
	x->x_out[0] = intout(x);

	x->x_fftsize = x->x_ffthop = x->x_fullspect = x->x_n = 0; // init to 0
	x->x_obj.z_misc = Z_PUT_FIRST;
	x->x_pfft = (t_pfftpub *)ps_spfft->s_thing;
	if (x->x_pfft) {
		// these are now correctly initialized in pfft~ when patch is laoded
		x->x_fftsize = x->x_pfft->x_fftsize;
		x->x_ffthop = x->x_pfft->x_ffthop;
		x->x_fullspect = (x->x_pfft->x_fullspect) ? 1 : 0;
		// get temp values for x_n until we turn on dsp and find the real ones
		if (x->x_fullspect)
			x->x_n = x->x_fftsize; // in "fullspect mode", frame size = fft size
		else
			x->x_n = x->x_fftsize/2; // in "regular mode", frame size = fft size / 2
	}

	return (x);
}



