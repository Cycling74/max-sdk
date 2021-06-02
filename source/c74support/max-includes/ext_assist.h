#ifndef _EXT_ASSIST_H_
#define _EXT_ASSIST_H_

#include "max_types.h"
#include "ext_prefix.h"
#include "ext_mess.h"

enum t_assist_function {
	ASSIST_INLET = 1,
	ASSIST_OUTLET
};

enum {
	// external object assist methods should limit returned string lengths to this
	ASSIST_MAX_STRING_LEN = 500
};

BEGIN_USING_C_LINKAGE

void stdinletinfo(t_object *s, void *b, long a, char *t);

END_USING_C_LINKAGE

#endif // #ifndef _EXT_ASSIST_H_
