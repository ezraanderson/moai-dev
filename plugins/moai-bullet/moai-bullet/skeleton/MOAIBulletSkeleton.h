// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIBULLETCOLLISIONHANDLER_H
#define	MOAIBULLETCOLLISIONHANDLER_H

#include <moai-bullet/MOAIBulletWorld.h>



//================================================================//
// MOAIBulletCollisionHandler
//================================================================//
/**	@name MOAIBulletCollisionHandler
	@text Collision Handler.
*/
class MOAIBulletCollisionHandler :
	public MOAIBulletPrim {
protected:	

	btDiscreteDynamicsWorld* mWorld; 

	//----------------------------------------------------------------//
	static int			_destroy							( lua_State* L );
	static int			_addToWorld							( lua_State* L );

	//----------------------------------------------------------------//
	void				SetWorld				(btDiscreteDynamicsWorld* world); 

public:	


	//----------------------------------------------------------------//
	void				Destroy					();
						MOAIBulletCollisionHandler			();
						~MOAIBulletCollisionHandler		();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
