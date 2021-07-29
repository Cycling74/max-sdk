/*
 *  ext_parameter.h
 *
 *  Copyright 2008 Cycling '74. All rights reserved.
 *
 */

#ifndef _EXT_PARAMETER_H_
#define _EXT_PARAMETER_H_

#include "ext_prefix.h"
#include "ext_mess.h"
#include "ext_dictionary.h"
#include "jpatcher_api.h"

BEGIN_USING_C_LINKAGE

enum t_parameter_method_flag {
	PARAMETER_METHOD_FLAG_OVERRIDE 	= 0,			// default is to override normal method with standard method
	PARAMETER_METHOD_FLAG_PRE 		= (1L << 0L),	// user-defined pre-processing function for standard method
	PARAMETER_METHOD_FLAG_POST		= (1L << 1L),	// user-defined post-processing function for standard method
	PARAMETER_METHOD_FLAG_FULL		= (1L << 2L),	// user-defined override method
	PARAMETER_METHOD_FLAG_DONOTHING	= (1L << 15L),	// don't override at all
};

enum t_parameter_color_flag {
	PARAMETER_COLOR_FLAG_DEFAULT	= 0,
	PARAMETER_COLOR_FLAG_STYLE		= (1L << 0L)	// use style system for color rather than defaults system
};

enum {
	PARAMETER_GESTURE_INDEX = 999999
};

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
	PARAM_FLAGS_NONE = 0,
	PARAM_FLAGS_FORCE_TYPE = 0x1,
} PARAM_FLAGS;

typedef enum {
	PARAM_TYPE_ENABLE_OFF,	// parameter type menu not available in the inspector
	PARAM_TYPE_ENABLE_ON,	// enables basic parameter types Int, Float, Enum in the parameter type menu
	PARAM_TYPE_ENABLE_BLOB,	// and additionally Blob
	PARAM_TYPE_ENABLE_BLOB_ONLY,
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
	PARAM_DATA_TYPE_MAPPING_INDEX, // deprecated, do not use
	PARAM_DATA_TYPE_NOBLOBCACHE,
	PARAM_DATA_TYPE_RANGE,
	PARAM_DATA_TYPE_REALVAL,
	PARAM_DATA_TYPE_DISTANCEVAL,
	PARAM_DATA_TYPE_LINEARVAL,
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
	t_symbol			*classname;
	t_symbol			*attrname;
	t_symbol			*colorname;
	long				flags;
} t_param_class_defcolor_data;

enum {
	PARAM_VALUECHANGED_UNDEFINED	= 0x00,
	PARAM_VALUECHANGED_VISIBLE		= 0x01
};

enum {
	PARAM_VISIBILITY_VISIBLE = 0,
	PARAM_VISIBILITY_STOREONLY, // no automation, only store (in blob)
	PARAM_VISIBILITY_HIDDEN
};

// call in main function
t_max_err class_parameter_init(t_class *c);
// call in new function
t_max_err object_parameter_init(t_object *x, PARAM_TYPE type);
// call in new function
t_max_err object_parameter_init_flags(t_object *x, PARAM_TYPE type, PARAM_FLAGS flags);
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
t_max_err class_parameter_register_default_color_flags(t_class *c, t_symbol *attrname, t_symbol *colorname, long flags);

t_bool object_parameter_is_initialized(t_object *x);
t_bool object_parameter_is_in_Live(t_object *x);
t_bool object_parameter_is_in_maxtilde(t_object *x);
t_bool object_parameter_is_automated(t_object *x);
t_max_err object_parameter_wants_focus(t_object *x);
t_bool object_parameter_is_parameter(t_object *x);
t_atom_long object_parameter_get_order(t_object *x);

typedef enum {
	PARAMETER_ENABLE_SAVESTATE_UNSAVED = -1,
	PARAMETER_ENABLE_SAVESTATE_OFF = 0,
	PARAMETER_ENABLE_SAVESTATE_ON
} PARAMETER_ENABLE_SAVESTATE;

PARAMETER_ENABLE_SAVESTATE object_parameter_getenable_savestate(t_object *x);

enum {
	PARAMETER_MAPPABLE_CONFIG_FLAGS_NONE = 0,
	PARAMETER_MAPPABLE_CONFIG_FLAGS_TOGGLE_ZEROONE	= 0x01,	// this object is a toggle with values 0 and 1 (will be locked to enum)
	PARAMETER_MAPPABLE_CONFIG_FLAGS_TOGGLE_OFFON 	= 0x02,	// this object is a toggle with values off and on (will be locked to enum)
	PARAMETER_MAPPABLE_CONFIG_FLAGS_ENUM			= 0x03,	// this object is an enum and will require an override to specify the range
	PARAMETER_MAPPABLE_CONFIG_FLAGS_INT_MIDI		= 0x04, // this object is an int (0 - 127)
	PARAMETER_MAPPABLE_CONFIG_FLAGS_INT_FULL		= 0x05, // this object is an int (0 - 255)
	PARAMETER_MAPPABLE_CONFIG_FLAGS_INT				= 0x06, // this object is an int and will require an override to specify the range

	PARAMETER_MAPPABLE_CONFIG_FLAGS_WANTSOVERRIDE	= 0x10	// this object uses a known pattern ('min'/'max' or 'size'), the kernel should autogenerate overrides
};

enum {
	PARAMETER_MAPPABLE_CONFIG_NOOVERRIDE = 0,
	PARAMETER_MAPPABLE_CONFIG_OVERRIDE_MINMAX, // the object already has individual attributes for min/max
	PARAMETER_MAPPABLE_CONFIG_OVERRIDE_SIZE, // the object already has an individual size attribute (min = 0, max = size - 1)
	PARAMETER_MAPPABLE_CONFIG_OVERRIDE_OBJ // object will implement minmax getter/setter methods if necessary
};

typedef t_bool (*t_hasminmax_getmethod)(void *);
typedef t_max_err (*t_hasminmax_setmethod)(void *, t_bool);

typedef t_max_err (*t_minmax_getmethod)(void *, double *, double *);
typedef t_max_err (*t_minmax_setmethod)(void *, double, double);

typedef t_max_err (*t_enum_getmethod)(void *, long *, t_atom **);
typedef t_max_err (*t_enum_setmethod)(void *, long, t_atom *);

typedef struct _parameter_mappable_override_minmax {
	t_symbol *minimum;
	t_symbol *maximum;
	t_bool readonly; // do not allow the parameter to change the min/max
} t_parameter_mappable_override_minmax;

typedef struct _parameter_mappable_override_size {
	t_symbol *size;
	t_bool readonly; // do not allow the parameter to change the size
} t_parameter_mappable_override_size;

typedef struct _parameter_mappable_override_obj {
	t_minmax_getmethod getmethod;
	t_minmax_setmethod setmethod;
	t_symbol *watchattr; // when this attr changes, we need to pull the new range
} t_parameter_mappable_override_obj;

typedef union _parameter_mappable_override {
	t_parameter_mappable_override_minmax minmax;
	t_parameter_mappable_override_size size;
	t_parameter_mappable_override_obj obj;
} t_parameter_mappable_override;

typedef struct _parameter_mappable_hasminmax {
	t_hasminmax_getmethod getmethod;
	t_hasminmax_setmethod setmethod;
} t_parameter_mappable_hasminmax;

typedef struct _parameter_mappable_enum {
	t_enum_getmethod getmethod;
	t_enum_setmethod setmethod;
} t_parameter_mappable_enum;

typedef struct _parameter_mappable_config {
	long 							flags;
	long							override_type;
	t_parameter_mappable_override	override_value;
	t_parameter_mappable_hasminmax	hasminmax;
	t_parameter_mappable_enum		enuminfo;
} t_parameter_mappable_config;

t_bool object_parameter_hasminmax_false(void *x);
t_bool object_parameter_hasminmax_true(void *x);

void class_parameter_mappable(t_class *c, t_parameter_mappable_config *config);
t_max_err class_parameter_setinfo(t_class *c, PARAM_DATA_TYPE type, long ac, t_atom *av);
t_max_err class_parameter_getinfo(t_class *c, PARAM_DATA_TYPE type, long *ac, t_atom **av);

END_USING_C_LINKAGE

#endif //_EXT_PARAMETER_H_
