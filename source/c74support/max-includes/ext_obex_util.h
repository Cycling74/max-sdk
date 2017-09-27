/*
 *  obex_util.h
 *
 *  Copyright 2006 Cycling '74. All rights reserved.
 *
 */

#ifndef _EXT_OBEX_UTIL_H_
#define _EXT_OBEX_UTIL_H_

BEGIN_USING_C_LINKAGE

// symbol macros which may be swapped to use common symbol pointers for performance
#ifndef USESYM
#define USESYM(x)	gensym(#x)
//#define USESYM(x)	_sym_##x
#endif

// macros for attributes
// class attributes are almost universally attr_offset, except for class static attributes


/**
	Create a char attribute and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
*/
#define CLASS_ATTR_CHAR(c,attrname,flags,structname,structmember) \
	class_addattr((c),attr_offset_new(attrname,USESYM(char),(flags),(method)0L,(method)0L,calcoffset(structname,structmember)))


/**
	Create a t_atom_long integer attribute and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
*/

#define CLASS_ATTR_LONG(c,attrname,flags,structname,structmember) \
		{		\
			C74_STATIC_ASSERT(structmembersize(structname,structmember)==sizeof(long), "structmember must be long type"); \
			class_addattr((c),attr_offset_new(attrname,USESYM(long),(flags),(method)0L,(method)0L,calcoffset(structname,structmember))); \
		}

/**
	Create a t_atom_long integer attribute and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
*/

#define CLASS_ATTR_ATOM_LONG(c,attrname,flags,structname,structmember) \
		{		\
			C74_STATIC_ASSERT(structmembersize(structname,structmember)==sizeof(t_atom_long), "structmember must be t_atom_long type"); \
			class_addattr((c),attr_offset_new(attrname,USESYM(atom_long),(flags),(method)0L,(method)0L,calcoffset(structname,structmember))); \
		}

// “int32” attribute types are not supported for user facing attributes

#define CLASS_ATTR_INT32(c,attrname,flags,structname,structmember) \
		{		\
			C74_STATIC_ASSERT(structmembersize(structname,structmember)==sizeof(t_int32), "structmember must be t_int32 type"); \
			class_addattr((c),attr_offset_new(attrname,USESYM(int32),(flags),(method)0L,(method)0L,calcoffset(structname,structmember))); \
		}

#define CLASS_ATTR_FILEPATH(c,attrname,flags,structname,structmember) \
		{		\
			C74_STATIC_ASSERT(structmembersize(structname,structmember)==sizeof(t_filepath), "structmember must be t_filepath type"); \
			class_addattr((c),attr_offset_new(attrname,USESYM(filepath),(flags),(method)0L,(method)0L,calcoffset(structname,structmember))); \
		}

/**
	Create a 32-bit float attribute and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
*/
#define CLASS_ATTR_FLOAT(c,attrname,flags,structname,structmember) \
	class_addattr((c),attr_offset_new(attrname,USESYM(float32),(flags),(method)0L,(method)0L,calcoffset(structname,structmember)))


/**
	Create a 64-bit float attribute and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
*/
#define CLASS_ATTR_DOUBLE(c,attrname,flags,structname,structmember) \
	class_addattr((c),attr_offset_new(attrname,USESYM(float64),(flags),(method)0L,(method)0L,calcoffset(structname,structmember)))


/**
	Create a #t_symbol* attribute and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
*/
#define CLASS_ATTR_SYM(c,attrname,flags,structname,structmember) \
	class_addattr((c),attr_offset_new(attrname,USESYM(symbol),(flags),(method)0L,(method)0L,calcoffset(structname,structmember)))


/**
	Create a #t_atom attribute and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
*/
#define CLASS_ATTR_ATOM(c,attrname,flags,structname,structmember) \
	class_addattr((c),attr_offset_new(attrname,USESYM(atom),(flags),(method)0L,(method)0L,calcoffset(structname,structmember)))


/**
	Create a #t_object* attribute and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
*/
#define CLASS_ATTR_OBJ(c,attrname,flags,structname,structmember) \
	class_addattr((c),attr_offset_new(attrname,USESYM(object),(flags),(method)0L,(method)0L,calcoffset(structname,structmember)))




/**
	Create an array-of-chars attribute of fixed length, and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	size			The number of chars in the array.
*/
#define CLASS_ATTR_CHAR_ARRAY(c,attrname,flags,structname,structmember,size) \
	class_addattr((c),attr_offset_array_new(attrname,USESYM(char),(size),(flags),(method)0L,(method)0L,0/*fix*/,calcoffset(structname,structmember)))


/**
	Create an array-of-long-integers attribute of fixed length, and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	size			The number of longs in the array.
*/
#define CLASS_ATTR_LONG_ARRAY(c,attrname,flags,structname,structmember,size) \
		{		\
			C74_STATIC_ASSERT(structmembersize(structname,structmember[0])==sizeof(long), "structmember must be long type"); \
			class_addattr((c),attr_offset_array_new(attrname,USESYM(long),(size),(flags),(method)0L,(method)0L,0/*fix*/,calcoffset(structname,structmember))); \
		}

/**
	Create an array-of-t_atom_long-integers attribute of fixed length, and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	size			The number of longs in the array.
*/
#define CLASS_ATTR_ATOM_LONG_ARRAY(c,attrname,flags,structname,structmember,size) \
		{		\
			C74_STATIC_ASSERT(structmembersize(structname,structmember[0])==sizeof(t_atom_long), "structmember must be t_atom_long type"); \
			class_addattr((c),attr_offset_array_new(attrname,USESYM(atom_long),(size),(flags),(method)0L,(method)0L,0/*fix*/,calcoffset(structname,structmember))); \
		}


/**
	Create an array-of-32bit-floats attribute of fixed length, and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	size			The number of floats in the array.
*/
#define CLASS_ATTR_FLOAT_ARRAY(c,attrname,flags,structname,structmember,size) \
	class_addattr((c),attr_offset_array_new(attrname,USESYM(float32),(size),(flags),(method)0L,(method)0L,0/*fix*/,calcoffset(structname,structmember)))


/**
	Create an array-of-64bit-floats attribute of fixed length, and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	size			The number of doubles in the array.
*/
#define CLASS_ATTR_DOUBLE_ARRAY(c,attrname,flags,structname,structmember,size) \
	class_addattr((c),attr_offset_array_new(attrname,USESYM(float64),(size),(flags),(method)0L,(method)0L,0/*fix*/,calcoffset(structname,structmember)))


/**
	Create an array-of-symbols attribute of fixed length, and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	size			The number of items in the #t_symbol* array.
*/
#define CLASS_ATTR_SYM_ARRAY(c,attrname,flags,structname,structmember,size) \
	class_addattr((c),attr_offset_array_new(attrname,USESYM(symbol),(size),(flags),(method)0L,(method)0L,0/*fix*/,calcoffset(structname,structmember)))


/**
	Create an array-of-atoms attribute of fixed length, and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	size			The number of items in the #t_atom array.
*/
#define CLASS_ATTR_ATOM_ARRAY(c,attrname,flags,structname,structmember,size) \
	class_addattr((c),attr_offset_array_new(attrname,USESYM(atom),(size),(flags),(method)0L,(method)0L,0/*fix*/,calcoffset(structname,structmember)))


/**
	Create an array-of-objects attribute of fixed length, and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	size			The number of items in the #t_object* array.
*/
#define CLASS_ATTR_OBJ_ARRAY(c,attrname,flags,structname,structmember,size) \
	class_addattr((c),attr_offset_array_new(attrname,USESYM(object),(size),(flags),(method)0L,(method)0L,0/*fix*/,calcoffset(structname,structmember)))




/**
	Create an array-of-chars attribute of variable length, and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	sizemember		The actual number of items in the char array at any given moment.
	@param	maxsize			The maximum number of items in the char array, i.e. the number of members allocated for the array in the struct.
*/
#define CLASS_ATTR_CHAR_VARSIZE(c,attrname,flags,structname,structmember,sizemember,maxsize) \
	class_addattr((c),attr_offset_array_new(attrname,USESYM(char),(maxsize),(flags),(method)0L,(method)0L,calcoffset(structname,sizemember),calcoffset(structname,structmember)))


/**
	Create an array-of-long-integers attribute of variable length, and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	sizemember		The actual number of items in the long array at any given moment.
	@param	maxsize			The maximum number of items in the long array, i.e. the number of members allocated for the array in the struct.
*/
#define CLASS_ATTR_LONG_VARSIZE(c,attrname,flags,structname,structmember,sizemember,maxsize) \
		{		\
			C74_STATIC_ASSERT(structmembersize(structname,structmember[0])==sizeof(long), "structmember must be t_atom_long type"); \
			class_addattr((c),attr_offset_array_new(attrname,USESYM(long),(maxsize),(flags),(method)0L,(method)0L,calcoffset(structname,sizemember),calcoffset(structname,structmember))); \
		}

/**
	Create an array-of-32bit-floats attribute of variable length, and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	sizemember		The actual number of items in the float array at any given moment.
	@param	maxsize			The maximum number of items in the float array, i.e. the number of members allocated for the array in the struct.
*/
#define CLASS_ATTR_FLOAT_VARSIZE(c,attrname,flags,structname,structmember,sizemember,maxsize) \
	class_addattr((c),attr_offset_array_new(attrname,USESYM(float32),(maxsize),(flags),(method)0L,(method)0L,calcoffset(structname,sizemember),calcoffset(structname,structmember)))


/**
	Create an array-of-64bit-floats attribute of variable length, and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	sizemember		The actual number of items in the double array at any given moment.
	@param	maxsize			The maximum number of items in the double array, i.e. the number of members allocated for the array in the struct.
*/
#define CLASS_ATTR_DOUBLE_VARSIZE(c,attrname,flags,structname,structmember,sizemember,maxsize) \
	class_addattr((c),attr_offset_array_new(attrname,USESYM(float64),(maxsize),(flags),(method)0L,(method)0L,calcoffset(structname,sizemember),calcoffset(structname,structmember)))


/**
	Create an array-of-symbols attribute of variable length, and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	sizemember		The actual number of items in the #t_symbol* array at any given moment.
	@param	maxsize			The maximum number of items in the #t_symbol* array, i.e. the number of members allocated for the array in the struct.
*/
#define CLASS_ATTR_SYM_VARSIZE(c,attrname,flags,structname,structmember,sizemember,maxsize) \
	class_addattr((c),attr_offset_array_new(attrname,USESYM(symbol),(maxsize),(flags),(method)0L,(method)0L,calcoffset(structname,sizemember),calcoffset(structname,structmember)))


/**
	Create an array-of-atoms attribute of variable length, and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	sizemember		The actual number of items in the #t_atom array at any given moment.
	@param	maxsize			The maximum number of items in the #t_atom array, i.e. the number of members allocated for the array in the struct.
*/
#define CLASS_ATTR_ATOM_VARSIZE(c,attrname,flags,structname,structmember,sizemember,maxsize) \
	class_addattr((c),attr_offset_array_new(attrname,USESYM(atom),(maxsize),(flags),(method)0L,(method)0L,calcoffset(structname,sizemember),calcoffset(structname,structmember)))


/**
	Create an array-of-objects attribute of variable length, and add it to a Max class.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	sizemember		The actual number of items in the #t_object* array at any given moment.
	@param	maxsize			The maximum number of items in the #t_object* array, i.e. the number of members allocated for the array in the struct.
*/
#define CLASS_ATTR_OBJ_VARSIZE(c,attrname,flags,structname,structmember,sizemember,maxsize) \
	class_addattr((c),attr_offset_array_new(attrname,USESYM(object),(maxsize),(flags),(method)0L,(method)0L,calcoffset(structname,sizemember),calcoffset(structname,structmember)))




// "struct" attributes are just like class attributes, but the struct member name is the same as the attribute name
// we use CMacro "stringification" in this case

// scalar variants

/**
	Create a char attribute and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
*/
#define STRUCT_ATTR_CHAR(c,flags,structname,structmember)		CLASS_ATTR_CHAR(c,#structmember,flags,structname,structmember)


/**
	Create a long integer attribute and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
*/
#define STRUCT_ATTR_LONG(c,flags,structname,structmember)		CLASS_ATTR_LONG(c,#structmember,flags,structname,structmember)

/**
	Create a t_atom_long integer attribute and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
*/
#define STRUCT_ATTR_ATOM_LONG(c,flags,structname,structmember)		CLASS_ATTR_ATOM_LONG(c,#structmember,flags,structname,structmember)

/**
	Create a 32bit float attribute and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
*/
#define STRUCT_ATTR_FLOAT(c,flags,structname,structmember)		CLASS_ATTR_FLOAT(c,#structmember,flags,structname,structmember)


/**
	Create a 64bit float attribute and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
*/
#define STRUCT_ATTR_DOUBLE(c,flags,structname,structmember)		CLASS_ATTR_DOUBLE(c,#structmember,flags,structname,structmember)


/**
	Create a #t_symbol* attribute and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
*/
#define STRUCT_ATTR_SYM(c,flags,structname,structmember)		CLASS_ATTR_SYM(c,#structmember,flags,structname,structmember)


/**
	Create a #t_atom attribute and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
*/
#define STRUCT_ATTR_ATOM(c,flags,structname,structmember)		CLASS_ATTR_ATOM(c,#structmember,flags,structname,structmember)


/**
	Create a #t_object* attribute and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
*/
#define STRUCT_ATTR_OBJ(c,flags,structname,structmember)		CLASS_ATTR_OBJ(c,#structmember,flags,structname,structmember)



// fixed size array variants

/**
	Create an array-of-chars attribute of fixed length, and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	size			The number of items in the char array.
*/
#define STRUCT_ATTR_CHAR_ARRAY(c,flags,structname,structmember,size)		CLASS_ATTR_CHAR_ARRAY(c,#structmember,flags,structname,structmember,size)


/**
	Create an array-of-long-integers attribute of fixed length, and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	size			The number of items in the long array.
*/
#define STRUCT_ATTR_LONG_ARRAY(c,flags,structname,structmember,size)		CLASS_ATTR_LONG_ARRAY(c,#structmember,flags,structname,structmember,size)


/**
	Create an array-of-32bit-floats attribute of fixed length, and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	size			The number of items in the floats array.
*/
#define STRUCT_ATTR_FLOAT_ARRAY(c,flags,structname,structmember,size)		CLASS_ATTR_FLOAT_ARRAY(c,#structmember,flags,structname,structmember,size)


/**
	Create an array-of-64bit-floats attribute of fixed length, and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	size			The number of items in the double array.
*/
#define STRUCT_ATTR_DOUBLE_ARRAY(c,flags,structname,structmember,size)		CLASS_ATTR_DOUBLE_ARRAY(c,#structmember,flags,structname,structmember,size)


/**
	Create an array-of-symbols attribute of fixed length, and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	size			The number of items in the #t_symbol* array.
*/
#define STRUCT_ATTR_SYM_ARRAY(c,flags,structname,structmember,size)			CLASS_ATTR_SYM_ARRAY(c,#structmember,flags,structname,structmember,size)


/**
	Create an array-of-atoms attribute of fixed length, and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	size			The number of items in the #t_atom array.
*/
#define STRUCT_ATTR_ATOM_ARRAY(c,flags,structname,structmember,size)		CLASS_ATTR_ATOM_ARRAY(c,#structmember,flags,structname,structmember,size)


/**
	Create an array-of-objects attribute of fixed length, and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	size			The number of items in the #t_object* array.
*/
#define STRUCT_ATTR_OBJ_ARRAY(c,flags,structname,structmember,size)			CLASS_ATTR_OBJ_ARRAY(c,#structmember,flags,structname,structmember,size)




// variable size array variants

/**
	Create an array-of-chars attribute of variable length, and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	sizemember		The actual number of items in the char array at any given moment.
	@param	maxsize			The maximum number of items in the char array, i.e. the number of members allocated for the array in the struct.
*/
#define STRUCT_ATTR_CHAR_VARSIZE(c,flags,structname,structmember,sizemember,maxsize)		CLASS_ATTR_CHAR_VARSIZE(c,#structmember,flags,structname,structmember,sizemember,maxsize)


/**
	Create an array-of-long-integers attribute of variable length, and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	sizemember		The actual number of items in the long array at any given moment.
	@param	maxsize			The maximum number of items in the long array, i.e. the number of members allocated for the array in the struct.
*/
#define STRUCT_ATTR_LONG_VARSIZE(c,flags,structname,structmember,sizemember,maxsize)		CLASS_ATTR_LONG_VARSIZE(c,#structmember,flags,structname,structmember,sizemember,maxsize)


/**
	Create an array-of-32bit-floats attribute of variable length, and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	sizemember		The actual number of items in the float array at any given moment.
	@param	maxsize			The maximum number of items in the float array, i.e. the number of members allocated for the array in the struct.
*/
#define STRUCT_ATTR_FLOAT_VARSIZE(c,flags,structname,structmember,sizemember,maxsize)		CLASS_ATTR_FLOAT_VARSIZE(c,#structmember,flags,structname,structmember,sizemember,maxsize)


/**
	Create an array-of-64bit-floats attribute of variable length, and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	sizemember		The actual number of items in the double array at any given moment.
	@param	maxsize			The maximum number of items in the double array, i.e. the number of members allocated for the array in the struct.
*/
#define STRUCT_ATTR_DOUBLE_VARSIZE(c,flags,structname,structmember,sizemember,maxsize)		CLASS_ATTR_DOUBLE_VARSIZE(c,#structmember,flags,structname,structmember,sizemember,maxsize)


/**
	Create an array-of-symbols attribute of variable length, and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	sizemember		The actual number of items in the #t_symbol* array at any given moment.
	@param	maxsize			The maximum number of items in the #t_symbol* array, i.e. the number of members allocated for the array in the struct.
*/
#define STRUCT_ATTR_SYM_VARSIZE(c,flags,structname,structmember,sizemember,maxsize)			CLASS_ATTR_SYM_VARSIZE(c,#structmember,flags,structname,structmember,sizemember,maxsize)


/**
	Create an array-of-atoms attribute of variable length, and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	sizemember		The actual number of items in the #t_atom array at any given moment.
	@param	maxsize			The maximum number of items in the #t_atom array, i.e. the number of members allocated for the array in the struct.
*/
#define STRUCT_ATTR_ATOM_VARSIZE(c,flags,structname,structmember,sizemember,maxsize)		CLASS_ATTR_ATOM_VARSIZE(c,#structmember,flags,structname,structmember,sizemember,maxsize)


/**
	Create an array-of-objects attribute of variable length, and add it to a Max class.
	The name of the attribute is automatically determined by the name of the struct member.

	@ingroup	attr
	@param	c				The class pointer.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param	structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param	sizemember		The actual number of items in the #t_object* array at any given moment.
	@param	maxsize			The maximum number of items in the #t_object* array, i.e. the number of members allocated for the array in the struct.
*/
#define STRUCT_ATTR_OBJ_VARSIZE(c,flags,structname,structmember,sizemember,maxsize)			CLASS_ATTR_OBJ_VARSIZE(c,#structmember,flags,structname,structmember,sizemember,maxsize)




// class static variants
// these are unused in any c74 code
#define STATIC_ATTR_ATOMS	class_addattr_atoms
#define STATIC_ATTR_PARSE	class_addattr_parse
#define STATIC_ATTR_FORMAT	class_addattr_format
#define STATIC_ATTR_CHAR(c,attrname,flags,val)		STATIC_ATTR_FORMAT(c,attrname,USESYM(char),flags,"c",val)
#define STATIC_ATTR_LONG(c,attrname,flags,val)		STATIC_ATTR_FORMAT(c,attrname,USESYM(long),flags,"l",val)
#define STATIC_ATTR_FLOAT(c,attrname,flags,val)		STATIC_ATTR_FORMAT(c,attrname,USESYM(float32),flags,"f",val)
#define STATIC_ATTR_DOUBLE(c,attrname,flags,val)	STATIC_ATTR_FORMAT(c,attrname,USESYM(float64),flags,"d",val)
#define STATIC_ATTR_SYM(c,attrname,flags,val)		STATIC_ATTR_FORMAT(c,attrname,USESYM(symbol),flags,"s",val)
#define STATIC_ATTR_ATOM(c,attrname,flags,val)		STATIC_ATTR_FORMAT(c,attrname,USESYM(atom),flags,"a",val)
#define STATIC_ATTR_OBJ(c,attrname,flags,val)		STATIC_ATTR_FORMAT(c,attrname,USESYM(object),flags,"o",val)
#define STATIC_ATTR_CHAR_ARRAY(c,attrname,flags,count,vals)		STATIC_ATTR_FORMAT(c,attrname,USESYM(char),flags,"C",count,vals)
#define STATIC_ATTR_LONG_ARRAY(c,attrname,flags,count,vals)		STATIC_ATTR_FORMAT(c,attrname,USESYM(long),flags,"L",count,vals)
#define STATIC_ATTR_FLOAT_ARRAY(c,attrname,flags,count,vals)	STATIC_ATTR_FORMAT(c,attrname,USESYM(float32),flags,"F",count,vals)
#define STATIC_ATTR_DOUBLE_ARRAY(c,attrname,flags,count,vals)	STATIC_ATTR_FORMAT(c,attrname,USESYM(float64),flags,"D",count,vals)
#define STATIC_ATTR_SYM_ARRAY(c,attrname,flags,count,vals)		STATIC_ATTR_FORMAT(c,attrname,USESYM(symbol),flags,"S",count,vals)
#define STATIC_ATTR_ATOM_ARRAY									STATIC_ATTR_ATOMS  // these are really the same, included for consistency
#define STATIC_ATTR_OBJ_ARRAY(c,attrname,flags,count,vals)		STATIC_ATTR_FORMAT(c,attrname,USESYM(object),flags,"O",count,vals)




// object versions, creates new object local attribute 
#define OBJ_ATTR_ATOMS		object_addattr_atoms
#define OBJ_ATTR_PARSE		object_addattr_parse
#define OBJ_ATTR_FORMAT		object_addattr_format


/**
	Create an instance-local char attribute and add it to a Max class.

	@ingroup	attr
	@param	x				The object pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	val				Pointer to the value.
*/
#define OBJ_ATTR_CHAR(x,attrname,flags,val)		OBJ_ATTR_FORMAT(x,attrname,USESYM(char),flags,"c",val)


/**
	Create an instance-local long integer attribute and add it to a Max class.

	@ingroup	attr
	@param	x				The object pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	val				Pointer to the value.
*/
#define OBJ_ATTR_LONG(x,attrname,flags,val)		OBJ_ATTR_FORMAT(x,attrname,USESYM(long),flags,"l",val)


/**
	Create an instance-local 32bit float attribute and add it to a Max class.

	@ingroup	attr
	@param	x				The object pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	val				Pointer to the value.
*/
#define OBJ_ATTR_FLOAT(x,attrname,flags,val)	OBJ_ATTR_FORMAT(x,attrname,USESYM(float32),flags,"f",val)


/**
	Create an instance-local 64bit float attribute and add it to a Max class.

	@ingroup	attr
	@param	x				The object pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	val				Pointer to the value.
*/
#define OBJ_ATTR_DOUBLE(x,attrname,flags,val)	OBJ_ATTR_FORMAT(x,attrname,USESYM(float64),flags,"d",val)


/**
	Create an instance-local #t_symbol* attribute and add it to a Max class.

	@ingroup	attr
	@param	x				The object pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	val				Pointer to the value.
*/
#define OBJ_ATTR_SYM(x,attrname,flags,val)		OBJ_ATTR_FORMAT(x,attrname,USESYM(symbol),flags,"s",val)


/**
	Create an instance-local #t_atom attribute and add it to a Max class.

	@ingroup	attr
	@param	x				The object pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	val				Pointer to the value.
*/
#define OBJ_ATTR_ATOM(x,attrname,flags,val)		OBJ_ATTR_FORMAT(x,attrname,USESYM(atom),flags,"a",val)


/**
	Create an instance-local #t_object* attribute and add it to a Max class.

	@ingroup	attr
	@param	x				The object pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	val				Pointer to the value.
*/
#define OBJ_ATTR_OBJ(x,attrname,flags,val)		OBJ_ATTR_FORMAT(x,attrname,USESYM(object),flags,"o",val)




/**
	Create an instance-local array-of-chars attribute of fixed length, and add it to the object.

	@ingroup	attr
	@param	x				The object pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	count			The number of items in the char array.
	@param	vals			Pointer to the values.
*/
#define OBJ_ATTR_CHAR_ARRAY(x,attrname,flags,count,vals)		OBJ_ATTR_FORMAT(x,attrname,USESYM(char),flags,"C",count,vals)


/**
	Create an instance-local array-of-long-integers attribute of fixed length, and add it to the object.

	@ingroup	attr
	@param	x				The object pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	count			The number of items in the long array.
	@param	vals			Pointer to the values.
*/
#define OBJ_ATTR_LONG_ARRAY(x,attrname,flags,count,vals)		OBJ_ATTR_FORMAT(x,attrname,USESYM(long),flags,"L",count,vals)


/**
	Create an instance-local array-of-32bit-floats attribute of fixed length, and add it to the object.

	@ingroup	attr
	@param	x				The object pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	count			The number of items in the float array.
	@param	vals			Pointer to the values.
*/
#define OBJ_ATTR_FLOAT_ARRAY(x,attrname,flags,count,vals)		OBJ_ATTR_FORMAT(x,attrname,USESYM(float32),flags,"F",count,vals)


/**
	Create an instance-local array-of-64bit-floats attribute of fixed length, and add it to the object.

	@ingroup	attr
	@param	x				The object pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	count			The number of items in the double array.
	@param	vals			Pointer to the values.
*/
#define OBJ_ATTR_DOUBLE_ARRAY(x,attrname,flags,count,vals)		OBJ_ATTR_FORMAT(x,attrname,USESYM(float64),flags,"D",count,vals)


/**
	Create an instance-local array-of-symbols attribute of fixed length, and add it to the object.

	@ingroup	attr
	@param	x				The object pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	count			The number of items in the #t_symbol* array.
	@param	vals			Pointer to the values.
*/
#define OBJ_ATTR_SYM_ARRAY(x,attrname,flags,count,vals)			OBJ_ATTR_FORMAT(x,attrname,USESYM(symbol),flags,"S",count,vals)


/**
	Create an instance-local array-of-atoms attribute of fixed length, and add it to the object.

	@ingroup	attr
	@param	x				The object pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	count			The number of items in the #t_atom array.
	@param	vals			Pointer to the values.
*/
#define OBJ_ATTR_ATOM_ARRAY										OBJ_ATTR_ATOMS  // these are really the same, included for consistency


/**
	Create an instance-local array-of-objects attribute of fixed length, and add it to the object.

	@ingroup	attr
	@param	x				The object pointer.
	@param	attrname		The name of this attribute as a C-string.
	@param	flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param	count			The number of items in the #t_object* array.
	@param	vals			Pointer to the values.
*/
#define OBJ_ATTR_OBJ_ARRAY(x,attrname,flags,count,vals)			OBJ_ATTR_FORMAT(x,attrname,USESYM(object),flags,"O",count,vals)





/**
	Specify custom accessor methods for an attribute.  
	If you specify a non-NULL value for the setter or getter, 
	then the function you specify will be called to set or get the attribute's value
	rather than using the built-in accessor.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	getter			An appropriate getter method as discussed in @ref attribute_accessors, 
							or NULL to use the default getter.
	@param	setter			An appropriate setter method as discussed in @ref attribute_accessors, 
							or NULL to use the default setter.
*/
#define CLASS_ATTR_ACCESSORS(c,attrname,getter,setter) \
	{ t_object *theattr=(t_object *)class_attr_get(c,gensym(attrname)); \
		object_method(theattr,gensym("setmethod"),USESYM(get),getter); \
		object_method(theattr,gensym("setmethod"),USESYM(set),setter); }


/**
	Add flags to an attribute.  

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to add to this attribute, as defined in #e_max_attrflags.
*/
#define CLASS_ATTR_ADD_FLAGS(c,attrname,flags) \
	{ t_object *theattr=(t_object *)class_attr_get(c,gensym(attrname)); \
		long oldflags = object_method(theattr,gensym("getflags")); \
		object_method(theattr,gensym("setflags"),oldflags|(flags)); }


/**
	Remove flags from an attribute.  

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to remove from this attribute, as defined in #e_max_attrflags.
*/
#define CLASS_ATTR_REMOVE_FLAGS(c,attrname,flags) \
	{ t_object *theattr=(t_object *)class_attr_get(c,gensym(attrname)); \
		long oldflags = object_method(theattr,gensym("getflags")); \
		object_method(theattr,gensym("setflags"),oldflags&(~(flags))); }


/**
	Add a filter to the attribute to limit the lower bound of a value.
	The limiting will be performed by the default attribute accessor.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	minval			The minimum acceptable value to which the attribute will be limited.
	@see	CLASS_ATTR_FILTER_MAX
	@see	CLASS_ATTR_FILTER_CLIP
	@see	CLASS_ATTR_MIN
*/
#define CLASS_ATTR_FILTER_MIN(c,attrname,minval) \
	{ t_object *theattr=(t_object *)class_attr_get(c,gensym(attrname)); \
		attr_addfilter_clip(theattr,minval,0,1,0); }


/**
	Add a filter to the attribute to limit the upper bound of a value.
	The limiting will be performed by the default attribute accessor.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	maxval			The maximum acceptable value to which the attribute will be limited.
	@see	CLASS_ATTR_FILTER_MIN
	@see	CLASS_ATTR_FILTER_CLIP
	@see	CLASS_ATTR_MAX
*/
#define CLASS_ATTR_FILTER_MAX(c,attrname,maxval) \
	{ t_object *theattr=(t_object *)class_attr_get(c,gensym(attrname)); \
		attr_addfilter_clip(theattr,0,maxval,0,1); }


/**
	Add a filter to the attribute to limit both the lower and upper bounds of a value.
	The limiting will be performed by the default attribute accessor.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	minval			The maximum acceptable value to which the attribute will be limited.
	@param	maxval			The maximum acceptable value to which the attribute will be limited.
	@see 
*/
#define CLASS_ATTR_FILTER_CLIP(c,attrname,minval,maxval) \
	{ t_object *theattr=(t_object *)class_attr_get(c,gensym(attrname)); \
		attr_addfilter_clip(theattr,minval,maxval,1,1); }


/**
	Create a new attribute that is an alias of an existing attribute.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the actual attribute as a C-string.
	@param	aliasname		The name of the new alias attribute.
*/
#define CLASS_ATTR_ALIAS(c,attrname,aliasname) \
	{	t_object *thealias; \
		t_object *theattr=(t_object *)class_attr_get(c,gensym(attrname)); \
		thealias = object_clone(theattr); \
		object_method(thealias,USESYM(setname),gensym(aliasname)); \
		class_addattr(c,thealias); \
		CLASS_ATTR_ATTR_PARSE(c,aliasname,"alias",USESYM(symbol),0,attrname); }




// macros for attribute of attributes
#define CLASS_ATTR_ATTR_ATOMS	class_attr_addattr_atoms
#define CLASS_ATTR_ATTR_PARSE	class_attr_addattr_parse
#define CLASS_ATTR_ATTR_FORMAT	class_attr_addattr_format


/**
	Add a new attribute to the specified attribute to specify a default value.
	The default value will be automatically set when the object is created only if your object uses a dictionary constructor
	with the #CLASS_FLAG_NEWDICTIONARY flag.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
*/
#define CLASS_ATTR_DEFAULT(c,attrname,flags,parsestr) \
	{ t_object *theattr=(t_object *)class_attr_get(c,gensym(attrname)); CLASS_ATTR_ATTR_PARSE(c,attrname,"default",(t_symbol *)object_method(theattr,USESYM(gettype)),flags,parsestr); }


/**
	Add a new attribute to the specified attribute to indicate that the specified attribute should be saved with the patcher.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
*/
#define CLASS_ATTR_SAVE(c,attrname,flags) \
	CLASS_ATTR_ATTR_PARSE(c,attrname,"save",USESYM(long),flags,"1")

/**
	Add a new attribute to the specified attribute to indicate that it is saved by the object 
	(so it does not appear in italics in the inspector).

	@ingroup	attr
	@param		c			The class pointer.
	@param		attrname	The name of the attribute as a C-string.
	@param		flags		Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
 */
#define CLASS_ATTR_SELFSAVE(c,attrname,flags) \
CLASS_ATTR_ATTR_PARSE(c,attrname,"selfsave",USESYM(long),flags,"1")

/**
	A convenience wrapper for both #CLASS_ATTR_DEFAULT and #CLASS_ATTR_SAVE.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
	@see	CLASS_ATTR_DEFAULT
	@see	CLASS_ATTR_SAVE
*/
#define CLASS_ATTR_DEFAULT_SAVE(c,attrname,flags,parsestr) \
	{ CLASS_ATTR_DEFAULT(c,attrname,flags,parsestr); CLASS_ATTR_SAVE(c,attrname,flags); }


/**
	Add a new attribute to the specified attribute to specify a default value, based on Max's Object Defaults.
	If a value is present in Max's Object Defaults, then that value will be used as the default value.
	Otherwise, use the default value specified here.
	The default value will be automatically set when the object is created only if your object uses a dictionary constructor
	with the #CLASS_FLAG_NEWDICTIONARY flag.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
*/
#define CLASS_ATTR_DEFAULTNAME(c,attrname,flags,parsestr) \
	{ t_object *theattr=(t_object *)class_attr_get(c,gensym(attrname)); CLASS_ATTR_ATTR_PARSE(c,attrname,"defaultname",(t_symbol *)object_method(theattr,USESYM(gettype)),flags,parsestr); }


/**
	A convenience wrapper for both #CLASS_ATTR_DEFAULTNAME and #CLASS_ATTR_SAVE.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
	@see	CLASS_ATTR_DEFAULTNAME
	@see	CLASS_ATTR_SAVE
*/
#define CLASS_ATTR_DEFAULTNAME_SAVE(c,attrname,flags,parsestr) \
	{ CLASS_ATTR_DEFAULTNAME(c,attrname,flags,parsestr); CLASS_ATTR_SAVE(c,attrname,flags); }


/**
	Add a new attribute to the specified attribute to specify a lower range.
	The values will not be automatically limited.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
	@see	CLASS_ATTR_MAX
	@see	CLASS_ATTR_FILTER_MAX
	@see	CLASS_ATTR_FILTER_CLIP
*/
#define CLASS_ATTR_MIN(c,attrname,flags,parsestr) \
  { t_object *theattr=(t_object *)class_attr_get(c,gensym(attrname)); CLASS_ATTR_ATTR_PARSE(c,attrname,"min",(t_symbol *)object_method(theattr,USESYM(gettype)),flags,parsestr); } 


/**
	Add a new attribute to the specified attribute to specify an upper range.
	The values will not be automatically limited.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
	@see	CLASS_ATTR_MIN
	@see	CLASS_ATTR_FILTER_MAX
	@see	CLASS_ATTR_FILTER_CLIP
*/
#define CLASS_ATTR_MAX(c,attrname,flags,parsestr) \
  { t_object *theattr=(t_object *)class_attr_get(c,gensym(attrname)); CLASS_ATTR_ATTR_PARSE(c,attrname,"max",(t_symbol *)object_method(theattr,USESYM(gettype)),flags,parsestr); } 


// useful attr attr macros for UI objects

/**
	Add a new attribute indicating that any changes to the specified attribute will trigger a call
	to the object's paint method.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
*/
#define CLASS_ATTR_PAINT(c,attrname,flags) \
	CLASS_ATTR_ATTR_PARSE(c,attrname,"paint",USESYM(long),flags,"1")


/**
	A convenience wrapper for both #CLASS_ATTR_DEFAULT and #CLASS_ATTR_PAINT.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
	@see	CLASS_ATTR_DEFAULT
	@see	CLASS_ATTR_PAINT
*/
#define CLASS_ATTR_DEFAULT_PAINT(c,attrname,flags,parsestr) \
	{ CLASS_ATTR_DEFAULT(c,attrname,flags,parsestr); CLASS_ATTR_PAINT(c,attrname,flags); }


/**
	A convenience wrapper for #CLASS_ATTR_DEFAULT, #CLASS_ATTR_SAVE, and #CLASS_ATTR_PAINT.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
	@see	CLASS_ATTR_DEFAULT
	@see	CLASS_ATTR_PAINT
	@see	CLASS_ATTR_SAVE
*/
#define CLASS_ATTR_DEFAULT_SAVE_PAINT(c,attrname,flags,parsestr) \
	{ CLASS_ATTR_DEFAULT(c,attrname,flags,parsestr); CLASS_ATTR_SAVE(c,attrname,flags); CLASS_ATTR_PAINT(c,attrname,flags); }


/**
	A convenience wrapper for #CLASS_ATTR_DEFAULTNAME, #CLASS_ATTR_SAVE, and #CLASS_ATTR_PAINT.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
	@see	CLASS_ATTR_DEFAULTNAME
	@see	CLASS_ATTR_PAINT
	@see	CLASS_ATTR_SAVE
*/	
#define CLASS_ATTR_DEFAULTNAME_PAINT(c,attrname,flags,parsestr) \
	{ CLASS_ATTR_DEFAULTNAME(c,attrname,flags,parsestr); CLASS_ATTR_PAINT(c,attrname,flags); }


/**
	A convenience wrapper for #CLASS_ATTR_DEFAULTNAME, #CLASS_ATTR_SAVE, and #CLASS_ATTR_PAINT.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
	@see	CLASS_ATTR_DEFAULTNAME
	@see	CLASS_ATTR_PAINT
	@see	CLASS_ATTR_SAVE
*/
#define CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c,attrname,flags,parsestr) \
	{ CLASS_ATTR_DEFAULTNAME(c,attrname,flags,parsestr); CLASS_ATTR_SAVE(c,attrname,flags); CLASS_ATTR_PAINT(c,attrname,flags); }


// useful attr attr macros for inpector properties


/**
	Add a new attribute to the specified attribute to specify an editor style for the Max inspector.
	Available styles include
	<ul>
	 	<li>"text"      : a text editor</li>
		<li>"onoff"     : a toggle switch</li>
		<li>"rgba"      : a color chooser</li>
		<li>"enum"      : a menu of available choices, whose symbol will be passed upon selection</li>
		<li>"enumindex" : a menu of available choices, whose index will be passed upon selection</li>
		<li>"rect"      : a style for displaying and editing #t_rect values</li>
		<li>"font"      : a font chooser</li>
		<li>"file"      : a file chooser dialog</li>
	</ul>

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
*/
#define CLASS_ATTR_STYLE(c,attrname,flags,parsestr) \
	CLASS_ATTR_ATTR_PARSE(c,attrname,"style",USESYM(symbol),flags,parsestr)


/**
	Add a new attribute to the specified attribute to specify an a human-friendly label for the Max inspector.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	labelstr		A C-string, which will be parsed into an array of atoms to set the initial value.
*/
#define CLASS_ATTR_LABEL(c,attrname,flags,labelstr) \
	CLASS_ATTR_ATTR_FORMAT(c,attrname,"label",USESYM(symbol),flags,"s",gensym_tr(labelstr))	


/**
	Add a new attribute to the specified attribute to specify a list of choices to display in a menu
	for the Max inspector.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
	
	@remark This macro automatically calls
	@code
	CLASS_ATTR_STYLE(c,attrname,flags,"enum").
	@endcode
	
	@see	CLASS_ATTR_ENUMINDEX
*/
#define CLASS_ATTR_ENUM(c,attrname,flags,parsestr) \
	{ CLASS_ATTR_STYLE(c,attrname,flags,"enum"); CLASS_ATTR_ATTR_PARSE(c,attrname,"enumvals",USESYM(atom),flags,parsestr); }


/**
	Add a new attribute to the specified attribute to specify a list of choices to display in a menu
	for the Max inspector.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
	
	@remark This macro automatically calls
	@code
	CLASS_ATTR_STYLE(c,attrname,flags,"enumindex").
	@endcode
	
	@see	CLASS_ATTR_ENUM
*/
#define CLASS_ATTR_ENUMINDEX(c,attrname,flags,parsestr) \
	{ CLASS_ATTR_STYLE(c,attrname,flags,"enumindex"); CLASS_ATTR_ATTR_PARSE(c,attrname,"enumvals",USESYM(atom),flags,parsestr); }

// localizable versions
#define CLASS_ATTR_ENUMINDEX2(c,attrname,flags,enum1,enum2) \
{ t_atom aaa[2]; CLASS_ATTR_STYLE(c,attrname,flags,"enumindex"); atom_setsym(aaa,gensym_tr(enum1)); atom_setsym(aaa+1,gensym_tr(enum2)); \
CLASS_ATTR_ATTR_ATOMS(c,attrname,"enumvals",USESYM(atom),flags,2,aaa); }
		
#define CLASS_ATTR_ENUMINDEX3(c,attrname,flags,enum1,enum2,enum3) \
{ t_atom aaa[3]; CLASS_ATTR_STYLE(c,attrname,flags,"enumindex"); atom_setsym(aaa,gensym_tr(enum1)); atom_setsym(aaa+1,gensym_tr(enum2)); atom_setsym(aaa+2,gensym_tr(enum3));\
CLASS_ATTR_ATTR_ATOMS(c,attrname,"enumvals",USESYM(atom),flags,3,aaa); }
		
#define CLASS_ATTR_ENUMINDEX4(c,attrname,flags,enum1,enum2,enum3,enum4) \
{ t_atom aaa[4]; CLASS_ATTR_STYLE(c,attrname,flags,"enumindex"); atom_setsym(aaa,gensym_tr(enum1)); atom_setsym(aaa+1,gensym_tr(enum2)); atom_setsym(aaa+2,gensym_tr(enum3)); atom_setsym(aaa+3,gensym_tr(enum4));\
CLASS_ATTR_ATTR_ATOMS(c,attrname,"enumvals",USESYM(atom),flags,4,aaa); }
		
#define CLASS_ATTR_ENUMINDEX5(c,attrname,flags,enum1,enum2,enum3,enum4,enum5) \
{ t_atom aaa[5]; CLASS_ATTR_STYLE(c,attrname,flags,"enumindex"); atom_setsym(aaa,gensym_tr(enum1)); atom_setsym(aaa+1,gensym_tr(enum2)); atom_setsym(aaa+2,gensym_tr(enum3));\
atom_setsym(aaa+3,gensym_tr(enum4)); atom_setsym(aaa+4,gensym_tr(enum5));\
CLASS_ATTR_ATTR_ATOMS(c,attrname,"enumvals",USESYM(atom),flags,5,aaa); }
		
#define CLASS_ATTR_ENUMINDEX6(c,attrname,flags,enum1,enum2,enum3,enum4,enum5,enum6) \
{ t_atom aaa[6]; CLASS_ATTR_STYLE(c,attrname,flags,"enumindex"); atom_setsym(aaa,gensym_tr(enum1)); atom_setsym(aaa+1,gensym_tr(enum2)); atom_setsym(aaa+2,gensym_tr(enum3));\
atom_setsym(aaa+3,gensym_tr(enum4)); atom_setsym(aaa+4,gensym_tr(enum5)); atom_setsym(aaa+5,gensym_tr(enum6));\
CLASS_ATTR_ATTR_ATOMS(c,attrname,"enumvals",USESYM(atom),flags,6,aaa); }
		
#define CLASS_ATTR_ENUMINDEX7(c,attrname,flags,enum1,enum2,enum3,enum4,enum5,enum6,enum7) \
{ t_atom aaa[7]; CLASS_ATTR_STYLE(c,attrname,flags,"enumindex"); atom_setsym(aaa,gensym_tr(enum1)); atom_setsym(aaa+1,gensym_tr(enum2)); atom_setsym(aaa+2,gensym_tr(enum3));\
atom_setsym(aaa+3,gensym_tr(enum4)); atom_setsym(aaa+4,gensym_tr(enum5)); atom_setsym(aaa+5,gensym_tr(enum6)); atom_setsym(aaa+6,gensym_tr(enum7));\
CLASS_ATTR_ATTR_ATOMS(c,attrname,"enumvals",USESYM(atom),flags,7,aaa); }

/**
	Add a new attribute to the specified attribute to specify a category to which the attribute is assigned
	in the Max inspector.  
	Categories are represented in the inspector as tabs.  
	If the specified category does not exist then it will be created.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
*/
#define CLASS_ATTR_CATEGORY(c,attrname,flags,parsestr) \
	CLASS_ATTR_ATTR_PARSE(c,attrname,"category",USESYM(symbol),flags,str_tr(parsestr))


/**
	A convenience wrapper for #CLASS_ATTR_STYLE, and #CLASS_ATTR_LABEL.

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	stylestr		A C-string that names the style for the attribute. 
							See #CLASS_ATTR_STYLE for the available styles.
	@param	labelstr		A C-string that names the category to which the attribute is assigned in the inspector.

	@see	CLASS_ATTR_STYLE
	@see	CLASS_ATTR_LABEL
*/
#define CLASS_ATTR_STYLE_LABEL(c,attrname,flags,stylestr,labelstr) \
	{ CLASS_ATTR_ATTR_PARSE(c,attrname,"style",USESYM(symbol),flags,stylestr); CLASS_ATTR_ATTR_FORMAT(c,attrname,"label",USESYM(symbol),flags,"s",gensym_tr(labelstr)); }	


/**
	Add a new attribute to the specified attribute to flag an attribute as invisible to the Max inspector.  

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
*/
#define CLASS_ATTR_INVISIBLE(c,attrname,flags) \
	CLASS_ATTR_ATTR_PARSE(c,attrname,"invisible",USESYM(long),flags,"1")


/**
	Add a new attribute to the specified attribute to specify a default order in which to list attributes.  

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
	
	@remark	A value of zero indicates that there is no ordering.  Ordering values begin at 1.  For example:
	@code
	CLASS_ATTR_ORDER(c, "firstattr",	0, "1");
	CLASS_ATTR_ORDER(c, "secondattr",	0, "2");
	CLASS_ATTR_ORDER(c, "thirdattr",	0, "3");
	@endcode
*/
#define CLASS_ATTR_ORDER(c,attrname,flags,parsestr) \
	CLASS_ATTR_ATTR_PARSE(c,attrname,"order",USESYM(long),flags,parsestr)
		
/**
	Add a new attribute to the specified attribute to specify that it should appear in the inspector's Basic tab.  

	@ingroup	attr
	@param	c				The class pointer.
	@param	attrname		The name of the attribute as a C-string.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
 
 */
#define CLASS_ATTR_BASIC(c,attrname,flags) \
CLASS_ATTR_ATTR_PARSE(c,attrname,"basic",USESYM(long),flags,"1")



	
// useful attr attr macro for objects that embed binary data as base64

#define CLASS_ATTR_ATOMARRAY(c,attrname,flags) \
	CLASS_ATTR_ATTR_PARSE(c,attrname,"atomarray",USESYM(long),flags,"1")


/**	Define and add attributes to class methods.
	@ingroup attr
	@param	c				The class pointer.
	@param	methodname		The name of the existing method as a C-string.
	@param	attrname		The name of the attribute to add as a C-string.
	@param	type			The datatype of the attribute to be added.
	@param	flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param	parsestring		A C-string, which will be parsed into an array of atoms to set the initial value.
	
	@remark An example which makes a method invisible to users:
	@code
	class_addmethod(c, (method)my_foo, "foo", 0);
	CLASS_METHOD_ATTR_PARSE(c, "foo", "undocumented", gensym("long"), 0, "1");
	@endcode
*/
#define CLASS_METHOD_ATTR_PARSE(c,methodname,attrname,type,flags,parsestring) \
	{	t_hashtab *methods=NULL; \
		t_object *m=NULL; \
		methods = (t_hashtab *)class_extra_lookup(c,gensym("methods")); \
		if (methods) { \
			hashtab_lookup(methods,gensym((methodname)),&m); \
			if (m) \
				object_addattr_parse(m,attrname,type,flags,parsestring); \
		} \
	} 


/**
	Add a new attribute to the specified attribute to specify a legacy default value.
	The default value will be automatically set when the object is created only if your object uses a dictionary constructor
	with the #CLASS_FLAG_NEWDICTIONARY flag.

	@ingroup	attr
	@param		c				The class pointer.
	@param		legacyattrname	The name of the attribute.
	@param		newattrname		The name of the attribute.
	@param		flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param		parsestr		A C-string, which will be parsed into an array of atoms to set the legacy value, used by jbox_processlegacydefaults()
 */
#define CLASS_ATTR_LEGACYDEFAULT(c,legacyattrname,newattrname,flags,parsestr) \
{ \
	t_object *theattr = (t_object *)class_attr_get(c,gensym(legacyattrname)); \
	t_hashtab *legs = NULL; \
	CLASS_ATTR_ATTR_PARSE(c,legacyattrname,"legacydefault",(t_symbol *)object_method(theattr,USESYM(gettype)),flags,parsestr); \
	legs = (t_hashtab *)class_extra_lookup(c, gensym("legacydefaults")); \
	if (legs == NULL) { \
		legs = (t_hashtab *)hashtab_new(0); hashtab_flags(legs, OBJ_FLAG_DATA); \
		class_extra_store(c, gensym("legacydefaults"), (t_object *)legs); \
	} \
	hashtab_store(legs, gensym(legacyattrname), (t_object *)gensym(newattrname)); \
}


/**
	Add a new attribute to the specified attribute to flag it as obsolete.

	@ingroup	attr
	@param		c				The class pointer.
	@param		attrname		The name of the attribute as a C-string.
	@param		flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
 */
#define CLASS_ATTR_OBSOLETE(c,attrname,flags) \
{ \
	t_object *attr; \
	attr = (t_object *)class_attr_get(c,gensym(attrname)); \
	if (!attr) { \
		attr = attribute_new(attrname, USESYM(atom), 0, (method)object_attr_obsolete_getter, (method)object_attr_obsolete_setter); \
		class_addattr(c, attr); \
	} \
	CLASS_ATTR_ATTR_PARSE(c,attrname,"obsolete",USESYM(long),flags,"1"); \
	CLASS_ATTR_ATTR_PARSE(c,attrname,"invisible",USESYM(long),flags,"1"); \
}


/**
	Add a new attribute to the specified attribute to flag it as renamed.

	@ingroup	attr
	@param		c				The class pointer.
	@param		oldname			The name of the old attribute as a C-string.
	@param		newname			The name of the new attribute as a C-string.
	@param		flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
 */
#define CLASS_ATTR_RENAMED(c,oldname,newname,flags) \
{ \
	CLASS_ATTR_OBSOLETE(c,oldname,flags); \
	CLASS_ATTR_ATTR_PARSE(c,oldname,"renamed",USESYM(symbol),flags,newname); \
}


/**
	Add a new attribute to the specified attribute to indicate in which version the attribute was introduced.
	
	@ingroup	attr
	@param		c				The class pointer.
	@param		attrname		The name of the attribute as a C-string.
	@param		flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param		versionstr		A C-string, which will be parsed set the version number (e.g. "7.0.0").
 */
#define CLASS_ATTR_INTRODUCED(c,attrname,flags,versionstr) \
CLASS_ATTR_ATTR_PARSE(c,attrname,"introduced",USESYM(symbol),flags,str_tr(versionstr))


/**
	Add a new attribute to the specified method to flag it as obsolete.
 
	@ingroup	attr
	@param		c				The class pointer.
	@param		methodname		The name of the method as a C-string.
	@param		flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
 */
#define CLASS_METHOD_OBSOLETE(c,methodname,flags) \
{	t_hashtab *methods=NULL; \
	t_object *m=NULL; \
	methods = (t_hashtab *)class_extra_lookup(c,gensym("methods")); \
	if (methods) { \
		hashtab_lookup(methods,gensym((methodname)),&m); \
		if (!m) \
		{ \
			class_addmethod(c,(method)object_method_obsolete,methodname,A_GIMME,0L); \
			hashtab_lookup(methods,gensym((methodname)),&m); \
		} \
		if (m) \
		{ \
			object_addattr_parse(m,"invisible",USESYM(long),flags,"1"); \
			object_addattr_parse(m,"obsolete",USESYM(long),flags,"1"); \
		} \
	} \
}

/**
	Add a new attribute to the specified method to flag a method as renamed.
 
	@ingroup	attr
	@param		c				The class pointer.
	@param		oldname			The name of the old method as a C-string.
	@param		newname			The name of the new method as a C-string.
	@param		flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
 */
#define CLASS_METHOD_RENAMED(c,oldname,newname,flags) \
{ \
	CLASS_METHOD_OBSOLETE(c,oldname,flags); \
	CLASS_METHOD_ATTR_PARSE(c,oldname,"renamed",USESYM(symbol),flags,newname); \
}

/**
	Add a new attribute to the specified method to indicate in which version the method was introduced.

	@ingroup	attr
	@param		c				The class pointer.
	@param		methodname		The name of the method as a C-string.
	@param		flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param		versionstr		A C-string, which will be parsed set the version number (e.g. "7.0.0").
 */
#define CLASS_METHOD_INTRODUCED(c,methodname,flags,versionstr) \
CLASS_METHOD_ATTR_PARSE(c,methodname,"introduced",USESYM(symbol),flags,str_tr(versionstr))


#define OBJ_ATTR_ATTR_ATOMS		object_attr_addattr_atoms
#define OBJ_ATTR_ATTR_PARSE		object_attr_addattr_parse
#define OBJ_ATTR_ATTR_FORMAT	object_attr_addattr_format


/**
	An instance-attribute version of #CLASS_ATTR_DEFAULT.

	@ingroup	attr
	@param		x				The #t_object instance pointer.
	@param		attrname		The name of the attribute as a C-string.
	@param		flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param		parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
	@see		CLASS_ATTR_DEFAULT
*/
#define OBJ_ATTR_DEFAULT(x,attrname,flags,parsestr) \
	{ t_object *theattr=(t_object *)object_attr_get(x,gensym(attrname)); OBJ_ATTR_ATTR_PARSE(x,attrname,"default",(t_symbol *)object_method(theattr,USESYM(gettype)),flags,parsestr); }


/**
	An instance-attribute version of #CLASS_ATTR_SAVE.

	@ingroup	attr
	@param		x				The #t_object instance pointer.
	@param		attrname		The name of the attribute as a C-string.
	@param		flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@see		CLASS_ATTR_SAVE
*/
#define OBJ_ATTR_SAVE(x,attrname,flags) \
	OBJ_ATTR_ATTR_PARSE(x,attrname,"save",USESYM(long),flags,"1")


/**
	An instance-attribute version of #CLASS_ATTR_DEFAULT_SAVE.

	@ingroup	attr
	@param		x				The #t_object instance pointer.
	@param		attrname		The name of the attribute as a C-string.
	@param		flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param		parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
	@see		CLASS_ATTR_DEFAULT_SAVE
*/
#define OBJ_ATTR_DEFAULT_SAVE(x,attrname,flags,parsestr) \
	{ OBJ_ATTR_DEFAULT(x,attrname,flags,parsestr); OBJ_ATTR_SAVE(x,attrname,flags); }


// sticky macros for attribute attributes, and method attributes. Useful for defining attribute groups

/**
	Create an attribute, and add it to all following attribute declarations.
	The block is closed by a call to #CLASS_STICKY_ATTR_CLEAR.

	@ingroup	attr
	@param		c				The class pointer.
	@param		name			The name of the new attribute to create as a C-string.
	@param		flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param		parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
	
	@remark		The most common use of CLASS_STICKY_ATTR is for creating multiple attributes with the same category,
				as in this example:
	@code
	CLASS_STICKY_ATTR(c, "category", 0, "Foo");
	
	CLASS_ATTR_DOUBLE(c, "bar", 0, t_myobject, x_bar);
	CLASS_ATTR_LABEL(c, "bar", 0, "A Bar");

	CLASS_ATTR_CHAR(c, "switch", 0, t_myobject, x_switch);
	CLASS_ATTR_STYLE_LABEL(c, "switch", 0, "onoff", "Bar Switch");

	CLASS_ATTR_DOUBLE(c, "flow", 0, t_myobject, x_flow);
	CLASS_ATTR_LABEL(c, "flow",	0, "Flow Amount");
	
	CLASS_STICKY_ATTR_CLEAR(c, "category");
	@endcode
	
	@see		CLASS_STICKY_ATTR_CLEAR
*/
#define CLASS_STICKY_ATTR(c,name,flags,parsestr) \
	{ t_object *attr = attribute_new_parse(name,NULL,flags,parsestr); class_sticky(c,gensym("sticky_attr"),gensym(name),attr); }


/**
	Close a #CLASS_STICKY_ATTR block.

	@ingroup	attr
	@param		c				The class pointer.
	@param		name			The name of the sticky attribute as a C-string.
	@see		CLASS_STICKY_ATTR
*/
#define CLASS_STICKY_ATTR_CLEAR(c,name) class_sticky_clear(c,gensym("sticky_attr"),name?gensym(name):NULL)

#define CLASS_STICKY_CATEGORY(c,flags,name) \
{ t_object *attr = attribute_new_format("category",NULL,flags,"s",gensym_tr(name)); class_sticky(c,gensym("sticky_attr"),gensym("category"),attr); }

#define CLASS_STICKY_CATEGORY_CLEAR(c) class_sticky_clear(c,gensym("sticky_attr"),gensym("category"))

/**
	Create an attribute, and add it to all following method declarations.
	The block is closed by a call to #CLASS_STICKY_METHOD_CLEAR.

	@ingroup	attr
	@param		c				The class pointer.
	@param		name			The name of the new attribute to create as a C-string.
	@param		flags			Any flags you wish to declare for this new attribute, as defined in #e_max_attrflags.
	@param		parsestr		A C-string, which will be parsed into an array of atoms to set the initial value.
	
	@remark		The most common use of CLASS_STICKY_ATTR is for creating multiple attributes with the same category,
				as in this example:
	@code
	CLASS_STICKY_METHOD(c, "undocumented", 0, "1");
	
	// add some methods here with class_addmethod()
	// the undocumented attribute for methods means that the ref-page 
	// generator will ignore these methods.
	
	CLASS_STICKY_METHOD_CLEAR(c, "undocumented");
	@endcode
	
	@see		CLASS_STICKY_METHOD_CLEAR
*/
#define CLASS_STICKY_METHOD(c,name,flags,parsestr) \
	{ t_object *attr = attribute_new_parse(name,NULL,flags,parsestr); class_sticky(c,gensym("sticky_method"),gensym(name),attr); }


/**
	Close a #CLASS_STICKY_METHOD block.

	@ingroup	attr
	@param		c				The class pointer.
	@param		name			The name of the sticky attribute as a C-string.
	@see		CLASS_STICKY_METHOD
*/
#define CLASS_STICKY_METHOD_CLEAR(c,name) class_sticky_clear(c,gensym("sticky_method"),name?gensym(name):NULL)




// support for long lists

#define OBEX_UTIL_MAX_ATOM_GETBYTES 	1048576 		
#define OBEX_UTIL_MAX_ATOM_STATIC		2048


//static memory case
#define OBEX_UTIL_ATOM_SETUP_VAR_STATIC t_atom atemp[OBEX_UTIL_MAX_ATOM_STATIC]; t_atom *av2=atemp; long ac2=OBEX_UTIL_MAX_ATOM_STATIC;
#define OBEX_UTIL_ATOM_CLEANUP_VAR_STATIC 
#define OBEX_UTIL_ATOM_SETUP_ARRAY_STATIC(ac) t_atom atemp[OBEX_UTIL_MAX_ATOM_STATIC]; t_atom *av2=atemp; long ac2; ac2 = MIN(ac,OBEX_UTIL_MAX_ATOM_STATIC);
#define OBEX_UTIL_ATOM_CLEANUP_ARRAY_STATIC(ac)  

//dynamic memory case
#define OBEX_UTIL_ATOM_SETUP_VAR_DYN t_atom *av2=NULL; long ac2=0;
#define OBEX_UTIL_ATOM_CLEANUP_VAR_DYN if (ac2&&av2) mm_freebytes((char *)av2,sizeof(t_atom)*ac2);
#define OBEX_UTIL_ATOM_SETUP_ARRAY_DYN(ac) t_atom *av2=NULL; long ac2=0; av2 = (t_atom *)mm_getbytes(sizeof(t_atom)*ac); ac2 = ac;
#define OBEX_UTIL_ATOM_CLEANUP_ARRAY_DYN(ac) if (ac2&&av2) mm_freebytes(av2,sizeof(t_atom)*ac2);


//combo static/dynamic. faster for smaller atom lists on input, but not limited
#define OBEX_UTIL_ATOM_SETUP_VAR_COMBO		OBEX_UTIL_ATOM_SETUP_VAR_DYN	// same for VAR
#define OBEX_UTIL_ATOM_CLEANUP_VAR_COMBO	OBEX_UTIL_ATOM_CLEANUP_VAR_DYN	// same for VAR
#define OBEX_UTIL_ATOM_SETUP_ARRAY_COMBO(ac) \
	t_atom atemp[OBEX_UTIL_MAX_ATOM_STATIC]; \
	t_atom *av2=atemp; \
	long ac2; \
	long usestatic=1; \
	ac2 = MIN(ac,OBEX_UTIL_MAX_ATOM_STATIC); \
	if (ac>OBEX_UTIL_MAX_ATOM_STATIC) { usestatic=0; av2 = (t_atom *)mm_getbytes(sizeof(t_atom)*ac); ac2=ac; }
#define OBEX_UTIL_ATOM_CLEANUP_ARRAY_COMBO(ac) if ((!usestatic)&&ac2&&av2) mm_freebytes((char *)av2,sizeof(t_atom)*ac2);


// default to combo
#define OBEX_UTIL_ATOM_SETUP_VAR			OBEX_UTIL_ATOM_SETUP_VAR_COMBO
#define OBEX_UTIL_ATOM_CLEANUP_VAR			OBEX_UTIL_ATOM_CLEANUP_VAR_COMBO
#define OBEX_UTIL_ATOM_SETUP_ARRAY			OBEX_UTIL_ATOM_SETUP_ARRAY_COMBO
#define OBEX_UTIL_ATOM_CLEANUP_ARRAY		OBEX_UTIL_ATOM_CLEANUP_ARRAY_COMBO


/**
	Flags that determine how functions convert atoms into text (C-strings).
	@ingroup atom
*/
typedef enum{
	OBEX_UTIL_ATOM_GETTEXT_DEFAULT =			0x00000000, ///< default translation rules for getting text from atoms
	OBEX_UTIL_ATOM_GETTEXT_TRUNCATE_ZEROS =		0x00000001, ///< eliminate redundant zeros for floating point numbers (default used)
	OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE	=		0x00000002, ///< don't introduce quotes around symbols with spaces
	OBEX_UTIL_ATOM_GETTEXT_SYM_FORCE_QUOTE =	0x00000004, ///< always introduce quotes around symbols (useful for JSON)
	OBEX_UTIL_ATOM_GETTEXT_COMMA_DELIM =		0x00000008, ///< separate atoms with commas (useful for JSON)
	OBEX_UTIL_ATOM_GETTEXT_FORCE_ZEROS =		0x00000010, ///< always print the zeros
	OBEX_UTIL_ATOM_GETTEXT_NUM_HI_RES =			0x00000020,	///< print more decimal places
	OBEX_UTIL_ATOM_GETTEXT_NUM_LO_RES =			0x00000040  ///< // print fewer decimal places (HI_RES will win though)
} e_max_atom_gettext_flags;


// atom utilities (will move to atomutils2.c)

/**
	Assign an array of char values to an array of atoms.

	@ingroup	atom
	@param		ac				The number of atoms to try to fetch from the array of chars.
								You should have at least this number of atoms allocated in av.
	@param		av				The address to the first of an array of allocated atoms.
	@param		count			The number of values in the array specified by vals.
	@param		vals			The array from which to copy the values into the array of atoms at av.
	@return						A Max error code.
*/
t_max_err atom_setchar_array(long ac, t_atom *av, long count, unsigned char *vals);


/**
	Assign an array of long integer values to an array of atoms.

	@ingroup	atom
	@param		ac				The number of atoms to try to fetch from the array of longs.
								You should have at least this number of atoms allocated in av.
	@param		av				The address to the first of an array of allocated atoms.
	@param		count			The number of values in the array specified by vals.
	@param		vals			The array from which to copy the values into the array of atoms at av.
	@return						A Max error code.
*/
t_max_err atom_setlong_array(long ac, t_atom *av, long count, t_atom_long *vals);


/**
	Assign an array of 32bit float values to an array of atoms.

	@ingroup	atom
	@param		ac				The number of atoms to try to fetch from the array of floats.
								You should have at least this number of atoms allocated in av.
	@param		av				The address to the first of an array of allocated atoms.
	@param		count			The number of values in the array specified by vals.
	@param		vals			The array from which to copy the values into the array of atoms at av.
	@return						A Max error code.
*/
t_max_err atom_setfloat_array(long ac, t_atom *av, long count, float *vals);


/**
	Assign an array of 64bit float values to an array of atoms.

	@ingroup	atom
	@param		ac				The number of atoms to try to fetch from the array of doubles.
								You should have at least this number of atoms allocated in av.
	@param		av				The address to the first of an array of allocated atoms.
	@param		count			The number of values in the array specified by vals.
	@param		vals			The array from which to copy the values into the array of atoms at av.
	@return						A Max error code.
*/
t_max_err atom_setdouble_array(long ac, t_atom *av, long count, double *vals);


/**
	Assign an array of #t_symbol* values to an array of atoms.

	@ingroup	atom
	@param		ac				The number of atoms to try to fetch from the array of symbols.
								You should have at least this number of atoms allocated in av.
	@param		av				The address to the first of an array of allocated atoms.
	@param		count			The number of values in the array specified by vals.
	@param		vals			The array from which to copy the values into the array of atoms at av.
	@return						A Max error code.
*/
t_max_err atom_setsym_array(long ac, t_atom *av, long count, t_symbol **vals);


/**
	Assign an array of #t_atom values to an array of atoms.

	@ingroup	atom
	@param		ac				The number of atoms to try to fetch from the second array of atoms.
								You should have at least this number of atoms allocated in av.
	@param		av				The address to the first of an array of allocated atoms.
	@param		count			The number of values in the array specified by vals.
	@param		vals			The array from which to copy the values into the array of atoms at av.
	@return						A Max error code.
*/
t_max_err atom_setatom_array(long ac, t_atom *av, long count, t_atom *vals);


/**
	Assign an array of #t_object* values to an array of atoms.

	@ingroup	atom
	@param		ac				The number of atoms to try to fetch from the array of objects.
								You should have at least this number of atoms allocated in av.
	@param		av				The address to the first of an array of allocated atoms.
	@param		count			The number of values in the array specified by vals.
	@param		vals			The array from which to copy the values into the array of atoms at av.
	@return						A Max error code.
*/
t_max_err atom_setobj_array(long ac, t_atom *av, long count, t_object **vals);


// these variable size calls can alloc mem if desired

/**
	Parse a C-string into an array of atoms.
	This function allocates memory for the atoms if the ac and av parameters are NULL.
	Otherwise it will attempt to use any memory already allocated to av.
	Any allocated memory should be freed with sysmem_freeptr().
	
	@ingroup	atom
	@param		ac			The address of a variable to hold the number of returned atoms.
	@param		av			The address of a #t_atom pointer to which memory may be allocated and atoms copied.
	@param		parsestr	The C-string to parse.
	@return					A Max error code.
	
	@remark		The following example will parse the string "foo bar 1 2 3.0" into an array of 5 atoms.
				The atom types will be determined automatically as 2 #A_SYM atoms, 2 #A_LONG atoms, and 1 #A_FLOAT atom.
	@code
	t_atom *av =  NULL;
	long ac = 0;
	t_max_err err = MAX_ERR_NONE;
	
	err = atom_setparse(&ac, &av, "foo bar 1 2 3.0");
	@endcode
*/
t_max_err atom_setparse(long *ac, t_atom **av, C74_CONST char *parsestr);


t_max_err atom_setbinbuf(long *ac, t_atom **av, void *buf);


t_max_err atom_setattrval(long *ac, t_atom **av, t_symbol *attrname, t_object *obj);


t_max_err atom_setobjval(long *ac, t_atom **av, t_object *obj);




/**
	Create an array of atoms populated with values using sprintf-like syntax.
	atom_setformat() supports clfdsoaCLFDSOA tokens 
 	(primitive type scalars and arrays respectively for the 
	char, long, float, double, #t_symbol*, #t_object*, #t_atom*).
	It also supports vbp@ tokens (obval, binbuf, parsestr, attribute).

	This function allocates memory for the atoms if the ac and av parameters are NULL.
	Otherwise it will attempt to use any memory already allocated to av.
	Any allocated memory should be freed with sysmem_freeptr().
	
	@ingroup	atom

	@param		ac			The address of a variable to hold the number of returned atoms.
	@param		av			The address of a #t_atom pointer to which memory may be allocated and atoms copied.
	@param		fmt			An sprintf-style format string specifying values for the atoms.
	@param		...			One or more arguments which are to be substituted into the format string. 

	@return		A Max error code.
	@see		atom_getformat()
	@see		atom_setparse()
*/
t_max_err atom_setformat(long *ac, t_atom **av, C74_CONST char *fmt, ...); 

// same as atom_setformat using va_list
t_max_err atom_setformat_va(long *ac, t_atom **av, C74_CONST char *fmt, va_list args);


/**
	Retrieve values from an array of atoms using sscanf-like syntax.
	atom_getformat() supports clfdsoaCLFDSOA tokens 
 	(primitive type scalars and arrays respectively for the 
	char, long, float, double, #t_symbol*, #t_object*, #t_atom*).
	It does not support vbp@ the tokens found in atom_setformat().
	
	@ingroup	atom

	@param		ac			The number of atoms to parse in av.
	@param		av			The address of the first #t_atom pointer in an array to parse.
	@param		fmt			An sscanf-style format string specifying types for the atoms.
	@param		...			One or more arguments which are address of variables to be set according to the fmt string. 

	@return		A Max error code.
	@see		atom_setformat()
*/
t_max_err atom_getformat(long ac, t_atom *av, C74_CONST char *fmt, ...);

// same as atom_getformat using va_list
t_max_err atom_getformat_va(long ac, t_atom *av, C74_CONST char *fmt, va_list args);


/**
	Convert an array of atoms into a C-string.
	
	@ingroup	atom

	@param		ac			The number of atoms to fetch in av.
	@param		av			The address of the first #t_atom pointer in an array to retrieve.
	@param		textsize	The size of the string to which the atoms will be formatted and copied.
	@param		text		The address of the string to which the text will be written.
	@param		flags		Determines the rules by which atoms will be translated into text.
							Values are bit mask as defined by #e_max_atom_gettext_flags.

	@return		A Max error code.
	@see		atom_setparse()
*/
t_max_err atom_gettext(long ac, t_atom *av, long *textsize, char **text, long flags);


/**
	Fetch an array of char values from an array of atoms.

	@ingroup	atom
	@param		ac				The number of atoms allocated in the av parameter.
	@param		av				The address to the first of an array of allocated atoms.
	@param		count			The number of values to fetch from the array specified by vals.
	@param		vals			The address of the array to which is copied the values from av.
	@return						A Max error code.
*/
t_max_err atom_getchar_array(long ac, t_atom *av, long count, unsigned char *vals);


/**
	Fetch an array of long integer values from an array of atoms.

	@ingroup	atom
	@param		ac				The number of atoms allocated in the av parameter.
	@param		av				The address to the first of an array of allocated atoms.
	@param		count			The number of values to fetch from the array specified by vals.
	@param		vals			The address of the array to which is copied the values from av.
	@return						A Max error code.
*/
t_max_err atom_getlong_array(long ac, t_atom *av, long count, t_atom_long *vals);


/**
	Fetch an array of 32bit float values from an array of atoms.

	@ingroup	atom
	@param		ac				The number of atoms allocated in the av parameter.
	@param		av				The address to the first of an array of allocated atoms.
	@param		count			The number of values to fetch from the array specified by vals.
	@param		vals			The address of the array to which is copied the values from av.
	@return						A Max error code.
*/
t_max_err atom_getfloat_array(long ac, t_atom *av, long count, float *vals);


/**
	Fetch an array of 64bit float values from an array of atoms.

	@ingroup	atom
	@param		ac				The number of atoms allocated in the av parameter.
	@param		av				The address to the first of an array of allocated atoms.
	@param		count			The number of values to fetch from the array specified by vals.
	@param		vals			The address of the array to which is copied the values from av.
	@return						A Max error code.
*/
t_max_err atom_getdouble_array(long ac, t_atom *av, long count, double *vals);


/**
	Fetch an array of #t_symbol* values from an array of atoms.

	@ingroup	atom
	@param		ac				The number of atoms allocated in the av parameter.
	@param		av				The address to the first of an array of allocated atoms.
	@param		count			The number of values to fetch from the array specified by vals.
	@param		vals			The address of the array to which is copied the values from av.
	@return						A Max error code.
*/
t_max_err atom_getsym_array(long ac, t_atom *av, long count, t_symbol **vals);


/**
	Fetch an array of #t_atom values from an array of atoms.

	@ingroup	atom
	@param		ac				The number of atoms allocated in the av parameter.
	@param		av				The address to the first of an array of allocated atoms.
	@param		count			The number of values to fetch from the array specified by vals.
	@param		vals			The address of the array to which is copied the values from av.
	@return						A Max error code.
*/
t_max_err atom_getatom_array(long ac, t_atom *av, long count, t_atom *vals);


/**
	Fetch an array of #t_object* values from an array of atoms.

	@ingroup	atom
	@param		ac				The number of atoms allocated in the av parameter.
	@param		av				The address to the first of an array of allocated atoms.
	@param		count			The number of values to fetch from the array specified by vals.
	@param		vals			The address of the array to which is copied the values from av.
	@return						A Max error code.
*/
t_max_err atom_getobj_array(long ac, t_atom *av, long count, t_object **vals);



/**
	Determines whether or not an atom represents a #t_string object.

	@ingroup	atom
	@param		a				The address of the atom to test.
	@return		Returns true if the #t_atom contains a valid #t_string object.
*/
long atomisstring(const t_atom *a);


/**
	Determines whether or not an atom represents a #t_atomarray object.

	@ingroup	atom
	@param		a				The address of the atom to test.
	@return		Returns true if the #t_atom contains a valid #t_atomarray object.
*/
long atomisatomarray(t_atom *a);


/**
	Determines whether or not an atom represents a #t_dictionary object.

	@ingroup	atom
	@param		a				The address of the atom to test.
	@return		Returns true if the #t_atom contains a valid #t_dictionary object.
*/
long atomisdictionary(t_atom *a);


// quick object programming macros
#define OB_MSG(x,p)	object_method_parse(x,NULL,p,NULL);

//object_method_typed utilities

/**
	Convenience wrapper for object_method_typed() that uses atom_setparse() to define the arguments.

	@ingroup	obj
	@param		x			The object to which the message will be sent.
	@param		s			The name of the method to call on the object.
	@param 		parsestr	A C-string to parse into an array of atoms to pass to the method.
	@param		rv			The address of an atom to hold a return value.
	@return		A Max error code.
	
	@see		object_method_typed()
	@see		atom_setparse()
*/
t_max_err object_method_parse(t_object *x, t_symbol *s, C74_CONST char *parsestr, t_atom *rv);
t_max_err object_method_binbuf(t_object *x, t_symbol *s, void *buf, t_atom *rv);
t_max_err object_method_attrval(t_object *x, t_symbol *s, t_symbol *attrname, t_object *obj, t_atom *rv);
t_max_err object_method_objval(t_object *x, t_symbol *s, t_object *obj, t_atom *rv);

/**
	Convenience wrapper for object_method_typed() that uses atom_setformat() to define the arguments.

	@ingroup	obj
	@param		x			The object to which the message will be sent.
	@param		s			The name of the method to call on the object.
	@param		rv			The address of an atom to hold a return value.
	@param		fmt			An sprintf-style format string specifying values for the atoms.
	@param		...			One or more arguments which are to be substituted into the format string. 
	@return		A Max error code.
	
	@see		object_method_typed()
	@see		atom_setformat()
*/
t_max_err object_method_format(t_object *x, t_symbol *s, t_atom *rv, C74_CONST char *fmt, ...);



/**
	Convenience wrapper for object_method_typed() that passes a single char as an argument.

	@ingroup	obj
	@param		x		The object to which the message will be sent.
	@param		s		The name of the method to call on the object.
	@param		v		An argument to pass to the method.
	@param		rv		The address of an atom to hold a return value.

	@return		A Max error code.
	@see		object_method_typed()
*/
t_max_err object_method_char(t_object *x, t_symbol *s, unsigned char v, t_atom *rv);


/**
	Convenience wrapper for object_method_typed() that passes a single long integer as an argument.

	@ingroup	obj
	@param		x		The object to which the message will be sent.
	@param		s		The name of the method to call on the object.
	@param		v		An argument to pass to the method.
	@param		rv		The address of an atom to hold a return value.

	@return		A Max error code.
	@see		object_method_typed()
*/
t_max_err object_method_long(t_object *x, t_symbol *s, long v, t_atom *rv);


/**
	Convenience wrapper for object_method_typed() that passes a single 32bit float as an argument.

	@ingroup	obj
	@param		x		The object to which the message will be sent.
	@param		s		The name of the method to call on the object.
	@param		v		An argument to pass to the method.
	@param		rv		The address of an atom to hold a return value.

	@return		A Max error code.
	@see		object_method_typed()
*/
t_max_err object_method_float(t_object *x, t_symbol *s, float v, t_atom *rv);


/**
	Convenience wrapper for object_method_typed() that passes a single 64bit float as an argument.

	@ingroup	obj
	@param		x		The object to which the message will be sent.
	@param		s		The name of the method to call on the object.
	@param		v		An argument to pass to the method.
	@param		rv		The address of an atom to hold a return value.

	@return		A Max error code.
	@see		object_method_typed()
*/
t_max_err object_method_double(t_object *x, t_symbol *s, double v, t_atom *rv);


/**
	Convenience wrapper for object_method_typed() that passes a single #t_symbol* as an argument.

	@ingroup	obj
	@param		x		The object to which the message will be sent.
	@param		s		The name of the method to call on the object.
	@param		v		An argument to pass to the method.
	@param		rv		The address of an atom to hold a return value.

	@return		A Max error code.
	@see		object_method_typed()
*/
t_max_err object_method_sym(t_object *x, t_symbol *s, t_symbol *v, t_atom *rv);


/**
	Convenience wrapper for object_method_typed() that passes a single #t_object* as an argument.

	@ingroup	obj
	@param		x		The object to which the message will be sent.
	@param		s		The name of the method to call on the object.
	@param		v		An argument to pass to the method.
	@param		rv		The address of an atom to hold a return value.

	@return		A Max error code.
	@see		object_method_typed()
*/
t_max_err object_method_obj(t_object *x, t_symbol *s, t_object *v, t_atom *rv);



/**
	Convenience wrapper for object_method_typed() that passes an array of char values as an argument.

	@ingroup	obj
	@param		x		The object to which the message will be sent.
	@param		s		The name of the method to call on the object.
	@param		ac		The number of arguments to pass to the method.
	@param		av		The address of the first of the array of arguments to pass to the method.
	@param		rv		The address of an atom to hold a return value.

	@return		A Max error code.
	@see		object_method_typed()
*/
t_max_err object_method_char_array(t_object *x, t_symbol *s, long ac, unsigned char *av, t_atom *rv);


/**
	Convenience wrapper for object_method_typed() that passes an array of long integers values as an argument.

	@ingroup	obj
	@param		x		The object to which the message will be sent.
	@param		s		The name of the method to call on the object.
	@param		ac		The number of arguments to pass to the method.
	@param		av		The address of the first of the array of arguments to pass to the method.
	@param		rv		The address of an atom to hold a return value.

	@return		A Max error code.
	@see		object_method_typed()
*/
t_max_err object_method_long_array(t_object *x, t_symbol *s, long ac, t_atom_long *av, t_atom *rv);


/**
	Convenience wrapper for object_method_typed() that passes an array of 32bit floats values as an argument.

	@ingroup	obj
	@param		x		The object to which the message will be sent.
	@param		s		The name of the method to call on the object.
	@param		ac		The number of arguments to pass to the method.
	@param		av		The address of the first of the array of arguments to pass to the method.
	@param		rv		The address of an atom to hold a return value.

	@return		A Max error code.
	@see		object_method_typed()
*/
t_max_err object_method_float_array(t_object *x, t_symbol *s, long ac, float *av, t_atom *rv);


/**
	Convenience wrapper for object_method_typed() that passes an array of 64bit float values as an argument.

	@ingroup	obj
	@param		x		The object to which the message will be sent.
	@param		s		The name of the method to call on the object.
	@param		ac		The number of arguments to pass to the method.
	@param		av		The address of the first of the array of arguments to pass to the method.
	@param		rv		The address of an atom to hold a return value.

	@return		A Max error code.
	@see		object_method_typed()
*/
t_max_err object_method_double_array(t_object *x, t_symbol *s, long ac, double *av, t_atom *rv);


/**
	Convenience wrapper for object_method_typed() that passes an array of #t_symbol* values as an argument.

	@ingroup	obj
	@param		x		The object to which the message will be sent.
	@param		s		The name of the method to call on the object.
	@param		ac		The number of arguments to pass to the method.
	@param		av		The address of the first of the array of arguments to pass to the method.
	@param		rv		The address of an atom to hold a return value.

	@return		A Max error code.
	@see		object_method_typed()
*/
t_max_err object_method_sym_array(t_object *x, t_symbol *s, long ac, t_symbol **av, t_atom *rv);


/**
	Convenience wrapper for object_method_typed() that passes an array of #t_object* values as an argument.

	@ingroup	obj
	@param		x		The object to which the message will be sent.
	@param		s		The name of the method to call on the object.
	@param		ac		The number of arguments to pass to the method.
	@param		av		The address of the first of the array of arguments to pass to the method.
	@param		rv		The address of an atom to hold a return value.

	@return		A Max error code.
	@see		object_method_typed()
*/
t_max_err object_method_obj_array(t_object *x, t_symbol *s, long ac, t_object **av, t_atom *rv);


// call_method_typed utilities -- not currently used in any Cycling '74 code

t_max_err call_method_typed(method m, t_object *x, t_symbol *s, long ac, t_atom *av, t_atom *rv);
t_max_err call_method_parse(method m, t_object *x, t_symbol *s, char *parsestr, t_atom *rv);
t_max_err call_method_binbuf(method m, t_object *x, t_symbol *s, void *buf, t_atom *rv);
t_max_err call_method_attrval(method m, t_object *x, t_symbol *s, t_symbol *attrname, t_object *obj, t_atom *rv);
t_max_err call_method_objval(method m, t_object *x, t_symbol *s, t_object *obj, t_atom *rv);
t_max_err call_method_format(method m, t_object *x, t_symbol *s, t_atom *rv, char *fmt, ...);

t_max_err call_method_char(method m, t_object *x, t_symbol *s, unsigned char v, t_atom *rv);
t_max_err call_method_long(method m, t_object *x, t_symbol *s, long v, t_atom *rv);
t_max_err call_method_float(method m, t_object *x, t_symbol *s,float v, t_atom *rv);
t_max_err call_method_double(method m, t_object *x, t_symbol *s, double v, t_atom *rv);
t_max_err call_method_sym(method m, t_object *x, t_symbol *s, t_symbol *v, t_atom *rv);
t_max_err call_method_obj(method m, t_object *x, t_symbol *s, t_object *v, t_atom *rv);

t_max_err call_method_char_array(method m, t_object *x, t_symbol *s, long ac, unsigned char *av, t_atom *rv);
t_max_err call_method_long_array(method m, t_object *x, t_symbol *s, long ac, t_atom_long *av, t_atom *rv);
t_max_err call_method_float_array(method m, t_object *x, t_symbol *s, long ac, float *av, t_atom *rv);
t_max_err call_method_double_array(method m, t_object *x, t_symbol *s, long ac, double *av, t_atom *rv);
t_max_err call_method_sym_array(method m, t_object *x, t_symbol *s, long ac, t_symbol **av, t_atom *rv);
t_max_err call_method_obj_array(method m, t_object *x, t_symbol *s, long ac, t_object **av, t_atom *rv);


// object attribute methods (will move to attribtue_util.c with the rest of these)

/**
	Set an attribute value with one or more atoms parsed from a C-string.

	@ingroup	attr
	@param		x			The object whose attribute will be set.
	@param		s			The name of the attribute to set.
	@param 		parsestr	A C-string to parse into an array of atoms to set the attribute value.
	@return		A Max error code.
	@see		atom_setparse()
*/
t_max_err object_attr_setparse(t_object *x, t_symbol *s, C74_CONST char *parsestr);
t_max_err object_attr_setbinbuf(t_object *x, t_symbol *s, void *buf);
t_max_err object_attr_setattrval(t_object *x, t_symbol *s, t_symbol *attrname, t_object *obj);
t_max_err object_attr_setobjval(t_object *x, t_symbol *s, t_object *obj);
t_max_err object_attr_setformat(t_object *x, t_symbol *s, C74_CONST char *fmt, ...);


// t_attribute these probably belong in attribute.c
t_object *attribute_new_atoms(C74_CONST char *attrname, t_symbol *type, long flags, long ac, t_atom *av);
t_object *attribute_new_parse(C74_CONST char *attrname, t_symbol *type, long flags, C74_CONST char *parsestr);
t_object *attribute_new_binbuf(C74_CONST char *attrname, t_symbol *type, long flags, void *buf);
t_object *attribute_new_attrval(C74_CONST char *attrname, t_symbol *type, long flags, t_symbol *objattrname, t_object *obj);
t_object *attribute_new_objval(C74_CONST char *attrname, t_symbol *type, long flags, t_object *obj);
t_object *attribute_new_format(C74_CONST char *attrname, t_symbol *type, long flags, C74_CONST char *fmt, ...);


// general object constructors for objects with typed constructors

/**
	Create a new object with one or more atoms parsed from a C-string.
	The object's new method must have an #A_GIMME signature.

	@ingroup	attr
	@param		name_space	The namespace in which to create the instance. Typically this is either #CLASS_BOX or #CLASS_NOBOX.
	@param		classname	The name of the class to instantiate.
	@param 		parsestr	A C-string to parse into an array of atoms to set the attribute value.

	@return		A pointer to the new instance.
	@see		atom_setparse()
	@see		object_new_typed()
*/
void *object_new_parse(t_symbol *name_space, t_symbol *classname, C74_CONST char *parsestr);
void *object_new_binbuf(t_symbol *name_space, t_symbol *classname, void *buf);
void *object_new_attrval(t_symbol *name_space, t_symbol *classname, t_symbol *objattrname, t_object *obj);
void *object_new_objval(t_symbol *name_space, t_symbol *classname, t_object *obj);
void *object_new_format(t_symbol *name_space, t_symbol *classname, C74_CONST char *fmt, ...);	// not used or tested in any Cycling '74 code


// attr attr functions necessary due to offset attributes as singletons for the class 
// need to copy object local to set any attributes.
// undocumented for now in favor of using the macros defined above.

t_max_err object_attr_addattr(t_object *x, t_symbol *attrname, t_object *attr);
t_object *object_attr_attr_get(t_object *x, t_symbol *attrname, t_symbol *attrname2);
t_max_err object_attr_attr_setvalueof(t_object *x, t_symbol *attrname, t_symbol *attrname2, long argc, t_atom *argv);
t_max_err object_attr_attr_getvalueof(t_object *x, t_symbol *attrname, t_symbol *attrname2, long *argc, t_atom **argv);

t_max_err class_attr_addattr(t_class *c, t_symbol *attrname, t_object *attr);
t_object *class_attr_attr_get(t_class *c, t_symbol *attrname, t_symbol *attrname2);
t_max_err class_attr_attr_setvalueof(t_class *c, t_symbol *attrname, t_symbol *attrname2, long argc, t_atom *argv);
t_max_err class_attr_attr_getvalueof(t_class *c, t_symbol *attrname, t_symbol *attrname2, long *argc, t_atom **argv);

t_max_err object_attr_enforcelocal(t_object *x, t_symbol *attrname);

t_max_err class_addattr_atoms(t_class *c, C74_CONST char *attrname, t_symbol *type, long flags, long ac, t_atom *av);
t_max_err class_addattr_parse(t_class *c, C74_CONST char *attrname, t_symbol *type, long flags, C74_CONST char *parsestr);
t_max_err class_addattr_format(t_class *c, C74_CONST char *attrname, t_symbol *type, long flags, C74_CONST char *fmt, ...);
t_max_err class_attr_addattr_atoms(t_class *c, C74_CONST char *attrname, C74_CONST char *attrname2, t_symbol *type, long flags, long ac, t_atom *av);
t_max_err class_attr_addattr_parse(t_class *c, C74_CONST char *attrname, C74_CONST char *attrname2, t_symbol *type, long flags, C74_CONST char *parsestr);
t_max_err class_attr_addattr_format(t_class *c, C74_CONST char *attrname, C74_CONST char *attrname2, C74_CONST t_symbol *type, long flags, C74_CONST char *fmt, ...);

t_max_err object_addattr_atoms(t_object *x, C74_CONST char *attrname, t_symbol *type, long flags, long ac, t_atom *av);
t_max_err object_addattr_parse(t_object *x, C74_CONST char *attrname, t_symbol *type, long flags, C74_CONST char *parsestr);
t_max_err object_addattr_format(t_object *x, C74_CONST char *attrname, t_symbol *type, long flags, C74_CONST char *fmt, ...);
t_max_err object_attr_addattr_atoms(t_object *x, C74_CONST char *attrname, C74_CONST char *attrname2, t_symbol *type, long flags, long ac, t_atom *av);
t_max_err object_attr_addattr_parse(t_object *x, C74_CONST char *attrname, C74_CONST char *attrname2, t_symbol *type, long flags, C74_CONST char *parsestr);
t_max_err object_attr_addattr_format(t_object *x, C74_CONST char *attrname, C74_CONST char *attrname2, t_symbol *type, long flags, C74_CONST char *fmt, ...);


// other general functions from obex.c
t_object *object_clone(t_object *x);
t_object *object_clone_generic(t_object *x);

// this function has been de-activated and now does nothing
void object_zero(t_object *x);


// menu command stuff 

t_max_err class_addcommand(t_class *c, method cmd, method enabler, method handler, C74_CONST char *message);
void *object_commandenabled(t_object *o, t_symbol *cmd);
t_max_err object_getenabler(t_object *c, t_symbol *cmd, method *m);
t_max_err object_getcommand(t_object *o, t_symbol *cmd, method *m);
void *object_handlecommand(t_object *o, t_symbol *s, long argc, t_atom *argv, t_atom *rv);

t_ptr_int object_attr_getdisabled(t_object *o, t_symbol *attrname);
t_max_err object_attr_setdisabled(t_object *o, t_symbol *attrname, long way);

// arg replacing (for objects that save their own way in dictionaries and want values treated as "attributes" would be)		
t_max_err object_replaceargs(t_object *x, long argc, t_atom *argv, char match, char poundfill);

// stubs for obsolete attrs/methods
t_max_err object_attr_obsolete_getter(t_object *x, t_object *attr, long *ac, t_atom **av);
t_max_err object_attr_obsolete_setter(t_object *x, t_object *attr, long ac, t_atom *av);
void object_method_obsolete(t_object *x, t_symbol *s, long ac, t_atom *av);


END_USING_C_LINKAGE

#endif //_EXT_OBEX_UTIL_H_
