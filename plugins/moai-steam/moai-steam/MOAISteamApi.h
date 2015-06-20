#ifndef MOAISTEAMAPI_H
#define MOAISTEAMAPI_H

#include <moai-core/MOAILua.h>


class MOAISteamApi :
	public virtual MOAILuaObject {
private:	

	bool mEnabled;

	static int		_start			( lua_State* L );


public:

	DECL_LUA_FACTORY ( MOAISteamApi )

	//----------------------------------------------------------------//
					MOAISteamApi			();
					~MOAISteamApi			();

	void			RegisterLuaClass	( MOAILuaState& state );
	void			RegisterLuaFuncs	( MOAILuaState& state );
};




#endif



