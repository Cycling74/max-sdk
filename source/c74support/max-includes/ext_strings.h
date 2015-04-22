#ifndef _EXT_STRINGS_H_
#define _EXT_STRINGS_H_

BEGIN_USING_C_LINKAGE

#ifndef strncpy_zero
/**	Copy the contents of one string to another, in a manner safer than the standard strcpy() or strncpy().
 	This is the prefered function to use for this operation in Max.
	@ingroup misc
	@param	dst		The destination string (already allocated) for the copy.
	@param	src		The source string that will be copied.
	@param	size	The number of chars allocated to the dst string.
*/
char *strncpy_zero(char *dst, const char* src, long size);
#endif


/**	Concatenate the contents of one string onto the end of another, 
	in a manner safer than the standard strcat() or strncat().
 	This is the prefered function to use for this operation in Max.
	@ingroup misc
	@param	dst		The destination string onto whose end the src string will be appended.
	@param	src		The source string that will be copied.
	@param	size	The number of chars allocated to the dst string.
*/
char *strncat_zero(char *dst, const char* src, long size);


/**	Copy the contents of a string together with value substitutions, 
	in a manner safer than the standard sprintf() or snprintf().
 	This is the prefered function to use for this operation in Max.
	@ingroup misc
	@param	buffer	The destination string (already allocated) for the copy.
	@param	count	The number of chars allocated to the buffer string.
	@param	format	The source string that will be copied, which may include sprintf() formatting codes for substitutions.
	@param	...		An array of arguments to be substituted into the format string.
*/
int snprintf_zero(char *buffer, size_t count, const char *format, ...);


#if    TARGET_API_MAC_CARBON
#define CtoPstr(x) CopyCStringToPascal((const char *)(x),(unsigned char *)(x))
#define PtoCstr(x) CopyPascalStringToC((ConstStr255Param)(x),(char *)(x))
#endif // TARGET_API_MAC_CARBON

#define SPRINTF_MAXLEN 4096

// Legacy

void ctopcpy(unsigned char *p1, char *p2);
void ptoccpy(char *p1, unsigned char *p2);
void pstrcpy(unsigned char *p2, unsigned char *p1);


END_USING_C_LINKAGE

#endif // _EXT_STRINGS_H_
