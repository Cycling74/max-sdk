/*
 *  obstring.h
 *
 *  Copyright 2006 Cycling '74. All rights reserved.
 *
 */

#ifndef _EXT_OBSTRING_H_
#define _EXT_OBSTRING_H_

BEGIN_USING_C_LINKAGE

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif


/** 
	The string object. This struct is provided for debugging convenience, 
	but should be considered opaque and is subject to change without notice. 

	@ingroup string
*/
typedef struct _string
{
	t_object		s_obj;
	char			*s_text;
	long			s_size;		// number of bytes allocated
} t_string;  

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif


/**
	Create a new string object.
	@ingroup string
	@param	psz		Pointer to a C-string that will be copied to memory internal to this string object instance.
	@return			The new string object instance pointer.
*/
t_string* string_new(const char *psz);


/**
	Fetch a pointer to a string object's internal C-string.
	@ingroup string
	@param	x		The string object instance.
	@return			A pointer to the internally maintained C-string.
*/
const char* string_getptr(t_string *x);

		
/**
	Reserve additional memory for future string growth.
	@ingroup string
	@param	x			The string object instance.
	@param	numbytes	The total number of bytes to allocate for this string object.
 */
void string_reserve(t_string *x, long numbytes);


/**
	Append a C-string onto the existing string maintained by a #t_string object.
	Memory allocation for the string will grow as needed to hold the concatenated string.
 
	@ingroup string
	@param	x			The string object instance.
	@param	s			A string to append/concatenate with the existing string.
 */
void string_append(t_string *x, const char *s);

		
/**
	Shorten a string by eliminating N characters from the end.
 
	@ingroup string
	@param	x			The string object instance.
	@param	numchars	The number of characters to chop from the end of the string.
 */
void string_chop(t_string *x, long numchars);


// TODO: This object has a number of additional methods exposed via Max's messaging interface

END_USING_C_LINKAGE

#endif //#ifndef _EXT_OBSTRING_H_
