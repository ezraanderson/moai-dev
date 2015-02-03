#ifndef	MOAIBULLETWORLD_H
#define	MOAIBULLETWORLD_H

#include <bullet/src/LinearMath/BtIdebugDraw.h>
#include <bullet/src/btBulletDynamicsCommon.h>

class MOAIBulletDebugDraw;

//class MOAIBulletBody;
//class MOAIBulletShape;

class MOAIBulletWorld : 
	public MOAIAction,	
	public virtual MOAILuaObject {		
private:

//DRAW
MOAIBulletDebugDraw* mDebugDraw;

/// Bullet collision configuration.
btCollisionConfiguration* collisionConfiguration_;
/// Bullet collision dispatcher.
btDispatcher* collisionDispatcher_;
/// Bullet collision broadphase.
btBroadphaseInterface* broadphase_;
/// Bullet constraint solver.
btConstraintSolver* solver_;

/// Bullet physics world.
btDiscreteDynamicsWorld* mWorld;


float mStep;
float mDrawScale;



//----------------------------------------------------------------//
static int		_setStep 				( lua_State* L );
static int		_setDrawScale 			( lua_State* L );
static int		_setGravity 			( lua_State* L );
static int		_useContinuous 			( lua_State* L );
static int		_splitImpulse 			( lua_State* L );
static int		_Iterations 			( lua_State* L );

static int		_addBody				( lua_State* L );
//static int		_addShape				( lua_State* L );

public:


	
	

	DECL_LUA_FACTORY ( MOAIBulletWorld )


    /// Return physics world.
	//WeakPtr<MOAIBulletWorld> world_;
    //btDiscreteDynamicsWorld* GetPhysicsWorld() const { return world_; }
	
	//----------------------------------------------------------------//
	MOAIBulletWorld				();
	~MOAIBulletWorld			();

	void			setBody	();
	void			OnUpdate				( float step );


	bool			IsDone					();
	void			DrawDebug				();
	void			RegisterLuaClass	( MOAILuaState& state );
	void			RegisterLuaFuncs	( MOAILuaState& state );
};


#endif
