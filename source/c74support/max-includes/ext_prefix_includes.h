//
//  ext_prefix_includes.h
//  max
//
//  Created by Jeremy Bernstein on 27.07.21.
//

#ifndef __EXT_PREFIX_INCLUDES_H__
#define __EXT_PREFIX_INCLUDES_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MAC_VERSION

// If the prefix header containing #include <Carbon/Carbon.h> is not present, then we include
// a minimal set of required headers here.
#ifndef __MACTYPES__
#include <MacTypes.h>
#endif

#include <sys/types.h>

#endif // MAC_VERSION

#ifdef WIN_VERSION

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <malloc.h>
#include <windows.h>
#include <richedit.h>
#include <commctrl.h>

#endif // WIN_VERSION

// c standard library
#include <assert.h>
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#ifdef __cplusplus
}
#endif

#endif /* __EXT_PREFIX_INCLUDES_H__ */
