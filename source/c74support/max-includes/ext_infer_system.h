#ifndef _EXT_INFER_SYSTEM_H_
#define _EXT_INFER_SYSTEM_H_

#if !(defined(MAC_VERSION)) && !(defined(WIN_VERSION)) && !(defined(LINUX_VERSION))

// in case this isn't set let's set it up automatically
#ifdef __APPLE__
#define MAC_VERSION 1
#elif defined(_WIN32)
#define WIN_VERSION 1
#elif defined(__linux__)
#define LINUX_VERSION 1
#else
#error Unexepected build platform!
#endif

#endif

#if defined(_WIN64) || defined(__LP64__)
#define C74_X64
#endif

#if defined (__arm__) || defined (__arm64__)
#define C74_ARM 1
#else
#define C74_INTEL 1
#endif

#endif /* _EXT_INFER_SYSTEM_H_ */
