#ifndef _EXT_POST_H_
#define _EXT_POST_H_

#include "ext_prefix.h"
#include "ext_mess.h"

BEGIN_USING_C_LINKAGE

/**
	Print text to the Max window.
	Max 5 introduced object_post(), which provides several enhancements to post()
	where a valid #t_object pointer is available.
	
	post() is a printf() for the Max window. It even works from non-main threads,
	queuing up multiple lines of text to be printed when the main thread processing resumes.
	post() can be quite useful in debugging your external object.
	
	@ingroup console
	@param	fmt		A C-string containing text and printf-like codes
					specifying the sizes and formatting of the additional arguments.
	@param	...		Arguments of any type that correspond to the format codes in fmtString.
	
	@remark		Note that post only passes 16 bytes of arguments to sprintf, so if
				you want additional formatted items on a single line, use postatom().
				 
				Example:
	@code
	short whatIsIt;

	whatIsIt = 999;
	post ("the variable is %ld",(long)whatIsIt);
	@endcode
	
	@remark		The Max Window output when this code is executed.
	@code
	the variable is 999
	@endcode
	
	@see object_post()
	@see error()
	@see cpost()
*/
void post(C74_CONST char *fmt, ...);


/**
	Print text to the system console.
	On the Mac this post will be visible by launching Console.app in the /Applications/Utilities folder.
	On Windows this post will be visible by launching the dbgView.exe program, which is a free download
	as a part of Microsoft's SysInternals.
	
	@ingroup console
	@param	fmt		A C-string containing text and printf-like codes
					specifying the sizes and formatting of the additional arguments.
	@param	...		Arguments of any type that correspond to the format codes in fmtString.
	
	@remark			Particularly on MacOS 10.5, posting to Console.app can be a computationally expensive operation.
					Use with care.
					
	@see post()
	@see object_post()
*/
void cpost(C74_CONST char *fmt, ...);


/**
	Print an error to the Max window.
	Max 5 introduced object_error(), which provides several enhancements to error()
	where a valid #t_object pointer is available.
	
	error() is very similar to post(), thought it offers two additional features:
	- the post to the Max window is highlighted (with a red background).
	- the post can be trapped with the error object in a patcher.
		
	@ingroup console
	@param	fmt		A C-string containing text and printf-like codes
					specifying the sizes and formatting of the additional arguments.
	@param	...		Arguments of any type that correspond to the format codes in fmtString.
		
	@see object_post()
	@see post()
	@see cpost()
*/
void error(C74_CONST char *fmt, ...);

/**
	Put up an error or advisory alert box on the screen.

	Don't use this function.  Instead use error(), object_error(), or object_error_obtrusive().
	
	This function performs an sprintf() on fmtstring and items, then
	puts up an alert box. ouchstring() will queue the message to a lower
	priority level if it's called in an interrupt and there is no alert box
	request already pending.
	
	@ingroup console
	@param	s		A C-string containing text and printf-like codes
					specifying the sizes and formatting of the additional arguments.
	@param	...		Arguments of any type that correspond to the format codes in fmtString.
	
	@see	error()
	@see	object_error()
	@see	object_error_obtrusive()
*/
void ouchstring(C74_CONST char *s, ...);


/**
	Print multiple items in the same line of text in the Max window.
	This function prints a single #t_atom on a line in the Max window
	without a carriage return afterwards, as post() does. Each #t_atom printed
	is followed by a space character.

	@ingroup console
	@param	ap		The address of a #t_atom to print.

	@see object_post()
	@see post()
	@see cpost()

*/
void postatom(t_atom *ap);

void debug_printf(C74_CONST char *,...);


/**	Receive messages from the error handler.
	@ingroup misc
	@param	x	The object to be subscribed to the error handler.
	
	@remark		error_subscribe() enables your object to receive a message (error),
				followed by the list of atoms in the error message posted to the Max
				window.
	
				Prior to calling error_subscribe(), you should bind the error
				message to an internal error handling routine:
	@code
	addmess((method)myobject_error, "error", A_GIMME, 0);
	@endcode
				Your error handling routine should be declared as follows:
	@code
	void myobject_error(t_myobject *x, t_symbol *s, short argc, t_atom *argv);
	@endcode
*/
void error_subscribe(t_object *x);


/** Remove an object as an error message recipient.
	@ingroup misc
	@param	x	The object to unsubscribe.
*/
void error_unsubscribe(t_object *x);


void xsetpost(void);

void poststring(const char *s);

enum {
	POSTROW_POST = 0,
	POSTROW_ERROR = 1,
	POSTROW_WARNING = 2,
	POSTROW_BUG = 3,
	POSTROW_BADGE = 4
};

enum {
	JMAXWINDOW_ADVANCE = 1,
	JMAXWINDOW_APPEND = 2,
	JMAXWINDOW_WRITE = 4,
	JMAXWINDOW_UNIQUE = 8,
	JMAXWINDOW_MULTILINE = 16
};


/**
	Print text to the Max window, linked to an instance of your object.

	Max window rows which are generated using object_post() or object_error() can be
	double-clicked by the user to have Max assist with locating the object in a patcher.
	Rows created with object_post() and object_error() will also automatically provide
	the name of the object's class in the correct column in the Max window.
		
	@ingroup console
	@param	x		A pointer to your object.
	@param	s		A C-string containing text and printf-like codes
					specifying the sizes and formatting of the additional arguments.
	@param	...		Arguments of any type that correspond to the format codes in fmtString.
	
	@remark			Example:
	@code
	void myMethod(myObject *x, long someArgument)
	{
		object_post((t_object*)x, "This is my argument: %ld", someArgument);
	}
	@endcode
		
	@see object_error()
*/
void object_post(t_object *x, C74_CONST char *s, ...);


/**
	Print text to the Max window, linked to an instance of your object,
	and flagged as an error (highlighted with a red background).

	Max window rows which are generated using object_post() or object_error() can be
	double-clicked by the user to have Max assist with locating the object in a patcher.
	Rows created with object_post() and object_error() will also automatically provide
	the name of the object's class in the correct column in the Max window.
		
	@ingroup console
	@param	x		A pointer to your object.
	@param	s		A C-string containing text and printf-like codes
					specifying the sizes and formatting of the additional arguments.
	@param	...		Arguments of any type that correspond to the format codes in fmtString.
		
	@see object_post()
	@see object_warn()
*/
void object_error(t_object *x, C74_CONST char *s, ...);


/**
	Print text to the Max window, linked to an instance of your object,
	and flagged as a warning (highlighted with a yellow background).

	Max window rows which are generated using object_post(), object_error(), or object_warn can be
	double-clicked by the user to have Max assist with locating the object in a patcher.
	Rows created with object_post(), object_error(), or object_warn() will also automatically provide
	the name of the object's class in the correct column in the Max window.
		
	@ingroup console
	@param	x		A pointer to your object.
	@param	s		A C-string containing text and printf-like codes
					specifying the sizes and formatting of the additional arguments.
	@param	...		Arguments of any type that correspond to the format codes in fmtString.
			
	@see object_post()
	@see object_error()
*/
void object_warn(t_object *x, C74_CONST char *s, ...);

// ?
void object_bug(t_object *x, C74_CONST char *s, ...);

// private?
void object_poststring(t_object *ob, long kind, long flags, char *text);

#define STARTUP_CALL_MESSAGE(message, function_name, ...) \
	{ \
		t_bool log = gensym("g_max_startuplog")->s_thing ? TRUE : FALSE; \
		double start = log ? systimer_gettime() : 0; \
		/* print name before and after so if crashes we know who to blame */  \
		/* print name both to minimize confusion for nested calls */ \
		const char* msg = message;   /* create error if message isn't a string */ \
		if (log) cpost("-> %s(%s)\n", #function_name, msg); \
		function_name(__VA_ARGS__); \
		if (log) cpost("<- %s(%s): %0.3f\n", #function_name, msg, systimer_gettime() - start); \
	}

#define STARTUP_CALL(function_name, ...) STARTUP_CALL_MESSAGE("", function_name, __VA_ARGS__)
	
END_USING_C_LINKAGE

#endif // #ifndef _EXT_POST_H_
