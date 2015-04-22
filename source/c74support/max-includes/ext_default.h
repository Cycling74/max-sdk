#ifndef __EXT_DEFAULT_H__
#define __EXT_DEFAULT_H__

#define DEFAULT_GLOBAL (void *)-1L		// this will be changed to NULL once hashtab supports it

#ifdef __cplusplus
extern "C" {
#endif

t_max_err patcher_setdefault(t_object *patcher, t_symbol *key, long argc, t_atom *argv);
t_max_err patcher_getdefault(t_object *patcher, t_symbol *key, long *argc, t_atom *argv);
t_max_err patcher_removedefault(t_object *patcher, t_symbol *key);

#ifdef __cplusplus
}
#endif

#endif // __EXT_DEFAULT_H__
