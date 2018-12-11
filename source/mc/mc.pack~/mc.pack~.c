// mc.pack~ combines inputs into a multichannel signal


#include "ext.h"
#include "ext_obex.h"
#include "commonsyms.h"
#include "z_dsp.h"


typedef struct _mcpack {
	t_pxobject m_obj;
	long m_size;                // number of inlets
	double *m_values;			// non-signal inputs
    long m_fixedoutputchans;    // if 0, auto-adapts, otherwise output channel count is fixed
    long m_inputcount;          // count of input channels
	long *m_siginchans;			// whether to use the values[] or the incoming signal
	long *m_chaninlets;			// for elements of ins[] array, which inlet do they belong to (used only in combine mode)
	long *m_inletstarts;		// what is the index of the first signal of each inlet
	t_bool m_muteall;			// could be attribute?
	long m_combinemode;			// limit to one input per inlet (false) or not (true)
} t_mcpack;


void *mcpack_new(t_symbol *name, long argc, t_atom *argv);
void mcpack_free(t_mcpack *x);
void mcpack_assist(t_mcpack *x, void *b, long m, long a, char *s);
void mcpack_setconstant(double *dest, double val, long count);
void mcpack_accum(double *src, double *dest, long count);
void mcpack_perform64(t_mcpack *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void mcpack_dsp64(t_mcpack *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
long mcpack_multichanneloutputs(t_mcpack *x, int index);
long mcpack_inputchanged(t_mcpack *x, long index, long chans);
void mcpack_countchannels(t_mcpack *x);
void mcpack_int(t_mcpack *x, long n);
void mcpack_float(t_mcpack *x, double f);
void mcpack_list(t_mcpack *x, t_symbol *s, long argc, t_atom *argv);
void mcpack_muteall(t_mcpack *x, long way);
void mcpack_helpname(t_mcpack *x, char *str);
void mcpack_initclass(t_class *c);


static t_class *s_mcpack_class, *s_mccombine_class;

static t_symbol *ps_getnuminputchannels, *ps_mc_combine;

void ext_main(void *r)
{
	t_class *c;
 
	common_symbols_init();
	ps_getnuminputchannels = gensym("getnuminputchannels");
	ps_mc_combine = gensym("mc.combine~");
	
	c = class_new("mc.pack~", (method)mcpack_new, (method)mcpack_free, sizeof(t_mcpack), 0L, A_GIMME, 0);
	mcpack_initclass(c);
	s_mcpack_class = c;
	class_register(CLASS_BOX, s_mcpack_class);

	c = class_new("mc.combine~", (method)mcpack_new, (method)mcpack_free, sizeof(t_mcpack), 0L, A_GIMME, 0);
	mcpack_initclass(c);
	s_mccombine_class = c;
	class_register(CLASS_BOX, s_mcpack_class);
}

void mcpack_initclass(t_class *c)
{
	class_addmethod(c, (method)mcpack_dsp64, "dsp64", A_CANT, 0);
	class_addmethod(c, (method)mcpack_assist, "assist",	A_CANT, 0);
    class_addmethod(c, (method)mcpack_inputchanged, "inputchanged", A_CANT, 0);
	class_addmethod(c, (method)mcpack_multichanneloutputs, "multichanneloutputs", A_CANT, 0);
	class_addmethod(c, (method)mcpack_int, "int", A_LONG, 0);
	class_addmethod(c, (method)mcpack_float, "float", A_FLOAT, 0);
	class_addmethod(c, (method)mcpack_list, "list", A_GIMME, 0);
	class_addmethod(c, (method)mcpack_muteall, "mute", A_LONG, 0);
	class_addmethod(c, (method)mcpack_helpname, "helpname", A_CANT, 0);
	   
    CLASS_ATTR_LONG(c, "chans", 0, t_mcpack, m_fixedoutputchans);
    CLASS_ATTR_LABEL(c, "chans", 0, "Output Channels");
    CLASS_ATTR_FILTER_CLIP(c, "chans", 0, MC_MAX_CHANS);
    CLASS_ATTR_BASIC(c, "chans", 0);
	
	class_dspinit(c);
}

long mcpack_multichanneloutputs(t_mcpack *x, int index)
{
    return x->m_fixedoutputchans? x->m_fixedoutputchans : x->m_inputcount;
}

long mcpack_inputchanged(t_mcpack *x, long index, long chans)
{
    if (x->m_fixedoutputchans)  // not sensitive to input channel count changes
        return false;
    
    if (chans != x->m_siginchans[index]) {
        x->m_siginchans[index] = chans;
        mcpack_countchannels(x);
        return true;
    }
    return false;
}

void mcpack_countchannels(t_mcpack *x)
{
    long i, inlet, it, sum;
    long total = 0;
	
	if (x->m_combinemode) {
		for (i = 0; i < x->m_size; i++) {
			total += x->m_siginchans[i]? x->m_siginchans[i] : 1;
		}
	} else {	// note: inletstarts is only used when combinemode is false
		long temp = 0;
		total = x->m_size;
		x->m_inletstarts[0] = 0;
		for (i = 1; i < total; i++) {
			temp += x->m_siginchans[i - 1]? x->m_siginchans[i - 1] : 1;
			x->m_inletstarts[i] = temp;
		}
	}
	
	if (total != x->m_inputcount) {
		x->m_inputcount = total;
	}
	
	// note if you for some reason make it possible to switch between pack and combine mode dynamically
	// you need to do this properly; it's disabled for pack because we aren't counting up
	// the input channels and thus chaninlets was too small (see #12232)
	
	if (x->m_combinemode) {
		sysmem_freeptr(x->m_chaninlets);
		x->m_chaninlets = (long *)sysmem_newptr(total * sizeof(long));
		for (inlet = 0, it = 0; inlet < x->m_size; inlet++) {
			sum = x->m_siginchans[inlet]? x->m_siginchans[inlet] : 1;
			for (i = 0; i < sum; i++)
				x->m_chaninlets[it + i] = inlet;
			it += sum;
		}
	}
}

void mcpack_int(t_mcpack *x, long n)
{
	mcpack_float(x, (double)n);
}

void mcpack_float(t_mcpack *x, double f)
{
	x->m_values[proxy_getinlet((t_object *)x)] = f;
}

void mcpack_list(t_mcpack *x, t_symbol *s, long argc, t_atom *argv)
{
	long i, start = proxy_getinlet((t_object *)x);
	long count = (argc < x->m_size - start) ? argc : x->m_size - start;

	for (i = 0; i < count; i++)
		x->m_values[i+start] = atom_getfloat(argv + i);
}

void mcpack_muteall(t_mcpack *x, long way)
{
	x->m_muteall = way ? true : false;
}

void mcpack_helpname(t_mcpack *x, char *str)
{
	if (x->m_combinemode)
		strcpy(str, "mc.combine~");
	else
		strcpy(str, "mc.pack~");
}

void *mcpack_new(t_symbol *name, long argc, t_atom *argv)
{
    long offset;
    t_mcpack *x;
	
	if (name == ps_mc_combine)
		x = (t_mcpack *)object_alloc(s_mccombine_class);
	else
		x = (t_mcpack *)object_alloc(s_mcpack_class);
	
	x->m_size = 2;
	x->m_combinemode = name == ps_mc_combine;
	offset = attr_args_offset(argc, argv);
	
	if (offset >= 1) {
		long size = (long)atom_getlong(argv);
		size = CLAMP(size, 2, MC_MAX_CHANS);
		x->m_size = size;
	}
    x->m_fixedoutputchans = 0;
    x->m_inputcount = x->m_size;    // default
	x->m_values = (double *)sysmem_newptrclear(x->m_size * sizeof(double));
	x->m_siginchans = (long *)sysmem_newptrclear(x->m_size * sizeof(long));
	x->m_chaninlets = (long *)sysmem_newptrclear(x->m_size * sizeof(long));
	x->m_inletstarts = (long *)sysmem_newptrclear(x->m_size * sizeof(long));
	x->m_muteall = false;
	dsp_setup((t_pxobject *)x, x->m_size);
	x->m_obj.z_misc = Z_NO_INPLACE | Z_MC_INLETS;	// probably needed since you're using sysmem_copyptr
	outlet_new((t_object *)x, "multichannelsignal");	// one multichannel output
	attr_args_process(x, argc, argv);
	return x;
}


void mcpack_free(t_mcpack *x)
{
	dsp_free((t_pxobject *)x);
	sysmem_freeptr(x->m_values);
	sysmem_freeptr(x->m_siginchans);
}


void mcpack_assist(t_mcpack *x, void *b, long m, long a, char *s)
{
	if (m == 1) {
		strcpy(s, "(signal, float) Input");
	} 
	else if (m == 2) {
		strcpy(s, "(multi-channel signal) Output");
	}
}

void mcpack_setconstant(double *dest, double val, long count)
{
	while (count--)
		*dest++ = val;
}

void mcpack_perform64(t_mcpack *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	long i;
	long inlet;
	
	if (x->m_combinemode) {
		for (i = 0; i < numins; i++) {
			
			if (i >= numouts)	// you're done
				return;
			if (x->m_muteall)
				set_zero64(outs[i], sampleframes);
			else {
				inlet = x->m_chaninlets[i];
				if (x->m_siginchans[inlet])
					sysmem_copyptr(ins[i], outs[i], sizeof(double) * sampleframes);
				else
					mcpack_setconstant(outs[i], x->m_values[inlet], sampleframes);
			}
		}
	} else {
		for (i = 0; i < numouts; i++) {
            if (i < x->m_size && !x->m_muteall) {
                if (x->m_siginchans[i])
                    sysmem_copyptr(ins[x->m_inletstarts[i]], outs[i], sizeof(double) * sampleframes);
                else
                    mcpack_setconstant(outs[i], x->m_values[i], sampleframes);
            } else
                set_zero64(outs[i], sampleframes);
        }
	}
}


void mcpack_dsp64(t_mcpack *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	int i;
	
    for (i = 0; i < x->m_size; i++) {
		if (count[i])
			x->m_siginchans[i] = (long)object_method(dsp64, ps_getnuminputchannels, x, i);
		else
			x->m_siginchans[i] = 0;
	}
	mcpack_countchannels(x);
	dsp_add64(dsp64, (t_object*)x, (t_perfroutine64)mcpack_perform64, 0, NULL);
}
