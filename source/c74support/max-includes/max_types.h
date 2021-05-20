#ifndef _MAX_TYPES_H_
#define _MAX_TYPES_H_

#include "ext_infer_system.h"

#include <stdint.h>

typedef unsigned int t_uint; 			///< an unsigned int as defined by the architecture / platform  @ingroup misc
typedef int8_t t_int8; 					///< a 1-byte int  @ingroup misc
typedef uint8_t t_uint8;		    	///< an unsigned 1-byte int  @ingroup misc
typedef int16_t t_int16; 				///< a 2-byte int  @ingroup misc
typedef uint16_t t_uint16; 		        ///< an unsigned 2-byte int  @ingroup misc
typedef int32_t t_int32; 				///< a 4-byte int  @ingroup misc
typedef uint32_t t_uint32; 			    ///< an unsigned 4-byte int  @ingroup misc
typedef int64_t t_int64;				///< an 8-byte int  @ingroup misc
typedef uint64_t t_uint64;	            ///< an unsigned 8-byte int  @ingroup misc
typedef t_uint32 t_fourcc; 				///< an integer of suitable size to hold a four char code / identifier  @ingroup misc


typedef uintptr_t t_ptr_uint;	///< an unsigned pointer-sized int  @ingroup misc
typedef  intptr_t t_ptr_int; 			///< a pointer-sized int  @ingroup misc

#ifdef C74_X64
typedef double t_atom_float;			///< the type that is an A_FLOAT in a #t_atom  @ingroup misc
typedef t_ptr_uint t_getbytes_size;		///< like size_t but for getbytes()  @ingroup misc
#define ATOM_LONG_FMT_MODIFIER "ll"
#define ATOM_FLOAT_FMT_MODIFIER "l"		// for scanf "%lf" will read into a double 

#ifdef WIN_VERSION
#define INT32_FMT_MODIFIER ""
#define INT64_FMT_MODIFIER "ll"
#endif

#if defined(MAC_VERSION) || defined(LINUX_VERSION)
#define INT32_FMT_MODIFIER ""
#define INT64_FMT_MODIFIER "l"
#endif

#else
typedef float t_atom_float; 			///< the type that is an A_FLOAT in a #t_atom  @ingroup misc
typedef short t_getbytes_size; 			///< like size_t but for getbytes()  @ingroup misc
#define ATOM_LONG_FMT_MODIFIER "l"
#define ATOM_FLOAT_FMT_MODIFIER ""		// for scanf we just want "%f" for scanf to read a float 
#define INT32_FMT_MODIFIER ""
#define INT64_FMT_MODIFIER "ll"
#endif

#define C74_INT16_MAX		INT16_MAX
#define C74_INT32_MAX		INT32_MAX
#define C74_INT64_MAX		INT64_MAX
#define C74_INT16_MIN		INT16_MIN
#define C74_INT32_MIN		INT32_MIN
#define C74_INT64_MIN		INT64_MIN
#define C74_UINT16_MAX		UINT16_MAX
#define C74_UINT32_MAX		UINT32_MAX
#define C74_UINT64_MAX		UINT64_MAX

#define C74_PTR_INT_MIN		INTPTR_MIN
#define C74_PTR_INT_MAX		INTPTR_MAX
#define C74_PTR_UINT_MAX	UINTPTR_MAX

#define C74_ATOM_LONG_MIN	C74_PTR_INT_MIN
#define C74_ATOM_LONG_MAX	C74_PTR_INT_MAX

#if defined(MAC_VERSION) || defined(LINUX_VERSION)
#define C74_LONG_INT_MIN	C74_PTR_INT_MIN
#define C74_LONG_INT_MAX	C74_PTR_INT_MAX
#define C74_ULONG_INT_MAX	C74_PTR_UINT_MAX
#else
#define C74_LONG_INT_MIN	C74_INT32_MIN
#define C74_LONG_INT_MAX	C74_INT32_MAX
#define C74_ULONG_INT_MAX	C74_UINT32_MAX
#endif

typedef t_ptr_int t_int;			///< an integer  @ingroup misc
typedef t_ptr_uint t_ptr_size;		///< unsigned pointer-sized value for counting (like size_t)  @ingroup misc
typedef t_ptr_int t_atom_long;		///< the type that is an A_LONG in a #t_atom  @ingroup misc
typedef t_atom_long t_max_err;		///< an integer value suitable to be returned as an error code  @ingroup misc

typedef char **t_handle;			///< a handle (address of a pointer)  @ingroup misc
typedef char *t_ptr;				///< a pointer  @ingroup misc

typedef t_uint8 t_bool; 			///< a true/false variable  @ingroup misc
typedef t_int16 t_filepath;			///< i.e. path/vol in file APIs identifying a folder  @ingroup misc

#ifdef WIN_VERSION
typedef t_int16 t_refnum;

#ifndef __cplusplus 
#define bool int
#define false (0)
#define true (1)
#endif

#endif

#ifdef MAC_VERSION
// typedef FSIORefNum t_refnum;		// don't want to require Carbon include for build
#ifdef C74_X64
typedef int t_refnum;    // for x64 an FSIORefNum is an int
#else
typedef short t_refnum; 
#endif
#endif // #ifdef MAC_VERSION

#ifdef LINUX_VERSION
typedef int t_refnum;
#endif


#ifndef bool
#include <stdbool.h>
#endif

/** Standard values returned by function calls with a return type of #t_max_err
	@ingroup misc */
typedef enum {
	MAX_ERR_NONE =			0,	///< No error
	MAX_ERR_GENERIC =		-1,	///< Generic error
	MAX_ERR_INVALID_PTR =	-2,	///< Invalid Pointer
	MAX_ERR_DUPLICATE =		-3,	///< Duplicate
	MAX_ERR_OUT_OF_MEM =	-4	///< Out of memory
} e_max_errorcodes;

#endif // #ifdef _MAX_TYPES_H_
