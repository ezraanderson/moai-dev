#ifndef MOAILIGHT_H
#define MOAILIGHT_H

#include <moai-core/MOAILua.h>

#include <moai-box2d/MOAIBox2DWorld.h>
#include <moai-box2d/MOAIBox2DBody.h>

#include <Box2D/common/b2Math.h>
#include <Box2D/common/b2Settings.h>

#include <moai-mathUtil/point.h>

#include "moai-mathUtil/clipper.hpp"
using namespace ClipperLib;



class BQueryCallback;

//********************************************************************
class BQueryCallback : public b2QueryCallback {
public:
	  MOAILuaState mState;

	  int		mTotal;
	  int		mReturn;
	  float		mUnitsToMeters;
	  bool		mHit;
	  std::vector<b2Fixture*> mFoundFixture;

	  friend class MOAIBox2DWorld;

	   BQueryCallback():
	   mUnitsToMeters	( 0 )
	   {
	   }   
     ~BQueryCallback	(){} ;
      bool ReportFixture(b2Fixture* fixture);
  };
	

//********************************************************************



class MOAILight :
	public virtual MOAILuaObject {
private:

	enum {
		mTriangle		= 0x01,
		mCircle			= 0x02,		
	};


	b2World*					mWorld;
	BQueryCallback*				mQueryList;
	bool						mDebug;				
	float						mUnitsToMeters;				
	float						mScale;
    float                       mOffX;
    float                       mOffY;

	//static int		_setFlashLight	( lua_State* L );
	static int		_draw			( lua_State* L );
	static int		_setWorld		( lua_State* L );
	static int		_query			( lua_State* L );
	static int		_queryOver		( lua_State* L );
	static int		_debug			( lua_State* L );
	static int		_scale			( lua_State* L );
	static int		_shadowTest		( lua_State* L );
	static int		_setOffset		( lua_State* L );

	static int		_AABB			( lua_State* L );


	Clipper mClipper;
	std::vector<mPoint> points_inner;

	//std::vector<mPoint> flashLight;


	std::vector<mPoint> edge_points;
	std::vector<int> edges;
public:


	DECL_LUA_FACTORY ( MOAILight )

	//----------------------------------------------------------------//
					MOAILight			();
					~MOAILight			();

	void			clipLight			();
	void			clipShadowInside	(float light_x,float light_y);
	void			clipShadowAll		(float light_x,float light_y);
    bool			inFrontLine			(float ax, float ay, float bx, float by, float px, float py);
	float			DotProduct2			(mPoint v1, mPoint v2);
	void			RegisterLuaClass	( MOAILuaState& state );
	void			RegisterLuaFuncs	( MOAILuaState& state );





};




#endif