// ext_typelist.h copyright 2019 cycling '74 all rights reserved

#ifndef __EXT_TYPELIST_H__
#define __EXT_TYPELIST_H__

#include "ext_prefix.h"
#include "max_types.h"

BEGIN_USING_C_LINKAGE

void typelist_make(t_fourcc *types, long include, short *numtypes);

END_USING_C_LINKAGE

#endif // #ifndef __EXT_TYPELIST_H__
