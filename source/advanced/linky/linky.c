/**
	@file
	linky - Demonstrates functions of the #t_linklist object..

	@ingroup		examples

	Copyright 2010 - Cycling '74
	Timothy Place, tim@cycling74.com
*/

#include "ext.h"
#include "ext_obex.h"


// Data Structures
typedef struct _linky {
	t_object	l_obj;
	t_linklist	*l_list;
	void		*l_outlet;
} t_linky;


// Prototypes
t_linky	*linky_new(t_symbol *s, long argc, t_atom *argv);
void		linky_free(t_linky *x);
void		linky_append(t_linky *x, t_symbol *s, long argc, t_atom *argv);
void		linky_deleteindex(t_linky *x, long index);
void		linky_post(t_linky *x);
void		linky_reverse(t_linky *x);

// Globals and Statics
static t_class	*s_linky_class = NULL;


/**********************************************************************/
// Class Definition and Life Cycle

void ext_main(void *r)
{
	t_class *c;

	c = class_new("linky", (method)linky_new, (method)linky_free, sizeof(t_linky), (method)NULL, A_GIMME, 0L);

	class_addmethod(c, (method)linky_append,		"append", A_GIMME, 0);
	class_addmethod(c, (method)linky_deleteindex,	"deleteindex", A_LONG, 0);
	class_addmethod(c, (method)linky_post,			"post", 0);
	class_addmethod(c, (method)linky_reverse,		"reverse", 0);

	class_register(CLASS_BOX, c);
	s_linky_class = c;
}


t_linky *linky_new(t_symbol *s, long argc, t_atom *argv)
{
	t_linky	*x = (t_linky *)object_alloc(s_linky_class);

	if (x) {
		x->l_list = linklist_new();
		linklist_flags(x->l_list, OBJ_FLAG_MEMORY);		// <-- use sysmem_freeptr() to free items in the list
		x->l_outlet = outlet_new(x, 0L);
		attr_args_process(x, argc, argv);
	}
	return x;
}


void linky_free(t_linky *x)
{
	object_free(x->l_list);
}


/**********************************************************************/
// Methods


void linky_append(t_linky *x, t_symbol *s, long argc, t_atom *argv)
{
	int i;

	// for each argument to the 'append' message...
	for (i=0; i<argc; i++) {
		t_atom *a = (t_atom *)sysmem_newptr(sizeof(t_atom));	// allocate memory for a new atom to put on the list

		memcpy(a, argv+i, sizeof(t_atom));					// copy the value of the atom to our newly allocated atom
		linklist_append(x->l_list, a);						// push the pointer onto the list

		// the memory will be freed when the item is removed from the list because we set the flag for this in our new method.
	}
}


void linky_deleteindex(t_linky *x, long index)
{
	long deleted_index;

	deleted_index = linklist_deleteindex(x->l_list, index);
	if (deleted_index < 0)
		object_error((t_object *)x, "deleteindex failed");
}


void linky_post_one(t_atom *a, t_linky *x)
{
	switch (a->a_type) {
	case A_LONG:
		object_post((t_object *)x, "post: %ld", atom_getlong(a));
		break;
	case A_FLOAT:
		object_post((t_object *)x, "post: %f", atom_getfloat(a));
		break;
	case A_SYM:
		object_post((t_object *)x, "post: %s", atom_getsym(a)->s_name);
		break;
	default:
		object_post((t_object *)x, "cannot post -- unknown type");
		break;
	}
}


void linky_post(t_linky *x)
{
	linklist_funall(x->l_list, (method)linky_post_one, x);
}


void linky_reverse(t_linky *x)
{
	linklist_reverse(x->l_list);
}

