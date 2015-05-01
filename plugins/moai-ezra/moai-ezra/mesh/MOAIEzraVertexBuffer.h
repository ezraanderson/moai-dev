// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIEZRAVERTEXBUFFER_H
#define	MOAIEZRAVERTEXBUFFER_H

class MOAIEzraVertexFormat;

//================================================================//
// MOAIVertexBuffer
//================================================================//
/**	@name	MOAIVertexBuffer
	@text	Vertex buffer class.
*/
class MOAIEzraVertexBuffer :
	public MOAILuaObject {
private:

	MOAILuaSharedPtr < MOAIVertexFormat > mFormat;

	ZLLeanArray < u8 >	mBuffer;
	ZLByteStream		mStream;
	ZLBox				mBounds;
    int                 mTotal;

 
	
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

    static int		_writeRings				( lua_State* L );
    static int		_writeCircles			( lua_State* L );
    static int		_writeLines				( lua_State* L );
    static int		_writeRects				( lua_State* L );

    static int		_setCursorZero			( lua_State* L );
    static int		_writeGeo   			( lua_State* L );

	//----------------------------------------------------------------//
	void			Clear					();
	
public:
	
	DECL_LUA_FACTORY ( MOAIEzraVertexBuffer )
	
	GET ( const ZLBox&, Bounds, mBounds )
	GET ( MOAIVertexFormat*, Format, mFormat )
	
	//----------------------------------------------------------------//
	bool			Bind					();
	u32				GetVertexCount			();
	bool			IsValid					();
					MOAIEzraVertexBuffer		();
					~MOAIEzraVertexBuffer		();
	void			RegisterLuaClass		( MOAILuaState& state );
	void			RegisterLuaFuncs		( MOAILuaState& state );
	void			Reserve					( u32 size );
	void			Unbind					();

	void			writeFloat_loc			(float a, float b);
    void			writeColor_rgb			(float r, float g,float b, float a);
    void			writeFloat_size			(float a);

 

    void            SetCursor               (long index );
    void            pCursor                 ();	

	void			writeFloat_uv			(s8 a, s8 b);

	


	void			bless_box				( );
	void			reset_box				( ) ;
    void            ReserveV                ( long size ); 


};

#endif


