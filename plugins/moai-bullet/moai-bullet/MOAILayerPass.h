// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAILAYERPASS_H
#define	MOAILAYERPASS_H

#include <moai-sim/MOAIFrameBuffer.h>
#include <moai-sim/MOAIPartition.h>
#include <moai-sim/MOAIProp.h>
#include <moai-sim/MOAIViewport.h>
#include <moai-sim/MOAIShader.h>

#include <moai-bullet/MOAIBulletFBO.h>

#include <moai-bullet/deferred/gBuffer.h>
#include <moai-bullet/deferred/ssaoPass.h>

class MOAICamera;


class MOAILayerPass :
	public virtual MOAIProp,
	public MOAIClearableView {
private:



//**********************************************************
//G_BUFFER
public:
  enum GBUFFER_TEXTURE_TYPE {
    GBUFFER_TEXTURE_TYPE_ALBEDO,
    GBUFFER_TEXTURE_TYPE_NORMALS_DEPTH,
    GBUFFER_TEXTURE_TYPE_LIGHT_PASS,
    GBUFFER_NUM_TEXTURES
  };

  u32 g_fbo;
  u32 g_textures[GBUFFER_NUM_TEXTURES];
  u32 g_renderBuffer;

//**********************************************************
//G_SAO


int   s_fbo_w;
int   s_fbo_h;
float s_texel_w;
float s_texel_h;
int   s_numSamples;

u32    s_fbo;
u32    s_ssaoTex;
  



//**********************************************************
//m_class


enum TEXTURE_UNITS {
    TEX_UNIT_ALBEDO,
    TEX_UNIT_NORMALS_DEPTH,
    TEX_UNIT_SSAO,
    TEX_UNIT_POINTLIGHT_PASS,
    TEX_UNIT_NUM_UNITS
  };



	u32 m_textureUnits[TEX_UNIT_NUM_UNITS];
	GBuffer m_gBuffer;
	SSAOPass m_ssaoPass;


	MOAILuaSharedPtr < MOAICamera >			mCamera;
	MOAILuaSharedPtr < MOAIViewport >		mViewport;

	MOAILuaSharedPtr < MOAIPartition >		mPartition;
	MOAILuaSharedPtr < MOAIPartition >		mPartitionLights;



	//MOAILuaSharedPtr < MOAIShader >	 m_pointLightPassShader;
	//MOAILuaSharedPtr < MOAIShader >	 m_pointLightStencilShader;
	//MOAILuaSharedPtr < MOAIShader >	 m_mainScene;
	//MOAILuaSharedPtr < MOAIShader >	 m_gBuffer;
	//MOAILuaSharedPtr < MOAIShader >	 m_ssao;



	 MOAIShader  *m_pointLightPassShader;
	 MOAIShader  *m_pointLightStencilShader;
	 MOAIShader  *m_mainSceneShader;
	 MOAIShader  *m_gBufferShader;
	 MOAIShader  *m_ssaoShader;

	 MOAIMultiTexture *mMultiTextureMain;
	 MOAIMultiTexture *mMultiTextureLight;



	bool mEnableLights;

	MOAIBulletFBO*	mFbo;

	ZLVec3D		mParallax;
	bool		mShowDebugLines;
	u32			mSortMode;

	float		mSortScale [ 4 ];

	bool		mPartitionCull2D;

	//----------------------------------------------------------------//
	static int	_setUp				( lua_State* L );

	static int	_clear				( lua_State* L );
	static int	_getFitting			( lua_State* L );
	static int	_getPartition		( lua_State* L );
	static int	_getSortMode		( lua_State* L );
	static int	_getSortScale		( lua_State* L );
	static int	_insertProp			( lua_State* L );
	static int	_removeProp			( lua_State* L );
	static int	_setCamera			( lua_State* L );
	
	static int	_setParallax		( lua_State* L );
	static int	_setPartition		( lua_State* L );
	static int	_setPartitionCull2D	( lua_State* L );
	static int	_setSortMode		( lua_State* L );
	static int	_setSortScale		( lua_State* L );
	static int	_setViewport		( lua_State* L );
	static int	_showDebugLines		( lua_State* L );
	static int	_wndToWorld			( lua_State* L );
	static int	_worldToWnd			( lua_State* L );

	static int	_setFBO				( lua_State* L );
	static int	_insertLight		( lua_State* L );
	static int	_enableLights		( lua_State* L );


	static int	_set_gBuffer		( lua_State* L );
	static int	_set_mainScene		( lua_State* L );
	static int	_set_lightPass		( lua_State* L );
	static int	_set_lightStencil	( lua_State* L );
	static int	_set_ssao			( lua_State* L );




	
	//----------------------------------------------------------------//
	void			AffirmPartition			();
	void			GetBillboardMtx			( ZLMatrix4x4& billboard );
	void			GetProjectionMtx		( ZLMatrix4x4& proj );
	void			GetViewMtx				( ZLMatrix4x4& view );

public:
	
	DECL_LUA_FACTORY ( MOAILayerPass )
	
	//----------------------------------------------------------------//
	void			Draw					( int subPrimID );
	float			GetFitting				( ZLRect& worldRect, float hPad, float vPad );
	u32				GetPropBounds			( ZLBox& bounds );
	void			GetWndToWorldMtx		( ZLMatrix4x4& wndToWorld );
	void			GetWorldToWndMtx		( ZLMatrix4x4& worldToWnd );
					MOAILayerPass			();
					~MOAILayerPass			();
	void			RegisterLuaClass		( MOAILuaState& state );
	void			RegisterLuaFuncs		( MOAILuaState& state );
	void			Render					();
	void			SerializeIn				( MOAILuaState& state, MOAIDeserializer& serializer );
	void			SerializeOut			( MOAILuaState& state, MOAISerializer& serializer );
};

#endif
