// ext_itm.h copyright 2008 cycling '74 all rights reserved

#ifndef __EXT_ITM_H__
#define __EXT_ITM_H__

BEGIN_USING_C_LINKAGE


/**	A low-level object for tempo-based scheduling.
	@ingroup	time
	@see		#t_timeobject
	@see		@ref chapter_itm	*/
typedef t_object t_itm;


// private -- internal use only
typedef struct _clocksource
{
	t_object c_ob;
	method c_getticks;		// returns the current tick count
	method c_getstate;		// returns 0 if transport not going, 1 if going
	t_symbol *c_name;		// name
	long c_usedcount;		// number of transports using this clock source
	method c_gettempo;		// get current tempo
	method c_gettimesig;	// get current timesig
	method c_getsr;			// get current samplerate 
} t_clocksource;

// used by clocksource to report time sig change to ITM

typedef struct _tschange {
	long c_num;
	long c_denom;
	double c_tsbaseticks;	// ticks at last ts change (use -1 for "unknown")
	long c_tsbasebars;		// bars at last ts change (use -1 for "unknown")
} t_tschange;

/**	Flags that determine attribute and time object behavior
	@ingroup time	*/
enum {
	TIME_FLAGS_LOCATION = 1,			///< 1 1 0 location-based bar/beat/unit values (as opposed to interval values, which are 0 0 0 relative)
	TIME_FLAGS_TICKSONLY = 2,			///< only ticks-based values (not ms) are acceptable
	TIME_FLAGS_FIXEDONLY = 4,			///< only fixed values (ms, hz, samples) are acceptable
	TIME_FLAGS_LOOKAHEAD = 8,			///< add lookahead attribute (unsupported)
	TIME_FLAGS_USECLOCK = 16,			///< this time object will schedule events, not just hold a value
	TIME_FLAGS_USEQELEM = 32,			///< this time object will defer execution of scheduled events to low priority thread
	TIME_FLAGS_FIXED = 64,				///< will only use normal clock (i.e., will never execute out of ITM)
	TIME_FLAGS_PERMANENT = 128,			///< event will be scheduled in the permanent list (tied to a specific time)
	TIME_FLAGS_TRANSPORT = 256,			///< add a transport attribute
	TIME_FLAGS_EVENTLIST = 512,			///< add an eventlist attribute (unsupported)
	TIME_FLAGS_CHECKSCHEDULE = 1024,	///< internal use only
	TIME_FLAGS_LISTENTICKS = 2048,		///< flag for time_listen: only get notifications if the time object holds tempo-relative values
	TIME_FLAGS_NOUNITS = 4096,			///< internal use only
	TIME_FLAGS_BBUSOURCE = 8192,		///< source time was in bar/beat/unit values, need to recalculate when time sig changes
	TIME_FLAGS_POSITIVE = 16384			///< constrain any values < 0 to 0
};


/*******************************************************************************/

/**	Return the global (default / unnamed) itm object.
	@ingroup	time
	@return		The global #t_itm object.	*/
void *itm_getglobal(void);

/**	Return a named itm object.
	@ingroup		time
	@param	s		The name of the itm to return.
	@param	scheduler	
	@param	defaultclocksourcename	
	@param	create	If non-zero, then create this named itm should it not already exist.
	@return			The global #t_itm object.	*/
void *itm_getnamed(t_symbol *s, void *scheduler, t_symbol *defaultclocksourcename, long create);

// currently the same as itm_getnamed(s,true);
void *itm_getfromarg(t_object *o, t_symbol *s);

/**	Reference an itm object.
	When you are using an itm object, you must call this function to increment its reference count.
	@ingroup	time
	@param	x	The itm object.	*/
void itm_reference(t_itm *x);

/**	Stop referencing an itm object.
	When you are done using an itm object, you must call this function to decrement its reference count.
	@ingroup	time
	@param	x	The itm object.	*/
void itm_dereference(t_itm *x);


// event list support is limited to use in javascript for the time being.
void itm_deleteeventlist(t_itm *x, t_symbol *eventlist);
void itm_eventlistseek(t_itm *x);
void itm_geteventlistnames(t_itm *x, long *count, t_symbol ***names);
void itm_switcheventlist(t_itm *x, t_symbol *eventlist, double offset);


/**	Report the current internal time.
	This is the same as calling clock_getftime();
	@ingroup	time
	@param	x	The itm object.	
	@return		The current internal time.	*/
double itm_gettime(t_itm *x);

/**	Report the current time of the itm in ticks.
	You can use functions such as itm_tickstobarbeatunits() or itm_tickstoms() to convert to a different representation of the time.
	@ingroup	time
	@param	x	The itm object.	
	@return		The current time in ticks.	*/
double itm_getticks(t_itm *x);

/**	Print diagnostic information about an itm object to the Max window.
	@ingroup	time
	@param	x	The itm object.		*/
void itm_dump(t_itm *x);


// private -- internal use only
void itm_sync(t_itm *x);



/**	Set an itm object's current time signature.
	@ingroup		time
	@param	x		The itm object.	
	@param	num		The top number of the time signature.
	@param	denom	The bottom number of the time signature.
	@param	flags	Currently unused -- pass zero.	*/
void itm_settimesignature(t_itm *x, long num, long denom, long flags);

/**	Query an itm object for its current time signature.
	@ingroup		time
	@param	x		The itm object.	
	@param	num		The address of a variable to hold the top number of the time signature upon return.
	@param	denom	The address of a variable to hold the bottom number of the time signature upon return.	*/
void itm_gettimesignature(t_itm *x, long *num, long *denom);

void itm_seek(t_itm *x, double oldticks, double newticks, long chase);

/**	Pause the passage of time for an itm object.
	This is the equivalent to setting the state of a transport object to 0 with a toggle.
	@ingroup		time
	@param	x		The itm object.		*/
void itm_pause(t_itm *x);

/**	Start the passage of time for an itm object, from it's current location.
	This is the equivalent to setting the state of a transport object to 0 with a toggle.
	@ingroup		time
	@param	x		The itm object.		*/
void itm_resume(t_itm *x);

/**	Find out if time is currently progressing for a given itm object.
	@ingroup		time
	@param	x		The itm object.	
	@return			Returns non-zero if the time is running, or zero if it is paused.
	@see			itm_pause()
	@see			itm_resume()	*/
long itm_getstate(t_itm *x);


/**	Set the number of ticks-per-quarter-note globally for the itm system.
	The default is 480.
	@ingroup		time
	@param	res		The number of ticks-per-quarter-note.
	@see			itm_getresolution()	*/
void itm_setresolution(double res);

/**	Get the number of ticks-per-quarter-note globally from the itm system.
	@ingroup		time
	@return			The number of ticks-per-quarter-note.
	@see			itm_setresolution()	*/
double itm_getresolution(void);


/**	Given an itm object, return its name.
	@ingroup	time
	@param	x	The itm object.	
	@return		The name of the itm.	*/
t_symbol *itm_getname(t_itm *x);



t_max_err itm_parse(t_itm *x, long argc, t_atom *argv, long flags, double *ticks, double *fixed, t_symbol **unit, long *bbu, char *bbusource);


/**	Convert a time value in ticks to the equivalent value in milliseconds, given the context of a specified itm object.
	@ingroup		time
	@param	x		An itm object.
	@param	ticks	A time specified in ticks.
	@return			The time specified in ms.	*/
double itm_tickstoms(t_itm *x, double ticks);

/**	Convert a time value in milliseconds to the equivalent value in ticks, given the context of a specified itm object.
	@ingroup		time
	@param	x		An itm object.
	@param	ms		A time specified in ms.
	@return			The time specified in ticks.	*/
double itm_mstoticks(t_itm *x, double ms);

/**	Convert a time value in milliseconds to the equivalent value in samples, given the context of a specified itm object.
	@ingroup		time
	@param	x		An itm object.
	@param	ms		A time specified in ms.
	@return			The time specified in samples.	*/
double itm_mstosamps(t_itm *x, double ms);

/**	Convert a time value in samples to the equivalent value in milliseconds, given the context of a specified itm object.
	@ingroup		time
	@param	x		An itm object.
	@param	samps	A time specified in samples.
	@return			The time specified in ms.	*/
double itm_sampstoms(t_itm *x, double samps);


/**	Convert a time value in bbu to the equivalent value in ticks, given the context of a specified itm object.
	@ingroup			time
	@param	x			An itm object.
	@param	bars		The measure number of the location/position.
	@param	beats		The beat number of the location/position.
	@param	units		The number of ticks past the beat of the location/position.
	@param	ticks		The address of a variable to hold the number of ticks upon return.
	@param	position	Set this parameter to #TIME_FLAGS_LOCATION or to zero (for position mode).	*/
void itm_barbeatunitstoticks(t_itm *x, long bars, long beats, double units, double *ticks, char position);

/**	Convert a time value in bbu to the equivalent value in ticks, given the context of a specified itm object.
	@ingroup			time
	@param	x			An itm object.
	@param	ticks		The number of ticks to translate into a time represented as bars, beats, and ticks.
	@param	bars		The address of a variable to hold the measure number of the location/position upon return.
	@param	beats		The address of a variable to hold the beat number of the location/position upon return.
	@param	units		The address of a variable to hold the number of ticks past the beat of the location/position upon return.
	@param	position	Set this parameter to #TIME_FLAGS_LOCATION or to zero (for position mode).	*/
void itm_tickstobarbeatunits(t_itm *x, double ticks, long *bars, long *beats, double *units, char position);


void itm_format(t_itm *x, double ms, double ticks, long flags, t_symbol *unit, long *argc, t_atom **argv);


/**	Given the name of a time unit (e.g. 'ms', 'ticks', 'bbu', 'samples', etc.), determine whether the unit is fixed
	(doesn't change with tempo, time-signature, etc.) or whether it is flexible.
	@ingroup		time
	@param	u		The name of the time unit.
	@return			Zero if the unit is fixed (milliseconds, for example) or non-zero if it is flexible (ticks, for example).	*/
long itm_isunitfixed(t_symbol *u);



void itmclock_delay(t_object *x, t_itm *m, t_symbol *eventlist, double delay, long quantization);
void *itmclock_new(t_object *owner, t_object *timeobj, method task, method killer, long permanent);
void itmclock_set(t_object *x, t_itm *m, t_symbol *eventlist, double time);
void itmclock_unset(t_object *x);


// private -- internal use only
void *itm_clocksource_getnamed(t_symbol *name, long create);
void itm_getclocksources(long *count, t_symbol ***sources);
double itm_getsr(t_itm *x);
double itm_gettempo(t_itm *x);


END_USING_C_LINKAGE

#endif // __EXT_ITM_H__
