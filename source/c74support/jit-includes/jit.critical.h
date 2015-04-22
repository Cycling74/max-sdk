/* 
	jit.critical.h

	Copyright 2001-2003 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
	
*/

#ifndef __JIT_CRITICAL_H__
#define __JIT_CRITICAL_H__


#ifdef __cplusplus
extern "C" {
#endif

void jit_global_critical_enter(void);
void jit_global_critical_exit(void);

#ifdef __cplusplus
}
#endif

#endif
