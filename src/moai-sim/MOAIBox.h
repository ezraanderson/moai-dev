#ifndef	MOAIBOX_H
#define	MOAIBOX_H


//#include <moai-core/MOAILua.h>

#include "pch.h"
#include <moai-sim/MOAIFrameBuffer.h>
#include <moai-sim/MOAIPartition.h>
#include <moai-sim/MOAIProp.h>
#include <moai-sim/MOAIViewport.h>

//#include <moai-sim/MOAIEaseDriver.h>

#include <moai-util/MOAIMutex.h>
#include <moai-util/MOAITaskSubscriber.h>
#include <moai-util/MOAITaskThread.h>



class MOAIBox2DWorld;
class MOAICamera;
class MOAICpSpace;
//class MOAIEzraTask;

 
//================================================================//
// MOAIBox
//================================================================//
/**	@name	MOAIBox
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
class MOAIBox :
	public virtual MOAIProp,
	public MOAIClearableView {

private:


	MOAILuaSharedPtr < MOAICamera >			mCamera;
	MOAILuaSharedPtr < MOAIViewport >		mViewport;
	MOAILuaSharedPtr < MOAIPartition >		mPartition;




	#if MOAI_WITH_CHIPMUNK
		MOAILuaSharedPtr < MOAICpSpace >	mCpSpace;
	#endif
	
	#if MOAI_WITH_BOX2D
		MOAILuaSharedPtr < MOAIBox2DWorld >	mBox2DWorld;
	#endif



	MOAIMutex			mMutex;
	ZLLeanArray < u8 >	mBytes;


	ZLVec3D		mParallax;
	bool		mShowDebugLines;
	int			mHigh;
	bool		mBounce;
	int         mTotal;
	int         mProps;
	int         mCollid;
	int         mScreen;

	ZLVec3D		mForce;
	int         tick;

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

	static int	_bounce			    ( lua_State* L );
	static int	_setforce		    ( lua_State* L );
	static int	_total			    ( lua_State* L );

	static int	_threadMake			( lua_State* L );
    static int	_threadStart		( lua_State* L );
    static int	_threadStop		    ( lua_State* L );
    static int	_threadRelease	    ( lua_State* L );

	static int	_results	( lua_State* L );
	static int	_high		( lua_State* L );
	static int	_soup		( lua_State* L );
	static int	_bounds		( lua_State* L );
	static int	_texture	( lua_State* L );
	static int	_insertDraw	( lua_State* L );
	static int	_size	( lua_State* L );
	static int	_shader	( lua_State* L );
	static int	_boom	( lua_State* L );
	static int	_buffers	( lua_State* L );
	static int	_color	( lua_State* L );

	//----------------------------------------------------------------//
	void			AffirmPartition			();
	void			GetBillboardMtx			( ZLMatrix4x4& billboard );
	void			GetProjectionMtx		( ZLMatrix4x4& proj );
	void			GetViewMtx				( ZLMatrix4x4& view );

	bool			Collide(MOAIProp * circleA, MOAIProp * circleB);


public:	
	DECL_LUA_FACTORY ( MOAIBox )

	int         mThread;


	//----------------------------------------------------------------//
	void			Draw					( int subPrimID );
	float			GetFitting				( ZLRect& worldRect, float hPad, float vPad );
	u32				GetPropBounds			( ZLBox& bounds );
	void			GetWndToWorldMtx		( ZLMatrix4x4& wndToWorld );
	void			GetWorldToWndMtx		( ZLMatrix4x4& worldToWnd );
    void            Clear                   ();
					MOAIBox					();
   // void           !MOAIBox                ();
					~MOAIBox				();


	void			RegisterLuaClass		( MOAILuaState& state );
	void			RegisterLuaFuncs		( MOAILuaState& state );
	void			Render					();

	void			SerializeIn				( MOAILuaState& state, MOAIDeserializer& serializer );
	void			SerializeOut			( MOAILuaState& state, MOAISerializer& serializer );

	void	  	    Loop					();
	void	  	    results					();

	void static     Finalize				();

};




#endif
