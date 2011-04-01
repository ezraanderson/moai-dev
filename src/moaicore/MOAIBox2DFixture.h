// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIBOX2DFIXTURE_H
#define	MOAIBOX2DFIXTURE_H
#if USE_BOX2D

#include <moaicore/MOAIBox2DWorld.h>

class b2Fixture;
class MOAIBox2DArbiter;

//================================================================//
// MOAIBox2DFixture
//================================================================//
/**	@brief Box2D fixture.
*/
class MOAIBox2DFixture :
	public MOAIBox2DPrim {
private:

	static const u32 MAX_POLY_VERTS = 1024;

	b2Fixture*	mFixture;

	USLuaRef	mCollisionHandler;
	u32			mCollisionMask;

	//----------------------------------------------------------------//
	static int	_setCollisionHandler	( lua_State* L );
	static int	_setDensity				( lua_State* L );
	static int	_setFilter				( lua_State* L );
	static int	_setFriction			( lua_State* L );
	static int	_setRestitution			( lua_State* L );
	static int	_setSensor				( lua_State* L );
	
	//----------------------------------------------------------------//
	void			BeginContact		( MOAIBox2DFixture* other, MOAIBox2DArbiter* arbiter );
	void			EndContact			( MOAIBox2DFixture* other, MOAIBox2DArbiter* arbiter );
	void			HandleCollision		( u32 eventType, MOAIBox2DFixture* other, MOAIBox2DArbiter* arbiter );
	static u32		LoadVerts			( USLuaState& state, int idx, b2Vec2* verts, u32 max  );
	void			PostSolve			( MOAIBox2DFixture* other, MOAIBox2DArbiter* arbiter );
	void			PreSolve			( MOAIBox2DFixture* other, MOAIBox2DArbiter* arbiter );
	void			SetFixture			( b2Fixture* fixture );

public:
	
	friend class MOAIBox2DArbiter;
	friend class MOAIBox2DBody;
	friend class MOAIBox2DWorld;
	
	DECL_LUA_FACTORY ( MOAIBox2DFixture )
	
	//----------------------------------------------------------------//
					MOAIBox2DFixture		();
					~MOAIBox2DFixture		();
	void			RegisterLuaClass		( USLuaState& state );
	void			RegisterLuaFuncs		( USLuaState& state );
	STLString		ToString				();
};

#endif
#endif