
#ifndef MOAIBULLETDEBUGDRAW_H
#define MOAIBULLETDEBUGDRAW_H

#include <src/LinearMath/BtIdebugDraw.h>



class MOAIGfxDevice;

// This class implements debug drawing callbacks that are invoked
// inside b2World::Step.
class MOAIBulletDebugDraw : public btIDebugDraw  {

	friend class MOAIBulletWorld;
	float mScale;
	long mSize;

	void WriteVtx ( MOAIGfxDevice& gfxDevice, float x, float y,float z );
	void MOAIBulletDebugDraw::resetSize ();

 public:

  virtual ~MOAIBulletDebugDraw() {};
  

  virtual bool    isVisible(const btVector3& aabbMin,const btVector3& aabbMax);

  virtual void		drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
    
  virtual void    drawLine(const btVector3& from,const btVector3& to, const btVector3& fromColor, const btVector3& toColor);

  
  virtual void  drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color);

  virtual void  reportErrorWarning(const char* warningString);

  virtual void  draw3dText(const btVector3& location,const char* textString);
  
  virtual void  setDebugMode(int debugMode);
  
  virtual int    getDebugMode() const;

  virtual void drawAabb(const btVector3& from,const btVector3& to,const btVector3& color);

  virtual void drawTransform(const btTransform& transform, btScalar orthoLen);







 
  //virtual void  drawSphere(btScalar radius, const btTransform& transform, const btVector3& color);  
  //virtual void  drawSphere (const btVector3& p, btScalar radius, const btVector3& color);


 
  //virtual  void  drawTriangle(const btVector3& v0,const btVector3& v1,const btVector3& v2,const btVector3& /*n0*/,const btVector3& /*n1*/,const btVector3& /*n2*/,const btVector3& color, btScalar alpha);
 
  //virtual  void  drawTriangle(const btVector3& v0,const btVector3& v1,const btVector3& v2,const btVector3& color, btScalar /*alpha*/);
 



  //virtual void drawArc(const btVector3& center, const btVector3& normal, const btVector3& axis, btScalar radiusA, btScalar radiusB, btScalar minAngle, btScalar maxAngle, const btVector3& color, bool drawSect, btScalar stepDegrees = btScalar(10.f)); 
  //virtual void drawSpherePatch(const btVector3& center, const btVector3& up, const btVector3& axis, btScalar radius, btScalar minTh, btScalar maxTh, btScalar minPs, btScalar maxPs, const btVector3& color, btScalar stepDegrees = btScalar(10.f),bool drawCenter = true);

  //
  //virtual void drawBox(const btVector3& bbMin, const btVector3& bbMax, const btVector3& color);

  //virtual void drawBox(const btVector3& bbMin, const btVector3& bbMax, const btTransform& trans, const btVector3& color);


  //virtual void drawCapsule(btScalar radius, btScalar halfHeight, int upAxis, const btTransform& transform, const btVector3& color);


  //virtual void drawCylinder(btScalar radius, btScalar halfHeight, int upAxis, const btTransform& transform, const btVector3& color);
 

  //virtual void drawCone(btScalar radius, btScalar height, int upAxis, const btTransform& transform, const btVector3& color);
 

  //virtual void drawPlane(const btVector3& planeNormal, btScalar planeConst, const btTransform& transform, const btVector3& color);
 

};





#endif
