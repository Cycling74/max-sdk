/*
 * Copyright 2001-2005 - Cycling '74
 * Joshua Kit Clayton - jkc@cycling74.com 
 *
 * OpenGL drawinfo structure used to store texture binding info per draw call. 
 */

/****************************************************************************/

#ifndef JIT_GL_DRAWINFO_H
#define JIT_GL_DRAWINFO_H

/****************************************************************************/

#include "jit.gl.context.h"

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

/**
 * t_jit_gl_drawinfo struct used for tasks such as multi texture unit binding.
 *
 */
typedef struct _jit_gl_drawinfo
{
	t_jit_gl_context	ctx;		///< current t_jit_gl_context
	void 				*ob3d;		///< object's t_jit_ob3d pointer
	void				*rfu[6];	///< reserved for future use
} t_jit_gl_drawinfo;

t_jit_err jit_gl_drawinfo_setup(void *x, t_jit_gl_drawinfo *drawinfo);
long jit_gl_drawinfo_active_textures(t_jit_gl_drawinfo *drawinfo);
void jit_gl_texcoord1f(t_jit_gl_drawinfo *drawinfo, float s);
void jit_gl_texcoord2f(t_jit_gl_drawinfo *drawinfo, float s, float t);
void jit_gl_texcoord3f(t_jit_gl_drawinfo *drawinfo, float s, float t, float r);
void jit_gl_texcoord1fv(t_jit_gl_drawinfo *drawinfo, float *v);
void jit_gl_texcoord2fv(t_jit_gl_drawinfo *drawinfo, float *v);
void jit_gl_texcoord3fv(t_jit_gl_drawinfo *drawinfo, float *v);
void jit_gl_bindtexture(t_jit_gl_drawinfo *drawinfo, t_symbol *s, long i);
void jit_gl_unbindtexture(t_jit_gl_drawinfo *drawinfo, t_symbol *s, long i);
void jit_gl_begincapture(t_jit_gl_drawinfo *drawinfo, t_symbol *s, long i);
void jit_gl_endcapture(t_jit_gl_drawinfo *drawinfo, t_symbol *s, long i);

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
