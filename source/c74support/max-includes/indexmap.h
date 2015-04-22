// indexmap.h copyright 2007 Cycling '74 all rights reserved

#ifndef _INDEXMAP_H_
#define _INDEXMAP_H_

BEGIN_USING_C_LINKAGE

#if !defined( _EXT_SYSTHREAD_H_ ) && !defined ( _SYSTHREAD_H_ )
typedef void *t_systhread_mutex;
#endif

/** An indexmap element. This struct is provided for debugging convenience, 
	but should be considered opaque and is subject to change without notice. 

	@ingroup indexmap
	@see t_indexmap
*/
typedef struct _indexmap_entry
{
	long	e_index;
	void	*e_data;
	long	e_mark;
} t_indexmap_entry;


/** An indexmap object. This struct is provided for debugging convenience, 
	but should be considered opaque and is subject to change without notice. 

	@ingroup indexmap
	@see t_indexmap_entry
*/
typedef struct _indexmap
{
	t_object m_ob;
	t_hashtab *m_data2index;			// convert from a data reference to an indexmap_entry (and hence index)
	t_indexmap_entry **m_index2data;	// convert from an index to a data reference
	long m_i2dsize;						// size of index2data array
	long m_count;						// how many items
	t_systhread_mutex m_mutex;			// protector
} t_indexmap;


// private -- initialize the indexmap class
void indexmap_initclass(void);


/** Create a new indexmap object.

	@ingroup indexmap
	@return Pointer to the new indexmap object.
*/
t_indexmap *indexmap_new(void);


/** Add an item to an indexmap.

	@ingroup		indexmap
	@param	x		The indexmap instance.
	@param	data	The item to add.
*/
void indexmap_append(t_indexmap *x, void *data);


/** Move an item to a different position in an indexmap.

	@ingroup			indexmap
	@param	x			The indexmap instance.
	@param	data		The item in the indexmap to move.
	@param	newindex	The new index to which to move the item.
	@return				A Max error code.
*/
t_max_err indexmap_move(t_indexmap *x, void *data, long newindex);


/** Delete a specified item from an indexmap.

	@ingroup		indexmap
	@param	x		The indexmap instance.
	@param	data	The item pointer to remove from the indexmap.
	@return			A Max error code.
*/
t_max_err indexmap_delete(t_indexmap *x, void *data);


/** Delete an item from the indexmap by index.

	@ingroup 		indexmap
	@param	x		The indexmap instance.
	@param	index	The index of the item to remove from the indexmap.
	@return			A Max error code.
*/
t_max_err indexmap_delete_index(t_indexmap *x, long index);


/** Delete multiple specified items from an indexmap.

	@ingroup		indexmap
	@param	x		The indexmap instance.
	@param	count	The number of items to remove from the indexmap.
	@param	pdata	The address of the first of an array of item pointers to remove from the indexmap.
	@return			A Max error code.
*/
t_max_err indexmap_delete_multi(t_indexmap *x, long count, void **pdata);


/** Delete multiple items from an indexmap by index.

	@ingroup		indexmap
	@param	x		The indexmap instance.
	@param	count	The number of items to remove from the indexmap.
	@param	indices	The address of the first of an array of index numbers to remove the indexmap.
	@return			A Max error code.
*/
t_max_err indexmap_delete_index_multi(t_indexmap *x, long count, long *indices);


/** Get an item from an indexmap by index.

	@ingroup		indexmap
	@param	x		The indexmap instance.
	@param	index	The index from which to fetch a stored item.
	@return			The item stored at the specified index.
*/
void *indexmap_datafromindex(t_indexmap *x, long index);


/** Find the index of an item given a pointer to the item.

	@ingroup		indexmap
	@param	x		The indexmap instance.
	@param	data	The item whose index you wish to look up.
	@param	index	The address of a variable to hold the retrieved index.
	@return			A Max error code.
*/
t_max_err indexmap_indexfromdata(t_indexmap *x, void *data, long *index);


/** Return the number of items in an indexmap.

	@ingroup	indexmap
	@param	x	The indexmap instance.
	@return		The number of items in the indexmap.
*/
long indexmap_getsize(t_indexmap *x);


/** Delete all items in an indexmap.

	@ingroup	indexmap
	@param	x	The indexmap instance.
*/
void indexmap_clear(t_indexmap *x);


/** Sort the items in an indexmap.
 	Item are sorted using a #t_cmpfn function that is passed in as an argument.

	@ingroup indexmap
	@param	x	The indexmap instance.
	@param	fn	The function used to sort the list.
	@see	linklist_sort()
*/
void indexmap_sort(t_indexmap *x, t_cmpfn fn);


END_USING_C_LINKAGE

#endif // _INDEXMAP_H_
