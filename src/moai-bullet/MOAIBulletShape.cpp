// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com


//NEED TO CHANGE THE SHAPES TO THE BASIC
// http://bulletphysics.com/Bullet/BulletFull/classbtSphereShape.html


#include "pch.h"
#include <moai-bullet/MOAIBulletShape.h>
#include <bullet/src/btBulletDynamicsCommon.h>




int MOAIBulletShape::_addPlane ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletShape, "U" )

	float width  = state.GetValue < float >( 2, 0.0f );	
	float height = state.GetValue < float >( 3, 0.0f ); 
	float lenght = state.GetValue < float >( 4, 0.0f ); 	

	//SHAPE
	//btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 10, 0), 0);
	self->mShape = new btStaticPlaneShape(btVector3(width, height, lenght), 0);

			//BODY
			//btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, self->mMotion, self->mShape, btVector3(0, 0, 0));
			//self->mBody = new btRigidBody(groundRigidBodyCI);
return 1;

};

// ***************************************************************
// ***************************************************************
// ***************************************************************
// ***************************************************************
// ***************************************************************
// ***************************************************************
int MOAIBulletShape::_addSphere ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletShape, "U" )
	float radius = state.GetValue < float >( 2, 0.0f );

	//btSphereShape * mShape = new btCylinderShape(btVector3(width, height, lenght)); 
	//btSphereShape * mShape = new btSphereShape(radius); 

	self->mShape = new btSphereShape(radius);

			//btRigidBody::btRigidBodyConstructionInfo mCI(self->mMass,  self->mMotion, self->mShape, self->mInertia);
			//self->mBody = new btRigidBody(mCI);  
	return 1;


};

// ***************************************************************
// ***************************************************************
// ***************************************************************
// ***************************************************************
// ***************************************************************
// ***************************************************************

int MOAIBulletShape::_addBox ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletShape, "U" )
	
	float width  = state.GetValue < float >( 2, 0.0f );	
	float height = state.GetValue < float >( 3, 0.0f ); 
	float lenght = state.GetValue < float >( 4, 0.0f ); 	

//SHAPE
	//btBoxShape * mShape = new btCylinderShape(btVector3(width, height, lenght));
	self->mShape = new btBoxShape(btVector3(width, height, lenght)); 


			//self->mShape->calculateLocalInertia(self->mMass, self->mInertia);

//BODY
	//btRigidBody::btRigidBodyConstructionInfo mCI(self->mMass, self->mMotion, self->mShape, self->mInertia);
    //self->mBody = new btRigidBody(mCI);    


	return 1;
};



// ***************************************************************
// ***************************************************************
// ***************************************************************
// ***************************************************************
// ***************************************************************
// ***************************************************************

int MOAIBulletShape::_addCylinder ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletShape, "U" )

	float width  = state.GetValue < float >( 2, 0.0f );	
	float height = state.GetValue < float >( 3, 0.0f ); 
	float lenght = state.GetValue < float >( 4, 0.0f ); 

//SHAPE
	//btCylinderShape * mShape = new btCylinderShape(btVector3(width, height, lenght)); 
	self->mShape = new btCylinderShape(btVector3(width, height, lenght)); 
//BODY
		//btRigidBody::btRigidBodyConstructionInfo mCI(self->mMass, self->mMotion, self->mShape, self->mInertia);
		//self->mBody = new btRigidBody(mCI);    
	return 1;
};




// ***************************************************************
// ***************************************************************
// ***************************************************************
// ***************************************************************
// ***************************************************************
// ***************************************************************

int MOAIBulletShape::_addCapsule ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletShape, "U" )



	float radius  = state.GetValue < float >( 2, 0.0f );	
	float height = state.GetValue < float >( 3, 0.0f ); 

//SHAPE
	//btCapsuleShape * mShape = new btCapsuleShape(radius, height); 
	self->mShape  = new btCapsuleShape(radius, height);

//BODY
	//btRigidBody::btRigidBodyConstructionInfo mCI(self->mMass, self->mMotion, self->mShape, self->mInertia);
	//self->mBody = new btRigidBody(mCI);   

	return 1;



};




// ***************************************************************
// ***************************************************************
// ***************************************************************
// ***************************************************************
// ***************************************************************
// ***************************************************************

int MOAIBulletShape::_addCone ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletShape, "U" )

	float radius  = state.GetValue < float >( 2, 0.0f );	
	float height = state.GetValue < float >( 3, 0.0f ); 

//SHAPE
	//btConeShape  * mShape = new btConeShape (radius, height); 
	self->mShape = new btConeShape (radius, height);

//BODY
	//btRigidBody::btRigidBodyConstructionInfo mCI(self->mMass, self->mMotion, self->mShape, self->mInertia);
	//self->mBody = new btRigidBody(mCI);  

	//self->mBody->setRestitution(2);

	return 1;



};
//----------------------------------------------------------------//
int MOAIBulletShape::_SetPosition ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletShape, "U" )
	self->mLoc_x		= state.GetValue < float >( 2, 0.0f );	
	self->mLoc_y		= state.GetValue < float >( 3, 0.0f ); 
	self->mLoc_z		= state.GetValue < float >( 4, 0.0f ); 
	return 1;
};
//----------------------------------------------------------------//
int MOAIBulletShape::_SetRotation ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletShape, "U" )

	self->mRot_x	= state.GetValue < float >( 2, 0.0f );	
	self->mRot_y	= state.GetValue < float >( 3, 0.0f ); 
	self->mRot_z	= state.GetValue < float >( 4, 0.0f ); 
	return 1;

};
//----------------------------------------------------------------//
int MOAIBulletShape::_setMass ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletShape, "UNN" );	

	float mass	  = state.GetValue < float >( 2, 0.0f );
	float Inertia = state.GetValue < float >( 3, 0.0f );

	//MASS
		btScalar mMass = mass;
	//inertia
		btVector3 mInertia(Inertia, Inertia, Inertia);	
		self->mShape->calculateLocalInertia(mMass, mInertia);

	//UPDATE // THIS IS WRONG BECAUSE IT CACLUATES MASS FROM SHAPES
		self->mBody->setMassProps(mass, mInertia);
   
	return 1;
}

//----------------------------------------------------------------//
int MOAIBulletShape::_addToBody ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletShape, "U" )
btTransform t; 

//PASS TRASNFORM
t.setIdentity();
t.setRotation ( btQuaternion ( self->mRot_x, self->mRot_y,self->mRot_z)); 
t.setOrigin(btVector3 ( self->mLoc_x, self->mLoc_y,self->mLoc_z));
self->mCompound->addChildShape(t,self->mShape); //MAKE FRIEND CLASS


return 1;
};
//----------------------------------------------------------------//
void MOAIBulletShape::setCompound (btCompoundShape*	mCompound) {
	this->mCompound = mCompound;
};

//----------------------------------------------------------------//
void MOAIBulletShape::setBody (btRigidBody*		mBody) {
	this->mBody = mBody;
};
//----------------------------------------------------------------//
void MOAIBulletShape::Destroy () {

}
//----------------------------------------------------------------//
MOAIBulletShape::MOAIBulletShape () :
mRot(0),
mLoc(0),
mShape(0),

mLoc_x(0),
mLoc_y(0),
mLoc_z(0),

mRot_x(0),
mRot_y(0),
mRot_z(0)

{	
	RTTI_BEGIN
		//RTTI_EXTEND ( MOAITransformBase )	
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END	
};
//----------------------------------------------------------------//
MOAIBulletShape::~MOAIBulletShape () {
	printf(" \n ~MOAIBulletShape \n");
	this->Destroy ();
}

//----------------------------------------------------------------//
void MOAIBulletShape::RegisterLuaClass ( MOAILuaState& state ) {
//	MOAITransformBase::RegisterLuaClass ( state );	
	
}
//----------------------------------------------------------------//
void MOAIBulletShape::RegisterLuaFuncs ( MOAILuaState& state ) {
//	MOAITransformBase::RegisterLuaFuncs ( state );

luaL_Reg regTable [] = {

	{ "addSphere",		_addSphere },
	{ "addBox",			_addBox },	
	{ "addCylinder",	_addCylinder },	
	{ "addCapsule",		_addCapsule },		
	{ "addCone",		_addCone },		
	{ "addPlane",		_addPlane },

	{ "setMass",		_setMass },
	{ "addToBody",		_addToBody },	

	{ "setPosition",		_SetPosition },		
	{ "setRotation",		_SetRotation },



{ NULL, NULL }
};
	
luaL_register ( state, 0, regTable );
}



