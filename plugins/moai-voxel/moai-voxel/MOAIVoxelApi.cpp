//ADD UNIT DEGREE MOD

#include "pch.h"
#include <moai-voxel/MOAIVoxelApi.h>

#include <stdint.h>

//#include <PolyVox/CubicSurfaceExtractorWithNormals.h>
//#include <PolyVox/MarchingCubesSurfaceExtractor.h>
//#include <PolyVox/SurfaceMesh.h>
//#include <PolyVox/SimpleVolume.h>
//#include <PolyVox/MaterialDensityPair.h>
//#include <PolyVox/LargeVolume.h>
//#include <PolyVox/Perlin.h>
//
//#include <PolyVox/MeshDecimator.h>


#include <moai-sim/MOAIIndexBuffer.h>
#include <moai-sim/MOAIVertexBuffer.h>

#ifdef MOAI_OS_WINDOWS
#define GLEW_STATIC
#include <gl/glew.h>
#endif

using namespace std;
//using namespace PolyVox;

const int32_t g_uVolumeSideLength = 128;

void start(){
	
}


int MOAIVoxelApi::_getVBO ( lua_State* L ) {
printf("MOAIVoxelApi:Start \n");
return 1;
};



int MOAIVoxelApi::_setVBO ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIVoxelApi, "U" )
self->vBuffer = state.GetLuaObject < MOAIVertexBuffer >(2, true );
return 0;
};

int MOAIVoxelApi::_setIBO ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIVoxelApi, "U" )
self->iBuffer = state.GetLuaObject < MOAIIndexBuffer >(2, true );
return 0;
};

int MOAIVoxelApi::_setShader(lua_State* L) {
MOAI_LUA_SETUP(MOAIVoxelApi, "U")
printf("SET SHADER\n");
self->shader = state.GetLuaObject < MOAIShader >(2, true);
return 0;
};

//
//void MOAIVoxelApi::createSphereInVolume(PolyVox::SimpleVolume<uint8_t>& volData, float fRadius)
//{
//        //This vector hold the position of the center of the volume
//        Vector3DFloat v3dVolCenter(volData.getWidth() / 2, volData.getHeight() / 2, volData.getDepth() / 2);
//
//        //This three-level for loop iterates over every voxel in the volume
//        for (int z = 0; z < volData.getDepth(); z++)
//        {
//                for (int y = 0; y < volData.getHeight(); y++)
//                {
//                        for (int x = 0; x < volData.getWidth(); x++)
//                        {
//                                //Store our current position as a vector...
//                                Vector3DFloat v3dCurrentPos(x,y,z);
//                                //And compute how far the current position is from the center of the volume
//                                float fDistToCenter = (v3dCurrentPos - v3dVolCenter).length();
//
//                                uint8_t uVoxelValue = 0;
//
//                                //If the current voxel is less than 'radius' units from the center then we make it solid.
//                                if(fDistToCenter <= fRadius)
//                                {
//                                        //Our new voxel value
//                                        uVoxelValue = 1;
//                                }
//
//                                //Wrte the voxel value into the volume
//                                volData.setVoxelAt(x, y, z, uVoxelValue);
//                        }
//                }
//        }
//};
//
////**************************************************************************************************************************
//void  MOAIVoxelApi::createPerlinVolumeSlow(LargeVolume<MaterialDensityPair44>& volData)
//{
//  Perlin perlin(2,8,1,234);
//
//  for(int z = 1; z < 256-1; z++)
//  {
//    std::cout << z << std::endl;
//    for(int y = 1; y < 256-1; y++)
//    {
//      for(int x = 1; x < 256-1; x++)
//      {              
//        float perlinVal = perlin.Get3D(x /static_cast<float>(256-1), (y) / static_cast<float>(256-1), z / static_cast<float>(256-1));
//
//        perlinVal += 1.0f;
//        perlinVal *= 0.5f;
//        perlinVal *= MaterialDensityPair44::getMaxDensity();
//
//        MaterialDensityPair44 voxel;
//
//        voxel.setMaterial(245);
//        voxel.setDensity(perlinVal);
//
//        if(perlinVal < 0.0f)
//        {
//			  voxel.setMaterial(245);
//			  voxel.setDensity(MaterialDensityPair44::getMaxDensity());
//        }
//        else
//        {
//			  voxel.setMaterial(0);
//			  voxel.setDensity(MaterialDensityPair44::getMinDensity());
//        }
//
//        //volData.setVoxelAt(x, y, z, voxel);
//      }
//    }
//  }
//}
//
////**************************************************************************************************************************
//void createCubeInVolume(LargeVolume<MaterialDensityPair44>& volData, Vector3DInt32 lowerCorner, Vector3DInt32 upperCorner, uint8_t uValue)
//{
//  uint8_t maxDen = MaterialDensityPair44::getMaxDensity();
//  uint8_t minDen = MaterialDensityPair44::getMinDensity();
//  //This three-level for loop iterates over every voxel between the specified corners
//  for (int z = lowerCorner.getZ(); z <= upperCorner.getZ(); z++)
//  {
//    for (int y = lowerCorner.getY(); y <= upperCorner.getY(); y++)
//    {
//      for (int x = lowerCorner.getX() ; x <= upperCorner.getX(); x++)
//      {
//      //  volData.setVoxelAt(x,y,z, MaterialDensityPair44(uValue, uValue > 0 ? maxDen : minDen));
//      }
//    }
//  }
//}
//
//
////**************************************************************************************************
////**************************************************************************************************
////**************************************************************************************************
////**************************************************************************************************
//void loadSphere(const ConstVolumeProxy<MaterialDensityPair44>& volume,const PolyVox::Region& reg)
//{
//     //This vector hold the position of the center of the volume
//        Vector3DFloat v3dVolCenter(reg.getWidthInCells () / 2, reg.getHeightInCells() / 2, reg.getDepthInCells() / 2);
//		float fRadius = 30;
//        //This three-level for loop iterates over every voxel in the volume
//		  for(int z = reg.getLowerCorner().getZ(); z <= reg.getUpperCorner().getZ(); z++)
//		  {
//			for(int x = reg.getLowerCorner().getX(); x <= reg.getUpperCorner().getX(); x++)
//			{
//			  for(int y = reg.getLowerCorner().getY(); y <= reg.getUpperCorner().getY(); y++)
//			  {
//                            
//                    Vector3DFloat v3dCurrentPos(x,y,z);                      
//                    float fDistToCenter = (v3dCurrentPos - v3dVolCenter).length();
//					MaterialDensityPair44 voxel;
//					voxel.setMaterial(245);
//					voxel.setDensity(MaterialDensityPair44::getMaxDensity());
//
//                    if(fDistToCenter <= fRadius)
//                    {
//                              
//							voxel.setMaterial(0);
//							voxel.setDensity(MaterialDensityPair44::getMinDensity());
//                    };
//
//                  
//					//printf("%d %d %d \n",x, y, z);
//					volume.setVoxelAt(x, y, z, voxel);
//                        }
//                }
//        }
//}
////**************************************************************************************************
////**************************************************************************************************
////**************************************************************************************************
//void load(const ConstVolumeProxy<MaterialDensityPair44>& volume, const PolyVox::Region& reg)
//{ 	
//  Perlin perlin(2,2,1,234);
//  for(int z = reg.getLowerCorner().getZ(); z <= reg.getUpperCorner().getZ(); z++)
//  {
//    for(int x = reg.getLowerCorner().getX(); x <= reg.getUpperCorner().getX(); x++)
//    {
//      float perlinVal = perlin.Get(x / static_cast<float>(255-1), z / static_cast<float>(255-1));
//      perlinVal += 1.0f;
//      perlinVal *= 0.5f;
//      perlinVal *= 255;
//
//      for(int y = reg.getLowerCorner().getY(); y <= reg.getUpperCorner().getY(); y++)
//      {
//        MaterialDensityPair44 voxel;
//
//        if(y < perlinVal)
//        {
//			voxel.setMaterial(245);
//			voxel.setDensity(MaterialDensityPair44::getMaxDensity());
//   
//        }
//        else
//        {
//          voxel.setMaterial(0);
//          voxel.setDensity(MaterialDensityPair44::getMinDensity());
//        }
//
//        volume.setVoxelAt(x, y, z, voxel);
//      }
//    }
//  }
//}
//
//void unload(const ConstVolumeProxy<MaterialDensityPair44>& , const PolyVox::Region& reg)
//{
//  std::cout << "unloading region: " << reg.getLowerCorner() << " -> " << reg.getUpperCorner() << std::endl;
//}



//
//
//int MOAIVoxelApi::_start ( lua_State* L ) {
//MOAI_LUA_SETUP ( MOAIVoxelApi, "U" )
//
//
//printf("MOAIVoxelApi:Start \n");
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////SurfaceMesh<PositionMaterialNormal> mesh;
////SimpleVolume<uint8_t> volData(PolyVox::Region(Vector3DInt32(0,0,0), Vector3DInt32(63, 63, 63)));
////self->createSphereInVolume(volData, 30);
////CubicSurfaceExtractorWithNormals< SimpleVolume<uint8_t> > surfaceExtractor(&volData, volData.getEnclosingRegion(), &mesh);
////surfaceExtractor.execute();
//
//
//
//
//
//
//
//
////**************************************************************************************************************************************************************
////**************************************************************************************************************************************************************
////**************************************************************************************************************************************************************
////**************************************************************************************************************************************************************
////**************************************************************************************************************************************************************
//
//
////LargeVolume<MaterialDensityPair44> volData(PolyVox::Region(Vector3DInt32(0,0,0), Vector3DInt32(g_uVolumeSideLength-1, g_uVolumeSideLength-1, g_uVolumeSideLength-1)));
////polyvox_shared_ptr< SurfaceMesh<PositionMaterialNormal> > mesh(new SurfaceMesh<PositionMaterialNormal>);
////
////
////int32_t minPos = 0;
////int32_t midPos = g_uVolumeSideLength / 2;
////int32_t maxPos = g_uVolumeSideLength - 1;
////
////cout << "Creating sphere 1" << std::endl;
////self->createSphereInVolumeB(volData,  30.0f, 1);
////
////int32_t regionStartX = 1;
////int32_t regionStartY = 1;
////int32_t regionStartZ = 1;
////	
////int32_t regionEndX = regionStartX + 100;
////int32_t regionEndY = regionStartY + 100;
////int32_t regionEndZ = regionStartZ + 100;
////
////Vector3DInt32 regLowerCorner(regionStartX, regionStartY, regionStartZ);
////Vector3DInt32 regUpperCorner(regionEndX, regionEndY, regionEndZ);
////
////createCubeInVolume(volData, Vector3DInt32(minPos, minPos, minPos), Vector3DInt32(midPos-1, midPos-1, midPos-1), 0);
////
////MarchingCubesSurfaceExtractor< LargeVolume<MaterialDensityPair44> > surfaceExtractor(&volData, PolyVox::Region(regLowerCorner, regUpperCorner), mesh.get());
////surfaceExtractor.execute();
//// const SurfaceMesh<PositionMaterialNormal>& meshB = *mesh.get();
////
//
//
//
//
//
//
//
////*****************************************************************************************************************************************************
////*****************************************************************************************************************************************************
////*****************************************************************************************************************************************************
////*****************************************************************************************************************************************************
//
//
//
// //
// // LargeVolume<MaterialDensityPair44> volData(&loadSphere, &unload, 64);
// //// LargeVolume<MaterialDensityPair44> volData(&load, &unload, 256);
//
// // volData.setMaxNumberOfBlocksInMemory(4096);
// // volData.setMaxNumberOfUncompressedBlocks(256);
// // volData.setCompressionEnabled(true);
//
// // std::cout << "Memory usage: " << (volData.calculateSizeInBytes()/1024.0/1024.0) << "MB" << std::endl;
// // std::cout << "Compression ratio: 1 to " << (1.0/(volData.calculateCompressionRatio())) << std::endl;
// // 
// // PolyVox::Region reg1(Vector3DInt32(0,0,0), Vector3DInt32(63,63,63));  
// // std::cout << "Size in voxels: "	 << reg1.getWidthInVoxels() << "x" << reg1.getHeightInVoxels() <<   "x" << reg1.getDepthInVoxels() << std::endl;
// // std::cout << "Prefetching region: " << reg1.getLowerCorner() << " -> " << reg1.getUpperCorner() << std::endl;
// // volData.prefetch(reg1);
//
//
//
// 
//  
//  //PolyVox::Region reg2(Vector3DInt32(0,0,0), Vector3DInt32(255,255,255));
//  //std::cout << "Flushing region: " << reg2.getLowerCorner() << " -> " << reg2.getUpperCorner() << std::endl;
//  //volData.flush(reg2);
//
//  //std::cout << "Memory usage: " << (volData.calculateSizeInBytes()/1024.0/1024.0) << "MB" << std::endl;
//  //std::cout << "Compression ratio: 1 to " << (1.0/(volData.calculateCompressionRatio())) << std::endl;
//  //std::cout << "Flushing entire volume" << std::endl;
//
//
//  //volData.flushAll();
//  //std::cout << "Memory usage: " << (volData.calculateSizeInBytes()/1024.0/1024.0) << "MB" << std::endl;
//  //std::cout << "Compression ratio: 1 to " << (1.0/(volData.calculateCompressionRatio())) << std::endl;
//
//
//
////
////  SurfaceMesh<PositionMaterialNormal> mesh;
////
////
////  CubicSurfaceExtractorWithNormals< LargeVolume<MaterialDensityPair44> > surfaceExtractor(&volData, reg1, &mesh);
////  surfaceExtractor.execute();
////
////
//////*************************************************************************************************************************************
//////*************************************************************************************************************************************
//////*************************************************************************************************************************************
//////*************************************************************************************************************************************
//////*************************************************************************************************************************************
////
////
////
////
//// const vector<uint32_t>& vecIndices					= mesh.getIndices();
//// const vector<PositionMaterialNormal>& vecVertices  = mesh.getVertices();
////
////	printf("index %d  \n",vecIndices.size());
////	self->iBuffer->ReserveIndices(vecIndices.size());
////	for (int i=0; i < vecIndices.size(); i++) {
////			self->iBuffer->SetIndex(i,vecIndices[i]);
////	};
////
////
////	printf("vertic %d \n", vecVertices.size());
////	self->vBuffer->ReserveVerts(mesh.getNoOfVertices());
////
////	int cnt;
////	cnt = 0;
////
////	for (int i=0; i < vecVertices.size(); i++) {
////			self->vBuffer->writeVert(vecVertices[i].getPosition().getX(),vecVertices[i].getPosition().getY(),vecVertices[i].getPosition().getZ());
////			self->vBuffer->writeNormal((vecVertices[i].getNormal().getX()),(vecVertices[i].getNormal().getY()),(vecVertices[i].getNormal().getZ()));
////
////		//	printf("%f %f %f \n ",vecVertices[i].getNormal().getX(),vecVertices[i].getNormal().getY(),vecVertices[i].getNormal().getZ());
////			
////				//++cnt;
////				//if (cnt == 1) self->vBuffer->writeUV(0,0);
////				//if (cnt == 2) self->vBuffer->writeUV(0,1);
////				//if (cnt == 3) self->vBuffer->writeUV(1,1);
////				//if (cnt == 4) self->vBuffer->writeUV(1,0);
////				//if (cnt == 4) cnt = 0;
////	};
////
////
//
//
//
//return 0;
//};
//



//******************************************************************************************************************************************************
//******************************************************************************************************************************************************
//******************************************************************************************************************************************************
//******************************************************************************************************************************************************
//******************************************************************************************************************************************************
//******************************************************************************************************************************************************
//******************************************************************************************************************************************************
//******************************************************************************************************************************************************
//******************************************************************************************************************************************************
//******************************************************************************************************************************************************
//******************************************************************************************************************************************************
//******************************************************************************************************************************************************




//GLuint voxel_front;
//GLuint voxel_offset;
//GLuint voxel_color;

int MOAIVoxelApi::_start(lua_State* L) {
	MOAI_LUA_SETUP(MOAIVoxelApi, "U")

		printf("MOAIVoxelApi:Start \n");


		//glGenBuffers(1, &voxel_front); // ORGINAL : Generate 1 buffer

		//glGenBuffers(1, &voxel_offset); // OFFSET : Generate 1 buffer

		//glGenBuffers(1, &voxel_color); //COLOR : Generate 1 buffer
};



//*********************************************************************************
//STATIC_FRONT : ORGINAL
int MOAIVoxelApi::_static(lua_State* L) {
	MOAI_LUA_SETUP(MOAIVoxelApi, "U")

	//static const GLfloat g_vertex_buffer_data[] = {
	//-0.5f, -0.5f, 0.0f,
	// 0.5f, -0.5f, 0.0f,
	//-0.5f, 0.5f, 0.0f,
	// 0.5f, 0.5f, 0.0f,
	//};

	//glBindBuffer(GL_ARRAY_BUFFER, voxel_front);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//static const GLfloat g_vertex_buffer_data[] = {
	//	-0.5f, -0.5f,
	//	0.5f, -0.5f, 
	//	-0.5f, 0.5f, 
	//	0.5f, 0.5f, 
	//};

	//glBindBuffer(GL_ARRAY_BUFFER, voxel_front);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	return 0;
};





int MOAIVoxelApi::_update(lua_State* L) {
	MOAI_LUA_SETUP(MOAIVoxelApi, "U")


//****************************************************************************************
//OFFSET
//float offset[] = {
//		0, 4, 0,
//		0, 2, 0,
//		0, 0, 0,
//		0, -2, 0,
//		0, -4, 0,
//	};
//
//
//		glBindBuffer(GL_ARRAY_BUFFER, voxel_offset);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(offset)*sizeof(GLfloat), NULL, GL_STREAM_DRAW);
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(offset)*sizeof(GLfloat), offset);

//****************************************************************************************
//COLORS

		//float colors[] = {
		//	1, 0, 0, 1,
		//	0, 1, 0, 1,
		//	0, 0, 1, 1,
		//	0, 1, 1, 1,
		//	1, 1, 0, 1,
		//};

		//glBindBuffer(GL_ARRAY_BUFFER, voxel_color);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(colors) * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
		//glEnableVertexAttribArray(2);
		//glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, 0, (void*)0);
		//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors) * sizeof(GLfloat), colors);


//***********************************************************************************************
////DRAW
//		int obj_cnt = 5;
//
//		//ENABLE
//					glVertexAttribDivisor(0, 0);   // ORGINAL
//					glVertexAttribDivisor(1, 1);   // OFFSET FROM CENTER
//							//glVertexAttribDivisor(2, 1); // COLOR PER SIDE/QUAD
//
//		//DRAW
//					glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, obj_cnt);
//
//		//DISABLE
//					glDisableVertexAttribArray(0);
//					glDisableVertexAttribArray(1);
//							//glDisableVertexAttribArray(2);



		return 0;
};




//----------------------------------------------------------------//
MOAIVoxelApi::MOAIVoxelApi () :
mEnabled ( false )

{

	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END

}

//----------------------------------------------------------------//
MOAIVoxelApi::~MOAIVoxelApi () {

}

//----------------------------------------------------------------//
void MOAIVoxelApi::RegisterLuaClass ( MOAILuaState& state ) {
}

//----------------------------------------------------------------//
void MOAIVoxelApi::RegisterLuaFuncs ( MOAILuaState& state ) {

	// here are the instance methods:
	luaL_Reg regTable [] = {

		{ "start",			_start },
		{ "getVBO",			_getVBO },
		{ "setVBO",			_setVBO },
		{ "setIBO",			_setIBO },
		{ "setShader",		_setShader },
		{ "update",			_update },
		{ "static",			_static },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

