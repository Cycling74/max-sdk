/**
	@page chapter_datastructures Data Structures



	@section chapter_datastructures_types Available Data Structures

	The Max API provides a variety of useful data structures which may be used across platforms and provide basic thread-safety.

		- @ref atomarray 	: container for an array of atoms
		- @ref linklist  	: doubly-linked-list
		- @ref hashtab   	: hash table for mapping symbols to data
		- @ref quickmap  	: a double hash with keys mapped to values and vice-versa
		- @ref database  	: SQLite database access
		- @ref indexmap  	: managed array of pointers
		- @ref string    	: wrapper for C-strings with an API for manipulating them
		- @ref symobject 	: wrapper for symbols
		- @ref dictionary	: structured/hierarchical data that is both sortable and fast


	@section chapter_datastructures_passing Passing Data Structures

	Most often, the use of a particular instance of a data structure will be limited to within the confines a single class or object you create.
	However, in some cases you may wish to pass structured data from one object to another.
	For this purpose, Max 6 introduced facilities for passing named #t_dictionary instances.

	Examples, descriptions, and API documentation can be found in @ref dictobj .
**/
