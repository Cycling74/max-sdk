#ifndef _EXT_MESS_H_
#define _EXT_MESS_H_

#include "ext_prefix.h"
#include "ext_common.h"

BEGIN_USING_C_LINKAGE

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif
	
#include "max_types.h"

/* mess.h -- define a symbol table and message-passing system.  */


/**	Function pointer type for generic methods.
	@ingroup datatypes
*/


typedef void *(*method)(void *);

typedef long (*t_intmethod)(void *);

// First cast to void* to trigger errors if arg is float, double, or larger than a pointer.
// Then cast to t_ptr_int as that's the type we specify for each arg, avoid warnings.
#define CALL_METHOD_ARG(p) (t_ptr_int)(void*)(p)
/**	Function pointer type for methods returning a long.
	@ingroup datatypes
*/
#define CALL_METHOD_0(m) ((void*(*)())(m))()
#define CALL_METHOD_1(m, p1) ((void*(*)(t_ptr_int))(m))(CALL_METHOD_ARG(p1))
#define CALL_METHOD_2(m, p1, p2) ((void*(*)(t_ptr_int, t_ptr_int))(m))(CALL_METHOD_ARG(p1), CALL_METHOD_ARG(p2))
#define CALL_METHOD_3(m, p1, p2, p3) ((void*(*)(t_ptr_int, t_ptr_int, t_ptr_int))(m))(CALL_METHOD_ARG(p1), CALL_METHOD_ARG(p2), CALL_METHOD_ARG(p3))
#define CALL_METHOD_4(m, p1, p2, p3, p4) ((void*(*)(t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int))(m))(CALL_METHOD_ARG(p1), CALL_METHOD_ARG(p2), CALL_METHOD_ARG(p3), CALL_METHOD_ARG(p4))
#define CALL_METHOD_5(m, p1, p2, p3, p4, p5) ((void*(*)(t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int))(m))(CALL_METHOD_ARG(p1), CALL_METHOD_ARG(p2), CALL_METHOD_ARG(p3), CALL_METHOD_ARG(p4), CALL_METHOD_ARG(p5))
#define CALL_METHOD_6(m, p1, p2, p3, p4, p5, p6) ((void*(*)(t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int))(m))(CALL_METHOD_ARG(p1), CALL_METHOD_ARG(p2), CALL_METHOD_ARG(p3), CALL_METHOD_ARG(p4), CALL_METHOD_ARG(p5), CALL_METHOD_ARG(p6))
#define CALL_METHOD_7(m, p1, p2, p3, p4, p5, p6, p7) ((void*(*)(t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int))(m))(CALL_METHOD_ARG(p1), CALL_METHOD_ARG(p2), CALL_METHOD_ARG(p3), CALL_METHOD_ARG(p4), CALL_METHOD_ARG(p5), CALL_METHOD_ARG(p6), CALL_METHOD_ARG(p7))
#define CALL_METHOD_8(m, p1, p2, p3, p4, p5, p6, p7, p8) ((void*(*)(t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int))(m))(CALL_METHOD_ARG(p1), CALL_METHOD_ARG(p2), CALL_METHOD_ARG(p3), CALL_METHOD_ARG(p4), CALL_METHOD_ARG(p5), CALL_METHOD_ARG(p6), CALL_METHOD_ARG(p7), CALL_METHOD_ARG(p8))
#define CALL_METHOD_9(m, p1, p2, p3, p4, p5, p6, p7, p8, p9) ((void*(*)(t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int))(m))(CALL_METHOD_ARG(p1), CALL_METHOD_ARG(p2), CALL_METHOD_ARG(p3), CALL_METHOD_ARG(p4), CALL_METHOD_ARG(p5), CALL_METHOD_ARG(p6), CALL_METHOD_ARG(p7), CALL_METHOD_ARG(p8), CALL_METHOD_ARG(p9))
#define CALL_METHOD_10(m, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10) ((void*(*)(t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int, t_ptr_int))(m))(CALL_METHOD_ARG(p1), CALL_METHOD_ARG(p2), CALL_METHOD_ARG(p3), CALL_METHOD_ARG(p4), CALL_METHOD_ARG(p5), CALL_METHOD_ARG(p6), CALL_METHOD_ARG(p7), CALL_METHOD_ARG(p8), CALL_METHOD_ARG(p9), CALL_METHOD_ARG(p10))

#define _GET_CALL_METHOD_MACRO_INDEX(_method, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define GET_CALL_METHOD_MACRO_INDEX(...) C74_EXPAND(_GET_CALL_METHOD_MACRO_INDEX(__VA_ARGS__, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))

#define GET_CALL_METHOD_MACRO_NAME(...) C74_JOIN_2(CALL_METHOD_, GET_CALL_METHOD_MACRO_INDEX(__VA_ARGS__))

#define CALL_METHOD(...) C74_EXPAND(GET_CALL_METHOD_MACRO_NAME(__VA_ARGS__) ( __VA_ARGS__ ))

#define CALL_METHOD_SAFE(rt, sig, m, ...) (((rt (*)sig)m)(__VA_ARGS__))

// Forward declarations of important Max types

typedef struct _atomarray t_atomarray;

// eventually convert all externals to use explicit types instead of void*
// can define C74_USE_STRICT_TYPES=1 to enable for specific externals to test
#if !defined(_MAX_CORE_H_) && !defined(C74_USE_STRICT_TYPES)
#define C74_USE_STRICT_TYPES 0
#else
#define C74_USE_STRICT_TYPES 1
#endif

#if C74_USE_STRICT_TYPES

typedef struct _outlet t_outlet;
typedef struct _inlet t_inlet;
typedef struct _binbuf t_binbuf;
typedef struct _qelem t_qelem;
typedef struct _scheduler t_scheduler;
typedef struct _clock t_clock;
typedef struct _setclock t_setclock;
typedef struct _toolfile t_toolfile;

#else

typedef void t_outlet;
typedef void t_inlet;
typedef void t_binbuf;
typedef void t_qelem;
typedef void t_scheduler;
typedef void t_clock;
typedef void t_setclock;
typedef void t_toolfile;

#endif // #if !C74_USE_STRICT_TYPES

/** The symbol.
	
	Note: You should <em>never</em> manipulate the s_name field of the #t_symbol directly!
	Doing so will corrupt Max's symbol table.  
	Instead, <em>always</em> use gensym() to get a symbol with the desired string 
	contents for the s_name field.

	@ingroup symbol	
*/
typedef struct symbol
{
	char *s_name;			///< name: a c-string
	struct object *s_thing;	///< possible binding to a t_object
} t_symbol;

#ifdef C74_DEFINE_DEPRECATED_TYPES
C74_DEPRECATED( typedef struct symbol Symbol );
#endif

#define CAREFUL

/**	Magic number used to determine if memory pointed to by a #t_object* is valid.	
	@ingroup obj
*/
enum {
	MAGIC = 1758379419L,	/* random (but odd) */
	OB_MAGIC = MAGIC
};

/** function version of NOGOOD test is potentially more reliable
*/
long object_isnogood(void *x);

#ifdef  WIN_VERSION
/**	Returns true if a pointer is not a valid object. 
	@ingroup obj
*/
#ifdef _DEBUG
#define NOGOOD(x) object_isnogood(x)
#else
#define NOGOOD(x) ( IsBadReadPtr((void *)(x),sizeof(struct object)) || ((struct object *)(x))->o_magic != MAGIC )
#endif

#else
/**	Returns true if a pointer is not a valid object. 
	@ingroup obj
*/
#define NOGOOD(x) ( (!(x)) || ((struct object *)(x))->o_magic != MAGIC )
#endif

#define OB_INVALID NOGOOD

/**	Maximum number of arguments that can be passed as a typed-list rather than using #A_GIMME.  It is generally recommended to use #A_GIMME. 
	@ingroup obj
*/
enum {
	MSG_MAXARG = 7
};


/** A list of symbols and their corresponding methods,
 	complete with typechecking information.	
	@ingroup obj
*/
typedef struct messlist
{
	struct symbol *m_sym;		///< Name of the message
	method m_fun;				///< Method associated with the message
	char m_type[MSG_MAXARG + 1];	///< Argument type information
} t_messlist;

#ifdef C74_DEFINE_DEPRECATED_TYPES
C74_DEPRECATED( typedef struct messlist Messlist );
#endif

/**	The tiny object structure sits at the head of any object to which you may
 	pass messages (and which you may feed to freeobject()).
	In general, you should use #t_object instead.
	@ingroup obj
*/
typedef struct tinyobject
{
	struct messlist *t_messlist;	///< list of messages and methods 
									// (also used as freelist link)
#ifdef CAREFUL
	long t_magic;					///< magic number
#endif
} t_tinyobject;

#ifdef C74_DEFINE_DEPRECATED_TYPES
C74_DEPRECATED( typedef struct tinyobject Tinyobject );
#endif


/** The structure for the head of any object which wants to have inlets or outlets,
	or support attributes.
	@ingroup obj
*/
typedef struct object
{
	struct messlist *o_messlist;	///<  list of messages and methods. The -1 entry of the message list of an object contains a pointer to its #t_class entry.
									// (also used as freelist link)
#ifdef CAREFUL
	t_ptr_int o_magic;					///< magic number
#endif
	t_inlet *o_inlet;			///<  list of inlets
	t_outlet *o_outlet;		///<  list of outlets
} t_object;

#ifdef C74_DEFINE_DEPRECATED_TYPES
C74_DEPRECATED( typedef struct object Object );
#endif

/** 
	The data structure for a Max class. This struct is provided for debugging convenience, 
	but should be considered opaque and is subject to change without notice.
					
	@ingroup class
*/
typedef struct maxclass
{
	struct symbol *c_sym;			///< symbol giving name of class
	struct object **c_freelist;		// linked list of free ones
	method c_freefun;				// function to call when freeing
	t_getbytes_size c_size;			// size of an instance
	char c_tiny;					// flag indicating tiny header
	char c_noinlet;					// flag indicating no first inlet for patcher
	struct symbol *c_filename;		///< name of file associated with this class
	t_messlist *c_newmess;			// constructor method/type information
	method c_menufun;				// function to call when creating from object pallette (default constructor)
	long c_flags;					// class flags used to determine context in which class may be used
	long c_messcount;				// size of messlist array
	t_messlist *c_messlist;			// messlist arrray
	void *c_attributes;				// t_hashtab object
	void *c_extra;					// t_hashtab object
	long c_obexoffset;				// if non zero, object struct contains obex pointer at specified byte offset
	void *c_methods;				// methods t_hashtab object
	method c_attr_get;				// if not set, NULL, if not present CLASS_NO_METHOD
	method c_attr_gettarget;		// if not set, NULL, if not present CLASS_NO_METHOD
	method c_attr_getnames;			// if not set, NULL, if not present CLASS_NO_METHOD
	struct maxclass *c_superclass;	// a superclass point if this is a derived class
} t_class;

#ifdef C74_DEFINE_DEPRECATED_TYPES
C74_DEPRECATED( typedef struct maxclass Maxclass );
#endif


/** Class flags. If not box or polyglot, class is only accessible in C via known interface
	@ingroup class
*/
typedef enum {
	CLASS_FLAG_BOX =					0x00000001L,	///< for use in a patcher
	CLASS_FLAG_POLYGLOT =				0x00000002L,	///< for use by any text language (c/js/java/etc)
	CLASS_FLAG_NEWDICTIONARY =			0x00000004L,	///< dictionary based constructor
	CLASS_FLAG_REGISTERED =				0x00000008L,	///< for backward compatible messlist implementation (once reg'd can't grow)
	CLASS_FLAG_UIOBJECT =				0x00000010L,	///< for objects that don't go inside a newobj box. 
	CLASS_FLAG_ALIAS =					0x00000020L,	///< for classes that are just copies of some other class (i.e. del is a copy of delay)
	CLASS_FLAG_MULTITOUCH =				0x00000040L,	///< sent multitouch version of mouse messages
	CLASS_FLAG_DO_NOT_PARSE_ATTR_ARGS =	0x00000080L, 	///< override dictionary based constructor attr arg parsing
	CLASS_FLAG_DO_NOT_ZERO =			0x00000100L, 	///< don't zero the object struct on construction (for efficiency)
	CLASS_FLAG_NOATTRIBUTES =			0x00010000L,	///< for efficiency
	CLASS_FLAG_OWNATTRIBUTES =			0x00020000L,	///< for classes which support a custom attr interface (e.g. jitter)
	CLASS_FLAG_PARAMETER =				0x00040000L,	///< for classes which have a parameter
	CLASS_FLAG_RETYPEABLE =				0x00080000L,	///< object box can be retyped without recreating the object
	CLASS_FLAG_OBJECT_METHOD =			0x00100000L,	///< objects of this class may have object specific methods
	CLASS_FLAG_VISUALIZER =				0x00200000L,	///< objects of this class are signal visualizers
	CLASS_FLAG_USES_PROXIES =			0x00400000L, 	///< objects of this class might use proxies (set automatically in proxy_new)
	CLASS_FLAG_OWN_DATA =				0x00800000L,	///< objects of this class save data in their own format
	CLASS_FLAG_DYNAMICCOLOR =			0x01000000L		///< objects which contain colors supporting dynamic colors (set automatically in class_attr_dynamiccolor_init)
} e_max_class_flags;


/** the list of officially recognized types, including pseudotypes for
	commas and semicolons.  Used in two places: 1. the reader, when it reads
	a string, returns long, float, sym, comma, semi, or dollar;
	and 2. each object method comes with an array of them saying what types
	it needs, from among long, float, sym, obj, gimme, and cant.
	
	@ingroup atom
	
	@remark	While these values are defined in an enum, you should use a long to represent the value.
			Using the enum type creates ambiguity in struct size and is subject to various inconsistent 
			compiler settings.
*/
typedef enum {
	A_NOTHING = 0,	///< no type, thus no atom
	A_LONG,			///< long integer
	A_FLOAT,		///< 32-bit float
	A_SYM,			///< t_symbol pointer
	A_OBJ,			///< t_object pointer (for argtype lists; passes the value of sym)
	A_DEFLONG,		///< long but defaults to zero
	A_DEFFLOAT,		///< float, but defaults to zero
	A_DEFSYM,		///< symbol, defaults to ""
	A_GIMME,		///< request that args be passed as an array, the routine will check the types itself.
	A_CANT,			///< cannot typecheck args
	A_SEMI,			///< semicolon
	A_COMMA,		///< comma
	A_DOLLAR,		///< dollar
	A_DOLLSYM,		///< dollar
	A_GIMMEBACK,	///< request that args be passed as an array, the routine will check the types itself. can return atom value in final atom ptr arg. function returns long error code 0 = no err. see gimmeback_meth typedef

	A_DEFER	=		0x41,	///< A special signature for declaring methods. This is like A_GIMME, but the call is deferred.
	A_USURP =		0x42,	///< A special signature for declaring methods. This is like A_GIMME, but the call is deferred and multiple calls within one servicing of the queue are filtered down to one call.
	A_DEFER_LOW =	0x43,	///< A special signature for declaring methods. This is like A_GIMME, but the call is deferref to the back of the queue.
	A_USURP_LOW =	0x44	///< A special signature for declaring methods. This is like A_GIMME, but the call is deferred to the back of the queue and multiple calls within one servicing of the queue are filtered down to one call.
} e_max_atomtypes;


/**	Defines the largest possible string size for an atom
	@ingroup atom */
enum {
	ATOM_MAX_STRLEN = 32768
};

/** Union for packing any of the datum defined in #e_max_atomtypes.
	@ingroup atom
*/
union word		
{
	t_atom_long w_long;			///< long integer
	t_atom_float w_float;	///< 32-bit float
	struct symbol *w_sym;	///< pointer to a symbol in the Max symbol table
	struct object *w_obj;	///< pointer to a #t_object or other generic pointer
};


/** An atom is a typed datum.
	@ingroup atom
*/
typedef struct atom		// and an atom which is a typed datum
{
	short			a_type;	
	union word		a_w;
} t_atom;

#ifdef C74_DEFINE_DEPRECATED_TYPES
C74_DEPRECATED( typedef struct atom Atom );
#endif

/**	Function pointer type for methods with no arguments.
	@ingroup datatypes
*/
typedef void *(*zero_meth)(void *x);


/**	Function pointer type for methods with a single argument.
	@ingroup datatypes
*/
typedef void *(*one_meth)(void *x, void *z);


/**	Function pointer type for methods with two arguments.
	@ingroup datatypes
*/
typedef void *(*two_meth)(void *x, void *z, void *a);


/**	Function pointer type for methods that pass back a result value through the last parameter as a #t_atom, 
	and return an error.
	@ingroup datatypes
*/
typedef long *(*gimmeback_meth)(void *x, t_symbol *s, long ac, t_atom *av, t_atom *rv);



// legacy macros...

#define ob_messlist(x) (((struct object *)(x))->o_messlist - 1)
#define ob_class(x) ((struct maxclass *) \
	(((struct object *)(x))->o_messlist[-1].m_sym))
#define ob_name(x) (ob_class(x)->c_sym->s_name)
#define ob_sym(x) (ob_class(x)->c_sym)
#define ob_filename(x) (ob_class(x)->c_filename->s_name)
#define ob_filesym(x) (ob_class(x)->c_filename)
#define OB_MESS0(x, y) (CALL_METHOD(getfn((struct object *)x, y), (struct object *)x))
#define mess0 OB_MESS0
// #define OB_MESS1(x, y, z1) (*(getfn((struct object *)x, y)))((struct object *)x, z1)
#define OB_MESS1(x, y, z1) (CALL_METHOD(getfn((struct object *)x, y), (struct object *)x, z1))
#define mess1 OB_MESS1
//#define OB_MESS2(x, y, z1,z2) (*(getfn((struct object *)x, y)))((struct object *)x, z1,z2)
#define OB_MESS2(x, y, z1,z2) (CALL_METHOD((getfn((struct object *)x, y)), (struct object *)x, z1, z2))
#define mess2 OB_MESS2
#define mess3(x, y, z1,z2,z3) (CALL_METHOD(getfn((struct object *)x, y), x, z1, z2, z3))
#define mess4(x, y, z1,z2,z3,z4) (CALL_METHOD(getfn((struct object *)x, y), x, z1,z2,z3,z4))
#define mess5(x, y, z1,z2,z3,z4,z5) (CALL_METHOD(getfn((struct object *)x, y), x, z1,z2,z3,z4,z5))
#define floatmess1(x,y,z1)  ((floatmeth)(*(getfn((struct object *)x, y))))((struct object *)x, z1)
#define NIL ((void *)0)
#define A_SETCOMMA(ap) ((ap)->a_type = A_COMMA)
#define A_SETSEMI(ap) ((ap)->a_type = A_SEMI)
#define A_SETSYM(ap, x) ((ap)->a_type = A_SYM, (ap)->a_w.w_sym = (x))
#define A_SETOBJ(ap, x) ((ap)->a_type = A_OBJ, (ap)->a_w.w_obj = (x))
#define A_SETLONG(ap, x) ((ap)->a_type = A_LONG, (ap)->a_w.w_long = (x))
#define A_SETFLOAT(ap, x) ((ap)->a_type = A_FLOAT, (ap)->a_w.w_float = (x))
#define A_SETDOLLAR(ap, x) ((ap)->a_type = A_DOLLAR, (ap)->a_w.w_long = (x))
#define A_SETDOLLSYM(ap,x) ((ap)->a_type = A_DOLLSYM, (ap)->a_w.w_sym = (x))

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

END_USING_C_LINKAGE

#endif /* _EXT_MESS_H_ */
