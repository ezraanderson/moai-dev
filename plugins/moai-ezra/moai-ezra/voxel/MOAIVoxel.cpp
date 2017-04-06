#include "pch.h"

#include <math.h>
#include <moai-ezra/voxel/MOAIVoxel.h>
#include <moai-ezra/voxel/Perlin.h>
#include <moai-ezra/voxel/FractalNoise.h>



vector3D::vector3D(int xIn, int yIn, int zIn)
{
	x= xIn;
	y=yIn;
	z=zIn;
}


bool Block::IsActive()
{
 return m_active;
}

void Block::SetActive(bool active)
{
 m_active = active;
}


//CLASS
int MOAIVoxel::_classHello ( lua_State* L ) {
	UNUSED ( L );
	return 0;
}

//----------------------------------------------------------------//
//RENDER CUBE
void MOAIVoxel::makeCube(int x,int y,int z,int cnt )
{

	
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    float a = 1.0f;



if ((cnt > 1) && (cnt < (CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE+1))) {	
	
	start_x =x-Block::BLOCK_RENDER_SIZE;
	start_y =y+Block::BLOCK_RENDER_SIZE;
	start_z =z+Block::BLOCK_RENDER_SIZE;

	this->mVbo->writeData(end_x,end_y,end_z,0,0,0,0,0,0);
	this->mVbo->writeData(start_x,start_y,start_z,0,0,0,0,0,0);
}

//1
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,0,0,r,g,b,a);
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,0,1,r,g,b,a);
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,1,0,r,g,b,a);
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,0,1,r,g,b,a);
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,1,1,r,g,b,a);
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,1,0,r,g,b,a);


//end_x =x+Block::BLOCK_RENDER_SIZE;
//end_y =y+Block::BLOCK_RENDER_SIZE;
//end_z =z+Block::BLOCK_RENDER_SIZE;


//2
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,0,0,r,g,b,a);
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,0,1,r,g,b,a);
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,1,0,r,g,b,a);
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,0,1,r,g,b,a);
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,1,1,r,g,b,a);
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,1,0,r,g,b,a);

//3
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,0,0,r,g,b,a);
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,0,1,r,g,b,a);
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,1,0,r,g,b,a);
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,0,1,r,g,b,a);
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,1,1,r,g,b,a);
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,1,0,r,g,b,a);

//4
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,0,0,r,g,b,a);
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,0,1,r,g,b,a);
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,1,0,r,g,b,a);
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,0,1,r,g,b,a);
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,1,1,r,g,b,a);
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,1,0,r,g,b,a);

//5
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,0,0,r,g,b,a);
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,0,1,r,g,b,a);
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,1,0,r,g,b,a);
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,0,1,r,g,b,a);
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,1,1,r,g,b,a);
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y+Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,1,0,r,g,b,a);


//6
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,0,0,r,g,b,a);
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,0,1,r,g,b,a);
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,1,0,r,g,b,a);
this->mVbo->writeData(x-Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,0,1,r,g,b,a);
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z-Block::BLOCK_RENDER_SIZE,1,1,r,g,b,a);
this->mVbo->writeData(x+Block::BLOCK_RENDER_SIZE,y-Block::BLOCK_RENDER_SIZE,z+Block::BLOCK_RENDER_SIZE,1,0,r,g,b,a);


end_x =x+Block::BLOCK_RENDER_SIZE;
end_y =y-Block::BLOCK_RENDER_SIZE;
end_z =z+Block::BLOCK_RENDER_SIZE;





}
//----------------------------------------------------------------//
//CREATE MESH


int MOAIVoxel::_makeMesh ( lua_State* L ) {

MOAI_LUA_SETUP ( MOAIVoxel, "U" ) 


bool lDefault = false;

self->mVbo->reset();
self->mVbo->setCursor(0);
self->cnt = 0;


//MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
//const ZLFrustum& viewVolume = gfxDevice.GetViewVolume ();
// viewVolume.mAABB(

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {

			 	  self->m_pBlocks[x][y][z].SetActive(true);
				 

				  //self->m_pBlocks[x][y][z].SetActive(false);
				  //if (sqrt((float) (x-CHUNK_SIZE/2)*(x-CHUNK_SIZE/2) + (y-CHUNK_SIZE/2)*(y-CHUNK_SIZE/2) + (z-CHUNK_SIZE/2)*(z-CHUNK_SIZE/2)) <= CHUNK_SIZE/2)
				  //{
						//self->m_pBlocks[x][y][z].SetActive(true);
				  //}
			}
		}
	}


	self->inca=self->inca+1;


    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {			
				++self->cnt;

			    bool lXNegative = lDefault;
				if(x > 0)
					lXNegative = self->m_pBlocks[x-1][y][z].IsActive();

				bool lXPositive = lDefault;
				if(x < CHUNK_SIZE - 1)
					lXPositive = self->m_pBlocks[x+1][y][z].IsActive();

				bool lYNegative = lDefault;
				if(y > 0)
					lYNegative = self->m_pBlocks[x][y-1][z].IsActive();

				bool lYPositive = lDefault;
				if(y < CHUNK_SIZE - 1)
					lYPositive = self->m_pBlocks[x][y+1][z].IsActive();

				bool lZNegative = lDefault;
				if(z > 0)
					lZNegative =self-> m_pBlocks[x][y][z-1].IsActive();

				bool lZPositive = lDefault;
				if(z < CHUNK_SIZE - 1)
					lZPositive = self->m_pBlocks[x][y][z+1].IsActive();

				if (lXNegative == true  &&  lXPositive == true && lYNegative == true &&  lYPositive ==  true && lZNegative == true && lZPositive ==true) {
					continue;
				}

                if(self->m_pBlocks[x][y][z].IsActive() == false)
                {           
                    continue;
				}



                //self->makeCube(x*2, self->noiseArray[x][y][z]*2,z*2,cnt);
				//printf("%d",3+inca);

				int xx= (x) + self->gridX;
				int yy= (y) + self->gridY;
				int zz= (z) + self->gridZ;

				self->makeCube((xx)*(2), (yy)*(2),(zz)*(2),self->cnt);
            }
        }
    }

 //self->makeCube(1,1,1);
return 0;
}


//***************************************************************************
int MOAIVoxel::_setVbo (lua_State* L) {
MOAI_LUA_SETUP ( MOAIVoxel, "U" )
self->mVbo = state.GetLuaObject < MOAIVertexBuffer >(2, true );
}
//***************************************************************************
int MOAIVoxel::_setGrid (lua_State* L) {
MOAI_LUA_SETUP ( MOAIVoxel, "UNNN" )		

self->gridX = state.GetValue < int >( 2, 0 );
self->gridY = state.GetValue < int >( 3, 0 );
self->gridZ = state.GetValue < int >( 4, 0 );


}


//----------------------------------------------------------------//
//MAKE VOXEL
int MOAIVoxel::_makeChunk ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxel, "U" ) 
   
	self->inca = 0;
    self->m_pBlocks = new Block**[CHUNK_SIZE];
    for(int i = 0; i < CHUNK_SIZE; i++)
    {
		self->m_pBlocks[i] = new Block*[CHUNK_SIZE];
        for(int j = 0; j < CHUNK_SIZE; j++)
        {
			self->m_pBlocks[i][j] = new Block[CHUNK_SIZE];
        }
    }

	//printf("DONE \n");

	return 0;
};


//**************************************************************
int MOAIVoxel::_makeNoise ( lua_State* L ) {

	MOAI_LUA_SETUP ( MOAIVoxel, "U" ) 

// Generate a noise value for each pixel
	int width  = CHUNK_SIZE;
	int height = CHUNK_SIZE;
	int depth  = CHUNK_SIZE;

	//// Initialize noise generator
	//FractalNoise *noiseMaker = new FractalNoise();	 

	//  self->noiseArray.resize(height);
	//  for (int i = 0; i < height; ++i) {
	//	self->noiseArray[i].resize(width);
	//		for (int j = 0; j < width; ++j){
	//			 self->noiseArray[i][j].resize(depth);
	//		}
	//  }    


	//float invWidth  = 1.0f / float(width);
	//float invHeight = 1.0f / float(height);
	//float invDeepth = 1.0f / float(depth);

	//float noise;
	//float min = 1;
	//float max = 1;
	//float temp = 1.0f / (max - min);

	//for (int x=0; x<width; ++x) for (int y=0; y<height; ++y) for (int z=0; z<height; ++z) {

	//	noise = noiseMaker->noise(float(x)*invWidth, float(y)*invHeight,0.72);
	//	self->noiseArray[x][y][z] = floor(noise*100);

	//	// Keep track of minimum and maximum noise values
	//	if (noise < min) min = noise;
	//	if (noise > max) max = noise;
	//}

	return 0;
};

//----------------------------------------------------------------//
MOAIVoxel::MOAIVoxel () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )	
		RTTI_END
}

//----------------------------------------------------------------//
MOAIVoxel::~MOAIVoxel () {
}

//----------------------------------------------------------------//
void MOAIVoxel::RegisterLuaClass ( MOAILuaState& state ) {
	// here are the class methods:
	luaL_Reg regTable [] = {
		{ "classHello",		_classHello },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIVoxel::RegisterLuaFuncs ( MOAILuaState& state ) {



	// here are the instance methods:
	luaL_Reg regTable [] = {
		{ "makeChunk",	_makeChunk },
		{ "makeMesh",	_makeMesh },
		{ "makeNoise",	_makeNoise },
		{ "setVbo",		_setVbo },
		{ "setGrid",	_setGrid },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

