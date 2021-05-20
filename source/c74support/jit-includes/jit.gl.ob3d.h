#ifndef JIT_GL_OB3D_H
#define JIT_GL_OB3D_H

/****************************************************************************/

#include "jit.gl.h"

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


typedef struct _jit_class3d
{
	long				oboffset; 		// instance byte offset to the ob3d struct.
	long				flags;
	// extensible
} t_jit_class3d;

/****************************************************************************/

void *jit_ob3d_setup(void * jit_class, long oboffset, long ob3d_flags);
t_jit_err jit_ob3d_set(void *x, void *p);
void *jit_ob3d_get(void *x);
void *jit_ob3d_new(void *x, t_symbol * dest_name);
void jit_ob3d_free(void *x);
t_jit_err jit_ob3d_set_context(void *x);
t_jit_err jit_ob3d_draw_chunk(void *ob3d, t_jit_glchunk * chunk);
void jit_ob3d_set_viewport(void *v, long x, long y, long width, long height);

void * ob3d_maxob_get(void *v);
void * ob3d_jitob_get(void *v);
void * ob3d_patcher_get(void *v);
long ob3d_auto_get(void *v);
long ob3d_enable_get(void *v);
long ob3d_ui_get(void *v);
void * ob3d_outlet_get(void *v);
long ob3d_dirty_get(void *v);
void ob3d_dirty_set(void *v, long c);
void ob3d_dest_dim_set(void *v, long width, long height);
void ob3d_dest_dim_get(void *v, long *width, long *height);
void ob3d_render_ptr_set(void *v, void *render_ptr);
void * ob3d_render_ptr_get(void *v);

void ob3d_set_color(void *v, float *color);
void ob3d_get_color(void *v, float *color);
long ob3d_texture_count(void *v);
	
t_jit_err ob3d_draw_begin(void *ob3d, long setup);
t_jit_err ob3d_draw_end(void *ob3d, long setup);
t_jit_err ob3d_draw_preamble(void *ob3d);

t_symbol * jit_ob3d_init_jpatcher_render(void *jitob);

t_jit_err jit_ob3d_dest_name_set(t_jit_object *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_vbo_create(void *x, GLenum target, GLenum usage);
t_jit_err jit_gl_vbo_submit(void *x, long size, const void *data);

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
