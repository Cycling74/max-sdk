/**
	@page chapter_files File Handling

	Max contains a cross-platform set of routines for handling files. These routines permit you to search for files, show file open and save dialogs, as well as open, read, write, and close them. The file API is based around a "path identifier" -- a number that describes the location of a file. When searching or reading a file, path identifiers can be either a folders or collectives. Path identifiers that are negative (or zero) describe actual folders in the computer's file system, while path identifiers that are positive refer to collectives.

	A basic thing you might want to do make your object accept the read message in a manner similar to existing Max objects. If the word read is followed by no arguments, a file dialog appears for the user to choose a file. If read is followed by an argument, your object will search for the file. If a file is found (or chosen), your object will open it and read data from it.

	First, make your object accept the read message. The simplest way to make the filename argument optional is to use the #A_DEFSYM argument type specifier. When the symbol argument is not present, Max passes your method the empty symbol.

@code
		class_addmethod(c, (method)myobject_read, "read", A_DEFSYM, 0);
@endcode

	The next requirement for any method that reads files is that it must defer execution to the low-priority thread, as shown in the following implementation, where the filename argument is passed as the symbol argument to defer.

@code
	void myobject_read(t_myobject *x, t_symbol *s)
	{
		defer(x, (method)myobject_doread, s, 0, NULL);
	}
@endcode

	The myobject_doread() function compares the filename argument with the empty symbol -- if the argument was not supplied, the open_dialog() is used, otherwise, we call locatefile_extended() to search for the file. This object looks for text files, so we use a four-character code 'TEXT' as our file type to either open or locate. File type codes define a set of acceptable extensions. The file max-fileformats.txt permits contains standard definitions, and you can add your own by creating a similar text file and placing it in the init folder inside the Cycling '74 folder.

@code
	void myobject_doread(t_myobject *x, t_symbol *s)
	{
		t_fourcc filetype = 'TEXT', outtype;
		short numtypes = 1;
		char filename[MAX_PATH_CHARS];
		short path;

		if (s == gensym("")) {		// if no argument supplied, ask for file
			if (open_dialog(filename, &path, &outtype, &filetype, 1))		// non-zero: user cancelled
				return;
		} else {
			strcpy(filename, s->s_name);	// must copy symbol before calling locatefile_extended
			if (locatefile_extended(filename, &path, &outtype, &filetype, 1)) {	// non-zero: not found
				object_error(x, "%s: not found", s->s_name);
				return;
			}
		}
		// we have a file
		myobject_openfile(x, filename, path);
	}
@endcode

	To open and read files, you can use the cross-platform sysfile API. Files can be opened using a filename plus path identifier. If successfully opened, the file can be accessed using a #t_filehandle. Note that "files" inside collective files are treated identically to regular files, with the exception that they are read-only.


	@section chapter_files_reading_text_files Reading Text Files

	First, we'll implement reading the text file whose name and path identifier are passed to myobject_openfile() using a high-level routine sysfile_readtextfile() specifically for reading text files that handles text encoding conversion for you. If you are reading text files, using this routine is strongly recommended since converting text encodings is unpleasant to say the least.

@code
	void myobject_openfile(t_myobject *x, char *filename, short path)
	{
		t_filehandle fh;
		char **texthandle;

		if (path_opensysfile(filename, path, &fh, READ_PERM)) {
			object_error(x, "error opening %s", filename);
			return
		}
		// allocate some empty memory to receive text
		texthandle = sysmem_newhandle(0);
		sysfile_readtextfile(fh, texthandle, 0, 0);		// see flags explanation below
		post("the file has %ld characters", sysmem_handlesize(texthandle));
		sysfile_close(fh);
		sysmem_freehandle(texthandle);
	}
@endcode

	In most situations, you will pass 0 for the final two arguments to sysfile_readtextfile(). The third argument specifies a maximum length to read, but if the value is 0, the entire file is read in, regardless of its size. The final argument is a set of flags specifying options for reading in the text. The options concern the conversion of line breaks, text encoding, and the ability to add a null character to the end of the data returned.

	Line breaks are converted on the basis of any line break flags. When reading text files, Max converts line breaks to "native" format, which is
	@code \r\n @endcode
	on Windows and
	@code \n @endcode
	on the Mac; this is the behavior you get if you either pass no line break flags or use #TEXT_LB_NATIVE. Other options include #TEXT_LB_MAC, #TEXT_LB_UNIX, or #TEXT_LB_PC.

	By default, text files are converted from their source encoding to UTF-8. If you do not want this conversion to occur, you can use the #TEXT_ENCODING_USE_FILE flag. This puts the burden on determining the encoding on you, which is probably not what you want. For example, the source text file might use UTF-16 encoding, which requires very different parsing than an 8-bit encoding.

	Finally, you can have the memory returned from sysfile_readtextfile() terminated with a NULL character if you use the #TEXT_NULL_TERMINATE flag.


	@section chapter_files_reading_data_files Reading Data Files

	To read data files where you do not want to do text encoding conversion or worry about line breaks, you can use the same technique shown above for text files, but write the myobject_openfile function using sysfile_read() instead of sysfile_readtextfile(). This example shows how to read an entire file into a single block of memory.

@code
	void myobject_openfile(t_myobject *x, char *filename, short path)
	{
		t_filehandle fh;
		char *buffer;
		long size;

		if (path_opensysfile(filename, path, &fh, READ_PERM)) {
			object_error(x, "error opening %s", filename);
			return
		}
		// allocate memory block that is the size of the file
		sysfile_geteof(fh, &size);
		buffer = sysmem_newptr(size);

		// read in the file
		sysfile_read(fh, &size, buffer);

		sysfile_close(fh);

		// do something with data in buffer here

		sysmem_freeptr(buffer);		// must free allocated memory
	}
@endcode


	@section chapter_files_writing_files Writing Files

	Some Max objects respond to the write message to save data into a file. If there is no argument present after the word write, a save file dialog is shown and the user specifies a file name and location. If an argument is present, it can either specify a complete path name or a filename. In the filename case, the file is written to the current "default" directory, which is the location where a patcher was last opened. In the full pathname case, the file is written to the location specified by the pathname.

	Here's how to implement this behavior. We'll show how to handle the message arguments, then provide text and data file writing examples.

	Message and argument handling is very similar to the way we implemented the read message above, including the use of deferred execution.

@code
	class_addmethod(c, (method)myobject_write, "write", A_DEFSYM, 0);

	void myobject_write(t_myobject *x, t_symbol *s)
	{
		defer(x, (method)myobject_dowrite, s, 0, NULL);
	}
@endcode

	The myobject_dowrite() function compares the filename argument with the empty symbol -- if the argument was not supplied, saveasdialog_extended() is used to obtain the user's choice for filename and location. Our first example looks for text files, so we use a four-character code 'TEXT' as our file type for saving. File type codes define a set of acceptable extensions. The file max-fileformats.txt permits contains standard definitions, and you can add your own by creating a similar text file and placing it in the init folder inside the Cycling '74 folder.

@code
	void myobject_dowrite(t_myobject *x, t_symbol *s)
	{
		long filetype = 'TEXT', outtype;
		short numtypes = 1;
		char filename[512];
		short path;

		if (s == gensym("")) {		// if no argument supplied, ask for file
			if (saveasdialog_extended(filename, &path, &outtype, &filetype, 1))		// non-zero: user cancelled
				return;
		} else {
			strcpy(filename, s->s_name);
			path = path_getdefault();
		}
		myobject_writefile(x, filename, path);
	}
@endcode

	Here is the text file variant of myobject_writefile() using the high-level sysfile_writetextfile() routine. We just write a sentence as our "text file" but your object will presumably have some text data stored internally that it will write. The buffer passed to sysfile_writetextfile() must be NULL-terminated, and will be assumed to be UTF-8 encoded.

	Note that path_createsysfile() can accept a full path in the filename argument, in which case, the path argument is ignored. This means your object's write message can either accept a filename or full pathname and you needn't do anything special to accept both.

@code
	void myobject_writefile(t_myobject *x, char *filename, short path)
	{
		char *buf = "write me into a file";
		long err;
		t_filehandle fh;

		err = path_createsysfile(filename, path, 'TEXT', &fh);
		if (err)
			return;
		err = sysfile_writetextfile(fh, &buf, TEXT_LB_NATIVE);
		sysfile_close(fh);
	}
@endcode

	Here is a data file variant of myobject_writefile(). It writes a small buffer of ten numbers to a file.

@code
	void myobject_writefile(t_myobject *x, char *filename, short path)
	{
		char *buf[10];
		long count, i;
		long err;
		t_filehandle fh;

		// create some data

		for (i = 0; i < 10; i++)
			buf[i] = i + 1;

		count = 10;

		err = path_createsysfile(filename, path, 'TEXT', &fh);
		if (err)
			return;
		err = sysfile_write(fh, &count, buf);
		sysfile_close(fh);
	}
@endcode


*/
