#include "pch.h"
#include <moai-ezra/draw/EZDraw.h>
#include <moai-sim/MOAIGfxDevice.h>
#include <moai-sim/MOAIDraw.h>


int EZDraw::_setBounds ( lua_State* L ) {

	//MOAI_LUA_SETUP ( EZDraw, "UNN" );
	MOAILuaState state ( L );


	float width =  state.GetValue < float >( 2, 480.0f );	
	
	float height = state.GetValue < float >( 3, 320.0f );

	//480 = width;
	//320 = height;

	//printf("*********  %f %f \n",480,320);
		
	return 0;
};


///****************************************************************************************
///****************************************************************************************
int EZDraw::_drawBlack ( lua_State* L ) {

//MOAI_LUA_SETUP ( EZDraw, "UN" )
MOAILuaState state ( L );

float alpha = state.GetValue < float >( 1, 0.0f );
float width	= state.GetValue < float >( 2, 0.0f ); //SECOND PARAM
float height= state.GetValue < float >( 3, 0.0f ); //SECOND PARAM

	//printf("_drawBlack *********  %f %f %f  \n",alpha,width,height);


	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	gfxDevice.SetPrimType ( ZGL_PRIM_TRIANGLE_STRIP );

	gfxDevice.SetPenColor ( 0.0, 0.0,0.0f,alpha );
	gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ONE, ZGL_BLEND_FACTOR_ONE_MINUS_DST_ALPHA );		
	gfxDevice.BeginPrim ();

		gfxDevice.WriteVtx ( 0, 0, 0.0f );
		gfxDevice.WriteFinalColor4b ();

		gfxDevice.WriteVtx ( width, 0, 0.0f );
		gfxDevice.WriteFinalColor4b ();


		gfxDevice.WriteVtx ( 0, height, 0.0f );
		gfxDevice.WriteFinalColor4b ();

		gfxDevice.WriteVtx ( width, height, 0.0f );
		gfxDevice.WriteFinalColor4b ();

	gfxDevice.EndPrim ();



	return 0;
}

///****************************************************************************************
///****************************************************************************************
int EZDraw::_drawRoomsB ( lua_State* L ) {

	//MOAI_LUA_SETUP ( EZDraw, "UNT" )
	MOAILuaState state ( L );

	float mod			= state.GetValue < float >( 2, 0.0f ); //SECOND PARAM
	float width			= state.GetValue < float >( 3, 0.0f ); //SECOND PARAM
	float height		= state.GetValue < float >( 4, 0.0f ); //SECOND PARAM

	float left			 = 0.0f;
	float top			= 0.0f;
	float right			= 0.0f;
	float bottom		= 0.0f;

	float cache_left    = 0.0f;
	float cache_top     = 0.0f;
	float cache_right   = 0.0f;
	float cache_bottom  = 0.0f;

	float cache_a		= 0.0f;
	float cache_b		= 0.0f;

	float cut_left		= 0.0f;
	float cut_top		= 0.0f;
	float cut_right		= 0.0f;
	float cut_bottom	= 0.0f;

	int total			= 0;


	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	gfxDevice.SetPrimType (  ZGL_PRIM_TRIANGLE_STRIP );

	gfxDevice.BeginPrim ();


	gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ONE, ZGL_BLEND_FACTOR_ONE_MINUS_DST_ALPHA );

	gfxDevice.SetPenColor (0, 0, 0,1 );	

	gfxDevice.WriteVtx ( 0, 0); //TOP_LEFT
	gfxDevice.WriteFinalColor4b ();

	gfxDevice.WriteVtx ( width, 0); //TOP_RIGHT
	gfxDevice.WriteFinalColor4b ();

	gfxDevice.WriteVtx ( 0, height ); //BOTTOM_LEFT
	gfxDevice.WriteFinalColor4b ();

	gfxDevice.WriteVtx ( width, height );//BOTTOM_RIGHT
	gfxDevice.WriteFinalColor4b ();


	//CHANGE_BLEND
	gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ZERO, ZGL_BLEND_FACTOR_ONE_MINUS_SRC_COLOR );


	//******************************
	//
	cache_a		=  width;
	cache_b		=  height;
	

	u32 counter = 0;
	lua_pushnil ( L );

	while ( lua_next ( L, 1 ) != 0 ) {

		if (counter == 0) {left    =(state.GetValue < float >( -1, 0.0f)  );};
		if (counter == 1) {top     =(state.GetValue < float >( -1, 0.0f) );};
		if (counter == 2) {right   =(state.GetValue < float >( -1, 0.0f) );};
		if (counter == 3) {bottom  =(state.GetValue < float >( -1, 0.0f) );};		


		if (counter == 3) {

			//READ 4
			counter = -1;
			++total; 

			if (total == 1) {

				//LAST
				gfxDevice.WriteVtx ( cache_a, cache_b);
				gfxDevice.WriteFinalColor4b ();

				//NEXT
				gfxDevice.WriteVtx ( right, top);
				gfxDevice.WriteFinalColor4b ();

			} else {


				////LAST
				gfxDevice.WriteVtx ( cache_a, cache_b);
				gfxDevice.WriteFinalColor4b ();

				//NEXT
				gfxDevice.WriteVtx ( right, top);
				gfxDevice.WriteFinalColor4b ();


			} //GREATER THAN 2





			//************************************************
			//RIGHT_


			gfxDevice.SetPenColor (0,0,0,0 );	

			gfxDevice.WriteVtx ( right, top);
			gfxDevice.WriteFinalColor4b ();	


			gfxDevice.WriteVtx ( right, bottom);
			gfxDevice.WriteFinalColor4b ();	

			gfxDevice.SetPenColor ( 0, 0,0, 1);

			gfxDevice.WriteVtx ( right-mod, top+mod);
			gfxDevice.WriteFinalColor4b ();	

			gfxDevice.WriteVtx ( right-mod, bottom-mod);
			gfxDevice.WriteFinalColor4b ();	


			////**************************
			////JUMP
		
			gfxDevice.WriteVtx ( right-mod, bottom-mod);
			gfxDevice.WriteFinalColor4b ();	
			//
			gfxDevice.WriteVtx ( right-mod, bottom-mod);
			gfxDevice.WriteFinalColor4b ();


		
			////************************************************
			////BOTTOM_


			gfxDevice.SetPenColor (0, 0, 0,1 );		

			gfxDevice.WriteVtx ( right-mod, bottom-mod);
			gfxDevice.WriteFinalColor4b ();

			gfxDevice.WriteVtx ( left+mod, bottom-mod );
			gfxDevice.WriteFinalColor4b ();


			gfxDevice.SetPenColor ( 0, 0,0,0 );
			gfxDevice.WriteVtx ( right,bottom );
			gfxDevice.WriteFinalColor4b ();

			gfxDevice.WriteVtx ( left, bottom);
			gfxDevice.WriteFinalColor4b ();	

	
	


			//************************************************
			//LEFT_
			gfxDevice.SetPenColor ( 0, 0,0,0 );

			gfxDevice.WriteVtx ( left, bottom);
			gfxDevice.WriteFinalColor4b ();	


			gfxDevice.WriteVtx ( left, top);
			gfxDevice.WriteFinalColor4b ();	

			gfxDevice.SetPenColor (0, 0, 0,1);

			gfxDevice.WriteVtx ( left+mod, bottom-mod);
			gfxDevice.WriteFinalColor4b ();		

			gfxDevice.WriteVtx ( left+mod, top+mod);
			gfxDevice.WriteFinalColor4b ();	




			////************************************************
			////TOP_
			gfxDevice.SetPenColor (0, 0, 0,1 );	

			gfxDevice.WriteVtx ( left+mod, top+mod );
			gfxDevice.WriteFinalColor4b ();

			gfxDevice.WriteVtx ( right-mod, top+mod);
			gfxDevice.WriteFinalColor4b ();

			gfxDevice.SetPenColor ( 0, 0,0,0 );	
			gfxDevice.WriteVtx ( left, top );
			gfxDevice.WriteFinalColor4b ();		

			gfxDevice.WriteVtx ( right, top );
			gfxDevice.WriteFinalColor4b ();


			////**************************
			////JUMP

			gfxDevice.WriteVtx ( right, top );
			gfxDevice.WriteFinalColor4b ();

			gfxDevice.WriteVtx ( left+mod, bottom-mod);
			gfxDevice.WriteFinalColor4b ();


			//CENTER________
			gfxDevice.SetPenColor (0, 0, 0,1);

			gfxDevice.WriteVtx ( left+mod, bottom-mod);
			gfxDevice.WriteFinalColor4b ();

			gfxDevice.WriteVtx ( right-mod, bottom-mod );
			gfxDevice.WriteFinalColor4b ();


			gfxDevice.WriteVtx ( left+mod, top+mod);
			gfxDevice.WriteFinalColor4b ();	


			gfxDevice.WriteVtx ( right-mod, top+mod );
			gfxDevice.WriteFinalColor4b ();




			//******************************
			//CACHE
			cache_a = right-mod;
			cache_b = top+mod;



		};


		++counter;
		lua_pop ( L, 1 );

	}







	//*************************************************************************************
	//PACTHES

	u32 counterA = 0;
	u32 counterB = 0;

	int totalA    = 0;
	int totalB    = 0;

	lua_pushnil ( L );


	while ( lua_next ( L, 1 ) != 0 ) {

		bool isBreak = false;	

		if (counterA == 0) {left    =state.GetValue < float >( -1, 0.0f );};
		if (counterA == 1) {top     =state.GetValue < float >( -1, 0.0f );};
		if (counterA == 2) {right   =state.GetValue < float >( -1, 0.0f );};
		if (counterA == 3) {bottom  =state.GetValue < float >( -1, 0.0f );};		

		if (counterA == 3) {
			counterA = -1;
			totalA++; //TOTAL NUMBER



			totalB = 0; //REST

			lua_pushnil ( L );
			//**************************************************************
			//INNER LOOP
			while ( lua_next ( L, 1 ) != 0 ) {
				if (counterB == 0) {cache_left    =state.GetValue < float >( -1, 0.0f );};
				if (counterB == 1) {cache_top     =state.GetValue < float >( -1, 0.0f );};
				if (counterB == 2) {cache_right   =state.GetValue < float >( -1, 0.0f );};
				if (counterB == 3) {cache_bottom  =state.GetValue < float >( -1, 0.0f );};		

				if (counterB == 3) {

					counterB = -1;
					totalB++; //TOTAL NUMBER

					if (totalB != totalA) {

						if    (left < (cache_right+1) && left > (cache_left-1) && top < (cache_bottom+1) && bottom > (cache_top-1)) 
						{														 

							cut_left  = max(left, cache_left)+(mod);
							cut_right = min(right,cache_right)-(mod);

							cut_top    = max(top, cache_top)+(mod);
							cut_bottom = min(bottom,cache_bottom)-(mod);


							//JUMP
							gfxDevice.WriteVtx ( cache_a, cache_b);
							gfxDevice.WriteFinalColor4b ();

							//NEXT
							gfxDevice.WriteVtx ( cut_left,  cut_bottom);
							gfxDevice.WriteFinalColor4b ();


							//DRAW CENTER
							////CENTER________
							gfxDevice.SetPenColor (1, 0, 0,1);

							gfxDevice.WriteVtx ( cut_left,  cut_bottom);
							gfxDevice.WriteFinalColor4b ();

							gfxDevice.WriteVtx (  cut_right,  cut_bottom );
							gfxDevice.WriteFinalColor4b ();


							gfxDevice.WriteVtx (  cut_left,  cut_top);
							gfxDevice.WriteFinalColor4b ();	


							gfxDevice.WriteVtx (  cut_right,  cut_top );
							gfxDevice.WriteFinalColor4b ();



							//CACHE
							cache_a =  cut_right;
							cache_b =  cut_top;



						}; //COLLESION


					};//END NOT THE SAME RECT

				};//END counterB



				++counterB;
				lua_pop ( L, 1 );
			}; //END LOOP B



			//************************************************************************
		};//END counterA

		++counterA;
		lua_pop ( L, 1 );
	}; //END LOOP A



	gfxDevice.EndPrim ();

	return 0;
}










///****************************************************************************************
///****************************************************************************************
int EZDraw::_drawRoomsC ( lua_State* L ) {

	//MOAI_LUA_SETUP ( EZDraw, "UNT" )
	MOAILuaState state ( L );

	float mod			= state.GetValue < float >( 2, 0.0f ); //SECOND PARAM
	float width			= state.GetValue < float >( 3, 0.0f ); //SECOND PARAM
	float height		= state.GetValue < float >( 4, 0.0f ); //SECOND PARAM

	float left			 = 0.0f;
	float top			= 0.0f;
	float right			= 0.0f;
	float bottom		= 0.0f;

	float cache_left    = 0.0f;
	float cache_top     = 0.0f;
	float cache_right   = 0.0f;
	float cache_bottom  = 0.0f;

	float cache_a		= 0.0f;
	float cache_b		= 0.0f;

	float cut_left		= 0.0f;
	float cut_top		= 0.0f;
	float cut_right		= 0.0f;
	float cut_bottom	= 0.0f;

	int total			= 0;



	//printf("_drawRoomsB:%f %f %f\n",mod,480,320);


	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	gfxDevice.SetPrimType (  ZGL_PRIM_TRIANGLE_STRIP );



	gfxDevice.BeginPrim ();


	gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ONE, ZGL_BLEND_FACTOR_ONE_MINUS_DST_ALPHA );

	gfxDevice.SetPenColor (0, 0, 0,1 );	

	gfxDevice.WriteVtx ( 0, 0); //TOP_LEFT
	gfxDevice.WriteFinalColor4b ();

	gfxDevice.WriteVtx ( 0, height); //TOP_RIGHT
	gfxDevice.WriteFinalColor4b ();

	gfxDevice.WriteVtx ( width, 0 ); //BOTTOM_LEFT
	gfxDevice.WriteFinalColor4b ();

	gfxDevice.WriteVtx ( width,height);//BOTTOM_RIGHT
	gfxDevice.WriteFinalColor4b ();


	//CHANGE_BLEND
	gfxDevice.SetBlendMode ( ZGL_BLEND_FACTOR_ZERO, ZGL_BLEND_FACTOR_ONE_MINUS_SRC_COLOR );


	//******************************
	//
	cache_a		=  width;
	cache_b		=  height;
	

	u32 counter = 0;
	lua_pushnil ( L );

	while ( lua_next ( L, 1 ) != 0 ) {

		if (counter == 0) {left    =(state.GetValue < float >( -1, 0.0f)  );};
		if (counter == 1) {top     =(state.GetValue < float >( -1, 0.0f) );};
		if (counter == 2) {right   =(state.GetValue < float >( -1, 0.0f) );};
		if (counter == 3) {bottom  =(state.GetValue < float >( -1, 0.0f) );};		


		if (counter == 3) {

			//READ 4
			counter = -1;
			++total; 

			if (total == 1) {

				//LAST
				gfxDevice.WriteVtx ( cache_a, cache_b);
				gfxDevice.WriteFinalColor4b ();

				//NEXT
				gfxDevice.WriteVtx ( right, top);
				gfxDevice.WriteFinalColor4b ();

			} else {


				////LAST
				gfxDevice.WriteVtx ( cache_a, cache_b);
				gfxDevice.WriteFinalColor4b ();

				//NEXT
				gfxDevice.WriteVtx ( right, top);
				gfxDevice.WriteFinalColor4b ();


			} //GREATER THAN 2





			//************************************************
			//RIGHT_


			gfxDevice.SetPenColor (0,0,0,0 );	

			gfxDevice.WriteVtx ( right, top);
			gfxDevice.WriteFinalColor4b ();	


			gfxDevice.WriteVtx ( right, bottom);
			gfxDevice.WriteFinalColor4b ();	

			gfxDevice.SetPenColor ( 0, 0,0, 1);

			gfxDevice.WriteVtx ( right-mod, top+mod);
			gfxDevice.WriteFinalColor4b ();	

			gfxDevice.WriteVtx ( right-mod, bottom-mod);
			gfxDevice.WriteFinalColor4b ();	


			////**************************
			////JUMP
		
			gfxDevice.WriteVtx ( right-mod, bottom-mod);
			gfxDevice.WriteFinalColor4b ();	
			//
			gfxDevice.WriteVtx ( right-mod, bottom-mod);
			gfxDevice.WriteFinalColor4b ();


		
			////************************************************
			////BOTTOM_


			gfxDevice.SetPenColor (0, 0, 0,1 );		

			gfxDevice.WriteVtx ( right-mod, bottom-mod);
			gfxDevice.WriteFinalColor4b ();

			gfxDevice.WriteVtx ( left+mod, bottom-mod );
			gfxDevice.WriteFinalColor4b ();


			gfxDevice.SetPenColor ( 0, 0,0,0 );
			gfxDevice.WriteVtx ( right,bottom );
			gfxDevice.WriteFinalColor4b ();

			gfxDevice.WriteVtx ( left, bottom);
			gfxDevice.WriteFinalColor4b ();	

	
	


			//************************************************
			//LEFT_
			gfxDevice.SetPenColor ( 0, 0,0,0 );

			gfxDevice.WriteVtx ( left, bottom);
			gfxDevice.WriteFinalColor4b ();	


			gfxDevice.WriteVtx ( left, top);
			gfxDevice.WriteFinalColor4b ();	

			gfxDevice.SetPenColor (0, 0, 0,1);

			gfxDevice.WriteVtx ( left+mod, bottom-mod);
			gfxDevice.WriteFinalColor4b ();		

			gfxDevice.WriteVtx ( left+mod, top+mod);
			gfxDevice.WriteFinalColor4b ();	




			////************************************************
			////TOP_
			gfxDevice.SetPenColor (0, 0, 0,1 );	

			gfxDevice.WriteVtx ( left+mod, top+mod );
			gfxDevice.WriteFinalColor4b ();

			gfxDevice.WriteVtx ( right-mod, top+mod);
			gfxDevice.WriteFinalColor4b ();

			gfxDevice.SetPenColor ( 0, 0,0,0 );	
			gfxDevice.WriteVtx ( left, top );
			gfxDevice.WriteFinalColor4b ();		

			gfxDevice.WriteVtx ( right, top );
			gfxDevice.WriteFinalColor4b ();


			////**************************
			////JUMP

			gfxDevice.WriteVtx ( right, top );
			gfxDevice.WriteFinalColor4b ();

			gfxDevice.WriteVtx ( left+mod, bottom-mod);
			gfxDevice.WriteFinalColor4b ();


			//CENTER________
			gfxDevice.SetPenColor (0, 0, 0,1);

			gfxDevice.WriteVtx ( left+mod, bottom-mod);
			gfxDevice.WriteFinalColor4b ();

			gfxDevice.WriteVtx ( right-mod, bottom-mod );
			gfxDevice.WriteFinalColor4b ();


			gfxDevice.WriteVtx ( left+mod, top+mod);
			gfxDevice.WriteFinalColor4b ();	


			gfxDevice.WriteVtx ( right-mod, top+mod );
			gfxDevice.WriteFinalColor4b ();




			//******************************
			//CACHE
			cache_a = right-mod;
			cache_b = top+mod;



		};


		++counter;
		lua_pop ( L, 1 );

	}







	//*************************************************************************************
	//PACTHES

	u32 counterA = 0;
	u32 counterB = 0;

	int totalA    = 0;
	int totalB    = 0;

	lua_pushnil ( L );


	while ( lua_next ( L, 1 ) != 0 ) {

		bool isBreak = false;	

		if (counterA == 0) {left    =state.GetValue < float >( -1, 0.0f );};
		if (counterA == 1) {top     =state.GetValue < float >( -1, 0.0f );};
		if (counterA == 2) {right   =state.GetValue < float >( -1, 0.0f );};
		if (counterA == 3) {bottom  =state.GetValue < float >( -1, 0.0f );};		

		if (counterA == 3) {
			counterA = -1;

			totalA++; //TOTAL NUMBER

			totalB = 0; //REST

			lua_pushnil ( L );
			//**************************************************************
			//INNER LOOP
			while ( lua_next ( L, 1 ) != 0 ) {
				if (counterB == 0) {cache_left    =state.GetValue < float >( -1, 0.0f );};
				if (counterB == 1) {cache_top     =state.GetValue < float >( -1, 0.0f );};
				if (counterB == 2) {cache_right   =state.GetValue < float >( -1, 0.0f );};
				if (counterB == 3) {cache_bottom  =state.GetValue < float >( -1, 0.0f );};		

				if (counterB == 3) {

					counterB = -1;
					totalB++; //TOTAL NUMBER

					if (totalB != totalA) {

						if    (left < (cache_right+1) && left > (cache_left-1) && top < (cache_bottom+1) && bottom > (cache_top-1)) 
						{														 

							cut_left  = max(left, cache_left)+(mod);
							cut_right = min(right,cache_right)-(mod);

							cut_top    = max(top, cache_top)+(mod);
							cut_bottom = min(bottom,cache_bottom)-(mod);


							//JUMP
							gfxDevice.WriteVtx ( cache_a, cache_b);
							gfxDevice.WriteFinalColor4b ();

							//NEXT
							gfxDevice.WriteVtx ( cut_left,  cut_bottom);
							gfxDevice.WriteFinalColor4b ();


							//DRAW CENTER
							////CENTER________
							gfxDevice.SetPenColor (1, 0, 0,1);

							gfxDevice.WriteVtx ( cut_left,  cut_bottom);
							gfxDevice.WriteFinalColor4b ();

							gfxDevice.WriteVtx (  cut_right,  cut_bottom );
							gfxDevice.WriteFinalColor4b ();


							gfxDevice.WriteVtx (  cut_left,  cut_top);
							gfxDevice.WriteFinalColor4b ();	


							gfxDevice.WriteVtx (  cut_right,  cut_top );
							gfxDevice.WriteFinalColor4b ();



							//CACHE
							cache_a =  cut_right;
							cache_b =  cut_top;



						}; //COLLESION


					};//END NOT THE SAME RECT

				};//END counterB



				++counterB;
				lua_pop ( L, 1 );
			}; //END LOOP B



			//************************************************************************
		};//END counterA

		++counterA;
		lua_pop ( L, 1 );
	}; //END LOOP A



	gfxDevice.EndPrim ();

	return 0;

}





//**********************************************************************
//BORDERS
int EZDraw::_drawBorders ( lua_State* L){

	//MOAI_LUA_SETUP ( EZDraw, "U" )
	MOAILuaState state ( L );

	float left   = state.GetValue < float >( 1, 0.0f );
	float top    = state.GetValue < float >( 2, 0.0f );
	float right  = state.GetValue < float >( 3, 0.0f );
	float bottom =  state.GetValue < float >( 4, 0.0f );

	float width  = state.GetValue < float >( 5, 0.0f );
	float height =  state.GetValue < float >( 6, 0.0f );



	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	gfxDevice.SetPrimType ( ZGL_PRIM_TRIANGLE_STRIP);
	gfxDevice.BeginPrim ();

	//******************
	//top

	gfxDevice.SetPenColor ( 0, 0,0,1 );	

	//TOP_

	gfxDevice.WriteVtx ( 0, 0 );
	gfxDevice.WriteFinalColor4b ();

	gfxDevice.WriteVtx ( width, 0);
	gfxDevice.WriteFinalColor4b ();


	gfxDevice.WriteVtx ( 0, top );
	gfxDevice.WriteFinalColor4b ();		

	gfxDevice.WriteVtx ( width, top );
	gfxDevice.WriteFinalColor4b ();


	//LEFT_

	gfxDevice.WriteVtx ( 0,top);
	gfxDevice.WriteFinalColor4b ();	


	gfxDevice.WriteVtx ( left, top);
	gfxDevice.WriteFinalColor4b ();	


	gfxDevice.WriteVtx ( 0,bottom);
	gfxDevice.WriteFinalColor4b ();


	gfxDevice.WriteVtx ( left, bottom);
	gfxDevice.WriteFinalColor4b ();	


	//BOTTOM_

	gfxDevice.WriteVtx ( 0,bottom);
	gfxDevice.WriteFinalColor4b ();	


	gfxDevice.WriteVtx ( width, bottom);
	gfxDevice.WriteFinalColor4b ();	


	gfxDevice.WriteVtx ( 0,height);
	gfxDevice.WriteFinalColor4b ();


	gfxDevice.WriteVtx ( width, height);
	gfxDevice.WriteFinalColor4b ();	



	//RIGHT_

	gfxDevice.WriteVtx ( width,bottom);
	gfxDevice.WriteFinalColor4b ();	


	gfxDevice.WriteVtx ( right, bottom);
	gfxDevice.WriteFinalColor4b ();	


	gfxDevice.WriteVtx ( width,top);
	gfxDevice.WriteFinalColor4b ();


	gfxDevice.WriteVtx ( right, top);
	gfxDevice.WriteFinalColor4b ();	



	//******************************************************************
	//GRDINET


	//MOVE
	gfxDevice.WriteVtx ( right, top);
	gfxDevice.WriteFinalColor4b ();	
	gfxDevice.WriteVtx (  right-16, top);
	gfxDevice.WriteFinalColor4b ();




	//RIGHT_
	gfxDevice.SetPenColor (0,0,0,0 );	

	gfxDevice.WriteVtx ( right-16, top);
	gfxDevice.WriteFinalColor4b ();	


	gfxDevice.WriteVtx ( right-16, bottom);
	gfxDevice.WriteFinalColor4b ();	

	gfxDevice.SetPenColor ( 0, 0,0, 1);

	gfxDevice.WriteVtx ( right, top);
	gfxDevice.WriteFinalColor4b ();	

	gfxDevice.WriteVtx ( right, bottom);
	gfxDevice.WriteFinalColor4b ();	

	////BOTTOM_


	gfxDevice.SetPenColor (0, 0, 0,1 );		

	gfxDevice.WriteVtx ( right, bottom);
	gfxDevice.WriteFinalColor4b ();

	gfxDevice.WriteVtx ( left, bottom );
	gfxDevice.WriteFinalColor4b ();



	gfxDevice.SetPenColor ( 0, 0,0,0 );
	gfxDevice.WriteVtx ( right,bottom-16 );
	gfxDevice.WriteFinalColor4b ();

	gfxDevice.WriteVtx ( left, bottom-16);
	gfxDevice.WriteFinalColor4b ();	



	//LEFT_
	gfxDevice.SetPenColor ( 0, 0,0,0 );

	gfxDevice.WriteVtx ( left+16, bottom);
	gfxDevice.WriteFinalColor4b ();	


	gfxDevice.WriteVtx ( left+16, top);
	gfxDevice.WriteFinalColor4b ();	

	gfxDevice.SetPenColor (0, 0, 0,1);

	gfxDevice.WriteVtx ( left, bottom);
	gfxDevice.WriteFinalColor4b ();		

	gfxDevice.WriteVtx ( left, top);
	gfxDevice.WriteFinalColor4b ();	


	////TOP_
	gfxDevice.SetPenColor (0, 0, 0,1 );	

	gfxDevice.WriteVtx ( left, top );
	gfxDevice.WriteFinalColor4b ();

	gfxDevice.WriteVtx ( right, top);
	gfxDevice.WriteFinalColor4b ();

	gfxDevice.SetPenColor ( 0, 0,0,0 );	

	gfxDevice.WriteVtx ( left, top+16 );
	gfxDevice.WriteFinalColor4b ();		

	gfxDevice.WriteVtx ( right, top+16 );
	gfxDevice.WriteFinalColor4b ();



	//end
	gfxDevice.EndPrim ();


return 0;
}







//================================================================//
//================================================================//

//----------------------------------------------------------------//
EZDraw::EZDraw () :
mWidth ( 480.0f ),
mHeight ( 320.0f )
{

	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )	
	RTTI_END
}

//----------------------------------------------------------------//
EZDraw::~EZDraw () {
}

//----------------------------------------------------------------//
void EZDraw::RegisterLuaClass ( MOAILuaState& state ) {

	//UNUSED ( state );
	// call any initializers for base classes here:
	// EZDraw::RegisterLuaClass ( state );
	// also register constants:
	// state.SetField ( -1, "FOO_CONST", ( u32 )FOO_CONST );
	// here are the class methods:
	//luaL_register ( state, 0, regTable );


		luaL_Reg regTable [] = {
		{ "drawBlack",		_drawBlack },
		{ "drawRoomsB",		_drawRoomsB },
		{ "drawBorders",	_drawBorders },	
		{ "setBounds",		_setBounds },				
		{ NULL, NULL }
		};

	luaL_register ( state, 0, regTable );

}

//----------------------------------------------------------------//
void EZDraw::RegisterLuaFuncs ( MOAILuaState& state ) {

		//call any initializers for base classes here:
		//EZDraw::RegisterLuaFuncs ( state );
		//MOAIDraw::RegisterLuaFuncs ( state );

	
		luaL_Reg regTable [] = {
		{ "drawBlack",		_drawBlack },
		{ "drawRoomsB",		_drawRoomsB },
		{ "drawRoomsC",		_drawRoomsC },
		{ "drawBorders",	_drawBorders },	
		{ "setBounds",		_setBounds },				
		{ NULL, NULL }
		};


	luaL_register ( state, 0, regTable );


}

