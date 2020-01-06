/**
	@page chapter_scheduler The Scheduler

	The Max scheduler permits operations to be delayed until a later time. It keeps track of time in double-precision, but the resolution of the scheduler depends on the user's environment preferences. The scheduler also works in conjunction with a low-priority queue, which permits time-consuming operations that might be initiated inside the scheduler to be executed in a way that does not disrupt timing accuracy.

	Most objects interface with the scheduler via a clock (#t_clock) object. A clock is associated with a task function that will execute when the scheduler's current time reaches the clock's time. There is also a function called schedule() that can be used for one-off delayed execution of a function. It creates a clock to do its job however, so if your object is going to be using the scheduler repeatedly, it is more efficient to store references to the clocks it creates so the clocks can be reused.

	The scheduler is periodically polled to see if it needs to execute clock tasks. There are numerous preferences Max users can set to determine when and how often this polling occurs. Briefly:

	- The Overdrive setting determines whether scheduler polling occurs in a high-prority timer thread or the main thread
	- The Interval setting determines the number of milliseconds elapse between polling the scheduler
	- The Throttle setting determines how many tasks can be executed in any particular scheduler poll

	Similar Throttle and Interval settings exist for the low-priority queue as well.

	For more information refer to the @ref sched documentation. While the details might be a little overwhelming on first glance, the important point is that the exact time your scheduled task will execute is subject to variability. Max permits this level of user control over the scheduler to balance all computational needs for a specific application.


	@section chapter_scheduler_clocks Creating and Using Clocks

	There are five steps to using a clock in an external object.

	1. Add a member to your object's data structure to hold a pointer to the clock object
@code
	typedef struct _myobject
	{
		t_object m_obj;

		void *m_clock;
	} t_object;
@endcode

	2. Write a task function that will do something when the clock is executed. The function has only a single argument, a pointer to your object. The example below gets the current scheduler time and prints it.

@code
	void myobject_task(t_myobject *x)
	{
		double time;

		sched_getftime(&time);
		post("instance %lx is executing at time %.2f", x, time);
	}
@endcode

	3. In your new instance routine, create the clock (passing a pointer to your object and the task function) and store the result in your object's data structure.
@code
		x->m_clock = clock_new((t_object *)x, (method)myobject_task);
@endcode

	4. Schedule your clock. Use clock_fdelay() to schedule the clock in terms of a delay from the current time. Below we schedule the clock to execute 100 milliseconds from now.
@code
		clock_fdelay(x->m_clock, 100.);
@endcode

	If you want to cancel the execution of a clock for some reason, you can use clock_unset().
@code
		clock_unset(x->m_clock);
@endcode

	5. In your object's free routine, free the clock
@code
		object_free(x->m_clock);
@endcode

	Note that if you call clock_delay() on a clock that is already set, its execution time will be changed. It won't execute twice.


	@section chapter_scheduler_qelems Creating and Using Qelems

	A qelem ("queue element") is used to ensure that an operation occurs in the low-priority thread. The task function associated with a #t_qelem is executed when the low-priority queue is serviced, always in the main (user interface) thread. Any qelem that is "set" belongs to the low-priority queue and will be executed as soon as it serviced.

	There are two principal things you want to avoid in the high priority thread: first, time-consuming or unpredictable operations such as file access, and second, anything that will block execution for any length of time -- for example, showing a dialog box (including a file dialog).

	The procedure for using a qelem is analogous to that for using a clock.

	1. Add a member to your object's data structure to hold a pointer to the qelem
@code
	typedef struct _myobject
	{
		t_object m_obj;

		void *m_qelem
	} t_myobject;
@endcode

	2. Write a task function that will do something when the qelem is executed. The function has only a single argument, a pointer to your object.
@code
	void myobject_qtask(t_myobject *x)
	{
		post("I am being executed a low priority!"
	}
@endcode

	3. In your new instance routine, create the qelem (passing a pointer to your object and the task function) and store the result in your object's data structure.
@code
		x->m_qelem = qelem_new((t_object *)x, (method)myobject_qtask);
@endcode

	4. Set the qelem by using qelem_set(). You could, for example, call qelem_set() in a clock task function or in direct response to a message such as bang or int.
@code
		qelem_set(x->m_qelem);
@endcode

	If you want to cancel the execution of a qelem for some reason, you can use qelem_unset().
@code
		qelem_unset(x->m_qelem);
@endcode

	5. In your object's free routine, call qelem_free(). Do not call object_free() or freeobject() -- unlike the clock, the qelem is not an object.
@code
		qelem_free(x->m_qelem);
@endcode

	Note that if you call qelem_set() on a qelem that is already set, it won't execute twice. This is a feature, not a bug, as it permits you to execute a low-priority task only as fast as the low-priority queue operates, not at the high-priority rate that the task might be triggered. An example would be that a number box will redraw more slowly than a counter that changes its value. This is not something you need to worry about, even if you are writing UI objects, as Max handles it internally (using a qelem).


	@section chapter_scheduler_defer Defer

	The defer function and its variants use a qelem to ensure that a function executes at low-priority. There are three variants: defer(), defer_low(), and defer_medium(). The difference between using defer() and a qelem is that defer() is a one-shot deal -- it creates a qelem, sets it, and then gets rid of it when the task function has executed. The effect of this is that if you have some rapid high-priority event that needs to trigger something to happen at low-priority, defer() will ensure that this low-priority task happens every time the high-priority event occurs (in a 1:1 ratio), whereas using a qelem will only run the task at a rate that corresponds to the service interval of the low-priority queue. If you repeatedly defer() something too rapidly, the low-priority queue will become backlogged and the responsiveness of the UI will suffer.

	A typical use of defer() is if your object implements a read message to ask the user for a file. Opening the dialog in the timer thread and waiting for user input will likely crash, but even if it didn't, the scheduler would effectively stop.

	To use defer(), you write a deferred task function that will execute at low priority. The function will be passed a pointer to your object, plus a symbol and atom list modeled on the prototype for an anything method. You need not pass any arguments to the deferred task if you don't need them, however.

@code
	void myobject_deferredtask(t_myobject *x, t_symbol *s, long argc, t_atom *argv)
	{
		post("I am deferred");
	}
@endcode

	To call the task, use defer() as shown below. The first example passes no arguments. The second passes a couple of long atoms.
@code
		defer((t_object *)x, (method)myobject_deferredtask, NULL, 0, NULL);

		t_atom av[2];

		atom_setlong(av, 1);
		atom_setlong(av+ 2, 74);

		defer((t_object *)x, (method)myobject_deferredtask, NULL, 2, av);
@endcode

	Defer copies any atoms you pass to newly allocated memory, which it frees when the deferred task has executed.


	@subsection chapter_scheduler_defer_variants Defer Variants

	defer has two variants, defer_low() and defer_medium(). Here is a comparison:

	defer()

	If executing at high priority, defer() puts the deferred task at the front of the low-priority queue. If not executing at highpriority, defer() calls the deferred task immediately.

	defer_low()

	At all priority levels, defer_low() puts the deferred task at the back of the low-priority queue.

	defer_medium()

	If executing at high priority, defer_medium() puts the deferred task at the back of the low-priority queue. If not executing at high priority, defer_medium() calls the deferred task immediately.


	@section chapter_scheduler_sechedule Schedule

	The schedule() function is to clocks as defer() is to qelems.  Schedule creates a clock for a task function you specify and calls clock_fdelay() on it to make the task execute at a desired time. As with defer(), schedule() can copy arguments to be delivered to the task when it executes.

	A schedule() variant, schedule_defer(), executes the task function at low priority after a specified delay.


*/
