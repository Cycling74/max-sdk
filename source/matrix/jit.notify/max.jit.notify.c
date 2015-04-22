/*
	Copyright 2001-2002 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_notify
{
	t_object		ob;
	void			*obex;
	t_symbol		*servername; //NOTIFY EXAMPLE
} t_max_jit_notify;

t_jit_err jit_notify_init(void);

void max_jit_notify_notify(t_max_jit_notify *x, t_symbol *s, t_symbol *msg, void *ob, void *data);
void *max_jit_notify_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_notify_free(t_max_jit_notify *x);
void *max_jit_notify_class;

void ext_main(void *r)
{
	t_class *p,*q;

	jit_notify_init();
	p = class_new("jit.notify", (method)max_jit_notify_new, (method)max_jit_notify_free, sizeof(t_max_jit_notify), NULL, A_GIMME, 0);
	max_jit_class_obex_setup(p, calcoffset(t_max_jit_notify,obex));
	q = jit_class_findbyname(gensym("jit_notify"));

	//NOTIFY EXAMPLE: WE NEED TO OVERRIDE THE DEFAULT MOP NOTIFY METHOD
	max_jit_class_mop_wrap(p, q, MAX_JIT_MOP_FLAGS_OWN_NOTIFY);			//name/type/dim/planecount/bang/outputmatrix/etc

	max_jit_class_wrap_standard(p, q, 0);	//getattributes/dumpout/maxjitclassaddmethods/etc
	class_addmethod(p, (method)max_jit_mop_assist, "assist", A_CANT,0);  //standard mop assist fn

	//NOTIFY EXAMPLE: HERE'S WHERE WE DECLARE OUR OWN NOTIFY METHOD
	class_addmethod(p, (method)max_jit_notify_notify, "notify", A_CANT,0);
}

//NOTIFY EXAMPLE: HERE'S WHERE WE GET INFO FROM SERVERS WE ARE ATTACHED TO
//s is the servername, msg is the message, ob is the server object pointer,
//and data is extra data the server might provide for a given message
void max_jit_notify_notify(t_max_jit_notify *x, t_symbol *s, t_symbol *msg, void *ob, void *data)
{
	if (msg==gensym("splat")) {
		post("notify: server=%s message=%s",s->s_name,msg->s_name);
		if (!data) {
			error("splat message NULL pointer");
			return;
		}
		//here's where we output using the rightmost outlet
		//we just happen to know that "data" points to a t_atom[3]
		//alternately you could use max_jit_obex_dumpout_get just to get
		//the outlet pointer
		max_jit_obex_dumpout(x,msg,3,(t_atom *)data);
	} else {
		//since we are a MOP, we are also attached to all the matrices for each input/output
		//so we need to deal with this by calling the default mop notify method
		//(this is how mops handle their matrices getting new names/freed/modified)
		//mop notify ignores the data element and you should also ignore the error that
		//max_jit_mop_notify has msg prototyped as a long *, it is really a symbol *(oops)
		max_jit_mop_notify(x,s,msg);
	}
}


void max_jit_notify_free(t_max_jit_notify *x)
{

	//NOTIFY EXAMPLE: DETACH FROM JIT OBJECT(SERVER)
	jit_object_detach(x->servername,x);

	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_object_free(x);
}

void *max_jit_notify_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_notify *x;
	void *o;

	if ((x=(t_max_jit_notify *)max_jit_object_alloc(max_jit_notify_class,gensym("jit_notify")))) {
		if ((o=jit_object_new(gensym("jit_notify")))) {
			max_jit_mop_setup_simple(x,o,argc,argv);
			max_jit_attr_args(x,argc,argv);

			//NOTIFY EXAMPLE: GENERATING A UNIQUE NAME + ASSOCIATING WITH JIT OBJECT(SERVER)
			x->servername = jit_symbol_unique();
			jit_object_method(o,_jit_sym_register,x->servername); //this registers w/ the name
			jit_object_attach(x->servername,x);	//this attaches max object(client) with jit object(server)
		} else {
			error("jit.notify: could not allocate object");
			object_free((t_object *)x);
		}
	}
	return (x);
}
