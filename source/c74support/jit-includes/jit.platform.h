/*
	jit.platform.h

	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com

*/

#ifndef __JIT_PLATFORM_H__
#define __JIT_PLATFORM_H__

#include "ext_infer_system.h"

#ifdef WIN_VERSION

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

// weak link macros
#ifdef __APPLE_CC__
#define JIT_WEAKLINK __attribute((weak_import))
#else
#define JIT_WEAKLINK
#endif

#ifdef C74_MAX
#include "jit.max.h"
#endif


//endian issues
#include "jit.byteorder.h"

//thread related
#include "jit.critical.h"

// rbs: altivec is never true now, we should clean this stuff up
#define JIT_CAN_ALTIVEC 0
JIT_EX_DATA long _jit_altivec;

//speed macros -- we currently always use post inc

#define PREFER_POST_INC
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
#endif

#ifdef MAC_VERSION

#include <AvailabilityMacros.h>

#endif // #ifdef MAC_VERSION

#endif // #ifndef __JIT_PLATFORM_H__
