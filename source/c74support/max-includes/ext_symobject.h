#ifndef __SYMOBJECT_H__
#define __SYMOBJECT_H__

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif


/** The symobject data structure. 
	@ingroup symobject
*/
typedef struct _symobject{
	t_object	obj;		///< Max object header.
	t_symbol	*sym;		///< The symbol contained by the object.
	long		flags;		///< Any user-flags you wish to set or get.
	void		*thing;		///< A generic pointer for attaching additional data to the symobject.
} t_symobject;


#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif


#ifdef __cplusplus
	extern "C" {
#endif // __cplusplus


// private
void symobject_initclass(void);


/** The symobject data structure. 

	@ingroup		symobject
	@param	sym		A symbol with which to initialize the new symobject.
	@return			Pointer to the new symobject instance.
*/
void *symobject_new(t_symbol *sym);


/** Utility for searching a linklist containing symobjects.

	@ingroup		symobject
	@param	a		(opaque)
	@param	b		(opaque)
	@return			Returns true if a match is found, otherwise returns false.
	
	@remark			The following example shows one common use of the this method.
	@code
	t_symobject	*item = NULL;
	long		index;
	t_symbol	*textsym;
	
	textsym = gensym("something to look for");

	// search for a symobject with the symbol 'something to look for'
	index = linklist_findfirst(s_ll_history, (void **)&item, symobject_linklist_match, textsym);
	if(index == -1){
		// symobject not found.
	}
	else{
		do something with the symobject, or with the index of the symbobject in the linklist
	}	
	@endcode
	
*/
long symobject_linklist_match(void *a, void *b);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SYMOBJECT_H__
