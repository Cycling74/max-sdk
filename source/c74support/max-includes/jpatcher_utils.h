#ifndef _JPATCHER_UTILS_H_
#define _JPATCHER_UTILS_H_

BEGIN_USING_C_LINKAGE

/**	Copy an array of atoms.
	@ingroup		atom
	@param	argc1	The count of atoms in argv1.
	@param	argv1	The address to the first of an array of atoms that is the source for the copy.
	@param	argv2	The address to the first of an array of atoms that is the destination for the copy.
					Note that this array must already by allocated using sysmem_newptr() or atom_alloc(). */
void atom_copy(long argc1, t_atom *argv1, t_atom *argv2);

//	Print the contents of an array of atoms to the Max window.
//	Internal C74 use only.
void postargs(long argc, t_atom *argv);

/**	Print the contents of a dictionary to the Max window.
	@ingroup		dictionary
	@param	d		A pointer to a dictionary object.	*/
void postdictionary(t_object *d);


/**	Return a pointer to an object contained in an atom if it is of the specified class.
	@ingroup		atom
	@param	x		The address of a pointer to the object contained in av if it is of the specified class upon return. 
					Otherwise NULL upon return.
	@param	idx		The index of the atom in the array from which to get the object pointer.
	@param	argc	The count of atoms in argv.
	@param	argv	The address to the first of an array of atoms.
	@param	cls		A symbol containing the class name of which the object should be an instance.
	@return			A Max error code.	*/
t_max_err atom_arg_getobjclass(t_object **x, long idx, long argc, t_atom *argv, t_symbol *cls);

/**	Return a pointer to an object contained in an atom if it is of the specified class.
	@ingroup		atom
	@param	av		A pointer to the atom from which to get the #t_object.
	@param	cls		A symbol containing the class name of which the object should be an instance.
	@return			A pointer to the object contained in av if it is of the specified class, otherwise NULL.	*/
void *atom_getobjclass(t_atom *av, t_symbol *cls);


method my_object_getmethod(void *obj, t_symbol *s);


END_USING_C_LINKAGE

#endif // #ifndef _JPATCHER_UTILS_H_
