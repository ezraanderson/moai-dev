//ADD UNIT DEGREE MOD

#include "pch.h"
#include <moai-mathUtil/MOAIMathUtil.h>
#include <moai-mathUtil/MOAIHit.h>

#include <math.h>
#include <zl-util/ZLVec2D.h>
#include <vector>
#include "point.h"

#include "moai-poly2tri/poly2tri.h"
using namespace p2t;

#include "moai-mathUtil/clipper.hpp"
using namespace ClipperLib;

template <class C> void FreeClear( C & cntr ) {
    for ( typename C::iterator it = cntr.begin(); 
              it != cntr.end(); ++it ) {
    	delete * it;
    }
    cntr.clear();
};



Clipper c;

#define PIV2 M_PI+M_PI
#define C360 360.0000000000000000000

//inline double Dot(const Point& a,const Point& b)       { return (a.x*b.x) + (a.y*b.y); }
//inline double PerpDot(const Point& a,const Point& b)   { return (a.y*b.x) - (a.x*b.y); }


float  length(float x, float y) {
  return sqrt(x*x + y*y);
};

float cross(float ax, float ay, float bx, float by) {
  return ay*bx - ax*by;
};

float getDistance(float x1, float y1, float x2, float y2){;
   return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));	
};
float dot(float x1,float y1,float x2,float y2){ 
return ( x1 * x2) + ( y1 * y2 );
};

float dotPre(float x1,float y1,float x2,float y2){ 
return ( y1 * x2) + ( x1 * y2 );
};

float signed_triangle_area(float ax, float ay, float bx, float by, float cx, float cy) {
  return (ax - cx)*(by - cy) - (ay - cy)*(bx - cx);
};

bool inFrontLine(float ax, float ay, float bx, float by, float px, float py){
     return ((bx - ax)*(py - ay) - (by - ay)*(px - ax)) > 0;
}

bool inFrontTriangle(float ax, float ay, float bx, float by,float cx, float cy, float px, float py){

  float pab = cross(px - ax, py - ay, bx - ax, by - ay);
  float pbc = cross(px - bx, py - by, cx - bx, cy - by);
  if ((pab < 0 && pbc >= 0) || (pab >= 0 && pbc < 0)) {
    return false;
  };
  float pca = cross(px - cx, py - cy, ax - cx, ay - cy);
  if ((pab < 0 && pca >= 0) || (pab >= 0 && pca < 0)) {
    return false;
  };
  return true;  
}

//----------------------------------------------------------------//
//COLLSION
void  MOAIMathUtil::cirlce_vs_circle
(
	float balls_i_x,float balls_i_y,float balls_i_vx,float balls_i_vy,float balls_i_r,
	float balls_j_x,float balls_j_y,float balls_j_vx,float balls_j_vy,float balls_j_r
){

if  ( (balls_j_x - balls_i_x) * (balls_i_vx - balls_j_vx) + (balls_j_y - balls_i_y) * (balls_i_vy - balls_j_vy) > 0  )
{

float ballA = balls_j_x - balls_i_x;
float ballB = balls_j_y - balls_i_y;

	if  ((ballA) * (ballA) + ((ballB) * (ballB) ) <= (balls_j_r + balls_i_r + EPSILON) * (balls_j_r + balls_i_r + EPSILON))
	{	

		float nx = (balls_i_x - balls_j_x) / (10+10 );
		float ny = (balls_i_y - balls_j_y) / (10+10);
		float a1 = balls_i_vx * nx + balls_i_vy * ny;
		float a2 = balls_j_vx * nx + balls_j_vy * ny;

		float p  = 2 * (a1 - a2) / (10 + 10); //mass (5,5)

		//circleA->mVec.mX  =balls_i_vx - p * nx  * 1;
		//circleA->mVec.mY = balls_i_vy - p * ny  * 1;		
		//circleB->mVec.mX = balls_j_vx + p * nx  * 1;
		//circleB->mVec.mY = balls_j_vy + p * ny * 1;


	}; //END COLLSION

}; //END MOVING



}; //END FUNCTION






int MOAIMathUtil::_project_to ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

float x		=  state.GetValue < float >( 2, 0 );
float y		=  state.GetValue < float >( 3, 0 );

float angle		=  state.GetValue < float >( 4, 0 );
float distance  =  state.GetValue < float >( 5, 0 );


//angle = (angle+self->mRot)* (PI / 180);

float  dx =x+distance * (cos(angle));
float  dy =y+distance * (sin(angle));

lua_pushnumber ( state, dx );
lua_pushnumber ( state, dy);
return 2;


};





int MOAIMathUtil::_point_on_rect ( lua_State* L ) {

//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

//POINTS
float px =  state.GetValue < float >( 2, 0 );
float py =  state.GetValue < float >( 3, 0 );

float x1 =  state.GetValue < float >( 4, 0 );
float y1 =  state.GetValue < float >( 5, 0 );

float x2 =  state.GetValue < float >( 6, 0 );
float y2 =  state.GetValue < float >( 7, 0 );

float qx = px;
float qy=   py;

  if (qx < x1) {
    qx = x1;
  }
  if (qx > x2) {
    qx = x2;
  }
  if (qy < y1) {
    qy = y1;
  }
  if (qy > y2) {
    qy = y2;
  };

float distance = getDistance(px,py,qx,qy);

lua_pushnumber ( state, distance );
lua_pushnumber ( state, qx );
lua_pushnumber ( state, qy);
return 3;

}




int MOAIMathUtil::_point_on_line ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

//POINTS
float px =  state.GetValue < float >( 2, 0 );
float py =  state.GetValue < float >( 3, 0 );

float ax =  state.GetValue < float >( 4, 0 );
float ay =  state.GetValue < float >( 5, 0 );

float bx =  state.GetValue < float >( 6, 0 );
float by =  state.GetValue < float >( 7, 0 );


float dx = ax - bx;
float dy = ay - by;

float det = ay*bx - ax*by;
float dot = dx*px + dy*py;

float x = dot*dx + det*dy;
float y = dot*dy - det*dx;
float z = dx*dx + dy*dy;

if (z == 0) {
	lua_pushnumber ( state, -1 );
	lua_pushnumber ( state, -1 );
	lua_pushnumber ( state, -1);
	return 3;
};

float zinv = 1/z;

float qx = x*zinv;
float qy = y*zinv;
float distance = getDistance(px,py,qx,qy);

lua_pushnumber ( state, distance );
lua_pushnumber ( state, qx );
lua_pushnumber ( state, qy);
return 3;

};







//*******************************************************************************************************************************************************************
//*******************************************************************************************************************************************************************


//DOES THIS LEAK MY C++ SUXS : When a vector goes out of scope, the compiler issues a call to its destructor which in turn frees the allocated memory on the heap.
//Remember that YOU didn't use new so YOU don't have to use delete
int MOAIMathUtil::_point_in_polygon ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

		//POINTS
		float px =  state.GetValue < float >( 2, 0 );
		float py =  state.GetValue < float >( 3, 0 );

		vector<mPoint> points;

		u32 counter = 0;
		float x =0;
		float y =0;		
		lua_pushnil ( L );
		while ( lua_next ( L, 4 ) != 0 ) {
			if ( counter % 2 == 0 ) {
				x = state.GetValue < float >( -1, 0 );		
			} else {
				y = state.GetValue < float >( -1, 0 );				
				points.push_back(mPoint(x,y));
		
			}	
			++counter;
			lua_pop ( L, 1 );
		}



	int i, j, nvert = points.size();
	bool c = false;
	for(i = 0, j = nvert - 1; i < nvert; j = i++) {
		if( ( (points[i]._x >= py ) != (points[j]._y >= py) ) && 
			(px <= (points[j]._x - points[i]._x) * (y - points[i]._y) / (points[j]._y - points[i]._y) + points[i]._x)
	)
		c = !c;
	}
	points.clear();//	???
	lua_pushboolean ( state, c);
	return 1;
};





//----------------------------------------------------------------//
int MOAIMathUtil::_point_in_circle ( lua_State* L ) {

//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

//POINTS
float px =  state.GetValue < float >( 2, 0 );
float py =  state.GetValue < float >( 3, 0 );

float cx =  state.GetValue < float >( 4, 0 );
float cy =  state.GetValue < float >( 5, 0 );
float cr =  state.GetValue < float >( 6, 0 );

  bool value = false;
  float dx = px - cx;
  float dy = py - cy;
  float distSq = dx*dx + dy*dy;
  if (distSq > cr*cr) {
    value = false;
  } else {
	value = true;
  };

 lua_pushboolean ( state, value);
 return 1;
};


//----------------------------------------------------------------//
int MOAIMathUtil::_point_in_rect ( lua_State* L ) {

//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

//POINTS
float px =  state.GetValue < float >( 2, 0 );
float py =  state.GetValue < float >( 3, 0 );

float x1 =  state.GetValue < float >( 4, 0 );
float y1 =  state.GetValue < float >( 5, 0 );
float x2 =  state.GetValue < float >( 6, 0 );
float y2 =  state.GetValue < float >( 7, 0 );

 lua_pushboolean ( state,  (px >= x1 && py >= y1 && px <= x2 && py <= y2));
 return 1;
};












//----------------------------------------------------------------//
//_doRectsCollide

bool MOAIMathUtil::doRectsCollide(float ax1,float ay1,float ax2, float ay2, float bx1,  float by1, float bx2, float by2){
return !(ax1 >= bx2 || ax2 <= bx1 || ay1 >= by2 || ay2 <= by1); 
};

//----------------------------------------------------------------//
//_doRectsCollide
int MOAIMathUtil::_doRectsCollide ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

float  ax1	 = state.GetValue < float >( 2, 0 );
float  ay1	 = state.GetValue < float >( 3, 0 );

float  ax2	 = state.GetValue < float >( 4, 0 );
float  ay2	 = state.GetValue < float >( 5, 0 );

float  bx1	 = state.GetValue < float >( 6, 0 );
float  by1	 = state.GetValue < float >( 7, 0 );

float  bx2	 = state.GetValue < float >( 8, 0 );
float  by2	 = state.GetValue < float >( 9, 0 );

lua_pushboolean ( state,  MOAIMathUtil::doRectsCollide(ax1,ay1,ax2, ay2, bx1,  by1, bx2, by2) );

return 1;	
}

//----------------------------------------------------------------//
//_doCirclesCollide

bool MOAIMathUtil::doCirclesCollide(float ax1,float ay1,float ar1, float bx1, float by1,  float br1){
  return (ax1 - bx1)* (ax1 - bx1) + (ay1 - by1)*(ay1 - by1) <= (ar1+  br1)*(ar1+  br1);
};

//----------------------------------------------------------------//
//_doRectsCollide
int MOAIMathUtil::_doCirclesCollide ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

float  ax1	 = state.GetValue < float >( 2, 0 );
float  ay1	 = state.GetValue < float >( 3, 0 );
float  ar1	 = state.GetValue < float >( 4, 0 );

float  bx1	 = state.GetValue < float >( 5, 0 );
float  by1	 = state.GetValue < float >( 6, 0 );
float  br1	 = state.GetValue < float >( 7, 0 );

lua_pushboolean ( state,  MOAIMathUtil::doCirclesCollide(ax1,ay1,ar1, bx1,by1,br1) );

return 1;	
}

//_line_vs_line
ZLHit MOAIMathUtil::line_vs_line(float ax1,float ay1,float bx1,float by1,float ax2, float ay2,float bx2,float by2) {

float sa1 = signed_triangle_area(ax1, ay1, bx1, by1, bx2, by2);
float sa2 = signed_triangle_area(ax1, ay1, bx1, by1, ax2, ay2);

ZLHit hit; 
hit.mDistance = -1;
hit.mX = -1;
hit.mY = -1;

  if ((sa1*sa2) < 0) {
    float sa3 = signed_triangle_area(ax2, ay2, bx2, by2, ax1, ay1);
    float sa4 = sa3 + sa2 - sa1;
    if ((sa3*sa4) < 0) {

		float t = sa3 /(sa3 - sa4);
		float qx = ax1 + t*(bx1 - ax1);
		float qy = ay1 + t*(by1 - ay1);

		ZLHit hit; 
		hit.mX	= qx;
		hit.mY	= qy;

		//DISTANCE FROM x1,y1 to hit point
		hit.mDistance = getDistance( ax1,ay1,qx,qy);
		return hit;
	}
		return hit;
  }
  	return hit;
};

//----------------------------------------------------------------//
//_line_vs_line
int MOAIMathUtil::_line_vs_line ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

float  ax1	 = state.GetValue < float >( 2, 0 );
float  ay1	 = state.GetValue < float >( 3, 0 );

float  bx1	 = state.GetValue < float >( 4, 0 );
float  by1	 = state.GetValue < float >( 5, 0 );

float  ax2	 = state.GetValue < float >( 6, 0 );
float  ay2	 = state.GetValue < float >( 7, 0 );

float  bx2	 = state.GetValue < float >( 8, 0 );
float  by2	 = state.GetValue < float >( 9, 0 );


ZLHit hit  = MOAIMathUtil::line_vs_line(ax1,ay1,bx1, by1, ax2,  ay2, bx2, by2) ;

lua_pushnumber ( state, hit.mDistance );
lua_pushnumber ( state, hit.mX );
lua_pushnumber ( state, hit.mY );
return 3;	
}

//----------------------------------------------------------------//
//_line_vs_line

int MOAIMathUtil::_line_vs_line_is ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

//1
float  _ax1	 = state.GetValue < float >( 2, 0 );
float  _ay1	 = state.GetValue < float >( 3, 0 );

float  _ax2	 = state.GetValue < float >( 4, 0 );
float  _ay2	 = state.GetValue < float >( 5, 0 );

//2
float  _bx1	 = state.GetValue < float >( 6, 0 );
float  _by1	 = state.GetValue < float >( 7, 0 );

float  _bx2	 = state.GetValue < float >( 8, 0 );
float  _by2	 = state.GetValue < float >( 9, 0 );


//IF ANY THING IS ZERO IT FAILS?? 

//PRE DOT
//(a.y*b.x) - (a.x*b.y); 
//Point a(A2-A1);
//Point b(B2-B1);

float  p1x	 = _ax2 - _ax1;
float  p1y	 = _ay2 - _ay1;

float  p2x	 = _bx2 - _bx1;
float  p2y	 = _by2 - _by1;

double f = (p1y*p2x)-(p1x*p2y);  
if(!f) {
	lua_pushboolean ( state, false);
	return 1;    
};

float  p3x	 =_bx2-_ax2;
float  p3y	 =_by2-_ay2; 

double aa = (p1y*p3x)-(p1x*p3y);  
double bb = (p2y*p3x)-(p2x*p3y);

//double aa = PerpDot(a,c);
//double bb = PerpDot(b,c);

boolean isTrue;
isTrue = true;

if(f < 0)
{
    if(aa > 0)     isTrue = false;
    if(bb > 0)     isTrue = false;
    if(aa < f)     isTrue = false;
    if(bb < f)     isTrue = false;
}
else
{
    if(aa < 0)    isTrue = false;
    if(bb < 0)    isTrue = false;
    if(aa > f)    isTrue = false;
    if(bb > f)    isTrue = false;
}

//IS COLLISION POINT
//double* out = 0;
//if(out)
//*out = 1.0 - (aa / f);
	lua_pushboolean ( state, isTrue);
    return 1;

}


//************************************************************************************************************************
//_line_vs_line
ZLHit MOAIMathUtil::line_vs_circle(float ax1,float ay1,float bx1,float by1,float cx,float cy,float radius) {

ZLHit hit; 
hit.mDistance = -1;
hit.mX = -1;
hit.mY = -1;

	float dx = bx1 - ax1; 
	float dy = by1 - ay1;

	float d = length(dx, dy);

	 dx = dx/d;
	 dy = dy/d;

	float mx  = ax1 - cx; 
	float my  = ay1 - cy;

	float b = dot(mx, my, dx, dy);
	float c = dot(mx, my, mx, my) - (radius*radius);

	if ((c > 0) && (b > 0)) {
		return hit;
	};  

	float discr = b*b - c;
	if (discr < 0) {
		return hit;
	};  

	float  t = -b - sqrt(discr);
	if (t < 0) {
		t = 0;
	};


	if (t > d) {
	return hit;
	};  

	hit.mDistance = t;
	hit.mX = ax1 + t*dx;
	hit.mY = ay1 + t*dy;
	return hit;
};

//----------------------------------------------------------------//
//_line_vs_circle
int MOAIMathUtil::_line_vs_circle ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

float  ax1	 = state.GetValue < float >( 2, 0 );
float  ay1	 = state.GetValue < float >( 3, 0 );

float  bx1	 = state.GetValue < float >( 4, 0 );
float  by1	 = state.GetValue < float >( 5, 0 );

float  cx		 = state.GetValue < float >( 6, 0 );
float  cy		 = state.GetValue < float >( 7, 0 );
float  radius	 = state.GetValue < float >( 8, 0 );

ZLHit hit  = MOAIMathUtil::line_vs_circle(ax1,ay1,bx1, by1, cx,  cy, radius) ;

lua_pushnumber ( state, hit.mDistance );
lua_pushnumber ( state, hit.mX );
lua_pushnumber ( state, hit.mY );
return 3;	
}


//************************************************************************************************************************
//_line_vs_rect
ZLHit MOAIMathUtil::line_vs_rect(float ax1,float ay1,float bx1,float by1,float l, float t,float r,float b) {

ZLHit hit; 
hit.mDistance	= -1;
hit.mX			= -1;
hit.mY			= -1;

	float dx=  bx1 - ax1; 
	float dy=  by1 - ay1;

	float d  = length(dx, dy);
	float nx = dx/d; 
	float ny = dy/d;

	float  tmin = 0;
	float  tmax = d;

	if (dx == 0) {
	if ((ax1 < l) || (ax1 > r)) {
		return hit;
	} 
	} else {
	float ood = 1/nx;
	float t1 = (l - ax1)*ood;
	float t2 = (r - ax1)*ood;
	if (t1 > t2) {
		
		float temp = t1;
		t1 = t2;
		t2 = temp;

	};
	tmin = max(tmin, t1); 
	tmax = min(tmax, t2); 

	if (tmin > tmax) {
		return hit;
	}
	};

	
	if (dy == 0) {
	if ((ay1 < t) || (ay1 > b)) {
		return hit;
	}
	} else {
	float ood = 1/ny;
	float t1 = (t - ay1)*ood;
	float t2 = (b - ay1)*ood;
	if (t1 > t2) {

        float temp = t1;
		t1 = t2;
		t2 = temp;
	}
	tmin = max(tmin, t1); 
	tmax = min(tmax, t2);

		if (tmin > tmax) {
			return hit;
		}
	}



  hit.mDistance = tmin;
  hit.mX = ax1 + nx*tmin;
  hit.mY = ay1 + ny*tmin;

  return hit;



};

//----------------------------------------------------------------//
//_line_vs_circle
int MOAIMathUtil::_line_vs_rect ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

float  ax1	 = state.GetValue < float >( 2, 0 );
float  ay1	 = state.GetValue < float >( 3, 0 );

float  bx1	 = state.GetValue < float >( 4, 0 );
float  by1	 = state.GetValue < float >( 5, 0 );

float  x1	 = state.GetValue < float >( 6, 0 );//LEFT
float  y1	 = state.GetValue < float >( 7, 0 );//TOP

float  x2	 = state.GetValue < float >( 8, 0 );//RIGHT
float  y2	 = state.GetValue < float >( 9, 0 );//BOTTOM

ZLHit hit  = MOAIMathUtil::line_vs_rect(ax1,ay1,bx1, by1, x1,  y1, x2, y2) ;

lua_pushnumber ( state, hit.mDistance );
lua_pushnumber ( state, hit.mX );
lua_pushnumber ( state, hit.mY );
return 3;	
}




//----------------------------------------------------------------//
//RECT COLLID

int MOAIMathUtil::_rect_vs_rect_is ( lua_State* L ) {

MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

int x1	= state.GetValue < float >( 2, 0 );//LEFT
int y1	= state.GetValue < float >( 3, 0 );//TOP
int w1	= state.GetValue < float >( 4, 0 );//TOP
int h1  = state.GetValue < float >( 5, 0 );//TOP

int x2	= state.GetValue < float >( 6, 0 );//RIGHT
int y2	= state.GetValue < float >( 7, 0 );//BOTTOM
int w2	= state.GetValue < float >( 8, 0 );//TOP
int h2  = state.GetValue < float >( 9, 0 );//TOP

lua_pushboolean ( state, !(x1 > x2+w2 || x1+w1 < x2 || y1 > y2+h2 || y1+h1 < y2));

return 1;
}





////----------------------------------------------------------------//
//moveTo2D
USVec2D  MOAIMathUtil::moveTo2D(float speed,float x1, float y1, float x2, float y2) {

	float angle = atan2(  (y2 - y1) , (x2 - x1) );
	USVec2D vec; 
	vec.mX  = cos(angle) * speed;
	vec.mY 	= sin(angle) * speed; 
	return vec;	
}

//----------------------------------------------------------------//
//_moveTo2D
int MOAIMathUtil::_moveTo2D ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" );

float  speed = state.GetValue < float >( 2, 0 );

float  x1	 = state.GetValue < float >( 3, 0 );
float  y1	 = state.GetValue < float >( 4, 0 );

float  x2	 = state.GetValue < float >( 5, 0 );
float  y2	 = state.GetValue < float >( 6, 0 );

USVec2D vec = MOAIMathUtil::moveTo2D(speed,x1,y1,x2,y2) ;

lua_pushnumber ( state, vec.mX );
lua_pushnumber ( state, vec.mY );
return 2;	
}





//----------------------------------------------------------------//
//getDistance2D
float  MOAIMathUtil::getDistance2D(float x1, float y1, float x2, float y2) {
return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));	
}

//----------------------------------------------------------------//
//_getDistance2D
int MOAIMathUtil::_getDistance2D ( lua_State* L ) {

//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

float  x1 =state.GetValue < float >( 2, 0 );
float  y1 =state.GetValue < float >( 3, 0 );

float  x2 = state.GetValue < float >( 4, 0 );
float  y2 = state.GetValue < float >( 5, 0 );

lua_pushnumber ( state, MOAIMathUtil::getDistance2D(x1,y1,x2,y2)  );
return 1;	
}

//----------------------------------------------------------------//
//getAngle2D
float  MOAIMathUtil::getAngle2D(float x1, float y1, float x2, float y2) {
return  atan2(  (y2 - y1) , (x2 - x1) );
}

//----------------------------------------------------------------//
//_getAngle2D
int MOAIMathUtil::_getAngle2D ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )


float  x1 =state.GetValue < float >( 2, 0 );
float  y1 =state.GetValue < float >( 3, 0 );

float  x2 = state.GetValue < float >( 4, 0 );
float  y2 = state.GetValue < float >( 5, 0 );

lua_pushnumber ( state, MOAIMathUtil::getAngle2D(x1,y1,x2,y2)  );
return 1;	
}



//----------------------------------------------------------------//
//_getAngle2D
int MOAIMathUtil::_mid_point ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )


float  x1 =state.GetValue < float >( 2, 0 );
float  y1 =state.GetValue < float >( 3, 0 );

float  x2 = state.GetValue < float >( 4, 0 );
float  y2 = state.GetValue < float >( 5, 0 );

 //mid Point((p1.x+p2.x)/2, (p1.y+p2.y)/2)
  //return Point((p1.x+p2.x)/2, (p1.y+p2.y)/2);

lua_pushnumber ( state, ((x1+x2)/2) );
lua_pushnumber ( state, ((y1+y2)/2) );
return 2;	
}










//****************************************************************************************************************************************
//****************************************************************************************************************************************


int MOAIMathUtil::_getSmallAngle2D ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

float  x =state.GetValue < float >( 2, 0 );
float  y =state.GetValue < float >( 3, 0 );

double arg;
int f = y-x;
arg = fmod(f, C360);
if (arg < 0 )  arg  = arg + C360;
if (arg > 180) arg  = arg - C360;

//float value = min((y-x, y-x+2*PI), (y-x-2*PI), key=abs);
lua_pushnumber ( state, -arg  );
return 1;

};



//****************************************************
//HERO_X
//HERO_Y
//HERO_ANGLE
//TRAGET_X
//TARGET_Y

int MOAIMathUtil::_inFrontLine ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

float  x1		=state.GetValue < float >( 2, 0 );
float  y1		=state.GetValue < float >( 3, 0 );

float  angle	=state.GetValue < float >( 4, 0 );

float  x2		=state.GetValue < float >( 5, 0 );
float  y2		=state.GetValue < float >( 6, 0 );


double  anglef = (angle+90+self->mRot)* (PI / 180);
double  angleb = (angle-90+self->mRot)* (PI / 180);

double  ax =x1+10000 * (cos(anglef));
double  ay =y1+10000 * (sin(anglef));

double  bx =x1+10000 * (cos(angleb));
double  by =y1+10000 * (sin(angleb));

bool   value = inFrontLine(ax,ay,bx,by,x2,y2);


lua_pushboolean ( state, value  );
lua_pushnumber ( state, ax  );
lua_pushnumber ( state, ay  );
lua_pushnumber ( state, bx  );
lua_pushnumber ( state, by  );
return 5;
};




//****************************************************************************************************************************************
//****************************************************************************************************************************************
int MOAIMathUtil::_inFrontTriangle ( lua_State* L ) {

//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

float  x1		=state.GetValue < float >( 2, 0 );
float  y1		=state.GetValue < float >( 3, 0 );

float  angle	=state.GetValue < float >( 4, 0 );

float  px		=state.GetValue < float >( 5, 0 );
float  py		=state.GetValue < float >( 6, 0 );



float  anglef = (angle+45+self->mRot)* (PI / 180);
float  angleb = (angle-45+self->mRot)* (PI / 180);

float  ax =x1+10000 * (cos(anglef));
float  ay =y1+10000 * (sin(anglef));

float  bx =x1+10000 * (cos(angleb));
float  by =y1+10000 * (sin(angleb));

bool   value = inFrontTriangle(x1,y1,ax,ay,bx,by,px,py);


lua_pushboolean ( state, value  );

lua_pushnumber ( state, ax  );
lua_pushnumber ( state, ay  );
lua_pushnumber ( state, bx  );
lua_pushnumber ( state, by  );
return 5;
};



//****************************************************************************************************************************************
//****************************************************************************************************************************************


//----------------------------------------------------------------//
//getDistance3D
float  MOAIMathUtil::getDistance3D(float x1, float y1,float z1, float x2, float y2,float z2) {
return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) + (z1 - z2)*(z1 - z2));
}

//----------------------------------------------------------------//
//_getDistance3D
int MOAIMathUtil::_getDistance3D ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

float  x1 =state.GetValue < float >( 2, 0 );
float  y1 =state.GetValue < float >( 3, 0 );
float  z1 =state.GetValue < float >( 4, 0 );

float  x2 = state.GetValue < float >( 5, 0 );
float  y2 = state.GetValue < float >( 6, 0 );
float  z2 =state.GetValue < float >( 7, 0 );

lua_pushnumber ( state, MOAIMathUtil::getDistance3D(x1,y1,z1,x2,y2,z2)  );
return 1;	
}



//----------------------------------------------------------------//
//_rot_points
int MOAIMathUtil::_rotate_point ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

float  degrees = state.GetValue < float >( 2, 0 );


float  point_x =state.GetValue < float >( 3, 0 );
float  point_y = state.GetValue < float >( 4, 0 );

float  offset_x =state.GetValue < float >( 5, 0 );
float  offset_y =state.GetValue < float >( 6, 0 );

degrees = degrees * (PI/180);

float rx  =  point_x + ( cos((degrees))*(offset_x) - sin((degrees)) * (offset_y) );
float ry  =  point_y + ( sin((degrees))*(offset_x) + cos((degrees)) * (offset_y) );

lua_pushnumber ( state, rx  );
lua_pushnumber ( state, ry  );

return 2;	
}




int MOAIMathUtil::_rotate_check ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

float  degrees = state.GetValue < float >( 2, 0 );
if (degrees > 360) {
	degrees = degrees - 360;
} else if (degrees < 0) {
	degrees = degrees + 360;
}
lua_pushnumber ( state, degrees  );
return 1;
};


int MOAIMathUtil::_setRotOff ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" );
	self->mRot =  state.GetValue < int >( 2, 0 );
return 0;
};


int MOAIMathUtil::_setMap ( lua_State* L ) {
//MOAILuaState state ( L );
MOAI_LUA_SETUP ( MOAIMathUtil, "U" );
	self->mTile   =  state.GetValue < int >( 2, 0 );
	self->mWidth  =  state.GetValue < int >( 3, 0 );
	self->mHeight =  state.GetValue < int >( 4, 0 );
return 0;
};


int MOAIMathUtil::_indexToGrid ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIMathUtil, "U" );

int index   =  state.GetValue < int >( 2, 0 );
index = index -1;

int grid_rx = (index % self->mWidth);
int grid_ry = (index / self->mHeight);

lua_pushnumber ( state, grid_rx  );
lua_pushnumber ( state, grid_ry  );
return 2;

};




//******************************************************************
// http://playtechs.blogspot.ca/2007/03/raytracing-on-grid.html
int MOAIMathUtil::_rayTest ( lua_State* L ) {

//printf("%f %f %f %f \n",x0,y0,x1,y1);
//lua_getglobal(L, "global_raycast");
//lua_pushnil ( L );
//lua_pop ( L, -3 );
//int i; 
// for (i = 1; i <= 20; i++) {
//        lua_pushnumber(L, i);   /* Push the table index */
//        lua_pushnumber(L, i);  /* Push the cell value */
//        lua_rawset(L, -3);     /* Stores the pair in the table */
//    }
//lua_pushnumber ( state, i-1  );
//return 1;


MOAI_LUA_SETUP ( MOAIMathUtil, "U" )
float  x0 = state.GetValue < int >( 3, 0 );
float  y0 = state.GetValue < int >( 4, 0 );

float  x1 = state.GetValue < int >( 5, 0 );
float  y1 = state.GetValue < int >( 6, 0 );

lua_pushnil ( L );
lua_pop ( L, -3 );

int tile   = self->mTile;
int width  = self->mWidth;
int height = self->mHeight;

x0 = x0 / tile;
y0 = y0 / tile;

x1 = x1 / tile;
y1 = y1 / tile;

u32 total = 0;

double dx = fabs(x1 - x0);
double dy = fabs(y1 - y0);

int x = int(floor(x0));
int y = int(floor(y0));

int n = 1;
int x_inc, y_inc;
double error;

if (dx == 0)
{
    x_inc = 0;
    error = std::numeric_limits<double>::infinity();
}
else if (x1 > x0)
{
    x_inc = 1;
    n += int(floor(x1)) - x;
    error = (floor(x0) + 1 - x0) * dy;
}
else
{
    x_inc = -1;
    n += x - int(floor(x1));
    error = (x0 - floor(x0)) * dy;
}

if (dy == 0)
{
    y_inc = 0;
    error -= std::numeric_limits<double>::infinity();
}
else if (y1 > y0)
{
    y_inc = 1;
    n += int(floor(y1)) - y;
    error -= (floor(y0) + 1 - y0) * dx;
}
else
{
    y_inc = -1;
    n += y - int(floor(y1));
    error -= (y0 - floor(y0)) * dx;
}

for (; n > 0; --n)
{
   
	if ((x >= 0 && x <= width) &&   (y >= 0 && y <= width)) {
		++total;
		lua_pushnumber(L, total);			 /* Push the table index */
        lua_pushnumber(L, x +(width*y)+1);  /* Push the cell value */
        lua_rawset(L, -3);					 /* Stores the pair in the table */
	}

    if (error > 0)
    {
        y += y_inc;
        error -= dx;
    }
    else
    {
        x += x_inc;
        error += dy;
    }
}    
lua_pushnumber ( state, total  );
return 1;
}


//******************************************************************
// http://playtechs.blogspot.ca/2007/03/raytracing-on-grid.html
int MOAIMathUtil::_raycast ( lua_State* L ) {

MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

float  x0 = state.GetValue < float >( 2, 0 );
float  y0 = state.GetValue < float >( 3, 0 );

float  x1 = state.GetValue < float >( 4, 0 );
float  y1 = state.GetValue < float >( 5, 0 );


//int width  = state.GetValue < float >( 6, 0 );
//int height = state.GetValue < float >( 7, 0 );
//int tile = state.GetValue < float >( 8, 0 );

int tile   = self->mTile;
int width  = self->mWidth;
int height = self->mHeight;


x0 = x0 / tile;
y0 = y0 / tile;

x1 = x1 / tile;
y1 = y1 / tile;

//lua_newtable(state);

u32 total = 0;

double dx = fabs(x1 - x0);
double dy = fabs(y1 - y0);

int x = int(floor(x0));
int y = int(floor(y0));

int n = 1;
int x_inc, y_inc;
double error;

if (dx == 0)
{
    x_inc = 0;
    error = std::numeric_limits<double>::infinity();
}
else if (x1 > x0)
{
    x_inc = 1;
    n += int(floor(x1)) - x;
    error = (floor(x0) + 1 - x0) * dy;
}
else
{
    x_inc = -1;
    n += x - int(floor(x1));
    error = (x0 - floor(x0)) * dy;
}

if (dy == 0)
{
    y_inc = 0;
    error -= std::numeric_limits<double>::infinity();
}
else if (y1 > y0)
{
    y_inc = 1;
    n += int(floor(y1)) - y;
    error -= (floor(y0) + 1 - y0) * dx;
}
else
{
    y_inc = -1;
    n += y - int(floor(y1));
    error -= (y0 - floor(y0)) * dx;
}

for (; n > 0; --n)
{
   
	if ((x >= 0 && x <= width) &&   (y >= 0 && y <= width)) {
		++total;
		//lua_pushnumber(state, total); 
		lua_pushnumber(state, x +(width*y)+1);
		//lua_settable(state, -3);
	}

    if (error > 0)
    {
        y += y_inc;
        error -= dx;
    }
    else
    {
        x += x_inc;
        error += dy;
    }
}

	//return 1;
	return total;
};





//*****************************************************************************************************************************
//*****************************************************************************************************************************
//*****************************************************************************************************************************
//*****************************************************************************************************************************
//*****************************************************************************************************************************
//*****************************************************************************************************************************










//*************************************************************************************

//struct VectorComp : std::binary_function<ClipperLib::IntPoint, ClipperLib::IntPoint, bool>
//{
//
//    ClipperLib::IntPoint M;
//	//int X;
//	//int Y;
//    IntersectComp(ClipperLib::IntPoint v) : M(v) {}
//
//    bool operator() ( ClipperLib::IntPoint o1,  ClipperLib::IntPoint o2)
//    {
//        float ang1     = atan( ((o1.Y - M.Y)/(o1.X - M.X) ) * M_PI / 180);
//        float ang2     = atan( (o2.Y - M.Y)/(o2.X - M.X) * M_PI / 180);
//        if(ang1 < ang2) return true;
//        else if (ang1 > ang2) return false;
//        return true;
//    }
//};


//**************************************************************************************************************
//**************************************************************************************************************
// I DON"T KNOW HOW TO USE MY STD

	//auto sort_predicate = [&centroid] (const IntPoint& a, const IntPoint& b) -> bool {			
	//	float ang1 = atan2f (a.X - centroid.X, a.Y - centroid.Y); 
	//	float ang2 = atan2f (b.X - centroid.X, b.Y - centroid.Y);
	//	return(ang1 < ang2);   	
	//};
	//std::sort (shadow[0].begin(), shadow[0].end(), sort_predicate);


//**************************************************************************************************************
//FAILS OF PINTS ARE IN ORDER;
//DOESN'TWORK
//IntPoint orgin = IntPoint(sum_x,sum_y);
//IntPoint ref   = IntPoint(150,210);


class angle_sort
{
    IntPoint m_origin;
    IntPoint m_dreference;
    static double xp(IntPoint a, IntPoint b)  { return a.X * b.Y - a.Y * b.X; }
   // const static IntPoint subP(IntPoint a, IntPoint b)  { return IntPoint(a.X-b.X,a.Y-b.Y);}
public:
	angle_sort(const IntPoint origin, const IntPoint reference) : m_origin(origin), m_dreference(reference.X -origin.X, reference.Y -origin.Y )  {}
    bool operator()(const IntPoint a, const IntPoint b) const
    {


        const IntPoint da (a.X -m_origin.X, a.Y -m_origin.Y );
		const IntPoint db (b.X -m_origin.X, b.Y -m_origin.Y );

		// const IntPoint da(subP(a , m_origin)); 
		// const IntPoint db(subP(b , m_origin));

        const double detb = xp(m_dreference, db);

        // nothing is less than zero degrees
   //  if (detb == 0 && db.X * m_dreference.X + db.Y * m_dreference.Y >= 0) return false;

        const double deta = xp(m_dreference, da);

	//	if (deta == 0 && da.X * m_dreference.X + da.Y * m_dreference.Y >= 0) return true;


        if (deta * detb >= 0) {
            // both on same side of reference, compare to each other
            return xp(da, db) > 0;
        }
        // vectors "less than" zero degrees are actually large, near 2 pi
        return deta > 0;
    }
};


//************************************************************************************************************************






//********************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************
int MOAIMathUtil::_clipLight ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )	

//PROBABLY CAST HERE FOR BOX2D DATA

Paths  light(1);

//LIGHT
//light[0] << IntPoint(180,200); 
//light[0] << IntPoint(260,200);
//light[0] << IntPoint(260,150);
//light[0] << IntPoint(180,150);


	lua_pushnil ( L );
	int x = 0;
	int y = 0;
	u32 counter = 0;
	lua_pushnil ( L );
    while ( lua_next ( L, 2 ) != 0 ) {
	++counter;
			if ( counter == 1 ) {	
				x = state.GetValue < int >( -1, 0);
			} else {
				y = state.GetValue < int >( -1, 0);			
			light[0] << IntPoint(x,y);
			counter = 0;		
			}				
			lua_pop ( L, 1 );
	}

//c.Clear();
c.AddPaths(light, ptSubject, true); //THIS COPIES THE ARRAY

return 0;
}
//********************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************
int MOAIMathUtil::_clipShadow ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

//
//Paths  inner(1),shadow(1);
//
////printf("SHADOW \n");
//
////SHDOWS
////shadow[0] << IntPoint(150,210); //1	
////shadow[0] << IntPoint(240,130); //2
////shadow[0] << IntPoint(150,130);	//4 : ORDER	
////shadow[0] << IntPoint(240,210); //3	
//
//float light_x = state.GetValue < float >( 3, 0 );
//float light_y = state.GetValue < float >( 4, 0 );
//
//
//	lua_pushnil ( L );
//	int x = 0;
//	int y = 0;
//	u32 counter = 0;
//	lua_pushnil ( L );
//    while ( lua_next ( L, 2 ) != 0 ) {
//	++counter;
//			if ( counter == 1 ) {	
//				x = state.GetValue < float >( -1, 0.0f);
//			} else {
//				y = state.GetValue < float >( -1, 0.0f);			
//			inner[0] << IntPoint(x,y);
//			counter = 0;		
//			}				
//			lua_pop ( L, 1 );
//	}
//
//
//	//*****************************************************************
//	//SORT : COSTLY
//	int sum_x = 0;
//	int sum_y = 0;
//	int sCnt  = 0;
//	for(auto j = inner[0].begin(); j != inner[0].end() ; ++j){		
//
//		sum_x = sum_x+j->X;
//		sum_y = sum_y+j->Y;	
//		++sCnt;
//	};
//	if (sCnt == 0) {
//		printf("CRASH \n");
//	} else {
//		sum_x = sum_x / sCnt;
//		sum_y = sum_y / sCnt;
//	}
//
//	//SORT INNER POINTS
//	IntPoint centroid = IntPoint(sum_x,sum_y);
//	IntPoint light    = IntPoint(light_x,light_y);
//	std::sort (inner[0].begin(), inner[0].end(), angle_sort(centroid,light));
//
//	//ADD TO SHADOW
//	for(auto j = inner[0].begin(); j != inner[0].end() ; ++j){
//		shadow[0] << IntPoint(j->X,j->Y);
//	};
//
//	//LOOP BACKWARDS AND PROJECT 
//   float distance = 400;
//   float x1		  = light_x;
//   float y1		  = light_y;
//
//	for(auto j = inner[0].rbegin(); j != inner[0].rend() ; ++j){			
//
//			float x2 = j->X;
//			float y2 = j->Y;
//
//			float angler = atan2(  (y2 - y1) , (x2 - x1) );
//
//			float  dx =x1+distance * (cos(angler));
//			float  dy =y1+distance * (sin(angler));
//
//			shadow[0] << IntPoint(dx,dy);
//
//	};
//
//
//
////********************************************************************
//c.AddPaths(shadow, ptClip, true);//THIS COPIES THE ARRAY
//
//
//
//
//int cnt = 0;
//for(auto j = shadow[0].begin(); j != shadow[0].end() ; ++j){
//	int x = j->X;
//	int y = j->Y;		
//	++cnt;
//	lua_pushnumber ( state, x);
//	lua_pushnumber ( state, y);
//};
//
//return cnt*2;
//

return 0;


};

//********************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************
//POLY TO TRY


int MOAIMathUtil::_clipExecute ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

//TEXTURE
MOAITexture* texture = (MOAITexture*)MOAITexture::AffirmTexture ( state, 2 );
float light_x = state.GetValue < float >( 3, 0 );
float light_y = state.GetValue < float >( 4, 0 );

//VAIRBLES
Paths  output(1);
int cnt = 0;


//REMOVE ALL SHADOWS(CLIPPERS) FROM THE SUBJECT(LIGHT) WITH DIFFERENCE
c.Execute(ctDifference, output, pftNonZero, pftNonZero);
//c.Execute(ctIntersection, output, pftNonZero, pftNonZero);
c.Clear();


//*****************************************************************************************
//*****************************************************************************************
//NOPE

					//
					//
					//double start_time = ZLDeviceTime::GetTimeInSeconds();
					//
					//vector<p2t::Point*> polyline;
					//vector<Triangle*> triangles;
					//vector< vector<Point*> > polylines;
					//
					//
					////for( int i = 0; i < output.size(); i++){	
					//		for(auto j = output[0].begin(); j != output[0].end() ; ++j){				
					//			polyline.push_back(new Point(j->X,j->Y));
					//		}
					////} 
					//
					//CDT* cdt = new CDT(polyline);
					//cdt->Triangulate();
					////cdt->a
					////
					//
					////****************************************************************
					//
					//triangles = cdt->GetTriangles();
					//cout << "Number of triangles = " << triangles.size() << endl;
					//p2t::Triangle* t;
					//
					//  for (int i = 0; i < triangles.size(); i++) {
					//	  t = triangles[i];  
					//		//printf("a %f %f \n",a.x,a.y); 
					//			lua_pushnumber ( state, t->GetPoint(0)->x);
					//			lua_pushnumber ( state, t->GetPoint(0)->y);
					//
					//		//printf("b %f %f \n",b.x,b.y); 
					//			lua_pushnumber ( state, t->GetPoint(1)->x);
					//			lua_pushnumber ( state, t->GetPoint(1)->y);
					//
					//		//printf("c %f %f \n",c.x,c.y); 
					//			lua_pushnumber ( state, t->GetPoint(2)->x);
					//			lua_pushnumber ( state, t->GetPoint(2)->y);
					//
					//		cnt = cnt + 6;
					//  };
					//
					//
					//
					//
					////****************************************************************
					////int cnt = 0;
					//
					////polylines.push_back(polyline);
					////  for(int i = 0; i < polylines.size(); i++) {
					////    vector<Point*> poly = polylines[i];
					////      for(int j = 0; j < poly.size(); j++) {
					////			int x = poly[j]->x;
					////			int y = poly[j]->y;	
					////
					////			lua_pushnumber ( state, x);
					////			lua_pushnumber ( state, y);
					////			//cnt = cnt + 2;
					////			//printf("%d %d \n",x,y);       
					////      }  
					////  }
					////
					//
					//   
					//
					//
					//
					//
					////*******************************************************
					//  delete cdt; 
					//  for(int i = 0; i < polylines.size(); i++) {
					//    vector<p2t::Point*> polyp = polylines[i];
					//	for( int j = 0; j < polyp.size(); j++){
					//			int x = polyp[j]->x;
					//			int y = polyp[j]->y;				
					//	};	
					//    FreeClear(polyp);
					//  }
					//
					// // printf("%f \n", ZLDeviceTime::GetTimeInSeconds()-start_time);
					//
					//  return cnt;
					//




  //return 0;

//*********************************************************************
//OUT PUT THE THE LIGHT BACK TO LUA
if ( texture ) {	
if (output[0].size() > 0) {

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();

	gfxDevice.SetShaderPreset ( MOAIShaderMgr::DECK2D_SHADER );	//SHADER		
	gfxDevice.SetTexture ( texture );							//TEXTURE	
	gfxDevice.SetVertexPreset ( MOAIVertexFormatMgr::XYZWUVC ); //VERTEX_FORMATE

	gfxDevice.BeginPrim ( ZGL_PRIM_TRIANGLE_FAN );


//CALCULATE UV ??
float tsize		 = 256;
float thalf		 = tsize*0.5;
int sub_left     = light_x-thalf;
int sub_top      = light_y-thalf;

//CENTER
gfxDevice.WriteVtx ( light_x,light_y );			
gfxDevice.WriteUV((light_x-sub_left)/tsize,(light_y-sub_top)/tsize );	
gfxDevice.WriteFinalColor4b ();

		for( int i = 0; i < output[0].size(); i++){	
			gfxDevice.WriteVtx ( output[0][i].X,output[0][i].Y );			
			gfxDevice.WriteUV(( output[0][i].X-sub_left)/tsize,(output[0][i].Y -sub_top)/tsize);	
			gfxDevice.WriteFinalColor4b ();
			//printf("%d %f %f \n",i,(output[0][i].X-sub_left)/tsize,(output[0][i].Y -sub_top)/tsize);
		};

//START
gfxDevice.WriteVtx ( output[0][0].X,output[0][0].Y );			
gfxDevice.WriteUV(( output[0][0].X-sub_left)/tsize,(output[0][0].Y -sub_top)/tsize);	
gfxDevice.WriteFinalColor4b ();
gfxDevice.EndPrim ();


};//SIZE
};//TEXTURE
  
//return cnt*2;
return 0;

};

//********************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************

int MOAIMathUtil::_clip ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIMathUtil, "U" )
//
////HOLES
//Paths light(1), shadow(1), output;
//
////LIGHT
//light[0] << IntPoint(180,200); 
//light[0] << IntPoint(260,200);
//light[0] << IntPoint(260,150);
//light[0] << IntPoint(180,150);
//
//
////SHDOWS
//shadow[0] << IntPoint(150,210); //1	
//shadow[0] << IntPoint(240,130); //2
//shadow[0] << IntPoint(150,130);	//4 : ORDER	
//shadow[0] << IntPoint(240,210); //3	
//
////*******************************************************
////SORT ALL SHADOWS BY CENTRIOD
//
//
//	//SORT : COSTLY
//	int sum_x = 0;
//	int sum_y = 0;
//	int sCnt  = 0;
//	for(auto j = shadow[0].begin(); j != shadow[0].end() ; ++j){
//		sum_x = sum_x+j->X;
//		sum_y = sum_y+j->Y;	
//		++sCnt;
//	};
//	sum_x = sum_x / sCnt;
//	sum_y = sum_y / sCnt;
//
//	//	printf("SORT %d %d %d\n",sum_x,sum_y,sCnt);
//	IntPoint centroid = IntPoint(sum_x,sum_y);
//	auto sort_predicate = [&centroid] (const IntPoint& a, const IntPoint& b) -> bool {			
//		float ang1 = atan2f (a.X - centroid.X, a.Y - centroid.Y); 
//		float ang2 = atan2f (b.X - centroid.X, b.Y - centroid.Y);
//		return(ang1 < ang2);   	
//	};
//	std::sort (shadow[0].begin(), shadow[0].end(), sort_predicate);
//
//
//
//
//	//ADD LIGHT AS SUBJECT
//	c.AddPaths(light, ptSubject, true); //THIS COPIES THE ARRAY
//	//ADD ALL SHADOWS AS CLIP
//	c.AddPaths(shadow, ptClip, true);//THIS COPIES THE ARRAY
//	c.AddPaths(shadow, ptClip, true);//THIS COPIES THE ARRAY
//	c.AddPaths(shadow, ptClip, true);//THIS COPIES THE ARRAY
//	c.AddPaths(shadow, ptClip, true);//THIS COPIES THE ARRAY
//	c.AddPaths(shadow, ptClip, true);//THIS COPIES THE ARRAY
//	c.AddPaths(shadow, ptClip, true);//THIS COPIES THE ARRAY
//
//	//REMOVE ALL SHADOWS(CLIPPERS) FROM THE SUBJECT(LIGHT) WITH DIFFERENCE
//	c.Execute(ctDifference, output, pftNonZero, pftNonZero);
//	c.Clear();
//
//
//	//************************************************************
//	std::stringstream buffer;
//	for(auto i = light.begin(); i != light.end() ; ++i)
//	{			
//		//std::cout << *i << std::endl;
//	};
//
//
//	//*********************************************************************
//	//OUT PUT THE THE LIGHT BACK TO LUA
//	int cnt = 0;
//    for( int i = 0; i < output.size(); i++){	
//			for(auto j = output[i].begin(); j != output[i].end() ; ++j){
//				int x = j->X;
//				int y = j->Y;		
//				++cnt;
//				lua_pushnumber ( state, x);
//				lua_pushnumber ( state, y);
//		 };
//    };
//	return cnt*2;
//
//
//
//
//	//************************************************************************
//	//OUTPUT REC
//
//	//int cnt = 0;
//
//	//		for(auto j = shadow[0].begin(); j != shadow[0].end() ; ++j){
//	//			int x = j->X;
//	//			int y = j->Y;		
//	//			++cnt;
//	//			lua_pushnumber ( state, x);
//	//			lua_pushnumber ( state, y);
//	//	 };
// //  
//	//return cnt*2;
//
//
//




return 0;
};




//***********************************************************************
//*******************************************************************************
int MOAIMathUtil::_AABB ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIMathUtil, "U" )

	//GFX
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	const ZLFrustum& viewVolume = gfxDevice.GetViewVolume ();	

	//TYPE
	float x1=state.GetValue   < float >( 2, 0 );	
	float y1=state.GetValue   < float >( 3, 0 );
	float x2=state.GetValue   < float >( 4, 0 );
	float y2=state.GetValue   < float >( 5, 0 );	

	//printf("%f %f %f %f",x1,y1,x2,y2);

	ZLBox box;	
	box.mMin.mX = x1;
	box.mMin.mY = y1;
	box.mMin.mZ = 0.0f;
	
	box.mMax.mX = x2;
	box.mMax.mY = y2;
	box.mMax.mZ = 0.0f;

	if (viewVolume.Cull(box) == false) {
			lua_pushboolean ( state, false);
	} else {
			lua_pushboolean ( state, true);
	};



	return 1;
}





//*****************************************************************************************************************************
//*****************************************************************************************************************************
//*****************************************************************************************************************************
//*****************************************************************************************************************************
//*****************************************************************************************************************************
//*****************************************************************************************************************************


//----------------------------------------------------------------//
MOAIMathUtil::MOAIMathUtil () :
mRot ( 90 ),
mWidth (300),
mHeight (300),
mTile (32)
{

	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END

}

//----------------------------------------------------------------//
MOAIMathUtil::~MOAIMathUtil () {

}

//----------------------------------------------------------------//
void MOAIMathUtil::RegisterLuaClass ( MOAILuaState& state ) {
}

//----------------------------------------------------------------//
void MOAIMathUtil::RegisterLuaFuncs ( MOAILuaState& state ) {

	// here are the instance methods:
	luaL_Reg regTable [] = {

		{ "rotate_point",			_rotate_point },
		{ "rotate_check",			_rotate_check },


		{ "getAngle2D",			_getAngle2D },
		{ "moveTo2D",			_moveTo2D },

		{ "doRectsCollide",		_doRectsCollide },
		{ "doCirclesCollide",	_doCirclesCollide },

		{ "point_in_polygon",	_point_in_polygon },	
		{ "point_in_rect",		_point_in_rect },	
		{ "point_in_circle",	_point_in_circle },

		{ "point_on_line",		_point_on_line },
		{ "point_on_rect",		_point_on_rect },


		{ "project_to",			_project_to },
		
		{ "getSmallAngle2D",	_getSmallAngle2D },	


		{ "rect_vs_rect_is",		_rect_vs_rect_is },
		{ "line_vs_line_is",		_line_vs_line_is },
		

		{ "line_vs_line",		_line_vs_line },
		{ "line_vs_circle",		_line_vs_circle },
		{ "line_vs_rect",		_line_vs_rect },



		{ "inFrontLine",		_inFrontLine },
		{ "inFrontTriangle",	_inFrontTriangle },

		{ "getDistance2D",		_getDistance2D },
		{ "getDistance3D",		_getDistance3D },


		{ "setRotOff",		 _setRotOff },
		{ "setMap",			 _setMap },

		{ "raycast",		 _raycast },
		{ "rayTest",		 _rayTest },
		
		{"mid_point",        _mid_point},     

		{ "indexToGrid",	_indexToGrid },


		{ "clip",		_clip},
		{ "clipLight",	_clipLight},
		{ "clipShadow",	_clipShadow},
		{ "clipExecute",_clipExecute},
		{ "AABB",	  _AABB },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

