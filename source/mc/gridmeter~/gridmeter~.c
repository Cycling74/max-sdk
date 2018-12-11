// gridmeter~ meters in little squares

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "jpatcher_api.h"		// jpatcher_api.h must come before z_dsp.h
#include "jgraphics.h"
#include "z_dsp.h"
#include <math.h>
#include "ext_boxstyle.h"

typedef struct  {
	t_pxjbox a_obj;
	long a_columns;
	long a_chans;			// how many inputs
	double *a_values;		// running totals
	double *a_rmsvalues;	// RMS values
	long a_count;			// number of samples of the total
	
	t_jrgba a_bgcolor;		// background
	t_jrgba a_emptycolor;	// no signal
	t_jrgba a_color;		// the thing with alpha
	
	long a_cellheight;
	long a_cellwidth;
	long a_dividersize;
	
	void *a_clock;
	double a_interval;
	double a_contrast;			// graphics scale factor
	char a_startclock;
} t_gridmeter;


void gridmeter_initclass();
void gridmeter_dsp64(t_gridmeter *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void gridmeter_perform64(t_gridmeter *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void gridmeter_paint(t_gridmeter *x, t_object *view);
void gridmeter_oksize(t_gridmeter *x, t_rect *newrect);

void gridmeter_tick(t_gridmeter *x);

void gridmeter_setattr_interval(t_gridmeter *x, t_object *attr, long ac, t_atom *av);
void gridmeter_assist(t_gridmeter *x, void *b, long m, long a, char *s);
void gridmeter_free(t_gridmeter *x);
void *gridmeter_new(t_symbol *s, long argc, t_atom *argv);

static t_class	*s_gridmeter_class;

static t_symbol *aps_color, *aps_bgcolor, *aps_elementcolor;


/*==========================================================================*/

void ext_main(void *r)
{
	t_class *c;
	
	common_symbols_init();
	c = class_new("gridmeter~",
				  (method)gridmeter_new,
				  (method)gridmeter_free,
				  sizeof(t_gridmeter),
				  (method)NULL,
				  A_GIMME,
				  0L);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY; /* | CLASS_FLAG_VISUALIZER; */
	jbox_initclass(c, 0);
	class_dspinitjbox(c);

	class_addmethod(c, (method)gridmeter_dsp64, "dsp64", A_CANT, 0);
	class_addmethod(c, (method)gridmeter_paint, "paint",	A_CANT, 0);
	class_addmethod(c, (method)gridmeter_oksize, "oksize", A_CANT, 0);
	
	class_addmethod(c, (method)gridmeter_assist, "assist",	A_CANT, 0);

	class_addmethod(c, (method)jbox_notify, "notify", A_CANT, 0);

	CLASS_STICKY_CATEGORY(c, 0, "Value");

	CLASS_ATTR_DOUBLE(c, "interval", 0, t_gridmeter, a_interval);
	CLASS_ATTR_ACCESSORS(c, "interval",NULL, gridmeter_setattr_interval);
	CLASS_ATTR_LABEL(c, "interval", 0, "Polling Interval");
	CLASS_ATTR_DEFAULT_SAVE(c, "interval", 0, "50");
	CLASS_ATTR_BASIC(c, "interval", 0);

	CLASS_STICKY_CATEGORY(c, 0, "Color");
		
	CLASS_ATTR_STYLE_RGBA_PREVIEW(c, "bgcolor", 0, t_gridmeter, a_bgcolor, "Background Color", "rect_fill");
	CLASS_ATTR_BASIC(c,	"bgcolor", 0);

	CLASS_ATTR_STYLE_RGBA_PREVIEW(c, "elementcolor", 0, t_gridmeter, a_emptycolor, "Empty Color", "rect_fill");
	CLASS_ATTR_BASIC(c,	"elementcolor", 0);
	
	CLASS_ATTR_STYLE_RGBA_PREVIEW(c, "color", 0, t_gridmeter, a_color, "Meter Color", "rect_fill");
	CLASS_ATTR_BASIC(c,	"color", 0);

	CLASS_STICKY_CATEGORY_CLEAR(c);
	
	CLASS_STICKY_CATEGORY(c, 0, "Appearance");
	
	CLASS_ATTR_LONG(c, "columns", 0, t_gridmeter, a_columns);
	CLASS_ATTR_LABEL(c, "columns", 0, "Max Columns");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "columns", 0, "8");
	CLASS_ATTR_BASIC(c,	"columns", 0);
	
	CLASS_ATTR_LONG(c, "cellwidth", 0, t_gridmeter, a_cellwidth);
	CLASS_ATTR_LABEL(c, "cellwidth", 0, "Meter Width");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "cellwidth", 0, "16");

	CLASS_ATTR_LONG(c, "cellheight", 0, t_gridmeter, a_cellheight);
	CLASS_ATTR_LABEL(c, "cellheight", 0, "Meter Height");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "cellheight", 0, "12");
	
	CLASS_ATTR_LONG(c, "dividersize", 0, t_gridmeter, a_dividersize);
	CLASS_ATTR_LABEL(c, "dividersize", 0, "Divider Size");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "dividersize", 0, "2");
	
	CLASS_ATTR_DOUBLE(c, "contrast", 0, t_gridmeter, a_contrast);
	CLASS_ATTR_LABEL(c, "contrast", 0, "Contrast");
	CLASS_ATTR_FILTER_CLIP(c, "contrast", 0.1, 0.9);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "contrast", 0, "0.5");

	CLASS_STICKY_CATEGORY_CLEAR(c);

	CLASS_ATTR_DEFAULT(c,"patching_rect",0, "0. 0. 74. 58.");

	s_gridmeter_class = c;
	class_register(CLASS_BOX, c);

	aps_color = gensym("color");
	aps_bgcolor = gensym("bgcolor");
	aps_elementcolor = gensym("elementcolor");
}

/*--------------------------------------------------------------------------*/

void gridmeter_multichannelsignal(t_gridmeter *x)
{
	t_atom rv;
	
	// send the signal method to yourself
	object_method_typed(x, _sym_signal, 0, NULL, &rv);
}

void gridmeter_initvalues(t_gridmeter *x)
{
	if (x->a_values)
		sysmem_freeptr(x->a_values);
	x->a_values = (double *)sysmem_newptrclear(sizeof(double) * x->a_chans);
	if (x->a_rmsvalues)
		sysmem_freeptr(x->a_rmsvalues);
	x->a_rmsvalues = (double *)sysmem_newptrclear(sizeof(double) * x->a_chans);
}

void gridmeter_dsp64(t_gridmeter *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->a_chans = (long)object_method(dsp64, gensym("getnuminputchannels"), x, 0);
		
	gridmeter_initvalues(x);

	dsp_add64(dsp64, (t_object *)x, (t_perfroutine64)gridmeter_perform64, 0, NULL);
	x->a_startclock = true;
}


void gridmeter_perform64(t_gridmeter *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	double *in;
	long ch, i;
	double *val;
	double samp, total;
	
	for (ch = 0; ch < numins; ch++) {
		in = ins[ch];
		val = x->a_values + ch;
		total = 0;
		for (i = 0; i < sampleframes; i++) {
			samp = in[i];
			if (samp < 0)
				samp = -samp;
			total += samp * samp;
		}
		*val += total;	// write into values array
	}
	x->a_count += sampleframes;

	if (x->a_startclock) {
		x->a_startclock = false;
		clock_delay(x->a_clock, 0);
	}
}

void gridmeter_paint(t_gridmeter *x, t_object *view)
{
	t_jgraphics *g;
	t_rect rect;
	t_rect cell;
	long c, r, index, visrows, totalcellheight;
	t_jrgba col;
	
	object_attr_getjrgba(x, aps_bgcolor, &x->a_bgcolor);
	object_attr_getjrgba(x, aps_elementcolor, &x->a_emptycolor);
	object_attr_getjrgba(x, aps_color, &x->a_color);

	g = (t_jgraphics *) patcherview_get_jgraphics(view);

	jbox_get_rect_for_view((t_object *)x, view, &rect);
	rect.x = rect.y = 0;
	
	if (x->a_bgcolor.alpha) {
		jgraphics_set_source_jrgba(g, &x->a_bgcolor);
		jgraphics_rectangle_fill_fast(g, 0, 0, rect.width, rect.height);
	}
	
	cell.width = x->a_cellwidth;
	cell.height = x->a_cellheight;
	totalcellheight = x->a_cellheight + x->a_dividersize;
	visrows = (rect.height / totalcellheight) + 1;
	
	jgraphics_clip(g, 0, 0, rect.width, rect.height);
	for (r = 0; r < visrows; r++) {
		for (c = 0; c < x->a_columns; c++) {
			index = r * x->a_columns + c;
			cell.x = c * x->a_cellwidth + (c + 1) * x->a_dividersize;
			cell.y = r * x->a_cellheight + (r + 1) * x->a_dividersize;
			if (index < x->a_chans) {
				t_jrgba blk;
				double rms, db;
				double scale = x->a_contrast;
				
				blk.red = 0;
				blk.green = 0;
				blk.blue = 0;
				
				rms = CLAMP(x->a_rmsvalues[index], 0.01, 1);
				db = log10(rms) * 0.5;
				
				blk.alpha = -db * scale;
				if (blk.alpha < 0)
					blk.alpha = 0;
				else if (blk.alpha > scale)
					blk.alpha = scale;
				
				col = jgraphics_jrgba_overlay(&x->a_color, &blk);
				jgraphics_set_source_jrgba(g, &col);
			} else
				jgraphics_set_source_jrgba(g, &x->a_emptycolor);

			jgraphics_rectangle_fill_fast(g, cell.x, cell.y, cell.width, cell.height);
		}
	}
}

void gridmeter_oksize(t_gridmeter *x, t_rect *newrect)
{
	long totalcellwidth = x->a_cellwidth + x->a_dividersize;
	long totalcellheight = x->a_cellheight + x->a_dividersize;
	long columns, rows;
	
	columns = (newrect->width - x->a_dividersize) / totalcellwidth;
	rows = (newrect->height - x->a_dividersize) / totalcellheight;
	
	if (columns < 1)
		columns = 1;
	else if (columns > x->a_columns)
		columns = x->a_columns;
	if (rows < 1)
		rows = 1;
	
	newrect->width = columns * totalcellwidth + x->a_dividersize;
	newrect->height = rows * totalcellheight + x->a_dividersize;
}

void gridmeter_setattr_interval(t_gridmeter *x, t_object *attr, long ac, t_atom *av)
{
	double n = atom_getfloat(av);
	x->a_interval = CLAMP(n, 0, 500);
}

void gridmeter_assist(t_gridmeter *x, void *b, long m, long a, char *s)
{
	if (m==1) {
		switch (a) {
		case 0: sprintf(s,"(signal) Input"); break;
		}
	}
}

void gridmeter_tick(t_gridmeter *x)
{
	long count = x->a_count;
	long ch;
	double val;
	
	for (ch = 0; ch < x->a_chans; ch++) {
		val = x->a_values[ch];
		x->a_values[ch] = 0;
		x->a_rmsvalues[ch] = sqrt(val / (double)count);
	}
	x->a_count = 0;
	clock_delay(x->a_clock, x->a_interval);
	jbox_redraw((t_jbox *)x);
}

void gridmeter_free(t_gridmeter *x)
{
	dsp_freejbox((t_pxjbox *)x);
	object_free((t_object *)x->a_clock);
	jbox_free((t_jbox *)x);
	if (x->a_values)
		sysmem_freeptr(x->a_values);
	if (x->a_rmsvalues)
		sysmem_freeptr(x->a_rmsvalues);
}

/*--------------------------------------------------------------------------*/

void *gridmeter_new(t_symbol *s, long argc, t_atom *argv)
{
	t_gridmeter *x;
	long boxflags;
	t_dictionary *d = NULL;

	if (!(d = object_dictionaryarg(argc, argv)))
		return NULL;

	x = (t_gridmeter *)object_alloc(s_gridmeter_class);

	boxflags = 0
			   | JBOX_DRAWFIRSTIN
			   | JBOX_NODRAWBOX
			   | JBOX_DRAWINLAST
			   //		| JBOX_TRANSPARENT
			   //		| JBOX_NOGROW
			   //		| JBOX_GROWY
			   | JBOX_GROWBOTH
			   //		| JBOX_HILITE
			   //		| JBOX_BACKGROUND
			   | JBOX_DRAWBACKGROUND
			   //		| JBOX_NOFLOATINSPECTOR
			   //		| JBOX_TEXTFIELD
			   //		| JBOX_MOUSEDRAGDELTA
			   //		| JBOX_TEXTFIELD
			   ;

	jbox_new((t_jbox *)x, boxflags, argc, argv);
	x->a_chans = 1;
	x->a_values = NULL;
	x->a_rmsvalues = NULL;
	gridmeter_initvalues(x);
	x->a_obj.z_box.b_firstin = (void *)x;
	dsp_setupjbox((t_pxjbox *)x, 1);
	x->a_obj.z_misc |= Z_MC_INLETS;

	x->a_clock = clock_new(x, (method)gridmeter_tick);
	attr_dictionary_process(x, d);
	jbox_ready((t_jbox *)x);
	return x;
}
