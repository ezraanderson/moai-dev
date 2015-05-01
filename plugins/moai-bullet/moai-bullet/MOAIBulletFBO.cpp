// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIGfxDevice.h>

#include <moai-bullet/MOAIBulletFBO.h>

#include <moai-bullet/lighting/ds_point_light_pass_tech.h>
#include <moai-bullet/lighting/ds_light_pass_tech.h>
#include <moai-bullet/lighting/ds_geom_pass_tech.h>
#include <moai-bullet/lighting/ds_dir_light_pass_tech.h>
#include <moai-bullet/lighting/util.h>

#include <stdio.h>
#include <math.h>

//#ifdef MOAI_OS_WINDOWS
//	#define GLEW_STATIC
//	#include <gl/glew.h>
//#endif

	//DSGeomPassTech			m_DSGeomPassTech;
	//DSPointLightPassTech	m_DSPointLightPassTech;
	//DSDirLightPassTech		m_DSDirLightPassTech;

	SpotLight				m_spotLight;
	DirectionalLight		m_dirLight;
	PointLight				m_pointLight[3];



 // The calculation solves a quadratic equation (see http://en.wikipedia.org/wiki/Quadratic_equation)
float CalcPointLightBSphere(const PointLight& Light)
{
	float MaxChannel = (std::max)((std::max)(Light.Color.x, Light.Color.y), Light.Color.z);
	float ret = (-Light.Attenuation.Linear + sqrtf(Light.Attenuation.Linear * Light.Attenuation.Linear - 4 * Light.Attenuation.Exp * (Light.Attenuation.Exp - 256 * MaxChannel * Light.DiffuseIntensity)))
	/
	2 * Light.Attenuation.Exp;
return ret;
} 

//================================================================//
// local
//================================================================//


int MOAIBulletFBO::_init ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletFBO, "UNN" )
	
	u32 width				= state.GetValue < u32 >( 2, 0 );
	u32 height				= state.GetValue < u32 >( 3, 0 );
	
	self->Init ( width, height);
	
	return 0;
}



//================================================================//
// MOAIFrameBufferTexture
//================================================================//

//----------------------------------------------------------------//
void MOAIBulletFBO::Init ( u32 width, u32 height ) {

	this->Clear ();

	if ( MOAIGfxDevice::Get ().IsFramebufferSupported ()) {

		this->mWidth			= width;
		this->mHeight			= height;
		
		this->Load ();
	}
	else {
		MOAILog ( 0, MOAILogMessages::MOAITexture_NoFramebuffer );
	}
}

//----------------------------------------------------------------//
bool MOAIBulletFBO::IsRenewable () {
	return true;
}

//----------------------------------------------------------------//
bool MOAIBulletFBO::IsValid () {
	return ( this->mGLFrameBufferID != 0 );
}

//----------------------------------------------------------------//
MOAIBulletFBO::MOAIBulletFBO () 
{
m_fbo = 0;
m_depthTexture = 0;
m_finalTexture = 0;
ZERO_MEM(m_textures);


	RTTI_BEGIN
		RTTI_EXTEND ( MOAIFrameBuffer )
		RTTI_EXTEND ( MOAITextureBase )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIBulletFBO::~MOAIBulletFBO () {

if (m_fbo != 0) {
	glDeleteFramebuffers(1, &m_fbo);
}
if (m_textures[0] != 0) {
	glDeleteTextures(3, m_textures);
}
if (m_depthTexture != 0) {
	glDeleteTextures(1, &m_depthTexture);
}
if (m_finalTexture != 0) {
	glDeleteTextures(1, &m_finalTexture);
}

	this->Clear ();
}

//----------------------------------------------------------------//
void MOAIBulletFBO::OnCreate () {


	  // delete existing fbo, textures, and render buffer in case we are regenerating at new size
  glDeleteTextures(GBUFFER_NUM_TEXTURES, m_textures);

  glDeleteRenderbuffers(1,	&m_renderBuffer);
  glDeleteFramebuffers(1,	&m_fbo);

  // create an fbo
  glGenFramebuffers(1, &m_fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

  // create all gbuffer textures
  glGenTextures(GBUFFER_NUM_TEXTURES, m_textures);

  // albedo/diffuse (16-bit channel rgba)
  glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_ALBEDO]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->mWidth, this->mHeight, 0, GL_RGBA, GL_FLOAT, NULL);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + GBUFFER_TEXTURE_TYPE_ALBEDO, GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_ALBEDO], 0);

  // normals + depth (32-bit RGBA float for accuracy)
  glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_NORMALS_DEPTH]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, this->mWidth, this->mHeight, 0, GL_RGBA, GL_FLOAT, NULL);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + GBUFFER_TEXTURE_TYPE_NORMALS_DEPTH, GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_NORMALS_DEPTH], 0);

  // lighting pass (16-bit RGBA)
  glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_LIGHT_PASS]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,  this->mWidth, this->mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + GBUFFER_TEXTURE_TYPE_LIGHT_PASS, GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_LIGHT_PASS], 0);

  // create depth texture (we don't use this explicitly, but since we use depth testing when rendering + for our stencil pass, our FBO needs a depth buffer)
  // we make it a renderbuffer and not a texture as we'll never access it directly in a shader
  glGenRenderbuffers(1, &m_renderBuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, this->mWidth, this->mHeight);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer);

  // check status
  GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);

  if (status != GL_FRAMEBUFFER_COMPLETE) {
    printf("GBuffer::setupFbo()", "Could not create framebuffer");
   // return false;
  }


  //SET NEW IDS
	this->mGLTexID			 = m_finalTexture;
	this->mGLFrameBufferID   = m_fbo;
	this->mIsDirty			 = true;

 // return true;

}

//----------------------------------------------------------------//
void MOAIBulletFBO::OnDestroy () {

}

//----------------------------------------------------------------//
void MOAIBulletFBO::OnInvalidate () {
	this->mGLFrameBufferID		= 0;
	this->MOAITextureBase::OnInvalidate ();
}

//----------------------------------------------------------------//
void MOAIBulletFBO::OnLoad () {
}

//----------------------------------------------------------------//
void MOAIBulletFBO::RegisterLuaClass ( MOAILuaState& state ) {
	
	MOAIFrameBuffer::RegisterLuaClass ( state );
	MOAITextureBase::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAIBulletFBO::RegisterLuaFuncs ( MOAILuaState& state ) {

	MOAIFrameBuffer::RegisterLuaFuncs ( state );
	MOAITextureBase::RegisterLuaFuncs ( state );	

	luaL_Reg regTable [] = {
		{ "init",						_init },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}













//****************************************************************************************************************
//****************************************************************************************************************
//****************************************************************************************************************



//----------------------------------------------------------------//
void MOAIBulletFBO::pass_geometry_bind() {

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

	GLenum DrawBuffers[] = {	GL_COLOR_ATTACHMENT0,
								GL_COLOR_ATTACHMENT1,
								GL_COLOR_ATTACHMENT2 
							};

	glDrawBuffers(ARRAY_SIZE_IN_ELEMENTS(DrawBuffers), DrawBuffers);

}
//----------------------------------------------------------------//
void MOAIBulletFBO::pass_geometry_start() {



		//bind_geometry();

		glDepthMask(GL_TRUE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		
		//Pipeline p;
		//p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
		//p.SetPerspectiveProj(m_persProjInfo);
		//p.Rotate(0.0f, m_scale, 0.0f);


		//FOR ALL THE OBJECTS
			// for (unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(m_boxPositions) ; i++) {
			//		p.WorldPos(m_boxPositions[i]);
			//		m_DSGeomPassTech.SetWVP(p.GetWVPTrans());
			//		m_DSGeomPassTech.SetWorldMatrix(p.GetWorldTrans());
			//		m_box.Render();
			//}

		
}
void MOAIBulletFBO::pass_geometry_end() {
	glDepthMask(GL_FALSE);
};




//****************************************************************************************************************
//****************************************************************************************************************
//****************************************************************************************************************




//----------------------------------------------------------------//
void MOAIBulletFBO::pass_stencil_bind() {
		glDrawBuffer(GL_NONE);
}


//----------------------------------------------------------------//
void MOAIBulletFBO::pass_stencil_start(int index) {

	// Disable color/depth write and enable stencil
	//bind_stencil();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glClear(GL_STENCIL_BUFFER_BIT);


	glStencilFunc(GL_ALWAYS, 0, 0);
	glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
	glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);

		//Pipeline p;
		//p.WorldPos(m_pointLight[PointLightIndex].Position);
		//float BBoxScale = CalcPointLightBSphere(m_pointLight[PointLightIndex]);
		//p.Scale(BBoxScale, BBoxScale, BBoxScale);
		//p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
		//p.SetPerspectiveProj(m_persProjInfo);

		//m_nullTech.SetWVP(p.GetWVPTrans());
		//m_bsphere.Render(); 

}

//----------------------------------------------------------------//
void MOAIBulletFBO::pass_stencil_end() {
	glDisable(GL_STENCIL_TEST);
};



//****************************************************************************************************************
//****************************************************************************************************************
//****************************************************************************************************************




//----------------------------------------------------------------//
void MOAIBulletFBO::pass_pointLight_bind() {

	//glDrawBuffer(GL_COLOR_ATTACHMENT4);
	//for (unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(m_textures); i++) {
	//	glActiveTexture(GL_TEXTURE0 + i);
	//	glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_POSITION + i]);
	//}

}

//----------------------------------------------------------------//
void MOAIBulletFBO::pass_pointLight_start(int index) {

	//bind_pointLight();

	//m_DSPointLightPassTech.Enable();
	//m_DSPointLightPassTech.SetEyeWorldPos(m_pGameCamera->GetPos());

	glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

			//Pipeline p;
			//p.WorldPos(m_pointLight[PointLightIndex].Position);
			//float BBoxScale = CalcPointLightBSphere(m_pointLight[PointLightIndex]);
			//p.Scale(BBoxScale, BBoxScale, BBoxScale);
			//p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
			//p.SetPerspectiveProj(m_persProjInfo);

			//m_DSPointLightPassTech.SetWVP(p.GetWVPTrans());
			//m_DSPointLightPassTech.SetPointLight(m_pointLight[PointLightIndex]);
			//m_bsphere.Render();



}

void MOAIBulletFBO::pass_pointLight_end() {
		glCullFace(GL_BACK);
		glDisable(GL_BLEND);
};





//****************************************************************************************************************
//****************************************************************************************************************
//****************************************************************************************************************


//----------------------------------------------------------------//
void MOAIBulletFBO::pass_dirLight_bind() {
	//glDrawBuffer(GL_COLOR_ATTACHMENT4);
	//for (unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(m_textures); i++) {
	//	glActiveTexture(GL_TEXTURE0 + i);
	//	glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_POSITION + i]);
	//}
};

//----------------------------------------------------------------//
void MOAIBulletFBO::pass_dirLight_start() {
	
		pass_dirLight_bind();		

			//m_DSDirLightPassTech.Enable();
			//m_DSDirLightPassTech.SetEyeWorldPos(m_pGameCamera->GetPos());

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);

				//m_quad.Render();

		glDisable(GL_BLEND);


}
//----------------------------------------------------------------//
void MOAIBulletFBO::pass_dirLight_end() {

};



//****************************************************************************************************************
//****************************************************************************************************************
//****************************************************************************************************************

void MOAIBulletFBO::pass_start() {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
	glDrawBuffer(GL_COLOR_ATTACHMENT4);
	glClear(GL_COLOR_BUFFER_BIT);
}
//----------------------------------------------------------------//
//void MOAIBulletFBO::pass_final_start() {
//	pass_final_bind();
//	glBlitFramebuffer(0, 0, this->mWidth, this->mHeight,0, 0, this->mWidth, this->mHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
//
//}
//----------------------------------------------------------------//
void MOAIBulletFBO::pass_end() {

glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
glReadBuffer(GL_COLOR_ATTACHMENT4);

glBlitFramebuffer(0, 0, this->mWidth, this->mHeight,0, 0, this->mWidth, this->mHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

};










//**************************************************************************************
//**************************************************************************************
//**************************************************************************************
void MOAIBulletFBO::tempLights () {

	glEnable(GL_STENCIL_TEST);
	for (unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(m_pointLight); i++) {
		pass_stencil_start(i);
		pass_pointLight_start(i);
	}

};


//----------------------------------------------------------------//
void MOAIBulletFBO::Render () {


//	pass_geometry();
//
//	glEnable(GL_STENCIL_TEST);
//
//	for (unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(m_pointLight); i++) {
//		pass_stencil(i);
//		pass_pointLight(i);
//	}
//
//	glDisable(GL_STENCIL_TEST);	
//
//	pass_dirLight();
//	
//	pass_final();
//
//
////NEED THIS TO RENDER THE ITEM
//	if ( this->mRenderTable ) {
//			MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
//			state.Push ( this->mRenderTable );
//			this->RenderTable ( state, -1 );
//			state.Pop ( 1 );
//	}
//


//*********************************************************************************************************************************
//*********************************************************************************************************************************




//NEED THIS TO RENDER THE ITEM
	if ( this->mRenderTable ) {
			MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
			state.Push ( this->mRenderTable );
			this->RenderTable ( state, -1 );
			state.Pop ( 1 );
	}







};









//----------------------------------------------------------------//
void MOAIBulletFBO::SerializeIn ( MOAILuaState& state, MOAIDeserializer& serializer ) {
	MOAITextureBase::SerializeIn ( state, serializer );
}

//----------------------------------------------------------------//
void MOAIBulletFBO::SerializeOut ( MOAILuaState& state, MOAISerializer& serializer ) {
	MOAITextureBase::SerializeOut ( state, serializer );
}