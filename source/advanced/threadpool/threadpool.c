#include "ext.h"
#include "ext_obex.h"
#include "ext_systhread.h"
#include "threadpooltask.h"

typedef struct _threadpool {
	t_object			x_ob;								// standard max object
	void				*x_outlet;							// our outlet
} t_threadpool;

void threadpool_task(t_threadpool *x, t_symbol *s, long argc, t_atom *argv);
void threadpool_dotask(t_threadpool *x, t_symbol *s, long ac, t_atom *av);
void threadpool_taskcomplete(t_threadpool *x, t_symbol *s, long ac, t_atom *av);
void threadpool_taskoutput(t_threadpool *x, t_symbol *s, long ac, t_atom *av);
void threadpool_cancel(t_threadpool *x);
void threadpool_stop(t_threadpool *x);
void threadpool_assist(t_threadpool *x, void *b, long m, long a, char *s);
void threadpool_free(t_threadpool *x);
void *threadpool_new(void);

t_class *threadpool_class;


void ext_main(void *r)
{
	t_class *c;

	c = class_new("threadpool", (method)threadpool_new, (method)threadpool_free, sizeof(t_threadpool), 0L, 0);

	class_addmethod(c, (method)threadpool_task,				"task",				A_GIMME, 0);
	class_addmethod(c, (method)threadpool_cancel,			"cancel",			0);

	// methods which we use internally. they all have A_GIMME style signature
	class_addmethod(c, (method)threadpool_dotask,			"dotask",			A_GIMME, 0);
	class_addmethod(c, (method)threadpool_taskcomplete,		"taskcomplete",		A_GIMME, 0);
	class_addmethod(c, (method)threadpool_taskoutput,		"taskoutput",		A_GIMME, 0);

	class_addmethod(c, (method)threadpool_assist,			"assist",			A_CANT, 0);

	class_register(CLASS_BOX,c);
	threadpool_class = c;

	threadpooltask_init(); // initialze one global background task thread pool for all of our objects
}

void threadpool_task(t_threadpool *x, t_symbol *s, long argc, t_atom *argv)
{
	// schedule a background task using A_GIMME style object methods and atoms
	// for the task execution (mtask), and the task completion (mcomp)
	// the object and arguments can be different for execution and completion
	//long threadpooltask_execute_method(t_object *obtask, t_symbol *mtask, long actask, t_atom *avtask,
	//									t_object *obcomp, t_symbol *mcomp, long accomp, t_atom *avcomp,
	//									t_threadpooltask **task, long flags)

	threadpooltask_execute_method((t_object *)x,gensym("dotask"),argc,argv,
								  (t_object *)x,gensym("taskcomplete"),argc,argv,
								  NULL,0);

	// alternately, schedule a background task using function pointer callbacks and void arg pointers
	// for the task execution cbtask, and cbcomplete (the same object and argument pointers are used for both)
	// long threadpooltask_execute(t_object *owner, void *args, method cbtask, method cbcomplete, t_threadpooltask **task, long flags)

}


void threadpool_dotask(t_threadpool *x, t_symbol *s, long ac, t_atom *av)
{
	long i;
	double f=0.74;
	double start = systimer_gettime();
	double end;
	long textsize=0;
	char *tmpstr=NULL;

	atom_gettext(ac,av,&textsize,&tmpstr,0);

	post("threadpool starting background task (%s)",tmpstr);

	for (i=0; i<100000000; i++) {
		f = sqrt(sin(f)*sin(f) + cos(f)*cos(f));
	}

	end = systimer_gettime();
	post("threadpool finished background task (%s) result=%f time=%f",tmpstr,f,end-start);

	if (tmpstr)
		sysmem_freeptr(tmpstr);
}

void threadpool_taskcomplete(t_threadpool *x, t_symbol *s, long ac, t_atom *av)
{
	long textsize=0;
	char *tmpstr=NULL;
	// our completion method will be called from our bakground thread
	// we cannot output to a patcher from this thread (ILLEGAL)
	// so we must defer or schedule output to the patcher

	atom_gettext(ac,av,&textsize,&tmpstr,0);
	post("threadpool background task (%s) completed in thread %x",tmpstr,systhread_self());
	post("deferring output to the main thread");

	defer_low(x,(method)threadpool_taskoutput,gensym("taskoutput"),ac,av);
	//schedule_delay(x,(method)threadpool_taskoutput,gensym("taskoutput"),ac,av);

	if (tmpstr)
		sysmem_freeptr(tmpstr);
}

void threadpool_taskoutput(t_threadpool *x, t_symbol *s, long ac, t_atom *av)
{
	outlet_anything(x->x_outlet, s, ac, av);
}

void threadpool_cancel(t_threadpool *x)
{
	threadpool_stop(x);
	outlet_anything(x->x_outlet,gensym("cancelled"), 0, NULL);
}

void threadpool_stop(t_threadpool *x)
{
	// stop all tasks associated with my object if they are still present
	threadpooltask_purge_object((t_object *)x);
}

void threadpool_assist(t_threadpool *x, void *b, long m, long a, char *s)
{
	if (m==1)
		sprintf(s,"make a new task");
	else if (m==2)
		sprintf(s,"report when done/cancelled");
}

void threadpool_free(t_threadpool *x)
{
	threadpool_stop(x);
}

void *threadpool_new(void)
{
	t_threadpool *x;

	x = (t_threadpool *)object_alloc(threadpool_class);
	x->x_outlet = outlet_new(x,NULL);

	return(x);
}




