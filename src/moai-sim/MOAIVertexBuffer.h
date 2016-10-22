// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIVERTEXBUFFER_H
#define	MOAIVERTEXBUFFER_H

class MOAIVertexFormat;

//================================================================//
// MOAIVertexBuffer
//================================================================//
/**	@name	MOAIVertexBuffer
	@text	Vertex buffer class.
*/
class MOAIVertexBuffer :
	public MOAILuaObject {
private:

	MOAILuaSharedPtr < MOAIVertexFormat > mFormat;

	ZLLeanArray < u8 >	mBuffer;
	ZLByteStream		mStream;
	ZLBox				mBounds;
	
	//----------------------------------------------------------------//
	static int		_bless					( lua_State* L );
	static int		_release				( lua_State* L );
	static int		_reserve				( lua_State* L );
	static int		_reserveVerts			( lua_State* L );
	static int		_reset					( lua_State* L );
	static int		_setFormat				( lua_State* L );
	static int		_writeColor32			( lua_State* L );
	static int		_writeFloat				( lua_State* L );
	static int		_writeInt8				( lua_State* L );
	static int		_writeInt16				( lua_State* L );
	static int		_writeInt32				( lua_State* L );


	
	//----------------------------------------------------------------//
	void			Clear					();
	
public:
	
	DECL_LUA_FACTORY ( MOAIVertexBuffer )
	
	GET ( const ZLBox&, Bounds, mBounds )
	GET ( MOAIVertexFormat*, Format, mFormat )
	
	//----------------------------------------------------------------//
	bool			Bind					();
	u32				GetVertexCount			();
	bool			IsValid					();
					MOAIVertexBuffer		();
					~MOAIVertexBuffer		();
	void			RegisterLuaClass		( MOAILuaState& state );
	void			RegisterLuaFuncs		( MOAILuaState& state );
	void			Reserve					( u32 size );
	void			Unbind					();


	void			ReserveVerts			(int total); 
	void			writeVert			(float x,float y,float z);
	void			writeNormal			(float x,float y,float z);
	void			writeUV				(float u,float v);

	void			writeData	(int x,int y,int z, float u,float v, float r,float g,float b,float a);
	void			reset		();
	void			setCursor	(long index);
};

#endif
