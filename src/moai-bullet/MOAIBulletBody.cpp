// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com


//NEED TO CHANGE THE SHAPES TO THE BASIC
// http://bulletphysics.com/Bullet/BulletFull/classbtSphereShape.html




#include "pch.h"


#include <moai-bullet/MOAIBulletBody.h>
#include <moai-bullet/MOAIBulletShape.h>

//#include <moai-bullet/MOAIBulletDebugDraw.h>

#include <bullet/src/btBulletDynamicsCommon.h>

//================================================================//
// local
//================================================================//

//
//int MOAIBulletBody::_addCompoundShape ( lua_State* L ) {
//	MOAI_LUA_SETUP ( MOAIBulletBody, "U" )
//	//SHAPE
//	self->mCompound = new btCompoundShape();
//
//	//BODY
//	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, self->mMotion, self->mShape, btVector3(0, 0, 0));
//	self->mBody = new btRigidBody(groundRigidBodyCI);
//
//	self->isCompound = true;
//
//	return 1;
//};

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//int MOAIBulletBody::_addChild ( lua_State* L ) {
//MOAI_LUA_SETUP ( MOAIBulletBody, "UUNNN" )
//
//MOAIBulletShape* shapeA = state.GetLuaObject < MOAIBulletShape >( 2, true );
//
//float offset_x = state.GetValue < float >( 3, 0.0f );
//float offset_y = state.GetValue < float >( 4, 0.0f );
//float offset_z = state.GetValue < float >( 5, 0.0f );
//
//btTransform offset; 
//offset.setIdentity();
//offset.setOrigin(btVector3 ( offset_x,offset_y,offset_z));
//self->mCompound->addChildShape(offset,shapeA->mShape); //MAKE FRIEND CLASS
//
//
//
//return 1;
//};






//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
////**************************************************************************************************************
//btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape)
//{
//	bool isDynamic = (mass != 0.f);
//	btVector3 localInertia(0,0,0);
//
//	if (isDynamic)
//		shape->calculateLocalInertia(mass,localInertia);
//		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
//		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,shape,localInertia);
//		btRigidBody* body = new btRigidBody(rbInfo);
//
//		//Kinematic Bodies 
//
//			//body->setCollisionFlags( body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
//			body->setActivationState(DISABLE_DEACTIVATION);
//
//
//	return body;
//}
//		




//int MOAIBulletBody::_addRag ( lua_State* L ) {
//MOAI_LUA_SETUP ( MOAIBulletBody, "U" )


//
//
//
//	enum
//{
//BODYPART_PELVIS = 0,
//BODYPART_SPINE,
//BODYPART_HEAD,
//BODYPART_LEFT_UPPER_LEG,
//BODYPART_LEFT_LOWER_LEG,
//BODYPART_RIGHT_UPPER_LEG,
//BODYPART_RIGHT_LOWER_LEG,
//BODYPART_LEFT_UPPER_ARM,
//BODYPART_LEFT_LOWER_ARM,
//BODYPART_RIGHT_UPPER_ARM,
//BODYPART_RIGHT_LOWER_ARM,
//BODYPART_COUNT
//};
//enum
//{
//JOINT_PELVIS_SPINE = 0,
//JOINT_SPINE_HEAD,
//JOINT_LEFT_HIP,
//JOINT_LEFT_KNEE,
//JOINT_RIGHT_HIP,
//JOINT_RIGHT_KNEE,
//JOINT_LEFT_SHOULDER,
//JOINT_LEFT_ELBOW,
//JOINT_RIGHT_SHOULDER,
//JOINT_RIGHT_ELBOW,
//JOINT_COUNT
//};
//
//
//float offsetX = state.GetValue < float >( 2, 0.0f );
//float offsetY = state.GetValue < float >( 3, 0.0f );
//float offsetZ = state.GetValue < float >( 4, 0.0f );
//
//float CONSTRAINT_DEBUG_SIZE = 50.0f;
//
//btCollisionShape*	m_shapes[BODYPART_COUNT];
//btRigidBody*		m_bodies[BODYPART_COUNT];
//btTypedConstraint*	m_joints[JOINT_COUNT];
//
//
//// Setup the geometry
//	m_shapes[BODYPART_PELVIS]			= new btCapsuleShape(btScalar(0.15), btScalar(0.20));
//	m_shapes[BODYPART_SPINE]			= new btCapsuleShape(btScalar(0.15), btScalar(0.28));
//	m_shapes[BODYPART_HEAD]				= new btCapsuleShape(btScalar(0.10), btScalar(0.05));
//	m_shapes[BODYPART_LEFT_UPPER_LEG]	= new btCapsuleShape(btScalar(0.07), btScalar(0.45));
//	m_shapes[BODYPART_LEFT_LOWER_LEG]	= new btCapsuleShape(btScalar(0.05), btScalar(0.37));
//	m_shapes[BODYPART_RIGHT_UPPER_LEG]	= new btCapsuleShape(btScalar(0.07), btScalar(0.45));
//	m_shapes[BODYPART_RIGHT_LOWER_LEG]	= new btCapsuleShape(btScalar(0.05), btScalar(0.37));
//	m_shapes[BODYPART_LEFT_UPPER_ARM]	= new btCapsuleShape(btScalar(0.05), btScalar(0.33));
//	m_shapes[BODYPART_LEFT_LOWER_ARM]	= new btCapsuleShape(btScalar(0.04), btScalar(0.25));
//	m_shapes[BODYPART_RIGHT_UPPER_ARM]	= new btCapsuleShape(btScalar(0.05), btScalar(0.33));
//	m_shapes[BODYPART_RIGHT_LOWER_ARM]	= new btCapsuleShape(btScalar(0.04), btScalar(0.25));
//
//
////**********************************************************************************
//// Setup all the rigid bodies
//btTransform offset; 
//offset.setIdentity();
//offset.setOrigin(btVector3 ( offsetX,offsetY,offsetZ));
//
////TRANSFORM
//btTransform transform;
//
////**********************************************************************************
//transform.setIdentity();
//transform.setOrigin(btVector3(btScalar(0.), btScalar(1.), btScalar(0.)));
//m_bodies[BODYPART_PELVIS] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_PELVIS]);
//self->mWorld->addRigidBody(m_bodies[BODYPART_PELVIS]);
////**********************************************************************************
//transform.setIdentity();
//transform.setOrigin(btVector3(btScalar(0.), btScalar(1.2), btScalar(0.)));
//m_bodies[BODYPART_SPINE] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_SPINE]);
//self->mWorld->addRigidBody(m_bodies[BODYPART_SPINE]);
//transform.setIdentity();
////**********************************************************************************
//transform.setIdentity();
//transform.setOrigin(btVector3(btScalar(0.), btScalar(1.6), btScalar(0.)));
//m_bodies[BODYPART_HEAD] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_HEAD]);
//self->mWorld->addRigidBody(m_bodies[BODYPART_HEAD]);
//
////**********************************************************************************
//transform.setIdentity();
//transform.setOrigin(btVector3(btScalar(-0.18), btScalar(0.65), btScalar(0.)));
//m_bodies[BODYPART_LEFT_UPPER_LEG] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_UPPER_LEG]);
//self->mWorld->addRigidBody(m_bodies[BODYPART_LEFT_UPPER_LEG]);
//
////**********************************************************************************
//transform.setIdentity();
//transform.setOrigin(btVector3(btScalar(-0.18), btScalar(0.2), btScalar(0.)));
//m_bodies[BODYPART_LEFT_LOWER_LEG] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_LOWER_LEG]);
//self->mWorld->addRigidBody(m_bodies[BODYPART_LEFT_LOWER_LEG]);
//
////**********************************************************************************
//transform.setIdentity();
//transform.setOrigin(btVector3(btScalar(0.18), btScalar(0.65), btScalar(0.)));
//m_bodies[BODYPART_RIGHT_UPPER_LEG] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_UPPER_LEG]);
//self->mWorld->addRigidBody(m_bodies[BODYPART_RIGHT_UPPER_LEG]);
//
////**********************************************************************************
//transform.setIdentity();
//transform.setOrigin(btVector3(btScalar(0.18), btScalar(0.2), btScalar(0.)));
//m_bodies[BODYPART_RIGHT_LOWER_LEG] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_LOWER_LEG]);
//self->mWorld->addRigidBody(m_bodies[BODYPART_RIGHT_LOWER_LEG]);
//
////**********************************************************************************
//transform.setIdentity();
//transform.setOrigin(btVector3(btScalar(-0.35), btScalar(1.45), btScalar(0.)));
//transform.getBasis().setEulerZYX(0,0,M_PI_2);
//m_bodies[BODYPART_LEFT_UPPER_ARM] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_UPPER_ARM]);
//self->mWorld->addRigidBody(m_bodies[BODYPART_LEFT_UPPER_ARM]);
//
////**********************************************************************************
//transform.setIdentity();
//transform.setOrigin(btVector3(btScalar(-0.7), btScalar(1.45), btScalar(0.)));
//transform.getBasis().setEulerZYX(0,0,M_PI_2);
//m_bodies[BODYPART_LEFT_LOWER_ARM] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_LOWER_ARM]);
//self->mWorld->addRigidBody(m_bodies[BODYPART_LEFT_LOWER_ARM]);
//
////**********************************************************************************
//transform.setIdentity();
//transform.setOrigin(btVector3(btScalar(0.35), btScalar(1.45), btScalar(0.)));
//transform.getBasis().setEulerZYX(0,0,-M_PI_2);
//m_bodies[BODYPART_RIGHT_UPPER_ARM] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_UPPER_ARM]);
//self->mWorld->addRigidBody(m_bodies[BODYPART_RIGHT_UPPER_ARM]);
//
////**********************************************************************************
//transform.setIdentity();
//transform.setOrigin(btVector3(btScalar(0.7), btScalar(1.45), btScalar(0.)));
//transform.getBasis().setEulerZYX(0,0,-M_PI_2);
//m_bodies[BODYPART_RIGHT_LOWER_ARM] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_LOWER_ARM]);
//self->mWorld->addRigidBody(m_bodies[BODYPART_RIGHT_LOWER_ARM]);
//
//
////*******************************************************************************************
//// Setup some damping on the m_bodies
//		for (int i = 0; i < BODYPART_COUNT; ++i)
//		{
//				m_bodies[i]->setDamping(0.05, 0.85);
//				m_bodies[i]->setDeactivationTime(0.8);
//				m_bodies[i]->setSleepingThresholds(1.6, 2.5);
//		}
//
//
////****************************************************************************************
////****************************************************************************************
//
//btHingeConstraint*		hingeC;
//btConeTwistConstraint*	coneC;
//
//btTransform localA, localB;
//
//
////****************************************************************************************
////****************************************************************************************
//localA.setIdentity(); 
//localB.setIdentity();
//localA.getBasis().setEulerZYX(0,M_PI_2,0); localA.setOrigin(btVector3(btScalar(0.), btScalar(0.15), btScalar(0.)));
//localB.getBasis().setEulerZYX(0,M_PI_2,0); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.15), btScalar(0.)));
//
//hingeC = new btHingeConstraint(*m_bodies[BODYPART_PELVIS], *m_bodies[BODYPART_SPINE], localA, localB);
//hingeC->setLimit(btScalar(-M_PI_4), btScalar(M_PI_2));
//hingeC->setDbgDrawSize(0);
//m_joints[JOINT_PELVIS_SPINE] = hingeC;	
//
//self->mWorld->addConstraint(m_joints[JOINT_PELVIS_SPINE], true);
//
////****************************************************************************************
////****************************************************************************************
//localA.setIdentity(); 
//localB.setIdentity();
//localA.getBasis().setEulerZYX(0,0,M_PI_2); 
//localA.setOrigin(btVector3(btScalar(0.), btScalar(0.30), btScalar(0.)));
//localB.getBasis().setEulerZYX(0,0,M_PI_2); 
//localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.14), btScalar(0.)));
//
//coneC = new btConeTwistConstraint(*m_bodies[BODYPART_SPINE], *m_bodies[BODYPART_HEAD], localA, localB);
//coneC->setLimit(M_PI_4, M_PI_4, M_PI_2);
//coneC->setDbgDrawSize(0);
//m_joints[JOINT_SPINE_HEAD] = coneC;
//
//self->mWorld->addConstraint(m_joints[JOINT_SPINE_HEAD], true);
//
////****************************************************************************************
////****************************************************************************************
//
//localA.setIdentity(); 
//localA.getBasis().setEulerZYX(0,0,-M_PI_4*5); 
//localA.setOrigin(btVector3(btScalar(-0.18), btScalar(-0.10), btScalar(0.)));
//
//localB.setIdentity();
//localB.getBasis().setEulerZYX(0,0,-M_PI_4*5); 
//localB.setOrigin(btVector3(btScalar(0.), btScalar(0.225), btScalar(0.)));
//
//coneC = new btConeTwistConstraint(*m_bodies[BODYPART_PELVIS], *m_bodies[BODYPART_LEFT_UPPER_LEG], localA, localB);
//coneC->setLimit(M_PI_4, M_PI_4, 0);
//coneC->setDbgDrawSize(0);
//m_joints[JOINT_LEFT_HIP] = coneC;
//	
//self->mWorld->addConstraint(m_joints[JOINT_LEFT_HIP], true);
//
////****************************************************************************************
////****************************************************************************************
//
//localA.setIdentity(); 
//localA.getBasis().setEulerZYX(0,M_PI_2,0); 
//localA.setOrigin(btVector3(btScalar(0.), btScalar(-0.225), btScalar(0.)));
//
//localB.setIdentity();
//localB.getBasis().setEulerZYX(0,M_PI_2,0); 
//localB.setOrigin(btVector3(btScalar(0.), btScalar(0.185), btScalar(0.)));
//
//hingeC = new btHingeConstraint(*m_bodies[BODYPART_LEFT_UPPER_LEG], *m_bodies[BODYPART_LEFT_LOWER_LEG], localA, localB);
//hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
//hingeC->setDbgDrawSize(0);
//m_joints[JOINT_LEFT_KNEE] = hingeC;	
//
//self->mWorld->addConstraint(m_joints[JOINT_LEFT_KNEE], true);
//
////****************************************************************************************
////****************************************************************************************
//localA.setIdentity(); 
//localA.getBasis().setEulerZYX(0,0,M_PI_4); 
//localA.setOrigin(btVector3(btScalar(0.18), btScalar(-0.10), btScalar(0.)));
//localB.setIdentity();
//localB.getBasis().setEulerZYX(0,0,M_PI_4); 
//localB.setOrigin(btVector3(btScalar(0.), btScalar(0.225), btScalar(0.)));
//
//coneC = new btConeTwistConstraint(*m_bodies[BODYPART_PELVIS], *m_bodies[BODYPART_RIGHT_UPPER_LEG], localA, localB);
//coneC->setLimit(M_PI_4, M_PI_4, 0);
//coneC->setDbgDrawSize(0);
//m_joints[JOINT_RIGHT_HIP] = coneC;
//
//self->mWorld->addConstraint(m_joints[JOINT_RIGHT_HIP], true);
//
////****************************************************************************************
////****************************************************************************************
//localA.setIdentity(); 
//localA.getBasis().setEulerZYX(0,M_PI_2,0); 
//localA.setOrigin(btVector3(btScalar(0.), btScalar(-0.225), btScalar(0.)));
//
//localB.setIdentity();
//localB.getBasis().setEulerZYX(0,M_PI_2,0);
//localB.setOrigin(btVector3(btScalar(0.), btScalar(0.185), btScalar(0.)));
//
//hingeC = new btHingeConstraint(*m_bodies[BODYPART_RIGHT_UPPER_LEG], *m_bodies[BODYPART_RIGHT_LOWER_LEG], localA, localB);
//hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
//hingeC->setDbgDrawSize(0);
//m_joints[JOINT_RIGHT_KNEE] = hingeC;
//
//
//self->mWorld->addConstraint(m_joints[JOINT_RIGHT_KNEE], true);
//
////****************************************************************************************
////****************************************************************************************
//localA.setIdentity();
//localA.getBasis().setEulerZYX(0,0,M_PI); 
//localA.setOrigin(btVector3(btScalar(-0.2), btScalar(0.15), btScalar(0.)));
//
//localB.setIdentity();
//localB.getBasis().setEulerZYX(0,0,M_PI_2); 
//localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.18), btScalar(0.)));
//
//coneC = new btConeTwistConstraint(*m_bodies[BODYPART_SPINE], *m_bodies[BODYPART_LEFT_UPPER_ARM], localA, localB);
//coneC->setLimit(M_PI_2, M_PI_2, 0);
//coneC->setDbgDrawSize(0);
//m_joints[JOINT_LEFT_SHOULDER] = coneC;
//
//self->mWorld->addConstraint(m_joints[JOINT_LEFT_SHOULDER], true);
//
////****************************************************************************************
////****************************************************************************************
//localA.setIdentity(); 
//localA.getBasis().setEulerZYX(0,M_PI_2,0); 
//localA.setOrigin(btVector3(btScalar(0.), btScalar(0.18), btScalar(0.)));
//
//localB.setIdentity();
//localB.getBasis().setEulerZYX(0,M_PI_2,0);
//localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.14), btScalar(0.)));
//
//hingeC = new btHingeConstraint(*m_bodies[BODYPART_LEFT_UPPER_ARM], *m_bodies[BODYPART_LEFT_LOWER_ARM], localA, localB);
//hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
//hingeC->setDbgDrawSize(0);
//m_joints[JOINT_LEFT_ELBOW] = hingeC;
//
//self->mWorld->addConstraint(m_joints[JOINT_LEFT_ELBOW], true);
//
////****************************************************************************************
////****************************************************************************************
//localA.setIdentity(); 
//localA.getBasis().setEulerZYX(0,0,0); 
//localA.setOrigin(btVector3(btScalar(0.2), btScalar(0.15), btScalar(0.)));
//localB.getBasis().setEulerZYX(0,0,M_PI_2); 
//localB.setIdentity();
//localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.18), btScalar(0.)));
//
//coneC = new btConeTwistConstraint(*m_bodies[BODYPART_SPINE], *m_bodies[BODYPART_RIGHT_UPPER_ARM], localA, localB);
//coneC->setLimit(M_PI_2, M_PI_2, 0);
//coneC->setDbgDrawSize(0);
//m_joints[JOINT_RIGHT_SHOULDER] = coneC;
//
//self->mWorld->addConstraint(m_joints[JOINT_RIGHT_SHOULDER], true);
//
////****************************************************************************************
////****************************************************************************************
//
//localA.setIdentity();
//localA.getBasis().setEulerZYX(0,M_PI_2,0); 
//localA.setOrigin(btVector3(btScalar(0.), btScalar(0.18), btScalar(0.)));
//
//localB.setIdentity();
//localB.getBasis().setEulerZYX(0,M_PI_2,0);
//localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.14), btScalar(0.)));
//
//hingeC = new btHingeConstraint(*m_bodies[BODYPART_RIGHT_UPPER_ARM], *m_bodies[BODYPART_RIGHT_LOWER_ARM], localA, localB);
//hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
//hingeC->setDbgDrawSize(0);
//m_joints[JOINT_RIGHT_ELBOW] = hingeC;
//
//self->mWorld->addConstraint(m_joints[JOINT_RIGHT_ELBOW], true);


//return 1;

//};

//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************


//----------------------------------------------------------------//
int MOAIBulletBody::_SetLinearVelocity ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	
	float velocity_x = state.GetValue < float >( 2, 0.0f );
	float velocity_y = state.GetValue < float >( 3, 0.0f );
	float velocity_z = state.GetValue < float >( 4, 0.0f );
    if (self->mBody)
    {
       self->mBody->setLinearVelocity(btVector3(velocity_x, velocity_y, velocity_z));   
    }

	return 1;
}

//----------------------------------------------------------------//
int MOAIBulletBody::_SetLinearFactor ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	
	float velocity_x = state.GetValue < float >( 2, 0.0f );
	float velocity_y = state.GetValue < float >( 3, 0.0f );
	float velocity_z = state.GetValue < float >( 4, 0.0f );
    if (self->mBody)
    {
       self->mBody->setLinearFactor(btVector3(velocity_x, velocity_y, velocity_z));   
    }

	return 1;
}

//----------------------------------------------------------------//
int MOAIBulletBody::_SetLinearRestThreshold ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	
	float threshold = state.GetValue < float >( 2, 0.0f );

    if (self->mBody)
	{     
		self->mBody->setSleepingThresholds(threshold, self->mBody->getAngularSleepingThreshold());
    }

	return 1;
}

//----------------------------------------------------------------//
int MOAIBulletBody::_SetLinearDamping ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	
	float damping = state.GetValue < float >( 2, 0.0f );
    if (self->mBody)
	{   		
		self->mBody->setDamping(damping,  self->mBody->getAngularDamping());
    }
	return 1;
}



//----------------------------------------------------------------//
int MOAIBulletBody::_SetAngularVelocity ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	
	float velocity_x = state.GetValue < float >( 2, 0.0f );
	float velocity_y = state.GetValue < float >( 3, 0.0f );
	float velocity_z = state.GetValue < float >( 4, 0.0f );
    if (self->mBody)
    {
       self->mBody->setAngularVelocity(btVector3(velocity_x, velocity_y, velocity_z));   
    }

	return 1;
}

//----------------------------------------------------------------//
int MOAIBulletBody::_SetAngularFactor ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	
	float velocity_x = state.GetValue < float >( 2, 0.0f );
	float velocity_y = state.GetValue < float >( 3, 0.0f );
	float velocity_z = state.GetValue < float >( 4, 0.0f );
    if (self->mBody)
    {
       self->mBody->setAngularFactor(btVector3(velocity_x, velocity_y, velocity_z));   
    }

	return 1;
}

//----------------------------------------------------------------//
int MOAIBulletBody::_SetAngularRestThreshold ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	
	float threshold = state.GetValue < float >( 2, 0.0f );

    if (self->mBody)
	{     
		self->mBody->setSleepingThresholds(self->mBody->getLinearSleepingThreshold(),threshold);
    }

	return 1;
}

//----------------------------------------------------------------//
int MOAIBulletBody::_SetAngularDamping ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	
	float damping = state.GetValue < float >( 2, 0.0f );
    if (self->mBody)
	{   		
		self->mBody->setDamping(self->mBody->getAngularDamping(),damping);
    }
	return 1;
}

//----------------------------------------------------------------//




//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************


//----------------------------------------------------------------//
int MOAIBulletBody::_SetRestitution ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	float restitution = state.GetValue < float >( 2, 0.0f );
    if (self->mBody)
    {      

	   self->mBody->setRestitution(restitution);
    }

	return 1;
}

//----------------------------------------------------------------//
int MOAIBulletBody::_SetFriction ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	float friction = state.GetValue < float >( 2, 0.0f );
    if (self->mBody)
    {       
	   self->mBody->setFriction(friction);
    }

	return 1;
}


//----------------------------------------------------------------//
//int MOAIBulletBody::_SetMass ( lua_State* L ) {
//	MOAI_LUA_SETUP ( MOAIBulletBody, "UUNN" );	
//
//	MOAIBulletShape* shapeA = state.GetLuaObject < MOAIBulletShape >( 2, true );
//
//	float mass	  = state.GetValue < float >( 3, 0.0f );
//	float Inertia = state.GetValue < float >( 4, 0.0f );
//
//    //if (self->mBody)
//    //{ 
//	//}
//
//	//SETS IT TO THE MASS AND BODY
//
//	//MASS
//		btScalar mMass = mass;
//	//inertia
//		btVector3 mInertia(Inertia, Inertia, Inertia);
//		//self->mShape->calculateLocalInertia(mMass, mInertia);
//		shapeA->mShape->calculateLocalInertia(mMass, mInertia);
//	//UPDATE
//		self->mBody->setMassProps(mass, mInertia);
//   
//	return 1;
//}



//*******************************************************************************************
int MOAIBulletBody::_GetCollidingBodies ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
    if (self->mBody)
    {       
	     
    }
	return 1;
}


//*******************************************************************************************
int MOAIBulletBody::_IsActive ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;    
	float isActive = self->mBody->isActive();
	lua_pushnumber ( state, isActive ); 
	return 1;
}

//*******************************************************************************************
int MOAIBulletBody::_GetCcdMotionThreshold ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;    
	float motionThreshold = self->mBody->getCcdMotionThreshold();
	lua_pushnumber ( state, motionThreshold ); 
	return 1;
}

//*******************************************************************************************
int MOAIBulletBody::_GetCcdRadius ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" );	    
	float radius = self->mBody->getCcdSweptSphereRadius();
	lua_pushnumber ( state, radius ); 
	return 1;
}


//*******************************************************************************************
int MOAIBulletBody::_GetContactProcessingThreshold ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" );	    
	float threshold = self->mBody->getContactProcessingThreshold();
	lua_pushnumber ( state, threshold ); 
	return 1;
}

//*******************************************************************************************
int MOAIBulletBody::_GetRestitution ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" );	    
	float restitution = self->mBody->getRestitution();
	lua_pushnumber ( state, restitution ); 
	return 1;
}

//*******************************************************************************************
int MOAIBulletBody::_GetRollingFriction ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;    
	float rollingFriction = self->mBody->getRollingFriction();
	lua_pushnumber ( state, rollingFriction ); 
	return 1;
}


//*******************************************************************************************
int MOAIBulletBody::_GetAnisotropicFriction ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	; 

	//btVector3 anisotropicFriction = self->mBody->getAnisotropicFriction();
	//float friction_x = btVector3.x;
	//float friction_y = btVector3.y;		
	//float friction_z = btVector3.z;

	//lua_pushnumber ( state, friction_x ); 
	//lua_pushnumber ( state, friction_y ); 
	//lua_pushnumber ( state, friction_z ); 

	return 1;
}


//*******************************************************************************************
int MOAIBulletBody::_GetFriction ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" );	    
	float friction = self->mBody->getFriction();
	lua_pushnumber ( state, friction ); 
	return 1;
}


//*******************************************************************************************
int MOAIBulletBody::_GetAngularDamping ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" );	    
	float angularDamping = self->mBody->getAngularDamping();
	lua_pushnumber ( state, angularDamping ); 
	return 1;
}

//*******************************************************************************************
int MOAIBulletBody::_GetAngularRestThreshold ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" );	    
	float restThreshold = self->mBody->getAngularSleepingThreshold();
	lua_pushnumber ( state, restThreshold ); 
	return 1;
}

//*******************************************************************************************
int MOAIBulletBody::_GetAngularFactor ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;    
	btVector3 angularFactor = self->mBody->getAngularFactor();

	//float angularFactor_x = btVector3.x;
	//float angularFactor_y = btVector3.y;		
	//float angularFactor_z = btVector3.z;

	//lua_pushnumber ( state, angularFactor_x ); 
	//lua_pushnumber ( state, angularFactor_y ); 
	//lua_pushnumber ( state, angularFactor_z ); 

	return 1;
}

//*******************************************************************************************
int MOAIBulletBody::_GetAngularVelocity ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;    
	btVector3 angularVelocity = self->mBody->getAngularVelocity();

	//float angularVelocity_x = btVector3.x;
	//float angularVelocity_y = btVector3.y;		
	//float angularVelocity_z = btVector3.z;

	//lua_pushnumber ( state, angularVelocity_x ); 
	//lua_pushnumber ( state, angularVelocity_y ); 
	//lua_pushnumber ( state, angularVelocity_z ); 
	return 1;
}

//*******************************************************************************************
int MOAIBulletBody::_GetLinearDamping ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" );	    
	float linearDamping = self->mBody->getLinearDamping();
	lua_pushnumber ( state, linearDamping ); 
	return 1;
}

//*******************************************************************************************
int MOAIBulletBody::_GetLinearRestThreshold ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;    
	float restThreshold = self->mBody->getLinearSleepingThreshold();
	lua_pushnumber ( state, restThreshold ); 
	return 1;
}

//*******************************************************************************************
int MOAIBulletBody::_GetVelocityAtPoint ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;  

//	btVector3 velocityAtPoint = self->mBody->getVelocityInLocalPoint(ToBtVector3(position - centerOfMass_));

	//float velocityAtPoint_x = btVector3.x;
	//float velocityAtPoint_y = btVector3.y;		
	//float velocityAtPoint_z = btVector3.z;

	//lua_pushnumber ( state, velocityAtPoint_x ); 
	//lua_pushnumber ( state, velocityAtPoint_y ); 
	//lua_pushnumber ( state, velocityAtPoint_z ); 
	return 1;
}

//*******************************************************************************************
int MOAIBulletBody::_GetLinearFactor ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;    
	btVector3 linearFactor = self->mBody->getLinearFactor();
	//float linearFactor_x = btVector3.x;
	//float linearFactor_y = btVector3.y;		
	//float linearFactor_z = btVector3.z;

	//lua_pushnumber ( state, linearFactor_x ); 
	//lua_pushnumber ( state, linearFactor_y ); 
	//lua_pushnumber ( state, linearFactor_z ); 
	return 1;
}

//*******************************************************************************************
int MOAIBulletBody::_GetLinearVelocity ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;    
	btVector3 linearVelocity = self->mBody->getLinearVelocity();
	//float linearVelocity_x = btVector3.x;
	//float linearVelocity_y = btVector3.y;		
	//float linearVelocity_z = btVector3.z;

	//lua_pushnumber ( state, linearVelocity_x ); 
	//lua_pushnumber ( state, linearVelocity_y ); 
	//lua_pushnumber ( state, linearVelocity_z ); 
	return 1;
}
//*******************************************************************************************
int MOAIBulletBody::_GetRotation ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;    
	//float rotation = self->mBody->getWorldTransform().getRotation();
	//   return body_ ? ToQuaternion(body_->getWorldTransform().getRotation()) : Quaternion::IDENTITY;
	//lua_pushnumber ( state, restThreshold ); 
	return 1;
}

//*******************************************************************************************
int MOAIBulletBody::_GetPosition ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;    
	const btTransform& transform = self->mBody->getWorldTransform();
   // return ToVector3(transform.getOrigin()) - ToQuaternion(transform.getRotation()) * centerOfMass_;
	//lua_pushnumber ( state, restThreshold ); 
	return 1;
}


//*******************************************************************************************
int MOAIBulletBody::_RemoveBodyFromWorld ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "U" )	;
self->mWorld->removeRigidBody(self->mBody);  
return 1;
};


//*******************************************************************************************
int MOAIBulletBody::_ResetForces ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;

	float torque_x = state.GetValue < float >( 2, 0.0f );
	float torque_y = state.GetValue < float >( 3, 0.0f );
	float torque_z = state.GetValue < float >( 4, 0.0f );

	btVector3 torque(torque_x, torque_y, torque_z);
	self->mBody->applyTorque(torque);

return 1;
};

//*******************************************************************************************
int MOAIBulletBody::_ApplyImpulse ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;

	float impulse_x = state.GetValue < float >( 2, 0.0f );
	float impulse_y = state.GetValue < float >( 3, 0.0f );
	float impulse_z = state.GetValue < float >( 4, 0.0f );
	btVector3 impulse(impulse_x, impulse_y, impulse_z);
	self->mBody->applyCentralImpulse(impulse);

return 1;
};

//*******************************************************************************************
int MOAIBulletBody::_ApplyImpulseOffset ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;

	float impulse_x = state.GetValue < float >( 2, 0.0f );
	float impulse_y = state.GetValue < float >( 3, 0.0f );
	float impulse_z = state.GetValue < float >( 4, 0.0f );

	float offset_x = state.GetValue < float >( 5, 0.0f );
	float offset_y = state.GetValue < float >( 6, 0.0f );
	float offset_z = state.GetValue < float >( 7, 0.0f );

	btVector3 impulse(impulse_x, impulse_y, impulse_z);
	btVector3 offset(offset_x, offset_y, offset_z);

	//body_->applyImpulse(ToBtVector3(impulse), ToBtVector3(position - centerOfMass_));
	self->mBody->applyImpulse(impulse,offset);

return 1;
};
//*******************************************************************************************
int MOAIBulletBody::_ApplyTorque ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;

	float torque_x = state.GetValue < float >( 2, 0.0f );
	float torque_y = state.GetValue < float >( 3, 0.0f );
	float torque_z = state.GetValue < float >( 4, 0.0f );
	btVector3 torque(torque_x, torque_y, torque_z);
	self->mBody->applyTorque(torque);

return 1;
};

//*******************************************************************************************
int MOAIBulletBody::_ApplyForce ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	float force_x = state.GetValue < float >( 2, 0.0f );
	float force_y = state.GetValue < float >( 3, 0.0f );
	float force_z = state.GetValue < float >( 4, 0.0f );
	btVector3 force(force_x, force_y, force_z);
	self->mBody->applyCentralForce(force);

return 1;
};

//*******************************************************************************************
int MOAIBulletBody::_ApplyForceOffset ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;

	float force_x = state.GetValue < float >( 2, 0.0f );
	float force_y = state.GetValue < float >( 3, 0.0f );
	float force_z = state.GetValue < float >( 4, 0.0f );

	float offset_x = state.GetValue < float >( 5, 0.0f );
	float offset_y = state.GetValue < float >( 6, 0.0f );
	float offset_z = state.GetValue < float >( 7, 0.0f );

	btVector3 force(force_x, force_y, force_z);
	btVector3 offset(offset_x, offset_y, offset_z);

	//body_->applyImpulse(ToBtVector3(impulse), ToBtVector3(position - centerOfMass_));
	self->mBody->applyForce(force,offset);

return 1;
};



//*******************************************************************************************
int MOAIBulletBody::_ApplyTorqueImpulse ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	float torque_x = state.GetValue < float >( 2, 0.0f );
	float torque_y = state.GetValue < float >( 3, 0.0f );
	float torque_z = state.GetValue < float >( 4, 0.0f );
	btVector3 torque(torque_x, torque_y, torque_z);
	self->mBody->applyTorqueImpulse(torque);

return 1;
};


//*******************************************************************************************
int MOAIBulletBody::_SetRollingFriction ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	float friction = state.GetValue < float >( 2, 0.0f );	
	self->mBody->setRollingFriction(friction);
return 1;
};


//*******************************************************************************************
int MOAIBulletBody::_SetAnisotropicFriction ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	float friction_x = state.GetValue < float >( 2, 0.0f );
	float friction_y = state.GetValue < float >( 3, 0.0f );
	float friction_z = state.GetValue < float >( 4, 0.0f );
	btVector3 friction(friction_x, friction_y, friction_z);
	self->mBody->setAnisotropicFriction(friction);

return 1;
};





//**********************************************************

int MOAIBulletBody::_SetKinematic ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	self->mBody->setCollisionFlags( self->mBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	self->mBody->setActivationState(DISABLE_DEACTIVATION);
	return 1;
};

//**********************************************************
int MOAIBulletBody::_SetPosition ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;

	float loc_x = state.GetValue < float >( 2, 0.0f );
	float loc_y = state.GetValue < float >( 3, 0.0f );
	float loc_z = state.GetValue < float >( 4, 0.0f );

	btTransform& worldTrans = self->mBody->getWorldTransform();
	worldTrans.setOrigin ( btVector3 ( loc_x,loc_y,loc_z) );

	return 1;
};

//**********************************************************
int MOAIBulletBody::_SetRotation ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	float rot_x = state.GetValue < float >( 2, 0.0f );
	float rot_y = state.GetValue < float >( 3, 0.0f );
	float rot_z = state.GetValue < float >( 4, 0.0f );

	btTransform& worldTrans = self->mBody->getWorldTransform();
	worldTrans.setRotation ( btQuaternion ( rot_x,rot_y,rot_z,1 ) ); 
	return 1;
};

//**********************************************************
int MOAIBulletBody::_AddToWorld ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "U" );	
	self->mWorld->addRigidBody(self->mBody);
	return 1;
};


//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************






//----------------------------------------------------------------//
void MOAIBulletBody::Destroy () {

}



//----------------------------------------------------------------//
MOAIBulletBody::MOAIBulletBody () :
	mBody ( 0 ),
	mMotion( 0 ),
	//mMass( 0.1 ),
	//mInertia ( 0.1,0.1,0.1 ),
	mCompound( 0 )
{
	
RTTI_BEGIN
	//RTTI_EXTEND ( MOAITransformBase )	
	RTTI_EXTEND ( MOAILuaObject )
RTTI_END

this->mMotion	= new btDefaultMotionState();	
this->mCompound = new btCompoundShape();   

	btScalar mMass = 1.0;
//inertia
	btVector3 mInertia(1.0, 1.0, 1.0);

btRigidBody::btRigidBodyConstructionInfo info(mMass,this->mMotion,this->mCompound,mInertia);  //create the constructioninfo, you can create multiple bodies with the same info
this->mBody = new btRigidBody(info);    //let's create the body itself
	
}


//----------------------------------------------------------------//
int MOAIBulletBody::_addToBody ( lua_State* L ) {

MOAI_LUA_SETUP ( MOAIBulletBody, "UU" )
MOAIBulletShape* shapeA = state.GetLuaObject < MOAIBulletShape >( 2, true );

btTransform t; 
t.setIdentity();
t.setRotation ( btQuaternion ( 0,0,0)); 
t.setOrigin(btVector3 ( 0,0,0));
self->mCompound->addChildShape(self->mBody->getWorldTransform(),shapeA->mShape); //MAKE FRIEND CLASS
return 1;
};



//----------------------------------------------------------------//
MOAIBulletBody::~MOAIBulletBody () {
	printf("\n ~MOAIBulletBody \n");


	//delete this->mMotion;
	//delete this->mCompound;
	//delete this->mBody;

	this->Destroy ();
}


//////----------------------------------------------------------------//
int MOAIBulletBody::_newShape ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "U" )	
	MOAIBulletShape* shape = new MOAIBulletShape ();
	shape->setCompound(self->mCompound);	
	shape->setBody(self->mBody);
	self->LuaRetain ( shape );
	shape->PushLuaUserdata ( state );
	return 1;
}





void MOAIBulletBody::setWorld (btDiscreteDynamicsWorld* world_) {
	this->mWorld = world_;
};


//----------------------------------------------------------------//
void MOAIBulletBody::RegisterLuaClass ( MOAILuaState& state ) {
	//MOAITransformBase::RegisterLuaClass ( state );	
}

//----------------------------------------------------------------//
void MOAIBulletBody::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	//MOAITransformBase::RegisterLuaFuncs ( state );
	
	luaL_Reg regTable [] = {


{ "addToBody",			_addToBody },


//BODY
{ "newShape",			_newShape },

//LINEAR
{ "setLinearVelocity",			_SetLinearVelocity },	
{ "setLinearFactor",			_SetLinearFactor },	
{ "setLinearRestThreshold",		_SetLinearRestThreshold },
{ "setLinearDamping",			_SetLinearDamping },

//ANGUALER
{ "setAngularVelocity",			_SetAngularVelocity },	
{ "setAngularFactor",			_SetAngularFactor },	
{ "setAngularRestThreshold",	_SetAngularRestThreshold },
{ "setAngularDamping",			_SetAngularDamping },

//DAMPING


//FRICTION
{ "setFriction",				 _SetFriction },	
{ "setAnisotropicFriction",			    _SetAnisotropicFriction },	
{ "setRollingFriction",			    _SetRollingFriction },	
//RESTITUTION
{ "setRestitution",			    _SetRestitution },
//FORCE
{ "applyForce",						 _ApplyForce },
{ "applyForceOffset",			   _ApplyForceOffset },
//TORQUE
{ "ApplyTorque",			   _ApplyTorque },
//IMPULSE
{ "applyImpulse",					_ApplyImpulse },
{ "applyImpulseOffset",			   _ApplyImpulseOffset },
{ "ApplyTorqueImpulse",			   _ApplyTorqueImpulse },
//RESET
{ "resetForces",			   _ResetForces },

//VALUES		

{ "setKinematic",				_SetKinematic },
{ "setPosition",				_SetPosition },		
{ "setRotation",				_SetRotation },	

{ "addToWorld",					_AddToWorld},	

//REMOVE
{ "removeBodyFromWorld",				_RemoveBodyFromWorld },	



//GET
{ "getPosition",					_GetPosition },	
{ "getRotation",					_GetRotation },	
{ "getLinearVelocity",				_GetLinearVelocity },	
{ "getLinearFactor",				_GetLinearFactor },	
{ "getVelocityAtPoint",				_GetVelocityAtPoint },	
{ "getLinearRestThreshold",			_GetLinearRestThreshold },	
{ "getLinearDamping",				_GetLinearDamping },	
{ "getAngularVelocity",				_GetAngularVelocity },	
{ "getAngularFactor",				_GetAngularFactor },	
{ "getAngularRestThreshold",		_GetAngularRestThreshold },	
{ "getAngularDamping",				_GetAngularDamping },	
{ "getFriction",					_GetFriction },	
{ "getAnisotropicFriction",			_GetAnisotropicFriction },	
{ "getRollingFriction",				_GetRollingFriction	 },	
{ "getRestitution",					_GetRestitution	 },	
{ "getContactProcessingThreshold",	_GetContactProcessingThreshold },	
{ "getCcdRadius",					_GetCcdMotionThreshold },	
{ "isActive",					_IsActive },	
{ "getCollidingBodies",					_GetCollidingBodies },	





		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}












//----------------------------------------------------------------//
void MOAIBulletBody::OnDepNodeUpdate () {

	if ( this->mBody ) {
		
				//b2Transform transform = this->mBody->GetTransform ();
				//float scale = 1.0f / this->GetUnitsToMeters ();		
				//float* m = this->mLocalToWorldMtx.m;

				//m [ ZLAffine3D::C0_R0 ] = ( float )transform.q.GetXAxis().x;
				//m [ ZLAffine3D::C0_R1 ] = ( float )transform.q.GetXAxis().y;

				//m [ ZLAffine3D::C1_R0 ] = ( float )transform.q.GetYAxis().x;
				//m [ ZLAffine3D::C1_R1 ] = ( float )transform.q.GetYAxis().y;

				//m [ ZLAffine3D::C3_R0 ] = ( float )transform.p.x * scale;
				//m [ ZLAffine3D::C3_R1 ] = ( float )transform.p.y * scale;
		
				//this->mWorldToLocalMtx.Inverse ( this->mLocalToWorldMtx );
	}
}





//----------------------------------------------------------------//
bool MOAIBulletBody::ApplyAttrOp ( u32 attrID, MOAIAttrOp& attrOp, u32 op ) {
	// TODO: these values may need to be cached for performance reasons
	/*if ( MOAITransform::MOAITransformAttr::Check ( attrID )) {
		const b2Transform & xform = mBody->GetTransform();
		
		switch ( UNPACK_ATTR ( attrID )) {
			case MOAITransform::ATTR_X_LOC: {
				float x = attrOp.Apply ( xform.p.x, op, MOAIAttrOp::ATTR_READ_WRITE ) * this->GetUnitsToMeters ();
				mBody->SetTransform ( b2Vec2( x, xform.p.y), xform.q.GetAngle() );
				return true;
			}

			case MOAITransform::ATTR_Y_LOC: {
				float y = attrOp.Apply ( xform.p.y, op, MOAIAttrOp::ATTR_READ_WRITE ) * this->GetUnitsToMeters ();
				mBody->SetTransform ( b2Vec2( xform.p.x, y ), xform.q.GetAngle() );
				return true;	
			}

			case MOAITransform::ATTR_Z_ROT: {
				float angle = attrOp.Apply ( xform.q.GetAngle(), op, MOAIAttrOp::ATTR_READ_WRITE );				
				mBody->SetTransform ( xform.p,  ( float )((angle * D2R) + M_PI_4 ));
				return true;	
			}


		}
	}*/
	//return MOAITransformBase::ApplyAttrOp (attrID, attrOp, op );
	return true;
}




//----------------------------------------------------------------//
void MOAIBulletBody::SetBody ( btRigidBody* body ) {
	this->mBody = body;
		//body->SetUserData ( this );
}
