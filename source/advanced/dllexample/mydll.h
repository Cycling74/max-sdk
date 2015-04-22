/**
	@file
	mydll - a DLL instance shared by several external objects

	@ingroup	examples

	Copyright 2013 - Cycling '74
	Timothy Place, tim@cycling74.com
*/

#include "ext.h"


// a macro to mark exported symbols in the code without requiring an external file to define them
#ifdef WIN_VERSION
// note that this is the required syntax on windows regardless of whether the compiler is msvc or gcc
#define T_EXPORT __declspec(dllexport)
#else // MAC_VERSION
// the mac uses the standard gcc syntax, you should also set the -fvisibility=hidden flag to hide the non-marked symbols
#define T_EXPORT __attribute__((visibility("default")))
#endif


// prototypes
BEGIN_USING_C_LINKAGE
void T_EXPORT mydll_init(void);
void T_EXPORT mydll_inc(void);
int  T_EXPORT mydll_getcount(void);
END_USING_C_LINKAGE
