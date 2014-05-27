// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAIGAMEBUTTONSENSOR_H
#define MOAIGAMEBUTTONSENSOR_H

//#include <moaicore/MOAILua.h>
#include <moai-sim/MOAISensor.h>

class MOAIGameButtonSensor :
	public MOAISensor {  

private:                  
  bool mDown;
  int  mKey;
  int  mPlayer;                        

MOAILuaStrongRef mCallback;

static int	_setCallback	( lua_State* L );

public:

	DECL_LUA_FACTORY ( MOAIGameButtonSensor )

	//----------------------------------------------------------------//
	void			HandleEvent				( ZLStream& eventStream );
					MOAIGameButtonSensor	();
					~MOAIGameButtonSensor	();
	void			RegisterLuaClass		( MOAILuaState& state );
	void			RegisterLuaFuncs		( MOAILuaState& state );
	static void		WriteEvent				( ZLStream& eventStream,int idPlayer, bool iSDown,int idKey);
};

#endif