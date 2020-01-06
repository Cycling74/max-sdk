/**
	@page chapter_appendix_d Appendix: Updating Externals for Max 6


	@section chapter_appendix_d_msp64 Updating MSP Externals for 64-bit Audio Processing

	@subsection chapter_appendix_d_background Background

	In Max 5 and prior versions, the signal chain for processing audio was compiled by sending all objects in the patcher a "dsp" message.  Objects responding to this message then executed their dsp method, typically adding one of the object's perform methods to the signal chain.

	In Max 6, the signal chain is compiled by first sending objects a "dsp64" message.  When your object responds to this message, you can add your 64-bit audio perform methods.  If an object supports the old "dsp" message but not the "dsp64" message, it then wraps the older 32-bit perform routine with conversion on the inputs and outputs.

	This means that the 64-bit engine will work just fine with the older 32-bit objects.  However, the conversion comes with some computational expense.  For the best performance your objects should support the 64-bit dsp chain natively by implementing the "dsp64" message as explained below.


	@subsection chapter_appendix_d_api API

	As noted, instead of the "dsp" method used by objects for Max 5 and earlier, Max 6 objects implement a "dsp64" method.  This has the same purpose as the original dsp method.  One notable difference is that the signals are not passed to the dsp64 method.  This is to allow for the signal that is used to change dynamically at runtime.  However, the relevant info (samplerate, number of signals connected, etc) is passed in.

	The main purpose of the dsp64 method is to call back into the audio lib to put perform methods on the dsp chain.  This is done by sending the 'dsp_add64' message to the dspchain object using object_method().

	The perform routine is now of type t_perfroutine64, defined in z_dsp.h, and now has a fixed function signature.  It does take a user-defined parameter that is passed back from the call to 'dsp_add64'.



	@subsection chapter_appendix_d_examples Example Code

	The simplemsp~ examples in the 'audio' folder of the SDK have been updated for 64-bit audio processing in Max 6.
	Several projects, including the simplemsp~ example, demonstrate how to support both 64-bit audio processing in Max 6 and 32-bit audio processing for compatibility with Max 5.



	@section chapter_appendix_d_cocoa Updating Max Externals for Cocoa

	On the Macintosh platform, Max 6 made the transition from using the Carbon API to using the Cocoa API for interacting with the Mac OS.
	In most cases the transition for third-party developers should be seemless.
	If you are operating directly using native Carbon calls then your code will need to be updated to Cocoa using Objective-C.

	The most common scenario is where you ask a patcherview for the native window handle with a call such as:

@code
	WindowRef viewWindow;
	object_method(patcherview, gensym("nativewindow"), (void**)&viewWindow);
@endcode

	In Max 6 this will not work because the returned 'viewWindow' is not the Carbon WindowRef but is instead a Cocoa NSWindow*.
	You may update your code to use Cocoa instead of Carbon, or you may wish to transition more slowly by continuing to use a WindowRef.
	Here is an example to assist in obtaining a WindowRef:

@code
	NSView		*cocoa_view = NULL;
	NSWindow	*cocoa_window = NULL;
	WindowRef	carbon_window;

	object_method(patcherview, gensym("nativewindow"), (void**)&cocoa_view);
	if (cocoa_view) {
		cocoa_window = [cocoa_view window];
		if (cocoa_window) {
			carbon_window = [cocoa_window windowRef];
		}
	}

	// now you can use your carbon_window as before
@endcode


**/
