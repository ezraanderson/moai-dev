#ifndef BOXVEHICLE_H
#define BOXVEHICLE_H

#include <moai-core/MOAILua.h>

#include <moai-box2d/MOAIBox2DWorld.h>
#include <moai-box2d/MOAIBox2DBody.h>
//================================================================//
// BOXVehicle
//================================================================//

class BOXVehicle :
	public virtual MOAILuaObject {
private:


	b2Body*			mBody;

	//----------------------------------------------------------------//
	static int		_updateDriveF			( lua_State* L );
	static int		_updateDriveB			( lua_State* L );
	static int		_updateFriction			( lua_State* L );
	static int		_setBody				( lua_State* L );

public:

	DECL_LUA_FACTORY ( BOXVehicle )

	//----------------------------------------------------------------//
					BOXVehicle				();
					~BOXVehicle			();
	void			RegisterLuaClass	( MOAILuaState& state );
	void			RegisterLuaFuncs	( MOAILuaState& state );
};

#endif
