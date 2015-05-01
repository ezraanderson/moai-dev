// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIEZRAMESH_H
#define	MOAIEZRAMESH_H

#include <moai-sim/MOAIDeck.h>

class MOAIIndexBuffer;
class MOAITextureBase;
class MOAIVertexBuffer;
class MOAIEzraVertexBuffer;
//================================================================//
// MOAIEzraMesh
//================================================================//
/**	@name	MOAIEzraMesh
	@text	Loads a texture and renders the contents of a vertex buffer.
			Grid drawing not supported.
	
	@const	GL_POINTS
	@const	GL_LINES
	@const	GL_TRIANGLES
	@const	GL_LINE_LOOP
	@const	GL_LINE_STRIP
	@const	GL_TRIANGLE_FAN
	@const	GL_TRIANGLE_STRIP
*/
class MOAIEzraMesh :
	public MOAIDeck {
private:

	MOAILuaSharedPtr < MOAIIndexBuffer >	mIndexBuffer;

	MOAILuaSharedPtr < MOAIEzraVertexBuffer >	mVertexBuffer;

	u32		mPrimType;
	
	float	mPenWidth;
	float	mPointSize;
    int	    mHigh;
	//----------------------------------------------------------------//
	static int		_setIndexBuffer		( lua_State* L );
	static int		_setPenWidth		( lua_State* L );
	static int		_setPointSize		( lua_State* L );
	static int		_setPrimType		( lua_State* L );
	static int		_setVertexBuffer	( lua_State* L );
    static int		_setHigh	        ( lua_State* L );
	//----------------------------------------------------------------//
	ZLBox			ComputeMaxBounds		();
	ZLBox			GetItemBounds			( u32 idx );

public:
	
	DECL_LUA_FACTORY ( MOAIEzraMesh )
	
	//----------------------------------------------------------------//
	void			DrawIndex				( u32 idx, float xOff, float yOff, float zOff, float xScl, float yScl, float zScl );
	MOAIGfxState*	GetShaderDefault		();
					MOAIEzraMesh				();
					~MOAIEzraMesh				();
	void			RegisterLuaClass		( MOAILuaState& state );
	void			RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
