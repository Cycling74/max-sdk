// ext_backgroundtask.h
#ifndef __BACKGROUNDTASK_H__
#define __BACKGROUNDTASK_H__

#if C74_PRAGMA_STRUCT_PACKPUSH
#pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
#pragma pack(2)
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef __BACKGROUNDTASK_H_INTERNAL__
	
typedef struct _backgroundtask 
{
	void *opaque;
} t_backgroundtask;
	
#endif // __BACKGROUNDTASK_H_INTERNAL__

long backgroundtask_execute(t_object *owner, void *args, method cbtask, method cbcomplete, t_backgroundtask **task, long flags);
long backgroundtask_execute_method(t_object *obtask, t_symbol *mtask, long actask, t_atom *avtask, 
										  t_object *obcomp, t_symbol *mcomp, long accomp, t_atom *avcomp,  t_backgroundtask **task, long flags);
void backgroundtask_purge_object(t_object *owner);
void backgroundtask_join_object(t_object *owner);
long backgroundtask_cancel(t_backgroundtask *task);
long backgroundtask_join(t_backgroundtask *task);
	

#ifdef __cplusplus
}
#endif // __cplusplus

#if C74_PRAGMA_STRUCT_PACKPUSH
#pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
#pragma pack()
#endif


#endif // __BACKGROUNDTASK_H__
