#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "ext_obex.h"
#include "ext_systhread.h"
#include "ext_critical.h"
#include "ext_atomic.h"
#include "ext_buffer.h"

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

enum {
	MAXCHAN = 4
};

enum {
	bi_basefreq = 0,
	bi_detune,
	bi_lowfreq,
	bi_hifreq,
	bi_lowvel,
	bi_hivel,
	bi_gain,
	bi_numparams
};


/**	Data structure for the buffer~ object.
	Deprectated.
	Use #t_buffer_ref and #t_buffer_obj instead.
*/
struct _buffer
{
	t_object b_obj;		///< doesn't have any signals so it doesn't need to be pxobject
	long b_valid;		///< flag is off during read replacement or editing operation
	float *b_samples;	///< stored with interleaved channels if multi-channel
	long b_frames;		///< number of sample frames (each one is sizeof(float) * b_nchans bytes)
	long b_nchans;		///< number of channels
	long b_size;		///< size of buffer in floats
	float b_sr;			///< sampling rate of the buffer
	float b_1oversr;	///< 1 / sr
	float b_msr;		///< sr * .001
	// Mac-specific stuff
	float *b_memory;	///< pointer to where memory starts (initial padding for interp)
	t_symbol *b_name;	///< name of the buffer
	short b_vol;
	short b_space;
	// looping info (from AIFF file)
	long b_susloopstart;	///< looping info (from AIFF file) in samples
	long b_susloopend;		///< looping info (from AIFF file) in samples
	long b_relloopstart;	///< looping info (from AIFF file) in samples
	long b_relloopend;		///< looping info (from AIFF file) in samples
	// instrument info (from AIFF file)
	short b_inst[bi_numparams];
	// window stuff
	void *b_wind;
	double b_pixperfr;
	double b_frperpix;
	long b_imagesize;
	short b_unusedshort1;		// was Point b_scroll
	short b_unusedshort2;		// could chop if struct compatibility wasn't important
	long b_scrollscale;
	long b_selbegin[MAXCHAN];	// unused - do NOT USE - MAXCHAN is retired
	long b_selend[MAXCHAN];		// unused - do NOT USE - MAXCHAN is retired
	long b_zoom;
	long b_zim[11];
	void *b_mouseout;
	long b_format;			///< 'AIFF' or 'Sd2f'
	t_symbol *b_filename;	///< last file read (not written) for info~
	long b_oldnchans;		///< used for resizing window in case of # of channels change
	void *b_doneout;
	long b_outputbytes;		///< number of bytes used for output sample (1-4)
	long b_modtime;			///< last modified time ("dirty" method)
	struct _buffer *b_peer;	///< objects that share this symbol (used as a link in the peers)
	t_bool b_owner;		///< b_memory/b_samples "owned" by this object
	long b_outputfmt;		///< sample type (A_LONG, A_FLOAT, etc.)
	t_int32_atomic b_inuse;	///< objects that use buffer should ATOMIC_INCREMENT / ATOMIC_DECREMENT this in their perform
	void *b_dspchain;		///< dspchain used for this instance
	long b_padding;			///< amount of padding (number of samples) in b_memory before b_samples starts
	long b_paddingchanged;	///< flag indicating that b_padding has changed and needs to be allocated
	t_object *b_jsoundfile;	///< internal instance for reading/writing FLAC format
	t_systhread_mutex b_mutex; ///< mutex to use when locking and performing operations anywhere except perform method
	long b_wasvalid;		///< internal flag used by replacement or editing operation
	method b_custom_error_handler_fn;	/// used to return error numbers to a caller if this object is embedded inside of another object (e.g. playlist~)
	t_object *b_custom_error_handler;	/// used to return error numbers to a caller if this object is embedded inside of another object (e.g. playlist~)
	t_clock *b_dirty_clock;				///< used to move buffer dirty notifications to the main thread
	t_qelem *b_dirty_qelem;				///< used to move buffer dirty notifications to the main thread
	t_bool b_dirty_done;				///< a buffer is not only dirty, but needs the 'done' message sent out its b_doneout outlet
	t_filepath b_filevol;	///< path of last file read (not written)
};

// Direct access to a t_buffer struct is deprecated and will no longer be supported in the future.
// Instead, use t_buffer_ref and t_buffer_obj as defined in the 'ext_buffer.h' header file.

#ifdef C74_BUFFER_INTERNAL
typedef struct _buffer t_buffer;
#else
C74_DEPRECATED( typedef struct _buffer t_buffer );
#endif // C74_BUFFER_INTERNAL


#define BUFWIND(x) ((t_wind *)(x->b_wind))


#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#endif // #ifndef _BUFFER_H_
