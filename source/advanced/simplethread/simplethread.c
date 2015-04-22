#include "ext.h"
#include "ext_obex.h"
#include "ext_systhread.h"


typedef struct _simplethread {
	t_object			x_ob;								// standard max object
	t_systhread		x_systhread;						// thread reference
	t_systhread_mutex	x_mutex;							// mutual exclusion lock for threadsafety
	int				x_systhread_cancel;					// thread cancel flag
	void				*x_qelem;							// for message passing between threads
	void				*x_outlet;							// our outlet
	int				x_foo;							// simple data to pass between threads
	int				x_sleeptime;						// how many milliseconds to sleep
} t_simplethread;

void simplethread_bang(t_simplethread *x);
void simplethread_foo(t_simplethread *x, long foo);
void simplethread_sleeptime(t_simplethread *x, long sleeptime);
void simplethread_stop(t_simplethread *x);
void simplethread_cancel(t_simplethread *x);
void *simplethread_threadproc(t_simplethread *x);
void simplethread_qfn(t_simplethread *x);
void simplethread_assist(t_simplethread *x, void *b, long m, long a, char *s);
void simplethread_free(t_simplethread *x);
void *simplethread_new(void);

t_class *simplethread_class;

void ext_main(void *r)
{
	t_class *c;

	c = class_new("simplethread", (method)simplethread_new, (method)simplethread_free, sizeof(t_simplethread), 0L, 0);

	class_addmethod(c, (method)simplethread_bang,		"bang",			0);
	class_addmethod(c, (method)simplethread_foo,		"foo",			A_DEFLONG, 0);
	class_addmethod(c, (method)simplethread_sleeptime,	"sleeptime",	A_DEFLONG, 0);
	class_addmethod(c, (method)simplethread_cancel,		"cancel",		0);
	class_addmethod(c, (method)simplethread_assist,		"assist",		A_CANT, 0);

	class_register(CLASS_BOX,c);
	simplethread_class = c;
}

void simplethread_bang(t_simplethread *x)
{
	simplethread_stop(x);								// kill thread if, any

	// create new thread + begin execution
	if (x->x_systhread == NULL) {
		post("starting a new thread");
		systhread_create((method) simplethread_threadproc, x, 0, 0, 0, &x->x_systhread);
	}
}

void simplethread_foo(t_simplethread *x, long foo)
{
	systhread_mutex_lock(x->x_mutex);
	x->x_foo = foo;																// override our current value
	systhread_mutex_unlock(x->x_mutex);
}

void simplethread_sleeptime(t_simplethread *x, long sleeptime)
{
	if (sleeptime<10)
		sleeptime = 10;
	x->x_sleeptime = sleeptime;														// no need to lock since we are readonly in worker thread
}


void simplethread_stop(t_simplethread *x)
{
	unsigned int ret;

	if (x->x_systhread) {
		post("stopping our thread");
		x->x_systhread_cancel = true;						// tell the thread to stop
		systhread_join(x->x_systhread, &ret);					// wait for the thread to stop
		x->x_systhread = NULL;
	}
}


void simplethread_cancel(t_simplethread *x)
{
	simplethread_stop(x);									// kill thread if, any
	outlet_anything(x->x_outlet, gensym("cancelled"), 0, NULL);
}

void *simplethread_threadproc(t_simplethread *x)
{
	// loop until told to stop
	while (1) {

		// test if we're being asked to die, and if so return before we do the work
		if (x->x_systhread_cancel)
			break;

		systhread_mutex_lock(x->x_mutex);
		x->x_foo++;																// fiddle with shared data
		systhread_mutex_unlock(x->x_mutex);

		qelem_set(x->x_qelem);													// notify main thread using qelem mechanism


		systhread_sleep(x->x_sleeptime);						// sleep a bit
	}

	x->x_systhread_cancel = false;							// reset cancel flag for next time, in case
	// the thread is created again

	systhread_exit(0);															// this can return a value to systhread_join();
	return NULL;
}

// triggered by the helper thread
void simplethread_qfn(t_simplethread *x)
{
	int myfoo;

	systhread_mutex_lock(x->x_mutex);
	myfoo = x->x_foo;															// access shared data
	systhread_mutex_unlock(x->x_mutex);

	// *never* wrap outlet calls with systhread_mutex_lock()
	outlet_int(x->x_outlet, myfoo);
}

void simplethread_assist(t_simplethread *x, void *b, long m, long a, char *s)
{
	if (m==1)
		sprintf(s,"bang starts a new thread");
	else if (m==2)
		sprintf(s,"report when done/cancelled");
}

void simplethread_free(t_simplethread *x)
{
	// stop our thread if it is still running
	simplethread_stop(x);

	// free our qelem
	if (x->x_qelem)
		qelem_free(x->x_qelem);

	// free out mutex
	if (x->x_mutex)
		systhread_mutex_free(x->x_mutex);
}

void *simplethread_new(void)
{
	t_simplethread *x;

	x = (t_simplethread *)object_alloc(simplethread_class);
	x->x_outlet = outlet_new(x,NULL);
	x->x_qelem = qelem_new(x,(method)simplethread_qfn);
	x->x_systhread = NULL;
	systhread_mutex_new(&x->x_mutex,0);
	x->x_foo = 0;
	x->x_sleeptime = 1000;

	return(x);
}




