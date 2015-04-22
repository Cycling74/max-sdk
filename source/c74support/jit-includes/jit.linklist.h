/* 
	jit.linklist.h

	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
		
*/

#ifndef _JIT_LINKLIST_H_
#define _JIT_LINKLIST_H_

#include "ext_linklist.h"

#ifdef __cplusplus
extern "C" {
#endif

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

	
typedef t_llelem t_jit_llelem;	
typedef t_linklist t_jit_linklist;	
void jit_linklist_init(void); //manual class registration	
	
	
// as of Max 6.1, we use the Max linklist from ext_linklist.h for jit_linklist. 
// jit_linklist is aliased to the linklist class, and we leave the following exports
// for compatibility purposes of older compiled externs. they simply call their
// max linklist counterparts

	
#ifdef JIT_LINKLIST_DECLARE_PROTOTYPES 

void *jit_linklist_new(void);
void jit_linklist_free(t_jit_linklist *x);
void jit_linklist_chuck(t_jit_linklist *x); //like free, but don't free the objects
t_atom_long jit_linklist_getsize(t_jit_linklist *x);
void *jit_linklist_getindex(t_jit_linklist *x, long index);
t_jit_llelem *jit_linklist_index2ptr(t_jit_linklist *x, long index);
long jit_linklist_ptr2index(t_jit_linklist *x, t_jit_llelem *p);
t_atom_long jit_linklist_objptr2index(t_jit_linklist *x, void *p);
t_atom_long jit_linklist_append(t_jit_linklist *x, void *o);
t_atom_long jit_linklist_insertindex(t_jit_linklist *x,  void *o, long index); // inserts at index(0 is head)
t_jit_llelem *jit_linklist_insertptr(t_jit_linklist *x,  void *o, t_jit_llelem *p); //inserts before ptr
t_atom_long jit_linklist_deleteindex(t_jit_linklist *x, long index); 
t_atom_long jit_linklist_chuckindex(t_jit_linklist *x, long index);
long jit_linklist_deleteptr(t_jit_linklist *x, t_jit_llelem *p);
long jit_linklist_chuckptr(t_jit_linklist *x, t_jit_llelem *p); //like delete, but don't free it
void jit_linklist_clear(t_jit_linklist *x);

long jit_linklist_insertnodeindex(t_jit_linklist *x, t_jit_llelem *p, long index);
t_jit_llelem *jit_linklist_insertnodeptr(t_jit_linklist *x, t_jit_llelem *p1, t_jit_llelem *p2);
long jit_linklist_appendnode(t_jit_linklist *x, t_jit_llelem *p);

t_jit_llelem *jit_linklistelem_new(void);
void jit_linklistelem_free(t_jit_llelem *x);

t_atom_long jit_linklist_makearray(t_jit_linklist *x, void **a, long max);

void jit_linklist_reverse(t_jit_linklist *x);
void jit_linklist_rotate(t_jit_linklist *x, long i);
void jit_linklist_shuffle(t_jit_linklist *x);
void jit_linklist_swap(t_jit_linklist *x, long a, long b); 
void jit_linklist_findfirst(t_jit_linklist *x, void **o, long cmpfn(void *, void *), void *cmpdata);
void jit_linklist_findall(t_jit_linklist *x, t_jit_linklist **out, long cmpfn(void *, void *), void *cmpdata);
t_atom_long jit_linklist_findcount(t_jit_linklist *x, long cmpfn(void *, void *), void *cmpdata); 
void jit_linklist_methodall(t_jit_linklist *x, t_symbol *s, ...); 
void *jit_linklist_methodindex(t_jit_linklist *x, long i, t_symbol *s, ...); 
void jit_linklist_sort(t_jit_linklist *x, long cmpfn(void *, void *));
void jit_linklist_funall(t_jit_linklist *x, method fun, void *arg);
void jit_linklist_funallsafe(t_jit_linklist *x, method fun, void *arg);
void *jit_linklist_funindex(t_jit_linklist *x, long i, method fun, void *arg);

#else

#define jit_linklist_new				linklist_new
//#define jit_linklist_free				linklist_free			(private/deprecated) should never be called directly
#define jit_linklist_chuck				linklist_chuck
#define jit_linklist_getsize			linklist_getsize
#define jit_linklist_getindex			linklist_getindex
//#define jit_linklist_index2ptr		linklist_index2ptr		(private/deprecated)
//#define jit_linklist_ptr2index		linklist_ptr2index		(private/deprecated)
#define jit_linklist_objptr2index		linklist_objptr2index
#define jit_linklist_append			    linklist_append
#define jit_linklist_insertindex		linklist_insertindex 
//#define jit_linklist_insertptr		linklist_insertptr		(private/deprecated)
#define jit_linklist_deleteindex		linklist_deleteindex 
#define jit_linklist_chuckindex			linklist_chuckindex
//#define jit_linklist_deleteptr		linklist_deleteptr		(private/deprecated)
//#define jit_linklist_chuckptr			linklist_chuckptr		(private/deprecated)
#define jit_linklist_clear			    linklist_clear
//#define jit_linklist_insertnodeindex	linklist_insertnodeindex(private/deprecated)
//#define jit_linklist_insertnodeptr	linklist_insertnodeptr	(private/deprecated)
//#define jit_linklist_appendnode		linklist_appendnode		(private/deprecated)
//#define jit_linklistelem_new			linklistelem_new		(private/deprecated)
//#define jit_linklistelem_free			linklistelem_free		(private/deprecated)
#define jit_linklist_makearray			linklist_makearray	
#define jit_linklist_reverse			linklist_reverse
#define jit_linklist_rotate			    linklist_rotate
#define jit_linklist_shuffle			linklist_shuffle
#define jit_linklist_swap			    linklist_swap 
#define jit_linklist_findfirst			linklist_findfirst
#define jit_linklist_findall			linklist_findall
//#define jit_linklist_findcount		linklist_findcount		// no linklist counterpart. use findall and count linklist size
#define jit_linklist_methodall			linklist_methodall 
#define jit_linklist_methodindex		linklist_methodindex 
#define jit_linklist_sort			    linklist_sort
#define jit_linklist_funall			    linklist_funall
#define jit_linklist_funallsafe			linklist_funall			// no linklist counterpart. funall should be safe
#define jit_linklist_funindex			linklist_funindex
	
#endif	// JIT_LINKLIST_DECLARE_PROTOTYPES

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif // _JIT_LINKLIST_H_

