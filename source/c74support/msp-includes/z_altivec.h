#ifdef __ALTIVEC__
#pragma altivec_model on

#ifdef __cplusplus
#include <stdlib.h>		// for vec_malloc
#endif

typedef union 
{
	float			flt[4];
	vector float	vFlt;
} floatToVector;

static floatToVector __vsf_temp;

// this is what was needed to convince the compiler to copy a float to
// the four float locations in a vector

#define vec_splat_float(v,f) {							\
    __vsf_temp.flt[0] = f;								\
    v = vec_splat( vec_lde( 0, __vsf_temp.flt ), 0 );	}

#define VRSAVE     asm { li r0,-1 ; mtspr vrsave,r0 }
    
#pragma altivec_model off
#endif
