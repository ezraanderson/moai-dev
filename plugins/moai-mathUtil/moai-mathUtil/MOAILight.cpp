#include "pch.h"
#include <moai-mathUtil/MOAILight.h>
#include <moai-sim/MOAIDraw.h>


int scale_factor= 1;

//***********************************************************************************************
//SUB CLASS
class angle_sort
{
	IntPoint m_origin;
	IntPoint m_dreference;
	static cInt xp(IntPoint a, IntPoint b)  { return a.X * b.Y - a.Y * b.X; }
	// const static IntPoint subP(IntPoint a, IntPoint b)  { return IntPoint(a.X-b.X,a.Y-b.Y);}
public:
	angle_sort(const IntPoint origin, const IntPoint reference) : m_origin(origin), m_dreference(reference.X -origin.X, reference.Y -origin.Y )  {}
	bool operator()(const IntPoint a, const IntPoint b) const
	{

		const IntPoint da (a.X -m_origin.X, a.Y -m_origin.Y );
		const IntPoint db (b.X -m_origin.X, b.Y -m_origin.Y );

		const cInt detb = xp(m_dreference, db);

		// nothing is less than zero degrees
		//  if (detb == 0 && db.X * m_dreference.X + db.Y * m_dreference.Y >= 0) return false;

		const cInt deta = xp(m_dreference, da);
			//if (deta == 0 && da.X * m_dreference.X + da.Y * m_dreference.Y >= 0) return true;


		if (deta * detb >= 0) {
			// both on same side of reference, compare to each other
			return xp(da, db) > 0;
		}
		// vectors "less than" zero degrees are actually large, near 2 pi
		return deta > 0;
	}
};



//***********************************************************************************************
float MOAILight::DotProduct2(mPoint v1, mPoint v2) {
//	printf(" %f \n",ceilf(v1._mag*v2._mag));
	float  c = ((v1._x*v2._x)+(v1._y*v2._y)) / ceilf(v1._mag*v2._mag);
	return c;
}


//********************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************
bool MOAILight::inFrontLine(float ax, float ay, float bx, float by, float px, float py){
     return ((bx - ax)*(py - ay) - (by - ay)*(px - ax)) > 0;
}

//********************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************
bool BQueryCallback::ReportFixture(b2Fixture* fixture) {
	mFoundFixture.push_back( fixture ); 
	return true;
};

//********************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************
int MOAILight::_setWorld ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILight, "U" )
	MOAIBox2DWorld* world = state.GetLuaObject < MOAIBox2DWorld >( 2, true );
	if (world) {
		self->mWorld		 = world->getWorld();
		self->mUnitsToMeters = world->getUnitsToMeters();
		self->mQueryList	 = new BQueryCallback();
	};
	return 0;
};

//********************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************
int MOAILight::_debug ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILight, "U" )	
	self->mDebug =state.GetValue   < bool >( 2, false );
	return 0;
};
//********************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************
int MOAILight::_setOffset ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILight, "U" )	
	self->mOffX =state.GetValue   < float >( 2, 0.0f );
	self->mOffY =state.GetValue   < float >( 3, 0.0f );

	return 0;
};
//********************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************
int MOAILight::_scale ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILight, "U" )	
	self->mScale =state.GetValue   < float >( 2, 1.0f );
	return 0;
};



//********************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************
void MOAILight::clipLight () {
	Paths  light(1);

	mClipper.Clear();
	for( size_t i = 0; i < points_inner.size(); i++){	
		mPoint point = points_inner[i];
		light[0] << IntPoint(point._x*scale_factor,point._y*scale_factor);
	}
	mClipper.AddPaths(light, ptSubject, true); //THIS COPIES THE ARRAY

}

//********************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************
void MOAILight::clipShadowAll (float light_x,float light_y) {

Paths  inner(1),shadow(1);

float	sum_x = 0;
float	sum_y = 0;
int		sCnt  = 0;
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();

//DRAW A LINE TO CENTER OF THE POLYGON
//IS ANGLE LESS THAN OR GREATHER THAN THIS ANGLE, ADJUST +-0.001



	//READ IN INNER
	for( size_t i = 0; i < points_inner.size(); i++){	
		++sCnt;
		mPoint point = points_inner[i];
		inner[0] << IntPoint(point._x*scale_factor,point._y*scale_factor);
		sum_x = sum_x + point._x;
		sum_y = sum_y + point._y;
	};


	//if ((sCnt == 0) || (sum_x == 0) || (sum_y ==0))  {
	if ((sCnt == 0))   {
	} else {
		sum_x = sum_x / sCnt;
		sum_y = sum_y / sCnt;
	};



	if (this->mDebug == true) { 
		MOAIDraw::DrawEllipseFill(sum_x,sum_y,2,2,36);
	};


	//CALCULATE SUM OF INNER
	float distance    = 500000;
	int   cnt		  = 0;


	float  angler = atan2f(  ((light_y/scale_factor)-sum_y) , ((light_x/scale_factor)-sum_x) );
	float  lxf	  =sum_x-1000000 * (cosf(angler));
	float  lyf	  =sum_y-1000000 * (sinf(angler));


	float  lxb	  =sum_x+1000000 * (cosf(angler));
	float  lyb	  =sum_y+1000000 * (sinf(angler));

	//gfxDevice.SetPenColor(1,0,1,1);
	//MOAIDraw::DrawLine(lxf,lyf,0,lxb,lyb,0);

	//gfxDevice.SetPenColor(1,0,0,1);	
	//MOAIDraw::DrawEllipseFill(sum_x,sum_y,5,5,36); 



	for(auto j = inner[0].begin(); j != inner[0].end() ; ++j){			
		++cnt;
		cInt x = j->X;
		cInt y = j->Y;

		//printf("x: %d y: %d \n",j->X,j->Y);
		//printf("lx: %f ly: %f \n",light_x,light_y);



				float  anglep = atan2f(  ( y-(light_y)) , ( x-light_x) );

				float  tpx	  =x+distance * (cosf(anglep));
				float  tpy	  =y+distance * (sinf(anglep));

				//gfxDevice.SetPenColor(0,1,0,1);
				//MOAIDraw::DrawEllipseFill(tpx/scale_factor,tpy/scale_factor,2,2,8); 
				

				if (inFrontLine(lxf,lyf,lxb,lyb,x,y) == true) {
					//anglep = anglep +0.2;
				} else {
					//anglep = anglep -0.2; 
				};

			
				float  px	  =x+distance * (cosf(anglep));
				float  py	  =y+distance * (sinf(anglep));



				////IF CORRNER PIEACE ??
				//float dx =  x-px;
				//float dy =  y-py;				

				//float nx = sum_x - x;
				//float ny = sum_y - y;

				////float d  = sqrt(dx*dx + dy*dy); 
				////float nx = (dx)/d; 
				////float ny = (dy)/d;

				//mPoint tv = mPoint(-dy,dx);
				//mPoint nv = mPoint(nx, ny);

				//double  angler2 = atan2f(  (tv._y- nv._y) , (tv._x-nv._x) );
		  //      float dp = DotProduct2(tv,nv);						
				//if(dp >= 0) { 
				//	//printf("SWAP\n");
				//	angler2 = angler2 + M_PI;
				//};		

				//double  bx	  =px+25000 * (cosf(angler2));
				//double  by	  =py+25000 * (sinf(angler2));

				//if (inFrontLine(px,py,light_x,light_y,bx,by)) {
				//		printf("SWAP\n");
				//	//bx = bx * -1;
				//	by = by *-1;
				//}
				//MOAIDraw::DrawLine(x,y,0,bx,by,0);
				//MOAIDraw::DrawLine(x,y,0,light_x,light_y,0);


		if (this->mDebug == true) { 
			//MOAIDraw::DrawEllipseOutline(x2,y2,12*(cnt+1),12*(cnt+1),16);
			gfxDevice.SetPenColor(1,0,0,1);
			MOAIDraw::DrawLine(x/scale_factor,y/scale_factor,0,px/scale_factor,py/scale_factor,0);	

		   //MOAIDraw::DrawLine(x/scale_factor,y/scale_factor,0,px/scale_factor,py/scale_factor,0);	
			gfxDevice.SetPenColor(1,1,1,1);
			MOAIDraw::DrawLine(tpx/scale_factor,tpy/scale_factor,0,px/scale_factor,py/scale_factor,0);	
			MOAIDraw::DrawEllipseFill(x/scale_factor,y/scale_factor,2,2,8); 
			MOAIDraw::DrawEllipseFill(px/scale_factor,py/scale_factor,2,2,8); 
			//MOAIDraw::DrawEllipseFill(bx,by,2,2,8); 

			//MOAIDraw::DrawEllipseOutline(dx2,dy2,12,12,36);
		};


		//shadow[0] << IntPoint(bx,by);
		shadow[0] << IntPoint(x,y);
		shadow[0] << IntPoint(tpx,tpy);
	

	};


	//*****************************************************************
	//SORT : COSTLY
	sum_x = 0;
	sum_y = 0;
	sCnt  = 0;
	for(auto j = shadow[0].begin(); j != shadow[0].end() ; ++j){	
		sum_x = sum_x+j->X;
		sum_y = sum_y+j->Y;	
		++sCnt;
	};
	if ((sCnt == 0) || (sum_x == 0) || (sum_y ==0))  {
	//	printf("CRASH \n");
	} else {
		sum_x = sum_x / sCnt;
		sum_y = sum_y / sCnt;
	}

	//SORT INNER POINTS
	IntPoint centroid = IntPoint(sum_x,sum_y);
	IntPoint light    = IntPoint(light_x,light_y);

	std::sort (shadow[0].begin(), shadow[0].end(), angle_sort(centroid,light));	


////*********************************************************
////EXPAND WITH CLIPPOFFSET
 //ClipperOffset co;
 //co.AddPath(shadow[0], jtRound, etClosedPolygon);
 //co.Execute(shadow, 1);
	
	//********************************************************************
	mClipper.AddPaths(shadow, ptClip, true);//THIS COPIES THE ARRAY



};






//********************************************************************************************************************
//********************************************************************************************************************
//********************************************************************************************************************
void MOAILight::clipShadowInside (float light_x,float light_y) {

	Paths  inner(1),shadow(1);

	//READ IN INNER
	for( size_t i = 0; i < points_inner.size(); i++){	
		mPoint point = points_inner[i];
		inner[0] << IntPoint(point._x,point._y);
	};



	//*****************************************************************
	//SORT : COSTLY
	cInt sum_x = 0;
	cInt sum_y = 0;
	int sCnt  = 0;
	for(auto j = inner[0].begin(); j != inner[0].end() ; ++j){	
		sum_x = sum_x+j->X;
		sum_y = sum_y+j->Y;	
		++sCnt;
	};
	if ((sCnt == 0) || (sum_x == 0) || (sum_y ==0))  {
		//printf("CRASH \n");
	} else {
		sum_x = sum_x / sCnt;
		sum_y = sum_y / sCnt;
	}

	//SORT INNER POINTS
	IntPoint centroid = IntPoint(sum_x,sum_y);
	IntPoint light    = IntPoint(light_x,light_y);

	std::sort (inner[0].begin(), inner[0].end(), angle_sort(centroid,light));	
	//std::sort (inner[0].begin(), inner[0].end(), angle_sort(light,centroid));


	//ADD TO SHADOW
	for(auto j = inner[0].begin(); j != inner[0].end() ; ++j){
		shadow[0] << IntPoint(j->X,j->Y);
	};

	//LOOP BACKWARDS AND PROJECT 
	float distance    = 600;
	float x1		  = light_x;
	float y1		  = light_y;
	int  cnt = 0;
	for(auto j = inner[0].rbegin(); j != inner[0].rend() ; ++j){			
		++cnt;
		cInt x2 = j->X;
		cInt y2 = j->Y;

		double angler = atan2f(  (y2 - y1) , (x2 - x1) );

		//NEED TO EXPAND THE CORNERS POINTS TO PRVENT THE TRANGLE STRIP TO USE THE SAME LINE to stop artifacts
		if (cnt == 1 ) {
			angler = angler +0.1; 
		}

		if (cnt == (inner[0].size()) ) {	
			angler = angler -0.1; 
		};	


		float  dx =x1+distance * (cosf((float)angler));
		float  dy =y1+distance * (sinf((float)angler));

		if (this->mDebug == true) { 
			MOAIDraw::DrawLine(dx,dy,0,x2,y2,0); 
		};

		shadow[0] << IntPoint(dx,dy);

	};

	//********************************************************************
	mClipper.AddPaths(shadow, ptClip, true);//THIS COPIES THE ARRAY

};




//*******************************************************************************
//*******************************************************************************


int MOAILight::_draw ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILight, "U" )	

	double start_time	 = ZLDeviceTime::GetTimeInSeconds();
	float mUnitsToMeters = (self->mUnitsToMeters);
	float scale          = (self->mScale); 

	std::vector<mPoint> points_draw;

	//GFX
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	
	//TYPE
	int idType = state.GetValue   < int >(2, 0 )*scale;

	//TEXTURE
	MOAITexture* texture = (MOAITexture*)MOAITexture::AffirmTexture ( state, 3 );

	//SIZE
	float light_x=state.GetValue   < float >( 4, 0 )*scale;
	float light_y=state.GetValue   < float >( 5, 0 )*scale;
	float light_r=state.GetValue   < float >( 6, 0 )*scale;	//DISTANCE FROM CENTER

	//COLOR
	float r=state.GetValue   < float >( 7, 0 );
	float g=state.GetValue   < float >( 8, 0 );
	float b=state.GetValue   < float >( 9, 0 );	
	float a=state.GetValue   < float >( 10, 0 );	//ALPHA NOT NEEDED

   //ROTAION
	float rot  =state.GetValue  < float >(  11, 0 );	//ALPHA NOT NEEDED
	float fa =state.GetValue  < float >(  12, 0 );	//ALPHA NOT NEEDED

	//CLEAR
	points_draw.clear();


//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************

	if (idType == mCircle) {
		//printf("CIRCLE\n");
			points_draw.push_back(mPoint( light_x-light_r,light_y-light_r)); //TOP	LEFT
			points_draw.push_back(mPoint( light_x+light_r,light_y-light_r)); //TOP	RIGHT
			points_draw.push_back(mPoint( light_x+light_r,light_y+light_r)); //BOTTOM RIGHT
			points_draw.push_back(mPoint( light_x-light_r,light_y+light_r)); //BOTTOM LEFT

	};


//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************

if (idType == mTriangle) {


//CENTER
float center_x =light_x;
float center_y =light_y;

points_draw.push_back(mPoint( center_x,center_y)); //CENTER


double fan     = (double) (fa)  / 180.0 * M_PI;
double fan45   = (double) (45)  / 180.0 * M_PI;
double fan90   = (double) (90)  / 180.0 * M_PI;
double fan180  = (double) (180) / 180.0 * M_PI;



float  width = light_r;

float  px=0;
float  py=0;


//**********************************************************************************************
//**********************************************************************************************
//90
px=center_x+(15) * (cosf(-fan90));
py=center_y+(15) * (sinf(-fan90));
points_draw.push_back(mPoint( px,py)); //BOTTOM LEFT



//*******************************************************
//OUT SIDE

//START
px=center_x+(width) * (cosf(-fan));
py=center_y+(width) * (sinf(-fan));
points_draw.push_back(mPoint( px,py)); 

//p
px=center_x+(width+20) * (cosf(-fan+(fan*.20)));
py=center_y+(width+20) * (sinf(-fan+(fan*.20)));
points_draw.push_back(mPoint( px,py)); 

//p
px=center_x+(width+30) * (cosf(-fan+(fan*.50)));
py=center_y+(width+30) * (sinf(-fan+(fan*.50)));
points_draw.push_back(mPoint( px,py)); 

	
//center
px=center_x+(width+40) * (cosf(-fan+(fan*.80)));
py=center_y+(width+40) * (sinf(-fan+(fan*.80)));
points_draw.push_back(mPoint( px,py)); //CENTER



//center
px=center_x+(width+40) * (cosf(fan-(fan*.80)));
py=center_y+(width+40) * (sinf(fan-(fan*.80)));
points_draw.push_back(mPoint( px,py)); //CENTER

//p
px=center_x+(width+30) * (cosf(fan-(fan*.50)));
py=center_y+(width+30) * (sinf(fan-(fan*.50)));
points_draw.push_back(mPoint( px,py)); 

//p
px=center_x+(width+20) * (cosf(fan-(fan*.20)));
py=center_y+(width+20) * (sinf(fan-(fan*.20)));
points_draw.push_back(mPoint( px,py)); 		

//END
px=center_x+(width) * (cosf(fan));
py=center_y+(width) * (sinf(fan));
points_draw.push_back(mPoint( px,py)); //BOTTOM LEFT


//*********************************************************************
//90
px=center_x+(15) * (cosf(fan90));
py=center_y+(15) * (sinf(fan90));
points_draw.push_back(mPoint( px,py)); //BOTTOM LEFT


//*********************************************************************
//BACK FAN
px=center_x+(15) * (cosf(fan180-(fan45)));
py=center_y+(15) * (sinf(fan180-(fan45)));
points_draw.push_back(mPoint( px,py)); //BOTTOM LEFT

//gfxDevice.SetPenColor(1,0,0,1);	
//MOAIDraw::DrawEllipseFill(px,py,2,2,36);


px=center_x+(15) * (cosf(fan180-(fan45*.5)));
py=center_y+(15) * (sinf(fan180-(fan45*.5)));
points_draw.push_back(mPoint( px,py)); //BOTTOM LEFT

//gfxDevice.SetPenColor(0,1,0,1);	
//MOAIDraw::DrawEllipseFill(px,py,2,2,36);


px=center_x+(15) * (cosf(fan180+(fan45*.5)));
py=center_y+(15) * (sinf(fan180+(fan45*.5)));
points_draw.push_back(mPoint( px,py)); //BOTTOM LEFT

//gfxDevice.SetPenColor(0,1,0,1);	
//MOAIDraw::DrawEllipseFill(px,py,2,2,36);


px=center_x+(15) * (cosf(fan180+(fan45)));
py=center_y+(15) * (sinf(fan180+(fan45)));
points_draw.push_back(mPoint( px,py)); //BOTTOM LEFT
	



//*********************************************************************
//STARTING
px=center_x+(15) * (cosf(-fan90));
py=center_y+(15) * (sinf(-fan90));
points_draw.push_back(mPoint( px,py)); //BOTTOM LEFT







			//USE LIGHT_X & LIGHT_Y AS THE CENTER
			double rotation_angle = (double) (rot*-1) / 180.0 * M_PI;
			double s = sin(rotation_angle);
			double c = cos(rotation_angle);

			for( size_t i = 0; i < points_draw.size(); i++){	

					double x = points_draw[i]._x;
					double y = points_draw[i]._y;

					x = x- center_x;
					y = y- center_y;

						//float xnew = x * c -y * s;
						//float ynew = x * s + y * c;

					double xnew = x * c +y * s;
					double ynew = -x * s +y * c;

					x =  xnew + center_x;
					y =  ynew + center_y;

					points_draw[i]._x =  (float)x;
					points_draw[i]._y =  (float)y;
			};


	}; //END TRIANGL











//********************************************************************************************
//********************************************************************************************
//********************************************************************************************
//********************************************************************************************
	Paths  light(1);
	self->mClipper.Clear();
	for( size_t i = 0; i < points_draw.size(); i++){	
		mPoint point = points_draw[i];
		light[0] << IntPoint(point._x*scale_factor,point._y*scale_factor);
	}
	self->mClipper.AddPaths(light, ptSubject, true); //THIS COPIES THE ARRAY




if (!light[0].empty()) {
 ClipperOffset co;
 co.AddPath(light[0], jtRound, etClosedPolygon);
 //co.Execute(output, 3);
  co.Execute(light, 2);
};
		









	//printf("--\n");

	if ( texture ) {	

		if (!points_draw.empty()) {

			//if (self->mDebug == true) { 
			//	for( size_t i = 0; i < points_draw.size()-1; i++){					
			//		gfxDevice.SetPenColor(1,0,0,1);	
			//		MOAIDraw::DrawLine(points_draw[0]._x,points_draw[0]._y,points_draw[i+1]._x,points_draw[i+1]._y);				
			//	};
			//};



			gfxDevice.BeginPrim ( ZGL_PRIM_TRIANGLE_FAN );
			gfxDevice.SetPenColor(r,g,b,1);

			float tsize		 = light_r*2;
			float thalf		 = light_r;
			float sub_left   = light_x-thalf;
			float sub_top    = light_y-thalf;

			//////CENTER
			gfxDevice.WriteVtx ( (light_x),(light_y) );	
			gfxDevice.WriteFinalColor4b ();	

			for( size_t i = 0; i < light[0].size(); i++){				
					gfxDevice.WriteVtx ( (light[0][i].X/scale_factor),(light[0][i].Y/scale_factor) );		
					gfxDevice.WriteFinalColor4b ();	
			};

			//START
			gfxDevice.WriteVtx ( ((light[0][0].X/scale_factor)),(light[0][0].Y/scale_factor) );		
			gfxDevice.WriteFinalColor4b ();

			gfxDevice.EndPrim ();


		};//SIZE
	};//TEXTURE	
	
















}




//*******************************************************************************
//*******************************************************************************
//*******************************************************************************

int MOAILight::_query ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILight, "U" )	

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();

    double start_time	 = ZLDeviceTime::GetTimeInSeconds();
	float mUnitsToMeters = (self->mUnitsToMeters);
	float scale          = (self->mScale); 

	
	//TYPE
	int idType = state.GetValue   < int >(2, 0 )*scale;

	//TEXTURE
	MOAITexture* texture = (MOAITexture*)MOAITexture::AffirmTexture ( state, 3 );

	//SIZE
	float light_x=state.GetValue   < float >( 4, 0 )*scale;
	float light_y=state.GetValue   < float >( 5, 0 )*scale;
	float light_r=state.GetValue   < float >( 6, 0 )*scale;	//DISTANCE FROM CENTER

	//COLOR
	float r=state.GetValue   < float >( 7, 0 );
	float g=state.GetValue   < float >( 8, 0 );
	float b=state.GetValue   < float >( 9, 0 );	
	float a=state.GetValue   < float >( 10, 0 );	//ALPHA NOT NEEDED

   //ROTAION
	float rot  =state.GetValue  < float >(  11, 0 );	//ALPHA NOT NEEDED
	float fa=state.GetValue  < float >(  12, 0 );	//ALPHA NOT NEEDED

	//CLEAR
	self->points_inner.clear();

//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************

	if (idType == mCircle) {
		//printf("CIRCLE\n");
			self->points_inner.push_back(mPoint( light_x-light_r,light_y-light_r)); //TOP	LEFT
			self->points_inner.push_back(mPoint( light_x+light_r,light_y-light_r)); //TOP	RIGHT
			self->points_inner.push_back(mPoint( light_x+light_r,light_y+light_r)); //BOTTOM RIGHT
			self->points_inner.push_back(mPoint( light_x-light_r,light_y+light_r)); //BOTTOM LEFT

	};


//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************

	if (idType == mTriangle) {
	//
	//self->points_inner.push_back(mPoint( light_x,light_y)); //CENTER


	//	double fan   = (double) (fa) / 180.0 * M_PI;
	//	float  width = light_r*2;

	//		float  left_x	      =light_x+(width) * (cosf(-fan));
	//		float  left_y	      =light_y+(width) * (sinf(-fan));
	//		self->points_inner.push_back(mPoint( left_x,left_y)); //BOTTOM LEFT


	//		float  right_x	      =light_x+(width) * (cosf(fan));
	//		float  right_y	      =light_y+(width) * (sinf(fan));
	//		self->points_inner.push_back(mPoint( right_x,right_y)); //BOTTOM LEFT

	//
	//		//USE LIGHT_X & LIGHT_Y AS THE CENTER

	//		double rotation_angle = (double) (rot*-1) / 180.0 * M_PI;
	//		double s = sin(rotation_angle);
	//		double c = cos(rotation_angle);

	//		for( size_t i = 0; i < self->points_inner.size(); i++){	

	//				double x = self->points_inner[i]._x;
	//				double y = self->points_inner[i]._y;

	//				x = x- light_x;
	//				y = y- light_y;

	//					//float xnew = x * c -y * s;
	//					//float ynew = x * s + y * c;

	//				double xnew = x * c +y * s;
	//				double ynew = -x * s +y * c;

	//				x =  xnew + light_x;
	//				y =  ynew + light_y;

	//				self->points_inner[i]._x =  (float)x;
	//				self->points_inner[i]._y =  (float)y;
	//		};














//CENTER
float center_x =light_x;
float center_y =light_y;

self->points_inner.push_back(mPoint( center_x,center_y)); //CENTER


double fan     = (double) (fa)  / 180.0 * M_PI;
double fan45   = (double) (45)  / 180.0 * M_PI;
double fan90   = (double) (90)  / 180.0 * M_PI;
double fan180  = (double) (180) / 180.0 * M_PI;



float  width = light_r;

float  px=0;
float  py=0;


//**********************************************************************************************
//**********************************************************************************************
//90
px=center_x+(15) * (cosf(-fan90));
py=center_y+(15) * (sinf(-fan90));
self->points_inner.push_back(mPoint( px,py)); //BOTTOM LEFT



//*******************************************************
//OUT SIDE

//START
px=center_x+(width) * (cosf(-fan));
py=center_y+(width) * (sinf(-fan));
self->points_inner.push_back(mPoint( px,py)); 

//p
px=center_x+(width+20) * (cosf(-fan+(fan*.20)));
py=center_y+(width+20) * (sinf(-fan+(fan*.20)));
self->points_inner.push_back(mPoint( px,py)); 

//p
px=center_x+(width+30) * (cosf(-fan+(fan*.50)));
py=center_y+(width+30) * (sinf(-fan+(fan*.50)));
self->points_inner.push_back(mPoint( px,py)); 

	
//center
px=center_x+(width+40) * (cosf(-fan+(fan*.80)));
py=center_y+(width+40) * (sinf(-fan+(fan*.80)));
self->points_inner.push_back(mPoint( px,py)); //CENTER



//center
px=center_x+(width+40) * (cosf(fan-(fan*.80)));
py=center_y+(width+40) * (sinf(fan-(fan*.80)));
self->points_inner.push_back(mPoint( px,py)); //CENTER

//p
px=center_x+(width+30) * (cosf(fan-(fan*.50)));
py=center_y+(width+30) * (sinf(fan-(fan*.50)));
self->points_inner.push_back(mPoint( px,py)); 

//p
px=center_x+(width+20) * (cosf(fan-(fan*.20)));
py=center_y+(width+20) * (sinf(fan-(fan*.20)));
self->points_inner.push_back(mPoint( px,py)); 		

//END
px=center_x+(width) * (cosf(fan));
py=center_y+(width) * (sinf(fan));
self->points_inner.push_back(mPoint( px,py)); //BOTTOM LEFT


//*********************************************************************
//90
px=center_x+(15) * (cosf(fan90));
py=center_y+(15) * (sinf(fan90));
self->points_inner.push_back(mPoint( px,py)); //BOTTOM LEFT


//*********************************************************************
//BACK FAN
px=center_x+(15) * (cosf(fan180-(fan45)));
py=center_y+(15) * (sinf(fan180-(fan45)));
self->points_inner.push_back(mPoint( px,py)); //BOTTOM LEFT

//gfxDevice.SetPenColor(1,0,0,1);	
//MOAIDraw::DrawEllipseFill(px,py,2,2,36);


px=center_x+(15) * (cosf(fan180-(fan45*.5)));
py=center_y+(15) * (sinf(fan180-(fan45*.5)));
self->points_inner.push_back(mPoint( px,py)); //BOTTOM LEFT

//gfxDevice.SetPenColor(0,1,0,1);	
//MOAIDraw::DrawEllipseFill(px,py,2,2,36);


px=center_x+(15) * (cosf(fan180+(fan45*.5)));
py=center_y+(15) * (sinf(fan180+(fan45*.5)));
self->points_inner.push_back(mPoint( px,py)); //BOTTOM LEFT

//gfxDevice.SetPenColor(0,1,0,1);	
//MOAIDraw::DrawEllipseFill(px,py,2,2,36);


px=center_x+(15) * (cosf(fan180+(fan45)));
py=center_y+(15) * (sinf(fan180+(fan45)));
self->points_inner.push_back(mPoint( px,py)); //BOTTOM LEFT
	



//*********************************************************************
//STARTING
px=center_x+(15) * (cosf(-fan90));
py=center_y+(15) * (sinf(-fan90));
self->points_inner.push_back(mPoint( px,py)); //BOTTOM LEFT







			//USE LIGHT_X & LIGHT_Y AS THE CENTER
			double rotation_angle = (double) (rot*-1) / 180.0 * M_PI;
			double s = sin(rotation_angle);
			double c = cos(rotation_angle);

			for( size_t i = 0; i < self->points_inner.size(); i++){	

					double x = self->points_inner[i]._x;
					double y = self->points_inner[i]._y;

					x = x- center_x;
					y = y- center_y;

						//float xnew = x * c -y * s;
						//float ynew = x * s + y * c;

					double xnew = x * c +y * s;
					double ynew = -x * s +y * c;

					x =  xnew + center_x;
					y =  ynew + center_y;

					self->points_inner[i]._x =  (float)x;
					self->points_inner[i]._y =  (float)y;
			};



























	}; //END TRIANGL





//***************************************************************************************
	//Paths redraw(1);
	//for( size_t i = 0; i < self->points_inner.size(); i++){	
	//	mPoint point = self->points_inner[i];
	//	redraw[0] << IntPoint(point._x,point._y);
	//}



 //ClipperOffset co;
 //co.AddPath(redraw[0], jtRound, etClosedPolygon);
 //co.Execute(redraw, 10);



	//	    gfxDevice.SetShaderPreset ( MOAIShaderMgr::DECK2D_SHADER );	//SHADER		
	//		gfxDevice.SetTexture ( texture );							//TEXTURE	
	//		gfxDevice.SetVertexPreset ( MOAIVertexFormatMgr::XYZWUVC ); //VERTEX_FORMATE
	//	
	//		//gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ONE, ZGL_BLEND_FACTOR_ONE );		
	//		//gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ZERO, ZGL_BLEND_FACTOR_ZERO );
	//		//gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_SRC_ALPHA, ZGL_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA );

	//		gfxDevice.BeginPrim ( ZGL_PRIM_TRIANGLE_FAN );
	//		gfxDevice.SetPenColor(1,1,1,1);

	//						//CALCULATE UV ??
	//						float tsize		 = light_r*2;
	//						float thalf		 = light_r;
	//						float sub_left   = light_x-thalf;
	//						float sub_top    = light_y-thalf;

	//						//////CENTER
	//						gfxDevice.WriteVtx ( (light_x),(light_y) );			
	//						gfxDevice.WriteUV((light_x-sub_left)/tsize,(light_y-sub_top)/tsize );	
	//						gfxDevice.WriteFinalColor4b ();	

	//						for( size_t j = 0; j < redraw[0].size(); j++){	
	//							//printf("WTF");
	//								int x = redraw[0][j].X;
	//								int y = redraw[0][j].Y;
	//								//	printf("WTF %d %d %d \n",j,x,y);
	//								gfxDevice.WriteVtx ( x,y );	
	//								gfxDevice.WriteUV(( x-sub_left)/tsize,(y -sub_top)/tsize);
	//								gfxDevice.WriteFinalColor4b ();	
	//						};

	//						//START
	//						int x = redraw[0][0].X;
	//						int y = redraw[0][0].Y;

	//						gfxDevice.WriteVtx ( x,y );			
	//						gfxDevice.WriteUV(( x-sub_left)/tsize,(y -sub_top)/tsize);	
	//						gfxDevice.WriteFinalColor4b ();



	//		gfxDevice.EndPrim ();













//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//LIGHT




	//******************************************************************************
	//WRITE LIGHT IN
	//self->points_inner.clear();

	////self->points_inner.push_back(mPoint( light_x-light_r,light_y-light_r)); //TOP	LEFT
	////self->points_inner.push_back(mPoint( light_x+light_r,light_y-light_r)); //TOP	RIGHT
	////self->points_inner.push_back(mPoint( light_x+light_r,light_y+light_r)); //BOTTOM RIGHT
	////self->points_inner.push_back(mPoint( light_x-light_r,light_y+light_r)); //BOTTOM LEFT



////TRIANGLE
//
//	//self->points_inner.push_back(mPoint( light_x-light_r,light_y-light_r)); //TOP	LEFT
//	self->points_inner.push_back(mPoint( light_x,light_y)); //CENTER
//	self->points_inner.push_back(mPoint( light_x+75,light_y+light_r)); //BOTTOM RIGHT
//	self->points_inner.push_back(mPoint( light_x-75,light_y+light_r)); //BOTTOM LEFT


//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//ROTATE




//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//READ THE LIGHT

self->clipLight(); //READS THE GLOBAL POINTS





//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//DRAW THE POLYGON
if (self->mDebug == true) { 
	gfxDevice.SetPenColor(0,1,0,1);
	MOAIDraw::DrawRectOutline(light_x-light_r,light_y-light_r,light_x+light_r,light_y+light_r);
	MOAIDraw::DrawEllipseOutline(light_x,light_y,2,2,32);
};


//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//DRAW AABB LIGHT DIRECTION



//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//QUERRY : MAKE AABB OFF THE NEW LIGHT DEMESION

//NO THIS IS WORLD

	BQueryCallback*   query = ( BQueryCallback*) self->mQueryList;
	query->mFoundFixture.clear();

	float blight_x= light_x* mUnitsToMeters;
	float blight_y= light_y* mUnitsToMeters;
	float blight_r =(light_r+32)* mUnitsToMeters;

	b2Vec2 lower( (blight_x-blight_r), (blight_y-blight_r) );
	b2Vec2 upper( (blight_x+blight_r), (blight_y+blight_r) );

	b2AABB aabb;
	aabb.lowerBound = lower;
	aabb.upperBound = upper;
	self->mWorld->QueryAABB( query, aabb );	



//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//WILL THIS FAIL ON GIANT BODYS ??
//ADD ALL FIXTURES TO POLY LISTS
//THIS MEANS 2 LOOPS
//printf("BEFORE \n");

	self->points_inner.clear();

	for( size_t i = 0; i < query->mFoundFixture.size(); i++){	

		b2Fixture* f = query->mFoundFixture[i];
		b2Shape::Type shapeType = f->GetType();


		float friction = f->GetFriction(); 

		//printf("%f \n",friction);

		if (friction != 1) {
		if (f->IsSensor() == false) {

		bool isShape = false;
		if ( shapeType == b2Shape::e_circle )
		{
			//printf("crash e_circle\n"); //SKIP
			//b2CircleShape* circleShape = (b2CircleShape*)f->GetShape();		
			//b2Vec2 va = circleShape->GetVertex(0);		
			//gfxDevice.SetPenColor(1,0,0,1);
			//MOAIDraw::DrawEllipseOutline(va.x/mUnitsToMeters,va.y/mUnitsToMeters,28,28,16);
		}
		else if ( shapeType == b2Shape::e_edge ) 
		{
			//printf("crash e_edge\n");//SKIP
		}
		else if ( shapeType == b2Shape::e_chain )		
		{			
			//printf("crash e_chain\n");//SKIP
		}
		else if ( shapeType == b2Shape::e_polygon )
		{


			isShape = true;
			b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();


			int  count = polygonShape->GetVertexCount();		 	

			int edge [256];
			for( int j = 0; j < 256; j++){
				edge[j] = -1;
			}

			//CLEAR_POINTS
			self->points_inner.clear();
			//CLEAR_POINTS
			self->edge_points.clear();
			//CLEAR EDGES
			self->edges.clear();


			int edge_last = 0;
			int edge_cur  = 0;
			for( int j = 0; j < count; j++){	
				edge_cur = 0;

				b2Vec2 va = polygonShape->GetVertex(j);	
				b2Vec2 vb;
				int jNext  = j+1;
				if (j == count-1) {				
					jNext = 0;
				};	
				vb = polygonShape->GetVertex(jNext);

				va.x = (va.x * scale);
				va.y = (va.y * scale);

				vb.x = (vb.x * scale);
				vb.y = (vb.y * scale);

				if (va.x == 0) va.x = va.x +(float)0.01;
				if (va.y == 0) va.y = va.y +(float)0.01;

				if (vb.x == 0) vb.x = vb.x +(float)0.01;
				if (vb.y == 0) vb.y = vb.y +(float)0.01;

				float dx = (va.x / mUnitsToMeters) - (vb.x / mUnitsToMeters);
				float dy = (va.y / mUnitsToMeters) - (vb.y / mUnitsToMeters);

				float nx = light_x - (va.x / mUnitsToMeters);
				float ny = light_y - (va.y / mUnitsToMeters);

				if (self->mDebug == true) { 
						gfxDevice.SetPenColor(1,0,0,1);
						MOAIDraw::DrawLine(va.x,va.y,vb.x,vb.y);
						gfxDevice.SetPenColor(1,1,1,1);
				};



				mPoint tv = mPoint(-dy,dx);
				mPoint nv = mPoint(nx, ny);

				float dp = self->DotProduct2(tv,nv);					
				if(dp <= 0) { 


						

							//edge_cur  = 0;
							////printf("%d %d BACK_0\n",j,edge[j]);				
							//if (edge[j] == -1) {
							//	edge[j]	  = 0;
							//	edge_cur = 0;
							//	self->points_inner.push_back(mPoint( va.x/mUnitsToMeters,va.y/mUnitsToMeters)); //INNER POINTS			

							//	if (self->mDebug == true) { 
							//		MOAIDraw::DrawEllipseOutline(va.x/mUnitsToMeters,va.y/mUnitsToMeters,8,8,16);
							//	};

							//}

							//if (edge[jNext] == -1) {
							//	edge[jNext] = 0;	
							//	edge_cur	= 0;
							//	self->points_inner.push_back(mPoint( vb.x/mUnitsToMeters,vb.y/mUnitsToMeters));
							//	if (self->mDebug == true) { 
							//		MOAIDraw::DrawEllipseOutline(vb.x/mUnitsToMeters,vb.y/mUnitsToMeters,8,8,16);
							//	};
							//};

				} else {	


			
					//*****************************************************************************************************
					//printf("%d FRONT_1\n",j);     

					edge_cur  = 1;

					if (edge[j] == -1) {
						edge[j]	  = 0;
						edge_cur  = 0;					

						self->points_inner.push_back(mPoint( (va.x/mUnitsToMeters),(va.y/mUnitsToMeters))); //INNER POINTS					
						if (self->mDebug == true) { 
							MOAIDraw::DrawEllipseOutline(va.x/mUnitsToMeters,va.y/mUnitsToMeters,8,8,16);
						};

					}

					if (edge[jNext] == -1) {
						edge[jNext] = 0;	
						edge_cur	= 0;

						self->points_inner.push_back(mPoint( vb.x/mUnitsToMeters,vb.y/mUnitsToMeters));			
						if (self->mDebug == true) { 
							MOAIDraw::DrawEllipseOutline(vb.x/mUnitsToMeters,vb.y/mUnitsToMeters,8,8,16);
						};
					};



			}; //END FACE
		};	//END VERTIC
	}; //END SHAPE



//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************

	//LOOP EDGES MY POINTS
	//if (self->edges.size() > 0) {
	//	    int edge_cnt = 0;
	//		int edge_stash [256];
	//		for( int j = 0; j < 256; j++){
	//			edge_stash[j] = -1;
	//		}


	//	//ADD FIRST TO END
	//		self->edges.push_back(self->edges[0]); 	
	//		int x = self->edge_points[0]._x;	
	//		int y = self->edge_points[0]._y;			
	//		self->edge_points.push_back(mPoint(x,y));

	//	int edge_last = self->edges[0];
	//	for( int j = 0; j < self->edges.size(); j++){	

	//		
	//		if (j == self->edges.size()-1) {
	//			edge_cnt = 0;
	//		};

	//		int edge_cur = self->edges[j];

	//		if ((edge_last != edge_cur) || (edge_cur == 1) && (edge_stash[edge_cnt] == -1) )  {
	//		//if (edge_cur == 1) {
	//			edge_stash[j] = 1;
	//			int x = self->edge_points[j]._x;
	//			int y = self->edge_points[j]._y;
	//			self->points_inner.push_back(mPoint( x,y));
	//			if (self->mDebug == true) {
	//				MOAIDraw::DrawEllipseOutline(x,y,8*(edge_cnt+1),8*(edge_cnt+1),16);
	//			}
	//			
	//		};
	//		edge_last = edge_cur;
	//		++edge_cnt;
	//	};
	//};

//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************

	
			//***********************************************************
			//SEND TO SHADOW
			if (isShape == true) {
				float lx = light_x*scale_factor;
				float ly =light_y*scale_factor;
	
				self->clipShadowAll (lx,ly);


				//self->clipShadowInside (light_x,light_y);
			}//IS CLIPP

	} //friction	
	}; //END IS SENSOR
};//END ALL FIXTURES







//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************




//*******************************************************************************************************************
//*******************************************************************************************************************
//*******************************************************************************************************************
//DIFFRENCE


	Paths  output(1);
	int cnt = 0;	
	//REMOVE ALL SHADOWS(CLIPPERS) FROM THE SUBJECT(LIGHT) WITH DIFFERENCE
	bool check = self->mClipper.Execute(ctDifference, output, pftNonZero, pftNonZero);
	self->mClipper.Clear();

	//if (check == true) {printf("crash\n");}




//*******************************************************************************************************************
//*******************************************************************************************************************
//*******************************************************************************************************************
//RESIZE
if (check == false) {printf("crash\n");}
//if (output[0]. == NULL) {printf("crash\n");};
if (!output[0].empty()) {
 ClipperOffset co;
 co.AddPath(output[0], jtRound, etClosedPolygon);
 co.Execute(output, 3*scale_factor);

};
		
//*******************************************************************************************************************
//*******************************************************************************************************************
//*******************************************************************************************************************
//DRAW


	//*********************************************************************
	//OUT PUT THE THE LIGHT BACK TO LUA
	if ( texture ) {	
		if (!output[0].empty()) {

			if (self->mDebug == true) { 
				for( size_t i = 0; i < output[0].size(); i++){						
					gfxDevice.SetPenColor(1,0,0,1);
					if (i == 0) gfxDevice.SetPenColor(1,1,0,1);
					MOAIDraw::DrawEllipseFill(output[0][i].X/scale_factor,output[0][i].Y/scale_factor,4,4,32);
				};
			};

			gfxDevice.SetShaderPreset ( MOAIShaderMgr::DISCARD_SHADER );	//SHADER		
			gfxDevice.SetTexture ( texture );							//TEXTURE	
			gfxDevice.SetVertexPreset ( MOAIVertexFormatMgr::XYZWUVC ); //VERTEX_FORMATE
		
			//gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ONE, ZGL_BLEND_FACTOR_ONE );		
			//gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ZERO, ZGL_BLEND_FACTOR_ZERO );
			//gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_SRC_ALPHA, ZGL_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA );

			gfxDevice.BeginPrim ( ZGL_PRIM_TRIANGLE_FAN );
			gfxDevice.SetPenColor(r,g,b,1);

			//CALCULATE UV ??
			float tsize		 = light_r*2;
			float thalf		 = light_r;
			float sub_left   = light_x-thalf;
			float sub_top    = light_y-thalf;

			//////CENTER
			gfxDevice.WriteVtx ( (light_x+self->mOffX),(light_y+self->mOffY) );			
			gfxDevice.WriteUV((light_x-sub_left)/tsize,(light_y-sub_top)/tsize );	
			gfxDevice.WriteFinalColor4b ();	



//NUDGE ALL POINTS FORWARD
	//float rr = 0.005;
	//for( size_t i = 0; i < output[0].size(); i++){	

	//		//double rotation_angle = (double) (rr*-1) / 180.0 * M_PI;
	//		rr = rr-  0.005;
	//		double s = sin(rr);
	//		double c = cos(rr);	

	//				double x = output[0][i].X;
	//				double y = output[0][i].Y;

	//				x = x- light_x;
	//				y = y- light_y;

	//					//float xnew = x * c -y * s;
	//					//float ynew = x * s + y * c;

	//				double xnew =  x * c +y * s;
	//				double ynew = -x * s +y * c;

	//				x =  xnew + light_x;
	//				y =  ynew + light_y;

	//				output[0][i].X =  (float)x;
	//				output[0][i].Y =  (float)y;
	//	


	//};






			//float cache_angle = 0;
			for( size_t i = 0; i < output[0].size(); i++){	
				//printf("%d %d \n",output[0][i].X,output[0][i].Y);


				//	float  anglep = atan2f(  ( output[0][i].Y-(light_y)) , ( output[0][i].X-light_x) );
					//printf("SHIT %d %f\n",i,anglep - cache_angle);
				//	if (anglep - cache_angle) {
				//		printf("SHIT %d\n",i);
				//	} else {
				//		printf("ELSE %f\n",ZLDeviceTime::GetTimeInSeconds());
				//	};

					gfxDevice.WriteVtx ( (output[0][i].X/scale_factor),(output[0][i].Y/scale_factor),0 );			
					gfxDevice.WriteUV(( (output[0][i].X/scale_factor)-sub_left)/tsize,((output[0][i].Y/scale_factor) -sub_top)/tsize);						
					gfxDevice.WriteFinalColor4b ();	

					//cache_angle = anglep;

			};

			//START
			gfxDevice.WriteVtx ( (output[0][0].X/scale_factor),(output[0][0].Y/scale_factor) );			
			gfxDevice.WriteUV(( (output[0][0].X/scale_factor)-sub_left)/tsize,((output[0][0].Y/scale_factor) -sub_top)/tsize);	
			gfxDevice.WriteFinalColor4b ();



			gfxDevice.EndPrim ();


		};//SIZE
	};//TEXTURE	
	
	
	
//****************************************************************
//printf("TIME: %f\n",ZLDeviceTime::GetTimeInSeconds()-start_time);
return 0;
};





//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//*******************************************************************************
//*******************************************************************************
//*******************************************************************************

int MOAILight::_queryOver ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILight, "U" )	

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();

    double start_time	 = ZLDeviceTime::GetTimeInSeconds();
	float mUnitsToMeters = (self->mUnitsToMeters);
	float scale          = (self->mScale); 

	
	//TYPE
	int idType = state.GetValue   < int >(2, 0 )*scale;

	//TEXTURE
	MOAITexture* texture = (MOAITexture*)MOAITexture::AffirmTexture ( state, 3 );

	//SIZE
	float light_x=state.GetValue   < float >( 4, 0 )*scale;
	float light_y=state.GetValue   < float >( 5, 0 )*scale;
	float light_r=state.GetValue   < float >( 6, 0 )*scale;	//DISTANCE FROM CENTER








	//COLOR
	float r=state.GetValue   < float >( 7, 0 );
	float g=state.GetValue   < float >( 8, 0 );
	float b=state.GetValue   < float >( 9, 0 );	
	float a=state.GetValue   < float >( 10, 0 );	//ALPHA NOT NEEDED

   //ROTAION
	float rot  =state.GetValue  < float >(  11, 0 );	//ALPHA NOT NEEDED
	float fa=state.GetValue  < float >(  12, 0 );	//ALPHA NOT NEEDED

	//CLEAR
	self->points_inner.clear();

//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************

	if (idType == mCircle) {
		//printf("CIRCLE\n");
			self->points_inner.push_back(mPoint( light_x-light_r,light_y-light_r)); //TOP	LEFT
			self->points_inner.push_back(mPoint( light_x+light_r,light_y-light_r)); //TOP	RIGHT
			self->points_inner.push_back(mPoint( light_x+light_r,light_y+light_r)); //BOTTOM RIGHT
			self->points_inner.push_back(mPoint( light_x-light_r,light_y+light_r)); //BOTTOM LEFT

	};


//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************

	if (idType == mTriangle) {
	//
	//self->points_inner.push_back(mPoint( light_x,light_y)); //CENTER


	//	double fan   = (double) (fa) / 180.0 * M_PI;
	//	float  width = light_r*2;

	//		float  left_x	      =light_x+(width) * (cosf(-fan));
	//		float  left_y	      =light_y+(width) * (sinf(-fan));
	//		self->points_inner.push_back(mPoint( left_x,left_y)); //BOTTOM LEFT


	//		float  right_x	      =light_x+(width) * (cosf(fan));
	//		float  right_y	      =light_y+(width) * (sinf(fan));
	//		self->points_inner.push_back(mPoint( right_x,right_y)); //BOTTOM LEFT

	//
	//		//USE LIGHT_X & LIGHT_Y AS THE CENTER

	//		double rotation_angle = (double) (rot*-1) / 180.0 * M_PI;
	//		double s = sin(rotation_angle);
	//		double c = cos(rotation_angle);

	//		for( size_t i = 0; i < self->points_inner.size(); i++){	

	//				double x = self->points_inner[i]._x;
	//				double y = self->points_inner[i]._y;

	//				x = x- light_x;
	//				y = y- light_y;

	//					//float xnew = x * c -y * s;
	//					//float ynew = x * s + y * c;

	//				double xnew = x * c +y * s;
	//				double ynew = -x * s +y * c;

	//				x =  xnew + light_x;
	//				y =  ynew + light_y;

	//				self->points_inner[i]._x =  (float)x;
	//				self->points_inner[i]._y =  (float)y;
	//		};














//CENTER
float center_x =light_x;
float center_y =light_y;

self->points_inner.push_back(mPoint( center_x,center_y)); //CENTER


double fan     = (double) (fa)  / 180.0 * M_PI;
double fan45   = (double) (45)  / 180.0 * M_PI;
double fan90   = (double) (90)  / 180.0 * M_PI;
double fan180  = (double) (180) / 180.0 * M_PI;



float  width = light_r;

float  px=0;
float  py=0;


//**********************************************************************************************
//**********************************************************************************************
//90
px=center_x+(15) * (cosf(-fan90));
py=center_y+(15) * (sinf(-fan90));
self->points_inner.push_back(mPoint( px,py)); //BOTTOM LEFT



//*******************************************************
//OUT SIDE

//START
px=center_x+(width) * (cosf(-fan));
py=center_y+(width) * (sinf(-fan));
self->points_inner.push_back(mPoint( px,py)); 

//p
px=center_x+(width+20) * (cosf(-fan+(fan*.20)));
py=center_y+(width+20) * (sinf(-fan+(fan*.20)));
self->points_inner.push_back(mPoint( px,py)); 

//p
px=center_x+(width+30) * (cosf(-fan+(fan*.50)));
py=center_y+(width+30) * (sinf(-fan+(fan*.50)));
self->points_inner.push_back(mPoint( px,py)); 

	
//center
px=center_x+(width+40) * (cosf(-fan+(fan*.80)));
py=center_y+(width+40) * (sinf(-fan+(fan*.80)));
self->points_inner.push_back(mPoint( px,py)); //CENTER



//center
px=center_x+(width+40) * (cosf(fan-(fan*.80)));
py=center_y+(width+40) * (sinf(fan-(fan*.80)));
self->points_inner.push_back(mPoint( px,py)); //CENTER

//p
px=center_x+(width+30) * (cosf(fan-(fan*.50)));
py=center_y+(width+30) * (sinf(fan-(fan*.50)));
self->points_inner.push_back(mPoint( px,py)); 

//p
px=center_x+(width+20) * (cosf(fan-(fan*.20)));
py=center_y+(width+20) * (sinf(fan-(fan*.20)));
self->points_inner.push_back(mPoint( px,py)); 		

//END
px=center_x+(width) * (cosf(fan));
py=center_y+(width) * (sinf(fan));
self->points_inner.push_back(mPoint( px,py)); //BOTTOM LEFT


//*********************************************************************
//90
px=center_x+(15) * (cosf(fan90));
py=center_y+(15) * (sinf(fan90));
self->points_inner.push_back(mPoint( px,py)); //BOTTOM LEFT


//*********************************************************************
//BACK FAN
px=center_x+(15) * (cosf(fan180-(fan45)));
py=center_y+(15) * (sinf(fan180-(fan45)));
self->points_inner.push_back(mPoint( px,py)); //BOTTOM LEFT

//gfxDevice.SetPenColor(1,0,0,1);	
//MOAIDraw::DrawEllipseFill(px,py,2,2,36);


px=center_x+(15) * (cosf(fan180-(fan45*.5)));
py=center_y+(15) * (sinf(fan180-(fan45*.5)));
self->points_inner.push_back(mPoint( px,py)); //BOTTOM LEFT

//gfxDevice.SetPenColor(0,1,0,1);	
//MOAIDraw::DrawEllipseFill(px,py,2,2,36);


px=center_x+(15) * (cosf(fan180+(fan45*.5)));
py=center_y+(15) * (sinf(fan180+(fan45*.5)));
self->points_inner.push_back(mPoint( px,py)); //BOTTOM LEFT

//gfxDevice.SetPenColor(0,1,0,1);	
//MOAIDraw::DrawEllipseFill(px,py,2,2,36);


px=center_x+(15) * (cosf(fan180+(fan45)));
py=center_y+(15) * (sinf(fan180+(fan45)));
self->points_inner.push_back(mPoint( px,py)); //BOTTOM LEFT
	



//*********************************************************************
//STARTING
px=center_x+(15) * (cosf(-fan90));
py=center_y+(15) * (sinf(-fan90));
self->points_inner.push_back(mPoint( px,py)); //BOTTOM LEFT







			//USE LIGHT_X & LIGHT_Y AS THE CENTER
			double rotation_angle = (double) (rot*-1) / 180.0 * M_PI;
			double s = sin(rotation_angle);
			double c = cos(rotation_angle);

			for( size_t i = 0; i < self->points_inner.size(); i++){	

					double x = self->points_inner[i]._x;
					double y = self->points_inner[i]._y;

					x = x- center_x;
					y = y- center_y;

						//float xnew = x * c -y * s;
						//float ynew = x * s + y * c;

					double xnew = x * c +y * s;
					double ynew = -x * s +y * c;

					x =  xnew + center_x;
					y =  ynew + center_y;

					self->points_inner[i]._x =  (float)x;
					self->points_inner[i]._y =  (float)y;
			};



























	}; //END TRIANGL





//***************************************************************************************
	//Paths redraw(1);
	//for( size_t i = 0; i < self->points_inner.size(); i++){	
	//	mPoint point = self->points_inner[i];
	//	redraw[0] << IntPoint(point._x,point._y);
	//}



 //ClipperOffset co;
 //co.AddPath(redraw[0], jtRound, etClosedPolygon);
 //co.Execute(redraw, 10);



	//	    gfxDevice.SetShaderPreset ( MOAIShaderMgr::DECK2D_SHADER );	//SHADER		
	//		gfxDevice.SetTexture ( texture );							//TEXTURE	
	//		gfxDevice.SetVertexPreset ( MOAIVertexFormatMgr::XYZWUVC ); //VERTEX_FORMATE
	//	
	//		//gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ONE, ZGL_BLEND_FACTOR_ONE );		
	//		//gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ZERO, ZGL_BLEND_FACTOR_ZERO );
	//		//gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_SRC_ALPHA, ZGL_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA );

	//		gfxDevice.BeginPrim ( ZGL_PRIM_TRIANGLE_FAN );
	//		gfxDevice.SetPenColor(1,1,1,1);

	//						//CALCULATE UV ??
	//						float tsize		 = light_r*2;
	//						float thalf		 = light_r;
	//						float sub_left   = light_x-thalf;
	//						float sub_top    = light_y-thalf;

	//						//////CENTER
	//						gfxDevice.WriteVtx ( (light_x),(light_y) );			
	//						gfxDevice.WriteUV((light_x-sub_left)/tsize,(light_y-sub_top)/tsize );	
	//						gfxDevice.WriteFinalColor4b ();	

	//						for( size_t j = 0; j < redraw[0].size(); j++){	
	//							//printf("WTF");
	//								int x = redraw[0][j].X;
	//								int y = redraw[0][j].Y;
	//								//	printf("WTF %d %d %d \n",j,x,y);
	//								gfxDevice.WriteVtx ( x,y );	
	//								gfxDevice.WriteUV(( x-sub_left)/tsize,(y -sub_top)/tsize);
	//								gfxDevice.WriteFinalColor4b ();	
	//						};

	//						//START
	//						int x = redraw[0][0].X;
	//						int y = redraw[0][0].Y;

	//						gfxDevice.WriteVtx ( x,y );			
	//						gfxDevice.WriteUV(( x-sub_left)/tsize,(y -sub_top)/tsize);	
	//						gfxDevice.WriteFinalColor4b ();



	//		gfxDevice.EndPrim ();













//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//LIGHT




	//******************************************************************************
	//WRITE LIGHT IN
	//self->points_inner.clear();

	////self->points_inner.push_back(mPoint( light_x-light_r,light_y-light_r)); //TOP	LEFT
	////self->points_inner.push_back(mPoint( light_x+light_r,light_y-light_r)); //TOP	RIGHT
	////self->points_inner.push_back(mPoint( light_x+light_r,light_y+light_r)); //BOTTOM RIGHT
	////self->points_inner.push_back(mPoint( light_x-light_r,light_y+light_r)); //BOTTOM LEFT



////TRIANGLE
//
//	//self->points_inner.push_back(mPoint( light_x-light_r,light_y-light_r)); //TOP	LEFT
//	self->points_inner.push_back(mPoint( light_x,light_y)); //CENTER
//	self->points_inner.push_back(mPoint( light_x+75,light_y+light_r)); //BOTTOM RIGHT
//	self->points_inner.push_back(mPoint( light_x-75,light_y+light_r)); //BOTTOM LEFT


//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//ROTATE




//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//READ THE LIGHT

self->clipLight(); //READS THE GLOBAL POINTS





//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//DRAW THE POLYGON
if (self->mDebug == true) { 
	gfxDevice.SetPenColor(0,1,0,1);
	MOAIDraw::DrawRectOutline(light_x-light_r,light_y-light_r,light_x+light_r,light_y+light_r);
	MOAIDraw::DrawEllipseOutline(light_x,light_y,2,2,32);
};


//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//DRAW AABB LIGHT DIRECTION



//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//QUERRY : MAKE AABB OFF THE NEW LIGHT DEMESION

//NO THIS IS WORLD

	BQueryCallback*   query = ( BQueryCallback*) self->mQueryList;
	query->mFoundFixture.clear();

	float blight_x= light_x* mUnitsToMeters;
	float blight_y= light_y* mUnitsToMeters;
	float blight_r =(light_r+32)* mUnitsToMeters;

	b2Vec2 lower( (blight_x-blight_r), (blight_y-blight_r) );
	b2Vec2 upper( (blight_x+blight_r), (blight_y+blight_r) );

	b2AABB aabb;
	aabb.lowerBound = lower;
	aabb.upperBound = upper;
	self->mWorld->QueryAABB( query, aabb );	



//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//WILL THIS FAIL ON GIANT BODYS ??
//ADD ALL FIXTURES TO POLY LISTS
//THIS MEANS 2 LOOPS
//printf("BEFORE \n");

	self->points_inner.clear();

	for( size_t i = 0; i < query->mFoundFixture.size(); i++){	

		b2Fixture* f = query->mFoundFixture[i];
		b2Shape::Type shapeType = f->GetType();


		float friction = f->GetFriction(); 

		//printf("%f \n",friction);

		if (friction == 1) {
	 if (f->IsSensor() == false) {

		bool isShape = false;
		if ( shapeType == b2Shape::e_circle )
		{
			//printf("crash e_circle\n"); //SKIP
			//b2CircleShape* circleShape = (b2CircleShape*)f->GetShape();		
			//b2Vec2 va = circleShape->GetVertex(0);		
			//gfxDevice.SetPenColor(1,0,0,1);
			//MOAIDraw::DrawEllipseOutline(va.x/mUnitsToMeters,va.y/mUnitsToMeters,28,28,16);
		}
		else if ( shapeType == b2Shape::e_edge ) 
		{
			//printf("crash e_edge\n");//SKIP
		}
		else if ( shapeType == b2Shape::e_chain )		
		{			
			//printf("crash e_chain\n");//SKIP
		}
		else if ( shapeType == b2Shape::e_polygon )
		{


			isShape = true;
			b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();


			int  count = polygonShape->GetVertexCount();		 	

			int edge [256];
			for( int j = 0; j < 256; j++){
				edge[j] = -1;
			}

			//CLEAR_POINTS
			self->points_inner.clear();
			//CLEAR_POINTS
			self->edge_points.clear();
			//CLEAR EDGES
			self->edges.clear();


			int edge_last = 0;
			int edge_cur  = 0;
			for( int j = 0; j < count; j++){	
				edge_cur = 0;

				b2Vec2 va = polygonShape->GetVertex(j);	
				b2Vec2 vb;
				int jNext  = j+1;
				if (j == count-1) {				
					jNext = 0;
				};	
				vb = polygonShape->GetVertex(jNext);

				va.x = (va.x * scale);
				va.y = (va.y * scale);

				vb.x = (vb.x * scale);
				vb.y = (vb.y * scale);

				if (va.x == 0) va.x = va.x +(float)0.01;
				if (va.y == 0) va.y = va.y +(float)0.01;

				if (vb.x == 0) vb.x = vb.x +(float)0.01;
				if (vb.y == 0) vb.y = vb.y +(float)0.01;

				float dx = (va.x / mUnitsToMeters) - (vb.x / mUnitsToMeters);
				float dy = (va.y / mUnitsToMeters) - (vb.y / mUnitsToMeters);

				float nx = light_x - (va.x / mUnitsToMeters);
				float ny = light_y - (va.y / mUnitsToMeters);

				if (self->mDebug == true) { 
						gfxDevice.SetPenColor(1,0,0,1);
						MOAIDraw::DrawLine(va.x,va.y,vb.x,vb.y);
						gfxDevice.SetPenColor(1,1,1,1);
				};



				mPoint tv = mPoint(-dy,dx);
				mPoint nv = mPoint(nx, ny);

				float dp = self->DotProduct2(tv,nv);					
				if(dp <= 0) { 


						

							//edge_cur  = 0;
							////printf("%d %d BACK_0\n",j,edge[j]);				
							//if (edge[j] == -1) {
							//	edge[j]	  = 0;
							//	edge_cur = 0;
							//	self->points_inner.push_back(mPoint( va.x/mUnitsToMeters,va.y/mUnitsToMeters)); //INNER POINTS			

							//	if (self->mDebug == true) { 
							//		MOAIDraw::DrawEllipseOutline(va.x/mUnitsToMeters,va.y/mUnitsToMeters,8,8,16);
							//	};

							//}

							//if (edge[jNext] == -1) {
							//	edge[jNext] = 0;	
							//	edge_cur	= 0;
							//	self->points_inner.push_back(mPoint( vb.x/mUnitsToMeters,vb.y/mUnitsToMeters));
							//	if (self->mDebug == true) { 
							//		MOAIDraw::DrawEllipseOutline(vb.x/mUnitsToMeters,vb.y/mUnitsToMeters,8,8,16);
							//	};
							//};

				} else {	


			
					//*****************************************************************************************************
					//printf("%d FRONT_1\n",j);     

					edge_cur  = 1;

					if (edge[j] == -1) {
						edge[j]	  = 0;
						edge_cur  = 0;					

						self->points_inner.push_back(mPoint( (va.x/mUnitsToMeters),(va.y/mUnitsToMeters))); //INNER POINTS					
						if (self->mDebug == true) { 
							MOAIDraw::DrawEllipseOutline(va.x/mUnitsToMeters,va.y/mUnitsToMeters,8,8,16);
						};

					}

					if (edge[jNext] == -1) {
						edge[jNext] = 0;	
						edge_cur	= 0;

						self->points_inner.push_back(mPoint( vb.x/mUnitsToMeters,vb.y/mUnitsToMeters));			
						if (self->mDebug == true) { 
							MOAIDraw::DrawEllipseOutline(vb.x/mUnitsToMeters,vb.y/mUnitsToMeters,8,8,16);
						};
					};



			}; //END FACE
		};	//END VERTIC
	}; //END SHAPE



//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************

	//LOOP EDGES MY POINTS
	//if (self->edges.size() > 0) {
	//	    int edge_cnt = 0;
	//		int edge_stash [256];
	//		for( int j = 0; j < 256; j++){
	//			edge_stash[j] = -1;
	//		}


	//	//ADD FIRST TO END
	//		self->edges.push_back(self->edges[0]); 	
	//		int x = self->edge_points[0]._x;	
	//		int y = self->edge_points[0]._y;			
	//		self->edge_points.push_back(mPoint(x,y));

	//	int edge_last = self->edges[0];
	//	for( int j = 0; j < self->edges.size(); j++){	

	//		
	//		if (j == self->edges.size()-1) {
	//			edge_cnt = 0;
	//		};

	//		int edge_cur = self->edges[j];

	//		if ((edge_last != edge_cur) || (edge_cur == 1) && (edge_stash[edge_cnt] == -1) )  {
	//		//if (edge_cur == 1) {
	//			edge_stash[j] = 1;
	//			int x = self->edge_points[j]._x;
	//			int y = self->edge_points[j]._y;
	//			self->points_inner.push_back(mPoint( x,y));
	//			if (self->mDebug == true) {
	//				MOAIDraw::DrawEllipseOutline(x,y,8*(edge_cnt+1),8*(edge_cnt+1),16);
	//			}
	//			
	//		};
	//		edge_last = edge_cur;
	//		++edge_cnt;
	//	};
	//};

//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************

	
			//***********************************************************
			//SEND TO SHADOW
			if (isShape == true) {
				float lx = light_x*scale_factor;
				float ly =light_y*scale_factor;
	
				self->clipShadowAll (lx,ly);


				//self->clipShadowInside (light_x,light_y);
			}//IS CLIPP

	} //friction	
	}; //END IS SENSOR
};//END ALL FIXTURES







//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************




//*******************************************************************************************************************
//*******************************************************************************************************************
//*******************************************************************************************************************
//DIFFRENCE


	Paths  output(1);
	int cnt = 0;	
	//REMOVE ALL SHADOWS(CLIPPERS) FROM THE SUBJECT(LIGHT) WITH DIFFERENCE
	bool check = self->mClipper.Execute(ctDifference, output, pftNonZero, pftNonZero);
	self->mClipper.Clear();

	//if (check == true) {printf("crash\n");}




//*******************************************************************************************************************
//*******************************************************************************************************************
//*******************************************************************************************************************
//RESIZE
if (check == false) {printf("crash\n");}
//if (output[0]. == NULL) {printf("crash\n");};
if (!output[0].empty()) {
 ClipperOffset co;
 co.AddPath(output[0], jtRound, etClosedPolygon);
 co.Execute(output, 3*scale_factor);

};
		
//*******************************************************************************************************************
//*******************************************************************************************************************
//*******************************************************************************************************************
//DRAW


	//*********************************************************************
	//OUT PUT THE THE LIGHT BACK TO LUA

		if (!output[0].empty()) {




			gfxDevice.SetShaderPreset ( MOAIShaderMgr::DISCARD_SHADER );	//SHADER		
			gfxDevice.SetTexture ( texture );							//TEXTURE	
			gfxDevice.SetVertexPreset ( MOAIVertexFormatMgr::XYZWUVC ); //VERTEX_FORMATE
		
			//gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ONE, ZGL_BLEND_FACTOR_ONE );		
			//gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ZERO, ZGL_BLEND_FACTOR_ZERO );
			//gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_SRC_ALPHA, ZGL_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA );

			gfxDevice.BeginPrim ( ZGL_PRIM_TRIANGLE_FAN );
			gfxDevice.SetPenColor(r,g,b,1);

			//CALCULATE UV ??
			float tsize		 = light_r*2;
			float thalf		 = light_r;
			float sub_left   = light_x-thalf;
			float sub_top    = light_y-thalf;

			//////CENTER
			gfxDevice.WriteVtx ( (light_x+self->mOffX),(light_y+self->mOffY) );			
			gfxDevice.WriteUV((light_x-sub_left)/tsize,(light_y-sub_top)/tsize );	
			gfxDevice.WriteFinalColor4b ();

			for( size_t i = 0; i < output[0].size(); i++){	

					gfxDevice.WriteVtx ( (output[0][i].X/scale_factor),(output[0][i].Y/scale_factor),0 );			
					gfxDevice.WriteUV(( (output[0][i].X/scale_factor)-sub_left)/tsize,((output[0][i].Y/scale_factor) -sub_top)/tsize);						
					gfxDevice.WriteFinalColor4b ();	
			

			};

			//START
			gfxDevice.WriteVtx ( (output[0][0].X/scale_factor),(output[0][0].Y/scale_factor) );			
			gfxDevice.WriteUV(( (output[0][0].X/scale_factor)-sub_left)/tsize,((output[0][0].Y/scale_factor) -sub_top)/tsize);	
			gfxDevice.WriteFinalColor4b ();


			gfxDevice.EndPrim ();


		};
	
	
	
//****************************************************************
//printf("TIME: %f\n",ZLDeviceTime::GetTimeInSeconds()-start_time);
return 0;
};






//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//TEST UNIION



int MOAILight::_shadowTest ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAILight, "U" )

int bodCnt = 10; //NUMBER OF FIXTURES FOUND
Paths  fixtures(bodCnt),output(1);

int x = 0;
int y = 0;
u32 counter = 0;



//*****************************************
	lua_pushnil ( L );
	x = 0;
	y = 0;
	counter = 0;
	lua_pushnil ( L );
    while ( lua_next ( L, 2 ) != 0 ) {
	++counter;
			if ( counter == 1 ) {	
				x = state.GetValue < int >( -1, 0);
			} else {
				y = state.GetValue < int >( -1, 0);			
				fixtures[0] << IntPoint(x,y);			
				counter = 0;		
			}				
			lua_pop ( L, 1 );
	};


//*****************************************
	lua_pushnil ( L );
	x = 0;
	y = 0;
	counter = 0;
	lua_pushnil ( L );
    while ( lua_next ( L, 3 ) != 0 ) {
	++counter;
			if ( counter == 1 ) {	
				x = state.GetValue < int >( -1, 0);
			} else {
				y = state.GetValue < int >( -1, 0);			
				fixtures[1] << IntPoint(x,y);			
				counter = 0;		
			}				
			lua_pop ( L, 1 );
	};


//*****************************************
self->mClipper.Clear();
self->mClipper.AddPaths(fixtures, ptSubject, true); //ADD EACH FIXTURES_ARRAY TO SUBJECT
self->mClipper.Execute(ctUnion, output, pftNonZero, pftNonZero); //MERAGE ALL POSIBLE FIXTURES


//CHECK ALL OUTPUTED POLYGONS
for( size_t i = 0; i < output.size(); i++){

	for( size_t j = 0; j < output[i].size()-1; j++){

		cInt x1 = output[i][j].X;
		cInt y1 = output[i][j].Y;

		cInt x2 = output[i][j+1].X;
		cInt y2 = output[i][j+1].Y;
		MOAIDraw::DrawLine(x1,y1,x2,y2);

		//DRAW LAST LINE
		if (j == output[0].size()-2){

			cInt x1 = output[i][j+1].X;
			cInt y1 = output[i][j+1].Y;

			cInt x2 = output[i][0].X;
			cInt y2 = output[i][0].Y;
			if (self->mDebug == true) {
				MOAIDraw::DrawLine(x1,y1,x2,y2);
			};

		};
};

};

//*******************************************************





	return 0;



}





//*******************************************************************************
int MOAILight::_AABB ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILight, "U" )

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




//----------------------------------------------------------------//
MOAILight::MOAILight () :
mQueryList			( 0 ),
mWorld				( 0 ),
mOffX				( 0 ),
mOffY				( 0 ),
mDebug				( false ),
mScale				( 1 ),
mUnitsToMeters	    ( 0 )
{




	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
		RTTI_END
}

//----------------------------------------------------------------//
MOAILight::~MOAILight () {

	if (this->mQueryList) {
		delete ( this->mQueryList );
	};
}

//----------------------------------------------------------------//
void MOAILight::RegisterLuaClass ( MOAILuaState& state ) {
	//luaL_Reg regTable [] = {
	//	{ NULL, NULL }
	//};

	//MOAILight::RegisterLuaClass ( state );
	


//	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAILight::RegisterLuaFuncs ( MOAILuaState& state ) {
	// here are the instance methods:
	luaL_Reg regTable [] = {
		{ "setWorld",	_setWorld },
		{ "query",	_query },
		{ "debug",	_debug },
		{ "scale",	_scale },
		{ "shadowTest",	_shadowTest },
		{ "setOffset",	_setOffset },
		{ "draw",	   _draw },
		{ "queryOver",	  _queryOver },
		{ "AABB",	  _AABB },
		
		{ NULL, NULL }
	};
	luaL_register ( state, 0, regTable );


	state.SetField ( -1, "TRIANGLE",			( u32 )mTriangle);
	state.SetField ( -1, "CIRCLE"  ,			( u32 )mCircle);


}

