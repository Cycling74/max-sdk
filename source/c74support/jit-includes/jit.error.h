/* 
	jit.error.h

	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
	
*/

#ifndef __JIT_ERROR_H__
#define __JIT_ERROR_H__

#include "ext_prefix.h"
#include "ext_mess.h"
#include "jit.byteorder.h"

typedef t_atom_long t_jit_err;

//errors
enum t_jit_error_code {
	JIT_ERR_NONE 				= 0,
	JIT_ERR_GENERIC				= FOUR_CHAR('EROR'),
	JIT_ERR_INVALID_OBJECT		= FOUR_CHAR('INOB'),
	JIT_ERR_OBJECT_BUSY			= FOUR_CHAR('OBSY'),
	JIT_ERR_OUT_OF_MEM			= FOUR_CHAR('OMEM'),
	JIT_ERR_INVALID_PTR			= FOUR_CHAR('INVP'),
	JIT_ERR_DUPLICATE			= FOUR_CHAR('DUPL'),
	JIT_ERR_OUT_OF_BOUNDS		= FOUR_CHAR('OBND'),
	JIT_ERR_INVALID_INPUT		= FOUR_CHAR('INVI'),
	JIT_ERR_INVALID_OUTPUT		= FOUR_CHAR('INVO'),
	JIT_ERR_MISMATCH_TYPE		= FOUR_CHAR('MSTP'),
	JIT_ERR_MISMATCH_PLANE		= FOUR_CHAR('MSPL'),
	JIT_ERR_MISMATCH_DIM		= FOUR_CHAR('MSDM'),
	JIT_ERR_MATRIX_UNKNOWN		= FOUR_CHAR('MXUN'),
	JIT_ERR_SUPPRESS_OUTPUT		= FOUR_CHAR('SPRS'),
	JIT_ERR_DATA_UNAVAILABLE	= FOUR_CHAR('DUVL'),
	JIT_ERR_HW_UNAVAILABLE		= FOUR_CHAR('HUVL')
};

#ifdef __cplusplus
extern "C" {
#endif

#define jit_catch(x) {t_jit_err _jit_catch_err; if (_jit_catch_err=(x)) { return _jit_catch_err; }} 

void jit_object_post(t_object *x, char *s, ...);
void jit_object_error(t_object *x, char *s, ...);

#ifdef __cplusplus
}
#endif

#endif //__JIT_ERROR_H__
