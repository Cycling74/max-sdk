/**
	@defgroup class Classes

	When a user types the name of your object into an object box,
	Max looks for an external of this name in the searchpath and, upon finding it,
	loads the bundle or dll and calls the ext_main() function.
	Thus, Max classes are typically defined in the ext_main() function of an external.

	Historically, Max classes have been defined using an API that includes functions like setup() and addmess().
	This interface is still supported, and the relevant documentation can be found in @ref class_old.

	A more recent and more flexible interface for creating objects was introduced with Jitter 1.0 and later
	included directly in Max 4.5.  This newer API includes functions such as class_new() and class_addmethod().
	Supporting attributes, user interface objects, and additional new features of Max requires the use of the
	newer interface for definiting classes documented on this page.

	You may not mix these two styles of creating classes within an object.

*/



/**
	@defgroup	class_old Old-Style Classes
	@ingroup	class
*/


/**
	@defgroup	inout Inlets and Outlets
	@ingroup	class

	Routines for creating and communicating with inlets and outlets.
*/