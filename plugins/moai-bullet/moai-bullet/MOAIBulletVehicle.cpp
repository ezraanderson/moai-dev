// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <bullet/src/btBulletDynamicsCommon.h>
#include <moai-bullet/MOAIBulletBody.h>
#include <moai-bullet/MOAIBulletVehicle.h>
#include <moai-bullet/MOAIBulletWorld.h>
#include <moai-bullet/MOAIBulletWheel.h>


//----------------------------------------------------------------//
int MOAIBulletVehicle::_destroy ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletVehicle, "U" )
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletVehicle::_newWheel ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletVehicle, "U" )
	MOAIBulletWheel* wheel = new MOAIBulletWheel ();
	wheel->setVehicle(self->mRaycastVehicle);	
	self->LuaRetain ( wheel );
	wheel->PushLuaUserdata ( state );
	return 1;
};
//----------------------------------------------------------------//
int MOAIBulletVehicle::_applyGas ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletVehicle, "UN" )
	float gas		= state.GetValue < float >( 2, 0 );
	int wheel		= state.GetValue < int >( 3, 0 );	
	self->mRaycastVehicle->applyEngineForce(gas,wheel-1);
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletVehicle::_applyBrake ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletVehicle, "UN" )
	float brake		= state.GetValue < float >( 2, 0 );
	int wheel		= state.GetValue < int >( 3, 0 );
	self->mRaycastVehicle->setBrake(brake,wheel-1);
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletVehicle::_applySteering( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletVehicle, "UN" )
	float steer		= state.GetValue < float >( 2, 0 );
	int wheel		= state.GetValue < int >( 3, 0 );
	self->mRaycastVehicle->setSteeringValue(steer,wheel-1);
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletVehicle::_setCoordinateSystem ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletVehicle, "UNNN" )	
		int rightIndex		= state.GetValue < int >( 2, 0 );
		int upIndex			= state.GetValue < int >( 3, 0 );
		int forwardIndex	= state.GetValue < int >( 4, 0 );		

		btRaycastVehicle* vehicle = ( btRaycastVehicle* )self->mRaycastVehicle;
		vehicle->setCoordinateSystem(rightIndex,upIndex,forwardIndex);

	return 0;
};
//----------------------------------------------------------------//
//SHOLD ME INDIVUAL
int MOAIBulletVehicle::_setTune ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletVehicle, "UNNN" )	
	//self->mTuning.m_frictionSlip				= state.GetValue < btScalar >( 2, 0.0f );
	//self->mTuning.m_maxSuspensionForce			= state.GetValue < btScalar >( 3, 0.0f );
	//self->mTuning.m_maxSuspensionTravelCm		= state.GetValue < btScalar >( 4, 0.0f );
	//self->mTuning.m_suspensionCompression		= state.GetValue < btScalar >( 5, 0.0f );
	//self->mTuning.m_suspensionDamping			= state.GetValue < btScalar >( 6, 0.0f );
	//self->mTuning.m_suspensionStiffness			= state.GetValue < btScalar >( 7, 0.0f );
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletVehicle::_setToWorld ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletVehicle, "U" )	
	btRaycastVehicle::btVehicleTuning mTuning;	
	self->mRaycastVehicle	= new btRaycastVehicle(mTuning,self->mBody,self->mVehicleRayCaster);
	self->mWorld->addVehicle(self->mRaycastVehicle);	
	return 0;
};
//----------------------------------------------------------------//
void MOAIBulletVehicle::Destroy () {
	//if ( this->mCaster ) {	
	//};
};
//----------------------------------------------------------------//
MOAIBulletVehicle::MOAIBulletVehicle () :
	mVehicleRayCaster ( 0 ), //RAYCAST
	mBody		 ( 0 ),	
	mCompound	 ( 0 )
	{	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END
}
//----------------------------------------------------------------//
MOAIBulletVehicle::~MOAIBulletVehicle () {
	this->Destroy ();
}
//----------------------------------------------------------------//
void MOAIBulletVehicle::RegisterLuaClass ( MOAILuaState& state ) {
	MOAIBulletPrim::RegisterLuaClass ( state );
}
//----------------------------------------------------------------//
void MOAIBulletVehicle::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAIBulletPrim::RegisterLuaFuncs ( state );

	luaL_Reg regTable [] = {
		{ "destroy",						_destroy },
		{ "newWheel",						_newWheel },
		{ "setCoordinateSystem",			_setCoordinateSystem },
		{ "setTune",						_setTune },
		{ "setToWorld",						_setToWorld },

		{ "applyBrake",						_applyBrake },
		{ "applyGas",						_applyGas },
		{ "applySteering",					_applySteering },

		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//***************************************************************************
//***************************************************************************
//SET POINTERS
//----------------------------------------------------------------//
void MOAIBulletVehicle::setCompound (btCompoundShape*	mCompound) {
	this->mCompound = mCompound;
};
//----------------------------------------------------------------//
//REMBERING THE BODY??
void MOAIBulletVehicle::setBody (btRigidBody*		mBody) {
	this->mBody = mBody;
};
//----------------------------------------------------------------//
void MOAIBulletVehicle::setCaster (btVehicleRaycaster*	mCaster) {
	this->mVehicleRayCaster = mCaster;
};
//----------------------------------------------------------------//
void MOAIBulletVehicle::setWorld (btDiscreteDynamicsWorld* world) {
	this->mWorld = world;
};




