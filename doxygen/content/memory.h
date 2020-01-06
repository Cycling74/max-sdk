/**
	@defgroup memory Memory Management

	In the past, Max has provided two separate APIs for memory management.
	One for allocating memory on the stack so that it was interrupt safe,
	including the getbytes() and freebytes() functions.
	The other, the "sysmem" API, were for allocating memory on the heap
	where larger amounts of memory were needed and the code could be guaranteed to
	operate at non-interrupt level.

	Many things have changed in the environment of recent operating systems
	(MacOS X and Windows XP/Vista), the memory routines function differently,
	and the scheduler is no longer directly triggered by a hardware interrupt.
	In Max 5, the sysmem and getbytes API's have been unified, and thus may be
	used interchangeably.

	The memory management unification can be switched on and off in the header files
	if needed, to compile code for older versions of Max for example, by changing
	the use of #MM_UNIFIED in the Max headers.

	@section The Sysmem API

	The Sysmem API provides a number of utilities for allocating and
	managing memory. It is relatively similar to some of the Macintosh
	Memory Manager API, and not too different from Standard C library
	memory functions. It is <em>not</em> safe to mix these routines with other
	memory routines (e.g. don’t use malloc() to allocate a pointer, and
	sysmem_freeptr() to free it).


*/

