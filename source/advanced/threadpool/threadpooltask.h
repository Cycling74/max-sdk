// threadpooltask.h
#ifndef __THREADPOOLTASK_H__
#define __THREADPOOLTASK_H__

#if C74_PRAGMA_STRUCT_PACKPUSH
#pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
#pragma pack(2)
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct _threadpooltask
{
	long				flags; // rfu
	long				state;
	long				id;
	t_object			*owner;
	void				*args;
	method				cbtask;
	method				cbcomplete;
} t_threadpooltask;

void threadpooltask_init(void);
long threadpooltask_execute(t_object *owner, void *args, method cbtask, method cbcomplete, t_threadpooltask **task, long flags);
long threadpooltask_execute_method(t_object *obtask, t_symbol *mtask, long actask, t_atom *avtask,
								   t_object *obcomp, t_symbol *mcomp, long accomp, t_atom *avcomp,  t_threadpooltask **task, long flags);
void threadpooltask_purge_object(t_object *owner);
void threadpooltask_join_object(t_object *owner);
long threadpooltask_cancel(t_threadpooltask *task);
long threadpooltask_join(t_threadpooltask *task);


#ifdef __cplusplus
}
#endif // __cplusplus

#if C74_PRAGMA_STRUCT_PACKPUSH
#pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
#pragma pack()
#endif


#endif // __THREADPOOLTASK_H__
