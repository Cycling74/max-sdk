/*
 *
 *		Represents a context within a container of some form (window, patcher view, etc.)
 *
 */

#ifndef JIT_GL_CONTEXT_VIEW_H
#define JIT_GL_CONTEXT_VIEW_H

#include "ext.h"
#include "ext_obex.h"
#include "jit.common.h"
#include "jit.gl.h"

/*
	The render target is the object that creates a jit_gl_context_view.  It manages its lifetime.  The 
	jit_gl_render object drawing to this destination will get a notification about destruction.  A 
	jit_gl_render object does not create a jit_gl_context_view, it only gets one via the destination 
	name.
*/


// return codes for renderer
typedef t_atom_long t_jit_gl_context_status;
#define JIT_GL_VIEW_AVAILABLE		0
#define JIT_GL_VIEW_UNAVAILABLE		1
#define JIT_GL_VIEW_ERROR			2


typedef long t_jit_gl_context_modifier;
#define JIT_GL_VIEW_COMMAND_KEY		(1<<0)
#define JIT_GL_VIEW_SHIFT_KEY		(1<<1)
#define JIT_GL_VIEW_CAPS_LOCK		(1<<2)
#define JIT_GL_VIEW_ALT_KEY			(1<<3)
#define JIT_GL_VIEW_CONTROL_KEY		(1<<4)
	
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

// attributes of t_jit_gl_context_view to cache when recreating
typedef struct _jit_gl_context_view_cache {
    long	doublebuffer;
    long	fsaa;
    long	depthbuffer;
    long	stereo;
    long	sync;
    long	shared;
    long	idlemouse;
    long	mousewheel;
    long    allow_hi_res;
} t_jit_gl_context_view_cache;

/**
 * t_jit_gl_context_view object struct.
 *
 * Manages an OpenGL context within a rectangle.  Objects that use a t_jit_gl_context_view 
 * to manage an OpenGL context should attach themselves to the object for its lifetime
 * and implement an "update" method in order to handle modifications to the 
 * t_jit_gl_context_view that may require a rebuild or further response within the embedding 
 * object.
 *
 * @ingroup gl
 * 
 */
typedef struct _jit_gl_context_view {
	t_object			ob;					///< jitter object
	long				rebuild;			///< rebuild flag
	t_jit_gl_context	context;			///< OpenGL context
	t_symbol			*shared_context;	///< shared context name
	t_wind_mouse_info	mouse_info;			///< data for mouse events
	t_wind_mousewheel_info mousewheel_info;	///< data for mouse wheel events 
	t_wind_key_info		key_info;			///< data for key events
	long				canrebuild;			///< flag for whether the context can rebuild or not
	long				doublebuffer;		///< double buffer flag
	long				depthbuffer;		///< depth buffer flag
	long				stereo;				///< active stereo flag
	t_jit_rect			frame;				///< frame of context
	long				fsaa;				///< FSAA flag
	long				sync;				///< V-sync flag
	long				shared;				///< Shader context flag
	t_hashtab			*shared_contexts;	///< Hashtab of shared context names
	long				idlemouse;			///< Idlemouse flag (events on mouse move)
	long				mousewheel;			///< mosuewheel flag (events on mouse wheel)
	void				*target;			///< target object we're controlled by
	long				targettype;			///< target type we're controlled by
	t_symbol			*name;				///< name of the view
	long				reshaping;			///< flag for breaking cycles on reshape notification
	long				ownerreshape;		///< flag for if the owner handles reshaping the context
	t_object			*patcher;			///< patcher the context view is in (if there is one)
	long				freeing;			///< in the process of freeing flag
	long				creating;			///< in the process of creating flag
	float				scalefactor;		///< scaling factor when drawing to retina display
	long				allow_hi_res;		///< allows for high resolution drawing when available
} t_jit_gl_context_view;


long jit_gl_context_view_are_shared(t_symbol *ctx1, t_symbol *ctx2);
void jit_gl_context_view_funall(method fun, void *arg);


t_jit_err jit_gl_context_view_init(void);
t_jit_gl_context_view * jit_gl_context_view_new();
void jit_gl_context_view_free(t_jit_gl_context_view *x);

// internal methods (these exist but aren't available in the header)
// t_jit_gl_context_status jit_gl_context_view_create(t_jit_gl_context_view *x);

// render destination interface
long jit_gl_context_view_is_available(t_jit_gl_context_view *x);
t_jit_err jit_gl_context_view_rebuild(t_jit_gl_context_view *x);
t_jit_err jit_gl_context_view_register_jpatcher(t_jit_gl_context_view *x);
t_jit_err jit_gl_context_view_destroy(t_jit_gl_context_view *x);
t_jit_err jit_gl_context_view_update(t_jit_gl_context_view *x);
t_jit_err jit_gl_context_view_clear(t_jit_gl_context_view *x);
t_jit_err jit_gl_context_view_attach(t_jit_gl_context_view *x, void *target);
t_jit_err jit_gl_context_view_detach(t_jit_gl_context_view *x);
t_jit_err jit_gl_context_view_reshape(t_jit_gl_context_view *x);
t_jit_err jit_gl_context_view_set_viewport(t_jit_gl_context_view *x, t_jit_rect rect);
t_jit_err jit_gl_context_view_set_frame(t_jit_gl_context_view *x, t_jit_rect *rect);
t_jit_err jit_gl_context_view_get_frame(t_jit_gl_context_view *x, t_jit_rect *rect);
t_jit_gl_context jit_gl_context_view_getcontext(t_jit_gl_context_view *x);
void * jit_gl_context_view_gettarget(t_jit_gl_context_view *x);
void jit_gl_context_view_handle_key_event(t_jit_gl_context_view *x, t_symbol *s, long keydown, long keycode, long textcharacter, t_jit_gl_context_modifier modifiers);
t_jit_err  jit_gl_context_view_get_key_info(t_jit_gl_context_view *x, t_wind_key_info **kinfo);
void jit_gl_context_view_handle_mouse_event(t_jit_gl_context_view *x, t_symbol *s, long mousedown, t_jit_pt pt, t_jit_gl_context_modifier modifiers);
void jit_gl_context_view_handle_mousewheel_event(t_jit_gl_context_view *x, t_symbol *s, long mousedown, t_jit_pt pt, t_jit_gl_context_modifier modifiers, double dx, double dy);
t_jit_err  jit_gl_context_view_get_mouse_info(t_jit_gl_context_view *x, t_wind_mouse_info **minfo);
t_jit_err jit_gl_context_view_get_mousewheel_info(t_jit_gl_context_view *x, t_wind_mousewheel_info **minfo);
void jit_gl_context_view_notify(t_jit_gl_context_view *x, t_symbol *sender_name, t_symbol *msg, void *p_sender);
t_jit_err jit_gl_context_view_disable_shared_context(t_jit_gl_context_view *x);
t_jit_err jit_gl_context_view_setname(t_jit_gl_context_view *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_context_view_setflag(t_jit_gl_context_view *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_context_view_setshared_context(t_jit_gl_context_view *x, void *attr, long argc, t_atom *argv);
t_jit_err jit_gl_context_view_calcpickray(t_jit_gl_context_view *x, long px, long py, float *ray);

// common to render destination and renderer interface
t_jit_gl_context_status jit_gl_context_view_make_current(t_jit_gl_context_view *x);

// renderer interface
t_jit_gl_context_status jit_gl_context_view_swap(t_jit_gl_context_view *x);

// inspection interface
t_jit_err jit_gl_context_view_describe(t_jit_gl_context_view *x, t_dictionary *d);

#endif
