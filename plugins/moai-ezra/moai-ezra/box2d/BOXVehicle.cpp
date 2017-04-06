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
	MOAI_LUA_SETUP(BOXVehicle, "U")

		//b2Vec2    currentForwardNormal = self->mBody->GetWorldVector( b2Vec2(0,1) ); 	
		//self->mBody->ApplyForce( 2000 * currentForwardNormal, self->mBody->GetWorldCenter(),false );


		//const b2Vec2 velocity = self->mBody->GetLinearVelocity();
		//const float32 speed = velocity.Length();
		////if (speed > 10)
		//	self->mBody->SetLinearVelocity((10 / speed) * velocity);

		//b2Vec2 v;
		//v.x = 60*1/32;
		//v.y = 60*1/32;
		//self->mBody->SetLinearVelocity(v);

		//self->mBody->SetLinearVelocity(b2Vec2(0,0));

		float mangnitude = 2000;
		b2Vec2 forceDirection = self->mBody->GetWorldVector(b2Vec2(0, 1));
		forceDirection = mangnitude * forceDirection;
		self->mBody->ApplyForce(forceDirection, self->mBody->GetPosition(), true);

		b2Vec2 v = self->mBody->GetLinearVelocity();
		const float32 speed = v.Normalize();
		//float maxSpeed = 60*4*1/60;
		//if (speed > maxSpeed){
		//////	printf("CLAMP\n");
		//	self->mBody->SetLinearVelocity(maxSpeed * v);
		//}




	//	if (v.x > 0) {
	//		v.x = 60 * 1 / 32;
	//	};
	//	if (v.x < 0) {
	//		v.x = -60 * 1 / 32;
	//	};

	//	if (v.y > 0) {
	//		v.y = 60 * 1 / 32;
	//	};
	//	if (v.y < 0) {
	//		v.y = -60 * 1 / 32;
	//	};

	///*	v.x = 60*1/32;
	//	v.y = 60*1/32;*/
	//	self->mBody->SetLinearVelocity(v);

		////printf("%f", speed);
		//if (speed > 2){
		//	printf("%f", speed);
		//	//v.x = floor(v.x);
		//	//v.y = floor(v.y);
		//	//self->mBody->SetLinearVelocity(v);
		//};

	




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

	luaL_Reg regTable [] = {
		{ "updateFriction",	_updateFriction },
		{ "updateDriveB",	_updateDriveB },
		{ "updateDriveF",	_updateDriveF },
		{ "setBody",		_setBody },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

