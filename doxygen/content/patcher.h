/**
	@defgroup patcher Patcher
	Max's patcher represents a graph of objects that communicate with messages.
	This is the public interface to the jpatcher -- the new patcher object in Max 5.
	The jpatcher is fully controllable via obex attributes and methods.

	The jpatcher_api.h header defines constants, enumerations, symbols, structs,
	and functions for working with the jpatcher.
	It also includes utility functions for getting/setting attributes
	and for calling methods. These utilities are just wrapping the obex
	interface and thus loosely connect your code to the jpatcher implementation.

	Finally methods are defined for implementing your own boxes.

	@defgroup jpatcher jpatcher
	@ingroup patcher
	The patcher.

	@defgroup jbox jbox
	@ingroup patcher
	A box in the patcher.

	@defgroup jpatchline jpatchline
	@ingroup patcher
	A patch cord.

	@defgroup jpatcherview jpatcherview
	@ingroup patcher
	A view of a patcher.

*/
