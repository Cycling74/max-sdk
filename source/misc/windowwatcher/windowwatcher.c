/**
	@file
	windowwatcher - Demonstrate how to get notifications about the window for a patcher in which an object exists.
					Scrolling or sizing can be obtained by attaching to the patcherview to get notifications.
					Getting the actual window position requires the "boxscreenrectchanged" method to be added.

	@ingroup		examples

	Copyright 2009 - Cycling '74
	Timothy Place, tim@cycling74.com
*/

#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"


// Data Structures
typedef struct _ww {
	t_object	w_obj;
	t_object	*w_patcher;
	t_object	*w_patcherview;
	void		*w_outlet;
} t_ww;


// Prototypes
t_ww		*ww_new(t_symbol *s, short argc, t_atom *argv);
void		ww_free(t_ww *x);
void		ww_attach(t_ww *x);
t_max_err	ww_notify(t_ww *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void		ww_boxscreenrectchanged(t_jbox *box, t_object *patcherview);

// Globals and Statics
static t_class	*s_ww_class = NULL;


/**********************************************************************/
// Class Definition and Life Cycle

void ext_main(void *r)
{
	t_class *c;

	c = class_new("windowwatcher", (method)ww_new, (method)ww_free, sizeof(t_ww), (method)NULL, A_GIMME, 0L);

	class_addmethod(c, (method)ww_notify,				"notify",				A_CANT, 0);

	// If your object were a UI external, then you can simply add the method to the class as below.
	// However, this example object is not a UI extern.

	// At somepoint in the future instance-methods may be supported.
	// If/when they are, you cound add a method to our instance in the 'new' method instead.

	// class_addmethod(c, (method)ww_boxscreenrectchanged,	"boxscreenrectchanged",	A_CANT, 0);

	class_register(CLASS_BOX, c);
	s_ww_class = c;
}


t_ww *ww_new(t_symbol *s, short argc, t_atom *argv)
{
	t_ww		*x = NULL;
	t_object	*box = NULL;

	x = (t_ww *)object_alloc(s_ww_class);
	if (x) {
		x->w_outlet = outlet_new(x, 0L);
		attr_args_process(x, argc, argv);

		object_obex_lookup(x, gensym("#P"), &x->w_patcher);
		object_obex_lookup(x, gensym("#B"), &box);

		// If/when instance methods are supported, we can use object_addmethod() to add the method
		// (as opposed to a class method) to our box.
		// Then we can be called when our box is moved.
		object_addmethod(box, (method)ww_boxscreenrectchanged, "boxscreenrectchanged",	A_CANT, 0);

		// The patcherview is not available when the object is created as a patcher is being read from disk,
		// so we have to defer to wait for it before getting it and attaching for notifications.
		// if we were in a ui object then we would instead add a 'patcherview_vis' method
		// (and possibly a 'patcherview_invis' method) and attach to our patcherview at that time.
		defer_low(x, (method)ww_attach, NULL, 0, NULL);

	}
	return x;
}


void ww_free(t_ww *x)
{
	if(x->w_patcherview)
		object_detach_byptr((t_object *)x, x->w_patcherview);
}


/**********************************************************************/
// Methods

void ww_attach(t_ww *x)
{
	x->w_patcherview = object_attr_getobj(x->w_patcher, gensym("firstview"));
	object_attach_byptr_register(x, x->w_patcherview, CLASS_NOBOX);
}


t_max_err ww_notify(t_ww *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol	*name = NULL;
	t_rect		r;
	t_atom		a[4];

	if (sender == x->w_patcherview) {
		if (msg == gensym("attr_modified")) {
			name = (t_symbol *)object_method((t_object *)data, gensym("getname"));

			// the patcherview is notified when its rect changes size
			if (name == gensym("rect")) {
				object_attr_get_rect(x->w_patcherview, gensym("rect"), &r);
				atom_setfloat(a+0, r.x);
				atom_setfloat(a+1, r.y);
				atom_setfloat(a+2, r.width);
				atom_setfloat(a+3, r.height);
				outlet_anything(x->w_outlet, gensym("patcherview"), 4, a);
			}
			// the patcherview is notified when its visible rect has changed (i.e. scrollbars have been moved)
			if (name == gensym("visiblecanvasrect")) {
				object_attr_get_rect(x->w_patcherview,gensym("visiblecanvasrect"), &r);
				atom_setfloat(a+0, r.x);
				atom_setfloat(a+1, r.y);
				atom_setfloat(a+2, r.width);
				atom_setfloat(a+3, r.height);
				outlet_anything(x->w_outlet, gensym("visiblecanvasrect"), 4, a);
			}
		}
		else if (msg == gensym("free")) {
			object_detach_byptr((t_object *)x, x->w_patcherview);
			x->w_patcherview = NULL;
		}
	}
	return MAX_ERR_NONE;
}


void ww_boxscreenrectchanged(t_jbox *box, t_object *patcherview)
{
	t_rect		r;
	t_atom		a[4];
	t_ww		*x = (t_ww *)box->b_firstin;

	// This method is an instance method of our box object (newobj)
	// So ...

	object_attr_get_rect(x->w_patcherview, gensym("rect"), &r);
	atom_setfloat(a+0, r.x);
	atom_setfloat(a+1, r.y);
	atom_setfloat(a+2, r.width);
	atom_setfloat(a+3, r.height);
	outlet_anything(x->w_outlet, gensym("boxscreenrectchanged"), 4, a);
}

