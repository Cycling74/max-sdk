#ifndef _EXT_SYSFILE_H_
#define _EXT_SYSFILE_H_


typedef struct _filestruct t_filestruct; 

/** A t_filehandle is a cross-platform way of referring to an open file.
	It is an opaque structure, meaning you don’t have access to the individual 
	elements of the data structure. You can use a t_filehandle only 
	with the file routines in the Sysfile API. Do not use other platform- 
	specific file functions in conjunction with these functions. 
	The perm parameter can be either READ_PERM, WRITE_PERM, or RW_PERM.

	@ingroup files */
typedef t_filestruct *t_filehandle;

/** Modes used by sysfile_setpos()
	@ingroup files */
typedef enum {
	SYSFILE_ATMARK = 0,			///< ?
	SYSFILE_FROMSTART = 1,		///< Calculate the file position from the start of the file.
	SYSFILE_FROMLEOF = 2,		///< Calculate the file position from the logical end of the file.
	SYSFILE_FROMMARK = 3		///< Calculate the file position from the current file position.
} t_sysfile_pos_mode;


typedef enum {
	SYSFILE_SUBFILE = 1,
	SYSFILE_HANDLE = 2,		// can call sysmem_freehandle on close
	SYSFILE_RESOURCE = 4,	// can call ReleaseResource on close
	SYSFILE_MEMORY = 6,		// either a handle or a resource
	SYSFILE_RESFILE = 8,	// a resource file
	SYSFILE_OPENRESFILE = 16,	// an already-open resource file
	SYSFILE_EXTERNALDATA = 32,	// don't do anything to f_data
	SYSFILE_JUSTAPOINTER = 64,	// f_data is really a 4-byte pointer
	SYSFILE_EXTERNALDATA_CANWRITE = 128,  // can sysfile_write() to external data
	SYSFILE_EXTERNALDATA_CANGROW = 256,	  // if write goes beyond data, grow the handle (not valid with SYSFILE_JUSTAPOINTER)
	SYSFILE_EXTERNALDATA_FREE = 512,		  // data is external, but free it anyway on file close 
	SYSFILE_EXTERNALDATA_LATEFREE = 1024
} t_sysfile_flags;

/** Flags used reading and writing text files.
	@ingroup files */
typedef enum {
	TEXT_LB_NATIVE =			0x00000001L,	///< Use the linebreak format native to the current platform.
	TEXT_LB_MAC =				0x00000002L,	///< Use Macintosh line breaks
	TEXT_LB_PC =				0x00000004L,	///< Use Windows line breaks
	TEXT_LB_UNIX =				0x00000008L,	///< Use Unix line breaks
	TEXT_LB_MASK = 0x0000000FL,				// can use to mask out non-LB related flags
	TEXT_ENCODING_USE_FILE =	0x00000100L,	///< If this flag is not set then the encoding is forced to UTF8
	TEXT_NULL_TERMINATE	=		0x00000200L		///< Terminate memory returned from sysfile_readtextfile() with a NULL character
} t_sysfile_text_flags; 

BEGIN_USING_C_LINKAGE

/**	Close a file opened with sysfile_open().
	This function is similar to FSClose() or fclose(). 
	It should be used instead of system-specific file closing routines in order to make max external 
	code that will compile cross-platform. 
	
	@ingroup	files
	@param	f	The #t_filehandle structure of the file the user wants to close. 
	@return		An error code.
*/
t_max_err sysfile_close(t_filehandle f);


/**	Read a file from disk.
	This function is similar to FSRead() or fread(). It should be used instead of 
	these functions (or other system-specific file reading routines) in order 
	to make max external code that will compile cross-platform. It reads 
	"count" bytes from file handle at current file position into "bufptr". 
	The byte count actually read is set in "count", and the file position is 
	updated by the actual byte count read.

	@ingroup files
	@param	f		The #t_filehandle structure of the file the user wants to open.
	@param	count	Pointer to the number of bytes that will be read from the file at the current file position. 
					The byte count actually read is returned to this value.
	@param	bufptr	Pointer to the buffer that the data will be read into.
	@return			An error code.
*/
t_max_err sysfile_read( t_filehandle f, t_ptr_size *count, void *bufptr);  


/**	Read the contents of a file into a handle.
	@ingroup files
	@param	f	The open #t_filehandle structure to read into the handle.
	@param	h	The address of a handle into which the file will be read.
	@return 	An error code.
	@remark		You should free the pointer, when you are done with it, using sysmem_freehandle().
*/
t_max_err sysfile_readtohandle(t_filehandle f, char ***h);


/**	Read the contents of a file into a pointer.
	@ingroup files
	@param	f	The open #t_filehandle structure to read into the handle.
	@param	p	The address of a pointer into which the file will be read.
	@return 	An error code.
	@remark		You should free the pointer, when you are done with it, using sysmem_freeptr().
*/
t_max_err sysfile_readtoptr(t_filehandle f, char **p);


/** Write part of a file to disk.
	This function is similar to FSWrite() or fwrite(). It should be used instead 
	of these functions (or other system-specific file reading routines) in 
	order to make max external code that will compile cross-platform. The 
	function writes "count" bytes from "bufptr" into file handle at current 
	file position. The byte count actually written is set in "count", and the
	file position is updated by the actual byte count written.

	@ingroup files
	@param	f		The t_filehandle structure of the file to which the user wants to write.
	@param	count	Pointer to the number of bytes that will be written to the file at the current file position. 
					The byte count actually written is returned to this value.
	@param	bufptr	Pointer to the buffer that the data will be read from. 
	@return			An error code.
*/
t_max_err sysfile_write(t_filehandle f, t_ptr_size *count, const void *bufptr);  


/**	Set the size of a file handle.
	This function is similar to and should be used instead of SetEOF(). 
	The function sets the size of file handle in bytes, specified by �“logeof?. 
	
	@ingroup		files
	@param	f		The file's #t_filehandle structure.
	@param	logeof	The file size in bytes.
	@return			An error code.
*/
t_max_err sysfile_seteof(t_filehandle f, t_ptr_size logeof);


/**	Get the size of a file handle.
	This function is similar to and should be used instead of GetEOF().
	The function gets the size of file handle in bytes, and places it in �“logeof?. 
	
	@ingroup		files
	@param	f		The file's #t_filehandle structure.
	@param	logeof	The file size in bytes is returned to this value.
	@return			An error code.
*/
t_max_err sysfile_geteof(t_filehandle f, t_ptr_size *logeof);


/**	Set the current file position of a file handle.
	This function is similar to and should be used instead of SetFPos(). 
	It is used to set the current file position of file handle to by the given 
	number of offset bytes relative to the mode used, as defined in #t_sysfile_pos_mode.
	
	@ingroup		files
	@param	f		The file's #t_filehandle structure.
	@param	mode	Mode from which the offset will be calculated, as defined in #t_sysfile_pos_mode.
	@param	offset	The offset in bytes relative to the mode.
	@return			An error code.
*/
t_max_err sysfile_setpos(t_filehandle f, t_sysfile_pos_mode mode, t_ptr_int offset);


/**	Get the current file position of a file handle.
	This function is similar to and should be used instead of GetFPos(). 
	The function gets the current file position of file handle in bytes, and places it in "filepos". 
	
	@ingroup		files
	@param	f		The file's #t_filehandle structure.
	@param	filepos	The address of a variable to hold the current file position of file handle in bytes. 
	@return			An error code.
*/
t_max_err sysfile_getpos(t_filehandle f, t_ptr_size *filepos);


/**	Copy the contents of one file handle to another file handle.
	@ingroup files
	@param	src		The file handle from which to copy.
	@param	dst		The file handle to which the copy is written.
	@param	size	The number of bytes to copy.  If 0 the size of src will be used.
	@return			An error code.
*/
t_max_err sysfile_spoolcopy(t_filehandle src, t_filehandle dst, t_ptr_size size);


// private
void sysfile_setobject(t_filehandle f, t_object *o);



/**	Read a text file from disk.
	This function reads up to the maximum number of bytes given by 
	maxlen from file handle at current file position into the htext 
	handle, performing linebreak translation if set in flags.

	@ingroup		files
	@param	f		The #t_filehandle structure of the text file the user wants to open.
	@param	htext	Handle that the data will be read into.
	@param	maxlen	The maximum length in bytes to be read into the handle. 
					Passing the value 0L indicates no maximum (i.e. read the entire file).
	@param	flags	Flags to set linebreak translation as defined in #t_sysfile_text_flags.
	@return			An error code.
*/
t_max_err sysfile_readtextfile(t_filehandle f, t_handle htext, t_ptr_size maxlen, t_sysfile_text_flags flags);


/**	Write a text file to disk.
	This function writes a text handle to a text file performing linebreak 
	translation if set in flags.

	@ingroup		files
	@param	f		The #t_filehandle structure of the text file to which the user wants to write.
	@param	htext	Handle that the data that will be read from.
	@param	flags	Flags to set linebreak translation as defined in #t_sysfile_text_flags.
	@return			An error code.
*/
t_max_err sysfile_writetextfile(t_filehandle f, t_handle htext, t_sysfile_text_flags flags);


/**	Create a #t_filehandle from a pre-existing handle.
	@ingroup	files	
	@param		h		A handle for some data, data is *not* copied and *not* freed on file close. 
	@param		flags	Pass 0 (additional flags are private).
	@param		fh		The address of a #t_filehandle which will be allocated.
	@return				An error code.
*/
t_max_err sysfile_openhandle(char **h, t_sysfile_flags flags, t_filehandle *fh);


/**	Create a #t_filehandle from a pre-existing pointer.
	@ingroup	files	
	@param		p		A pointer to some data. Data is *not* copied and *not* freed on file close.
	@param		length	The size of p.
	@param		flags	Pass 0 (additional flags are private).
	@param		fh		The address of a #t_filehandle which will be allocated.
	@return				An error code.
*/
t_max_err sysfile_openptrsize(char *p, t_ptr_size length, t_sysfile_flags flags, t_filehandle *fh);

END_USING_C_LINKAGE

#endif // _EXT_SYSFILE_H_

