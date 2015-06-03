#ifndef MOAIMATHNEON_H
#define MOAIMATHNEON_H

#include <moai-core/MOAILua.h>


	
class MOAIMathNeon :
	public virtual MOAILuaObject {
private:

	//----------------------------------------------------------------//
	static int		_classHello			( lua_State* L );
	static int		_getDirNeon		( lua_State* L );
	static int		_getDir			( lua_State* L );
public:

	DECL_LUA_FACTORY ( MOAIMathNeon )

	//----------------------------------------------------------------//
					MOAIMathNeon				();
					~MOAIMathNeon			();


	void			RegisterLuaClass	( MOAILuaState& state );
	void			RegisterLuaFuncs	( MOAILuaState& state );
};

#endif
