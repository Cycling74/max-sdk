/*
 * Copyright 2001-2005 - Cycling '74
 * Derek Gerstmann - derek@cycling74.com
 *
 * Support for 16 bit floating point evaluation.
 *
 */

#ifndef JIT_HALF_H
#define JIT_HALF_H

// --------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

// --------------------------------------------------------------------------

// 16 bit "half" floating point
typedef unsigned short half;

// init half datatype
void jit_half_init();

// convert float-to-half
half jit_float_to_half(float i);

// convert half-to-float
float jit_half_to_float(half y);

// round to n-bits of precision
half jit_half_round(half h, unsigned int n);

// returns -h
half jit_half_negate(half h);

// returns h + a
half jit_half_add(half h, half a);

// returns h + a
half jit_half_add_float(half h, float a);

// returns h - a
half jit_half_sub(half h, half a);

// returns h - a
half jit_half_sub_float(half h, float a);

// returns h * a
half jit_half_mul(half h, half a);

// returns h * a
half jit_half_mul_float(half h, float a);

// returns h / a
half jit_half_div(half h, half a);

// returns h / a
half jit_half_div_float(half h, float a);

// returns 1 if h is a proper real
long jit_half_is_finite(half h);

// returns 1 if h is normalized
long jit_half_is_normalized(half h);

// returns 1 if h is denormalized
long jit_half_is_denormalized(half h);

// returns 1 if h == 0
long jit_half_is_zero(half h);

// returns 1 if h is < 0
long jit_half_is_negative(half h);

// returns 1 if h is a nan
long jit_half_is_nan(half h);

// returns 1 if h is an infinity
long jit_half_is_inf(half h);

// --------------------------------------------------------------------------

#ifdef WIN_VERSION

#define JIT_HALF_MIN		5.96046448e-08f	// smallest positive half
#define JIT_HALF_NRM_MIN	6.10351562e-05f	// smallest positive normalized half
#define JIT_HALF_MAX		65504.0f		// largest positive half
#define JIT_HALF_EPSILON	0.00097656f		// smallest positive e for which half (1.0 + e) != half (1.0)

#else

#define JIT_HALF_MIN		5.96046448e-08	// smallest positive half
#define JIT_HALF_NRM_MIN	6.10351562e-05	// smallest positive normalized half
#define JIT_HALF_MAX		65504.0			// largest positive half
#define JIT_HALF_EPSILON	0.00097656		// smallest positive e for which half (1.0 + e) != half (1.0)

#endif // WIN_VERSION

#define JIT_HALF_MANT_DIG	11				// number of digits in mantissa (significand + hidden leading 1)
#define JIT_HALF_DIG		2				// number of base 10 digits that can be represented without change
#define JIT_HALF_RADIX		2				// base of the exponent
#define JIT_HALF_MIN_EXP	-13				// minimum negative exponent
#define JIT_HALF_MAX_EXP	16				// maximum positive exponent
#define JIT_HALF_MIN_10_EXP	-4				// minimum positive 10^exponent
#define JIT_HALF_MAX_10_EXP	4				// maximum positive 10^exponent
#define JIT_HALF_POSINF		(0x7c00)		// positive infinity
#define JIT_HALF_NEGINF		(0xfc00)		// negative infinity
#define JIT_HALF_QNAN		(0x7fff)		// qnan
#define JIT_HALF_SNAN		(0x7dff)		// signed nan

// --------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

// --------------------------------------------------------------------------

#endif // JIT_HALF_H
