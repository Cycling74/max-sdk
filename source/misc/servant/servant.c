/**
	@file
	servant - demonstrates object subscription, registration and notification, use with 'master'
	jeremy bernstein - jeremy@cycling74.com

	@ingroup	examples
*/

#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"

////////////////////////// object struct
typedef struct _servant
{
	t_object					ob;			// the object itself (must be first)
	t_symbol					*name;
	void						*out;
} t_servant;

///////////////////////// function prototypes
void *servant_new(t_symbol *s);
void servant_free(t_servant *x);
void servant_assist(t_servant *x, void *b, long m, long a, char *s);
void servant_notify(t_servant *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

//////////////////////// global class pointer variable
t_class *servant_class;

static t_symbol *ps_nothing;
static t_symbol *ps_conduit;

void ext_main(void *r)
{
	t_class *c;

	c = class_new("servant", (method)servant_new, (method)servant_free, sizeof(t_servant), 0L, A_DEFSYM, 0);

	class_addmethod(c, (method)servant_notify,			"notify",			A_CANT, 0);
	class_addmethod(c, (method)servant_assist,			"assist",			A_CANT, 0);

	// the servant has no inlet
	// adding a 'set' message is left as an exercise for the reader
	c->c_noinlet = true;

	class_register(CLASS_BOX, c);
	servant_class = c;

	ps_nothing = gensym("");
	ps_conduit = gensym("conduit");
}

void servant_notify(t_servant *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	object_post((t_object *)x, "servant_notify: %s", msg->s_name);
	if (msg == gensym("free")) {
		// the conduit is disappearing, no more servers
		// but we remain subscribed, so there's nothing to do here
		// if a new master appears, we will be called with 'subscribe_attach'
		// and automatically be attached.
	} else if (msg == gensym("sendmessage")) { // the conduit is calling with a message from 'master'
		t_atomarray *aa = (t_atomarray *)data;

		outlet_anything(x->out, atom_getsym(aa->av), aa->ac - 1, aa->av + 1);
	}
}

void servant_assist(t_servant *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // inlets, of which we have none...
		sprintf(s, "I am inlet %ld", a);
	}
	else {	// outlet
		sprintf(s, "Messages received from my dark master %s", x->name->s_name);
	}
}

void servant_free(t_servant *x)
{
	// be neat and unsubscribe
	object_unsubscribe(ps_conduit, x->name, ps_conduit, x);
}

void *servant_new(t_symbol *s)
{
	t_servant *x = NULL;

	if (s && s != ps_nothing) {
		x = (t_servant *)object_alloc(servant_class);
		if (x) {
			// subscribe to this name in the conduit namespace
			// we will be automatically notified and attached when the server appears
			// (or simply attached if it's already there)
			// the third arg to object_subscribe limits the classes I want to hear from
			// in this example, it's not really necessary, because we're using a custom
			// namespace ("conduit"), but if you're listening for things like buffers in
			// Max's box namespace, you'd want to create such a filter.
			object_subscribe(ps_conduit, s, ps_conduit, x);
			x->name = s;
			x->out = outlet_new(x, NULL);
		}
	}
	return (x);
}