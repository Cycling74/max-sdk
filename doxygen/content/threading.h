/**

	@defgroup threading Threads

	In Max, there are several threads of execution.
	The details of these threads are highlighted in the article "Event Priority in Max (Scheduler vs. Queue)"
	located online at http://www.cycling74.com/story/2005/5/2/133649/9742.

	Not all of the details of Max's threading model are expounded here.
	Most important to understand is that we typically deal the scheduler
	(which when overdrive is on runs in a separate and high priority thread)
	and the low priority queue (which always runs in the main application thread).

	@see http://www.cycling74.com/twiki/bin/view/ProductDocumentation/JitterSdkSchedQueue
	@see http://www.cycling74.com/story/2005/5/2/133649/9742
*/


/**
	@defgroup critical Critical Regions
	@ingroup threading

	A critical region is a simple mechanism that prevents multiple threads
	from accessing at once code protected by the same critical region. The
	code fragments could be different, and in completely different
	modules, but as long as the critical region is the same, no two threads
	should call the protected code at the same time. If one thread is inside
	a critical region, and another thread wants to execute code protected
	by the same critical region, the second thread must wait for the first
	thread to exit the critical region. In some implementations a critical
	region can be set so that if it takes too long for the first thread to exit
	said critical region, the second thread is allowed to execute,
	dangerously and potentially causing crashes. This is the case for the
	critical regions exposed by Max and the default upper limit for a given
	thread to remain inside a critical region is two seconds. Despite the fact
	that there are two seconds of leeway provided before two threads can
	dangerously enter a critical region, it is important to only protect as
	small a portion of code as necessary with a critical region.

	Under Max 4.1 and earlier there was a simple protective mechanism
	called "lockout" that would prevent the scheduler from interrupting
	the low priority thread during sensitive operations such as sending
	data out an outlet or modifying members of a linked list. This lockout
	mechanism has been deprecated, and under the Mac OS X and
	Windows XP versions (Max 4.2 and later) does nothing. So how do
	you protect thread sensitive operations? Use critical regions (also
	known as critical sections). However, it is very important to mention
	that all outlet calls are now thread safe and should never be contained
	inside a critical region. Otherwise, this could result in serious timing
	problems. For other tasks which are not thread safe, such as accessing a
	linked list, critical regions or some other thread protection mechanism
	are appropriate.

	In Max, the critical_enter() function is used to enter a critical
	region, and the critical_exit() function is used to exit a critical
	region. It is important that in any function which uses critical regions,
	all control paths protected by the critical region, exit the critical region
	(watch out for goto or return statements). The critical_enter() and
	critical_exit() functions take a critical region as an argument.
	However, for almost all purposes, we recommend using the global
	critical region in which case this argument is zero. The use of multiple
	critical regions can cause problems such as deadlock, i.e. when thread
	#1 is inside critical region A waiting on critical region B, but thread #2
	is inside critical region B and is waiting on critical region A. In a
	flexible programming environment such as Max, deadlock conditions
	are easier to generate than you might think. So unless you are
	completely sure of what you are doing, and absolutely need to make
	use of multiple critical regions to protect your code, we suggest you use
	the global critical region.

	In the following example code we show how one might use critical
	regions to protect the traversal of a linked list, testing to find the first
	element whose values is equal to "val". If this code were not protected,
	another thread which was modifying the linked list could invalidate
	assumptions in the traversal code.

	@code
	critical_enter(0);
	for (p = head; p; p = p->next) {
		if (p->value == val)
			break;
	}
	critical_exit(0);
	return p;
	@endcode

	And just to illustrate how to ensure a critical region is exited when
	multiple control paths are protected by a critical region, here's a slight
	variant.

	@code
	critical_enter(0);
	for (p = head; p; p = p->next) {
		if (p->value == val) {
			critical_exit(0);
			return p;
		}
	}
	critical_exit(0);
	return NULL;
	@endcode

	For more information on multi-threaded programming, hardware
	interrupts, and related topics, we suggest you perform some research
	online or read the relevant chapters of "Modern Operating Systems" by
	Andrew S. Tanenbaum (Prentice Hall). At the time of writing, some
	relevant chapters from this book are available for download in PDF
	format on Prentice Hall’s web site. See:

	http://www.prenhall.com/divisions/esm/app/author_tanenbaum/custom/mos2e/

	Look under "sample sections".

*/


/**
	@defgroup mutex Mutexes
	@ingroup threading

	@see @ref critical
*/
