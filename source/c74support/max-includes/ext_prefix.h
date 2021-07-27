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

////////////////////////////////////////////////////////////////////////////////
// Mac Target

#ifdef MAC_VERSION

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

#endif // MAC_VERSION


////////////////////////////////////////////////////////////////////////////////
// Linux Target

#ifdef LINUX_VERSION

#define C74_PRAGMA_STRUCT_PACKPUSH	0
#define C74_PRAGMA_STRUCT_PACK		0
#define C74_STRUCT_PACK_SIZE		4

#endif // LINUX_VERSION

////////////////////////////////////////////////////////////////////////////////
// Win32 Target

#ifdef WIN_VERSION

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

#endif // WIN_VERSION

#include "ext_prefix_includes.h"

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
#define calcoffset(x,y) offsetof(x, y)
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

// debug support
#if defined (__GNUC__) && defined(C74_X64)
#ifndef C74DebugBreak
#ifdef __x86_64__
#define C74DebugBreak asm("int3")
#elif defined(__aarch64__)
#define C74DebugBreak __asm__ volatile(".inst 0xd4200000")
#else
#warning implement me
#endif
#endif
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
// Can be disabled by defining C74_ENABLE_STATIC_ASSERT to be 0 before including max headers
#if defined(_DEBUG) && !defined(C74_ENABLE_STATIC_ASSERT)
#define C74_ENABLE_STATIC_ASSERT 1
#endif
#if C74_ENABLE_STATIC_ASSERT
#if (__cplusplus >= 201103L)
#define C74_STATIC_ASSERT(e, m) static_assert(e, m)
#else
#define C74_STATIC_ASSERT(e, m) extern char __C74_STATIC_ASSERT__[(e)?1:-1];
#endif
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

#ifdef C74_POISON_FLAVOUR_MACROS

#ifndef WIN_VERSION
#pragma GCC poison RT PLUG MFL
#endif

#endif // #ifdef C74_POISON_FLAVOUR_MACROS

#endif // _EXT_PREFIX_H_
