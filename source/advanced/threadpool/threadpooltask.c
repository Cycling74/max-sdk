
// threadpooltask.c

#include "ext.h"
#include "ext_obex.h"
#include "ext_systhread.h"
#include "threadpooltask.h"


// POSSIBLE IMPROVEMENT:
// could reduce latency and polling, if we used cond vars instead of sleeping threads
// a good pthread tutorial is online at http://www.laptev.org/doc/pthreads.html#condvar
// for the most part you, can just replace the use "pthread" with "systhread"


#define THREADPOOLTASK_THREAD_COUNT		4
#define THREADPOOLTASK_SLEEPTIME		5

// request state
#define THREADPOOLTASK_REQ_COMPLETE		0
#define THREADPOOLTASK_REQ_PENDING		1
#define THREADPOOLTASK_REQ_PROCESSING	2


#define THREADPOOLTASK_MUTEX_NEW 	(systhread_mutex_new((t_systhread_mutex *)&s_threadpooltask_mutex,0))
#define THREADPOOLTASK_MUTEX_LOCK 	(systhread_mutex_lock((t_systhread_mutex)s_threadpooltask_mutex))
#define THREADPOOLTASK_MUTEX_UNLOCK 	(systhread_mutex_unlock((t_systhread_mutex)s_threadpooltask_mutex))

// private
void threadpooltask_terminate(void);
void threadpooltask_threadproc(void);
long threadpooltask_makerequest(t_threadpooltask *task);
long threadpooltask_getrequest(t_threadpooltask **task);
void threadpooltask_completerequest(t_threadpooltask *task);

typedef	struct _threadpooltask_method_caller
{
	t_object	*obtask;
	t_symbol	*mtask;
	long		actask;
	t_atom		*avtask;
	t_object	*obcomp;
	t_symbol	*mcomp;
	long		accomp;
	t_atom		*avcomp;

} t_threadpooltask_method_caller;

void threadpooltask_method_caller_task(t_threadpooltask_method_caller *x);
void threadpooltask_method_caller_complete(t_threadpooltask_method_caller *x);
void threadpooltask_method_caller_free(t_threadpooltask_method_caller *x);

static t_systhread			s_threadpooltask_thread_pool[THREADPOOLTASK_THREAD_COUNT];
static t_systhread_mutex	s_threadpooltask_mutex = NULL;
static t_linklist			*s_threadpooltask_requestlist = NULL;
static t_linklist			*s_threadpooltask_executelist = NULL;
static long					s_threadpooltask_numrequests = 0;
static long					s_threadpooltask_init = 0;
static long					s_threadpooltask_exit = 0;
static long					s_threadpooltask_id = 0;


void threadpooltask_init(void)
{
	long i,err;

	if (s_threadpooltask_init)
		return;

	THREADPOOLTASK_MUTEX_NEW;
	s_threadpooltask_numrequests = 0;
	s_threadpooltask_init = 1;
	s_threadpooltask_requestlist = linklist_new();
	s_threadpooltask_executelist = linklist_new();

	for (i=0; i<THREADPOOLTASK_THREAD_COUNT; i++) {
		if ((err=systhread_create((method)threadpooltask_threadproc,NULL,0,0,0,s_threadpooltask_thread_pool+i))) {
			error("threadpooltask thread could not be created: %d", err);
			s_threadpooltask_thread_pool[i] = NULL;
		}
	}
	quittask_install((method)threadpooltask_terminate,NULL);
}

void threadpooltask_terminate(void)
{
	long i;

	s_threadpooltask_exit = 1;
	for (i=0; i<THREADPOOLTASK_THREAD_COUNT; i++) {
		if (s_threadpooltask_thread_pool[i]) {
			// may wish to join instead?
			systhread_terminate(s_threadpooltask_thread_pool[i]);
			s_threadpooltask_thread_pool[i] = NULL;
		}
	}
	systhread_mutex_free(s_threadpooltask_mutex);
}

void threadpooltask_threadproc(void)
{
	t_threadpooltask *r;

	while (true) {
		if (threadpooltask_getrequest(&r)<0) {
			systhread_sleep(THREADPOOLTASK_SLEEPTIME); // could change this number dynamically, or use condvars
		} else {
			if (r) {
				r->state = THREADPOOLTASK_REQ_PROCESSING;
				threadpooltask_completerequest(r);
			}
		}
	}
}

long threadpooltask_makerequest(t_threadpooltask *task)
{
	long rv=-1;

	if (s_threadpooltask_exit)
		return -1;

	THREADPOOLTASK_MUTEX_LOCK;
	linklist_append(s_threadpooltask_requestlist,task);
	s_threadpooltask_numrequests++;
	THREADPOOLTASK_MUTEX_UNLOCK;

	rv = 0;

	return rv;
}

long threadpooltask_getrequest(t_threadpooltask **task)
{
	long  rv=-1;

	THREADPOOLTASK_MUTEX_LOCK;
	if (s_threadpooltask_numrequests>0) {
		*task = (t_threadpooltask *)linklist_getindex(s_threadpooltask_requestlist,0);
		linklist_chuckindex(s_threadpooltask_requestlist,0);
		linklist_append(s_threadpooltask_executelist,*task);
		s_threadpooltask_numrequests--;
		rv = 0;
	} else {
		*task = NULL;
	}
	THREADPOOLTASK_MUTEX_UNLOCK;
	return rv;
}

void threadpooltask_completerequest(t_threadpooltask *task)
{
	if (task&&task->cbtask) {
		(*((method)task->cbtask))(task->owner,task->args,task);
	}
	task->state = THREADPOOLTASK_REQ_COMPLETE; // redundant to set state
	if (task&&task->cbcomplete) {
		(*((method)task->cbcomplete))(task->owner,task->args,task);
	}

	THREADPOOLTASK_MUTEX_LOCK;
	linklist_chuckobject(s_threadpooltask_executelist,task);
	THREADPOOLTASK_MUTEX_UNLOCK;

	sysmem_freeptr(task);
}

typedef struct _threadpooltask_requestmatch
{
	t_object	*owner;
	t_linklist	*list;
} t_threadpooltask_requestmatch;

void threadpooltask_requestmatch_fn(t_threadpooltask *task, t_threadpooltask_requestmatch *match);
void threadpooltask_requestmatch_fn(t_threadpooltask *task, t_threadpooltask_requestmatch *match)
{
	t_threadpooltask_method_caller *caller;

	if (task&&match) {
		if (task->owner==match->owner)
			linklist_append(match->list,task);
		if ((void *)task->cbtask==(void *)threadpooltask_method_caller_task) {
			caller = (t_threadpooltask_method_caller *)task->owner;
			if (caller->obtask==match->owner || caller->obcomp==match->owner)
				linklist_append(match->list,task);
		}
	}
}

t_linklist *threadpooltask_object_requestlist(t_object *owner);
t_linklist *threadpooltask_object_requestlist(t_object *owner)
{
	t_linklist *list=NULL;
	t_threadpooltask_requestmatch match;

	list = linklist_new();
	linklist_flags(list,OBJ_FLAG_REF);
	match.owner = owner;
	match.list = list;

	THREADPOOLTASK_MUTEX_LOCK;
	linklist_funall(s_threadpooltask_requestlist,(method)threadpooltask_requestmatch_fn,(void *)&match);
	linklist_funall(s_threadpooltask_executelist,(method)threadpooltask_requestmatch_fn,(void *)&match);
	THREADPOOLTASK_MUTEX_UNLOCK;

	return list;
}

void threadpooltask_purge_object(t_object *owner)
{
	t_linklist *list;
	t_threadpooltask *task;

	// build linklist of requests whose owner pointer matches
	list = threadpooltask_object_requestlist(owner);
	// call threadpooltask_cancel on each one
	while ((task = (t_threadpooltask *)linklist_getindex(list,0))) {
		threadpooltask_cancel(task);
		linklist_chuckindex(list,0);
	}
	linklist_chuck(list);
}

void threadpooltask_join_object(t_object *owner)
{
	t_linklist *list;
	t_threadpooltask *task;

	// build linklist of requests whose owner pointer matches
	list = threadpooltask_object_requestlist(owner);
	// call threadpooltask_join on each one
	while ((task = (t_threadpooltask *)linklist_getindex(list,0))) {
		threadpooltask_join(task);
		linklist_chuckindex(list,0);
	}
	linklist_chuck(list);
}

long threadpooltask_cancel(t_threadpooltask *task)
{
	long i,wait=FALSE;
	long rv = -1;

	THREADPOOLTASK_MUTEX_LOCK;
	i = linklist_objptr2index(s_threadpooltask_requestlist,task);
	if (i>=0) {
		linklist_chuckindex(s_threadpooltask_requestlist,i);
		if ((void *)task->cbtask==(void *)threadpooltask_method_caller_task) {
			threadpooltask_method_caller_free((t_threadpooltask_method_caller *)task->owner);
		}
		sysmem_freeptr(task);
		rv = 0; // found and cancelled
	} else {
		i = linklist_objptr2index(s_threadpooltask_executelist,task);
		wait = (i>=0);
		rv = 1; // found and joined
	}
	THREADPOOLTASK_MUTEX_UNLOCK;

	// if the task is executing, stall
	while (wait) {
		systhread_sleep(THREADPOOLTASK_SLEEPTIME);
		i = linklist_objptr2index(s_threadpooltask_executelist,task);
		wait = (i>=0);
	}
	return rv;
}


long threadpooltask_join(t_threadpooltask *task)
{
	long i,j,wait=TRUE;
	long rv = -1;

	while (wait) {
		THREADPOOLTASK_MUTEX_LOCK;
		i = linklist_objptr2index(s_threadpooltask_requestlist,task);
		j = linklist_objptr2index(s_threadpooltask_executelist,task);
		if (i>=0 || j>=0) {
			wait = TRUE;
			rv = 0; // found and joined
		} else {
			wait = FALSE;
		}
		THREADPOOLTASK_MUTEX_UNLOCK;
		if (wait)
			systhread_sleep(THREADPOOLTASK_SLEEPTIME);
	}
	return rv;
}

long threadpooltask_execute(t_object *owner, void *args, method cbtask, method cbcomplete, t_threadpooltask **task, long flags)
{
	long err=-1;
	t_threadpooltask *bgt;

	if (!s_threadpooltask_init)
		threadpooltask_init();

	if ((bgt=(t_threadpooltask *)sysmem_newptr(sizeof(t_threadpooltask)))) {
		// store flags and permissions for later use
		bgt->flags = flags;
		bgt->state = THREADPOOLTASK_REQ_PENDING;
		bgt->id = s_threadpooltask_id;
		bgt->owner = owner;
		bgt->cbtask = cbtask;
		bgt->cbcomplete = cbcomplete;
		bgt->args = args;

		if (task)
			*task = bgt;

		return threadpooltask_makerequest(bgt);
	}

	return err;
}


void threadpooltask_method_caller_task(t_threadpooltask_method_caller *x)
{
	if (x&&x->obtask)
		object_method_typed(x->obtask,x->mtask,x->actask,x->avtask,NULL);
}

void threadpooltask_method_caller_complete(t_threadpooltask_method_caller *x)
{
	if (x&&x->obcomp)
		object_method_typed(x->obcomp,x->mcomp,x->accomp,x->avcomp,NULL);
	threadpooltask_method_caller_free(x);
}

void threadpooltask_method_caller_free(t_threadpooltask_method_caller *x)
{
	if (x) {
		if (x->avtask)
			sysmem_freeptr(x->avtask);
		if (x->avcomp)
			sysmem_freeptr(x->avcomp);
		sysmem_freeptr(x);
	}
}


long threadpooltask_execute_method(t_object *obtask, t_symbol *mtask, long actask, t_atom *avtask,
								   t_object *obcomp, t_symbol *mcomp, long accomp, t_atom *avcomp,  t_threadpooltask **task, long flags)
{
	long i;
	t_threadpooltask_method_caller *x;

	x = (t_threadpooltask_method_caller *) sysmem_newptr(sizeof(t_threadpooltask_method_caller));

	if (x) {
		x->obtask = obtask;
		x->mtask = mtask;
		x->actask = actask;
		if (x->actask>0)
			x->avtask = (t_atom *) sysmem_newptr(actask*sizeof(t_atom));
		else
			x->avtask = NULL;
		for (i=0; i<x->actask; i++)
			x->avtask[i] = avtask[i];

		x->obcomp = obcomp;
		x->mcomp = mcomp;
		x->accomp = accomp;
		if (x->accomp>0)
			x->avcomp = (t_atom *) sysmem_newptr(accomp*sizeof(t_atom));
		else
			x->avcomp = NULL;
		for (i=0; i<x->accomp; i++)
			x->avcomp[i] = avcomp[i];

		return threadpooltask_execute((t_object *)x,(void *)NULL,(method)threadpooltask_method_caller_task,(method)threadpooltask_method_caller_complete,task,flags);
	}

	return -1;
}



