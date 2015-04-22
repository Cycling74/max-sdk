/**
	@file
	scripto - patcher scripting from C example
	scripto makes a custom UI object and then puts it in a window -- so it is similar to the old "kalim" example

	@ingroup	examples
*/

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include "jpatcher_api.h"
#include "jgraphics.h"

#define SCRIPTO_UI_ROWS 40
#define SCRIPTO_UI_COLS 30
#define SCRIPTO_UI_CELLS (40 * 30)

typedef struct _celldesc {
	long row;
	long col;
	long state;
} t_celldesc;

typedef struct _scripto_ui {
	t_jbox		u_box;
	char		u_state[SCRIPTO_UI_CELLS];
	t_jrgba		u_oncolor;
	t_jrgba		u_offcolor;
	char		u_dragstate;
} t_scripto_ui;

void scripto_ui_classinit(void);
void *scripto_ui_new(t_symbol *s, long argc, t_atom *argv);
void scripto_ui_makerect(t_scripto_ui *x, long row, long col, t_rect *r);
void scripto_ui_pt2rc(t_scripto_ui *x, t_pt pt, long *row, long *col);
void scripto_ui_clear(t_scripto_ui *x);
void scripto_ui_paint(t_scripto_ui *x, t_object *patcherview);
void scripto_ui_mousedown(t_scripto_ui *x, t_object *patcherview, t_pt pt, long modifiers);
void scripto_ui_mousedrag(t_scripto_ui *x, t_object *patcherview, t_pt pt, long modifiers);
void scripto_ui_free(t_scripto_ui *x);


typedef struct _scripto {
	t_object		s_ob;			// the object itself (must be first)
	t_object		*s_patcher;
	t_object		*s_ui;
	t_jrgba			s_oncolor;
	t_jrgba			s_offcolor;
	void			*s_out;
} t_scripto;

void scripto_classinit(void);
void *scripto_new(t_symbol *s, long argc, t_atom *argv);
void scripto_free(t_scripto *x);
long scripto_callback(t_scripto *x, t_object *obj);
void scripto_assist(t_scripto *x, void *b, long m, long a, char *s);
void scripto_bang(t_scripto *x);
t_max_err scripto_setattr_oncolor(t_scripto *x, void *attr, long argc, t_atom *argv);
t_max_err scripto_setattr_offcolor(t_scripto *x, void *attr, long argc, t_atom *argv);
void scripto_dblclick(t_scripto *x);
t_max_err scripto_notify(t_scripto *x, t_symbol *s, t_symbol *msg, void *sender, void *data);


// global class pointers
static t_class	*s_scripto_class;
static t_class	*s_scripto_ui_class;


void ext_main(void *r)
{
	scripto_classinit();		// register our object class
	scripto_ui_classinit();		// now we'll register a secret UI object class
}


/**************************************************************************************************************/
// the scripto object

void scripto_classinit(void)
{
	t_class *c = class_new("scripto", (method)scripto_new, (method)scripto_free, sizeof(t_scripto), 0L, A_GIMME, 0);

	class_addmethod(c, (method)scripto_bang,		"bang",			0);
	class_addmethod(c, (method)scripto_assist,		"assist",		A_CANT, 0);
	class_addmethod(c, (method)scripto_dblclick,	"dblclick",		A_CANT, 0);
	class_addmethod(c, (method)scripto_notify,		"notify",		A_CANT, 0);

	CLASS_ATTR_RGBA(c, "oncolor", 0, t_scripto, s_oncolor);
	CLASS_ATTR_ACCESSORS(c, "oncolor", NULL, scripto_setattr_oncolor);
	// defaults don't work with non-UI objects (an optimization)
	CLASS_ATTR_RGBA(c, "offcolor", 0, t_scripto, s_offcolor);
	CLASS_ATTR_ACCESSORS(c, "offcolor", NULL, scripto_setattr_offcolor);

	class_register(CLASS_BOX, c);

	s_scripto_class = c;
}


void scripto_assist(t_scripto *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)	// inlet
		strcpy(s, "bang Opens Window");
	else	// outlet
		strcpy(s, "Clicked Square");
}

t_max_err scripto_notify(t_scripto *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == gensym("free")) {
		if (sender == x->s_patcher)
			x->s_patcher = NULL;
	}
	else if (msg == gensym("cellclicked")) {
		if (sender == x->s_ui) {
			t_atom argv[3];
			t_celldesc *desc;

			desc = (t_celldesc *)data;
			atom_setlong(argv, desc->row);
			atom_setlong(argv + 1, desc->col);
			atom_setlong(argv + 2, desc->state);
			outlet_list(x->s_out, NULL, 3, argv);
		}
	}
	return 0;
}

// custom attr setter changes colors in UI object

t_max_err scripto_setattr_oncolor(t_scripto *x, void *attr, long argc, t_atom *argv)
{
	if (x->s_ui)
		object_attr_setvalueof(x->s_ui, gensym("oncolor"), argc, argv);
	if (argc >= 4) {
		x->s_oncolor.red = atom_getfloat(argv);
		x->s_oncolor.green = atom_getfloat(argv + 1);
		x->s_oncolor.blue = atom_getfloat(argv + 2);
		x->s_oncolor.alpha = atom_getfloat(argv + 3);
	}
	return 0;
}

t_max_err scripto_setattr_offcolor(t_scripto *x, void *attr, long argc, t_atom *argv)
{
	if (x->s_ui)
		object_attr_setvalueof(x->s_ui, gensym("offcolor"), argc, argv);
	if (argc >= 4) {
		x->s_offcolor.red = atom_getfloat(argv);
		x->s_offcolor.green = atom_getfloat(argv + 1);
		x->s_offcolor.blue = atom_getfloat(argv + 2);
		x->s_offcolor.alpha = atom_getfloat(argv + 3);
	}
	return 0;
}

void scripto_dblclick(t_scripto *x)
{
	if (x->s_patcher)
		object_method(x->s_patcher, gensym("vis"));
	else {
		t_dictionary *d = dictionary_new();
		char parsebuf[256];
		t_atom a;
		long ac = 0;
		t_atom *av = NULL;

		// create a patcher without scroll bars and a toolbar
		sprintf(parsebuf,"@defrect 0 0 300 400 @title scripto @enablehscroll 0 @enablevscroll 0 @presentation 0 @toolbarid \"\"");
		atom_setparse(&ac,&av,parsebuf);
		attr_args_dictionary(d,ac,av);
		atom_setobj(&a,d);
		sysmem_freeptr(av);
		x->s_patcher = (t_object *)object_new_typed(CLASS_NOBOX,gensym("jpatcher"),1, &a);
		freeobject((t_object *)d);	// we created this dictionary and we don't need it anymore

		object_method(x->s_patcher,gensym("vis"));
		x->s_ui = newobject_sprintf(x->s_patcher, "@maxclass scripto_ui @patching_rect 0 0 300 400 @oncolor %.2f %.2f %.2f %.2f @offcolor %.2f %.2f %.2f %.2f",
									x->s_oncolor.red, x->s_oncolor.green, x->s_oncolor.blue, x->s_oncolor.alpha, x->s_offcolor.red, x->s_offcolor.green, x->s_offcolor.blue, x->s_offcolor.alpha);
		object_attach_byptr_register(x, x->s_ui, CLASS_BOX);			// attach our UI object to us
		object_attach_byptr_register(x, x->s_patcher, CLASS_NOBOX);		// attach our UI object to us
	}
}

void scripto_bang(t_scripto *x)
{
	defer(x, (method)scripto_dblclick, 0, 0, 0);
}

void scripto_free(t_scripto *x)
{
	if (x->s_patcher)
		object_free(x->s_patcher);
}

void *scripto_new(t_symbol *s, long argc, t_atom *argv)
{
	t_scripto *x = NULL;

	x = (t_scripto *)object_alloc(s_scripto_class);

	x->s_patcher = NULL;
	x->s_ui = NULL;
	x->s_oncolor.red = x->s_oncolor.green = x->s_oncolor.blue = 0.8;
	x->s_oncolor.alpha = 1.;
	x->s_offcolor.red = x->s_offcolor.green = x->s_offcolor.blue = 0.2;
	x->s_offcolor.alpha = 1.;
	x->s_out = listout((t_object *)x);
	return x;
}


/**************************************************************************************************************/
// the secret scripto_ui object

void scripto_ui_classinit(void)
{
	t_class *c = class_new("scripto_ui", (method)scripto_ui_new, (method)scripto_ui_free, sizeof(t_scripto_ui), 0L, A_GIMME, 0L);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;

	jbox_initclass(c, 0);
	class_addmethod(c, (method)scripto_ui_paint,	"paint",		A_CANT, 0);
	class_addmethod(c, (method)scripto_ui_mousedown,"mousedown",	A_CANT, 0);
	class_addmethod(c, (method)scripto_ui_mousedrag,"mousedrag",	A_CANT, 0);
	class_addmethod(c, (method)jbox_notify,			"notify",	A_CANT, 0);		// for auto-repainting

	CLASS_ATTR_RGBA(c, "oncolor", 0, t_scripto_ui, u_oncolor);
	CLASS_ATTR_PAINT(c, "oncolor", 0);
	CLASS_ATTR_RGBA(c, "offcolor", 0, t_scripto_ui, u_offcolor);
	CLASS_ATTR_PAINT(c, "offcolor", 0);

	class_register(CLASS_BOX, c);

	s_scripto_ui_class = c;
}


void *scripto_ui_new(t_symbol *s, long argc, t_atom *argv)
{
	t_scripto_ui *x = NULL;
	t_max_err err = MAX_ERR_GENERIC;
	t_dictionary *d;
	long flags;

	if (!(d=object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_scripto_ui *) object_alloc(s_scripto_ui_class);
	flags = 0
			| JBOX_DRAWFIRSTIN
			//		| JBOX_NODRAWBOX
			| JBOX_DRAWINLAST
			| JBOX_TRANSPARENT
			//		| JBOX_NOGROW
			//		| JBOX_GROWY
			| JBOX_GROWBOTH
			//		| JBOX_HILITE
			//		| JBOX_BACKGROUND
			//		| JBOX_TEXTFIELD
			| JBOX_DRAWBACKGROUND
			;

	err = jbox_new(&x->u_box, flags, argc, argv);

	x->u_box.b_firstin = (t_object *) x;

	scripto_ui_clear(x);
	attr_dictionary_process(x, d);
	jbox_ready(&x->u_box);

	return x;
}

void scripto_ui_clear(t_scripto_ui *x)
{
	long i;

	for (i = 0; i < SCRIPTO_UI_CELLS; i++)
		x->u_state[i] = 0;
}

void scripto_ui_paint(t_scripto_ui *x, t_object *patcherview)
{
	t_jgraphics *g;
	t_rect r;
	long i, j;

	g = (t_jgraphics *) patcherview_get_jgraphics(patcherview);
	for (i = 0; i < SCRIPTO_UI_ROWS; i++) {
		for (j = 0; j < SCRIPTO_UI_COLS; j++) {
			scripto_ui_makerect(x, i, j, &r);
			jgraphics_set_source_jrgba(g, x->u_state[(i * SCRIPTO_UI_COLS) + j]? &x->u_oncolor : &x->u_offcolor);
			jgraphics_rectangle_fill_fast(g, r.x, r.y, r.width, r.height);
		}
	}
}

void scripto_ui_makerect(t_scripto_ui *x, long row, long col, t_rect *r)
{
	r->y = row * 10;
	r->x = col * 10;
	r->width = 10;
	r->height = 10;
}

void scripto_ui_pt2rc(t_scripto_ui *x, t_pt pt, long *row, long *col)
{
	*row = CLAMP(pt.y / 10, 0, SCRIPTO_UI_ROWS-1);
	*col = CLAMP(pt.x / 10, 0, SCRIPTO_UI_COLS-1);
}

void scripto_ui_mousedown(t_scripto_ui *x, t_object *patcherview, t_pt pt, long modifiers)
{
	long row, col, index;
	t_celldesc desc;

	scripto_ui_pt2rc(x, pt, &row, &col);
	index = (row * SCRIPTO_UI_COLS) + col;
	x->u_dragstate = !x->u_state[index];
	x->u_state[index] = x->u_dragstate;
	desc.row = row;
	desc.col = col;
	desc.state = x->u_dragstate;
	object_notify((t_object *)x, gensym("cellclicked"), (void *)&desc);
	jbox_redraw((t_jbox *)x);
}

void scripto_ui_mousedrag(t_scripto_ui *x, t_object *patcherview, t_pt pt, long modifiers)
{
	long row, col, index;
	char state;

	scripto_ui_pt2rc(x, pt, &row, &col);
	index = (row * SCRIPTO_UI_COLS) + col;
	state = x->u_state[index];
	if (state != x->u_dragstate) {		// optimization: only redraw if state is changing
		x->u_state[index] = x->u_dragstate;
		jbox_redraw((t_jbox *)x);
	}
}

void scripto_ui_free(t_scripto_ui *x)
{
	jbox_free((t_jbox *)x);
}
