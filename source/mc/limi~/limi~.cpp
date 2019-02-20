#include "ext.h"
#include "ext_common.h"
#include "z_dsp.h"

#include <memory>
#include "../limi~/c74_lib_dcblocker.h"
#include "../limi~/c74_min_operator_vector.h"
#include "../limi~/c74_min_dataspace.h"
#include "../limi~/c74_lib_limiter.h"

#ifdef MC_VERSION
#define LIMI_NAME "mcs.limi~"
#else
#define LIMI_NAME "limi~"
#endif


typedef struct _limi {
	t_pxobject				x_obj;
	c74::min::lib::limiter	*x_limiter;
	int						x_channelcount;
	int						x_buffersize;
	char					x_bypass;
	char					x_dcblock;
	char					x_mode;
	long 					x_lookahead;
	double					x_preamp;
	double					x_postamp;
	double					x_threshold;
	double					x_release;
} t_limi;


void *limi_new(t_symbol *s, long argc, t_atom *argv);
void limi_free(t_limi *x);
void limi_assist(t_limi *x, void *b, long m, long a, char *s);
long limi_multichanneloutputs(t_limi *x, int index);
long limi_inputchanged(t_limi *x, long index, long chans);
void limi_clear(t_limi *x);
t_max_err limi_setbypass(t_limi *x, void *attr, long argc, t_atom *argv);
t_max_err limi_setdcblock(t_limi *x, void *attr, long argc, t_atom *argv);
t_max_err limi_setmode(t_limi *x, void *attr, long argc, t_atom *argv);
t_max_err limi_setlookahead(t_limi *x, void *attr, long argc, t_atom *argv);
t_max_err limi_setpreamp(t_limi *x, void *attr, long argc, t_atom *argv);
t_max_err limi_setpostamp(t_limi *x, void *attr, long argc, t_atom *argv);
t_max_err limi_setthreshold(t_limi *x, void *attr, long argc, t_atom *argv);
t_max_err limi_setrelease(t_limi *x, void *attr, long argc, t_atom *argv);
void limi_dsp64(t_limi *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);


static t_class *s_limi_class;


void ext_main(void *r)
{
	t_class *c = class_new(LIMI_NAME, (method)limi_new, (method)limi_free, sizeof(t_limi), NULL, A_GIMME, 0);
		
	class_addmethod(c, (method)limi_dsp64, "dsp64", A_CANT, 0);
	class_addmethod(c, (method)limi_assist,"assist", A_CANT, 0);
#ifdef MC_VERSION
	class_addmethod(c, (method)limi_multichanneloutputs, "multichanneloutputs", A_CANT, 0);
	class_addmethod(c, (method)limi_inputchanged, "inputchanged", A_CANT, 0);
#endif
	class_addmethod(c, (method)limi_clear,"clear",0);

	CLASS_ATTR_CHAR(c,		"bypass", 0, t_limi, x_bypass);
	CLASS_ATTR_LABEL(c,		"bypass", 0, "Bypass");
	CLASS_ATTR_ACCESSORS(c,	"bypass", NULL, limi_setbypass);
	CLASS_ATTR_STYLE(c, 	"bypass", 0, "onoff");

	CLASS_ATTR_CHAR(c,		"dcblock", 0, t_limi, x_dcblock);
	CLASS_ATTR_LABEL(c,		"dcblock", 0, "Block DC offsets");
	CLASS_ATTR_ACCESSORS(c,	"dcblock", NULL, limi_setdcblock);
	CLASS_ATTR_STYLE(c, 	"dcblock", 0, "onoff");

	CLASS_ATTR_CHAR(c,		"mode",	0, t_limi, x_mode);
	CLASS_ATTR_LABEL(c,		"mode",	0, "Response Mode");
	CLASS_ATTR_ACCESSORS(c,	"mode",	NULL, limi_setmode);
	CLASS_ATTR_ENUMINDEX2(c, "mode",	0, "Linear", "Exponential");

	CLASS_ATTR_LONG(c,		"lookahead", 0, t_limi, x_lookahead);
	CLASS_ATTR_LABEL(c,		"lookahead", 0, "Lookahead");
	CLASS_ATTR_ACCESSORS(c,	"lookahead", NULL, limi_setlookahead);

	CLASS_ATTR_DOUBLE(c,	"preamp", 0, t_limi, x_preamp);
	CLASS_ATTR_LABEL(c,		"preamp", 0, "Preamp Gain");
	CLASS_ATTR_ACCESSORS(c,	"preamp", NULL, limi_setpreamp);
	
	CLASS_ATTR_DOUBLE(c,	"postamp", 0, t_limi, x_postamp);
	CLASS_ATTR_LABEL(c,		"postamp", 0, "Postamp Gain");
	CLASS_ATTR_ACCESSORS(c,	"postamp", NULL, limi_setpostamp);
	
	CLASS_ATTR_DOUBLE(c,	"threshold", 0, t_limi, x_threshold);
	CLASS_ATTR_LABEL(c,		"threshold", 0, "Threshold Level");
	CLASS_ATTR_ACCESSORS(c,	"threshold", NULL, limi_setthreshold);
	
	CLASS_ATTR_DOUBLE(c,	"release", 0, t_limi, x_release);
	CLASS_ATTR_LABEL(c,		"release", 0, "Release Time");
	CLASS_ATTR_ACCESSORS(c,	"release", NULL, limi_setrelease);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	s_limi_class = c;
}


void *limi_new(t_symbol *s, long argc, t_atom *argv)
{
	t_limi *x = (t_limi *)object_alloc(s_limi_class);
	long offset = attr_args_offset(argc, argv);

	x->x_buffersize = 512;
	x->x_channelcount = 1;
	if (offset) {
		x->x_channelcount = CLAMP(atom_getlong(argv), 1, MC_MAX_CHANS);
		if (offset > 1)
			x->x_buffersize = CLAMP(atom_getlong(argv+1), 100, 96000);
	}
	
#ifdef MC_VERSION
	dsp_setup((t_pxobject *)x, 1);
	outlet_new((t_object *)x, "multichannelsignal");
	x->x_obj.z_misc |= Z_NO_INPLACE | Z_MC_INLETS;
#else
    dsp_setup((t_pxobject *)x, x->x_channelcount);
    for (int i=0; i < x->x_channelcount; i++)
        outlet_new((t_object *)x, "signal");
    x->x_obj.z_misc |= Z_NO_INPLACE;
#endif
	
	x->x_limiter = new c74::min::lib::limiter(x->x_channelcount, x->x_buffersize, sys_getsr());

	x->x_bypass = 0;
	x->x_dcblock = 1;
	x->x_mode = 1;
	x->x_lookahead = 100;
	x->x_preamp = 0.0;
	x->x_postamp = 0.0;
	x->x_threshold = 0.0;
	x->x_release = 1000.0;
	attr_args_process(x, argc, argv);
	return x;
}


void limi_free(t_limi *x)
{
	dsp_free((t_pxobject *)x);
	delete x->x_limiter;
}


void limi_assist(t_limi *x, void *b, long m, long a, char *s)
{
#ifdef MC_VERSION
	if (m == ASSIST_INLET)
		printf(s,"(multi-channel signal) Input");
	else
		sprintf(s,"(multi-channel signal) Output");
#else
    if (m == ASSIST_INLET)
        printf(s,"(signal) Input");
    else
        sprintf(s,"(signal) Output");
#endif
}


long limi_multichanneloutputs(t_limi *x, int index)
{
	return x->x_channelcount;
}


long limi_inputchanged(t_limi *x, long index, long chans)
{
	if (chans != x->x_channelcount) {
		x->x_channelcount = chans;
		
		delete x->x_limiter;
		x->x_limiter = new c74::min::lib::limiter(x->x_channelcount, x->x_buffersize, sys_getsr());
	
		x->x_limiter->bypass(x->x_bypass);
		x->x_limiter->dcblock(x->x_dcblock);
		x->x_limiter->mode(static_cast<c74::min::lib::limiter::response_mode>(x->x_mode));
		x->x_limiter->lookahead(x->x_lookahead);
		x->x_limiter->preamp(x->x_preamp);
		x->x_limiter->postamp(x->x_postamp);
		x->x_limiter->threshold(x->x_threshold);
		x->x_limiter->release(x->x_release);
		return true;
	}
	return false;
}


void limi_clear(t_limi *x)
{
	x->x_limiter->clear();
}


t_max_err limi_setbypass(t_limi *x, void *attr, long argc, t_atom *argv)
{
	x->x_bypass = atom_getlong(argv);
	x->x_limiter->bypass(x->x_bypass);
	return MAX_ERR_NONE;
}


t_max_err limi_setdcblock(t_limi *x, void *attr, long argc, t_atom *argv)
{
	x->x_dcblock = atom_getlong(argv);
	x->x_limiter->dcblock(x->x_dcblock);
	return MAX_ERR_NONE;
}


t_max_err limi_setmode(t_limi *x, void *attr, long argc, t_atom *argv)
{
	x->x_mode = atom_getlong(argv);
	x->x_limiter->mode( static_cast<c74::min::lib::limiter::response_mode>(x->x_mode) );
	return MAX_ERR_NONE;
}


t_max_err limi_setlookahead(t_limi *x, void *attr, long argc, t_atom *argv)
{
	x->x_lookahead = atom_getlong(argv);
	x->x_limiter->lookahead(x->x_lookahead);
	return MAX_ERR_NONE;
}


t_max_err limi_setpreamp(t_limi *x, void *attr, long argc, t_atom *argv)
{
	x->x_preamp = atom_getfloat(argv);
	x->x_limiter->preamp(x->x_preamp);
	return MAX_ERR_NONE;
}


t_max_err limi_setpostamp(t_limi *x, void *attr, long argc, t_atom *argv)
{
	x->x_postamp = atom_getfloat(argv);
	x->x_limiter->postamp(x->x_postamp);
	return MAX_ERR_NONE;
}


t_max_err limi_setthreshold(t_limi *x, void *attr, long argc, t_atom *argv)
{
	x->x_threshold = atom_getfloat(argv);
	x->x_limiter->threshold(x->x_threshold);
	return MAX_ERR_NONE;
}


t_max_err limi_setrelease(t_limi *x, void *attr, long argc, t_atom *argv)
{
	x->x_release = atom_getfloat(argv);
	x->x_limiter->release(x->x_release);
	return MAX_ERR_NONE;
}


void limi_perform64(t_limi *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	c74::min::audio_bundle input(ins, numins, sampleframes);
	c74::min::audio_bundle output(outs, numouts, sampleframes);

	(*x->x_limiter)(input, output);
}


void limi_dsp64(t_limi *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->x_limiter->reset(x->x_limiter->release(), x->x_limiter->mode(), samplerate);
	dsp_add64(dsp64, (t_object *)x, (t_perfroutine64)limi_perform64, 0, NULL);
}
