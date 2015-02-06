// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <bullet/src/btBulletDynamicsCommon.h>
#include <moai-bullet/MOAIBulletBody.h>
#include <moai-bullet/MOAIBulletJoint.h>
#include <moai-bullet/MOAIBulletWorld.h>
//----------------------------------------------------------------//
int MOAIBulletJoint::_getBreakingImpulse ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletJoint, "U" )
	float unitsToMeters = self->GetUnitsToMeters ();

	if ( !self->mJoint ) {
		MOAILog ( state, MOAILogMessages::MOAIBox2DJoint_MissingInstance );
		return 0;
	}

	float length = state.GetValue < float >( 2, 0.0f );	
	btTypedConstraint*	joint = self->mJoint;

	state.Push ( joint->getBreakingImpulseThreshold() );
	
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletJoint::_setBreakingImpulse ( lua_State* L ) {
	

	MOAI_LUA_SETUP ( MOAIBulletJoint, "U" )
	float unitsToMeters = self->GetUnitsToMeters ();

	if ( !self->mJoint ) {
		MOAILog ( state, MOAILogMessages::MOAIBox2DJoint_MissingInstance );
		return 0;
	}

		float length = state.GetValue < float >( 2, 0.0f );	
		btTypedConstraint*	joint = self->mJoint;
		joint->setBreakingImpulseThreshold(length);	

	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletJoint::_getBodyA ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletJoint, "U" )
	
	if ( !self->mJoint ) {
		MOAILog ( state, MOAILogMessages::MOAIBox2DJoint_MissingInstance );
		return 0;
	}		
	self->mBodyA->PushLuaUserdata ( state);	
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletJoint::_getBodyB ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletJoint, "U" )
	
	if ( !self->mJoint ) {
		MOAILog ( state, MOAILogMessages::MOAIBox2DJoint_MissingInstance );
		return 0;
	}
	self->mBodyB->PushLuaUserdata ( state);		
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletJoint::_destroy ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletJoint, "U" )	
	if ( self->mWorld ) {
		self->mWorld->ScheduleDestruction(*self);
	};
	return 0;
};

//================================================================//
// MOAIBox2DJoint
//================================================================//

void MOAIBulletJoint::Destroy () {
	if ( this->mJoint ) {		
		btDiscreteDynamicsWorld* mWorld = this->mWorld->mWorld;	
		mWorld->removeConstraint(this->mJoint);
		this->mJoint = 0;
	}
}
//----------------------------------------------------------------//
MOAIBulletJoint::MOAIBulletJoint () :
	mJoint ( 0 ) {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIBulletJoint::~MOAIBulletJoint () {

	if ( this->mJoint ) {	
		this->LuaRelease ( this->mBodyA );
		this->LuaRelease ( this->mBodyB );
	}
	
	this->Destroy ();
}

//----------------------------------------------------------------//
void MOAIBulletJoint::RegisterLuaClass ( MOAILuaState& state ) {
	MOAIBulletPrim::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAIBulletJoint::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAIBulletPrim::RegisterLuaFuncs ( state );

	luaL_Reg regTable [] = {
		{ "destroy",						_destroy },
		{ "getBodyA",						_getBodyA },
		{ "getBodyB",						_getBodyB },
		{ "getBreakingImpulse",				_getBreakingImpulse },
		{ "setBreakingImpulse",				_setBreakingImpulse },

		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIBulletJoint::SetJoint ( btTypedConstraint* joint ) {
	this->mJoint = joint;
	joint->setUserConstraintPtr ( this );
}
//----------------------------------------------------------------//
void MOAIBulletJoint::SetBodyA (  MOAIBulletBody* body ) {
	this->mBodyA = body;
}
//----------------------------------------------------------------//
void MOAIBulletJoint::SetBodyB (  MOAIBulletBody* body ) {
	this->mBodyB = body;
}