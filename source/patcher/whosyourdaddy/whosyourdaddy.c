/**
	@file
	whosyourdaddy - who's the parent patcher
	jeremy bernstein - jeremy@bootsquad.com

	@ingroup	examples
*/

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include "ext_strings.h"
#include "jpatcher_api.h"

////////////////////////// object struct
typedef struct _whosyourdaddy
{
	t_object					a_ob;			// the object itself (must be first)
} t_whosyourdaddy;

///////////////////////// function prototypes
//// standard set
void *whosyourdaddy_new(t_symbol *s, long argc, t_atom *argv);
void whosyourdaddy_free(t_whosyourdaddy *x);
void whosyourdaddy_assist(t_whosyourdaddy *x, void *b, long m, long a, char *s);
//// additional methods
void whosyourdaddy_bang(t_whosyourdaddy *x); // incoming bang message

//////////////////////// global class pointer variable
void *whosyourdaddy_class;

void ext_main(void *r)
{
	t_class *c;

	c = class_new("whosyourdaddy", (method)whosyourdaddy_new, (method)whosyourdaddy_free, (long)sizeof(t_whosyourdaddy), 0L, A_GIMME, 0);

	class_addmethod(c, (method)whosyourdaddy_bang, "bang", 0);
	class_addmethod(c, (method)whosyourdaddy_assist,			"assist",		A_CANT, 0);

	class_register(CLASS_BOX, c);
	whosyourdaddy_class = c;
}

void whosyourdaddy_assist(t_whosyourdaddy *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { //inlet
		snprintf_zero(s, 256, "I am inlet %ld", a);
	}
	else {	// outlet
		snprintf_zero(s, 256, "I am outlet %ld", a);
	}
}

void whosyourdaddy_bang(t_whosyourdaddy *x)
{
	t_object *jp;
	t_object *jbx;
	t_object *o;
	t_max_err err;

	// get the object's parent patcher
	err = object_obex_lookup(x, gensym("#P"), (t_object **)&jp);
	if (err != MAX_ERR_NONE)
		return;

	// some kind of patcher in a box
	if ((jbx = jpatcher_get_box(jp))) {
		t_symbol *filepath = object_attr_getsym((t_object *)jp, gensym("filepath"));

//		post("object_classname(jbx): %s, object_classname(o): %s, filepath: %s", object_classname(jbx)->s_name, object_classname(jbox_get_object(jbx))->s_name, filepath->s_name);
		if (object_classname(jbx) == gensym("bpatcher")) {
			post("bpatcher");
		} else {
			if (filepath && filepath != gensym("")) {
				post("abstraction");
			} else {
				post("subpatcher");
			}
		}
	} else {
		t_object *p2 = NULL;
		t_object *target = NULL;
		t_object *nextbox;
		method m;

		object_method(jp, gensym("getassoc"), &target);
		if (target) {
			if ((m = zgetfn(target, gensym("parentpatcher"))))
				(*m)(target, &p2);
			if (p2) {
				nextbox = jpatcher_get_firstobject(p2);
				while (nextbox) {
					o = jbox_get_object(nextbox);
					if (o == target) {
						post("%s", object_classname(o)->s_name);
						return;
					}
					nextbox = jbox_get_nextobject(nextbox);
				}
			}
		}
	}
}

void whosyourdaddy_free(t_whosyourdaddy *x)
{
}

void *whosyourdaddy_new(t_symbol *s, long argc, t_atom *argv)
{
	t_whosyourdaddy *x = NULL;

	if ((x = (t_whosyourdaddy *)object_alloc(whosyourdaddy_class))) {
	}
	return (x);
}
