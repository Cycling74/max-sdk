/**
	@file
	dllreport - get the current state from a DLL shared by several external objects

	@ingroup	examples

	Copyright 2013 - Cycling '74
	Timothy Place, tim@cycling74.com
*/

#include "mydll.h"


// max object instance data
typedef struct _dllreport {
	t_object	d_obj;
	void		*d_outlet;
} t_dllreport;


// prototypes
void	*dllreport_new(t_symbol *s, long argc, t_atom *argv);
void	dllreport_assist(t_dllreport *x, void *b, long m, long a, char *s);
void	dllreport_bang(t_dllreport *x);


// globals
static t_class	*s_dllreport_class = NULL;

/************************************************************************************/

void ext_main(void *r)
{
	t_class	*c;

	mydll_init(); // call the init function in our dll -- will post to the Max window the first time only (for all objects linked to our dll)

	c = class_new("dllreport", (method)dllreport_new, (method)NULL, sizeof(t_dllreport), (method)NULL, A_GIMME, 0);
	class_addmethod(c, (method)dllreport_bang,		"bang",			0);
	class_addmethod(c, (method)dllreport_assist,	"assist",		A_CANT, 0);
	class_addmethod(c, (method)stdinletinfo,		"inletinfo",	A_CANT, 0);

	class_register(CLASS_BOX, c);
	s_dllreport_class = c;
}


/************************************************************************************/
// Object Creation Method

void *dllreport_new(t_symbol *s, long argc, t_atom *argv)
{
	t_dllreport *x = (t_dllreport *)object_alloc(s_dllreport_class);
	x->d_outlet = outlet_new((t_object *)x, NULL);
	return x;
}


/************************************************************************************/
// Methods bound to input/inlets

void dllreport_assist(t_dllreport *x, void *b, long msg, long arg, char *dst)
{
	if (msg == 1)
		strcpy(dst, "bang to get the current count");
	else
		strcpy(dst, "(int) the count");
}


void dllreport_bang(t_dllreport *x)
{
	int count = mydll_getcount();// call the function in our dll to fetch the count

	outlet_int(x->d_outlet, count);
}
