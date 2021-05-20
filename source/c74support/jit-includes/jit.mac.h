#ifndef __JIT_MAC_H__
#define __JIT_MAC_H__

#include "ext_prefix.h"

#if MAC_VERSION

#ifndef TRUE
#define TRUE 	1
#endif
#ifndef FALSE
#define FALSE 	0
#endif

#ifdef __cplusplus
extern "C" {
#endif

OSErr jit_mac_gestalt(OSType selector, long *response);

#ifdef __cplusplus
}
#endif

#endif // MAC_VERSION
#endif //__JIT_MAC_H__
