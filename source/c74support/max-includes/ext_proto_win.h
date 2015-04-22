#ifndef __EXT_PROTO_WIN_H__
#define __EXT_PROTO_WIN_H__

BEGIN_USING_C_LINKAGE

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

#ifdef WIN_VERSION

HINSTANCE main_get_instance(void);
HWND main_get_client(void);	
HWND main_get_frame(void);
LPSTR main_get_commandline(void);
LPSTR main_get_appfilename(void);

#endif // WIN_VERSION

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

END_USING_C_LINKAGE

#endif // __EXT_PROTO_WIN_H__
