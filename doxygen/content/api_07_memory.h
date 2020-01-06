/**
	@page chapter_memory Memory Allocation

	The Max API offers cross-platform calls memory management. There are two types of calls, those for pointers and those for handles. Handles are pointers to pointers, and were used in the early Mac OS to permit memory to be relocated without changing a reference, and many Mac OS API calls used handle. There are a few legacy Max API calls that use handles as well, but in general, unless the OS or Max requires the use of a handle, you're probably better off using the simpler pointer.

	Longtime Max object programmers may have used memory calls getbytes() and freebytes() in the past, but all memory calls now use same underlying OS mechanisms, so while getbytes() and freebytes() are still supported, they are restricted to 32K of memory or less due to the arguments they use, and we recommend the use of sysmem_newptr() and sysmem_freeptr() instead.


	Here are some examples of allocating and freeing pointers and handles.

@code
		char *ptr;
		char **hand;

		ptr = sysmem_newptr(2000);
		post("I have a pointer %lx and it is %ld bytes in size",ptr, sysmem_ptrsize(ptr));
		ptr = sysmem_resizeptrclear(ptr, 3000);
		post("Now I have a pointer %lx and it is %ld bytes in size",ptr, sysmem_ptrsize(ptr));
		sysmem_freeptr(ptr);

		hand = sysmem_newhandle(2000);
		post("I have a handle %lx and it is %ld bytes in size",hand, sysmem_handlesize(hand));
		sysmem_resizehandle(hand, 3000);
		post("Now the handle %lx is %ld bytes in size",hand, sysmem_ptrsize(hand));
		sysmem_freehandle(hand);
@endcode


*/
