#ifndef JIT_GL_SUPPORT_H
#define JIT_GL_SUPPORT_H

/*
 * Copyright 2001-2005 - Cycling '74
 * Derek Gerstmann - derek@cycling74.com
 *
 * Struct and associated methods for checking feature support
 * for various OpenGL extensions.
 *
 */

/****************************************************************************/

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

typedef struct _jit_gl_support {
	long				initialized;				// flag for support initialization
	long				color_buffer_float;			// flag if float pixels are supported for creating a color buffer pixelformat
	long				color_float_pixels;			// flag if float pixels are enabled in current context
	long				color_red_bits;				// number of color red bit planes in current context
	long				color_green_bits;			// number of color green bit planes in current context
	long				color_blue_bits;			// number of color blue bit planes in current context
	long				color_alpha_bits;			// number of color alpha bit planes in current context
	long				color_index_bits;			// number of color index bit planes in current context
	long				accum_red_bits;				// number of accum red bit planes in current context
	long				accum_green_bits;			// number of accum green bit planes in current context
	long				accum_blue_bits;			// number of accum blue bit planes in current context
	long				accum_alpha_bits;			// number of accum alpha bit planes in current context
	long				stencil_bits;				// number of stencil bit planes in current context
	long				depth_bits;					// number of depth bit planes in current context
	long				aux_buffers;				// number of auxiliary buffers in current context
	long				multitexture;				// flag for multi-texturing support
	long				multisample;				// flag for multi-sample support
	long				multisample_buffers;		// number of available multisample buffers
	long				multisample_samples;		// number of samples available in multisampling mode
	long				light_count;				// number of lights available
	long				texture_units;				// number of texture units available
	long				texture_image_units;		// number of texture image units available	
	long				texture_max_size;			// maximum texture width or height
	long				texture_3d;					// flag for 3d texture support
	long				texture_cubemap;			// flag for cubemap support
	long				texture_depth;				// flag for depth texture support
	long				texture_shadow;				// flag for shadow texture support
	long 				texture_float;				// flag for floating point texture support
	long				texture_env;				// flag for env support
	long				texture_env_add;			// flag for env add support
	long				texture_env_combine;		// flag for env combine support
	long				texture_env_crossbar;		// flag for env crossbar support
	long				texture_env_dot3;			// flag for env dot3 support
	long				texture_env_target;			// target for all env features
	long				texture_border_clamp;		// flag for clamp to border support
	long				texture_mirrored_repeat;	// flag for mirrored repeat support
	long				texture_anisotropic;		// flag for anisotropic support
	long				texture_max_anisotropy;		// max anisotropic filter size
	long				texture_rect;				// flag for rectangular textures support
	long				texture_rect_target;		// backend for rect support (ARB, EXT)
	long				texture_rect_uniform;		// flag for uniform texture coords
	long				texture_compression;		// flag for texture compression support
	long				texture_compression_s3tc;	// flag for s3tc compression
	long				texture_compression_vtc;	// flag for vtc compression
	long				texture_range;				// flag for texture range support (APPLE only)
	long				client_storage;				// flag for client storage support (APPLE only)
	long				pixel_float16;				// flag for 16bit float pixel support
	long				pixel_float32;				// flag for 32bit float pixel support
	long				pixel_float_target;			// backend for float support (APPLE, ATI, NV)
	long				pbo;						// flag for pixel buffer objects support
	long				fbo;						// flag for frame buffer object support
	long				vbo;						// flag for vertex buffer object support
	long				pbuffer;					// flag for hardware assisted pbuffer support
	long				pbuffer_float;				// flag for float pbuffer support
	long				pbuffer_float_target;		// backend for float support (APPLE, ATI, NV)
	long				pbuffer_rtt;				// flag for render to texture support 
	long				pbuffer_rtt_rect;			// flag for rectangular render to texture support
	long				pbuffer_rtt_rect_target;	// target for rectangular render to texture support
	long				pbuffer_rtt_depth;			// flag for render to depth texture support
	long				shader_objects_glsl_arb;	// flag for glsl shader objects
	long				vertex_shader_glsl_arb;		// flag for glsl vertex shader programs
	long				fragment_shader_glsl_arb;	// flag for glsl fragment shader programs
	long				shading_language_support_glsl_arb;	// flag for native glsl compiler support
	long				vertex_program_arb;			// flag for arb vertex program support
	long				fragment_program_arb;		// flag for arb fragment program support
	long				vertex_program_nv;			// flag for nv vertex program support
	long				vertex_program_nv_version;	// version for nv vertex program support
	long				fragment_program_nv;		// flag for nv fragment program support
	long				fragment_program_nv_version;// version for nv fragment program support
	long				fragment_program_shadow;	// flag for frament shader depth comparison capability
	long				geometry_shader;			// flag for geometry shader support
	long				gpu_program4_nv;			// flag for nvidia geometry shader support (for Cg)
	long				transform_feedback;			// flag for transform feedback support
	long				gpu_program_parameters;		// flag for shader parameter environment support
	long				gpu_shader4;				// flag for shader model 4 support
	long				version_major;				// major version number
	long				version_minor;				// minor version number
	long				version_release;			// release version number
	long				glsl_version_major;			// glsl major version
	long				glsl_version_minor;			// glsl minor version

} t_jit_gl_support;

/****************************************************************************/

t_jit_gl_support *jit_gl_support_new(void);
t_jit_err jit_gl_support_init(t_jit_gl_support *x, const char *extensions);
long jit_gl_support_field_value(t_jit_gl_support *x, t_symbol *name);
void jit_gl_support_free(t_jit_gl_support *x);

/****************************************************************************/

// backend targets
#define JIT_GL_ARB											(5)
#define JIT_GL_NV											(6)
#define JIT_GL_APPLE										(7)
#define JIT_GL_EXT											(8)
#define JIT_GL_FBO											(9)
#define JIT_GL_PBUFFER										(10)
#define JIT_GL_NONE											(-1)

// float targets
#define JIT_GL_FLOAT_NONE									(0)
#define JIT_GL_FLOAT_ARB									(1)
#define JIT_GL_FLOAT_ATI									(2)
#define JIT_GL_FLOAT_NV										(3)
#define JIT_GL_FLOAT_APPLE									(4)

// format flags
#define JIT_GL_LUMINANCE									(1 << 0)
#define JIT_GL_INTENSITY									(1 << 1)
#define JIT_GL_ALPHA										(1 << 2)
#define JIT_GL_LUMINANCE_ALPHA								(1 << 3)
#define JIT_GL_RGB											(1 << 4)
#define JIT_GL_RGBA											(1 << 5)
#define JIT_GL_DEPTH										(1 << 6)
#define JIT_GL_UYVY											(1 << 7)

// float flags
#define JIT_GL_FLOAT16										(1 << 8)
#define JIT_GL_FLOAT32										(1 << 9)

// compression flags
#define JIT_GL_DXT1											(1 << 10)
#define JIT_GL_DXT3											(1 << 11)
#define JIT_GL_DXT5											(1 << 12)

// clamp flags
#define JIT_GL_CLAMP										(1 << 13)
#define JIT_GL_CLAMP_TO_EDGE								(1 << 14)

// filter flags
#define JIT_GL_NEAREST										(1 << 15)
#define JIT_GL_LINEAR										(1 << 16)
#define JIT_GL_NEAREST_MIPMAP_NEAREST						(1 << 17)
#define JIT_GL_LINEAR_MIPMAP_NEAREST						(1 << 18)
#define JIT_GL_LINEAR_MIPMAP_LINEAR							(1 << 19)

// anisotropy flags
#define JIT_GL_ANISOTROPY1									(1 << 20)
#define JIT_GL_ANISOTROPY2									(1 << 21)
#define JIT_GL_ANISOTROPY4									(1 << 22)
#define JIT_GL_ANISOTROPY8									(1 << 23)
#define JIT_GL_ANISOTROPY16									(1 << 24)


/****************************************************************************/

// ARB texture rectangle
#ifndef GL_ARB_texture_rectangle
#define GL_ARB_texture_rectangle							(1)
#define GL_TEXTURE_RECTANGLE_ARB							(0x84F5)
#define GL_TEXTURE_BINDING_RECTANGLE_ARB					(0x84F6)
#define GL_PROXY_TEXTURE_RECTANGLE_ARB						(0x84F7)
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_ARB					(0x84F8)
#endif

// ARB float16
#ifndef GL_ARB_half_float_pixel
#define GL_ARB_half_float_pixel								(1)
#define GL_HALF_FLOAT_ARB									(0x140B)
#endif

// ARB float32
#ifndef GL_ARB_texture_float
#define GL_ARB_texture_float								(1)
#define GL_TEXTURE_RED_TYPE_ARB								(0x8C10)
#define GL_TEXTURE_GREEN_TYPE_ARB							(0x8C11)
#define GL_TEXTURE_BLUE_TYPE_ARB							(0x8C12)
#define GL_TEXTURE_ALPHA_TYPE_ARB							(0x8C13)
#define GL_TEXTURE_LUMINANCE_TYPE_ARB						(0x8C14)
#define GL_TEXTURE_INTENSITY_TYPE_ARB						(0x8C15)
#define GL_TEXTURE_DEPTH_TYPE_ARB							(0x8C16)
#define GL_UNSIGNED_NORMALIZED_ARB							(0x8C17)
#define GL_RGBA32F_ARB										(0x8814)
#define GL_RGB32F_ARB										(0x8815)
#define GL_ALPHA32F_ARB										(0x8816)
#define GL_INTENSITY32F_ARB									(0x8817)
#define GL_LUMINANCE32F_ARB									(0x8818)
#define GL_LUMINANCE_ALPHA32F_ARB							(0x8819)
#define GL_RGBA16F_ARB										(0x881A)
#define GL_RGB16F_ARB										(0x881B)
#define GL_ALPHA16F_ARB										(0x881C)
#define GL_INTENSITY16F_ARB									(0x881D)
#define GL_LUMINANCE16F_ARB									(0x881E)
#define GL_LUMINANCE_ALPHA16F_ARB							(0x881F)
#endif

// ARB color buffer float
#ifndef GL_ARB_color_buffer_float
#define GL_ARB_color_buffer_float							(1)
#define GL_RGBA_FLOAT_MODE_ARB								(0x8820)
#define GL_CLAMP_VERTEX_COLOR_ARB							(0x891A)
#define GL_CLAMP_FRAGMENT_COLOR_ARB							(0x891B)
#define GL_CLAMP_READ_COLOR_ARB								(0x891C)
#define GL_FIXED_ONLY_ARB									(0x891D)
#define WGL_TYPE_RGBA_FLOAT_ARB								(0x21A0)
#endif

// ATI pixel format float
#ifndef WGL_ATI_pixel_format_float
#define WGL_ATI_pixel_format_float							(1)
#define WGL_TYPE_RGBA_FLOAT_ATI								(0x21A0)
#define GL_RGBA_FLOAT_MODE_ATI								(0x8820)
#define GL_COLOR_CLEAR_UNCLAMPED_VALUE_ATI					(0x8835)
#endif

// APPLE float32 & float16
#ifndef GL_APPLE_float_pixels
#define GL_APPLE_float_pixels								(1)
#define GL_HALF_APPLE										(0x140B)
#define GL_RGBA_FLOAT32_APPLE								(0x8814)
#define GL_RGB_FLOAT32_APPLE								(0x8815)
#define GL_ALPHA_FLOAT32_APPLE								(0x8816)
#define GL_INTENSITY_FLOAT32_APPLE							(0x8817)
#define GL_LUMINANCE_FLOAT32_APPLE							(0x8818)
#define GL_LUMINANCE_ALPHA_FLOAT32_APPLE					(0x8819)
#define GL_RGBA_FLOAT16_APPLE								(0x881A)
#define GL_RGB_FLOAT16_APPLE								(0x881B)
#define GL_ALPHA_FLOAT16_APPLE								(0x881C)
#define GL_INTENSITY_FLOAT16_APPLE							(0x881D)
#define GL_LUMINANCE_FLOAT16_APPLE							(0x881E)
#define GL_LUMINANCE_ALPHA_FLOAT16_APPLE					(0x881F)
#define GL_COLOR_FLOAT_APPLE 								(0x8A0F)
#endif

// APPLE texture range
#ifndef GL_APPLE_texture_range
#define GL_APPLE_texture_range								(1)
#define GL_TEXTURE_STORAGE_HINT_APPLE						(0x85BC)
#define GL_STORAGE_PRIVATE_APPLE							(0x85BD)
#define GL_STORAGE_CACHED_APPLE								(0x85BE)
#define GL_STORAGE_SHARED_APPLE								(0x85BF)
#define GL_TEXTURE_RANGE_LENGTH_APPLE						(0x85B7)
#define GL_TEXTURE_RANGE_POINTER_APPLE						(0x85B8)
#endif

// EXT texture rectangle
#ifndef GL_EXT_texture_rectangle
#define GL_EXT_texture_rectangle							(1)
#define GL_TEXTURE_RECTANGLE_EXT          					(0x84F5)
#define GL_TEXTURE_BINDING_RECTANGLE_EXT  					(0x84F6)
#define GL_PROXY_TEXTURE_RECTANGLE_EXT    					(0x84F7)
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_EXT 					(0x84F8)
#endif

// ATI render texture rectangle
#ifndef WGL_TEXTURE_RECTANGLE_ATI
#define WGL_TEXTURE_RECTANGLE_ATI							(0x21A5)
#endif

// FBO framebuffer object
#ifndef GL_EXT_framebuffer_object				
#define GL_EXT_framebuffer_object							(1)
#define GL_FRAMEBUFFER_EXT									(0x8D40)
#define GL_RENDERBUFFER_EXT									(0x8D41)
#define GL_STENCIL_INDEX1_EXT								(0x8D46)
#define GL_STENCIL_INDEX4_EXT								(0x8D47)
#define GL_STENCIL_INDEX8_EXT								(0x8D48)
#define GL_STENCIL_INDEX16_EXT								(0x8D49)
#define GL_RENDERBUFFER_WIDTH_EXT							(0x8D42)
#define GL_RENDERBUFFER_HEIGHT_EXT							(0x8D43)
#define GL_RENDERBUFFER_INTERNAL_FORMAT_EXT					(0x8D44)
#define GL_RENDERBUFFER_RED_SIZE_EXT						(0x8D50)
#define GL_RENDERBUFFER_GREEN_SIZE_EXT						(0x8D51)
#define GL_RENDERBUFFER_BLUE_SIZE_EXT						(0x8D52)
#define GL_RENDERBUFFER_ALPHA_SIZE_EXT						(0x8D53)
#define GL_RENDERBUFFER_DEPTH_SIZE_EXT						(0x8D54)
#define GL_RENDERBUFFER_STENCIL_SIZE_EXT					(0x8D55)
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT			(0x8CD0)
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT			(0x8CD1)
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT			(0x8CD2)
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_EXT	(0x8CD3)
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT	(0x8CD4)
#define GL_COLOR_ATTACHMENT0_EXT							(0x8CE0)
#define GL_COLOR_ATTACHMENT1_EXT							(0x8CE1)
#define GL_COLOR_ATTACHMENT2_EXT							(0x8CE2)
#define GL_COLOR_ATTACHMENT3_EXT							(0x8CE3)
#define GL_COLOR_ATTACHMENT4_EXT							(0x8CE4)
#define GL_COLOR_ATTACHMENT5_EXT							(0x8CE5)
#define GL_COLOR_ATTACHMENT6_EXT							(0x8CE6)
#define GL_COLOR_ATTACHMENT7_EXT							(0x8CE7)
#define GL_COLOR_ATTACHMENT8_EXT							(0x8CE8)
#define GL_COLOR_ATTACHMENT9_EXT							(0x8CE9)
#define GL_COLOR_ATTACHMENT10_EXT							(0x8CEA)
#define GL_COLOR_ATTACHMENT11_EXT							(0x8CEB)
#define GL_COLOR_ATTACHMENT12_EXT							(0x8CEC)
#define GL_COLOR_ATTACHMENT13_EXT							(0x8CED)
#define GL_COLOR_ATTACHMENT14_EXT							(0x8CEE)
#define GL_COLOR_ATTACHMENT15_EXT							(0x8CEF)
#define GL_DEPTH_ATTACHMENT_EXT								(0x8D00)
#define GL_STENCIL_ATTACHMENT_EXT							(0x8D20)
#define GL_FRAMEBUFFER_COMPLETE_EXT							(0x8CD5)
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT			(0x8CD6)
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT	(0x8CD7)
#define GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT	(0x8CD8)
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT			(0x8CD9)
#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT				(0x8CDA)
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT			(0x8CDB)
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT			(0x8CDC)
#define GL_FRAMEBUFFER_UNSUPPORTED_EXT						(0x8CDD)
#define GL_FRAMEBUFFER_BINDING_EXT							(0x8CA6)
#define GL_RENDERBUFFER_BINDING_EXT							(0x8CA7)
#define GL_MAX_COLOR_ATTACHMENTS_EXT						(0x8CDF)
#define GL_MAX_RENDERBUFFER_SIZE_EXT						(0x84E8)
#define GL_INVALID_FRAMEBUFFER_OPERATION_EXT				(0x0506)
//#define GL_MAX_DRAW_BUFFERS_ARB								(0x8824)
#endif

//geometry shaders
#ifndef GL_EXT_geometry_shader4
#define GL_EXT_geometry_shader4						1
#define GL_GEOMETRY_SHADER_EXT						0x8DD9
#define GL_GEOMETRY_VERTICES_OUT_EXT				0x8DDA
#define GL_GEOMETRY_INPUT_TYPE_EXT					0x8DDB
#define GL_GEOMETRY_OUTPUT_TYPE_EXT					0x8DDC
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT		0x8C29
#define GL_MAX_GEOMETRY_VARYING_COMPONENTS_EXT		0x8DDD
#define GL_MAX_VERTEX_VARYING_COMPONENTS_EXT		0x8DDE
#define GL_MAX_VARYING_COMPONENTS_EXT				0x8B4B
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_EXT		0x8DDF
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT			0x8DE0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_EXT	0x8DE1
#define GL_LINES_ADJACENCY_EXT						0xA
#define GL_LINE_STRIP_ADJACENCY_EXT					0xB
#define GL_TRIANGLES_ADJACENCY_EXT					0xC
#define GL_TRIANGLE_STRIP_ADJACENCY_EXT				0xD
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT	0x8DA8
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_EXT	0x8DA9
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT		0x8DA7
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER_EXT	0x8CD4
#define GL_PROGRAM_POINT_SIZE_EXT					0x8642
#endif

//transform feedback
#ifndef GL_EXT_transform_feedback
#define GL_EXT_transform_feedback								1
#define GL_TRANSFORM_FEEDBACK_BUFFER_EXT                      0x8C8E 
#define GL_TRANSFORM_FEEDBACK_BUFFER_START_EXT                0x8C84 
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE_EXT                 0x8C85 
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING_EXT              0x8C8F 
#define GL_INTERLEAVED_ATTRIBS_EXT                            0x8C8C 
#define GL_SEPARATE_ATTRIBS_EXT                               0x8C8D 
#define GL_PRIMITIVES_GENERATED_EXT                           0x8C87 
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN_EXT          0x8C88 
#define GL_RASTERIZER_DISCARD_EXT                             0x8C89 
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS_EXT  0x8C8A 
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS_EXT        0x8C8B 
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS_EXT     0x8C80 
#define GL_TRANSFORM_FEEDBACK_VARYINGS_EXT                    0x8C83 
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE_EXT                 0x8C7F
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH_EXT          0x8C76 
#endif

// draw buffer for MRT FBO
#ifndef GL_ARB_draw_buffers
#define GL_MAX_DRAW_BUFFERS_ARB           0x8824
#define GL_DRAW_BUFFER0_ARB               0x8825
#define GL_DRAW_BUFFER1_ARB               0x8826
#define GL_DRAW_BUFFER2_ARB               0x8827
#define GL_DRAW_BUFFER3_ARB               0x8828
#define GL_DRAW_BUFFER4_ARB               0x8829
#define GL_DRAW_BUFFER5_ARB               0x882A
#define GL_DRAW_BUFFER6_ARB               0x882B
#define GL_DRAW_BUFFER7_ARB               0x882C
#define GL_DRAW_BUFFER8_ARB               0x882D
#define GL_DRAW_BUFFER9_ARB               0x882E
#define GL_DRAW_BUFFER10_ARB              0x882F
#define GL_DRAW_BUFFER11_ARB              0x8830
#define GL_DRAW_BUFFER12_ARB              0x8831
#define GL_DRAW_BUFFER13_ARB              0x8832
#define GL_DRAW_BUFFER14_ARB              0x8833
#define GL_DRAW_BUFFER15_ARB              0x8834
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

#endif // JIT_GL_SUPPORT_H
