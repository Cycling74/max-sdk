/*
	jit.platform.h

	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com

*/

#ifndef __JIT_PLATFORM_H__
#define __JIT_PLATFORM_H__

#ifndef WIN_VERSION
#define MAC
#endif

#ifdef WIN_VERSION

// the maxcrt is now deprecated
// we recommend you link dynamically to the VS2013 CRT as this is what max currently uses
#define MAXAPI_MAXCRT_DEPRECATED

#if !defined(MAXAPI_USE_MSCRT) && !defined(MAXAPI_MAXCRT_DEPRECATED)

#ifndef _CRT_NOFORCE_MANIFEST
#define _CRT_NOFORCE_MANIFEST
#endif

#ifndef _STL_NOFORCE_MANIFEST
#define _STL_NOFORCE_MANIFEST
#endif

#ifndef _DEBUG
// for debug use the standard microsoft C runtime

#pragma comment(linker,"/NODEFAULTLIB:msvcrt.lib")
#pragma comment(lib,"maxcrt.lib")
#pragma comment(linker,"/NODEFAULTLIB:msvcprt.lib")
#pragma comment(lib,"maxcrt_p.lib")
#endif

#endif // #if !defined(MAXAPI_USE_MSCRT) && !defined(MAXAPI_MAXCRT_DEPRECATED)

#define JIT_EX_DATA_DECL __declspec(dllexport)
#ifdef WIN_JITLIB
#define JIT_EX_DATA extern __declspec(dllexport)
#else
#define JIT_EX_DATA extern __declspec(dllimport)
#endif //WIN_JITLIB
#else
#define JIT_EX_DATA_DECL
#define JIT_EX_DATA extern
#endif // WIN_VERSION

#define C74_MAX

#ifdef MAC
#include "jit.mac.h"
#else
#define PREFER_POST_INC
#ifdef WIN_JITLIB
//used by jitlib only
#ifdef C74_USING_QUICKTIME
#include "QTML.h"
#include "jit.mac.h"
#define ushort ushort
#define FREDDIE ushort
#define GetPixRowBytes QTGetPixMapHandleRowBytes
#endif  // #ifdef C74_USING_QUICKTIME
#endif //WIN_JITLIB
#endif

// weak link macros
#ifdef __APPLE_CC__
#define JIT_WEAKLINK __attribute((weak_import))
#else
#define JIT_WEAKLINK
#endif

#ifdef C74_MAX
#include "jit.max.h"
#endif

//load test

#ifdef __APPLE_CC__
#define IS_JIT_LIBRARY_AVAILABLE (jit_object_method != NULL)
#else
#define IS_JIT_LIBRARY_AVAILABLE (jit_object_method != NULL)
#endif

//endian issues
#include "jit.byteorder.h"

//thread related
#include "jit.critical.h"

// disable CG entirely
#if 0 //!defined(C74_X64)
#define C74_SUPPORT_CG
#endif

//vector
#ifdef WIN_VERSION
#define JIT_CAN_ALTIVEC 0
#else
// may want a better way to detect Mac Intel
#if __i386__
#define JIT_CAN_ALTIVEC 0
#else
// rbs: altivec is never true now, we should clean this stuff up
#define JIT_CAN_ALTIVEC 0
#endif

#endif // !WIN_VERSION

//speed macros
#ifdef PREFER_POST_INC
#define FAST_INC_SETUP(x)			// nothing
#define FAST_INC(x)			((x)++)
#define FAST_INC_DEREF(x)	(*((x)++))
#define FAST_DEC_SETUP(x)			// nothing
#define FAST_DEC(x)			((x)--)
#define FAST_DEC_DEREF(x)	(*((x)--))
#else
#define FAST_INC_SETUP(x)	(--(x)) 	// predec
#define FAST_INC(x)			(++(x))
#define FAST_INC_DEREF(x)	(*(++(x)))
#define FAST_DEC_SETUP(x)	(++(x))		// preinc
#define FAST_DEC(x)			(--(x))
#define FAST_DEC_DEREF(x)	(*(--(x)))
#endif

//utils
#ifndef calcoffset
#define calcoffset(x,y) ((long)(&(((x *)0L)->y)))
#endif

#ifdef WIN_VERSION
#define	hypot _hypot
// not sure that we want to define pascal to be nothing
// windef.h defines it to be __stdcall but that gives an error
// when used like: pascal void foo() as it is expecting
//  void __stdcall foo()
#define pascal
#endif

#endif
