// mc.rotate~ -- example of MC auto-adapting


#include "ext.h"
#include "ext_obex.h"
#include "commonsyms.h"
#include "z_dsp.h"


typedef struct _mcrotate {
	t_pxobject m_obj;
	long m_size;	// the count of input channels
} t_mcrotate;


void *mcrotate_new(long size);
void mcrotate_free(t_mcrotate *x);
void mcrotate_assist(t_mcrotate *x, void *b, long m, long a, char *s);
void mcrotate_perform64(t_mcrotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void mcrotate_dsp64(t_mcrotate *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
long mcrotate_inputchanged(t_mcrotate *x, long index, long count);
long mcrotate_multichanneloutputs(t_mcrotate *x, long index);

static t_class *s_mcrotate_class;

void ext_main(void *r)
{
	t_class *c = class_new("mc.rotate~", (method)mcrotate_new, (method)mcrotate_free, sizeof(t_mcrotate), 0L, A_DEFLONG, 0);

	class_addmethod(c, (method)mcrotate_dsp64,			"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)mcrotate_assist,		"assist",	A_CANT, 0);
	class_addmethod(c, (method)mcrotate_multichanneloutputs, "multichanneloutputs", A_CANT, 0);
    class_addmethod(c, (method)mcrotate_inputchanged, "inputchanged", A_CANT, 0);
	
	class_dspinit(c);
    
	s_mcrotate_class = c;
	class_register(CLASS_BOX, s_mcrotate_class);
}

long mcrotate_multichanneloutputs(t_mcrotate *x, long index)
{
	return x->m_size;
}

long mcrotate_inputchanged(t_mcrotate *x, long index, long count)
{
	if (count != x->m_size) {
		x->m_size = count;
		return true;
	} else
		return false;
}

void *mcrotate_new(long size)
{
	t_mcrotate *x = (t_mcrotate *)object_alloc(s_mcrotate_class);
	
	if (size == 0)
		size = 2;
	
	x->m_size = CLAMP(size, 1, 512);
	
	dsp_setup((t_pxobject *)x, 1);
	x->m_obj.z_misc |= Z_NO_INPLACE | Z_MC_INLETS;
	outlet_new((t_object *)x, "multichannelsignal");
	return x;
}

void mcrotate_free(t_mcrotate *x)
{
	dsp_free((t_pxobject *)x);
}

void mcrotate_assist(t_mcrotate *x, void *b, long m, long a, char *s)
{
	if (m == 1)
		strcpy(s, "(multi-channel signal) Input");
	else if (m == 2)
		sprintf(s, "(multi-channel signal) Input, Rotated");
}

void mcrotate_perform64(t_mcrotate *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	long ch;
	double *in, *out;
	
	for (ch = 0; ch < numins; ch++) {		// for each input channel
		in = ins[ch];
		if (ch == numins - 1)
			out = outs[0];
		else
			out = outs[ch + 1];
		sysmem_copyptr(in, out, sizeof(double) * sampleframes);
	}
}

void mcrotate_dsp64(t_mcrotate *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	dsp_add64(dsp64, (t_object *)x, (t_perfroutine64)mcrotate_perform64, 0, NULL);
}

