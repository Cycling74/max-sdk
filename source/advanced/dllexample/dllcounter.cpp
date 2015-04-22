/**
	@file
	dllreport - alter the current state from a DLL shared by several external objects

	@ingroup	examples

	Copyright 2013 - Cycling '74
	Timothy Place, tim@cycling74.com
*/

#include "mydll.h"


// max object instance data
typedef struct _dllcounter {
	t_object	d_obj;
} t_dllcounter;


// prototypes
void	*dllcounter_new(t_symbol *s, long argc, t_atom *argv);
void	dllcounter_assist(t_dllcounter *x, void *b, long m, long a, char *s);
void	dllcounter_bang(t_dllcounter *x);


// globals
static t_class	*s_dllcounter_class = NULL;

/************************************************************************************/

void ext_main(void *r)
{
	t_class	*c;

	mydll_init(); // call the init function in our dll -- will post to the Max window the first time only (for all objects linked to our dll)

	c = class_new("dllcounter", (method)dllcounter_new, (method)NULL, sizeof(t_dllcounter), (method)NULL, A_GIMME, 0);
	class_addmethod(c, (method)dllcounter_bang,	"bang",			0);
	class_addmethod(c, (method)dllcounter_assist,	"assist",		A_CANT, 0);
	class_addmethod(c, (method)stdinletinfo,	"inletinfo",	A_CANT, 0);

	class_register(CLASS_BOX, c);
	s_dllcounter_class = c;
}


/************************************************************************************/
// Object Creation Method

void *dllcounter_new(t_symbol *s, long argc, t_atom *argv)
{
	return object_alloc(s_dllcounter_class);
}


/************************************************************************************/
// Methods bound to input/inlets

void dllcounter_assist(t_dllcounter *x, void *b, long msg, long arg, char *dst)
{
	strcpy(dst, "bang to increase the count by 1");
}


void dllcounter_bang(t_dllcounter *x)
{
	mydll_inc();	// call the function in our dll to increase the count
}
