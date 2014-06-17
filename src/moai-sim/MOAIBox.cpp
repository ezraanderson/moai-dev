// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAICamera.h>


//#include <moai-sim/MOAICpSpace.h>
//#include <moai-sim/MOAIBox2DWorld.h>
//#include <moai-sim/MOAILogMessages.h>

#include <moai-sim/MOAIDebugLines.h>
#include <moai-sim/MOAIDeck.h>
#include <moai-sim/MOAIFrameBufferTexture.h>
#include <moai-sim/MOAIGfxDevice.h>

#include <moai-sim/MOAIProp.h>

#include <moai-sim/MOAIPartitionResultBuffer.h>
#include <moai-sim/MOAIPartitionResultMgr.h>
#include <moai-sim/MOAIProp.h>


#include <moai-sim/MOAIVertexFormat.h>
#include <moai-sim/MOAIVertexBuffer.h>
#include <moai-sim/MOAIIndexBuffer.h>


#include <moai-sim/MOAITexture.h>
#include <moai-sim/MOAITextureBase.h>


#include <moai-sim/MOAITransform.h>
#include <zl-util/STLArray.h>

#include <moai-util/MOAIThread.h>
#include <moai-util/MOAITaskThread.h>
//
#include <moai-sim/MOAIBox.h>
#include <moai-sim/MOAIEzraTask.h>

#include <moai-sim/MOAISim.h>
#include <moai-sim/MOAIQuadBrush.h>
#include <moai-sim/MOAIShaderMgr.h>

//#ifdef __unix__
//# include <unistd.h>
//#elif defined _WIN32
 //#include <windows.h>

//#define sleep(x) Sleep(1000 * x)
//#endif;

 


//MOAIThread thread;
int _GRID_WIDTH = (int)(1280 / (10 * 2.0f));
int _GRID_HEIGHT = (int)(720 / (10 * 2.0f)); 


int bounds_left = 0;
int bounds_top  = 0;
int bounds_right = 0;
int bounds_bottom = 0;


std::vector<MOAIProp *> _grid[200][200];

//vector<vector<MOAIProp *> > _grid;


std::vector<MOAIProp *> _mProps;
std::vector<MOAIProp*> _mResults;






int delete_step = 0;
int doCollid	= 0;

int total_loop		= 0;
int total_screen    = 0;
int total_collid	= 0;

int soup			= 0;
int blend			= 0;

int right		   =-1;
int bottom		   =-1;
int top			   =-1;
int left		   =-1;

int size		   =32;

int threadState   = 0;

//
MOAITaskThread  * tThread;
MOAIEzraTask    * task;
//MOAITaskQueue   * queue;

MOAIProp*		drawProp;  

//TEXTURE
MOAITexture * texture;
MOAIShader  * shader;

//BUFFERS
MOAIVertexBuffer * vbo;
MOAIIndexBuffer * ibo;



//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	clear
	@text	Remove all props from the layer's partition.
	
	@in		MOAIBox self
	@out	nil
*/
int MOAIBox::_clear ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )

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
	
	@in		MOAIBox self
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
int MOAIBox::_getFitting ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "UNNNN" )

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
	
	@in		MOAIBox self
	@out	MOAIPartition partition
*/
int	MOAIBox::_getPartition ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )

	if ( self->mPartition ) {
		self->mPartition->PushLuaUserdata ( state );
		return 1;
	}
	return 0;
}


//----------------------------------------------------------------//
/**	@name	GET TOTAL
*/
int	MOAIBox::_total ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )
		
	lua_pushnumber ( state, self->mProps);
	lua_pushnumber ( state, self->mTotal);
	lua_pushnumber ( state, self->mCollid);
	lua_pushnumber ( state, self->mScreen);	

				return 4;
}



//----------------------------------------------------------------//
/**	@name	getSortMode
	@text	Get the sort mode for rendering.
	
	@in		MOAIBox self
	@out	number sortMode
*/
int MOAIBox::_getSortMode ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )
	
	lua_pushnumber ( state, self->mSortMode );
	return 1;
}

//----------------------------------------------------------------//
/**	@name	getSortScale
	@text	Return the scalar applied to axis sorts.
	
	@in		MOAIBox2D self
	@out	number x
	@out	number y
	@out	number priority
*/
int	MOAIBox::_getSortScale ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )

	lua_pushnumber ( state, self->mSortScale [ 0 ]);
	lua_pushnumber ( state, self->mSortScale [ 1 ]);
	lua_pushnumber ( state, self->mSortScale [ 3 ]);

	return 3;
}






//----------------------------------------------------------------//
/**	@name	setBox2DWorld
	@text	Sets a Box2D world for debug drawing.
	
	@in		MOAIBox self
	@in		MOAIBox2DWorld world
	@out	nil
*/
int MOAIBox::_setBox2DWorld ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "UU" )
	
	#if USE_BOX2D
		self->mBox2DWorld.Set ( *self, state.GetLuaObject < MOAIBox2DWorld >( 2, true ));
	#endif
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setCamera
	@text	Sets a camera for the layer. If no camera is supplied,
			layer will render using the identity matrix as view/proj.
	
	@overload
	
		@in		MOAIBox self
		@opt	MOAICamera camera		Default value is nil.
		@out	nil
	
	@overload
	
		@in		MOAIBox self
		@opt	MOAICamera2D camera		Default value is nil.
		@out	nil
*/
int MOAIBox::_setCamera ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )

	self->mCamera.Set ( *self, state.GetLuaObject < MOAICamera >( 2, true ));

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setCpSpace
	@text	Sets a Chipmunk space for debug drawing.
	
	@in		MOAIBox self
	@in		MOAICpSpace space
	@out	nil
*/
int MOAIBox::_setCpSpace ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "UU" )
	
	#if USE_CHIPMUNK
		self->mCpSpace.Set ( *self, state.GetLuaObject < MOAICpSpace >( 2, true ));
	#endif
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setParallax
	@text	Sets the parallax scale for this layer. This is simply a
			scalar applied to the view transform before rendering.
	
	@in		MOAIBox self
	@opt	number xParallax	Default value is 1.
	@opt	number yParallax	Default value is 1.
	@opt	number zParallax	Default value is 1.
	@out	nil
*/
int MOAIBox::_setParallax ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )

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
	
	@in		MOAIBox self
	@in		MOAIPartition partition
	@out	nil
*/
int MOAIBox::_setPartition ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "UU" )

	self->mPartition.Set ( *self, state.GetLuaObject < MOAIPartition >( 2, true ));

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setPartitionCull2D
	@text	Enables 2D partition cull (projection of frustum AABB will
			be used instead of AABB or frustum).
	
	@in		MOAIBox self
	@in		boolean partitionCull2D		Default value is false.
	@out	nil
*/
int	MOAIBox::_setPartitionCull2D ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )

	self->mPartitionCull2D = state.GetValue < bool >( 2, false );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setSortMode
	@text	Set the sort mode for rendering.
	
	@in		MOAIBox self
	@in		number sortMode		One of MOAIBox.SORT_NONE, MOAIBox.SORT_PRIORITY_ASCENDING,
								MOAIBox.SORT_PRIORITY_DESCENDING, MOAIBox.SORT_X_ASCENDING,
								MOAIBox.SORT_X_DESCENDING, MOAIBox.SORT_Y_ASCENDING,
								MOAIBox.SORT_Y_DESCENDING, MOAIBox.SORT_Z_ASCENDING,
								MOAIBox.SORT_Z_DESCENDING
	@out	nil
*/
int MOAIBox::_setSortMode ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )
	
	self->mSortMode = state.GetValue < u32 >( 2, MOAIPartitionResultBuffer::SORT_PRIORITY_ASCENDING );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setSortScale
	@text	Set the scalar applied to axis sorts.
	
	@in		MOAIBox self
	@opt	number x			Default value is 0.
	@opt	number y			Default value is 0.
	@opt	number z			Default value is 0.
	@opt	number priority		Default value is 1.
	@out	nil
*/
int	MOAIBox::_setSortScale ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )

	self->mSortScale [ 0 ] = state.GetValue < float >( 2, 0.0f );
	self->mSortScale [ 1 ] = state.GetValue < float >( 3, 0.0f );
	self->mSortScale [ 2 ] = state.GetValue < float >( 4, 0.0f );
	self->mSortScale [ 3 ] = state.GetValue < float >( 5, 1.0f );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setViewport
	@text	Set the layer's viewport.
	
	@in		MOAIBox self
	@in		MOAIViewport viewport
	@out	nil
*/
int MOAIBox::_setViewport ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "UU" )

	self->mViewport.Set ( *self, state.GetLuaObject < MOAIViewport >( 2, true ));

	return 0;
}

//----------------------------------------------------------------//
/**	@name	showDebugLines
	@text	Display debug lines for props in this layer.
	
	@in		MOAIBox self
	@opt	bool showDebugLines		Default value is 'true'.
	@out	nil
*/
int	MOAIBox::_showDebugLines ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )
	
	self->mShowDebugLines = state.GetValue < bool >( 2, true );
	
	return 0;
}





//----------------------------------------------------------------//
/**	@name	wndToWorld
	@text	Project a point from window space into world space and return
			a normal vector representing a ray cast from the point into
			the world away from the camera (suitable for 3D picking).
	
	@in		MOAIBox self
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
int MOAIBox::_wndToWorld ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "UNN" )

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
	
	@in		MOAIBox self
	@in		number x
	@in		number y
	@in		number Z
	@out	number x
	@out	number y
	@out	number z
*/
int MOAIBox::_worldToWnd ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "UNN" )

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
void MOAIBox::AffirmPartition () {

	if ( !this->mPartition ) {
		this->mPartition.Set ( *this, new MOAIPartition ());
		
		MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
		this->mPartition->PushLuaUserdata ( state );
		state.Pop ( 1 );
	}
};








//----------------------------------------------------------------//
void MOAIBox::GetBillboardMtx ( ZLMatrix4x4& billboard ) {
	
	if ( this->mCamera ) {
		billboard = this->mCamera->GetBillboardMtx ();
	}
	else {
		billboard.Ident ();
	}
}

//----------------------------------------------------------------//
float MOAIBox::GetFitting ( ZLRect& worldRect, float hPad, float vPad ) {

	if ( !( this->mCamera && this->mViewport )) return 1.0f;

	ZLRect viewRect = this->mViewport->GetRect ();
	
	float hFit = ( viewRect.Width () - ( hPad * 2 )) / worldRect.Width ();
	float vFit = ( viewRect.Height () - ( vPad * 2 )) / worldRect.Height ();
	
	return ( hFit < vFit ) ? hFit : vFit;
}

//----------------------------------------------------------------//
void MOAIBox::GetProjectionMtx ( ZLMatrix4x4& proj ) {
	
	if ( this->mCamera ) {
		proj.Init ( this->mCamera->GetProjMtx ( *this->mViewport ));
	}
	else {
		proj.Init ( this->mViewport->GetProjMtx ());
	}
}

//----------------------------------------------------------------//
u32 MOAIBox::GetPropBounds ( ZLBox& bounds ) {
	
	if ( this->mViewport ) {
		ZLRect frame = this->mViewport->GetRect ();
		bounds.Init ( frame.mXMin, frame.mYMax, frame.mXMax, frame.mYMin, 0.0f, 0.0f );
		return MOAIProp::BOUNDS_OK;
	}
	return MOAIProp::BOUNDS_EMPTY;
}

//----------------------------------------------------------------//
void MOAIBox::GetViewMtx ( ZLMatrix4x4& view ) {
	
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
void MOAIBox::GetWndToWorldMtx ( ZLMatrix4x4& wndToWorld ) {
	this->GetWorldToWndMtx ( wndToWorld );
	wndToWorld.Inverse ();
}

//----------------------------------------------------------------//
void MOAIBox::GetWorldToWndMtx ( ZLMatrix4x4& worldToWnd ) {

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






//**************************************************************************************************
//**************************************************************************************************
//RESULTS
void MOAIBox::results () {


//
//MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
//
//		MOAIPartitionResultBuffer& buffer	= MOAIPartitionResultMgr::Get ().GetBuffer ();
//		const USFrustum& viewVolume			= gfxDevice.GetViewVolume ();
//		
//		u32 totalResults = 0;
//
//			totalResults = this->mPartition->GatherProps ( buffer, 0, viewVolume.mAABB, MOAIProp::CAN_DRAW | MOAIProp::CAN_DRAW_DEBUG );			
//
//
//		if ( !totalResults ) return;
//
//				buffer.GenerateKeys (
//					this->mSortMode,
//					this->mSortScale [ 0 ],
//					this->mSortScale [ 1 ],
//					this->mSortScale [ 2 ],
//					this->mSortScale [ 3 ]
//				);
//		
//	
//		totalResults = buffer.Sort ( this->mSortMode );	
//
//
//
//
//// mResults.clear();
//
//
//
//////////////////////////////////////////////////////
//	for ( u32 i = 0; i < totalResults; ++i ) {
//				MOAIPartitionResult* result = buffer.GetResultUnsafe ( i );
//				mResults.push_back(result);
//	};
//
//






			
};

//**************************************************************************************************
//RESULTS
int	MOAIBox::_results ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )	
	self->results ();
	return 0;
}







//----------------------------------------------------------------//
//COLLSION
bool  MOAIBox::Collide(MOAIProp * circleA, MOAIProp * circleB){


float balls_i_x  =  circleA->GetXLoc();
float balls_i_y  =  circleA->GetYLoc();

float balls_i_vx = circleA->mVec.mX;
float balls_i_vy = circleA->mVec.mY;

float balls_i_r  = 10;


//J
float balls_j_x =  circleB->GetXLoc();
float balls_j_y =  circleB->GetYLoc();

float balls_j_vx = circleB->mVec.mX;
float balls_j_vy = circleB->mVec.mY;

float balls_j_r  = 10;


//if ((circleA->isBounce = false) && (circleB->isBounce = false)){




if  ( (balls_j_x - balls_i_x) * (balls_i_vx - balls_j_vx) + (balls_j_y - balls_i_y) * (balls_i_vy - balls_j_vy) > 0  )
{

float ballA = balls_j_x - balls_i_x;
float ballB = balls_j_y - balls_i_y;

	if  ((ballA) * (ballA) + ((ballB) * (ballB) ) <= (balls_j_r + balls_i_r + EPSILON) * (balls_j_r + balls_i_r + EPSILON))
	{		
			

		++total_collid;

		circleA->isBounce = true;
		circleB->isBounce = true;

	

		float nx = (balls_i_x - balls_j_x) / (10+10 );
		float ny = (balls_i_y - balls_j_y) / (10+10);
		float a1 = balls_i_vx * nx + balls_i_vy * ny;
		float a2 = balls_j_vx * nx + balls_j_vy * ny;

		float p  = 2 * (a1 - a2) / (10 + 10); //mass (5,5)


//DEFUALT
		//circleA->mVec.mX  = balls_i_vx - p * nx  * 10;//mass 
		//circleA->mVec.mY  = balls_i_vy - p * ny  * 10;//mass 

		//circleB->mVec.mX = balls_j_vx + p * nx  * 10;//mass 
		//circleB->mVec.mY = balls_j_vy + p * ny * 10; //mass 

//SOUP
		circleA->mVec.mX  =(balls_i_vx - p * nx  * 1+(((2 * (float)rand() / (float)RAND_MAX - 1)/10))*soup);
		circleA->mVec.mY = (balls_i_vy - p * ny  * 1+(((2 * (float)rand() / (float)RAND_MAX - 1)/10))*soup);

		
		circleB->mVec.mX = (balls_j_vx + p * nx  * 1+(((2 * (float)rand() / (float)RAND_MAX - 1)/10))*soup);
		circleB->mVec.mY = (balls_j_vy + p * ny  * 1+(((2 * (float)rand() / (float)RAND_MAX - 1)/10))*soup);
	


        return true;

//CIRCLES
		//circleA->mVec.mX  =balls_i_vx - p * nx  * 1;
		//circleA->mVec.mY = balls_i_vy - p * ny  * 1;

		//
		//circleB->mVec.mX = balls_j_vx + p * nx  * 1;
		//circleB->mVec.mY = balls_j_vy + p * ny * 1;


//UPDATE
		//circleA->SetLoc(balls_i_x+circleA->mVec.mX,balls_i_y+circleA->mVec.mY,0);
		//circleB->SetLoc(balls_j_x+circleB->mVec.mX,balls_j_y+circleB->mVec.mY,0);



	}; //END COLLSION

}; //END MOVING


return false;


//};



}; //END FUNCTION





//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************
void MOAIBox::Loop () {


if (threadState == 1) {

   // printf("START \n");

 total_loop		 = 0;
 total_screen    = 0;
 total_collid	 = 0;

//this->mMutex.Lock ();
// Sleep(1);
//if (delete_step == 0){
//////////////////////////////////////////////////////////////////////////////////////



//*********************************************************************
//CLEAR
    for (int i = 0; i < _GRID_WIDTH; ++i) {
           for (int j = 0; j < _GRID_HEIGHT; ++j) {
               _grid[i][j].clear();
           };
       };
	

//********************************************************************
//SORT
		int current_max = this->mHigh;
		for(std::vector<int>::size_type i = 0; i != current_max; i++) {
	//for(std::vector<int>::size_type i = 0; i != _mProps.size(); i++) {


	MOAIProp * prop = _mProps[i];		
	
	float	 ax = prop->GetXLoc();
	float	 ay = prop->GetYLoc();
	int		 x = (ax / (10*2));
	int		 y = (ay / (10*2));

//************************************************************
	//if 	(prop->isBounce == false) {
	//		//	prop->mVec.mX = prop->mVec.mX;
	//		//	prop->mVec.mY = prop->mVec.mY;	

	//			prop->mVec.mX = prop->mVec.mX+(this->mForce.mX);
	//			prop->mVec.mY = prop->mVec.mY+(this->mForce.mY);	

	//}


	//prop->SetLoc(ax+prop->mVec.mX,ay+prop->mVec.mY,0);
	//prop->ScheduleUpdate ();



//*************************************************************************************
//BOUNDS
	if (ay <= bounds_top) {

		//prop->mVec.mY =0.25;
		//prop->mVec.mY = 1+(2 * (float)rand() / (float)RAND_MAX - 1)/10;
		//prop->mVec.mY = ((100 * (float)rand() / (float)RAND_MAX )/1000);
		//prop->mVec.mY =prop->mVec.mY*-1;

		if (prop->mVec.mY <= 0) {
			prop->mVec.mY =(prop->mVec.mY*-1)*.3;
		};

	}


	if (ay >= bounds_bottom ) {


		if (prop->mVec.mY >= 0) {
			prop->mVec.mY =(prop->mVec.mY*-1)*.3;
		};

			//prop->mVec.mY = -0.25;
			//prop->mVec.mY = -1-(2 * (float)rand() / (float)RAND_MAX - 1)/10;
			//prop->mVec.mY = -((100 * (float)rand() / (float)RAND_MAX)/1000);
			//prop->mVec.mY =prop->mVec.mY*-1;
	}



	if (ax <= bounds_left) {

		if (prop->mVec.mX <= 0) {
			prop->mVec.mX =(prop->mVec.mX*-1)*.3;
		};
	
			//prop->mVec.mX = 0.25;
			//prop->mVec.mX = 1+(2 * (float)rand() / (float)RAND_MAX - 1)/10;
			//prop->mVec.mX = 1+(2 * (float)rand() / (float)RAND_MAX - 1)/10;
			//prop->mVec.mX = prop->mVec.mX *-1;
	}


	if (ax >= bounds_right) {
			//prop->mVec.mX = -0.25;
			//prop->mVec.mX = -1-(2 * (float)rand() / (float)RAND_MAX - 1)/10;
			//prop->mVec.mX = -1-(2 * (float)rand() / (float)RAND_MAX - 1)/10;
			//prop->mVec.mX = prop->mVec.mX *-1;

		if (prop->mVec.mX >= 0) {
			prop->mVec.mX =(prop->mVec.mX*-1)*.3;
		};

	}





			if (((x > -1) && x < (_GRID_WIDTH)) && ((y > -1) && y < (_GRID_HEIGHT))) {
						prop->isBounce	= false;	
						_grid[x][y].push_back(prop);
						++total_screen;

			};


};




//***************************************************************************
//***************************************************************************
//***************************************************************************
//COLLID


 //  for (size_t i = 0, ilen = things.size(); i < ilen; ++i) { /**/ }

 //TOP EXPLOED

 float simStartTime = ZLDeviceTime::GetTimeInSeconds ();


for ( u32 y = 0; y < _GRID_HEIGHT; ++y ) {

for ( u32 x = 0; x < _GRID_WIDTH; ++x ) {

 



		for(std::vector<int>::size_type i = 0; i != _grid[x][y].size(); i++) {


				MOAIProp * sendMe = _grid[x][y][i];
//
//
////***********************************************************************
////CENTER
				for(std::vector<int>::size_type j = 0; j != _grid[x][y].size(); j++) {
						++total_loop;
						if (Collide(sendMe, _grid[x][y][j])) {
                            //break;
                        }
				}; //J


//***********************************************************************
//TOP
				if (y > 0) {

		
					for(std::vector<int>::size_type j = 0; j != _grid[x][y-1].size(); j++) {
							++total_loop;
							if (Collide(sendMe, _grid[x][y-1][j]) ){
                                //break;
                            }
					}; //J


					//***********************************************************
					//LEFT
							if (x > 0)  {

										for(std::vector<int>::size_type j = 0; j != _grid[x-1][y-1].size(); j++) {
													++total_loop;
                                                    if (Collide(sendMe, _grid[x-1][y-1][j])){ 
                                                    //    break; 
                                                    };

										}; //J

							}


						//********************************************************
						//RIGHT
                                  

							if (x < _GRID_WIDTH-1) {
										for(std::vector<int>::size_type j = 0; j != _grid[x+1][y-1].size(); j++) {
													++total_loop;
													if (Collide(sendMe, _grid[x+1][y-1][j])){ 
                                                    //    break; 
                                                    };
										}; //J
							};
							
				};


			//********************************************************
			//BOTTOM
				if (y < _GRID_HEIGHT-1) {
			
							for(std::vector<int>::size_type j = 0; j != _grid[x][y+1].size(); j++) {
									++total_loop;
									if (Collide(sendMe, _grid[x][y+1][j])){ 
                                        //break; 
                                    };
							}; //J



					//********************************************************
					//LEFT
							if (x > 0)  {

										for(std::vector<int>::size_type j = 0; j != _grid[x-1][y+1].size(); j++) {
													++total_loop;
													if (Collide(sendMe, _grid[x-1][y+1][j])){ 
                                                        //break; 
                                                    };
										}; //J

							};



						//********************************************************
						//RIGHT
							if (x < _GRID_WIDTH-1) {

										for(std::vector<int>::size_type j = 0; j != _grid[x+1][y+1].size(); j++) {
													++total_loop;
													if (Collide(sendMe, _grid[x+1][y+1][j])){ 
                                                        //break; 
                                                    };
										}; //J
							};






				};


//**********************************************************************************
////////LEFT
if (x > 0)  {

		for(std::vector<int>::size_type j = 0; j != _grid[x-1][y].size(); j++) {
				  	++total_loop;
					if (Collide(sendMe, _grid[x-1][y][j])){ 
                        //break; 
                    };
		}; //J

}
			
//**********************************************************************************
//RIGHT
if (x < _GRID_WIDTH-1) {

		for(std::vector<int>::size_type j = 0; j != _grid[x+1][y].size(); j++) {
					++total_loop;

					if (Collide(sendMe, _grid[x+1][y][j])){ 
                        //break; 
                    };
		}; //J

}; //IF





};//I


}; //Y


        //printf("%f \n", (ZLDeviceTime::GetTimeInSeconds ()-simStartTime)*1000);
        float end = ZLDeviceTime::GetTimeInSeconds()-simStartTime;
        if ( end > 5) {
            printf("WTF %f \n", end);
            break;
        };


//CEHCK BREAK

}; //X






this->mCollid	= total_collid;
this->mScreen   = total_screen;
this->mTotal	= total_loop;

//printf("%f \n", (ZLDeviceTime::GetTimeInSeconds ()-simStartTime)*1000);


/////////////////////////////////////////////////////////////////////////////////////

 //  #ifndef MOAI_OS_WINDOWS
   //   Sleep ( 1);
   //#endif 

  //  printf("FINISH \n");
}; //THREAD RUNNING

//} //DELETE STEP



//if  (delete_step == 1) {
//	delete_step = 2;
//}



//this->mMutex.Unlock ();




};




vector<unsigned char> intToBytes(int paramInt)
{
     vector<unsigned char> arrayOfByte(4);
     for (int i = 0; i < 4; i++)
         arrayOfByte[3 - i] = (paramInt >> (i * 8));
     return arrayOfByte;
}



//*********************************************************************************************
//EZRA
void MOAIBox::Draw ( int subPrimID ) {
	UNUSED ( subPrimID );
    
    //if ( !( this->mFlags & FLAGS_VISIBLE )) return;
	//if ( !this->mViewport ) return;
	
	MOAIViewport& viewport = *this->mViewport;
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	
	gfxDevice.ResetState ();
	
	ZLRect viewportRect = viewport;

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
	

	gfxDevice.UpdateViewVolume ();

	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM );
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_VIEW_TRANSFORM, view );
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_PROJ_TRANSFORM, proj );

//*******************************************************
//*******************************************************
//*******************************************************
this->mProps	= _mResults.size();






//SET SUBPRIME



drawProp->Draw (  subPrimID);












//********************************************************************************************
//********************************************************************************************


//QUAD BRUSH
//gfxDevice.SetTexture ( texture );	
//gfxDevice.SetShader(shader);
//if (blend == 1) {
//	gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_SRC_ALPHA, ZGL_BLEND_FACTOR_ONE );	
//}
//
//MOAIQuadBrush::BindVertexFormat ( gfxDevice );
//MOAIQuadBrush quad;



//********************************************************************************************
//********************************************************************************************


//printf("********************\n");

//VBO NOT  NEEDED
 vbo->SetCursor(0); //CASUES CRASHES
 vbo->reset_box(); //NEEDS THIS TO RESET POINT TRIAL //THIS SETS CURSOR TO ZERO

  

   // ibo->Update(); //UPDATE ONCE


int cursor   = 0;
float cX     = 0;
float cY     = 0;

	//for(std::vector<int>::size_type i = 0; i != _mResults.size(); i++) {

int current_max = this->mHigh;


//double simStartTime = ZLDeviceTime::GetTimeInSeconds ();

	for(std::vector<int>::size_type i = 0; i != current_max; i++) {

				MOAIProp * prop = _mResults[i];	



				if 	(prop->isBounce == false) {
						prop->mVec.mX = prop->mVec.mX+(this->mForce.mX);
						prop->mVec.mY = prop->mVec.mY+(this->mForce.mY);	
				}



                        float	 ax = prop->GetXLoc();
                        float	 ay = prop->GetYLoc();						

                        prop->isBounce = false;		
                        prop->SetLoc(ax+(prop->mVec.mX),ay+(prop->mVec.mY),0);




//*****************************************************************************************


         /*               float	 ax = 500;
                        float	 ay = 500;	

                        float	 vxx = 0;
                        float	 vyy = 0;
                       

                        float	 ddx = 500;
                        float	 ddy = 500;	
                        float	 ddz = 500;	*/

//printf("--------%d \n",i);



//*****************************************************************
//*****************************************************************
		
 /*                       gfxDevice.SetPenColor ( prop->mR, prop->mG, prop->mB, prop->mA );	
						quad.SetVerts ( ax-size, ay-size, ax+size, ay+size );
						quad.SetUVs ( 0, 0, 1, 1 );	
						quad.Draw ();*/
//*****************************************************************
//*****************************************************************
//STRIPES : IBO
					    //vbo->writeFloat_loc ( ax - size, ay - size);
         //               cursor = cursor + 24;
         //               vbo->SetCursor(cursor);

					    //vbo->writeFloat_loc( ax - size, ay + size );			
         //               cursor = cursor + 24;
         //               vbo->SetCursor(cursor);
	
					    //vbo->writeFloat_loc ( ax + size, ay - size );
         //               cursor = cursor + 24;
         //               vbo->SetCursor(cursor);

					    //vbo->writeFloat_loc ( ax + size, ay + size );
         //               cursor = cursor + 24;
         //               vbo->SetCursor(cursor);		
 






//*****************************************************************
//*****************************************************************




  /*      if (i > 0) {

                vbo->writeFloat_loc( cX, cY );        
                cursor = cursor + 24;
                vbo->SetCursor(cursor);

                vbo->writeFloat_loc( ax - size, ay - size );
                cursor = cursor + 24;
                vbo->SetCursor(cursor);
	

        };


                    vbo->writeFloat_loc( ax - size, ay - size );				
                    cursor = cursor + 24;
                    vbo->SetCursor(cursor);
 
                    vbo->writeFloat_loc ( ax + size, ay - size );
                    cursor = cursor + 24;
                    vbo->SetCursor(cursor);


                    vbo->writeFloat_loc ( ax - size, ay + size);
                    cursor = cursor + 24;
                    vbo->SetCursor(cursor);

 
                    vbo->writeFloat_loc ( ax + size, ay + size );
                    cursor = cursor + 24;
                    vbo->SetCursor(cursor);
 


                 cX  =   ax + size;
                 cY  =  ay + size ;

*/

 // vbo->SetCursor(cursor);

					            //float R =prop->mR;
					            //float G =prop->mG; 
					            //float B =prop->mB; 
					            //float A =prop->mA;


   /*                             vbo->writeFloat_loc( ax - size, ay - size );
                                vbo->writeFloat_uv ( 0, 0);
                                vbo->writeColor_rgb (R,G,B,A );
 

                                vbo->writeFloat_loc ( ax + size, ay + size );
                                vbo->writeFloat_uv ( 1, 0 );
                                vbo->writeColor_rgb (R,G,B,A );
*/



    //vertexBuffer:writeFloat(math.random(500,600),math.random(300,400),0) --POSITION
    //vertexBuffer:writeColor32(math.random(), math.random(), math.random(), 1) --COLOR
    //vertexBuffer:writeFloat(math.random(20,20)) --SIZE

//printf("\n");
//vbo->SetCursor(cursor);
//
//vbo->pCursor();

//if (i == 0) { ax = 100.0f; }
//if (i == 1) { ax = 200.0f; }
//if (i == 2) { ax = 300.0f; }
//if (i == 3) { ax = 400.0f; }
//if (i == 4) { ax = 500.0f; }
//
//
//if (i == 5) { ax = 600.0f; }
//if (i == 6) { ax = 700.0f; }
//if (i == 7) { ax = 800.0f; }
//if (i == 8) { ax = 900.0f; }
//if (i == 9) { ax = 1000.0f; }



//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//SKIP BUFFER
//vbo->writeFloat_loc ( ax, ay  );
//cursor = cursor + 20;
//vbo->SetCursor(cursor);

//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************

//float R =prop->mR;
//float G =prop->mG; 
//float B =prop->mB; 
//float A =prop->mA;

//printf("%f _ %f \n",ax,ay);

vbo->writeFloat_loc ( ax,ay);

//vbo->writeColor_rgb (R,G,B,A );
//vbo->writeFloat_size (size);



//vbo->pCursor();

cursor = cursor + 20;
vbo->SetCursor(cursor);








//vbo->pCursor();
//
//cursor = cursor + 24;
//vbo->SetCursor(cursor);
//vbo->pCursor();
////
////cursor = cursor + 4;
////vbo->SetCursor(cursor);
////vbo->pCursor();

//vbo->writeColor_rgb (R,G,B,A );
//vbo->writeFloat_size (size);


//
//cursor = cursor + 20;
//vbo->SetCursor(cursor);


  //  vbo->pCursor();

  //  vbo->pCursor();


//printf("\n");




                                //if (i > 0) {

                                //        vbo->writeFloat_loc( cX,cY );
                                //        vbo->writeFloat_uv ( 1, 1 );
                                //        vbo->writeColor_rgb (R,G,B,A );

                                //        cursor = cursor + 24;
                                //        vbo->SetCursor(cursor);
                                //             
                                //        vbo->writeFloat_loc( ax - size, ay - size );
                                //        vbo->writeFloat_uv ( 0, 0 );
                                //        vbo->writeColor_rgb (R,G,B,A );
                                //      //  cursor = cursor + 24;
                                //      //  vbo->SetCursor(cursor);


                                //};




                              //  vbo->writeFloat_loc( ax - size, ay - size );

                              //  vbo->writeFloat_uv ( 0, 0);
                              //  vbo->writeColor_rgb (R,G,B,A );
 
                              ////  cursor = cursor + 24;
                              ////  vbo->SetCursor(cursor);

                              //  vbo->writeFloat_loc ( ax + size, ay - size );
                              //  vbo->writeFloat_uv ( 1, 0 );
                              //  vbo->writeColor_rgb (R,G,B,A );

                              // // cursor = cursor + 24;
                              // // vbo->SetCursor(cursor);


                              //  vbo->writeFloat_loc ( ax - size, ay + size);
                              //   vbo->writeFloat_uv ( 0, 1 );
                              //  vbo->writeColor_rgb (R,G,B,A );

                              //  //cursor = cursor + 24;
                              //  //vbo->SetCursor(cursor);

 
                              //  vbo->writeFloat_loc ( ax + size, ay + size );
					           
                              //  vbo->writeFloat_uv ( 1, 1 );
                              //  vbo->writeColor_rgb (R,G,B,A ); 

                              // // cursor = cursor + 24;
                              // // vbo->SetCursor(cursor);
              
                              //  cX =   ax + size;
                              //  cY =   ay + size; 


//printf("\n");










  



                 //if (i > 0) {

                 //       vbo->writeFloat_loc( cX,cY );
                 //       cursor = cursor + 24;
                 //       vbo->SetCursor(cursor);
				


                 //       vbo->writeFloat_loc( ax - size, ay - size );
		
                 //       cursor = cursor + 24;
                 //       vbo->SetCursor(cursor);

                 //       };




                 //       vbo->writeFloat_loc( ax - size, ay - size );
                 //       cursor = cursor + 24;
                 //       vbo->SetCursor(cursor);
 
                 //       vbo->writeFloat_loc ( ax + size, ay - size );
                 //       cursor = cursor + 24;
                 //       vbo->SetCursor(cursor);


                 //       vbo->writeFloat_loc ( ax - size, ay + size);
                 //       cursor = cursor + 24;
                 //       vbo->SetCursor(cursor);

 
                 //       vbo->writeFloat_loc ( ax + size, ay + size );
                 //       cursor = cursor + 24;
                 //       vbo->SetCursor(cursor);
              
                 //       cX =   ax + size;
                 //       cY =   ay + size;                       




//*****************************************************************
//*****************************************************************







				////VBO	shit	
					//int R =prop->mR;
					//int G =prop->mG; 
					//int B =prop->mB; 
					//int A =prop->mA;

					//vbo->writeFloat_loc( ax - size, ay + size );
					//vbo->writeFloat_uv ( 0, 0 );
					//vbo->writeColor_rgb (R,G,B,A );
 
					//vbo->writeFloat_loc ( ax + size, ay + size );
					//vbo->writeFloat_uv ( 1, 0 );
					//vbo->writeColor_rgb (R,G,B,A );
 
					//vbo->writeFloat_loc ( ax + size, ay - size );
					//vbo->writeFloat_uv ( 1, 1 );
					//vbo->writeColor_rgb (R,G,B,A );
 
					//vbo->writeFloat_loc ( ax - size, ay - size );
					//vbo->writeFloat_uv ( 0, 1 );
					//vbo->writeColor_rgb (R,G,B,A );
					
				
                   
 
 






					
	        		//gfxDevice.SetPenColor ( 1, 0, 1, 1 );
					//MOAIQuadBrush::BindVertexFormat ( gfxDevice );

					//quad.SetVerts ( ax-100, ay-100, ax-32-100, ay-100-32 );
					//quad.SetUVs ( 0, 0, 1, 1 );	
					//quad.Draw ();




     //   			gfxDevice.SetPenColor ( 1, 1, 0, 1 );
					//MOAIQuadBrush::BindVertexFormat ( gfxDevice );

					//quad.SetVerts ( ax+100, ay+100, ax+32+100, ay+100+32 );
					//quad.SetUVs ( 0, 0, 1, 1 );	
					//quad.Draw ();



					//const ZLColorVec& orgColor = gfxDevice.GetPenColor ();
					//gfxDevice.SetBlendMode ();
					//gfxDevice.SetPenColor ( orgColor );

			


//**********************************************************************
//RORATE


			//	MOAIDraw::DrawEllipseFill ( ax, ay, 20, 20, 40 );
			//	MOAIDraw::DrawEllipseOutline ( ax, ay, 10, 10, 20 );
//
				//USVec3D rot = prop->GetRot ();
				//rot.mX		= rot.mX;
				//rot.mY		= rot.mY;
				//rot.mZ		= rot.mZ+0.5;
				//prop->SetRot(rot);

			//	printf("%f %f %f \n",rot.mX,rot.mY,rot.mZ );
		
			

				//prop->ScheduleUpdate ();

                        

	}


   // vbo->bless_box();

//printf("%f \n", (ZLDeviceTime::GetTimeInSeconds ()-simStartTime)*1000);





//NOT NEEDED


//****************************************************
//VERTEX 



//ALWAYS
//gfxDevice.Flush ();

  


       // vbo->bless_box();
        //vbo->Bind();
       // gfxDevice.Flush ();









//****************************************************
//CALL EITHER FOR LESS PROPS

            //MOAIDraw::Bind ();
            //gfxDevice.Flush ();











//MOAIBox::Loop ();

	//if (soup == 1) {
		//MOAIBox::Loop ();
	//}




	//if (delete_step == 2) {


	//for ( u32 i = 0; i < 500; ++i ) {
	//	MOAIProp * prop = _mResults[_mResults.size()-1];
	//	_mProps.erase(   _mProps.end()	-1);
	//	_mResults.erase( _mResults.end() -1);	
	//
	//	this->mPartition->RemoveProp ( *prop );
	//	prop->ScheduleUpdate ();

	//	//delete prop;
	//	//prop->setfi

	//};



	//		delete_step = 0;
	//}

	//printf("delete_step %d \n",delete_step);






	




};
















//----------------------------------------------------------------//
/**	@name	insertProp
	@text	Adds a prop to the layer's partition.
	
	@in		MOAIBox self
	@in		MOAIProp prop
	@out	nil
*/
int	MOAIBox::_insertProp ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "UU" )

	MOAIProp* prop = state.GetLuaObject < MOAIProp >( 2, true );

	if ( !prop ) return 0;
	if ( prop == self ) return 0;

	self->AffirmPartition ();
	//self->mPartition->InsertProp ( *prop );

	_mProps.push_back(prop);
	_mResults.push_back(prop);
	prop->ScheduleUpdate ();

	//self->mPartition->

	return 0;
}




//----------------------------------------------------------------//
/**	@name	removeProp
	@text	Removes a prop from the layer's partition.
	
	@in		MOAIBox self
	@in		MOAIProp prop
	@out	nil
*/
int	MOAIBox::_removeProp ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "UU" )

	MOAIProp* prop = state.GetLuaObject < MOAIProp >( 2, true );
	if ( !prop ) return 0;
	if ( prop == self ) return 0;

	//self->mPartition->RemoveProp ( *prop );


//if (delete_step == 0) {
//	delete_step = 1;
//}

	//if ( self->mPartition ) {

		//_mProps.erase(   _mProps.end()	-1);
		//_mResults.erase( _mResults.end() -1);	

	//	self->mPartition->RemoveProp ( *prop );
	//	prop->ScheduleUpdate ();



	//}

	return 0;
}






//*************************************************************************
//FORCE
int	MOAIBox::_setforce ( lua_State* L ) {

	MOAI_LUA_SETUP ( MOAIBox, "U" )
	
		self->mForce.mX = state.GetValue < float >( 2, 1.0f );
		self->mForce.mY = state.GetValue < float >( 3, 1.0f  );
		self->mForce.mZ = state.GetValue < float >( 4, 1.0f  );
	
	return 0;
};



//**************************************************************************************************
//THREAD
int	MOAIBox::_threadMake ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )

    //** 1.4p0 -->	task->Start ( *tThread, MOAISim::Get ().GetTaskSubscriber ());



tThread = new	MOAITaskThread();
task	= new	MOAIEzraTask ();
task->Init ( *self, MOAIEzraTask::SAVE_ACTION ); 



//task->threadRunning(true);
//task->Start ( *tThread, MOAIMainThreadTaskSubscriber::Get ());
//task->mLoopState = false;
//tThread->Stop();
//task->mLoopState = false;
//task->mLoopState = true;
//task->Execute();
//tThread->Stop();
//task->Start ( *tThread, MOAIMainThreadTaskSubscriber::Get ());
//task->Start ( *tThread, MOAISim::Get ().GetTaskSubscriber );





//*******************************************************************
//*******************************************************************
//*******************************************************************
//BUFFER ARRAY

printf("SET VERTEX BUFFER\n");

// *******MAKE THEM IN LUA **************//

		//MOAIVertexFormat * vertexFormat = new MOAIVertexFormat();	
		//vertexFormat->DeclareAttribute ( 0, ZGL_TYPE_FLOAT, 0, 3, false );	
		//vertexFormat->DeclareAttribute ( 1, ZGL_TYPE_FLOAT, 0, 2, false );	
		//vertexFormat->DeclareAttribute ( 2, ZGL_TYPE_UNSIGNED_BYTE, 5, 0, true );
		//
		//MOAIVertexBuffer * vbo = new MOAIVertexBuffer;
		//vbo->mFormat.Set (*self, vertexFormat ); //IN ACCESIABLE
		//vbo->Reserve ( 4 * 10000 );


	


    printf("THREAD MAKE : DONE  \n");

	return 0;
}






//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************


//START
int	MOAIBox::_threadStart ( lua_State* L ) {

MOAI_LUA_SETUP ( MOAIBox, "U" )

    task->threadRunning(true);
    threadState = 1;
    task->Start ( *tThread, MOAIMainThreadTaskSubscriber::Get ());
    //task->IsRunning
    //task->IsRun
    //printf("THREAD STARTED \n");
    //tThread->mThread->IsRunning();

  
    return 0;
};


//STOP
int	MOAIBox::_threadStop ( lua_State* L ) {

	MOAI_LUA_SETUP ( MOAIBox, "U" )       

   task->threadRunning(false);
   threadState = 0;
   tThread->Stop();


   printf("THREAD STOPPED \n");
  
   return 0;
};


//RELEASE
int	MOAIBox::_threadRelease ( lua_State* L ) {

	MOAI_LUA_SETUP ( MOAIBox, "U" )       

            task->threadRunning(false);
            threadState = 0;
            tThread->Stop();
            tThread->Release();  
      
        
             printf("THREAD RELEASE \n");

   return 0;
};















//**************************************************************************************************
//SOUP
int	MOAIBox::_soup ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )	

	//self->mBounce = state.GetValue < bool >( 2, true );
	//tThread->Stop();
	soup	= state.GetValue < int >( 2, true );


	return 0;
}



//**************************************************************************************************
//SOUP
int	MOAIBox::_bounds ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )	

	const int left 		= state.GetValue < int >( 2, 0 );
	const int top 		= state.GetValue < int >( 3, 0 );
	const int right 	= state.GetValue < int >( 4, 0 );
	const int bottom	= state.GetValue < int >( 5, 0 );

	 _GRID_WIDTH =	(int)(right / (10 * 2.0f));
	 _GRID_HEIGHT = (int)(bottom / (10 * 2.0f)); 


	bounds_left		=   left  +20;
	bounds_top		=	top   +20;
	bounds_right	=	right -20;
	bounds_bottom	=   bottom-20;


	printf("X %d Y %d \n",_GRID_WIDTH,_GRID_HEIGHT);
	printf("RIGHT %d BOTTOM %d \n",bounds_right,bounds_bottom);

	return 0;
}



//**************************************************************************************************
//SOUP
int	MOAIBox::_size ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )	

	 size 		= state.GetValue < int >( 2, 0 );

     vbo->reset_box();     

    for(std::vector<int>::size_type i = 0; i != _mResults.size(); i++) {

		                MOAIProp* prop = _mResults[i];   
				        float	 ax = prop->GetXLoc();
				        float	 ay = prop->GetYLoc();		
                            
				
					    float R =prop->mR;
					    float G =prop->mG; 
					    float B =prop->mB; 
					    float A =prop->mA;

                        vbo->writeFloat_loc ( ax, ay  );
                        vbo->writeColor_rgb (R,G,B,A );
                        vbo->writeFloat_size (size);

    };







	return 0;
}

//**************************************************************************************************
//SHADER
int	MOAIBox::_shader ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )	

	 
		 shader = state.GetLuaObject < MOAIShader >( 2, true );
		 blend  = state.GetValue < int >( 3, 0 );

	return 0;
}






int	MOAIBox::_insertDraw ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "UU" )

	MOAIProp* prop = state.GetLuaObject < MOAIProp >( 2, true );

	if ( !prop ) return 0;
	if ( prop == self ) return 0;

	drawProp = prop;
	prop->ScheduleUpdate ();

	//self->mPartition->

	return 0;
}


//**************************************************************************************************
//SET TEXTURE
int	MOAIBox::_texture ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )	
	texture	= state.GetLuaObject < MOAITexture>( 2, false );
	return 0;
}


//**************************************************************************************************
//SET BUFFERS
int	MOAIBox::_buffers ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )	
	vbo	= state.GetLuaObject < MOAIVertexBuffer>( 2, false );
	ibo	= state.GetLuaObject < MOAIIndexBuffer>( 3, false );

	return 0;
};




//**************************************************************************************************
//SET BOOM
int	MOAIBox::_boom ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )	

ZLBox box;
	


box.mMin.mX = state.GetValue < float >( 2, 0.0f );
box.mMin.mY = state.GetValue < float >( 3, 0.0f );
box.mMin.mZ = 0.0f;
	
box.mMax.mX = state.GetValue < float >( 4, 0.0f );
box.mMax.mY = state.GetValue < float >( 5, 0.0f );
box.mMax.mZ = 0.0f;

int charge = state.GetValue < int >( 6, 3 );

	
float x1	 =  box.mMax.mX-(box.mMax.mX-box.mMin.mX)*0.5;
float y1	 =  box.mMax.mY-(box.mMax.mY-box.mMin.mY)*0.5;
float width  =  box.mMax.mY-box.mMin.mY;


	int current_max = self->mHigh;
	for(std::vector<int>::size_type i = 0; i != current_max; i++) {	
		
			MOAIProp * prop = _mResults[i];	

			float x2 = prop->GetXLoc();
			float y2 = prop->GetYLoc();

			float distance =   sqrt( (x2-x1)*(x2-x1) + (y2-y1)* (y2-y1) );		

			if (distance < (width/2)) {

						float angle = atan2(  (y2 - y1) , (x2 -x1) );
						float dx 	= cos(angle)  * charge;
						float dy 	= sin(angle)  * charge;

						prop->mVec.mX = dx;
						prop->mVec.mY = dy;	
						//prop->m

			};

			
	};



	return 0;
}




//**************************************************************************************************
//BOUNCE
int	MOAIBox::_bounce ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )	
	self->mBounce = state.GetValue < bool >( 2, true );
	return 0;
};







//**************************************************************************************************
//BOUNCE
int	MOAIBox::_color ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )	


   vbo->reset_box();     

    for(std::vector<int>::size_type i = 0; i != _mResults.size(); i++) {

		                MOAIProp* prop = _mResults[i];   
				        float	 ax = prop->GetXLoc();
				        float	 ay = prop->GetYLoc();		
                            
				    ////VBO	shit	
					    float R =prop->mR;
					    float G =prop->mG; 
					    float B =prop->mB; 
					    float A =prop->mA;

                        vbo->writeFloat_loc ( ax, ay  );
                        vbo->writeColor_rgb (R,G,B,A );
                        vbo->writeFloat_size (size);

              


                         //printf("UPDATING COLOR %f %f %f %f\n",R,G,B,A);

					    //vbo->writeFloat_loc( ax - size, ay + size );
					    //vbo->writeFloat_uv ( 0, 0 );
					    //vbo->writeColor_rgb (R,G,B,A );
 
					    //vbo->writeFloat_loc ( ax + size, ay + size );
					    //vbo->writeFloat_uv ( 1, 0 );
					    //vbo->writeColor_rgb (R,G,B,A );
 
					    //vbo->writeFloat_loc ( ax + size, ay - size );
					    //vbo->writeFloat_uv ( 1, 1 );
					    //vbo->writeColor_rgb (R,G,B,A );
 
					    //vbo->writeFloat_loc ( ax - size, ay - size);
					    //vbo->writeFloat_uv ( 0, 1 );
					    //vbo->writeColor_rgb (R,G,B,A );








    };

// vbo->reset_box();  
//vbo->bless_box();

    return 0;


}





//**************************************************************************************************
//BOUNCE
int	MOAIBox::_high ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBox, "U" )	

	int newHigh = state.GetValue < int >( 2, true );
	int temphigh = self->mHigh + newHigh;
	int oldhigh  = self->mHigh;


	if (temphigh < 0) { temphigh = 0;} ;
	if  (temphigh >  _mProps.size()) {temphigh = _mProps.size();} ;

	self->mHigh = temphigh;



//**********************************************************************
//REMOVE TO PARTIN
//if (newHigh > 0)  {




printf("_high _high : _high %d\n",temphigh);
printf("_high _high : _high %d\n",temphigh);
printf("_high _high : _high %d\n",temphigh);




//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//VBO
    // vbo->reset_box(); //NEDS THIS TO RESET POINT TRIAL
    // vbo->SetCursor(-1);
     int curSprite =0;



vbo->ReserveV (temphigh);
vbo->reset_box();


//vbo->ReserveV (4 * temphigh);

ibo->ReserveIndices(temphigh);


int cX = 0;
int cY = 0;





    int current_max = self->mHigh;
	for(std::vector<int>::size_type i = 0; i != current_max; i++) {

		                MOAIProp* prop = _mResults[i];

              

             

//******************************************************************************
//******************************************************************************   
//******************************************************************************
//DONT TOUCH : INDEX FOR TRAINAGLES :

				                     ibo->SetIndex ( i * 1 + 0, i * 1 + 0 );

					                //ibo->SetIndex ( i * 6 + 1, i * 4 + 3 );
					                //ibo->SetIndex ( i * 6 + 2, i * 4 + 2 );
					                //ibo->SetIndex ( i * 6 + 3, i * 4 + 0 );
					                //ibo->SetIndex ( i * 6 + 4, i * 4 + 2 );
					                //ibo->SetIndex ( i * 6 + 5, i * 4 + 1 );	
//******************************************************************************
//******************************************************************************   
//******************************************************************************
//DONT TOUCH : INDEX FOR TRAINAGLES_STRIP
                        

				                 //   ibo->SetIndex ( i * 8 + 0, i * 4 + 0 );
					                //ibo->SetIndex ( i * 8 + 1, i * 4 + 1 );
					                //ibo->SetIndex ( i * 8 + 2, i * 4 + 2 );
					                //ibo->SetIndex ( i * 8 + 3, i * 4 + 3 );
					                //ibo->SetIndex ( i * 8 + 4, i * 4 + 3 );
					                //ibo->SetIndex ( i * 8 + 5, i * 4 + 0 );	
					                //ibo->SetIndex ( i * 8 + 6, i * 4 + 0 );
					                //ibo->SetIndex ( i * 8 + 7, i * 4 + 4 );	


                           //FRIST DRAW
				                float	 ax = prop->GetXLoc();
				                float	 ay = prop->GetYLoc();		
                            
				            ////VBO	shit	
					            float R =prop->mR;
					            float G =prop->mG; 
					            float B =prop->mB; 
					            float A =prop->mA;


                                vbo->writeFloat_loc ( ax, ay  );
                                vbo->writeColor_rgb (R,G,B,A );
                                vbo->writeFloat_size (size);



//******************************************************************************
//******************************************************************************   
//******************************************************************************
	/*				    vbo->writeFloat_loc( ax - size, ay + size );
					    vbo->writeFloat_uv ( 0, 0 );
					    vbo->writeColor_rgb (R,G,B,A );
 
					    vbo->writeFloat_loc ( ax + size, ay + size );
					    vbo->writeFloat_uv ( 1, 0 );
					    vbo->writeColor_rgb (R,G,B,A );
 
					    vbo->writeFloat_loc ( ax + size, ay - size );
					    vbo->writeFloat_uv ( 1, 1 );
					    vbo->writeColor_rgb (R,G,B,A );
 
					    vbo->writeFloat_loc ( ax - size, ay - size);
					    vbo->writeFloat_uv ( 0, 1 );
					    vbo->writeColor_rgb (R,G,B,A );*/
//******************************************************************************
//******************************************************************************
//******************************************************************************

         //               vbo->writeFloat_loc ( ax - size, ay - size);
					    //vbo->writeFloat_uv ( 0, 1 );
         //               vbo->writeColor_rgb (1,1,1,1 );


					    //vbo->writeFloat_loc( ax - size, ay + size );
					    //vbo->writeFloat_uv ( 0, 0 );
					    //vbo->writeColor_rgb (1,1,1,1 );
 

					    //vbo->writeFloat_loc ( ax + size, ay - size );
					    //vbo->writeFloat_uv ( 1, 1 );
		       //         vbo->writeColor_rgb (1,1,1,1 );

					    //vbo->writeFloat_loc ( ax + size, ay + size );
					    //vbo->writeFloat_uv ( 1, 0 );
		       //         vbo->writeColor_rgb (1,1,1,1 );
 

 



		//--TOP-LEFT
		//vbo:writeFloat ( -32, -32 )
		//vbo:writeFloat ( 0, 0 )
		//vbo:writeColor32 ( 1, 1, 1 )

		//--TOP-RIGHT
		//vbo:writeFloat ( 32, -32 )
		//vbo:writeFloat ( 1, 0 )
		//vbo:writeColor32 ( 1, 1, 1 )


		//--BOTTOM-RIGHT
		//vbo:writeFloat ( -32, 32 )
		//vbo:writeFloat ( 0, 1 )
		//vbo:writeColor32 ( 1, 1, 1 )



		//--BOTTOM-LEFT
		//vbo:writeFloat ( 32, 32 )
		//vbo:writeFloat ( 1, 1 )
		//vbo:writeColor32 ( 1, 1, 1 )





              //                   if (i > 0) {

              //                        			vbo->writeFloat_loc( cX,cY );
					         //                   vbo->writeFloat_uv ( 0, 0 );
					         //                         vbo->writeColor_rgb (R,G,B,A );


				          //                      vbo->writeFloat_loc( ax - size, ay - size );
					         //                   vbo->writeFloat_uv ( 0, 0 );
					         //                   vbo->writeColor_rgb (R,G,B,A );


              //                  };




	             //               vbo->writeFloat_loc( ax - size, ay - size );
					         //   vbo->writeFloat_uv ( 0, 0);
					         //   vbo->writeColor_rgb (R,G,B,A );
 
					         //   vbo->writeFloat_loc ( ax + size, ay - size );
					         //   vbo->writeFloat_uv ( 1, 0 );
					         //   vbo->writeColor_rgb (R,G,B,A );


					         //   vbo->writeFloat_loc ( ax - size, ay + size);
					         //   vbo->writeFloat_uv ( 0, 1 );
					         //   vbo->writeColor_rgb (R,G,B,A );

 
					         //   vbo->writeFloat_loc ( ax + size, ay + size );
					         //   vbo->writeFloat_uv ( 1, 1 );
						        //vbo->writeColor_rgb (R,G,B,A ); 
              //
              //                  cX =   ax + size;
              //                  cY =   ay + size; 



	        };


//vbo->reset_box();
//vbo->bless_box();

//vbo->reset_box();

 //vbo->reset_box();








//}

lua_pushnumber ( state, self->mHigh);

	return 1;


}




//**************************************************************************************************
MOAIBox::MOAIBox () :
	mParallax ( 1.0f, 1.0f, 1.0f ),
	mShowDebugLines ( true ),
	mSortMode ( MOAIPartitionResultBuffer::SORT_NONE ),
	mPartitionCull2D ( true ) {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIProp )
		RTTI_EXTEND ( MOAIClearableView )
	RTTI_END
	
	this->SetMask ( MOAIProp::CAN_DRAW | MOAIProp::CAN_DRAW_DEBUG );
	this->SetClearFlags ( 0 );

//EZRA
	this->mForce.mX  =0;
	this->mForce.mY  =0;
	this->tick		 =0;
	this->mThread    =0;
	this->mHigh		 =0;

    tThread = 0;
    task    = 0;


       printf(">>>>>>>>> START\n");
//MAKE THREAD
     //   tThread = new	MOAITaskThread();
     //   task	= new	MOAIEzraTask ();
     //   task->Init ( *this, MOAIEzraTask::SAVE_ACTION ); 
   //   printf(">>>>>>>>> END\n");



}


void MOAIBox::Finalize() {

     printf(" \n Finalize Finalize Finalize \n");
     printf(" \n Finalize Finalize Finalize \n");
     printf(" \n Finalize Finalize Finalize \n");

   task->threadRunning(false);
   threadState = 0;
   tThread->Stop();


};


//----------------------------------------------------------------//
void MOAIBox::Clear () {

	////this->mMutex.Lock ();
	////this->mBytes.Clear ();
 //           //tThread->Stop();
 //          // printf("RELEASE DONE");
 //           ////////////////

 //           //if (tThread) {
 //           //        //printf(" \n RELEASE \n");
 //           //       //  tThread->Release();
 //           //            printf(" \n TASK RELASE \n");
 //           //            task->LatchRelease();
 //           //            //task->LatchRelease();

 //           //            tThread->Stop();

 //           //        printf(" \n DELETE THREAD \n");
	//           //     delete tThread;
	//	          //  tThread = 0;
 //           //};



 //           //if (task) {
 //           //         printf("\n DELETE TASK \n");
	//           //     delete task;
	//	          //  task = 0;
 //           //};
	////this->mMutex.Unlock ();

}



//----------------------------------------------------------------//
//MOAIBox::!MOAIBox () {
//     printf(">>>>>>>>>C  CRASH box\n");
//};

//----------------------------------------------------------------//
MOAIBox::~MOAIBox () {
    
	//this->mMutex.Lock ();
	//this->mBytes.Clear ();
	//this->mMutex.Unlock ();

   // tThread->Join();
     //tThread->Join();

    printf(">>>>>>>>>C  CRASH box\n");
	this->mCamera.Set ( *this, 0 );
	this->mViewport.Set ( *this, 0 );
	this->mPartition.Set ( *this, 0 );

    printf(">>>>>>>>>> D CRASH box -DONE\n");

     this->Clear ();

////	//printf("\nDESTRUCTION>>>>>>>>>>>>>>>>>>>\n");
//if (threadState == 1) {
//
//        this->Clear ();
//  //tThread->Join();
//        printf(">>>>>>>>>> D THREAD KILL\n");
//     //   threadState = 0;
//        //task->Clear();
//       // tThread->Clear();
//	   // tThread->Stop();
//
//      //  task->
//
//
//        // delete task;
//
//         //delete tThread;
//        // delete task;
//
//            //tThread = new	MOAITaskThread();
//            //task	= new	MOAIEzraTask ();
//            //task->Init ( *self, MOAIEzraTask::SAVE_ACTION ); 
//       printf(">>>>>>>>>> E THREAD KILL - done\n");
//}
//
//
//	//this->mMutex.Lock ();
//	//this->mBytes.Clear ();
//	//this->mMutex.Unlock ();
//
//  printf("\n \n **** 4. MOAIBox --> FIRE DESTRUCTOR  ****  \n\n");
//


	//self->Clear ();
	//self->Clear ();

}




//----------------------------------------------------------------//
void MOAIBox::RegisterLuaClass ( MOAILuaState& state ) {

	MOAIProp::RegisterLuaClass ( state );
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
void MOAIBox::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	MOAIProp::RegisterLuaFuncs ( state );
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

		{ "setforce",				_setforce },
		{ "bounce",					_bounce },
		{ "getTotal",				_total },	
		{ "sethigh",				_high },	
		{ "makeThread",				_threadMake },
        { "startThread",			_threadStart },
        { "stopThread",				_threadStop },
        { "releaseThread",  		_threadRelease },

		{ "results",				_results },
		{ "makeSoup",				_soup },
		{ "setBounds",				_bounds },
		{ "setTexture",				_texture },
		{ "setDraw",				_insertDraw },
		{ "setSize",				_size },
		{ "setShader",				_shader },
		{ "setBoom",				_boom },
		{ "setBuffers",				_buffers },
        { "updateColor",			_color },

		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIBox::Render () {	
	this->Draw ( MOAIProp::NO_SUBPRIM_ID );
}





//**********************************************************************************
//----------------------------------------------------------------//
void MOAIBox::SerializeIn ( MOAILuaState& state, MOAIDeserializer& serializer ) {
	//MOAIProp::SerializeIn ( state, serializer );
}

//----------------------------------------------------------------//
void MOAIBox::SerializeOut ( MOAILuaState& state, MOAISerializer& serializer ) {
	//MOAIProp::SerializeOut ( state, serializer );
}