#ifndef _EXT_ATOMBUF_H_
#define _EXT_ATOMBUF_H_

/** The atombuf struct provides a way to pass a collection of atoms.
	@ingroup atombuf
*/
typedef struct atombuf {
	long a_argc;			///< the number of atoms
	t_atom a_argv[1];		///< the first of the array of atoms
} t_atombuf;

// atombuf functions

BEGIN_USING_C_LINKAGE

/**
	Use atombuf_new() to create a new Atombuf from an array of t_atoms.
	
	@ingroup atombuf
	@param	argc	Number of t_atoms in the argv array. May be 0.
	@param	argv	Array of t_atoms. If creating an empty Atombuf, you may pass 0.
	@return			atombuf_new() create a new #t_atombuf and returns a pointer to it. 
					If 0 is returned, insufficient memory was available.
*/
void *atombuf_new(long argc, t_atom *argv);


/**
	Use atombuf_free() to dispose of the memory used by a #t_atombuf.

	@ingroup atombuf
	@param	x	The #t_atombuf to free.
*/
void atombuf_free(t_atombuf *x);


/**
	Use atombuf_text() to convert text to a #t_atom array in a #t_atombuf.
	To use this routine to create a new Atombuf from the text buffer, first 
	create a new empty t_atombuf with a call to atombuf_new(0,NULL).
		
	@ingroup atombuf
	@param	x		Pointer to existing atombuf variable. 
					The variable will be replaced by a new Atombuf containing the converted text.
	@param	text	Handle to the text to be converted. It need not be zero-terminated.
	@param	size	Number of characters in the text.
*/
void atombuf_text(t_atombuf **x, char **text, long size);

short atombuf_totext(t_atombuf *x, char **text, long *size);
short atombuf_count(t_atombuf *x);
void atombuf_set(t_atombuf *x, long start, long num);
long atombuf_replacepoundargs(t_atombuf *x, long argc, t_atom *argv);

END_USING_C_LINKAGE

#endif // #ifndef _EXT_ATOMBUF_H_
