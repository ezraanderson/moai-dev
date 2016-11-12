#ifndef MOAIMATHUTIL_H
#define MOAIMATHUTIL_H

#include <moai-core/MOAILua.h>
#include <moai-mathUtil/MOAIHit.h>




class MOAIMathUtil :
	public virtual MOAILuaObject {
private:

	int mRot;
	int mWidth;
	int mHeight;
	int mTile;
	//----------------------------------------------------------------//
	static int		_rotate_check		(lua_State* L);
	static int		_rotate_point		(lua_State* L);

	static int		_getDistance3D		(lua_State* L);


	static int		_getDistance2D		(lua_State* L);
	static int		_getAngle2D			(lua_State* L);
	static int		_moveTo2D			(lua_State* L);

	static int		_doRectsCollide		(lua_State* L);
	static int		_doCirclesCollide	(lua_State* L);

	static int		_line_vs_line		(lua_State* L);
	static int		_line_vs_circle		( lua_State* L );
	static int		_line_vs_rect		( lua_State* L );


	static int		_project_to			( lua_State* L );

	static int		_point_in_polygon	( lua_State* L );
	static int		_point_in_circle	( lua_State* L );
	static int		_point_in_rect		( lua_State* L );

	static int		_point_on_line		( lua_State* L );
	static int		_point_on_rect		( lua_State* L );	

	static int		_getSmallAngle2D	( lua_State* L );	

	static int		_inFrontLine		( lua_State* L );
	static int		_inFrontTriangle	( lua_State* L );

	static int		_setRotOff			( lua_State* L );
	static int		_setMap				( lua_State* L );

	static int		_raycast			( lua_State* L );
	static int		_rayTest			( lua_State* L );

	static int		_indexToGrid		( lua_State* L );

	static int		_mid_point			( lua_State* L );

	static int		_AABB			( lua_State* L );

	static int     _rect_vs_rect_is ( lua_State* L );
	static int     _line_vs_line_is ( lua_State* L );
	static int     _circle_vs_line_is ( lua_State* L );
	static int     _circle_vs_circle_is ( lua_State* L );
	static int     _line_vs_rect_is ( lua_State* L );

	static int     _testBench ( lua_State* L );
	static int     _distance2DLess ( lua_State* L );

	static int     _tiled_shift(lua_State* L);
//****************************************************
static int		_clip			( lua_State* L );


static int		_clipLight			( lua_State* L );
static int		_clipShadow			( lua_State* L );
static int		_clipExecute		( lua_State* L );







public:

	DECL_LUA_FACTORY ( MOAIMathUtil )

	//----------------------------------------------------------------//
					MOAIMathUtil				();
					~MOAIMathUtil			();

	static float 	getDistance3D			(float x1, float y1,float z1, float x2, float y2,float z2);

	static float 	getDistance2D			(float x1, float y1, float x2, float y2);
	static float 	getAngle2D				(float x1, float y1, float x2, float y2);
	static USVec2D 	moveTo2D				(float speed, float x1, float y1, float x2, float y2);

	static void  cirlce_vs_circle
	(
		float balls_i_x,float balls_i_y,float balls_i_vx,float balls_i_vy,float balls_i_r,
		float balls_j_x,float balls_j_y,float balls_j_vx,float balls_j_vy,float balls_j_r
	);


	static bool		doRectsCollide			(float ax1,float ay1,float ax2, float ay2, float bx1,  float by1, float bx2, float by2);
	static bool		doCirclesCollide		(float ax1,float ay1,float ar1, float bx1, float by1,  float br1);

	static ZLHit	line_vs_line			(float ax1,float ay1,float bx1,float by1,float ax2, float ay2,float bx2,float by2);
	static ZLHit	line_vs_circle			(float ax1,float ay1,float bx1,float by1,float cx,float cy,float radius);
	static ZLHit	line_vs_rect			(float ax1,float ay1,float bx1,float by1,float l, float t,float r,float b);

	void			RegisterLuaClass	( MOAILuaState& state );
	void			RegisterLuaFuncs	( MOAILuaState& state );
};




#endif



