// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAICamera.h>
#include <moai-sim/MOAIDebugLines.h>
#include <moai-sim/MOAIDeck.h>
#include <moai-sim/MOAIFrameBufferTexture.h>
#include <moai-sim/MOAIGfxDevice.h>
#include <moai-sim/MOAIPartitionResultBuffer.h>
#include <moai-sim/MOAIPartitionResultMgr.h>

#include <moai-sim/MOAITextureBase.h>
#include <moai-sim/MOAITransform.h>

#include <MOAIVoxelLayer.h>
#include <MOAIVoxelProp.h>

#if MOAI_WITH_BOX2D
  #include <moai-box2d/MOAIBox2DWorld.h>
#endif

//#if MOAI_WITH_CHIPMUNK
//  #include <moai-chipmunk/MOAICpSpace.h>
//#endif

//#if MOAI_WITH_BULLET
// #include <moai-bullet/MOAIBulletWorld.h>
//#endif


//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	clear
	@text	Remove all props from the layer's partition.
	
	@in		MOAIVoxelLayer self
	@out	nil
*/
int MOAIVoxelLayer::_clear ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "U" )

	if ( self->mPartition ) {
		self->mPartition->Clear ();
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@name	getFitting
	@text	Computes a camera fitting for a given world rect along with
			an optional screen space padding. To do a fitting, compute
			the world rect based on whatever you are fitting to, use
			this method to get the fitting, then animate the camera
			to match.
	
	@in		MOAIVoxelLayer self
	@in		number xMin
	@in		number yMin
	@in		number xMax
	@in		number yMax
	@opt	number xPad
	@opt	number yPad
	@out	number x		X center of fitting (use for camera location).
	@out	number y		Y center of fitting (use for camera location).
	@out	number s		Scale of fitting (use for camera scale).
*/
int MOAIVoxelLayer::_getFitting ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "UNNNN" )

	ZLRect worldRect;
	worldRect.mXMin = state.GetValue < float >( 2, 0.0f );
	worldRect.mYMin = state.GetValue < float >( 3, 0.0f );
	worldRect.mXMax = state.GetValue < float >( 4, 0.0f );
	worldRect.mYMax = state.GetValue < float >( 5, 0.0f );

	worldRect.Bless ();

	float hPad = state.GetValue < float >( 6, 0.0f );
	float vPad = state.GetValue < float >( 7, 0.0f );

	float x = worldRect.mXMin + (( worldRect.mXMax - worldRect.mXMin ) * 0.5f );
	float y = worldRect.mYMin + (( worldRect.mYMax - worldRect.mYMin ) * 0.5f );

	lua_pushnumber ( state, x );
	lua_pushnumber ( state, y );

	float fitting = self->GetFitting ( worldRect, hPad, vPad );
	lua_pushnumber ( state, fitting );

	return 3;
}

//----------------------------------------------------------------//
/**	@name	getPartition
	@text	Returns the partition (if any) currently attached to this layer.
	
	@in		MOAIVoxelLayer self
	@out	MOAIPartition partition
*/
int	MOAIVoxelLayer::_getPartition ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "U" )

	if ( self->mPartition ) {
		self->mPartition->PushLuaUserdata ( state );
		return 1;
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@name	getSortMode
	@text	Get the sort mode for rendering.
	
	@in		MOAIVoxelLayer self
	@out	number sortMode
*/
int MOAIVoxelLayer::_getSortMode ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "U" )
	
	lua_pushnumber ( state, self->mSortMode );
	return 1;
}

//----------------------------------------------------------------//
/**	@name	getSortScale
	@text	Return the scalar applied to axis sorts.
	
	@in		MOAIVoxelLayer self
	@out	number x
	@out	number y
	@out	number priority
*/
int	MOAIVoxelLayer::_getSortScale ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "U" )

	lua_pushnumber ( state, self->mSortScale [ 0 ]);
	lua_pushnumber ( state, self->mSortScale [ 1 ]);
	lua_pushnumber ( state, self->mSortScale [ 3 ]);

	return 3;
}

//----------------------------------------------------------------//
/**	@name	insertProp
	@text	Adds a prop to the layer's partition.
	
	@in		MOAIVoxelLayer self
	@in		MOAIVoxelProp prop
	@out	nil
*/
int	MOAIVoxelLayer::_insertProp ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "UU" )

	MOAIVoxelProp* prop = state.GetLuaObject < MOAIVoxelProp >( 2, true );
	if ( !prop ) return 0;
	if ( prop == self ) return 0;

	self->AffirmPartition ();
	self->mPartition->InsertProp ( *prop );
	prop->ScheduleUpdate ();

	return 0;
}

//----------------------------------------------------------------//
/**	@name	removeProp
	@text	Removes a prop from the layer's partition.
	
	@in		MOAIVoxelLayer self
	@in		MOAIVoxelProp prop
	@out	nil
*/
int	MOAIVoxelLayer::_removeProp ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "UU" )

	MOAIVoxelProp* prop = state.GetLuaObject < MOAIVoxelProp >( 2, true );
	if ( !prop ) return 0;
	if ( prop == self ) return 0;

	if ( self->mPartition ) {
		self->mPartition->RemoveProp ( *prop );
		prop->ScheduleUpdate ();
	}

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setBox2DWorld
	@text	Sets a Box2D world for debug drawing.
	
	@in		MOAIVoxelLayer self
	@in		MOAIBox2DWorld world
	@out	nil
*/
int MOAIVoxelLayer::_setBox2DWorld ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "UU" )
	
	#if MOAI_WITH_BOX2D
		self->mBox2DWorld.Set ( *self, state.GetLuaObject < MOAIBox2DWorld >( 2, true ));
	#endif
	return 0;
}


//----------------------------------------------------------------//
/**	@name	setBulletDWorld
	@text	Sets a Box2D world for debug drawing.
	
	@in		MOAIVoxelLayer self
	@in		setBulletDWorld world
	@out	nil
*/
//int MOAIVoxelLayer::_setBulletWorld ( lua_State* L ) {
//	MOAI_LUA_SETUP ( MOAIVoxelLayer, "UU" )
//	
//	#if MOAI_WITH_BOX2D
//		//self->mBulletWorld.Set ( *self, state.GetLuaObject < MOAIBulletWorld >( 2, true ));
//	#endif
//	return 0;
//}






//----------------------------------------------------------------//
/**	@name	setCamera
	@text	Sets a camera for the layer. If no camera is supplied,
			layer will render using the identity matrix as view/proj.
	
	@overload
	
		@in		MOAIVoxelLayer self
		@opt	MOAICamera camera		Default value is nil.
		@out	nil
	
	@overload
	
		@in		MOAIVoxelLayer self
		@opt	MOAICamera2D camera		Default value is nil.
		@out	nil
*/
int MOAIVoxelLayer::_setCamera ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "U" )

	self->mCamera.Set ( *self, state.GetLuaObject < MOAICamera >( 2, true ));

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setCpSpace
	@text	Sets a Chipmunk space for debug drawing.
	
	@in		MOAIVoxelLayer self
	@in		MOAICpSpace space
	@out	nil
*/
int MOAIVoxelLayer::_setCpSpace ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "UU" )
	
	#if MOAI_WITH_CHIPMUNK
		//self->mCpSpace.Set ( *self, state.GetLuaObject < MOAICpSpace >( 2, true ));
	#endif
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setParallax
	@text	Sets the parallax scale for this layer. This is simply a
			scalar applied to the view transform before rendering.
	
	@in		MOAIVoxelLayer self
	@opt	number xParallax	Default value is 1.
	@opt	number yParallax	Default value is 1.
	@opt	number zParallax	Default value is 1.
	@out	nil
*/
int MOAIVoxelLayer::_setParallax ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "U" )

	self->mParallax.mX = state.GetValue < float >( 2, 1.0f );
	self->mParallax.mY = state.GetValue < float >( 3, 1.0f );
	self->mParallax.mZ = state.GetValue < float >( 4, 1.0f );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setPartition
	@text	Sets a partition for the layer to use. The layer will automatically
			create a partition when the first prop is added if no partition
			has been set.
	
	@in		MOAIVoxelLayer self
	@in		MOAIPartition partition
	@out	nil
*/
int MOAIVoxelLayer::_setPartition ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "UU" )

	self->mPartition.Set ( *self, state.GetLuaObject < MOAIPartition >( 2, true ));

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setPartitionCull2D
	@text	Enables 2D partition cull (projection of frustum AABB will
			be used instead of AABB or frustum).
	
	@in		MOAIVoxelLayer self
	@in		boolean partitionCull2D		Default value is false.
	@out	nil
*/
int	MOAIVoxelLayer::_setPartitionCull2D ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "U" )

	self->mPartitionCull2D = state.GetValue < bool >( 2, false );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setSortMode
	@text	Set the sort mode for rendering.
	
	@in		MOAIVoxelLayer self
	@in		number sortMode		One of MOAIVoxelLayer.SORT_NONE, MOAIVoxelLayer.SORT_PRIORITY_ASCENDING,
								MOAIVoxelLayer.SORT_PRIORITY_DESCENDING, MOAIVoxelLayer.SORT_X_ASCENDING,
								MOAIVoxelLayer.SORT_X_DESCENDING, MOAIVoxelLayer.SORT_Y_ASCENDING,
								MOAIVoxelLayer.SORT_Y_DESCENDING, MOAIVoxelLayer.SORT_Z_ASCENDING,
								MOAIVoxelLayer.SORT_Z_DESCENDING
	@out	nil
*/
int MOAIVoxelLayer::_setSortMode ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "U" )
	
	self->mSortMode = state.GetValue < u32 >( 2, MOAIPartitionResultBuffer::SORT_PRIORITY_ASCENDING );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setSortScale
	@text	Set the scalar applied to axis sorts.
	
	@in		MOAIVoxelLayer self
	@opt	number x			Default value is 0.
	@opt	number y			Default value is 0.
	@opt	number z			Default value is 0.
	@opt	number priority		Default value is 1.
	@out	nil
*/
int	MOAIVoxelLayer::_setSortScale ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "U" )

	self->mSortScale [ 0 ] = state.GetValue < float >( 2, 0.0f );
	self->mSortScale [ 1 ] = state.GetValue < float >( 3, 0.0f );
	self->mSortScale [ 2 ] = state.GetValue < float >( 4, 0.0f );
	self->mSortScale [ 3 ] = state.GetValue < float >( 5, 1.0f );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setViewport
	@text	Set the layer's viewport.
	
	@in		MOAIVoxelLayer self
	@in		MOAIViewport viewport
	@out	nil
*/
int MOAIVoxelLayer::_setViewport ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "UU" )

	self->mViewport.Set ( *self, state.GetLuaObject < MOAIViewport >( 2, true ));

	return 0;
}

//----------------------------------------------------------------//
/**	@name	showDebugLines
	@text	Display debug lines for props in this layer.
	
	@in		MOAIVoxelLayer self
	@opt	boolean showDebugLines		Default value is 'true'.
	@out	nil
*/
int	MOAIVoxelLayer::_showDebugLines ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "U" )
	
	self->mShowDebugLines = state.GetValue < bool >( 2, true );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	wndToWorld
	@text	Project a point from window space into world space and return
			a normal vector representing a ray cast from the point into
			the world away from the camera (suitable for 3D picking).
	
	@in		MOAIVoxelLayer self
	@in		number x
	@in		number y
	@in		number z
	@out	number x
	@out	number y
	@out	number z
	@out	number xn
	@out	number yn
	@out	number zn
*/
int MOAIVoxelLayer::_wndToWorld ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "UNN" )

	USVec4D loc;
	loc.mX = state.GetValue < float >( 2, 0.0f );
	loc.mY = state.GetValue < float >( 3, 0.0f );
	loc.mZ = state.GetValue < float >( 4, 0.0f );
	loc.mW = 1.0f;

	USVec4D vec = loc;
	vec.mZ += 0.1f;

	ZLMatrix4x4 wndToWorld;
	self->GetWndToWorldMtx ( wndToWorld );
	
	wndToWorld.Project ( loc );
	wndToWorld.Project ( vec );

	lua_pushnumber ( state, loc.mX );
	lua_pushnumber ( state, loc.mY );
	lua_pushnumber ( state, loc.mZ );

	ZLVec3D norm;

	norm.mX = vec.mX - loc.mX;
	norm.mY = vec.mY - loc.mY;
	norm.mZ = vec.mZ - loc.mZ;
	
	norm.Norm ();
	
	lua_pushnumber ( state, norm.mX );
	lua_pushnumber ( state, norm.mY );
	lua_pushnumber ( state, norm.mZ );

	return 6;
}

//----------------------------------------------------------------//
/**	@name	worldToWnd
	@text	Transform a point from world space to window space.
	
	@in		MOAIVoxelLayer self
	@in		number x
	@in		number y
	@in		number Z
	@out	number x
	@out	number y
	@out	number z
*/
int MOAIVoxelLayer::_worldToWnd ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelLayer, "UNN" )

	USVec4D loc;
	loc.mX = state.GetValue < float >( 2, 0.0f );
	loc.mY = state.GetValue < float >( 3, 0.0f );
	loc.mZ = state.GetValue < float >( 4, 0.0f );
	loc.mW = 1.0f;

	ZLMatrix4x4 worldToWnd;
	self->GetWorldToWndMtx ( worldToWnd );
	worldToWnd.Project ( loc );

	lua_pushnumber ( state, loc.mX );
	lua_pushnumber ( state, loc.mY );
	lua_pushnumber ( state, loc.mZ );

	return 3;
}

//================================================================//
// MOAINode
//================================================================//

//----------------------------------------------------------------//
void MOAIVoxelLayer::AffirmPartition () {

	if ( !this->mPartition ) {
		this->mPartition.Set ( *this, new MOAIPartition ());
		
		MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
		this->mPartition->PushLuaUserdata ( state );
		state.Pop ( 1 );
	}
}

//----------------------------------------------------------------//
void MOAIVoxelLayer::Draw ( int subPrimID ) {
	UNUSED ( subPrimID );
    
   	if ( !this->IsVisible () ) return;
	if ( !this->mViewport ) return;
	
	MOAIViewport& viewport = *this->mViewport;
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	
	gfxDevice.ResetState ();
	
	ZLRect viewportRect = viewport;

	// TODO:
	ZLMatrix4x4 mtx;
	mtx.Init ( this->mLocalToWorldMtx );
	// TODO:
			//mtx.Append ( gfxDevice.GetWorldToWndMtx ( 1.0f, 1.0f ));
	mtx.Transform ( viewportRect );

	gfxDevice.SetViewRect ( viewportRect );
	gfxDevice.SetScissorRect ( viewportRect );
	this->ClearSurface ();
	
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM );
	
	ZLMatrix4x4 view;
	this->GetViewMtx ( view );
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_VIEW_TRANSFORM, view );
	
	ZLMatrix4x4 proj;
	this->GetProjectionMtx ( proj );
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_PROJ_TRANSFORM, proj );
	
	ZLMatrix4x4 billboard;
	this->GetBillboardMtx ( billboard );
	gfxDevice.SetBillboardMtx ( billboard );
	
	// recompute the frustum
	gfxDevice.UpdateViewVolume ();
	
	if ( this->mShowDebugLines ) {
		
		//#if MOAI_WITH_CHIPMUNK
		//	if ( this->mCpSpace ) {
		//		this->mCpSpace->DrawDebug ();
		//		gfxDevice.Flush ();
		//	}
		//#endif
		
		#if MOAI_WITH_BOX2D
			if ( this->mBox2DWorld ) {
				this->mBox2DWorld->DrawDebug ();
				gfxDevice.Flush ();
			}
		#endif

		//#if MOAI_WITH_BULLET
			//if ( this->mBulletWorld ) {
			//	this->mBulletWorld->DrawDebug ();
			//	gfxDevice.Flush ();
			//}
		//#endif

	};
	
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM );
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_VIEW_TRANSFORM, view );
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_PROJ_TRANSFORM, proj );
	
	if ( this->mPartition ) {
		
		MOAIPartitionResultBuffer& buffer = MOAIPartitionResultMgr::Get ().GetBuffer ();
		const ZLFrustum& viewVolume = gfxDevice.GetViewVolume ();
		
		u32 totalResults = 0;
		
		//INTERESTING SHOULD< I SORT ON SETTING A PRIOTITY OF A PROP //THEN NOT SORT HERE??

		if ( this->mPartitionCull2D ) {
			totalResults = this->mPartition->GatherProps ( buffer, 0, viewVolume.mAABB, MOAIVoxelProp::CAN_DRAW | MOAIVoxelProp::CAN_DRAW_DEBUG );
		}
		else {
			totalResults = this->mPartition->GatherProps ( buffer, 0, viewVolume, MOAIVoxelProp::CAN_DRAW | MOAIVoxelProp::CAN_DRAW_DEBUG );
		}
		
		if ( !totalResults ) return;
		
		buffer.GenerateKeys (
			this->mSortMode,
			this->mSortScale [ 0 ],
			this->mSortScale [ 1 ],
			this->mSortScale [ 2 ],
			this->mSortScale [ 3 ]
		);
		

		totalResults = buffer.Sort ( this->mSortMode );

		//totalResults = buffer.Sort ( ( u32 )MOAIPartitionResultBuffer::SORT_NONE );
		

		
		// set up the ambient color
		gfxDevice.SetAmbientColor ( this->mColor );
		
		// render the sorted list
		for ( u32 i = 0; i < totalResults; ++i ) {
			MOAIPartitionResult* result = buffer.GetResultUnsafe ( i );
			MOAIVoxelProp* prop = result->mProp;
			prop->Draw ( result->mSubPrimID );
		}
		
		if ( this->mShowDebugLines ) {
		
			// clear the ambient color and bind vector drawing
			gfxDevice.SetAmbientColor ( 1.0f, 1.0f, 1.0f, 1.0f );
			MOAIDraw::Get ().Bind ();
			
			// debug draw the sorted list
			for ( u32 i = 0; i < totalResults; ++i ) {
				MOAIPartitionResult* result = buffer.GetResultUnsafe ( i );
				MOAIVoxelProp* prop = result->mProp;
				prop->DrawDebug ( result->mSubPrimID );
			}
		}
	}
	
	gfxDevice.Flush ();
}

//----------------------------------------------------------------//
void MOAIVoxelLayer::GetBillboardMtx ( ZLMatrix4x4& billboard ) {
	
	if ( this->mCamera ) {
		billboard = this->mCamera->GetBillboardMtx ();
	}
	else {
		billboard.Ident ();
	}
}

//----------------------------------------------------------------//
float MOAIVoxelLayer::GetFitting ( ZLRect& worldRect, float hPad, float vPad ) {

	if ( !( this->mCamera && this->mViewport )) return 1.0f;

	ZLRect viewRect = this->mViewport->GetRect ();
	
	float hFit = ( viewRect.Width () - ( hPad * 2 )) / worldRect.Width ();
	float vFit = ( viewRect.Height () - ( vPad * 2 )) / worldRect.Height ();
	
	return ( hFit < vFit ) ? hFit : vFit;
}

//----------------------------------------------------------------//
void MOAIVoxelLayer::GetProjectionMtx ( ZLMatrix4x4& proj ) {
	
	if ( this->mCamera ) {
		proj.Init ( this->mCamera->GetProjMtx ( *this->mViewport ));
	}
	else {
		proj.Init ( this->mViewport->GetProjMtx ());
	}
}

//----------------------------------------------------------------//
u32 MOAIVoxelLayer::GetPropBounds ( ZLBox& bounds ) {
	
	if ( this->mViewport ) {
		ZLRect frame = this->mViewport->GetRect ();
		bounds.Init ( frame.mXMin, frame.mYMax, frame.mXMax, frame.mYMin, 0.0f, 0.0f );
		return MOAIVoxelProp::BOUNDS_OK;
	}
	return MOAIVoxelProp::BOUNDS_EMPTY;
}

//----------------------------------------------------------------//
void MOAIVoxelLayer::GetViewMtx ( ZLMatrix4x4& view ) {
	
	if ( this->mCamera ) {
		
		view = this->mCamera->GetViewMtx ();
		view.m [ ZLMatrix4x4::C3_R0 ] *= this->mParallax.mX;
		view.m [ ZLMatrix4x4::C3_R1 ] *= this->mParallax.mY;
		view.m [ ZLMatrix4x4::C3_R2 ] *= this->mParallax.mZ;
	}
	else {
		view.Ident ();
	}
}

//----------------------------------------------------------------//
void MOAIVoxelLayer::GetWndToWorldMtx ( ZLMatrix4x4& wndToWorld ) {

	this->GetWorldToWndMtx ( wndToWorld );
	wndToWorld.Inverse ();
}

//----------------------------------------------------------------//
void MOAIVoxelLayer::GetWorldToWndMtx ( ZLMatrix4x4& worldToWnd ) {

	if ( this->mViewport ) {
		
		ZLMatrix4x4 view;
		this->GetViewMtx ( view );

		ZLMatrix4x4 proj;
		this->GetProjectionMtx ( proj );
		
		ZLMatrix4x4 wnd;
		this->mViewport->GetNormToWndMtx ( wnd );
		
		worldToWnd = view;
		worldToWnd.Append ( proj );
		worldToWnd.Append ( wnd );
	}
	else {
		worldToWnd.Ident ();
	}
	
	ZLMatrix4x4 mtx;
	mtx.Init ( this->mLocalToWorldMtx );
	worldToWnd.Append ( mtx );
}

//----------------------------------------------------------------//
MOAIVoxelLayer::MOAIVoxelLayer () :
	mParallax ( 1.0f, 1.0f, 1.0f ),
	mShowDebugLines ( true ),
	mSortMode ( MOAIPartitionResultBuffer::SORT_PRIORITY_ASCENDING ),
	mPartitionCull2D ( true ) {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIVoxelProp )
		RTTI_EXTEND ( MOAIClearableView )
	RTTI_END
	
	this->SetMask ( MOAIVoxelProp::CAN_DRAW | MOAIVoxelProp::CAN_DRAW_DEBUG );
	this->SetClearFlags ( 0 );
}

//----------------------------------------------------------------//
MOAIVoxelLayer::~MOAIVoxelLayer () {

	this->mCamera.Set ( *this, 0 );
	this->mViewport.Set ( *this, 0 );
	this->mPartition.Set ( *this, 0 );

	//#if MOAI_WITH_CHIPMUNK
	//	this->mCpSpace.Set ( *this, 0 );
	//#endif
	
	#if MOAI_WITH_BOX2D
		this->mBox2DWorld.Set ( *this, 0 );
	#endif


	//#if MOAI_WITH_BULLET
	//	this->mBulletWorld.Set ( *this, 0 );
	//#endif

}

//----------------------------------------------------------------//
void MOAIVoxelLayer::RegisterLuaClass ( MOAILuaState& state ) {

	MOAIVoxelProp::RegisterLuaClass ( state );
	MOAIClearableView::RegisterLuaClass ( state );
	
	state.SetField ( -1, "SORT_NONE",					( u32 )MOAIPartitionResultBuffer::SORT_NONE );
	state.SetField ( -1, "SORT_ISO",					( u32 )MOAIPartitionResultBuffer::SORT_ISO );
	state.SetField ( -1, "SORT_PRIORITY_ASCENDING",		( u32 )MOAIPartitionResultBuffer::SORT_PRIORITY_ASCENDING );
	state.SetField ( -1, "SORT_PRIORITY_DESCENDING",	( u32 )MOAIPartitionResultBuffer::SORT_PRIORITY_DESCENDING );
	state.SetField ( -1, "SORT_X_ASCENDING",			( u32 )MOAIPartitionResultBuffer::SORT_X_ASCENDING );
	state.SetField ( -1, "SORT_X_DESCENDING",			( u32 )MOAIPartitionResultBuffer::SORT_X_DESCENDING );
	state.SetField ( -1, "SORT_Y_ASCENDING",			( u32 )MOAIPartitionResultBuffer::SORT_Y_ASCENDING );
	state.SetField ( -1, "SORT_Y_DESCENDING",			( u32 )MOAIPartitionResultBuffer::SORT_Y_DESCENDING );
	state.SetField ( -1, "SORT_Z_ASCENDING",			( u32 )MOAIPartitionResultBuffer::SORT_Z_ASCENDING );
	state.SetField ( -1, "SORT_Z_DESCENDING",			( u32 )MOAIPartitionResultBuffer::SORT_Z_DESCENDING );
	state.SetField ( -1, "SORT_VECTOR_ASCENDING",		( u32 )MOAIPartitionResultBuffer::SORT_VECTOR_ASCENDING );
	state.SetField ( -1, "SORT_VECTOR_DESCENDING",		( u32 )MOAIPartitionResultBuffer::SORT_VECTOR_DESCENDING );
}

//----------------------------------------------------------------//
void MOAIVoxelLayer::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	MOAIVoxelProp::RegisterLuaFuncs ( state );
	MOAIClearableView::RegisterLuaFuncs ( state );
	
	luaL_Reg regTable [] = {
		{ "clear",					_clear },
		{ "getFitting",				_getFitting },
		{ "getPartition",			_getPartition },
		{ "getSortMode",			_getSortMode },
		{ "getSortScale",			_getSortScale },
		{ "insertProp",				_insertProp },
		{ "removeProp",				_removeProp },
		{ "setBox2DWorld",			_setBox2DWorld },
		//{ "setBulletWorld",			_setBulletWorld },
		{ "setCamera",				_setCamera },
		{ "setCpSpace",				_setCpSpace },
		{ "setParallax",			_setParallax },
		{ "setPartition",			_setPartition },
		{ "setPartitionCull2D",		_setPartitionCull2D },
		{ "setSortMode",			_setSortMode },
		{ "setSortScale",			_setSortScale },
		{ "setViewport",			_setViewport },
		{ "showDebugLines",			_showDebugLines },
		{ "wndToWorld",				_wndToWorld },
		{ "worldToWnd",				_worldToWnd },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIVoxelLayer::Render () {
	
	this->Draw ( MOAIVoxelProp::NO_SUBPRIM_ID );
}

//----------------------------------------------------------------//
void MOAIVoxelLayer::SerializeIn ( MOAILuaState& state, MOAIDeserializer& serializer ) {
	MOAIVoxelProp::SerializeIn ( state, serializer );
}

//----------------------------------------------------------------//
void MOAIVoxelLayer::SerializeOut ( MOAILuaState& state, MOAISerializer& serializer ) {
	MOAIVoxelProp::SerializeOut ( state, serializer );
}