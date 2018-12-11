#ifndef _JIT_GL_COMMON_H_
#define _JIT_GL_COMMON_H_

#include "jit.common.h"

#ifdef __cplusplus
extern "C" {
#endif

#if C74_PRAGMA_STRUCT_PACKPUSH
#pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
#pragma pack(2)
#endif



// constants
#define		JIT_GL_RENDER_REG_STR	"jit_r3nd3r_"
#define		JIT_CLASS3D_FINDER		"this_is_the_jit_class3d"
	
#define		JIT_GL_MAX_TEXTUREUNITS	32
	
#ifndef PI
#define		PI	3.141592653589793
#endif
	
// layer defines
#define JIT_GL_LAYER_FIRST		-1000
#define JIT_GL_LAYER_DEFAULT	0
#define JIT_GL_LAYER_LAST		1000
	
// animator update priority flags
#define JIT_ANIMATOR_PRIORITY_FIRST	-1000
#define JIT_ANIMATOR_PRIORITY_DEF	0
#define JIT_ANIMATOR_PRIORITY_PASS2	1000	// updated *after* nodes are updated
	
// default animator mouse-ui priority
#define JIT_ANIM_UIP_FIRST			-1000
#define JIT_ANIM_UIP_CORNERPIN		-900	// gl.cornerpin
#define JIT_ANIM_UIP_PHYS			-800	// phys.picker
#define JIT_ANIM_UIP_HANDLE			-700	// gl.handle
#define JIT_ANIM_UIP_DEFAULT		0
#define JIT_ANIM_UIP_ADRIVE			900	// anim.drive
#define JIT_ANIM_UIP_LAST			1000
	
#define JIT_GL_MAX_PICK_FILTERS		10



// ob3d stuff
// flags -- default: all flags off.
	
#define JIT_OB3D_NO_ROTATION_SCALE			1 << 0      ///< ob3d flag @ingroup jitter
#define JIT_OB3D_NO_POLY_VARS				1 << 1      ///< ob3d flag @ingroup jitter
#define JIT_OB3D_NO_BLEND					1 << 2      ///< ob3d flag @ingroup jitter
#define JIT_OB3D_NO_TEXTURE					1 << 3      ///< ob3d flag @ingroup jitter
#define JIT_OB3D_NO_MATRIXOUTPUT			1 << 4      ///< ob3d flag @ingroup jitter
#define JIT_OB3D_AUTO_ONLY					1 << 5      ///< ob3d flag @ingroup jitter
#define JIT_OB3D_DOES_UI					1 << 6      ///< ob3d flag @ingroup jitter
#define JIT_OB3D_NO_DEPTH					1 << 7      ///< ob3d flag @ingroup jitter
#define JIT_OB3D_NO_ANTIALIAS				1 << 8      ///< ob3d flag @ingroup jitter
#define JIT_OB3D_NO_FOG						1 << 9      ///< ob3d flag @ingroup jitter
#define JIT_OB3D_NO_LIGHTING_MATERIAL		1 << 10     ///< ob3d flag @ingroup jitter
#define JIT_OB3D_HAS_LIGHTS					1 << 11     ///< ob3d flag @ingroup jitter
#define JIT_OB3D_HAS_CAMERA					1 << 12     ///< ob3d flag @ingroup jitter
#define JIT_OB3D_IS_RENDERER				1 << 13     ///< ob3d flag @ingroup jitter
#define JIT_OB3D_NO_COLOR					1 << 14     ///< ob3d flag @ingroup jitter
#define JIT_OB3D_IS_SLAB					1 << 15     ///< ob3d flag @ingroup jitter
#define JIT_OB3D_NO_SHADER					1 << 16
#define JIT_OB3D_IS_NODE					1 << 17
#define JIT_OB3D_IS_CAMERA					1 << 18
#define JIT_OB3D_NO_BOUNDS					1 << 19
#define JIT_OB3D_NO_POSITION				1 << 20
	
	

typedef long t_jit_gl_context_modifier;
#define JIT_GL_VIEW_COMMAND_KEY		(1<<0)
#define JIT_GL_VIEW_SHIFT_KEY		(1<<1)
#define JIT_GL_VIEW_CAPS_LOCK		(1<<2)
#define JIT_GL_VIEW_ALT_KEY			(1<<3)
#define JIT_GL_VIEW_CONTROL_KEY		(1<<4)



extern t_symbol *_jit_glengine;



void max_ob3d_setup(void);					// legacy api
void max_jit_class_ob3d_wrap(t_class *c);	// newer api

// attach jit object bearing an ob3d to a max object and its outlet.
void max_jit_ob3d_attach(void *x, t_jit_object *jit_ob, void *outlet);
void max_jit_ob3d_detach(void *x);
t_jit_err max_jit_ob3d_assist(void *x, void *b, long m, long a, char *s);
t_atom_long max_jit_ob3d_acceptsdrag(void *x, t_object *drag, t_object *view);
void max_jit_ob3d_seterrorob(void *x);
void* max_jit_ob3d_geterrorob();

	
/**
 * t_wind_mouse_info_struct provided by jit.window and jit.pwindow mouse events
 *
 */
typedef struct {
	t_atom		mouseatoms[8];	///< h, v, (up/down), cmdKey, shiftKey, alphaLock, option, control.
	int			argc;			///< argument count
	t_symbol 	*mousesymbol;	///< mouse event type
}  t_wind_mouse_info;

typedef struct {
	t_atom		mouseatoms[16];	///< h, v, (up/down), cmdKey, shiftKey, alphaLock, option, control, dx, dy + RFU
	int			argc;			///< argument count
	t_symbol 	*mousesymbol;	///< mouse event type
}  t_wind_mousewheel_info;

typedef struct {
	t_atom		keyatoms[8];	///< keycode, textcharacter, (up/down), cmdKey, shiftKey, alphaLock, option, control.
	int			argc;			///< argument count
	t_symbol 	*keysymbol;		///< key event type
}  t_wind_key_info;



// --------------------------------------------------------------------------------
// geometry stuff

/** 2D point (GLfloat) */
typedef float t_point_2d[2];
/** 3D point (GLfloat) */
typedef float t_point_3d[3];
/** 3D vector (GLfloat) */
typedef float t_vec_3d[3];
/** 4D quaternion (GLfloat). Used for rotation */
typedef float t_quaternion[4];
/** 4D angle/axis rotation vector (GLfloat) */
typedef float t_rotation[4];
/** RGBA color vector (GLfloat) */
typedef float t_color[4];

/** Line or line segment in 3D space (GLfloat) */
typedef struct {
	float u[3]; ///< starting point
	float v[3]; ///< ending point
}  	t_line_3d;						// line or line segment

typedef struct {
	t_symbol	*colormode;	///< texture colormode
	t_symbol	*type;		///< texture data type (char, float32, ...)
	int			dim[3];		///< texture dimensions
	int			dimcount;	///< number of texture dimensions
} t_jit_gl_texture_info;



typedef struct _jit_pt {
	long	x;
	long	y;
} t_jit_pt;

typedef struct _jit_rect {
	long	x;
	long	y;
	long	width;
	long	height;
} t_jit_rect;



#ifdef MAC_VERSION

typedef void*						t_jit_gl_native_window;			// NWWindow *
typedef CGDirectDisplayID			t_jit_gl_native_device;			// Defines a reference to a list of graphics devices.
typedef void*						t_jit_gl_native_drawable;		// NSView *
typedef void*						t_jit_gl_native_context;		// NSOpenGLContext *
typedef void*						t_jit_gl_native_pixelformat;	// NSOpenGLPixelFormat *

#else



#endif

extern t_symbol *ps_draw, *ps_get_state, *ps_matrixoutput, *ps_get_geometry, *ps_boundcalc, *ps_calcbounds;

#if C74_PRAGMA_STRUCT_PACKPUSH
#pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
#pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif
