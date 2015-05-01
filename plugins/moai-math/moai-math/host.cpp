// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-math/host.h>
#include <moai-math/headers.h>





//================================================================//
// aku-ezra
//================================================================//

//----------------------------------------------------------------//
void MOAIMathAppFinalize () {
	//PARTICLE_SOUP
	// MOAIEzraParticleLayer::Finalize();
};

//----------------------------------------------------------------//
void MOAIMathAppInitialize () {
};
//----------------------------------------------------------------//
void MOAIMathContextInitialize () {


	printf("---------------------------------------\n");
	printf(">>>>>>>>>>>>>>>>>>>  MATH NEON \n");
	printf("---------------------------------------\n");

	REGISTER_LUA_CLASS ( MOAIMathNeon );

};
//----------------------------------------------------------------//
