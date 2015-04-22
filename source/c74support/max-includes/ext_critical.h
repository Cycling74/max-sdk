// critical.h -- platform-independent way to define critical regions

#ifndef _EXT_CRITICAL_H_
#define _EXT_CRITICAL_H_

BEGIN_USING_C_LINKAGE

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

#ifdef MAC_VERSION

typedef MPCriticalRegionID t_critical;	///< a critical region  @ingroup critical
	
#endif // MAC_VERSION
	
#ifdef WIN_VERSION
	
typedef LPCRITICAL_SECTION t_critical;	///< a critical region  @ingroup critical
	
#endif  // WIN_VERSION
	

/**
	Create a new critical region.
	Normally, you do not need to create your own critical region, because 
	you can use Max’s global critical region. Only use this function (in 
	your object’s instance creation method) if you are certain you are not 
	able to use the global critical region.
	
	@ingroup	critical
	@param	x	A #t_critical struct will be returned to you via this pointer.
*/
void critical_new(t_critical *x);


/**
	Enter a critical region.
	Typically you will want the argument to be zero to enter the global 
	critical region, although you could pass your own critical created with 
	critical_new(). It is important to try to keep the amount of code in 
	the critical region to a minimum.
	Exit the critical region with critical_exit().
		
	@ingroup	critical
	@param	x	A pointer to a #t_critical struct, or zero to uses Max’s global critical region. 
	@see		critical_exit()
*/
void critical_enter(t_critical x);


/**
	Leave a critical region.
	Typically you will want the argument to be zero to exit the global 
	critical region, although, you if you are using your own critical regions 
	you will want to pass the same one that you previously passed to 
	critical_enter().

	@ingroup	critical
	@param	x	A pointer to a #t_critical struct, or zero to uses Max’s global critical region. 
*/
void critical_exit(t_critical x);


/**
	Free a critical region created with critical_new().
	If you created your own critical region, you will need to free it in your object’s free method.
	
	@ingroup	critical
	@param	x	The #t_critical struct that will be freed.
*/
void critical_free(t_critical x);


/**	Try to enter a critical region if it is not locked.
	@ingroup	critical
	@param	x	A pointer to a #t_critical struct, or zero to uses Max’s global critical region. 
	@return		returns non-zero if there was a problem entering
	@see		critical_enter()
*/
short critical_tryenter(t_critical x);


#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

END_USING_C_LINKAGE

#endif // _EXT_CRITICAL_H_
