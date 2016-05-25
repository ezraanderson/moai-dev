// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-mathUtil/host.h>
#include <moai-mathUtil/headers.h>

//================================================================//
// aku-ezra
//================================================================//

//----------------------------------------------------------------//
void MOAIMathUtilAppFinalize () {
	//PARTICLE_SOUP
	// MOAIEzraParticleLayer::Finalize();
};

//----------------------------------------------------------------//
void MOAIMathUtilAppInitialize () {
};
//----------------------------------------------------------------//
void MOAIMathUtilContextInitialize () {


	printf("---------------------------------------\n");
	printf(">>>>>>>>>>>>>>>>>>>  MATH UTIL \n");
	printf("---------------------------------------\n");

	//REGISTER_LUA_CLASS ( MOAIMathNeon );
	REGISTER_LUA_CLASS ( MOAIMathUtil );
	REGISTER_LUA_CLASS ( MOAILight );
	REGISTER_LUA_CLASS ( MOAIPolygon );
};
//----------------------------------------------------------------//
