#ifndef JIT_GL_CONTEXT_H
#define JIT_GL_CONTEXT_H

/****************************************************************************/

#include "jit.gl.h"
#if defined(WIN_VERSION) || !defined(GL3_VERSION)
	#define JIT_GL_USE_PROCS 1
#endif
#ifdef JIT_GL_USE_PROCS
	#include "jit.gl.procs.h"
#endif
#include "jit.gl.support.h"
#include "jit.gl.pixelformat.h"

/*************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif


/****************************************************************************/

typedef struct _jit_gl_context_struct
{
	t_jit_gl_native_context			context;
	t_jit_gl_native_device			device;
	t_jit_gl_native_pixelformat 	pixelformat;
#ifdef JIT_GL_USE_PROCS
	t_jit_gl_extprocs				*procs;			// proc table for opengl extensions
#endif
	t_jit_gl_support				*support;		// opengl feature support
	const char						*extensions;	// opengl extensions string 
	void							*target;
	long							targettype;		// window/pwindow/matrix/other
	long							renderer_id;	// mac only
	long							flags;
	void							*auxdata;
	void							*offscreentex;
	void							*offscreenfbo;
#ifdef WIN_VERSION
	t_jit_gl_platform_data			platform_data;
#endif
} t_jit_gl_context_struct, *t_jit_gl_context;

typedef struct _jit_gl_context_info
{
	long							flags;
	long							targettype;		//window/pwindow/matrix/other
	long							renderer_id;	//mac only
	t_jit_gl_context				share;
	t_jit_gl_pixelformat			*pixelformat;
	void							*nativewin;
} t_jit_gl_context_info;


/****************************************************************************/

t_jit_gl_context jit_gl_create_context(void *target, t_jit_gl_context_info *info);
GLboolean jit_gl_destroy_context(t_jit_gl_context ctx);
GLboolean jit_gl_destroy_native_context(t_jit_gl_native_context native);
GLboolean jit_gl_update_context(t_jit_gl_context ctx);
GLboolean jit_gl_set_context(t_jit_gl_context ctx);
t_jit_gl_context jit_gl_get_context(void);
t_jit_gl_support *jit_gl_get_support(void);
GLboolean jit_gl_context_swap_buffers(t_jit_gl_context ctx);
GLboolean jit_gl_configure(GLenum pname, GLuint param);
long jit_gl_set_swap_interval(t_jit_gl_context ctx, long interval);
char jit_gl_is_extension_supported(t_jit_gl_context ctx, const char* ext);

/****************************************************************************/

// context flags
#define JIT_GL_CTX_DOUBLEBUF		0x00000001
#define JIT_GL_CTX_DEPTHBUF			0x00000002
#define JIT_GL_CTX_ACCELERATED		0x00000004
#define JIT_GL_CTX_FSAA				0x00000008
#define JIT_GL_CTX_HINT_QUALITY		0x00000010
#define JIT_GL_CTX_STEREO			0x00000020

// target types	
#define JIT_GL_TARGET_WINDOW		0x00000000
#define	JIT_GL_TARGET_MATRIX		0x00000001
#define JIT_GL_TARGET_PWINDOW		0x00000002
#define JIT_GL_TARGET_TEXTURE		0x00000003
#define JIT_GL_TARGET_ROOT_SHARED	0x00000004

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

#endif
