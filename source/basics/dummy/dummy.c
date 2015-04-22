/**
	@file
	dummy - a dummy object
	jeremy bernstein - jeremy@bootsquad.com

	@ingroup	examples
*/

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object

////////////////////////// object struct
typedef struct _dummy
{
	t_object	ob;
	t_atom		val;
	t_symbol	*name;
	void		*out;
} t_dummy;

///////////////////////// function prototypes
//// standard set
void *dummy_new(t_symbol *s, long argc, t_atom *argv);
void dummy_free(t_dummy *x);
void dummy_assist(t_dummy *x, void *b, long m, long a, char *s);

void dummy_int(t_dummy *x, long n);
void dummy_float(t_dummy *x, double f);
void dummy_anything(t_dummy *x, t_symbol *s, long ac, t_atom *av);
void dummy_bang(t_dummy *x);
void dummy_identify(t_dummy *x);
void dummy_dblclick(t_dummy *x);
void dummy_acant(t_dummy *x);

//////////////////////// global class pointer variable
void *dummy_class;


void ext_main(void *r)
{
	t_class *c;

	c = class_new("dummy", (method)dummy_new, (method)dummy_free, (long)sizeof(t_dummy),
				  0L /* leave NULL!! */, A_GIMME, 0);

	class_addmethod(c, (method)dummy_bang,			"bang", 0);
	class_addmethod(c, (method)dummy_int,			"int",		A_LONG, 0);
	class_addmethod(c, (method)dummy_float,			"float",	A_FLOAT, 0);
	class_addmethod(c, (method)dummy_anything,		"anything",	A_GIMME, 0);
	class_addmethod(c, (method)dummy_identify,		"identify", 0);
	CLASS_METHOD_ATTR_PARSE(c, "identify", "undocumented", gensym("long"), 0, "1");

	// we want to 'reveal' the otherwise hidden 'xyzzy' method
	class_addmethod(c, (method)dummy_anything,		"xyzzy", A_GIMME, 0);
	// here's an otherwise undocumented method, which does something that the user can't actually
	// do from the patcher however, we want them to know about it for some weird documentation reason.
	// so let's make it documentable. it won't appear in the quickref, because we can't send it from a message.
	class_addmethod(c, (method)dummy_acant,			"blooop", A_CANT, 0);
	CLASS_METHOD_ATTR_PARSE(c, "blooop", "documentable", gensym("long"), 0, "1");

	/* you CAN'T call this from the patcher */
	class_addmethod(c, (method)dummy_assist,			"assist",		A_CANT, 0);
	class_addmethod(c, (method)dummy_dblclick,			"dblclick",		A_CANT, 0);

	CLASS_ATTR_SYM(c, "name", 0, t_dummy, name);

	class_register(CLASS_BOX, c);
	dummy_class = c;
}

void dummy_acant(t_dummy *x)
{
	object_post((t_object *)x, "can't touch this!");
}

void dummy_assist(t_dummy *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { //inlet
		sprintf(s, "I am inlet %ld", a);
	}
	else {	// outlet
		sprintf(s, "I am outlet %ld", a);
	}
}

void dummy_free(t_dummy *x)
{
	;
}

void dummy_dblclick(t_dummy *x)
{
	object_post((t_object *)x, "I got a double-click");
}

void dummy_int(t_dummy *x, long n)
{
	atom_setlong(&x->val, n);
	dummy_bang(x);
}

void dummy_float(t_dummy *x, double f)
{
	atom_setfloat(&x->val, f);
	dummy_bang(x);
}

void dummy_anything(t_dummy *x, t_symbol *s, long ac, t_atom *av)
{
	if (s == gensym("xyzzy")) {
		object_post((t_object *)x, "A hollow voice says 'Plugh'");
	} else {
		atom_setsym(&x->val, s);
		dummy_bang(x);
	}
}

void dummy_bang(t_dummy *x)
{
	switch (x->val.a_type) {
	case A_LONG: outlet_int(x->out, atom_getlong(&x->val)); break;
	case A_FLOAT: outlet_float(x->out, atom_getfloat(&x->val)); break;
	case A_SYM: outlet_anything(x->out, atom_getsym(&x->val), 0, NULL); break;
	default: break;
	}
}

void dummy_identify(t_dummy *x)
{
	object_post((t_object *)x, "my name is %s", x->name->s_name);
}

void *dummy_new(t_symbol *s, long argc, t_atom *argv)
{
	t_dummy *x = NULL;

	if ((x = (t_dummy *)object_alloc(dummy_class))) {
		x->name = gensym("");
		if (argc && argv) {
			x->name = atom_getsym(argv);
		}
		if (!x->name || x->name == gensym(""))
			x->name = symbol_unique();

		atom_setlong(&x->val, 0);
		x->out = outlet_new(x, NULL);
	}
	return (x);
}
