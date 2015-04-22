// ext_maxtypes.h: Max data types and structure definitions for external objects
// Copyright 1990-2004 IRCAM/Cycling '74 -- All rights reserved

#ifndef _EXT_MAXTYPES_H_
#define _EXT_MAXTYPES_H_

BEGIN_USING_C_LINKAGE

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif


/**	A patcher. As of Max 5, the patcher struct is opaque.  
	Messages can be sent to a patcher using object_method() or object_method_typed(), or by using @ref attr accessors.
	@ingroup patcher
*/
typedef t_object t_patcher;


/**	A box. As of Max 5, the box struct is opaque.  
	Messages can be sent to a box using object_method() or object_method_typed(), or by using @ref attr accessors.
	@ingroup patcher
*/
typedef t_object t_box;


/** A clock. 
	@ingroup	clocks
*/
typedef t_object t_clock;


/** A qelem. 
	@ingroup	qelems
*/
typedef void* t_qelem;


/** patcher iteration flags 
	@ingroup patcher	
*/
enum {
	PI_DEEP = 1,						///< descend into subpatchers (not used by audio library)
	PI_REQUIREFIRSTIN = 2,	///< if b->b_firstin is NULL, do not call function
	PI_WANTBOX = 4,					///< instead, of b->b_firstin, pass b to function, whether or not b->b_firstin is NULL
	PI_SKIPGEN = 8,
	PI_WANTPATCHER = 16
};

/** A simple doubly-linked list used by the #t_funbuff object.
	@ingroup funbuff
*/
typedef struct zll
{											/* note:  no obj header  */
	long	z_x;
	long	z_y;
	struct zll *z_next;
	struct zll *z_prev;
} Zll, t_zll;


/** The structure of a funbuff object 
	@ingroup funbuff
*/
typedef struct funbuff
{
	t_object f_obj;
	void *f_outlet;
	void *f_outlet1;
	void *f_outlet2;
	t_zll f_head;	   		///< head of double linked list of function elements
	t_zll *f_foot;			///< foot in the door pointer for list
	long f_gotoDelta;		///< used by goto and next
	long f_selectX;			///< selected region start
	long f_selectW;			///< selected region width
	t_symbol *f_sym;		///< filename
	long f_y;				///< y-value from inlet
	char f_yvalid;			///< flag that y has been set since x has
	char f_embed;			///< flag for embedding funbuff values in patcher
} Funbuff, t_funbuff;


#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

END_USING_C_LINKAGE

#endif // _EXT_MAXTYPES_H_
