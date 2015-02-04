#include "pch.h"

#include <bullet/src/btBulletDynamicsCommon.h>

#include <moai-bullet/MOAIBulletWorld.h>

#include <moai-bullet/MOAIBulletDebugDraw.h>

#include <moai-bullet/MOAIBulletBody.h>
#include <moai-bullet/MOAIBulletShape.h>

#include <moai-bullet/MOAIBulletJoint.h>
#include <moai-bullet/MOAIBulletJointCone.h>
#include <moai-bullet/MOAIBulletJointFixed.h>
#include <moai-bullet/MOAIBulletJointFreedom.h>
#include <moai-bullet/MOAIBulletJointHinge.h>
#include <moai-bullet/MOAIBulletJointPoint.h>
#include <moai-bullet/MOAIBulletJointSlide.h>




#include <moai-bullet/MOAIBulletTransform.h>

//********************************************************************************
//----------------------------------------------------------------//
float MOAIBulletPrim::GetUnitsToMeters () {
	if ( this->mWorld ) {
		//NO DONE
	}
	return 1.0f;
}

//----------------------------------------------------------------//
MOAIBulletPrim::MOAIBulletPrim () :
	mWorld ( 0 ),
	mDestroy ( false ),
	mDestroyNext ( 0 ) {
}
//----------------------------------------------------------------//
//CALLS TO CHECK TO ACTION IS DONE
bool MOAIBulletWorld::IsDone () {
	return false;
}

//----------------------------------------------------------------//
//RUNS STEP
void MOAIBulletWorld::OnUpdate ( float step ) {			
     mWorld->stepSimulation(1 / mStep, 10);	
};
//----------------------------------------------------------------//
//DEBUG DRAW
void MOAIBulletWorld::DrawDebug () {
	if ( this->mDebugDraw ) {	
		MOAIDraw::Bind ();	
		this->mDebugDraw->mSize = 0;

		MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();	
		gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_MODEL, MOAIGfxDevice::VTX_STAGE_PROJ );
		gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM );	
		gfxDevice.BeginPrim ( ZGL_PRIM_LINES );

				this->mDebugDraw->mScale = this->mDrawScale; //* //(30.0f/10.0f);
				this->mWorld->debugDrawWorld();

		gfxDevice.addDrawCount();
		gfxDevice.setPrimeSize(this->mDebugDraw->mSize*2);
		gfxDevice.EndPrim ();
	}
}


//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************


//----------------------------------------------------------------//
void MOAIBulletWorld::SayGoodbye ( btCompoundShape* shape) {

//NO USER DATA CONTAINER

	//MOAIBulletShape* moaiFixture = ( MOAIBulletShape* )fixture->GetUserData ();
	//if ( moaiFixture->mFixture ) {
	//	moaiFixture->mFixture = 0;
	//	moaiFixture->SetWorld ( 0 );
	//	this->LuaRelease ( moaiFixture );
	//}
}

//----------------------------------------------------------------//
void MOAIBulletWorld::SayGoodbye ( btTypedConstraint* joint ) {

//NO USER DATA CONTAINER

	//MOAIBulletJoint* moaiJoint = ( MOAIBulletJoint* )joint->GetUserData ();
	//if ( moaiJoint->mJoint ) {
	//		moaiJoint->mJoint = 0;
	//		moaiJoint->SetWorld ( 0 );
	//		this->LuaRelease ( moaiJoint );
	//}

}

//----------------------------------------------------------------//
void MOAIBulletWorld::ScheduleDestruction (MOAIBulletBody& body) {

	if ( !body.mDestroy ) {
		body.mDestroyNext = this->mDestroyBodies;
		this->mDestroyBodies = &body;
		body.mDestroy = true;
	}
	this->Destroy ();
}

//----------------------------------------------------------------//
void MOAIBulletWorld::ScheduleDestruction ( MOAIBulletShape& shape ) {

	if ( !shape.mDestroy ) {
		shape.mDestroyNext = this->mDestroyShapes;
		this->mDestroyShapes = &shape;
		shape.mDestroy = true;
	}
	this->Destroy ();
}

//----------------------------------------------------------------//
void MOAIBulletWorld::ScheduleDestruction (  MOAIBulletJoint& joint ) {

	if ( !joint.mDestroy ) {
		joint.mDestroyNext = this->mDestroyJoints;
		this->mDestroyJoints = &joint;
		joint.mDestroy = true;
	}
	this->Destroy ();
}

//----------------------------------------------------------------//
void MOAIBulletWorld::Destroy () {

	if ( this->mLock ) return;
	this->mLock = true;

	while ( this->mDestroyShapes ) {
		MOAIBulletPrim* prim = this->mDestroyShapes;
		this->mDestroyShapes = this->mDestroyShapes->mDestroyNext;
		prim->Destroy ();
		
		prim->SetWorld ( 0 );
		this->LuaRelease ( prim );
	}
	
	while ( this->mDestroyJoints ) {
		MOAIBulletPrim* prim = this->mDestroyJoints;
		this->mDestroyJoints = this->mDestroyJoints->mDestroyNext;
		prim->Destroy ();
		
		prim->SetWorld ( 0 );
		this->LuaRelease ( prim );
	}
	
	while ( this->mDestroyBodies ) {
		MOAIBulletPrim* prim = this->mDestroyBodies;
		this->mDestroyBodies = this->mDestroyBodies->mDestroyNext;
		prim->Destroy ();
		
		prim->SetWorld ( 0 );
		this->LuaRelease ( prim );
	}	
	this->mLock = false;
}
//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
MOAIBulletWorld::MOAIBulletWorld () :
    mCollisionConfiguration(0),
    mCollisionDispatcher(0),
    mBroadphase(0),
    mSolver(0),
    mWorld(0),
	mDrawScale(1),
	mDrawJointSize(1),
	mStep(60),
	mLock(false)
{

RTTI_BEGIN
	RTTI_EXTEND ( MOAIAction )			
RTTI_END

	mBroadphase				= new btDbvtBroadphase();	
	//LOWER MEMORY
	btDefaultCollisionConstructionInfo constructionInfo = btDefaultCollisionConstructionInfo();
	constructionInfo.m_defaultMaxCollisionAlgorithmPoolSize = 1023;
	constructionInfo.m_defaultMaxPersistentManifoldPoolSize = 1023;
	mCollisionConfiguration = new btDefaultCollisionConfiguration(constructionInfo);
	//collisionConfiguration_	= new btDefaultCollisionConfiguration();
	

	mCollisionDispatcher	= new btCollisionDispatcher(mCollisionConfiguration);
	mSolver					= new btSequentialImpulseConstraintSolver;
	mWorld					= new btDiscreteDynamicsWorld(mCollisionDispatcher, mBroadphase, mSolver, mCollisionConfiguration);

	mWorld->setGravity(btVector3(0, 0, 0));
	mWorld->getDispatchInfo().m_useContinuous	= true;
	mWorld->getSolverInfo().m_splitImpulse		= true; // Disable by default for performance
	//DEBUG
	mDebugDraw = new MOAIBulletDebugDraw ();
	mWorld->setDebugDrawer(this->mDebugDraw );	

};
//----------------------------------------------------------------//
MOAIBulletWorld::~MOAIBulletWorld () {
	delete mWorld;
    delete mSolver;
    delete mCollisionDispatcher;
    delete mCollisionConfiguration;
    delete mBroadphase;
	delete mDebugDraw;

};

//----------------------------------------------------------------//
//ADD SHAPE ??





//----------------------------------------------------------------//
int MOAIBulletWorld::_addBody ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UU" )	

//NEW CLASS
	MOAIBulletBody* body = new MOAIBulletBody ();	



//DOES SETTING THE MOATION WORK?
	MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >(2, true );
	if ( !( transA )) return 0;
	btTransform ta = *transA->mTransform;


//MASS
	btScalar mMass = 1.0;
//INERTIA
	btVector3 mInertia(0.0, 0.0, 0.0);


	//**************************************************************
	//**************************************************************
			btTransform transform;
			transform.setIdentity();
			transform.setOrigin(btVector3(btScalar(0.), btScalar(1.2), btScalar(0.)));
			btCollisionShape* shape = new btCapsuleShape(btScalar(0.15), btScalar(0.20));

			//btRigidBody::btRigidBodyConstructionInfo info(mMass,body->mMotion,shape,mInertia);  //create the constructioninfo, you can create multiple bodies with the same info
			//body->mBody = new btRigidBody(info);    //let's create the body itself

	//**************************************************************
	//**************************************************************

//COMMPOUD SHAPE SOESN:T WORK

	body->mMotion	= new btDefaultMotionState(transform);	
	body->mCompound = new btCompoundShape();   
	

	btRigidBody::btRigidBodyConstructionInfo info(mMass,body->mMotion,body->mCompound,mInertia);  
	body->mBody = new btRigidBody(info);  
	



	body->setWorld(self->mWorld);	
	self->LuaRetain ( body );
	body->PushLuaUserdata ( state );
	return 1;
}


//----------------------------------------------------------------//
int MOAIBulletWorld::_addJointHinge ( lua_State* L ) {

	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUUU" )	
	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );	

	if ( !( bodyA && bodyB )) return 0;

		MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >( 4, true );
		MOAIBulletTransform* transB = state.GetLuaObject < MOAIBulletTransform >( 5, true );

		if ( !( transA && transB )) return 0;

			btTransform ta = *transA->mTransform;
			btTransform tb = *transB->mTransform;


				//float a_x = state.GetValue < float >( 4, 0.0f );
				//float a_y = state.GetValue < float >( 5, 0.0f );
				//float a_z = state.GetValue < float >( 6, 0.0f );
				//float b_x = state.GetValue < float >( 7, 0.0f );
				//float b_y = state.GetValue < float >( 8, 0.0f );
				//float b_z = state.GetValue < float >( 9, 0.0f );
				//btTransform localA, localB;
				//localA.setIdentity(); 
				//localB.setIdentity();
				//localA.getBasis().setEulerZYX(0,M_PI_2,0); 
				//localA.setOrigin(btVector3(btScalar(a_x), btScalar(a_y), btScalar(a_z)));
				//localB.getBasis().setEulerZYX(0,M_PI_2,0); 
				//localB.setOrigin(btVector3(btScalar(b_x), btScalar(a_y), btScalar(a_z)));	
	


	btHingeConstraint*		hingeC;
	hingeC = new btHingeConstraint(*bodyA->mBody, *bodyB->mBody, ta, tb); //IS THIS A LEAK?

	//hingeC->setLimit(-M_PI_4, M_PI_2);

	hingeC->setDbgDrawSize(self->mDrawJointSize);
	self->mWorld->addConstraint(hingeC, true);	

	MOAIBulletJointHinge* mJoint = new MOAIBulletJointHinge (); //POINTER TO POINTER?
	mJoint->SetJoint(hingeC);
	mJoint->SetBodyA(bodyA);
	mJoint->SetBodyB(bodyB);
	//mJoint->setuserdata ?
	mJoint->SetWorld ( self );
	mJoint->LuaRetain ( bodyA );
	mJoint->LuaRetain ( bodyB );
	self->LuaRetain ( mJoint );
	mJoint->PushLuaUserdata ( state );
	return 1;
}

//----------------------------------------------------------------//
//SHOULD USE CONTRAINT CLASS NOT INDUVUAL CLASSES
int MOAIBulletWorld::_addJointCone ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUUU" )	

	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );
	
	if ( !( bodyA && bodyB )) return 0;


		MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >( 4, true );
		MOAIBulletTransform* transB = state.GetLuaObject < MOAIBulletTransform >( 5, true );

		if ( !( transA && transB )) return 0;

			btTransform ta = *transA->mTransform;
			btTransform tb = *transB->mTransform;

	//float a_x = state.GetValue < float >( 4, 0.0f );
	//float a_y = state.GetValue < float >( 5, 0.0f );
	//float a_z = state.GetValue < float >( 6, 0.0f );

	//float b_x = state.GetValue < float >( 7, 0.0f );
	//float b_y = state.GetValue < float >( 8, 0.0f );
	//float b_z = state.GetValue < float >( 9, 0.0f );

	//btTransform localA, localB;
	//localA.setIdentity(); 
	//localB.setIdentity();

	//localA.getBasis().setEulerZYX(0,M_PI_2,0); 
	//localA.setOrigin(btVector3(btScalar(a_x), btScalar(a_y), btScalar(a_z)));

	//localB.getBasis().setEulerZYX(0,M_PI_2,0); 
	//localB.setOrigin(btVector3(btScalar(b_x), btScalar(a_y), btScalar(a_z)));



	btConeTwistConstraint*	coneC;	
	coneC = new btConeTwistConstraint(*bodyA->mBody, *bodyB->mBody, ta, tb); //NEED TO MAKE JOINT SIZE
	coneC->setDbgDrawSize(self->mDrawJointSize);
	self->mWorld->addConstraint(coneC, true);

	//SET LIMIT
	//coneC->setLimit(M_PI_4, M_PI_4, M_PI_2);
	//coneC->setDbgDrawSize(self->mDrawJointSize);
	//coneC->setBreakingImpulseThreshold(100.0f);
	

	MOAIBulletJointCone* mJoint = new MOAIBulletJointCone (); //POINTER TO POINTER?
	mJoint->SetJoint(coneC);
	mJoint->SetBodyA(bodyA);
	mJoint->SetBodyB(bodyB);
	//mJoint->setuserdata ?
	mJoint->SetWorld ( self );
	mJoint->LuaRetain ( bodyA );
	mJoint->LuaRetain ( bodyB );
	self->LuaRetain ( mJoint );
	mJoint->PushLuaUserdata ( state );


	return 1;
};
//----------------------------------------------------------------//
//SHOULD USE CONTRAINT CLASS NOT INDUVUAL CLASSES
int MOAIBulletWorld::_addJointSlider ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUUUN" )	

	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );
	
	if ( !( bodyA && bodyB )) return 0;

		MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >( 4, true );
		MOAIBulletTransform* transB = state.GetLuaObject < MOAIBulletTransform >( 5, true );

		if ( !( transA && transB )) return 0;

			btTransform ta = *transA->mTransform;
			btTransform tb = *transB->mTransform;


	//float a_x = state.GetValue < float >( 4, 0.0f );
	//float a_y = state.GetValue < float >( 5, 0.0f );
	//float a_z = state.GetValue < float >( 6, 0.0f );

	//float b_x = state.GetValue < float >( 7, 0.0f );
	//float b_y = state.GetValue < float >( 8, 0.0f );
	//float b_z = state.GetValue < float >( 9, 0.0f );


	//btTransform localA, localB;
	//localA.setIdentity(); 
	//localB.setIdentity();

	//localA.getBasis().setEulerZYX(0,M_PI_2,0); 
	//localA.setOrigin(btVector3(btScalar(a_x), btScalar(a_y), btScalar(a_z)));

	//localB.getBasis().setEulerZYX(0,M_PI_2,0); 
	//localB.setOrigin(btVector3(btScalar(b_x), btScalar(a_y), btScalar(a_z)));


	bool joint_bool = state.GetValue < bool >( 6, false );

	btSliderConstraint*	sliderC;	
	sliderC = new btSliderConstraint(*bodyA->mBody, *bodyB->mBody, ta, tb,joint_bool); //ANOTHER ARGGUMENT
	sliderC->setDbgDrawSize(self->mDrawJointSize);
	self->mWorld->addConstraint(sliderC, true);

		//sliderC->setBreakingImpulseThreshold(100.0f);
		//sliderC->setLowerLinLimit(-15.0F);
		//sliderC->setUpperLinLimit(-5.0F);
		//sliderC->setLowerAngLimit(-SIMD_PI / 3.0F);
		//sliderC->setUpperAngLimit( SIMD_PI / 3.0F);
		//self->mWorld->addConstraint(sliderC, true);


	MOAIBulletJointSlide* mJoint = new MOAIBulletJointSlide (); //POINTER TO POINTER?
	mJoint->SetJoint(sliderC);
	mJoint->SetBodyA(bodyA);
	mJoint->SetBodyB(bodyB);
	//mJoint->setuserdata ?
	mJoint->SetWorld ( self );
	mJoint->LuaRetain ( bodyA );
	mJoint->LuaRetain ( bodyB );
	self->LuaRetain ( mJoint );
	mJoint->PushLuaUserdata ( state );

	
	return 1;
};
//----------------------------------------------------------------//
//SHOULD USE CONTRAINT CLASS NOT INDUVUAL CLASSES
int MOAIBulletWorld::_addJointFreedom ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUUUN" )	

	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );
	
	if ( !( bodyA && bodyB )) return 0;

		MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >( 4, true );
		MOAIBulletTransform* transB = state.GetLuaObject < MOAIBulletTransform >( 5, true );

		if ( !( transA && transB )) return 0;

			btTransform ta = *transA->mTransform;
			btTransform tb = *transB->mTransform;



	//float a_x = state.GetValue < float >( 4, 0.0f );
	//float a_y = state.GetValue < float >( 5, 0.0f );
	//float a_z = state.GetValue < float >( 6, 0.0f );

	//float b_x = state.GetValue < float >( 7, 0.0f );
	//float b_y = state.GetValue < float >( 8, 0.0f );
	//float b_z = state.GetValue < float >( 9, 0.0f );

	//

	//btTransform localA, localB;
	//localA.setIdentity(); 
	//localB.setIdentity();
	//
	//localA.getBasis().setEulerZYX(0,M_PI_2,0); 
	//localA.setOrigin(btVector3(btScalar(a_x), btScalar(a_y), btScalar(a_z)));

	//localB.getBasis().setEulerZYX(0,M_PI_2,0); 
	//localB.setOrigin(btVector3(btScalar(b_x), btScalar(a_y), btScalar(a_z)));





	bool joint_bool = state.GetValue < bool >( 5, false );


	btGeneric6DofConstraint*	freeDomeC;	
	freeDomeC = new btGeneric6DofConstraint(*bodyA->mBody, *bodyB->mBody, ta, tb,joint_bool); //ANOTHER ARGGUMENT
	freeDomeC->setDbgDrawSize(self->mDrawJointSize);
	self->mWorld->addConstraint(freeDomeC, true);


	freeDomeC->setBreakingImpulseThreshold(100.0f);

	btTransform sliderTransform;
	btVector3 lowerSliderLimit = btVector3(-10,0,0);
	btVector3 hiSliderLimit = btVector3(10,0,0);

	freeDomeC->setLinearLowerLimit(lowerSliderLimit);
	freeDomeC->setLinearUpperLimit(hiSliderLimit);
	freeDomeC->setAngularLowerLimit(btVector3(-SIMD_PI,0,0));
	freeDomeC->setAngularUpperLimit(btVector3(1.5,0,0));

	freeDomeC->getTranslationalLimitMotor()->m_enableMotor[0] = true;
	freeDomeC->getTranslationalLimitMotor()->m_targetVelocity[0] = -5.0f;
	freeDomeC->getTranslationalLimitMotor()->m_maxMotorForce[0] = 0.1f;
	


	MOAIBulletJointFreedom* mJoint = new MOAIBulletJointFreedom (); //POINTER TO POINTER?
	mJoint->SetJoint(freeDomeC);
	mJoint->SetBodyA(bodyA);
	mJoint->SetBodyB(bodyB);
	//mJoint->setuserdata ?
	mJoint->SetWorld ( self );
	mJoint->LuaRetain ( bodyA );
	mJoint->LuaRetain ( bodyB );
	self->LuaRetain ( mJoint );
	mJoint->PushLuaUserdata ( state );





//btGeneric6DofSpringConstraint* pGen6DOFSpring = new btGeneric6DofSpringConstraint(*pBodyA, *pBodyB, frameInA, frameInB, true);
//pGen6DOFSpring->setLinearUpperLimit(btVector3(5., 0., 0.));
//pGen6DOFSpring->setLinearLowerLimit(btVector3(-5., 0., 0.));
//pGen6DOFSpring->setAngularLowerLimit(btVector3(0.f, 0.f, -1.5f));
//pGen6DOFSpring->setAngularUpperLimit(btVector3(0.f, 0.f, 1.5f));
//m_dynamicsWorld->addConstraint(pGen6DOFSpring, true);
//pGen6DOFSpring->setDbgDrawSize(btScalar(5.f));
//pGen6DOFSpring->enableSpring(0, true);
//pGen6DOFSpring->setStiffness(0, 39.478f);
//pGen6DOFSpring->setDamping(0, 0.5f);
//pGen6DOFSpring->enableSpring(5, true);
//pGen6DOFSpring->setStiffness(5, 39.478f);
//pGen6DOFSpring->setDamping(0, 0.3f);
//pGen6DOFSpring->setEquilibriumPoint();


	return 1;
};
//----------------------------------------------------------------//
//SHOULD USE CONTRAINT CLASS NOT INDUVUAL CLASSES
int MOAIBulletWorld::_addJointFixed ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUUUN" )	

	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );
	
	if ( !( bodyA && bodyB )) return 0;

		MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >( 4, true );
		MOAIBulletTransform* transB = state.GetLuaObject < MOAIBulletTransform >( 5, true );

		if ( !( transA && transB )) return 0;

			btTransform ta = *transA->mTransform;
			btTransform tb = *transB->mTransform;



	//float a_x = state.GetValue < float >( 4, 0.0f );
	//float a_y = state.GetValue < float >( 5, 0.0f );
	//float a_z = state.GetValue < float >( 6, 0.0f );

	//float b_x = state.GetValue < float >( 7, 0.0f );
	//float b_y = state.GetValue < float >( 8, 0.0f );
	//float b_z = state.GetValue < float >( 9, 0.0f );

	//btTransform localA, localB;
	//localA.setIdentity(); 
	//localB.setIdentity();
	
	//localA.getBasis().setEulerZYX(0,M_PI_2,0); 
	//localA.setOrigin(btVector3(btScalar(a_x), btScalar(a_y), btScalar(a_z)));

	//localB.getBasis().setEulerZYX(0,M_PI_2,0); 
	//localB.setOrigin(btVector3(btScalar(b_x), btScalar(a_y), btScalar(a_z)));







	btFixedConstraint*	fixedC;	
	fixedC = new btFixedConstraint(*bodyA->mBody, *bodyB->mBody, ta, tb); //ANOTHER ARGGUMENT
	fixedC->setDbgDrawSize(self->mDrawJointSize);
	self->mWorld->addConstraint(fixedC, true);

	//fixedC->setBreakingImpulseThreshold(100.0f);
	//self->mWorld->addConstraint(fixedC, true);

	MOAIBulletJointFixed* mJoint = new MOAIBulletJointFixed (); //POINTER TO POINTER?
	mJoint->SetJoint(fixedC);
	mJoint->SetBodyA(bodyA);
	mJoint->SetBodyB(bodyB);
	//mJoint->setuserdata ?
	mJoint->SetWorld ( self );
	mJoint->LuaRetain ( bodyA );
	mJoint->LuaRetain ( bodyB );
	self->LuaRetain ( mJoint );
	mJoint->PushLuaUserdata ( state );






	return 1;
};


//----------------------------------------------------------------//
//NEEDS PIVOT OBJECT
//SHOULD USE CONTRAINT CLASS NOT INDUVUAL CLASSES
int MOAIBulletWorld::_addJointPoint ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUNNNNNN" )	

	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );
	
	if ( !( bodyA && bodyB )) return 0;

	float a_x = state.GetValue < float >( 4, 0.0f );
	float a_y = state.GetValue < float >( 5, 0.0f );
	float a_z = state.GetValue < float >( 6, 0.0f );

	float b_x = state.GetValue < float >( 7, 0.0f );
	float b_y = state.GetValue < float >( 8, 0.0f );
	float b_z = state.GetValue < float >( 9, 0.0f );

	btVector3 pivotInA(a_x,a_y,a_z);
	btVector3 pivotInB(b_x,b_y,b_z);

	btPoint2PointConstraint*	PointC;	
	PointC = new btPoint2PointConstraint(*bodyA->mBody, *bodyB->mBody, pivotInA, pivotInB); //ANOTHER ARGGUMENT
	PointC->setDbgDrawSize(self->mDrawJointSize); //DOESN'T DRAW? 
	self->mWorld->addConstraint(PointC, true);

	//PointC->setBreakingImpulseThreshold(100.0f);

	MOAIBulletJointPoint* mJoint = new MOAIBulletJointPoint (); //POINTER TO POINTER?
	mJoint->SetJoint(PointC);
	mJoint->SetBodyA(bodyA);
	mJoint->SetBodyB(bodyB);
	//mJoint->setuserdata ?
	mJoint->SetWorld ( self );
	mJoint->LuaRetain ( bodyA );
	mJoint->LuaRetain ( bodyB );
	self->LuaRetain ( mJoint );
	mJoint->PushLuaUserdata ( state );





	return 1;
};













//----------------------------------------------------------------//
int MOAIBulletWorld::_setStep ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )
	float step = state.GetValue < float >( 2, 60.0f );
	self->mStep = step;	
	return 1;
}
//----------------------------------------------------------------//

int MOAIBulletWorld::_setGravity ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )	
	float gravity_x = state.GetValue < float >( 2, 0.0f );
	float gravity_y = state.GetValue < float >( 3, 0.0f );
	float gravity_z = state.GetValue < float >( 4, 0.0f );
	self->mWorld->setGravity(btVector3(gravity_x, gravity_y, gravity_z));
	return 1;
};
//----------------------------------------------------------------//

int MOAIBulletWorld::_useContinuous ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )
	bool continous = state.GetValue < bool >( 2, true );
	self->mWorld->getDispatchInfo().m_useContinuous	= continous;
	return 0;
}
//----------------------------------------------------------------//

int MOAIBulletWorld::_splitImpulse ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )
	bool impluse = state.GetValue < bool >( 2, true );
	///NOT SURE WHY EXMAPLE SHOWS BOOLEAN BECAUSE IT WANTS AN INTEGER
	self->mWorld->getSolverInfo().m_splitImpulse		= impluse;	
	return 0;
}
//----------------------------------------------------------------//

int MOAIBulletWorld::_Iterations ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )	
	int iterations = state.GetValue < int >( 2, 4 );
	btContactSolverInfo& info = self->mWorld->getSolverInfo();
	info.m_numIterations = iterations;
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_setDrawScale ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )	
	float drawScale = state.GetValue < float >( 2, 1.0f );
	self->mDrawScale = drawScale;
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_setDrawJointSize ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )	
	float drawSize = state.GetValue < float >( 2, 1.0f );
	self->mDrawJointSize = drawSize;
	return 1;
}
//----------------------------------------------------------------//
void MOAIBulletWorld::RegisterLuaClass ( MOAILuaState& state ) {
	MOAIAction::RegisterLuaClass ( state );		
	state.SetField ( -1, "COMPOUND_SHAPE", ( u32 )1 );
}
//----------------------------------------------------------------//
void MOAIBulletWorld::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAIAction::RegisterLuaFuncs ( state );
	luaL_Reg regTable [] = {
//BODY
		{ "addBody",					_addBody }, 

//JOINTS : NO REENTION : GOING TO TRY TO USE CHIPMUNKS LAYOUT
		{ "addJointHinge",				_addJointHinge }, //isCLass
		{ "addJointCone",				_addJointCone }, //isCLass
		{ "addJointFixed",				_addJointFixed }, //isCLass
		{ "addJointPoint",				_addJointPoint }, //isCLass
		{ "addJointSlider",				_addJointSlider }, //isCLass
		{ "addJointFreedom",			_addJointFreedom }, //isCLass

//HINGE
		{ "setDrawScale",				_setDrawScale },
		{ "setDrawJointSize",			_setDrawJointSize },
		{ "setStep",					_setStep },
		{ "setGravity",					_setGravity },
		{ "useContinuous",				_useContinuous },
		{ "splitImpulse",				_splitImpulse },
		{ "Iterations",					_Iterations },	
		{ NULL, NULL }
	};	
	luaL_register ( state, 0, regTable );
}
