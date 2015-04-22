/* common.h -- those things we define often */
#ifndef _EXT_COMMON_H_
#define _EXT_COMMON_H_


#ifdef WIN_VERSION
#define C74_EXPORT __declspec(dllexport)
#define C74_MUST_CHECK
#else // MAC_VERSION

#define C74_EXPORT __attribute__((visibility("default")))

/** If the result of a function is unused, force a compiler warning about it. */
#define C74_MUST_CHECK __attribute__((warn_unused_result))

#endif


#if C74_NO_CONST == 0
#define C74_CONST const
#else
#define C74_CONST
#endif

#ifdef C74_NO_DEPRECATION
#define C74_DEPRECATED(func) func
#endif

#ifndef C74_DEPRECATED
#ifdef __GNUC__
#define C74_DEPRECATED(func) func __attribute__ ((deprecated))
#elif defined(_MSC_VER)
#define C74_DEPRECATED(func) __declspec(deprecated) func
#else
#define C74_DEPRECATED(func) func
#endif
#endif // C74_DEPRECATED


/**
	If a value is within the specified range, then return true.  Otherwise return false.

	@ingroup	misc
	@param	v	The value to test.
	@param	lo	The low bound for the range.
	@param	hi	The high bound for the range.
	@return		Returns true if within range, otherwise false.
*/
#define INRANGE(v,lo,hi) ((v)<=(hi)&&(v)>=(lo))


/**
	Return the higher of two values.

	@ingroup	misc
	@param	a	The first value to compare.
	@param	b	The second value to compare.
	@return		Returns the higher of a or b.
*/
#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif


/**
	Return the lower of two values.

	@ingroup	misc
	@param	a	The first value to compare.
	@param	b	The second value to compare.
	@return		Returns the lower of a or b.
*/
#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif


/**
	Limit values to within a specified range.

	@ingroup	misc
	@param	a	The value to constrain. NB: CLIP_ASSIGN modifies param 'a' but CLAMP only returns limited value
	@param	lo	The low bound for the range.
	@param	hi	The high bound for the range.
	@return		Returns the value a constrained to the range specified by lo and hi.
*/
#define CLAMP(a, lo, hi) ( (a)>(lo)?( (a)<(hi)?(a):(hi) ):(lo) )
#define CLIP_ASSIGN(a, lo, hi) ((a) = ( (a)>(lo)?( (a)<(hi)?(a):(hi) ):(lo) ))

#ifndef ABS
#define ABS(x) ((x)<0?-(x):(x))
#endif

#endif /* _EXT_COMMON_H_ */
