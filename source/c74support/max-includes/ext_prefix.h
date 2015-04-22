#include "max_types.h"  // safety check to insure C74_X64 is defined appropriately

#ifndef _EXT_PREFIX_H_
#define _EXT_PREFIX_H_

////////////////////////////////////////////////////////////////////////////////
// macros

#ifdef __cplusplus
/**
	Ensure that any definitions following this macro use a C-linkage, not a C++ linkage.
	The Max API uses C-linkage.
	This is important for objects written in C++ or that use a C++ compiler.
	This macro must be balanced with the #END_USING_C_LINKAGE macro.
	@ingroup misc
*/
#define BEGIN_USING_C_LINKAGE \
	extern "C" {
#else
/**
	Ensure that any definitions following this macro use a C-linkage, not a C++ linkage.
	The Max API uses C-linkage.
	This is important for objects written in C++ or that use a C++ compiler.
	This macro must be balanced with the #END_USING_C_LINKAGE macro.
	@ingroup misc
*/
#define BEGIN_USING_C_LINKAGE
#endif // __cplusplus

#ifdef __cplusplus
/**
	Close a definition section that was opened using #BEGIN_USING_C_LINKAGE.
	@ingroup misc
*/
#define END_USING_C_LINKAGE \
	}
#else
/**
	Close a definition section that was opened using #BEGIN_USING_C_LINKAGE.
	@ingroup misc
*/
#define END_USING_C_LINKAGE
#endif // __cplusplus

#ifdef C74_X64
// anything we want to define only for x64 builds here? 
#else
// not x64? let's enable quicktime, if it was asked for 
// but note that only on windows do we explicitly ask for it
#if defined(USE_QTML) || defined(INCLUDE_APPLE_HEADERS) || defined(MAC_VERSION)
#define C74_USING_QUICKTIME 1
#endif

#endif

#ifdef calcoffset
	// The ifdefs for this macro have been set up like this so that Doxygen can document this macro on a Mac [TAP]
#else
	/** 
		Find byte offset of a named member of a struct, relative to the beginning of that struct.
		@ingroup misc
		@param	x	The name of the struct
		@param	y	The name of the member
		@return		A pointer-sized integer representing the number of bytes into the struct where the member begins.
	*/
	#define calcoffset(x,y) ((t_ptr_int)(&(((x *)0L)->y)))
#endif

#ifdef structmembersize
	// The ifdefs for this macro have been set up like this so that Doxygen can document this macro on a Mac [TAP]
#else
	/** 
		Find size of a named member of a struct.
		@ingroup misc
		@param	structname	The name of the struct
		@param	membername	The name of the member
		@return		The size of the member of the struct.
	*/
	#define structmembersize(structname, membername) (sizeof(((structname*)0)->membername))
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

#endif // #ifdef WIN_VERSION

////////////////////////////////////////////////////////////////////////////////
// Mac Target

#ifdef MAC_VERSION
#ifndef powerc
#pragma d0_pointers on
#endif
#define _K( k )	

#define INCLUDE_APPLE_HEADERS

#if !TARGET_API_MAC_CARBON
#define GRAFPORT_IN_WIND
#endif

#if 1 // defined( __MOTO__ ) && !defined( __cplusplus )
#define FPTR_ELLIPSES		0
#else 
#define FPTR_ELLIPSES		1
#endif

// the C74_PRAGMA_STRUCT_PACK* macros are used to ensure that 
// Win32 builds of Max externals use a 2 byte struct packing 
// for all Max structs in projects that have a default struct 
// packing other than 2 (this is typically 4). On Macintosh
// the default byte packing is 4, and it is with this packing
// that all Max structs are packed on Macintosh. If for some 
// reason you are using a struct byte packing of something other
// than 4 on macintosh, there may be problems. Please let us
// know, and we can address this and the other Max header files to 
// ensure 4 byte struct packing on Macintosh in such a setting.
#define C74_PRAGMA_STRUCT_PACKPUSH	0
#define C74_PRAGMA_STRUCT_PACK		0
#define C74_STRUCT_PACK_SIZE		4

// If the prefix header containing #include <Carbon/Carbon.h> is not present, then we include 
// a minimal set of required headers here.
#ifndef __MACTYPES__
#include <MacTypes.h>
#endif
#include <sys/types.h>

#endif // MAC_VERSION

////////////////////////////////////////////////////////////////////////////////
// Win32 Target

#ifdef WIN_VERSION

#if !defined( __cplusplus )
#define FPTR_ELLIPSES		0
#else
#define FPTR_ELLIPSES		1
#endif

#ifndef C74_X64

// the C74_PRAGMA_STRUCT_PACK* macros are used to ensure that 
// Win32 builds of Max externals use a 2 byte struct packing 
// for all Max structs in projects that have a default struct 
// packing other than 2 (this is typically 4). On Macintosh
// the default byte packing is 4, and it is with this packing
// that all Max structs are packed on Macintosh. If for some 
// reason you are using a struct byte packing of something other
// than 4 on macintosh, there may be problems. Please let us
// know, and we can address this and the other Max header files to 
// ensure 4 byte struct packing on Macintosh in such a setting.
#if ((defined(_MSC_VER) && !defined(__MWERKS__)) || (defined(__MWERKS__)&&(__MWERKS__ >= 0x0900)))
// Visual C++ or Metrowerks >=0x0900 support pack(push,n)
// this may not accomodate building for a windows target
// using Metrowerks on a macintosh, which might need to use 
// the pragma align statement.
#define C74_PRAGMA_STRUCT_PACKPUSH	1
#else
#define C74_PRAGMA_STRUCT_PACKPUSH	0
#endif

#define C74_PRAGMA_STRUCT_PACK		1
#define C74_STRUCT_PACK_SIZE		2

#else  // #if !C74_X64
#define C74_PRAGMA_STRUCT_PACKPUSH	0		// don't specify packing for x64 target, use default
#define C74_PRAGMA_STRUCT_PACKPUSH	0
#endif

// promote this warning to an error because 
// it helps catch using long* when we really need t_atom_long* for x64
#pragma warning ( error : 4133 ) // incompatible types 

#if defined(DISABLE_A_BUNCH_OF_WINDOWS_WARNINGS)
#pragma warning( disable : 4005 ) // macro redefinition
#pragma warning( disable : 4101 ) // unreferenced local
#pragma warning( disable : 4800 ) // forcing value to bool 'true' or 'false'
#pragma warning( disable : 4805 ) // unsafe mix of type 'BOOL' and type 'bool'
#pragma warning( disable : 4087 ) // 'function' declared with 'void' parameter list
#pragma warning( disable : 4068 ) // unknown pragma
#pragma warning( disable : 4244 ) // implicit larger to smaller type conversion (int + float)
#pragma warning( disable : 4245 ) // implicit unsigned/signed type conversion
#pragma warning( disable : 4305 ) // truncation from 'type1' to 'type2' (e.g. double->float)
#endif 

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif 

#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif 

// crtl
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <setjmp.h>
#include <assert.h>

// windows
#include <windows.h>
#include <richedit.h>
#include <commctrl.h>

#if (defined(USE_QTML) || defined(C74_USING_QUICKTIME) || defined(INCLUDE_APPLE_HEADERS))&& !defined(C74_X64)

#ifndef INCLUDE_APPLE_HEADERS
#define INCLUDE_APPLE_HEADERS
#endif	

#include "qtml.h"

#else

#if ((defined(USE_QTML) || defined(C74_USING_QUICKTIME) || defined(INCLUDE_APPLE_HEADERS)) && C74_x64)
#pragma message ("QuickTime is not supported for x64!")
#endif

#ifndef __cplusplus 
#define bool int
#define false ((int)0)
#define true ((int)1)
#endif

#endif  // #ifdef USE_QTML

#endif // WIN_VERSION

// debug support
#ifdef MAC_VERSION
#define C74DebugBreak asm("int3")
#endif

#ifdef WIN_VERSION
#define C74DebugBreak DebugBreak()
#endif

#ifndef C74_STR
	#define C74_STR_HELPER(x) #x
	#define C74_STR(x) C74_STR_HELPER(x)
#endif

#ifndef C74_ASSERT
#if defined(_DEBUG) || defined(DEBUG)
#define C74_ASSERT(condition) \
	if (!(condition)) { cpost("ASSERTION - failed condition: %s\n", C74_STR(condition)); C74DebugBreak; }
#else
#define C74_ASSERT(condition) 
#endif
#endif

// the following are convenient before casting to a smaller size 
// so the debug build will let you know if you are truncating unexpectedly
#define C74_ASSERT_FITS_CHAR(x)		 C74_ASSERT(((char)(x)) == (long long) (x))
#define C74_ASSERT_FITS_UCHAR(x)	 C74_ASSERT(((unsigned char)(x)) == (unsigned long long) (x))
#define C74_ASSERT_FITS_SHORT(x)	 C74_ASSERT(((short)(x)) == (long long) (x))
#define C74_ASSERT_FITS_USHORT(x)	 C74_ASSERT(((unsigned short)(x)) == (unsigned long long) (x))
#define C74_ASSERT_FITS_LONG(x)		 C74_ASSERT(((long)(x)) == (long long) (x))
#define C74_ASSERT_FITS_ULONG(x)	 C74_ASSERT(((unsigned long)(x)) == (unsigned long long)(x))
#define C74_ASSERT_FITS_INT32(x)	 C74_ASSERT(((t_int32)(x)) == (long long) (x))
#define C74_ASSERT_FITS_UINT32(x)	 C74_ASSERT(((t_uint32)(x)) == (unsigned long long) (x))
#define C74_ASSERT_FITS_PTR_INT(x)	 C74_ASSERT(((t_ptr_int)(x)) == (long long) (x))
#define C74_ASSERT_FITS_PTR_UINT(x)	 C74_ASSERT(((t_ptr_uint)(x)) == (unsigned long long) (x))

// C74_STATIC_ASSERT: generates a compile error if expression e is false 
#ifdef _DEBUG
#define ENABLE_STATIC_ASSERT
#endif
#ifdef ENABLE_STATIC_ASSERT
#define C74_STATIC_ASSERT(e, m) typedef char __C74_STATIC_ASSERT__[(e)?1:-1]
#else
#define C74_STATIC_ASSERT(e, m)
#endif

#if defined(C74_X64) && defined(WIN_VERSION)
// It used to be required to set two-byte packing of structures on windows. 
// For x64 it is important to set packing to default. 
typedef struct _testpackingstruct 
{
	t_uint8 firstmember;
	t_int32 secondmember;  //
} t_testpackingstruct;

// if external is still configured for two byte alignment this will cause a compile error
// in which case you should change the structure alignment to the compiler default
C74_STATIC_ASSERT( (calcoffset(t_testpackingstruct, secondmember) - calcoffset(t_testpackingstruct, firstmember)) > 2, "struct alignment must be set to default!" ); 

#endif

#define C74_EXTERNAL_NOT_ON_X64(name) void ext_main(void *r) { error("%s: not supported on x64", name); }
#define C74_EXTERNAL_NOT_ON_X64_QUIET void ext_main(void *r) { return; }

#endif // _EXT_PREFIX_H_
