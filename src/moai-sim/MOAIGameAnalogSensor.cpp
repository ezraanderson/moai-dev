// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-core/MOAILogMessages.h>
#include <moai-sim/MOAIGameAnalogSensor.h>



//----------------------------------------------------------------//
/**  @name  setCallback
  @text  Sets or clears the callback to be issued when the level changes.

  @in    MOAIGameButtonSensor self
  @opt  function callback    Default value is nil.
  @out  nil
*/
int MOAIGameAnalogSensor::_setCallback ( lua_State* L ) {
  MOAI_LUA_SETUP ( MOAIGameAnalogSensor, "U" )
  
  self->mCallback.SetStrongRef ( state, 2 );
  
  return 0;
}

//================================================================//
// MOAIGameButtonSensor
//================================================================//

//----------------------------------------------------------------//
void MOAIGameAnalogSensor::HandleEvent ( ZLStream& eventStream ) {

this->mPlayer		= eventStream.Read < int >( 0 );  
this->mLeftAxisX	= eventStream.Read < float >( 0.0f );
this->mLeftAxisY    = eventStream.Read < float >( 0.0f );  
this->mRightAxisX	= eventStream.Read < float >( 0.0f );
this->mRightAxisY	= eventStream.Read < float >( 0.0f );      
       
      if ( this->mCallback ) {              
              MOAIScopedLuaState state = this->mCallback.GetSelf ();  
			  lua_pushnumber ( state, this->mPlayer );
              lua_pushnumber ( state, this->mLeftAxisX );
              lua_pushnumber ( state, this->mLeftAxisY );              
              lua_pushnumber ( state, this->mRightAxisX );    
              lua_pushnumber ( state, this->mRightAxisY );              
              state.DebugCall ( 5, 0 );
      }
}

//----------------------------------------------------------------//
MOAIGameAnalogSensor::MOAIGameAnalogSensor () :
  mPlayer     ( 0 ),   
  mLeftAxisX ( 0.0f ),
  mLeftAxisY ( 0.0f ),  
  mRightAxisX ( 0.0f ),
  mRightAxisY ( 0.0f )    
  {  
  RTTI_SINGLE ( MOAISensor )
}

//----------------------------------------------------------------//
MOAIGameAnalogSensor::~MOAIGameAnalogSensor () {
}

//----------------------------------------------------------------//
void MOAIGameAnalogSensor::RegisterLuaClass ( MOAILuaState& state ) {

  MOAISensor::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAIGameAnalogSensor::RegisterLuaFuncs ( MOAILuaState& state ) {

  luaL_Reg regTable [] = {          
    { "setCallback",    _setCallback },
    { NULL, NULL }
  };

  luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIGameAnalogSensor::WriteEvent ( ZLStream& eventStream,int idPlayer,  float leftAxisX, float leftAxisY,float rightAxisX, float rightAxisY) {
  eventStream.Write < int >( idPlayer );   
  eventStream.Write < float >( leftAxisX );
  eventStream.Write < float >( leftAxisY );  
  eventStream.Write < float >( rightAxisX );
  eventStream.Write < float >( rightAxisY ); 
  
}
