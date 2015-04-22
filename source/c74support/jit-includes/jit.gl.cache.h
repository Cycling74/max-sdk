/*
 * jit.gl.cache.h
 *
 * Internal data structure for storing cached geometric data.
 *
 */

// --------------------------------------------------------------------------------

#ifndef JIT_GL_MESH_CACHE_H
#define JIT_GL_MESH_CACHE_H

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

#define JIT_GL_MESH_CACHE_NONE				0
#define JIT_GL_MESH_CACHE_AUTO				1
#define JIT_GL_MESH_CACHE_DISPLAYLIST		2
#define JIT_GL_MESH_CACHE_VERTEXARRAY		3
#define JIT_GL_MESH_CACHE_VERTEXBUFFER		4
#define JIT_GL_MESH_CACHE_DEFAULT_GROW		64

#define JIT_SYM_IF(x) ((x) && (x) != _jit_sym_nothing && (x)->s_name)
#define JIT_SYM_SAFECSTR(x) ((JIT_SYM_IF(x)) ? (x)->s_name : "<null>" )

// --------------------------------------------------------------------------------

typedef struct _jit_gl_cache {
	void						*data;			// raw data values
	long						bytes;			// number of allocated bytes
	long						manage;			// flag to manage data creation/deletion
	long						type;			// type of cached data (VERTEX/NORMAL/etc)
	long						buffertype;		// type of buffer (ARRAY/ELEMENT)
	long						datatype;		// enumerated datatype prim
	long						datasize;		// sizeof datatype
	long						enumtype;		// type of geometry (quad, triangles, line)
	long						geomsize;		// size of geometry primitive (4=quad, 3=triangle, 2=line)
	long						elements;		// total elements
	long						drawcount;		// number of draw submissions
	long						drawsize;		// size of draw submission
	long						count;			// number of coordinates
	long						coords;			// coordinate dimensions (1-4)
	long						stride;			// stride length between elements
	long						start;			// start index
	long						end;			// end index
	long						mode;			// cache mode (STATIC/DYNAMIC)
	long						used;			// used flag
	long						update;			// update flag
	long						capacity;		// allocated element count
	long						grow;			// resize amount
	long						id;				// id for cached data
	
} t_jit_gl_cache;

// --------------------------------------------------------------------------------

extern t_symbol *ps_jit_gl_cache_none;
extern t_symbol *ps_jit_gl_cache_auto;
extern t_symbol *ps_jit_gl_cache_var;
extern t_symbol *ps_jit_gl_cache_vbo;
extern t_symbol *ps_jit_gl_cache_dl;
extern t_symbol *ps_jit_gl_cache_vertexarray;
extern t_symbol *ps_jit_gl_cache_vertexbuffer;
extern t_symbol *ps_jit_gl_cache_displaylist;

// --------------------------------------------------------------------------------

t_jit_err jit_gl_cache_init(void);
t_jit_gl_cache * jit_gl_cache_new(long count, long coords, long datatype);
void jit_gl_cache_free(t_jit_gl_cache *x);
t_jit_err jit_gl_cache_clear(t_jit_gl_cache *x);
t_jit_err jit_gl_cache_buffer_destroy(t_jit_gl_cache *x);
t_jit_err jit_gl_cache_destroy(t_jit_gl_cache *x);
t_jit_err jit_gl_cache_reset(t_jit_gl_cache *x);
long jit_gl_cache_compare(t_jit_gl_cache *x, long a, long b, double epsilon);
t_jit_err jit_gl_cache_weld(t_jit_gl_cache *x, double epsilon);
t_jit_err jit_gl_cache_grow(t_jit_gl_cache *x, long bytes, long copy);
t_jit_err jit_gl_cache_resize(t_jit_gl_cache *x, long elements, long coords, long datatype, long copy);
t_jit_err jit_gl_cache_append(t_jit_gl_cache *x, char *data, long count, long coords, long datatype);
t_jit_err jit_gl_cache_replace(t_jit_gl_cache *x, long index, char *data, long count, long coords, long datatype);
GLenum jit_gl_cache_datatype_from_symbol(t_symbol *s);
long jit_gl_cache_datasize_from_datatype(GLenum e);

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


#endif // JIT_GL_MESH_CACHE_H
