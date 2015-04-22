/* 
	jit.fixmath.h

	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
	
*/

#ifndef __JIT_FIXMATH_H__
#define __JIT_FIXMATH_H__

/* the following is to account for duplicates in GXMath.h */

#ifdef fixed1
#undef fixed1
#endif
#ifdef IntToFixed                    
#undef IntToFixed                    
#endif
#ifdef FloatToFixed                
#undef FloatToFixed                
#endif
#ifdef FixedToInt 
#undef FixedToInt 
#endif
#ifdef FixedToFloat        
#undef FixedToFloat        
#endif

#ifndef __MACTYPES__
typedef t_int32                         Fixed;
typedef Fixed *							FixedPtr;
typedef t_int32                         Fract;
typedef Fract *                         FractPtr;
typedef t_uint32                        UnsignedFixed;
typedef UnsignedFixed *                 UnsignedFixedPtr;
typedef short                           ShortFixed;
typedef ShortFixed *                    ShortFixedPtr;
#endif

#define fixed1		(1<<16L) 
#define fixedhalf	(1<<15L)
#define IntToFixed(x) ((Fixed)((x)<<16L))                     
#define FloatToFixed(x) ((Fixed)((x) * (float)fixed1))                    
#define DoubleToFixed(x) ((Fixed)((x) * (double)fixed1))                  
#define FixedToInt(x) ((x)>>16L)                    
#define FixedToFloat(x) ((float) (x) * 1./(float)fixed1)            
#define FixedToDouble(x) ((double)(x) * 1./(double)fixed1)         
#define FixMul(x,y) (((y)>>8L) * ((x)>>8L))   //both are large(>1)         	
#define FixMul2(x,y) (((y) * ((x)>>8L))>>8L)  //y is small          
#define FixMul3(x,y) ((((y)>>8L) * (x))>>8L)  //x is small          
#define FixMul4(x,y) (((y) * (x))>>16L)       //both are small          

#define FixDiv(x,y) ((((y)>>8L)!=0)?((((x)<<4L) / ((y)>>8L))<<4L):0)
#define FixedFraction(x) ((x)&0xffffL)        //unsigned fraction    
#define FixedFractionSigned(x) ((x)&0x8000ffffL)         

#define FixedEps ((long) 1)
#define FixedOneMinusEps (fixed1 - FixedEps)
#define FixedFrac(x) ((x) & FixedOneMinusEps)
#define FixedFloor(x) ((x) & ~FixedOneMinusEps)
#define FixedCeil(x) FixedFloor((x) + FixedOneMinusEps)
#define FixedMod2(x) ((x) & (fixed1 | FixedOneMinusEps))

#ifdef FixedRound
#undef FixedRound
#endif
#define FixedRound(x) ((FixedFrac(x) < fixedhalf) ? FixedFloor(x) : FixedCeil(x))

#endif //__JIT_FIXMATH_H__
