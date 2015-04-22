/**
	@file
	shepherd - demonstrates object registration and notification, and some hashtab techniques
			for use with the "sheep" object
	jeremy bernstein - jeremy@bootsquad.com

	@ingroup	examples
*/

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include "jpatcher_api.h"

////////////////////////// object struct
typedef struct _shepherd
{
	t_object					ob;			// the object itself (must be first)
	t_hashtab					*ht;
} t_shepherd;

///////////////////////// function prototypes
//// standard set
void *shepherd_new(t_symbol *s, long argc, t_atom *argv);
void shepherd_free(t_shepherd *x);
void shepherd_assist(t_shepherd *x, void *b, long m, long a, char *s);
void shepherd_notify(t_shepherd *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void shepherd_detach_obj(t_hashtab_entry *e, void *arg);
void shepherd_detach(t_shepherd *x);
void shepherd_attach_obj(t_hashtab_entry *e, void *arg);
void shepherd_attach(t_shepherd *x);
void shepherd_boo(t_shepherd *x);

//////////////////////// global class pointer variable
void *shepherd_class;


void ext_main(void *r)
{
	t_class *c;

	c = class_new("shepherd", (method)shepherd_new, (method)shepherd_free, (long)sizeof(t_shepherd),
				  0L, A_GIMME, 0);

	class_addmethod(c, (method)shepherd_boo,			"boo", 0);
	class_addmethod(c, (method)shepherd_assist,			"assist",		A_CANT, 0);
	class_addmethod(c, (method)shepherd_notify,			"notify",		A_CANT, 0);

	class_register(CLASS_BOX, c);
	shepherd_class = c;
}

void shepherd_boo(t_shepherd *x)
{
	// call the "shepherd_moved" method of every object in the hashtable
	hashtab_methodall(x->ht, gensym("shepherd_moved"));
}

void shepherd_notify(t_shepherd *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == gensym("sheep")) {
		object_post((t_object *)x, "sheep!!!");
	} else if (msg == gensym("hashtab_entry_new")) { // something arrived in the hashtab
		t_symbol *key = (t_symbol *)data;
		t_object *obj = NULL;

		hashtab_lookup(sender, key, &obj);
		if (obj) // we could verify that it's a sheep object with 'if (object_classname(obj) == gensym("sheep"))'
			object_attach_byptr(x, obj); // attach to it
		object_post((t_object *)x, "Oh joy! I have %ld sheep to tend.", hashtab_getsize(sender));
	} else if (msg == gensym("hashtab_entry_free")) { // something left the hashtab
		t_symbol *key = (t_symbol *)data;
		t_object *obj = NULL;

		hashtab_lookup(sender, key, &obj);
		if (obj)
			object_detach_byptr(x, obj); // detach from it
		// we receive the notification before the entry is removed from the hashtable
		if (hashtab_getsize(sender) > 1) {
			object_post((t_object *)x, "Oh untimely death! Only %ld sheep left.", hashtab_getsize(sender) - 1);
		} else {
			object_post((t_object *)x, "Oh inconsolable sadness! My sheep are gone...");
		}
	}
}

void shepherd_assist(t_shepherd *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // inlet
		sprintf(s, "I am inlet %ld", a);
	}
	else {	// outlet
		sprintf(s, "I am outlet %ld", a);
	}
}

void shepherd_detach_obj(t_hashtab_entry *e, void *arg)
{
	t_shepherd *x = (t_shepherd *)arg;
	if (x) {
		// detach from the object, it's going away...
		object_detach_byptr(x, e->value);
	}
}

void shepherd_detach(t_shepherd *x)
{
	if (x->ht) {
		hashtab_funall(x->ht, (method)shepherd_detach_obj, x);
		object_detach_byptr(x, x->ht); // detach from the hashtable
	}
}

void shepherd_attach_obj(t_hashtab_entry *e, void *arg)
{
	t_shepherd *x = (t_shepherd *)arg;
	if (x) {
		// attach to the object to receive its notifications
		object_attach_byptr(x, e->value);
	}
}

void shepherd_attach(t_shepherd *x)
{
	t_object *jp;

	object_obex_lookup(x, gensym("#P"), &jp); // get the object's patcher
	if (jp) {
		t_hashtab *ht;

		// look in the jpatcher's obex for an object called "sheephash"
		object_obex_lookup(jp, gensym("sheephash"), (t_object **)&ht);
		if (!ht) {
			// it's not there? create it.
			ht = hashtab_new(0);
			// objects stored in the obex will be freed when the obex's owner is freed
			// in this case, when the patcher object is freed. so we don't need to
			// manage the memory associated with the "sheephash".
			object_obex_store(jp, gensym("sheephash"), (t_object *)ht);
		}
		x->ht = ht;
		// attach to the hashtab, registering it if necessary
		// this way, we can receive notifications from the hashtab as things are added and removed
		object_attach_byptr_register(x, x->ht, CLASS_NOBOX);
		// call a method on every object in the hash table
		hashtab_funall(x->ht, (method)shepherd_attach_obj, x);
		if (hashtab_getsize(x->ht)) {
			object_post((t_object *)x, "I, the shepherd, have %ld sheep to tend! What joy!", hashtab_getsize(x->ht));
		} else {
			object_post((t_object *)x, "I, the shepherd, have no sheep to tend. Whatever shall I do?");
		}
	}
}

void shepherd_free(t_shepherd *x)
{
	// detach from all of our sheep, and the hashtable
	shepherd_detach(x);
}

void *shepherd_new(t_symbol *s, long argc, t_atom *argv)
{
	t_shepherd *x = NULL;

	// object instantiation, NEW STYLE
	if ((x = (t_shepherd *)object_alloc(shepherd_class))) {
		shepherd_attach(x); // attach to every object in the hashtab + the hashtab
	}
	return (x);
}
