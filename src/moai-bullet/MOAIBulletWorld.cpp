#include "pch.h"
#include <moai-bullet/MOAIBulletWorld.h>

#include <moai-bullet/MOAIBulletDebugDraw.h>
#include <moai-bullet/MOAIBulletBody.h>
#include <moai-bullet/MOAIBulletShape.h>

#include <bullet/src/btBulletDynamicsCommon.h>




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


//----------------------------------------------------------------//
MOAIBulletWorld::MOAIBulletWorld () :
    collisionConfiguration_(0),
    collisionDispatcher_(0),
    broadphase_(0),
    solver_(0),
    mWorld(0),
	mDrawScale(1),
	mStep(60)
{
	

RTTI_BEGIN
	RTTI_EXTEND ( MOAIAction )			
RTTI_END

	broadphase_				= new btDbvtBroadphase();
	
	//LOWER MEMORY
		btDefaultCollisionConstructionInfo constructionInfo = btDefaultCollisionConstructionInfo();
		constructionInfo.m_defaultMaxCollisionAlgorithmPoolSize = 1023;
		constructionInfo.m_defaultMaxPersistentManifoldPoolSize = 1023;
		collisionConfiguration_ = new btDefaultCollisionConfiguration(constructionInfo);

	//collisionConfiguration_	= new btDefaultCollisionConfiguration();


	collisionDispatcher_	= new btCollisionDispatcher(collisionConfiguration_);
	solver_					= new btSequentialImpulseConstraintSolver;
	mWorld					= new btDiscreteDynamicsWorld(collisionDispatcher_, broadphase_, solver_, collisionConfiguration_);


	mWorld->setGravity(btVector3(0, 0, 0));
	mWorld->getDispatchInfo().m_useContinuous	= true;
    mWorld->getSolverInfo().m_splitImpulse		= true; // Disable by default for performance


//DEBUG
	mDebugDraw = new MOAIBulletDebugDraw ();
	mWorld->setDebugDrawer(this->mDebugDraw );

	

};


//----------------------------------------------------------------//
MOAIBulletWorld::~MOAIBulletWorld () {
	printf(">>>>>>>>> DESTRUCTED MOAIBulletWorld \n");

	//delete broadphase_;
	//delete collisionConfiguration_;
	//delete collisionDispatcher_;
	//delete solver_;
 //   delete mWorld;
	//delete mDebugDraw;


	
};


////----------------------------------------------------------------//

int MOAIBulletWorld::_addBody ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )	
	MOAIBulletBody* body = new MOAIBulletBody ();
	body->setWorld(self->mWorld);	
	self->LuaRetain ( body );
	body->PushLuaUserdata ( state );
	return 1;
}


//////----------------------------------------------------------------//
//
//int MOAIBulletWorld::_addShape ( lua_State* L ) {
//	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )	
//	MOAIBulletShape* shape = new MOAIBulletShape ();
//	self->LuaRetain ( shape );
//	shape->PushLuaUserdata ( state );
//	return 1;
//}


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
//STATS
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
void MOAIBulletWorld::RegisterLuaClass ( MOAILuaState& state ) {
	MOAIAction::RegisterLuaClass ( state );		
	state.SetField ( -1, "COMPOUND_SHAPE", ( u32 )1 );

}
//----------------------------------------------------------------//
void MOAIBulletWorld::RegisterLuaFuncs ( MOAILuaState& state ) {

	MOAIAction::RegisterLuaFuncs ( state );
	luaL_Reg regTable [] = {

		{ "addBody",					_addBody }, //isCLass
		//{ "addShape",					_addShape }, //isCLass

		{ "setDrawScale",				_setDrawScale },
		{ "setStep",					_setStep },
		{ "setGravity",					_setGravity },
		{ "useContinuous",				_useContinuous },
		{ "splitImpulse",				_splitImpulse },
		{ "Iterations",					_Iterations },	
		{ NULL, NULL }
	};	
	luaL_register ( state, 0, regTable );
}
