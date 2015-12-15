/**
 @file
 index~ - SDK example of an object which accesses an MSP buffer~

 @ingroup	examples
 */

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h" // contains CLAMP macro
#include "z_dsp.h"
#include "ext_buffer.h"


typedef struct _index {
	t_pxobject l_obj;
	t_buffer_ref *l_buffer_reference;
	long l_chan;
} t_index;


void index_perform64(t_index *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void index_dsp64(t_index *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void index_set(t_index *x, t_symbol *s);
void *index_new(t_symbol *s, long chan);
void index_free(t_index *x);
t_max_err index_notify(t_index *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void index_in1(t_index *x, long n);
void index_assist(t_index *x, void *b, long m, long a, char *s);
void index_dblclick(t_index *x);


static t_class *index_class;


void ext_main(void *r)
{
	t_class *c = class_new("index~", (method)index_new, (method)index_free, sizeof(t_index), 0L, A_SYM, A_DEFLONG, 0);

	class_addmethod(c, (method)index_dsp64, "dsp64", A_CANT, 0);
	class_addmethod(c, (method)index_set, "set", A_SYM, 0);
	class_addmethod(c, (method)index_in1, "in1", A_LONG, 0);
	class_addmethod(c, (method)index_assist, "assist", A_CANT, 0);
	class_addmethod(c, (method)index_dblclick, "dblclick", A_CANT, 0);
	class_addmethod(c, (method)index_notify, "notify", A_CANT, 0);
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	index_class = c;
}


void index_perform64(t_index *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double	*in = ins[0];
	t_double	*out = outs[0];
	int			n = sampleframes;
	t_float		*tab;
	double		temp;
	double		f;
	long		index, chan, frames, nc;
	t_buffer_obj	*buffer = buffer_ref_getobject(x->l_buffer_reference);

	tab = buffer_locksamples(buffer);
	if (!tab)
		goto zero;

	frames = buffer_getframecount(buffer);
	nc = buffer_getchannelcount(buffer);
	chan = MIN(x->l_chan, nc);
	while (n--) {
		temp = *in++;
		f = temp + 0.5;
		index = f;
		if (index < 0)
			index = 0;
		else if (index >= frames)
			index = frames - 1;
		if (nc > 1)
			index = index * nc + chan;
		*out++ = tab[index];
	}
	buffer_unlocksamples(buffer);
	return;
zero:
	while (n--)
		*out++ = 0.0;
}

void index_set(t_index *x, t_symbol *s)
{
	if (!x->l_buffer_reference)
		x->l_buffer_reference = buffer_ref_new((t_object *)x, s);
	else
		buffer_ref_set(x->l_buffer_reference, s);
}

void index_in1(t_index *x, long n)
{
	if (n)
		x->l_chan = MAX(n, 1) - 1;
	else
		x->l_chan = 0;
}


void index_dsp64(t_index *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	dsp_add64(dsp64, (t_object *)x, (t_perfroutine64)index_perform64, 0, NULL);
}


// this lets us double-click on index~ to open up the buffer~ it references
void index_dblclick(t_index *x)
{
	buffer_view(buffer_ref_getobject(x->l_buffer_reference));
}

void index_assist(t_index *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_OUTLET)
		sprintf(s,"(signal) Sample Value at Index");
	else {
		switch (a) {
		case 0:	sprintf(s,"(signal) Sample Index");	break;
		case 1:	sprintf(s,"Audio Channel In buffer~");	break;
		}
	}
}

void *index_new(t_symbol *s, long chan)
{
	t_index *x = object_alloc(index_class);
	dsp_setup((t_pxobject *)x, 1);
	intin((t_object *)x,1);
	outlet_new((t_object *)x, "signal");
	index_set(x, s);
	index_in1(x,chan);
	return (x);
}


void index_free(t_index *x)
{
	dsp_free((t_pxobject *)x);
	object_free(x->l_buffer_reference);
}


t_max_err index_notify(t_index *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	return buffer_ref_notify(x->l_buffer_reference, s, msg, sender, data);
}
