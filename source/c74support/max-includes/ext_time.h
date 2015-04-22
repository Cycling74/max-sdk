/*
 *  ext_time.h
 *
 *  Copyright 2008 Cycling '74. All rights reserved.
 *
 */

#ifndef __EXT_TIME_H__
#define __EXT_TIME_H__

#include "ext_itm.h"

BEGIN_USING_C_LINKAGE



/**
	A high-level time object for tempo-based scheduling.

	@ingroup	time
	@see		#t_itm
	@see		@ref chapter_itm
*/
typedef t_object t_timeobject;


/*******************************************************************************/


/**
 Stop a currently scheduled time object.
 
 @ingroup	time
 @param		x				The time object.

*/
void time_stop(t_timeobject *x);


/**
 Execute a time object's task, then if it was already set to execute, reschedule for the current interval value of the object.
 
 @ingroup	time
 @param		x				The time object.
 
*/
void time_tick(t_timeobject *x);


/**
 Convert the value of a time object to milliseconds.
 
 @ingroup	time
 @param		x				The time object.
 @return					The time object's value, converted to milliseconds.
*/
double time_getms(t_timeobject *x);


/**
 Convert the value of a time object to ticks.
 
 @ingroup	time
 @param		x				The time object.
 @return					The time object's value, converted to ticks.
*/
double time_getticks(t_timeobject *x);


/**
 Return the phase of the ITM object (transport) associated with a time object.
 
 @ingroup	time
 @param		tx				The time object.
 @param		phase			Pointer to a double to receive the progress within the specified time value of the associated ITM object.
 @param		slope			Pointer to a double to receive the slope (phase difference) within the specified time value of the associated ITM object.
 @param		ticks			
*/
void time_getphase(t_timeobject *tx, double *phase, double *slope, double *ticks);


/**
 Specify that a millisecond-based attribute to be updated automatically when the converted milliseconds of the time object's value changes.
 
 @ingroup	time
 @param		x				The time object.
 @param		attr			Name of the millisecond based attribute in the owning object that will be updated
 @param		flags			If TIME_FLAGS_LISTENTICKS is passed here, updating will not happen if the time value is fixed (ms) based
 */
void time_listen(t_timeobject *x, t_symbol *attr, long flags);


/**
 Set the current value of a time object (either an interval or a position) using a Max message.
 
 @ingroup	time
 @param		tx				The time object.
 @param		s				Message selector.
 @param		argc			Count of arguments.
 @param		argv			Message arguments.
 */
void time_setvalue(t_timeobject *tx, t_symbol *s, long argc, t_atom *argv);

/**
 Create an attribute permitting a time object to be changed in a user-friendly way.
 
 @ingroup	time
 @param		c				Class being initialized.
 @param		attrname		Name of the attribute associated with the time object.
 @param		attrlabel		Descriptive label for the attribute (appears in the inspector)
 @param		flags			Options, see "Flags that determine time object behavior" above
*/
void class_time_addattr(t_class *c, const char *attrname, const char *attrlabel, long flags);

/**
 Create a new time object.
 
 @ingroup	time
 @param		owner			Object that will own this time object (task routine, if any, will pass owner as argument).
 @param		attrname		Name of the attribute associated with the time object.
 @param		tick			Task routine that will be executed (can be NULL)
 @param		flags			Options, see "Flags that determine time object behavior" above
 @return					The newly created #t_timeobject.
*/
void *time_new(t_object *owner, t_symbol *attrname, method tick, long flags);

/**
 Return a time object associated with an attribute of an owning object.
 
 @ingroup	time
 @param		owner			Object that owns this time object (task routine, if any, will pass owner as argument).
 @param		attrname		Name of the attribute associated with the time object.
 @return					The #t_timeobject associated with the named attribute.
*/
t_object *time_getnamed(t_object *owner, t_symbol *attrname);


void time_enable_attributes(t_object *x);

/**
 Return whether this time object currently holds a fixed (millisecond-based) value.
 
 @ingroup	time
 @param		x				Time object.
 @return					True if time object's current value is fixed, false if it is tempo-relative.
*/
long time_isfixedunit(t_timeobject *x);


/**
 Schedule a task, with optional quantization.
 
 @ingroup	time
 @param		x				The time object that schedules temporary events (must have been created with TIME_FLAGS_USECLOCK but not TIME_FLAGS_PERMANENT)
 @param		quantize		A time object that holds a quantization interval, can be NULL for no quantization.
*/
void time_schedule(t_timeobject *x, t_timeobject *quantize);


/**
 Schedule a task, with optional minimum interval, 
 
 @ingroup	time
 @param		x				The time object that schedules temporary events (must have been created with TIME_FLAGS_USECLOCK but not TIME_FLAGS_PERMANENT)
 @param		quantize		The minimum interval into the future when the event can occur, can be NULL if there is no minimum interval.
*/
void time_schedule_limit(t_timeobject *x, t_timeobject *quantize);

/**
 Schedule a task for right now, with optional quantization.
 
 @ingroup	time
 @param		x				The time object that schedules temporary events. The time interval is ignored and 0 ticks is used instead.
 @param		quantize		A time object that holds a quantization interval, can be NULL for no quantization.
*/
void time_now(t_timeobject *x, t_timeobject *quantize);


/**
 Return the ITM object associated with this time object.
 
 @ingroup	time
 @param		ox				Time object.
 @return					The associated #t_itm object.
*/
void *time_getitm(t_timeobject *ox);


/**
 Calculate the quantized interval (in ticks) if this time object were to be scheduled at the current time.
 
 @ingroup	time
 @param		ox				Time object.
 @param		vitm			The associated ITM object (use time_getitm() to determine it).
 @param		oq				A time object that holds a quantization interval, can be NULL.
 @return					Interval (in ticks) for scheduling this object.
*/
double time_calcquantize(t_timeobject *ox, t_itm *vitm, t_timeobject *oq);


/**
 Associate a named setclock object with a time object (unsupported).
 
 @ingroup	time
 @param		tx				Time object.
 @param		sc				Name of an associated setclock object.
*/
void time_setclock(t_timeobject *tx, t_symbol *sc);

END_USING_C_LINKAGE

#endif // __EXT_TIME_H__

