// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIBULLETBODY_H
#define	MOAIBULLETBODY_H

#include <moai-bullet/MOAIBulletWorld.h>
#include <bullet/src/LinearMath/btMotionState.h>
#include <bullet/src/btBulletDynamicsCommon.h>


class btRigidBody;

class MOAIBulletBody :
	//public MOAITransformBase	
	public MOAIBulletPrim,
	public virtual MOAILuaObject 
{
private:	

	//btScalar mMass;
	//btVector3 mInertia;

//WORLD
	btDiscreteDynamicsWorld* mWorld; //<--REALLY FUCKING DUMB
//BODY
	btRigidBody*			mBody;

//MOTION
	btDefaultMotionState*	mMotion;

//SHAPE : SHOULD HAVE OWN SHAPES MAYBE?
//	btCollisionShape*		mShape;

	btCompoundShape*		mCompound;


//	bool					isCompound;

    /// Bullet compound collision shape.
    //btCompoundShape* mCompoundShape;
    /// Compound collision shape with center of mass offset applied.
    //btCompoundShape* mShiftedCompoundShape;

	//----------------------------------------------------------------//
	
	//static int		_addCompoundShape		( lua_State* L );
	//static int		_addChild				( lua_State* L );
	static int		_newShape				( lua_State* L );
	static int		_addToBody				( lua_State* L );
	static int		_addRag				( lua_State* L );
	//static int		_addPlane				( lua_State* L );
	//static int		_addSphere				( lua_State* L );
	//static int		_addBox					( lua_State* L );
	//static int		_addCylinder			( lua_State* L );
	//static int		_addCapsule				( lua_State* L );
	//static int		_addCone				( lua_State* L );
	//static int		_addRag					( lua_State* L );




//LINEAR
	static int		_SetLinearVelocity			( lua_State* L );
	static int		_SetLinearFactor			( lua_State* L );
	static int		_SetLinearRestThreshold		( lua_State* L );
	static int		_SetLinearDamping			( lua_State* L );
//ANGULAR
	static int		_SetAngularVelocity				( lua_State* L );
	static int		_SetAngularFactor				( lua_State* L );
	static int		_SetAngularRestThreshold		( lua_State* L );
	static int		_SetAngularDamping				( lua_State* L );
//FRICTION
	static int		_SetFriction				( lua_State* L );
	static int		_SetAnisotropicFriction		( lua_State* L );
	static int		_SetRollingFriction			( lua_State* L );
//RESITUTION	
	static int		_SetRestitution			( lua_State* L );
//GRAVITY
	//static int		_SetUseGravity			( lua_State* L );
	//static int		_SetGravityOverride		( lua_State* L );
//FORCE
	static int		_ApplyForce				( lua_State* L );
	static int		_ApplyForceOffset		( lua_State* L );
//TORQUE
	static int		_ApplyTorque			( lua_State* L );
//IMPULSE
	static int		_ApplyImpulse			( lua_State* L );
	static int		_ApplyImpulseOffset		( lua_State* L );
	static int		_ApplyTorqueImpulse		( lua_State* L );	
//RESET
	static int		_ResetForces		( lua_State* L );	

//SET GARVITY
	static int		_SetGravity		( lua_State* L );
//DAMPING
	static int		_SetDamping		( lua_State* L );

	static int		_SetDeactivationTime	( lua_State* L );
	static int		_SetSleepingThresholds	( lua_State* L );	
	

//MASS	: ON SHAPE
	//static int		_SetMass		( lua_State* L );

	static int		_SetPosition		( lua_State* L );
	static int		_SetRotation		( lua_State* L );
	static int		_AddToWorld			( lua_State* L );

	static int		_SetKinematic		( lua_State* L );

//GET
	static int		_GetPosition				( lua_State* L );
	static int		_GetRotation				( lua_State* L );
	static int		_GetLinearVelocity			( lua_State* L );
	static int		_GetLinearFactor			( lua_State* L );
	static int		_GetVelocityAtPoint			( lua_State* L );
	static int		_GetLinearRestThreshold		( lua_State* L );	
	static int		_GetLinearDamping			( lua_State* L );	
	static int		_GetAngularVelocity			( lua_State* L );
	static int		_GetAngularFactor			( lua_State* L );
	static int		_GetAngularRestThreshold	( lua_State* L );
	static int		_GetAngularDamping			( lua_State* L );
	static int		_GetFriction				( lua_State* L );
	static int		_GetAnisotropicFriction		( lua_State* L );
	static int		_GetRollingFriction			( lua_State* L );
	static int		_GetRestitution				( lua_State* L );
	static int		_GetContactProcessingThreshold	( lua_State* L );
	static int		_GetCcdRadius				( lua_State* L );
	static int		_GetCcdMotionThreshold		( lua_State* L );
	static int		_IsActive					( lua_State* L );
	static int		_GetCollidingBodies			( lua_State* L );


//
	static int		_RemoveBodyFromWorld			( lua_State* L );

	

	//----------------------------------------------------------------//
	bool			ApplyAttrOp				( u32 attrID, MOAIAttrOp& attrOp, u32 op );
	void			SetBody					( btRigidBody* body );
	void			OnDepNodeUpdate			();

public:
	
	friend class MOAIBulletShape;
	friend class MOAIBulletWorld;
	//friend class MOAIBulletConstraint;

	DECL_LUA_FACTORY ( MOAIBulletBody )

	//----------------------------------------------------------------//
	void			setWorld				(btDiscreteDynamicsWorld* world_);
	void			Destroy					();
					MOAIBulletBody			();
					~MOAIBulletBody			();
	void			RegisterLuaClass		( MOAILuaState& state );
	void			RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
