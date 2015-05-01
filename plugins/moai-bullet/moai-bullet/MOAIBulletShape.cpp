// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com


//NEED TO CHANGE THE SHAPES TO THE BASIC
// http://bulletphysics.com/Bullet/BulletFull/classbtSphereShape.html
// THERE SEEMS TO BE SOME REDUNDENCY STUFF HERE
// CALLING THE SETMASS TWICE

#include "pch.h"
#include <moai-bullet/MOAIBulletShape.h>
#include <bullet/src/btBulletDynamicsCommon.h>
//----------------------------------------------------------------//
void MOAIBulletShape::setMassData ( float mass,float inertia  ) {
	//printf("TRACE 6. Reset Mass\n");
	//MASS
		btScalar mMass = btScalar(mass);
	//inertia
		btVector3 mInertia(inertia, inertia, inertia);	
	//APPLY
		this->mShape->calculateLocalInertia(mMass, mInertia);
	//FORCE UPDATE
	if (this->mBody) {
		//UPDATE // THIS IS WRONG BECAUSE IT CACLUATES MASS FROM SHAPES : FIXED
		this->mBody->setMassProps(mMass, mInertia);
		//UPDATE INETIA
		this->mBody->updateInertiaTensor();
	};
};
//----------------------------------------------------------------//
int MOAIBulletShape::_makePlane ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletShape, "U" )
	float width  = state.GetValue < float >( 2, 0.0f );	
	float height = state.GetValue < float >( 3, 0.0f ); 
	float lenght = state.GetValue < float >( 4, 0.0f ); 

	self->mShape = new btStaticPlaneShape(btVector3(width, height, lenght),0);
	self->setMassData(0,0);
return 1;

};

//----------------------------------------------------------------//
//NEED TO IMPORT A TABLE
int MOAIBulletShape::_makeSphereM ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletShape, "U" )

		float width  = state.GetValue < float >( 2, 0.0f );	
		float height = state.GetValue < float >( 3, 0.0f ); 
		float step	 = state.GetValue < float >( 4, 0.0f ); 

		btVector3 spherePositions[2];
		btScalar sphereRadii[2];
  
		sphereRadii[0] = width;
		sphereRadii[1] = width;

		spherePositions[0] = btVector3 (0.0, (height/btScalar(2.0) - width), 0.0);
		spherePositions[1] = btVector3 (0.0, (-height/btScalar(2.0) + width), 0.0);

		self->mShape = new btMultiSphereShape (&spherePositions[0], &sphereRadii[0], 2);

		return 0;
};

//----------------------------------------------------------------//

//----------------------------------------------------------------//
int MOAIBulletShape::_makeSphere ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletShape, "U" )
	   //printf("TRACE 5. btSphereShape\n");
	float radius = state.GetValue < float >( 2, 0.0f );
	self->mShape = new btSphereShape(radius);	
	self->setMassData(0,0);
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletShape::_makeBox ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletShape, "U" )
	
	float width  = state.GetValue < float >( 2, 0.0f );	
	float height = state.GetValue < float >( 3, 0.0f ); 
	float lenght = state.GetValue < float >( 4, 0.0f ); 

	self->mShape = new btBoxShape(btVector3(width, height, lenght)); 
	self->setMassData(0,0);
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletShape::_makeCylinder ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletShape, "U" )

	float width  = state.GetValue < float >( 2, 0.0f );	
	float height = state.GetValue < float >( 3, 0.0f ); 
	float lenght = state.GetValue < float >( 4, 0.0f ); 

	self->mShape = new btCylinderShape(btVector3(width, height, lenght)); 
	self->setMassData(0,0);
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletShape::_makeCapsule ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletShape, "U" )

	float radius  = state.GetValue < float >( 2, 0.0f );	
	float height = state.GetValue < float >( 3, 0.0f ); 

	self->mShape  = new btCapsuleShape(radius, height);
	self->setMassData(0,0);
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletShape::_makeCone ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletShape, "U" )
	float radius  = state.GetValue < float >( 2, 0.0f );	
	float height = state.GetValue < float >( 3, 0.0f ); 

	self->mShape = new btConeShape (radius, height);
	self->setMassData(0,0);

	return 0;

};
//----------------------------------------------------------------//
int MOAIBulletShape::_SetPosition ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletShape, "U" )
	float mLoc_x	= state.GetValue < float >( 2, 0.0f );	
	float mLoc_y	= state.GetValue < float >( 3, 0.0f ); 
	float mLoc_z	= state.GetValue < float >( 4, 0.0f ); 
	self->mLoc->setX(mLoc_x);
	self->mLoc->setY(mLoc_y);
	self->mLoc->setZ(mLoc_z);
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletShape::_SetRotation ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletShape, "U" )
	float mRot_x	= state.GetValue < float >( 2, 0.0f );	
	float mRot_y	= state.GetValue < float >( 3, 0.0f ); 
	float mRot_z	= state.GetValue < float >( 4, 0.0f ); 	
	self->mRot->setX(mRot_x);
	self->mRot->setY(mRot_y);
	self->mRot->setZ(mRot_z);
	return 0;

};
//----------------------------------------------------------------//
int MOAIBulletShape::_setMargin ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletShape, "U" )
	float margin= state.GetValue < float >( 2, 0.0f );	
	self->mShape->setMargin(margin);
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletShape::_setMass ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletShape, "UNN" );	
	float mass		= state.GetValue < float >( 2, 0.0f );	
	float inertia	= state.GetValue < float >( 3, 0.0f ); 
	self->setMassData(mass,inertia);
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletShape::_addToBody ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletShape, "U" )
	btTransform t; 
	t.setIdentity();
	t.setOrigin ( btVector3 ( (self->mLoc->getX()),(self->mLoc->getY()),(self->mLoc->getZ())) );
	t.setRotation ( btQuaternion ( self->mRot->getX(),self->mRot->getY(),self->mRot->getZ() ) ); 

	self->mCompound->addChildShape(t,self->mShape); //MAKE FRIEND CLASS
return 0;
};
//----------------------------------------------------------------//
void MOAIBulletShape::setCompound (btCompoundShape*	mCompound) {
	this->mCompound = mCompound;
};
//----------------------------------------------------------------//
void MOAIBulletShape::Destroy () {
	printf("\nMOAIBulletShape::Destroy\n");
}
//----------------------------------------------------------------//
MOAIBulletShape::MOAIBulletShape () :
mRot(0),
mLoc(0),
mShape(0)
{	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END	

	 mRot = new btVector3(0, 0, 0);
	 mLoc = new btVector3(0, 0, 0);

};
//----------------------------------------------------------------//
MOAIBulletShape::~MOAIBulletShape () {
	printf(" \nMOAIBulletShape::~MOAIBulletShape\n");

	delete mRot;
	delete mLoc;
	this->Destroy ();
}
//----------------------------------------------------------------//
void MOAIBulletShape::RegisterLuaClass ( MOAILuaState& state ) {
	
}
//----------------------------------------------------------------//
void MOAIBulletShape::RegisterLuaFuncs ( MOAILuaState& state ) {

luaL_Reg regTable [] = {
	{ "makeSphereM",	_makeSphereM },
	{ "makeSphere",		_makeSphere },
	{ "makeBox",		_makeBox },	
	{ "makeCylinder",	_makeCylinder },	
	{ "makeCapsule",	_makeCapsule },		
	{ "makeCone",		_makeCone },		
	{ "makePlane",		_makePlane },

	{ "setMass",		_setMass },
	{ "setMargin",		_setMargin },

	{ "addToBody",		_addToBody },	

	{ "setPosition",		_SetPosition },		
	{ "setRotation",		_SetRotation },

{ NULL, NULL }
};
	
luaL_register ( state, 0, regTable );
}
//----------------------------------------------------------------//
void MOAIBulletShape::setOrigin	(float loc_x,float loc_y,float loc_z) {
	this->mLoc->setX(loc_x);
	this->mLoc->setY(loc_y);
	this->mLoc->setZ(loc_z);

};
//----------------------------------------------------------------//
void MOAIBulletShape::setEulerZYX	(float rot_x,float rot_y,float rot_z) {
	this->mRot->setX(rot_x);
	this->mRot->setY(rot_y);
	this->mRot->setZ(rot_z);
};
//----------------------------------------------------------------//
void MOAIBulletShape::setBody (btRigidBody*		mBody) {
	this->mBody = mBody;
	

};
