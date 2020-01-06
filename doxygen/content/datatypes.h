/**
   @defgroup datatypes Data Types
*/


/**
	@defgroup atom Atoms
	@ingroup datatypes
*/




/**
	@defgroup atombuf Atombufs
	@ingroup datatypes

	An Atombuf is an alternative to @ref binbuf for temporary storage of atoms.
	Its principal advantage is that the internal structure is publicly
	available so you can manipulate the atoms in place.
	The standard Max text objects (message box, object box, comment) use the Atombuf
	structure to store their text (each word of text is stored as a #t_symbol or a number).
*/


/**
	@defgroup binbuf Binbufs
	@ingroup datatypes

	You won’t need to know about the internal structure of a Binbuf, so
	you can use the void * type to refer to one.
*/



/**
	@defgroup symbol Symbols
	@ingroup datatypes

	Max maintains a symbol table of all strings
	to speed lookup for message passing. If you want to access the bang
	symbol for example, you’ll have to use the expression
	gensym("bang").
	For example, gensym() may be needed when sending
	messages directly to other Max objects such as with object_method() and
	outlet_anything(). These functions expect a #t_symbol*, they don’t
	gensym() character strings for you.

	The #t_symbol data structure also contains a place to store an arbitrary
	value. The following example shows how you can use this feature to
	use symbols to share values among two different external object
	classes. (Objects of the same class can use the code resource’s global
	variable space to share data.) The idea is that the s_thing field of a
	#t_symbol can be set to some value, and gensym() will return a
	reference to the Symbol. Thus, the two classes just have to agree about
	the character string to be used. Alternatively, each could be passed a
	#t_symbol that will be used to share data.

	Storing a value:

	@code
	t_symbol *s;
	s = gensym("some_weird_string");
	s->s_thing = (t_object *)someValue;
	@endcode

	Retrieving a value:

	@code
	t_symbol *s;
	s = gensym("some_weird_string");
	someValue = s->s_thing;
	@endcode

*/

