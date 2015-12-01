#ifndef _EXT_BUFFER_H_
#define _EXT_BUFFER_H_


/**	A buffer~ reference.
	Use this struct to represent a reference to a buffer~ object in Max.
	Use the buffer_ref_getbuffer() call to return a pointer to the buffer.
	You can then make calls on the buffer itself.
 
	@ingroup buffers
*/
typedef struct _buffer_ref t_buffer_ref;


/**	A buffer~ object.
	This represents the actual buffer~ object.
	You can use this to send messages, query attributes, etc. of the actual buffer object
	referenced by a #t_buffer_ref.
 
	@ingroup buffers
 */
typedef t_object t_buffer_obj;


/**	Common buffer~ data/metadata.
	This info can be retreived from a buffer~ using the buffer_getinfo() call.
 
	@ingroup buffers
 */
typedef struct _buffer_info
{
	t_symbol	*b_name;		///< name of the buffer
	float		*b_samples;		///< stored with interleaved channels if multi-channel
	long		b_frames;		///< number of sample frames (each one is sizeof(float) * b_nchans bytes)
	long		b_nchans;		///< number of channels
	long		b_size;			///< size of buffer in floats
	float		b_sr;			///< sampling rate of the buffer
	long		b_modtime;		///< last modified time ("dirty" method)
	long		b_rfu[57];		///< reserved for future use (total struct size is 64x4 = 256 bytes)
} t_buffer_info;


BEGIN_USING_C_LINKAGE


/**	Create a reference to a buffer~ object by name.
	You must release the buffer reference using object_free() when you are finished using it.
 
	@ingroup buffers
	@param	self	pointer to your object
	@param	name 	the name of the buffer~
	@return			a pointer to your new buffer reference
*/
t_buffer_ref* buffer_ref_new(t_object *self, t_symbol *name);


/**	Change a buffer reference to refer to a different buffer~ object by name.
 
	 @ingroup buffers
	 @param	x		the buffer reference
	 @param	name 	the name of a different buffer~ to reference
 */
void buffer_ref_set(t_buffer_ref *x, t_symbol *name);


/**	Query to find out if a buffer~ with the referenced name actually exists.
 
	@ingroup buffers
	@param	x		the buffer reference
	@return			non-zero if the buffer~ exists, otherwise zero
*/
t_atom_long buffer_ref_exists(t_buffer_ref *x);


/**	Query a buffer reference to get the actual buffer~ object being referenced, if it exists.
 
	 @ingroup buffers
	 @param	x			the buffer reference
	 @return			the buffer object if exists, otherwise NULL
 */
t_buffer_obj *buffer_ref_getobject(t_buffer_ref *x);


/**	Your object needs to handle notifications issued by the buffer~ you reference.
	You do this by defining a "notify" method.
	Your notify method should then call this notify method for the #t_buffer_ref.
 
	@ingroup buffers
	@param	x		the buffer reference
	@param	s 		the registered name of the sending object
	@param	msg		then name of the notification/message sent
	@param	sender	the pointer to the sending object
	@param	data	optional argument sent with the notification/message
	@return			a max error code
*/
t_max_err buffer_ref_notify(t_buffer_ref *x, t_symbol *s, t_symbol *msg, void *sender, void *data);





/**	Open a viewer window to display the contents of the buffer~.
 
	@ingroup buffers
	@param	buffer_object	the buffer object
*/
void buffer_view(t_buffer_obj *buffer_object);


/**	Claim the buffer~ and get a pointer to the first sample in memory.
	When you are done reading/writing to the buffer you must call buffer_unlocksamples().
	If the attempt to claim the buffer~ fails the returned pointer will be NULL.
 
	@ingroup buffers
	@param	buffer_object	the buffer object
	@return					a pointer to the first sample in memory, or NULL if the buffer doesn't exist.
*/
float *buffer_locksamples(t_buffer_obj *buffer_object);


/**	Release your claim on the buffer~ contents so that other objects may read/write to the buffer~.
 
	@ingroup buffers
	@param	buffer_object	the buffer object
*/
void buffer_unlocksamples(t_buffer_obj *buffer_object);


#ifndef C74_BUFFER_INTERNAL


/**	Query a buffer~ to find out how many channels are present in the buffer content.
 
	@ingroup buffers
	@param	buffer_object	the buffer object
	@return					the number of channels in the buffer
*/
t_atom_long buffer_getchannelcount(t_buffer_obj *buffer_object);


/**	Query a buffer~ to find out how many frames long the buffer content is in samples.
 
	@ingroup buffers
	@param	buffer_object	the buffer object
	@return					the number of frames in the buffer
*/
t_atom_long buffer_getframecount(t_buffer_obj *buffer_object);


/**	Query a buffer~ to find out its native sample rate in samples per second.
 
	@ingroup buffers
	@param	buffer_object	the buffer object
	@return					the sample rate in samples per second
*/
t_atom_float buffer_getsamplerate(t_buffer_obj *buffer_object);


/**	Query a buffer~ to find out its native sample rate in samples per millisecond.
 
	@ingroup buffers
	@param	buffer_object	the buffer object
	@return					the sample rate in samples per millisecond
*/
t_atom_float buffer_getmillisamplerate(t_buffer_obj *buffer_object);


/** Set the number of samples with which to zero-pad the buffer~'s contents.
	The typical application for this need is to pad a buffer with enough room to allow for the reach of a FIR kernel in convolution.
 
	@ingroup buffers
	@param	buffer_object	the buffer object
	@param	samplecount		the number of sample to pad the buffer with on each side of the contents
	@return					an error code
*/
t_max_err buffer_setpadding(t_buffer_obj *buffer_object, t_atom_long samplecount);


/**	Set the buffer's dirty flag, indicating that changes have been made.
 
	@ingroup buffers
	@param	buffer_object	the buffer object
	@return					an error code
 */
t_max_err buffer_setdirty(t_buffer_obj *buffer_object);


/** Retrieve the name of the last file to be read by a buffer~.
	(Not the last file written).
 
	@ingroup buffers
	@param	buffer_object	the buffer object
	@return					The name of the file last read, or gensym("") if no files have been read.
 
	@version Introduced in Max 7.0.1 on the Mac, not available until Max 7.1 on Windows.
 */
t_symbol *buffer_getfilename(t_buffer_obj *buffer_object);


#endif //  C74_BUFFER_INTERNAL


// Internal or low-level functions


// buffer_perform functions to replace the direct use of
// atomics and other buffer state flags from the perform method
// wrapped by buffer_locksamples() and buffer_unlocksamples()
t_max_err buffer_perform_begin(t_buffer_obj *buffer_object);
t_max_err buffer_perform_end(t_buffer_obj *buffer_object);

// utility function for getting buffer info in struct form
// without needing to know entire buffer struct
t_max_err buffer_getinfo(t_buffer_obj *buffer_object, t_buffer_info *info);


// the following functions are not to be called in the perform method
// please use the lightweight buffer_perform methods

// use buffer_edit functions to collapse all operations of
// locking heavy b_mutex, setting b_valid flag,
// waiting on lightweight atomic b_inuse, etc.
t_max_err buffer_edit_begin(t_buffer_obj *buffer_object);
t_max_err buffer_edit_end(t_buffer_obj *buffer_object, long valid);  // valid 0=FALSE, positive=TRUE, negative=RESTORE_OLD_VALID (not common)

// low level mutex locking used by buffer_edit fucntions.
// use only if you really know what you're doing.
// otherwise, use the buffer_edit functions
// if you're touching a t_buffer outside perform
t_max_err buffer_lock(t_buffer_obj *buffer_object);
t_max_err buffer_trylock(t_buffer_obj *buffer_object);
t_max_err buffer_unlock(t_buffer_obj *buffer_object);

// low level utilities used by buffer_edit functions
// use only if you really know what you're doing.
// otherwise, use the buffer_edit functions
// if you're touching a t_buffer outside perform
t_buffer_obj *buffer_findowner(t_buffer_obj *buffer_object);
long buffer_spinwait(t_buffer_obj *buffer_object);
long buffer_valid(t_buffer_obj *buffer_object, long way);




END_USING_C_LINKAGE


#endif // #ifndef _EXT_BUFFER_H_
