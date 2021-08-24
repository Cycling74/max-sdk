/**
	@file
	uires - demonstrate the use of resources

	@ingroup	examples
*/

#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"
#include "jgraphics.h"


/**********************************************************************/
// Data Structures

typedef struct _uires {
	t_jbox				j_box;
	char				j_clicked;
	char				j_hover;
	t_jsurface			*j_idrewitmyself;
	t_jsurface			*j_idrewitmyselftongue;
} t_uires;


/**********************************************************************/
// Prototypes

void uires_initclass();
t_uires *uires_new(t_symbol *s, short argc, t_atom *argv);
void uires_free(t_uires *x);
void uires_load_surfaces(t_uires *x);
t_jsurface * uires_load_surface_from_name(t_uires *, char *name);

void uires_setmouse(t_uires *x, long which);
void uires_mousedown(t_uires *x, t_object *patcherview, t_pt pt, long modifiers);
void uires_mouseup(t_uires *x, t_object *patcherview, t_pt pt, long modifiers);
void uires_mouseenter(t_uires *x, t_object *patcherview, t_pt pt, long modifiers);
void uires_mouseleave(t_uires *x, t_object *patcherview, t_pt pt, long modifiers);

void uires_paint(t_uires *x, t_object *view);


/**********************************************************************/
// Globals and Statics

static t_class *s_uires_class = NULL;


/**********************************************************************/
// Class Definition and Life Cycle

void ext_main(void *moduleRef)
{
	t_class *c;

	c = class_new("uires",
				  (method)uires_new,
				  (method)uires_free,
				  sizeof(t_uires),
				  (method)NULL,
				  A_GIMME,
				  0L);

	jbox_initclass(c, 0);

	class_addmethod(c, (method) uires_mousedown,		"mousedown", A_CANT, 0);
	class_addmethod(c, (method) uires_mouseup,			"mouseup", A_CANT, 0);
	class_addmethod(c, (method) uires_mouseenter,		"mouseenter", A_CANT, 0);
	class_addmethod(c, (method) uires_mouseleave,		"mouseleave", A_CANT, 0);
	class_addmethod(c, (method) uires_paint,			"paint", A_CANT, 0);

	CLASS_ATTR_DEFAULT(c, "rect", 0, "0. 0. 150. 150.");

	class_register(CLASS_BOX, c);
	s_uires_class = c;
}


t_uires *uires_new(t_symbol *s, short argc, t_atom *argv)
{
	t_uires *x = (t_uires *)object_alloc(s_uires_class);

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
				| JBOX_HILITE
				//		| JBOX_BACKGROUND
				//		| JBOX_NOFLOATINSPECTOR
				//		| JBOX_TEXTFIELD
				;

		jbox_new(&x->j_box, flags, argc, argv);
		x->j_box.b_firstin = (t_object *) x;
		
		// find the images in the search path, and load them.
		uires_load_surfaces(x);

		jbox_ready(&x->j_box);
	}
	return x;
}


void uires_load_surfaces(t_uires *x)
{
	if (x->j_idrewitmyself == NULL) {
		x->j_idrewitmyself = uires_load_surface_from_name(x, "idrewitmyself.png");
	}
	if (x->j_idrewitmyselftongue == NULL) {
		x->j_idrewitmyselftongue = uires_load_surface_from_name(x, "idrewitmyselftongue.png");
	}
}

t_jsurface * uires_load_surface_from_name(t_uires *x, char *name)
{
	short path;
	t_fourcc outtype;
	char filename[MAX_FILENAME_CHARS];

	strncpy_zero(filename, name, MAX_FILENAME_CHARS);
	if (!locatefile_extended(filename, &path, &outtype, NULL, 0)) {
		// found the image, get the t_jsurface* from the file
		return jgraphics_image_surface_create_from_file(filename, path);
	} else {
		object_warn((t_object *)x, "Couldn't locate image (%s)", name);
		return NULL;
	}
}

void uires_free(t_uires *x)
{
	if (x->j_idrewitmyself) {
		jgraphics_surface_destroy(x->j_idrewitmyself);
		x->j_idrewitmyself = NULL;
	}
	if (x->j_idrewitmyselftongue) {
		jgraphics_surface_destroy(x->j_idrewitmyselftongue);
		x->j_idrewitmyselftongue = NULL;
	}
	jbox_free(&x->j_box);
}


/**********************************************************************/
// Methods
void uires_mousedown(t_uires *x, t_object *patcherview, t_pt pt, long modifiers)
{
	x->j_clicked = true;
	jbox_redraw((t_jbox *)x);
}

void uires_mouseup(t_uires *x, t_object *patcherview, t_pt pt, long modifiers)
{
	x->j_clicked = false;
	jbox_redraw((t_jbox *)x);
}

void uires_mouseenter(t_uires *x, t_object *patcherview, t_pt pt, long modifiers)
{
	x->j_hover = true;
	jbox_redraw((t_jbox *)x);
}

void uires_mouseleave(t_uires *x, t_object *patcherview, t_pt pt, long modifiers)
{
	x->j_hover = false;
	jbox_redraw((t_jbox *)x);
}

void uires_paint(t_uires *x, t_object *view)
{
	// paint the box grey
	t_rect rect;
	t_jgraphics *g;

	g = (t_jgraphics *) patcherview_get_jgraphics(view);

	// set up matrix
	jbox_get_rect_for_view((t_object *) x, view, &rect);

	jgraphics_set_source_rgba(g, 0, 0, 0, 1);
	if (x->j_idrewitmyself && x->j_idrewitmyselftongue) {
		t_rect src, dst;

		src.x = src.y = 0.;
		src.width = jgraphics_image_surface_get_width(x->j_idrewitmyself);		// we know that both images
		src.height = jgraphics_image_surface_get_height(x->j_idrewitmyself);	// have the same dimensions.

		dst.x = dst.y = 0.;
		dst.width = rect.width;
		dst.height = rect.height;

		if (x->j_clicked)
			jgraphics_image_surface_draw(g, x->j_idrewitmyselftongue, src, dst);
		else
			jgraphics_image_surface_draw(g, x->j_idrewitmyself, src, dst);
	}

	if (x->j_hover) {
		jgraphics_set_source_rgba(g, 1., 1., 1., 1.);
		jgraphics_arc(g, rect.width * 0.53, rect.height * 0.4, rect.width * 0.015, 0, JGRAPHICS_2PI);
		jgraphics_fill(g);
		jgraphics_arc(g, rect.width * 0.54, rect.height * 0.5, rect.width * 0.015, 0, JGRAPHICS_2PI);
		jgraphics_fill(g);
		jgraphics_arc(g, rect.width * 0.54, rect.height * 0.6, rect.width * 0.015, 0, JGRAPHICS_2PI);
		jgraphics_fill(g);
	}
}
