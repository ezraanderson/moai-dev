#include "pch.h"
#include <moai-math/MOAIMathNeon.h>

#include <math.h>

//
//#if defined(MOAI_OS_ANDROID) 
//	#include <android/log.h>
//	#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "MOAI-C++", __VA_ARGS__))
//#endif

#if defined(_WIN32)
	#include <windows.h>
	#include <Psapi.h>
#elif defined(__APPLE__) //&& defined(TARGET_IPHONE_SIMULATOR)
	// Not sure if using mach API is disallowed in the app store. :/
	#include <mach/mach.h>
	#include <unistd.h>
#elif defined (__QNX__)
	#include <unistd.h>
#elif defined (__EMSCRIPTEN__)
  #include <unistd.h>
#elif defined (ANDROID)
  #include <unistd.h>
#endif



#if __ARM_NEON__
extern "C" {
	#include <moai-math/math-neon/math_neon.h>
	}
#else
	#include <moai-math/math-neon/math_neon.h>
#endif

//
//static float FOPI = 1.27323954473516;
//static float PIO4F = 0.7853981633974483096;
///* These are for a 24-bit significand: */
//static float DP1 = 0.78515625;
//static float DP2 = 2.4187564849853515625e-4;
//static float DP3 = 3.77489497744594108e-8;
//static float lossth = 8192.;
//static float T24M1 = 16777215.;
//
//static float sincof[] = {
//  -1.9515295891E-4,
//  8.3321608736E-3,
//  -1.6666654611E-1
//};
//static float coscof[] = {
//  2.443315711809948E-005,
//  -1.388731625493765E-003,
//  4.166664568298827E-002
//};
//
//static float cephes_sinf( float xx )
//{
//  float *p;
//  float x, y, z;
//  register unsigned long j;
//  register int sign;
//
//  sign = 1;
//  x = xx;
//  if( xx < 0 )
//    {
//      sign = -1;
//      x = -xx;
//    }
//  if( x > T24M1 )
//    {
//      //mtherr( "sinf", TLOSS );
//      return(0.0);
//    }
//  j = FOPI * x; /* integer part of x/(PI/4) */
//  y = j;
//  /* map zeros to origin */
//  if( j & 1 )
//    {
//      j += 1;
//      y += 1.0;
//    }
//  j &= 7; /* octant modulo 360 degrees */
//  /* reflect in x axis */
//  if( j > 3)
//    {
//      sign = -sign;
//      j -= 4;
//    }
//  if( x > lossth )
//    {
//      //mtherr( "sinf", PLOSS );
//      x = x - y * PIO4F;
//    }
//  else
//    {
//      /* Extended precision modular arithmetic */
//      x = ((x - y * DP1) - y * DP2) - y * DP3;
//    }
//  /*einits();*/
//  z = x * x;
//  //printf("my_sinf: corrected oldx, x, y = %14.10g, %14.10g, %14.10g\n", oldx, x, y);
//  if( (j==1) || (j==2) )
//    {
//      /* measured relative error in +/- pi/4 is 7.8e-8 */
//      /*
//        y = ((  2.443315711809948E-005 * z
//        - 1.388731625493765E-003) * z
//        + 4.166664568298827E-002) * z * z;
//      */
//      p = coscof;
//      y = *p++;
//      y = y * z + *p++;
//      y = y * z + *p++;
//      y *= z; y *= z;
//      y -= 0.5 * z;
//      y += 1.0;
//    }
//  else
//    {
//      /* Theoretical relative error = 3.8e-9 in [-pi/4, +pi/4] */
//      /*
//        y = ((-1.9515295891E-4 * z
//        + 8.3321608736E-3) * z
//        - 1.6666654611E-1) * z * x;
//        y += x;
//      */
//      p = sincof;
//      y = *p++;
//      y = y * z + *p++;
//      y = y * z + *p++;
//      y *= z; y *= x;
//      y += x;
//    }
//  /*einitd();*/
//  //printf("my_sinf: j=%d result = %14.10g * %d\n", j, y, sign);
//  if(sign < 0)
//    y = -y;
//  return( y);
//}
//
//
//
//
//
//
//
//float cephes_cosf( float xx )
//{
//  float x, y, z;
//  int j, sign;
//
//  /* make argument positive */
//  sign = 1;
//  x = xx;
//  if( x < 0 )
//    x = -x;
//
//  if( x > T24M1 )
//    {
//      //mtherr( "cosf", TLOSS );
//      return(0.0);
//    }
//
//  j = FOPI * x; /* integer part of x/PIO4 */
//  y = j;
//  /* integer and fractional part modulo one octant */
//  if( j & 1 )	/* map zeros to origin */
//    {
//      j += 1;
//      y += 1.0;
//    }
//  j &= 7;
//  if( j > 3)
//    {
//      j -=4;
//      sign = -sign;
//    }
//
//  if( j > 1 )
//    sign = -sign;
//
//  if( x > lossth )
//    {
//      //mtherr( "cosf", PLOSS );
//      x = x - y * PIO4F;
//    }
//  else
//    /* Extended precision modular arithmetic */
//    x = ((x - y * DP1) - y * DP2) - y * DP3;
//
//  //printf("xx = %g -> x corrected = %g sign=%d j=%d y=%g\n", xx, x, sign, j, y);
//
//  z = x * x;
//
//  if( (j==1) || (j==2) )
//    {
//      y = (((-1.9515295891E-4f * z
//             + 8.3321608736E-3f) * z
//            - 1.6666654611E-1f) * z * x)
//        + x;
//    }
//  else
//    {
//      y = ((  2.443315711809948E-005f * z
//              - 1.388731625493765E-003f) * z
//           + 4.166664568298827E-002f) * z * z;
//      y -= 0.5 * z;
//      y += 1.0;
//    }
//  if(sign < 0)
//    y = -y;
//  return( y );
//}
//
//
////**********************************************************************************
////**********************************************************************************
//
//

static const float __sinf_rng[2] = {
	2.0 / M_PI,
	M_PI / 2.0
} ALIGN(16);

static const float __sinf_lut[4] = {
	-0.00018365f,	//p7
	-0.16664831f,	//p3
	+0.00830636f,	//p5
	+0.99999661f,	//p1
} ALIGN(16);


static float sinfEZ(float x)
{
#ifdef __MATH_NEON
	asm volatile (
	
	"vld1.32 		d3, [%0]				\n\t"	//d3 = {invrange, range}
	"vdup.f32 		d0, d0[0]				\n\t"	//d0 = {x, x}
	"vabs.f32 		d1, d0					\n\t"	//d1 = {ax, ax}
	
	"vmul.f32 		d2, d1, d3[0]			\n\t"	//d2 = d1 * d3[0] 
	"vcvt.u32.f32 	d2, d2					\n\t"	//d2 = (int) d2
	"vmov.i32	 	d5, #1					\n\t"	//d5 = 1	
	"vcvt.f32.u32 	d4, d2					\n\t"	//d4 = (float) d2	
	"vshr.u32 		d7, d2, #1				\n\t"	//d7 = d2 >> 1
	"vmls.f32 		d1, d4, d3[1]			\n\t"	//d1 = d1 - d4 * d3[1]
	
	"vand.i32 		d5, d2, d5				\n\t"	//d5 = d2 & d5
	"vclt.f32 		d18, d0, #0				\n\t"	//d18 = (d0 < 0.0)
	"vcvt.f32.u32 	d6, d5					\n\t"	//d6 = (float) d5
	"vmls.f32 		d1, d6, d3[1]			\n\t"	//d1 = d1 - d6 * d3[1]
	"veor.i32 		d5, d5, d7				\n\t"	//d5 = d5 ^ d7	
	"vmul.f32 		d2, d1, d1				\n\t"	//d2 = d1*d1 = {x^2, x^2}	
	
	"vld1.32 		{d16, d17}, [%1]		\n\t"	//q8 = {p7, p3, p5, p1}
	"veor.i32 		d5, d5, d18				\n\t"	//d5 = d5 ^ d18	
	"vshl.i32 		d5, d5, #31				\n\t"	//d5 = d5 << 31
	"veor.i32 		d1, d1, d5				\n\t"	//d1 = d1 ^ d5
	
	"vmul.f32 		d3, d2, d2				\n\t"	//d3 = d2*d2 = {x^4, x^4}		
	"vmul.f32 		q0, q8, d1[0]			\n\t"	//q0 = q8 * d1[0] = {p7x, p3x, p5x, p1x}
	"vmla.f32 		d1, d0, d2[0]			\n\t"	//d1 = d1 + d0*d2 = {p5x + p7x^3, p1x + p3x^3}		
	"vmla.f32 		d1, d3, d1[0]			\n\t"	//d1 = d1 + d3*d0 = {...., p1x + p3x^3 + p5x^5 + p7x^7}		

	"vmov.f32 		s0, s3					\n\t"	//s0 = s3
	: 
	: "r"(__sinf_rng), "r"(__sinf_lut) 
    : "q0", "q1", "q2", "q3", "q8", "q9"
	);
#else
	return 1;
#endif
}










//CLASS
int MOAIMathNeon::_classHello ( lua_State* L ) {
	UNUSED ( L );
	return 0;
}











//----------------------------------------------------------------//
//INSTANCE
int MOAIMathNeon::_getDirNeon ( lua_State* L ) {
MOAILuaState state ( L );

	//float  x1 =state.GetValue < float >( 1, 0 );
	//float  y1 =state.GetValue < float >( 2, 0 );

	//float  x2 = state.GetValue < float >( 3, 0 );
	//float  y2 = state.GetValue < float >( 4, 0 );


	double start_time = ZLDeviceTime::GetTimeInSeconds();

	#ifndef MOAI_OS_WINDOWS
	usleep ( 1 );
	#else
	// WARNING: sleep on windows is not quite as precise
	Sleep ( 1 );
	#endif


	 for (int i = 0; i < 5000; ++i) {
	//	float angle	  = atan2f_neon(  (1 - 1) , (1 - 1) );
	//	float dx 	  = cosf_neon(0.5);
		float dy 	  = sinfEZ(0.5);
	}

double time = ZLDeviceTime::GetTimeInSeconds()-start_time;
lua_pushnumber ( state, time  );



return 1;	
}

//----------------------------------------------------------------//
//INSTANCE
int MOAIMathNeon::_getDir ( lua_State* L ) {
MOAILuaState state ( L );

	double start_time = ZLDeviceTime::GetTimeInSeconds();

	#ifndef MOAI_OS_WINDOWS
	usleep ( 1 );
	#else
	Sleep ( 1 );
	#endif
	
    for (int i = 0; i < 5000; ++i) {
	//		float angle	  = atan2f(  (1 - 1) , (1 - 1) );
	//		float dx 	  = cosf(0.5);
			float dy 	  = sinf(0.5); 
	};

double time = ZLDeviceTime::GetTimeInSeconds()-start_time;
lua_pushnumber ( state, time  );


return 1;	
}






//================================================================//
// MOAIFoo
//================================================================//

//----------------------------------------------------------------//
MOAIMathNeon::MOAIMathNeon () {

	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
		// and any other objects from multiple inheritance...
		// RTTI_EXTEND ( MOAIFooBase )
		RTTI_END
}

//----------------------------------------------------------------//
MOAIMathNeon::~MOAIMathNeon () {
}

//----------------------------------------------------------------//
void MOAIMathNeon::RegisterLuaClass ( MOAILuaState& state ) {

	// call any initializers for base classes here:
	// MOAIFooBase::RegisterLuaClass ( state );

	// also register constants:
	// state.SetField ( -1, "FOO_CONST", ( u32 )FOO_CONST );

	// here are the class methods:
	luaL_Reg regTable [] = {
		{ "classHello",		_classHello },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIMathNeon::RegisterLuaFuncs ( MOAILuaState& state ) {

	// call any initializers for base classes here:
	// MOAIMathNeon::RegisterLuaFuncs ( state );
	//MOAITransformBase::RegisterLuaFuncs ( state );


	// here are the instance methods:
	luaL_Reg regTable [] = {
		{ "getDirNeon",	_getDirNeon },
		{ "getDir",	_getDir },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

