/**
	@file
	iterate2 - object that iterates through a patcher and its subpatchers
	jeremy bernstein - jeremy@bootsquad.com

	@ingroup	examples
*/

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include "jpatcher_api.h"

////////////////////////// object struct
typedef struct _iterate2
{
	t_object					a_ob;			// the object itself (must be first)
	t_symbol					*subpatchername;
} t_iterate2;

///////////////////////// function prototypes
//// standard set
void *iterate2_new(t_symbol *s, long argc, t_atom *argv);
void iterate2_free(t_iterate2 *x);
long iterate2_callback(t_iterate2 *x, t_object *obj);
void iterate2_opensubpatcher(t_iterate2 *x, t_symbol *s);
long iterate2_opensubpatcher_callback(t_iterate2 *x, t_object *obj);
void iterate2_assist(t_iterate2 *x, void *b, long m, long a, char *s);
//// additional methods
void iterate2_bang(t_iterate2 *x); // incoming bang message

//////////////////////// global class pointer variable
void *iterate2_class;

void ext_main(void *r)
{
	t_class *c;

	c = class_new("iterate2", (method)iterate2_new, (method)iterate2_free, (long)sizeof(t_iterate2), 0L, A_GIMME, 0);

	class_addmethod(c, (method)iterate2_bang, "bang", 0);
	class_addmethod(c, (method)iterate2_assist,			"assist",		A_CANT, 0);
	class_addmethod(c, (method)iterate2_opensubpatcher, "open_subpatcher", A_SYM, 0);

	class_register(CLASS_BOX, c);
	iterate2_class = c;

	post("I am the iterate2 object");
}

void iterate2_assist(t_iterate2 *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { //inlet
		sprintf(s, "I am inlet %ld", a);
	}
	else {	// outlet
		sprintf(s, "I am outlet %ld", a);
	}
}

void iterate2_bang(t_iterate2 *x)
{
	t_object *jp;
	t_max_err err;
	long result = 0;

	err = object_obex_lookup(x, gensym("#P"), (t_object **)&jp);
	if (err != MAX_ERR_NONE)
		return;
	object_method(jp, gensym("iterate"), (method)iterate2_callback, x, PI_DEEP | PI_WANTBOX, &result);
}

long iterate2_callback(t_iterate2 *x, t_object *obj)
{
	t_rect jr;
	t_object *p;
	t_symbol *s;

	jbox_get_patching_rect(obj, &jr);
	p = jbox_get_patcher(obj);
	s = jpatcher_get_name(p);
	object_post((t_object *)x, "in %s, box @ x %ld y %ld, w %ld, h %ld", s->s_name, (long)jr.x, (long)jr.y, (long)jr.width, (long)jr.height);
	return 0;
}

void iterate2_opensubpatcher(t_iterate2 *x, t_symbol *s)
{
	t_object *jp;
	t_max_err err;
	long result = 0;

	x->subpatchername = s;

	if (x->subpatchername == gensym(""))
		return;

	err = object_obex_lookup(x, gensym("#P"), (t_object **)&jp);
	if (err != MAX_ERR_NONE)
		return;
	object_method(jp, gensym("iterate"), (method)iterate2_opensubpatcher_callback, x, PI_DEEP | PI_WANTBOX, &result);
}

long iterate2_opensubpatcher_callback(t_iterate2 *x, t_object *obj)
{
	t_object *p;
	t_symbol *s;

	p = jbox_get_patcher(obj);
	s = jpatcher_get_name(p);

	// open the subpatcher if the name matches
	if (x->subpatchername == s)
		typedmess(p, gensym("front"), 0, NULL);	// opens the subpatcher

	return 0;
}

void iterate2_free(t_iterate2 *x)
{
	;
}

void *iterate2_new(t_symbol *s, long argc, t_atom *argv)
{
	t_iterate2 *x = NULL;

	if ((x = (t_iterate2 *)object_alloc(iterate2_class))) {
		x->subpatchername = gensym("");
	}
	return (x);
}
