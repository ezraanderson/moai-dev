
#ifndef	MOAIBULLETTEST_H
#define	MOAIBULLETTEST_H

#include <moai-bullet/MOAIBulletWorld.h>


class MOAIBulletTest :
		public virtual MOAILuaObject {
protected:
	btDiscreteDynamicsWorld* mWorld; 

public:	
	//----------------------------------------------------------------//
	static int		_testJoint			( lua_State* L );
	static int		_testRagDoll		( lua_State* L );
	static int		_testCar			( lua_State* L );
	static int		_testCarUpdate		( lua_State* L );

	DECL_LUA_FACTORY ( MOAIBulletTest )

	//----------------------------------------------------------------//
	void				Destroy					();
						MOAIBulletTest			();
						~MOAIBulletTest		();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );

	void				SetWorld				(btDiscreteDynamicsWorld* world); 
	btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape);
};

#endif
