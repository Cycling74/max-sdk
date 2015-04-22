#include "ext.h"
#include "ext_obex.h"
#include "ext_strings.h"
#include "ext_dictobj.h"

#define MAX_NUM_ITEMS 256


typedef struct _dict_strip {
	t_object	obj;
	void		*outlet_keyvals;
	void		*outlet_dict;
	t_symbol	*keys[MAX_NUM_ITEMS];
	long		numkeys;
	t_symbol	*name;
} t_dict_strip;


// prototypes
void *dict_strip_new(t_symbol *s, long argc, t_atom *argv);
void dict_strip_free(t_dict_strip *x);
void dict_strip_assist(t_dict_strip *x, void *b, long m, long a, char *s);
void dict_strip_bang(t_dict_strip *x);
void dict_strip_dictionary(t_dict_strip *x, t_symbol *s);


// class statics/globals
static t_class	*s_dict_strip_class;
static t_symbol	*ps_dictionary;
static t_symbol *ps_modified;


/************************************************************************************/
void ext_main(void *r)
{
	t_class	*c = class_new("dict.strip", (method)dict_strip_new, (method)dict_strip_free, sizeof(t_dict_strip), (method)NULL, A_GIMME, 0);

	class_addmethod(c, (method)dict_strip_dictionary, 	"dictionary", 	A_SYM, 0);
	// class_addmethod(c, (method)dict_strip_bang, 		"bang", 		0);
	class_addmethod(c, (method)dict_strip_assist,		"assist",		A_CANT, 0);

	CLASS_ATTR_SYM_VARSIZE(c,	"keys",		0, t_dict_strip, keys, numkeys, MAX_NUM_ITEMS);
	CLASS_ATTR_CATEGORY(c,		"keys",		0, "Dictionary");
	CLASS_ATTR_LABEL(c,			"keys",		0, "Keys");
	CLASS_ATTR_BASIC(c,			"keys",		0);

	class_register(CLASS_BOX, c);
	s_dict_strip_class = c;
	
	ps_dictionary = gensym("dictionary");
	ps_modified = gensym("modified");
}


/************************************************************************************/
void *dict_strip_new(t_symbol *s, long argc, t_atom *argv)
{
	t_dict_strip 	*x;
	long			attrstart = attr_args_offset(argc, argv);

	x = (t_dict_strip *)object_alloc(s_dict_strip_class);
	if (x) {
		x->outlet_keyvals = outlet_new(x, 0L);
		x->outlet_dict = outlet_new(x, "dictionary");

		if (attrstart)
			object_attr_setvalueof(x, gensym("keys"), attrstart, argv);

		attr_args_process(x, argc, argv);
	}
	return x;
}


void dict_strip_free(t_dict_strip *x)
{
	;
}


/************************************************************************************/
void dict_strip_assist(t_dict_strip *x, void *b, long m, long a, char *s)
{
	if (m==ASSIST_INLET) {
		strcpy(s, "dictionary input");
	}
	else if (m==ASSIST_OUTLET) {
		switch (a) {
		case 0: strcpy(s, "dictionary output stripped of specified keys"); break;
		case 1: strcpy(s, "series of key/value pairs stripped from the dictionary"); break;
		}
	}
}


void dict_strip_dictionary(t_dict_strip *x, t_symbol *s)
{
	t_dictionary	*d = dictobj_findregistered_retain(s);
	long			i;
	t_atom			a[2];
	t_max_err		err;

	if (!d) {
		object_error((t_object *)x, "unable to reference dictionary named %s", s);
		return;
	}

	for (i=0; i < x->numkeys; i++) {
		t_atom			akey[1];
		t_dictionary	*d0 = NULL;
		t_symbol		*key0 = NULL;

		atom_setsym(akey, x->keys[i]);
		err = dictobj_key_parse((t_object *)x, d, akey, false, &d0, &key0, NULL);
		if (err) {
			object_error((t_object *)x, "could not parse key %s", x->keys[i]->s_name);
			continue;
		}

		err = dictionary_getatom(d0, key0, a);
		if (!err) {
			if (atomisatomarray(a)) {
				t_atom	*av = NULL;
				long	ac = 0;

				atomarray_copyatoms((t_atomarray *)a->a_w.w_obj, &ac, &av);
				outlet_anything(x->outlet_keyvals, x->keys[i], ac, av);
				sysmem_freeptr(av);
			}
			else if (atomisdictionary(a)) {
				t_dictionary	*d1 = (t_dictionary *)atom_getobj(a);
				t_symbol		*d1_name;

				d1_name = dictobj_namefromptr(d1);
				if (!d1_name)
					dictobj_register(d1, &d1_name);

				atom_setsym(a, ps_dictionary);
				atom_setsym(a+1, d1_name);
				outlet_anything(x->outlet_keyvals, x->keys[i], 2, a);
			}
			else
				outlet_anything(x->outlet_keyvals, x->keys[i], 1, a);
			dictionary_deleteentry(d0, key0);
		}
	}

	x->name = s;
	dict_strip_bang(x);
	object_notify(d, ps_modified, NULL);
	dictobj_release(d);
}


void dict_strip_bang(t_dict_strip *x)
{
	if (x->name) {
		t_atom a[1];

		atom_setsym(a, x->name);
		outlet_anything(x->outlet_dict, ps_dictionary, 1, a);
	}
}

