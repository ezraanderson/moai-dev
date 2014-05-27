// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAIGAMEANALOGSENSOR_H
#define MOAIGAMEANALOGSENSOR_H


//#include <moaicore/MOAILua.h>
#include <moai-sim/MOAISensor.h>




class MOAIGameAnalogSensor :
	public MOAISensor {  
private:  
        
  int   mPlayer;
  float mLeftAxisX;
  float mLeftAxisY;
  float mRightAxisX;
  float mRightAxisY;                          

	MOAILuaStrongRef mCallback;

	//----------------------------------------------------------------//
	static int	_setCallback	( lua_State* L );

public:

	DECL_LUA_FACTORY ( MOAIGameAnalogSensor )

	//----------------------------------------------------------------//
	void			HandleEvent				( ZLStream& eventStream );
					MOAIGameAnalogSensor	();
					~MOAIGameAnalogSensor	();
	void			RegisterLuaClass		( MOAILuaState& state );
	void			RegisterLuaFuncs		( MOAILuaState& state );
	static void		WriteEvent				( ZLStream& eventStream,int idPlayer, float leftAxisX,float leftAxisY,float rightAxisX, float rightAxisY);
};

#endif
