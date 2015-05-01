// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIEZRAINDEXBUFFER_H
#define	MOAIEZRAINDEXBUFFER_H

#include <moai-sim/MOAIGfxResource.h>

//================================================================//
// MOAIEzraIndexBuffer
//================================================================//
/**	@name	MOAIEzraIndexBuffer
	@text	Index buffer class. Unused at this time.
*/
class MOAIEzraIndexBuffer :
	public virtual MOAILuaObject,
	public MOAIGfxResource {
private:

	u32*	mBuffer;
	u32		mIndexCount;
	
	u32		mGLBufferID;
	u32		mHint;
	
	//----------------------------------------------------------------//
	static int	_release				( lua_State* L );
	static int	_reserve				( lua_State* L );
	static int	_setIndex				( lua_State* L );

	//----------------------------------------------------------------//
	bool		IsRenewable				();
	bool		IsValid					();
	void		OnBind					();
	void		OnClear					();
	void		OnCreate				();
	void		OnDestroy				();
	void		OnInvalidate			();
	void		OnLoad					();
   
	
public:
	
	DECL_LUA_FACTORY ( MOAIEzraIndexBuffer )
	
	GET ( u32, IndexCount, mIndexCount )
	
	//----------------------------------------------------------------//
	bool		LoadGfxState			();
				MOAIEzraIndexBuffer			();
				~MOAIEzraIndexBuffer		();
	void		RegisterLuaClass		( MOAILuaState& state );
	void		RegisterLuaFuncs		( MOAILuaState& state );
	void		ReserveIndices			( u32 indexCount );
	void		SetIndex				( u32 idx, u32 value );
    void		Update					();
};

#endif
