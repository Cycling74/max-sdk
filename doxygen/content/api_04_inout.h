/**
	@page chapter_inout Inlets and Outlets

	You are familiar with inlets and outlets when connecting two objects together in a patcher. To receive data in your object or send data to other objects, you need to create the C versions of inlets and outlets. In this section, we'll explain what inlets and outlets are, how to create them, and how to use them. We'll also discuss a more advanced type of inlet called a proxy that permits a message to be received in any of your object's inlets. Proxies are used by audio objects to permit inlets to handle both signals and normal Max messages.

	By default, every object shows one inlet. Additional inlets appear to the right of the default inlet, with the rightmost inlet being created last.

	Inlets are essentially message translators. For example, if you create an int inlet, your object will receive the "in1" message instead of the "int" message when a number arrives at this newly created inlet. You can use the different message name to define special behavior for numbers arriving at each inlet. For example, a basic arithmetic object in Max such as + stores the number to be added when it arrives in the right inlet, but performs the computation and outputs the result when a number arrives in the left inlet.

	Outlets define connections between objects and are used to send messages from your object to the objects to which it is connected. What is not obvious about an outlet, however, is that when you send a number out an outlet, the outlet-sending function does not return until all computation "below" the outlet has completed. This stack-based execution model is best illustrated by observing a patch with the Max debugger window. To understand this stack-based model it may be helpful to use the breakpoint and debugging features in Max and follow the stack display as you step through the execution of a patch.  Outlets, like inlets, appear in the order you create them from right-to-left. In other words, the first inlet or outlet you create will be the visually farthest to the right.


	@section chapter_inout_inlets Creating and Using Inlets

	Proper use of an inlet involves two steps: first, add a method that will respond to the message sent via the inlet in your initialization routine, and second, create the inlet in your new instance routine. (Creating inlets at any other time is not supported.)

	There are three types of inlets: int, float, and custom. We'll only describe int and float inlets here because proxies are generally a better way to create an inlet that can respond to any message. For int inlets, you'll bind a function to a message "in1", "in2", "in3" etc. depending on the inlet number you assign. Here's how to create a single inlet using "in1"...

	In your initialization routine:
@code
		class_addmethod(c, (method)myobject_in1, "in1", A_LONG, 0);
@endcode

	In your new instance routine, after calling object_alloc() to create your instance:
@code
		intin(x, 1);
@endcode

	The method that will be called when an int is received in the right inlet:
@code
	void myobject_in1(t_myobject *x, long n)
	{
		// do something with n
	}
@endcode

	Creating a single inlet in this way gives your object two inlets (remember that it always has one by default).
	If you want to create multiple inlets, you'll need to create them in order from right to left, as shown below:
@code
		intin(x, 2);		// creates an inlet (the right inlet) that will send your object the "in2" message
		intin(x, 1);		// creates an inlet (the middle inlet) that will send your object the "in1" message
@endcode

	Inlets that send float messages to your object are created with floatin() and translate the float message into "ft1","ft2","ft3" etc. Example:

	In initialization routine:
@code
		class_addmethod(c, (method)myobject_ft1, "ft1", A_FLOAT, 0);
@endcode

	In new instance routine:
@code
		floatin(x, 1);
@endcode

	Method:
@code
	void myobject_ft1(t_myobject *x, double f)
	{
		post("float %.2f received in right inlet,f);
	}
@endcode

	Note that you can mix int and float inlets, but each inlet must have a unique number. Example:
@code
		intin(x, 2);
		floatin(x, 1);
@endcode


	@section chapter_inout_outlets Creating and Using Outlets

	You create outlets in your new instance routine. Outlet creators return a pointer that you should store for later use when you want to send a message. As with inlets, outlets are created from right to left.

	Here's a simple example. First we'll add two void pointers to our data structure to store the outlets for each instance.
@code
	typedef struct _myobject
	{
		t_object m_ob;
		void *m_outlet1;
		void *m_outlet2;
	} t_myobject;
@endcode

	Then we'll create the outlets in our new instance routine.
@code
		x = (t_myobject *)object_alloc(s_myobject_class);
		x->m_outlet2 = bangout((t_object *)x);
		x->m_outlet1 = intout((t_object *)x);
		return x;
@endcode

	These outlets are type-specific, meaning that we will always send the same type of message through them. If you want to create outlets that can send any message, use outlet_new(). Type-specific outlets execute faster, because they make a direct connection to the method handler that will be called at the time you send a message. When we want to send messages out these outlets, say, in our bang method, we do the following:

@code
	void myobject_bang(t_myobject *x)
	{
		outlet_bang(x->m_outlet2);
		outlet_int(x->m_outlet1, 74);
	}
@endcode

	The bang method above sends the bang message out the m_outlet2 outlet first, then sends the number 74 out the m_outlet1. This is consistent with the general design in Max to send values out outlets from right to left. However, there is nothing enforcing this design, and you could reverse the statements if you felt like it.

	A more general message-sending routine, outlet_anything(), will be shown in the @ref chapter_atoms section.


	@section chapter_inout_proxies Creating and Using Proxies

	A proxy is a small object that controls an inlet, but does not translate the message it receives. Instead it sets a location inside your object's data structure to a value you associate with the inlet. If the message comes "directly" to your object via the left inlet, the value will be 0.  However, in order to be thread-safe, you should not read the value of this "inlet number" directly. Instead, you'll use the proxy_getinlet() routine to determine the inlet that has received the message.

	The advantage of proxies over regular inlets is that your object can respond to any message in all of its inlets, not just the left inlet. As a Max user, you may already appreciate the proxy feature without knowing it. For example, the pack object can combine ints, floats, lists, or symbols arriving in any of its inlets. It uses proxies to make this happen. MSP audio objects that accept signals in more than one inlet use proxies as well. In fact, the proxy capability is built into the way you create audio objects, as will be discussed in the @ref chapter_msp_anatomy section.

	If your object's non-left inlets will only respond to ints or floats, implementing proxies is usually overkill.

	@section chapter_inout_example Example

	First, add a place in your object to store the proxy value. You shouldn't access this directly, but the proxy needs it. Second, you'll need to store the proxy, because you need to free it when your object goes away. If you create many proxies, you'll need to store pointers to all of them, but all proxies share the same long integer value field.

@code
	typedef struct _myobject
	{
		t_object m_obj;
		long m_in;			// space for the inlet number used by all the proxies
		void *m_proxy;
	} t_myobject;
@endcode

	In your new instance routine, create the proxy, passing your object, a non-zero code value associated with the proxy, and a pointer to your object's inlet number location.

@code
		x->m_proxy = proxy_new((t_object *)x, 1, &x->m_in);
@endcode

	If you want to create regular inlets for your object, you can do so. Proxies and regular inlets can be mixed, although such a design might confuse a user of your object.

	Finally, here is a method that takes a different action depending on the value of x->m_in that we check using proxy_getinlet().

@code
	 void myobject_bang(t_myobject *x)
	{
		switch (proxy_getinlet((t_object *)x)) {
			case 0:
				post("bang received in left inlet");
				break;
			case 1:
				post("bang received in right inlet");
				break;
		}
	}
@endcode

*/
