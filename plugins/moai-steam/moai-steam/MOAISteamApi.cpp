//ADD UNIT DEGREE MOD

#include "pch.h"
#include <moai-steam/MOAISteamApi.h>


//#include <F:/steam_sdk/steamworks_sdk_133b/sdk/public/steam/isteamclient.h>
//#include <F:/steam_sdk/steamworks_sdk_133b/sdk/public/steam/isteamapps.h>
//#include <F:/steam_sdk/steamworks_sdk_133b/sdk/public/steam/steam_api.h>

#include <steam_api.h>



int MOAISteamApi::_start ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAISteamApi, "U" )




return 0;


};



//----------------------------------------------------------------//
MOAISteamApi::MOAISteamApi () :
mEnabled ( false )

{

	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END

}

//----------------------------------------------------------------//
MOAISteamApi::~MOAISteamApi () {

}

//----------------------------------------------------------------//
void MOAISteamApi::RegisterLuaClass ( MOAILuaState& state ) {
}

//----------------------------------------------------------------//
void MOAISteamApi::RegisterLuaFuncs ( MOAILuaState& state ) {

	// here are the instance methods:
	luaL_Reg regTable [] = {

		{ "start",			_start },
	
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

