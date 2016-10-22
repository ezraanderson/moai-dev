// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIGfxDevice.h>
#include <moai-ezra/mesh/MOAIEzraVertexFormat.h>
#include <moai-ezra/mesh/MOAIEzraVertexBuffer.h>





///*********
//LOC
void MOAIEzraVertexBuffer::writeFloat_loc (float a, float b ) {	    


		this->mStream.Write < float >( a );
		this->mStream.Write < float >( b );
		this->mStream.Write < float >( 0);
       // this->mStream.Write < float >( 0);

}


//******************************************************
//COLOR
void MOAIEzraVertexBuffer::writeColor_rgb ( float r,float g,float b, float a ) {

	u32 color = ZLColor::PackRGBA ( r, g, b, 1.0f );
	this->mStream.Write < u32 >( color );	

}



///*********
//SIZE
void MOAIEzraVertexBuffer::writeFloat_size (float a ) {	
		this->mStream.Write < float   > ( a );

       // this->mStream.Write < float >   ( 0);
}




///*********
void MOAIEzraVertexBuffer::SetCursor (long index ) {
            this->mStream.SetCursor(index);   
}


///*********
void MOAIEzraVertexBuffer::pCursor () {

                printf("%d \n", this->mStream.GetCursor());
}


///*********
void MOAIEzraVertexBuffer::writeFloat_uv (s8 a, s8 b ) {	
		this->mStream.Write < s8  >( a );
		this->mStream.Write < s8  >( b );	
}



void MOAIEzraVertexBuffer::reset_box ( ) {
    this->mStream.SetBuffer( this->mBuffer,this->mBuffer.Size ());
}

void MOAIEzraVertexBuffer::bless_box ( ) {
	
	this->mBounds.Init ( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );	
	if ( this->mFormat ) {
		this->mFormat->ComputeBounds ( this->mBuffer, this->mStream.GetLength (), this->mBounds );
	}
	

}





//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//WRITE GEO
int MOAIEzraVertexBuffer::_writeGeo (lua_State* L ) {	

MOAI_LUA_SETUP ( MOAIEzraVertexBuffer, "U" )

//LOC
    //float loc_x = state.GetValue < float >( 5, 1.0f );
    //float loc_y = state.GetValue < float >( 6, 1.0f );
    //float loc_z = state.GetValue < float >( 7, 1.0f );

    self->mStream.Write < float   > ( state.GetValue < float >( 2, 1.0f ) );
    self->mStream.Write < float   > ( state.GetValue < float >( 3, 1.0f ) );
    self->mStream.Write < float   > ( state.GetValue < float >( 4, 1.0f ) );




//COLOR
    //float r = state.GetValue < float >( 5, 1.0f );
    //float g = state.GetValue < float >( 6, 1.0f );
    //float b = state.GetValue < float >( 7, 1.0f );
    //float a = state.GetValue < float >( 8, 1.0f );

    u32 color = ZLColor::PackRGBA ( 
                                    state.GetValue < float >( 5, 1.0f ), 
                                    state.GetValue < float >( 6, 1.0f ), 
                                    state.GetValue < float >( 7, 1.0f ), 
                                    state.GetValue < float >( 8, 1.0f ) 
                                    );

    self->mStream.Write < u32 >( color );


//SIZE
    //float size = state.GetValue < float >( 9, 1.0f );
    self->mStream.Write < float   > ( state.GetValue < float >( 9, 1.0f ) );



//ROTATE
    //float cos = state.GetValue < float >( 10, 1.0f );
    //float sin = state.GetValue < float >( 11, 1.0f );

   self->mStream.Write < float   > ( state.GetValue < float >( 10, 1.0f ) );
   self->mStream.Write < float   > ( state.GetValue < float >( 11, 1.0f ) );



//UV
    //float ux = state.GetValue < float >( 12, 1.0f );
    //float uy = state.GetValue < float >( 13, 1.0f );

   self->mStream.Write < float   > ( state.GetValue < float >( 12, 1.0f ) );
   self->mStream.Write < float   > ( state.GetValue < float >( 13, 1.0f ) );

return true;

}



//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//RINGS
int MOAIEzraVertexBuffer::_writeRings (lua_State* L ) {	

MOAI_LUA_SETUP ( MOAIEzraVertexBuffer, "U" )  
self->SetCursor(0);

float loc_x  = 0.0f;
float loc_y  = 0.0f;
float rad    = 0.0f;

float red    = 0.0f;
float green  = 0.0f;
float blue   = 0.0f;
float alpha  = 0.0f;

float cacheA = 0.0f;
float cacheB = 0.0f;
 
u32 counter      = 0;
u32 total        = 0;

//int max         = self->mTotal;

int   steps      = 32;
float angle      = ( float )TWOPI / ( float )steps;
float angleStep  = 0;
int   high       = 0;

//GET GLOBAL TABLE
lua_getglobal (L, "list_rings");
lua_pushnil(L);
while (lua_next(L, -2) != 0) {

    //PREVENT WRTIING IN TO MANY VERTIC SHOULD BE OUT SIDE OF A LOOP
    //if (max == total) {break;};

       //CORDINATE
		if (counter == 0) {loc_x  =(float)lua_tonumber(L, -1);};
		if (counter == 1) {loc_y  =(float)lua_tonumber(L, -1);};	
        if (counter == 2) {rad    =(float)lua_tonumber(L, -1);};	
        //COLOR    
		if (counter == 3) {red    =(float)lua_tonumber(L, -1);};
		if (counter == 4) {green  =(float)lua_tonumber(L, -1);};
		if (counter == 5) {blue   =(float)lua_tonumber(L, -1);};
		if (counter == 6) {alpha  =(float)lua_tonumber(L, -1);};	

        float angleStep = 0;

		if (counter == 6) {
            counter = -1;

                u32 color = ZLColor::PackRGBA ( red, green, blue, alpha );

                for(int i=0; i<steps; i++) {

                            angleStep = angleStep + angle;

                    		float x = loc_x + ( sin ( angleStep )* rad );
				            float y = loc_y + ( cos ( angleStep )* rad );

                            self->mStream.Write < float   > ( x );
                            self->mStream.Write < float   > ( y );                        
                            self->mStream.Write < u32 >( color );
                            
				            x = loc_x + ( sin ( angleStep+angle )* rad );
				            y = loc_y + ( cos ( angleStep+angle )* rad );

                            self->mStream.Write < float   > ( x );
                            self->mStream.Write < float   > ( y );                           
                            self->mStream.Write < u32 >( color );
                     
                };

        ++total;
		};

++counter;

lua_pop(L, 1);
}

return true;
}

//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//CIRCLES

int MOAIEzraVertexBuffer::_writeCircles (lua_State* L ) {	
MOAI_LUA_SETUP ( MOAIEzraVertexBuffer, "U" )  

self->SetCursor(0);
self->reset_box();

float loc_x  = 0.0f;
float loc_y  = 0.0f;
float rad    = 0.0f;

float red    = 0.0f;
float green  = 0.0f;
float blue   = 0.0f;
float alpha  = 0.0f;

float cache_x = 0.0f;
float cache_y = 0.0f;
 
u32 counter      = 0;
u32 total        = 0;

int max = self->mTotal;



int     steps       = 32-1;
float   angle       = ( float )TWOPI / ( float )steps;
float   angleStep   = 0;
int     high        = 0;

//GET GLOBAL TABLE
lua_getglobal (L, "list_circles");
lua_pushnil(L);
while (lua_next(L, -2) != 0) {


    //PREVENT WRTIING IN TO MANY VERTIC SHOULD BE OUT SIDE OF A LOOP
   // if (max == total) {break;};


       //CORDINATE
		if (counter == 0) {loc_x  =(float)lua_tonumber(L, -1);};
		if (counter == 1) {loc_y  =(float)lua_tonumber(L, -1);};	
        if (counter == 2) {rad    =(float)lua_tonumber(L, -1);};	
        //COLOR    
		if (counter == 3) {red    =(float)lua_tonumber(L, -1);};
		if (counter == 4) {green  =(float)lua_tonumber(L, -1);};
		if (counter == 5) {blue   =(float)lua_tonumber(L, -1);};
		if (counter == 6) {alpha  =(float)lua_tonumber(L, -1);};	

  

		if (counter == 6) {
            counter = -1;
           

             u32 color = ZLColor::PackRGBA ( red, green, blue, alpha );

   
             if (total > 0) {
                
                        //printf("C++JUMP\n");

				        //CACHE 			
                        self->mStream.Write < float   > ( cache_x );
                        self->mStream.Write < float   > ( cache_y );                           
                        self->mStream.Write < u32 >( color );

                        //LOC
                        self->mStream.Write < float   > ( loc_x );
                        self->mStream.Write < float   > ( loc_y );                           
                        self->mStream.Write < u32 >( color );				
				
             };

                 // printf("----\n");

                for(int i=0; i<steps; i++) {
                

                   // printf("STEPS %i \n",i);

                            //STEP
                           angleStep = angleStep + angle;

                            //CENTER_POINT
                            self->mStream.Write < float   > ( loc_x );
                            self->mStream.Write < float   > ( loc_y );                           
                            self->mStream.Write < u32 >( color );

                            //NEXT_POINT
                    		float x = loc_x + ( sin ( angleStep )* rad );
				            float y = loc_y + ( cos ( angleStep )* rad );

                            self->mStream.Write < float   > ( x );
                            self->mStream.Write < float   > ( y );                        
                            self->mStream.Write < u32 >( color );

                       
                 
                     
                };


                         //LAST_POINT
                            angleStep = angleStep + angle;
                    		float x = loc_x + ( sin ( angleStep )* rad );
				            float y = loc_y + ( cos ( angleStep )* rad );

                            self->mStream.Write < float   > ( x );
                            self->mStream.Write < float   > ( y );                        
                            self->mStream.Write < u32 >( color );

                            //CACHE POINTS
				            cache_x = x;
					        cache_y = y;


            ++total;
		};



++counter;
lua_pop(L, 1);
}

 return true;
}









//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//LINES
int MOAIEzraVertexBuffer::_writeLines (lua_State* L ) {	

MOAI_LUA_SETUP ( MOAIEzraVertexBuffer, "U" )  
self->SetCursor(0);

float x1        = 0.0f;
float y1        = 0.0f;
float x2        = 0.0f;
float y2        = 0.0f;

float red        = 0.0f;
float green     = 0.0f;
float blue      = 0.0f;
float alpha     = 0.0f;

float cacheA    = 0.0f;
float cacheB    = 0.0f;
 
u32 counter      = 0;
u32 total        = 0;
int max         = self->mTotal;

//GET GLOBAL TABLE
lua_getglobal (L, "list_lines");
lua_pushnil(L);
while (lua_next(L, -2) != 0) {


    //PREVENT WRTIING IN TO MANY VERTIC SHOULD BE OUT SIDE OF A LOOP
    //if (max == total) {break;};

       //CORDINATE
		if (counter == 0) {x1    =(float)lua_tonumber(L, -1);};
		if (counter == 1) {y1    =(float)lua_tonumber(L, -1);};	
        if (counter == 2) {x2    =(float)lua_tonumber(L, -1);};	
        if (counter == 3) {y2    =(float)lua_tonumber(L, -1);};	
        //COLOR    
		if (counter == 4) {red    =(float)lua_tonumber(L, -1);};
		if (counter == 5) {green  =(float)lua_tonumber(L, -1);};
		if (counter == 6) {blue   =(float)lua_tonumber(L, -1);};
		if (counter == 7) {alpha  =(float)lua_tonumber(L, -1);};	
    

		if (counter == 7) {
            counter = -1;

   
           // printf("wtf %f %f %f %f \n",x1,y1,x2,y2);
                u32 color = ZLColor::PackRGBA ( red, green, blue, alpha );

                            self->mStream.Write < float   > ( x1 );
                            self->mStream.Write < float   > ( y1 );                       
                            self->mStream.Write < u32 >( color );                            
				           
                            self->mStream.Write < float   > ( x2 );
                            self->mStream.Write < float   > ( y2 );                           
                            self->mStream.Write < u32 >( color );
                     
           

		};

++counter;
++total;
lua_pop(L, 1);
}

 return true;
}













//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************


int MOAIEzraVertexBuffer::_setCursorZero (lua_State* L ) {	
    MOAI_LUA_SETUP ( MOAIEzraVertexBuffer, "U" )  
    self->SetCursor(0);
    return true;
};
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************
//*******************************************************************

int MOAIEzraVertexBuffer::_writeRects (lua_State* L ) {	
MOAI_LUA_SETUP ( MOAIEzraVertexBuffer, "U" )  

self->SetCursor(0);

u32 counter     = 0;
float cache_x   = 0.0f;
float cache_y   = 0.0f;


 for(int y=0; y<125; y++) {
           for(int x=0; x<125; x++) {

               float loc_x =x*5;
               float loc_y =y*5;

               u32 color = ZLColor::PackRGBA ( 1.0f, 0.2f, 0.2f, 0.2f );

           

               if (counter > 0) {
                 //  printf("Jump \n");
                       //LEFT_BOTTOM
                            self->mStream.Write < float   > ( cache_x );
                            self->mStream.Write < float   > ( cache_y );                           
                            self->mStream.Write < u32 >( color );


                         //LEFT_BOTTOM
                            self->mStream.Write < float   > ( loc_x );
                            self->mStream.Write < float   > ( loc_y );                           
                            self->mStream.Write < u32 >( color );
               };
          
                  

                            //LEFT_BOTTOM
                            self->mStream.Write < float   > ( loc_x );
                            self->mStream.Write < float   > ( loc_y );                           
                            self->mStream.Write < u32 >( color );

                            //RIGHT_BOTTOM    
                            self->mStream.Write < float   > ( loc_x );
                            self->mStream.Write < float   > ( loc_y+4 );                           
                            self->mStream.Write < u32 >( color );

                             //RIGHT_TOP
                            self->mStream.Write < float   > ( loc_x+4 );
                            self->mStream.Write < float   > ( loc_y );                           
                            self->mStream.Write < u32 >( color );


                            //LEFT_TOP
                            self->mStream.Write < float   > ( loc_x+4 );
                            self->mStream.Write < float   > ( loc_y+4 );                       
                            self->mStream.Write < u32 >( color );     

                                cache_x =loc_x+4 ;
                                cache_y =loc_y+4; 

                 ++counter;
           };          
    };














 
//float x1        = 0.0f;
//float y1        = 0.0f;
//float x2        = 0.0f;
//float y2        = 0.0f;
//
//float red       = 0.0f;
//float green     = 0.0f;
//float blue      = 0.0f;
//float alpha     = 0.0f;
//
//float cache_x   = 0.0f;
//float cache_y   = 0.0f;
// 
//u32 counter     = 0;
//u32 total       = 0;
//int max         = self->mTotal;




//
//
//
//lua_getglobal (L, "list_rects");
//lua_pushnil(L);
//while (lua_next(L, -2) != 0) {
//
//
//
//		if (counter == 0) {x1    =(float)lua_tonumber(L, -1);};
//		if (counter == 1) {y1    =(float)lua_tonumber(L, -1);};	
//        if (counter == 2) {x2    =(float)lua_tonumber(L, -1);};	
//        if (counter == 3) {y2    =(float)lua_tonumber(L, -1);};	
//   
//		if (counter == 4) {red    =(float)lua_tonumber(L, -1);};
//		if (counter == 5) {green  =(float)lua_tonumber(L, -1);};
//		if (counter == 6) {blue   =(float)lua_tonumber(L, -1);};
//		if (counter == 7) {alpha  =(float)lua_tonumber(L, -1);};	
//    
//
//		if (counter == 7) {
//            counter = -1;
//
//             //u32 color = ZLColor::PackRGBA ( red, green, blue, alpha );
//
//
//            //  if (total > 0) {
//
//            //      //LAST
//
//            //                self->mStream.Write < float   > ( cache_x );
//            //                self->mStream.Write < float   > (cache_y );                       
//            //                self->mStream.Write < u32 >( color ); 
//
//            //      //FIRST
//            //                self->mStream.Write < float   > ( x1 );
//            //                self->mStream.Write < float   > ( y1 );                       
//            //                self->mStream.Write < u32 >( color ); 
//
//            //   }; 
//
//
//
//            //                //LEFT_TOP
//            //                self->mStream.Write < float   > ( x1 );
//            //                self->mStream.Write < float   > ( y1 );                       
//            //                self->mStream.Write < u32 >( color );                            
//				        //   
//
//            //                //LEFT_BOTTOM
//            //                self->mStream.Write < float   > ( x1 );
//            //                self->mStream.Write < float   > ( y2 );                           
//            //                self->mStream.Write < u32 >( color );
//
//
//            //                //RIGHT_TOP
//            //                self->mStream.Write < float   > ( x2 );
//            //                self->mStream.Write < float   > ( y1 );                           
//            //                self->mStream.Write < u32 >( color );
//
//            //                //RIGHT_BOTTOM    
//            //                self->mStream.Write < float   > ( x2 );
//            //                self->mStream.Write < float   > ( y2 );                           
//            //                self->mStream.Write < u32 >( color );
//
//
//            //                cache_x    = x2;
//            //                cache_y    = y2;   
//
//
//            //*****************************************************************
//            //IBO
//
//
//                            u32 color = ZLColor::PackRGBA ( red, green, blue, alpha );
//
//                            //LEFT_BOTTOM
//                            self->mStream.Write < float   > ( x1-2 );
//                            self->mStream.Write < float   > ( y1+2 );                           
//                            self->mStream.Write < u32 >( color );
//
//                            //RIGHT_BOTTOM    
//                            self->mStream.Write < float   > ( x1+2 );
//                            self->mStream.Write < float   > ( y1+2 );                           
//                            self->mStream.Write < u32 >( color );
//
//                             //RIGHT_TOP
//                            self->mStream.Write < float   > ( x1+2 );
//                            self->mStream.Write < float   > ( y1-2 );                           
//                            self->mStream.Write < u32 >( color );
//
//
//                            //LEFT_TOP
//                            self->mStream.Write < float   > ( x1-2 );
//                            self->mStream.Write < float   > ( y1-2 );                       
//                            self->mStream.Write < u32 >( color );                            
//
//           
//            ++total;
//		};
//
//
//
//++counter;
//lua_pop(L, 1);
//}

 return true;
}



//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/** @name bless
@text Call this after initializing the buffer and settings it vertices
to prepare it for use.
@in MOAIEzraVertexBuffer self
@out nil
*/
int MOAIEzraVertexBuffer::_bless ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIEzraVertexBuffer, "U" )

self->mBounds.Init ( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );

if ( self->mFormat ) {
self->mFormat->ComputeBounds ( self->mBuffer, self->mStream.GetLength (), self->mBounds );
}

return 0;
}

//----------------------------------------------------------------//
/** @name release
@text Releases any memory associated with buffer.
@in MOAIEzraVertexBuffer self
@out nil
*/
int	MOAIEzraVertexBuffer::_release ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIEzraVertexBuffer, "U" )

self->Clear ();
return 0;
}

//----------------------------------------------------------------//
/** @name reserve
@text Sets capacity of buffer in bytes.
@in MOAIEzraVertexBuffer self
@in number size
@out nil
*/
int	MOAIEzraVertexBuffer::_reserve ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIEzraVertexBuffer, "UN" )

u32 size = state.GetValue < u32 >( 2, 0 );
self->Reserve ( size );

return 0;
}

//----------------------------------------------------------------//
/** @name reserveVerts
@text Sets capacity of buffer in vertices. This function should
only be used after attaching a valid MOAIezraVertexFormat
to the buffer.
@in MOAIEzraVertexBuffer self
@in number size
@out nil
*/
int	MOAIEzraVertexBuffer::_reserveVerts ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIEzraVertexBuffer, "UN" )

u32 total = state.GetValue < u32 >( 2, 0 );

self->mTotal = total;

if ( self->mFormat ) {
self->Reserve ( total * self->mFormat->GetVertexSize ());
}
return 0;
}








//----------------------------------------------------------------//
/** @name reset
@text Resets the vertex stream writing to the head of the stream.
@in MOAIEzraVertexBuffer self
@out nil
*/
int MOAIEzraVertexBuffer::_reset ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIEzraVertexBuffer, "U" )

self->mStream.SetBuffer ( self->mBuffer, self->mBuffer.Size ());

return 0;
}

//----------------------------------------------------------------//
/** @name setFormat
@text Sets the vertex format for the buffer.
@in MOAIEzraVertexBuffer self
@in MOAIezraVertexFormat format
@out nil
*/
int MOAIEzraVertexBuffer::_setFormat ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIEzraVertexBuffer, "U" )

self->mFormat.Set ( *self, state.GetLuaObject < MOAIVertexFormat >( 2, true ));

return 0;
}

//----------------------------------------------------------------//
/** @name writeColor32
@text Write a packed 32-bit color to the vertex buffer.
@in MOAIEzraVertexBuffer self
@opt number r Default value is 1.
@opt number g Default value is 1.
@opt number b Default value is 1.
@opt number a Default value is 1.
@out nil
*/
int MOAIEzraVertexBuffer::_writeColor32 ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIEzraVertexBuffer, "U" )

float r = state.GetValue < float >( 2, 1.0f );
float g = state.GetValue < float >( 3, 1.0f );
float b = state.GetValue < float >( 4, 1.0f );
float a = state.GetValue < float >( 5, 1.0f );

u32 color = ZLColor::PackRGBA ( r, g, b, a );
self->mStream.Write < u32 >( color );

return 0;
}

//----------------------------------------------------------------//
/** @name writeFloat
@text Write a 32-bit float to the vertex buffer.
@in MOAIEzraVertexBuffer self
@opt number f Default value is 0.
@out nil
*/
int MOAIEzraVertexBuffer::_writeFloat ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIEzraVertexBuffer, "U" )

u32 top = state.GetTop ();
for ( u32 i = 2; i <= top; ++i ) {
float param = state.GetValue < float >( i, 0.0f );
self->mStream.Write < float >( param );
}
return 0;
}

//----------------------------------------------------------------//
/** @name writeInt8
@text Write an 8-bit integer to the vertex buffer.
@in MOAIEzraVertexBuffer self
@opt number i Default value is 0.
@out nil
*/
int MOAIEzraVertexBuffer::_writeInt8 ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIEzraVertexBuffer, "U" )

u32 top = state.GetTop ();
for ( u32 i = 2; i <= top; ++i ) {
int param = state.GetValue < int >( i, 0 );
self->mStream.Write < s8 >(( s8 )param );
}
return 0;
}

//----------------------------------------------------------------//
/** @name writeInt16
@text Write an 16-bit integer to the vertex buffer.
@in MOAIEzraVertexBuffer self
@opt number i Default value is 0.
@out nil
*/
int MOAIEzraVertexBuffer::_writeInt16 ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIEzraVertexBuffer, "U" )

u32 top = state.GetTop ();
for ( u32 i = 2; i <= top; ++i ) {
int param = state.GetValue < int >( i, 0 );
self->mStream.Write < s16 >(( s16 )param );
}
return 0;
}

//----------------------------------------------------------------//
/** @name writeInt32
@text Write an 32-bit integer to the vertex buffer.
@in MOAIEzraVertexBuffer self
@opt number i Default value is 0.
@out nil
*/
int MOAIEzraVertexBuffer::_writeInt32 ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIEzraVertexBuffer, "U" )

u32 top = state.GetTop ();
for ( u32 i = 2; i <= top; ++i ) {
int param = state.GetValue < int >( i, 0 );
self->mStream.Write < s32 >(( s32 )param );
}
return 0;
}

//================================================================//
// MOAIGfxQuadListDeck2D
//================================================================//

//----------------------------------------------------------------//
bool MOAIEzraVertexBuffer::Bind () {
	if ( this->mFormat && this->mBuffer ) {     
		 MOAIGfxDevice::Get ().SetVertexFormat ( *this->mFormat, this->mBuffer );
		return true;
	}
		return false;
}






//----------------------------------------------------------------//
void MOAIEzraVertexBuffer::Clear () {

this->Reserve ( 0 );
this->mFormat.Set ( *this, 0 );
}

//----------------------------------------------------------------//
u32 MOAIEzraVertexBuffer::GetVertexCount () {

if ( this->mFormat ) {

//PARTICLE_SOUP
//return ( u32 )( this->mStream.GetLength () / this->mFormat->GetVertexSize ());


return ( u32 )( this->mStream.GetLength () );

}
return 0;
}

//----------------------------------------------------------------//
bool MOAIEzraVertexBuffer::IsValid () {

return ( this->mFormat && this->mStream.GetLength ());
}

//----------------------------------------------------------------//
MOAIEzraVertexBuffer::MOAIEzraVertexBuffer () {

RTTI_SINGLE ( MOAIEzraVertexBuffer )

this->mBounds.Init ( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );
}

//----------------------------------------------------------------//
MOAIEzraVertexBuffer::~MOAIEzraVertexBuffer () {

this->Clear ();
}

//----------------------------------------------------------------//
void MOAIEzraVertexBuffer::RegisterLuaClass ( MOAILuaState& state ) {
UNUSED ( state );
}

//----------------------------------------------------------------//
void MOAIEzraVertexBuffer::RegisterLuaFuncs ( MOAILuaState& state ) {

luaL_Reg regTable [] = {
{ "bless",	_bless },
{ "release",	_release },
{ "reserve",	_reserve },
{ "reserveVerts",	_reserveVerts },
{ "reset",	_reset },

{ "setFormat",	_setFormat },
{ "writeColor32",	_writeColor32 },
{ "writeFloat",	_writeFloat },
{ "writeInt8",	_writeInt8 },
{ "writeInt16",	_writeInt16 },
{ "writeInt32",	_writeInt32 },

{ "writeRects",	_writeRects },
{ "writeCircles",	_writeCircles },
{ "writeLines",	_writeLines },
{ "writeRings",	_writeRings },


{ "setCursorZero",	_setCursorZero },
{ "writeGeo",	    _writeGeo },


{ NULL, NULL }
};

luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIEzraVertexBuffer::Reserve ( u32 size ) {
this->mBuffer.Init ( size );
this->mStream.SetBuffer ( this->mBuffer, size );
}


void MOAIEzraVertexBuffer::ReserveV ( long size ) {
    long total = size; 
    this->Reserve ( total * this->mFormat->GetVertexSize ());
  
};



//----------------------------------------------------------------//
void MOAIEzraVertexBuffer::Unbind () {

if ( this->mFormat ) {
MOAIGfxDevice::Get ().SetVertexFormat ();
}
}