/* 
	jit.op.h

	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com	
*/

#ifndef _JIT_OP_H_
#define _JIT_OP_H_

#include "jit.common.h"

#ifdef __cplusplus
extern "C" {
#endif

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

/**
 * Provides base pointer and stride for vector operator functions
 */
typedef struct _jit_op_info
{
	void 	*p;			///< base pointer (coerced to appropriate type)
	long 	stride;		///< stride between elements (in type, not bytes)
} t_jit_op_info;

typedef void (*t_jit_op_fn)(long, ...);
typedef void *(*t_jit_op_fn_rv)(long, ...);

typedef struct _jit_op_fn_object
{
	t_object 		ob;
	t_symbol		*name;
	long			argcount;
	t_jit_op_fn		charfn;
	t_jit_op_fn		longfn;
	t_jit_op_fn		float32fn;
	t_jit_op_fn		float64fn;	
} t_jit_op_fn_object;

t_jit_err jit_op_init(void); 
t_jit_op_fn jit_op_sym2fn(t_symbol *opsym, t_symbol *type);
t_jit_op_fn_object *jit_op_fn_lookup(t_symbol *opsym);
t_jit_err jit_op_fn_store(t_symbol *opsym, t_jit_op_fn_object *x);

//note vecdata is unused by the following functions.

//arith
void jit_op_vector_pass_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_mult_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_div_char		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_mod_char		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_add_char		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_adds_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_sub_char		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_subs_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_min_char		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_max_char		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_avg_char		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_absdiff_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_pass_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *op); 
void jit_op_vector_mult_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); 
void jit_op_vector_div_char_altivec		(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); //unimplemented
void jit_op_vector_mod_char_altivec		(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); //unimplemented
void jit_op_vector_add_char_altivec		(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); 
void jit_op_vector_adds_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); 
void jit_op_vector_sub_char_altivec		(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); 
void jit_op_vector_subs_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); 
void jit_op_vector_min_char_altivec		(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); 
void jit_op_vector_max_char_altivec		(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); 
void jit_op_vector_avg_char_altivec		(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); 

void jit_op_vector_pass_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_mult_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_div_long		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_mod_long		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_add_long		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_sub_long		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_min_long		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_max_long		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_abs_long		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_avg_long		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_absdiff_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_pass_long_altivec	(long n, void *vecdata, t_int32 *ip1, t_int32 *op); 
void jit_op_vector_mult_long_altivec	(long n, void *vecdata, t_int32 *ip1, t_int32 *ip2, t_int32 *op); 
void jit_op_vector_div_long_altivec		(long n, void *vecdata, t_int32 *ip1, t_int32 *ip2, t_int32 *op); //unimplemented
void jit_op_vector_mod_long_altivec		(long n, void *vecdata, t_int32 *ip1, t_int32 *ip2, t_int32 *op); //unimplemented
void jit_op_vector_add_long_altivec		(long n, void *vecdata, t_int32 *ip1, t_int32 *ip2, t_int32 *op); 
void jit_op_vector_sub_long_altivec		(long n, void *vecdata, t_int32 *ip1, t_int32 *ip2, t_int32 *op); 
void jit_op_vector_min_long_altivec		(long n, void *vecdata, t_int32 *ip1, t_int32 *ip2, t_int32 *op); 
void jit_op_vector_max_long_altivec		(long n, void *vecdata, t_int32 *ip1, t_int32 *ip2, t_int32 *op); 
void jit_op_vector_abs_long_altivec		(long n, void *vecdata, t_int32 *ip1, t_int32 *op); 
void jit_op_vector_avg_long_altivec		(long n, void *vecdata, t_int32 *ip1, t_int32 *ip2, t_int32 *op); 

void jit_op_vector_pass_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_mult_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_div_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_add_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_sub_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_min_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_max_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_abs_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_avg_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_absdiff_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_mod_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_fold_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_wrap_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_pass_float32_altivec		(long n, void *vecdata, float *ip1, float *op); 
void jit_op_vector_mult_float32_altivec		(long n, void *vecdata, float *ip1, float *ip2, float *op); 
void jit_op_vector_div_float32_altivec		(long n, void *vecdata, float *ip1, float *ip2, float *op); //unimplemented
void jit_op_vector_add_float32_altivec		(long n, void *vecdata, float *ip1, float *ip2, float *op); 
void jit_op_vector_sub_float32_altivec		(long n, void *vecdata, float *ip1, float *ip2, float *op); 
void jit_op_vector_min_float32_altivec		(long n, void *vecdata, float *ip1, float *ip2, float *op); 
void jit_op_vector_max_float32_altivec		(long n, void *vecdata, float *ip1, float *ip2, float *op); 
void jit_op_vector_abs_float32_altivec		(long n, void *vecdata, float *ip1, float *op); 
void jit_op_vector_avg_float32_altivec		(long n, void *vecdata, float *ip1, float *ip2, float *op); 
void jit_op_vector_absdiff_float32_altivec(long n, void *vecdata, float *ip1, float *ip2, float *op);

void jit_op_vector_pass_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_mult_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_div_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_add_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_sub_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_min_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_max_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_abs_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_avg_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_absdiff_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_mod_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_fold_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_wrap_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

//fliparith(calls corresponding arith function)
void jit_op_vector_flippass_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_flipdiv_char		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_flipmod_char		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_flipsub_char		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_flippass_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_flipdiv_long		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_flipmod_long		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_flipsub_long		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_flippass_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_flipdiv_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_flipmod_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_flipsub_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_flippass_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_flipdiv_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_flipmod_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_flipsub_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

//bitwise
void jit_op_vector_bitand_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_bitor_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_bitxor_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_bitnot_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_lshift_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_rshift_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_bitand_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); 
void jit_op_vector_bitor_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); 
void jit_op_vector_bitxor_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); 
void jit_op_vector_bitnot_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *op); 
void jit_op_vector_lshift_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); 
void jit_op_vector_rshift_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); 

void jit_op_vector_bitand_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_bitor_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_bitxor_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_bitnot_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_lshift_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_rshift_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_bitand_long_altivec	(long n, void *vecdata, t_int32 *ip1, t_int32 *ip2, t_int32 *op); 
void jit_op_vector_bitor_long_altivec	(long n, void *vecdata, t_int32 *ip1, t_int32 *ip2, t_int32 *op); 
void jit_op_vector_bitxor_long_altivec	(long n, void *vecdata, t_int32 *ip1, t_int32 *ip2, t_int32 *op); 
void jit_op_vector_bitnot_long_altivec	(long n, void *vecdata, t_int32 *ip1, t_int32 *op); 
void jit_op_vector_lshift_long_altivec	(long n, void *vecdata, t_int32 *ip1, t_int32 *ip2, t_int32 *op); 
void jit_op_vector_rshift_long_altivec	(long n, void *vecdata, t_int32 *ip1, t_int32 *ip2, t_int32 *op); 

//logical
void jit_op_vector_and_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_or_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_not_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_gt_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_gte_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_lt_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_lte_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_eq_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_neq_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_and_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); 
void jit_op_vector_or_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); 
void jit_op_vector_not_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *op); 
void jit_op_vector_gt_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); 
void jit_op_vector_gte_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op); 
void jit_op_vector_lt_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op);  
void jit_op_vector_lte_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op);  
void jit_op_vector_eq_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op);  
void jit_op_vector_neq_char_altivec	(long n, void *vecdata, uchar *ip1, uchar *ip2, uchar *op);  

void jit_op_vector_and_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_or_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_not_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_gt_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_gte_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_lt_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_lte_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_eq_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_neq_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_and_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_or_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_not_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_gt_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_gte_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_lt_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_lte_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_eq_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_neq_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_and_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_or_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_not_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_gt_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_gte_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_lt_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_lte_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_eq_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_neq_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

//logical pass
void jit_op_vector_gtp_char		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_gtep_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_ltp_char		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_ltep_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_eqp_char		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_neqp_char	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_gtp_long		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_gtep_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_ltp_long		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_ltep_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_eqp_long		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_neqp_long	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_gtp_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_gtep_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_ltp_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_ltep_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_eqp_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_neqp_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_gtp_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_gtep_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_ltp_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_ltep_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_eqp_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_neqp_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

//transcendental(float32/float64 only)
void jit_op_vector_sin_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_cos_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_tan_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_asin_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_acos_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_atan_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_atan2_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_sinh_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_cosh_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_tanh_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_asinh_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_acosh_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_atanh_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_exp_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_exp2_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_log_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_log2_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_log10_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_hypot_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_pow_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_sqrt_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_ceil_float32		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_floor_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_round_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_trunc_float32	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_sin_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_cos_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_tan_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_asin_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_acos_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_atan_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_atan2_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_sinh_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_cosh_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_tanh_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_asinh_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_acosh_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_atanh_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_exp_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_exp2_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_log_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_log2_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_log10_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_hypot_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_pow_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_sqrt_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_ceil_float64		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_floor_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_round_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_trunc_float64	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

//linear algebra
void jit_op_vector_ax_float32				(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_ax_float32_complex		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_ax_float64				(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_ax_float64_complex		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_axpy_float32				(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_axpy_float32_complex		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_axpy_float64				(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_axpy_float64_complex		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_dotprod_float32			(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_dotprod_float32_complex	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_dotprod_float64			(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_dotprod_float64_complex	(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

void jit_op_vector_swap_float32				(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_swap_float32_complex		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_swap_float64				(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 
void jit_op_vector_swap_float64_complex		(long n, void *vecdata, t_jit_op_info *in0, t_jit_op_info *in1, t_jit_op_info *out); 

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif //_JIT_OP_H_

