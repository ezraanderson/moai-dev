// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <bullet/src/btBulletDynamicsCommon.h>


#include <moai-bullet/MOAIBulletCollisionHandler.h>
#include <moai-bullet/MOAIBulletBody.h>

// CProfileManager()
//THIS CALLBACKS DON' WORK I DON' UNDERSTAND
//#include "btRigidBodyWithCollisionEvents.h"
//btRigidBody* g_StaticGroundBox = NULL;
// ICollisionInterface
//void  MOAIBulletWorld::OnCollisionStart(btRigidBodyWithEvents* thisBodyA,btCollisionObject* bodyB,const btVector3& localSpaceContactPoint,const btVector3& worldSpaceContactPoint,const btVector3& worldSpaceContactNormal,const btScalar penetrationDistance,const btScalar appliedImpulse)	{
//	printf("COLLID MOTHER FUCKER A\n");
//}
//void  MOAIBulletWorld::OnCollisionContinue(btRigidBodyWithEvents* thisBodyA,btCollisionObject* bodyB,const btVector3& localSpaceContactPoint,const btVector3& worldSpaceContactPoint,const btVector3& worldSpaceContactNormal,const btScalar penetrationDistance,const btScalar appliedImpulse)	{
//	//printf("Collision Continue: %s - %s\n",thisBodyA!=g_StaticGroundBox ? thisBodyA->getCollisionShape()->getName() : "g_StaticGroundBox",bodyB!=g_StaticGroundBox ? bodyB->getCollisionShape()->getName() : "g_StaticGroundBox" );
//	printf("COLLID MOTHER FUCKER D\n");
//}
//void  MOAIBulletWorld::OnCollisionStop(btRigidBodyWithEvents* thisBodyA,btCollisionObject* bodyB,const btVector3& localSpaceContactPoint,const btVector3& worldSpaceContactPoint,const btVector3& worldSpaceContactNormal,const btScalar penetrationDistance,const btScalar appliedImpulse)	{
//	//printf("Collision End: %s - %s\n",thisBodyA!=g_StaticGroundBox ? thisBodyA->getCollisionShape()->getName() : "g_StaticGroundBox",bodyB!=g_StaticGroundBox ? bodyB->getCollisionShape()->getName() : "g_StaticGroundBox" );
//	printf("COLLID MOTHER FUCKER C\n");
//}



//----------------------------------------------------------------//
// COLLISION CALL BACK SHOULD BE IN IT OWN FILE
// HAS ISSUE WITH ALWASY BUMPPING PLANES
struct YourOwnFilterCallback : public btOverlapFilterCallback
{
	virtual bool	needBroadphaseCollision(btBroadphaseProxy* proxy0,btBroadphaseProxy* proxy1) const
	{
		bool collides = (proxy0->m_collisionFilterGroup & proxy1->m_collisionFilterMask) != 0;
		collides = collides && (proxy1->m_collisionFilterGroup & proxy0->m_collisionFilterMask);	

			btCollisionObject* colObj0 = static_cast<btCollisionObject*>(proxy0->m_clientObject);
			btCollisionObject* colObj1 = static_cast<btCollisionObject*>(proxy1->m_clientObject);
			
			//PREVENT COLLIDING WITH SELF
			if (colObj1 == colObj0) {
				return collides;
			};		

			////LOOK : THE PLANE THE PLANE THE FUCKING PLANE
			btCompoundShape *shapeA = (btCompoundShape *)colObj0->getCollisionShape();
			btCompoundShape *shapeB = (btCompoundShape *)colObj1->getCollisionShape();	

			btRigidBody* rigBodyA = ( btRigidBody* )colObj0;
			MOAIBulletBody* moaiBodyA = ( MOAIBulletBody* )rigBodyA->getUserPointer (); 	

			btRigidBody* rigBodyB = ( btRigidBody* )colObj1;
			MOAIBulletBody* moaiBodyB = ( MOAIBulletBody* )rigBodyB->getUserPointer ();

			if ((moaiBodyA) && (moaiBodyB)) {		
				//printf("ass \n");

				//MOAI BODIES ARE COMMPOUND SHAPES
				//DON"T RETURN PLANE COLLISION MAYBE THIS IS FIXED
				//WHY IS THE THE PLANE ALWAYS COLLDING WITH OBJECTS ????
				if (shapeA->getNumChildShapes() > 0) {			
					if (shapeA->getChildShape(0)->getShapeType() == STATIC_PLANE_PROXYTYPE)  {
						return collides; //RETURN COLLID OR DOSNt HAPPEN
					};			
				};

				if (shapeB->getNumChildShapes() > 0) {
					if (shapeB->getChildShape(0)->getShapeType() == STATIC_PLANE_PROXYTYPE)  {
						return collides;//RETURN COLLID OR DOSNT HAPPEN
					};			
				};	
		
				//RETURN CALLBACK

				//if (moaiBodyA) {
				//	moaiBodyA->HandleCollision ( 1, moaiBodyA,moaiBodyB );
				//};

				if (moaiBodyB) {
					moaiBodyB->HandleCollision ( 1, moaiBodyB,moaiBodyA );
				};

			} else {
				//printf("NOT A MOAI BODY \n");
				//return collides;
			};

//**************************************************************************************
//**************************************************************************************
//**************************************************************************************
//**************************************************************************************
//COLLISION IS  A PLANE 

			//	if (shapeA->getNumChildShapes() > 0) {			
			//		if (shapeA->getChildShape(0)->getShapeType() == STATIC_PLANE_PROXYTYPE)  {
			//			return collides; //RETURN COLLID OR DOSNt HAPPEN
			//		};			
			//	};

			//	if (shapeB->getNumChildShapes() > 0) {
			//		if (shapeB->getChildShape(0)->getShapeType() == STATIC_PLANE_PROXYTYPE)  {
			//			return collides;//RETURN COLLID OR DOSNT HAPPEN
			//		};			
			//	};	

			//
			//////PUSH TO CALLBACK
			//btRigidBody* rigBodyA = ( btRigidBody* )colObj0;
			//MOAIBulletBody* moaiBodyA = ( MOAIBulletBody* )rigBodyA->getUserPointer (); 			
			//
			//btRigidBody* rigBodyB = ( btRigidBody* )colObj1;
			//MOAIBulletBody* moaiBodyB = ( MOAIBulletBody* )rigBodyB->getUserPointer (); 			

			//	//if (moaiBodyA) {
			//	//	moaiBodyA->HandleCollision ( 1, moaiBodyA,moaiBodyB );
			//	//};

			//	if (moaiBodyB) {
			//		moaiBodyB->HandleCollision ( 1, moaiBodyB,moaiBodyA );
			//	};

//**************************************************************************************
//**************************************************************************************
//**************************************************************************************
//**************************************************************************************

		return collides;
	}
};

//**************************************************************************************
void MOAIBulletCollisionHandler::mNearCallback(btBroadphasePair& collisionPair, btCollisionDispatcher& dispatcher, const btDispatcherInfo& dispatchInfo) {
	btCollisionObject* colObj0 = static_cast<btCollisionObject*>(collisionPair.m_pProxy0->m_clientObject);
	btCollisionObject* colObj1 = static_cast<btCollisionObject*>(collisionPair.m_pProxy1->m_clientObject);

	if(dispatcher.needsCollision(colObj0,colObj1))
	{
		btCollisionObjectWrapper obj0Wrap(0,colObj0->getCollisionShape(),colObj0,colObj0->getWorldTransform(),-1,-1);
		btCollisionObjectWrapper obj1Wrap(0,colObj1->getCollisionShape(),colObj1,colObj1->getWorldTransform(),-1,-1);	
		
		//dispatcher will keep algorithms persistent in the collision pair
		if (!collisionPair.m_algorithm)
		{
			collisionPair.m_algorithm = dispatcher.findAlgorithm(&obj0Wrap,&obj1Wrap);
		}
		if (collisionPair.m_algorithm)
		{
			btManifoldResult contactPointResult(&obj0Wrap,&obj1Wrap);


			if (dispatchInfo.m_dispatchFunc == btDispatcherInfo::DISPATCH_DISCRETE)
			{
				//discrete collision detection query
				collisionPair.m_algorithm->processCollision(&obj0Wrap,&obj1Wrap,dispatchInfo,&contactPointResult);

				//CALL TO LUA
				btRigidBody* rigBodyA = ( btRigidBody* )colObj0;
				MOAIBulletBody* moaiBodyA = ( MOAIBulletBody* )rigBodyA->getUserPointer (); 
			
				//
				btRigidBody* rigBodyB = ( btRigidBody* )colObj1;
				MOAIBulletBody* moaiBodyB = ( MOAIBulletBody* )rigBodyB->getUserPointer (); 			

				moaiBodyB->HandleCollision ( 1, moaiBodyA,moaiBodyB );			}
			else
			{
				//continuous collision detection query, time of impact (toi)
				btScalar toi = collisionPair.m_algorithm->calculateTimeOfImpact(colObj0,colObj1,dispatchInfo,&contactPointResult);
				if (dispatchInfo.m_timeOfImpact > toi)
				{
					dispatchInfo.m_timeOfImpact = toi;
				}
			}
			if (contactPointResult.getPersistentManifold()->getNumContacts()>0) 
			{			


			
			}
		}
	}
	dispatcher.defaultNearCallback(collisionPair, dispatcher, dispatchInfo);

}

//----------------------------------------------------------------//
void MOAIBulletCollisionHandler::Destroy () {

}
//----------------------------------------------------------------//
MOAIBulletCollisionHandler::MOAIBulletCollisionHandler () :
	mWorld ( 0 ), 
	filterCallback( 0 )
	{	

}
//----------------------------------------------------------------//
MOAIBulletCollisionHandler::~MOAIBulletCollisionHandler () {	

	if (this->filterCallback) {
		delete filterCallback;
	};

	this->Destroy ();
}

//--------------------------------------------------------//
void MOAIBulletCollisionHandler::init () {	

	if (this->mWorld) {
		this->filterCallback = new YourOwnFilterCallback();
		this->mWorld->getPairCache()->setOverlapFilterCallback(filterCallback);
	};

};

//--------------------------------------------------------//
void MOAIBulletCollisionHandler::setWorld (btDiscreteDynamicsWorld* world) {
	this->mWorld = world;
};