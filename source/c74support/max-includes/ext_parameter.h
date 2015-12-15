/*
 *  ext_parameter.h
 *
 *  Copyright 2008 Cycling '74. All rights reserved.
 *
 */

#ifndef _EXT_PARAMETER_H_
#define _EXT_PARAMETER_H_


BEGIN_USING_C_LINKAGE

#define PARAMETER_METHOD_FLAG_OVERRIDE    (0L) // default is to override normal method with standard method
#define PARAMETER_METHOD_FLAG_PRE         (1L << 0L) // user-defined pre-processing function for standard method
#define PARAMETER_METHOD_FLAG_POST        (1L << 1L) // user-defined post-processing function for standard method
#define PARAMETER_METHOD_FLAG_FULL        (1L << 2L) // user-defined override method
#define PARAMETER_METHOD_FLAG_DONOTHING   (1L << 15L) // don't override at all

#define PARAMETER_GESTURE_INDEX			  999999

typedef enum {
	PARAM_TYPE_INVALID = -1,
	// these parameter types can be automated
	PARAM_TYPE_FLOAT = 0,
	PARAM_TYPE_INT,
	PARAM_TYPE_ENUM,
	
	///////////////////////////////////////////////////////
	// these parameter types cannot be automated, not are they known to anyone but Max
	PARAM_TYPE_BLOB,	// generic atom type, can be stored, but doesn't use 
						// any other parameter features at this time (order excepted)

	PARAM_TYPE_FILE
} PARAM_TYPE;

typedef enum {
	PARAM_TYPE_ENABLE_OFF,	// parameter type menu not available in the inspector
	PARAM_TYPE_ENABLE_ON,	// enables basic parameter types Int, Float, Enum in the parameter type menu
	PARAM_TYPE_ENABLE_BLOB,	// and additionally Blob
} PARAM_TYPE_ENABLE;

typedef enum {
	PARAM_UNITSTYLE_INVALID = -1,
	PARAM_UNITSTYLE_INT,
	PARAM_UNITSTYLE_FLOAT,
	PARAM_UNITSTYLE_MS,
	PARAM_UNITSTYLE_HZ,
	PARAM_UNITSTYLE_DB,
	PARAM_UNITSTYLE_PERCENT,
	PARAM_UNITSTYLE_PAN,
	PARAM_UNITSTYLE_SEMITONE,
	PARAM_UNITSTYLE_MIDINOTE,
	PARAM_UNITSTYLE_CUSTOM, // what does this do?
	PARAM_UNITSTYLE_NATIVE, // use the type of the parameter to determine style
} PARAM_UNITSTYLE;

typedef enum {
	PARAM_MOD_INVALID = -1,
	PARAM_MOD_NONE,
	PARAM_MOD_UNI,
	PARAM_MOD_BI,
	PARAM_MOD_ADD,
	PARAM_MOD_ABS
} PARAM_MOD;

typedef enum {
	PARAM_DATA_TYPE_INVALID = -1,
	PARAM_DATA_TYPE_VALUE,
	PARAM_DATA_TYPE_TYPE,
	PARAM_DATA_TYPE_TYPE_ENABLE,
	PARAM_DATA_TYPE_ORDER,
	PARAM_DATA_TYPE_LONGNAME,
	PARAM_DATA_TYPE_SHORTNAME,
	PARAM_DATA_TYPE_MIN,
	PARAM_DATA_TYPE_MAX,
	PARAM_DATA_TYPE_ENUM,
	PARAM_DATA_TYPE_MODMODE,
	PARAM_DATA_TYPE_MODMIN,
	PARAM_DATA_TYPE_MODMAX,
	PARAM_DATA_TYPE_INITIAL_ENABLE,
	PARAM_DATA_TYPE_INITIAL,
	PARAM_DATA_TYPE_INITIAL_EDITABLE,
	PARAM_DATA_TYPE_UNITSTYLE,
	PARAM_DATA_TYPE_EXPONENT,
	PARAM_DATA_TYPE_STEPS,
	PARAM_DATA_TYPE_SPEEDLIM,
	PARAM_DATA_TYPE_SMOOTHING, // unimplemented
	PARAM_DATA_TYPE_UNITS,
	PARAM_DATA_TYPE_INFO,
	PARAM_DATA_TYPE_FOCUS, // read-only. use object_parameter_wants_focus() to set focus
	PARAM_DATA_TYPE_INVISIBLE,
	PARAM_DATA_TYPE_AUTOMATION_VALUE,
	PARAM_DATA_TYPE_AUTOMATION_STATE,
	PARAM_DATA_TYPE_MODULATION_VALUE,
	PARAM_DATA_TYPE_DIRTY,
	PARAM_DATA_TYPE_ASSIGNMENT_TEXT_MIDI,
	PARAM_DATA_TYPE_ASSIGNMENT_TEXT_KEY,
	PARAM_DATA_TYPE_ASSIGNMENT_TEXT_MACRO,
	PARAM_DATA_TYPE_LEARNING_MODE,
	PARAM_DATA_TYPE_FILEREF_PATH,
	PARAM_DATA_TYPE_FILEREF_DISPLAYPATH,
	PARAM_DATA_TYPE_FILEREF_DISPLAYNAME,
	PARAM_DATA_TYPE_DEVICESTATE, // read-only
	PARAM_DATA_TYPE_DEFER,
	PARAM_DATA_TYPE_MAPPING_INDEX,
	PARAM_DATA_TYPE_NOBLOBCACHE,
} PARAM_DATA_TYPE;

typedef enum {
	PARAM_VALUE_SET_DISTANCE = 0,
	PARAM_VALUE_SET_REAL,
	PARAM_VALUE_SET_GETONLY,
	PARAM_VALUE_SET_DISTANCE_NONOTIFY,
	PARAM_VALUE_SET_REAL_NONOTIFY
} PARAM_VALUE_SET_TYPE;

typedef enum {
	PARAM_VALUE_GET_OUTPUT = 0,
	PARAM_VALUE_GET_AUTOMATION,
	PARAM_VALUE_GET_MODULATION
} PARAM_VALUE_GET_TYPE;

typedef enum {
	PARAM_VALUE_DISTANCE = 0,
	PARAM_VALUE_LINEAR,
	PARAM_VALUE_REAL
} PARAM_VALUE_FORMAT;

typedef enum {
	PARAM_AUTOMATION_STATE_NONE			= 0x00,
	PARAM_AUTOMATION_STATE_AUTOMATED	= 0x01,
	PARAM_AUTOMATION_STATE_AUTOENABLED	= 0x02,
	PARAM_AUTOMATION_STATE_IRRELEVANT	= 0x04,
	PARAM_AUTOMATION_STATE_DISABLED		= 0x08,
	PARAM_AUTOMATION_STATE_MACRO		= 0x10
} PARAM_AUTOMATION_STATE;

typedef enum {
	PARAM_DEVICESTATE_ACTIVE			= 0,
	PARAM_DEVICESTATE_INACTIVE			= 1
} PARAM_DEVICESTATE;

typedef enum {
	PARAM_LEARNING_TYPE_NONE = 0,
	PARAM_LEARNING_TYPE_MIDI,
	PARAM_LEARNING_TYPE_KEY,
	PARAM_LEARNING_TYPE_MACRO
} PARAM_LEARNING_TYPE;

typedef struct _parameter_notify_data {
	PARAM_DATA_TYPE		 type;
	long				 ac;
	t_atom				*av;
} t_parameter_notify_data;

typedef struct _param_class_defcolor_data {
	t_class				*c;
	t_symbol			*attrname;
	t_symbol			*colorname;
} t_param_class_defcolor_data;

// call in main function
t_max_err class_parameter_init(t_class *c);
// call in new function
t_max_err object_parameter_init(t_object *x, PARAM_TYPE type);
// call at end of new function, passing in object dictionary
t_max_err object_parameter_dictionary_process(t_object *x, t_dictionary *d);
// call in free function
t_max_err object_parameter_free(t_object *x);
// call in notify function, return value of TRUE means the notification was param data, in the pnd struct
t_bool object_parameter_notify(t_object *x, t_symbol *s, t_symbol *msg, void *sender, void *data, t_parameter_notify_data *pnd);
// get the value of a particular parameter datum
t_max_err object_parameter_getinfo(t_object *x, PARAM_DATA_TYPE type, long *ac, t_atom **av);
// set the value of a particular parameter datum
t_max_err object_parameter_setinfo(t_object *x, PARAM_DATA_TYPE type, long ac, t_atom *av);
// get the display string for a particular value
t_max_err object_parameter_string_get(t_object *x, double val, char **outstr);
// convert the string according to parameter type and unit to a value
t_max_err object_parameter_stringtovalue(t_object *x, double *value, char *str);
// set object value, returns clipped/stepped value
t_max_err object_parameter_value_set(t_object *x, PARAM_VALUE_SET_TYPE how, double *linear, double *real, char blobnotify);
// get the specified value, in the specified format
t_max_err object_parameter_value_get(t_object *x, PARAM_VALUE_GET_TYPE how, PARAM_VALUE_FORMAT what, double *value);
// set the initial value from the current value
t_max_err object_parameter_current_to_initial(t_object *x);
// get RGB color (0.-1.) based on one of the color symbols, listed below
t_max_err object_parameter_color_get(t_object *x, t_symbol *s, t_jrgba *jrgba);

// set object value using atoms, most useful for blob or file types
t_max_err object_parameter_value_setvalueof(t_object *x, long ac, t_atom *av, char blobnotify);
t_max_err object_parameter_value_setvalueof_nonotify(t_object *x, long ac, t_atom *av, char blobnotify);
// get object value using atoms, most useful for blob or file types
t_max_err object_parameter_value_getvalueof(t_object *x, long *ac, t_atom **av);
//
t_max_err object_parameter_value_changed(t_object *x, char blobnotify);
t_max_err object_parameter_value_changed_nonotify(t_object *x, char blobnotify);

t_max_err class_parameter_addmethod(t_class *c, method m, char *name, long flags, ...);

t_max_err parameter_default_int(t_object *x, long n);
t_max_err parameter_default_float(t_object *x, double d);
t_max_err parameter_default_anything(t_object *x, t_symbol *s, long ac, t_atom *av);

t_max_err class_parameter_register_default_color(t_class *c, t_symbol *attrname, t_symbol *colorname);

t_bool object_parameter_is_initialized(t_object *x);
t_bool object_parameter_is_in_Live(t_object *x);
t_bool object_parameter_is_in_maxtilde(t_object *x);
t_bool object_parameter_is_automated(t_object *x);
t_max_err object_parameter_wants_focus(t_object *x);
t_bool object_parameter_is_parameter(t_object *x);
t_atom_long object_parameter_get_order(t_object *x);


// available colors
#define ps_surface_bg			gensym("surface_bg")
#define ps_control_bg			gensym("control_bg")
#define ps_control_text_bg		gensym("control_text_bg")
#define ps_control_fg			gensym("control_fg")
#define ps_control_fg_on		gensym("control_fg_on")
#define ps_control_fg_off		gensym("control_fg_off")
#define ps_control_selection	gensym("control_selection")
#define ps_control_zombie		gensym("control_zombie")
#define ps_value_arc			gensym("value_arc")
#define ps_value_bar			gensym("value_bar")
#define ps_active_automation	gensym("active_automation")
#define ps_inactive_automation	gensym("inactive_automation")
#define ps_macro_assigned		gensym("macro_assigned")
#define ps_contrast_frame		gensym("contrast_frame")
#define ps_key_assignment		gensym("key_assignment")
#define ps_midi_assignment		gensym("midi_assignment")
#define ps_macro_assignment		gensym("macro_assignment")
#define ps_assignment_text_bg	gensym("assignment_text_bg")
#define ps_control_fg_zombie	gensym("control_fg_zombie")
#define ps_value_arc_zombie		gensym("value_arc_zombie")
#define ps_numbox_triangle		gensym("numbox_triangle")
#define ps_macro_title			gensym("macro_title")
#define ps_selection			gensym("selection")
#define ps_led_bg				gensym("led_bg")

#define PARAM_COLOR_SURFACE_BG				"0.552941 0.552941 0.552941 1."
#define PARAM_COLOR_CONTROL_BG				"0.6 0.6 0.6 1."
#define PARAM_COLOR_CONTROL_TEXT_BG			"0.74902 0.74902 0.74902 1."
#define PARAM_COLOR_CONTROL_FG				"0. 0.019608 0.078431 1."
#define PARAM_COLOR_CONTROL_FG_ON			"0. 0. 0. 1."
#define PARAM_COLOR_CONTROL_FG_OFF			"0. 0. 0. 1."
#define PARAM_COLOR_CONTROL_SELECTION		"1. 0.788235 0.027451 1."
#define PARAM_COLOR_CONTROL_ZOMBIE			"0.490196 0.482353 0.478431 1."
#define PARAM_COLOR_VALUE_ARC				"0.94902 0.376471 0. 1."
#define PARAM_COLOR_VALUE_BAR				"0.94902 0.376471 0. 1."
#define PARAM_COLOR_ACTIVE_AUTOMATION		"1. 0.070588 0. 1."
#define PARAM_COLOR_INACTIVE_AUTOMATION		"0.329412 0.329412 0.329412 1."
#define PARAM_COLOR_MACRO_ASSIGNED			"0. 0.854902 0.282353 1."
#define PARAM_COLOR_CONTRAST_FRAME			"0.196078 0.196078 0.196078 1."
#define PARAM_COLOR_KEY_ASSIGNMENT			"1. 0.392157 0. 1."
#define PARAM_COLOR_MIDI_ASSIGNMENT			"0.25098 0.203922 0.937255 1."
#define PARAM_COLOR_MACRO_ASSIGNMENT		"0. 0.854902 0.282353 1."
#define PARAM_COLOR_ASSIGNMENT_TEXT_BG		"0.709804 0.698039 0.694118 1."
#define PARAM_COLOR_CONTROL_FG_ZOMBIE		"0.321569 0.321569 0.321569 1."
#define PARAM_COLOR_VALUE_ARC_ZOMBIE		"0.752941 0.784314 0.839216 1."
#define PARAM_COLOR_NUMBOX_TRIANGLE			"1. 0.380392 0. 1."
#define PARAM_COLOR_MACRO_TITLE				"0.709804 0.698039 0.694118 1."
#define PARAM_COLOR_SELECTION				"0.498039 1. 1. 1."
#define PARAM_COLOR_LED_BG					"0.4 0.4 0.4 1."

#define PARAM_COLOR_COUNT 24

END_USING_C_LINKAGE

#endif //_EXT_PARAMETER_H_