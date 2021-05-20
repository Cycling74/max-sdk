//
//  ext_dynamiccolor.h
//  max4
//
//  Created by Jeremy Bernstein on 19.10.19.
//

#ifndef ext_dynamiccolor_h
#define ext_dynamiccolor_h

#include "jgraphics.h"

BEGIN_USING_C_LINKAGE

t_bool object_attr_dynamiccolor_supported(t_object *x, t_symbol *attrname);
t_bool object_attr_dynamiccolor_setsym_setup(t_object *x, t_symbol *attrname, long ac, t_atom *av);

// Note: object_attr_dynamiccolor_apply needs to be called after setters to make the final color available in the base attribute
t_symbol *object_attr_dynamiccolor_getname(t_object *x, t_symbol *attrname);
t_max_err object_attr_dynamiccolor_setname(t_object *x, t_symbol *attrname, t_symbol *colorname);
t_bool object_attr_dynamiccolor_geton(t_object *x, t_symbol *attrname);
t_max_err object_attr_dynamiccolor_seton(t_object *x, t_symbol *attrname, t_bool on);
t_max_err object_attr_dynamiccolor_getregular(t_object *x, t_symbol *attrname, long *argc, t_atom **argv);
t_max_err object_attr_dynamiccolor_setregular(t_object *x, t_symbol *attrname, long argc, t_atom *argv);
t_jrgba object_attr_dynamiccolor_getregularrgba(t_object *x, t_symbol *attrname);
t_max_err object_attr_dynamiccolor_setregularrgba(t_object *x, t_symbol *attrname, t_jrgba *color);

t_symbol *object_attr_dynamiccolor_gethumanname(t_object *x, t_symbol *attrname);

t_jpopupmenu *dynamiccolor_getmenu(t_object *context, t_symbol *current, long mask, long *selecteditem, long *headercount, t_bool filtered);
void dynamiccolor_handlemenu(t_object *context, long itemindex, t_symbol **current, t_bool filtered);

void object_attr_dynamiccolor_apply(t_object *x, t_symbol *attrname);

typedef enum {
	DYNAMICCOLOR_FLAGS_NONE = 0x0000,
	DYNAMICCOLOR_FLAGS_LIVE = 0x0001 // should only be linked in a Live context
} t_dynamiccolor_flags;

t_max_err class_attr_dynamiccolor_init(t_class *c, t_symbol *name, t_dynamiccolor_flags flags);

// Adds an attr_attr to this attribute that is not saved to disk but only used to hold the default dynamic color name and to check if this attribute has dynamic color enabled.
#define CLASS_ATTR_DYNAMICCOLOR_FLAGS(c, name, flags, semflags, color_parsestring) \
	class_attr_addattr_parse(c, name, "dynamiccolor_default", gensym("symbol"), flags, color_parsestring); \
	class_attr_dynamiccolor_init(c, gensym(name), semflags);

#define CLASS_ATTR_DYNAMICCOLOR(c, name, flags, color_parsestring) \
	CLASS_ATTR_DYNAMICCOLOR_FLAGS(c, name, flags, DYNAMICCOLOR_FLAGS_NONE, color_parsestring);

END_USING_C_LINKAGE

#endif /* ext_dynamiccolor_h */

