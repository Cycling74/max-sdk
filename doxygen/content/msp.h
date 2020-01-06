/**

	@defgroup msp MSP


	@defgroup buffers Buffers
	@ingroup msp

	Your object can access shared data stored in an MSP buffer~ object.
	Similar to table and coll objects, buffer~ objects are bound to a #t_symbol from which you can direct gain access to the t_buffer struct.
	This is potentially dangerous, and not guaranteed to be forward (or backward) compatible.
	Beginning with Max 6.1, developers accessing buffer~ objects are encouraged to use the #t_buffer_ref API.
	The #t_buffer_ref API provides many enhancements to improve thread-safety, simplify your perform routine,
	and manage the binding to the buffer~ object.

	A class that accesses a buffer~ is the simpwave~ object included with Max SDK example projects.

	While the Max 6 signal processing chain operates on 64-bit double-precision floats,
	the #t_buffer_obj storage remains as 32-bit single-precision float format.
	This is essential to maintain backward compatibility with older third-party externals.

	If you have written to the buffer~ and thus changed the values of its samples, you should now mark the buffer~ as dirty.
	This will ensure that objects such as waveform~ update their rendering of the contents of this buffer~.
	This can be accomplished with the following call:
@code
	object_method(b, gensym("dirty"));
@endcode



	@defgroup pfft PFFT
	@ingroup msp

	When an object is instantiated, it is possible to determine if it is being created in pfft~ context in the new method.
	In the new method (and only at this time), you can check the s_thing member of the #t_symbol '__pfft~__'.
	If this is non-null, then you will have a pointer to a #t_pfftpub struct.

	@code
	t_pfftpub *pfft_parent = (t_pfftpub*) gensym("__pfft~__")->s_thing;

	if (pfft_parent) {
		// in a pfft~ context
	}
	else {
		// not in a pfft~
	}
	@endcode



	@defgroup poly Poly
	@ingroup msp

	If your object is instatiated as a voice of a poly~ object, it is possible both to determine this context
	and to determine information about the specific voice.
	This is done by querying the patcher in which your object exists for an associated object, and then calling methods on that object.

	@code
	t_object *patcher = NULL;
	t_max_err err = MAX_ERR_NONE;
	t_object *assoc = NULL;
	method m = NULL;
	long voices = -1;
	long index = -1;

	err = object_obex_lookup(x, gensym("#P"), &patcher);
	if (err == MAX_ERR_NONE) {
		object_method(patcher, gensym("getassoc"), &assoc);
		if (assoc) {
			post("found %s", object_classname(assoc)->s_name);

			voices = object_attr_getlong(assoc, gensym("voices"));
			post("total amount of voices: %ld", voices);

			if(m = zgetfn(assoc, gensym("getindex")))
				index = (long)(*m)(assoc, patcher);
			post("index: %ld", index);
		}
	}

	@endcode



*/
