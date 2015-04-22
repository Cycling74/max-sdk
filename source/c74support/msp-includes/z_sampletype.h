// z_sampletype.h -- defines t_sample and friends copyright 1997-2010 Cycling '74

#ifndef _Z_SAMPLETYPE_H
#define _Z_SAMPLETYPE_H

#ifndef MSP64
// tap -- set to build 64-bit audio chains
#define MSP64 1
#endif

/**	A float -- always a 32 bit floating point number.		@ingroup msp	*/
typedef float t_float;

/**	A double -- always a 64 bit floating point number.		@ingroup msp	*/
typedef double t_double;

/**	A sample value -- width determined by MSP version.		@ingroup msp	*/
#if MSP64
typedef double t_sample; 
#else
typedef float t_sample;
#endif

// macro loop for checking for NAN/INF

// note: this may be platform-dependent

#define NAN_MASK 0x7F800000

#define NAN_CHECK(n,o) \
while (n--) { if ((*(o) & NAN_MASK) == NAN_MASK) *(o) = 0; (o)++; } // now post inc/dec -Rd jun 05

#define IS_DENORM_FLOAT(v)		((((*(t_uint32 *)&(v))&0x7f800000)==0)&&((v)!=0.f))
#define IS_DENORM_DOUBLE(v)		((((((t_uint32 *)&(v))[1])&0x7fe00000)==0)&&((v)!=0.))			

#define IS_NAN_FLOAT(v)			(((*(t_uint32 *)&(v))&0x7f800000)==0x7f800000)
#define IS_NAN_DOUBLE(v)		(((((t_uint32 *)&(v))[1])&0x7fe00000)==0x7fe00000) 

#define IS_DENORM_NAN_FLOAT(v)		(IS_DENORM_FLOAT(v)||IS_NAN_FLOAT(v))
#define IS_DENORM_NAN_DOUBLE(v)		(IS_DENORM_DOUBLE(v)||IS_NAN_DOUBLE(v))			

// currently all little endian processors are x86
// an external could #define DENORM_WANT_FIX to disable or enable denorm checks
// but now we disable them all by default 
#ifndef DENORM_WANT_FIX
#if 0 
// || defined(WIN_VERSION)	// no longer fixing denormals on Win.  Instead using SSE processor flags. 
// || (defined(MAC_VERSION)&&TARGET_RT_LITTLE_ENDIAN) // no longer fixing denormals on Mac. Instead using SSE processor flags.
// user can #define DENORM_WANT_FIX to 0 to disable
#define DENORM_WANT_FIX		1
#endif
#endif  // #ifndef DENORM_WANT_FIX

#if DENORM_WANT_FIX

#define FIX_DENORM_FLOAT(v)		((v)=IS_DENORM_FLOAT(v)?0.f:(v))
#define FIX_DENORM_DOUBLE(v)	((v)=IS_DENORM_DOUBLE(v)?0.f:(v))

#define FIX_DENORM_NAN_FLOAT(v)		((v)=IS_DENORM_NAN_FLOAT(v)?0.f:(v))
#define FIX_DENORM_NAN_DOUBLE(v)	((v)=IS_DENORM_NAN_DOUBLE(v)?0.:(v))

#else

#define FIX_DENORM_FLOAT(v)		
#define FIX_DENORM_DOUBLE(v)	

#define FIX_DENORM_NAN_FLOAT(v)		((v)=IS_NAN_FLOAT(v)?0.0:(v))
#define FIX_DENORM_NAN_DOUBLE(v)	((v)=IS_NAN_DOUBLE(v)?0.0:(v))

#endif  // #ifdef DENORM_WANT_FIX

#if MSP64
#define IS_DENORM_SAMPLE(v)			IS_DENORM_DOUBLE(v)
#define IS_NAN_SAMPLE(v)			IS_NAN_DOUBLE(v)
#define IS_DENORM_NAN_SAMPLE(v)		IS_DENORM_NAN_DOUBLE(v)
#define FIX_DENORM_SAMPLE(v)		FIX_DENORM_DOUBLE(v)
#define FIX_DENORM_NAN_SAMPLE(v)	FIX_DENORM_NAN_DOUBLE(v)
#else
#define IS_DENORM_SAMPLE(v)			IS_DENORM_FLOAT(v)
#define IS_NAN_SAMPLE(v)			IS_NAN_FLOAT(v)
#define IS_DENORM_NAN_SAMPLE(v)		IS_DENORM_NAN_FLOAT(v)
#define FIX_DENORM_SAMPLE(v)		FIX_DENORM_FLOAT(v)
#define FIX_DENORM_NAN_SAMPLE(v)	FIX_DENORM_NAN_FLOAT(v)
#endif

#endif // _Z_SAMPLETYPE_H

