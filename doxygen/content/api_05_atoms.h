/**
	@page chapter_atoms Atoms and Messages

	When a Max object receives a message, it uses its class to look up the message selector ("int", "bang", "set" etc.) and invoke the associated C function (method). This association is what you are creating when you use class_addmethod() in the initialization routine. If the lookup fails, you'll see an "object doesn't understand message" error in the Max window.

	Message selectors are not character strings, but a special data structure called a symbol (#t_symbol). A symbol holds a string and a value, but what is more important is that every symbol in Max is unique. This permits you to compare two symbols for equivalence by comparing pointers, rather than having to compare each character in two strings.

	The "data" or argument part of a message, if it exists, is transmitted in the form of an array of atoms (#t_atom). The atom is a structure that can hold integers, floats, symbols, or even pointers to other objects, identified by a tag. You'll use symbols and atoms both in sending messages and receiving them.

	To illustrate the use of symbols and atoms, here is how you would send a message out an outlet. Let's say we want to send the message "green 43 crazy 8.34." This message consists of a selector "green" plus an array of three atoms.

	First, we'll need to create a generic outlet with outlet_new in our new instance routine.
@code
		x->m_outlet = outlet_new((t_object *)x, NULL);
@endcode

	The second argument being NULL indicates that the outlet can be used to send any message. If the second argument had been a character string such as "int" or "set" only that specific message could be sent out the outlet. You'd be correct if you wondered whether intout() is actually just outlet_new(x, "int").

	Now that we have our generic outlet, we'll call outlet_anything() on it in a method. The first step, however, is to assemble our message, with a selector "green" plus an array of atoms. Assigning ints and floats to an atom is relatively simple, but to assign a symbol, we need to transform a character string into a symbol using gensym(). The gensym() function returns a pointer to a symbol that is guaranteed to be unique for the string you supply. This means the string is compared with other symbols to ensure its uniqueness. If it already exists, gensym() will supply a pointer to the symbol. Otherwise it will create a new one and store it in a table so it can be found the next time someone asks for it.

@code
	void myobject_bang(t_object *x)
	{
		t_atom argv[3];

		atom_setlong(argv, 43);
		atom_setsym(argv + 1, gensym("crazy"));
		atom_setfloat(argv + 2, 8.34);

		outlet_anything(x->m_outlet, gensym("green"), 3, argv);
	}
@endcode

	In the call to outlet_anything() above, gensym("green") represents the message selector. The outlet_anything() function will try to find a message "green" in each of the objects connected to the outlet. If outlet_anything() finds such a message, it will execute it, passing it the array of atoms it received.

	If it cannot find a match for the symbol green, it does one more thing, which allows objects to handle messages generically. Your object can define a special method bound to the symbol "anything" that will be invoked if no other match is found for a selector. We'll discuss the anything method in a moment, but first, we need to return to class_addmethod() and explain the final arguments it accepts.

	To access atoms, you can use the functions atom_setlong(), atom_getlong() etc. or you can access the #t_atom structure directly. We recommend using the accessor functions, as they lead to both cleaner code and will permit your source to work without modifications when changes to the #t_atom structure occur over time.


	@section chapter_atoms_types Argument Type Specifiers

	In the simp example, you saw the int method defined as follows:
@code
		class_addmethod(c, (method)simp_int, "int", A_LONG, 0);
@endcode

	The #A_LONG, 0 arguments to class_addmethod() specify the type of arguments expected by the C function you have written. #A_LONG means that the C function accepts a long integer argument. The 0 terminates the argument specifier list, so for the int message, there is a single long integer argument.

	The other options are #A_FLOAT for doubles, #A_SYM for symbols, and #A_GIMME, which passes the raw list of atoms that were originally used to send the Max message in the first place. These argument type specifiers define what are known as "typed" methods in Max. Typed methods are those where Max checks the type of each atom in a message to ensure it is consistent with what the receiving object has said it expects for a given selector.

	If the atoms cannot be coerced into the format of the argument type specifier, a bad arguments error is printed in the Max window.

	There is a limit to the number of specifiers you can use, and in general, multiple #A_FLOAT specifiers should be avoided due to the historically unpredictable nature of compiler implementations when passing floating-point values on the stack. Use #A_GIMME for more than four arguments or with multiple floating-point arguments.

	You can also specify that missing arguments to a message be filled in with default values before your C function receives them. #A_DEFLONG will put a 0 in place of a missing long argument, #A_DEFFLOAT will put 0.0 in place of a missing float argument, and #A_DEFSYM will put the empty symbol (equal to gensym("")) in place of a missing symbol argument.


	@section chapter_atoms_gimme_funcs Writing A_GIMME Functions

	A method that uses #A_GIMME is declared as follows:
@code
	void myobject_message(t_myobject *x, t_symbol *s, long argc, t_atom *argv);
@endcode

	The symbol argument s is the message selector. Ordinarily this might seem redundant, but it is useful for the "anything" method as we'll discuss below.

	argc is the number of atoms in the argv array. It could be 0 if the message was sent without arguments. argv is the array of atoms holding the arguments.

	For typed messages, the atoms will be of type #A_SYM, #A_FLOAT, or #A_LONG. Here is an example of a method that merely prints all of the arguments.

@code
	void myobject_printargs(t_myobject *x, t_symbol *s, long argc, t_atom *argv)
	{
		long i;
		t_atom *ap;

		post("message selector is %s",s->s_name);
		post("there are %ld arguments",argc);

		// increment ap each time to get to the next atom
		for (i = 0, ap = argv; i < argc; i++, ap++) {
			switch (atom_gettype(ap)) {
				case A_LONG:
					post("%ld: %ld",i+1,atom_getlong(ap));
					break;
				case A_FLOAT:
					post("%ld: %.2f",i+1,atom_getfloat(ap));
					break;
				case A_SYM:
					post("%ld: %s",i+1, atom_getsym(ap)->s_name);
					break;
				default:
					post("%ld: unknown atom type (%ld)", i+1, atom_gettype(ap));
					break;
			}
		}
	}
@endcode

	You can interpret the arguments in whatever manner you wish. You cannot, however, modify the arguments as they may be about to be passed to another object.


@section chapter_atoms_anything_methods Writing "Anything" Methods

As previously mentioned, your object can define a special method bound to the symbol "anything" that will be invoked if no other match is found for a selector.  For example:
@code
	class_addmethod(c, (method)myobject_anything, "anything", A_GIMME, 0);
@endcode

Your function definition for an anything method follows the same pattern as for all other #A_GIMME methods:
@code
	void myobject_anything(t_myobject *x, t_symbol *s, long argc, t_atom *argv)
	{
		object_post( (t_object*)x,
					 "This method was invoked by sending the '%s' message to this object.",
					  s->s_name);
		// argc and argv are the arguments, as described in above.
	}
@endcode


*/
