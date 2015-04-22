/**
	@file
	simplejs - a max object used as a JavaScript class

	@ingroup	examples
*/

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object

////////////////////////// object struct
typedef struct _simplejs
{
	t_object					ob;			// the object itself (must be first)
	double						myattr;
} t_simplejs;

///////////////////////// function prototypes
//// standard set
void *simplejs_new(t_symbol *s, long argc, t_atom *argv);
void simplejs_free(t_simplejs *x);
void simplejs_print(t_simplejs *x, t_symbol *s, long ac, t_atom *av);
t_max_err simplejs_doabs(t_simplejs *x, t_symbol *s, long ac, t_atom *av, t_atom *rv);


//////////////////////// global class pointer variable
static t_class *simplejs_class;


void ext_main(void *r)
{
	t_class *c;

	c = class_new("simplejs", (method)simplejs_new, (method)simplejs_free, (long)sizeof(t_simplejs),
				  0L /* leave NULL!! */, A_GIMME, 0);

	class_addmethod(c, (method)simplejs_print,			"print",		0);
	class_addmethod(c, (method)simplejs_doabs,			"doAbs",		A_GIMMEBACK, 0);

	CLASS_ATTR_DOUBLE(c, "myattr", 0, t_simplejs, myattr);

	c->c_flags = CLASS_FLAG_POLYGLOT;
	class_register(CLASS_NOBOX, c);
	simplejs_class = c;
}

void simplejs_free(t_simplejs *x)
{
	;
}

void *simplejs_new(t_symbol *s, long argc, t_atom *argv)
{
	t_simplejs *x = NULL;

	// object instantiation, NEW STYLE
	if ((x = (t_simplejs *)object_alloc(simplejs_class))) {
		// Initialize values
		x->myattr = 74.;
	}
	return (x);
}

void simplejs_print(t_simplejs *x, t_symbol *s, long ac, t_atom *av)
{
	post("The value of myattr is: %f", x->myattr);
}

t_max_err simplejs_doabs(t_simplejs *x, t_symbol *s, long ac, t_atom *av, t_atom *rv)
{
	t_atom a[1];
	double f = 0;

	if (ac) {
		if (atom_gettype(av) == A_LONG)
			f = (double)abs(atom_getlong(av));
		else if( atom_gettype(av) == A_FLOAT)
			f = fabs(atom_getfloat(av));
	} else
		error("missing argument for method doAbs()");

	// store the result in the a array.
	atom_setfloat(a, f);

	// return the result to js
	atom_setobj(rv, object_new(gensym("nobox"), gensym("atomarray"), 1, a));

	return MAX_ERR_NONE;
}