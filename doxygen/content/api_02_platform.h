/**
	@page chapter_platform Development System Information


	@section chapter_platform_building Building

	This SDK documentation is accompanied by a series of projects for compiling some example Max external objects.
	The details of how to build these projects are documented below in separate sections for the @ref chapter_platform_mac and @ref chapter_platform_win.

	When you build the example projects, the resulting Max external will be located in a folder called "externals" at the top level of the SDK package.
	This is located a couple of folders up from the project and source file.

 	Place the SDK package in your "Packages" folder in order to load and test the externals you build in Max itself.


	@section chapter_platform_buildscript Build Script

	We have provided a basic script that will build all of the projects in the SDK at once.
	This script is written using the Ruby language.  A Ruby interpretter is standard on the Mac.
	On windows you can download and install Ruby (1.9.3 recommended) from http://rubyinstaller.org/ .

	Run from Terminal.app (Mac) or a Command Prompt (Windows)
	by cd'ing into the examples directory, and then running:
@code
	ruby build.rb
@endcode


	@section chapter_platform_mac Mac

	Max external objects for the Mac are Mach-O bundles (folders that appear to be files) whose filenames must end with the .mxo extension.
	The example projects have been tested using Xcode 6.2.
	Xcode is available through the Apple Mac Store.

	After installing Xcode, if you wish to run the aforementioned Ruby script, you will also need to install the Command Line Tools.
	This is done via the menu item: Xcode > Open Developer Tool > More Development Tools...


	@subsection chapter_platform_mac_xcodeproj XCode Project Setup

	The example projects are set up to have Development and Deployment build configurations.
	The Development configuration does not optimize and ensures debugging symbols are present.
	The Deployment configuration creates a universal binary and performs optimization.

	The files required for the projects are included in the project folders with the exception of the following two files:
	- Info.plist
	- maxmspsdk.xcconfig

	These two files are located one folder-level up from the project folder, and are required for the Xcode project to build the Max external.


	@subsection chapter_platform_mac_linking Linking and Frameworks

	External objects use dynamic linking to access the API functions provided by the Max application.
	When an object is loaded, calls to functions inside the application are resolved by the operating system to the correct memory address.
	Due to the fact that "Max" could exist as an application, a standalone you create, or a library inside another application,
	an object's Xcode project does not link directly to a framework, library, or application.
	Instead, the list of permitted symbols is provided to the linker.
	This list is defined in the aforementioned maxmspsdk.xcconfig file.

	Audio objects will link against MaxAudioAPI.framework and Jitter objects link against JitterAPI.framework.
	Alternatively, you could also provide linker flags as we have provided for Max itself.
	The most recent version of all frameworks will be found inside the application you are using
	(they are found inside the application bundle in Contents/Frameworks).
	In addition, there are versions inside the c74support folder provided with the SDK.
	These will be used only to link your objects; they are never actually executed.

	Xcode uses something called the Frameworks Search Path to locate frameworks when linking.
	The example SDK projects use a frameworks search path with a c74support folder two levels up from your the folder containing your Xcode project.
	If you rearrange the SDK folders, projects may not find the frameworks and will fail to link properly.
	Furthermore, even though we specify the frameworks search path, Xcode seems to look in /Library/Frameworks first.
	If you have installed a version of the Max SDK for version 4.6 or ealier, you may have older versions of MaxAPI.framework and MaxAudioAPI.framework in /Library/Frameworks.
	When you try to link objects that contain references to functions only defined in the newest MaxAPI.framework, the link may fail because the projects are using the old frameworks.
	To fix this, you'll need to remove the Max frameworks from /Library/Frameworks.
	If you want to develop objects for both the Max 4.6 and Max 5 SDKs on the same machine, you'll need to modify your 4.6 projects to specify a Frameworks Search Path, and relocate the 4.6 frameworks to the specified location.


	@section chapter_platform_win Windows

	Max external objects for Windows are Dynamic Link Libraries (DLLs) whose filenames must end with the .mxe extension (for 32-bit builds) or .mxe64 (for 64-bit builds).
	These DLLs will export a single function called "ext_main" which is called by max when the external object is first loaded.
	Generally these DLLs will import functions of the Max API from the import library "MaxAPI.lib" which is located in the c74support\\max-includes\\ folder.
	External objects that use audio functionality will import functions from the import library "MaxAudio.lib" which is located in c74support\\msp-includes\\.
	External objects that use Jitter functionality will import functions from the import library "jitlib.lib" which is located in c74support\\jit-includes\\.

	@subsection chapter_platform_win_vs Compiling with Visual Studio

	The example projects are in Visual C++ 2013 format (vcxproj files).  A free version of Visual C++ can be obtained from Microsoft at http://www.microsoft.com/express/.
	You will want to choose "Visual Studio Express 2013 for Windows Desktop".

	The projects are set up to have both a Debug and a Release configuration.  The Release configuration is optimized whereas the Debug one is not.
	Note that for debugging purposes you can exercise your object in the Max Runtime since the copy protection for the Max Application will interfere when run under the debugger.

	Another thing to note is that Max has a private build of the Microsoft C Runtime Library for historical and backward compatibility reasons.
	It is recommended that you link with Microsoft's standard C runtime library rather than the Max C runtime library.
	When you include "ext.h" from the max API it will include ext_prefix.h which for the release build will automatically cause your project to use the max C runtime library.
	To use the Microsoft C Runtime define the C preprocessor macro MAXAPI_USE_MSCRT before including ext.h.


	@section chapter_platform_settings Important Project Settings

	The easiest way to create a new external is to choose one of the existing SDK examples, duplicate it, and then change only the settings that need to be changes (such as the name of the project).
	This will help to guarantee that important project settings are correct.
	Project settings of particular importance are noted below.


	@subsection chapter_platform_settings_mac Mac

	Particularly important for Max externals on the Mac are that the Info.plist is correct set up and that the "Force Package Info Generation" is set to true.
	Without these your object may fail to load on some machines.

	@subsection chapter_platform_settings_win Windows

	In the preprocessor definitions for the Visual Studio project it is important to define WIN_VERSION and EXT_WIN_VERSION to ensure that the
	headers are set up properly.


	@section chapter_platform_specificity Platform-specificity

	If you are writing a cross-platform object and you need to do something that is specific to one platform, the Max API headers provide some predefined symbols you can use.

@code
	#ifdef MAC_VERSION
	// do something specific to the Mac
	#endif
	#ifdef WIN_VERSION
	// do something specific to Windows
	#endif
@endcode

	Another reason for conditional compilation is to handle endianness on the Mac platform.
	If you are still supporting PowerPC, you may have situations where the ordering of bytes within a 16- or 32-bit word is important.
	ext_byteorder.h provides cross-platform tools for manipulating memory in an endian-independent way.


	@section chapter_platform_configuration Configuration

	As the Max API evolves, the use of a number of older legacy functions are discouraged.
	Use of said functions will issue a 'deprecation' warning when you try to compile the code.
	To disable these deprecation warnings you can define the preprocessor symbol C74_NO_DEPRECATION in the target preprocessor section of your IDE.

*/
