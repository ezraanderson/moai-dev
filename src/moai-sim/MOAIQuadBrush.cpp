// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIQuadBrush.h>
#include <moai-sim/MOAIVertexFormatMgr.h>
#include <math.h>
//================================================================//
// MOAIQuadBrush
//================================================================//

//----------------------------------------------------------------//
void MOAIQuadBrush::BindVertexFormat ( MOAIGfxDevice& gfxDevice ) {
	
	gfxDevice.SetVertexPreset ( MOAIVertexFormatMgr::XYZWUVC );
	gfxDevice.SetPrimType ( ZGL_PRIM_TRIANGLES );
}

//----------------------------------------------------------------//
void MOAIQuadBrush::Draw () {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	gfxDevice.WriteQuad ( this->mVtx, this->mUV );
}

//----------------------------------------------------------------//
void MOAIQuadBrush::Draw ( float xOff, float yOff, float zOff ) {
	
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	gfxDevice.WriteQuad ( this->mVtx, this->mUV, xOff, yOff, zOff ); 
}

//----------------------------------------------------------------//
void MOAIQuadBrush::Draw ( float xOff, float yOff, float zOff, float xScale, float yScale ) {
	
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	gfxDevice.WriteQuad ( this->mVtx, this->mUV, xOff, yOff, zOff, xScale, yScale ); 
}

//----------------------------------------------------------------//
void MOAIQuadBrush::Draw ( float xOff, float yOff, float zOff, float xScale, float yScale, float uOff, float vOff, float uScale, float vScale ) {
	
MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();



float rad	  = 90*(PI/180);
float rad_cos = cos(rad);
float rad_sin = sin(rad);


int x[4] = { -0.5, 0.5, 0.5, -0.5 };
int y[4] = { 0.5, 0.5, -0.5, -0.5 };

double x0 = -0.5;
double y0 =  0.5;

double x1 = 0.5;
double y1 = 0.5;

double x2 =  0.5;
double y2 = -0.5;

double x3 = -0.5;
double y3 = -0.5;


////0 *********************************************************************************
//x1 = -0.5;
//y1 = 0.5;
//this->mVtx [ 0 ].mX =  x1 * rad_cos - y1 * rad_sin; 
//this->mVtx [ 0 ].mY =  x1 * rad_sin + y1 * rad_cos;
////1 *********************************************************************************
//x1 = 0.5;
//y1 = 0.5;
//this->mVtx [ 1 ].mX =x1 * rad_cos - y1 * rad_sin; 
//this->mVtx [ 1 ].mY =x1 * rad_sin + y1 * rad_cos;
////2 *********************************************************************************
//x1 = 0.5;
//y1 = -0.5;
//this->mVtx [ 2 ].mX = x1 * rad_cos - y1 * rad_sin;  
//this->mVtx [ 2 ].mY = x1 * rad_sin + y1 * rad_cos;
////3 *********************************************************************************
//x1 = -0.5;
//y1 = -0.5;
//this->mVtx [ 3 ].mX = x1 * rad_cos - y1 * rad_sin; 
//this->mVtx [ 3 ].mY = x1 * rad_sin + y1 * rad_cos;




//if (true) {
//	//0 *********************************************************************************
//	this->mVtx[0].mX = -0.5;
//	this->mVtx[0].mY = -0.5;
//	//1 *********************************************************************************
//	this->mVtx[1].mX = -0.5;
//	this->mVtx[1].mY =  0.5;
//	//2 *********************************************************************************
//	this->mVtx[2].mX =  0.5;
//	this->mVtx[2].mY =  0.5;
//	//3 *********************************************************************************
//	this->mVtx[3].mX =  0.5;
//	this->mVtx[3].mY = -0.5;
//
//}



//printf("___________________\n");
//printf("0: %f %f  \n",	this->mVtx [ 0 ].mX,this->mVtx [ 0 ].mY);
//printf("1: %f %f  \n",	this->mVtx [ 1 ].mX,this->mVtx [ 1 ].mY);
//printf("2: %f %f \n",	this->mVtx [ 2 ].mX,this->mVtx [ 2 ].mY);
//printf("3: %f %f  \n",	this->mVtx [ 3 ].mX,this->mVtx [ 3 ].mY);


gfxDevice.WriteQuad ( this->mVtx, this->mUV, xOff, yOff, zOff, xScale, yScale, uOff, vOff, uScale, vScale ); 

	



}



//----------------------------------------------------------------//
void MOAIQuadBrush::Draw_up(float xOff, float yOff, float zOff, float xScale, float yScale, float uOff, float vOff, float uScale, float vScale) {


	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	//0 *********************************************************************************
	this->mVtx[0].mX = -0.5;
	this->mVtx[0].mY = 0.5;
	//1 *********************************************************************************
	this->mVtx[1].mX = 0.5;
	this->mVtx[1].mY =  0.5;
	//2 *********************************************************************************
	this->mVtx[2].mX =  0.5;
	this->mVtx[2].mY =  -0.5;
	//3 *********************************************************************************
	this->mVtx[3].mX =  -0.5;
	this->mVtx[3].mY = -0.5;

	gfxDevice.WriteQuad(this->mVtx, this->mUV, xOff, yOff, zOff, xScale, yScale, uOff, vOff, uScale, vScale);

}
//----------------------------------------------------------------//
void MOAIQuadBrush::Draw_right(float xOff, float yOff, float zOff, float xScale, float yScale, float uOff, float vOff, float uScale, float vScale) {
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	//0 *********************************************************************************
	this->mVtx[0].mX = -0.5;
	this->mVtx[0].mY = -0.5;
	//1 *********************************************************************************
	this->mVtx[1].mX = -0.5;
	this->mVtx[1].mY = 0.5;
	//2 *********************************************************************************
	this->mVtx[2].mX = 0.5;
	this->mVtx[2].mY = 0.5;
	//3 *********************************************************************************
	this->mVtx[3].mX = 0.5;
	this->mVtx[3].mY = -0.5;

	gfxDevice.WriteQuad(this->mVtx, this->mUV, xOff, yOff, zOff, xScale, yScale, uOff, vOff, uScale, vScale);

}

//----------------------------------------------------------------//
void MOAIQuadBrush::Draw_down(float xOff, float yOff, float zOff, float xScale, float yScale, float uOff, float vOff, float uScale, float vScale) {
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	//0 *********************************************************************************
	this->mVtx[0].mX = 0.5;
	this->mVtx[0].mY = -0.5;
	//1 *********************************************************************************
	this->mVtx[1].mX = -0.5;
	this->mVtx[1].mY = -0.5;
	//2 *********************************************************************************
	this->mVtx[2].mX = -0.5;
	this->mVtx[2].mY = 0.5;
	//3 *********************************************************************************
	this->mVtx[3].mX = 0.5;
	this->mVtx[3].mY = 0.5;

	gfxDevice.WriteQuad(this->mVtx, this->mUV, xOff, yOff, zOff, xScale, yScale, uOff, vOff, uScale, vScale);

}

//----------------------------------------------------------------//
void MOAIQuadBrush::Draw_left(float xOff, float yOff, float zOff, float xScale, float yScale, float uOff, float vOff, float uScale, float vScale) {
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	//0 *********************************************************************************
	this->mVtx[0].mX = 0.5;
	this->mVtx[0].mY = 0.5;
	//1 *********************************************************************************
	this->mVtx[1].mX = 0.5;
	this->mVtx[1].mY = -0.5;
	//2 *********************************************************************************
	this->mVtx[2].mX = -0.5;
	this->mVtx[2].mY = -0.5;
	//3 *********************************************************************************
	this->mVtx[3].mX = -0.5;
	this->mVtx[3].mY = 0.5;

	gfxDevice.WriteQuad(this->mVtx, this->mUV, xOff, yOff, zOff, xScale, yScale, uOff, vOff, uScale, vScale);

}





//----------------------------------------------------------------//
ZLRect MOAIQuadBrush::GetUVBounds () {

	ZLRect rect;
	
	rect.Init ( this->mUV [ 0 ]);
	rect.Grow ( this->mUV [ 1 ]);
	rect.Grow ( this->mUV [ 2 ]);
	rect.Grow ( this->mUV [ 3 ]);
	
	return rect;
}

//----------------------------------------------------------------//
ZLRect MOAIQuadBrush::GetVtxBounds () {

	ZLRect rect;
	
	rect.Init ( this->mVtx [ 0 ]);
	rect.Grow ( this->mVtx [ 1 ]);
	rect.Grow ( this->mVtx [ 2 ]);
	rect.Grow ( this->mVtx [ 3 ]);
	
	return rect;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::ScaleUVs ( float xScale, float yScale ) {

	this->mUV [ 0 ].Scale ( xScale, yScale );
	this->mUV [ 1 ].Scale ( xScale, yScale );
	this->mUV [ 2 ].Scale ( xScale, yScale );
	this->mUV [ 3 ].Scale ( xScale, yScale );
}

//----------------------------------------------------------------//
void MOAIQuadBrush::ScaleVerts ( float xScale, float yScale ) {

	this->mVtx [ 0 ].Scale ( xScale, yScale );
	this->mVtx [ 1 ].Scale ( xScale, yScale );
	this->mVtx [ 2 ].Scale ( xScale, yScale );
	this->mVtx [ 3 ].Scale ( xScale, yScale );
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetUVs ( const ZLRect& rect ) {
	
	// left top
	this->mUV [ 0 ].mX = rect.mXMin;
	this->mUV [ 0 ].mY = rect.mYMax;
	
	// right top
	this->mUV [ 1 ].mX = rect.mXMax;
	this->mUV [ 1 ].mY = rect.mYMax;
	
	// right bottom
	this->mUV [ 2 ].mX = rect.mXMax;
	this->mUV [ 2 ].mY = rect.mYMin;
	
	// left bottom
	this->mUV [ 3 ].mX = rect.mXMin;
	this->mUV [ 3 ].mY = rect.mYMin;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetUVs ( float* buffer ) {

	// left top
	this->mUV [ 0 ].mX = buffer [ 0 ];
	this->mUV [ 0 ].mY = buffer [ 1 ];
	
	// right top
	this->mUV [ 1 ].mX = buffer [ 2 ];
	this->mUV [ 1 ].mY = buffer [ 3 ];
	
	// right bottom
	this->mUV [ 2 ].mX = buffer [ 4 ];
	this->mUV [ 2 ].mY = buffer [ 5 ];
	
	// left bottom
	this->mUV [ 3 ].mX = buffer [ 6 ];
	this->mUV [ 3 ].mY = buffer [ 7 ];
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetUVs ( float x0, float y0, float x1, float y1 ) {
	
	// left top
	this->mUV [ 0 ].mX = x0;
	this->mUV [ 0 ].mY = y1;
	
	// right top
	this->mUV [ 1 ].mX = x1;
	this->mUV [ 1 ].mY = y1;
	
	// right bottom
	this->mUV [ 2 ].mX = x1;
	this->mUV [ 2 ].mY = y0;
	
	// left bottom
	this->mUV [ 3 ].mX = x0;
	this->mUV [ 3 ].mY = y0;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetUVs ( const USVec2D& v0, const USVec2D& v1,const  USVec2D& v2, const USVec2D& v3 ) {

	// left top
	this->mUV [ 0 ] = v0;
	
	// right top
	this->mUV [ 1 ] = v1;
	
	// right bottom
	this->mUV [ 2 ] = v2;
	
	// left bottom
	this->mUV [ 3 ] = v3;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetUVs ( float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3 ) {

	// left top
	this->mUV [ 0 ].mX = x0;
	this->mUV [ 0 ].mY = y0;
	
	// right top
	this->mUV [ 1 ].mX = x1;
	this->mUV [ 1 ].mY = y1;
	
	// right bottom
	this->mUV [ 2 ].mX = x2;
	this->mUV [ 2 ].mY = y2;
	
	// left bottom
	this->mUV [ 3 ].mX = x3;
	this->mUV [ 3 ].mY = y3;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetVerts ( const ZLRect& rect ) {
	
	// left top
	this->mVtx [ 0 ].mX = rect.mXMin;
	this->mVtx [ 0 ].mY = rect.mYMax;
	
	// right top
	this->mVtx [ 1 ].mX = rect.mXMax;
	this->mVtx [ 1 ].mY = rect.mYMax;
	
	// right bottom
	this->mVtx [ 2 ].mX = rect.mXMax;
	this->mVtx [ 2 ].mY = rect.mYMin;
	
	// left bottom
	this->mVtx [ 3 ].mX = rect.mXMin;
	this->mVtx [ 3 ].mY = rect.mYMin;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetVerts ( float* buffer ) {

	// left top
	this->mVtx [ 0 ].mX = buffer [ 0 ];
	this->mVtx [ 0 ].mY = buffer [ 1 ];
	
	// right top
	this->mVtx [ 1 ].mX = buffer [ 2 ];
	this->mVtx [ 1 ].mY = buffer [ 3 ];
	
	// right bottom
	this->mVtx [ 2 ].mX = buffer [ 4 ];
	this->mVtx [ 2 ].mY = buffer [ 5 ];
	
	// left bottom
	this->mVtx [ 3 ].mX = buffer [ 6 ];
	this->mVtx [ 3 ].mY = buffer [ 7 ];
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetVerts ( float x0, float y0, float x1, float y1 ) {
	
	// left top
	this->mVtx [ 0 ].mX = x0;
	this->mVtx [ 0 ].mY = y1;
	
	// right top
	this->mVtx [ 1 ].mX = x1;
	this->mVtx [ 1 ].mY = y1;
	
	// right bottom
	this->mVtx [ 2 ].mX = x1;
	this->mVtx [ 2 ].mY = y0;
	
	// left bottom
	this->mVtx [ 3 ].mX = x0;
	this->mVtx [ 3 ].mY = y0;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetVerts ( const USVec2D& v0, const USVec2D& v1, const USVec2D& v2, const USVec2D& v3 ) {

	// left top
	this->mVtx [ 0 ] = v0;
	
	// right top
	this->mVtx [ 1 ] = v1;
	
	// right bottom
	this->mVtx [ 2 ] = v2;
	
	// left bottom
	this->mVtx [ 3 ] = v3;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetVerts ( float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3 ) {

	// left top
	this->mUV [ 0 ].mX = x0;
	this->mUV [ 0 ].mY = y0;
	
	// right top
	this->mUV [ 1 ].mX = x1;
	this->mUV [ 1 ].mY = y1;
	
	// right bottom
	this->mUV [ 2 ].mX = x2;
	this->mUV [ 2 ].mY = y2;
	
	// left bottom
	this->mUV [ 3 ].mX = x3;
	this->mUV [ 3 ].mY = y3;
}

//----------------------------------------------------------------//
void MOAIQuadBrush::SetVerts ( const USVec2D& v0, float radius ) {

	this->SetVerts (
		v0.mX - radius,
		v0.mY - radius,
		v0.mX + radius,
		v0.mY + radius
	);
}

//----------------------------------------------------------------//
void MOAIQuadBrush::TransformVerts ( const ZLAffine3D& mtx ) {
	
	mtx.Transform ( this->mVtx [ 0 ]);
	mtx.Transform ( this->mVtx [ 1 ]);
	mtx.Transform ( this->mVtx [ 2 ]);
	mtx.Transform ( this->mVtx [ 3 ]);
}

//----------------------------------------------------------------//
void MOAIQuadBrush::TransformUVs ( const ZLAffine3D& mtx ) {

	mtx.Transform ( this->mUV [ 0 ]);
	mtx.Transform ( this->mUV [ 1 ]);
	mtx.Transform ( this->mUV [ 2 ]);
	mtx.Transform ( this->mUV [ 3 ]);
}
