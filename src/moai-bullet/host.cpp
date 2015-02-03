// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-bullet/host.h>
#include <moai-bullet/headers.h>

//================================================================//
// aku-bullet
//================================================================//

//----------------------------------------------------------------//
void AKUBulletAppFinalize () {
};

//----------------------------------------------------------------//
void AKUBulletAppInitialize () {	

};
//----------------------------------------------------------------//
void AKUBulletContextInitialize () {
	REGISTER_LUA_CLASS ( MOAIBulletWorld )
	REGISTER_LUA_CLASS ( MOAIBulletShape )
};
//----------------------------------------------------------------//
