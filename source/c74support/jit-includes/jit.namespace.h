#ifndef __JIT_NAMESPACE_H__
#define __JIT_NAMESPACE_H__

// object structs
typedef struct _jit_namespace_data
{
	t_jit_object			ob;
	t_symbol				*name;
	void					*data;
} t_jit_namespace_data;

typedef struct _jit_namespace
{
	t_jit_object			ob;
	void					*reference;
	t_jit_linklist			*list;
} t_jit_namespace;

void jit_namespace_init(void);
void *jit_namespace_lookup(void *reference);
void *jit_namespace_attach(void *reference, t_symbol *name, void *data);
void *jit_namespace_attach_decorated(void *reference, t_symbol *name, void *data, t_symbol **out_name);

/* 

////// available methods

t_jit_namespace *jit_namespace_lookup(void *reference);
	returns the namespace associated with a particular reference, or NULL if one doesn't exist.
	
t_jit_namespace *jit_namespace_attach(void *reference, t_symbol *name, void *data);
	attaches a name and data to the namespace associated with a particular reference, creating
	a new namespace for that reference if one doesn't yet exist. returns the namespace, or NULL
	if the method fails.


////// object messages (t_jit_namespace)

long jit_object_method(t_jit_namespace *ns, gensym("getsize"));
	returns the size of the namespace
	
long jit_object_method(t_jit_namespace *ns, gensym("findsize"), long cmpfn(void *, void *), void *cmpdata);
	returns the number of namespace elements matching the comparison criteria

void *jit_namespace_iterate(t_jit_namespace *x, long *index);
	returns the t_jit_namespace_data object associated with a particular index. to use, pass a
	long pointer to 0 in index. the index will be incremented automatically, so a while() loop
	can be used to iterate every member.

void jit_object_method(t_jit_namespace *ns, gensym("findfirst"), t_jit_namespace_data **out, long cmpfn(void *, void *), void *cmpdata);
	returns (in the out field) a pointer to the first t_jit_namespace_data object matching the 
	comparison criteria.

void jit_object_method(t_jit_namespace *ns, gensym("findall"), t_jit_linklist **out, long cmpfn(void *, void *), void *cmpdata);
	returns (in the out field) a pointer to a t_jit_linklist object containing pointers to 
	all of the t_jit_namespace_data objects matching the comparison criteria. the user must
	dispose of the linklist using "chuck", or the t_jit_namespace_data objects will be freed,
	and havok will be unleashed upon the earth.

void jit_namespace_sort(t_jit_namespace *x, long cmpfn(void *, void *));
	sorts the namespace members based on the comparison function.

void *jit_object_method(t_jit_namespace *ns, gensym("detach"), t_symbol *name);
	detaches a name from the namespace. (detaching a name doesn't affect the associated
	data, although it's no longer attached to the namespace. if the data contains objects
	which must be freed, the user must manually do this). returns the namespace pointer, or NULL
	if the namespace was freed in the detach.
	
void *jit_namespace_detachall(t_jit_namespace *x);
	detaches all names from the namespace. returns the namespace pointer, or NULL
	if the namespace was freed in the detach.
	
void *jit_namespace_finddetach(t_jit_namespace *x, long cmpfn(void *, void *), void *cmpdata)
	detaches all names from the namespace matching the comparison criteria. returns the 
	namespace pointer, or NULL if the namespace was freed in the detach.

void *jit_object_method(t_jit_namespace *ns, gensym("add"), t_symbol *name, void *data);
	attaches a name and data to a known namespace, and returns the namespace pointer if successful,
	or NULL if not.

void *jit_object_method(t_jit_namespace *ns, gensym("replace"), t_symbol *name, void *data);
	replaces the data associated with a name within a known namespace, and returns the namespace 
	pointer if successful, or NULL if not.

t_symbol *jit_object_method(t_jit_namespace *ns, gensym("gettype"), t_symbol *name);
	returns a symbol describing the type of data associated with a name. if the data
	is a t_jit_attribute (or compatible), this method will return the type of data stored in
	the attribute (char, long, float, etc.). otherwise, if the data points to an object,
	this method returns the object's class name, or an empty symbol if the data can't be typed.
	the method will resolve any namespace hierarchies.

t_symbol *jit_object_method(t_jit_namespace *ns, gensym("ob_sym"), t_symbol *name);
	if the data associated with a name points to an object, this method returns the object's
	class name. otherwise, it returns an empty symbol. the method will resolve any 
	namespace hierarchies.

t_jit_namespace_data *jit_object_method(t_jit_namespace *ns, gensym("resolve_name"), t_symbol *name);
	returns a pointer to the t_jit_namespace_data object associated with a particular name,
	resolving any namespace hierarchies ("foo::bar").

void *jit_object_method(t_jit_namespace *x, gensym("resolve_raw"), t_symbol *name);
	returns a pointer to the data stored with a name, resolving any namespace hierarchies.

t_jit_err jit_object_method(t_jit_namespace *x, gensym("resolve_char"), t_symbol *name, long *size, uchar **data);
t_jit_err jit_object_method(t_jit_namespace *x, gensym("resolve_long"), t_symbol *name, long *size, long **data);
t_jit_err jit_object_method(t_jit_namespace *x, gensym("resolve_float"), t_symbol *name, long *size, float **data);
t_jit_err jit_object_method(t_jit_namespace *x, gensym("resolve_double"), t_symbol *name, long *size, double **data);
t_jit_err jit_object_method(t_jit_namespace *x, gensym("resolve_symbol"), t_symbol *name, long *size, t_symbol ***data);
t_jit_err jit_object_method(t_jit_namespace *x, gensym("resolve_atom"), t_symbol *name, long *size, t_atom **data);
t_jit_err jit_object_method(t_jit_namespace *x, gensym("resolve_object"), t_symbol *name, long *size, t_object ***data);
t_jit_err jit_object_method(t_jit_namespace *x, gensym("resolve_pointer"), t_symbol *name, long *size, void ***data);
	when used with attribute-compatible data, returns a vector of typed data (data), 
	and the vector's size (size) stored with a name, resolving any namespace hierarchies.

////// object messages (t_jit_namespace_data)

t_symbol *jit_object_method(t_jit_namespace_data *nsd, gensym("getname"));
	returns the data's name

void *jit_object_method(t_jit_namespace_data *nsd, gensym("getdata"));
	returns the data pointer
	
t_symbol *jit_object_method(t_jit_namespace_data *nsd, gensym("gettype"));
	returns a symbol describing the type of the data. if the data
	is a t_jit_attribute (or compatible), this method will return the type of data stored in
	the attribute (char, long, float, etc.). otherwise, if the data points to an object,
	this method returns the object's class name, or an empty symbol if the data can't be typed.
	
t_symbol *jit_object_method(t_jit_namespace_data *nsd, gensym("ob_sym"));
	if the data points to an object, this method returns the object's
	class name. otherwise, it returns an empty symbol. 
	
*/

#endif // __JIT_NAMESPACE_H__
