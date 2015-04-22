#ifndef _EXT_SYSPARALLEL_H_
#define _EXT_SYSPARALLEL_H_

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

BEGIN_USING_C_LINKAGE

#define SYSPARALLEL_PRIORITY_DEFAULT		0x00
#define SYSPARALLEL_PRIORITY_LOW			0x00
#define SYSPARALLEL_PRIORITY_MEDIUM			0x04
#define SYSPARALLEL_PRIORITY_HIGH			0x08
#define SYSPARALLEL_PRIORITY_TASK_LOCAL		0xa0

#define SYSPARALLEL_MAX_WORKERS			64

#define SYSPARALLEL_STATE_IDLE			0
#define SYSPARALLEL_STATE_RUN			1
#define SYSPARALLEL_STATE_DONE			0		// changed to be the same as IDLE since it means the same thing
#define SYSPARALLEL_STATE_QUIT			3

#define SYSPARALLEL_TASK_FLAG_WORKERTRIGGERS		(0x00000001)		// first worker signals other works as necessary
		
typedef struct _sysparallel_task
{
	t_object	ob;
	void		*obex;
	void		*data;			// global task data
	method 		workerproc;		// worker callback function 
	long 		workercount;	// number of workers to use
	struct _sysparallel_worker	**workers;	// worker array		
	unsigned char priority;		// thread priority 
	char		benchmark;		// benchmark
	long		iteration;		// for benchmarking 
	double		begintime;		// for benchmarking
	double		endtime;		// for benchmarking
	long		cancel;			// for cancel request
	struct _sysparallel_thread_pool *pool; // this will be NULL. unless using SYSPARALLEL_PRIORITY_TASK_LOCAL
	long 		maxworkercount;	// maximum number of workers to use
	long		flags;			// flags can be set after sysparallel_task_new but before running
} t_sysparallel_task;


typedef struct _sysparallel_worker
{
	t_object		ob;
	void			*obex;
	void			*data;			// worker specific data
	method 			workerproc;		// worker callback function, worker object passed in
	t_sysparallel_task *task;		// pointer to task parent (can be used to access global task data)
	long			id;				// worker id
	double			begintime;		// for benchmarking (uses task info)
	double			endtime;		// for benchmarking (uses task info)
	
} t_sysparallel_worker;


void sysparallel_init(void);
long sysparallel_processorcount(void);
t_sysparallel_task *sysparallel_task_new(void *data, method workerproc, long maxworkercount);
t_max_err sysparallel_task_workercount(t_sysparallel_task *x, long workercount);
t_max_err sysparallel_task_execute(t_sysparallel_task *x);
void sysparallel_task_signalworkers(t_sysparallel_task *x, long count); 
t_max_err sysparallel_task_cancel(t_sysparallel_task *x);
void sysparallel_task_free(t_sysparallel_task *x);
void sysparallel_task_benchprint(t_sysparallel_task *x);
void sysparallel_task_data(t_sysparallel_task *x, void * data);
void sysparallel_task_workerproc(t_sysparallel_task *x, method workerproc);

t_sysparallel_worker *sysparallel_worker_new(void *data, method workerproc, t_sysparallel_task *task);
t_max_err sysparallel_worker_execute(t_sysparallel_worker *x);
void sysparallel_worker_free(t_sysparallel_worker *x);

END_USING_C_LINKAGE

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#endif // _EXT_SYSPARALLEL_H_
