/**

	@defgroup sched Timing


*/


/**
	@defgroup clocks Clocks
	@ingroup sched

	Clock objects are your interface to Max’s scheduler. To use the
	scheduler, you create a new Clock object using clock_new in your
	instance creation function. You also have to write a clock function that
	will be executed when the clock goes off, declared as follows:

	@code
	void myobject_tick (myobject *x);
	@endcode

	The argument x is determined by the arg argument to clock_new().
	Almost always it will be pointer to your object.
	Then, in one of your methods, use clock_delay() or clock_fdelay() to
	schedule yourself. If you want unschedule yourself, call
	clock_unset(). To find out what time it is now, use gettime() or
	clock_getftime(). More advanced clock operations are possible with
	the setclock object interface described in Chapter 9. We suggest you
	take advantage of the higher timing precision of the floating-point
	clock routines—all standard Max 4 timing objects such as metro use
	them.

	When the user has Overdrive mode enabled, your clock function will
	execute at interrupt level.


	@section clocks_using_clocks Using Clocks

	Under normal circumstances, gettime or clock_getftime will not
	be necessary for scheduling purposes if you use clock_delay or
	clock_fdelay, but it may be useful for recording the timing of
	messages or events.

	As an example, here’s a fragment of how one might go about writing a
	metronome using the Max scheduler. First, here’s the data structure
	we’ll use.

	@code
	typedef struct mymetro {
		t_object *m_obj;
		void *m_clock;
		double m_interval;
		void *m_outlet;
	} t_mymetro;
	@endcode

	We’ll assume that the class has been initialized already. Here’s the
	instance creation function that will allocate a new Clock.

	@code
	void *mymetro_create (double defaultInterval)
	{
		t_mymetro *x;
		x = (t_mymetro *)newobject(mymetro_class); // allocate space
		x->m_clock = clock_new(x,(method)mymetro_tick); // make a clock
		x->m_interval = defaultInterval; // store the interval
		x->m_outlet = bangout(x); // outlet for ticks
		return x; // return the new object
	}
	@endcode

	Here’s the method written to respond to the bang message that starts
	the metronome.

	@code
	void mymetro_bang (t_mymetro *x)
	{
		clock_fdelay(x->m_clock,0.);
	}
	@endcode

	Here’s the Clock function.

	@code
	void mymetro_tick(t_mymetro *x)
	{
		clock_fdelay(x->m_clock, x->m_interval);
		// schedule another metronome tick
		outlet_bang(x->m_outlet); // send out a bang
	}
	@endcode

	You may also want to stop the metronome at some point. Here’s a
	method written to respond to the message stop. It uses clock_unset.

	@code
	void mymetro_stop (t_mymetro *x)
	{
		clock_unset(x->m_clock);
	}
	@endcode

	In your object’s free function, you should call freeobject on any
	Clocks you’ve created.

	@code
	void mymetro_free (MyMetro *x)
	{
		freeobject((t_object *)x->m_clock);
	}
	@endcode


	@section setclock Scheduling with setclock Objects

	The setclock object allows a more general way of scheduling Clocks by
	generalizing the advancement of the time associated with a scheduler.
	Each setclock object’s "time" can be changed by a process other than the
	internal millisecond clock. In addition, the object implements routines
	that modify the mapping of the internal millisecond clock onto the
	current value of time in an object. Your object can call a set of routines
	that use either setclock or the normal millisecond clock transparently.
	Many Max objects accept the message clock followed by an optional
	symbol to set their internal scheduling to a named setclock object. The
	typical implementation passes the binding of a Symbol (the s_thing
	field) to the Setclock functions. By default, the empty symbol is passed.
	If the binding has been linked to a setclock object, it will be used to
	schedule the Clock. Otherwise, the Clock is scheduled using the main
	internal millisecond scheduler. The Setclock data structure is a
	replacement for void * since there will be no reason for external
	objects to access it directly.

	@subsection setclock_using_the_routines Using the setclock Object Routines

	Here’s an example implementation of the relevant methods of a
	metronome object using the Setclock routines.

	@code
	typedef struct metro
	{
		t_object m_ob;
		long m_interval;
		long m_running;
		void *m_clock;
		t_symbol *m_setclock;
	} t_metro;
	@endcode

	Here’s the implementation of the routines for turning the metronome
	on and off. Assume that in the instance creation function, the
	#t_symbol m_setclock has been set to the empty symbol (gensym
	("")) and m_clock has been created; the clock function
	metro_tick() is defined further on.

	@code
	void metro_bang(Metro *x) // turn metronome on
	{
		x->m_running = 1;
		setclock_delay(x->m_setclock->s_thing,x->m_clock,0);
	}

	void metro_stop(Metro *x)
	{
		x->m_running = 0;
		setclock_unset(x->m_setclock->s_thing,x->m_clock);
	}
	@endcode

	Here is the implementation of the clock function metro_tick() that
	runs periodically.

	@code
	void metro_tick(Metro *x)
	{
		outlet_bang(x->m_ob.o_outlet);
		if (x->m_running)
			setclock_delay(x->m_setclock->s_thing,x->m_clock,x->m_interval);
	}
	@endcode

	Finally, here is an implementation of the method to respond to the
	clock message. Note that the function tries to verify that a non-zero
	value bound to the #t_symbol passed as an argument is in fact an
	instance of setclock by checking to see if it responds to the unset
	message. If not, the metronome refuses to assign the #t_symbol to its
	internal m_setclock field.

	@code
	void metro_clock(Metro *x, t_symbol *s)
	{
		void *old = x->m_setclock->s_thing;
		void *c = 0;

		// the line below can be restated as:
		//	if s is the empty symbol
		//	or s->s_thing is zero
		//	or s->s_thing is non-zero and a setclock object
		if ((s == gensym("")) || ((c = s->s_thing) && zgetfn(c,&s_unset)))
		{
			if (old)
				setclock_unset(old,x->m_clock);
			x->m_setclock = s;
			if (x->m_running)
				setclock_delay(c,x->m_clock,0L);
		}
	}
	@endcode



	@section creating_schedulers Creating Schedulers

	If you want to schedule events independently of the time of the global
	Max scheduler, you can create your own scheduler with
	scheduler_new(). By calling scheduler_set() with the newly created
	scheduler, calls to clock_new() will create Clocks tied to your scheduler
	instead of Max’s global one. You can then control the time of the
	scheduler (using scheduler_settime()) as well as when it executes
	clock functions (using scheduler_run()). This is a more general
	facility than the setclock object routines, but unlike using the time
	from a setclock object to determine when a Clock function runs, once
	a Clock is tied to a scheduler.

*/




/**
	@defgroup qelems Qelems
	@ingroup sched

	Your object’s methods may be called at interrupt level. This happens
	when the user has Overdrive mode enabled and one of your methods is
	called, directly or indirectly, from a scheduler Clock function. This
	means that you cannot count on doing certain things—like drawing,
	asking the user what file they would like opened, or calling any
	Macintosh toolbox trap that allocates or purges memory—from within
	any method that responds to any message that could be sent directly
	from another Max object. The mechanism you’ll use to get around this
	limitation is the Qelem (queue element) structure. Qelems also allow
	processor-intensive tasks to be done at a lower priority than in an
	interrupt. As an example, drawing on the screen, especially in color,
	takes a long time in comparison with a task like sending MIDI data.

	A Qelem works very much like a Clock. You create a new Qelem in
	your creation function with qelem_new and store a pointer to it in
	your object. Then you write a queue function, very much like the clock
	function (it takes the same single argument that will usually be a
	pointer to your object) that will be called when the Qelem has been set.
	You set the Qelem to run its function by calling qelem_set().

	Often you’ll want to use Qelems and Clocks together. For example,
	suppose you want to update the display for a counter that changes 20
	times a second. This can be accomplished by writing a Clock function
	that calls qelem_set() and then reschedules itself for 50 milliseconds
	later using the technique shown in the metronome example above.
	This scheme works even if you call qelem_set() faster than the
	computer can draw the counter, because if a Qelem is already set,
	qelem_set() will not set it again. However, when drawing the counter,
	you’ll display its current value, not a specific value generated in the
	Clock function.

	Note that the Qelem-based defer mechanism discussed later in this
	chapter may be easier for lowering the priority of one-time events,
	such as opening a standard file dialog box in response to a read
	message.

	If your Qelem routine sends messages using outlet_int() or any other
	of the outlet functions, it needs to use the lockout mechanism
	described in the Interrupt Level Considerations section.
*/




/**
	@defgroup systime Systime API
	@ingroup sched

	The Systime API provides the means of getting the system time,
	instead of the scheduler time as you would with functions like gettime().
*/


/**
	@defgroup time ITM Time Objects
	@ingroup sched

	ITM Time Objects are a high-level interface to ITM, a tempo-based scheduler API. 
	They provide an abtraction so your object can schedule events either in milliseconds (as traditional clock objects) or ticks (tempo-relative units).
*/

