// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <bullet/src/btBulletDynamicsCommon.h>
#include <moai-bullet/MOAIBulletBody.h>
#include <moai-bullet/MOAIBulletJoint.h>
#include <moai-bullet/MOAIBulletWorld.h>

//----------------------------------------------------------------//
int MOAIBulletJoint::_setDebugDrawSize ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletJoint, "UN" )
	if ( !self->mJoint ) {	
		return 0;
	}
	float debugDrawSize = state.GetValue < float >( 2, 0.0f );	
	btTypedConstraint*	btJoint = self->mJoint;
	btJoint->setDbgDrawSize(debugDrawSize);	
	return 1;
}

//----------------------------------------------------------------//
int MOAIBulletJoint::_getBreakingImpulse ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletJoint, "U" )
	if ( !self->mJoint ) {	
		return 0;
	}
	float length = state.GetValue < float >( 2, 0.0f );	
	btTypedConstraint*	btJoint = self->mJoint;

	state.Push ( btJoint->getBreakingImpulseThreshold() );
	
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletJoint::_addToWorld ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletJoint, "U" )
	if ( !self->mJoint ) {
		return 0;
	}
	bool disableCollisionBetweenLinkedBodies = state.GetValue < bool >( 2, 0.0f );
	btTypedConstraint*	btJoint = self->mJoint;
	self->mWorld->addConstraint(btJoint, disableCollisionBetweenLinkedBodies);
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletJoint::_setBreakingImpulse ( lua_State* L ) {

	MOAI_LUA_SETUP ( MOAIBulletJoint, "U" )
	if ( !self->mJoint ) {
		return 0;
	}
		float length = state.GetValue < float >( 2, 0.0f );	
		btTypedConstraint*	btJoint = self->mJoint;
		btJoint->setBreakingImpulseThreshold(length);	

	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletJoint::_isEnabled ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletJoint, "U" )
	if ( !self->mJoint ) {
		return 0;
	}

	btTypedConstraint*	btJoint = self->mJoint;
	state.Push ( btJoint->isEnabled() );
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletJoint::_setEnabled ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletJoint, "U" )
	if ( !self->mJoint ) {
		return 0;
	}

	bool enabled = state.GetValue < bool >( 2, 0.0f );	
	btTypedConstraint*	btJoint = self->mJoint;
	btJoint->setEnabled(enabled);
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletJoint::_getBodyA ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletJoint, "U" )	
	if ( !self->mJoint ) {
		return 0;
	}		
	self->mBodyA->PushLuaUserdata ( state);	
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletJoint::_getBodyB ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletJoint, "U" )	
	if ( !self->mJoint ) {
		return 0;
	}
	self->mBodyB->PushLuaUserdata ( state);		
	return 1;
}


//----------------------------------------------------------------//
int MOAIBulletJoint::_destroy ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletJoint, "U" )	
	if ( self->mWorld ) {
		//self->mWorld->ScheduleDestruction(*self);
	};
	return 0;
};
//----------------------------------------------------------------//
void MOAIBulletJoint::Destroy () {
	if ( this->mJoint ) {		
		//btDiscreteDynamicsWorld* mWorld = this->mWorld->mWorld;	
		////mWorld->removeConstraint(this->mJoint);
		//this->mJoint = 0;
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

		//WTF ? 

			//MOAIBulletBody* bodyA = ( MOAIBulletBody* )this->mJoint->getRigidBodyA ();
			//MOAIBulletBody* bodyB = ( MOAIBulletBody* )this->mJoint->getRigidBodyB ();

			//MOAIBox2DBody* bodyA = ( MOAIBox2DBody* )this->mJoint->GetBodyA ();
			//MOAIBox2DBody* bodyB = ( MOAIBox2DBody* )this->mJoint->GetBodyB ();

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
		{ "addToWorld",						_addToWorld },
		{ "getBodyA",						_getBodyA },
		{ "getBodyB",						_getBodyB },
		{ "getBreakingImpulse",				_getBreakingImpulse },
		{ "setBreakingImpulse",				_setBreakingImpulse },
		{ "isEnabled",						_isEnabled },
		{ "setEnabled",						_setEnabled },
		{ "setDebugDrawSize",				_setDebugDrawSize },

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
//----------------------------------------------------------------//
void MOAIBulletJoint::SetWorld (btDiscreteDynamicsWorld* world) {
	this->mWorld = world;
};