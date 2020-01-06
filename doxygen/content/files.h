/**
	@defgroup files Files and Folders

	These routines assist your object in opening and saving files,
	as well as locating the user’s files in the Max
	search path. There have been a significant number of changes to these
	routines (as well as the addition of many functions), so some history
	may be useful in understanding their use.

	Prior to version 4, Max used a feature of Mac OS 9 called "working
	directories" to specify files. When you used the locatefile() service
	routine, you would get back a file name and a volume number. This
	name (converted to a Pascal string) and the volume number could be
	passed to FSOpen() to open the located file for reading. The
	open_dialog() routine worked similarly.

	In Mac OSX, working directories are no longer supported. In addition,
	the use of these "volume" numbers makes it somewhat difficult to port
	Max file routines to other operating systems, such as Windows XP,
	that specify files using complete pathnames (i.e.,
	"C:\dir1\dir2\file.pat").

	However, it is useful to be able to refer to the path and the name of the
	file separately. The solution involves the retention of the
	volume number (now called Path ID), but with a platform-
	independent wrapper that determines its meaning. There are now calls
	to locate, open, and choose files using C filename strings and Path IDs,
	as well as routines to convert between a "native" format for specifying
	a file (such as a full pathname on Windows or an FSRef on the
	Macintosh) to the C string and Path ID.
	As of Max version 5 FSSpecs, long ago deprecated by Apple, are no longer supported.

	Now that paths in Max have changed to use the slash style, as opposed
	to the old Macintosh colon style (see the Max 4.3 documentation for a
	description of the file path styles), there is one function in particular
	that you will find useful for converting between the various ways paths
	can be represented, including operating system native paths. This
	function is path_nameconform(). Note that for compatibility purposes
	Path API functions accept paths in any number of styles, but will
	typically return paths, or modify paths inline to use the newer slash style.
	In addition to absolute paths, paths relative to the Max Folder, the
	"Cycling '74" folder and the boot volume are also supported. See the
	conformpath.help and ext_path.h files for more information on the
	various styles and types of paths. See the "filebyte" SDK example
	project for a demonstration of how to use the path functions to convert
	a Max name and path ref pair to a Windows native path for use with
	CreateFile().

	There are a large number of service routine in the Max 4 kernel that
	support files, but only a handful will be needed by most external
	objects.  In addition to the descriptions that follow, you should consult
	the movie, folder and filedate examples included with the SDK.


	@section sysfile_api The Sysfile API

	The Sysfile API provides the means of reading and writing files opened
	by path_createsysfile() and similar. These functions all make use of an
	opaque structure, #t_filehandle. See the path functions
	path_opensysfile() and path_createsysfile() described earlier
	in this chapter for more information. The Sysfile API is relatively
	similar to parts of the old Macintosh File Manager API, and not too
	different from Standard C library file functions. The "filebyte" example
	project in the SDK shows how to use these functions to read from a
	file. It is not safe to mix these routines with other file routines (e.g.
	don’t use fopen() to open a file and sysfile_close() to close it).

	In addition to being able to use these routines to write cross-platform
	code in your max externals, another advantage of the Sysfile API is that
	it is able to read files stored in the collective file format on
	both Windows XP and Mac OSX.


	@section filebyte_example Example: filebyte (notes from the IRCAM workshop)

	@subsection paths Paths

	- A number that specifies a file location
	- Returned by locatefile_extended() and open_dialog()
	- Supply a path when opening a file with path_opensysfile()
	- Can convert path to and from pathname

	@subsection filehandle t_filehandle

	- Returned by path_opensysfile
	- Refers to an open file you want to read or write using sysfile_read / sysfile_write
	- Could refer to a file in a collective

	@subsection filenames File Names

	- C string
	- Max 5 filenames are UTF-8
	- Max 5 supports long (unicode) filenames on both Mac and Windows

	@subsection filepathname File Path Names

	- Max uses a platform-independent path string format: volume:/path1/path2/filename returned by path_topathname
	- Can convert to platform-specific format using path_nameconform (not needed if using path_opensysfile)
	- Platform-independent format must be used with path_frompathname



	@section fileusage Collectives and Fileusage

	Use the fileusage routines to add files to a collective when a user chooses to build a collective.
	Your object can respond to a "fileusage" message, which is sent by Max when the collective builder
	is building a collective using the following:
	@code
	class_addmethod(c, (method)my_fileusage,	"fileusage", A_CANT, 0L);
	@endcode
	Where my file usage has the prototype:
	@code
	void my_fileusage(t_myObject *x, void *w);
	@endcode

	Then you can use fileusage_addfile() to add any requisite files to the collective.



	@section filewatchers Filewatchers

	Your object can watch a file or folder and be notified of changes.
	Use filewatcher_new(), filewatcher_start(), and filewatcher_stop() to implement this functionality.
	You may wish to use filewatchers sparingly as they can potentially incur computational overhead in the background.

*/

