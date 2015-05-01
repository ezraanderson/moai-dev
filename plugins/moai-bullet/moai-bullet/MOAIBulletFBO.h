// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIBULLETFOB_H
#define	MOAIBULLETFOB_H

#include <moai-sim/MOAIFrameBuffer.h>
#include <moai-sim/MOAITextureBase.h>

//================================================================//
// MOAIFrameBufferTexture
//================================================================//
/**	@name	MOAIFrameBufferTexture
	@text	This is an implementation of a frame buffer that may be
			attached to a MOAILayer for offscreen rendering. It is
			also a texture that may be bound and used like any other.
*/
class MOAIBulletFBO :
	public MOAIFrameBuffer,
	public MOAITextureBase {
private:
	



	u32					mGLColorBufferID;
	u32					mGLDepthBufferID;
	u32					mGLStencilBufferID;
	
	u32					mColorFormat;
	u32					mDepthFormat;
	u32					mStencilFormat;



	
	//----------------------------------------------------------------//
	static int			_init					( lua_State* L );
	
	//----------------------------------------------------------------//
	virtual bool		IsRenewable				();
	virtual void		OnCreate				();
	virtual void		OnDestroy				();
	virtual void		OnInvalidate			();
	virtual void		OnLoad					();




public:




//*************************************************************	
//*************************************************************	
//*************************************************************	

		#define GL_DEPTH32F_STENCIL8              0x8CAD
		#define GL_DEPTH_COMPONENT                0x1902
		#define GL_DRAW_FRAMEBUFFER               0x8CA9




enum GBUFFER_TEXTURE_TYPE {
		GBUFFER_TEXTURE_TYPE_ALBEDO,
		GBUFFER_TEXTURE_TYPE_NORMALS_DEPTH,
		GBUFFER_TEXTURE_TYPE_LIGHT_PASS,
		GBUFFER_NUM_TEXTURES
  };



		//enum GBUFFER_TEXTURE_TYPE {
		//		GBUFFER_TEXTURE_TYPE_POSITION,
		//		GBUFFER_TEXTURE_TYPE_DIFFUSE,
		//		GBUFFER_TEXTURE_TYPE_NORMAL,
		//		GBUFFER_NUM_TEXTURES
		//};


	u32 m_fbo;
	u32 m_renderBuffer;
	u32 m_textures[GBUFFER_NUM_TEXTURES];
	u32 m_depthTexture;
	u32 m_finalTexture;









//#define ZERO_MEM(a) memset(a, 0, sizeof(a));
//#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]));
//*************************************************************	
//*************************************************************	
//*************************************************************	



	friend class MOAIGfxDevice;
	friend class MOAITextureBase;
	
	DECL_LUA_FACTORY ( MOAIBulletFBO )
	
	//----------------------------------------------------------------//
	void				Init						( u32 width, u32 height );
	bool				IsValid						();
						MOAIBulletFBO		();
						~MOAIBulletFBO		();
	void				RegisterLuaClass			( MOAILuaState& state );
	void				RegisterLuaFuncs			( MOAILuaState& state );
	void				Render						();
	void				SerializeIn					( MOAILuaState& state, MOAIDeserializer& serializer );
	void				SerializeOut				( MOAILuaState& state, MOAISerializer& serializer );




	//*********************************************************************

	void				pass_geometry_bind			();
	void				pass_geometry_start			();
	void				pass_geometry_end			();

	void				pass_pointLight_bind		();
	void				pass_pointLight_start		(int index);
	void				pass_pointLight_end			();



	void				pass_stencil_bind			();
	void				pass_stencil_start			(int index);
	void				pass_stencil_end			();


	void				pass_dirLight_bind			();
	void				pass_dirLight_start			();
	void				pass_dirLight_end			();

	void				pass_start					();
	void				pass_end					();
	//void				pass_final_end				();

	void				tempLights				();
};

#endif
