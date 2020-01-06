/**
	@mainpage Objects in C: A Roadmap

	Max has an extensive API for developing new objects in C.
	Before you start learning about it, however, we would like to save you time and make sure you learn the minimum about the API for what you need to do.
	Therefore, we've made a brief list of application areas for object development along with the sections of this document with which you'll probably want to become familiar.



	@section chapter_roadmap_max_objects Max Objects

	For <strong>logic and arithmetic objects</strong>,
	such as new mathematical functions or more complex conditional operations than what is offered in Max,
	it should be sufficient to read the @ref chapter_anatomy section.

	For objects that use @ref chapter_datastructures, you'll want to read, in addition,
	the @ref chapter_atoms section to learn about Max's basic mechanisms for representing and communicating data.

	If you are interested in writing interfaces to <strong>operating system services</strong>,
	you may need to learn about Max's @ref chapter_threading model and @ref chapter_scheduler.

	For objects that deal with time and timing you'll want to learn about @ref chapter_scheduler.
	If you're interested in tempo-based scheduling, you'll want to read the section on @ref chapter_itm and look at the delay2 example.

	To create new user interface gadgets, you'll want to read all of the above, plus the section on Attributes and the @ref chapter_ui_anatomy.
	The section on @ref jgraphics will also be helpful.

	To create <strong>objects with editing windows</strong>, things are much more complicated than they used to be.
	You'll need to learn everything about UI objects, plus understand the scripto example object project.

	For patcher scripting and interrogation objects, the section on @ref chapter_scripting, plus a few of the examples will be very helpful.
	It is also helpful to have a clear conceptual understanding of the patcher,
	which might be aided by reading the patcher scripting sections of the js object documentation.

	Max 6 introduced support for passing structured data with the @ref dictobj.


	@section chapter_roadmap_msp_objects MSP Objects

	To create audio <strong>filters</strong> and <strong>signal generators</strong>,
	read the @ref chapter_anatomy, then read the @ref chapter_msp_anatomy section.
	MSP objects make use of @ref chapter_inout_proxies when receiving multiple audio inputs, so familiarity with that concept could be helpful.

	For audio objects that output events (messages), you'll need to use the services of @ref chapter_scheduler, so we suggest reading about that.

	For UI objects for analyzing and controlling audio, you'll need to learn about regular MSP objects as well as Max UI objects.

	Information on updating MSP objects from Max 5 or earlier for 64-bit audio (introduced in Max 6) is located in @ref chapter_appendix_d.
 
 	Max 8 introduced MC for working with multi-voice/multi-channel signals. More information is available in the @ref chapter_mc chapter.
 

	@section chapter_roadmap_jit_objects Jitter Objects

	The @ref chapter_jit_objectmodel outlines some important basic information about Jitter's flexible object model.
	@ref chapter_jit_maxwrappers describes how to write Max wrapper objects that contain Jitter objects for use in the Max patcher world.
	@ref chapter_jit_mopqs and @ref chapter_jit_mopdetails describe how to create a particular type of Jitter object called matrix operators, or MOPs.
	@ref chapter_jit_ob3dqs and @ref chapter_jit_ob3ddetails describe how to create OB3D Jitter objects for use in rendering OpenGL scenes.
	@ref chapter_jit_sched covers important threading and timing issues when building Jitter objects.
	@ref chapter_jit_notification explains how Jitter objects can be registered by name and notify clients as they change or important events occur.
	@ref chapter_jit_usingobjs provides some examples of how to instantiate and take advantage of Jitter objects from C, just as one would from Java, Javascript, or the patcher.
	Finally, The @ref chapter_jit_jxf and @ref chapter_jit_networking contain information relating to the data formats involved in the JXF file format and Jitter networking protocols, respectively.


*/
