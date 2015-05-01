// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com


//NEED TO SQITCH TO ZIPLINE CALLS
#ifdef MOAI_OS_WINDOWS
	#define GLEW_STATIC
	#include <gl/glew.h>
#endif


#include "pch.h"
#include <moai-sim/MOAICamera.h>
#include <moai-sim/MOAIDebugLines.h>
#include <moai-sim/MOAIDeck.h>
#include <moai-sim/MOAIFrameBufferTexture.h>
#include <moai-sim/MOAIGfxDevice.h>
#include <moai-sim/MOAIPartitionResultBuffer.h>
#include <moai-sim/MOAIPartitionResultMgr.h>
#include <moai-sim/MOAIProp.h>
#include <moai-sim/MOAITextureBase.h>
#include <moai-sim/MOAITransform.h>


#include <moai-bullet/MOAILayerPass.h>




int MOAILayerPass::_setUp ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAILayerPass, "U" );


printf("MOAILayerPass::_setUp --> setp \n");

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	ZLMatrix4x4 view;
	self->GetViewMtx ( view );


//***************************************************************************************************
//***************************************************************************************************
//***************************************************************************************************
//***************************************************************************************************
//G_BUFFER
  printf("1. GBuffer::setupFbo --> SETTING UP THE FBO\n");


 int m_buffer_w = 1280;
 int m_buffer_h = 720;

  // delete existing fbo, textures, and render buffer in case we are regenerating at new size
  glDeleteTextures(GBUFFER_NUM_TEXTURES, self->g_textures);
  glDeleteRenderbuffers(1, &self->g_renderBuffer);
  glDeleteFramebuffers(1, &self->g_fbo);

  // create an fbo
  glGenFramebuffers(1, &self->g_fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, self->g_fbo);

  // create all gbuffer textures
  glGenTextures(GBUFFER_NUM_TEXTURES, self->g_textures);

  // albedo/diffuse (16-bit channel rgba)
  glBindTexture(GL_TEXTURE_2D, self->g_textures[GBUFFER_TEXTURE_TYPE_ALBEDO]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_buffer_w, m_buffer_h, 0, GL_RGBA, GL_FLOAT, NULL);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + GBUFFER_TEXTURE_TYPE_ALBEDO, GL_TEXTURE_2D, self->g_textures[GBUFFER_TEXTURE_TYPE_ALBEDO], 0);

  // normals + depth (32-bit RGBA float for accuracy)
  glBindTexture(GL_TEXTURE_2D, self->g_textures[GBUFFER_TEXTURE_TYPE_NORMALS_DEPTH]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_buffer_w, m_buffer_h, 0, GL_RGBA, GL_FLOAT, NULL);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + GBUFFER_TEXTURE_TYPE_NORMALS_DEPTH, GL_TEXTURE_2D, self->g_textures[GBUFFER_TEXTURE_TYPE_NORMALS_DEPTH], 0);

  // lighting pass (16-bit RGBA)
  glBindTexture(GL_TEXTURE_2D, self->g_textures[GBUFFER_TEXTURE_TYPE_LIGHT_PASS]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_buffer_w, m_buffer_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + GBUFFER_TEXTURE_TYPE_LIGHT_PASS, GL_TEXTURE_2D, self->g_textures[GBUFFER_TEXTURE_TYPE_LIGHT_PASS], 0);

  // create depth texture (we don't use this explicitly, but since we use depth testing when rendering + for our stencil pass, our FBO needs a depth buffer)
  // we make it a renderbuffer and not a texture as we'll never access it directly in a shader
  glGenRenderbuffers(1, &self->g_renderBuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, self->g_renderBuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, m_buffer_w, m_buffer_h);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, self->g_renderBuffer);

  // check status
  GLenum status_gbuffer = glCheckFramebufferStatus(GL_FRAMEBUFFER);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);

   if (status_gbuffer != GL_FRAMEBUFFER_COMPLETE) {
    printf("GBuffer::setupFbo()", "Could not create framebuffer");
    return false;
  }


//***************************************************************************************************
//***************************************************************************************************
//***************************************************************************************************
//***************************************************************************************************
//SAO BUFFER
     printf("1. SAO::setupFbo --> SETTING UP THE FBO\n");
  
  self->s_fbo_w = 1280;
  self->s_fbo_h = 720;
  
  self->s_texel_w = 1.0f/(float)self->s_fbo_w;
  self->s_texel_h = 1.0f/(float)self->s_fbo_h;
  
  // setup fbo
  
  // delete existing fbo + textures in case we are regenerating them to new size
  glDeleteTextures(1, &self->s_ssaoTex);
  glDeleteFramebuffers(1, &self->s_fbo);
  
  // create all gbuffer textures
  glGenTextures(1, &self->s_ssaoTex);
  
  // 16-bit RGB texture for SSAO
  glBindTexture(GL_TEXTURE_2D, self->s_ssaoTex);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, self->s_fbo_w, self->s_fbo_h, 0, GL_RGB, GL_FLOAT, NULL);
  
  // create an fbo
  glGenFramebuffers(1, &self->s_fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, self->s_fbo);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, self->s_ssaoTex, 0);
  
  // check status
  GLenum status_ssao = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  
  if (status_ssao != GL_FRAMEBUFFER_COMPLETE) {
   // ofLogError("SSAOPass::setupFbo()", "Could not create framebuffer");
	  printf("SSAOPass::setupFbo()", "Could not create framebuffer \n");

    return false;
  }
  
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
    

  //********************************************************
  		//m_ssaoShader.begin();
		//m_ssaoShader.setUniformMatrix4f("u_inverseProjMatrix", invProjMatrix.getPtr());
		//m_ssaoShader.setUniform1f("u_farDistance", farDistance);
		//m_ssaoShader.end();
    //********************************************************



//*********************************************************************************************************
//*********************************************************************************************************
//*********************************************************************************************************
//MY SELF
     printf("1. MOAILayerPass::setupFbo --> MYSELF SETTING UP\n");


  // set up the texture units we want to use - we're using them every frame, so we'll leave them bound to these units to save speed vs. binding/unbinding
  self->m_textureUnits[TEX_UNIT_ALBEDO]				= 15;
  self->m_textureUnits[TEX_UNIT_NORMALS_DEPTH]		= 14;
  self->m_textureUnits[TEX_UNIT_SSAO]				= 13;
  self->m_textureUnits[TEX_UNIT_POINTLIGHT_PASS]    = 12;

  // bind all GBuffer textures
  glActiveTexture(GL_TEXTURE0 + self->m_textureUnits[TEX_UNIT_ALBEDO]);
  glBindTexture(GL_TEXTURE_2D,  self->m_gBuffer.getTexture(GBuffer::GBUFFER_TEXTURE_TYPE_ALBEDO));

  glActiveTexture(GL_TEXTURE0 +  self->m_textureUnits[TEX_UNIT_NORMALS_DEPTH]);
  glBindTexture(GL_TEXTURE_2D,  self->m_gBuffer.getTexture(GBuffer::GBUFFER_TEXTURE_TYPE_NORMALS_DEPTH));

  // bind SSAO texture
  glActiveTexture(GL_TEXTURE0 +  self->m_textureUnits[TEX_UNIT_SSAO]);
  glBindTexture(GL_TEXTURE_2D,  self->m_ssaoPass.getTextureReference());

  // point light pass texture
  glActiveTexture(GL_TEXTURE0 +  self->m_textureUnits[TEX_UNIT_POINTLIGHT_PASS]);
  glBindTexture(GL_TEXTURE_2D,  self->m_gBuffer.getTexture(GBuffer::GBUFFER_TEXTURE_TYPE_LIGHT_PASS));

  
  
  self->mMultiTextureMain = new MOAIMultiTexture();
  self->mMultiTextureMain->Reserve(3);



  
  //******************************************
  //MAIN_PASS

		//self->m_mainSceneShader->setTexture();
	  //m_shader.setUniform1i("u_albedoTex",			m_textureUnits[TEX_UNIT_ALBEDO]);
	  //m_shader.setUniform1i("u_ssaoTex",				m_textureUnits[TEX_UNIT_SSAO]);
	  //m_shader.setUniform1i("u_pointLightPassTex",	m_textureUnits[TEX_UNIT_POINTLIGHT_PASS]);



  //******************************************
  //LIGHT_PASS

		//m_pointLightPassShader.begin();  // our point light pass shader
		//m_pointLightPassShader.setUniform1i("u_albedoTex",			m_textureUnits[TEX_UNIT_ALBEDO]);
		//m_pointLightPassShader.setUniform1i("u_normalAndDepthTex",	m_textureUnits[TEX_UNIT_NORMALS_DEPTH]);
		//m_pointLightPassShader.setUniform1i("u_ssaoTex",				m_textureUnits[TEX_UNIT_SSAO]);
		//m_pointLightPassShader.setUniform2f("u_inverseScreenSize",	1.0f/m_windowWidth, 1.0f/m_windowHeight);
		//m_pointLightPassShader.end();




  return 1;
};












int MOAILayerPass::_clear ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "U" )

	if ( self->mPartition ) {
		self->mPartition->Clear ();
	}
	return 0;
}

//*******************************************************//
int MOAILayerPass::_getFitting ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "UNNNN" )

	ZLRect worldRect;
	worldRect.mXMin = state.GetValue < float >( 2, 0.0f );
	worldRect.mYMin = state.GetValue < float >( 3, 0.0f );
	worldRect.mXMax = state.GetValue < float >( 4, 0.0f );
	worldRect.mYMax = state.GetValue < float >( 5, 0.0f );

	worldRect.Bless ();

	float hPad = state.GetValue < float >( 6, 0.0f );
	float vPad = state.GetValue < float >( 7, 0.0f );

	float x = worldRect.mXMin + (( worldRect.mXMax - worldRect.mXMin ) * 0.5f );
	float y = worldRect.mYMin + (( worldRect.mYMax - worldRect.mYMin ) * 0.5f );

	lua_pushnumber ( state, x );
	lua_pushnumber ( state, y );

	float fitting = self->GetFitting ( worldRect, hPad, vPad );
	lua_pushnumber ( state, fitting );

	return 3;
}

//*******************************************************//
int	MOAILayerPass::_getPartition ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "U" )

	if ( self->mPartition ) {
		self->mPartition->PushLuaUserdata ( state );
		return 1;
	}
	return 0;
}
//*******************************************************//

int MOAILayerPass::_getSortMode ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "U" )
	
	lua_pushnumber ( state, self->mSortMode );
	return 1;
}
//*******************************************************//

int	MOAILayerPass::_getSortScale ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "U" )

	lua_pushnumber ( state, self->mSortScale [ 0 ]);
	lua_pushnumber ( state, self->mSortScale [ 1 ]);
	lua_pushnumber ( state, self->mSortScale [ 3 ]);

	return 3;
}

//*******************************************************//
int	MOAILayerPass::_insertProp ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "UU" )

	MOAIProp* prop = state.GetLuaObject < MOAIProp >( 2, true );

	if ( !prop ) return 0;
	if ( prop == self ) return 0;

		self->AffirmPartition ();
		self->mPartition->InsertProp ( *prop );
		prop->ScheduleUpdate ();

	return 0;
}

//*******************************************************//
int	MOAILayerPass::_removeProp ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "UU" )

	MOAIProp* prop = state.GetLuaObject < MOAIProp >( 2, true );
	if ( !prop ) return 0;
	if ( prop == self ) return 0;

	if ( self->mPartition ) {
		self->mPartition->RemoveProp ( *prop );
		prop->ScheduleUpdate ();
	}

	return 0;
}



//----------------------------------------------------------------//
/**	@name	setCamera
	@text	Sets a camera for the layer. If no camera is supplied,
			layer will render using the identity matrix as view/proj.
	
	@overload
	
		@in		MOAILayer self
		@opt	MOAICamera camera		Default value is nil.
		@out	nil
	
	@overload
	
		@in		MOAILayer self
		@opt	MOAICamera2D camera		Default value is nil.
		@out	nil
*/
int MOAILayerPass::_setCamera ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "U" )

	self->mCamera.Set ( *self, state.GetLuaObject < MOAICamera >( 2, true ));

	return 0;
}



//----------------------------------------------------------------//
/**	@name	setParallax
	@text	Sets the parallax scale for this layer. This is simply a
			scalar applied to the view transform before rendering.
	
	@in		MOAILayer self
	@opt	number xParallax	Default value is 1.
	@opt	number yParallax	Default value is 1.
	@opt	number zParallax	Default value is 1.
	@out	nil
*/
int MOAILayerPass::_setParallax ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "U" )

	self->mParallax.mX = state.GetValue < float >( 2, 1.0f );
	self->mParallax.mY = state.GetValue < float >( 3, 1.0f );
	self->mParallax.mZ = state.GetValue < float >( 4, 1.0f );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setPartition
	@text	Sets a partition for the layer to use. The layer will automatically
			create a partition when the first prop is added if no partition
			has been set.
	
	@in		MOAILayer self
	@in		MOAIPartition partition
	@out	nil
*/
int MOAILayerPass::_setPartition ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "UU" )

	self->mPartition.Set ( *self, state.GetLuaObject < MOAIPartition >( 2, true ));

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setPartitionCull2D
	@text	Enables 2D partition cull (projection of frustum AABB will
			be used instead of AABB or frustum).
	
	@in		MOAILayer self
	@in		boolean partitionCull2D		Default value is false.
	@out	nil
*/
int	MOAILayerPass::_setPartitionCull2D ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "U" )

	self->mPartitionCull2D = state.GetValue < bool >( 2, false );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setSortMode
	@text	Set the sort mode for rendering.
	
	@in		MOAILayer self
	@in		number sortMode		One of MOAILayer.SORT_NONE, MOAILayer.SORT_PRIORITY_ASCENDING,
								MOAILayer.SORT_PRIORITY_DESCENDING, MOAILayer.SORT_X_ASCENDING,
								MOAILayer.SORT_X_DESCENDING, MOAILayer.SORT_Y_ASCENDING,
								MOAILayer.SORT_Y_DESCENDING, MOAILayer.SORT_Z_ASCENDING,
								MOAILayer.SORT_Z_DESCENDING
	@out	nil
*/
int MOAILayerPass::_setSortMode ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "U" )
	
	self->mSortMode = state.GetValue < u32 >( 2, MOAIPartitionResultBuffer::SORT_PRIORITY_ASCENDING );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setSortScale
	@text	Set the scalar applied to axis sorts.
	
	@in		MOAILayer self
	@opt	number x			Default value is 0.
	@opt	number y			Default value is 0.
	@opt	number z			Default value is 0.
	@opt	number priority		Default value is 1.
	@out	nil
*/
int	MOAILayerPass::_setSortScale ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "U" )

	self->mSortScale [ 0 ] = state.GetValue < float >( 2, 0.0f );
	self->mSortScale [ 1 ] = state.GetValue < float >( 3, 0.0f );
	self->mSortScale [ 2 ] = state.GetValue < float >( 4, 0.0f );
	self->mSortScale [ 3 ] = state.GetValue < float >( 5, 1.0f );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setViewport
	@text	Set the layer's viewport.
	
	@in		MOAILayer self
	@in		MOAIViewport viewport
	@out	nil
*/
int MOAILayerPass::_setViewport ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "UU" )

	self->mViewport.Set ( *self, state.GetLuaObject < MOAIViewport >( 2, true ));

	return 0;
}

//----------------------------------------------------------------//
/**	@name	showDebugLines
	@text	Display debug lines for props in this layer.
	
	@in		MOAILayer self
	@opt	boolean showDebugLines		Default value is 'true'.
	@out	nil
*/
int	MOAILayerPass::_showDebugLines ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "U" )
	
	self->mShowDebugLines = state.GetValue < bool >( 2, true );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	wndToWorld
	@text	Project a point from window space into world space and return
			a normal vector representing a ray cast from the point into
			the world away from the camera (suitable for 3D picking).
	
	@in		MOAILayer self
	@in		number x
	@in		number y
	@in		number z
	@out	number x
	@out	number y
	@out	number z
	@out	number xn
	@out	number yn
	@out	number zn
*/
int MOAILayerPass::_wndToWorld ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "UNN" )

	USVec4D loc;
	loc.mX = state.GetValue < float >( 2, 0.0f );
	loc.mY = state.GetValue < float >( 3, 0.0f );
	loc.mZ = state.GetValue < float >( 4, 0.0f );
	loc.mW = 1.0f;

	USVec4D vec = loc;
	vec.mZ += 0.1f;

	ZLMatrix4x4 wndToWorld;
	self->GetWndToWorldMtx ( wndToWorld );
	
	wndToWorld.Project ( loc );
	wndToWorld.Project ( vec );

	lua_pushnumber ( state, loc.mX );
	lua_pushnumber ( state, loc.mY );
	lua_pushnumber ( state, loc.mZ );

	ZLVec3D norm;

	norm.mX = vec.mX - loc.mX;
	norm.mY = vec.mY - loc.mY;
	norm.mZ = vec.mZ - loc.mZ;
	
	norm.Norm ();
	
	lua_pushnumber ( state, norm.mX );
	lua_pushnumber ( state, norm.mY );
	lua_pushnumber ( state, norm.mZ );

	return 6;
}

//----------------------------------------------------------------//
/**	@name	worldToWnd
	@text	Transform a point from world space to window space.
	
	@in		MOAILayer self
	@in		number x
	@in		number y
	@in		number Z
	@out	number x
	@out	number y
	@out	number z
*/
int MOAILayerPass::_worldToWnd ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "UNN" )

	USVec4D loc;
	loc.mX = state.GetValue < float >( 2, 0.0f );
	loc.mY = state.GetValue < float >( 3, 0.0f );
	loc.mZ = state.GetValue < float >( 4, 0.0f );
	loc.mW = 1.0f;

	ZLMatrix4x4 worldToWnd;
	self->GetWorldToWndMtx ( worldToWnd );
	worldToWnd.Project ( loc );

	lua_pushnumber ( state, loc.mX );
	lua_pushnumber ( state, loc.mY );
	lua_pushnumber ( state, loc.mZ );

	return 3;
}


//**************************************************************************
//**************************************************************************
//**************************************************************************
int MOAILayerPass::_set_gBuffer( lua_State* L ) {
MOAI_LUA_SETUP ( MOAILayerPass, "UU" )	
	printf("_set_gBuffer\n");
	self->m_gBufferShader = state.GetLuaObject < MOAIShader >( 2, true );

	//self->m_gBuffer = ( *self, state.GetLuaObject < MOAIShader >( 2, true ));

	return 1;
};

int MOAILayerPass::_set_mainScene( lua_State* L ) {
MOAI_LUA_SETUP ( MOAILayerPass, "UU" )	
	printf("_set_mainScene\n");
	self->m_mainSceneShader = state.GetLuaObject < MOAIShader >( 2, true );

	//	self->m_mainScene = ( *self, state.GetLuaObject < MOAIShader >( 2, true ));
	return 1;
};

int MOAILayerPass::_set_lightPass( lua_State* L ) {
MOAI_LUA_SETUP ( MOAILayerPass, "UU" )	
	printf("_set_lightPass\n");
	self->m_pointLightPassShader = state.GetLuaObject < MOAIShader >( 2, true );
		//	self->m_pointLightPassShader = ( *self, state.GetLuaObject < MOAIShader >( 2, true ));
	return 1;
};

int MOAILayerPass::_set_lightStencil( lua_State* L ) {
MOAI_LUA_SETUP ( MOAILayerPass, "UU" )	
		printf("_set_lightStencil\n");
	self->m_pointLightStencilShader = state.GetLuaObject < MOAIShader >( 2, true );
				//self->m_pointLightStencilShader = ( *self, state.GetLuaObject < MOAIShader >( 2, true ));
	return 1;
};

int MOAILayerPass::_set_ssao( lua_State* L ) {
MOAI_LUA_SETUP ( MOAILayerPass, "UU" )	
	printf("_set_ssao\n");
	self->m_ssaoShader = state.GetLuaObject < MOAIShader >( 2, true );
		//self->m_ssao = ( *self, state.GetLuaObject < MOAIShader >( 2, true ));
	return 1;
};










int MOAILayerPass::_setFBO( lua_State* L ) {
MOAI_LUA_SETUP ( MOAILayerPass, "UU" )	

	self->mFbo = state.GetLuaObject < MOAIBulletFBO >( 2, true );
	return 1;
};








//*******************************************************//
int	MOAILayerPass::_insertLight ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "UU" )

	MOAIProp* prop = state.GetLuaObject < MOAIProp >( 2, true );

	if ( !prop ) return 0;
	if ( prop == self ) return 0;

		self->AffirmPartition ();
		self->mPartitionLights->InsertProp ( *prop );
		prop->ScheduleUpdate ();

	return 0;
}

//*******************************************************//
int	MOAILayerPass::_enableLights ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerPass, "UB" )

	self->mEnableLights = state.GetValue < bool >( 2, false );

	return 0;

}


//================================================================//
// MOAINode
//================================================================//

//----------------------------------------------------------------//
void MOAILayerPass::AffirmPartition () {

	if ( !this->mPartition ) {
		this->mPartition.Set ( *this, new MOAIPartition ());
		
		MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
		this->mPartition->PushLuaUserdata ( state );
		state.Pop ( 1 );
	}


	if ( !this->mPartitionLights ) {
		this->mPartitionLights.Set ( *this, new MOAIPartition ());		
		MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
		this->mPartition->PushLuaUserdata ( state );
		state.Pop ( 1 );
	}





}

//----------------------------------------------------------------//
void MOAILayerPass::Draw ( int subPrimID ) {
	UNUSED ( subPrimID );
    
   	if ( !this->IsVisible () )  return;
	if ( !this->mViewport )		return;

	//printf(" ---------------- \n");
	//printf(" DRAWING LAYER \n");
	
	MOAIViewport& viewport   = *this->mViewport;
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	
//REST
	gfxDevice.ResetState ();
	
	ZLRect viewportRect = viewport;

	// TODO:
	ZLMatrix4x4 mtx;
	mtx.Init ( this->mLocalToWorldMtx );
	// TODO:
	//mtx.Append ( gfxDevice.GetWorldToWndMtx ( 1.0f, 1.0f ));
	mtx.Transform ( viewportRect );

	gfxDevice.SetViewRect ( viewportRect );
	gfxDevice.SetScissorRect ( viewportRect );
	this->ClearSurface ();
	
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM );
	
	ZLMatrix4x4 view;
	this->GetViewMtx ( view );
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_VIEW_TRANSFORM, view );
	
	ZLMatrix4x4 proj;
	this->GetProjectionMtx ( proj );
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_PROJ_TRANSFORM, proj );
	
	ZLMatrix4x4 billboard;
	this->GetBillboardMtx ( billboard );
	gfxDevice.SetBillboardMtx ( billboard );
	
	// recompute the frustum
	gfxDevice.UpdateViewVolume ();
	

	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM );
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_VIEW_TRANSFORM, view );
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_PROJ_TRANSFORM, proj );
	

//*****************************************************
//DISABLE ALL SHADERS
//gfxDevice.ShaderDisable(true);
//*****************************************************


if ( this->mPartition ) {
		
		MOAIPartitionResultBuffer& buffer = MOAIPartitionResultMgr::Get ().GetBuffer ();
		const ZLFrustum& viewVolume		  = gfxDevice.GetViewVolume ();
		


//DISABLE DECK SHADERS SHADERS
	//gfxDevice.ShaderDisable(true);

		//gfxDevice.SetShader ( this->m_pointLightPassShader );		
		//gfxDevice.SetShader ( this->m_pointLightStencilShader );
		//gfxDevice.SetShaderAll ( this->m_mainScene ); 
		//gfxDevice.SetShader ( this->m_gBuffer );
		//gfxDevice.SetShader ( this->m_ssao );
		// this->m_mainScene.



//***************************************************************************************************
//***************************************************************************************************
// 1 :geometryPass 
// --DEFAULT SHADER
	//	gfxDevice.ShaderDisable(true);
	//	gfxDevice.SetShaderAll ( this->m_gBufferShader );	
	



		u32 totalResultsProps = 0;	
		totalResultsProps = this->mPartition->GatherProps ( buffer, 0, viewVolume, MOAIProp::CAN_DRAW | MOAIProp::CAN_DRAW_DEBUG );	
		
		if ( !totalResultsProps ) return;
		
			buffer.GenerateKeys (
				this->mSortMode,
				this->mSortScale [ 0 ],
				this->mSortScale [ 1 ],
				this->mSortScale [ 2 ],
				this->mSortScale [ 3 ]
			);
		
			totalResultsProps = buffer.Sort ( this->mSortMode );

						//******************************************************************
						gfxDevice.SetAmbientColor ( this->mColor ); //CRASHES WITH SHADER
						//******************************************************************

			for ( u32 i = 0; i < totalResultsProps; ++i ) {
				MOAIPartitionResult* result = buffer.GetResultUnsafe ( i );
				MOAIProp* prop = result->mProp;	
				prop->Draw ( result->mSubPrimID );
			}




};














//
//
////***************************************************************************************************
////***************************************************************************************************
//// 2 :pointLightPass
//		gfxDevice.ShaderDisable(true);
//		gfxDevice.SetShaderAll ( this->m_pointLightPassShader );				
//
////*********************************
////SETUP
//			this->m_pointLightPassShader->setInt(0,1); //u_numLights
//			this->m_pointLightPassShader->setFloat(1,1.0f); //u_farDistance
//
//
//////******************************************************************************************************************
//////PROPS
//	if ( this->mPartitionLights ) {
//
//		MOAIPartitionResultBuffer& buffer = MOAIPartitionResultMgr::Get ().GetBuffer ();
//		const ZLFrustum& viewVolume		  = gfxDevice.GetViewVolume ();
//
//		u32 totalResultsProps = 0;	
//		totalResultsProps = this->mPartition->GatherProps ( buffer, 0, viewVolume, MOAIProp::CAN_DRAW | MOAIProp::CAN_DRAW_DEBUG );	
//		
//		if ( !totalResultsProps ) return;
//		
//		buffer.GenerateKeys (
//			this->mSortMode,
//			this->mSortScale [ 0 ],
//			this->mSortScale [ 1 ],
//			this->mSortScale [ 2 ],
//			this->mSortScale [ 3 ]
//		);
//		
//	totalResultsProps = buffer.Sort ( this->mSortMode );
//
//
//
//	//DRAW ALL LIGHT PROPS
//	for ( u32 i = 0; i < totalResultsProps; ++i ) {
//		MOAIPartitionResult* result = buffer.GetResultUnsafe ( i );
//		MOAIProp* prop = result->mProp;	
//
//						//*********************************
//						//FLOATS : READ FROM PROP
//
//									this->m_pointLightPassShader->setFloat(2,1.0f); //u_lightIntensity
//									this->m_pointLightPassShader->setFloat(3,1.0f); //u_lightRadius
//
//						////*********************************
//						////COLORS
//									ZLColorVec u_lightDiffuse(1,0,0,0.5);
//									this->m_pointLightPassShader->setColor(5,u_lightDiffuse); //u_lightDiffuse
//
//
//									ZLColorVec u_lightSpecular(1,0,0,0.5);
//									this->m_pointLightPassShader->setColor(6,u_lightSpecular); //u_lightSpecular
//
//						//*********************************
//						//POSTIONS
//									this->m_pointLightPassShader->setFloat(7,1.0f); //u_lightPosition_x
//									this->m_pointLightPassShader->setFloat(8,1.0f); //u_lightPosition_y
//									this->m_pointLightPassShader->setFloat(9,1.0f); //u_lightPosition_z
//
//
//									this->m_pointLightPassShader->setFloat(10,1.0f); //u_lightAttenuation_x
//									this->m_pointLightPassShader->setFloat(11,1.0f); //u_lightAttenuation_x
//									this->m_pointLightPassShader->setFloat(12,1.0f); //u_lightAttenuation_z
//
//
//
//		prop->Draw ( result->mSubPrimID );
//	}
//
//
//}





	gfxDevice.Flush ();
}

//----------------------------------------------------------------//
void MOAILayerPass::GetBillboardMtx ( ZLMatrix4x4& billboard ) {
	
	if ( this->mCamera ) {
		billboard = this->mCamera->GetBillboardMtx ();
	}
	else {
		billboard.Ident ();
	}
}

//----------------------------------------------------------------//
float MOAILayerPass::GetFitting ( ZLRect& worldRect, float hPad, float vPad ) {

	if ( !( this->mCamera && this->mViewport )) return 1.0f;

	ZLRect viewRect = this->mViewport->GetRect ();
	
	float hFit = ( viewRect.Width () - ( hPad * 2 )) / worldRect.Width ();
	float vFit = ( viewRect.Height () - ( vPad * 2 )) / worldRect.Height ();
	
	return ( hFit < vFit ) ? hFit : vFit;
}

//----------------------------------------------------------------//
void MOAILayerPass::GetProjectionMtx ( ZLMatrix4x4& proj ) {
	
	if ( this->mCamera ) {
		proj.Init ( this->mCamera->GetProjMtx ( *this->mViewport ));
	}
	else {
		proj.Init ( this->mViewport->GetProjMtx ());
	}
}

//----------------------------------------------------------------//
u32 MOAILayerPass::GetPropBounds ( ZLBox& bounds ) {
	
	if ( this->mViewport ) {
		ZLRect frame = this->mViewport->GetRect ();
		bounds.Init ( frame.mXMin, frame.mYMax, frame.mXMax, frame.mYMin, 0.0f, 0.0f );
		return MOAIProp::BOUNDS_OK;
	}
	return MOAIProp::BOUNDS_EMPTY;
}

//----------------------------------------------------------------//
void MOAILayerPass::GetViewMtx ( ZLMatrix4x4& view ) {
	
	if ( this->mCamera ) {
		
		view = this->mCamera->GetViewMtx ();
		view.m [ ZLMatrix4x4::C3_R0 ] *= this->mParallax.mX;
		view.m [ ZLMatrix4x4::C3_R1 ] *= this->mParallax.mY;
		view.m [ ZLMatrix4x4::C3_R2 ] *= this->mParallax.mZ;
	}
	else {
		view.Ident ();
	}
}

//----------------------------------------------------------------//
void MOAILayerPass::GetWndToWorldMtx ( ZLMatrix4x4& wndToWorld ) {

	this->GetWorldToWndMtx ( wndToWorld );
	wndToWorld.Inverse ();
}









//----------------------------------------------------------------//
void MOAILayerPass::GetWorldToWndMtx ( ZLMatrix4x4& worldToWnd ) {

	if ( this->mViewport ) {
		
		ZLMatrix4x4 view;
		this->GetViewMtx ( view );

		ZLMatrix4x4 proj;
		this->GetProjectionMtx ( proj );
		
		ZLMatrix4x4 wnd;
		this->mViewport->GetNormToWndMtx ( wnd );
		
		worldToWnd = view;
		worldToWnd.Append ( proj );
		worldToWnd.Append ( wnd );
	}
	else {
		worldToWnd.Ident ();
	}
	
	ZLMatrix4x4 mtx;
	mtx.Init ( this->mLocalToWorldMtx );
	worldToWnd.Append ( mtx );
}




//----------------------------------------------------------------//
MOAILayerPass::MOAILayerPass () :
	mParallax ( 1.0f, 1.0f, 1.0f ),

//m_pointLightPassShader( 0 ),
//m_pointLightStencilShader( 0 ),
//m_mainScene( 0 ),
//m_gBuffer( 0 ),
//m_ssao( 0 ),

	mShowDebugLines ( true ),
	mSortMode ( MOAIPartitionResultBuffer::SORT_PRIORITY_ASCENDING ),
	mPartitionCull2D ( true ) ,
	mEnableLights ( false ),
	mFbo( 0 )
	{
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIProp )
		RTTI_EXTEND ( MOAIClearableView )
	RTTI_END
	
	this->SetMask ( MOAIProp::CAN_DRAW | MOAIProp::CAN_DRAW_DEBUG );
	this->SetClearFlags ( 0 );


}






//----------------------------------------------------------------//
MOAILayerPass::~MOAILayerPass () {

	this->mCamera.Set ( *this, 0 );
	this->mViewport.Set ( *this, 0 );
	this->mPartition.Set ( *this, 0 );
	this->mPartitionLights.Set ( *this, 0 );

}


//----------------------------------------------------------------//
void MOAILayerPass::RegisterLuaClass ( MOAILuaState& state ) {

	MOAIProp::RegisterLuaClass ( state );
	MOAIClearableView::RegisterLuaClass ( state );
	
	state.SetField ( -1, "SORT_NONE",					( u32 )MOAIPartitionResultBuffer::SORT_NONE );
	state.SetField ( -1, "SORT_ISO",					( u32 )MOAIPartitionResultBuffer::SORT_ISO );
	state.SetField ( -1, "SORT_PRIORITY_ASCENDING",		( u32 )MOAIPartitionResultBuffer::SORT_PRIORITY_ASCENDING );
	state.SetField ( -1, "SORT_PRIORITY_DESCENDING",	( u32 )MOAIPartitionResultBuffer::SORT_PRIORITY_DESCENDING );
	state.SetField ( -1, "SORT_X_ASCENDING",			( u32 )MOAIPartitionResultBuffer::SORT_X_ASCENDING );
	state.SetField ( -1, "SORT_X_DESCENDING",			( u32 )MOAIPartitionResultBuffer::SORT_X_DESCENDING );
	state.SetField ( -1, "SORT_Y_ASCENDING",			( u32 )MOAIPartitionResultBuffer::SORT_Y_ASCENDING );
	state.SetField ( -1, "SORT_Y_DESCENDING",			( u32 )MOAIPartitionResultBuffer::SORT_Y_DESCENDING );
	state.SetField ( -1, "SORT_Z_ASCENDING",			( u32 )MOAIPartitionResultBuffer::SORT_Z_ASCENDING );
	state.SetField ( -1, "SORT_Z_DESCENDING",			( u32 )MOAIPartitionResultBuffer::SORT_Z_DESCENDING );
	state.SetField ( -1, "SORT_VECTOR_ASCENDING",		( u32 )MOAIPartitionResultBuffer::SORT_VECTOR_ASCENDING );
	state.SetField ( -1, "SORT_VECTOR_DESCENDING",		( u32 )MOAIPartitionResultBuffer::SORT_VECTOR_DESCENDING );
}

//----------------------------------------------------------------//
void MOAILayerPass::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	MOAIProp::RegisterLuaFuncs ( state );
	MOAIClearableView::RegisterLuaFuncs ( state );
	
	luaL_Reg regTable [] = {
		{ "setUp",						_setUp },

	
		{ "clear",					_clear },
		{ "getFitting",				_getFitting },
		{ "getPartition",			_getPartition },
		{ "getSortMode",			_getSortMode },
		{ "getSortScale",			_getSortScale },
		{ "insertProp",				_insertProp },
		{ "removeProp",				_removeProp },
		{ "setCamera",				_setCamera },
	
		{ "setParallax",			_setParallax },
		{ "setPartition",			_setPartition },
		{ "setPartitionCull2D",		_setPartitionCull2D },
		{ "setSortMode",			_setSortMode },
		{ "setSortScale",			_setSortScale },
		{ "setViewport",			_setViewport },
		{ "showDebugLines",			_showDebugLines },
		{ "wndToWorld",				_wndToWorld },
		{ "worldToWnd",				_worldToWnd },

		{ "setFBO",					_setFBO },
		{ "insertLight",			_insertLight },
		{ "enableLights",			_enableLights },


		{ "set_gBuffer",			_set_gBuffer },
		{ "set_mainScene",			_set_mainScene },
		{ "set_lightPass",			_set_lightPass },
		{ "set_lightStencil",		_set_lightStencil },
		{ "set_ssao",				_set_ssao },


		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAILayerPass::Render () {
	
	this->Draw ( MOAIProp::NO_SUBPRIM_ID );
}

//----------------------------------------------------------------//
void MOAILayerPass::SerializeIn ( MOAILuaState& state, MOAIDeserializer& serializer ) {
	MOAIProp::SerializeIn ( state, serializer );
}

//----------------------------------------------------------------//
void MOAILayerPass::SerializeOut ( MOAILuaState& state, MOAISerializer& serializer ) {
	MOAIProp::SerializeOut ( state, serializer );
}