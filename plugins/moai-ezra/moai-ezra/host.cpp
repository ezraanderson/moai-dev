// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-ezra/host.h>
#include <moai-ezra/headers.h>





//================================================================//
// aku-ezra
//================================================================//

//----------------------------------------------------------------//
void MOAIEzraAppFinalize () {
	//PARTICLE_SOUP
	// MOAIEzraParticleLayer::Finalize();
};

//----------------------------------------------------------------//
void MOAIEzraAppInitialize () {
};
//----------------------------------------------------------------//
void MOAIEzraContextInitialize () {


	printf("---------------------------------------\n");
	printf(">>>>>>>>>>>>>>>>>>> EZRA MODULES \n");
	printf("---------------------------------------\n");

	REGISTER_LUA_CLASS ( MOAIEzraVertexBuffer );
	REGISTER_LUA_CLASS ( MOAIEzraMesh );
	REGISTER_LUA_CLASS ( MOAIEzraIndexBuffer );
	REGISTER_LUA_CLASS ( MOAIEzraParticleLayer );

	REGISTER_LUA_CLASS ( MOAIShell );
	REGISTER_LUA_CLASS ( MOAIVoxel );
	REGISTER_LUA_CLASS ( EZDraw );

	REGISTER_LUA_CLASS ( BOXVehicle );

};
//----------------------------------------------------------------//
