// ext_drag.h copyright 2008 cycling '74
// functions for handling drag-and-drop from the max file browser (but not from the mac finder)

#ifndef __EXT_DRAG_H__

#define __EXT_DRAG_H__

BEGIN_USING_C_LINKAGE

enum {
	JDRAG_MATCHFLAGS_ANY = 1		// any item with this role is OK, default is that all must match
};

typedef struct _jdrag_inquiry
{
	t_symbol *i_role;			// kind of file that works (one inquiry per file kind)
	t_symbol *i_prepend;		// corresponding message
} t_jdrag_inquiry;

char *jdrag_getitemstring(t_object *dg, long index, long quote, long backslash);
t_object *jdrag_getobject(t_object *dg, long index);
void jdrag_getlocation(t_object *dg, long index, double *xpos, double *ypos);
t_object *jdrag_createobject(t_object *dg, t_object *pv, void *d, long dragobjectindex);
t_object *jdrag_createnewobj(t_object *dg, t_object *pv, char *classname, char *str);
t_object *jdrag_createmessage(t_object *dg, t_object *pv, t_symbol *msg, long ac, t_atom *av);
long jdrag_itemcount(t_object *dg);

//	dg		the jdrag object
//	rcv		the jbox which will have a message called when the dragged thing is released
//	msg		the message name that will be sent to the box when the dragged thing is released
//	desc	a description to be displayed in a contextual menu for the drop action
//	arg		user data to be passed to the drag function (for example, the t_symbol* of the message to call in the case of jdrag_box_add())
void jdrag_add(t_object *dg, t_object *rcv, t_symbol *msg, char *desc, void *arg);

void jdrag_process_drop(t_object *dx, t_object *receiver, void *ref, t_symbol *msg, void *src, double x, double y);


long jdrag_matchdragrole(t_object *dx, t_symbol *role, long flags);


void jdrag_setboxlocation(t_object *dg, t_object *box);


void jdrag_object_add(t_object *dg, t_object *obj, t_symbol *msg);

// a wrapper around jbox_add() used by most ui objects; demonstrated in the pictmeter~ example project in the sdk
void jdrag_box_add(t_object *dg, t_object *box, t_symbol *msg);


END_USING_C_LINKAGE

#endif	// __EXT_DRAG_H__
