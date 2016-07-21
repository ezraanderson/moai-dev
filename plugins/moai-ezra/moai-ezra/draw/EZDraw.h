#ifndef EZDRAW_H
#define EZDRAW_H

#include <moai-core/MOAILua.h>


class EZDraw :
	public virtual MOAILuaObject {
private:

	float mWidth;
	float mHeight;

	//----------------------------------------------------------------//
	static int		_drawBlack			( lua_State* L );
	static int		_drawRoomsB			( lua_State* L );
	static int		_drawRoomsC			( lua_State* L );
	static int		_drawBorders		( lua_State* L );	
	static int		_setBounds			( lua_State* L );
	

public:

	DECL_LUA_FACTORY ( EZDraw )

	//----------------------------------------------------------------//
					EZDraw				();
					~EZDraw			();

		void			RegisterLuaClass	( MOAILuaState& state );
		void			RegisterLuaFuncs	( MOAILuaState& state );
};

#endif
