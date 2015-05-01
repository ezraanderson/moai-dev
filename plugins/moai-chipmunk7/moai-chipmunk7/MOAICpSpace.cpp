// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-chipmunk7/MOAICpArbiter.h>
#include <moai-chipmunk7/MOAICpBody.h>
#include <moai-chipmunk7/MOAICpConstraint.h>
#include <moai-chipmunk7/MOAICpDebugDraw.h>
#include <moai-chipmunk7/MOAICpShape.h>
#include <moai-chipmunk7/MOAICpSpace.h>

#include "chipmunk/chipmunk.h"
#include "chipmunk/chipmunk_unsafe.h"







//|| defined(MOAI_OS_IPHONE) || defined(MOAI_OS_LINUX) || defined(MOAI_OS_OSX)

#if defined(MOAI_OS_ANDROID) || defined(MOAI_OS_IPHONE) || defined(MOAI_OS_LINUX) || defined(MOAI_OS_OSX)

extern "C" {
	#include <chipmunk/cpHastySpace.h>
}  

  static cpSpace *MakeHastySpace(){
    cpSpace *space = cpHastySpaceNew();
    cpHastySpaceSetThreads(space, 0);
    return space;
  }
  
  #define BENCH_SPACE_NEW MakeHastySpace
  #define BENCH_SPACE_FREE cpHastySpaceFree
  #define BENCH_SPACE_STEP cpHastySpaceStep
#endif



#ifdef MOAI_OS_WINDOWS
  #define BENCH_SPACE_NEW cpSpaceNew
  #define BENCH_SPACE_FREE cpSpaceFree
  #define BENCH_SPACE_STEP cpSpaceStep
#endif


//#ifdef MOAI_OS_IPHONE
//#include "chipmunk/cpHastySpace.h"
//  
//  static cpSpace *MakeHastySpace(){
//    cpSpace *space = cpHastySpaceNew();
//    cpHastySpaceSetThreads(space, 0);
//    return space;
//  }
//  
//  #define BENCH_SPACE_NEW MakeHastySpace
//  #define BENCH_SPACE_FREE cpHastySpaceFree
//  #define BENCH_SPACE_STEP cpHastySpaceStep
//#endif



//
//#ifdef MOAI_OS_OSX    
//
//#endif
//
//#ifdef MOAI_OS_WINDOWS
//
//#endif
//
//
//
//#ifdef MOAI_OS_HTML
//
//#endif
//
//#ifdef MOAI_OS_IPHONE
//
//#endif
//
//
//#ifdef MOAI_OS_ANDROID
//
//
//#endif
//

#ifdef MOAI_OS_LINUX

#endif







//================================================================//
// MOAICpPrim
//================================================================//
class MOAICpCollisionHandler  {
public:

	friend class MOAICpSpace;

	cpCollisionType		mTypeA;
	cpCollisionType		mTypeB;
	MOAILuaStrongRef	mHandler;
	u32					mMask;
	
	MOAICpSpace* mSpace;
	MOAICpCollisionHandler* mNext;
};

//================================================================//
// MOAICpPrim
//================================================================//

//----------------------------------------------------------------//
void MOAICpPrim::DoRemove () {
}

//----------------------------------------------------------------//
MOAICpPrim::MOAICpPrim () :
	mSpace ( 0 )
	{
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END
	
	this->mLinkInSpace.Data ( this );
}

//----------------------------------------------------------------//
MOAICpPrim::~MOAICpPrim () {

	this->Remove ();
}

//----------------------------------------------------------------//
void MOAICpPrim::Remove () {

	if ( this->mSpace ) {
		this->mSpace->RemovePrim ( *this );
	}
}

//================================================================//
// collision handlers
//================================================================//

//----------------------------------------------------------------//
static int _cpCollisionFunc ( cpArbiter* arb, void* data, u32 eventType, bool checkResult ) {

	MOAICpCollisionHandler* handler = ( MOAICpCollisionHandler* )data;
	if ( handler->mMask & eventType ) {

		// this can be called during shutdown, so make sure the runtime is still valid
		if ( MOAILuaRuntime::IsValid ()) {

			MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
			if ( handler->mHandler.PushRef ( state )) {
				
				cpShape* a;
				cpShape* b;
				cpArbiterGetShapes ( arb, &a, &b );
				
				if ( a && b ) {
					
					state.Push ( eventType );

						MOAICpShape *shapeGetA = (MOAICpShape *)cpShapeGetUserData(a);
						shapeGetA->PushLuaUserdata(state);

						MOAICpShape *shapeGetB = (MOAICpShape *)cpShapeGetUserData(b);
						shapeGetB->PushLuaUserdata(state);

					//(( MOAICpShape* )a->data )->PushLuaUserdata ( state );
					//(( MOAICpShape* )b->data )->PushLuaUserdata ( state );
					
					MOAICpArbiter* arbiter = handler->mSpace->GetArbiter ();
					arbiter->SetArbiter ( arb );
					arbiter->PushLuaUserdata ( state );
					
					state.DebugCall ( 4, 1 );
					
					//lua_call ( state, 4, 1 );
					
					if ( checkResult ) {
						bool result = state.GetValue < bool >( -1, true );
						return result ? cpTrue : cpFalse;
					}
				}
			}
		}
	}
	return cpTrue;
}

//----------------------------------------------------------------//
static cpBool  _cpCollisionBeginFunc ( cpArbiter* arb, cpSpace* space, void *data ) {
	UNUSED ( space );
	
	if ( cpArbiterIsFirstContact ( arb )) {
		return _cpCollisionFunc ( arb, data, MOAICpSpace::BEGIN, true );
	}
	return true;
}

//----------------------------------------------------------------//
static cpBool _cpCollisionPreSolveFunc ( cpArbiter* arb, cpSpace* space, void *data ) {
	UNUSED ( space );
	return _cpCollisionFunc ( arb, data, MOAICpSpace::PRE_SOLVE, true );
}

//----------------------------------------------------------------//
static void _cpCollisionPostSolveFunc ( cpArbiter* arb, cpSpace* space, void *data ) {
	UNUSED ( space );
	_cpCollisionFunc ( arb, data, MOAICpSpace::POST_SOLVE, false );
}

//----------------------------------------------------------------//
static void _cpCollisionSeparateFunc ( cpArbiter* arb, cpSpace* space, void *data ) {
	UNUSED ( space );
	_cpCollisionFunc ( arb, data, MOAICpSpace::SEPARATE, false );
}










//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************
//*****************************************************************************************************






//================================================================//
// query callbacks
//================================================================//

//----------------------------------------------------------------//
//static void _shapeListForPointCallback ( cpShape *shape, void *data ) {
static void _shapeListForPointCallback(cpShape *shape, cpVect p, cpFloat d, cpVect g, void *data) {

	MOAILuaState& state = *( MOAILuaState* )data;

	MOAICpShape *shapeGet = (MOAICpShape *)cpShapeGetUserData(shape);
	shapeGet->PushLuaUserdata(state);

	//(( MOAICpShape* )shape->data )->PushLuaUserdata ( state );
}

//----------------------------------------------------------------//
static void _shapeListForRectCallback ( cpShape *shape, void *data ) {

	MOAILuaState& state = *( MOAILuaState* )data;	

	MOAICpShape *shapeGet = (MOAICpShape *)cpShapeGetUserData(shape);
	shapeGet->PushLuaUserdata(state);

	//(( MOAICpShape* )shape->data )->PushLuaUserdata ( state );
}

//----------------------------------------------------------------//
static void _shapeListForSegmentCallback ( cpShape *shape, cpVect p, cpVect n, cpFloat t, void *data ) {

	MOAILuaState& state = *( MOAILuaState* )data;
	(( MOAICpShape* )shape->userData )->PushLuaUserdata ( state );
	
	lua_pushnumber ( state, t );
	lua_pushnumber ( state, n.x );
	lua_pushnumber ( state, n.y );
}













//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	activateShapesTouchingShape
	@text	Activates shapes that are currently touching the specified shape.
	
	@in		MOAICpSpace self
	@in		MOAICpShape shape
	@out	nil
*/
int MOAICpSpace::_activateShapesTouchingShape ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "UU" )
	
	MOAICpShape* shape = state.GetLuaObject < MOAICpShape >( 2, true );
	if ( shape && shape->mShape ) {
		//EZRA ERROR
		//cpSpaceActivateShapesTouchingShape ( self->mSpace, shape->mShape );
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@name	getDamping
	@text	Returns the current damping in the space.

	@in		MOAICpSpace self
	@out	number damping
*/
int MOAICpSpace::_getDamping ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "U" )
	
	lua_pushnumber ( L, self->mSpace->damping );
	return 1;
}

//----------------------------------------------------------------//
/**	@name	getGravity
	@text	Returns the current gravity as two return values (x grav, y grav).

	@in		MOAICpSpace self
	@out	number xGrav
	@out	number yGrav
*/
int MOAICpSpace::_getGravity ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "U" )
	
	cpVect gravity = cpSpaceGetGravity(self->mSpace);
	lua_pushnumber ( L, gravity.x );
	lua_pushnumber ( L, gravity.y );
	return 1;
}

//----------------------------------------------------------------//
/**	@name	getIdleSpeedThreshold
	@text	Returns the speed threshold which indicates whether a body
			is idle (less than or equal to threshold) or in motion (greater than threshold).

	@in		MOAICpSpace self
	@out	number idleThreshold
*/
int MOAICpSpace::_getIdleSpeedThreshold ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "U" )
	
	lua_pushnumber ( L, self->mSpace->idleSpeedThreshold );
	return 1;
}

//----------------------------------------------------------------//
/**	@name	getIterations
	@text	Returns the number of iterations the space is configured to perform.
	
	@in		MOAICpSpace self
	@out	number iterations
*/
int MOAICpSpace::_getIterations ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "U" )
	
	lua_pushnumber ( L, self->mSpace->iterations );
	return 1;
}

//----------------------------------------------------------------//
/**	@name	getSleepTimeThreshold
	@text	Returns the sleep time threshold.

	@in		MOAICpSpace self
	@out	number sleepTimeThreshold
*/
int MOAICpSpace::_getSleepTimeThreshold ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "U" )
	
	lua_pushnumber ( L, self->mSpace->sleepTimeThreshold );
	return 1;
}

//----------------------------------------------------------------//
/**	@name	getStaticBody
	@text	Returns the static body associated with this space.

	@in		MOAICpSpace self
	@out	MOAICpBody staticBody
*/
int MOAICpSpace::_getStaticBody ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "U" )
	
	if ( !self->mStaticBody ) {
	//	self->mStaticBody.Set ( *self, new MOAICpBody ());
	//	self->mStaticBody->mBody = &self->mSpace->staticBody;
	//	self->mStaticBody->mBody->userData = self->mStaticBody;
	}
	
	self->mStaticBody->PushLuaUserdata ( state );
	return 1;
}

//----------------------------------------------------------------//
/**	@name	insertPrim
	@text	Inserts a new prim into the world (can be used as a body, joint, etc.)

	@in		MOAICpSpace self
	@in		MOAICpPrim prim
	@out	nil
*/
int MOAICpSpace::_insertPrim ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "UU" )
	
	MOAICpPrim* prim = state.GetLuaObject < MOAICpPrim >( 2, true );
	if ( prim ) {
		self->InsertPrim ( *prim );
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@name	rehashShape
	@text	Updates the shape in the spatial hash.

	@in		MOAICpSpace self
	@in		MOAICpShape shape
	@out	nil
*/
int MOAICpSpace::_rehashShape ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "UU" )
	
	MOAICpShape* shape = state.GetLuaObject < MOAICpShape >( 2, true );
	if ( shape && shape->mShape ) {
		//cpSpaceRehashShape ( self->mSpace, shape->mShape );
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@name	rehashStatic
	@text	Updates the static shapes in the spatial hash.

	@in		MOAICpSpace self
	@out	nil
*/
int MOAICpSpace::_rehashStatic ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "U" )
	
	//cpSpaceRehashStatic ( self->mSpace );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	removePrim
	@text	Removes a prim (body, joint, etc.) from the space.

	@in		MOAICpSpace self
	@in		MOAICpPrim prim
	@out	nil
*/
int MOAICpSpace::_removePrim ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "UU" )
	
	MOAICpPrim* prim = state.GetLuaObject < MOAICpPrim >( 2, true );
	if ( prim ) {
		self->RemovePrim ( *prim );
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@name	resizeActiveHash
	@text	Sets the dimensions of the active object hash.

	@in		MOAICpSpace self
	@in		number dim
	@in		number count
	@out	nil
*/
int MOAICpSpace::_resizeActiveHash ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "UNN" )
	
	cpFloat dim = state.GetValue < cpFloat >( 2, 0 );
	int count = state.GetValue < int >( 3, 0 );
	//cpSpaceResizeActiveHash ( self->mSpace, dim, count );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	resizeStaticHash
	@text	Sets the dimensions of the static object hash.

	@in		MOAICpSpace self
	@in		number dim
	@in		number count
	@out	nil
*/
int MOAICpSpace::_resizeStaticHash ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "UNN" )
	
	cpFloat dim = state.GetValue < cpFloat >( 2, 0 );
	int count = state.GetValue < int >( 3, 0 );
	//cpSpaceResizeStaticHash ( self->mSpace, dim, count );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setCollisionHandler
	@text	Sets a function to handle the specific collision type on
			this object.  If nil is passed as the handler, the collision
			handler is unset.

	@in		MOAICpSpace self
	@in		number collisionTypeA
	@in		number collisionTypeB
	@in		number mask
	@in		function handler
	@out	nil
*/
int MOAICpSpace::_setCollisionHandler ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "UNN" )
	
	cpCollisionType typeA = state.GetValue < cpCollisionType >( 2, 0 );
	cpCollisionType typeB = state.GetValue < cpCollisionType >( 3, 0 );
	
	if ( typeB < typeA ) {
		cpCollisionType temp = typeA;
		typeA = typeB;
		typeB = temp;
	}
	
	if ( state.IsType ( 5, LUA_TFUNCTION )) {
		
		MOAICpCollisionHandler* handler = self->mCollisionHandlers;
		for ( ; handler; handler = handler->mNext ) {
			if (( handler->mTypeA == typeA ) && ( handler->mTypeB == typeB )) break;
		}
		
		if ( !handler ) {
			
			handler = new MOAICpCollisionHandler ();
			handler->mTypeA = typeA;
			handler->mTypeB = typeB;
			handler->mSpace = self;
			
			 cpCollisionHandler *cpHandler = cpSpaceAddCollisionHandler (
				self->mSpace,
				typeA,
				typeB
				//_cpCollisionBeginFunc,
				//_cpCollisionPreSolveFunc,
				//_cpCollisionPostSolveFunc,
				//_cpCollisionSeparateFunc,
				//handler
			);
			

			 cpHandler->beginFunc	 = _cpCollisionBeginFunc;
			 cpHandler->preSolveFunc = _cpCollisionPreSolveFunc;

			 cpHandler->postSolveFunc = _cpCollisionPostSolveFunc;
			 cpHandler->separateFunc  = _cpCollisionSeparateFunc;



			handler->mNext = self->mCollisionHandlers;
			self->mCollisionHandlers = handler;
		}
		
		handler->mMask = state.GetValue < u32 >( 4, ALL );
		handler->mHandler.SetRef ( state, 5 );
	}
	else {
	
		MOAICpCollisionHandler* handler = self->mCollisionHandlers;
		self->mCollisionHandlers = 0;
		
		while ( handler ) {
			MOAICpCollisionHandler* temp = handler;
			handler = handler->mNext;
		
			if (( temp->mTypeA == typeA ) && ( temp->mTypeB == typeB )) {
				//cpSpaceRemoveCollisionHandler ( self->mSpace, typeA, typeB );
				delete temp;
				continue;
			}
			temp->mNext = self->mCollisionHandlers;
			self->mCollisionHandlers = temp;
		}
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setDamping
	@text	Sets the current damping in the space.

	@in		MOAICpSpace self
	@in		number damping
	@out	nil
*/
int MOAICpSpace::_setDamping ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "UN" )
	
	//self->mSpace->damping = state.GetValue < cpFloat >( 2, 0 );
	cpSpaceSetDamping(self->mSpace,state.GetValue < cpFloat >( 2, 0 ));
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setGravity
	@text	Sets the current gravity in the space.

	@in		MOAICpSpace self
	@in		number xGrav
	@in		number yGrav
	@out	nil
*/
int MOAICpSpace::_setGravity ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "UNN" )
	
	cpFloat x = state.GetValue < cpFloat >( 2, 0 );
	cpFloat y = state.GetValue < cpFloat >( 3, 0 );

	cpSpaceSetGravity(self->mSpace, cpv(x,y));

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setIdleSpeedThreshold
	@text	Sets the speed threshold which indicates whether a body is
			idle (less than or equal to threshold) or in motion (greater than threshold).

	@in		MOAICpSpace self
	@in		number threshold
	@out	nil
*/
int MOAICpSpace::_setIdleSpeedThreshold ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "UN" )	
	//self->mSpace->idleSpeedThreshold = state.GetValue < cpFloat >( 2, 0 );
	cpSpaceSetIdleSpeedThreshold(self->mSpace,state.GetValue < cpFloat >( 2, 0 ));
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setIterations
	@text	Sets the number of iterations performed each simulation step.

	@in		MOAICpSpace self
	@in		number iterations
	@out	nil
*/
int MOAICpSpace::_setIterations ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "UN" )	
	 //self->mSpace->iterations = state.GetValue < int >( 2, 0 );
	  cpSpaceSetIterations(self->mSpace, state.GetValue < int >( 2, 0 ));
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setSleepTimeThreshold
	@text	Sets the sleep time threshold. This is the amount of time
			it takes bodies at rest to fall asleep.

	@in		MOAICpSpace self
	@in		number threshold
	@out	nil
*/
int MOAICpSpace::_setSleepTimeThreshold ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "UN" )
	 //self->mSpace->sleepTimeThreshold = state.GetValue < cpFloat >( 2, 0 );
	 cpSpaceSetSleepTimeThreshold(self->mSpace, state.GetValue < cpFloat >( 2, 0 ));

	return 0;
}

//----------------------------------------------------------------//
/**	@name	shapeForPoint
	@text	Retrieves a shape located at the specified X and Y position,
			that exists on the specified layer (or any layer if nil) and
			is part of the specified group (or any group if nil).
			
	@in		MOAICpSpace self
	@in		number x
	@in		number y
	@opt	number layers
	@opt	number group
	@out	MOAICpShape shape
*/
int MOAICpSpace::_shapeForPoint ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "UNN" )
	
	cpVect point;
	point.x = state.GetValue < cpFloat >( 2, 0 );
	point.y = state.GetValue < cpFloat >( 3, 0 );
	
	cpBitmask layers = state.GetValue < cpBitmask >( 4, CP_ALL_CATEGORIES );
	cpGroup group	 = state.GetValue < cpGroup >( 5, CP_NO_GROUP );
	
	//cpShape* shape = cpSpacePointQueryNearest ( self->mSpace, point,0.0f, layers, group );
	cpShapeFilter GRAB_FILTER = cpShapeFilterNew(1, CP_ALL_CATEGORIES, CP_NO_GROUP);
	cpPointQueryInfo info;
    cpShape* shape = (cpSpacePointQueryNearest(self->mSpace, point, 0, GRAB_FILTER, &info));

	if ( shape ) {
			(( MOAICpShape* )shape->userData )->PushLuaUserdata ( state );
			return 1;
	};
	



	//if ( shape ) {
	//	(( MOAICpShape* )shape->userData )->PushLuaUserdata ( state );
	//	return 1;
	//}


	return 0;
}

//----------------------------------------------------------------//
/**	@name	shapeForSegment
	@text	Retrieves a shape that crosses the segment specified, that exists
			on the specified layer (or any layer if nil) and is part of the
			specified group (or any group if nil).
			
	@in		MOAICpSpace self
	@in		number x1
	@in		number y1
	@in		number x2
	@in		number y2
	@opt	number layers
	@opt	number group
	@out	MOAICpShape shape
*/
int MOAICpSpace::_shapeForSegment ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "UNNNN" )
	
	cpVect start;
	start.x = state.GetValue < cpFloat >( 2, 0 );
	start.y = state.GetValue < cpFloat >( 3, 0 );
	
	cpVect end;
	end.x = state.GetValue < cpFloat >( 4, 0 );
	end.y = state.GetValue < cpFloat >( 5, 0 );
	
	int layers = state.GetValue < int >( 6, CP_ALL_CATEGORIES );
	int group = state.GetValue < int >( 7, CP_ALL_CATEGORIES );
	
	cpShapeFilter filter = cpShapeFilterNew(1, CP_ALL_CATEGORIES, CP_ALL_CATEGORIES);

	cpSegmentQueryInfo info;
	
	cpShape* shape = cpSpaceSegmentQueryFirst (
		self->mSpace,
		start,
		end,
		0.0f,//RADIUS
		filter,		
		&info
	);
	
	if ( shape ) {
		(( MOAICpShape* )shape->userData )->PushLuaUserdata ( state );
		//MOAICpShape *shapeGet = (MOAICpShape *)cpShapeGetUserData(shape);
		//EZRA
		//lua_pushnumber ( state, info.t );
		//lua_pushnumber ( state, info.n.x );
		///lua_pushnumber ( state, info.n.y );

		lua_pushnumber ( state, info.alpha );
		lua_pushnumber ( state, info.point.x );
		lua_pushnumber ( state, info.point.y );
		return 4;
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@name	shapeListForPoint
	@text	Retrieves a list of shapes that overlap the point specified, that exists
			on the specified layer (or any layer if nil) and is part of the
			specified group (or any group if nil).
			
	@in		MOAICpSpace self
	@in		number x
	@in		number y
	@opt	number layers
	@opt	number group
	@out	MOAICpShape shapes		The shapes that were matched as multiple return values.
*/
int MOAICpSpace::_shapeListForPoint ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "UNN" )
	
	cpVect point;
	point.x = state.GetValue < cpFloat >( 2, 0 );
	point.y = state.GetValue < cpFloat >( 3, 0 );
	
	//cpLayers layers = state.GetValue < cpLayers >( 4, CP_ALL_LAYERS );
	//cpLayers group = state.GetValue < cpGroup >( 5, CP_NO_GROUP );
	

	cpBitmask layers = state.GetValue < cpBitmask >( 4, CP_ALL_CATEGORIES );
	cpGroup group	 = state.GetValue < cpGroup >( 5, CP_NO_GROUP );
	
	
	cpShapeFilter GRAB_FILTER = cpShapeFilterNew(1, layers, group);


	int base = state.GetTop ();
	
	cpSpacePointQuery (
		self->mSpace,
		point,
		0.0,
		GRAB_FILTER,
		_shapeListForPointCallback,
		&state
	);

	//(cpSpacePointQueryFunc)PointQueryIteratorFunc


	int results = state.GetTop () - base;
	return results;
}

//----------------------------------------------------------------//
/**	@name	shapeListForRect
	@text	Retrieves a list of shapes that overlap the rect specified, that exists
			on the specified layer (or any layer if nil) and is part of the
			specified group (or any group if nil).
			
	@in		MOAICpSpace self
	@in		number xMin
	@in		number yMin
	@in		number xMax
	@in		number yMax
	@opt	number layers
	@opt	number group
	@out	MOAICpShape shapes		The shapes that were matched as multiple return values.
*/
int MOAICpSpace::_shapeListForRect ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "UNNNN" )
	
	ZLMetaRect < cpFloat > rect = state.GetRect < cpFloat >( 2 ); 
	rect.Bless ();
	
	cpBB bb;
	bb.l = rect.mXMin;
	bb.b = rect.mYMin;
	bb.r = rect.mXMax;
	bb.t = rect.mYMax;
	
	//cpLayers layers = state.GetValue < cpLayers >( 6, CP_ALL_LAYERS );
	//cpLayers group = state.GetValue < cpGroup >( 7, CP_NO_GROUP );


	cpBitmask layers = state.GetValue < cpBitmask >( 4, CP_ALL_CATEGORIES );
	cpGroup group	 = state.GetValue < cpGroup >( 5, CP_NO_GROUP );

	cpShapeFilter GRAB_FILTER = cpShapeFilterNew(1, layers, group);

	int base = state.GetTop ();
	
	cpSpaceBBQuery (
		self->mSpace,
		bb,	
		GRAB_FILTER,
		_shapeListForRectCallback,
		&state
	);
	
	int results = state.GetTop () - base;
	return results;
}

//----------------------------------------------------------------//
/**	@name	shapeListForSegment
	@text	Retrieves a list of shapes that overlap the segment specified, that exists
			on the specified layer (or any layer if nil) and is part of the
			specified group (or any group if nil).
			
	@in		MOAICpSpace self
	@in		number x1
	@in		number y1
	@in		number x2
	@in		number y2
	@opt	number layers
	@opt	number group
	@out	MOAICpShape shapes		The shapes that were matched as multiple return values.
*/
int MOAICpSpace::_shapeListForSegment ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "UNNNN" )
	
	cpVect start;
	start.x = state.GetValue < cpFloat >( 2, 0 );
	start.y = state.GetValue < cpFloat >( 3, 0 );
	
	cpVect end;
	end.x = state.GetValue < cpFloat >( 4, 0 );
	end.y = state.GetValue < cpFloat >( 5, 0 );
	
//	cpLayers layers = state.GetValue < cpLayers >( 6, CP_ALL_LAYERS );
//	cpLayers group = state.GetValue < cpGroup >( 7, CP_NO_GROUP );

	cpBitmask layers = state.GetValue < cpBitmask >( 4, CP_ALL_CATEGORIES );
	cpGroup group	 = state.GetValue < cpGroup >( 5, CP_NO_GROUP );

	cpShapeFilter GRAB_FILTER = cpShapeFilterNew(1, layers, group);

		
	int base = state.GetTop ();
	
	cpSpaceSegmentQuery (
		self->mSpace,
		start,
		end,
		0.0f,
		GRAB_FILTER,
		_shapeListForSegmentCallback,
		&state
	);
	
	int results = state.GetTop () - base;
	return results;
}

//================================================================//
// MOAICpSpace
//================================================================//

//----------------------------------------------------------------//
void MOAICpSpace::DrawDebug () {

	if ( this->mSpace ) {
		
		MOAICpDebugDrawOptions options;

		options.drawHash = 0;
		options.drawBBs = 0;
		options.drawShapes = 1;
		options.collisionPointSize = 4.0f;
		options.bodyPointSize = 0.0f;
		options.lineThickness = 1.5f;

		MOAIGfxDevice::Get ().SetTexture ();

		zglEnableClientState ( ZGL_PIPELINE_VERTEX_ARRAY );
		MOAICpDebugDraw::DrawSpace ( this->mSpace, &options );
	}
}

//----------------------------------------------------------------//
MOAICpArbiter* MOAICpSpace::GetArbiter () {

	if ( !this->mArbiter ) {
		this->mArbiter.Set ( *this, new MOAICpArbiter ());
	}
	return this->mArbiter;
}

//----------------------------------------------------------------//
void MOAICpSpace::InsertPrim ( MOAICpPrim& prim ) {

	if ( prim.mSpace == this ) return;
	
	this->LuaRetain ( &prim );

	if ( prim.mSpace ) {
		prim.mSpace->RemovePrim ( prim );
	}

	prim.CpAddToSpace ( this->mSpace );
	this->mPrims.PushBack ( prim.mLinkInSpace );
	prim.mSpace = this;
}

//----------------------------------------------------------------//
bool MOAICpSpace::IsDone () {

	return false;
}

//----------------------------------------------------------------//
MOAICpSpace::MOAICpSpace () :
	mSpace ( 0 ),
	mCollisionHandlers ( 0 ) ,
	mBench( 0.0 ),
	mTime ( 0.0 ),
	mStep (0 )
	{
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIAction )
	RTTI_END

	 this->mSpace = BENCH_SPACE_NEW();
	

 cpSpaceSetIterations(this->mSpace,1);

  //cpSpaceSetSleepTimeThreshold(this->mSpace, 0.5f);
  //cpSpaceSetCollisionSlop(this->mSpace, 0.5f);
  //cpSpaceSetDamping(this->mSpace, 0.5f);

   // cpSpaceUseSpatialHash(this->mSpace,32, 90000);
		
}

//----------------------------------------------------------------//
MOAICpSpace::~MOAICpSpace () {

	PrimIt primIt;
	
	for ( primIt = this->mPrims.Head (); primIt; primIt = primIt->Next ()) {
		MOAICpPrim* prim = primIt->Data ();
		prim->CpRemoveFromSpace ( this->mSpace );
		prim->mSpace = 0;
	}

	primIt = this->mPrims.Head ();
	while ( primIt ) {
		MOAICpPrim* prim = primIt->Data ();
		primIt = primIt->Next ();
		this->LuaRelease ( prim );
	}

	this->mPrims.Clear ();

	if ( this->mStaticBody ) {
		this->mStaticBody->ClearShapes ();
		this->mStaticBody->mBody = 0;
	}

	// DO THIS LAST! cpShape hangs on to refs to its handler and will
	// attempt to call it as it is being release; if the handlers are
	// removed/deleted first, the app will crash
	while ( this->mCollisionHandlers ) {
	
		MOAICpCollisionHandler* handler = this->mCollisionHandlers;
		this->mCollisionHandlers = this->mCollisionHandlers->mNext;
		
	
		//ERROR CAN"T REMOVE
		//cpSpaceRemoveCollisionHandler ( this->mSpace, handler->mTypeA, handler->mTypeB );

		delete handler;
	}

	this->mStaticBody.Set ( *this, 0 );
	this->mArbiter.Set ( *this, 0 );

	//cpSpaceFree ( this->mSpace );
		BENCH_SPACE_FREE(this->mSpace);
}

//----------------------------------------------------------------//
void MOAICpSpace::OnUpdate ( float step ) {
	
	ZLLeanList < MOAICpPrim* > removeList;
	
	if ( this->mSpace ) {

		mStep = mStep + 1;		
		double start_time = ZLDeviceTime::GetTimeInSeconds();
	
		BENCH_SPACE_STEP( this->mSpace, step );

		cpBody** bodies = ( cpBody** )this->mSpace->dynamicBodies->arr;
		int num = this->mSpace->dynamicBodies->num;
		
		for ( int i = 0; i < num; ++i ) {
			MOAICpBody* body = ( MOAICpBody* )bodies [ i ]->userData;

				//b2Body* body = t
			if (cpBodyIsSleeping(bodies[i]) == false) {
				body->ScheduleUpdate ();
			}
			
			if ( body->mRemoveFlag != MOAICpBody::NONE ) {
				body->mLinkInSpace.Remove ();
				removeList.PushBack ( body->mLinkInSpace );
			}
		}
		


		while ( removeList.Count ()) {
			MOAICpPrim* prim = removeList.Front ();
			removeList.PopFront ();
			prim->DoRemove ();
		}


		mBench = mBench +  ZLDeviceTime::GetTimeInSeconds()-start_time;
		if (mStep == 60) {		
			mTime	= mBench / mStep;
			mStep	= 1;
			mBench  = 0;
		}


	}




}



//***********************************************************************
int MOAICpSpace::_drawDebugLua ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "U" )
   
	self->DrawDebug ();
	return 0;
};

//***********************************************************************
int MOAICpSpace::_benchmark ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICpSpace, "U" )   
	lua_pushnumber ( state, self->mTime);
	return 1;
};

//----------------------------------------------------------------//
void MOAICpSpace::RegisterLuaClass ( MOAILuaState& state ) {

	MOAIAction::RegisterLuaClass ( state );
	
	state.SetField ( -1, "BEGIN", ( u32 )BEGIN );
	state.SetField ( -1, "PRE_SOLVE", ( u32 )PRE_SOLVE );
	state.SetField ( -1, "POST_SOLVE", ( u32 )POST_SOLVE );
	state.SetField ( -1, "SEPARATE", ( u32 )SEPARATE );
	state.SetField ( -1, "ALL", ( u32 )ALL );
}

//----------------------------------------------------------------//
void MOAICpSpace::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	MOAIAction::RegisterLuaFuncs ( state );
	
	luaL_Reg regTable [] = {
		{ "activateShapesTouchingShape",	_activateShapesTouchingShape },
		{ "getDamping",						_getDamping },
		{ "getGravity",						_getGravity },
		{ "getIdleSpeedThreshold",			_getIdleSpeedThreshold },
		{ "getIterations",					_getIterations },
		{ "getSleepTimeThreshold",			_getSleepTimeThreshold },
		{ "getStaticBody",					_getStaticBody },
		{ "insertPrim",						_insertPrim },
		{ "rehashShape",					_rehashShape },
		{ "rehashStatic",					_rehashStatic },
		{ "removePrim",						_removePrim },
		{ "resizeActiveHash",				_resizeActiveHash },
		{ "resizeStaticHash",				_resizeStaticHash },
		{ "setCollisionHandler",			_setCollisionHandler },
		{ "setDamping",						_setDamping },
		{ "setGravity",						_setGravity },
		{ "setIdleSpeedThreshold",			_setIdleSpeedThreshold },
		{ "setIterations",					_setIterations },
		{ "setSleepTimeThreshold",			_setSleepTimeThreshold },
		{ "shapeForPoint",					_shapeForPoint },
		{ "shapeForSegment",				_shapeForSegment },
		{ "shapeListForPoint",				_shapeListForPoint },
		{ "shapeListForRect",				_shapeListForRect },
		{ "shapeListForSegment",			_shapeListForSegment },

		{ "benchmark",					    _benchmark },
		{ "drawDebugLua",					_drawDebugLua },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAICpSpace::RemovePrim ( MOAICpPrim& prim ) {

	if ( prim.mSpace != this ) return;
	
	prim.CpRemoveFromSpace ( this->mSpace );
	this->mPrims.Remove ( prim.mLinkInSpace );
	
	prim.mSpace = 0;
	this->LuaRelease ( &prim );
}
