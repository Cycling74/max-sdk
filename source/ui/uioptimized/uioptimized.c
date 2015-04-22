/**
	@file
	uioptimized - demonstrate the drawing of various objects using jgraphics

	@ingroup	examples
*/

#include <stdlib.h>
#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"
#include "jgraphics.h"


/**********************************************************************/
// Data Structures

typedef struct _uioptimized {
	t_jbox				j_box;
	t_jrgba				j_rectcolor;	// rectangle color
	t_jrgba				j_overcolor;	// rectangle over color
	long				j_rectangle;	// number of rectangles to display
	t_rect				*j_rects;		// the location of the rectangles
	long				j_overrect;		// index of the over rectangle
	void				*j_out;			// index outlet
} t_uioptimized;


/**********************************************************************/
// Prototypes

void uioptimized_initclass();
t_uioptimized *uioptimized_new(t_symbol *s, short argc, t_atom *argv);
void uioptimized_free(t_uioptimized *x);

void uioptimized_mousemove(t_uioptimized *x, t_object *patcherview, t_pt pt, long modifiers);
void uioptimized_mouseleave(t_uioptimized *x, t_object *patcherview, t_pt pt, long modifiers);

void uioptimized_paint(t_uioptimized *x, t_object *view);
void uioptimized_paint_background(t_uioptimized *x, t_object *view, t_rect *rect);
t_max_err uioptimized_notify(t_uioptimized *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void uioptimized_assist(t_uioptimized *x, void *b, long m, long a, char *s);
t_max_err uioptimized_setattr_rectangle(t_uioptimized *x, void *attr, long ac, t_atom *av);


/**********************************************************************/
// Globals and Statics

static t_class *s_uioptimized_class = NULL;


/**********************************************************************/
// Class Definition and Life Cycle

void ext_main(void *r)
{
	t_class *c;

	c = class_new("uioptimized",
				  (method)uioptimized_new,
				  (method)uioptimized_free,
				  sizeof(t_uioptimized),
				  (method)NULL,
				  A_GIMME,
				  0L);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, 0);

	class_addmethod(c, (method) uioptimized_mousemove,		"mousemove", A_CANT, 0);
	class_addmethod(c, (method) uioptimized_mouseleave,		"mouseleave", A_CANT, 0);
	class_addmethod(c, (method) uioptimized_paint,			"paint", A_CANT, 0);
	class_addmethod(c, (method) uioptimized_notify,			"notify", A_CANT, 0);	// so the PAINT attribute of the attribute redraws the object
	class_addmethod(c, (method) uioptimized_assist,			"assist", A_CANT, 0);

	CLASS_ATTR_RGBA(c, "rectcolor", 0, t_uioptimized, j_rectcolor);
	CLASS_ATTR_STYLE_LABEL(c, "rectcolor", 0, "rgba", "Rectangle Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "rectcolor", 0, "0. 0. 0. 1.");

	CLASS_ATTR_RGBA(c, "overcolor", 0, t_uioptimized, j_overcolor);
	CLASS_ATTR_STYLE_LABEL(c, "overcolor", 0, "rgba", "Rectangle Over Color");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "overcolor", 0, "1. 0. 0. 1.");

	CLASS_ATTR_LONG(c, "rectangle", 0, t_uioptimized, j_rectangle);
	CLASS_ATTR_LABEL(c, "rectangle", 0, "Number of Rectangles");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "rectangle", 0, "74");
	CLASS_ATTR_ACCESSORS(c, "rectangle", (method)NULL, (method)uioptimized_setattr_rectangle);

	CLASS_ATTR_DEFAULT(c, "rect", 0, "0. 0. 128. 128.");

	class_register(CLASS_BOX, c);
	s_uioptimized_class = c;
}


t_uioptimized *uioptimized_new(t_symbol *s, short argc, t_atom *argv)
{
	t_uioptimized *x = (t_uioptimized *)object_alloc(s_uioptimized_class);
	t_dictionary *d = NULL;

	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;

	if (x) {
		long flags;
		flags = 0
				| JBOX_DRAWFIRSTIN
				//		| JBOX_NODRAWBOX
				//		| JBOX_DRAWINLAST
				| JBOX_TRANSPARENT
				//		| JBOX_NOGROW
				//		| JBOX_GROWY
				| JBOX_GROWBOTH
				//		| JBOX_IGNORELOCKCLICK
				//		| JBOX_HILITE
				//		| JBOX_BACKGROUND
				//		| JBOX_NOFLOATINSPECTOR
				//		| JBOX_TEXTFIELD
				;

		jbox_new(&x->j_box, flags, argc, argv);
		x->j_box.b_firstin = (t_object *) x;

		x->j_rects = NULL;
		x->j_overrect = -1;
		x->j_out = intout((t_object *)x);

		// call this after initializing defaults
		attr_dictionary_process((t_object *)x, d); // handle attribute args

		jbox_ready(&x->j_box);
	}
	return x;
}


void uioptimized_free(t_uioptimized *x)
{
	if (x->j_rects)
		sysmem_freeptr(x->j_rects);
	jbox_free(&x->j_box);
}


/**********************************************************************/
// Methods

void uioptimized_mousemove(t_uioptimized *x, t_object *patcherview, t_pt pt, long modifiers)
{
	t_rect rect;
	long i, last_over = x->j_overrect;
	x->j_overrect = -1;

	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);

	for (i = 0; i < x->j_rectangle; i++) {
		if (	pt.x >= x->j_rects[i].x * rect.width - x->j_rects[i].width * (rect.width * 0.05) &&
				pt.x <= x->j_rects[i].x * rect.width + x->j_rects[i].width * (rect.width * 0.05) &&
				pt.y >= x->j_rects[i].y * rect.height - x->j_rects[i].height * (rect.height * 0.05) &&
				pt.y <= x->j_rects[i].y * rect.height + x->j_rects[i].height * (rect.height * 0.05)) {

			x->j_overrect = i;
			break;
		}
	}

	if (last_over != x->j_overrect) {	// redraw only if it's different
		outlet_int(x->j_out, x->j_overrect);
		jbox_redraw((t_jbox *)x);
	}
}

void uioptimized_mouseleave(t_uioptimized *x, t_object *patcherview, t_pt pt, long modifiers)
{
	x->j_overrect = -1;
	outlet_int(x->j_out, x->j_overrect);
	jbox_redraw((t_jbox *)x);
}

void uioptimized_paint(t_uioptimized *x, t_object *view)
{
	// paint the box grey
	t_rect rect;
	t_jgraphics *g;

	g = (t_jgraphics *) patcherview_get_jgraphics(view);
	jbox_get_rect_for_view((t_object *)x, view, &rect);

	// draw the background rectangles if necessary
	uioptimized_paint_background(x, view, &rect);

	if (x->j_overrect != -1) {
		jgraphics_set_source_jrgba(g, &x->j_overcolor);
		jgraphics_rectangle_fill_fast(g,	x->j_rects[x->j_overrect].x * rect.width - x->j_rects[x->j_overrect].width * (rect.width * 0.05),
									  x->j_rects[x->j_overrect].y * rect.height - x->j_rects[x->j_overrect].height * (rect.height * 0.05),
									  x->j_rects[x->j_overrect].width * (rect.width * 0.1),
									  x->j_rects[x->j_overrect].height * (rect.height * 0.1));
	}
}

void uioptimized_paint_background(t_uioptimized *x, t_object *view, t_rect *rect)
{
	long i;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), rect->width, rect->height);

	if (g) {
		// when the layer has been invalidated using jbox_invalidate_layer, we redraw the contents of the layer
		jgraphics_set_source_jrgba(g, &x->j_rectcolor);	// set the color

		for (i = 0; i < x->j_rectangle; i++) {
			// jgraphics_rectangle_fill_fast() is the antialiased version of jgraphics_rectangle()
			// it's about 40 times faster than jgraphics_rectangle()
			jgraphics_rectangle_fill_fast(g,	x->j_rects[i].x * rect->width - x->j_rects[i].width * (rect->width * 0.05),
										  x->j_rects[i].y * rect->height - x->j_rects[i].height * (rect->height * 0.05),
										  x->j_rects[i].width * (rect->width * 0.1),
										  x->j_rects[i].height * (rect->height * 0.1));
		}
		jbox_end_layer((t_object *)x, view, gensym("background_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), 0., 0.);	// position of the layer
}

t_max_err uioptimized_setattr_rectangle(t_uioptimized *x, void *attr, long ac, t_atom *av)
{
	if (ac && av) {
		long rectangle = atom_getlong(av);
		if (rectangle < 1)
			rectangle = 1;
		if (rectangle > 8192)	// it's slightly more impressive to use power of two ;-)
			rectangle = 8192;

		if (rectangle != x->j_rectangle) {
			long i;

			x->j_rectangle = rectangle;
			if (x->j_rects)
				sysmem_freeptr(x->j_rects);

			x->j_rects = (t_rect *)sysmem_newptr(x->j_rectangle * sizeof(t_rect));
			for (i = 0; i < x->j_rectangle; i++) {
				x->j_rects[i].x = (double)rand() / (double)RAND_MAX;
				x->j_rects[i].y = (double)rand() / (double)RAND_MAX;
				x->j_rects[i].width = (double)rand() / (double)RAND_MAX;
				x->j_rects[i].height = (double)rand() / (double)RAND_MAX;
			}
			jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
		}
	}
	return MAX_ERR_NONE;
}

t_max_err uioptimized_notify(t_uioptimized *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (s == gensym("attr_modified")) {
		t_symbol *name = (t_symbol *)object_method((t_object *)data, gensym("getname"));

		if (name == gensym("rectcolor"))
			jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
	}
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

void uioptimized_assist(t_uioptimized *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)	// inlet
		sprintf(s, "Message in");
	else					// outlet
		sprintf(s, "(int) Index of the Over Rectangle");
}

