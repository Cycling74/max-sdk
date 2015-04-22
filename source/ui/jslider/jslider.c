#ifdef WIN_VERSION
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "ext_parameter.h"
#include "ext_boxstyle.h"
#include "common/commonsyms.c"

#ifdef WIN_VERSION
#include <float.h>
#endif

static t_class	*s_jslider_class = 0;

static t_symbol *ps_knobcolor;
static t_symbol *ps_elementcolor;
static t_symbol *ps_floatoutput;
static t_symbol *ps_hslider;
static t_symbol *ps_min;
static t_symbol *ps_preset;
static t_symbol *ps_relative;
static t_symbol *ps_sizeattr;
static t_symbol *ps_slider;
static t_symbol *ps_slider_mousedown;
static t_symbol *ps_slider_mouseup;

// mouse tracking stuff

static t_pt s_jslider_cum;
static double s_jslider_startval;

#define INRANGE(v,lo,hi) ((v)<=(hi)&&(v)>=(lo))

#define	JSLIDER_BORDERTHICKNESS			(2.)
#define JSLIDER_CORNERSIZE				(6.)
#define JSLIDER_MOUSEOVER_DELAY			(200.0)

#define JSLIDER_DISPLAYINSET			5		// amount subtracted from rect for value
#define JSLIDER_INDICATOR_PLUS_THICKNESS (6.0)
enum {
	JSLIDER_SHAPE_INDICATOR_PLUS = 0,
    JSLIDER_SHAPE_LESSROUNDED,
    JSLIDER_SHAPE_ROUNDED,
    JSLIDER_SHAPE_TRIANGLE,
	JSLIDER_SHAPE_RECTANGLE,
	JSLIDER_SHAPE_INDICATOR
};

typedef struct _jslider
{
	t_jbox		j_box;
	double		j_min;
	double		j_size;			// number of steps
	double		j_mult;
	double		j_val;
	t_atom_long	j_floatoutput;
	char		j_relative;		// relative mousing (like orig miller slider, but not like h/uslider)
	char		j_orientation;	// 0 = auto, 1 = horiz, 2 = vertical
	char		j_mouseoverpending;
	char		j_mouseover;
	int			j_mousepos;
	char		j_knobshape;
	t_jrgba		j_brgba;
	t_jrgba		j_frgba;
	t_jrgba		j_frgba2;
	t_jrgba		j_elementcolor;
	double		j_thickness;
} t_jslider;

void *jslider_new(t_symbol *s, short argc, t_atom *argv);
void jslider_free(t_jslider *x);
void jslider_symbols_init();
t_max_err jslider_notify(t_jslider *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void jslider_assist(t_jslider *x, void *b, long m, long a, char *s);
void jslider_preset(t_jslider *x);
void jslider_tick(t_jslider *x);
void *jslider_stdargs(t_dictionary *d, t_symbol *s, long argc, t_atom *argv);
void jslider_paint(t_jslider *x, t_object *view);
void jslider_paint_horizontal_shape(t_jslider *x, t_jgraphics *g, t_rect *r, char is_background);
void jslider_paint_vertical_shape(t_jslider *x, t_jgraphics *g, t_rect *r, char is_background);
void jslider_bang(t_jslider *x);
void jslider_int(t_jslider *x, long n);
void jslider_float(t_jslider *x, double f);
void jslider_set(t_jslider *x, t_symbol *s, long argc, t_atom *argv);
void jslider_setminmax(t_jslider *x, t_symbol *s, long argc, t_atom *argv);
t_max_err jslider_setattr_size(t_jslider *x, t_object *attr, long ac, t_atom *av);
t_max_err jslider_setattr_floatoutput(t_jslider *x, t_object *attr, long ac, t_atom *av);
t_max_err jslider_setvalueof(t_jslider *x, long ac, t_atom *av);
t_max_err jslider_getvalueof(t_jslider *x, long *ac, t_atom **av);
void jslider_assign(t_jslider *x, double f, long notify);
double jslider_constrain(t_jslider *x, double f);
char jslider_ishorizontal(t_jslider *x, t_rect *r);
double jslider_postoval(t_jslider *x, t_pt pt, t_rect *r, char ishoriz);
double jslider_valtopos(t_jslider *x, double val, t_rect *r, char ishoriz);
void jslider_mousedown(t_jslider *x, t_object *patcherview, t_pt pt, long modifiers);
void jslider_mousedragdelta(t_jslider *x, t_object *patcherview, t_pt pt, long modifiers);
void jslider_mouseup(t_jslider *x, t_object *patcherview, t_pt pt, long modifiers);

void ext_main(void *r)
{
	t_class *c;

	common_symbols_init();
	jslider_symbols_init();

	c = class_new("slider",
				  (method)jslider_new,
				  (method)jslider_free,
				  sizeof(t_jslider),
				  (method)NULL,
				  A_GIMME,
				  0L);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY; // to specify dictionary constructor

	jbox_initclass(c, JBOX_FIXWIDTH | JBOX_LEGACYCOLOR);

	class_addmethod(c, (method)jslider_paint, "paint", A_CANT, 0);
	class_addmethod(c, (method)jslider_stdargs, "stdargs", A_CANT, 0);

	class_addmethod(c, (method)jslider_int, "int", A_LONG, 0);
	class_addmethod(c, (method)jslider_float, "float", A_FLOAT, 0);
	class_addmethod(c, (method)jslider_bang, "bang", 0);
	class_addmethod(c, (method)jslider_set, "set", A_GIMME, 0);
	class_addmethod(c, (method)jslider_setminmax, "setminmax", A_GIMME, 0);
	class_addmethod(c, (method)jslider_mousedown, "mousedown", A_CANT, 0);
	class_addmethod(c, (method)jslider_mousedragdelta, "mousedragdelta", A_CANT, 0);
	class_addmethod(c, (method)jslider_mouseup, "mouseup", A_CANT, 0);
	class_addmethod(c, (method)jslider_getvalueof, "getvalueof", A_CANT, 0);
	class_addmethod(c, (method)jslider_setvalueof, "setvalueof", A_CANT, 0);
	class_addmethod(c, (method)jslider_assist, "assist", A_CANT, 0);
	class_addmethod(c, (method)jslider_preset, "preset", 0);
	class_addmethod(c, (method)jslider_notify, "notify", A_CANT, 0);

	CLASS_ATTR_DEFAULT(c,"patching_rect",0, "0. 0. 20. 140.");

	CLASS_STICKY_CATEGORY(c,0,"Value");
	CLASS_ATTR_DOUBLE(c, "size", 0, t_jslider, j_size);
	CLASS_ATTR_ACCESSORS(c,"size",(method)NULL,(method)jslider_setattr_size);
	CLASS_ATTR_BASIC(c, "size", 0);

	CLASS_ATTR_DOUBLE(c, "min", 0, t_jslider, j_min);
	CLASS_ATTR_BASIC(c, "min", 0);

	CLASS_ATTR_DOUBLE(c, "mult", 0, t_jslider, j_mult);
	CLASS_ATTR_BASIC(c, "mult", 0);

	CLASS_ATTR_ATOM_LONG(c, "floatoutput", 0, t_jslider, j_floatoutput);
	CLASS_ATTR_ACCESSORS(c, "floatoutput", (method)NULL, (method)jslider_setattr_floatoutput);
	CLASS_ATTR_BASIC(c, "floatoutput", 0);

	CLASS_ATTR_CHAR(c,"relative", 0, t_jslider, j_relative);
	CLASS_ATTR_LABEL(c,"relative", 0, "Mousing Mode");
	CLASS_ATTR_ENUMINDEX2(c, "relative", 0, "Absolute", "Relative");
	CLASS_ATTR_BASIC(c, "relative", 0);
	CLASS_STICKY_CATEGORY_CLEAR(c);

	CLASS_ATTR_CHAR(c,"orientation",0,t_jslider,j_orientation);
	CLASS_ATTR_LABEL(c,"orientation",0,"Orientation");
	CLASS_ATTR_ENUMINDEX3(c,"orientation", 0,"Automatic", "Horizontal", "Vertical");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "orientation", 0, "0");
	CLASS_ATTR_CATEGORY(c, "orientation", 0, "Appearance");

	CLASS_ATTR_CHAR(c, "knobshape", 0, t_jslider, j_knobshape);
	CLASS_ATTR_ENUMINDEX6(c, "knobshape", 0, "Indicator+", "Less Rounded", "Rounded", "Triangle", "Rectangle", "Indicator");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "knobshape", 0, "0");
	CLASS_ATTR_LABEL(c, "knobshape", 0, "Knob Shape");
	CLASS_ATTR_CATEGORY(c, "knobshape", 0, "Appearance");

	CLASS_STICKY_CATEGORY(c, 0, "Color");
	
	CLASS_ATTR_STYLE_RGBA_PREVIEW(c,"bgcolor",0,t_jslider,j_brgba,"Background Color","rect_fill");
	CLASS_ATTR_BASIC(c,"bgcolor",0);
	CLASS_ATTR_STYLE_ALIAS_RGBA_LEGACY(c,"bgcolor","brgba");
	CLASS_ATTR_STYLE_ALIAS_RGBA_LEGACY(c,"bgcolor","brgb");
	CLASS_ATTR_LEGACYDEFAULT(c, "bgcolor", "bgcolor", 0, "1. 1. 1. 1.");
	
	CLASS_ATTR_STYLE_RGBA_PREVIEW(c,"elementcolor",0,t_jslider,j_elementcolor,"Off Color","side_arch");
	CLASS_ATTR_BASIC(c,"elementcolor",0);

	CLASS_ATTR_STYLE_RGBA_PREVIEW(c,"knobcolor",0,t_jslider,j_frgba,"On Color","side_arch");
	CLASS_ATTR_BASIC(c, "knobcolor", 0);
	class_attr_stylemap(c, "knobcolor", "color");
	CLASS_ATTR_LEGACYDEFAULT(c, "knobcolor", "knobcolor", 0, "0.2 0.2 0.2 1.");
	CLASS_ATTR_STYLE_ALIAS_NOSAVE(c,"knobcolor", "frgba");	// ej: I doubt anyone used this but color instead so leaving it as a normal alias (will use class_attr_style_alias if something comes up)

	CLASS_STICKY_CATEGORY_CLEAR(c);
	
	CLASS_ATTR_DOUBLE(c,"thickness",0,t_jslider,j_thickness);
	CLASS_ATTR_LABEL(c,"thickness",0,"Thickness");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "thickness", 0, "100");
	CLASS_ATTR_CATEGORY(c, "thickness", 0, "Appearance");
	CLASS_ATTR_FILTER_CLIP(c,"thickness",1,100);

	// hide the color attribute from the inspector
	// it's still posisble to set color via the color message or the "Color..." item menu
	//CLASS_ATTR_INVISIBLE(c, "color", 0);
	//CLASS_ATTR_ATTR_PARSE(c, "color","save", USESYM(long), 0, "0");

	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"size",0,"128");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"min",0,"0");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"mult",0,"1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"floatoutput",0,"0");
	CLASS_ATTR_DEFAULT_SAVE(c,"relative",0,"0");
	CLASS_ATTR_LABEL(c,"size", 0, "Range");
	CLASS_ATTR_LABEL(c,"min", 0, "Output Minimum");
	CLASS_ATTR_LABEL(c,"mult", 0, "Output Multiplier");
	CLASS_ATTR_STYLE_LABEL(c,"floatoutput",0,"onoff","Float Output");

	CLASS_ATTR_ORDER(c, "floatoutput",	0, "1");
	CLASS_ATTR_ORDER(c, "relative",		0, "2");
	CLASS_ATTR_ORDER(c, "size",			0, "3");
	CLASS_ATTR_ORDER(c, "min",			0, "4");
	CLASS_ATTR_ORDER(c, "mult",			0, "5");

	CLASS_ATTR_OBSOLETE(c, "bordercolor", 0);
	CLASS_ATTR_INTRODUCED(c, "elementcolor", 0, "7.0.0");
	CLASS_ATTR_INTRODUCED(c, "knobshape", 0, "7.0.0");
	CLASS_ATTR_INTRODUCED(c, "style", 0, "7.0.0");
	CLASS_ATTR_INTRODUCED(c, "thickness", 0, "7.0.0");

	class_register(CLASS_BOX, c);
	s_jslider_class = c;

}

void jslider_symbols_init()
{
	ps_elementcolor = gensym("elementcolor");
	ps_floatoutput = gensym("floatoutput");
	ps_hslider = gensym("hslider");
	ps_min = gensym("min");
	ps_preset = gensym("_preset");
	ps_relative = gensym("relative");
	ps_sizeattr = gensym("size");
	ps_slider = gensym("slider");
	ps_slider_mousedown = gensym("slider_mousedown");
	ps_slider_mouseup = gensym("slider_mouseup");
	ps_knobcolor = gensym("knobcolor");
}

// slider has 6 args: x, y, w, size (height), min, and mult
void *jslider_stdargs(t_dictionary *d, t_symbol *s, long argc, t_atom *argv)
{
	long left, top, width, height, thin, length;
	short horiz, type;
	t_atom at[4];

	horiz = (s == ps_hslider) ? 1 : 0;
	type = (s == ps_slider) ? 0 : 1; // Miller's original slider (relative mousing by default)

	if (d && argc>3 && argv) {

		// all psaved versions should have the first 4 args, even if it's a really old patch
		left = atom_getlong(argv);
		top = atom_getlong(argv+1);
		thin = atom_getlong(argv+2);
		length = atom_getlong(argv+3);
		height = (horiz) ? thin : length+(type?16:7); // we need to add 16 because we have an 8 pixel border on either side of x->s_size
		width = (horiz) ? length+(16) : thin; // old vanilla slider was always vert so we don't need to check type

		atom_setlong(at+0, left);
		atom_setlong(at+1, top);
		atom_setlong(at+2, width);
		atom_setlong(at+3, height);

		dictionary_appendatoms(d, _sym_patching_rect, 4, at); // rect is x y width, height, like t_rect, but with long args

		//dictionary_appendatom(d, _sym_max, argv+3);  // argv+3 is both the max and the height when importing from a miller slider
		// slider and u/hslider have different order... don't ask why...
		if (!type && argc > 5) {
			dictionary_appendatom(d, gensym("size"), argv+3);
			dictionary_appendatom(d, gensym("min"), argv+4);
			dictionary_appendatom(d, _sym_mult, argv+5);
		} else if (type && argc > 6) {
			dictionary_appendatom(d, gensym("size"), argv+4);
			dictionary_appendatom(d, _sym_mult, argv+5);
			dictionary_appendatom(d, gensym("min"), argv+6);
		}

		// if it's an old slider and we're doing the stdargs then it's forced either horiz or vert, for compatibility
		if (horiz)
			dictionary_appendlong(d, _sym_orientation, 1); // force horizontal
		else
			dictionary_appendlong(d, _sym_orientation, 2); // force vertical

		dictionary_appendlong(d, ps_relative, type ? 0 : 1);

		// if it's hslider/uslider it does have an extra value which defines the color background
		if (type && argc > 7) {
			t_jrgba c;
			long color = CLAMP(atom_getlong(argv+7), 0, 15); // constrains colors to 0-15 zone
			set_jrgba_from_boxcolor_index(color + 1, &c);

			// ej: mapped old color message to the color attribute (the knob)
			// the old color message used to set the background color
			// the main reason to assign the color N to the knob when importing is to keep the dark background of Max 7.
			// we can revert that if testing proves to be inapropriate
			dictionary_appendjrgba(d, gensym("knobcolor"), &c);
		}
	}
	return 0;
}

void *jslider_new(t_symbol *s, short argc, t_atom *argv)
{
	t_jslider *x;
	long flags;
	t_dictionary *d=NULL;

	if (!(d=object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_jslider *) object_alloc(s_jslider_class);
	if (!x)
		return NULL;

	flags = 0
			| JBOX_DRAWFIRSTIN
			| JBOX_NODRAWBOX
			| JBOX_DRAWINLAST			// rbs -- I think we can turn this off
			//		| JBOX_TRANSPARENT
			//		| JBOX_NOGROW
			//		| JBOX_GROWY
			| JBOX_GROWBOTH
			//		| JBOX_HILITE
			| JBOX_DRAWBACKGROUND
			| JBOX_MOUSEDRAGDELTA
			//		| JBOX_NOFLOATINSPECTOR
			;

	x->j_val = 0;
	x->j_mousepos = -1;
	
	jbox_new(&x->j_box, flags, argc, argv);
	x->j_box.b_firstin = (t_object *) x;
	outlet_new((t_object *)x,NULL);

	// make sure the floatoutput mode is set properly before asking for the size
	dictionary_getlong(d, gensym("floatoutput"), &x->j_floatoutput);

	jbox_processlegacydefaults((t_jbox *)x, d, 0);
	attr_dictionary_process(x,d); // handle attribute args
	jbox_ready(&x->j_box);
	return x;
}

void jslider_assist(t_jslider *x, void *b, long m, long a, char *s)
{
	if (m==ASSIST_INLET) {
		sprintf(s,"Displays Value Received");
	}
	else {
		sprintf(s,"Outputs Value When Slider is Changed");
	}
}

void jslider_preset(t_jslider *x)
{
	void *z;

	if (!(z = ps_preset->s_thing))
		return;

	binbuf_vinsert(z,"ossf",x,object_classname(x), _sym_float, x->j_val);
}

void jslider_free(t_jslider *x)
{
	jbox_free(&x->j_box);
}


void jslider_paint(t_jslider *x, t_object *view)
{
	t_rect rect, elemrect;
	t_jgraphics *g;
	t_jrgba c;
	char ishoriz;
	double val, thick, offset;
	int pos;
	
	g = (t_jgraphics *) patcherview_get_jgraphics(view);
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	object_attr_getjrgba((t_object *)x, _sym_bgcolor, &c);
	jgraphics_set_source_jrgba(g, &c);
	
	// draw background
	jgraphics_rectangle_fill_fast(g, 0, 0, rect.width, rect.height);
	
	if (x->j_knobshape != JSLIDER_SHAPE_INDICATOR) {
		// draw element
		ishoriz = jslider_ishorizontal(x, &rect);
		
		if (ishoriz) {
			thick = rect.height * x->j_thickness * 0.01;
			if (x->j_knobshape == JSLIDER_SHAPE_RECTANGLE)
				offset = 0.0;
			else if (x->j_knobshape == JSLIDER_SHAPE_INDICATOR_PLUS) {
				offset = JSLIDER_INDICATOR_PLUS_THICKNESS * 2.0;
			} else
				offset = thick;
			elemrect.x = JSLIDER_DISPLAYINSET;
			elemrect.y = (rect.height - thick) * 0.5;
			elemrect.width = rect.width - JSLIDER_DISPLAYINSET * 2.0 - offset * 0.5;
			elemrect.height = thick;
		} else {
			thick = rect.width * x->j_thickness * 0.01;
			if (x->j_knobshape == JSLIDER_SHAPE_RECTANGLE)
				offset = 0.0;
			else if (x->j_knobshape == JSLIDER_SHAPE_INDICATOR_PLUS) {
				offset = JSLIDER_INDICATOR_PLUS_THICKNESS * 2.0;
			} else
				offset = thick;
			elemrect.x = (rect.width - thick) * 0.5;
			elemrect.y = JSLIDER_DISPLAYINSET + offset * 0.5;
			elemrect.width = thick;
			elemrect.height = rect.height - JSLIDER_DISPLAYINSET * 2.0 - offset * 0.5;
		}
		
		object_attr_getjrgba((t_object *)x, ps_elementcolor, &c);
		jgraphics_set_source_jrgba(g, &c);
		if (ishoriz)
			jslider_paint_horizontal_shape(x, g, &elemrect, true);
		else
			jslider_paint_vertical_shape(x, g, &elemrect, true);
		
		// draw indicator
		val = CLAMP(x->j_val, 0, x->j_size);
		pos = jslider_valtopos(x, val, &rect, ishoriz);
		
		if (ishoriz) {
			elemrect.x = JSLIDER_DISPLAYINSET;
			elemrect.width = pos - JSLIDER_DISPLAYINSET;
		} else {
			elemrect.y = pos;
			elemrect.height = (rect.height - JSLIDER_DISPLAYINSET) - pos;
		}
		
		object_attr_getjrgba((t_object *)x, ps_knobcolor, &c);
		c.alpha *= val != 0 ? 1 : 0.5;
		jgraphics_set_source_jrgba(g, &c);
		if (ishoriz)
			jslider_paint_horizontal_shape(x, g, &elemrect, false);
		else
			jslider_paint_vertical_shape(x, g, &elemrect, false);
	} else {
		double val = x->j_val;

		ishoriz = jslider_ishorizontal(x, &rect);
		val = CLAMP(val, 0, x->j_size);
		pos = jslider_valtopos(x, val, &rect, ishoriz);
		object_attr_getjrgba((t_object *)x, ps_knobcolor, &c);
		jgraphics_set_source_jrgba(g, &c);
		if (ishoriz) {
			jgraphics_move_to(g, pos,3);
			jgraphics_line_to(g, pos,rect.height - 3);
		} else {
			jgraphics_move_to(g, 3, pos);
			jgraphics_line_to(g, rect.width - 3, pos);
		}
		jgraphics_set_line_width(g, 6 * x->j_thickness * 0.01);
		jgraphics_stroke(g);
	}	
}

void jslider_paint_horizontal_shape(t_jslider *x, t_jgraphics *g, t_rect *r, char is_background)
{
	if (x->j_knobshape == JSLIDER_SHAPE_ROUNDED) {
		jgraphics_rectangle(g, r->x, r->y, r->width, r->height);
		jgraphics_arc(g, r->x + r->width, r->y + r->height * 0.5, r->height * 0.5, -JGRAPHICS_PIOVER2, JGRAPHICS_PIOVER2);
		jgraphics_fill(g);
	} else if (x->j_knobshape == JSLIDER_SHAPE_LESSROUNDED) {	// like a rounded rectangle with a radius of 4.0
		jgraphics_move_to(g, r->x, r->y + r->height);
		jgraphics_line_to(g, (r->x + r->width + r->height * 0.5) - 5.03, r->y + r->height);
		jgraphics_curve_to(g, (r->x + r->width + r->height * 0.5) - 2.25, r->y + r->height, (r->x + r->width + r->height * 0.5), (r->y + r->height) - 1.38, (r->x + r->width + r->height * 0.5), (r->y + r->height) - 3.08);
		jgraphics_line_to(g, (r->x + r->width + r->height * 0.5), r->y + 3);
		jgraphics_curve_to(g, (r->x + r->width + r->height * 0.5), r->y + 1.3, (r->x + r->width + r->height * 0.5) - 2.25, r->y, (r->x + r->width + r->height * 0.5) - 5.03, r->y);
		jgraphics_line_to(g, r->x, r->y);
		jgraphics_close_path(g);
		jgraphics_fill(g);
	} else if (x->j_knobshape == JSLIDER_SHAPE_TRIANGLE) {
		jgraphics_rectangle(g, r->x, r->y, r->width, r->height);
		jgraphics_move_to(g, r->x + r->width, r->y);
		jgraphics_line_to(g, r->x + r->width + r->height * 0.5, r->y  + r->height * 0.5);
		jgraphics_line_to(g, r->x + r->width, r->y + r->height);
		jgraphics_close_path(g);
		jgraphics_fill(g);
	} else if (x->j_knobshape == JSLIDER_SHAPE_RECTANGLE) {
		jgraphics_rectangle(g, r->x, r->y, r->width, r->height);
		jgraphics_fill(g);
	} else if (x->j_knobshape == JSLIDER_SHAPE_INDICATOR_PLUS) {
		if (is_background) {
			jgraphics_rectangle_fill_fast(g, r->x, r->y, r->width + JSLIDER_INDICATOR_PLUS_THICKNESS, r->height);
		} else {
			if (r->width > 0)	// when the slider is at 0 only draw one rect
				jgraphics_rectangle_fill_fast(g, r->x, r->y, r->width - 1.0, r->height);
			jgraphics_rectangle_fill_fast(g, r->x + r->width, r->y, JSLIDER_INDICATOR_PLUS_THICKNESS, r->height);
		}
	}
}

void jslider_paint_vertical_shape(t_jslider *x, t_jgraphics *g, t_rect *r, char is_background)
{
	if (x->j_knobshape == JSLIDER_SHAPE_ROUNDED) {
		jgraphics_rectangle(g, r->x, r->y, r->width, r->height);
		jgraphics_arc(g, r->x + r->width * 0.5, r->y, r->width * 0.5, JGRAPHICS_PI, 0.);
		jgraphics_fill(g);
	} else if (x->j_knobshape == JSLIDER_SHAPE_LESSROUNDED) {	// like a rounded rectangle with a radius of 4.0
		jgraphics_move_to(g, r->x, r->y + r->height);
		jgraphics_line_to(g, r->x + r->width, r->y + r->height);
		jgraphics_line_to(g, r->x + r->width, r->y - r->width * 0.5 + 4);
		jgraphics_curve_to(g, r->x + r->width, r->y - r->width * 0.5 + 1.79, (r->x + r->width) - 1.16, r->y - r->width * 0.5 , (r->x + r->width) - 2.59, r->y - r->width * 0.5 );
		jgraphics_line_to(g, r->x + 2.59, r->y - r->width * 0.5);
		jgraphics_curve_to(g, r->x + 1.16, r->y - r->width * 0.5, r->x, r->y  - r->width * 0.5+ 1.79, r->x, r->y  - r->width * 0.5+ 4);
		jgraphics_line_to(g, r->x, r->y + r->height);
		jgraphics_close_path(g);
		jgraphics_fill(g);
	} else if (x->j_knobshape == JSLIDER_SHAPE_TRIANGLE) {
		jgraphics_rectangle(g, r->x, r->y, r->width, r->height);
		jgraphics_move_to(g, r->x, r->y);
		jgraphics_line_to(g, r->x + r->width * 0.5, r->y - r->width * 0.5);
		jgraphics_line_to(g, r->x + r->width, r->y);
		jgraphics_close_path(g);
		jgraphics_fill(g);
	} else if (x->j_knobshape == JSLIDER_SHAPE_RECTANGLE) {
		jgraphics_rectangle(g, r->x, r->y, r->width, r->height);
		jgraphics_fill(g);
	} else if (x->j_knobshape == JSLIDER_SHAPE_INDICATOR_PLUS) {
		if (is_background) {
			jgraphics_rectangle_fill_fast(g, r->x, r->y - JSLIDER_INDICATOR_PLUS_THICKNESS, r->width, r->height + JSLIDER_INDICATOR_PLUS_THICKNESS);
		} else {
			jgraphics_rectangle_fill_fast(g, r->x, r->y +1, r->width, r->height - 1);
			jgraphics_rectangle_fill_fast(g, r->x, r->y - JSLIDER_INDICATOR_PLUS_THICKNESS, r->width, JSLIDER_INDICATOR_PLUS_THICKNESS);
		}
	}
}

void jslider_bang(t_jslider *x)
{
	double value;

	value = CLAMP(x->j_val, 0, x->j_size) * x->j_mult;
	value += x->j_min;

	if (x->j_floatoutput)
		outlet_float(x->j_box.b_ob.o_outlet, value);
	else {
		long iv;

		iv = value + (value >= 0 ? 0.5 : -0.5); // rounding properly negative numbers too
		outlet_int(x->j_box.b_ob.o_outlet, iv);
	}
}

void jslider_int(t_jslider *x, long n)
{
	jslider_assign(x, (double)n, true);
	jslider_bang(x);
}

void jslider_float(t_jslider *x, double f)
{
	jslider_assign(x, f, true);
	jslider_bang(x);
}

void jslider_setminmax(t_jslider *x, t_symbol *s, long argc, t_atom *argv)
{
	double a, b;

	if (argc > 1) {
		double old_min = x->j_min;
		double old_size = x->j_size;
		a = b = 0;

		if (argv[0].a_type == A_LONG)
			a = (double)atom_getlong(&argv[0]);
		else if (argv[0].a_type == A_FLOAT)
			a = (double)atom_getfloat(&argv[0]);

		if (argv[1].a_type == A_LONG)
			b = (double)atom_getlong(&argv[1]);
		else if (argv[1].a_type == A_FLOAT)
			b = (double)atom_getfloat(&argv[1]);

		if (a == b) {
			x->j_min = 0.;
			x->j_size = 1.;
		} else  if (a < b) {
			x->j_min = a;
			x->j_size = b - a;
		} else {
			x->j_min = b;
			x->j_size = a - b;
		}

		x->j_floatoutput = 1;

		object_attr_touch((t_object *)x, ps_min);
		object_attr_touch((t_object *)x, ps_sizeattr);
		object_attr_touch((t_object *)x, ps_floatoutput);

		if (old_min != x->j_min || old_size != x->j_size)
			jbox_redraw(&x->j_box);
	}
}

void jslider_set(t_jslider *x, t_symbol *s, long argc, t_atom *argv)
{
	if (argc && (argv->a_type == A_FLOAT || argv->a_type == A_LONG))
		jslider_assign(x, atom_getfloat(argv), true);
}

t_max_err jslider_setattr_size(t_jslider *x, t_object *attr, long ac, t_atom *av)
{
	double d;

	if (ac && av) {
		d = atom_getfloat(av);
		if (x->j_floatoutput == 1) {
			if (d < 1)
				d = 1;
		} else if (x->j_floatoutput != -1) {
			d = (long)d;
			if (d < 2)
				d = 2;
		}
		x->j_size = d;
		x->j_val = jslider_constrain(x, x->j_val);
	}
	return MAX_ERR_NONE;
}

t_max_err jslider_setattr_floatoutput(t_jslider *x, t_object *attr, long ac, t_atom *av)
{
	if (ac && av) {
		x->j_floatoutput = atom_getlong(av) ? 1 : 0;
		object_attr_setfloat(x, gensym("size"), x->j_size);	// make sure the range is correct
	}
	return MAX_ERR_NONE;
}

t_max_err jslider_setvalueof(t_jslider *x, long ac, t_atom *av)
{
	if (ac && av) {
		if (av->a_type == A_FLOAT)
			jslider_assign(x, atom_getfloat(av), false);
		else if (av->a_type == A_LONG)
			jslider_assign(x, atom_getlong(av), false);

		jslider_bang(x);
	}
	return MAX_ERR_NONE;
}

t_max_err jslider_getvalueof(t_jslider *x, long *ac, t_atom **av)
{
	t_atom a;

	if (ac && av) {
		if (*ac && *av) {
			//memory passed in use it
		} else {
			*av = (t_atom *)getbytes(sizeof(t_atom));
		}
		*ac = 1;
		if (x->j_floatoutput)
			atom_setfloat(&a,x->j_val);
		else
			atom_setlong(&a,(long)x->j_val);
		**av = a;
	}
	return MAX_ERR_NONE;
}

void jslider_assign(t_jslider *x, double f, long notify)
{
	x->j_val = jslider_constrain(x,f);
	if (notify)
		object_notify(x, _sym_modified, NULL);
	jbox_redraw(&x->j_box);
}

double jslider_constrain(t_jslider *x, double f)
{
	if (f < 0. || (f != f))		// rbs -- f != f tests for infinities and nans
		f = 0.;

	if (x->j_floatoutput) {		// constrain number between 0 and max, inclusive
		if (f > x->j_size)
			f = x->j_size;
		return f;
	} else {	// constrain number from 0 and max - 1
		long val;
		long max = (long) x->j_size;

		// rbs -- compare f to x->j_size which is a double.
		// This way, if f is very big (bigger than max value a long can take)
		// there won't be a problem.  For example (long)(5672881664.) is actually negative!
		if (f > x->j_size)
			f = x->j_size;
		val = (long) f;			// do cast now that we've limited the value
		if (val >= max)
			val = max - 1;
		return (double)val;
	}
}

char jslider_ishorizontal(t_jslider *x, t_rect *r)
{
	if (x->j_orientation == 0) { // automatic mode
		if (r->height > r->width)
			return (0);
		else
			return (1);
	} else
		return (x->j_orientation == 2 ? 0 : 1);
}

double jslider_postoval(t_jslider *x, t_pt pt, t_rect *r, char ishoriz)
{
	double pos, range, offset;
	
	if (x->j_knobshape == JSLIDER_SHAPE_INDICATOR || x->j_knobshape == JSLIDER_SHAPE_RECTANGLE) {
		offset = 0.0;
	} else if (x->j_knobshape == JSLIDER_SHAPE_INDICATOR_PLUS) {
		offset = JSLIDER_INDICATOR_PLUS_THICKNESS;
	} else {
		offset = ishoriz ? (r->height * x->j_thickness * 0.01 * 0.5) : (r->width * x->j_thickness * 0.01 * 0.5);
	}

	if (ishoriz) {
		pos = pt.x - offset;
		range = r->width - offset;
	} else {
		pos = r->height - pt.y - offset;
		range = r->height - offset;
	}
	if (pos <= JSLIDER_DISPLAYINSET)
		pos = 0.;
	else {
		pos -= JSLIDER_DISPLAYINSET;
		pos = (pos / (range - (JSLIDER_DISPLAYINSET*2))) * x->j_size;
	}
	return jslider_constrain(x,pos);
}

double jslider_valtopos(t_jslider *x, double val, t_rect *r, char ishoriz)
{
	double pos, range;
	double size;

	if (x->j_knobshape == JSLIDER_SHAPE_INDICATOR || x->j_knobshape == JSLIDER_SHAPE_RECTANGLE) {
		range = ishoriz ? r->width : r->height;
	} else if (x->j_knobshape == JSLIDER_SHAPE_INDICATOR_PLUS) {
		range = ishoriz ? (r->width - JSLIDER_INDICATOR_PLUS_THICKNESS) : (r->height - JSLIDER_INDICATOR_PLUS_THICKNESS);
	} else {
		if (ishoriz)
			range = r->width - (r->height * x->j_thickness * 0.01 * 0.5);
		else
			range = r->height - (r->width * x->j_thickness * 0.01 * 0.5);
	}

	if (x->j_floatoutput)
		size = x->j_size;
	else
		size = x->j_size - 1;

	if (size < 0)
		size = 0;
	if (size)
		pos = (val / size) * (range - (JSLIDER_DISPLAYINSET*2));
	else
		pos = 0;

	pos += JSLIDER_DISPLAYINSET;
	if (ishoriz)
		return pos;
	else
		return r->height - pos;
}

void jslider_mousedown(t_jslider *x, t_object *patcherview, t_pt pt, long modifiers)
{
	t_rect rect;
	double val;
	char ishoriz;

	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
	s_jslider_cum.x = s_jslider_cum.y = 0;
	ishoriz = jslider_ishorizontal(x, &rect);
	val = jslider_postoval(x, pt, &rect, ishoriz);
	object_notify(x, ps_slider_mousedown, NULL);
	if (!x->j_relative)
		jslider_float(x, val);	// set value immediately
	s_jslider_startval = x->j_val;
	x->j_mousepos = -1;
}

void jslider_mousedragdelta(t_jslider *x, t_object *patcherview, t_pt pt, long modifiers)
{
	t_rect rect;
	double inc;
	double val, cval;
	double factor;

	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);

	if (modifiers & eShiftKey) {
		pt.y *= 0.2;
		pt.x *= 0.2;
	}
	// need to cancel cum change if it is beyond zero or the max value
	s_jslider_cum.x += pt.x;
	s_jslider_cum.y -= pt.y;
	if (jslider_ishorizontal(x, &rect)) {
		factor = x->j_size / (rect.width - (JSLIDER_DISPLAYINSET*2));
		inc = s_jslider_cum.x * factor;
		val = s_jslider_startval + inc;
		if (! x->j_floatoutput)			// if shift is down, rounding make it work when the slider goes up in integer mode
			val = (long)(val + 0.5);
		cval = jslider_constrain(x,val);
		jslider_float(x,cval);
		// in case we were constrained, adjust the cum
		if (cval != val)
			s_jslider_cum.x = (cval-s_jslider_startval) / factor;
	} else {
		factor = x->j_size / (rect.height - (JSLIDER_DISPLAYINSET*2));
		inc = s_jslider_cum.y * factor;
		val = s_jslider_startval + inc;
		if (! x->j_floatoutput)			// if shift is down, rounding make it work when the slider goes up in integer mode
			val = (long)(val + 0.5);
		cval = jslider_constrain(x,val);
		jslider_float(x,cval);
		if (cval != val)
			s_jslider_cum.y = (cval - s_jslider_startval) / factor;
	}
}

void jslider_mouseup(t_jslider *x, t_object *patcherview, t_pt pt, long modifiers)
{
	double pos, vp;
	t_rect rect;
	double mx, my;
	char ishoriz;
	double offset = 0.0;

	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
	ishoriz = jslider_ishorizontal(x, &rect);
	pos = jslider_valtopos(x, x->j_val, &rect, ishoriz);
	vp = pos + 0.5;
	if (ishoriz) {
		if (x->j_knobshape == JSLIDER_SHAPE_INDICATOR_PLUS)
			offset = JSLIDER_INDICATOR_PLUS_THICKNESS;
		else if (x->j_knobshape != JSLIDER_SHAPE_INDICATOR && x->j_knobshape != JSLIDER_SHAPE_RECTANGLE)
			offset = (rect.height * x->j_thickness * 0.01 * 0.5);
		mx = vp + offset;
		my = pt.y;	// have y position be same as where mouse down clicked
	} else {
		if (x->j_knobshape == JSLIDER_SHAPE_INDICATOR_PLUS)
			offset = JSLIDER_INDICATOR_PLUS_THICKNESS;
		else if (x->j_knobshape != JSLIDER_SHAPE_INDICATOR && x->j_knobshape != JSLIDER_SHAPE_RECTANGLE)
			offset = (rect.width * x->j_thickness * 0.01 * 0.5);
		mx = pt.x;	// have x position be same as where mouse down clicked
		my = vp - offset;
	}

	if (fabs(pt.x-mx) > 1. || fabs(pt.y-my) > 1.) // this make sure that if you click at the "same" location we don't move the mouse.
		jmouse_setposition_box(patcherview, (t_object *) x, mx, my);
	
	x->j_mousepos = pos;
	object_notify(x, ps_slider_mouseup, NULL);
}

t_max_err jslider_notify(t_jslider *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
#if 0
	long argc = 0;
	t_atom *argv = NULL;
	t_symbol *name;

	if (msg == _sym_attr_modified) {
		name = (t_symbol *)object_method((t_object *)data,_sym_getname);
		if (name == _sym_color) {
			object_attr_getvalueof(x, _sym_color, &argc, &argv);
			if (argc && argv) {
				object_attr_setvalueof(x, _sym_bgcolor, argc, argv);
				sysmem_freeptr(argv);
			}
		}
	}
#endif
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}
