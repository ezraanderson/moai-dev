#ifndef MOAIPOLYGON_H
#define MOAIPOLYGON_H

#include <moai-core/MOAILua.h>

//********************************************************************





class MOAIPolygon :
	public virtual MOAILuaObject {
private:


	static int		_AABB			( lua_State* L );




public:


	DECL_LUA_FACTORY ( MOAIPolygon )

	//----------------------------------------------------------------//
					MOAIPolygon			();
					~MOAIPolygon			();

	//void			clipLight			();
	void			RegisterLuaClass	( MOAILuaState& state );
	void			RegisterLuaFuncs	( MOAILuaState& state );





};




#endif