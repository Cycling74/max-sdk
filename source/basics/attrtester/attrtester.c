/**
	@file
	attrtester - a max object shell
	jeremy bernstein - jeremy@bootsquad.com

	@ingroup	examples
*/

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object

////////////////////////// object struct
typedef struct _attrtester
{
	t_object					a_ob;			// the object itself (must be first)
	long						a_val;
	char						a_usemin;
	char						a_usemax;
	long						a_min;
	long						a_max;
	void						*a_out;
} t_attrtester;

///////////////////////// function prototypes
//// standard set
void *attrtester_new(t_symbol *s, long argc, t_atom *argv);
void attrtester_free(t_attrtester *x);
void attrtester_assist(t_attrtester *x, void *b, long m, long a, char *s);
//// additional methods
void attrtester_int(t_attrtester *x, long n);
void attrtester_float(t_attrtester *x, double f);
void attrtester_bang(t_attrtester *x); // incoming bang message

t_max_err attrtester_min_get(t_attrtester *x, void *attr, long *ac, t_atom **av);
t_max_err attrtester_min_set(t_attrtester *x, void *attr, long ac, t_atom *av);

//////////////////////// global class pointer variable
void *attrtester_class;

//	CLASS_ATTR_ORDER(c, "val", 0, "1");
//	CLASS_ATTR_ORDER(c, "usemax", 0, "-1");
//	CLASS_ATTR_ACCESSORS(c, "min", (method)attrtester_min_get, (method)attrtester_min_set);
//	CLASS_ATTR_STYLE_LABEL(c, "usemin", 0, "onoff", "Use Minimum");
//	CLASS_ATTR_INVISIBLE(c, "val", 0);
//	CLASS_ATTR_SAVE(c, "min", 0, "0");
//	CLASS_ATTR_ATTR_PARSE(c, "float", "undocumented", gensym("long"), 0, "1");

void ext_main(void *r)
{
	t_class *c;

	c = class_new("attrtester", (method)attrtester_new, (method)attrtester_free, (long)sizeof(t_attrtester), 0L, A_GIMME, 0);

	class_addmethod(c, (method)attrtester_bang, "bang", 0);
	class_addmethod(c, (method)attrtester_int, "int", A_LONG, 0);
	class_addmethod(c, (method)attrtester_float, "float", A_FLOAT, 0);

	class_addmethod(c, (method)attrtester_assist,			"assist",		A_CANT, 0);

	/* Inspector items ARE ATTRIBUTES */
	CLASS_ATTR_LONG(c, "min", 0, t_attrtester, a_min);
	CLASS_ATTR_SAVE(c, "min", 0);
	// override default accessors
	CLASS_ATTR_ACCESSORS(c, "min", (method)attrtester_min_get, (method)attrtester_min_set);

	CLASS_ATTR_LONG(c, "max", 0, t_attrtester, a_max);
	// clip max value to 0-100
	CLASS_ATTR_FILTER_CLIP(c, "max", 0, 100);

	CLASS_ATTR_CHAR(c, "usemin", 0, t_attrtester, a_usemin);
	CLASS_ATTR_CHAR(c, "usemax", 0, t_attrtester, a_usemax);

	// read-only
	CLASS_ATTR_LONG(c, "val", 0 /*ATTR_SET_OPAQUE_USER*/, t_attrtester, a_val);

	CLASS_ATTR_CATEGORY(c, "val", 0, "Value"); // define 'Value' category

	CLASS_ATTR_ORDER(c, "val", 0, "1"); // top of the list
	CLASS_ATTR_ORDER(c, "usemax", 0, "-1"); // bottom of the list

	// index-based enumeration style
	CLASS_ATTR_ENUMINDEX(c, "val", 0, "zero one two \"three four\" five");
	// set the label without setting the style
	CLASS_ATTR_LABEL(c, "val", 0, "Enumerated Value");
	CLASS_ATTR_INVISIBLE(c, "val", 0); // hide attribute from inspector

	/* style */  /* label */
	CLASS_ATTR_STYLE_LABEL(c, "usemin", 0, "onoff", "Use Minimum");
	CLASS_ATTR_STYLE_LABEL(c, "usemax", 0, "onoff", "Use Maximum");

	class_register(CLASS_BOX, c);
	attrtester_class = c;

	post("I am the attrtester object");
}

void attrtester_assist(t_attrtester *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { //inlet
		sprintf(s, "I am inlet %ld", a);
	}
	else {	// outlet
		sprintf(s, "I am outlet %ld", a);
	}
}

void attrtester_int(t_attrtester *x, long n)
{
	if (x->a_usemin)
		n = n < x->a_min ? x->a_min : n;
	if (x->a_usemax)
		n = n > x->a_max ? x->a_max : n;
	x->a_val = n;

	attrtester_bang(x);
}

void attrtester_float(t_attrtester *x, double f)
{
	attrtester_int(x, (long)f);
}

void attrtester_bang(t_attrtester *x)
{
	outlet_int(x->a_out, x->a_val);
}

t_max_err attrtester_min_get(t_attrtester *x, void *attr, long *ac, t_atom **av)
{
	if (ac && av) {
		char alloc;

		if (atom_alloc(ac, av, &alloc)) {
			return MAX_ERR_GENERIC;
		}
		atom_setlong(*av, x->a_min);
	}
	return MAX_ERR_NONE;
}

t_max_err attrtester_min_set(t_attrtester *x, void *attr, long ac, t_atom *av)
{
	if (ac && av) {
		t_atom_long min = atom_getlong(av);
		// for instance...
		if (min <= x->a_max)
			x->a_min = min;
	}
	return MAX_ERR_NONE;
}


void attrtester_free(t_attrtester *x)
{
	;
}

void *attrtester_new(t_symbol *s, long argc, t_atom *argv)
{
	t_attrtester *x = (t_attrtester *)object_alloc(attrtester_class);

	if (x) {
		x->a_val = 0;
		x->a_min = -52;
		x->a_max = 0;
		x->a_usemin = 0;
		x->a_usemax = 0;
		x->a_out = outlet_new(x, NULL); // then to the left

		attr_args_process(x, argc, argv);
	}
	return (x);
}
