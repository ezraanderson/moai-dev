#include "pch.h"
#include <bullet/src/LinearMath/btQuickprof.h>
#include <moai-bullet/MOAIBulletTest.h>





//#include <bullet/src/btBulletDynamicsCommon.h>
//#include "btRigidBodyWithCollisionEvents.h"

//#include "bullet/src/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.h"
//#include "bullet/src/BulletCollision/CollisionShapes/btBoxShape.h"
//#include "bullet/src/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h"
//#include "bullet/src/BulletCollision/NarrowPhaseCollision/btPointCollector.h"
//#include "bullet/src/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.h"
//#include "bullet/src/BulletCollision/NarrowPhaseCollision/btConvexPenetrationDepthSolver.h"
//#include "bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h"

////*********************************************
//struct bulletObject{
//        int id;
//        float r,g,b;
//        bool hit;
//        btRigidBody* body;
//        bulletObject(btRigidBody* b,int i,float r0,float g0,float b0) : body(b),id(i),r(r0),g(g0),b(b0),hit(false) {}
//};
////*********************************************
//bool MOAIBulletWorld::callbackFunc(btManifoldPoint& cp,const btCollisionObject* obj1,int id1,int index1,const btCollisionObject* obj2,int id2,int index2)
//{
//        ((bulletObject*)obj1->getUserPointer())->hit=true;       
//       ((bulletObject*)obj2->getUserPointer())->hit=true;
//        return false;
//}
//


//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
// TEST CODE
#define ENABLE_ALL_DEMOS 1
#define CUBE_HALF_EXTENTS 1.f
#define SIMD_PI_2 ((SIMD_PI)*0.5f)
#define SIMD_PI_4 ((SIMD_PI)*0.25f)
#define M_PI_8 0.5 * M_PI_4


btRigidBody* MOAIBulletTest::localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape)
{
		btVector3 localInertia(1,0,0);
		shape->calculateLocalInertia(1,localInertia);
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,shape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);
		return body;


}


//****************************************************************//
int MOAIBulletTest::_testJoint ( lua_State* L ) {

		MOAI_LUA_SETUP ( MOAIBulletTest, "U" )	
		printf("TESTING : FIXED JOINT \n");

		btCollisionShape* shapeA = new btBoxShape(btVector3(.5,.5,.5));
		btCollisionShape* shapeB = new btBoxShape(btVector3(.5,.5,.5));
				
		btTransform transA;
		transA.setIdentity();
		transA.setOrigin(btVector3(0,0,0));

		btTransform transB;
		transB.setIdentity();
		transB.setOrigin(btVector3(0,0,0));

		float mass = 1.0f;
		btTransform tr;
		tr.setIdentity();
		tr.setOrigin(btVector3(btScalar(0), btScalar(0), btScalar(0)));
		tr.getBasis().setEulerZYX(0,0,0);	
		btRigidBody* pBodyA = self->localCreateRigidBody( 0.0, transA, shapeA);			
		self->mWorld->addRigidBody(pBodyA);


		tr.setIdentity();
		tr.setOrigin(btVector3(btScalar(0), btScalar(0), btScalar(0)));
		tr.getBasis().setEulerZYX(0,0,0);
		btRigidBody* pBodyB = self->localCreateRigidBody(mass, transB, shapeB);		
		self->mWorld->addRigidBody(pBodyB);

		btTransform frameInA;
		frameInA = btTransform::getIdentity();
		frameInA.getBasis().setEulerZYX(0, 0, 0);
		frameInA.setOrigin(btVector3(btScalar(0.), btScalar(0), btScalar(0.)));

		btTransform	frameInB;
		frameInB = btTransform::getIdentity();
		frameInB.getBasis().setEulerZYX(0,0, 0);
		frameInB.setOrigin(btVector3(btScalar(0.), btScalar(0), btScalar(0.)));

		btFixedConstraint*	btJoint = new btFixedConstraint(*pBodyA, *pBodyB, frameInA, frameInB);	

		self->mWorld->addConstraint(btJoint, true);
		btJoint->setDbgDrawSize(btScalar(1.f));		


	return 0;
}

//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************

int MOAIBulletTest::_testRagDoll ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletTest, "UNNN" )

	enum
{
BODYPART_PELVIS = 0,
BODYPART_SPINE,
BODYPART_HEAD,
BODYPART_LEFT_UPPER_LEG,
BODYPART_LEFT_LOWER_LEG,
BODYPART_RIGHT_UPPER_LEG,
BODYPART_RIGHT_LOWER_LEG,
BODYPART_LEFT_UPPER_ARM,
BODYPART_LEFT_LOWER_ARM,
BODYPART_RIGHT_UPPER_ARM,
BODYPART_RIGHT_LOWER_ARM,
BODYPART_COUNT
};
enum
{
JOINT_PELVIS_SPINE = 0,
JOINT_SPINE_HEAD,
JOINT_LEFT_HIP,
JOINT_LEFT_KNEE,
JOINT_RIGHT_HIP,
JOINT_RIGHT_KNEE,
JOINT_LEFT_SHOULDER,
JOINT_LEFT_ELBOW,
JOINT_RIGHT_SHOULDER,
JOINT_RIGHT_ELBOW,
JOINT_COUNT
};


float offsetX = state.GetValue < float >( 2, 0.0f );
float offsetY = state.GetValue < float >( 3, 0.0f );
float offsetZ = state.GetValue < float >( 4, 0.0f );

printf("TESTING : RAGDOLL %f %f %f\n",offsetX,offsetY,offsetZ);


btCollisionShape*	m_shapes[BODYPART_COUNT];
btRigidBody*		m_bodies[BODYPART_COUNT];
btTypedConstraint*	m_joints[JOINT_COUNT];


//******************************************************************************************
// Setup the geometry
	m_shapes[BODYPART_PELVIS]			= new btCapsuleShape(btScalar(0.15), btScalar(0.20));
	m_shapes[BODYPART_SPINE]			= new btCapsuleShape(btScalar(0.15), btScalar(0.28));
	m_shapes[BODYPART_HEAD]				= new btCapsuleShape(btScalar(0.10), btScalar(0.05));
	m_shapes[BODYPART_LEFT_UPPER_LEG]	= new btCapsuleShape(btScalar(0.07), btScalar(0.45));
	m_shapes[BODYPART_LEFT_LOWER_LEG]	= new btCapsuleShape(btScalar(0.05), btScalar(0.37));
	m_shapes[BODYPART_RIGHT_UPPER_LEG]	= new btCapsuleShape(btScalar(0.07), btScalar(0.45));
	m_shapes[BODYPART_RIGHT_LOWER_LEG]	= new btCapsuleShape(btScalar(0.05), btScalar(0.37));
	m_shapes[BODYPART_LEFT_UPPER_ARM]	= new btCapsuleShape(btScalar(0.05), btScalar(0.33));
	m_shapes[BODYPART_LEFT_LOWER_ARM]	= new btCapsuleShape(btScalar(0.04), btScalar(0.25));
	m_shapes[BODYPART_RIGHT_UPPER_ARM]	= new btCapsuleShape(btScalar(0.05), btScalar(0.33));
	m_shapes[BODYPART_RIGHT_LOWER_ARM]	= new btCapsuleShape(btScalar(0.04), btScalar(0.25));


//**********************************************************************************
// Setup all the rigid bodies
btTransform offset; 
offset.setIdentity();
offset.setOrigin(btVector3 ( offsetX,offsetY,offsetZ));

//TRANSFORM
btTransform transform;
transform.setIdentity();
//**********************************************************************************

transform.setOrigin(btVector3(btScalar(0.), btScalar(1), btScalar(0.)));
m_bodies[BODYPART_PELVIS] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_PELVIS]);
self->mWorld->addRigidBody(m_bodies[BODYPART_PELVIS]);






//**********************************************************************************

transform.setIdentity();
transform.setOrigin(btVector3(btScalar(0.), btScalar(1.2), btScalar(0.)));
m_bodies[BODYPART_SPINE] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_SPINE]);



self->mWorld->addRigidBody(m_bodies[BODYPART_SPINE]);





//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(0.), btScalar(1.6), btScalar(0.)));
m_bodies[BODYPART_HEAD] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_HEAD]);
self->mWorld->addRigidBody(m_bodies[BODYPART_HEAD]);


//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(-0.18), btScalar(0.65), btScalar(0.)));
m_bodies[BODYPART_LEFT_UPPER_LEG] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_UPPER_LEG]);

self->mWorld->addRigidBody(m_bodies[BODYPART_LEFT_UPPER_LEG]);


//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(-0.18), btScalar(0.2), btScalar(0.)));
m_bodies[BODYPART_LEFT_LOWER_LEG] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_LOWER_LEG]);
self->mWorld->addRigidBody(m_bodies[BODYPART_LEFT_LOWER_LEG]);


//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(0.18), btScalar(0.65), btScalar(0.)));
m_bodies[BODYPART_RIGHT_UPPER_LEG] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_UPPER_LEG]);
self->mWorld->addRigidBody(m_bodies[BODYPART_RIGHT_UPPER_LEG]);

//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(0.18), btScalar(0.2), btScalar(0.)));
m_bodies[BODYPART_RIGHT_LOWER_LEG] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_LOWER_LEG]);
self->mWorld->addRigidBody(m_bodies[BODYPART_RIGHT_LOWER_LEG]);

//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(-0.35), btScalar(1.45), btScalar(0.)));
transform.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI_2));
m_bodies[BODYPART_LEFT_UPPER_ARM] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_UPPER_ARM]);
self->mWorld->addRigidBody(m_bodies[BODYPART_LEFT_UPPER_ARM]);

//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(-0.7), btScalar(1.45), btScalar(0.)));
transform.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI_2));
m_bodies[BODYPART_LEFT_LOWER_ARM] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_LOWER_ARM]);
self->mWorld->addRigidBody(m_bodies[BODYPART_LEFT_LOWER_ARM]);

//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(0.35), btScalar(1.45), btScalar(0.)));
transform.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(-M_PI_2));
m_bodies[BODYPART_RIGHT_UPPER_ARM] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_UPPER_ARM]);
self->mWorld->addRigidBody(m_bodies[BODYPART_RIGHT_UPPER_ARM]);

//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(0.7), btScalar(1.45), btScalar(0.)));
transform.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(-M_PI_2));
m_bodies[BODYPART_RIGHT_LOWER_ARM] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_LOWER_ARM]);
self->mWorld->addRigidBody(m_bodies[BODYPART_RIGHT_LOWER_ARM]);







//*******************************************************************************************
// Setup some damping on the m_bodies
		//for (int i = 0; i < BODYPART_COUNT; ++i)
		//{
		//		m_bodies[i]->setDamping(0.05, 0.85);
		//		m_bodies[i]->setDeactivationTime(0.8);
		//		m_bodies[i]->setSleepingThresholds(1.6, 2.5);
		//}


//****************************************************************************************
//****************************************************************************************

btHingeConstraint*		hingeC;
btConeTwistConstraint*	coneC;

btTransform localA; 
btTransform	localB;

float joint_draw = 0.1f;
//****************************************************************************************
//****************************************************************************************
localA.setIdentity(); 
localB.setIdentity();

localA.getBasis().setEulerZYX(0,0,0); 
localA.setOrigin(btVector3(btScalar(0.), btScalar(0.15), btScalar(0.)));

localB.getBasis().setEulerZYX(0,0,0); 
localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.15), btScalar(0.)));

hingeC = new btHingeConstraint(*m_bodies[BODYPART_PELVIS], *m_bodies[BODYPART_SPINE], localA, localB);
hingeC->setLimit(btScalar(-M_PI_4), btScalar(M_PI_2));
hingeC->setDbgDrawSize(joint_draw);
m_joints[JOINT_PELVIS_SPINE] = hingeC;	

self->mWorld->addConstraint(m_joints[JOINT_PELVIS_SPINE], true);
//
////****************************************************************************************
////****************************************************************************************
localA.setIdentity(); 
localB.setIdentity();
localA.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI_2)); localA.setOrigin(btVector3(btScalar(0.), btScalar(0.30), btScalar(0.)));
localB.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI_2)); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.14), btScalar(0.)));

coneC = new btConeTwistConstraint(*m_bodies[BODYPART_SPINE], *m_bodies[BODYPART_HEAD], localA, localB);
coneC->setLimit(btScalar(M_PI_4), btScalar(M_PI_4), btScalar(M_PI_2));
coneC->setDbgDrawSize(joint_draw);
m_joints[JOINT_SPINE_HEAD] = coneC;

self->mWorld->addConstraint(m_joints[JOINT_SPINE_HEAD], true);
//
////****************************************************************************************
////****************************************************************************************
//
localA.setIdentity(); 
localA.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(-M_PI_4*5)); localA.setOrigin(btVector3(btScalar(-0.18), btScalar(-0.10), btScalar(0.)));

localB.setIdentity();
localB.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(-M_PI_4*5)); localB.setOrigin(btVector3(btScalar(0.), btScalar(0.225), btScalar(0.)));

coneC = new btConeTwistConstraint(*m_bodies[BODYPART_PELVIS], *m_bodies[BODYPART_LEFT_UPPER_LEG], localA, localB);
coneC->setLimit(btScalar(M_PI_4), btScalar(M_PI_4), btScalar(0));
coneC->setDbgDrawSize(joint_draw);
m_joints[JOINT_LEFT_HIP] = coneC;
	
self->mWorld->addConstraint(m_joints[JOINT_LEFT_HIP], true);

//****************************************************************************************
//****************************************************************************************

localA.setIdentity(); 
localA.getBasis().setEulerZYX(btScalar(0),btScalar(M_PI_2),btScalar(0)); localA.setOrigin(btVector3(btScalar(0.), btScalar(-0.225), btScalar(0.)));

localB.setIdentity();
localB.getBasis().setEulerZYX(btScalar(0),btScalar(M_PI_2),btScalar(0)); localB.setOrigin(btVector3(btScalar(0.), btScalar(0.185), btScalar(0.)));

hingeC = new btHingeConstraint(*m_bodies[BODYPART_LEFT_UPPER_LEG], *m_bodies[BODYPART_LEFT_LOWER_LEG], localA, localB);
hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
hingeC->setDbgDrawSize(joint_draw);
m_joints[JOINT_LEFT_KNEE] = hingeC;	

self->mWorld->addConstraint(m_joints[JOINT_LEFT_KNEE], true);

//****************************************************************************************
//****************************************************************************************
localA.setIdentity(); 
localA.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI_4)); localA.setOrigin(btVector3(btScalar(0.18), btScalar(-0.10), btScalar(0.)));
localB.setIdentity();
localB.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI_4)); localB.setOrigin(btVector3(btScalar(0.), btScalar(0.225), btScalar(0.)));

coneC = new btConeTwistConstraint(*m_bodies[BODYPART_PELVIS], *m_bodies[BODYPART_RIGHT_UPPER_LEG], localA, localB);
coneC->setLimit(btScalar(M_PI_4), btScalar(M_PI_4), btScalar(0));
coneC->setDbgDrawSize(joint_draw);
m_joints[JOINT_RIGHT_HIP] = coneC;

self->mWorld->addConstraint(m_joints[JOINT_RIGHT_HIP], true);

//****************************************************************************************
//****************************************************************************************
localA.setIdentity(); 
localA.getBasis().setEulerZYX(btScalar(0),btScalar(M_PI_2),btScalar(0)); localA.setOrigin(btVector3(btScalar(0.), btScalar(-0.225), btScalar(0.)));

localB.setIdentity();
localB.getBasis().setEulerZYX(btScalar(0),btScalar(M_PI_2),btScalar(0));localB.setOrigin(btVector3(btScalar(0.), btScalar(0.185), btScalar(0.)));

hingeC = new btHingeConstraint(*m_bodies[BODYPART_RIGHT_UPPER_LEG], *m_bodies[BODYPART_RIGHT_LOWER_LEG], localA, localB);
hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
hingeC->setDbgDrawSize(joint_draw);
m_joints[JOINT_RIGHT_KNEE] = hingeC;


self->mWorld->addConstraint(m_joints[JOINT_RIGHT_KNEE], true);
//****************************************************************************************
//****************************************************************************************
localA.setIdentity();
localA.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI)); localA.setOrigin(btVector3(btScalar(-0.2), btScalar(0.15), btScalar(0.)));

localB.setIdentity();
localB.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI_2)); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.18), btScalar(0.)));

coneC = new btConeTwistConstraint(*m_bodies[BODYPART_SPINE], *m_bodies[BODYPART_LEFT_UPPER_ARM], localA, localB);
coneC->setLimit(btScalar(M_PI_2), btScalar(M_PI_2), btScalar(0));
coneC->setDbgDrawSize(joint_draw);
m_joints[JOINT_LEFT_SHOULDER] = coneC;

self->mWorld->addConstraint(m_joints[JOINT_LEFT_SHOULDER], true);

//****************************************************************************************
//****************************************************************************************
localA.setIdentity(); 
localA.getBasis().setEulerZYX(btScalar(0),btScalar(M_PI_2),btScalar(0)); localA.setOrigin(btVector3(btScalar(0.), btScalar(0.18), btScalar(0.)));

localB.setIdentity();
localB.getBasis().setEulerZYX(btScalar(0),btScalar(M_PI_2),btScalar(0));localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.14), btScalar(0.)));

hingeC = new btHingeConstraint(*m_bodies[BODYPART_LEFT_UPPER_ARM], *m_bodies[BODYPART_LEFT_LOWER_ARM], localA, localB);
hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
hingeC->setDbgDrawSize(joint_draw);
m_joints[JOINT_LEFT_ELBOW] = hingeC;

self->mWorld->addConstraint(m_joints[JOINT_LEFT_ELBOW], true);

//****************************************************************************************
//****************************************************************************************
localA.setIdentity(); 

localA.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(0)); localA.setOrigin(btVector3(btScalar(0.2), btScalar(0.15), btScalar(0.)));
localB.setIdentity();
localB.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI_2)); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.18), btScalar(0.)));

coneC = new btConeTwistConstraint(*m_bodies[BODYPART_SPINE], *m_bodies[BODYPART_RIGHT_UPPER_ARM], localA, localB);
coneC->setLimit(btScalar(M_PI_2), btScalar(M_PI_2), btScalar(0));
coneC->setDbgDrawSize(joint_draw);
m_joints[JOINT_RIGHT_SHOULDER] = coneC;

self->mWorld->addConstraint(m_joints[JOINT_RIGHT_SHOULDER], true);

//****************************************************************************************
//****************************************************************************************

localA.setIdentity();
localA.getBasis().setEulerZYX(btScalar(0),btScalar(M_PI_2),btScalar(0)); 
localA.setOrigin(btVector3(btScalar(0.), btScalar(0.18), btScalar(0.)));

localB.setIdentity();
localB.getBasis().setEulerZYX(btScalar(0),btScalar(M_PI_2),btScalar(0));
localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.14), btScalar(0.)));

hingeC = new btHingeConstraint(*m_bodies[BODYPART_RIGHT_UPPER_ARM], *m_bodies[BODYPART_RIGHT_LOWER_ARM], localA, localB);
hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
hingeC->setDbgDrawSize(joint_draw);
m_joints[JOINT_RIGHT_ELBOW] = hingeC;

self->mWorld->addConstraint(m_joints[JOINT_RIGHT_ELBOW], true);


return 1;

};


//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
///CAR

//TEMP GLOBAL
btRaycastVehicle	*m_vehicle;
btRigidBody			*m_carChassis;

//WTF ????
//btScalar suspensionRestLength(0.6);
float suspensionRestLength = 0.6f;

float	gEngineForce			= 00.f;
float	gBreakingForce			= 00.f;
float	maxEngineForce			= 1000.f;//this should be engine/velocity dependent
float	maxBreakingForce		= 100.f;
float	gVehicleSteering		= 0.f;
float	steeringIncrement		= 0.01f;
float	steeringClamp			= 0.3f;
float	wheelRadius				= 0.7f;
float	wheelWidth				= 0.4f;
float	wheelFriction			= 1000;//BT_LARGE_FLOAT;
float	suspensionStiffness		= 20.f;
float	suspensionDamping		= 2.3f;
float	suspensionCompression	= 4.4f;
float	rollInfluence			= 0.1f;//1.0f;

btVector3 wheelDirectionCS0(0,-1,0);
btVector3 wheelAxleCS(-1,0,0);





//*************************************************************************//
//--------------------------------------------------------------------//
int MOAIBulletTest::_testCar ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletTest, "U" )

btCollisionShape*	chassisShape = new btBoxShape(btVector3(1.f,0.5f,2.f));
btCompoundShape*	compound	 = new btCompoundShape();

//****************************************************
//SHAPE
btTransform localTrans;
localTrans.setIdentity();
localTrans.getBasis().setEulerZYX(0,0,0);
localTrans.setOrigin(btVector3(0,1,0));	
compound->addChildShape(localTrans,chassisShape);


//********************************************************
//BODY 
btTransform tr;
tr.setIdentity();
tr.getBasis().setEulerZYX(0,0,0);
tr.setOrigin(btVector3(0,0,0));
m_carChassis = self->localCreateRigidBody(0,tr,compound); //MASS 300 or 800


//SET IT TO THE WORLD
	self->mWorld->addRigidBody(m_carChassis);

		{

			//MAKE A RAY CAST
			btVehicleRaycaster* m_vehicleRayCaster  = new btDefaultVehicleRaycaster(self->mWorld);
			//TUNE IT
			btRaycastVehicle::btVehicleTuning m_tuning;

					//m_tuning.m_frictionSlip			= 0;
					//m_tuning.m_maxSuspensionForce		= 0;
					//m_tuning.m_maxSuspensionTravelCm	= 0;
					//m_tuning.m_suspensionCompression	= 0;
					//m_tuning.m_suspensionDamping		= 0;
					//m_tuning.m_suspensionStiffness	= 0;


			//MAKE A VEHICLE : TUNE : BODY : CASTER
			m_vehicle			= new btRaycastVehicle(m_tuning,m_carChassis,m_vehicleRayCaster);	
			m_carChassis->setActivationState(DISABLE_DEACTIVATION);	



			// MAKE JOINTS
			btVector3 connectionPointCS0;
			float connectionHeight	= 1.2f;
			bool  isFrontWheel		= false;	

			//***********************	
			connectionPointCS0= btVector3(btScalar(CUBE_HALF_EXTENTS-(0.3*wheelWidth)),btScalar(connectionHeight),btScalar(2*CUBE_HALF_EXTENTS-wheelRadius));
			m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);
			//***********************
			connectionPointCS0 = btVector3(btScalar(-CUBE_HALF_EXTENTS+(0.3*wheelWidth)),btScalar(connectionHeight),btScalar(2*CUBE_HALF_EXTENTS-wheelRadius));
			m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);
			//***********************
			connectionPointCS0 = btVector3(btScalar(-CUBE_HALF_EXTENTS+(0.3*wheelWidth)),btScalar(connectionHeight),btScalar(-2*CUBE_HALF_EXTENTS+wheelRadius));	
			m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);
			//***********************
			connectionPointCS0 = btVector3(btScalar(CUBE_HALF_EXTENTS-(0.3*wheelWidth)),btScalar(connectionHeight),btScalar(-2*CUBE_HALF_EXTENTS+wheelRadius));
			m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);
			
			//*************************************************************************
			//*************************************************************************

					//for (int i=0;i<m_vehicle->getNumWheels();i++)
					//{
					//	btWheelInfo& wheel = m_vehicle->getWheelInfo(i);
					//	wheel.m_suspensionStiffness			= suspensionStiffness;
					//	wheel.m_wheelsDampingRelaxation		= suspensionDamping;
					//	wheel.m_wheelsDampingCompression	= suspensionCompression;
					//	wheel.m_frictionSlip				= wheelFriction;
					//	wheel.m_rollInfluence				= rollInfluence;
					//	//wheel.
					//}




			//SET VIEHICLE TO WORLD
			self->mWorld->addVehicle(m_vehicle);		

			//SET CORDINATES ON VEICL
			int rightIndex   = 0;
			int upIndex		 = 1;
			int forwardIndex = 2;			
			m_vehicle->setCoordinateSystem(rightIndex,upIndex,forwardIndex);

					//m_tuning.m_frictionSlip			= 0;
					//m_tuning.m_maxSuspensionForce		= 0;
					//m_tuning.m_maxSuspensionTravelCm	= 0;
					//m_tuning.m_suspensionCompression	= 0;
					//m_tuning.m_suspensionDamping		= 0;
					//m_tuning.m_suspensionStiffness	= 0;




		}

return 1;
};
//------------------------------------------------------------///
int MOAIBulletTest::_testCarUpdate ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletTest, "UN" )	

int dir = state.GetValue < int >( 2, 0 );

if (dir == 5) {	
	gVehicleSteering = 0;
};

//UP
if (dir == 1) {	
	gEngineForce = maxEngineForce;
	gBreakingForce = 0.f;
};
//RIGHT
if (dir == 4) {	
	gVehicleSteering += steeringIncrement;
	if ( gVehicleSteering > steeringClamp) 
	gVehicleSteering = steeringClamp;
};
//DOWN
if (dir == 3) {	
	gBreakingForce = maxBreakingForce;
	gEngineForce = 0.f;
};
//LEFT
if (dir == 2) {	
	gVehicleSteering -= steeringIncrement;
	if ( gVehicleSteering < -steeringClamp)
	gVehicleSteering = -steeringClamp;
}


	btTransform chassisWorldTrans;
	//look at the vehicle
	m_carChassis->getMotionState()->getWorldTransform(chassisWorldTrans);
	btVector3 m_cameraTargetPosition = chassisWorldTrans.getOrigin();
	

	btQuaternion rotation =chassisWorldTrans.getRotation();
	float quaternion_x = rotation.x();
	float quaternion_y = rotation.y();		
	float quaternion_z = rotation.z();

	//printf("%f \n",quaternion_x);
	//**************************************************************************************************************
	int wheelIndex;


//BRAKING

	//********************************
		wheelIndex = 3;
		m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
		m_vehicle->setBrake(gBreakingForce,wheelIndex);
	//********************************
		wheelIndex = 2;
		m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
		m_vehicle->setBrake(gBreakingForce,wheelIndex);




//STEARING
	//********************************
				wheelIndex = 1;
				m_vehicle->setSteeringValue(gVehicleSteering,wheelIndex);
	//********************************
				wheelIndex = 4;
				m_vehicle->setSteeringValue(gVehicleSteering,wheelIndex);


		//LOC
		lua_pushnumber ( state, m_cameraTargetPosition.getX() ); 
		lua_pushnumber ( state, m_cameraTargetPosition.getY() ); 
		lua_pushnumber ( state, m_cameraTargetPosition.getZ() ); 
		//ROT
		lua_pushnumber ( state, quaternion_x ); 
		lua_pushnumber ( state, quaternion_y ); 
		lua_pushnumber ( state, quaternion_z ); 
		
		return 6;

};



//----------------------------------------------------------------//
void MOAIBulletTest::Destroy () {

}
//----------------------------------------------------------------//
MOAIBulletTest::MOAIBulletTest () :
	mWorld ( 0 ) {	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END	
}
//----------------------------------------------------------------//
MOAIBulletTest::~MOAIBulletTest () {	

}
//----------------------------------------------------------------//
void MOAIBulletTest::RegisterLuaClass ( MOAILuaState& state ) {
		
}
//----------------------------------------------------------------//
void MOAIBulletTest::RegisterLuaFuncs ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{"testJoint",					 _testJoint},
		{"testRagDoll",					 _testRagDoll},
		{"testCar",						 _testCar},
		{"testCarUpdate",				 _testCarUpdate},
		{ NULL, NULL }
	};	
	luaL_register ( state, 0, regTable );
}


//----------------------------------------------------------------//
void MOAIBulletTest::SetWorld (btDiscreteDynamicsWorld* world) {
	this->mWorld = world;
};














//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************








