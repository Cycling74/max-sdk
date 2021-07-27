#pragma once

#include <stdio.h>
#include <cwchar>
#include <cmath>
#include <cstring>
#include <memory>

// include this outside of the namespace, and
// before any Max headers can include ext_prefix.h
#include "ext_prefix_includes.h"

namespace c74 {
namespace max {

#define calcoffset(x,y) ((c74::max::t_ptr_int)(&(((x *)0L)->y)))

#include "max-includes/ext.h"
#include "max-includes/ext_dictobj.h"
#include "max-includes/ext_time.h"
#include "max-includes/commonsyms.h"
#include "max-includes/jgraphics.h"
#include "max-includes/ext_parameter.h"
#include "max-includes/ext_boxstyle.h"

#undef min
#undef max

}
}

// necessary to redefine this outside of the namespace
BEGIN_USING_C_LINKAGE
/**	ext_main() is the entry point for an extern to be loaded, which all externs must implement
	this shared/common prototype ensures that it will be exported correctly on all platforms.

	@ingroup	class
	@param		r	Pointer to resources for the external, if applicable.
	@see		@ref chapter_anatomy
	@version Introduced in Max 6.1.9
*/
void C74_EXPORT ext_main(void *r);
END_USING_C_LINKAGE
