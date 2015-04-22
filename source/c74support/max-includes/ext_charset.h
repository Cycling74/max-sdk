/*
 *  charset.h
 *
 *  Created by Jeremy Bernstein on 24.05.06.
 *  Copyright 2006 Cycling '74. All rights reserved.
 *
 */

#ifndef _EXT_CHARSET_H_
#define _EXT_CHARSET_H_

BEGIN_USING_C_LINKAGE

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif


/** The charset_converter object. This struct is provided for debugging convenience, 
	but should be considered opaque and is subject to change without notice. 

	@ingroup unicode
*/
typedef struct _charset_converter
{
	t_object 				ob;
	void					*conv;
	void					*src_encoding;
	void					*dst_encoding;
} t_charset_converter;


/**	A convenience function that simplifies usage by wrapping the other charset functions.
	@ingroup unicode
	
	@param	src_encoding	The name encoding of the input.
	@param	in				The input string.
	@param	inbytes			The number of bytes in the input string.
	@param	dest_encoding	The name of the encoding to use for the output.
	@param	out				The address of a char*, which will be allocated and filled with the string in the new encoding.
	@param	outbytes		The address of a value that will hold the number of bytes long the output is upon return.
	@return					A Max error code.
	@remark					Remember to call sysmem_freeptr(*out) to free any allocated memory.
*/
t_max_err charset_convert(t_symbol *src_encoding, const char *in, long inbytes, t_symbol *dest_encoding, char **out, long *outbytes); 


/**	Convert a UTF8 C-String into a 16-bit-wide-character array.
	@ingroup unicode
	@param	s		The string to be converted to unicode.
	@param	outlen	The address of a variable to hold the size of the number of chars 
					but does not include the NULL terminator in the count.
	@return			A pointer to the buffer of unicode (wide) characters.
*/
unsigned short *charset_utf8tounicode(char *s, long *outlen);


/** Convert a 16-bit-wide-character array into a UTF C-string.
	Accepts either null termination, or not (len is zero in the latter case).
	@ingroup unicode
	@param	s		An array of wide (16-bit) unicode characters.
	@param	len		The length of s.	
	@param	outlen	The address of a variable to hold the size of the number of chars 
					but does not include the NULL terminator in the count.
	@return			A UTF8-encoded C-string.
	
*/
char *charset_unicodetoutf8(unsigned short *s, long len, long *outlen);


/**	Returns utf8 character count, and optionally bytecount.
	@ingroup unicode
	@param	utf8		The UTF-8 encoded string whose characters are to be counted.
	@param	bytecount	The address of a variable to hold the byte count on return.
						Pass NULL if you don't require the byte count.
	@return				The number of characters in the UTF8 string.
*/
long charset_utf8_count(char *utf8, long *bytecount);


/**	Returns utf8 character offset (positive or negative), and optionally byte offset.
	@ingroup unicode
	@param	utf8		A UTF-8 encoded string.
	@param	charoffset	The char offset into the string at which to find the byte offset.
	@param	byteoffset	The address of a variable to hold the byte offset on return.
						Pass NULL if you don't require the byte offset.
	@return				The character offset.
*/
char *charset_utf8_offset(char *utf8, long charoffset, long *byteoffset);


#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

END_USING_C_LINKAGE

#endif // _EXT_CHARSET_H_
