/**
	@file
	master - demonstrates object subscription, registration and notification, use with 'servant'
	jeremy bernstein - jeremy@cycling74.com

	@ingroup	examples
*/

#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"

////////////////////////// object struct
typedef struct _master
{
	t_object					ob;			// the object itself (must be first)
	t_object					*conduit;
} t_master;

typedef struct _conduit
{
	t_object					ob;
	long						usagecount;
} t_conduit;

///////////////////////// function prototypes
void *master_new(t_symbol *s);
void master_free(t_master *x);
void master_assist(t_master *x, void *b, long m, long a, char *s);
void master_notify(t_master *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void master_bang(t_master *x);
void master_int(t_master *x, long n);
void master_float(t_master *x, double f);
void master_anything(t_master *x, t_symbol *s, long ac, t_atom *av);

void *conduit_new(t_symbol *name);
void conduit_free(t_conduit *x);
void conduit_retain(t_conduit *x);
void conduit_release(t_conduit *x);


//////////////////////// global class pointer variable
t_class *master_class;
t_class *conduit_class;

static t_symbol *ps_nothing;
static t_symbol *ps_conduit;

void ext_main(void *r)
{
	t_class *c;

	// Create the "master" class. This is roughly equivalent to the 'send' object in Max.
	// It takes a single symbolic argument and sends messages on to 'servant' objects with the same name.
	c = class_new("master", (method)master_new, (method)master_free, sizeof(t_master), 0L, A_SYM, 0);

	class_addmethod(c, (method)master_bang,				"bang",			0);
	class_addmethod(c, (method)master_int,				"int",			A_LONG, 0);
	class_addmethod(c, (method)master_float,			"float",		A_FLOAT, 0);
	class_addmethod(c, (method)master_anything,			"list",			A_GIMME, 0);

	class_addmethod(c, (method)master_anything,			"anything",		A_GIMME, 0);

	class_addmethod(c, (method)master_assist,			"assist",		A_CANT, 0);
	class_addmethod(c, (method)master_notify,			"notify",		A_CANT, 0);

	class_register(CLASS_BOX, c);
	master_class = c;

	// Create the "conduit" class. This class is actually responsible for the communication
	// with the 'servant' objects, and we need it in order to support multiple 'master' objects
	// sending to one or several 'servant' objects.
	c = class_new("conduit", (method)conduit_new, (method)conduit_free, sizeof(t_conduit), 0L, A_CANT, 0);

	class_addmethod(c, (method)conduit_retain,			"retain", 0);
	class_addmethod(c, (method)conduit_release,			"release", 0);

	class_register(CLASS_NOBOX, c);
	conduit_class = c;

	ps_nothing = gensym("");
	ps_conduit = gensym("conduit");
}

void master_bang(t_master *x)
{
	master_anything(x, gensym("bang"), 0, NULL);
}

void master_int(t_master *x, long n)
{
	t_atom a;

	atom_setlong(&a, n);
	master_anything(x, gensym("int"), 1, &a);
}

void master_float(t_master *x, double f)
{
	t_atom a;

	atom_setfloat(&a, f);
	master_anything(x, gensym("float"), 1, &a);
}

void master_anything(t_master *x, t_symbol *s, long ac, t_atom *av)
{
	t_atomarray *aa = NULL;
	t_atom *argv = NULL;
	long argc = 0;
	char alloc;

	if (atom_alloc_array(ac + 1, &argc, &argv, &alloc) == MAX_ERR_NONE) {
		atom_setsym(argv, s);
		sysmem_copyptr(av, argv + 1, sizeof(t_atom) * ac);
		aa = atomarray_new(argc, argv);
		if (aa) {
			object_notify(x->conduit, gensym("sendmessage"), aa);
			object_free(aa);
		}
		sysmem_freeptr(argv);
	}
}

void master_notify(t_master *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == gensym("free")) {
		// the conduit is going away, this would be fatal, but will never actually happen
	}
}

void master_assist(t_master *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // inlet
		sprintf(s, "Messages for my sweet servant");
	}
	else {	// outlets, of which we have none...
		sprintf(s, "I am outlet %ld", a);
	}
}

void master_free(t_master *x)
{
	// tell the conduit that we are finished with it. When the number of
	// users drops to 0, the conduit self-destructs to avoid leaking memory.
	object_method(x->conduit, gensym("release"));
}

void *master_new(t_symbol *s)
{
	t_master *x = NULL;

	if ((x = (t_master *)object_alloc(master_class))) {
		t_object *conduit;

		// check and see if there is already a named conduit for this 'master'
		conduit = object_findregistered(ps_conduit, s);
		if (!conduit) {
			// no? let's create one and register it under this object's name
			object_new(CLASS_NOBOX, ps_conduit, s);
			conduit = object_findregistered(ps_conduit, s);
		}
		if (conduit) {
			x->conduit = conduit;
			// tell the conduit that we are using it
			object_method(conduit, gensym("retain"));
		}
	}
	return (x);
}

//////////////////////////////////////////////////////////

void conduit_retain(t_conduit *x)
{
	x->usagecount++;
}

void conduit_release(t_conduit *x)
{
	x->usagecount--;
	if (x->usagecount <= 0) { // commit suicide
		object_free(x);
	}
}

void conduit_free(t_conduit *x)
{
	object_unregister(x);
}

void *conduit_new(t_symbol *name)
{
	t_conduit *x = NULL;

	if (name && name != ps_nothing) {
		x = (t_conduit *)object_alloc(conduit_class);
		if (x) {
			x->usagecount = 0;
			object_register(ps_conduit, name, x);
		}
	}
	return x;
}
