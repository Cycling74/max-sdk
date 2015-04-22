#ifndef _JIT_AGL_H_
#define _JIT_AGL_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MAC_VERSION

#ifdef JIT_GL_AGL
OSStatus aglInitEntryPoints (void);
void aglDellocEntryPoints (void);
void * aglGetProcAddress (char * pszProc);
void nsglSetRect(void);
#endif

#ifdef JIT_GL_NSGL
void * nsglGetProcAddress (const char *pszProc);
void nsglSetRect(void *context, GLint *val);
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif
