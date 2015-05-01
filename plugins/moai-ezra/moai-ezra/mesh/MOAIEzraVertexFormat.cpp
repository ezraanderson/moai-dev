// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIGfxDevice.h>

#include <moai-ezra/Mesh/MOAIEzraVertexFormat.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	declareAttribute
	@text	Declare a custom attribute (for use with programmable pipeline).
	
	@in		MOAIEzraVertexFormat self
	@in		number index		Default value is 1.
	@in		number type			Data type of component elements. See OpenGL ES documentation.
	@in		number size			Number of elements. See OpenGL ES documentation.
	@opt	boolean normalized	See OpenGL ES documentation.
	@out	nil
*/
int	MOAIEzraVertexFormat::_declareAttribute ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIEzraVertexFormat, "UNNN" )

	u32 index			= state.GetValue < u32 >( 2, 1 ) - 1;
	u32 type			= state.GetValue < u32 >( 3, 0 );
	u32 size			= state.GetValue < u32 >( 4, 0 );
	bool normalized		= state.GetValue < bool >( 5, false );

	self->DeclareAttribute ( index, type, size, 0, normalized );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	declareColor
	@text	Declare a vertex color.
	
	@in		MOAIEzraVertexFormat self
	@in		number index
	@in		number type			Data type of component elements. See OpenGL ES documentation.
	@out	nil
*/
int MOAIEzraVertexFormat::_declareColor ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIEzraVertexFormat, "UNN" )

	u32 index			= state.GetValue < u32 >( 2, 1 ) - 1;
	u32 type			= state.GetValue < u32 >( 3, 0 );
	
	self->DeclareAttribute ( index, type, COLOR_SIZE, ARRAY_COLOR, true );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	declareCoord
	@text	Declare a vertex coordinate.
	
	@in		MOAIEzraVertexFormat self
	@in		number index
	@in		number type			Data type of coordinate elements. See OpenGL ES documentation.
	@in		number size			Number of coordinate elements. See OpenGL ES documentation.
	@out	nil
*/
int MOAIEzraVertexFormat::_declareCoord ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIEzraVertexFormat, "UNNN" )

	u32 index			= state.GetValue < u32 >( 2, 1 ) - 1;
	u32 type			= state.GetValue < u32 >( 3, 0 );
	u32 size			= state.GetValue < u32 >( 4, 0 );
	
	self->DeclareAttribute ( index, type, size, ARRAY_VERTEX, false );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	declareNormal
	@text	Declare a vertex normal.
	
	@in		MOAIEzraVertexFormat self
	@in		number index
	@in		number type			Data type of normal elements. See OpenGL ES documentation.
	@out	nil
*/
int MOAIEzraVertexFormat::_declareNormal ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIEzraVertexFormat, "UNN" )
	
	u32 index			= state.GetValue < u32 >( 2, 1 ) - 1;
	u32 type			= state.GetValue < u32 >( 3, 0 );
	
	self->DeclareAttribute ( index, type, NORMAL_SIZE, ARRAY_NORMAL, false );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	declareUV
	@text	Declare a vertex texture coordinate.
	
	@in		MOAIEzraVertexFormat self
	@in		number index
	@in		number type			Data type of texture coordinate elements. See OpenGL ES documentation.
	@in		number size			Number of texture coordinate elements. See OpenGL ES documentation.
	@out	nil
*/
int MOAIEzraVertexFormat::_declareUV ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIEzraVertexFormat, "UNNN" )

	u32 index			= state.GetValue < u32 >( 2, 1 ) - 1;
	u32 type			= state.GetValue < u32 >( 3, 0 );
	u32 size			= state.GetValue < u32 >( 4, 0 );
	
	self->DeclareAttribute ( index, type, size, ARRAY_TEX_COORD, false );

	return 0;
}

//================================================================//
// MOAIEzraVertexFormat
//================================================================//

//----------------------------------------------------------------//
bool MOAIEzraVertexFormat::Bind ( void* buffer ) const {

	if ( buffer ) {
		if ( MOAIGfxDevice::Get ().IsProgrammable ()) {
			this->BindProgrammable ( buffer );
		}
		else {
			this->BindFixed ( buffer );
		}
		return true;
	}
	return false;
}

//----------------------------------------------------------------//
void MOAIEzraVertexFormat::BindFixed ( void* buffer ) const {
	UNUSED ( buffer );

	#if USE_OPENGLES1
		for ( u32 i = 0; i < TOTAL_ARRAY_TYPES; ++i ) {
		
			const MOAIEzraVertexAttributeUse& attrUse = this->mAttributeUseTable [ i ];
			
			if ( attrUse.mAttrID == NULL_INDEX ) {
				zglDisableClientState ( attrUse.mUse );
			}
			else {
			
             

				MOAIEzraVertexAttribute& attr = this->mAttributes [ attrUse.mAttrID ];
				
				void* addr = ( void* )(( size_t )buffer + attr.mOffset );
				
				switch ( attrUse.mUse ) {
					case ZGL_PIPELINE_COLOR_ARRAY:
						zglColorPointer ( attr.mSize, attr.mType, this->mVertexSize, addr );
						break;
					case ZGL_PIPELINE_NORMAL_ARRAY:
						zglNormalPointer ( attr.mType, this->mVertexSize, addr );
						break;
					case ZGL_PIPELINE_TEXTURE_COORD_ARRAY:
						zglTexCoordPointer ( attr.mSize, attr.mType, this->mVertexSize, addr );
						break;
					case ZGL_PIPELINE_VERTEX_ARRAY:
						zglVertexPointer ( attr.mSize, attr.mType, this->mVertexSize, addr );
						break;
					default:
						break;
				}
				zglEnableClientState ( attrUse.mUse );
			}
		}
	#endif
}

//----------------------------------------------------------------//
void MOAIEzraVertexFormat::BindProgrammable ( void* buffer ) const {

	for ( u32 i = 0; i < this->mTotalAttributes; ++i ) {
		
		MOAIEzraVertexAttribute& attr = this->mAttributes [ i ];

		void* addr = ( void* )(( size_t )buffer + attr.mOffset );
		zglVertexAttribPointer (	attr.mIndex, attr.mSize, attr.mType, attr.mNormalized, this->mVertexSize, addr );
		zglEnableVertexAttribArray ( attr.mIndex );
	}
}

//----------------------------------------------------------------//
bool MOAIEzraVertexFormat::ComputeBounds ( void* buffer, u32 size, ZLBox& bounds ) {


    printf("\n \n --- ComputeBounds -- %d \n\n", this->mVertexSize);


	u32 total = this->mVertexSize ? ( size / this->mVertexSize ) : 0;
	if ( !total ) return false;

	u32 coordAttributeIdx = this->mAttributeUseTable [ ARRAY_VERTEX ].mAttrID;
	if ( coordAttributeIdx >= this->mTotalAttributes ) return false;

	MOAIEzraVertexAttribute& coordAttr = this->mAttributes [ coordAttributeIdx ];
	if ( coordAttr.mType != ZGL_TYPE_FLOAT ) return false; // TODO: handle other types
	if ( coordAttr.mSize < 2 ) return false;
	
	buffer = ( void* )(( size_t )buffer + coordAttr.mOffset );
	
	float* components = ( float* )buffer;
	
	ZLVec3D coord ( components [ 0 ], components [ 1 ], (  coordAttr.mSize > 2 ? components [ 2 ] : 0.0f ));
	
	bounds.Init ( coord );
	bounds.Inflate ( 0.0000001f ); // prevent 'empty' bounds on cardinal direction lines or single vertex objects
	
	for ( u32 i = 1; i < total; ++i ) {
		
		buffer = ( void* )(( size_t )buffer + this->mVertexSize );
		components = ( float* )buffer;
		coord.Init ( components [ 0 ], components [ 1 ], (  coordAttr.mSize > 2 ? components [ 2 ] : 0.0f ));
		bounds.Grow ( coord );
	}
	return true;
}

//----------------------------------------------------------------//
void MOAIEzraVertexFormat::DeclareAttribute ( u32 index, u32 type, u32 size, u32 use, bool normalized ) {

	u32 attrID = this->mTotalAttributes++;
	this->mAttributes.Grow ( this->mTotalAttributes );
	MOAIEzraVertexAttribute& attr = this->mAttributes [ attrID ];
	
	u32 offset = this->mVertexSize;
	
	attr.mIndex         = index;
	attr.mSize          = size;
	attr.mType          = type;
	attr.mNormalized    = normalized;
	attr.mOffset        = offset;
	
	this->mVertexSize += MOAIEzraVertexFormat::GetComponentSize ( size, type );
	
	//u32 useIdx = MOAIEzraVertexFormat::GetIndexForUse ( use );
	u32 useIdx = use;
	if ( useIdx < TOTAL_ARRAY_TYPES ) {
		this->mAttributeUseTable [ useIdx ].mAttrID = attrID;
	}
}

//----------------------------------------------------------------//
u32 MOAIEzraVertexFormat::GetComponentSize ( u32 size, u32 type ) {

	u32 bytes;
	switch ( type ) {
	
		case ZGL_TYPE_BYTE:
		case ZGL_TYPE_UNSIGNED_BYTE:
			bytes = 1;
			break;
		
		case ZGL_TYPE_SHORT:

            //bytes = 2;
			//break;


		case ZGL_TYPE_UNSIGNED_SHORT:
			bytes = 2;
			break;
		
		//case ZGL_FIXED:
		case ZGL_TYPE_FLOAT:
			bytes = 4;
			break;
		
		default:
			bytes = 0;
			break;		
	}
	
	return size * bytes;
}

//----------------------------------------------------------------//
u32 MOAIEzraVertexFormat::GetIndexForUse ( u32 use ) {
	UNUSED ( use );

	#if USE_OPENGLES1
		switch ( use ) {
			case ZGL_PIPELINE_COLOR_ARRAY:			return ARRAY_COLOR;
			case ZGL_PIPELINE_NORMAL_ARRAY:			return ARRAY_NORMAL;
			case ZGL_PIPELINE_TEXTURE_COORD_ARRAY:	return ARRAY_TEX_COORD;
			case ZGL_PIPELINE_VERTEX_ARRAY:			return ARRAY_VERTEX;
			default:								break;
		}
	#endif
	return NULL_INDEX;
}

//----------------------------------------------------------------//
u32 MOAIEzraVertexFormat::GetUseForIndex ( u32 idx ) {
	UNUSED ( idx );

	#if USE_OPENGLES1
		switch ( idx ) {
			case ARRAY_COLOR:			return ZGL_PIPELINE_COLOR_ARRAY;
			case ARRAY_NORMAL:			return ZGL_PIPELINE_NORMAL_ARRAY;
			case ARRAY_TEX_COORD:		return ZGL_PIPELINE_TEXTURE_COORD_ARRAY;
			case ARRAY_VERTEX:			return ZGL_PIPELINE_VERTEX_ARRAY;
			default:					break;
		}
	#endif
	return 0;
}

//----------------------------------------------------------------//
MOAIEzraVertexFormat::MOAIEzraVertexFormat () :
	mTotalAttributes ( 0 ),
	mVertexSize ( 0 ) {
	
	RTTI_SINGLE ( MOAILuaObject )
	
	this->mAttributes.Init ( TOTAL_ARRAY_TYPES );
	
	for ( u32 i = 0; i < TOTAL_ARRAY_TYPES; ++i ) {
		this->mAttributeUseTable [ i ].mUse = MOAIEzraVertexFormat::GetUseForIndex ( i );
		this->mAttributeUseTable [ i ].mAttrID = NULL_INDEX;
	}
}

//----------------------------------------------------------------//
MOAIEzraVertexFormat::~MOAIEzraVertexFormat () {
}

//----------------------------------------------------------------//
void MOAIEzraVertexFormat::RegisterLuaClass ( MOAILuaState& state ) {
	
	state.SetField ( -1, "GL_BYTE", ( u32 )ZGL_TYPE_BYTE );
	//state.SetField ( -1, "GL_FIXED", ( u32 )GL_FIXED );
	state.SetField ( -1, "GL_FLOAT", ( u32 )ZGL_TYPE_FLOAT );
	state.SetField ( -1, "GL_SHORT", ( u32 )ZGL_TYPE_SHORT );
	state.SetField ( -1, "GL_UNSIGNED_BYTE", ( u32 )ZGL_TYPE_UNSIGNED_BYTE );
	state.SetField ( -1, "GL_UNSIGNED_SHORT", ( u32 )ZGL_TYPE_UNSIGNED_SHORT );
}

//----------------------------------------------------------------//
void MOAIEzraVertexFormat::RegisterLuaFuncs ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{ "declareAttribute",		_declareAttribute },
		{ "declareColor",			_declareColor },
		{ "declareCoord",			_declareCoord },
		{ "declareNormal",			_declareNormal },
		{ "declareUV",				_declareUV },
		{ NULL, NULL }
	};
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIEzraVertexFormat::Unbind () const {

	if ( MOAIGfxDevice::Get ().IsProgrammable ()) {
		this->UnbindProgrammable ();
	}
	else {
		this->UnbindFixed ();
	}
}

//----------------------------------------------------------------//
void MOAIEzraVertexFormat::UnbindFixed () const {

	#if USE_OPENGLES1
		for ( u32 i = 0; i < TOTAL_ARRAY_TYPES; ++i ) {
			zglDisableClientState ( this->mAttributeUseTable [ i ].mUse );
		}
	#endif
}

//----------------------------------------------------------------//
void MOAIEzraVertexFormat::UnbindProgrammable () const {

	for ( u32 i = 0; i < this->mTotalAttributes; ++i ) {
		
		MOAIEzraVertexAttribute& attr = this->mAttributes [ i ];
		zglDisableVertexAttribArray ( attr.mIndex );
	}
}
