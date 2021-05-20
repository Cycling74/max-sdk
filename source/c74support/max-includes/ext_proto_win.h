#ifndef __EXT_PROTO_WIN_H__
#define __EXT_PROTO_WIN_H__

#include "ext_prefix.h"

BEGIN_USING_C_LINKAGE

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

#ifdef WIN_VERSION

HINSTANCE main_get_instance();
HWND main_get_client();	
HWND main_get_frame();
LPSTR main_get_commandline();
LPSTR main_get_appfilename();

#endif // WIN_VERSION

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

END_USING_C_LINKAGE

#endif // __EXT_PROTO_WIN_H__
