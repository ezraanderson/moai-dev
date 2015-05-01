// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-ezra/mesh/MOAIEzraIndexBuffer.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	release
	@text	Release any memory held by this index buffer.
	
	@in		MOAIEzraIndexBuffer self
	@out	nil
*/
int	MOAIEzraIndexBuffer::_release ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIEzraIndexBuffer, "U" )
	
	self->Clear ();
	return 0;
}

//----------------------------------------------------------------//
/**	@name	reserve
	@text	Set capacity of buffer.
	
	@in		MOAIEzraIndexBuffer self
	@in		number nIndices
	@out	nil
*/
int	MOAIEzraIndexBuffer::_reserve ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIEzraIndexBuffer, "UN" )
	
	u32 indexCount = state.GetValue < u32 >( 2, 0 );
	self->ReserveIndices ( indexCount );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setIndex
	@text	Initialize an index.
	
	@in		MOAIEzraIndexBuffer self
	@in		number idx
	@in		number value
	@out	nil
*/
int	MOAIEzraIndexBuffer::_setIndex ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIEzraIndexBuffer, "UNN" )
	
	u32 idx		= state.GetValue < u32 >( 2, 1 ) - 1;
	u32 value	= state.GetValue < u16 >( 3, 1 ) - 1;
	
	self->SetIndex ( idx, value );
	
	return 0;
}

//================================================================//
// MOAIGfxQuadListDeck2D
//================================================================//

//----------------------------------------------------------------//
bool MOAIEzraIndexBuffer::IsRenewable () {

	return true;
}

//----------------------------------------------------------------//
bool MOAIEzraIndexBuffer::IsValid () {

	return ( this->mGLBufferID != 0 );
}

//----------------------------------------------------------------//
bool MOAIEzraIndexBuffer::LoadGfxState () {

	return this->Bind ();
}

//----------------------------------------------------------------//
MOAIEzraIndexBuffer::MOAIEzraIndexBuffer () :
	mBuffer ( 0 ),
	mIndexCount ( 0 ),
	mGLBufferID ( 0 ),
	mHint ( ZGL_BUFFER_USAGE_STATIC_DRAW )

	//PARTICLE_SOUP
   // mHint ( ZGL_BUFFER_USAGE_DYNAMIC_DRAW )    
    {
	
	RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
MOAIEzraIndexBuffer::~MOAIEzraIndexBuffer () {

	this->Clear ();
}

//----------------------------------------------------------------//
void MOAIEzraIndexBuffer::OnBind () {

	if ( this->mGLBufferID ) {
		zglBindBuffer ( ZGL_BUFFER_TARGET_ELEMENT_ARRAY, this->mGLBufferID );
	}
}

//----------------------------------------------------------------//
void MOAIEzraIndexBuffer::OnClear () {
	
	if ( this->mBuffer ) {
		free ( this->mBuffer );
		this->mBuffer = 0;
	}
}

//----------------------------------------------------------------//
void MOAIEzraIndexBuffer::OnCreate () {
	if ( this->mBuffer ) {		
		this->mGLBufferID = zglCreateBuffer ();
		if ( this->mGLBufferID ) {
    
			zglBindBuffer ( ZGL_BUFFER_TARGET_ELEMENT_ARRAY, this->mGLBufferID );
			zglBufferData ( ZGL_BUFFER_TARGET_ELEMENT_ARRAY, this->mIndexCount * sizeof ( u32 ), this->mBuffer, this->mHint );
		
		}
	}
}

//----------------------------------------------------------------//
void MOAIEzraIndexBuffer::OnDestroy () {

	if ( this->mGLBufferID ) {
		zglDeleteBuffer ( this->mGLBufferID );
		this->mGLBufferID = 0;
	}
}

//----------------------------------------------------------------//
void MOAIEzraIndexBuffer::OnInvalidate () {

	this->mGLBufferID = 0;
}

//----------------------------------------------------------------//
void MOAIEzraIndexBuffer::OnLoad () {
}

//----------------------------------------------------------------//
void MOAIEzraIndexBuffer::RegisterLuaClass ( MOAILuaState& state ) {
	UNUSED ( state );
}

//----------------------------------------------------------------//
void MOAIEzraIndexBuffer::RegisterLuaFuncs ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{ "release",			_release },
		{ "reserve",			_reserve },
		{ "setIndex",			_setIndex },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIEzraIndexBuffer::ReserveIndices ( u32 indexCount ) {
	this->Clear ();	
	this->mIndexCount = indexCount;
	this->mBuffer = ( u32* )malloc ( indexCount * sizeof ( u32 ));	
	this->Load ();
}

//----------------------------------------------------------------//
void MOAIEzraIndexBuffer::SetIndex ( u32 idx, u32 value ) {

	if ( idx < this->mIndexCount ) {
		this->mBuffer [ idx ] = value;
	}
}
