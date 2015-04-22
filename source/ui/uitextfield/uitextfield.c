/**
	@file
	uitextfield - demonstrate the textfield with keyboard input

	@ingroup	examples
*/

#include "ext.h"
#include "ext_obex.h"
#include "ext_dictionary.h"
#include "jpatcher_api.h"
#include "jpatcher_syms.h"
#include "jgraphics.h"
#include "ext_boxstyle.h"


/**********************************************************************/
// Data Structures
typedef struct _uitextfield {
	t_jbox				j_box;
	t_jrgba				j_textcolor;
	t_jrgba				j_bgcolor;
} t_uitextfield;


/**********************************************************************/
// Prototypes

t_uitextfield *uitextfield_new(t_symbol *s, short argc, t_atom *argv);
void uitextfield_free(t_uitextfield *x);
void uitextfield_set(t_uitextfield *x, t_symbol *s, long ac, t_atom *av);
void uitextfield_select(t_uitextfield *x);
void uitextfield_doselect(t_uitextfield *x);
void uitextfield_paint(t_uitextfield *x, t_object *view);
long uitextfield_key(t_uitextfield *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
long uitextfield_keyfilter(t_uitextfield *x, t_object *patcherview, long *keycode, long *modifiers, long *textcharacter);
void uitextfield_enter(t_uitextfield *x);
void uitextfield_jsave(t_uitextfield *x, t_dictionary *d);


/**********************************************************************/
// Globals and Statics

static t_class *s_uitextfield_class = NULL;


/**********************************************************************/
// Class Definition and Life Cycle

void ext_main(void *r)
{
	t_class *c;

	jpatcher_syms_init();

	c = class_new("uitextfield",
				  (method)uitextfield_new,
				  (method)uitextfield_free,
				  sizeof(t_uitextfield),
				  (method)NULL,
				  A_GIMME,
				  0L);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_TEXTFIELD | JBOX_FONTATTR | JBOX_FIXWIDTH);	// include textfield and Fonts attributes

	class_addmethod(c, (method)uitextfield_paint,		"paint",		A_CANT, 0);
	class_addmethod(c, (method)uitextfield_key,			"key",			A_CANT, 0);
	class_addmethod(c, (method)uitextfield_keyfilter,	"keyfilter",	A_CANT, 0);
	class_addmethod(c, (method)uitextfield_enter,		"enter",		A_CANT, 0);
	class_addmethod(c, (method)uitextfield_jsave,		"jsave",		A_CANT, 0);
	class_addmethod(c, (method)uitextfield_set,			"anything",		A_GIMME, 0);
	class_addmethod(c, (method)uitextfield_select,		"select",		0);
	class_addmethod(c, (method)jbox_notify,				"notify",		A_CANT, 0);

	CLASS_ATTR_RGBA(c, "textcolor", 0, t_uitextfield, j_textcolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "textcolor", 0, "0. 0. 0. 1.");
	CLASS_ATTR_STYLE_LABEL(c, "textcolor", 0, "rgba", "Text Color");
	CLASS_ATTR_CATEGORY(c, "textcolor", 0, "Color");

	// In Max 6 you would define a background color attribute like this:
	// CLASS_ATTR_RGBA(c, "bgcolor", 0, t_uitextfield, j_bgcolor);
	// CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "0.8 0.8 0.8 1.");
	// CLASS_ATTR_STYLE_LABEL(c, "bgcolor", 0, "rgba", "Background Color");
	// CLASS_ATTR_CATEGORY(c, "bgcolor", 0, "Color");
	//
	// In Max 7 we do this:
	CLASS_ATTR_STYLE_RGBA_PREVIEW(c, "bgcolor", 0, t_uitextfield, j_bgcolor, "Background Color", "rect_fill");
	CLASS_ATTR_BASIC(c, "bgcolor", 0);

	CLASS_ATTR_RGBA(c,			"bgfillcolor", 0, t_uitextfield, j_bgcolor);
	CLASS_ATTR_STYLE_LABEL(c,	"bgfillcolor", 0, "rgba", "Background Color");
	CLASS_ATTR_CATEGORY(c,		"bgfillcolor", 0, "Color");
	CLASS_ATTR_BASIC(c,			"bgfillcolor", 0);
	class_attr_setstyle(c,		"bgfillcolor");
	class_attr_setfill(c,		"bgfillcolor", FILL_ATTR_SAVE);
	CLASS_ATTR_PAINT(c,			"bgfillcolor", 0);
	CLASS_ATTR_ATTR_PARSE(c,	"bgfillcolor", "preview", USESYM(symbol), 0, "rect_fill");	

	CLASS_ATTR_DEFAULT(c, "rect", 0, "0. 0. 100. 20.");

	class_register(CLASS_BOX, c);
	s_uitextfield_class = c;
}


t_uitextfield *uitextfield_new(t_symbol *name, short argc, t_atom *argv)
{
	t_uitextfield *x;
	t_dictionary *d = NULL;

	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_uitextfield *)object_alloc(s_uitextfield_class);
	if (x) {
		long		flags;
		t_object	*textfield;
		t_symbol	*s = NULL;

		flags = 0
				| JBOX_DRAWFIRSTIN
				| JBOX_NODRAWBOX
				| JBOX_DRAWINLAST
				| JBOX_TRANSPARENT
				//		| JBOX_NOGROW
				//		| JBOX_GROWY
				//		| JBOX_GROWBOTH
				//		| JBOX_IGNORELOCKCLICK
				//		| JBOX_HILITE
				//		| JBOX_BACKGROUND
				//		| JBOX_NOFLOATINSPECTOR
				| JBOX_TEXTFIELD
				;

		jbox_new(&x->j_box, flags, argc, argv);
		x->j_box.b_firstin = (t_object *) x;

		textfield = jbox_get_textfield((t_object *) x);
		if (textfield) {
			textfield_set_editonclick(textfield, 1);			// set it to 0 if you don't want user to edit it in lock mode
			textfield_set_textmargins(textfield, 3, 3, 3, 3);	// margin on each side
			textfield_set_textcolor(textfield, &x->j_textcolor);// textcolor
		}
		attr_dictionary_process(x, d);

		// access custom data saved in the patcher by our jsave method
		dictionary_getsym(d, gensym("my_string"), &s);
		if (s)
			object_post((t_object *)x,"custom data saved with patcher: %s", s->s_name);

		jbox_ready(&x->j_box);
	}
	return x;
}

void uitextfield_free(t_uitextfield *x)
{
	jbox_free(&x->j_box);
}

void uitextfield_set(t_uitextfield *x, t_symbol *s, long ac, t_atom *av)
{
	char buff[MAX_FILENAME_CHARS];

	if (ac && av) {
		if (atom_gettype(av) == A_SYM)
			strcpy(buff, atom_getsym(av)->s_name);
		else if (atom_gettype(av) == A_LONG)
			sprintf(buff, "%i", (int)atom_getlong(av));
		else if (atom_gettype(av) == A_FLOAT)
			sprintf(buff, "%f", atom_getfloat(av));
		else {
			object_error((t_object *)x, "bad argument for message set");
			return;
		}
		object_method(jbox_get_textfield((t_object *)x), gensym("settext"), buff);
		jbox_redraw((t_jbox *)x);
	}
}

void uitextfield_select(t_uitextfield *x)
{
	defer(x, (method)uitextfield_doselect, 0, 0, 0);
}

void uitextfield_doselect(t_uitextfield *x)
{
	t_object *p = NULL;
	object_obex_lookup(x,gensym("#P"), &p);
	if (p) {
		t_atom rv;
		long ac = 1;
		t_atom av[1];
		atom_setobj(av, x);
		object_method_typed(p, gensym("selectbox"), ac, av, &rv);
	}
}


long uitextfield_key(t_uitextfield *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
	char buff[256];
	buff[0] = textcharacter;  // we know this is just a simple char
	buff[1] = 0;
	object_method(patcherview, gensym("insertboxtext"), x, buff);
	jbox_redraw((t_jbox *)x);

	return 1;
}

long uitextfield_keyfilter(t_uitextfield *x, t_object *patcherview, long *keycode, long *modifiers, long *textcharacter)
{
	t_atom arv;
	long rv = 1;
	long k = *keycode;

	if (k == JKEY_TAB || k == JKEY_ENTER || k == JKEY_RETURN || k == JKEY_ESC) {
		object_method_typed(patcherview, gensym("endeditbox"), 0, NULL, &arv);
		rv = 0;		// don't pass those keys to uitextfield
	}
	return rv;
}

void uitextfield_enter(t_uitextfield *x)	// enter is triggerd at "endeditbox time"
{
	long size	= 0;
	char *text	= NULL;
	t_object *textfield = jbox_get_textfield((t_object *)x);

	object_method(textfield, gensym("gettextptr"), &text, &size);
	if (size)
		post("This is the new text: %s", text);
}


/**********************************************************************/
// Methods
void uitextfield_bang(t_uitextfield *x)
{
	t_object *textfield = NULL;
	jbox_get_textfield((t_object *)x);
	if (textfield) {
		;
	}
}


void uitextfield_paint(t_uitextfield *x, t_object *view)
{
	t_rect rect;
	t_jgraphics *g;

	g = (t_jgraphics *) patcherview_get_jgraphics(view);

	// set up matrix
	jbox_get_rect_for_view((t_object *) x, view, &rect);

	// soft gray background
	jgraphics_rectangle(g, 0., 0., rect.width, rect.height);
	jgraphics_set_source_jrgba(g, &x->j_bgcolor);
	jgraphics_fill(g);

	// set line width for the corners
	jgraphics_set_line_width(g, 2.);
	jgraphics_set_source_rgba(g, x->j_bgcolor.red * 0.7, x->j_bgcolor.green * 0.7, x->j_bgcolor.blue * 0.7, x->j_bgcolor.alpha * 0.7);

	// draw top left corner
	jgraphics_move_to(g, 1., rect.height - 8.);
	jgraphics_line_to(g, 1., rect.height - 1.);
	jgraphics_line_to(g, 8., rect.height - 1.);
	jgraphics_stroke(g);

	// draw bottom right corner
	jgraphics_move_to(g, rect.width - 8., 1.);
	jgraphics_line_to(g, rect.width - 1., 1.);
	jgraphics_line_to(g, rect.width - 1., 8.);
	jgraphics_stroke(g);
}


// The jsave method is called when the patcher is being saved so that we can add custom data (data that is not an attribute)
// to the patcher dictionary.

void uitextfield_jsave(t_uitextfield *x, t_dictionary *d)
{
	t_object	*textfield = jbox_get_textfield((t_object *)x);
	long		size = 0;
	char		*text = NULL;

	object_method(textfield, gensym("gettextptr"), &text, &size);
	if (size)
		dictionary_appendsym(d, gensym("my_string"), gensym(text));
	else
		dictionary_appendsym(d, gensym("my_string"), gensym(""));
}
