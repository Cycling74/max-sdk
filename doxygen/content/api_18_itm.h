/**
	@page chapter_itm ITM

	ITM is the tempo-based timing system introduced with Max 5. It allows users to express time in tempo-relative units as well as milliseconds, samples, and an ISO 8601 hour-minute-second format. In addition, ITM supports one or more transports, which can be synchronized to external sources. An ITM-aware object can schedule events to occur when the transport reaches a specific time, or find out the current transport state.

	The ITM API is provided on two different levels. The time object (#t_timeobject) interface provides a higher-level way to parse time format information and schedule events. In addition, you can use lower-level routines to access ITM objects (#t_itm) directly. An ITM object is responsible for maintaining the current time and scheduling events. There can be multiple ITM objects in Max, each running independently of the others.


@section chapter_itm_temp Scheduling Temporary Events


	There are two kinds of events in ITM. Temporary events are analogous to Max clock objects in that they are scheduled and fire at a dynamically assigned time. Once they have executed, they are removed from the scheduler. Permanent events always fire when the transport reaches a specific time, and are not removed from the scheduler. The ITM-aware metro is an example of an object that uses temporary events, while the timepoint object uses permanent events. We'll show how to work both types using an example included in the SDK called delay2. The existing Max delay object provides this capability, but this example shows most of the things you can do with the time object interface. To see the complete object, look at the <i>delay2 example</i>. We'll introduce a simpler version of the object, then proceed to add the quantization and the additional outlet that generates a delayed bang based on low-level ITM calls.

	The ITM time object API is based on a Max object you create that packages up common ways you will be using ITM, including attribute support, quantization, and, if you want it, the ability to switch between traditional millisecond-based timing and tempo-based timing using an interface that is consistent with the existing Max objects such as metro and delay. (If you haven't familiarized yourself with attributes, you may want to read through the discussion about them in @ref attr before reading further.)

	To use the time object, you'll first need to provide some space in your object to hold a pointer to the object(s) you'll be creating.

@code
	typedef struct _delay2simple
	{
		t_object m_ob;
		t_object *m_timeobj;
		void *m_outlet;
	} _delay2simple;
@endcode

	Next, in your ext_main() routine, you'll create attributes associated with the time object using the class_time_addattr() function.
@code
		class_time_addattr(c, "delaytime", "Delay Time", TIME_FLAGS_TICKSONLY | TIME_FLAGS_USECLOCK | TIME_FLAGS_TRANSPORT);
@endcode

	The second argument, "delaytime", is a string that names the attribute. Users of your object will be able to change the delay value by sending a delaytime message. "Delay Time" is the label users see for the attribute in the inspector. The flags argument permits you to customize the type of time object you'd like. #TIME_FLAGS_TICKSONLY means that the object can only be specified in tempo-relative units. You would not use this flag if you want the object to use the regular Max scheduler if the user specifies an absolute time (such as milliseconds). #TIME_FLAGS_USECLOCK means that it is a time object that will actually schedule events. If you do not use this flag, you can use the time object to hold and convert time values, which you use to schedule events manually. #TIME_FLAGS_TRANSPORT means that an additional attribute for specifying the transport name is added to your object automatically (it's called "transport" and has the label "Transport Name"). The combination of flags above is appropriate for an object that will be scheduling events on a temporary basis that are only synchronized with the transport and specified in tempo-relative units.

	The next step is to create a time object in your new instance routine using time_new. The time_new function is something like clock_new -- you pass it a task function that will be executed when the scheduler reaches a certain time (in this case, delay2simple_tick, which will send out a bang). The first argument to time_new is a pointer to your object, the second is the name of the attribute created via class_time_addattr, the third is your task function, and the fourth are flags to control the behavior of the time object, as explained above for class_time_addattr.

	Finally, we use time_setvalue to set the initial delay value to 0.
@code
	void *delay2simple_new()
	{
		t_delay2simple *x;
		t_atom a;

		x = (t_delay2simple *)object_alloc(s_delay2simple_class);
		x->m_timeobj = (t_object *)time_new((t_object *)x, gensym("delaytime"), (method)delay2simple_tick, TIME_FLAGS_TICKSONLY | TIME_FLAGS_USECLOCK);
		x->m_outlet = bangout((t_object *)x);
		atom_setfloat(&a, 0.);
		time_setvalue(x->d_timeobj, NULL, 1, &a);
		return x;
	}
@endcode

	To make a delayed bang, we need a delay2simple_bang function that causes our time object to put its task function into the ITM scheduler. This is accomplished using time_schedule. Note that unlike the roughly equivalent clock_fdelay, where the delay time is an argument, the time value must already be stored inside the time object using time_setvalue. The second argument to time_schedule is another time object that can be used to control quantization of an event. Since we aren't using quantization in this simple version of delay2, we pass NULL.
@code
	void delay2simple_bang(t_delay2 *x)
	{
		time_schedule(x->d_timeobj, NULL);
	}
@endcode

	Next, our simple task routine, delay2simple_tick. After the specified number of ticks in the time object has elapsed after the call to time_schedule, the task routine will be executed.
@code
	void delay2_tick(t_delay2 *x)
	{
		outlet_bang(x->d_outlet);
	}
@endcode

	Now let's add the two more advanced features found in delay2: quantization and a second (unquantized) bang output using low-level ITM routines. Here is the delay2 data structure. The new elements are a proxy (for receiving a delay time), a time object for quantization (d_quantize), a clock to be used for low-level ITM scheduling, and an outlet for the use of the low-level clock's task.

@code
	typedef struct delay2
	{
		t_object d_obj;
		void *d_outlet;
		void *d_proxy;
		long d_inletnum;
		t_object *d_timeobj;
		t_object *d_outlet2;
		t_object *d_quantize;
		void *d_clock;
 } t_delay2;
@endcode

	In the initialization routine, we'll define a quantization time attribute to work in conjunction with the d_quantize time object we'll be creating. This attribute does not have its own clock to worry about. It just holds a time value, which we specify will only be in ticks (quantizing in milliseconds doesn't make sense in the ITM context). If you build delay2 and open the inspector, you will see time attributes for both Delay Time and Quantization.
@code
	class_time_addattr(c, "quantize", "Quantization", TIME_FLAGS_TICKSONLY);
@endcode

Here is part of the revised delay2 new instance routine. It now creates two time objects, plus a regular clock object.

@code
	x->d_inletnum = 0;
	x->d_proxy = proxy_new(x, 1, &x->d_inletnum);
	x->d_outlet2 = bangout(x);
	x->d_outlet = bangout(x);

	x->d_timeobj = (t_object*) time_new((t_object *)x, gensym("delaytime"), (method)delay2_tick, TIME_FLAGS_TICKSONLY | TIME_FLAGS_USECLOCK);
	x->d_quantize = (t_object*) time_new((t_object *)x, gensym("quantize"), NULL, TIME_FLAGS_TICKSONLY);
	x->d_clock = clock_new((t_object *)x, (method)delay2_clocktick);
@endcode

To use the quantization time object, we can pass it as the second argument to time_schedule. If the value of the quantization is 0, there is no effect. Otherwise, time_schedule will move the event time so it lies on a quantization boundary. For example, if the quantization value is 4n (480 ticks), the delay time is 8n (240 ticks) and current time is 650 ticks, the delay time will be adjusted so that the bang comes out of the delay2 object at 980 ticks instead of 890 ticks.

In addition to using quantization with time_schedule, delay2_bang shows how to calculate a millisecond equivalent for an ITM time value using itm_tickstoms. This delay value is not quantized, although you read the time value from the d_quantize object and calculate your own quantized delay if wanted. The "calculated" delay is sent out the right outlet, since the clock we created uses delay2_clocktick.

@code
	void delay2_bang(t_delay2 *x)
	{
		double ms, tix;

		time_schedule(x->d_timeobj, x->d_quantize);

		tix = time_getticks(x->d_timeobj);
		tix += (tix / 2);
		ms = itm_tickstoms(time_getitm(x->d_timeobj), tix);
		clock_fdelay(x->d_clock, ms);
	}

	void delay2_clocktick(t_delay2 *x)
	{
		outlet_bang(x->d_outlet2);
	}
@endcode

@section chapter_itm_permanent Permanent Events

	A permanent event in ITM is one that has been scheduled to occur when the transport reaches a specific time. You can schedule a permanent event in terms of ticks or bars/beats/units. An event based in ticks will occur when the transport reaches the specified tick value, and it will not be affected by changes in time signature. An event specified for a time in bars/beats/units will be affected by the time signature. As an example, consider an event scheduled for bar 2, beat 1, unit 0. If the time signature of the ITM object on which the event has been scheduled is 3/4, the event will occur at 480 times 3 or 1440 ticks. But if the time signature is 4/4, the event will occur at 1920 ticks. If, as an alternative, you had scheduled the event to occur at 1920 ticks, setting the time signature to 3/4 would not have affected when it occurred.

	You don't "schedule" a permanent event. Once it is created, it is always in an ITM object's list of permanent events. To specify when the event should occur, use time_setvalue.

	The high-level time object interface handles permanent events. Let's say we want to have a time value called "targettime." First, we declare an attribute using class_time_addattr. The flags used are #TIME_FLAGS_TICKSONLY (required because you can't specify a permanent event in milliseconds), #TIME_FLAGS_LOCATION (which interprets the bar/beat/unit times where 1 1 0 is zero ticks), #TIME_FLAGS_PERMANENT (for a permanent event), and #TIME_FLAGS_TRANSPORT (which adds a transport attribute permitting a user to choose a transport object as a destination for the event) and #TIME_FLAGS_POSITIVE (constrains the event to happen only for positive tick and bar/beat/unit values).

@code
	class_time_addattr(c, "targettime", "Target Time", TIME_FLAGS_TICKSONLY | TIME_FLAGS_LOCATION | TIME_FLAGS_PERMANENT | TIME_FLAGS_TRANSPORT | TIME_FLAGS_POSITIVE);
@endcode

The #TIME_FLAGS_TRANSPORT flag is particularly nice. Without any intervention on your part, it creates a transport attribute for your object, and takes care of scheduling the permanent event on the transport the user specifies, with a default value of the global ITM object. If you want to cause your event to be rescheduled dynamically when the user changes the transport, your object can respond to the reschedule message as follows.

@code
	class_addmethod(c, (method)myobject_reschedule,	"reschedule",	A_CANT, 0);			// for dynamic transport reassignment
@endcode

All you need to do in your reschedule method is just act as if the user has changed the time value, and use the current time value to call time_setvalue.

In your new instance routine, creating a permanent event with time_new uses the same flags as were passed to class_time_addattr:

@code
	x->t_time = (t_object*) time_new((t_object *)x, gensym("targettime"), (method)myobject_tick, TIME_FLAGS_TICKSONLY | TIME_FLAGS_USECLOCK | TIME_FLAGS_PERMANENT | TIME_FLAGS_LOCATION | TIME_FLAGS_POSITIVE);
@endcode

The task called by the permanent time object is identical to a clock task or an ITM temporary event task.

@section chapter_itm_clean Cleaning Up

With all time objects, both permanent and temporary, it's necessary to free the objects in your object's free method. Failure to do so will lead to crashes if your object is freed but its events remain in the ITM scheduler. For example, here is the delay2 free routine:

@code
	void delay2_free(t_delay2 *x)
	{
		freeobject(x->d_timeobj);
		freeobject(x->d_quantize);
		freeobject((t_object *) x->d_proxy);
		freeobject((t_object *)x->d_clock);
	}
@endcode




*/
