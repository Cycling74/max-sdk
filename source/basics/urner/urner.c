/**
	@file
	urner - a max object shell
	jeremy bernstein - jeremy@bootsquad.com

	@ingroup	examples
*/

// The standard random() function is not standard on Windows.
// We need to do this to setup the rand_s() function.
#ifdef WIN_VERSION
#define _CRT_RAND_S
#endif

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object


////////////////////////// object struct
typedef struct _urner
{
	t_object					ob;			// the object itself (must be first)
	char                        *table; // lookup table for urn values
	long                        count; // number of values already picked

	void                        *bangout; // bang when urn is empty
	void                        *out; // random num
} t_urner;

///////////////////////// function prototypes
//// standard set
void *urner_new(t_symbol *s, long argc, t_atom *argv);
void urner_free(t_urner *x);
void urner_assist(t_urner *x, void *b, long m, long a, char *s);
//// additional methods
void urner_bang(t_urner *x); // incoming bang message
void urner_reset(t_urner *x); // incoming reset message

//////////////////////// global class pointer variable
void *urner_class;


void ext_main(void *r)
{
	t_class *c;

	c = class_new("urner", (method)urner_new, (method)urner_free, (long)sizeof(t_urner), 0L, A_GIMME, 0);

	class_addmethod(c, (method)urner_bang,		"bang",		0);
	class_addmethod(c, (method)urner_reset,		"reset",	0);
	class_addmethod(c, (method)urner_assist,	"assist",	A_CANT, 0);

	class_register(CLASS_BOX, c);
	urner_class = c;

	post("I am the urner object");
}

void urner_assist(t_urner *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { //inlet
		sprintf(s, "I am inlet %ld", a);
	}
	else {	// outlet
		sprintf(s, "I am outlet %ld", a);
	}
}

void urner_reset(t_urner *x)
{
	long i;
	long size = sysmem_ptrsize(x->table);

	for (i = 0; i < size; i++) {
		x->table[i] = 0; // zero table
	}
	x->count = 0;
}

void urner_bang(t_urner *x)
{
	long rand;
	long size = sysmem_ptrsize(x->table); // RETURNS SIZE OF POINTER IN BYTES

#ifdef WIN_VERSION
	rand_s(&rand);
#else
	rand = random();
#endif

	rand = rand % size;

	if (x->count == size) {
		outlet_bang(x->bangout); // SEND A BANG WHEN WE'VE HIT MAXIMUM
		return;
	}

	if (x->table[rand] != 0) { // NUMBER HAS ALREADY BEEN CHOSEN
		do {
#ifdef WIN_VERSION
			rand_s(&rand);
#else
			rand = random();
#endif
			rand = rand % size;
		} while (x->table[rand] != 0);
	}

	// WE GOT A NUMBER
	x->table[rand] = 1; // MARK THIS VALUE AS USED
	x->count++; // INCREMENT OUR COUNT
	outlet_int(x->out, rand);
}


void urner_free(t_urner *x)
{
	sysmem_freeptr(x->table); // FREE ALLOCED MEMORY
}

void *urner_new(t_symbol *s, long argc, t_atom *argv)
{
	t_urner *x = NULL;
	long size;

	if (argc < 1) return NULL;

	size = atom_getlong(argv); // SIZE OF OUR URN
	if (size < 1) return NULL; // CHECK FOR INVALID DATA

	if ((x = (t_urner *)object_alloc(urner_class))) {
		x->table = (char *)sysmem_newptrclear(size); // size BYTES for the alloced pointer
		urner_reset(x); // initializes x->count

		x->bangout = outlet_new(x, NULL); // rightmost outlet first
		x->out = outlet_new(x, NULL); // then to the left
	}
	return (x);
}
