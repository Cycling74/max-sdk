#ifndef __EXT_GLOBALSYMBOL_H__
#define __EXT_GLOBALSYMBOL_H__

BEGIN_USING_C_LINKAGE

/**	Get a reference to an object that is bound to a #t_symbol.
	@ingroup misc
	@param	x			The object that is getting the reference to the symbol.
	@param	name		The name of the symbol to reference.
	@param	classname	The name of the class of which the object we are referencing should be an instance.
	@return				The s_thing of the #t_symbol.
	
	@remark				An example of real-world use is to get the buffer~ object associated with a symbol.
	@code
	// the struct of our object
	typedef struct _myobject {
		t_object	obj;
		t_symbol	*buffer_name;
		t_buffer	*buffer_object;
	} t_myobject;
	
	void myobject_setbuffer(t_myobject *x, t_symbol *s, long argc, t_atom *argv)
	{		
		if(s != x->buffer_name){
			// Reference the buffer associated with the incoming name
			x->buffer_object = (t_buffer *)globalsymbol_reference((t_object *)x, s->s_name, "buffer~");
			
			// If we were previously referencing another buffer, we should not longer reference it.
			globalsymbol_dereference((t_object *)x, x->buffer_name->s_name, "buffer~");
			
			x->buffer_name = s;
		}		
	}
	@endcode
*/
void *globalsymbol_reference(t_object *x, C74_CONST char *name, C74_CONST char *classname);


/**	Stop referencing an object that is bound to a #t_symbol, previously referenced using globalsymbol_reference().
	@ingroup misc
	@param	x			The object that is getting the reference to the symbol.
	@param	name		The name of the symbol to reference.
	@param	classname	The name of the class of which the object we are referencing should be an instance.
	@see	globalsymbol_reference()
*/
void globalsymbol_dereference(t_object *x, C74_CONST char *name, C74_CONST char *classname);


/**	Bind an object to a #t_symbol.
	@ingroup misc
	@param	x		The object to bind to the #t_symbol.
	@param	name	The name of the #t_symbol to which the object will be bound.
	@param	flags	Pass 0.
	@return		A Max error code.
*/
t_max_err globalsymbol_bind(t_object *x, C74_CONST char *name, long flags);


/** Remove an object from being bound to a #t_symbol.
	@ingroup misc
	@param	x		The object from which to unbind the #t_symbol.
	@param	name	The name of the #t_symbol from which the object will be unbound.
	@param	flags	Pass 0.
*/
void globalsymbol_unbind(t_object *x, C74_CONST char *name, long flags);


// private
void globalsymbol_notify(t_object *x, C74_CONST char *name, t_symbol *msg, void *data);


END_USING_C_LINKAGE

#endif // __EXT_GLOBALSYMBOL_H__

