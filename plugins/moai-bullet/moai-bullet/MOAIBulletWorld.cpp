#include "pch.h"
//I THINK I NEED TO MAKE VERY MANUAL

//1. HOW TO REMOVE JOINTS ???
//2. HOW TO ADD JOINTS ???
//3. WHY ARE PLANES ON RIGID BODIES THEY NEED TO BE JUST SHAPES ???

// NEW BODY  ?
// NEW SHAPE ?
// body add shape

//WILL ADD TO LUA ? OT FIELDS PERHAPS? OR WORLD
//#define ACTIVE_TAG 1
//#define ISLAND_SLEEPING 2
//#define WANTS_DEACTIVATION 3
//#define DISABLE_DEACTIVATION 4
//#define DISABLE_SIMULATION 5


//WTF
#include <bullet/src/LinearMath/btQuickprof.h>


#include <moai-bullet/MOAIBulletTest.h>
#include <moai-bullet/MOAIBulletWorld.h>
#include <moai-bullet/MOAIBulletDebugDraw.h>
#include <moai-bullet/MOAIBulletCollisionHandler.h>


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
bool MOAIBulletWorld::IsDone () {
	return false;
}


//************************************************************************************************//
//************************************************************************************************//
//************************************************************************************************//
//************************************************************************************************//
//************************************************************************************************//
//FROM MOAI ACTION
void MOAIBulletWorld::OnUpdate ( float step ) {			
     mWorld->stepSimulation( mStep, mMaxSubSteps);	
	//UPDATE ALL OBJECTS
	for (int j=mWorld->getNumCollisionObjects()-1; j>=0 ;j--){	
		btCollisionObject* obj = mWorld->getCollisionObjectArray()[j];
		btRigidBody* body = btRigidBody::upcast(obj);

		//ACTIVE AND AWAKE THE SAME THING?
			if ( body->isActive()) {
				if (body && body->getMotionState())
				{								
						//FIX FOR RAG DOLLS
						MOAIBulletBody* moaiBody = ( MOAIBulletBody* )body->getUserPointer (); //HAD TO ADD TO BULLET
						if (moaiBody) {
							moaiBody->ScheduleUpdate ();
						}
				};
			
			};	
	};



					//***************************************************************************************************
					//***************************************************************************************************
					//***************************************************************************************************
					//COLLISION MANIFOLDS
					 /*  int numManifolds = mWorld->getDispatcher()->getNumManifolds();
						for (int i=0;i<numManifolds;i++)
						{
							btPersistentManifold* contactManifold =  mWorld->getDispatcher()->getManifoldByIndexInternal(i);
							btCollisionObject* obA =  const_cast<btCollisionObject*>(contactManifold->getBody0());
							btCollisionObject* obB =  const_cast<btCollisionObject*>(contactManifold->getBody1());

							int numContacts = contactManifold->getNumContacts();
							for (int j=0;j<numContacts;j++)
							{
								btManifoldPoint& pt = contactManifold->getContactPoint(j);
								if (pt.getDistance()<0.f)
								{
									printf("objects \n");
							CALL TO LUA
									btRigidBody* rigBodyA = ( btRigidBody* )obA;
									btRigidBody* rigBodyB = ( btRigidBody* )obB;

									MOAIBulletBody* moaiBodyA = ( MOAIBulletBody* )rigBodyA->getUserPointer (); 				
									MOAIBulletBody* moaiBodyB = ( MOAIBulletBody* )rigBodyB->getUserPointer (); 			

									WHY IS I ON B
									moaiBodyB->HandleCollision ( 1, moaiBodyA,moaiBodyB );

									printf("COLLISION\n");
									const btVector3& ptA = pt.getPositionWorldOnA();
									const btVector3& ptB = pt.getPositionWorldOnB();
									const btVector3& normalOnB = pt.m_normalWorldOnB;

								}
							}
						}*/
					//***************************************************************************************************
					//***************************************************************************************************
					//***************************************************************************************************
};

//----------------------------------------------------------------//
void MOAIBulletWorld::SayGoodbye ( btCompoundShape* shape) {

		MOAIBulletShape* moaishape = ( MOAIBulletShape* )shape->getUserPointer();
		if ( moaishape->mShape ) {
			moaishape->mShape = 0;
			moaishape->SetWorld ( 0 );
			this->LuaRelease ( moaishape );
		}
}

//----------------------------------------------------------------//
void MOAIBulletWorld::SayGoodbye ( btTypedConstraint* joint ) {

	MOAIBulletJoint* moaiJoint = ( MOAIBulletJoint* )joint->getUserConstraintPtr();
	if ( moaiJoint->mJoint ) {
			moaiJoint->mJoint = 0;
			moaiJoint->SetWorld ( 0 );
			this->LuaRelease ( moaiJoint );
	}

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
//I DON'T UNDERSTAND HOW THIS WORKS ???
//THIS IS CALLED FROM THE SECHDUAL DES

void MOAIBulletWorld::Destroy () {
	printf("\nMOAIBulletWorld::Destroy\n");

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




//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//CREATE



//----------------------------------------------------------------//
int MOAIBulletWorld::_create( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )

	self->mBroadphase				= new btDbvtBroadphase();	
	self->mCollisionConfiguration	= new btDefaultCollisionConfiguration(self->mConstructionInfo);
	self->mCollisionDispatcher		= new btCollisionDispatcher(self->mCollisionConfiguration);
	self->mSolver					= new btSequentialImpulseConstraintSolver;
	self->mWorld					= new btDiscreteDynamicsWorld(self->mCollisionDispatcher, self->mBroadphase, self->mSolver, self->mCollisionConfiguration);

	//*********************************************************
	//SWEEPING ???
		//const btVector3 worldAabbMin( -1000.0, -1000.0, -1000.0 );
		//const btVector3 worldAabbMax( 1000.0, 1000.0, 1000.0 );
		//btBroadphaseInterface = new btAxisSweep3(worldAabbMin, worldAabbMax, 1638 );

	//GRAVITY
		self->mWorld->setGravity(btVector3(0, 0, 0));
	
	//SOLVER
		self->mWorld->getSolverInfo().m_splitImpulse			= false; // Disable by default for performance

	//DISPATCH
		self->mWorld->getDispatchInfo().m_useContinuous			= false;
		self->mWorld->getDispatchInfo().m_enableSPU				= false;
		self->mWorld->getDispatchInfo().m_allowedCcdPenetration = 0.00f;
		self->mWorld->getDispatchInfo().m_stepCount  =100;
	return 1;
}

//----------------------------------------------------------------//
MOAIBulletWorld::MOAIBulletWorld () :
    mCollisionConfiguration(0),
    mCollisionDispatcher(0),
	mDebugDraw(0),
    mBroadphase(0),
    mSolver(0),
    mWorld(0),
	mCollision(0),
	mDrawScale(1),
	mDrawJointSize(1),
	mStep(1/60),
	mMaxSubSteps(10),
	mLock(false)

{

RTTI_BEGIN
	RTTI_EXTEND ( MOAIAction )			
RTTI_END

	//LOWER MEMORY FOOT PRINT ?????
	 this->mConstructionInfo		=  btDefaultCollisionConstructionInfo();
				//mConstructionInfo.m_defaultMaxCollisionAlgorithmPoolSize = 1023;
				//mConstructionInfo.m_defaultMaxPersistentManifoldPoolSize = 1023;	
				//m_defaultMaxPersistentManifoldPoolSize( 1638 ), //65536
				//m_defaultMaxCollisionAlgorithmPoolSize( 1638 ), //65536
				//m_defaultStackAllocatorSize( 131072 ) // 5 * 1024 * 1024


};
//----------------------------------------------------------------//
MOAIBulletWorld::~MOAIBulletWorld () {
	printf("\nMOAIBulletWorld::~MOAIBulletWorld\n");

	//THIS IS BODY NEEDS TO GET ALL SHAPES TO DELETE
	if (this->mWorld) {
			int i;

			for (i=this->mWorld->getNumCollisionObjects()-1; i>=0 ;i--)
			{
				//btCollisionObject* obj = this->mWorld->getCollisionObjectArray()[i];
				//btRigidBody* body = btRigidBody::upcast(obj);
				//if (body && body->getMotionState())
				//{
				//	delete body->getMotionState();
				//}
				//this->mWorld->removeCollisionObject( obj );
				//delete obj;
			}
	};



	if (this->mWorld) {
		delete mWorld;
	};

	if (this->mSolver) {
		delete mSolver;
	}

	if (this->mCollisionDispatcher) {
		delete mCollisionDispatcher;
	}

	if (this->mCollisionConfiguration) {
		delete mCollisionConfiguration;
	}

	if (this->mBroadphase) {
		delete mBroadphase;
	}

	if (this->mCollision) {	
		delete mCollision;
	};


	if (this->mDebugDraw) {
		delete mDebugDraw;
	}





	//this->Destroy ();
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_newBody ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UU" )	

	MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >(2, true );
	if ( !( transA )) return 0;
	btTransform ta = *transA->mTransform;

	//RESET VALUES	

	//NEW CLASS
		MOAIBulletBody* body = new MOAIBulletBody ();	
	//MASS
		btScalar mMass = 1.0;
	//INERTIA
		btVector3 mInertia(0.0, 0.0, 0.0);
	//MOTION & COMPOIND
		body->mMotion	= new btDefaultMotionState(ta);	
		body->mCompound = new btCompoundShape();   	

//printf("TRACE 1. btDefaultMotionState \n");
//printf("TRACE 2. btCompoundShape \n");
//printf("TRACE 3. btRigidBodyConstructionInfo \n");

	btRigidBody::btRigidBodyConstructionInfo info(mMass,body->mMotion,body->mCompound,mInertia);  
	
	//*********************************************************
	//*********************************************************
	//*********************************************************
	//*********************************************************
			//body->mBody = new btRigidBody(info); //DOESN'T WORK
			//static_cast <btRigidBodyWithEvents*> (body->mBody)->setMonitorCollisions(true); 
			//static_cast <btRigidBodyWithEvents*>(body->mBody)->setMonitorCollisions(true);
			//body->mBody->setMonitorCollisions(true);	

	//*********************************************************
	//*********************************************************
	//*********************************************************
	//*********************************************************
	
	body->mBody = new btRigidBody(info);

	body->setWorld(self->mWorld);	
	body->SetBody(body->mBody);
	self->LuaRetain ( body );
	body->PushLuaUserdata ( state );
	return 1;
}




//----------------------------------------------------------------//
int MOAIBulletWorld::_addJointHinge ( lua_State* L ) {	
//DISSABLE COLLISION BETWEEN BODIES --> self->mWorld->addConstraint(btJoint, false);
//USE FRAME A						--> btHingeConstraint(*bodyA->mBody, *bodyB->mBody, ta, tb);


	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUUUB" )	


	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );
	
	if ( !( bodyA && bodyB )) return 0;


		MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >( 4, true );
		MOAIBulletTransform* transB = state.GetLuaObject < MOAIBulletTransform >( 5, true );

		if ( !( transA && transB )) return 0;

			bool joint_bool = state.GetValue < bool >( 6, false );

			btTransform ta = *transA->mTransform;
			btTransform tb = *transB->mTransform;

			btHingeConstraint* btJoint = new btHingeConstraint(*bodyA->mBody, *bodyB->mBody, ta, tb,joint_bool);
			btJoint->setDbgDrawSize(self->mDrawJointSize);	

			MOAIBulletJointHinge* mJoint = new MOAIBulletJointHinge (); 

			mJoint->SetJoint(btJoint); 	 // HERE SETS --> btJoint->setUserConstraintPtr(mJoint); 


			mJoint->SetBodyA(bodyA);
			mJoint->SetBodyB(bodyB);
			mJoint->SetWorld ( self->mWorld );

			mJoint->LuaRetain ( bodyA );
			mJoint->LuaRetain ( bodyB );

			self->LuaRetain ( mJoint );
			mJoint->PushLuaUserdata ( state );

	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_addJointCone ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUUUB" )	
	
	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );

		if ( !( bodyA && bodyB )) return 0;

		MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >( 4, true );
		MOAIBulletTransform* transB = state.GetLuaObject < MOAIBulletTransform >( 5, true );

			if ( !( transA && transB )) return 0;

				//NOT USED
				bool joint_bool = state.GetValue < bool >( 6, false );

				btTransform ta = *transA->mTransform;
				btTransform tb = *transB->mTransform;

				btConeTwistConstraint* btJoint = new btConeTwistConstraint(*bodyA->mBody, *bodyB->mBody, ta, tb);
				btJoint->setDbgDrawSize(self->mDrawJointSize);

				MOAIBulletJointCone* mJoint = new MOAIBulletJointCone ();
				mJoint->SetJoint(btJoint);  // HERE SETS --> btJoint->setUserConstraintPtr(mJoint); 

				mJoint->SetBodyA(bodyA);
				mJoint->SetBodyB(bodyB);
				mJoint->SetWorld ( self->mWorld );

				mJoint->LuaRetain ( bodyA );
				mJoint->LuaRetain ( bodyB );
			

				self->LuaRetain ( mJoint );
				mJoint->PushLuaUserdata ( state );


	return 1;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_addJointSlider ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUUUB" )	

	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );
	
	if ( !( bodyA && bodyB )) return 0;

		MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >( 4, true );
		MOAIBulletTransform* transB = state.GetLuaObject < MOAIBulletTransform >( 5, true );

		if ( !( transA && transB )) return 0;

			btTransform ta = *transA->mTransform;
			btTransform tb = *transB->mTransform;

			bool joint_bool = state.GetValue < bool >( 6, false );

			btSliderConstraint*	 btJoint = new btSliderConstraint(*bodyA->mBody, *bodyB->mBody, ta, tb,joint_bool); 
			btJoint->setDbgDrawSize(self->mDrawJointSize);

			MOAIBulletJointSlide* mJoint = new MOAIBulletJointSlide (); 
			mJoint->SetJoint(btJoint); // HERE SETS --> btJoint->setUserConstraintPtr(mJoint); 

			mJoint->SetBodyA(bodyA);
			mJoint->SetBodyB(bodyB);
			mJoint->SetWorld ( self->mWorld );

			mJoint->LuaRetain ( bodyA );
			mJoint->LuaRetain ( bodyB );	

			self->LuaRetain ( mJoint );
			mJoint->PushLuaUserdata ( state );



//*******************************************************************
//*******************************************************************

		//sliderC->setBreakingImpulseThreshold(100.0f);
		//sliderC->setLowerLinLimit(-15.0F);
		//sliderC->setUpperLinLimit(-5.0F);
		//sliderC->setLowerAngLimit(-SIMD_PI / 3.0F);
		//sliderC->setUpperAngLimit( SIMD_PI / 3.0F);
		//self->mWorld->addConstraint(sliderC, true);

//*******************************************************************
//*******************************************************************




	
	return 1;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_addJointFreedom ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUUUB" )	


	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );
	
	if ( !( bodyA && bodyB )) return 0;

		MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >( 4, true );
		MOAIBulletTransform* transB = state.GetLuaObject < MOAIBulletTransform >( 5, true );

		if ( !( transA && transB )) return 0;

			bool joint_bool = state.GetValue < bool >( 6, false );

			btTransform ta = *transA->mTransform;
			btTransform tb = *transB->mTransform;		
	
			btGeneric6DofConstraint* btJoint = new btGeneric6DofConstraint(*bodyA->mBody, *bodyB->mBody, ta, tb,joint_bool); //ANOTHER ARGGUMENT
			btJoint->setDbgDrawSize(self->mDrawJointSize);

			MOAIBulletJointFreedom* mJoint = new MOAIBulletJointFreedom (); 

			mJoint->SetJoint(btJoint);  // HERE SETS --> btJoint->setUserConstraintPtr(mJoint); 

			mJoint->SetBodyA(bodyA);
			mJoint->SetBodyB(bodyB);

			mJoint->SetWorld ( self->mWorld );
			mJoint->LuaRetain ( bodyA );
			mJoint->LuaRetain ( bodyB );

			self->LuaRetain ( mJoint );
			mJoint->PushLuaUserdata ( state );



//*******************************************************************
//*******************************************************************
	btJoint->setBreakingImpulseThreshold(100.0f);
	btTransform sliderTransform;
	btVector3 lowerSliderLimit		= btVector3(-10,0,0);
	btVector3 hiSliderLimit			= btVector3(10,0,0);

	btJoint->setLinearLowerLimit(lowerSliderLimit);
	btJoint->setLinearUpperLimit(hiSliderLimit);
	btJoint->setAngularLowerLimit(btVector3(-SIMD_PI,0,0));
	btJoint->setAngularUpperLimit(btVector3(1.5,0,0));

	btJoint->getTranslationalLimitMotor()->m_enableMotor[0]		= true;
	btJoint->getTranslationalLimitMotor()->m_targetVelocity[0]	= -5.0f;
	btJoint->getTranslationalLimitMotor()->m_maxMotorForce[0]	= 0.1f;

//*******************************************************************
//*******************************************************************



//***********************************************************************
//***********************************************************************

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
int MOAIBulletWorld::_addJointFixed ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUUU" )	
		

	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );
		
	if ( !( bodyA && bodyB )) return 0;

		MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >( 4, true );
		MOAIBulletTransform* transB = state.GetLuaObject < MOAIBulletTransform >( 5, true );

		if ( !( transA && transB )) return 0;

			//NOT USED
			bool joint_bool = state.GetValue < bool >( 6, false );

			btTransform ta = *transA->mTransform;
			btTransform tb = *transB->mTransform;
	
			btFixedConstraint* btJoint = new btFixedConstraint(*bodyA->mBody, *bodyB->mBody, ta, tb); 
			btJoint->setDbgDrawSize(self->mDrawJointSize);

			MOAIBulletJointFixed* mJoint = new MOAIBulletJointFixed (); 

			mJoint->SetJoint(btJoint);  // HERE SETS --> btJoint->setUserConstraintPtr(mJoint); 

			mJoint->SetBodyA(bodyA);
			mJoint->SetBodyB(bodyB);
			mJoint->SetWorld ( self->mWorld );

			mJoint->LuaRetain ( bodyA );
			mJoint->LuaRetain ( bodyB );

			self->LuaRetain ( mJoint );
			mJoint->PushLuaUserdata ( state );

	return 1;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_addJointPoint ( lua_State* L ) {
//PIGGY BACK OFF TRANSFORM ??
//REQURES VEC3?

	
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUUUB" )

	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );
	
	if ( !( bodyA && bodyB )) return 0;

	//float a_x = state.GetValue < float >( 4, 0.0f );
	//float a_y = state.GetValue < float >( 5, 0.0f );
	//float a_z = state.GetValue < float >( 6, 0.0f );

	//float b_x = state.GetValue < float >( 7, 0.0f );
	//float b_y = state.GetValue < float >( 8, 0.0f );
	//float b_z = state.GetValue < float >( 9, 0.0f );
	//if ( !( bodyA && bodyB )) return 0;

		MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >( 4, true );
		MOAIBulletTransform* transB = state.GetLuaObject < MOAIBulletTransform >( 5, true );

		if ( !( transA && transB )) return 0;

		btTransform* mTransformA = ( btTransform* )transA->mTransform;
		btTransform* mTransformB = ( btTransform* )transB->mTransform;

		btVector3 pivotInA = mTransformA->getOrigin();
		btVector3 pivotInB = mTransformB->getOrigin();

		//printf("%f %f %f \n",mTransformA->getOrigin().x(),mTransformA->getOrigin().y(),mTransformA->getOrigin().z());
		//printf("%f %f %f \n",mTransformA->getOrigin().x(),mTransformA->getOrigin().getY(),mTransformA->getOrigin().getZ());
		

	btPoint2PointConstraint*	btJoint = new btPoint2PointConstraint(*bodyA->mBody, *bodyB->mBody, pivotInA, pivotInB); 
	btJoint->setDbgDrawSize(self->mDrawJointSize);

	MOAIBulletJointPoint* mJoint = new MOAIBulletJointPoint (); 

	mJoint->SetJoint(btJoint); 	 // HERE SETS --> btJoint->setUserConstraintPtr(mJoint); 

	mJoint->SetBodyA(bodyA);
	mJoint->SetBodyB(bodyB);
	mJoint->SetWorld ( self->mWorld );

	mJoint->LuaRetain ( bodyA );
	mJoint->LuaRetain ( bodyB );

	self->LuaRetain ( mJoint );
	mJoint->PushLuaUserdata ( state );

	return 1;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_setStep ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )
	float step = state.GetValue < float >( 2, 1.0f/60.0f );
	self->mStep = step;	
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_setMaxSubSteps ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )
	int step = state.GetValue < int >( 2, 10 );
	self->mMaxSubSteps = step;	
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_setGravity ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )	
	float gravity_x = state.GetValue < float >( 2, 0.0f );
	float gravity_y = state.GetValue < float >( 3, 0.0f );
	float gravity_z = state.GetValue < float >( 4, 0.0f );
	self->mWorld->setGravity(btVector3(gravity_x, gravity_y, gravity_z));
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_setForceUpdateAllAabbs ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )
	bool forceUpdate = state.GetValue < bool >( 2, true );
	self->mWorld->setForceUpdateAllAabbs(forceUpdate);
	return 1;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_defaultMaxCollisionAlgorithmPoolSize ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )
	int defaultMaxCollisionAlgorithmPoolSize = state.GetValue < int >( 2, 0 );
	self->mConstructionInfo.m_defaultMaxCollisionAlgorithmPoolSize = defaultMaxCollisionAlgorithmPoolSize;
	return 0;	
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_defaultMaxPersistentManifoldPoolSize ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )
	int defaultMaxCollisionAlgorithmPoolSize = state.GetValue < int >( 2, 0 );
	self->mConstructionInfo.m_defaultMaxPersistentManifoldPoolSize = defaultMaxCollisionAlgorithmPoolSize;
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_useContinuous ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )
	bool continous = state.GetValue < bool >( 2, true );
	self->mWorld->getDispatchInfo().m_useContinuous	= continous;
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_enableSPU	( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )
	bool spu = state.GetValue < bool >( 2, true );
	self->mWorld->getDispatchInfo().m_enableSPU	= spu;
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_allowedCcdPenetration	( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )
	float pen = state.GetValue < float >( 2, 0.0f );
	self->mWorld->getDispatchInfo().m_allowedCcdPenetration	= pen;
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
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_setDrawScale ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )	
	float drawScale = state.GetValue < float >( 2, 1.0f );
	self->mDrawScale = drawScale;
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_setDrawJointSize ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )	
	float drawSize = state.GetValue < float >( 2, 1.0f );
	self->mDrawJointSize = drawSize;
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_DrawDebugLua ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )	
		if ( self->mDebugDraw ) {	
		MOAIDraw::Bind ();	

		self->mDebugDraw->mSize = 0;
		MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();	

			gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_MODEL, MOAIGfxDevice::VTX_STAGE_PROJ );
			gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM );	
			gfxDevice.BeginPrim ( ZGL_PRIM_LINES );

		self->mDebugDraw->mScale = self->mDrawScale; 
		self->mWorld->debugDrawWorld();

		gfxDevice.GetDrawCount();

		gfxDevice.setPrimeSize(self->mDebugDraw->mSize*2);
		gfxDevice.EndPrim ();
	}

	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_forceStep ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )	
		self->OnUpdate(0);
		return 0;
};

//----------------------------------------------------------------//
int MOAIBulletWorld::_addCollisionObject ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )	
		//self->mWorld->addCollisionObject(); ///WHAT THE FUCK ???
		return 0;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_removeCollisionObject ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )	
		//self->mWorld->removeCollisionObject(); ///WHAT THE FUCK ???
		return 0;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_collisionHandler ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UB" )

	bool collisionHandler = state.GetValue < bool >( 2, false );

	if (collisionHandler == true ) {
		self->mCollision =  new MOAIBulletCollisionHandler();
		self->mCollision->setWorld(self->mWorld);
		self->mCollision->init();
	}

	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_debugDraw ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UB" )

	bool debugDraw = state.GetValue < bool >( 2, false );

	if (debugDraw == true) {
		self->mDebugDraw = new MOAIBulletDebugDraw ();
		self->mWorld->setDebugDrawer(self->mDebugDraw );	
	};

	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_testObj ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )

	printf("STARTING TEST OBJ\n");

	MOAIBulletTest* testObj = new MOAIBulletTest();
	testObj->SetWorld(self->mWorld);
	self->LuaRetain ( testObj );
	testObj->PushLuaUserdata ( state );

	return 1;
}
//----------------------------------------------------------------//
void MOAIBulletWorld::RegisterLuaClass ( MOAILuaState& state ) {
	MOAIAction::RegisterLuaClass ( state );		
	state.SetField ( -1, "ACTIVE_TAG",				( u32 )1 );
	state.SetField ( -1, "ISLAND_SLEEPING",			( u32 )2 );
	state.SetField ( -1, "WANTS_DEACTIVATION",		( u32 )3 );
	state.SetField ( -1, "DISABLE_DEACTIVATION",	( u32 )4 );
	state.SetField ( -1, "DISABLE_SIMULATION",		( u32 )5 );
	//#define ACTIVE_TAG 1
	//#define ISLAND_SLEEPING 2
	//#define WANTS_DEACTIVATION 3
	//#define DISABLE_DEACTIVATION 4
	//#define DISABLE_SIMULATION 5

}
//----------------------------------------------------------------//
void MOAIBulletWorld::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAIAction::RegisterLuaFuncs ( state );
	luaL_Reg regTable [] = {
//TEST
		{"testObj",					 _testObj},
//SETTINGS
		{"debugDraw",				_debugDraw},
		{"collisionHandler",		_collisionHandler},
//FORCE STEP
		{"forceStep",					 _forceStep},	
//MANIFOLD
		{ "defaultMaxCollisionAlgorithmPoolSize",					_defaultMaxCollisionAlgorithmPoolSize }, 
		{ "defaultMaxPersistentManifoldPoolSize",					_defaultMaxPersistentManifoldPoolSize }, 
//INTI
		{ "create",						_create }, 
		{ "newBody",					_newBody }, 
//JOINTS
		{ "addJointHinge",				_addJointHinge },
		{ "addJointCone",				_addJointCone }, 
		{ "addJointFixed",				_addJointFixed },
		{ "addJointPoint",				_addJointPoint },
		{ "addJointSlider",				_addJointSlider },
		{ "addJointFreedom",			_addJointFreedom },
//WORLD
		{ "setDrawScale",				_setDrawScale },
		{ "setDrawJointSize",			_setDrawJointSize },
		{ "setForceUpdateAllAabbs",		_setForceUpdateAllAabbs },
		
		{ "setStep",					_setStep },
		{ "setMaxSubSteps",				_setMaxSubSteps },
	
		{ "setGravity",					_setGravity },
		{ "useContinuous",				_useContinuous },
		{ "splitImpulse",				_splitImpulse },

		{ "allowedCcdPenetration",		_allowedCcdPenetration },
		{ "enableSPU",					_enableSPU },

		{ "iterations",					_Iterations },	
//DEBUG DRAW
		{"drawDebugLua",				_DrawDebugLua	},


//COLLISION OBJECT
		{"_addCollisionObject",				_addCollisionObject	},
		{"_removeCollisionObject",			_removeCollisionObject	},







		{ NULL, NULL }
	};	
	luaL_register ( state, 0, regTable );
}




