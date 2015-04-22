#ifndef JIT_GL_PIXELFORMAT_H
#define JIT_GL_PIXELFORMAT_H

/*
 * Copyright 2001-2005 - Cycling '74
 * Derek Gerstmann - derek@cycling74.com
 *
 * Struct and associated methods for defining an OpenGL 
 * pixel format for creating a drawable.
 *
 */

/****************************************************************************/

#include "jit.gl.h"
#include "jit.common.h"

/****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

/****************************************************************************/

#define JIT_GL_PF_MAX_ATTRIBCOUNT				(512)

#define JIT_GL_PF_TARGET_DRAW_TO_WINDOW			(0)	// render to window
#define JIT_GL_PF_TARGET_DRAW_TO_BITMAP			(1)	// render to memory
#define JIT_GL_PF_TARGET_DRAW_TO_PBUFFER		(2)	// render to pbuffer (offscreen drawable)

#define JIT_GL_PF_PIXELTYPE_INDEXED				(0)
#define JIT_GL_PF_PIXELTYPE_R					(1)	// only for BIND_TO_TEXTURE
#define JIT_GL_PF_PIXELTYPE_RG					(2) // only for BIND_TO_TEXTURE
#define JIT_GL_PF_PIXELTYPE_RGB					(3) 
#define JIT_GL_PF_PIXELTYPE_RGBA				(4)
#define JIT_GL_PF_PIXELTYPE_DEPTH				(5) // only for BIND_TO_TEXTURE

#define JIT_GL_PF_PIXEL_FLOAT_ARB				(1 << 0)
#define JIT_GL_PF_PIXEL_FLOAT_NV				(1 << 1)
#define JIT_GL_PF_PIXEL_FLOAT_ATI				(1 << 2)
#define JIT_GL_PF_PIXEL_FLOAT_APPLE				(1 << 3)
#define JIT_GL_PF_FLAG_TEXTURE_RECTANGLE		(1 << 4)
#define JIT_GL_PF_FLAG_TEXTURE_DEPTH			(1 << 5)
#define JIT_GL_PF_FLAG_BIND_TO_TEXTURE			(1 << 6)	// render to texture

#ifdef JIT_GL_NSGL
typedef uint32_t t_jit_gl_pixel_attribute;
#else
typedef GLint t_jit_gl_pixel_attribute;
#endif

/****************************************************************************/

typedef struct _jit_gl_pixelformat
{
	long							target;				// destination target for pixel data
	long							pixel_type;			// type of pixel data (INDEXED/RGB/RGBA/etc)
	long							pixel_size;			// size of all pixel components in bits
	long							pixel_float;		// flag for floating point pixels (16 or 32bit)
	long							pixel_float_target;	// target for floating point pixels (16 or 32bit)
	long							red_size;			// size of red component in bits
	long							green_size;			// size of green component in bits
	long							blue_size;			// size of blue component in bits
	long							alpha_size;			// size of alpha component in bits
	long							depth_size;			// size of depth buffer in bits
	long							stencil_size;		// size of stencil buffer in bits
	long							accum_size;			// sixe of all accumulation componenets in bits
	long							accum_red_size;		// size of red component in bits
	long							accum_green_size;	// size of green accumulation component in bits
	long							accum_blue_size;	// size of blue accumulation component in bits
	long							accum_alpha_size;	// size of alpha accumulation component in bits
	long							samples;			// number of samples for multisampling
	long							sample_buffers;		// number of sample buffers for multisampling
	long							aux_buffers;		// number of auxiliary buffers
	long							stereo;				// flag for stereo rendering
	long							quality;			// flag for quality hint
	long							doublebuffer;		// flag to enable double buffering
	long							accelerated;		// flag to enable hw accelerated buffer
	long							rectangle;			// flag to enable rectangular color buffer (for bind to texture)
	long							fullscreen;			// flag to enable fullscreen rendering
	long							flags;				// set of additional flags for extended attributes
} t_jit_gl_pixelformat;

/****************************************************************************/

t_jit_gl_pixelformat *jit_gl_pixelformat_new(void);
t_jit_err jit_gl_pixelformat_create_attributes(t_jit_gl_pixelformat *x, t_jit_gl_pixel_attribute **pfattrib, GLuint *pfcount);
void *jit_gl_pixelformat_create_native_from_attributes(t_jit_gl_pixel_attribute *attrib, void *device);
void *jit_gl_pixelformat_create_native(t_jit_gl_pixelformat *x, void *device);
void *jit_gl_pixelformat_create_no_context(t_jit_gl_pixelformat *x, void *device, void *window);
t_jit_err jit_gl_pixelformat_destroy_native(void *native);
t_jit_err jit_gl_pixelformat_reset(t_jit_gl_pixelformat *x);
void jit_gl_pixelformat_free(t_jit_gl_pixelformat *x);

/****************************************************************************/

// APPLE extended pixel format attribute flags
#ifndef AGL_PIXEL_SIZE
#define AGL_PIXEL_SIZE 						50
#endif
#ifndef AGL_MINIMUM_POLICY 					
#define AGL_MINIMUM_POLICY 					51
#endif
#ifndef AGL_MAXIMUM_POLICY 					
#define AGL_MAXIMUM_POLICY 					52
#endif
#ifndef AGL_OFFSCREEN 						
#define AGL_OFFSCREEN 						53
#endif
#ifndef AGL_FULLSCREEN 						
#define AGL_FULLSCREEN 						54
#endif
#ifndef AGL_SAMPLE_BUFFERS_ARB 				
#define AGL_SAMPLE_BUFFERS_ARB 				55
#endif
#ifndef AGL_SAMPLES_ARB 					
#define AGL_SAMPLES_ARB 					56
#endif
#ifndef AGL_AUX_DEPTH_STENCIL 				
#define AGL_AUX_DEPTH_STENCIL 				57
#endif
#ifndef AGL_COLOR_FLOAT 					
#define AGL_COLOR_FLOAT 					58
#endif
#ifndef AGL_MULTISAMPLE 					
#define AGL_MULTISAMPLE 					59
#endif
#ifndef AGL_SUPERSAMPLE 					
#define AGL_SUPERSAMPLE 					60
#endif
#ifndef AGL_SAMPLE_ALPHA 					
#define AGL_SAMPLE_ALPHA 					61
#endif
#ifndef AGL_RENDERER_GENERIC_FLOAT_ID
#define AGL_RENDERER_GENERIC_FLOAT_ID         0x00020400 
#endif

// WGL pixel format
//#ifndef WGL_ARB_pixel_format
#define WGL_ARB_pixel_format				1
#define WGL_NUMBER_PIXEL_FORMATS_ARB        0x2000
#define WGL_DRAW_TO_WINDOW_ARB              0x2001
#define WGL_DRAW_TO_BITMAP_ARB              0x2002
#define WGL_ACCELERATION_ARB                0x2003
#define WGL_NEED_PALETTE_ARB                0x2004
#define WGL_NEED_SYSTEM_PALETTE_ARB         0x2005
#define WGL_SWAP_LAYER_BUFFERS_ARB          0x2006
#define WGL_SWAP_METHOD_ARB                 0x2007
#define WGL_NUMBER_OVERLAYS_ARB             0x2008
#define WGL_NUMBER_UNDERLAYS_ARB            0x2009
#define WGL_TRANSPARENT_ARB                 0x200A
#define WGL_TRANSPARENT_RED_VALUE_ARB       0x2037
#define WGL_TRANSPARENT_GREEN_VALUE_ARB     0x2038
#define WGL_TRANSPARENT_BLUE_VALUE_ARB      0x2039
#define WGL_TRANSPARENT_ALPHA_VALUE_ARB     0x203A
#define WGL_TRANSPARENT_INDEX_VALUE_ARB     0x203B
#define WGL_SHARE_DEPTH_ARB                 0x200C
#define WGL_SHARE_STENCIL_ARB               0x200D
#define WGL_SHARE_ACCUM_ARB                 0x200E
#define WGL_SUPPORT_GDI_ARB                 0x200F
#define WGL_SUPPORT_OPENGL_ARB              0x2010
#define WGL_DOUBLE_BUFFER_ARB               0x2011
#define WGL_STEREO_ARB                      0x2012
#define WGL_PIXEL_TYPE_ARB                  0x2013
#define WGL_COLOR_BITS_ARB                  0x2014
#define WGL_RED_BITS_ARB                    0x2015
#define WGL_RED_SHIFT_ARB                   0x2016
#define WGL_GREEN_BITS_ARB                  0x2017
#define WGL_GREEN_SHIFT_ARB                 0x2018
#define WGL_BLUE_BITS_ARB                   0x2019
#define WGL_BLUE_SHIFT_ARB                  0x201A
#define WGL_ALPHA_BITS_ARB                  0x201B
#define WGL_ALPHA_SHIFT_ARB                 0x201C
#define WGL_ACCUM_BITS_ARB                  0x201D
#define WGL_ACCUM_RED_BITS_ARB              0x201E
#define WGL_ACCUM_GREEN_BITS_ARB            0x201F
#define WGL_ACCUM_BLUE_BITS_ARB             0x2020
#define WGL_ACCUM_ALPHA_BITS_ARB            0x2021
#define WGL_DEPTH_BITS_ARB                  0x2022
#define WGL_STENCIL_BITS_ARB                0x2023
#define WGL_AUX_BUFFERS_ARB                 0x2024
#define WGL_NO_ACCELERATION_ARB             0x2025
#define WGL_GENERIC_ACCELERATION_ARB        0x2026
#define WGL_FULL_ACCELERATION_ARB           0x2027
#define WGL_SWAP_EXCHANGE_ARB               0x2028
#define WGL_SWAP_COPY_ARB                   0x2029
#define WGL_SWAP_UNDEFINED_ARB              0x202A
#define WGL_TYPE_RGBA_ARB                   0x202B
#define WGL_TYPE_COLORINDEX_ARB             0x202C
//#endif

// ATI pixel format
#ifndef WGL_ATI_pixel_format_float
#define WGL_ATI_pixel_format_float  1
#define WGL_TYPE_RGBA_FLOAT_ATI             0x21A0
#define GL_TYPE_RGBA_FLOAT_ATI              0x8820
#define GL_COLOR_CLEAR_UNCLAMPED_VALUE_ATI  0x8835
#endif

/****************************************************************************/

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

/****************************************************************************/

#endif // JIT_GL_PIXELFORMAT_H
