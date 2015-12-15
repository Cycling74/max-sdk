/* 
	jit.common.h

	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
		
*/

#ifndef __JIT_COMMON_H__
#define __JIT_COMMON_H__

#ifdef __cplusplus
	extern "C" {
#endif // __cplusplus

#include "ext.h"
#include "jit.platform.h"
#include "jit.error.h"
#include "jit.file.h"
#include "jit.math.h"
#include "jit.symbols.h"
#include "jit.critical.h"
#include "ext_preprocessor.h"

#define SIZE_INT32		sizeof(t_int32)
#define SIZE_INT64		sizeof(t_int64)
#define SIZE_FLOAT32	sizeof(float)
#define SIZE_FLOAT64	sizeof(double)
#define SIZE_PTR		sizeof(t_ptr_int)

#ifndef TRUE
#define TRUE 	1
#endif
#ifndef FALSE
#define FALSE 	0
#endif

#define JIT_ATTR_GET_OPAQUE			0x00000001	///< private getter (all)          @ingroup jitter
#define JIT_ATTR_SET_OPAQUE			0x00000002	///< private setter (all)          @ingroup jitter
#define JIT_ATTR_GET_OPAQUE_USER	0x00000100	///< private getter (user)         @ingroup jitter
#define JIT_ATTR_SET_OPAQUE_USER	0x00000200	///< private setter (user)         @ingroup jitter
#define JIT_ATTR_GET_DEFER			0x00010000	///< defer getter (deprecated)     @ingroup jitter
#define JIT_ATTR_GET_USURP			0x00020000	///< usurp getter (deprecated)     @ingroup jitter
#define JIT_ATTR_GET_DEFER_LOW		0x00040000	///< defer getter                  @ingroup jitter
#define JIT_ATTR_GET_USURP_LOW		0x00080000	///< usurp getter                  @ingroup jitter
#define JIT_ATTR_SET_DEFER			0x01000000	///< defer setter (deprecated)     @ingroup jitter
#define JIT_ATTR_SET_USURP			0x02000000	///< usurp setter (deprecated)     @ingroup jitter
#define JIT_ATTR_SET_DEFER_LOW		0x04000000	///< defer setter                  @ingroup jitter
#define JIT_ATTR_SET_USURP_LOW		0x08000000	///< usurp setter                  @ingroup jitter

// t_jit_matrix_info flags
#define JIT_MATRIX_DATA_HANDLE		0x00000002	///< data is handle                                                   @ingroup jitter
#define JIT_MATRIX_DATA_REFERENCE	0x00000004 	///< data is reference to outside memory                              @ingroup jitter
#define JIT_MATRIX_DATA_PACK_TIGHT	0x00000008 	///< data is tightly packed (doesn't use standard 16 byte alignment)  @ingroup jitter
#define JIT_MATRIX_DATA_FLAGS_USE	0x00008000 	/**< necessary if using handle/reference data flags when creating     @ingroup jitter
												 * jit_matrix, however, it is never stored in matrix */ 
                                                                                                        
#define JIT_MATRIX_MAX_DIMCOUNT		32 			///< maximum dimension count                                          @ingroup jitter
#define JIT_MATRIX_MAX_PLANECOUNT	32 			///< maximum plane count                                              @ingroup jitter
                                                                                                        
// t_matrix_conv_info flags                                                                                           @ingroup jitter
#define JIT_MATRIX_CONVERT_CLAMP	0x00000001  ///< not currently used                                               @ingroup jitter
#define JIT_MATRIX_CONVERT_INTERP	0x00000002	///< use interpolation                                                @ingroup jitter
#define JIT_MATRIX_CONVERT_SRCDIM	0x00000004	///< use source dimensions                                            @ingroup jitter
#define JIT_MATRIX_CONVERT_DSTDIM	0x00000008	///< use destination dimensions                                       @ingroup jitter

typedef unsigned long 	ulong;
typedef unsigned int 	uint;
typedef unsigned short 	ushort;
typedef unsigned char 	uchar;

#include "jit.op.h"
#include "jit.linklist.h"

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

/**
 * Common attribute struct.
 * Shared by all built in attribute classes. 
 *
 * @ingroup attrmod
 */
typedef struct _jit_attr
{
	t_jit_object	ob;				///< common object header
	t_symbol		*name;			///< attribute name
	t_symbol		*type;			///< attribute type (char, long, float32, float64, symbol, atom, or obj)
	long			flags;  		///< flags for public/private get/set methods
	method			get;    		///< override default get method
	method			set;    		///< override default set method
	void			*filterget;		///< filterobject for get method
	void			*filterset; 	///< filterobject for set method
	void			*reserved;		///< for future use
} t_jit_attr;		

/**
 * Matrix information struct. 
 * Used to get/set multiple matrix attributes at once.
 *
 * @ingroup matrixfun
 */
typedef struct _jit_matrix_info
{
	long			size;			///< in bytes (0xFFFFFFFF=UNKNOWN)
	t_symbol		*type;			///< primitifve type (char, long, float32, or float64)
	long			flags;			///< flags to specify data reference, handle, or tightly packed
	long			dimcount;		///< number of dimensions
	long			dim[JIT_MATRIX_MAX_DIMCOUNT];		///< dimension sizes
	long			dimstride[JIT_MATRIX_MAX_DIMCOUNT]; ///< stride across dimensions in bytes
	long			planecount;		///< number of planes
} t_jit_matrix_info;


/**
 * Matrix conversion struct. 
 * Used to copy data from one matrix to another with special characteristics.
 *
 * @ingroup matrixfun
 */
typedef struct _matrix_conv_info
{
	long 	flags;									///< flags for whether or not to use interpolation, or source/destination dimensions
	long	planemap[JIT_MATRIX_MAX_PLANECOUNT];	///< plane mapping
	long	srcdimstart[JIT_MATRIX_MAX_DIMCOUNT];	///< source dimension start	
	long	srcdimend[JIT_MATRIX_MAX_DIMCOUNT];		///< source dimension end
	long	dstdimstart[JIT_MATRIX_MAX_DIMCOUNT];	///< destination dimension start	
	long	dstdimend[JIT_MATRIX_MAX_DIMCOUNT];		///< destination dimension end
} t_matrix_conv_info;

#include "jit.parallel.utils.h"


t_atom_long jit_method_true(void *x);
t_atom_long jit_method_false(void *x);

void *jit_class_new(C74_CONST char *name, method mnew, method mfree, long size, ...);
t_jit_err jit_class_free(void *c);
t_jit_err jit_class_register(void *c);
t_jit_err jit_class_addmethod(void *c, method m, const char *name, ...);
t_jit_err jit_class_addattr(void *c, t_jit_object *attr);
t_jit_err jit_class_addadornment(void *c, t_jit_object *o);
t_jit_err jit_class_addinterface(void *c, void *interfaceclass, long byteoffset, long flags);
void *jit_class_adornment_get(void *c, t_symbol *classname);
t_symbol *jit_class_nameget(void *c);
void *jit_class_findbyname(t_symbol *classname);
long jit_object_classname_compare(void *x, t_symbol *name);
method jit_class_method(void *c, t_symbol *methodname);
void *jit_class_attr_get(void *c, t_symbol *attrname);
t_jit_err jit_class_addtypedwrapper(void *c, method m, char *name, ...);
t_messlist *jit_class_typedwrapper_get(void *c, t_symbol *s);
t_jit_err jit_class_method_addargsafe(void *c, char *argname, char *methodname);
t_symbol *jit_class_method_argsafe_get(void *c, t_symbol *s);

void *jit_object_alloc(void *c);
void *jit_object_new(t_symbol *classname, ...);
#ifdef C74_X64
#define jit_object_new(...) C74_VARFUN(jit_object_new_imp, __VA_ARGS__)
#endif
void *jit_object_new_imp(void *classname, void *p1, void *p2, void *p3, void *p4, void *p5, void *p6, void *p7, void *p8, void *dummy);
t_jit_err jit_object_free(void *x);
void *jit_object_method(void *x, t_symbol *s, ...) JIT_WEAKLINK;
#ifdef C74_X64
#define jit_object_method(...) C74_VARFUN(jit_object_method_imp, __VA_ARGS__)
#endif
void *jit_object_method_imp(void *x, void *s, void *p1, void *p2, void *p3, void *p4, void *p5, void *p6, void *p7, void *p8);
void *jit_object_method_typed(void *x, t_symbol *s, long ac, t_atom *av, t_atom *rv);
method jit_object_getmethod(void *x, t_symbol *s);
t_symbol *jit_object_classname(void *x);
void * jit_object_register(void *x, t_symbol *s);
void *jit_object_findregistered(t_symbol *s);
t_symbol *jit_object_findregisteredbyptr(void *x);
t_jit_err jit_object_unregister(void *x);
void *jit_object_attach(t_symbol *s, void *x);
t_jit_err jit_object_detach(t_symbol *s, void *x);
t_jit_err jit_object_notify(void *x, t_symbol *s, void *data);
void *jit_object_class(void *x);
long jit_object_attr_usercanget(void *x,t_symbol *s);
long jit_object_attr_usercanset(void *x,t_symbol *s);
void *jit_object_attr_get(void *x, t_symbol *attrname);
t_jit_err jit_object_importattrs(void *x, t_symbol *s, long argc, t_atom *argv);
t_jit_err jit_object_exportattrs(void *x, t_symbol *s, long argc, t_atom *argv);
t_jit_err jit_object_exportsummary(void *x, t_symbol *s, long argc, t_atom *argv);
t_symbol *jit_object_method_argsafe_get(void *x, t_symbol *s);

//memory functions
void *jit_getbytes(long size);
void jit_freebytes(void *ptr,long size);
void **jit_handle_new(long size);
void jit_handle_free(void **handle);
long jit_handle_size_get(void **handle);
t_jit_err jit_handle_size_set(void **handle, long size);
long jit_handle_lock(void **handle, long lock);
void jit_copy_bytes(void *dest, const void *src, long bytes);
long jit_freemem(void);
char *jit_newptr(long size);
void jit_disposeptr(char *ptr);


//atom functions
t_jit_err jit_atom_setlong(t_atom *a, t_atom_long b);
t_jit_err jit_atom_setfloat(t_atom *a, double b);
t_jit_err jit_atom_setsym(t_atom *a, t_symbol *b);				
t_jit_err jit_atom_setobj(t_atom *a, void *b);
t_atom_long jit_atom_getlong(t_atom *a);
double jit_atom_getfloat(t_atom *a);
t_symbol *jit_atom_getsym(t_atom *a);
void *jit_atom_getobj(t_atom *a);
long jit_atom_getcharfix(t_atom *a);
//the following are useful for setting the values _only_ if there is an arg
//rather than setting it to 0 or _jit_sym_nothing
long jit_atom_arg_getlong(t_atom_long *c, long idx, long ac, t_atom *av);
long jit_atom_arg_getfloat(float *c, long idx, long ac, t_atom *av);
long jit_atom_arg_getdouble(double *c, long idx, long ac, t_atom *av);
long jit_atom_arg_getsym(t_symbol **c, long idx, long ac, t_atom *av);

//matrix info utils
t_jit_err jit_matrix_info_default(t_jit_matrix_info *info);
long jit_matrix_info_typesize(t_jit_matrix_info *minfo); 

//mop utils
t_jit_err jit_mop_single_type(void *x, t_symbol *s);
t_jit_err jit_mop_single_planecount(void *x, long c);
t_jit_err jit_mop_methodall(void *x, t_symbol *s, ...);
t_jit_err jit_mop_input_nolink(void *mop, long c);
t_jit_err jit_mop_output_nolink(void *mop, long c);
t_jit_err jit_mop_ioproc_copy_adapt(void *mop, void *mop_io, void *matrix);
t_jit_err jit_mop_ioproc_copy_trunc(void *mop, void *mop_io, void *matrix);
t_jit_err jit_mop_ioproc_copy_trunc_zero(void *mop, void *mop_io, void *matrix);
t_symbol *jit_mop_ioproc_tosym(void *ioproc);

//attr functions
long max_jit_attr_args_offset(short ac, t_atom *av);
void max_jit_attr_args(void *x, short ac, t_atom *av);
//for easy access of simple attributes
t_atom_long jit_attr_getlong(void *x, t_symbol *s);
t_jit_err jit_attr_setlong(void *x, t_symbol *s, t_atom_long c);
t_atom_float jit_attr_getfloat(void *x, t_symbol *s);
t_jit_err jit_attr_setfloat(void *x, t_symbol *s, t_atom_float c);
t_symbol *jit_attr_getsym(void *x, t_symbol *s);
t_jit_err jit_attr_setsym(void *x, t_symbol *s, t_symbol *c);
long jit_attr_getlong_array(void *x, t_symbol *s, long max, t_atom_long *vals);
t_jit_err jit_attr_setlong_array(void *x, t_symbol *s, long count, t_atom_long *vals);
long jit_attr_getchar_array(void *x, t_symbol *s, long max, uchar *vals);
t_jit_err jit_attr_setchar_array(void *x, t_symbol *s, long count, uchar *vals);
long jit_attr_getfloat_array(void *x, t_symbol *s, long max, float *vals);
t_jit_err jit_attr_setfloat_array(void *x, t_symbol *s, long count, float *vals);
long jit_attr_getdouble_array(void *x, t_symbol *s, long max, double *vals);
t_jit_err jit_attr_setdouble_array(void *x, t_symbol *s, long count, double *vals);
long jit_attr_getsym_array(void *x, t_symbol *s, long max, t_symbol **vals);
t_jit_err jit_attr_setsym_array(void *x, t_symbol *s, long count, t_symbol **vals);

//attr filters util
t_jit_err jit_attr_addfilterset_clip(void *x, double min, double max, long usemin, long usemax);
t_jit_err jit_attr_addfilterset_clip_scale(void *x, double scale, double min, double max, long usemin, long usemax);
t_jit_err jit_attr_addfilterget_clip(void *x, double min, double max, long usemin, long usemax);
t_jit_err jit_attr_addfilterget_clip_scale(void *x, double scale, double min, double max, long usemin, long usemax);
t_jit_err jit_attr_addfilter_clip(void *x, double min, double max, long usemin, long usemax);
t_jit_err jit_attr_addfilter_clip_scale(void *x, double scale, double min, double max, long usemin, long usemax);
t_jit_err jit_attr_addfilterset_proc(void *x, method proc);
t_jit_err jit_attr_addfilterget_proc(void *x, method proc);

// attr functions for assisting in user level notifications when setting attributes from C code
t_jit_err jit_attr_user_setvalueof(void *x, t_symbol *s, long ac, t_atom *av);
t_jit_err jit_attr_user_touch(void *x, t_symbol *s);
t_jit_err jit_attr_user_touch_parse(void *x, char *attrnames);
t_jit_err jit_object_addattr(void *x, t_object *attr);
t_jit_err jit_object_deleteattr(void *x, t_symbol *attrname);
		
		
//more util functions
void jit_rand_setseed(long n);
long jit_rand(void);
t_symbol *jit_symbol_unique();
void jit_error_code(void *x,t_jit_err v); //interrupt safe
void jit_error_sym(void *x,t_symbol *s); //interrupt safe
void jit_post_sym(void *x,t_symbol *s);  //interrupt safe

//load test

#ifdef __APPLE_CC__
#define IS_JIT_LIBRARY_AVAILABLE (jit_object_method != NULL)
#else
#define IS_JIT_LIBRARY_AVAILABLE (jit_object_method != NULL)
#endif

//util macros
#ifndef CLIP_ASSIGN
#define CLIP_ASSIGN(x,a,b) (x)=(x)<(a)?(a):(x)>(b)?(b):(x)		
#endif

#ifndef CLAMP
#define CLAMP(x,a,b) (x)<(a)?(a):(x)>(b)?(b):(x)
#endif

#ifndef MAX
#define MAX(x,y) ((x)>(y)?(x):(y))
#endif

#ifndef MIN
#define MIN(x,y) ((x)<(y)?(x):(y))
#endif

#ifndef ABS
#define ABS(x) ((x)<0?-(x):(x))
#endif

#ifndef SET_FLAG
#define	SET_FLAG(word, flag)	((word) |= (flag))
#endif

#ifndef CLEAR_FLAG
#define	CLEAR_FLAG(word, flag)	((word) &= ~(flag))
#endif

#ifndef GET_FLAG
#define GET_FLAG(word, flag)	((word) & (flag))
#endif

// include obex after all jit includes		
#include "ext_obex.h"		
		
#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __JIT_COMMON_H__
