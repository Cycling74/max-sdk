/**
	@file
	howbigisyourp - object that iterates through a patcher and its subpatchers and count the number of objects
	emmanuel jourdan

	@ingroup	examples
*/

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include "jpatcher_api.h"

////////////////////////// object struct
typedef struct _howbigisyourp
{
	t_object					a_ob;			// the object itself (must be first)
	t_symbol					*subpatchername;
	t_hashtab					*hash;
	void						*out;
} t_howbigisyourp;

typedef struct _an_item
{
	t_symbol					*name;
	long						val;
} t_an_item;

///////////////////////// function prototypes
//// standard set
void *howbigisyourp_new(t_symbol *s, long argc, t_atom *argv);
void howbigisyourp_free(t_howbigisyourp *x);
void howbigisyourp_dump(t_howbigisyourp *x);
void howbigisyourp_cp_to_linklist(t_hashtab_entry *e, void *list);
long howbigisyourp_callback(t_howbigisyourp *x, t_object *obj);
void howbigisyourp_assist(t_howbigisyourp *x, void *b, long m, long a, char *s);
//// additional methods
void howbigisyourp_bang(t_howbigisyourp *x); // incoming bang message

t_an_item *an_item_new(t_symbol *s, long items);

//////////////////////// global class pointer variable
void *howbigisyourp_class;

void ext_main(void *r)
{
	t_class *c;

	c = class_new("howbigisyourp", (method)howbigisyourp_new, (method)howbigisyourp_free, (long)sizeof(t_howbigisyourp), 0L, A_GIMME, 0);

	class_addmethod(c, (method)howbigisyourp_bang,		"bang",		0);
	class_addmethod(c, (method)howbigisyourp_assist,	"assist",	A_CANT, 0);
	class_addmethod(c, (method)howbigisyourp_dump,		"dump",		0);

	class_register(CLASS_BOX, c);
	howbigisyourp_class = c;
}

void howbigisyourp_assist(t_howbigisyourp *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { //inlet
		sprintf(s, "bang, dump");
	}
	else {	// outlet
		sprintf(s, "(list) {Classname instances}");
	}
}

void howbigisyourp_bang(t_howbigisyourp *x)
{
	t_object *jp;
	t_max_err err;
	long result = 0;

	hashtab_clear(x->hash);

	err = object_obex_lookup(x, gensym("#P"), (t_object **)&jp);
	if (err != MAX_ERR_NONE)
		return;

	// iterate through every objects
	if (jp)
		object_method(jp, gensym("iterate"), (method)howbigisyourp_callback, x, PI_DEEP | PI_WANTBOX, &result);
}

long howbigisyourp_callback(t_howbigisyourp *x, t_object *obj)
{
	long numberofinstances = 1;
	t_symbol *name = object_classname(obj);

	// if it's a newobj, get the "real" name (e.g. borax)
	if (name == gensym("newobj"))
		name = object_classname(jbox_get_object(obj));

	if (name) {
		t_object *obj;

		// if the object was already in the hashtable, increment the number of instances
		if (hashtab_lookup(x->hash, name, &obj) == MAX_ERR_NONE)
			numberofinstances = (long)obj + 1;

		// write the number of instances in the hashtable
		hashtab_store(x->hash, name, (t_object *)numberofinstances);
	}

	return 0;
}

void howbigisyourp_free(t_howbigisyourp *x)
{
	hashtab_clear(x->hash);
}

long linklist_ascending(void *a, void *b)
{
	t_an_item *item1 = a;
	t_an_item *item2 = b;

	if (item1->val < item2->val)
		return true;
	else
		return false;
}

void howbigisyourp_dump(t_howbigisyourp *x)
{
	t_an_item *item;
	t_atom a;
	t_linklist *list = linklist_new();
	linklist_flags(list, OBJ_FLAG_MEMORY);	// will use sysmem_freeptr on the objects

	// first item of list contains the totalnumberofobjects
	item = an_item_new(gensym("totalnumberofobjects"), 0);
	linklist_append(list, item);

	// copy the hash table to a linklist, and count the total number of object
	hashtab_funall(x->hash, (method)howbigisyourp_cp_to_linklist, list);

	// get the first item totalnumberofobjects which now contains the total number of objects
	item = linklist_getindex(list, 0);
	post("The total number of objects is %d", item->val);
	linklist_deleteindex(list, 0);	// remove it so we can proceed

	// sorting is nicer
	linklist_sort(list, linklist_ascending);

	// iterate through the linklist and output {name, instances} out the outlet.
	item = linklist_getindex(list, 0);
	while (item) {
		atom_setlong(&a, item->val);
		outlet_anything(x->out, item->name, 1, &a);
		linklist_next(list, item, (void **)&item);
	}

	// free the linklist items, the hashtab items are not removed).
	if (list)
		object_free(list);
}

void howbigisyourp_cp_to_linklist(t_hashtab_entry *e, void *list)
{
	if (e->key && e->value) {
		t_an_item *item = an_item_new(e->key, (long)e->value);	// copy the object name and the number of instances to the linklist
		linklist_append(list, item);

		item = linklist_getindex(list, 0);	// that's totalnumberofobjects
		item->val += (long)e->value;		// increment the totalnumberofobjects by the number of instances of this object
	}
}

t_an_item *an_item_new(t_symbol *s, long items)
{
	t_an_item *x = (t_an_item *)sysmem_newptr(sizeof(t_an_item));
	x->name = s;
	x->val = items;
	return (x);
}

void *howbigisyourp_new(t_symbol *s, long argc, t_atom *argv)
{
	t_howbigisyourp *x = NULL;

	if ((x = (t_howbigisyourp *)object_alloc(howbigisyourp_class))) {
		x->subpatchername = gensym("");
		x->out = outlet_new(x, NULL);
		x->hash = hashtab_new(0);
		hashtab_flags(x->hash, OBJ_FLAG_DATA);
	}
	return (x);
}
