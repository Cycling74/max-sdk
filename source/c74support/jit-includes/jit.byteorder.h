/* 
	jit.byteorder.h

	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
	
*/

#ifndef __JIT_BYTEORDER_H__
#define __JIT_BYTEORDER_H__

#if (defined(WIN32) || TARGET_RT_LITTLE_ENDIAN || C74_LITTLE_ENDIAN || __i386__)
#define JIT_LITTLE_ENDIAN
#else
#define JIT_BIG_ENDIAN 
#endif

#define SWAP16(x) ((t_int16)(((((t_uint16)(x))>>8)&0x00ff)+((((t_uint16)(x))<<8)&0xff00)))
#define SWAP32(x) ((t_int32)(((((t_uint32)(x))>>24L)&0x000000ff)+((((t_uint32)(x))>>8L)&0x0000ff00)+ \
((((t_uint32)(x))<<24L)&0xff000000)+((((t_uint32)(x))<<8L)&0x00ff0000)))
#define SWAPF32 			swapf32
#define SWAPF64 			swapf64
#define SWAPF32_PTR 		swap_pointer_32
#define SWAPF64_PTR 		swap_pointer_64
#define SWAPF32_PTR_TO_PTR 	swap_pointer_32_copy
#define SWAPF64_PTR_TO_PTR 	swap_pointer_64_copy
#define SWAPF32_FROM_PTR 	swap_pointer_32_to_float32
#define SWAPF64_FROM_PTR 	swap_pointer_64_to_float64

#ifdef JIT_BIG_ENDIAN
#define LE_I16(x) 				SWAP16(x)
#define LE_I32(x) 				SWAP32(x)
#define LE_F32(x) 				SWAPF32(x)
#define LE_F64(x) 				SWAPF64(x)
#define LE_F32_PTR(x) 			SWAPF32_PTR((unsigned char *)(x))
#define LE_F64_PTR(x) 			SWAPF64_PTR((unsigned char *)(x))
#define LE_F32_FROM_PTR(x) 		SWAPF32_FROM_PTR((unsigned char *)(x))
#define LE_F64_FROM_PTR(x) 		SWAPF64_FROM_PTR((unsigned char *)(x))
#define LE_F32_PTR_TO_PTR(x,y) 	SWAPF32_PTR_TO_PTR((unsigned char *)(x),(unsigned char *)(y))
#define LE_F64_PTR_TO_PTR(x,y) 	SWAPF64_PTR_TO_PTR((unsigned char *)(x),(unsigned char *)(y))
#define BE_I16(x) 				(x)
#define BE_I32(x) 				(x)
#define BE_F32_PTR(x) 		
#define BE_F64_PTR(x) 		
#define BE_F32_FROM_PTR(x) 		(*(float *)(x))
#define BE_F64_FROM_PTR(x) 		(*(double *)(x))
#define BE_F32_PTR_TO_PTR(x,y) 	((*(float *)(y))=(*(float *)(x)))
#define BE_F64_PTR_TO_PTR(x,y) 	((*(double *)(y))=(*(double *)(x)))
#define FOUR_CHAR(x)			(x)
#else
#define LE_I16(x) 				(x)
#define LE_I32(x) 				(x)
#define LE_F32(x) 				(x)
#define LE_F64(x) 				(x)
#define LE_F32_PTR(x) 		
#define LE_F64_PTR(x) 		
#define LE_F32_FROM_PTR(x) 		(*(float *)(x))
#define LE_F64_FROM_PTR(x) 		(*(double *)(x))
#define LE_F32_PTR_TO_PTR(x,y) 	((*(float *)(y))=(*(float *)(x)))
#define LE_F64_PTR_TO_PTR(x,y) 	((*(double *)(y))=(*(double *)(x)))
#define BE_I16(x) 				SWAP16(x)
#define BE_I32(x) 				SWAP32(x)
#define BE_F32_PTR(x) 			SWAPF32_PTR((unsigned char *)(x))
#define BE_F64_PTR(x) 			SWAPF64_PTR((unsigned char *)(x))
#define BE_F32_FROM_PTR(x) 		SWAPF32_FROM_PTR((unsigned char *)(x))
#define BE_F64_FROM_PTR(x) 		SWAPF64_FROM_PTR((unsigned char *)(x))
#define BE_F32_PTR_TO_PTR(x,y) 	SWAPF32_PTR_TO_PTR((unsigned char *)(x),(unsigned char *)(y))
#define BE_F64_PTR_TO_PTR(x,y) 	SWAPF64_PTR_TO_PTR((unsigned char *)(x),(unsigned char *)(y))

#define FOUR_CHAR(x)		(x)
#endif


#ifdef __cplusplus
extern "C" {
#endif
	
// OBSOLETE. don't use. not safe to pass byteswapped floats in registers
float swapf32(float f);
double swapf64(double f);

// these functions are inplace
void swap_pointer_16(unsigned char *p);
void swap_pointer_32(unsigned char *p);
void swap_pointer_64(unsigned char *p);
// these function copy from one pointer to another (src!=dst)
void swap_pointer_16_copy(unsigned char *src, unsigned char *dst);
void swap_pointer_32_copy(unsigned char *src, unsigned char *dst);
void swap_pointer_64_copy(unsigned char *src, unsigned char *dst);
// these functions return floating point values from a byteswapped pointer
float swap_pointer_32_to_float32(unsigned char *p);
double swap_pointer_64_to_float64(unsigned char *p);

	
#ifdef __cplusplus
}
#endif

#endif // __JIT_BYTEORDER_H__
