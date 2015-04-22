/*
	uisimp -- fancier version of a toggle
*/

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include "jpatcher_api.h"
#include "jgraphics.h"

typedef struct _uisimp
{
	t_jbox u_box;						// header for UI objects
	void *u_out;						// outlet pointer
	long u_state;						// state (1 or 0)
	char u_mouseover;					// is mouse over the object
	char u_mousedowninside;				// is mouse down within the object
	char u_trackmouse;					// if non-zero, track mouse when button not down
	t_jrgba u_outline;
	t_jrgba u_background;
	t_jrgba u_hilite;
} t_uisimp;

void *uisimp_new(t_symbol *s, long argc, t_atom *argv);
void uisimp_free(t_uisimp *x);
void uisimp_assist(t_uisimp *x, void *b, long m, long a, char *s);
void uisimp_paint(t_uisimp *x, t_object *patcherview);
void uisimp_getdrawparams(t_uisimp *x, t_object *patcherview, t_jboxdrawparams *params);
void uisimp_mousedown(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers);
void uisimp_mousedrag(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers);
void uisimp_mouseup(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers);
void uisimp_mouseenter(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers);
void uisimp_mouseleave(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers);
void uisimp_mousemove(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers);
void uisimp_bang(t_uisimp *x);
void uisimp_int(t_uisimp *x, long n);


static t_class *s_uisimp_class;

void ext_main(void *r)
{
	t_class *c;

	c = class_new("uisimp", (method)uisimp_new, (method)uisimp_free, sizeof(t_uisimp), 0L, A_GIMME, 0);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_FIXWIDTH | JBOX_COLOR);

	class_addmethod(c, (method)uisimp_paint,		"paint",	A_CANT, 0);
	class_addmethod(c, (method)uisimp_mousedown,	"mousedown",	A_CANT, 0);
	class_addmethod(c, (method)uisimp_mousedrag,	"mousedrag",	A_CANT, 0);
	class_addmethod(c, (method)uisimp_mouseup,		"mouseup",	A_CANT, 0);
	class_addmethod(c, (method)uisimp_mouseenter,	"mouseenter",	A_CANT, 0);
	class_addmethod(c, (method)uisimp_mouseleave,	"mouseleave",	A_CANT, 0);
	class_addmethod(c, (method)uisimp_mousemove,	"mousemove",	A_CANT, 0);
	class_addmethod(c, (method)uisimp_assist,		"assist",	A_CANT, 0);

	// messages for state setting / retrieval

	class_addmethod(c, (method)uisimp_int,			"int",	A_LONG, 0);
	class_addmethod(c, (method)uisimp_bang,			"bang", 0);

	// attributes

	CLASS_ATTR_CHAR(c, "trackmouse", 0, t_uisimp, u_trackmouse);
	CLASS_ATTR_STYLE_LABEL(c, "trackmouse", 0, "onoff", "Track Mouse");
	CLASS_ATTR_SAVE(c, "trackmouse", 0);
	CLASS_ATTR_CATEGORY(c, "trackmouse", 0, "Behavior");

	CLASS_STICKY_ATTR(c, "category", 0, "Color");
	CLASS_ATTR_RGBA(c, "bgcolor", 0, t_uisimp, u_background);
	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c, "bgcolor", 0, "1. 1. 1. 1.");
	CLASS_ATTR_STYLE_LABEL(c,"bgcolor",0,"rgba","Background Color");

	CLASS_ATTR_RGBA(c, "bordercolor", 0, t_uisimp, u_outline);
	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c, "bordercolor", 0, "0.5 0.5 0.5 1.");
	CLASS_ATTR_STYLE_LABEL(c,"bordercolor",0,"rgba","Border Color");

	CLASS_ATTR_RGBA(c, "hilitecolor", 0, t_uisimp, u_hilite);
	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c, "hilitecolor", 0, "0.5 0.5 0.5 1.");
	CLASS_ATTR_STYLE_LABEL(c,"hilitecolor",0,"rgba","Hilite Color");

	// color uses the color declared in t_jbox.b_color
	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c, "color", 0, "0. 0. 0. 1.");
	CLASS_ATTR_STYLE_LABEL(c,"color",0,"rgba","Check Color");

	CLASS_STICKY_ATTR_CLEAR(c, "category");


	CLASS_ATTR_DEFAULT(c,"patching_rect",0, "0. 0. 20. 20.");

	class_register(CLASS_BOX, c);
	s_uisimp_class = c;
}

void uisimp_assist(t_uisimp *x, void *b, long m, long a, char *s)
{
	if (m == 1)		//inlet
		sprintf(s, "(signal) Audio Input");
}

void uisimp_paint(t_uisimp *x, t_object *patcherview)
{
	t_rect rect;
	t_jgraphics *g = (t_jgraphics *) patcherview_get_jgraphics(patcherview);		// obtain graphics context
	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);

	// paint outline
	jgraphics_set_source_jrgba(g, &x->u_outline);
	jgraphics_set_line_width(g, 1.);
	jgraphics_rectangle(g, 0., 0., rect.width, rect.height);
	jgraphics_stroke(g);

	// paint "inner highlight" to indicate mouseover
	if (x->u_mouseover && !x->u_mousedowninside) {
		jgraphics_set_source_jrgba(g, &x->u_hilite);
		jgraphics_set_line_width(g, 1.);
		jgraphics_rectangle(g, 1., 1., rect.width - 2, rect.height - 2);
		jgraphics_stroke(g);
	}
	if (x->u_mousedowninside && !x->u_state) {		// paint hilite color
		jgraphics_set_source_jrgba(g, &x->u_hilite);
		jgraphics_rectangle(g, 1., 1., rect.width - 2, rect.height - 2);
		jgraphics_fill(g);
	}

	// paint "check" (actually a filled rectangle) if state is on
	if (x->u_state) {
		t_jrgba col;

		jbox_get_color((t_object *)x, &col);
		jgraphics_set_source_jrgba(g, &col);
		if (x->u_mousedowninside)		// make rect bigger if mouse is down and we are unchecking
			jgraphics_rectangle(g, 3., 3., rect.width - 6, rect.height - 6);
		else
			jgraphics_rectangle(g, 4., 4., rect.width - 8, rect.height - 8);
		jgraphics_fill(g);
	}
}

// mouse interaction

void uisimp_mousedown(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers)
{
	x->u_mousedowninside = true;	// wouldn't get a click unless it was inside the box
	jbox_redraw((t_jbox *)x);
}

void uisimp_mousedrag(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers)
{
	t_rect rect;

	// test to see if mouse is still inside the object
	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);

	// redraw if changed
	if (pt.x >= 0 && pt.x <= rect.width && pt.y >= 0 && pt.y <= rect.height) {
		if (!x->u_mousedowninside) {
			x->u_mousedowninside = true;
			jbox_redraw((t_jbox *)x);
		}
	} else {
		if (x->u_mousedowninside) {
			x->u_mousedowninside = false;
			jbox_redraw((t_jbox *)x);
		}
	}
}

void uisimp_mouseup(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers)
{
	if (x->u_mousedowninside) {
		x->u_state = !x->u_state;
		uisimp_bang(x);
		x->u_mousedowninside = false;
		jbox_redraw((t_jbox *)x);
	}
}

void uisimp_mouseenter(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers)
{
	x->u_mouseover = true;
	jbox_redraw((t_jbox *)x);
}

void uisimp_mouseleave(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers)
{
	x->u_mouseover = false;
	jbox_redraw((t_jbox *)x);
}

void uisimp_mousemove(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers)
{
	// nothing to do here, but could track mouse position inside object
}

void uisimp_bang(t_uisimp *x)
{
	outlet_int(x->u_out, x->u_state);
}

void uisimp_int(t_uisimp *x, long n)
{
	x->u_state = n? 1 : 0;
	uisimp_bang(x);
	jbox_redraw((t_jbox *)x);
}

void uisimp_getdrawparams(t_uisimp *x, t_object *patcherview, t_jboxdrawparams *params)
{
	params->d_bordercolor.alpha = 0;
	params->d_boxfillcolor.alpha = 0;
}

void uisimp_free(t_uisimp *x)
{
	jbox_free((t_jbox *)x);
}

void *uisimp_new(t_symbol *s, long argc, t_atom *argv)
{
	t_uisimp *x = NULL;
	t_dictionary *d = NULL;
	long boxflags;

	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_uisimp *)object_alloc(s_uisimp_class);
	boxflags = 0
			   | JBOX_DRAWFIRSTIN
			   | JBOX_NODRAWBOX
			   | JBOX_DRAWINLAST
			   | JBOX_TRANSPARENT
			   //		| JBOX_NOGROW
			   | JBOX_GROWY
			   //		| JBOX_GROWBOTH
			   //		| JBOX_HILITE
			   //		| JBOX_BACKGROUND
			   | JBOX_DRAWBACKGROUND
			   //		| JBOX_NOFLOATINSPECTOR
			   //		| JBOX_TEXTFIELD
			   //		| JBOX_MOUSEDRAGDELTA
			   //		| JBOX_TEXTFIELD
			   ;

	jbox_new((t_jbox *)x, boxflags, argc, argv);
	x->u_box.b_firstin = (void *)x;
	x->u_mousedowninside = x->u_mouseover = x->u_state = 0;
	x->u_out = intout((t_object *)x);
	attr_dictionary_process(x,d);
	jbox_ready((t_jbox *)x);
	return x;
}
