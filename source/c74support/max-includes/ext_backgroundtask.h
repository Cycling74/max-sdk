// ext_backgroundtask.h
#ifndef __BACKGROUNDTASK_H__
#define __BACKGROUNDTASK_H__

#include "ext_prefix.h"
#include "ext_mess.h"

#if C74_PRAGMA_STRUCT_PACKPUSH
#pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
#pragma pack(2)
#endif

BEGIN_USING_C_LINKAGE

#ifndef __BACKGROUNDTASK_H_INTERNAL__
	
typedef struct _backgroundtask 
{
	void *opaque;
} t_backgroundtask;
	
#endif // __BACKGROUNDTASK_H_INTERNAL__

typedef enum {
	BACKGROUNDTASK_FLAG_COMPLETE_MAINTHREAD = 0x00000001L		// call cbcomplete callback from main thread
} e_backgroundtask_execute_flags;

long backgroundtask_execute(t_object *owner, void *args, method cbtask, method cbcomplete, t_backgroundtask **task, long flags);
long backgroundtask_execute_method(t_object *obtask, t_symbol *mtask, long actask, t_atom *avtask, 
										  t_object *obcomp, t_symbol *mcomp, long accomp, t_atom *avcomp,  t_backgroundtask **task, long flags);
void backgroundtask_purge_object(t_object *owner);
void backgroundtask_join_object(t_object *owner);
long backgroundtask_cancel(t_backgroundtask *task);
long backgroundtask_join(t_backgroundtask *task);
	
END_USING_C_LINKAGE

#if C74_PRAGMA_STRUCT_PACKPUSH
#pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
#pragma pack()
#endif

#endif // __BACKGROUNDTASK_H__
