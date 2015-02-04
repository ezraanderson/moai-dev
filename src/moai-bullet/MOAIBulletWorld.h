#ifndef	MOAIBULLETWORLD_H
#define	MOAIBULLETWORLD_H

#include <bullet/src/LinearMath/BtIdebugDraw.h>
#include <bullet/src/btBulletDynamicsCommon.h>

class MOAIBulletDebugDraw;

class MOAIBulletBody;
class MOAIBulletShape;
class MOAIBulletJoint;

//================================================================//
// MOAIBox2DPrim
//================================================================//
class MOAIBulletPrim :
	public virtual MOAILuaObject  {
protected:

	MOAIBulletWorld* mWorld;
	
	bool			mDestroy;
	MOAIBulletPrim*	mDestroyNext;	
public:
	friend class MOAIBulletWorld;

	GET_SET ( MOAIBulletWorld*, World, mWorld )

	//----------------------------------------------------------------//
	virtual void	Destroy					() = 0;
	float			GetUnitsToMeters		();
					MOAIBulletPrim			();
	
	//----------------------------------------------------------------//
	inline bool IsDestroyed () {
		return this->mDestroy;
	}
};





class MOAIBulletWorld : 
	public MOAIAction,	
	public virtual MOAILuaObject {		
private:

//DRAW
MOAIBulletDebugDraw* mDebugDraw;

/// Bullet collision configuration.
btCollisionConfiguration* mCollisionConfiguration;
/// Bullet collision dispatcher.
btDispatcher* mCollisionDispatcher;
/// Bullet collision broadphase.
btBroadphaseInterface* mBroadphase;
/// Bullet constraint solver.
btConstraintSolver* mSolver;

/// Bullet physics world.
btDiscreteDynamicsWorld* mWorld;

MOAIBulletPrim*		mDestroyBodies;
MOAIBulletPrim*		mDestroyShapes;
MOAIBulletPrim*		mDestroyJoints;

float mStep;
float mDrawScale;
float mDrawJointSize;
bool mLock;


//----------------------------------------------------------------//
static int		_setStep 				( lua_State* L );
static int		_setDrawScale 			( lua_State* L );
static int		_setDrawJointSize		( lua_State* L );

static int		_setGravity 			( lua_State* L );
static int		_useContinuous 			( lua_State* L );
static int		_splitImpulse 			( lua_State* L );
static int		_Iterations 			( lua_State* L );

static int		_addBody				( lua_State* L );


static int		_addJointHinge			( lua_State* L );
static int		_addJointCone			( lua_State* L );
static int		_addJointFixed			( lua_State* L );
static int		_addJointFreedom		( lua_State* L );
static int		_addJointPoint			( lua_State* L );
static int		_addJointSlider			( lua_State* L );


void			Destroy					();
void			SayGoodbye				(btCompoundShape* shape ); 
void			SayGoodbye				(btTypedConstraint* joint );

void			ScheduleDestruction		( MOAIBulletBody& body );
void			ScheduleDestruction		( MOAIBulletShape& shape );
void			ScheduleDestruction		( MOAIBulletJoint& joint );


public:
	
	friend class MOAIBulletBody; 
	friend class MOAIBulletShapes;
	friend class MOAIBulletJoint;

	DECL_LUA_FACTORY ( MOAIBulletWorld )

	
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
