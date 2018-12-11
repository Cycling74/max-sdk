// jit.gl.h
// 


#ifndef __JIT_GL_H__
#define __JIT_GL_H__

// --------------------------------------------------------------------------------

#include "jit.gl.common.h"

// --------------------------------------------------------------------------------

#ifdef MAC_VERSION

	#ifdef GL3_VERSION

		#include <OpenGL/gl3.h>
		#define GL_QUAD_STRIP                     0x0008
		#define GL_POLYGON                        0x0009

	#else

		#include <OpenGL/gl.h>
		#include <OpenGL/glu.h>

	#endif

	#include <OpenGL/OpenGL.h>

	void * nsglGetProcAddress (const char *pszProc);
	void nsglSetRect(void *context, GLint *val);

	#define glGetProcAddress nsglGetProcAddress

	#include "jit.glext.h"

#endif	// MAC_VERSION

// --------------------------------------------------------------------------------

#ifdef WIN_VERSION

	#include <windows.h>

	#ifdef GL3_VERSION
		#if defined(_DEBUG)
			#define printf printf2
			int __cdecl printf2(const char *format, ...);
		#endif

		#include "GL\gl3w.h"
		
		#include "wglext.h"
		//#include "jit.wglext.h"
		//#include "jit.glext.h"

		#ifndef GL_APPLE_ycbcr_422
		#define GL_APPLE_ycbcr_422 1
		#define GL_YCBCR_422_APPLE                0x85B9
		#endif /* GL_APPLE_ycbcr_422 */

		#define GL_QUAD_STRIP                     0x0008
		#define GL_POLYGON                        0x0009

		#define GLsizeiptrARB GLsizeiptr
		#define GLintptrARB GLintptr
		#define GLhandleARB unsigned int
		#define GLcharARB GLchar
		#define GLhalfARB unsigned short
		#define GLhalfNV unsigned short

	#else

		#include "gl\gl.h"
		#include "gl\glu.h"
		#include "jit.wglext.h"
		#include "jit.glext.h"
	#endif
	
	#define glGetProcAddress wglGetProcAddress
	#define glCheckFramebufferStatus glCheckFramebufferStatusEXT


	/*
	Key object types:

	HDC - a handle to a device independent graphics context (screen, printer, memory, etc.).  HDC
	conflates the AGLDevice and AGLDrawable concepts.

	HGLRC - a handle to an opengl rendering context.  Equivalent to an AGLContext.
	*/
	typedef HWND						t_jit_gl_native_window;
	typedef HDC							t_jit_gl_native_device;
	typedef HDC							t_jit_gl_native_drawable;
	typedef HGLRC						t_jit_gl_native_context;
	typedef GLint*						t_jit_gl_native_pixelformat;

	typedef struct _jit_gl_platform_data {
		PROC set_swap_interval;
		float scalefactor;
	} t_jit_gl_platform_data;

#endif	// WIN_VERSION

// --------------------------------------------------------------------------------

#include "jit.gl.draw.h"
#include "jit.gl.chunk.h"
#include "jit.gl.ob3d.h"
#ifndef GL3_VERSION
#include "jit.gl.procs.h"
#endif
#include "jit.gl.support.h"
#include "jit.gl.context.h"
#include "jit.gl.drawinfo.h"
#include "jit.gl.pixelformat.h"
#include <math.h>

/****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif


// --------------------------------------------------------------------------------
// get the appropriate version of objects depending on OpenGL version used
long jit_gl_object_is_texture(void *x);
long jit_gl_texture_get(void **tex, t_symbol *dest_name);
long jit_gl_slab_get(void **slab, t_symbol *dest_name);
long jit_gl_mesh_get(void **mesh, t_symbol *dest_name);

// --------------------------------------------------------------------------------
// utility methods

long jit_gl_available(void);
void jit_gl_init(void);
void jit_gl_renderer_set(void * p);
void * jit_gl_renderer_get();
void jit_gl_set_floats(float *pf, int count, ...);
int jit_gl_get_blend_mode(int index);
long jit_gl_report_error (char *prefix);
long jit_gl_object_report_error (void *x, char *prefix);
void jit_gl_object_error (void *x, char *s, ...);

// --------------------------------------------------------------------------------
// query methods

const char* jit_gl_get_vendor();
const char* jit_gl_get_renderer();
const char* jit_gl_get_version();
const char* jit_gl_get_glu_version();
const char* jit_gl_get_extensions();
const char* jit_gl_get_glsl_version();
char jit_gl_is_min_version(int major, int minor, int release);
long jit_gl_plane_from_format(GLenum format);
long jit_gl_get_datasize_from_datatype(GLenum e);


t_jit_err jit_gl_worldtoscreen(t_jit_object *x, t_point_3d p_world, t_point_3d p_screen); 
t_jit_err jit_gl_screentoworld(t_jit_object *x, t_point_3d p_screen, t_point_3d p_world);
extern void * jit_gl_getscenegraph(t_symbol *ctx);

t_jit_err jit_err_from_max_err(t_max_err err);

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

#endif // __JIT_GL_H__
