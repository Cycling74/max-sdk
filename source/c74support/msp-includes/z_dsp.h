// z_dsp.h -- the main header file for all DSP objects copyright 1997-2003 Cycling '74

// DSP services:

#ifndef _Z_DSP_H
#define _Z_DSP_H
	
#include "z_sampletype.h"
#include "ext_systhread.h"
#include "ext_linklist.h"
#include "ext_atomic.h"

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

/**	MSP System Properties.
	@ingroup	 msp	*/
enum {
	SYS_MAXBLKSIZE = 2048,	///< a good number for a maximum signal vector size
	SYS_MAXSIGS = 250		///< number of signal inlets you can have in an object
};

// header for all DSP objects. Provides a proxy.

// z_misc flags:

#define Z_NO_INPLACE 1	///< flag indicating the object doesn't want signals in place @ingroup msp
#define Z_PUT_LAST 2	///< when list of ugens is resorted, put this object at end @ingroup msp
#define Z_PUT_FIRST 4	///< when list of ugens is resorted, put this object at beginning @ingroup msp
#define Z_IGNORE_DISABLE 8	///< ignore the disable field when executing the chain, e.g. to process the pass~ object in a muted patcher.
#define Z_DONT_ADD 16		///< if this flag is set the object will be ignored and its dsp method won't be called.

#define SIXTEENIZE(p) ((((t_ptr_uint)(p)) + 16) & (~(t_ptr_uint)0xF))
#define THIRTYTWOIZE(p) ((((t_ptr_uint)(p)) + 32) & (~(t_ptr_uint)0x1F))

typedef void *t_proxy;

/**	Common struct for MSP objects. 
 @ingroup	msp	*/
typedef struct _pxdata {
	long	z_in;
	void	*z_proxy;
	long	z_disabled;		///< set to non-zero if this object is muted (using the pcontrol or mute~ objects)
	short	z_count;		///< an array that indicates what inlets/outlets are connected with signals
	short	z_misc;			///< flags (bitmask) determining object behaviour, such as #Z_NO_INPLACE, #Z_PUT_FIRST, or #Z_PUT_LAST
} t_pxdata; 

/**	Header for any non-ui signal processing object. 
	For ui objects use #t_pxjbox.
	@ingroup	msp	*/
typedef struct t_pxobject {
	struct object z_ob;	///< The standard #t_object struct.
	long z_in;
	void *z_proxy;
	long z_disabled;	///< set to non-zero if this object is muted (using the pcontrol or mute~ objects)
	short z_count;		///< an array that indicates what inlets/outlets are connected with signals
	short z_misc;		///< flags (bitmask) determining object behaviour, such as #Z_NO_INPLACE, #Z_PUT_FIRST, or #Z_PUT_LAST
} t_pxobject;


#define MAXLOGSIG 13
#define MAXSIGSIZE (1 << MAXLOGSIG)
/** The signal data structure.
	@ingroup	msp	*/
typedef struct _signal
{
    long s_n;						///< The vector size of the signal.
    t_sample *s_vec;				///< An array of buffers holding the vectors of audio.
    float s_sr;						///< The sample rate of the signal.
    struct _signal *s_next;
    struct _signal *s_nextused;
    short s_refcount;
    short s_size;					// element size (* s_n == memory)
    char *s_ptr;					// what to free
} t_signal;


// c74 private

struct _chain64item;
struct _chain64item_extra;

typedef struct _dspchain
{
	t_object c_ob;
	t_int *c_chain;
	long c_chainsize;
	long c_callcount;
	long c_usedcount;
	long c_reusedcount;
	long c_freedcount;
	long c_sr;
	long c_bs;
	t_signal *c_usedlist;
	t_signal *c_freelist;
	t_signal *c_zero;
	struct _ugenbox *c_ugenlist;	// temporary variable, allows reentrant compiling
	struct _dspchain *c_prev;
	void *c_patcher;				// top-level parent or 0 if global
	void *c_inlets;					// collection of inlets
	void *c_outlets;				// collection of outlets
	void *c_inputs;					// signal input list (zero before first exec)
	void *c_outputs; 				// signal output list
	// have to determine whether freelist is global or local
	volatile long c_broken;			// object being freed, don't run it
	long c_intype;					// using old signal linklist (0) or array
	long c_outtype;					// using old signal linklist (0) or array
	t_int32_atomic c_dontbreak;		// temporarily prevent chain from being broken
	t_int32_atomic c_wantsbreak;		// so main thread can tell audio thread it wants to become broken
	void *c_patchers;				// used to keep track of all patchers in chain
	void *c_posttickobjects;		// list of objects to be ticked after process (called from same thread as dspchain is ticked from)
	void *c_mixerlisteners;			// list of objects listening to various mixer notifications
	void *unused;					// was c_chain64 but no longer used
	struct _ugenbox *c_curugen;		// internal use: ugenbox pointer to current box during dsp64 method call 
	t_object *c_implicitugens;		// internal use
	long c_32bitchain;				// flag set when this is really a 32 bit chain (for wrapper)
	long c_benchmark;				// flag set when benchmarking cpu consumption
	double c_benchtime_used;		// cumulative cputime (in milliseconds) used for ticking all objects in the chain (only when benchmarking is enabled)
	double c_benchtime_available;	// cumulative time (in milliseconds) since this dspchain has been started (only when benchmarking is enabled)
	long c_chain64_alloclen; 
	long c_chain64_len; 
	struct _chain64item *c_chain64_array; 
	struct _chain64item_extra *c_chain64_extra_array;
} t_dspchain;

#ifndef VPTR_TYPEDEF
/** A void pointer.		@ingroup msp	*/
typedef void *t_vptr;
/** A void pointer.		@ingroup msp	*/
typedef void *vptr;
#define VPTR_TYPEDEF
#endif 

// useful define

#ifndef PI
/** The pi constant.				@ingroup msp	*/
#define PI 3.14159265358979323846
#endif
#ifndef TWOPI
/** Twice the pi constant.			@ingroup msp	*/
#define TWOPI		6.28318530717958647692
#endif  // TWOPI
#ifndef PIOVERTWO
/** Half of the pi constant.		@ingroup msp	*/
#define PIOVERTWO	1.57079632679489661923
#endif  // PIOVERTWO

// system access prototypes

BEGIN_USING_C_LINKAGE 

/**	A function pointer for the audio perform routine used by MSP objects to process blocks of samples. @ingroup msp */
typedef t_int *(*t_perfroutine)(t_int *args);

typedef void (*t_perfroutine64)(t_object *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam); 

// messages to the dsp object

void *dspmess(t_symbol *mess);

// access to DSP system variables

/**	Query MSP for the maximum global vector (block) size.
	@ingroup	msp	
	@return		The maximum global vector size for the MSP environment.		*/
int sys_getmaxblksize(void);

/**	Query MSP for the current global vector (block) size.
	@ingroup	msp	
	@return		The current global vector size for the MSP environment.		*/
int sys_getblksize(void);

/**	Query MSP for the global sample rate.
	@ingroup	msp	
	@return		The global sample rate of the MSP environment.		*/
float sys_getsr(void);

int sys_getch(void);			// returns current number of channels
int sys_optimize(void);			// returns whether to optimize or not
int sys_altivec(void);			// returns whether machine has vector processing

/**	Query MSP to determine whether or not it is running.
	@ingroup	msp	
	@return		Returns true if the DSP is turned on, otherwise returns false.		*/
int sys_getdspstate(void);		// returns whether audio is on or off

/** Query MSP to determine whether or not a given audio object is 
    in a running dsp chain.  This is preferable over sys_getdspstate() 
	since global audio can be on but an object could be in a patcher that
	is not running. 
	@ingroup	msp
	@return		Returns true if the MSP object is in a patcher that has audio on, otherwise returns false. 
*/
int sys_getdspobjdspstate(t_object *o);  

// controlling the DSP

void canvas_start_dsp(void);
void canvas_stop_dsp(void);
void dsp_tick(void);			// no longer used

// the dspchain object

#define DSPCHAIN_MIXERLISTENER_WILLPROCESSIOVECTOR		(0x00000001)
#define DSPCHAIN_MIXERLISTENER_WILLPROCESSMIXER			(0x00000002)
#define DSPCHAIN_MIXERLISTENER_DIDPROCESSMIXER			(0x00000004)
#define DSPCHAIN_MIXERLISTENER_DIDPROCESSIOVECTOR		(0x00000008)
#define DSPCHAIN_MIXERLISTENER_MIXERGRAPHWILLSTART		(0x00000010)
#define DSPCHAIN_MIXERLISTENER_MIXERGRAPHWILLSTOP		(0x00000020)

t_dspchain *dspchain_start(long bs, long sr);
t_dspchain *dspchain_get(void);
t_dspchain *dspchain_compile(t_patcher *p, long bs, long sr);
t_dspchain *dspchain_compile2(t_patcher *p, t_dspchain *x);
void dspchain_tick(t_dspchain *c);
void canvas_start_onedsp(t_patcher *p, t_dspchain **c, long bs, long sr); 
void canvas_stop_onedsp(t_dspchain *c);
void dspchain_setbroken(t_dspchain *c);
t_max_err dspchain_lock(t_dspchain *c); 
void dspchain_unlock(t_dspchain *c); 
t_dspchain *dspchain_fromobject(t_object *o); 
void dspchain_addmixerlistener(t_dspchain *chain, t_object *listener, long notifications); 

// utility perform routines

void set_zero(float *dst, long n);
void set_zero64(double *dst, long n);
void copy_64from32(t_double *dst, const t_float *src, long n);
void copy_32from64(t_float *dst, const t_double *src, long n);
t_int *plus_perform(t_int *args);
t_int *plus_perform64(t_int *args);
t_int *sig_perform(t_int *args);
t_int *sig_perform64(t_int *args);
t_int *copy_perform(t_int *args);
t_int *copy_perform64(t_int *args);
t_int *plus2_perform(t_int *w);
t_int *plus2_perform64(t_int *w);

// setup routines used by DSP objects

/**	Call this function in your MSP object's dsp method.
	This function adds your object's perform method to the DSP call chain 
	and specifies the arguments it will be passed. 
	n, the number of arguments to your perform method, should be followed by n 
	additional arguments, all of which must be the size of a pointer or a long.
	
	@ingroup	msp
	@param	f	The perform routine to use for processing audio.
	@param	n	The number of arguments that will follow
	@param	...	The arguments that will be passed to the perform routine.	
	@see		@ref chapter_msp_anatomy_dsp
	@see		@ref chapter_msp_advanced_connections	*/
C74_DEPRECATED( void dsp_add(t_perfroutine f, int n, ...) );

/**	Call this function in your MSP object's dsp method.
	Use dsp_addv() to add your object's perform routine to the DSP call 
	chain and specify its arguments in an array rather than as arguments to 
	a function. 
		
	@ingroup		msp
	@param	f		The perform routine to use for processing audio.
	@param	n		The number of arguments that will follow in the vector parameter.
	@param	vector 	The arguments that will be passed to the perform routine.
	@see			@ref chapter_msp_anatomy_dsp
	@see			@ref chapter_msp_advanced_connections	*/
C74_DEPRECATED( void dsp_addv(t_perfroutine f, int n, void **vector) );

// objects should only have one perform method
// in exceptional cases there may be a situation where warnings about this need to be disabled.
// this flag to dsp_add64 will accomplish that
// for internal use only
#define DSP_ADD64_FLAG_INTERNALITEM (0x00000001)

void dsp_add64(t_object *chain, t_object *x, t_perfroutine64 f, long flags, void *userparam); 

/**	Call this routine after creating your object in the new instance routine 
	with object_alloc(). Cast your object to #t_pxobject as the first 
	argument, then specify the number of signal inputs your object will 
	have. dsp_setup() initializes fields of the #t_pxobject header and 
	allocates any proxies needed (if num_signal_inputs is greater than 1).
	
	Some signal objects have no inputs; you should pass 0 for 
	num_signal_inputs in this case. After calling dsp_setup(), you can 
	create additional non-signal inlets using intin(), floatin(), or 
	inlet_new().

	@ingroup			msp
	@param	x			Your object's pointer.
	@param	nsignals	The number of signal/proxy inlets to create for the object.
	@see 				#dsp_setup	*/
void z_dsp_setup(t_pxobject *x, long nsignals);		// called in new method

/**	This is commonly used rather than directly calling z_dsp_setup() in MSP objects.
 	@ingroup	msp	*/
#define dsp_setup z_dsp_setup

void dsp_resize(t_pxobject *x, long nsignals); // for dynamic inlets


/**	This function disposes of any memory used by proxies allocated by 
	dsp_setup(). It also notifies the signal compiler that the DSP call chain 
	needs to be rebuilt if signal processing is active. You should be sure to 
	call this before de-allocating any memory that might be in use by your 
	object’s perform routine, in the event that signal processing is on when 
	your object is freed.

	@ingroup	msp
	@param	x	The object to free.
	@see		#dsp_free	*/
void z_dsp_free(t_pxobject *x);

/**	This is commonly used rather than directly calling z_dsp_free() in MSP objects.
 	@ingroup	msp	*/
#define dsp_free z_dsp_free


C74_DEPRECATED ( void z_add_signalmethod(void) );						// called in initialization routine
#define dsp_initclass z_add_signalmethod

void z_sysinit(void);
#define dsp_sysinit z_sysinit

void dsp_setpatcher(void *p);
void *dsp_getpatcher();

short z_isconnected(t_object *x, t_object *dst, short *index);
#define dsp_isconnected z_isconnected

short z_dsp_setloadupdate(short way);
#define dsp_setloadupdate z_dsp_setloadupdate

void *dsp_setpostprocess(method pm);
void *dsp_setpreprocess(method pm);

// used only by audio driver objects

void sys_setprocessflag(short way);

// lame audio file utility (do not use)

short aiff_parse(char *header, long *offset, long *size, long *nchans, long *ssize,
	long *srate, void *chunk, void *markers);

// memory utilities

void *t_resizebytes(char *old, long oldsize, long newsize);
void *t_getbytes(long size);
void *t_freebytes(void *fatso, long size);

// atom utilities

t_int atom_getintarg(short which, short argc, t_atom *argv);
float atom_getfloatarg(short which, short argc, t_atom *argv);
t_symbol *atom_getsymarg(short which, short argc, t_atom *argv);

#define PROXY_GETINLET(x) proxy_getinlet(x)


/**	This routine must be called in your object's initialization routine. It 
	adds a set of methods to your object's class that are called by MSP to 
	build the DSP call chain. These methods function entirely 
	transparently to your object so you don't have to worry about them. 
	However, you should avoid binding anything to their names: signal, 
	userconnect, nsiginlets, and enable. 
	
	This routine is for non-user-interface objects only
	(where the first item in your object's struct is a t_pxobject).
	It must be called prior to calling class_register() for your class.

	@ingroup	msp
	@param	c	The class to make dsp-ready.
	@see		class_dspinitjbox()	*/
void class_dspinit(t_class *c);

/**	This routine must be called in your object's initialization routine. It 
	adds a set of methods to your object's class that are called by MSP to 
	build the DSP call chain. These methods function entirely 
	transparently to your object so you don't have to worry about them. 
	However, you should avoid binding anything to their names: signal, 
	userconnect, nsiginlets, and enable. 
	
	This routine is for user-interface objects only
	(where the first item in your object's struct is a t_jbox). 

	@ingroup	msp
	@param	c	The class to make dsp-ready.
	@see		class_dspinit()	*/
void class_dspinitjbox(t_class *c);


// defines for SIMD optimization

// minimum vector size to use SIMD optimization
#define DSP_OPTIMIZE_MIN	64

// simple (e.g. times, minus) not worth optimizing, disabled
#define DSP_SIMPLE_OPTIMIZE_TEST(sigptr)		(FALSE)

// simple parameter setting test (e.g. times, minus) not worth optimizing, disabled
#define DSP_SIMPLE_OPTIMIZE_TEST_PARAM			(FALSE)

// complex (e.g. cos, log, sqrt, fft family) optimize as long as enabled and vector is large enough
#define DSP_COMPLEX_OPTIMIZE_TEST(sigptr)		(FALSE)
//#define DSP_COMPLEX_OPTIMIZE_TEST(sigptr)		(sys_optimize()&&(sigptr)&&(sigptr)->s_n>=DSP_OPTIMIZE_MIN)

// buffered routines optimize always if enabled since signal vector isn't relevant
#define DSP_BUFFERED_OPTIMIZE_TEST(sigptr)		(FALSE)
//#define DSP_BUFFERED_OPTIMIZE_TEST(sigptr)	(sys_optimize())



END_USING_C_LINKAGE 

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

//-- ddz, so this is OK, just needs jpatcher_api.h first, right?

#if defined(_JPATCHER_API_H_) || defined(_DOXY_)
BEGIN_USING_C_LINKAGE


/**	Header for any ui signal processing object. 
	For non-ui objects use #t_pxobject.
	@ingroup	msp	*/
typedef struct _pxjbox {
	t_jbox	z_box;			///< The box struct used by all ui objects.
	long	z_in;
	void	*z_proxy;
	long	z_disabled;		///< set to non-zero if this object is muted (using the pcontrol or mute~ objects)
	short	z_count;		///< an array that indicates what inlets/outlets are connected with signals
	short	z_misc;			///< flags (bitmask) determining object behaviour, such as #Z_NO_INPLACE, #Z_PUT_FIRST, or #Z_PUT_LAST
} t_pxjbox;

void z_jbox_dsp_setup(t_pxjbox *x, long nsignals); 
void z_jbox_dsp_free(t_pxjbox *x);

#define dsp_setupjbox z_jbox_dsp_setup
#define dsp_freejbox z_jbox_dsp_free

END_USING_C_LINKAGE


#endif // _JPATCHER_API_H_
#endif // _Z_DSP_H

