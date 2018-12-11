#ifndef JIT_GL_DRAW_H
#define JIT_GL_DRAW_H 1

#include "jit.common.h"
#include "jit.vecmath.h"

#ifdef __cplusplus
extern "C" {
#endif

t_jit_err jit_ob3d_draw_geometry(void *ob3d, t_jit_object *geometry);

/** Data structures and functions for OpenGL drawing
*/


/** Represents a view into a buffer, for use with glVertexAttribPointer etc.
*/
typedef struct _jit_gl_buffer_view
{
	t_symbol		*name;		//< Name of buffer view
	uint			type;		//< Type of data (e.g. GL_FLOAT)
	uint			size;		//< Number of components (e.g. 3 for vec3)
	uchar			normalized;	//< Whether fixed-point values should be normalized or not
	int				stride;		//< Byte offset between elements
	long			offset;		//< Byte offset to start of buffer
	long			active;		//< Used internally, do not touch
	void			*ud;		//< Used internally, do not touch
} t_jit_gl_buffer_view;

typedef enum {
	BUFFER_DATA_PERSISTENT = (1<<0)
} e_buffer_data_flag;


/** Represents data to be stored in a buffer
*/
typedef struct _jit_gl_buffer_data
{
	long					nviews;		//< Number of views
	t_jit_gl_buffer_view	**views;	//< Views into data
	long					constant;	//< Whether the data represents a constant vertex attribute
	long					size;		//< Size of data
	long					flags;		//< Data flags
	void					*ptr;		//< Pointer to data (can be NULL)
	int						instance_div; 	//< If set indicates glVertexAttribDivisor value for instance drawing
} t_jit_gl_buffer_data;


/** Create a buffer data object with a format specified by tags
	Tag format: buffer kind, buffer type, ..., ..., VIEW_TAG_NULL
	NOTE: the list of tags must always be terminated by a VIEW_TAG_NULL tag.
	
		examples:
			1) A buffer with vertices and normals:
				tags - {
					VIEW_TAG_VERTEX, VIEW_TAG_VEC3, 
					VIEW_TAG_NORMAL, VIEW_TAG_VEC3, 
					VIEW_TAG_NULL
				}
				buffer layout - VVVNNN
	
			2) A buffer with only vertices: 
				tags - {
					VIEW_TAG_VERTEX, VIEW_TAG_VEC3, 
					VIEW_TAG_NULL
				}
				buffer layout - VVV
				
			3) A buffer with vertices, texture coordinates, and colors: 
				tags - {
					VIEW_TAG_VERTEX, VIEW_TAG_VEC3, 
					VIEW_TAG_TEXCOORD, VIEW_TAG_VEC2, 
					VIEW_TAG_COLOR, VIEW_TAG_VEC4, 
					VIEW_TAG_NULL
				}
				buffer layout - VVVTTCCCC
*/
typedef enum {
	VIEW_TAG_INVALID = -1,
	VIEW_TAG_NULL = 0,
	
	// buffer semantics
	VIEW_TAG_IGNORE,
	VIEW_TAG_VERTEX,
	VIEW_TAG_TEXCOORD,
	VIEW_TAG_NORMAL,
	VIEW_TAG_COLOR,
	VIEW_TAG_INDEX,

	// buffer types
	VIEW_TAG_CHAR,
	VIEW_TAG_UCHAR,
	VIEW_TAG_INT,
	VIEW_TAG_UINT,
	VIEW_TAG_FLOAT,
	VIEW_TAG_DOUBLE,
	VIEW_TAG_VEC2,
	VIEW_TAG_VEC3,
	VIEW_TAG_VEC4
} e_view_tag;

void jit_gl_buffer_data_create_tagged(t_jit_gl_buffer_data *x, e_view_tag *tags, long size, char *ptr);
void jit_gl_buffer_data_create_constant(t_jit_gl_buffer_data *x, e_view_tag *tags, long size, char *ptr);
long jit_gl_buffer_data_create_from_matrix_data(t_jit_gl_buffer_data *x, t_jit_matrix_info *info, char *ptr);
void jit_gl_buffer_data_create_instances(t_jit_gl_buffer_data *x, e_view_tag view_type, int count, long size, char *ptr);
void jit_gl_buffer_data_destroy_tagged(t_jit_gl_buffer_data * x);

/** Immediate mode simulating functions
	
	Example usage:
	
	float c[] = {1., 0., 0., 1.};
	void *state = jit_object_method(x, gensym("get_state"));
	jit_gl_state_begin(state);
		jit_gl_colorfv(c);
		jit_gl_polygon_mode(JIT_STATE_FRONT_AND_BACK, JIT_STATE_LINE);
		// do the drawing
	jit_gl_state_end();
*/


/** Enable transations with the rendering state
*/
void jit_gl_state_begin(void *state);
void jit_gl_state_end();

/** Enums for manipulating rendering state
*/
typedef enum {
	JIT_STATE_FALSE = 0,
	JIT_STATE_TRUE = 1,
	
	// primitives
	JIT_STATE_POINTS,
	JIT_STATE_LINES,
	JIT_STATE_LINE_LOOP,
	JIT_STATE_LINE_STRIP,
	JIT_STATE_TRIANGLES,
	JIT_STATE_TRIANGLE_STRIP,
	JIT_STATE_TRIANGLE_FAN,
	JIT_STATE_QUADS,
	JIT_STATE_QUAD_STRIP,
	JIT_STATE_POLYGON,
	JIT_STATE_LINES_ADJACENCY,
	JIT_STATE_LINE_STRIP_ADJACENCY,
	JIT_STATE_TRIANGLES_ADJACENCY,
	JIT_STATE_TRIANGLE_STRIP_ADJACENCY,
	
	// matrices
	JIT_STATE_MODELVIEW,
	JIT_STATE_PROJECTION,

	// material enums
	JIT_STATE_FRONT_AND_BACK,
	JIT_STATE_FRONT,
	JIT_STATE_BACK,
	JIT_STATE_CULL_FACE,
	JIT_STATE_EMISSION,
	JIT_STATE_AMBIENT,
	JIT_STATE_DIFFUSE,
	JIT_STATE_SPECULAR,
	JIT_STATE_SHININESS,
	JIT_STATE_AMBIENT_AND_DIFFUSE,
	
	// light enums
	JIT_STATE_LIGHT0=100,
	JIT_STATE_LIGHT1=101,
	JIT_STATE_LIGHT2=102,
	JIT_STATE_LIGHT3=103,
	JIT_STATE_LIGHT4=104,
	JIT_STATE_LIGHT5=105,
	JIT_STATE_LIGHT6=106,
	JIT_STATE_LIGHT7=107,
	JIT_STATE_SPOT_EXPONENT,
	JIT_STATE_SPOT_CUTOFF,
	JIT_STATE_CONSTANT_ATTENUATION,
	JIT_STATE_LINEAR_ATTENUATION,
	JIT_STATE_QUADRATIC_ATTENUATION,
	JIT_STATE_POSITION,
	JIT_STATE_SPOT_DIRECTION,
	JIT_STATE_LIGHT_MODEL_AMBIENT,
	JIT_STATE_LIGHT_MODEL_TWO_SIDE,
	
	JIT_STATE_LIGHTING,
	JIT_STATE_NORMALIZE,
	JIT_STATE_COLOR_MATERIAL,
	
	JIT_STATE_POINT,
	JIT_STATE_LINE,
	JIT_STATE_FILL,
	
	JIT_STATE_SMOOTH,
	JIT_STATE_FLAT,
	
	JIT_STATE_FOG,
	JIT_STATE_FOG_MODE,
	JIT_STATE_FOG_DENSITY,
	JIT_STATE_FOG_START,
	JIT_STATE_FOG_END,
	JIT_STATE_FOG_COLOR,

	JIT_STATE_LINEAR,
	JIT_STATE_EXP,
	JIT_STATE_EXP2,
	
	JIT_STATE_INSTANCING
} e_jit_state;


/** Apply updates on the rendering state
*/
void jit_gl_materialf(e_jit_state face, e_jit_state pname, float v);
void jit_gl_materialfv(e_jit_state face, e_jit_state pname, float *v);
void jit_gl_lightf(e_jit_state light, e_jit_state pname, float v);
void jit_gl_lightfv(e_jit_state light, e_jit_state pname, float *v);
void jit_gl_light_modeli(e_jit_state pname, int v);
void jit_gl_light_modelfv(e_jit_state pname, float *v);
void jit_gl_enable(e_jit_state cap);
void jit_gl_disable(e_jit_state cap);
void jit_gl_polygon_mode(e_jit_state face, e_jit_state mode);
void jit_gl_cull_face(e_jit_state mode);
void jit_gl_shade_model(e_jit_state mode);
void jit_gl_colorfv(float *c);
void jit_gl_colorf(float r, float g, float b, float a);
void jit_gl_color(t_jit_vec4 *c);
void jit_gl_color_material(e_jit_state face, e_jit_state mode);
void jit_gl_fogi(e_jit_state pname, long v);
void jit_gl_fogf(e_jit_state pname, float v);
void jit_gl_fogfv(e_jit_state pname, float *v);
void jit_gl_matrix_mode(e_jit_state mode);
t_jit_mat4 * jit_gl_get_matrix();
void jit_gl_get_modelview_matrix(t_jit_mat4 * modelview);
void jit_gl_get_projection_matrix(t_jit_mat4 * proj);
void jit_gl_push_matrix();
void jit_gl_pop_matrix();
void jit_gl_load_identity();
void jit_gl_load_matrix(t_jit_mat4 *m);
void jit_gl_translate(float x, float y, float z);
void jit_gl_rotate(float angle, float x, float y, float z);
void jit_gl_scale(float x, float y, float z);
void jit_gl_ortho(double left, double right, double bottom, double top, double zNear, double zFar);
void jit_gl_set_shader(void *shader);
void jit_gl_bind_texture(long unit, void *texture);
void jit_gl_unbind_texture(long unit, void *texture);
void jit_gl_immediate_begin(e_jit_state primitive);
void jit_gl_immediate_end();
void jit_gl_immediate_vertex2f(float x, float y);
void jit_gl_immediate_vertex3f(float x, float y, float z);
void jit_gl_immediate_texcoord2f(float x, float y);
void jit_gl_immediate_texcoord3f(float x, float y, float z);
void jit_gl_immediate_normal3f(float x, float y, float z);
void jit_gl_immediate_color3f(float r, float g, float b);
void jit_gl_immediate_color4f(float r, float g, float b, float a);
void *jit_gl_immediate_getgeometry();

void *jit_ob3d_state_get(t_jit_object *x);
void jit_ob3d_state_set(t_jit_object *x, void *state);
void jit_ob3d_state_begin(t_jit_object *x);
void jit_ob3d_state_end(t_jit_object *x);
	
// fullscreen quad
void * jit_gl_fs_quad_getgeometry(long flipped);
void jit_gl_fs_quad_draw(void *geometry, void *state, long width, long height);

t_jit_err jit_gl_state_bind_texture(void *state, long unit, void *texture);
t_jit_err jit_gl_state_unbind_texture(void *state, long unit, void *texture);
	
// struct to manage external textures
typedef struct _jit_gl_texture_ex {
	t_jit_object		ob;
	void				*pob;
	long				id;
	long				target;			// TEXTURE_1D, TEXTURE_2D, etc.
	long				dim[3];			// Dimensions of texture
	long				rectangle;		// 2D textures use rectangle target
	long				flip;
	t_symbol			*name;
	method				bindmeth;
	method				unbindmeth;
} t_jit_gl_texture_ex;
	
#ifdef __cplusplus
}
#endif

#endif
