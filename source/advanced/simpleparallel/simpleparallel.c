#include "ext.h"
#include "ext_obex.h"
#include "ext_systhread.h"
#include "ext_sysparallel.h"


typedef struct _simpleparallel {
	t_object			x_ob;							// standard max object
	t_sysparallel_task	*x_sysparallel_task;						// thread reference
	t_systhread_mutex	x_mutex;						// mutual exclusion lock for threadsafety
	void				*x_outlet;						// our outlet
	int				x_foo;								// value
	int				x_iterations;								// number of iterations
} t_simpleparallel;

void simpleparallel_bang(t_simpleparallel *x);
void simpleparallel_dobang(t_simpleparallel *x);
void simpleparallel_foo(t_simpleparallel *x, long foo);
t_max_err simpleparallel_setattr_iterations(t_simpleparallel *x, void *attr, long ac, t_atom *av);
void *simpleparallel_threadproc(t_sysparallel_worker *w);
void simpleparallel_assist(t_simpleparallel *x, void *b, long m, long a, char *s);
void simpleparallel_free(t_simpleparallel *x);
void *simpleparallel_new(t_symbol *s, long ac, t_atom *av);

t_class *simpleparallel_class;

void ext_main(void *r)
{
	t_class *c;

	c = class_new("simpleparallel", (method)simpleparallel_new, (method)simpleparallel_free, sizeof(t_simpleparallel), 0L, A_GIMME, 0);

	class_addmethod(c, (method)simpleparallel_bang,			"bang",			0);
	class_addmethod(c, (method)simpleparallel_foo,			"foo",			A_DEFLONG, 0);
	class_addmethod(c, (method)simpleparallel_assist,		"assist",		A_CANT, 0);

	CLASS_ATTR_LONG(c, "iterations", 0, t_simpleparallel, x_iterations);

	class_register(CLASS_BOX,c);
	simpleparallel_class = c;
}

void simpleparallel_bang(t_simpleparallel *x)
{
	// always force to execute from one thread so we don't mess with our thread pools.
	defer(x,(method)simpleparallel_dobang,NULL,0,NULL);
}

void simpleparallel_dobang(t_simpleparallel *x)
{
	int myfoo;

	// create new task and execute it
	if (x->x_sysparallel_task == NULL) {
		post("creating a new parallel task");
		x->x_sysparallel_task = sysparallel_task_new(x,(method) simpleparallel_threadproc, 0);
		x->x_sysparallel_task->flags = SYSPARALLEL_PRIORITY_TASK_LOCAL;
	}

	sysparallel_task_execute(x->x_sysparallel_task);

	systhread_mutex_lock(x->x_mutex);
	myfoo = x->x_foo;
	systhread_mutex_unlock(x->x_mutex);

	// *never* wrap outlet calls with systhread_mutex_lock()
	outlet_int(x->x_outlet, myfoo);
}

void simpleparallel_foo(t_simpleparallel *x, long foo)
{
	systhread_mutex_lock(x->x_mutex);
	x->x_foo = foo;																// override our current value
	systhread_mutex_unlock(x->x_mutex);
}


t_max_err simpleparallel_setattr_iterations(t_simpleparallel *x, void *attr, long ac, t_atom *av)
{
	if (ac && av) {
		t_atom_long iterations = atom_getlong(av);

		if (iterations < 1)
			iterations = 1;

		x->x_iterations = iterations;
	}
	return MAX_ERR_NONE;
}

void *simpleparallel_threadproc(t_sysparallel_worker *w)
{
	t_simpleparallel *x = (t_simpleparallel *)w->data;
	int i,myfoo=0,iterations;
	double time = systimer_gettime();

	object_post((t_object *)x,"worker %ld of %ld started",w->id,w->task->workercount);

	// do some work
	iterations = x->x_iterations;
	for (i=0; i<iterations; i++) {
		myfoo++;
	}

	// increment our main value
	systhread_mutex_lock(x->x_mutex);
	x->x_foo += myfoo;																// fiddle with shared data
	systhread_mutex_unlock(x->x_mutex);

	object_post((t_object *)x,"worker %ld of %ld ended (%fms)",w->id,w->task->workercount,systimer_gettime()-time);

	return NULL;
}

void simpleparallel_assist(t_simpleparallel *x, void *b, long m, long a, char *s)
{
	if (m==1)
		sprintf(s,"bang spawns a parallel process");
	else if (m==2)
		sprintf(s,"report when done");
}

void simpleparallel_free(t_simpleparallel *x)
{

	if (x->x_sysparallel_task)
		object_free((t_object *)x->x_sysparallel_task);

	// free our mutex
	if (x->x_mutex)
		systhread_mutex_free(x->x_mutex);
}

void *simpleparallel_new(t_symbol *s, long ac, t_atom *av)
{
	t_simpleparallel *x;

	x = (t_simpleparallel *)object_alloc(simpleparallel_class);
	x->x_outlet = outlet_new(x,NULL);
	x->x_sysparallel_task = NULL;
	systhread_mutex_new(&x->x_mutex,0);
	x->x_foo = 0;
	x->x_iterations = 5000000;
	attr_args_process(x, ac, av);

	return(x);
}




