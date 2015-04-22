/**
	@file
	delay2 - an ITM-based delay

	@ingroup	examples
*/

#include "ext.h"
#include "ext_common.h"
#include "ext_obex.h"
#include "ext_time.h"
#include "ext_itm.h"

typedef struct delay2
{
	t_object d_obj;
	void *d_outlet;
	void *d_proxy;
	long d_inletnum;
	t_object *d_timeobj;
	void *d_outlet2;
	t_object *d_quantize;
	void *d_clock;
} t_delay2;

void *delay2_new(t_symbol *s, long argc, t_atom *argv);
void delay2_free(t_delay2 *x);
void delay2_assist(t_delay2 *x, void *b, long m, long a, char *s);
void delay2_inletinfo(t_delay2 *x, void *b, long a, char *t);
void delay2_int(t_delay2 *x, long n);
void delay2_float(t_delay2 *x, double f);
void delay2_list(t_delay2 *x, t_symbol *s, long argc, t_atom *argv);
void delay2_anything(t_delay2 *x, t_symbol *msg, long argc, t_atom *argv);
void delay2_tick(t_delay2 *x);
void delay2_bang(t_delay2 *x);
void delay2_stop(t_delay2 *x);
void delay2_clocktick(t_delay2 *x);

static t_class *s_delay2_class = NULL;

void ext_main(void *r)
{
	t_class *c = class_new(	"delay2", (method)delay2_new, (method)delay2_free, sizeof(t_delay2), (method)0L, A_GIMME, 0);

	class_addmethod(c, (method)delay2_bang,				"bang",			0);
	class_addmethod(c, (method)delay2_stop,				"stop",			0);
	class_addmethod(c, (method)delay2_int,				"int",			A_LONG, 0);
	class_addmethod(c, (method)delay2_float,				"float",		A_FLOAT, 0);
	class_addmethod(c, (method)delay2_list,				"list",			A_GIMME, 0);
	class_addmethod(c, (method)delay2_anything,			"anything",		A_GIMME, 0);

	class_addmethod(c, (method)delay2_assist,			"assist",		A_CANT, 0);
	class_addmethod(c, (method)delay2_inletinfo,			"inletinfo",	A_CANT, 0);

	class_time_addattr(c, "delaytime", "Delay Time", TIME_FLAGS_TICKSONLY | TIME_FLAGS_USECLOCK | TIME_FLAGS_TRANSPORT);
	class_time_addattr(c, "quantize", "Quantization", TIME_FLAGS_TICKSONLY);

	class_register(CLASS_BOX, c);

	s_delay2_class = c;
}

// initial optional arg is delay time

void *delay2_new(t_symbol *s, long argc, t_atom *argv)
{
	t_delay2 *x = (t_delay2 *)object_alloc(s_delay2_class);
	long attrstart = attr_args_offset(argc, argv);
	t_atom a;

	x->d_inletnum = 0;
	x->d_proxy = proxy_new(x, 1, &x->d_inletnum);
	x->d_outlet2 = bangout(x);
	x->d_outlet = bangout(x);

	x->d_timeobj = (t_object *) time_new((t_object *)x, gensym("delaytime"), (method)delay2_tick, TIME_FLAGS_TICKSONLY | TIME_FLAGS_USECLOCK);
	x->d_quantize = (t_object *) time_new((t_object *)x, gensym("quantize"), NULL, TIME_FLAGS_TICKSONLY);
	x->d_clock = clock_new((t_object *)x, (method)delay2_clocktick);

	if (attrstart && argv)
		time_setvalue(x->d_timeobj, NULL, 1, argv);
	else {
		atom_setfloat(&a, 0.);
		time_setvalue(x->d_timeobj, NULL, 1, &a);
	}
	atom_setfloat(&a,0);
	time_setvalue(x->d_quantize, NULL, 1, &a);

	attr_args_process(x, argc, argv);
	return x;
}


void delay2_free(t_delay2 *x)
{
	freeobject(x->d_timeobj);
	freeobject(x->d_quantize);
	freeobject((t_object *) x->d_proxy);
	freeobject((t_object *)x->d_clock);
}

void delay2_assist(t_delay2 *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {	// Inlets
		switch (a) {
		case 0: sprintf(s, "bang Gets Delayed, stop Cancels"); break;
		case 1: sprintf(s, "Set Delay Time"); break;
		}
	}
	else {						// Outlets
		switch (a) {
		case 0: sprintf(s, "Delayed bang"); break;
		case 1: sprintf(s, "Another Delayed bang"); break;
		}
	}
}

void delay2_inletinfo(t_delay2 *x, void *b, long a, char *t)
{
	if (a)
		*t = 1;
}

void delay2_int(t_delay2 *x, long n)
{
	delay2_float(x, n);
}

void delay2_float(t_delay2 *x, double f)
{
	t_atom a;

	atom_setfloat(&a, f);
	time_setvalue(x->d_timeobj, NULL, 1, &a);

	if (proxy_getinlet((t_object *)x) == 0)
		delay2_bang(x);
}

void delay2_list(t_delay2 *x, t_symbol *s, long argc, t_atom *argv)
{
	delay2_anything(x, NULL, argc, argv);
}

void delay2_anything(t_delay2 *x, t_symbol *msg, long argc, t_atom *argv)
{
	time_setvalue(x->d_timeobj, msg, argc, argv);

	if (proxy_getinlet((t_object *)x) == 0)
		delay2_bang(x);
}

void delay2_tick(t_delay2 *x)
{
	outlet_bang(x->d_outlet);
}

void delay2_bang(t_delay2 *x)
{
	double ms, tix;

	time_schedule(x->d_timeobj, x->d_quantize);

	tix = time_getticks(x->d_timeobj);
	ms = itm_tickstoms(time_getitm(x->d_timeobj), tix);
	clock_fdelay(x->d_clock, ms);
}

void delay2_clocktick(t_delay2 *x)
{
	outlet_bang(x->d_outlet2);
}

void delay2_stop(t_delay2 *x)
{
	time_stop(x->d_timeobj);
	clock_unset(x->d_clock);
}


