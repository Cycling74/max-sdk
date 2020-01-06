/**	@defgroup datastore Data Storage

	Max provides a number of ways of storing and manipulating data at a high level.
	It is recommended to use Max's data storage mechanisms where possible,
	as Max's systems are designed for thread-safety and integration with the rest of Max API.
**/



/**	@defgroup atomarray Atom Array
	@ingroup datastore

	Max's atomarray object is a container for an array of atoms with an interface for manipulating that array.
	It can be useful for passing lists as a single atom, such as for the return value of an #A_GIMMEBACK method.
	It also used frequently in when working with Max's #t_dictionary object.

	@see dictionary
**/



/**	@defgroup database Database
	@ingroup datastore

	Max's database ( i.e. #t_database ) support currently consists of a SQLite ( http://sqlite.org ) extension which is loaded
	dynamically by Max at launch time.
	Because it is loaded dynamically, all interfacing with the sqlite object relies on Max's message passing interface,
	using object_method() and related functions.

	For most common database needs, a C-interface is defined in the ext_database.h header file and implemented in the
	ext_database.c source file.  The functions defined in this interface wrap the message passing calls and provide
	a convenient means by which you can work with databases.
 	ext_database.c is located in the 'common' folder inside of the 'max-includes' folder.
	If you use any of the functions defined ext_database.h, you will need to add ext_database.c to your project.
**/



/**	@defgroup dictionary Dictionary
	@ingroup datastore

	Max 5, introduced the #t_dictionary structure/object.
	This is used for object prototypes, object serialization, object constructors, and many other tasks.
	A dictionary is ultimately a collection of atom values assigned to symbolic keys.
	In addition to primitive #A_LONG, #A_FLOAT, and #A_SYM atom types,
	the #A_OBJ atom type is used for #t_atomarray (for a set of atoms assigned to a key),
	#t_dictionary (for hierarhical use),
	#t_string (for large blocks of text which we don't wish to bloat the symbol table), and potentially other object data types.
	Internally, the dictionary object uses a combination data structure of a hash table (for fast key lookup)
	and a linked-list (to maintain ordering of information within the dictionary).

	Dictionaries are clonable entites, but note that all the member objects of a given dictionary may not be clonable.
	At the time of this writing, for example, the #t_string object is not clonable, though it will be made clonable in the near future.
	In order for prototype entities to be g  uaranteed their passage into the constructor,
	they must be clonable (currenlty a symbol conversion is in place for the t_string class).


	@section using_dictionaries Using Dictionaries

	Dictionaries are used in many places in Max 5. They can be confusing in many respects.
	It is easy to produce memory leaks or bugs where objects are freed twice.
	It is easy to confuse what type of dictionary is used for what.
	This page will begin with some high level information to help understand when to free and when not to free.
	Then, we will offer recipies for using dictionaries to accomplish common tasks.


	@subsection understanding_dictionaries Understanding Dictionaries

	A dictionary stores atom values under named key entries. These atoms can contain #A_OBJ values.
	When the dictionary is freed, any #A_OBJ values that are in the dictionary will also be freed.
	Thus, it is easy to mistakenly free objects twice, thus this is something to be careful about.
	For example, look at this code:

	@code
	t_dictionary *d = dictionary_new();
	t_dictionary *sd = dictionary_new();
	dictionary_appenddictionary(d, gensym("subdictionary"), sd);
	do_something(d);
	object_free(d);  // this will free *both* d and sd since sd is contained by d
	// freeing "sd" here would be bad
	@endcode

	You primarily need to keep this in mind when calling dictionary_appendobject(), dictionary_appenddictionary(), or dictionary_appendatomarray().
	So, what do you do if you need to free a dictionary but you also want to hang on to an object that is inside of the dictionary?
	In this case, chuck the entry in question first.
	For example, let's assume that for some reason you cannot free the "sd" dictionary in the code above.
	Perhaps it doesn't belong to you. But, to do some operation you need to append it to a new dictionary.
	Then, do this:

	@code
	void function_foo(t_dictionary *sd) {
	  t_dictionary *d = dictionary_new();
	  dictionary_appenddictionary(d, gensym("subdictionary"), sd);
	  do_something(d);
	  dictionary_chuckentry(d, gensym("subdictionary"));
	  object_free(d);
	}
	@endcode


	@subsection when_to_free_a_dictionary When to Free a Dictionary

	So, how do you know when you need to free a dictionary?
	Well, generally if you make a dictionary, you need to free it when you are done (unless you transfer ownership of the dictionary to someone else).
	On the other hand, if you are passed a dictionary (i.e. as a parameter of your function or method)
	then it is not yours to free and you should just use it.
	However, it is not always obvious that you made a dictionary vs just borrowed it.

	Here are some common (and not so common) ways to make a dictionary.
	These functions return a new dictionary and thus the dictionary you get should be freed when you are done,
	unless you pass the dictionary on to someone else who will free it at an appropriate time. Here they are:

		- dictionary_new()
		- dictionary_clone()
		- dictionary_read()
		- dictionary_sprintf()
		- dictionary_vsprintf()
		- jsonreader_parse()
		- jpatcher_monikerforobject()
		- class_cloneprototype()
		- prototype_getdictionary()
		- clipboard_todictionary()
		- jpatchercontroller_copytodictionary()
		- probably others of course


	Here are some functions that return borrowed dictionaries.
	These are dictionaries that you can use but you cannot free since you do not own them.
	Here they are:

		- dictionary_prototypefromclass()
		- object_refpage_get_class_info_fromclassname()
		- object_refpage_get_class_info()
		- object_dictionaryarg()


	Finally, most functions that accept dictionaries as parameters will not assume ownership of the dictionary.
	Usually the way ownership is assumed is if you add a dictionary as a subdictionary to a dictionary that you do not own.
	One exception is the utility newobject_fromdictionary_delete()
	who's name makes it clear that the dictionary will be deleted after calling the function.


	@subsection dictionaries_common_uses Some Common Uses of Dictionaries

	You can make a patcher by passing a dictionary to object_new_typed() when making a "jpatcher".
	Using atom_setparse() and attr_args_dictionary() makes this relatively easy.

	Use newobject_sprintf() to programmatically make an object in a patch.
	Actually, you don't explicitly use a dictionary here!
	If you do want more control, so you can touch the dictionary to customize it, then see the next bullet.

	Use dictionary_sprintf() to make a dictionary to specify a box (i.e. specify class with \@maxclass attr).
	Then, make another dictionary and append your box dictionary to it under the key "box" via dictionary_appenddictionary().
	Finally, make your object with newobject_fromdictionary().

	@see linklist
	@see hashtab

	@version 5.0


	@section dictionaries_serialization_and_deserialization Reading and Writing Dictionaries as JSON

	@subsection dictionaries_deserialization Creating a Dictionary from JSON

	The easiest way to get read a t_dictionary from a JSON file on disk is to use the dictionary_read() function.
	In some cases you may wish have more control, such as to generate JSON but not write it to disk.
	For that purpose you can create a jsonreader object as demonstrated below.

	@code
	t_dictionary	*d = NULL;
	t_max_err		err;
	t_atom			result[1];
	t_object		*jsonreader = (t_object*)object_new(_sym_nobox, _sym_jsonreader);

	// assume we have an argument called 'jsontext' which is a const char* with the JSON
	// from which we wish to create a t_dictionary instance

	err = (t_max_err)object_method(jsonreader, _sym_parse, jsontext, result);
	if (!err) {
		t_object *ro = (t_object*)atom_getobj(result);

		if (ro) {
			if (object_classname_compare(ro, _sym_dictionary))
				d = (t_dictionary*)ro;
			else
				object_free(ro);
		}
	}
	object_free(jsonreader);

	// we now have a t_dictionary in d that can be used as we see fit
	@endcode




	@subsection dictionaries_serialization Creating JSON from a Dictionary

	The easiest way to get write a t_dictionary to disk as JSON is to use the dictionary_write() function.
	In some cases you may wish have more control, such as to generate JSON but not write it to disk.
	For that purpose you can create a jsonwriter object as demonstrated below.

	@code
	t_object	*jsonwriter = (t_object*)object_new(_sym_nobox, _sym_jsonwriter);
	t_handle	json;
	const char	*str;

	object_method(jsonwriter, _sym_writedictionary, d);
	object_method(jsonwriter, _sym_getoutput, &json);

	str = *json;

	// now str contains our JSON serialization of the t_dictionary d

	object_free(jsonwriter);
	@endcode
**/



/**	@defgroup hashtab Hash Table
	@ingroup datastore

	A hash table is a data structure that associates some data with a unique key. If you know the key, you can get back the data much more quickly than with a linked list, particularly as the number of items stored grows larger. The Max hash table #t_hashtab is optimized to work with symbol pointers as keys, but you can use any pointer or number, as long as it is unique.

	To create a #t_hashtab, you use hashtab_new(). To add items, use hashtab_store(). To find items that have been added, use hashtab_lookup().

	By contrast with linked lists and arrays, hash tables do not have a strong sense of ordering. You can iterate through all items using hashtab_funall(), but the exact order is not under your control as items are added and removed. There is also no way to "sort" a hash table.

	Example:

	The following example creates a hashtab, shows how to add some data (in this case, just a number), look it up, and delete the hashtab.

	@code
	t_hashtab *tab = (t_hashtab *)hashtab_new(0);
	long result, value;

	hashtab_store(tab, gensym("a great number"), (t_object *)74);

	result = hashtab_lookup(tab, gensym("a great number"), (t_object **)value);

	if (!result)
		post("found the value and it is %ld",value);
	else
		post("did not find the value");

	hashtab_chuck(tab);
	@endcode

	Note that the Max #t_dictionary used for managing patcher data is implemented internally using both a #t_hashtab and a #t_linklist in parallel.
	The #t_hashtab provides fast access, and the #t_linklist provides sorting.

	@see http://en.wikipedia.org/wiki/Hash_table
	@see linklist
**/



/**	@defgroup indexmap Index Map
	@ingroup datastore

	An indexmap is basically a managed array of pointers,
	but it allows you to derive relatively quickly the index from a pointer in the array.

	The index is assumed to be 0-N (where N is the current size of the array).
	You can sort the data and retain access to an index from the data relatively quickly.
	There is a hashtab which holds pieces of memory that hold indices that can be referenced by the data pointer.
	There is also an array of data pointers -- this is in "index" order.
	When operations take place on the array (insert, delete, sort), the pointers in the hashtab are updated with new indices.
**/



/**	@defgroup linklist Linked List
	@ingroup datastore

	The Max #t_linklist data structure is useful for maintaining ordered lists of items where you want to be able to insert and delete items efficiently. Random access of individual items, however, gets appreciably slower as the list grows in size. The #t_linklist is thread-safe by default, but thread safety can be turned off for performance benefits in single-threaded applications. However, ensure that your use of the linked list is truly single-threaded (based on an understanding of Max's @ref chapter_threading model) before turning off the thread safety features.

	By default, the #t_linklist holds pointers to Max objects. However, you can treat what the linklist holds as data rather than objects to be freed by using the linklist_flags() function.

	Here is a simple example of the use of #t_linklist. The code below stores five symbols, sorts them, searches for a specific item, deletes an item, prints all items, and then frees the entire structure. Since symbols in Max are never freed, linklist_flags() is used to specify that data, rather than object pointers, are being stored.

@code
	void mylistfun()
	{
		t_linklist *list;

		list = (t_linklist *)linklist_new();
		linklist_flags(list, OBJ_FLAG_DATA);

		// add some data
		linklist_append(list, gensym("one"));
		linklist_append(list, gensym("two"));
		linklist_append(list, gensym("three"));
		linklist_append(list, gensym("four"));
		linklist_append(list, gensym("five"));

		// sort
		linklist_sort(list, (t_cmpfn)mysortfun);

		// search
		index = linklist_findfirst(list, &found, mysearchfun, gensym("four"));	// find the "four" symbol
		if (index != -1)	// found
			linklist_chuckindex(list, index);

		// iterate
		linklist_funall(list, myprintfun, NULL);

		// delete
		linklist_chuck(list);
	}
@endcode

	The sorting function compares two items in the list and returns non-zero if the first one should go before the second one.

@code
	long mysortfun(void *a, void *b)
	{
		t_symbol *sa = (t_symbol *)a;
		t_symbol *sb = (t_symbol *)b;

		return strcmp(sa->s_name, sb->s_name) > 0;
	}
@endcode

	The search function is passed the final argument to linklist_findfirst() and, in this case, just returns the symbol that matches, which is just testing for pointer equivalence since all Max symbols are unique. You could do more sophisticated searching if you store more complex data in a linklist.

@code
	long mysearchfun(t_symbol *elem, t_symbol *match)
	{
		return elem == match;
	}
@endcode

	The iteration function takes some action on all items in the list. The third argument to linklist_funall() is passed as the second argument to your iteration function. In this example, we don't do anything with it.

@code
	void myprintfun(t_symbol *item, void *dummy)
	{
		post("%s",item->s_name);
	}
@endcode

	@see http://en.wikipedia.org/wiki/Linked_list

**/



/**	@defgroup quickmap Quick Map
	@ingroup datastore

	A quickmap implements a pair of #t_hashtab hash tables so that it is fast to look up a unique value for a unique key or vice-versa.
	This implies that both the keys and the values must be unique so that look-ups can be performed in both directions.
**/



/**	@defgroup string String Object
	@ingroup datastore

	Max's string object is a simple wrapper for c-strings, useful when working with Max's #t_dictionary, #t_linklist, or #t_hashtab.

	@see dictionary
**/



/**	@defgroup symobject Symbol Object
	@ingroup datastore

	The symobject class is a simple object that wraps a #t_symbol* together with a couple of additional fields.
	It is useful for storing symbols, possibly with additional flags or pointers, into a @ref hashtab or  @ref linklist.

	@version 5.0
**/



/**	@defgroup dictobj Dictionary Passing API
	@ingroup datastore

	The Dictionary Passing API defines a means by which #t_dictionary instances may be passed between Max objects
	in a way similar to the way Jitter Matrices are passed between objects.
	There are important differences, however, between Jitter matrix passing and dictionary passing.
	Many of these differences are documented in Max's documentation on dictionaries and structured data.

	Every dictionary instance in this system is mapped to a unique name that identifies the dictionary.
	Dictionaries are passed between objects using the "dictionary" message with a single argument, which is the name of the dictionary.


	@section using_dictobj_accessing Registration and Access

	The C-API for working with these dictionaries is composed of 5 primary registration/access methods:

		- dictobj_register()				: register a #t_dictionary instance with the system, and map the instance to a name
		- dictobj_unregister()			: unregister a #t_dictionary from the system
		- dictobj_findregistered_clone()	: find the #t_dictionary for a given name, and return a <i>copy</i> of that dictionary
		- dictobj_findregistered_retain()	: find the #t_dictionary for a given name, return a pointer to that #t_dictionary, and increment its reference count.
		- dictobj_release()				: for a #t_dictionary/name that was previously retained with dictobj_findregistered_retain(), release it (decrement its reference count).


	It is useful to think of objects in the dictionary system as "nouns" and "verbs".

	A "noun" is an object that possess or owns a dictionary.
	These objects are servers whose dictionary will accessed by other object that are clients.
	An example of a "noun" is the dict.pack object that creates a dictionary that is passed to other objects.

	A "verb" is an object that does not maintain its own dictionary (it is not a thing) but merely does something to any dictionaries it receives.
	This object is a client rather than a server.
	An example of a "verb" is the dict.strip object, which removes entries from an existing dictionary but possesses no dictionary of its own.

	Any object which is a dictionary "noun", can keep and rely on their dictionary pointer.
	Because of the way object_register() works, there should be no possiblity for this pointer to change behind the scenes.
	They each need to call object_free() on their respective object pointer, however.
	A call to object_free() also calls object_unregister() once, so there's technically not a need to unregister from the owner itself.
	They work like jit.matrix (and similar to buffer~), and use object_register() to increment a server reference count.
	If an object has already registered an object with the given name, the pointer passed in to register is freed and the existing one is returned from the registration function.

	Dictionary "verbs" on the other hand should just call dict_findregistered_retain() and dict_release() when done.
	They are not incrementing the server reference count.
	They increment a reference count with regards to object freeing, which is compatible with and complementary to the server reference count.


	@section using_dictobj_syntax Dictionary Syntax

	Dictionaries may be represented in a variety of textual formats including JSON.
	Max also supports a compact YAML-like dictionary notation which is useful for proving data structure contents as lists of atoms in object boxes.
	This format is documented in Max's documentation of the dictionary features.
	The following functions are used for formatting and parsing the dictionary syntax.

		- dictobj_jsonfromstring()
		- dictobj_dictionaryfromstring()
		- dictobj_dictionaryfromatoms()
		- dictobj_dictionarytoatoms()



	@section using_dictobj_utilities Utilities

	There are several utility functions available to assist in coding objects that pass dictionaries.

		- dictobj_outlet_atoms()
		- dictobj_atom_safety()
		- dictobj_validate()


	The dictobj_validate() object is a utility routine for validating a dictionary against "schema" dictionary.
	This enables a behavior somewhat analogous to Objective-C or Smalltalk prototypes.
	Dictionary validation can be useful to implement a kind of dictionary polymorphism.
	For a multiple-inheritance behavior, simply validate a dictionary against multiple schemas to verify the presence of required keys and values.


	@section using_dictobj_limitations Limitations

	The dict_outlet_atoms() function will not output #A_OBJ atoms directly (nor should any other object) and
	as such it will also not output #t_atomarray instances containing objects,
	thus atomarrays are <i>not</i> hierarchical in the dictionary passing implementation.

	It will output an atom array if provided a single A_OBJ atom with class atomarray.
	If there is an array of atoms which contain A_OBJ atoms, they are converted to the *symbols* <dictionary-object>, <atomarray-object>, <string-object>, <other-object> respectively.
	Ideally such a case should never be reached if everything which inserts values into a dictionary is well behaved--i.e.

	 	- a key may be a single atom
		- a key may be an atomarray (but no A_OBJ atoms)
		- a key may be a dictionary



	@version 6.0
**/