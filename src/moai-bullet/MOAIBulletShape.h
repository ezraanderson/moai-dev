#ifndef	MOAIBULLETSHAPE_H
#define	MOAIBULLETSHAPE_H

#include <moai-bullet/MOAIBulletWorld.h>

#include <bullet/src/LinearMath/btMotionState.h>
#include <bullet/src/btBulletDynamicsCommon.h>



class MOAIBulletShape :
	public MOAIBulletPrim,
	public virtual MOAILuaObject 
{
private:	

//WORLD
	btCollisionShape*		mShape;
	btCompoundShape*		mCompound;
	btRigidBody*			mBody;	
	
//IAM STUPID

	float mRot_x;
	float mRot_y;
	float mRot_z;

	float mLoc_x;
	float mLoc_y;
	float mLoc_z;

	ZLVec3D* mRot;
	ZLVec3D* mLoc;

	static int		_addPlane				( lua_State* L );
	static int		_addSphere				( lua_State* L );
	static int		_addBox					( lua_State* L );
	static int		_addCylinder			( lua_State* L );
	static int		_addCapsule				( lua_State* L );
	static int		_addCone				( lua_State* L );

	static int		_addToBody				( lua_State* L );
	static int		_setMass				( lua_State* L );

	static int		_SetPosition					( lua_State* L );
	static int		_SetRotation					( lua_State* L );




public:
	
	friend class MOAIBulletBody;

	DECL_LUA_FACTORY ( MOAIBulletShape )

	//----------------------------------------------------------------//
	void			setCompound					(btCompoundShape*	mCompound);
	void			setBody						(btRigidBody*		mBody);

	void			Destroy					();
					MOAIBulletShape			();
					~MOAIBulletShape		();
	void			RegisterLuaClass		( MOAILuaState& state );
	void			RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
