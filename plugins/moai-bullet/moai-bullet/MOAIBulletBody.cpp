// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com
#include "pch.h"

#include <moai-bullet/MOAIBulletBody.h>
#include <moai-bullet/MOAIBulletShape.h>
#include <moai-bullet/MOAIBulletVehicle.h>

#include <bullet/src/btBulletDynamicsCommon.h>
#include <moai-bullet/MOAIBulletTransform.h>





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

	return 0;
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
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_SetLinearRestThreshold ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	
	float threshold = state.GetValue < float >( 2, 0.0f );
    if (self->mBody)
	{     
		self->mBody->setSleepingThresholds(threshold, self->mBody->getAngularSleepingThreshold());
    }
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_SetLinearDamping ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	
	float damping = state.GetValue < float >( 2, 0.0f );
    if (self->mBody)
	{   		
		self->mBody->setDamping(damping,  self->mBody->getAngularDamping());
    }
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_SetDamping ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UNN" )	
	
	float dampingX = state.GetValue < float >( 2, 0.0f );
	float dampingY = state.GetValue < float >( 3, 0.0f );
    if (self->mBody)
	{   		
		self->mBody->setDamping(dampingX, dampingY);
	
    }
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_SetSleepingThresholds ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UNN" )	
	float sleepX = state.GetValue < float >( 2, 0.0f );
	float sleepY = state.GetValue < float >( 3, 0.0f );
    if (self->mBody)
	{   		
		self->mBody->setDamping(sleepX, sleepY);
	
    }
	return 0;
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
	
	return 0;
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
	return 0;
}

//----------------------------------------------------------------//
int MOAIBulletBody::_SetAngularRestThreshold ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	
	float threshold = state.GetValue < float >( 2, 0.0f );

    if (self->mBody)
	{     
		self->mBody->setSleepingThresholds(self->mBody->getLinearSleepingThreshold(),threshold);
    }
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_SetAngularDamping ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	
	float damping = state.GetValue < float >( 2, 0.0f );
    if (self->mBody)
	{   		
		self->mBody->setDamping(self->mBody->getAngularDamping(),damping);
    }
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_SetRestitution ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	float restitution = state.GetValue < float >( 2, 0.0f );
    if (self->mBody)
    {      

	   self->mBody->setRestitution(restitution);
    }

	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_SetFriction ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	float friction = state.GetValue < float >( 2, 0.0f );
    if (self->mBody)
    {       
	   self->mBody->setFriction(friction);
    }

	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetCollidingBodies ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
    if (self->mBody)
    {       
	     
    }
	return 2;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_IsActive ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;    
	float isActive = self->mBody->isActive();
	lua_pushnumber ( state, isActive ); 
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetCcdMotionThreshold ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;    
	float motionThreshold = self->mBody->getCcdMotionThreshold();
	lua_pushnumber ( state, motionThreshold ); 
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetCcdRadius ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" );	    
	float radius = self->mBody->getCcdSweptSphereRadius();
	lua_pushnumber ( state, radius ); 
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetContactProcessingThreshold ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" );	    
	float threshold = self->mBody->getContactProcessingThreshold();
	lua_pushnumber ( state, threshold ); 
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetRestitution ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" );	    
	float restitution = self->mBody->getRestitution();
	lua_pushnumber ( state, restitution ); 
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetRollingFriction ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;    
	float rollingFriction = self->mBody->getRollingFriction();
	lua_pushnumber ( state, rollingFriction ); 
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetAnisotropicFriction ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	; 

	btVector3 anisotropicFriction = self->mBody->getAnisotropicFriction();
	float friction_x = anisotropicFriction.x();
	float friction_y = anisotropicFriction.y();		
	float friction_z = anisotropicFriction.z();

	lua_pushnumber ( state, friction_x ); 
	lua_pushnumber ( state, friction_y ); 
	lua_pushnumber ( state, friction_z ); 
	return 3;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetFriction ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" );	    
	float friction = self->mBody->getFriction();
	lua_pushnumber ( state, friction ); 
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetAngularDamping ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" );	    
	float angularDamping = self->mBody->getAngularDamping();
	lua_pushnumber ( state, angularDamping ); 
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetAngularRestThreshold ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" );	    
	float restThreshold = self->mBody->getAngularSleepingThreshold();
	lua_pushnumber ( state, restThreshold ); 
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetAngularFactor ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "U" )	;    
	btVector3 angularFactor = self->mBody->getAngularFactor();

	float angularFactor_x = angularFactor.x();
	float angularFactor_y = angularFactor.y();		
	float angularFactor_z = angularFactor.z();

	lua_pushnumber ( state, angularFactor_x ); 
	lua_pushnumber ( state, angularFactor_y ); 
	lua_pushnumber ( state, angularFactor_z ); 

	return 3;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetAngularVelocity ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "U" )	;    
	btVector3 angularVelocity = self->mBody->getAngularVelocity();

	float angularVelocity_x = angularVelocity.x();
	float angularVelocity_y = angularVelocity.y();		
	float angularVelocity_z = angularVelocity.z();

	lua_pushnumber ( state, angularVelocity_x ); 
	lua_pushnumber ( state, angularVelocity_y ); 
	lua_pushnumber ( state, angularVelocity_z ); 
	return 3;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetLinearDamping ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "U" );	    
	float linearDamping = self->mBody->getLinearDamping();
	lua_pushnumber ( state, linearDamping ); 
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetLinearRestThreshold ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "U" )	;    
	float restThreshold = self->mBody->getLinearSleepingThreshold();
	lua_pushnumber ( state, restThreshold ); 
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetVelocityAtPoint ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "U" )	;  

	//btVector3 velocityAtPoint = self->mBody->getVelocityInLocalPoint(ToBtVector3(position - centerOfMass_));

	//float velocityAtPoint_x = velocityAtPoint.x();
	//float velocityAtPoint_y = velocityAtPoint.y();		
	//float velocityAtPoint_z = velocityAtPoint.z();

	//lua_pushnumber ( state, velocityAtPoint_x ); 
	//lua_pushnumber ( state, velocityAtPoint_y ); 
	//lua_pushnumber ( state, velocityAtPoint_z ); 
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetLinearFactor ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "U" )	;    
	btVector3 linearFactor = self->mBody->getLinearFactor();
	float linearFactor_x = linearFactor.x();
	float linearFactor_y = linearFactor.y();		
	float linearFactor_z = linearFactor.z();

	lua_pushnumber ( state, linearFactor_x ); 
	lua_pushnumber ( state, linearFactor_y ); 
	lua_pushnumber ( state, linearFactor_z ); 
	return 3;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetLinearVelocity ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "U" )	;    
	btVector3 linearVelocity = self->mBody->getLinearVelocity();
	float linearVelocity_x = linearVelocity.x();
	float linearVelocity_y = linearVelocity.y();		
	float linearVelocity_z = linearVelocity.z();
	lua_pushnumber ( state, linearVelocity_x ); 
	lua_pushnumber ( state, linearVelocity_y ); 
	lua_pushnumber ( state, linearVelocity_z ); 
	return 3;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetRotation ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "U" )	;   

	btQuaternion rotation = self->mBody->getWorldTransform().getRotation();
	float quaternion_x = rotation.x();
	float quaternion_y = rotation.y();		
	float quaternion_z = rotation.z();

	lua_pushnumber ( state, quaternion_x ); 
	lua_pushnumber ( state, quaternion_y ); 
	lua_pushnumber ( state, quaternion_z ); 

	//return body_ ? ToQuaternion(body_->getWorldTransform().getRotation()) : Quaternion::IDENTITY;
	//lua_pushnumber ( state, restThreshold );

	return 3;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_GetPosition ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "U" )	;   

	btVector3 origine = self->mBody->getWorldTransform().getOrigin();
	float loc_x = origine.x();
	float loc_y = origine.y();		
	float loc_z = origine.z();

	lua_pushnumber ( state, loc_x ); 
	lua_pushnumber ( state, loc_y ); 
	lua_pushnumber ( state, loc_z ); 

   // return ToVector3(transform.getOrigin()) - ToQuaternion(transform.getRotation()) * centerOfMass_;
	//lua_pushnumber ( state, restThreshold ); 
	return 3;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_RemoveBodyFromWorld ( lua_State* L ) { 
	MOAI_LUA_SETUP ( MOAIBulletBody, "U" )	;
	self->mWorld->removeRigidBody(self->mBody);  
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_ResetForces ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UNNN" )	;

	float torque_x = state.GetValue < float >( 2, 0.0f );
	float torque_y = state.GetValue < float >( 3, 0.0f );
	float torque_z = state.GetValue < float >( 4, 0.0f );

	btVector3 torque(torque_x, torque_y, torque_z);
	self->mBody->applyTorque(torque);

return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_ApplyImpulse ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UNNN" )	;

	float impulse_x = state.GetValue < float >( 2, 0.0f );
	float impulse_y = state.GetValue < float >( 3, 0.0f );
	float impulse_z = state.GetValue < float >( 4, 0.0f );
	btVector3 impulse(impulse_x, impulse_y, impulse_z);
	self->mBody->applyCentralImpulse(impulse);

return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_ApplyImpulseOffset ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UNNN" )	;

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

return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_ApplyTorque ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UNNN" )	;

	float torque_x = state.GetValue < float >( 2, 0.0f );
	float torque_y = state.GetValue < float >( 3, 0.0f );
	float torque_z = state.GetValue < float >( 4, 0.0f );
	btVector3 torque(torque_x, torque_y, torque_z);
	self->mBody->applyTorque(torque);

return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_ApplyForce ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UNNN" )	;
	float force_x = state.GetValue < float >( 2, 0.0f );
	float force_y = state.GetValue < float >( 3, 0.0f );
	float force_z = state.GetValue < float >( 4, 0.0f );
	btVector3 force(force_x, force_y, force_z);
	self->mBody->applyCentralForce(force);

return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_ApplyForceOffset ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UNNNNNN" )	;

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

return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_ApplyTorqueImpulse ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UNNN" )	;
	float torque_x = state.GetValue < float >( 2, 0.0f );
	float torque_y = state.GetValue < float >( 3, 0.0f );
	float torque_z = state.GetValue < float >( 4, 0.0f );
	btVector3 torque(torque_x, torque_y, torque_z);
	self->mBody->applyTorqueImpulse(torque);

return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_SetRollingFriction ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	float friction = state.GetValue < float >( 2, 0.0f );	
	self->mBody->setRollingFriction(friction);
return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_SetAnisotropicFriction ( lua_State* L ) { 
MOAI_LUA_SETUP ( MOAIBulletBody, "UNNN" )	;
	float friction_x = state.GetValue < float >( 2, 0.0f );
	float friction_y = state.GetValue < float >( 3, 0.0f );
	float friction_z = state.GetValue < float >( 4, 0.0f );
	btVector3 friction(friction_x, friction_y, friction_z);
	self->mBody->setAnisotropicFriction(friction);

return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_SetActivationState ( lua_State* L ) {		
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;	
	int state_set = state.GetValue < int >( 2, 1 );
	self->mBody->setActivationState(state_set);
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_ForceActivationState ( lua_State* L ) {		
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;	
	int state_set = state.GetValue < int >( 2, 1 );
		self->mBody->forceActivationState(state_set);
	return 0;
};

//----------------------------------------------------------------//
int MOAIBulletBody::_SetKinematic ( lua_State* L ) {
		
MOAI_LUA_SETUP ( MOAIBulletBody, "U" )	;
self->mBody->setCollisionFlags( self->mBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
self->mBody->setActivationState(DISABLE_DEACTIVATION);
return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_SetDynamic ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "U" )	;
	self->mBody->setCollisionFlags( self->mBody->getCollisionFlags() & ~btCollisionObject::CF_KINEMATIC_OBJECT);
	self->mBody->forceActivationState(ACTIVE_TAG);
	return 0;
};

//----------------------------------------------------------------//
int MOAIBulletBody::_NoResponse ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "U" )
	self->mBody->setCollisionFlags( self->mBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_SetPosition ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UNNN" )	;

	float loc_x = state.GetValue < float >( 2, 0.0f );
	float loc_y = state.GetValue < float >( 3, 0.0f );
	float loc_z = state.GetValue < float >( 4, 0.0f );

	btTransform& worldTrans = self->mBody->getWorldTransform();
	worldTrans.setIdentity();
	worldTrans.setOrigin ( btVector3 ( btScalar(loc_x),btScalar(loc_y),btScalar(loc_z)) );

	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_SetRotation ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UNNN" )	;
	float rot_x = state.GetValue < float >( 2, 0.0f );
	float rot_y = state.GetValue < float >( 3, 0.0f );
	float rot_z = state.GetValue < float >( 4, 0.0f );
	float angle = state.GetValue < float >( 5, 0.0f );

	btTransform& worldTrans = self->mBody->getWorldTransform();
	worldTrans.setIdentity();
	worldTrans.setRotation ( btQuaternion ( rot_x,rot_y,rot_z,1 ) ); 
	//worldTrans.setRotation ( btQuaternion ( btVector3(rot_x,rot_y,rot_z),angle ) );
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_SetGravity ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UNNN" )	;
	float gravity_x = state.GetValue < float >( 2, 0.0f );
	float gravity_y = state.GetValue < float >( 3, 0.0f );
	float gravity_z = state.GetValue < float >( 4, 0.0f );
	self->mBody->setGravity(btVector3(gravity_x, gravity_y, gravity_z));	
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_SetDeactivationTime ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	float time = state.GetValue < float >( 2, 0.0f );	
	self->mBody->setDeactivationTime(time);	
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_SetContactProcessingThreshold ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	float setCcdMotionThreshold = state.GetValue < float >( 2, 0.0f );	
	self->mBody->setContactProcessingThreshold(btScalar(setCcdMotionThreshold));	
	return 0;
};

//----------------------------------------------------------------//
int MOAIBulletBody::_SetCcdMotionThreshold ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	float setCcdMotionThreshold = state.GetValue < float >( 2, 0.0f );	
	self->mBody->setCcdMotionThreshold(btScalar(setCcdMotionThreshold));	
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_SetCcdSweptSphereRadius ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	float setCcdSweptSphereRadius = state.GetValue < float >( 2, 0.0f );	
	self->mBody->setCcdMotionThreshold(btScalar(setCcdSweptSphereRadius));	
	return 0;
};

//----------------------------------------------------------------//
void MOAIBulletBody::Destroy () {
	printf("\nMOAIBulletBody::Destroy\n");
	if ( this->mBody ) {
			this->mWorld->removeRigidBody(this->mBody); 		
			this->mBody = 0;
	}
	delete (this->mBody);
	delete (this->mCompound);
	delete (this->mMotion);
	delete (this->mRot);
	delete (this->mLoc);
}
//----------------------------------------------------------------//
MOAIBulletBody::MOAIBulletBody () :
	mBody ( 0 ),
	mMotion( 0 ),
	mCompound( 0 ),
	mRot( 0 ),
	mLoc( 0 ),
	idName("id"),
	mCollision_group(DEFAULT_COLLISION_GROUP),
	mCollision_mask(DEFAULT_COLLISION_MASK)
{	
	 mRot = new btVector3(0, 0, 0);
	 mLoc = new btVector3(0, 0, 0);

RTTI_BEGIN
	RTTI_EXTEND ( MOAILuaObject )
	RTTI_EXTEND ( MOAITransformBase )		
RTTI_END	
}
//----------------------------------------------------------------//
MOAIBulletBody::~MOAIBulletBody () {
	printf("\nMOAIBulletBody::~MOAIBulletBody\n");
	this->Destroy ();	
}
//----------------------------------------------------------------//
int MOAIBulletBody::_AddCollisionGroup ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	uint16 group = state.GetValue < uint16 >( 2, 0 );	
	self->mCollision_group = group;	
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_AddCollisionMask ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	uint16 mask = state.GetValue < uint16  >( 2, 0);	
	self->mCollision_mask = mask;
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletBody::_SetCallback ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UF" )	;	
	self->mCollisionHandler.SetRef ( *self, state, 2 );
	return 0;
}
//----------------------------------------------------------------//
void MOAIBulletBody::HandleCollision ( u32 eventType, MOAIBulletBody* bodyA,MOAIBulletBody* bodyB) {	
	if ( this->mCollisionHandler ) {
			
		MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
		if ( this->mCollisionHandler.PushRef ( state )) {					
			state.Push ( 1 );	
			bodyA->PushLuaUserdata ( state );
			bodyB->PushLuaUserdata ( state );					
			state.DebugCall ( 3, 0 );
		}
	};	
}
//----------------------------------------------------------------//
int MOAIBulletBody::_SetFilter ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UNN" )	;
	uint16 group = state.GetValue < uint16  >( 2, 0);
	uint16 mask = state.GetValue < uint16  >( 3, 0);	
	self->mCollision_group = group;
	self->mCollision_mask = mask;
	return 0;
};
//----------------------------------------------------------------//
//I DON't DON'T UNDERSTAND
int MOAIBulletBody::_SetCollisionFlags ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UN" )	;
	 int mask = state.GetValue <  int  >( 2, 1 );	
	self->mBody->setCollisionFlags( self->mBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);	
	return 0;
};

//----------------------------------------------------------------//
int MOAIBulletBody::_AddToWorld ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UB" );	

	self->mWorld->addRigidBody(self->mBody,self->mCollision_group,self->mCollision_mask);



//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

		//self->mWorld->addRigidBody(self->mBody);
		// self->mWorld->addRigidBody(self->mBody);
		// self->mBody->setCollisionFlags(self->mBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

		//static_cast <btRigidBodyWithEvents*>(self->mBody)->setMonitorCollisions(true);
 
		//bool filter = state.GetValue <  bool  >( 2, false );
		//if( filter == true) {
		////	printf("FILTER TRUE \n");
		//	self->mWorld->addRigidBody(self->mBody,self->mCollision_group,self->mCollision_mask);
		//} else {
		//// 	printf("FILTER FALSE \n");
		//	self->mWorld->addRigidBody(self->mBody);
		//}


		//#define BIT(x) (1<<(x))
		//enum collisiontypes {
		//    COL_NOTHING = 0, //<Collide with nothing
		//    COL_SHIP = BIT(0), //<Collide with ships
		//    COL_WALL = BIT(1), //<Collide with walls
		//    COL_POWERUP = BIT(2) //<Collide with powerups
		//}
		//
		//int shipCollidesWith = COL_WALL;
		//int wallCollidesWith = COL_NOTHING;
		//int powerupCollidesWith = COL_SHIP | COL_WALL;


		//btRigidBody ship; // Set up the other ship stuff
		//btRigidBody wall; // Set up the other wall stuff
		//btRigidBody powerup; // Set up the other powerup stuff
		//
		//mWorld->addRigidBody(ship, COL_SHIP, shipCollidesWith);
		//mWorld->addRigidBody(wall, COL_WALL, wallCollidesWith);
		//mWorld->addRigidBody(powerup, COL_POWERUP, powerupCollidesWith);
	
		//	addRigidBody 	( 	btRigidBody *  	body,short  	group,short  	mask ) 	

		//printf("%d %d \n",self->mCollision_group,self->mCollision_mask);
		//self->mWorld->addRigidBody(self->mBody,self->mCollision_group,self->mCollision_mask);

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************


	return 0;
};



//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************

//----------------------------------------------------------------//
//MAYBE ADD LIN AND ANG VELOCITY
int	MOAIBulletBody::_StateSet( lua_State* L ){
MOAI_LUA_SETUP ( MOAIBulletBody, "U" )	
	btVector3 origine = self->mBody->getWorldTransform().getOrigin();
	self->mLoc->setX(origine.x());
	self->mLoc->setY(origine.y());
	self->mLoc->setZ(origine.z());

	btQuaternion rotation = self->mBody->getWorldTransform().getRotation();
	self->mRot->setX(rotation.x());
	self->mRot->setY(rotation.y());
	self->mRot->setZ(rotation.z());

return 0;
};
//----------------------------------------------------------------//
int	MOAIBulletBody::_StateRest( lua_State* L ){
MOAI_LUA_SETUP ( MOAIBulletBody, "U" )	
	//REMOVE FROM WORLD
	self->mWorld->removeRigidBody(self->mBody);

	//RESET
	self->mBody->clearForces();
	btVector3 zeroVector(0,0,0);
	self->mBody->setLinearVelocity(zeroVector);
	self->mBody->setAngularVelocity(zeroVector);

	//ORIGIN
	btTransform	tr;
	tr.setIdentity();
	tr.setOrigin ( btVector3 ( (self->mLoc->getX()),(self->mLoc->getY()),(self->mLoc->getZ())) );
	tr.setRotation ( btQuaternion ( self->mRot->getX(),self->mRot->getY(),self->mRot->getZ() ) ); 
	self->mBody->setWorldTransform(tr); 

	//PROXIES
	self->mWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(self->mBody->getBroadphaseHandle(),self->mWorld->getDispatcher());

	//ADD TO WORLD
	self->mWorld->addRigidBody(self->mBody);


return 0;
};



//***************************************************************************//
//***************************************************************************//
//***************************************************************************//
//***************************************************************************//
//MAYBE ADD TO WORLD AND ATTACHED TO BODY
int MOAIBulletBody::_NewShape ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "UU" )	

	MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >(2, true );
	if ( !( transA )) return 0;
	btTransform ta = *transA->mTransform;

	float loc_x = ta.getOrigin().getX();
	float loc_y = ta.getOrigin().getY();
	float loc_z = ta.getOrigin().getZ();

	//NOT SURE THIS IS CORRECT;
	float rot_x = ta.getRotation().getX();
	float rot_y = ta.getRotation().getY();
	float rot_z = ta.getRotation().getZ();
	

	//printf("TRACE 4. making refrence in \n");

	MOAIBulletShape* shape = new MOAIBulletShape ();

	shape->setCompound(self->mCompound);	

	shape->setBody(self->mBody);
	self->mCompound->setUserPointer(shape);//?? WRONG PLACE

	shape->setOrigin(loc_x,loc_y,loc_z); //DUMB ?
	shape->setEulerZYX(rot_x,rot_y,rot_z);//DUMB ?

	self->LuaRetain ( shape );
	shape->PushLuaUserdata ( state );

	return 1;
}

//***************************************************************************//
//***************************************************************************//
//***************************************************************************//
//***************************************************************************//


//----------------------------------------------------------------//
//REALY UGLY
int MOAIBulletBody::_SetIdName ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletBody, "U" )		
cc8* idName	= state.GetValue < cc8* >( 2, "none" );
int top = state.GetTop();
//printf("top ---%d \n",top);
for (int i = top; i --> 0; ) {
	bool has = state.HasField(i,"idName");
	//printf("i ---%d \n",i);
	if (has == 1) {
			state.SetField ( i, "idName", idName); //IS TOP THIS IS WRONG 
	};
};
	return 0;
};
//----------------------------------------------------------------//
//REALY UGLY
int MOAIBulletBody::_SetIdType ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletBody, "U" )	
cc8* idName	= state.GetValue < cc8* >( 2, "none" );
int top = state.GetTop();
//printf("top ---%d \n",top);
for (int i = top; i --> 0; ) {
	bool has = state.HasField(i,"idType");
	//printf("i ---%d \n",i);
	if (has == 1) {
			state.SetField ( i, "idType", idName); //IS TOP THIS IS WRONG 
	};
};
	return 0;
};

//----------------------------------------------------------------//
int MOAIBulletBody::_NewVehicle ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "U" )	

	//MAKE A RAY CAST
	btVehicleRaycaster* m_vehicleRayCaster  = new btDefaultVehicleRaycaster(self->mWorld);

	MOAIBulletVehicle* vehicle = new MOAIBulletVehicle ();

	vehicle->setCompound(self->mCompound);	//SET COMOUND
	vehicle->setBody(self->mBody);			
	vehicle->setCaster(m_vehicleRayCaster);		
	vehicle->setWorld(self->mWorld);	

	self->LuaRetain ( vehicle );
	vehicle->PushLuaUserdata ( state );
	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_CleanProxyFromPairs ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "U" )		
		self->mWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(self->mBody->getBroadphaseHandle(),self->mWorld->getDispatcher());
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletBody::_ClearForces ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletBody, "U" )		
	self->mBody->clearForces();
	return 0;
}
//----------------------------------------------------------------//
void MOAIBulletBody::setWorld (btDiscreteDynamicsWorld* world) {
	this->mWorld = world;
};
//----------------------------------------------------------------//
void MOAIBulletBody::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITransformBase::RegisterLuaClass ( state );	
}
//----------------------------------------------------------------//
void MOAIBulletBody::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	MOAITransformBase::RegisterLuaFuncs ( state );

	state.SetField ( -1, MOAI_BULLET_idName, "idName");
	state.SetField ( -1, MOAI_BULLET_idType, "idType");
	
	luaL_Reg regTable [] = {


{ "setIdName",							_SetIdName }, 
{ "setIdType",							_SetIdType },


{ "setContactProcessingThreshold",					_SetContactProcessingThreshold }, 


//CLEAN
{ "cleanProxyFromPairs",					_CleanProxyFromPairs }, 

//COLLISION
{ "addCollisionGroup",				_AddCollisionGroup },
{ "addCollisionMask",				_AddCollisionMask },	
{ "setCollisionFlags",				_SetCollisionFlags },	

{ "setFilter",						_SetFilter },
{ "setCallback",					_SetCallback },
{ "noReponse",						_NoResponse },

//CLEAR FORCE
{ "clearForces",			_ClearForces },

//BIND TO THIS BODY // SHOULD SWITCH TO MANUALLY
{ "addToBody",			_AddToBody },

//BODY
{ "newShape",			_NewShape },
{ "newVehicle",			_NewVehicle },

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

//SET PASS
{ "setCcdMotionThreshold",		_SetCcdMotionThreshold },
{ "setCcdSweptSphereRadius",	_SetCcdSweptSphereRadius },

//DAMPING
{ "stateSet",				 _StateSet },
{ "stateReset",				 _StateRest },

//DAMPING
{ "setDamping",				 _SetDamping },


//GRAVAITY
{ "setGravity",				 _SetGravity },

//FRICTION
{ "setFriction",				 _SetFriction },	
{ "setAnisotropicFriction",		_SetAnisotropicFriction },	
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

{ "setPosition",				_SetPosition },		
{ "setRotation",				_SetRotation },	

//ADD

{ "addToWorld",					_AddToWorld},	

//DEACTION

{ "setDeactivationTime",			_SetDeactivationTime},	
{ "setSleepingThresholds",			_SetSleepingThresholds},


//REMOVE
{ "removeBodyFromWorld",				_RemoveBodyFromWorld },	

//ACTIVE
{ "setActivationState",					_SetActivationState },	
{ "forceActivationState",				_ForceActivationState },	

{ "setKinematic",				_SetKinematic },
{ "setDynamic",					_SetDynamic },

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
{ "isActive",						_IsActive },	
{ "getCollidingBodies",				_GetCollidingBodies },	

//setContactProcessingThreshold


//NULS
{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
// SO I NEED TO MAKE THIS FOR COLLISION SHAPE ALSO ????
void MOAIBulletBody::OnDepNodeUpdate () {	

	if ( this->mBody ) {	

		btScalar worldMat[16]; 
		this->mBody->getWorldTransform().getOpenGLMatrix(worldMat);
			
		float* m = this->mLocalToWorldMtx.m;
		
		m [ ZLAffine3D::C0_R0 ] = worldMat[0];
		m [ ZLAffine3D::C0_R1 ] = worldMat[1];
		m [ ZLAffine3D::C0_R2 ] = worldMat[2];

		m [ ZLAffine3D::C1_R0 ] =  worldMat[4];
		m [ ZLAffine3D::C1_R1 ] =  worldMat[5];
		m [ ZLAffine3D::C1_R2 ] =  worldMat[6];

		m [ ZLAffine3D::C2_R0 ] =  worldMat[8];
		m [ ZLAffine3D::C2_R1 ] =  worldMat[9];
		m [ ZLAffine3D::C2_R2 ] =  worldMat[10];

		m [ ZLAffine3D::C3_R0 ] =  worldMat[12];
		m [ ZLAffine3D::C3_R1 ] =  worldMat[13];
		m [ ZLAffine3D::C3_R2 ] =  worldMat[14];

		this->mWorldToLocalMtx.Inverse ( this->mLocalToWorldMtx );
	}
}





//----------------------------------------------------------------//
bool MOAIBulletBody::ApplyAttrOp ( u32 attrID, MOAIAttrOp& attrOp, u32 op ) {
	// TODO: these values may need to be cached for performance reasons
	
	
	//printf("\n ApplyAttrOp %d \n",attrID);		


	//if ( MOAITransform::MOAITransformAttr::Check ( attrID ) == true) {
	//			printf("\n true %d \n",attrID);
	//};

	//if ( MOAITransform::MOAITransformAttr::Check ( attrID ) == false) {
			//	printf("\n false %d \n",attrID);
	//};



	if ( MOAITransform::MOAITransformAttr::Check ( attrID )) {
		//const b2Transform & xform = mBody->GetTransform();

		//printf("\nApplyAttrOp attrID\n");


		switch ( UNPACK_ATTR ( attrID )) {
			case MOAITransform::ATTR_X_LOC: {

					printf("\nApplyAttrOp X\n");

				//float x = attrOp.Apply ( xform.p.x, op, MOAIAttrOp::ATTR_READ_WRITE ) * this->GetUnitsToMeters ();
				//mBody->SetTransform ( b2Vec2( x, xform.p.y), xform.q.GetAngle() );
				return true;
			}

			case MOAITransform::ATTR_Y_LOC: {

					printf("\nApplyAttrOp Y\n");

				//float y = attrOp.Apply ( xform.p.y, op, MOAIAttrOp::ATTR_READ_WRITE ) * this->GetUnitsToMeters ();
				//mBody->SetTransform ( b2Vec2( xform.p.x, y ), xform.q.GetAngle() );
				return true;	
			}

			case MOAITransform::ATTR_Z_ROT: {

						printf("\nApplyAttrOp Z\n");
			//	float angle = attrOp.Apply ( xform.q.GetAngle(), op, MOAIAttrOp::ATTR_READ_WRITE );				
			//	mBody->SetTransform ( xform.p,  ( float )((angle * D2R) + M_PI_4 ));
				return true;	
			}

		}
}
	return MOAITransformBase::ApplyAttrOp (attrID, attrOp, op );
};


//----------------------------------------------------------------//
void MOAIBulletBody::SetBody ( btRigidBody* body ) {
	this->mBody = body;
	body->setUserPointer(this);
}















//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************
//MANUALL SET A SHAPE TO A BODY
//NO LONGER WORKS
int MOAIBulletBody::_AddToBody ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletBody, "UU" )
MOAIBulletShape* shapeA = state.GetLuaObject < MOAIBulletShape >( 2, true );
	btTransform t; 
	t.setIdentity();
	t.setOrigin(btVector3 ( 0,0,0));
	t.getBasis().setEulerZYX(0,0,0);
 	self->mCompound->addChildShape(t,shapeA->mShape); //MAKE FRIEND CLASS
return 0;
};
