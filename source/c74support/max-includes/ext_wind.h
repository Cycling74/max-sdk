/*************************/
/* Copyright 1988 IRCAM. */
/*************************/
#ifndef _EXT_WIND_H_
#define _EXT_WIND_H_

BEGIN_USING_C_LINKAGE

/** Returned values from wind_advise()
	@ingroup misc
*/
typedef enum {
	aaYes =	1,		///< Yes button was choosen
	aaNo,			///< No button was choosen
	aaCancel		///< Cancel button was choosen
} e_max_wind_advise_result;
	

// advise returns...
	
#define ADVISE_SAVE		1
#define aaSave			ADVISE_SAVE
#define ADVISE_DISCARD	2
#define aaDiscard		ADVISE_DISCARD
#define ADVISE_CANCEL	3
#define aaCancel		ADVISE_CANCEL
#define ADVISE_FIRST	ADVISE_SAVE
#define ADVISE_SECOND	ADVISE_DISCARD
#define ADVISE_THIRD	ADVISE_CANCEL



/**	Throw a dialog which may have text and up to three buttons.  
	For example, this can be used to ask "Save changes before..." 
	@ingroup	misc
	@param	w	The window with which this dialog is associated.
	@param	s	A string with any sprintf()-like formatting to be displayed.
	@param	...	Any variables that should be substituted in the string defined by s.
	@return		One of the values defined in #e_max_wind_advise_result, depending on what the user selected.
*/
short wind_advise(t_object *w, char *s, ...);

// internal use only
short wind_advise_explain(t_object *w, char *note, char *explanation, char *b1, char *b2, char *b3);

/**	Change the cursor.
	@ingroup		misc

	@param	which	One of the following predefined cursors:
	@code
	#define C_ARROW		1
	#define C_WATCH		2
	#define C_IBEAM		3
	#define C_HAND		4
	#define	C_CROSS		5
	#define C_PENCIL	6
	#define	C_GROW		8
	@endcode

	@remark		wind_setcursor() keeps track of what the cursor was previously set 
				to, so if something else has changed the cursor, you may not see a new 
				cursor if you set it to the previous argument to wind_setcursor().
				
				The solution is to call wind_setcursor(0) before calling it with the 
				desired cursor constant. Use wind_setcursor(-1) to tell Max you’ll set 
				the cursor to your own cursor directly.
*/
void wind_setcursor(short which);


END_USING_C_LINKAGE

#endif // _EXT_WIND_H_
