

/**
	@defgroup unicode Unicode

	@section unicode_character_encodings Character Encodings

	Currently supported character encodings
	- _sym_utf_8;		// utf-8, no bom
	- _sym_utf_16;		// utf-16, big-endian
	- _sym_utf_16be;	// utf-16, big-endian
	- _sym_utf_16le;	// utf-16, little-endian
	- _sym_iso_8859_1;	// iso-8859-1 (latin-1)
	- _sym_us_ascii;		// us-ascii 7-bit
	- _sym_ms_ansi;		// ms-ansi (microsoft code page 1252)
	- _sym_macroman;	// mac roman
	-
	- _sym_charset_converter;
	- _sym_convert;

	@subsection unicode_character_encodings_example Example Usage

	@code
	t_charset_converter *conv = object_new(CLASS_NOBOX, gensym("charset_converter"), ps_macroman, ps_ms_ansi);
	char *cstr = "Text to convert";
	char *cvtbuffer = NULL; // to-be-allocated data buffer
	long cvtbuflen = 0; // length of buffer on output

	if (conv) {
		// note that it isn't necessary to send in a 0-terminated string, although we do so here
		if (object_method(conv, gensym("convert"), cstr, strlen(cstr) + 1, &cvtbuffer, &cvtbuflen) == ERR_NONE) {
			// do something with the converted buffer
			sysmem_freeptr(cvtbuffer); // free newly allocated data buffer
		}
		object_free(conv); // free converter
	}
	@endcode

*/

