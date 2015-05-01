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
	btOverlapFilterCallback* filterCallback; 
public:	


	//----------------------------------------------------------------//
	void				Destroy							();
						MOAIBulletCollisionHandler		();
						~MOAIBulletCollisionHandler		();
						
	void				setWorld				(btDiscreteDynamicsWorld* world); 
	void				init					(); 

	
	static bool callbackFunc(btManifoldPoint& cp,const btCollisionObject* obj1,int id1,int index1,const btCollisionObject* obj2,int id2,int index2);
	static void mNearCallback(btBroadphasePair& collisionPair, btCollisionDispatcher& dispatcher, const btDispatcherInfo& dispatchInfo);					


};

#endif


// ICollisionEvents
//virtual bool	needsCollision(btCollisionObject* body0,btCollisionObject* body1);
//virtual bool	needsResponse(btCollisionObject* body0,btCollisionObject* body1);
//virtual void	dispatchAllCollisionPairs(btOverlappingPairCache* pairCache,const btDispatcherInfo& dispatchInfo,btDispatcher* dispatcher);

//protected :
//virtual void  OnCollisionStart(btRigidBodyWithEvents* thisBodyA,btCollisionObject* bodyB,const btVector3& localSpaceContactPoint,const btVector3& worldSpaceContactPoint,const btVector3& worldSpaceContactNormal,const btScalar penetrationDistance,const btScalar appliedImpulse);
//virtual void  OnCollisionContinue(btRigidBodyWithEvents* thisBodyA,btCollisionObject* bodyB,const btVector3& localSpaceContactPoint,const btVector3& worldSpaceContactPoint,const btVector3& worldSpaceContactNormal,const btScalar penetrationDistance,const btScalar appliedImpulse);
//virtual void  OnCollisionStop(btRigidBodyWithEvents* thisBodyA,btCollisionObject* bodyB,const btVector3& localSpaceContactPoint,const btVector3& worldSpaceContactPoint,const btVector3& worldSpaceContactNormal,const btScalar penetrationDistance,const btScalar appliedImpulse);	



