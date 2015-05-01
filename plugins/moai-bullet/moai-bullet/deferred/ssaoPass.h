#ifndef __deferred__ssaopass__
#define __deferred__ssaopass__

//#include "ofMain.h"

#include <vector>
#include <zl-util/ZLVec2D.h>
#include <zl-util/ZLMatrix4x4.h>


class SSAOPass {

public:
  SSAOPass();
  ~SSAOPass();

  bool setup(int w, int h, int numSamples=12);
  bool setupFbo(int w, int h);
  void setParameters(float occluderBias, float samplingRadius, float constantAttenuation, float linearAttenuation);

  void setCameraProperties(const ZLMatrix4x4& invProjMatrix, float farDistance);

  void applySSAO(u32 normalsAndDepthTexUnit);
  void drawDebug(int x, int y);
  
  u32 getTextureReference();

private:
  static const USVec2D  s_quadVerts[];
  static const USVec2D  s_quadTexCoords[];
  //static		ofVbo  s_quadVbo;

  bool  m_bIsSetup;
  
  int   m_fbo_w;
  int   m_fbo_h;
  float m_texel_w;
  float m_texel_h;
  int   m_numSamples;
  

 // MOAIShader   m_ssaoShader;
 // MOAITexture  m_randomTexture;



  u32    m_fbo;
  u32    m_ssaoTex;
  
  void drawScreenQuad();
};

#endif
