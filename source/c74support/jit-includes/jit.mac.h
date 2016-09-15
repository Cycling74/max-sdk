/* 
	jit.mac.h

	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
	
*/

#ifndef __JIT_MAC_H__
#define __JIT_MAC_H__

#if (__APPLE_CC__||TARGET_RT_MAC_MACHO)
// can use prefix files for faster compilation, in which case, the following are 
// redundant, but harmless, as they will exit quickly based on header defines
#include <Carbon/Carbon.h>
#else
#include <MacTypes.h>
#include <devices.h> 
#include <MacWindows.h> 
#include <controls.h> 
#include <Quickdraw.h>
#include <QDOffscreen.h>
#include <Aliases.h>
#endif // TARGET_RT_MAC_MACHO

#ifndef TRUE
#define TRUE 	1
#endif
#ifndef FALSE
#define FALSE 	0
#endif

#if (TARGET_API_MAC_CARBON)
#define StripAddress(theAddress) ((Ptr)(theAddress))
#endif


#ifdef __cplusplus
extern "C" {
#endif

OSErr jit_mac_gestalt(OSType selector, long *response);

#ifdef __cplusplus
}
#endif

#endif //__JIT_MAC_H__
