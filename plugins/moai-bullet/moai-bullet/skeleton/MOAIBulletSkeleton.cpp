// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <bullet/src/btBulletDynamicsCommon.h>
#include <moai-bullet/MOAIBulletCollisionHandler.h>



//----------------------------------------------------------------//
int MOAIBulletCollisionHandler::_addToWorld ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletCollisionHandler, "U" )

	return 0;
};


//----------------------------------------------------------------//
int MOAIBulletCollisionHandler::_destroy ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletCollisionHandler, "U" )	

	return 0;
};
//----------------------------------------------------------------//
void MOAIBulletCollisionHandler::Destroy () {
}
//----------------------------------------------------------------//
MOAIBulletCollisionHandler::MOAIBulletCollisionHandler (){
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END
}
//----------------------------------------------------------------//
MOAIBulletCollisionHandler::~MOAIBulletCollisionHandler () {

	
	this->Destroy ();
}
//----------------------------------------------------------------//
void MOAIBulletCollisionHandler::RegisterLuaClass ( MOAILuaState& state ) {

}

//----------------------------------------------------------------//
void MOAIBulletCollisionHandler::RegisterLuaFuncs ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{ "destroy",						_destroy },
		{ "addToWorld",						_addToWorld },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//--------------------------------------------------------//
void MOAIBulletCollisionHandler::SetWorld (btDiscreteDynamicsWorld* world) {
	this->mWorld = world;
};