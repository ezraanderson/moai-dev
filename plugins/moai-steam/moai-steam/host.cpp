// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-steam/host.h>
#include <moai-steam/headers.h>

#include <steam_api.h>


//================================================================//
// aku-bullet
//================================================================//

//----------------------------------------------------------------//
void MOAISteamAppFinalize () {
	SteamAPI_Shutdown();
};

//----------------------------------------------------------------//
void MOAISteamAppInitialize () {	

	// Initialize Steam
	bool bRet = SteamAPI_Init();	

	// Create the SteamAchievements object if Steam was successfully initialized
	if (bRet)
	{
		printf("------------------------------------------ \n");
		printf("MOAISteamApi :: STARTED :: SUCCESS \n");
		printf("------------------------------------------ \n");
	
	} else {
		printf("------------------------------------------ \n");
		printf("MOAISteamApi :: STARTED :: FAILED \n");
		printf("------------------------------------------ \n");
	}


};
//----------------------------------------------------------------//
void MOAISteamContextInitialize () {
	REGISTER_LUA_CLASS ( MOAISteamApi );

};
//----------------------------------------------------------------//
