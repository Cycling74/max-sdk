/**
	@file
	sheep - demonstrates object registration and notification, and some hashtab techniques
			for use with the "shepherd" object
	jeremy bernstein - jeremy@bootsquad.com

	@ingroup	examples
*/

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include "jpatcher_api.h"

////////////////////////// object struct
typedef struct _sheep
{
	t_object					ob;			// the object itself (must be first)
	t_symbol					*myobjname;
} t_sheep;

///////////////////////// function prototypes
//// standard set
void *sheep_new(t_symbol *s, long argc, t_atom *argv);
void sheep_free(t_sheep *x);
void sheep_assist(t_sheep *x, void *b, long m, long a, char *s);
void sheep_notify(t_sheep *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void sheep_baah(t_sheep *x);
void sheep_shepherd_moved(t_sheep *x);

//////////////////////// global class pointer variable
void *sheep_class;


void ext_main(void *r)
{
	t_class *c;

	c = class_new("sheep", (method)sheep_new, (method)sheep_free, (long)sizeof(t_sheep),
				  0L, A_GIMME, 0);

	class_addmethod(c, (method)sheep_baah,				"baah",				0);

	/* you CAN'T call this from the patcher */
	class_addmethod(c, (method)sheep_shepherd_moved,	"shepherd_moved",	A_CANT,	0);
	class_addmethod(c, (method)sheep_assist,			"assist",			A_CANT, 0);

	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	sheep_class = c;
}

void sheep_shepherd_moved(t_sheep *x)
{
	object_post((t_object *)x, "Oh, no! The shepherd!!!");
}

void sheep_baah(t_sheep *x)
{
	// send the notification "sheep" to any object which is listening
	object_notify(x, gensym("sheep"), NULL);
}

void sheep_assist(t_sheep *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // inlet
		sprintf(s, "I am inlet %ld", a);
	}
	else {	// outlet
		sprintf(s, "I am outlet %ld", a);
	}
}

void sheep_free(t_sheep *x)
{
	t_object *jp;

	object_obex_lookup(x, gensym("#P"), &jp); // get the object's patcher
	if (jp) {
		t_hashtab *ht;

		// find the sheephash
		object_obex_lookup(jp, gensym("sheephash"), (t_object **)&ht);
		if (ht) {
			hashtab_chuckkey(ht, x->myobjname); // remove self from hashtab
		}
	}
}

void *sheep_new(t_symbol *s, long argc, t_atom *argv)
{
	t_sheep *x = NULL;
	t_object *jp = NULL;

	if ((x = (t_sheep *)object_alloc(sheep_class))) {
		jp = (t_object *)gensym("#P")->s_thing;
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
			// cache the registered name so we can remove self from hashtab
			x = object_register(CLASS_BOX, x->myobjname = symbol_unique(), x);
			// store self in the hashtab. IMPORTANT: set the OBJ_FLAG_REF flag so that the
			// hashtab knows not to free us when it is freed.
			hashtab_storeflags(ht, x->myobjname, (t_object *)x, OBJ_FLAG_REF);
		}
	}
	return (x);
}