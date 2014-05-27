// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-core/MOAILogMessages.h>
#include <moai-sim/MOAIGameButtonSensor.h>



//----------------------------------------------------------------//
/**  @name  setCallback
  @text  Sets or clears the callback to be issued when the level changes.

  @in    MOAIGameButtonSensor self
  @opt  function callback    Default value is nil.
  @out  nil
*/
int MOAIGameButtonSensor::_setCallback ( lua_State* L ) {
  MOAI_LUA_SETUP ( MOAIGameButtonSensor, "U" )
  
  self->mCallback.SetStrongRef ( state, 2 );
  
  return 0;
}

//================================================================//
// MOAIGameButtonSensor
//================================================================//

//----------------------------------------------------------------//
void MOAIGameButtonSensor::HandleEvent ( ZLStream& eventStream ) {

  this->mPlayer = eventStream.Read < int >( 0 );
  this->mDown   = eventStream.Read < bool >( 0 );
  this->mKey    = eventStream.Read < int >( 0 );        
       
      if ( this->mCallback ) {   

              MOAIScopedLuaState state = this->mCallback.GetSelf ();   
              lua_pushnumber ( state, this->mPlayer ); 
              lua_pushnumber ( state, this->mDown );
              lua_pushnumber ( state, this->mKey );                     
              state.DebugCall ( 3, 0 );
      }
}

//----------------------------------------------------------------//
MOAIGameButtonSensor::MOAIGameButtonSensor () :
  mPlayer ( 0 ),
  mDown ( false ),
  mKey ( 0 )
  {
  
  RTTI_SINGLE ( MOAISensor )
}

//----------------------------------------------------------------//
MOAIGameButtonSensor::~MOAIGameButtonSensor () {
}

//----------------------------------------------------------------//
void MOAIGameButtonSensor::RegisterLuaClass ( MOAILuaState& state ) {

  MOAISensor::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAIGameButtonSensor::RegisterLuaFuncs ( MOAILuaState& state ) {

  luaL_Reg regTable [] = {          
    { "setCallback",    _setCallback },
    { NULL, NULL }
  };

  luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIGameButtonSensor::WriteEvent ( ZLStream& eventStream,int idPlayer, bool isDown,int idKey ) {
  eventStream.Write < int >( idPlayer );
  eventStream.Write < bool >( isDown );
  eventStream.Write < int >( idKey );  
}
