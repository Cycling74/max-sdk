This example contains three projects.  One builds a dynamically-linked library (DLL on Windows, or dylib on the Mac, we'll use DLL to refer to both of these).  The other two projects build Max externals that use the DLL.

In order to facilitate the distribution of your external, which will also require that you distribute your DLL, we recommend that you use the packages feature available in Max 6.1.  To do this, create a 'support' folder in your package's folder and place your DLL in that location.

On Windows this support folder is added to the path where the Max application searches for DLLs.

On the Mac things work a bit differently, and you may need to take some care when linking your binaries.


BACKGROUND: LINKING ON THE MAC

On the Mac, a dylib is a library that is loaded when needed.  In this case it will be loaded when your external's class is initialized (i.e. the main() function is called).

When you compile the dylib, you specify a path where it is to be installed.  This path is then written into the dylib itself.
When you compile your external, the path to the dylib will be read from the dylib and that path written into your external.
With only a couple of exceptions, the dylib must then be in the exact path that is linked into your external when it was built.
Without specifying an "install name" your dylib must be in a special system directory such as /usr/local/lib.

Frameworks are bundles that wrap a dylib.  They function the same way, and are subject to the same linking mechanism.
If no "install name" is specified then your framework must also be in a special system directory such as /Library/Frameworks.

Using these global locations is a hassle.
They make it more difficult to distribute your Max externals because an installer is required to put them in the special location, rather than just copying your package folder into ~/Max/Packages.
Installing to these locations requires Admin authentication, which isn't always available to potential users.
They also make it impossible to have multiple versions of your DLL on the same system (e.g. one for Max, one for a standalone app someone made, etc).

If you have a single external object using a framework or dylib, then you should include the dylib or framework in your object's mxo bundle.  Then you can use a special relative path, "@loader_path", to point to the DLL inside of your bundle.

If your bundle's structure is:

	myobject.mxo
		Contents
			Info.plist
			MacOS
				myobject
			PkgInfo
			Frameworks
				somelibrary.framework

Then you should set the install_name for the framework you build to "@loader_path/../Frameworks/somelibrary.framework".
In the latest versions of Xcode you set this in the "Dynamic Library Install Name" field of your target's settings.
Or you can specify the option directly to the linker if you are using a Makefile with:

LDFLAGS += -install_name "@loader_path/../Frameworks/somelibrary.framework" 

This option is fine when you have one external that accesses one DLL.  What happens when you have multiple externals needing to access that DLL?  You can't just bury the dylib or framework in your external's bundle.  In the packages folder we have provided a location for such dylibs or frameworks called "support".  Your dylib can have its install name set to this location as it does in our "mydll" example's Makefile:

LDFLAGS += -install_name "@loader_path/../../../../support/$(NAME).dylib" 


BACKGROUND: THIRD-PARTY LIBRARIES ON THE MAC

The discussion of setting the install name when linking your DLL presumes that you are compiling the DLL that will then be used by your object(s).
If you are using the framework of dylib that is already compiled then it is unlikely to have the install_name set correctly.
To examine the install_name of a DLL you can use the command-line program "otool" as in the the following two examples.


$ otool -l /Applications/Max\ 6.1/Max.app/Contents/Frameworks/MaxAudioAPI.framework/Versions/A/MaxAudioAPI
	Load command 3
          cmd LC_ID_DYLIB
      cmdsize 104
         name @executable_path/../Frameworks/MaxAudioAPI.framework/Versions/A/MaxAudioAPI (offset 24)

$ otool -l /usr/lib/libz.dylib 
	Load command 3
          cmd LC_ID_DYLIB
      cmdsize 48
         name /usr/lib/libz.1.dylib (offset 24)
		 

A lot more information will come pouring from the console for these commands.  We've reduced it to the part that is relevant to our needs.
Namely, the "Load Command" section labelled "LC_ID_DYLIB".  In the first case we are looking at the binary for a framework embedded inside of Max itself.  The path is specified relative to the application binary using @executable_path.  In the second case we look at a dylib that specifies an absolute path.

It is not recommended that you change either of these, as its possible to break things unintentionally.
So imagine you have a dylib with an install name of /usr/local/foo/bar.dylib.
Before you link your external to it, make a copy of it and then change the install name on the copy.
You do this with the command-line program called "install_name_tool".
For further reference see http://stackoverflow.com/questions/1304239/osx-changing-path-of-framework


IMPLEMENTATION

On Windows we compile our DLL with Visual Studio.

On the Mac, we could compile our DLL with Xcode.  Often the reason for linking to a DLL is to use a third-party library, which will typically ship with a Makefile rather than an Xcode project.  Using a Makefile will also make our settings more explicit.  So, for our DLL we compile using a Makefile.  In the terminal, "cd" to the directory of this example and run "make".

For convenience there is also a "mydll.xcodeproj".  This is an Xcode project that just calls "make" when building rather than using Xcode to manage the compile.


On Windows we should now have "mydll.dll" and on the Mac we should now have "mydll.dylib" in the sdk-build/support folder.  The sdk-build folder is structured as a Max package.

Now build the two externals as you would normally, with Xcode or Visual Studio.


IN USE

When you instantiate one of the objects for the first time, you should notice a post in the Max window that comes from the dll.  One object will increase a counter with each bang it receives.  Another object will report the current count.


