#ifndef MOAISHELL_H
#define MOAISHELL_H

#include <moai-core/MOAILua.h>

//================================================================//
// MOAIFoo
//================================================================//

class MOAIShell :
	public virtual MOAILuaObject {
private:

	//----------------------------------------------------------------//
	static int		_classHello			( lua_State* L );
	static int		_shellWeb		( lua_State* L );

public:

	DECL_LUA_FACTORY ( MOAIShell )

	//----------------------------------------------------------------//
					MOAIShell				();
					~MOAIShell			();
	void			RegisterLuaClass	( MOAILuaState& state );
	void			RegisterLuaFuncs	( MOAILuaState& state );
};

#endif
