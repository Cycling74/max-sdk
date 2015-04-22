#include "ext.h"
#include "ext_obex.h"
#include "ext_strings.h"
#include "ext_dictobj.h"


typedef struct _dict_route {
	t_object		obj;
	void			*outlet_dict;
	void			*outlet_nomatch;
	long			inletnum;
	void			*inlet_tomatch;
	t_symbol		*schema_name;
	t_dictionary	*schema_dict;
} t_dict_route;


// prototypes
void *dict_route_new(t_symbol *s, long argc, t_atom *argv);
void dict_route_free(t_dict_route *x);
void dict_route_assist(t_dict_route *x, void *b, long m, long a, char *s);
void dict_route_dictionary(t_dict_route *x, t_symbol *s);


// class statics/globals
static t_class	*s_dict_route_class;
static t_symbol	*ps_dictionary;


/************************************************************************************/
void ext_main(void *r)
{
	t_class	*c;

	c = class_new("dict.route", (method)dict_route_new, (method)dict_route_free, sizeof(t_dict_route), (method)NULL, A_GIMME, 0);

	class_addmethod(c, (method)dict_route_dictionary, 	"dictionary", 	A_SYM, 0);
	class_addmethod(c, (method)dict_route_assist,		"assist",		A_CANT, 0);

	class_register(CLASS_BOX, c);
	s_dict_route_class = c;
	
	ps_dictionary = gensym("dictionary");
}


/************************************************************************************/
void *dict_route_new(t_symbol *s, long argc, t_atom *argv)
{
	t_dict_route 	*x = (t_dict_route *)object_alloc(s_dict_route_class);
	long			attrstart = attr_args_offset(argc, argv);
	t_dictionary	*d = NULL;	// dictionary with our 'prototype' specified by args to this object

	if (x) {
		x->outlet_nomatch = outlet_new(x, "dictionary");
		x->outlet_dict = outlet_new(x, "dictionary");
		x->inlet_tomatch = proxy_new(x, 1, &x->inletnum);

		if (attrstart)
			dictobj_dictionaryfromatoms(&d, attrstart, argv);
		if (!d) {
			char		errorstring[256];
			t_max_err	err;

			err = dictobj_dictionaryfromstring(&d, "{ \"schema\" : \"*\" }", true, errorstring);
			if (err)
				error("dict.route: %s", errorstring);
		}
		x->schema_dict = dictobj_register(d, &x->schema_name);

		attr_args_process(x, argc, argv);
	}
	return x;
}


void dict_route_free(t_dict_route *x)
{
	object_free(x->schema_dict);
}


/************************************************************************************/
void dict_route_assist(t_dict_route *x, void *b, long m, long a, char *s)
{
	if (m==ASSIST_INLET) {
		switch (a) {
		case 0: strcpy(s, "dictionary output routeped of specified keys"); break;
		case 1: strcpy(s, "series of key/value pairs routed from the dictionary"); break;
		}
		strcpy(s, "dictionary input");
	}
	else if (m==ASSIST_OUTLET) {
		switch (a) {
		case 0: strcpy(s, "dictionary matching specified keys/values"); break;
		case 1: strcpy(s, "dictionary not-matching specified keys/values"); break;
		}
	}
}


void dict_route_dictionary(t_dict_route *x, t_symbol *s)
{
	t_dictionary	*d = dictobj_findregistered_retain(s);

	if (!d) {
		object_error((t_object *)x, "unable to reference dictionary named %s", s);
		return;
	}

	if (proxy_getinlet((t_object *)x) == 0) {
		// left inlet : validate the input against the schema

		long			validates = false;
		t_atom			a;

		validates = dictobj_validate(x->schema_dict, d);
		atom_setsym(&a, s);
		if (validates)
			outlet_anything(x->outlet_dict, ps_dictionary, 1, &a);
		else
			outlet_anything(x->outlet_nomatch, ps_dictionary, 1, &a);
	}
	else {
		// right inlet : set the contents of the schema with a copy of the incoming dictionary

		if (d) {
			dictionary_clear(x->schema_dict);
			dictionary_clone_to_existing(d, x->schema_dict);
		}
	}
	dictobj_release(d);
}

