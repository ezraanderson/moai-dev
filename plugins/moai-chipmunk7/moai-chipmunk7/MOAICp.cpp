// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-chipmunk7/MOAICp.h>
#include <moai-chipmunk7/MOAICpSpace.h>



//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@name getBiasCoefficient
	@text Returns the current bias coefficient.

	@out	number	bias	The bias coefficient.
*/
int MOAICp::_getBiasCoefficient ( lua_State* L ) {
	
	MOAILuaState state ( L );
	if ( !state.CheckParams ( 1, "UU" )) return 0;
	MOAICpSpace* space = state.GetLuaObject < MOAICpSpace >( 1, true );
	cpFloat  value = cpSpaceGetCollisionBias(space->mSpace);


	lua_pushnumber ( L, value );
	return 1;
}

//----------------------------------------------------------------//
/**	@name	getCollisionSlop
	@text	Returns the current collision slop.
	@out	number slop	
*/
int MOAICp::_getCollisionSlop ( lua_State* L ) {

	MOAILuaState state ( L );
	if ( !state.CheckParams ( 1, "UU" )) return 0;
	MOAICpSpace* space = state.GetLuaObject < MOAICpSpace >( 1, true );
	cpFloat  value = cpSpaceGetCollisionSlop(space->mSpace);

	lua_pushnumber ( L, value );
	return 1;
}

//----------------------------------------------------------------//
/**	@name	getContactPersistence
	@text	Returns the current contact persistence.
	@out	number persistence	
*/
int MOAICp::_getContactPersistence ( lua_State* L ) {

	MOAILuaState state ( L );
	if ( !state.CheckParams ( 1, "UU" )) return 0;
	MOAICpSpace* space = state.GetLuaObject < MOAICpSpace >( 1, true );
	cpFloat  value = cpSpaceGetCollisionPersistence(space->mSpace);

	lua_pushnumber ( L, value );
	return 1;

}

//----------------------------------------------------------------//
/**	@name	setBiasCoefficient
	@text	Sets the bias coefficient.
	@in		number bias
	@out	nil
*/
int MOAICp::_setBiasCoefficient ( lua_State* L ) {

	MOAILuaState state ( L );
	if ( !state.CheckParams ( 1, "UUN" )) return 0;

	MOAICpSpace* space = state.GetLuaObject < MOAICpSpace >( 1, true );
	cpFloat  value_old = cpSpaceGetCollisionBias(space->mSpace);
	cpFloat  value_new =  state.GetValue < cpFloat >( 2, value_old );	
	cpSpaceSetCollisionBias(space->mSpace,value_new);
	
	//cp_bias_coef =	state.GetValue < cpFloat >( 1, cp_bias_coef );


	return 0;
}

//----------------------------------------------------------------//
/**	@name	setCollisionSlop
	@text	Sets the collision slop.
	@in		number slop
	@out	nil
*/
int MOAICp::_setCollisionSlop ( lua_State* L ) {

	
	MOAILuaState state ( L );
	if ( !state.CheckParams ( 1, "UUN" )) return 0;

	MOAICpSpace* space = state.GetLuaObject < MOAICpSpace >( 1, true );
	cpFloat  value_old = cpSpaceGetCollisionSlop(space->mSpace);
	cpFloat  value_new =  state.GetValue < cpFloat >( 2, value_old );	
	cpSpaceSetCollisionSlop(space->mSpace,value_new);

	//cp_collision_slop =	state.GetValue < cpFloat >( 1, cp_collision_slop );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setContactPersistence
	@text	Sets the contact persistance.
	@in		number persistance
	@out	nil
*/
int MOAICp::_setContactPersistence ( lua_State* L ) {

	MOAILuaState state ( L );
	if ( !state.CheckParams ( 1, "UUN" )) return 0;

	MOAICpSpace* space = state.GetLuaObject < MOAICpSpace >( 1, true );
	cpFloat  value_old = cpSpaceGetCollisionPersistence(space->mSpace);
	cpFloat  value_new =  state.GetValue < cpFloat >( 2, value_old );	
	cpSpaceSetCollisionPersistence(space->mSpace,value_new);
	
	//cp_contact_persistence =	state.GetValue < cpTimestamp >( 1, cp_contact_persistence );
	return 0;
}

//================================================================//
// MOAICp
//================================================================//

//----------------------------------------------------------------//
MOAICp::MOAICp () {

	RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
MOAICp::~MOAICp () {
}

//----------------------------------------------------------------//
void MOAICp::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "INFINITY",	INFINITY );

	luaL_Reg regTable[] = {
		{ "getBiasCoefficient",		_getBiasCoefficient },
		{ "getCollisionSlop",		_getCollisionSlop },
		{ "getContactPersistence",	_getContactPersistence },
		{ "setBiasCoefficient",		_setBiasCoefficient },
		{ "setCollisionSlop",		_setCollisionSlop },
		{ "setContactPersistence",	_setContactPersistence },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}
