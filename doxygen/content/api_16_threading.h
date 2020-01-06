/**
	@page chapter_threading Threading

	The Max systhread API has two main purposes. First, it can be used to implement thread protection which works in conjunction with Max's existing threading model and is cross-platform. Thread protection prevents data corruption in the case of simultaneously executing threads in the same application. We'll discuss the Max threading model and show you a simple example of thread protection below, but you can often avoid the need to use thread protection by using one of the thread-safe @ref datastore Max provides.

	The second use of the systhread API is a cross-platform way to create and manage threads. This is an advanced feature that very few programmers will ever need. For information on creating and managing threads look at the systhread API header file.


	@section chapter_threading_op Max Threading Operation

	Please note that this description of how Max operates is subject to change and may not apply to future versions. For more information about the Max scheduler and low-priority queue, see the @ref chapter_scheduler section.

	Max (without audio) has two threads. The main or event thread handles user interaction, asks the system to redraw the screen, processes events in the low-priority queue. When not in Overdrive mode, the main thread handles the execution of events in the Max scheduler as well. When Overdrive is enabled, the scheduler is moved to a high-priority timer thread that, within performance limits imposed by the operating system, attempts to run at the precise scheduler interval set by user preference. This is usually 1 or 2 milliseconds.

	The basic idea is to put actions that require precise timing and are relatively computationally cheap in the high-priority thread and computationally expensive events that do not require precise timing in the main thread. On multi-core machines, the high-priority thread may (or may not) be executing on a different core.

	On both Mac and Windows, either the main thread or the timer thread can interrupt the other thread, even though the system priority level of the timer thread is generally much higher. This might seem less than optimal, but it is just how operating systems work. For example, if the OS comes to believe the Max timer thread is taking too much time, the OS may "punish" the thread by interrupting it with other threads, even if those threads have a lower system priority.

	Because either thread can be interrupted by the other, it is necessary to use thread protection to preserve the integrity of certain types of data structures and logical operations. A good example is a linked list, which can be corrupted if a thread in the process of modifying the list is interrupted by another thread that tries to modify the list. The Max #t_linklist data structure is designed to be thread-safe, so if you need such a data structure, we suggest you use #t_linklist. In addition, Max provides thread protection between the timer thread and the main thread for many of its common operations, such as sending messages and using outlets.

	When we add audio into the mix (so to speak), the threading picture gets more complicated. The audio perform routine is run inside a thread that is controlled by the audio hardware driver. In order to eliminate excessive thread blocking and potential race conditions, the thread protection offered inside the audio perform routine is far less comprehensive, and as discussed in the MSP section of the API documentation, the only supported operation for perform routines to communicate to Max is to use a clock. This will trigger a function to run inside the Max scheduler.

	The Max scheduler can be run in many different threading conditions. As explained above it can be run either in the main thread or the timer thread. When Scheduler in Audio Interrupt (SIAI) is enabled, the scheduler runs with an interval equal to every signal vector of audio inside the audio thread. However, if the Non-Real-Time audio driver is used, the audio thread is run inside the main thread, and if SIAI is enabled, the scheduler will also run inside the main thread. If not, it will run either in the main thread or the timer thread depending on the Overdrive setting. (Using the Non-Real-Time audio driver without SIAI will generally lead to unpredictable results and is not recommended.)


	@section chapter_threading_protection Thread Protection

	The easiest method for thread protection is to use critical sections. A critical section represents a region of code that cannot be interrupted by another thread. We speak of entering and exiting a critical section, and use critical_enter() and critical_exit() to do so.

	Max provides a default global critical section for your use. This same critical section is used to protect the timer thread from the main thread (and vice versa) for many common Max data structures such as outlets. If you call critical_enter() and critical_exit() with argument of 0, you are using this global critical section. Typically it is more efficient to use fewer critical sections, so for many uses, the global critical section is sufficient. Note that the critical section is recursive, so you if you exit the critical section from within some code that is already protected, you won't be causing any trouble.


	@subsection chapter_threading_protection_arrival When Messages Arrive

	It's possible that a message sent to your object could interrupt the same message sent to your object ("myobject"). For example, consider what happens when a button is connected to the left inlet of myobject and  a metro connected to the same inlet.

	When a user clicks on the bang button, the message is sent to your object in the main thread. When Overdrive is enabled, the metro will send a bang message to your object in the timer thread. Either could interrupt the other. If your object performs operations on a data structure that cannot be interrupted, you should use thread protection.


	@subsection chapter_threading_protection_example Critical Section Example

	Here is an example that uses the global critical section to provide thread protection for an array data structure. Assume we have an operation array_read() that reads data from an array, and array_insert() that inserts data into the same array. We wish to ensure that reading doesn't interrupt writing and vice versa.

@code
	long array_read(t_myobject *x, long index)
	{
		critical_enter(0);
		result = x->m_data[index];
		critical_exit(0);
		return result;
	}
@endcode

	Note that all paths of your code must exit the critical region once it is entered, or the other threads in Max will never execute.
@code
	long array_insert(t_myobject *x, long index, long value)
	{
		critical_enter(0);
		// move existing data
		sysmem_copyptr(x->m_data + index, x->m_data + index + 1, (x->m_size - x->m_index) * sizeof(long));
		// write new data
		x->m_data[index] = value;
		critical_exit(0);
	}
@endcode

*/
