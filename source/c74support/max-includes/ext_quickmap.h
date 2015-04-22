
#ifndef __QUICKMAP_H__
#define __QUICKMAP_H__

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif


/** The quickmap object. This struct is provided for debugging convenience, 
	but should be considered opaque and is subject to change without notice. 

	@ingroup quickmap
*/
typedef struct _quickmap {
	t_object m_obj;
	t_hashtab *m_p1key;
	t_hashtab *m_p2key;
} t_quickmap;


#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif


BEGIN_USING_C_LINKAGE

/** 
	Create a new quickmap object.

	@ingroup	quickmap	
	@return		Pointer to the new quickmap object.
*/
void *quickmap_new(void);


/** 
	Add a pair of keys mapped to each other to the quickmap.
	Note that these are considered to be a #t_symbol internally.  
	This means that if you are mapping a #t_symbol to a #t_object, for example, the #t_object will not automatically be 
	freed when you free the quickmap (unlike what happens when you typically free a #t_hashtab).

	@ingroup	quickmap
	
	@param	x	The quickmap instance.
	@param	p1	The (first) key.
	@param	p2	The value (or the second key).
	@return		A Max error code.
*/
void quickmap_add(t_quickmap *x, void *p1, void *p2);


/** 
	Drop a pair of keys mapped to each other in the quickmap.

	@ingroup	quickmap
	
	@param	x	The quickmap instance.
	@param	p1	The first key.
	@param	p2	The second key.
	@return		A Max error code.
*/
void quickmap_drop(t_quickmap *x, void *p1, void *p2);


/** 
	Given a (first) key, lookup the value (the second key).

	@ingroup	quickmap
	
	@param	x	The quickmap instance.
	@param	p1	The (first) key.
	@param	p2	The address of a pointer which will hold the resulting key upon return.
	@return		A Max error code.
*/
long quickmap_lookup_key1(t_quickmap *x, void *p1, void **p2);


/** 
	Given a (second) key, lookup the value (the first key).

	@ingroup	quickmap
	
	@param	x	The quickmap instance.
	@param	p1	The (second) key.
	@param	p2	The address of a pointer which will hold the resulting key upon return.
	@return		A Max error code.
*/
long quickmap_lookup_key2(t_quickmap *x, void *p1, void **p2);


/** 
	Set the readonly flag of the quickmap's hash tables.
	See hashtab_readonly() for more information about this.

	@ingroup	quickmap
	
	@param	x	The quickmap instance.
	@param	way	Set to true to make the quickmap readonly (disable thread protection)
	 			or false (the default) to enable thread protection.
*/
void quickmap_readonly(t_quickmap *x, long way);


END_USING_C_LINKAGE

#endif // __QUICKMAP_H__
