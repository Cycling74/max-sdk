
/* 
	jit.math.h
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com

	- platform independent mathlib calls
*/

#ifndef _JIT_MATH_H_
#define _JIT_MATH_H_

// --------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

double jit_math_cos		(double x);
double jit_math_sin		(double x);
double jit_math_tan		(double x);
double jit_math_acos	(double x);
double jit_math_asin	(double x);
double jit_math_atan	(double x);
double jit_math_atan2	(double y, double x);
double jit_math_cosh	(double x);
double jit_math_sinh	(double x);
double jit_math_tanh	(double x);
double jit_math_acosh	(double x);
double jit_math_asinh	(double x);
double jit_math_atanh	(double x);
double jit_math_exp		(double x);
double jit_math_expm1	(double x);
double jit_math_exp2	(double x);
double jit_math_log		(double x);
double jit_math_log2	(double x);
double jit_math_log10	(double x);
double jit_math_hypot	(double x, double y);
double jit_math_pow		(double x, double y);
double jit_math_sqrt	(double x);
double jit_math_ceil	(double x);
double jit_math_floor	(double x);
double jit_math_round	(double x);
double jit_math_trunc	(double x);
double jit_math_fmod	(double x, double y);
double jit_math_wrap	(double x, double lo, double hi);
double jit_math_fold	(double x, double lo, double hi);
double jit_math_j1		(double x);

long jit_math_is_valid(float x);
unsigned long jit_math_roundup_poweroftwo(unsigned long x);
long jit_math_is_poweroftwo(long x);
long jit_math_is_finite(float x);
long jit_math_is_nan(float x);


float jit_math_project_to_sphere(float r, float x, float y);

// --------------------------------------------------------------------------

float jit_math_fast_sqrt(float x);
float jit_math_fast_invsqrt(float x);

float jit_math_fast_sin(float x);		// absolute error of 1.7e-04 for [0, PI/2]
float jit_math_fast_cos(float x);		// absolute error of 1.2e-03 for [0, PI/2]
float jit_math_fast_tan(float x);		// absolute error of 1.9e-08 for [0, PI/4]
float jit_math_fast_asin(float x);		// absolute error of 6.8e-05 for [0, 1]
float jit_math_fast_acos(float x);		// absolute error of 6.8e-05 for [0, 1]
float jit_math_fast_atan(float x);		// absolute error of 1.43-08 for [-1, 1]

// --------------------------------------------------------------------------

// constants (compiler will collapse these)
#define JIT_MATH_F32_PI (3.14159265358979323846f)
#define JIT_MATH_F32_TWO_PI (2.0f * JIT_MATH_F32_PI)
#define JIT_MATH_F32_HALF_PI (0.5f * JIT_MATH_F32_PI)
#define JIT_MATH_F32_INV_PI (1.0f / JIT_MATH_F32_PI)
#define JIT_MATH_F32_DEGTORAD (JIT_MATH_F32_PI / 180.0f)
#define JIT_MATH_F32_RADTODEG (180.0f/JIT_MATH_F32_PI)
#define JIT_MATH_F32_EPS (10e-6f)
#define JIT_MATH_F32_MAXVAL (3.402823466e+38F)

#define JIT_MATH_F64_PI (3.14159265358979323846)
#define JIT_MATH_F64_TWO_PI (2.0 * JIT_MATH_F64_PI)
#define JIT_MATH_F64_HALF_PI (0.5 * JIT_MATH_F64_PI)
#define JIT_MATH_F64_INV_PI (1.0 / JIT_MATH_F64_PI)
#define JIT_MATH_F64_DEGTORAD (JIT_MATH_F64_PI / 180.0)
#define JIT_MATH_F64_RADTODEG (180.0 / JIT_MATH_F64_PI)
#define JIT_MATH_F64_EPS (10e-6f)
#define JIT_MATH_F64_MAXVAL (1.7976931348623158e+308)

#define JIT_MATH_FIXED_PI (DoubleToFixed(JIT_MATH_F64_PI))
#define JIT_MATH_FIXED_TWO_PI (DoubleToFixed(JIT_MATH_F64_TWO_PI))
#define JIT_MATH_FIXED_HALF_PI (DoubleToFixed(JIT_MATH_F64_HALF_PI))
#define JIT_MATH_FIXED_INV_PI (DoubleToFixed(JIT_MATH_F64_INV_PI))
#define JIT_MATH_FIXED_DEGTORAD (DoubleToFixed(JIT_MATH_F64_DEGTORAD))
#define JIT_MATH_FIXED_RADTODEG (DoubleToFixed(JIT_MATH_F64_RADTODEG))
#define JIT_MATH_FIXED_EPS (DoubleToFixed(JIT_MATH_F64_EPS))
#define JIT_MATH_FIXED_MAXVAL (2147483647L)

// --------------------------------------------------------------------------

// squared and cubed
#define JIT_MATH_SQR(x) ((x) * (x))
#define JIT_MATH_CUBE(x) ((x) * (x) * (x))

// clamp value x between a and b
#define JIT_MATH_CLAMP(x,a,b) (x)<(a)?(a):(x)>(b)?(b):(x)

// clip value x between a and b
#define JIT_MATH_CLIP(x,a,b) (x)=(x)<(a)?(a):(x)>(b)?(b):(x)

// max and min
#define JIT_MATH_MAX(x,y) ((x)>(y)?(x):(y))
#define JIT_MATH_MIN(x,y) ((x)<(y)?(x):(y))

// step or threshold
#define JIT_MATH_STEP(x,a) (((x) >= (a)) ? 1 : 0)

// linear interpolation of x between a and b
#define JIT_MATH_LERP(x,a,b) ((a) + (x) * ((b) - (a)))
#define JIT_MATH_FIXED_LERP(x,a,b) ((a) + FixMul4((x), ((b) - (a))))

// absolute value
#define JIT_MATH_F32_ABS(x) ((x)<0.0f?-(x):(x))
#define JIT_MATH_F64_ABS(x) ((x)<0.0?-(x):(x))
#define JIT_MATH_FIXED_ABS(x) ((x)<FloatToFixed(0.0f)?-(x):(x))

// fast floor to nearest long
#define JIT_MATH_F32_FLOOR(x) ((long)(x) - ( (x) < 0.0f && (x) != (long)(x) ))
#define JIT_MATH_F64_FLOOR(x) ((long)(x) - ( (x) < 0.0 && (x) != (long)(x) ))
#define JIT_MATH_F32_CEIL(x) ( ( ( (x) > 0.0f ) && ( (x) != (long) (x) ) ) ? 1 + (x) : (x) )
#define JIT_MATH_F64_CEIL(x) ( ( ( (x) > 0.0 ) && ( (x) != (long) (x) ) ) ? 1 + (x) : (x) )

// fractional component extraction
#define JIT_MATH_F32_FRAC2(x) (((x) >= 0.0f) ? (x) - (long)(x) : 0.0f)
#define JIT_MATH_F32_FRAC(x) (((x) >= 0.0f) ? (x) - (long)(x) : JIT_MATH_F32_FRAC2((-(x))))
#define JIT_MATH_F64_FRAC2(x) (((x) >= 0.0) ? (x) - (long)(x) : 0.0)
#define JIT_MATH_F64_FRAC(x) (((x) >= 0.0) ? (x) - (long)(x) : JIT_MATH_F64_FRAC2((-(x))))

// fast lcg rand (seed is ulong)
#define JIT_RAND_ULONG_LCG(seed) (1402024253 * seed + 586950981)

// fast uniform rand [0, 1]
#define JIT_RAND_F32_UNIFORM_LCG(seed) ((seed + 0.5f) * (1.0f / 4294967296.0f))
#define JIT_RAND_F64_UNIFORM_LCG(seed) ((seed + 0.5) * (1.0 / 4294967296.0))

// float32 bit extraction
#define JIT_MATH_F32_BITS(x) (*(t_int32 *)&(x))
#define JIT_MATH_F32_ABS_BITS(x) (JIT_MATH_F32_BITS(x)&0x7FFFFFFF)
#define JIT_MATH_F32_SIGN_BIT(x) (JIT_MATH_F32_BITS(x)&0x80000000)
#define JIT_MATH_F32_ONE_BITS 0x3F800000

// float32 inversion (r = 1/p)
#define JIT_MATH_F32_INV(r,p)                                                \
{                                                                            \
    int _i = 2 * JIT_MATH_F32_BITS - *(int *)&(p);                           \
    r = *(float *)&_i;                                                       \
    r = r * (2.0f - (p) * r);                                                \
}

// float32 exp (e = exp(p))
#define JIT_MATH_F32_EXP(e,p)                                                \
{                                                                            \
    int _i;                                                                  \
    e = -1.44269504f * (float)0x00800000 * (p);                              \
    _i = (int)e + 0x3F800000;                                                \
    e = *(float *)&_i;                                                       \
}

// determinant calculation
#define JIT_MATH_DET2x2(a1, a2, b1, b2) ((a1) * (b2) - (b1) * (a2))
#define JIT_MATH_DET3x3(a1, a2, a3, b1, b2, b3, c1, c2, c3) \
	((a1) * JIT_MATH_DET2x2(b2, b3, c2, c3) - (b1) * JIT_MATH_DET2x2(a2, a3, c2, c3) + (c1) * JIT_MATH_DET2x2(a2, a3, b2, b3))

// --------------------------------------------------------------------------

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif /* _JIT_MATH_H_ */
