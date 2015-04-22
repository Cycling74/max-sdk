
#ifndef _MAX_TYPES_H_
#define _MAX_TYPES_H_

#if !defined(MAC_VERSION) && !defined(WIN_VERSION)

// in case this isn't set let's set it up automatically
#ifdef __APPLE__
#define MAC_VERSION
#elif defined(_WIN32)
#define WIN_VERSION
#else
#error Unexepected build platform!
#endif

#endif  // #if !defined(MAC_VERSION) && !defined(WIN_VERSION)

#ifdef WIN_VERSION
#ifdef _WIN64
#define C74_X64
#endif 
#endif  // #ifdef WIN_VERSION

#ifdef MAC_VERSION
#if __LP64__
#define C74_X64
#endif
#endif // #ifdef MAC_VERSION

typedef unsigned int t_uint; 			///< an unsigned int as defined by the architecture / platform  @ingroup misc
typedef char t_int8; 					///< a 1-byte int  @ingroup misc
typedef unsigned char t_uint8;			///< an unsigned 1-byte int  @ingroup misc
typedef short t_int16; 					///< a 2-byte int  @ingroup misc
typedef unsigned short t_uint16; 		///< an unsigned 2-byte int  @ingroup misc
typedef int t_int32; 					///< a 4-byte int  @ingroup misc
typedef unsigned int t_uint32; 			///< an unsigned 4-byte int  @ingroup misc
typedef long long t_int64;				///< an 8-byte int  @ingroup misc
typedef unsigned long long t_uint64;	///< an unsigned 8-byte int  @ingroup misc
typedef t_uint32 t_fourcc; 				///< an integer of suitable size to hold a four char code / identifier  @ingroup misc

#ifdef C74_X64

typedef unsigned long long t_ptr_uint;	///< an unsigned pointer-sized int  @ingroup misc
typedef long long t_ptr_int; 			///< a pointer-sized int  @ingroup misc
typedef double t_atom_float;			///< the type that is an A_FLOAT in a #t_atom  @ingroup misc
typedef t_ptr_uint t_getbytes_size;		///< like size_t but for getbytes()  @ingroup misc
#define ATOM_LONG_FMT_MODIFIER "ll"
#define ATOM_FLOAT_FMT_MODIFIER "l"		// for scanf "%lf" will read into a double 

#ifdef WIN_VERSION
#define INT32_FMT_MODIFIER ""
#define INT64_FMT_MODIFIER "ll"
#endif

#ifdef MAC_VERSION
#define INT32_FMT_MODIFIER ""
#define INT64_FMT_MODIFIER "l"
#endif

#else

typedef unsigned long t_ptr_uint;		///< an unsigned pointer-sized int  @ingroup misc
typedef long t_ptr_int; 				///< a pointer-sized int  @ingroup misc
typedef float t_atom_float; 			///< the type that is an A_FLOAT in a #t_atom  @ingroup misc
typedef short t_getbytes_size; 			///< like size_t but for getbytes()  @ingroup misc
#define ATOM_LONG_FMT_MODIFIER "l"
#define ATOM_FLOAT_FMT_MODIFIER ""		// for scanf we just want "%f" for scanf to read a float 
#define INT32_FMT_MODIFIER ""
#define INT64_FMT_MODIFIER "ll"
#endif

#define C74_INT16_MAX		32767
#define C74_INT32_MAX		2147483647
#define C74_INT64_MAX		9223372036854775807LL
#define C74_INT16_MIN		(-C74_INT16_MAX-1) 
#define C74_INT32_MIN		(-C74_INT32_MAX-1) 
#define C74_INT64_MIN		(-C74_INT64_MAX-1)
#define C74_UINT16_MAX		65535
#define C74_UINT32_MAX		4294967295U
#define C74_UINT64_MAX		18446744073709551615ULL

#ifdef C74_X64
#define C74_PTR_INT_MIN		C74_INT64_MIN
#define C74_PTR_INT_MAX		C74_INT64_MAX
#define C74_PTR_UINT_MAX	C74_UINT64_MAX
#else
#define C74_PTR_INT_MIN		C74_INT32_MIN
#define C74_PTR_INT_MAX		C74_INT32_MAX
#define C74_PTR_UINT_MAX	C74_UINT32_MAX
#endif

#ifdef MAC_VERSION
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
#endif

#ifdef MAC_VERSION
// typedef FSIORefNum t_refnum;		// don't want to require Carbon include for build
#ifdef C74_X64
typedef int t_refnum;    // for x64 an FSIORefNum is an int
#else
typedef short t_refnum; 
#endif

#endif

#endif // #ifdef _MAX_TYPES_H_
