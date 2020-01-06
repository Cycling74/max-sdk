/**
	@page chapter_anatomy Anatomy of a Max Object

	Max objects are written in the C language, and the Max API is C-based. You could use C++ but we don't support it at the API level. Writing a Max object in C, you have five basic tasks:

	1) including the right header files (usually ext.h and ext_obex.h)

	2) declaring a C structure for your object

	3) writing an initialization routine called ext_main that defines the class

	4) writing a new instance routine that creates a new instance of the class, when someone makes one or types its name into an object box

	5) writing methods (or message handlers) that implement the behavior of the object

	Let's look at each of these in more detail. It's useful to open the simplemax example project as we will be citing examples from it.


	@section chapter_anatomy_includes Include Files

	Most of the basic Max API is included in the files ext.h and ext_obex.h. These are essentially required for any object. Beyond this there are specific include files for more specialized objects.

	The header files are cross-platform.

	- jpatcher_api.h is required for any Max UI objects
	- z_dsp.h is required for MSP audio objects

@code
	#include "ext.h" // should always be first, followed by ext_obex.h and any other files.
@endcode


	@section chapter_anatomy_object_decl The Object Declaration

	Basic Max objects are declared as C structures. The first element of the structure is a #t_object, followed by whatever you want. The example below has one long structure member.

@code
	typedef struct _simp
	{
		t_object s_obj;		// t_object header
		long s_value;		// something else
	} t_simp;
@endcode

	Your structure declaration will be used in the prototypes to functions you declare, so you'll need to place above these prototypes.

	@section chapter_anatomy_object_init Initialization Routine

	The initialization routine, which must be called ext_main, is called when Max loads your object for the first time.
	In the initialization routine, you define one or more classes. Defining a class consists of the following:

	1) telling Max about the size of your object's structure and how to create and destroy an instance
	2) defining methods that implement the object's behavior
	3) in some cases, defining attributes that describe the object's data
	4) registering the class in a name space

	Here is the simp class example initialization routine:

@code
	static t_class *s_simp_class; // global pointer to our class definition that is setup in ext_main()

	void ext_main(void *r)
	{
		t_class *c;

		c = class_new("simp", (method)simp_new, (method)NULL, sizeof(t_simp), 0L, 0);
		class_addmethod(c, (method)simp_int, "int", A_LONG, 0);
		class_addmethod(c, (method)simp_bang, "bang", 0);

		class_register(CLASS_BOX, c);

		s_simp_class = c;
	}
@endcode

	In order for Max to call the ext_main() function on your compiled external, that function must be "exported" or made public.
	This is accomplished by using the C74_EXPORT macro in the prototype of the ext_main() function, which is provided for you automatically in the "ext.h" header file.

	class_new() creates a class with the new instance routine (see below), a free function (in this case there isn't one, so we pass NULL), the size of the structure, a no-longer used argument, and then a description of the arguments you type when creating an instance (in this case, there are no arguments, so we pass 0).

	class_addmethod() binds a C function to a text symbol. The two methods defined here are int and bang.

	class_register() adds this class to the #CLASS_BOX name space, meaning that it will be searched when a user tries to type it into a box.

	Finally, we assign the class we've created to a global variable so we can use it when creating new instances.

	More complex classes will declare more methods. In many cases, you'll declare methods to implement certain API features. This is particularly true for UI objects.


	@section chapter_anatomy_object_new New Instance Routine

	The standard new instance routine allocates the memory to create an instance of your class and then initializes this instance. It then returns a pointer to the newly created object.

	Here is the simp new instance routine

@code
	void *simp_new()
	{
		t_simp *x = (t_simp *)object_alloc(s_simp_class);

		x->s_value = 0;

		return x;
	}
@endcode

	The first line uses the global variable s_simp_class we defined in the initialization routine to create a new instance of the class. Essentially, the instance is a block of memory of the size defined by the class, along with a pointer to the class that permits us to dispatch messages correctly.

	The next line initializes our data. More complex objects will do a lot more here, such as creating inlets and outlets. By default, the object being created will appear with one inlet and no outlets.

	Finally, in the last line, we return a pointer to the newly created instance.


	@section chapter_anatomy_object_mess_handlers Message Handlers

	We are now ready to define some actual behavior for our object by writing C functions that will be called when our object is sent messages. For this simple example, we will write only two functions. simp_int will be called when our object receives numbers. It will store the received number in the s_value field. simp_bang will be called when our object receives a bang. It will print the value in the Max window. So, yes, this object is pretty useless!

	The C functions you write will be declared according to the arguments the message requires. All functions are passed a pointer to your object as the first argument. For a function handling the int message, a single second argument that is a long is passed. For a function handling the bang message, no additional arguments are passed.

	Here is the int method:

@code
	void simp_int(t_simp *x, long n)
	{
		x->s_value = n;
	}
@endcode

	This simply copies the value of the argument to the internal storage within the instance.

	Here is the bang method:

@code
	void simp_bang(t_simp *x)
	{
		post("value is %ld",x->s_value);
	}
@endcode

	The post() function is similar to printf(), but puts the text in the Max window. post() is very helpful for debugging, particularly when you cannot stop user interaction or real-time computation to look at something in a debugger.

	You can also add a float message, which is invoked when a floating-point number is sent to your object. Add the following to your initialization routine:

@code
		class_addmethod(c, (method)simp_float, "float", A_FLOAT, 0);
@endcode

	Then write the method that receives the floating-point value as follows:

@code
	void simp_float(t_simp *x, double f)
	{
		post("got a float and it is %.2f", f);
	}
@endcode

*/
