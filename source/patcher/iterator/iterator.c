/**
	@file
	iterator - patch iterator
	jeremy bernstein - jeremy@bootsquad.com

	@ingroup	examples
*/

#include "ext.h"					// standard Max include, always required
#include "ext_obex.h"				// required for new style Max object
#include "jpatcher_api.h"

////////////////////////// object struct
typedef struct _iterator
{
	t_object	a_ob;				// the object itself (must be first)
	t_object	*a_patcher;			// pointer to our patcher
	t_object	*a_patcherview;		// pointer to our first patcherview
	t_pt		a_cached;
} t_iterator;

///////////////////////// function prototypes
//// standard set
void *iterator_new(t_symbol *s, long argc, t_atom *argv);
void iterator_free(t_iterator *x);
void iterator_assist(t_iterator *x, void *b, long m, long a, char *s);
//// additional methods
void iterator_bang(t_iterator *x); // incoming bang message
void iterator_notify(t_iterator *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void iterator_attach(t_iterator *x);

//////////////////////// global class pointer variable
void *iterator_class;

void ext_main(void *r)
{
	t_class *c;

	c = class_new("iterator", (method)iterator_new, (method)iterator_free, sizeof(t_iterator), 0L, A_GIMME, 0);

	class_addmethod(c, (method)iterator_bang,		"bang",			0);
	class_addmethod(c, (method)iterator_assist,		"assist",		A_CANT, 0);
	class_addmethod(c, (method)iterator_notify,		"notify",		A_CANT, 0);

	class_register(CLASS_BOX, c);
	iterator_class = c;

	post("I am the iterator object");
}

void iterator_assist(t_iterator *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { //inlet
		sprintf(s, "I am inlet %ld", a);
	}
	else {	// outlet
		sprintf(s, "I am outlet %ld", a);
	}
}

void iterator_bang(t_iterator *x)
{
	t_object *jp;
	t_object *jb;
	t_object *mybox;
	t_object *o;
	t_rect jr;
	t_symbol *scriptingname;
	t_max_err err;

	// get the object's parent patcher
	err = object_obex_lookup(x, gensym("#P"), (t_object **)&jp);
	if (err != MAX_ERR_NONE)
		return;

	// get the object's wrapping box
	err = object_obex_lookup(x, gensym("#B"), (t_object **)&mybox);
	if (err != MAX_ERR_NONE)
		return;

	jb = jpatcher_get_firstobject(jp); // get the first BOX in the object list

	while(jb) {
		jbox_get_patching_rect(jb, &jr); // x, y, width, height (double)

		object_post((t_object *)x, "found an object at %ld %ld, w %ld, h %ld", (long)jr.x, (long)jr.y, (long)jr.width, (long)jr.height);

		scriptingname = jbox_get_varname(jb); // scripting name
		if (scriptingname && scriptingname != gensym(""))
			object_post((t_object *)x, " it is named %s...", scriptingname->s_name);

		o = jbox_get_object(jb); // get the box's object (b_firstin in Max4)
		post(" it's a(n) %s object...", object_classname(o)->s_name);

		if (jpatcher_is_patcher(o)) {
			post(" which is some kind of a patcher. we could recurse here...");
		}

		if (jb == mybox)
			post(" ...and it's me!");

		jb = jbox_get_nextobject(jb); // iterate
	}

	// jbox_get_patcher(abox); // get a box's patcher

	// maybe upwards? jpatcher_get_parentpatcher(<#t_object * p#>)
}

void iterator_notify(t_iterator *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
//	post("got %s message from %X (%s)", msg->s_name, sender, s->s_name);
	if (msg == gensym("attr_modified") && sender == x->a_patcherview) { // sent when an attribute of the sender changes
		t_symbol *attrname;

		// 'data' arg is the modified attribute object
		// get its name:
		attrname = (t_symbol *)object_method(data, gensym("getname"));
		post("'%s' attribute was modified", attrname->s_name);

		if (attrname == gensym("rect")) {
			t_atom *av = NULL;
			long ac = 0;

			object_attr_getvalueof(sender, attrname, &ac, &av);
			if (ac && av) {
				t_object *jb;

				post("new rect: %ld %ld %ld %ld", atom_getlong(av), atom_getlong(av+1), atom_getlong(av+2), atom_getlong(av+3));
				object_obex_lookup(x, gensym("#B"), &jb);
				if (jb) {
					t_atom *rv = NULL;
					long rc = 0;

					object_attr_getvalueof(jb, gensym("patching_rect"), &rc, &rv);
					if (rc && rv) {
						// we have box rect
						// compare cached view size to current view
						long dx = atom_getlong(av+2) - x->a_cached.x;
						long dy = atom_getlong(av+3) - x->a_cached.y;
						long boxw = atom_getlong(rv+2);
						long boxh = atom_getlong(rv+3);

						// recache new size
						x->a_cached.x = atom_getlong(av+2);
						x->a_cached.y = atom_getlong(av+3);

						// modify my box width
						atom_setlong(rv+2, boxw + dx);
						// (height is ignored by jnewobj)
						atom_setlong(rv+3, boxh + dy);
						object_attr_setvalueof(jb, gensym("patching_rect"), rc, rv);
						freebytes(rv, sizeof(t_atom) * rc);
					}
				}
				freebytes(av, sizeof(t_atom) * ac);
			}
		}

	}

}

void iterator_free(t_iterator *x)
{
	t_object *jp = NULL;
	t_object *pv;

	// detach from any objects that you have attached to.
	object_obex_lookup(x, gensym("#P"), &jp);
	if (jp) {
		pv = jpatcher_get_firstview(jp);
		object_detach_byptr(x, pv);
	}
}

void *iterator_new(t_symbol *s, long argc, t_atom *argv)
{
	t_iterator *x = NULL;

	if ((x = (t_iterator *)object_alloc(iterator_class))) {

		// Get a pointer to our patcher
		object_obex_lookup(x, gensym("#P"), &x->a_patcher);

		// The patcherview is not available when the object is created as a patcher is being read from disk,
		// so we have to defer to wait for it before getting it and attaching for notifications.
		defer_low(x, (method)iterator_attach, NULL, 0, NULL);
	}
	return (x);
}

void iterator_attach(t_iterator *x)
{
	t_atom *av = NULL;
	long ac = 0;

	x->a_patcherview = object_attr_getobj(x->a_patcher, gensym("firstview"));
	object_attach_byptr_register(x, x->a_patcherview, CLASS_NOBOX);

	// get the bounds of the first patcherview and cache them
	object_attr_getvalueof(x->a_patcherview, gensym("rect"), &ac, &av);
	if (ac && av) {
		x->a_cached.x = atom_getfloat(av+2); // width
		x->a_cached.y = atom_getfloat(av+3); // height
		freebytes(av, sizeof(t_atom) * ac); // or sysmem_freeptr()
	}
}
