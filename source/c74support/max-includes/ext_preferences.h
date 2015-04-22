#ifndef _EXT_PREFERENCES_H_
#define _EXT_PREFERENCES_H_

BEGIN_USING_C_LINKAGE

t_max_err preferences_getatomforkey(t_symbol *key, t_atom *value);
t_symbol *preferences_getsym(C74_CONST char *name);
void preferences_setsym(C74_CONST char *name, t_symbol *value);
long preferences_getlong(C74_CONST char *name);
void preferences_setlong(C74_CONST char *name, long value);
long preferences_getchar(C74_CONST char *name);
void preferences_setchar(C74_CONST char *name, long value);
t_max_err preferences_getatoms(C74_CONST char *name, long *argc, t_atom **argv);
t_max_err preferences_setatoms(C74_CONST char *name, long argc, t_atom *argv);
void *preferences_define(C74_CONST char *name, C74_CONST char *type, C74_CONST char *label, C74_CONST char *style, C74_CONST char *category, long attrflags, method get, method set, long flags);
void *preferences_class_define(t_class *c, C74_CONST char *name, C74_CONST char *type, C74_CONST char *label, C74_CONST char *style, C74_CONST char *category, long attrflags, method get, method set, long flags);
void *preferences_defineoption(C74_CONST char *name, C74_CONST char *label, C74_CONST char *category, char *ptr, method notify, long flags);
void *preferences_class_defineoption(t_class *c, C74_CONST char *name, C74_CONST char *label, C74_CONST char *category, char *ptr, method notify, long flags);
t_max_err preferences_writedictionary(C74_CONST t_dictionary *d, C74_CONST char *filename);
t_max_err preferences_readdictionary(C74_CONST char *filename, t_dictionary **d);
t_dictionary *simpleprefs_dictionary();

END_USING_C_LINKAGE

enum {
	PREFERENCES_FLAGS_INVISIBLE = 1,
	PREFERENCES_FLAGS_DONTSAVE = 2
};


#endif // _EXT_PREFERENCES_H_
