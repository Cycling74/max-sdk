#ifndef _EXT_ASSIST_H_
#define _EXT_ASSIST_H_

#include "max_types.h"
#include "ext_prefix.h"
#include "ext_mess.h"

#define ASSIST_INLET 1
#define ASSIST_OUTLET 2

// external object assist methods should limit returned string lengths to this 
#define ASSIST_MAX_STRING_LEN 500

BEGIN_USING_C_LINKAGE

void stdinletinfo(t_object *s, void *b, long a, char *t);

END_USING_C_LINKAGE

#endif // #ifndef _EXT_ASSIST_H_
