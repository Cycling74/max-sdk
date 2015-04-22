/**
	@file
	uisimp - a very simple ui object - step 7

	@ingroup	examples
*/

#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"
#include "jgraphics.h"


t_class	*s_uisimp_class = 0;

enum {
	EXAMP_SQUARE = 0,
	EXAMP_CIRCLE,
	EXAMP_ANGLE
};

typedef struct _uisimp
{
	t_jbox		j_box;
	long		j_mouse_is_down;
	int			j_mouse_counter;
	long		j_inset;
	char		j_reset;
	long		j_shape;
	char		j_has_focus;
	t_pt		j_absolute_position;
} t_uisimp;



void uisimp_assist(t_uisimp *x, void *b, long m, long a, char *s);
t_uisimp *uisimp_new(t_symbol *s, long argc, t_atom *argv);
void uisimp_int(t_uisimp *x, long n);
void uisimp_free(t_uisimp *x);

void uisimp_paint(t_uisimp *x, t_object *view);

void uisimp_mousedragdelta(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers);
void uisimp_mousedown(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers);
void uisimp_mouseup(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers);
void uisimp_getdrawparams(t_uisimp *x, t_object *patcherview, t_jboxdrawparams *params);
long uisimp_key(t_uisimp *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
void uisimp_focusgained(t_uisimp *x, t_object *patcherview);
void uisimp_focuslost(t_uisimp *x, t_object *patcherview);
long uisimp_hittest(t_uisimp *x, t_object *patcherview, t_pt pt);

void uisimp_bang(t_uisimp *x);




void ext_main(void *r)
{
	t_class *c;

	c = class_new("uisimp5",
				  (method)uisimp_new,
				  (method)uisimp_free,
				  sizeof(t_uisimp),
				  (method)NULL,
				  A_GIMME,
				  0L);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;

	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);

	class_addmethod(c, (method) uisimp_paint, "paint", A_CANT, 0);
	class_addmethod(c, (method) uisimp_int, "int", A_LONG, 0);

	class_addmethod(c, (method) uisimp_mousedown, "mousedown", A_CANT, 0);
	class_addmethod(c, (method) uisimp_mousedragdelta, "mousedragdelta", A_CANT, 0);
	class_addmethod(c, (method) uisimp_mouseup, "mouseup", A_CANT, 0);
	class_addmethod(c, (method) uisimp_getdrawparams, "getdrawparams", A_CANT, 0);
	class_addmethod(c, (method) uisimp_hittest, "hittest", A_CANT, 0);

	class_addmethod(c, (method) uisimp_key, "key", A_CANT, 0);
	class_addmethod(c, (method) uisimp_focusgained, "focusgained", A_CANT, 0);
	class_addmethod(c, (method) uisimp_focuslost, "focuslost", A_CANT, 0);

	class_addmethod(c, (method) uisimp_assist, "assist", A_CANT, 0);
	class_addmethod(c, (method) jbox_notify, "notify", A_CANT, 0);

	CLASS_ATTR_DEFAULT(c, "patching_rect", 0, "0 0 60 60");
	CLASS_ATTR_DEFAULT(c, "color", 0, "0.8 0.5 0.2 1");

	CLASS_ATTR_LONG(c,"inset",0, t_uisimp, j_inset);
	CLASS_ATTR_LABEL(c,"inset",0,"Filled Area Inset");
	CLASS_ATTR_CATEGORY(c,"inset",0,"Tweaks");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"inset",0,"3");

	CLASS_ATTR_CHAR(c,"reset",0, t_uisimp, j_reset);
	CLASS_ATTR_STYLE_LABEL(c,"reset",0,"onoff","Reset Counter on Click");
	CLASS_ATTR_CATEGORY(c,"reset",0,"Tweaks");
	CLASS_ATTR_DEFAULT_SAVE(c,"reset",0,"1");

	CLASS_ATTR_LONG(c,"shape",0, t_uisimp, j_shape);
	CLASS_ATTR_LABEL(c,"shape", 0, "Fill Shape");
	CLASS_ATTR_CATEGORY(c,"shape",0,"Shape");
	CLASS_ATTR_ENUMINDEX(c,"shape", 0, "Square Circle Angle");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"shape",0,"0");

	s_uisimp_class = c;
	class_register(CLASS_BOX, s_uisimp_class);
	return 0;
}

void uisimp_assist(t_uisimp *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s,"bang Says \"bang\"");
}


t_uisimp *uisimp_new(t_symbol *s, long argc, t_atom *argv)
{
	t_uisimp *x = NULL;
	t_max_err err = MAX_ERR_GENERIC;
	t_dictionary *d;
	long flags;

	if (!(d=object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_uisimp *) object_alloc(s_uisimp_class);
	flags = 0
			| JBOX_DRAWFIRSTIN
			//		| JBOX_NODRAWBOX
			| JBOX_DRAWINLAST
			| JBOX_TRANSPARENT
			//		| JBOX_NOGROW
			//		| JBOX_GROWY
			| JBOX_GROWBOTH
			| JBOX_HILITE
			//		| JBOX_BACKGROUND
			//		| JBOX_TEXTFIELD
			| JBOX_DRAWBACKGROUND
			| JBOX_MOUSEDRAGDELTA
			;

	err = jbox_new(&x->j_box, flags, argc, argv);

	x->j_box.b_firstin = (t_object *) x;

	attr_dictionary_process(x, d);
	jbox_ready(&x->j_box);

	return x;
}

void uisimp_int(t_uisimp *x, long n)
{
	x->j_mouse_counter = n;
	jbox_redraw((t_jbox *)x);
}

void uisimp_free(t_uisimp *x)
{
	jbox_free(&x->j_box);
}

void uisimp_paint(t_uisimp *x, t_object *view)
{
	t_jgraphics *g;
	t_rect rect;
	t_jrgba rgba, textcolor;
	t_jfont *jf;
	t_jtextlayout *jtl;
	char text[16];
	long inset = x->j_inset;

	g = (t_jgraphics *) patcherview_get_jgraphics(view);
	jbox_get_rect_for_view(&x->j_box.b_ob, view, &rect);

	if (x->j_shape == EXAMP_SQUARE)
		jgraphics_rectangle(g, inset, inset, rect.width - (inset * 2), rect.height - (inset * 2));
	else if (x->j_shape == EXAMP_CIRCLE) {
		jgraphics_arc(g, rect.width * .5, rect.height * .5, (rect.width * .5) - (inset * 2), 0, JGRAPHICS_2PI);
		jgraphics_close_path(g);
	} else if (x->j_shape == EXAMP_ANGLE) {
		jgraphics_move_to(g, inset * 2, inset);
		jgraphics_line_to(g, rect.width - (inset * 2), inset);
		jgraphics_line_to(g, rect.width - (inset * 2), inset * 2);
		jgraphics_line_to(g, rect.width - (inset * 2), rect.height - (inset * 2));
		jgraphics_line_to(g, rect.width - (inset * 2), rect.height - inset);
		jgraphics_line_to(g, inset * 2, rect.height - (inset * 2));
		jgraphics_line_to(g, inset, rect.height - (inset * 3));
		jgraphics_line_to(g, inset, inset * 2);
		jgraphics_line_to(g, inset * 2, inset);
		jgraphics_close_path(g);
	}

	if (x->j_mouse_is_down) {
		jbox_get_color((t_object *)x, &rgba);
		jgraphics_set_source_jrgba(g, &rgba);
	} else
		jgraphics_set_source_rgba(g, 0, 0, 0, 1.0);
	jgraphics_fill(g);
	// draw counter
	jf = jfont_create(jbox_get_fontname((t_object *)x)->s_name, jbox_get_font_slant((t_object *)x), jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));
	jtl = jtextlayout_create();
	sprintf(text,"%d",x->j_mouse_counter);

	jtextlayout_set(jtl, text, jf, 5, 5, rect.width - 10, rect.height- 10, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, JGRAPHICS_TEXTLAYOUT_NOWRAP);
	textcolor.red = textcolor.green = textcolor.blue = 1;
	textcolor.alpha = 1;
	jtextlayout_settextcolor(jtl, &textcolor);
	jtextlayout_draw(jtl, g);
	jtextlayout_destroy(jtl);
	jfont_destroy(jf);
}

void uisimp_getdrawparams(t_uisimp *x, t_object *patcherview, t_jboxdrawparams *params)
{
	if (x->j_has_focus) {
		params->d_bordercolor.red = 1;
		params->d_bordercolor.green = 0;
		params->d_bordercolor.blue = 0;
		params->d_bordercolor.alpha = 1;
		params->d_borderthickness = 2.;
	}
}

void uisimp_bang(t_uisimp *x)
{
	object_post((t_object *)x, "bang!");
}

void uisimp_mousedragdelta(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
	rect.x += pt.x;
	rect.y += pt.y;
	jbox_set_rect_for_view((t_object *)x, patcherview, &rect);
}

void uisimp_mousedown(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers)
{
	x->j_absolute_position = pt;

	x->j_mouse_is_down = true;
	if (x->j_reset)
		x->j_mouse_counter = 0;
	jbox_redraw((t_jbox *)x);
}

void uisimp_mouseup(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers)
{
	t_rect rect;
	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
	jmouse_setposition_view(patcherview, rect.x + x->j_absolute_position.x, rect.y + x->j_absolute_position.y);
	x->j_mouse_is_down = false;
	jbox_redraw((t_jbox *)x);
}

long uisimp_key(t_uisimp *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
	switch (textcharacter) {
	case '+':
		x->j_mouse_counter++;
		jbox_redraw((t_jbox *)x);
		break;
	case '-':
		x->j_mouse_counter--;
		jbox_redraw((t_jbox *)x);
		break;
	}

	return 0;	// returns 1 if you want to filter it from the key object
}

void uisimp_focusgained(t_uisimp *x, t_object *patcherview)
{
	post("You can now press \"+\" or \"-\"");
	x->j_has_focus = true;
	jbox_redraw((t_jbox *)x);
}

void uisimp_focuslost(t_uisimp *x, t_object *patcherview)
{
	post("You have lost the keyboard focus.");
	x->j_has_focus = false;
	jbox_redraw((t_jbox *)x);
}

long uisimp_hittest(t_uisimp *x, t_object *patcherview, t_pt pt)
{
	t_rect	rect;
	long	rv = 1;	// 1 means that we will respond to user clicks

	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);

	if (pt.x < rect.width / 2) {
		rv = 0;		// setting to 0 means that we will not response to user clicks
		// and thus we will pass the click to any objects layered beneath our object
	}
	return rv;
}

