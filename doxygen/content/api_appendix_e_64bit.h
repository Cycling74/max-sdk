/**
	@page chapter_appendix_e Appendix: Updating Externals for Max 6.1 (x64 architecture)


	@section chapter_appendix_e_background Background

	The Max 6.0.x application binary, and the external objects and libraries it uses, are compiled for the i386 processor architecture.
	This architecture uses 32-bit memory addressing, meaning that the size of a pointer is 32 bits (or 4 bytes).

	Max 6.1 introduces support for the x86_64 (or x64) architecture which uses 64-bit (8 bytes) memory addressing.
	Among the benefits are the ability to use more than 2 GB of memory in Max.
	Additionally, the size of the #t_atom is 8-bytes on x64, meaning that double-precision floating pointer numbers can be represented.

	For backwards compatibility, Max 6.1 also continues to be distributed as a 32-bit application binary.
	On the Windows platform the 32-bit and 64-bit applications are distributed separately, as are the external objects you create for them.
	On the Mac platform a Universal Binary (or "FAT" binary) is distributed containing both the 32-bit and 64-bit versions in the same dynamically-loaded library.

	All externals on the Mac remain bundles using the ".mxo" filename extension.

	32-bit externals on Windows remain DLLs using the ".mxe" filename extension.

	64-bit externals on Windows are still DLLs but use a new ".mxe64" filename extension.


	@subsection chapter_appendix_e_types New Types

	In addition to the change of size in a pointer, there are some additional changes for 64-bit.
	For example, a "long" integer for 32-bit targets is 4 bytes on both the Mac and Windows.
	However, a "long" integer for 64-bit targets is 4 bytes on Windows but 8 bytes (the size of a pointer) on the Mac!

	To facilitate cross platform code that is independent of these platform differences, the Max 6.1 API defines some new types used throughout the SDK.

	Types of fixed size:

	@code
		t_int8
		t_uint8
		t_int16
		t_uint16
		t_int32
		t_uint32
		t_int64
		t_uint64
	@endcode


	Types of architecture-dependent size:

	@code
		t_ptr_int : an int that is the same size as a pointer
		t_ptr_uint : an unsigned int that is the same size as a pointer
		t_atom_long : the type that is an A_LONG in an atom (32-bits on i386; 64-bits on x64)
		t_atom_float : the type that is an A_FLOAT in an atom (float on i386; double on x64)
	@endcode

	Types for specific contexts:

	@code
		t_filepath : i.e. path/vol in file APIs identifying a folder
		t_fourcc : use for type codes in locatefile_extended(), file dialogs, etc. to represent a four char code
		t_getbytes_size : if you are using getbytes() and freebytes(), use this type to represent the size of the memory
	@endcode



	@section chapter_appendix_e_projects Xcode and Visual Studio Projects

	For new objects, you can base projects on those in the new SDK.
	To update existing projects you will need to make a few changes to your project settings.


	@subsection chapter_appendix_e_projects_mac Mac / Xcode

	Max 6.1 on the Mac no longer uses the intermediary MaxAPI.framework for linking.
	Instead, the linking is handled at runtime and the symbols are checked using special flags to the linker.
	To update an existing project:

	-# remove references to the MaxAPI.framework
	-# update the .xcconfig file on which the project is based with the .xcconfig file in the new Max SDK
	-# in your target's build settings find the "Other Linker Flags" and set it to "$(C74_SYM_LINKER_FLAGS)"
	-# in your target's build settings find the "Architectures" and set it to "i386 x86_64"


	@subsection chapter_appendix_e_projects_win Windows / Visual Studio

	In order to build for x64 with Visual Studio 2008, you must have the "Pro" version.
	The free "Express" version will not work.
	The "Express" versions of Visual Studio 2010 and 2012 do work (2012 is recommended).

	Due to bugs in Visual Studio 2008, it is really difficult to update an existing project.
	Instead, it is recommended to simply create a new Visual Studio project based on an existing example.
	For Visual Studio 2008 use the "vcproj" files.  For Visual Studio 2010 and 2012 use the "vcxproj" files.

	-# choose a relevant starting point, e.g., the "dummy" example project
	-# copy it to the folder your old project was in, rename it
	-# open it in a text editor such as "sublime text 2"
	-# do a find/replace for all instances of the text "dummy" changing it to your object's name
	-# open the Visual Studio project and build
		you can choose either "Win32" or "x64" from the platform drop-down menu in the IDE



	@section chapter_appendix_e_code Changes to Code


	@subsection chapter_appendix_e_code_atoms Atoms

	Any assumptions in your code about the size of a #t_atom or the size of its members should be reviewed.
	When setting or getting values to and from atoms you should use the types #t_atom_long and #t_atom_float as appropriate.


	@subsection chapter_appendix_e_code_returnvals Return Values

	All methods which return a value must return a pointer-sized value, e.g., #t_ptr_int, #t_ptr_uint, #t_max_err, etc.


	@subsection chapter_appendix_e_code_files File Code

	File access in Max involves several areas subject to either required or suggested update.

	A path in Max has traditionally been represented with a short int; it is recommened to now use the new #t_filepath type.

	File types in Max are represented using four char codes.
	Traditionally these have been defined using variables of type "long", which is now problematic.
	This is a 4-byte type but the long on the Mac for x64 is 8-bytes.
	These must be updated to use the new #t_fourcc type.


	@subsection chapter_appendix_e_gotchas Miscellaneous Gotchas

	Look for any %ld or %lu strings in sprintf() or related formatting functions.


	@section chapter_appendix_e_scenarios Common Scenarios

	@subsection chapter_appendix_e_scenarios_long "Long" integers

	One of biggest areas we've had to address is the use of the long datatype.
	The reason for this is that under 64bit windows a long integer is 32 bits and under 64bit OS X (and Unix),
	a long is a 64 bit integer.

	To assist in this process, we have a the new data types documented above.
	We'll distinguis these from what we are calling a "platform long".

	This platform long discrepancy can lead to all sorts of problems which are outlined
	with a brief statement of the problem scenario, and our recommended fix with types:


	<b>Problem:  long integers as A_LONG/A_DEFLONG method arguments (this includes your object constructors)</b>

	Solution: type your A_LONG/A_DEFLONG methods' function signatures to use the t_atom_long in place of long


	<b>Problem: long integers as A_CANT method arguments called only through object_method()</b>

	Solution: either redefine your A_CANT method's arguments to t_atom_long, or define your type as A_DIRECT,
	and make use of the object_method_direct() macro, passing in a function prototype to the macro
	(also see under floating point how this is required for anything which previously was A_CANT with floating point values).
	Technically many of these will still work properly due to the nature of how integers are passed on the stack under x64,
	without any change, it is still best practice.


	<b>Problem: long integers being used to store pointers as integer values either for pointer arithmetic, attributes, or other situations.</b>

	Solution: use t_atom_long or even better t_ptr_uint (for pointer sized unsigned integer) or the actual pointer type.


	<b>Problem: long integers as four character codes for filetypes (t_fourcc) which applies to locatefile_extended and path functions and friends</b>

	Solution: Use t_foucc inplace of long, for anywhere you are using filetype codes.


	<b>Problem: long integers as return values for functions called via object_method()</b>

	Solution: These should always return a t_atom_long or other pointer sized integer


	<b>Problem: long integers passed as pointers into functions like dictionary_getlong() which are now prototyped to take a t_atom_long *</b>

	Solution: Use a t_atom_long value, and pass a pointer to it.
	A cast from a platform long *to  a t_atom_long * is not safe.


	<b>Problem: long integers for performing bitwise manipulation of 32bit floating point values including byteswapping</b>

	Solution: Use t_int32/t_uint32


	There are many cases where it is safe to use long integers, and we have continued to use them in our code.
	Below are the scenarios where they are okay and in several cases required.
	This might provide some confusion at some points, but hopefully it makes the porting process a little bit easier,
	allowing more code to remain unchanged.


		-  Attributes defined as _sym_long should remain a platform long.
			If you need to have a t_atom_long attribute, you will need to use the new atom_long attribute type.
			This is probably the most confusing aspect of porting to 64bit and a very real ambiguity of the word "long".
			Unfortunately, having to balance the difficulties of porting with the clarity of API, this is something we felt necessary to do.
		-  Attribute getters/setters should still use the long type for ac. this is especially important for getters which are passed a pointer to a platform long in the ac value.
		-  A_GIMME methods may still use the long type for ac without issues


	@subsection chapter_appendix_e_scenarios_float Floating point values

	For A_FLOAT/A_DEFFLOAT function signatures, you should always use double as is currently recommended in the Max SDK.
	You should not use the new t_atom_float dataype.
	(this includes your object constructors)

	For A_CANT functions with floating point arguments that currently use object_method().
	You will need to use object_method_direct() or pass in pointers to the floating point values
	(which is safe as it is a pointer sized integer).
	It is no longer possible to pass floats through object_method() or the many functions like it
	(linklist_methodall(), hashtab_methodall(), etc.)

	Attributes are already defined in terms of their bitsize float32 or float 64.
	If you wish for your attribute to make use of the new atom support for double preceision.
	You will want to change your struct definition, as well as your attribute constructor to be a double (_sym_float64).
	There isn't currently a t_atom_float attribute type like we've added for long.


	@subsection chapter_appendix_e_scenarios_apple Deprecated Apple types

	like Byte/Boolean/Point/etc

	Use the t_byte/t_bool/t_point/etc types instead.


	@section chapter_appendix_e_misc Additional Miscellaneous Changes

	The old 32-bit 'dsp' (and perform) methods are no longer supported as of Max 6.1.
	They must be updated as per @ref chapter_appendix_d_msp64 .


	@section chapter_appendix_e_resources Additional Resources

	-  http://www.viva64.com/en/a/0004/
	-  https://developer.apple.com/library/mac/#documentation/Cocoa/Conceptual/Cocoa64BitGuide/64BitChangesCocoa/64BitChangesCocoa.html
	-  https://developer.apple.com/library/mac/#documentation/Carbon/Conceptual/Carbon64BitGuide/OtherAPIChanges/OtherAPIChanges.html
	-  http://msdn.microsoft.com/en-us/magazine/cc300794.aspx


**/
