// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-chipmunk7/host.h>
#include <moai-chipmunk7/headers.h>

//================================================================//
// aku-util
//================================================================//

//----------------------------------------------------------------//
void MOAIChipmunk7AppFinalize () {
}

//----------------------------------------------------------------//
void MOAIChipmunk7AppInitialize () {

	//cpInitChipmunk ();
}

//----------------------------------------------------------------//
void MOAIChipmunk7ContextInitialize () {

	REGISTER_LUA_CLASS ( MOAICp )
	REGISTER_LUA_CLASS ( MOAICpArbiter )
	REGISTER_LUA_CLASS ( MOAICpBody )
	REGISTER_LUA_CLASS ( MOAICpConstraint )
	REGISTER_LUA_CLASS ( MOAICpShape )
	REGISTER_LUA_CLASS ( MOAICpSpace )
}
