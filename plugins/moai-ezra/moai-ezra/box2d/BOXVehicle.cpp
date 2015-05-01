#include "pch.h"

#include <moai-ezra/box2d/BOXVehicle.h>

#include <Box2D/common/b2Math.h>
#include <Box2D/common/b2Settings.h>



int BOXVehicle::_setBody ( lua_State* L ) {
MOAI_LUA_SETUP ( BOXVehicle, "UU" )

	MOAIBox2DBody* temp_body = state.GetLuaObject < MOAIBox2DBody >( 2, true );
	self->mBody = temp_body->GetBody();
	
return 0;
};
//******************************************************************************************************************************************************
//******************************************************************************************************************************************************
//DRIVE
int BOXVehicle::_updateDriveF ( lua_State* L ) {
	MOAI_LUA_SETUP ( BOXVehicle, "U" )

		b2Vec2    currentForwardNormal = self->mBody->GetWorldVector( b2Vec2(0,1) ); 
		//dead dark
		//self->mBody->ApplyForce( 1000 * currentForwardNormal, self->mBody->GetWorldCenter() );
		self->mBody->ApplyForce( 2000 * currentForwardNormal, self->mBody->GetWorldCenter(),false );	
		return 0;
};

//******************************************************************************************************************************************************
//******************************************************************************************************************************************************
int BOXVehicle::_updateDriveB ( lua_State* L ) {
	MOAI_LUA_SETUP ( BOXVehicle, "U" )

		const b2Vec2 velocity = self->mBody->GetLinearVelocity();
		const float32 speed = velocity.Length();

		//printf()

		//if (speed > 5) {
		//	self->mBody->SetLinearVelocity((5 / speed) * velocity);
		//} else {

		b2Vec2    currentForwardNormal = self->mBody->GetWorldVector( b2Vec2(0,1) ); 	
		self->mBody->ApplyForce( -1000 * currentForwardNormal, self->mBody->GetWorldCenter(),true );

		//}



		// self->mBody->ApplyTorque( -15 );


		//   b2Vec2 currentForwardNormal = self->mBody->GetWorldVector( b2Vec2(0,1) );
		//   float currentSpeed = b2Dot(    (b2Dot( currentForwardNormal, self->mBody->GetLinearVelocity() ) * currentForwardNormal) , currentForwardNormal );
		// //          
		//	////b2Vec2 currentForwardNormal = m_body->GetWorldVector( b2Vec2(0,1) );

		// //    

		//float desiredSpeed = -100;
		// //      //apply necessary force
		//       float force = 0;
		//       if ( desiredSpeed > currentSpeed )
		//           force = 1000;
		//       else if ( desiredSpeed < currentSpeed )
		//           force = -1000;
		//       else
		//           return 1;
		//       self->mBody->ApplyForce(  force * currentForwardNormal, self->mBody->GetWorldCenter() );




		return 0;
};
//******************************************************************************************************************************************************
//******************************************************************************************************************************************************
int BOXVehicle::_updateFriction ( lua_State* L ) {

	MOAI_LUA_SETUP ( BOXVehicle, "U" )

		b2Vec2 currentRightNormal;
		b2Vec2 currentForwardNormal;
		float  m_currentTraction = 0.5;
		double m_maxLateralImpulse = 1000;

		//*********************************
		//lateral linear velocity
		currentRightNormal = self->mBody->GetWorldVector( b2Vec2(1,0) );
		b2Vec2 impulse	   = self->mBody->GetMass() * -(b2Dot( currentRightNormal, self->mBody->GetLinearVelocity() ) * currentRightNormal);

		if ( impulse.Length() > m_maxLateralImpulse )
		{
			impulse *= m_maxLateralImpulse / impulse.Length();
		}

		self->mBody->ApplyLinearImpulse( m_currentTraction * impulse, self->mBody->GetWorldCenter(),true );

		//*****************************************
		//angular velocity
		self->mBody->ApplyAngularImpulse( m_currentTraction * 0.1f * self->mBody->GetInertia() * -self->mBody->GetAngularVelocity(),true );

		//******************************************
		//forward linear velocity
		currentForwardNormal = self->mBody->GetWorldVector( b2Vec2(0,1) );  
		currentForwardNormal = b2Dot( currentForwardNormal, self->mBody->GetLinearVelocity() ) * currentForwardNormal;

		float currentForwardSpeed = currentForwardNormal.Normalize();
		float dragForceMagnitude = -2 * currentForwardSpeed;

		self->mBody->ApplyForce( m_currentTraction * dragForceMagnitude * currentForwardNormal, self->mBody->GetWorldCenter(),true );

		return 0;

}

//================================================================//
// BOXVehicle
//================================================================//

//----------------------------------------------------------------//
BOXVehicle::BOXVehicle () :
mBody ( 0 ) 
{

	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )	
		RTTI_END
}

//----------------------------------------------------------------//
BOXVehicle::~BOXVehicle () {
}

//----------------------------------------------------------------//
void BOXVehicle::RegisterLuaClass ( MOAILuaState& state ) {
}

//----------------------------------------------------------------//
void BOXVehicle::RegisterLuaFuncs ( MOAILuaState& state ) {

	// call any initializers for base classes here:
	// MOAIFooBase::RegisterLuaFuncs ( state );

	luaL_Reg regTable [] = {
		{ "updateFriction",	_updateFriction },
		{ "updateDriveB",	_updateDriveB },
		{ "updateDriveF",	_updateDriveF },
		{ "setBody",		_setBody },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

