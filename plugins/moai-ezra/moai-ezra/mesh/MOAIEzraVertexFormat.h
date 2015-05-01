// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIEZRAVERTEXFORMAT_H
#define	MOAIEZRAVERTEXFORMAT_H

//================================================================//
// MOAIEzraVertexAttributeUse
//================================================================//
class MOAIEzraVertexAttributeUse {
private:

	friend class MOAIEzraVertexFormat;
	
	u32			mUse;
	u32			mAttrID;
};

//================================================================//
// MOAIEzraVertexAttribute
//================================================================//
class MOAIEzraVertexAttribute {
private:

	friend class MOAIEzraVertexFormat;
	
	u32			mIndex;
	u32			mSize;
	u32			mType;			// type of the element
	bool		mNormalized;
	u32			mOffset;
};

//================================================================//
// MOAIEzraVertexFormat
//================================================================//
/**	@name	MOAIEzraVertexFormat
	@text	Vertex format class.
*/
class MOAIEzraVertexFormat :
	public virtual MOAILuaObject {
public:

	enum {
		ARRAY_COLOR,
		ARRAY_NORMAL,
		ARRAY_TEX_COORD,
		ARRAY_VERTEX,
		TOTAL_ARRAY_TYPES,
	};

private:

	static const u32 COLOR_SIZE				= 4;
	static const u32 NORMAL_SIZE			= 3;
	static const u32 NULL_INDEX				= 0xffffffff;
	
	ZLLeanArray < MOAIEzraVertexAttribute >		mAttributes;
	u32										mTotalAttributes;
	u32										mVertexSize;

	MOAIEzraVertexAttributeUse					mAttributeUseTable [ TOTAL_ARRAY_TYPES ]; // use for fixed function pipeline
	
	//----------------------------------------------------------------//
	static int		_declareAttribute				( lua_State* L );
	static int		_declareColor					( lua_State* L );
	static int		_declareCoord					( lua_State* L );
	static int		_declareNormal					( lua_State* L );
	static int		_declareUV						( lua_State* L );
	
	//----------------------------------------------------------------//
	bool			Bind							( void* buffer ) const;
	void			BindFixed						( void* buffer ) const;
	void			BindProgrammable				( void* buffer ) const;
	static u32		GetComponentSize				( u32 size, u32 type );
	static u32		GetIndexForUse					( u32 use );
	static u32		GetUseForIndex					( u32 idx );
	void			Unbind							() const;
	void			UnbindFixed						() const;
	void			UnbindProgrammable				() const;
	
public:
	
	friend class MOAIGfxDevice;
	
	DECL_LUA_FACTORY ( MOAIEzraVertexFormat )
	
	GET_CONST ( u32, VertexSize, mVertexSize )
	
	//----------------------------------------------------------------//
	bool			ComputeBounds					( void* buffer, u32 size, ZLBox& bounds );
	void			DeclareAttribute				( u32 index, u32 type, u32 size, u32 use, bool normalized );
					MOAIEzraVertexFormat				();
					~MOAIEzraVertexFormat				();
	void			RegisterLuaClass				( MOAILuaState& state );
	void			RegisterLuaFuncs				( MOAILuaState& state );
};

#endif
