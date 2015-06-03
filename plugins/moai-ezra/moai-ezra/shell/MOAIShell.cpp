#include "pch.h"
#include <moai-ezra/shell/MOAIShell.h>

//CLASS
int MOAIShell::_classHello ( lua_State* L ) {
	UNUSED ( L );



	return 0;
}

//----------------------------------------------------------------//
//INSTANCE
int MOAIShell::_shellWeb ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIShell, "US" ) 
	cc8* website = state.GetValue < cc8* >( 1, "" );
	ShellExecute(0, "open", website, 0, 0, SW_SHOWNORMAL);

	return 0;
}



//----------------------------------------------------------------//
MOAIShell::MOAIShell () {

	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
		// and any other objects from multiple inheritance...
	
		RTTI_END
}

//----------------------------------------------------------------//
MOAIShell::~MOAIShell () {
}

//----------------------------------------------------------------//
void MOAIShell::RegisterLuaClass ( MOAILuaState& state ) {


	// here are the class methods:
	luaL_Reg regTable [] = {
		{ "classHello",		_classHello },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIShell::RegisterLuaFuncs ( MOAILuaState& state ) {



	// here are the instance methods:
	luaL_Reg regTable [] = {
		{ "shellWeb",	_shellWeb },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

