// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-voxel/host.h>
#include <moai-voxel/headers.h>

//#include <steam_api.h>


//===============y=================================================//
// aku-bullet
//================================================================//

//----------------------------------------------------------------//
void MOAIVoxelAppFinalize () {
	//SteamAPI_Shutdown();
};

//----------------------------------------------------------------//
void MOAIVoxelAppInitialize () {	

	// Initialize Steam
	//bool bRet = SteamAPI_Init();	

	// Create the SteamAchievements object if Steam was successfully initialized
	//if (bRet)
	//{
	//	printf("------------------------------------------ \n");
	///	printf("MOAISteamApi :: STARTED :: SUCCESS \n");
	//	printf("------------------------------------------ \n");
	
	//} else {
	//	printf("------------------------------------------ \n");
	//	printf("MOAISteamApi :: STARTED :: FAILED \n");
	//	printf("------------------------------------------ \n");
	//}


};
//----------------------------------------------------------------//
void MOAIVoxelContextInitialize () {
	REGISTER_LUA_CLASS ( MOAIVoxelApi );
	REGISTER_LUA_CLASS(MOAIVoxelMesh);
};
//----------------------------------------------------------------//
