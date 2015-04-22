/* 
	jit.gworld.h

	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
	
*/

#ifndef __JIT_GWORLD_H__
#define __JIT_GWORLD_H__

#ifdef C74_USING_QUICKTIME

#ifdef __cplusplus
extern "C" {
#endif

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

typedef struct _gworld_conv_info
{
	long 	flags;
	long	planemap[4];
	Rect	srcrect;
	Rect	dstrect;
} t_gworld_conv_info;

//utils for 32 bit gworlds
void jit_gworld_clear(GWorldPtr gp, long c);

long jit_gworld_can_coerce_matrix(t_gworld_conv_info *gc, void *m);
long jit_gworld_matrix_equal_dim(GWorldPtr gp, void *m);
t_jit_err jit_coerce_matrix_pixmap(void *m, PixMap *pm);

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif // #ifdef C74_USING_QUICKTIME

#endif //__JIT_GWORLD_H__
