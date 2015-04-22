/*
 * Copyright 2001-2005 - Cycling '74
 * Randall Jones - rej@2uptech.com 
 *
 * OpenGL Chunk structure used to store one gl-command's-worth of data, 
 * in a format which can be passed easily to glDrawRangeElements
 */

/****************************************************************************/

#ifndef JIT_GL_CHUNK_H
#define JIT_GL_CHUNK_H

/****************************************************************************/

#include "jit.gl.h"

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
 * t_jit_glchunk is a public structure to store one gl-command's-worth of data, 
 * in a format which can be passed easily to glDrawRangeElements, and matrixoutput.  
 *
 */
typedef struct _jit_glchunk {
	t_symbol	*	prim;			///< drawing primitive. "tri_strip", "tri", "quads", "quad_grid", etc. 
	t_jit_object *	m_vertex;		///< vertex matrix containing xyzst... data 
	t_symbol *		m_vertex_name;	///< vertex matrix name
	t_jit_object *	m_index;		///< optional 1d matrix of vertex indices to use with drawing primitive
	t_symbol *		m_index_name;	///< index matrix name
	unsigned long	m_flags;		///< chunk flags to ignore texture, normal, color, or edge planes when drawing
	void *			next_chunk;		///< pointer to next chunk for drawing a list of chunks together
}
t_jit_glchunk;

/****************************************************************************/

t_jit_glchunk * jit_glchunk_new(t_symbol * prim, int planes, int vertices, int indices);
t_jit_glchunk * jit_glchunk_grid_new(t_symbol * prim, int planes, int width, int height);
void jit_glchunk_delete(t_jit_glchunk * x);
t_jit_err jit_glchunk_copy(t_jit_glchunk ** newcopy, t_jit_glchunk * orig);

/****************************************************************************/

// flags for chunk creation
#define JIT_GL_CHUNK_IGNORE_TEXTURES		1 << 0
#define JIT_GL_CHUNK_IGNORE_NORMALS			1 << 1
#define JIT_GL_CHUNK_IGNORE_COLORS			1 << 2
#define JIT_GL_CHUNK_IGNORE_EDGES			1 << 3

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

#endif // JIT_GL_CHUNK_H
