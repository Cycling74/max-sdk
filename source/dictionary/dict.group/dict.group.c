#include "ext.h"
#include "ext_obex.h"
#include "ext_strings.h"
#include "ext_dictobj.h"


typedef struct _dict_group {
	t_object		obj;
	void			*outlet_dict;
	t_symbol		*name;			// symbol mapped to the dictionary
	t_dictionary	*dictionary;	// the actual dictionary
} t_dict_group;


// prototypes
void *dict_group_new(t_symbol *s, long argc, t_atom *argv);
void dict_group_free(t_dict_group *x);
void dict_group_assist(t_dict_group *x, void *b, long m, long a, char *s);
void dict_group_bang(t_dict_group *x);
void dict_group_anything(t_dict_group *x, t_symbol *s, long argc, t_atom *argv);
void dict_group_list(t_dict_group *x, t_symbol *s, long argc, t_atom *argv);
void dict_group_setname(t_dict_group *x, void *attr, long argc, t_atom *argv);


// class statics/globals
static t_class	*s_dict_group_class;
t_symbol *ps_name;
static t_symbol *ps_modified;
static t_symbol *ps_dictionary;


/************************************************************************************/
void ext_main(void *r)
{
	t_class	*c = class_new("dict.group", (method)dict_group_new, (method)dict_group_free, sizeof(t_dict_group), (method)NULL, A_GIMME, 0);

	class_addmethod(c, (method)dict_group_anything, 	"anything", 	A_GIMME, 0);
	class_addmethod(c, (method)dict_group_list,			"list",			A_GIMME, 0);
	class_addmethod(c, (method)dict_group_bang,			"bang", 		0);
	class_addmethod(c, (method)dict_group_assist,		"assist",		A_CANT, 0);
	class_addmethod(c, (method)stdinletinfo,			"inletinfo",	A_CANT, 0);

	CLASS_ATTR_SYM(c,			"name",			0, t_dict_group, name);
	CLASS_ATTR_ACCESSORS(c,		"name",			NULL, dict_group_setname);
	CLASS_ATTR_CATEGORY(c,		"name",			0, "Dictionary");
	CLASS_ATTR_LABEL(c,			"name",			0, "Name");
	CLASS_ATTR_BASIC(c,			"name",			0);

	class_register(CLASS_BOX, c);
	s_dict_group_class = c;

	ps_name = gensym("name");
	ps_modified = gensym("modified");
	ps_dictionary = gensym("dictionary");
}


/************************************************************************************/

void *dict_group_new(t_symbol *s, long argc, t_atom *argv)
{
	t_dict_group	*x = (t_dict_group *)object_alloc(s_dict_group_class);
	long			attrstart = attr_args_offset(argc, argv);
	t_symbol		*name = NULL;

	if (x) {
		if (attrstart && atom_gettype(argv) == A_SYM)
			name = atom_getsym(argv);

		x->outlet_dict = outlet_new(x, "dictionary");
		x->dictionary = dictionary_new();

		attr_args_process(x, argc, argv);
		if (!x->name) {
			if (name)
				object_attr_setsym(x, ps_name, name);
			else
				object_attr_setsym(x, ps_name, symbol_unique());
		}
	}
	return x;
}


void dict_group_free(t_dict_group *x)
{
	object_free((t_object *)x->dictionary); // will call object_unregister
}


/************************************************************************************/
void dict_group_assist(t_dict_group *x, void *b, long m, long a, char *s)
{
	if (m==ASSIST_INLET) {
		strcpy(s, "dictionary syntax for appending a key/value pair, bang sends the dictionary and resets");
	}
	else if (m==ASSIST_OUTLET) {
		switch (a) {
		case 0: strcpy(s, "dictionary output"); break;
		}
	}
}


void dict_group_bang(t_dict_group *x)
{
	if (x->name) {
		t_atom	a[1];

		atom_setsym(a, x->name);
		outlet_anything(x->outlet_dict, ps_dictionary, 1, a);
		dictionary_clear(x->dictionary);
	}
}


void dict_group_anything(t_dict_group *x, t_symbol *s, long argc, t_atom *argv)
{
	// if there is a colon in the first two atoms, then we use dictionary syntax
	// otherwise we just append the atoms as simple values

	if (strrchr(s->s_name, ':') || (atom_gettype(argv) == A_SYM && strchr(atom_getsym(argv)->s_name, ':')) || argc >= 1) {
		t_dictionary	*dp = NULL;	// dictionary with our 'prototype' specified by args to this object
		long			numkeys = 0;
		t_symbol		**keys = NULL;
		int				i;
		long			argc_extended = argc+1;
		t_atom			*argv_extended = (t_atom *)sysmem_newptr(sizeof(t_atom) * (argc_extended+1));

		atom_setsym(argv_extended, s);
		if (!(strrchr(s->s_name, ':') || (atom_gettype(argv) == A_SYM && atom_getsym(argv)->s_name[0] == ':'))) {
			// no colon, so we take s to be the key (and append the colon to it for parsing)
			argc_extended++;
			atom_setsym(argv_extended+1, gensym(":"));
			sysmem_copyptr(argv, argv_extended+2, sizeof(t_atom) * argc);
		}
		else
			sysmem_copyptr(argv, argv_extended+1, sizeof(t_atom) * argc);

		dictobj_dictionaryfromatoms(&dp, argc_extended, argv_extended);
		if (dp) {
			dictionary_getkeys_ordered(dp, &numkeys, &keys);
			if (keys) {
				for (i=0; i<numkeys; i++) {
					long	ac = 0;
					t_atom	*av = NULL;

					dictionary_deleteentry(x->dictionary, keys[i]);
					dictionary_getatoms(dp, keys[i], &ac, &av);
					if (ac > 1)
						dictionary_appendatoms(x->dictionary, keys[i], ac, av);
					else {
						if (atom_gettype(av) == A_LONG)
							dictionary_appendlong(x->dictionary, keys[i], atom_getlong(av));
						else if (atom_gettype(av) == A_FLOAT)
							dictionary_appendfloat(x->dictionary, keys[i], atom_getfloat(av));
						else if (atom_gettype(av) == A_SYM)
							dictionary_appendsym(x->dictionary, keys[i], atom_getsym(av));
						else
							object_error((t_object *)x, "unknown atom type");
					}
				}
				sysmem_freeptr(keys);
			}
			object_free(dp);
		}
		else {
			object_error((t_object *)x, "could not create dictionary from args");
		}

		sysmem_freeptr(argv_extended);
		return;
	}
	else {
		object_error((t_object *)x, "messages must contain at least 2 items (a key and a value)");
		return;
	}

	// not using dictionary syntax, just append the atoms

	dictionary_deleteentry(x->dictionary, s);
	if (argc > 1)
		dictionary_appendatoms(x->dictionary, s, argc, argv);
	else {
		if (atom_gettype(argv) == A_LONG)
			dictionary_appendlong(x->dictionary, s, atom_getlong(argv));
		else if (atom_gettype(argv) == A_FLOAT)
			dictionary_appendfloat(x->dictionary, s, atom_getfloat(argv));
		else if (atom_gettype(argv) == A_SYM)
			dictionary_appendsym(x->dictionary, s, atom_getsym(argv));
		else
			object_error((t_object *)x, "unknown atom type");
	}
	object_notify(x->dictionary, ps_modified, NULL);
}


void dict_group_list(t_dict_group *x, t_symbol *s, long argc, t_atom *argv)
{
	if (argc) {
		if (atom_gettype(argv) == A_SYM)
			dict_group_anything(x, atom_getsym(argv), argc-1, argv+1);
		else if (atom_gettype(argv) == A_LONG) {
			char str[32];

			snprintf_zero(str, 32, "%ld", atom_getlong(argv));
			dict_group_anything(x, gensym(str), argc-1, argv+1);
		}
		else if (atom_gettype(argv) == A_FLOAT) {
			char str[32];

			snprintf_zero(str, 32, "%f", atom_getfloat(argv));
			dict_group_anything(x, gensym(str), argc-1, argv+1);
		}
		else
			object_error((t_object *)x, "unknown atom type received as first element of list");
	}
}


void dict_group_setname(t_dict_group *x, void *attr, long argc, t_atom *argv)
{
	t_symbol		*name = atom_getsym(argv);

	if (!x->name || !name || x->name!=name) {
		object_free(x->dictionary); // will call object_unregister
		x->dictionary = dictionary_new();
		x->dictionary = dictobj_register(x->dictionary, &name);
		x->name = name;
	}
	if (!x->dictionary)
		object_error((t_object *)x, "could not create dictionary named %s", name->s_name);
}

