
#ifndef _EXT_SYSTIME_H_
#define _EXT_SYSTIME_H_

#include "ext_prefix.h"
#include "max_types.h"

BEGIN_USING_C_LINKAGE

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif


/** 
	The Systime data structure.
	@ingroup systime	
*/
	
typedef struct _datetime {
	t_uint32	year;			///< year
	t_uint32	month;			///< month, in range 1 through 12
	t_uint32	day;			///< day, in range 1 through 31
	t_uint32	hour;			///< hour
	t_uint32	minute;			///< minute
	t_uint32	second;			///< second
	t_uint32	millisecond;	///< (reserved for future use)
} t_datetime;

/**	Flags for the sysdateformat_formatdatetime() function.
	@ingroup systime
*/
typedef enum {
	SYSDATEFORMAT_FLAGS_SHORT = 1,	///< short
	SYSDATEFORMAT_FLAGS_MEDIUM = 2,	///< medium
	SYSDATEFORMAT_FLAGS_LONG = 3,	///< long

	SYSDATEFORMAT_RELATIVE = 16
} e_max_dateflags;
	
/**
	Find out the operating system’s time in ticks. 
	@ingroup systime
	@return	the system time in ticks.
*/
t_uint32 systime_ticks(void);


/**
	Find out the operating system’s time in milliseconds.
	Note that this is approximately the number of milliseconds since the OS was started up.
	@ingroup systime
	@return	the system time in milliseconds.
*/
t_uint32 systime_ms(void);


/**
 Find out the current date/time as number of ms since January 1, 1970, GMT.
 @ingroup systime
 @return	the number of milliseconds since January 1, 1970, GMT.
 */
t_int64 systime_datetime_milliseconds(void);

/**
	Find out the operating system’s current local date and time.
	@ingroup systime
	@param	d	Returns the system’s date and time in the local time zone in a #t_datetime data structure.
*/
void systime_datetime(t_datetime *d);


/**
	Find out the operating system’s time in seconds since midnight, January 1, 1904, GMT (mac HFS time).
	@ingroup systime
	@return	the system time in seconds since midnight, January 1, 1904, GMT. 
*/
t_ptr_uint systime_seconds(void);


/**
	Convert a time in seconds into a #t_datetime representation.
	@ingroup systime
	@param secs	A number of seconds since midnight, January 1, 1904, GMT, to be represented as a #t_datetime.
	@param d	The address of a #t_datetime that will be filled to the corresponding time, in the local time zone.
*/
void systime_secondstodate(t_ptr_uint secs, t_datetime *d);


/**
	Convert a #t_datetime representation of time into seconds since midnight, January 1, 1904, GMT.
	@ingroup	systime
	@param d	The address of a #t_datetime to be converted to seconds. The #t_datetime values are in the local time zone.
	@return 	The number of seconds between midnight, January 1, 1904, GMT and the time represented in d.
*/
t_ptr_uint systime_datetoseconds(const t_datetime *d);


/**
	Fill a #t_datetime struct with a datetime formatted string.
	For example, the string "2007-12-24 12:21:00".
	@ingroup	systime
	@param		strf	A string containing the datetime.
	@param		d		The address of a #t_datetime to fill.
*/
void sysdateformat_strftimetodatetime(const char *strf, t_datetime *d);


/**
	Get a human friendly string representation of a #t_datetime.
	For example: "Dec 17, 2020 at 10:48 AM"
	or, when dateflags is SYSDATEFORMAT_RELATIVE a string like "Today", "Yesterday", etc.
	@ingroup	systime
	@param		d			The address of a #t_datetime to format as a string. The t_datetime entries correspond to the local time.
	@param		dateflags	One of the values defined in #e_max_dateflags.
	@param		timeflags	Currently unused.  Pass 0.
	@param		s			An already allocated string to hold the human friendly result.
	@param		buflen		The number of characters allocated to the string s.
*/
void sysdateformat_formatdatetime(const t_datetime *d, long dateflags, long timeflags, char *s, long buflen);

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

END_USING_C_LINKAGE

#endif // _EXT_SYSTIME_H_

