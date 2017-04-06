// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIVOXELLAYER_H
#define	MOAIVOXELLAYER_H

#include <moai-sim/MOAIFrameBuffer.h>
#include <moai-sim/MOAIPartition.h>
#include <moai-sim/MOAIViewport.h>

#include <MOAIVoxelProp.h>

class MOAIBulletWorld; //THIS IS STUPID WHATS GOING ON

class MOAIBox2DWorld;
class MOAICamera;
class MOAICpSpace;

//================================================================//
// MOAIVoxelLayer
//================================================================//
/**	@name	MOAIVoxelLayer
	@text	Scene controls class.
	
	@const	SORT_NONE
	@const	SORT_ISO
	@const	SORT_PRIORITY_ASCENDING
	@const	SORT_PRIORITY_DESCENDING
	@const	SORT_X_ASCENDING
	@const	SORT_X_DESCENDING
	@const	SORT_Y_ASCENDING
	@const	SORT_Y_DESCENDING
	@const	SORT_Z_ASCENDING
	@const	SORT_Z_DESCENDING
	@const	SORT_VECTOR_ASCENDING
	@const	SORT_VECTOR_DESCENDING
*/
class MOAIVoxelLayer :
	public virtual MOAIVoxelProp,
	public MOAIClearableView {
private:

	MOAILuaSharedPtr < MOAICamera >			mCamera;
	MOAILuaSharedPtr < MOAIViewport >		mViewport;
	MOAILuaSharedPtr < MOAIPartition >		mPartition;

	//#if MOAI_WITH_CHIPMUNK
	//	MOAILuaSharedPtr < MOAICpSpace >	mCpSpace;
	//#endif
	
	#if MOAI_WITH_BOX2D
		MOAILuaSharedPtr < MOAIBox2DWorld >	mBox2DWorld;
	#endif

	//#if MOAI_WITH_BULLET
	//	MOAILuaSharedPtr < MOAIBulletWorld >	mBulletWorld;
	//#endif

	ZLVec3D		mParallax;
	bool		mShowDebugLines;
	u32			mSortMode;

	float		mSortScale [ 4 ];

	bool		mPartitionCull2D;

	//----------------------------------------------------------------//
	static int	_clear				( lua_State* L );
	static int	_getFitting			( lua_State* L );
	static int	_getPartition		( lua_State* L );
	static int	_getSortMode		( lua_State* L );
	static int	_getSortScale		( lua_State* L );
	static int	_insertProp			( lua_State* L );
	static int	_removeProp			( lua_State* L );
	static int	_setBox2DWorld		( lua_State* L );

	//static int	_setBulletWorld		( lua_State* L );

	static int	_setCamera			( lua_State* L );
	static int	_setCpSpace			( lua_State* L );
	static int	_setParallax		( lua_State* L );
	static int	_setPartition		( lua_State* L );
	static int	_setPartitionCull2D	( lua_State* L );
	static int	_setSortMode		( lua_State* L );
	static int	_setSortScale		( lua_State* L );
	static int	_setViewport		( lua_State* L );
	static int	_showDebugLines		( lua_State* L );
	static int	_wndToWorld			( lua_State* L );
	static int	_worldToWnd			( lua_State* L );
	
	//----------------------------------------------------------------//
	void			AffirmPartition			();
	void			GetBillboardMtx			( ZLMatrix4x4& billboard );
	void			GetProjectionMtx		( ZLMatrix4x4& proj );
	void			GetViewMtx				( ZLMatrix4x4& view );

public:
	
	DECL_LUA_FACTORY ( MOAIVoxelLayer )
	
	//----------------------------------------------------------------//
	void			Draw					( int subPrimID );
	float			GetFitting				( ZLRect& worldRect, float hPad, float vPad );
	u32				GetPropBounds			( ZLBox& bounds );
	void			GetWndToWorldMtx		( ZLMatrix4x4& wndToWorld );
	void			GetWorldToWndMtx		( ZLMatrix4x4& worldToWnd );
					MOAIVoxelLayer				();
					~MOAIVoxelLayer				();
	void			RegisterLuaClass		( MOAILuaState& state );
	void			RegisterLuaFuncs		( MOAILuaState& state );
	void			Render					();
	void			SerializeIn				( MOAILuaState& state, MOAIDeserializer& serializer );
	void			SerializeOut			( MOAILuaState& state, MOAISerializer& serializer );
};

#endif
