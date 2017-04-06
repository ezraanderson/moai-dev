// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIGfxDevice.h>
#include <moai-sim/MOAIGrid.h>
#include <moai-sim/MOAIIndexBuffer.h>
#include <moai-sim/MOAIProp.h>
#include <moai-sim/MOAIShader.h>
#include <moai-sim/MOAIShaderMgr.h>
#include <moai-sim/MOAITextureBase.h>
#include <moai-sim/MOAIVertexBuffer.h>
#include <moai-sim/MOAIVertexFormat.h>

#include <MOAIVoxelMesh.h>

#ifdef MOAI_OS_WINDOWS
#define GLEW_STATIC
#include <gl/glew.h>
#endif


GLuint voxel_vert;
GLuint voxel_offset;
GLuint voxel_color;
GLuint voxel_uv;
GLuint voxel_normal;
GLuint voxel_index;

int const box = 10;
int const INSTANCE_COUNT = box * box * box;
int const INSTANCE_HIGH = INSTANCE_COUNT * 3+2;

float offset[INSTANCE_HIGH];
uint color[INSTANCE_COUNT];







//static const GLfloat g_vertex_buffer_data[] = {
//	// Front face
//	-1, -1, 1,   1, -1, 1,   -1, 1, 1,   1, 1, 1,
//	// Right face
//	1, -1, 1,   1, -1, -1,   1, 1, 1,   1, 1, -1,
//	// Back face
//	1, -1, -1,   -1, -1, -1,   1, 1, -1,   -1, 1, -1,
//	// Left face
//	-1, -1, -1,   -1, -1, 1,   -1, 1, -1,   -1, 1, 1,
//	// Bottom face
//	-1, -1, -1,   1, -1, -1,   -1, -1, 1,   1, -1, 1,
//	// Top face
//	-1, 1, 1,   1, 1, 1,   -1, 1, -1,     1, 1, -1
//};


//static const GLfloat g_vertex_buffer_data[] = {
//	// Front face
//	-0.5, -0.5, 0.5,   0.5, -0.5, 0.5,   -0.5, 0.5, 0.5,   0.5, 0.5, 0.5,
//	// Right face
//	0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5,
//	// Back face
//	0.5, -0.5, -0.5, -0.5, -0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, -0.5,
//	// Left face
//	-0.5, -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, 0.5, -0.5, -0.5, 0.5, 0.5,
//	// Bottom face
//	-0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5,
//	// Top face
//	-0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5
//};

//static const GLfloat g_uv_buffer_data[] = {
//	// Front face
//	0, 0,  1, 0,  0, 1,   1, 1,
//	// Right face
//	0, 0, 1, 0, 0, 1, 1, 1,
//	// Back face
//	0, 0, 1, 0, 0, 1, 1, 1,
//	// Left face
//	0, 0, 1, 0, 0, 1, 1, 1,
//	// Bottom face
//	0, 0, 1, 0, 0, 1, 1, 1,
//	// Top face
//	0, 0, 1, 0, 0, 1, 1, 1
//};
//

//*********************************************************************************************************************
//*********************************************************************************************************************
//*********************************************************************************************************************
//*********************************************************************************************************************
//*********************************************************************************************************************

	/*	static const GLfloat g_vertex_buffer_data[] = {
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f,

			 0.5f, 0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, 0.5f, -0.5f,

			0.5f, -0.5f, 0.5f,
			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,

			0.5f, 0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,


			-0.5f, -0.5f, -0.5f,
			-0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, -0.5f,
			0.5f, -0.5f, 0.5f,
			-0.5f, -0.5f, 0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, 0.5f, 0.5f,
			-0.5f, -0.5f, 0.5f,
			0.5f, -0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, 0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, 0.5f, 0.5f,
			0.5f, -0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,
			0.5f, 0.5f, -0.5f,
			-0.5f, 0.5f, -0.5f,
			0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, -0.5f,
			-0.5f, 0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f,
			0.5f, -0.5f, 0.5f
		};
*/


		/*static const GLfloat g_uv_buffer_data[] = {
			0.0f, 0.0f ,

			0.000000f, 1.0f - 0.336048f,

			0.335973f, 1.0f - 0.335903f,
			1.000023f, 1.0f - 0.000013f,

			0.667979f, 1.0f - 0.335851f,
			0.999958f, 1.0f - 0.336064f,

			0.667979f, 1.0f - 0.335851f,
			0.336024f, 1.0f - 0.671877f,

			0.667969f, 1.0f - 0.671889f,
			1.000023f, 1.0f - 0.000013f,
			0.668104f, 1.0f - 0.000013f,
			0.667979f, 1.0f - 0.335851f,
			0.000059f, 1.0f - 0.000004f,
			0.335973f, 1.0f - 0.335903f,
			0.336098f, 1.0f - 0.000071f,
			0.667979f, 1.0f - 0.335851f,
			0.335973f, 1.0f - 0.335903f,
			0.336024f, 1.0f - 0.671877f,
			1.000004f, 1.0f - 0.671847f,
			0.999958f, 1.0f - 0.336064f,
			0.667979f, 1.0f - 0.335851f,
			0.668104f, 1.0f - 0.000013f,
			0.335973f, 1.0f - 0.335903f,
			0.667979f, 1.0f - 0.335851f,
			0.335973f, 1.0f - 0.335903f,
			0.668104f, 1.0f - 0.000013f,
			0.336098f, 1.0f - 0.000071f,
			0.000103f, 1.0f - 0.336048f,
			0.000004f, 1.0f - 0.671870f,
			0.336024f, 1.0f - 0.671877f,
			0.000103f, 1.0f - 0.336048f,
			0.336024f, 1.0f - 0.671877f,
			0.335973f, 1.0f - 0.335903f,
			0.667969f, 1.0f - 0.671889f,
			1.000004f, 1.0f - 0.671847f,
			0.667979f, 1.0f - 0.335851f
		};
*/









////*********************************************************************************************************************
////*********************************************************************************************************************
////*********************************************************************************************************************
////*********************************************************************************************************************
////*********************************************************************************************************************
///COLORS NO TEXTURE

	/*	static const GLfloat g_vertex_buffer_data[] = {
			-0.5, -0.5, 0.5,
			 0.5, -0.5, 0.5,
			-0.5, 0.5, 0.5,
			 0.5, 0.5, 0.5,

			-0.5, -0.5, -0.5,
			0.5, -0.5, -0.5,
			-0.5, 0.5, -0.5,
			0.5, 0.5, -0.5,
		};



		static const GLushort g_indexs_buffer_data[] = {
			0,1,2, 
			3,7,1, 

			5,4,7, 
			6,2,4,			

			0, 1
		}; 
*/


		//static const GLfloat g_uv_buffer_data[] = {
		//	0.0, 0.0,
		//	0.0, 1,
		//
		//	1, 1,
		//	1, 0.0,
		//
		//	0.0,1,
		//	1, 1,
		//
		//	0.0, 1.0,
		//	1, 1.0,
		//};

////*********************************************************************************************************************
////*********************************************************************************************************************
////*********************************************************************************************************************
////*********************************************************************************************************************
////*********************************************************************************************************************
//
//
//static const GLushort g_indexs_buffer_data[] = {
//	0, 1, 2,
//	0, 2, 3,
//
//	1, 5, 6,
//	1, 6, 2,
//
//	2, 6, 7,
//	2, 7, 3,
//
//	3, 4, 0,
//	3, 7, 4,
//
//	4, 5, 1,
//	4, 1, 0,
//
//	5, 7, 6,
//	5, 4, 7,
//};
//
//
//
//
//
//static const GLfloat g_vertex_buffer_data[] = {
//// front square vertices
//-0.5, -0.5, 0.5,
//0.5, -0.5, 0.5,
//0.5, 0.5, 0.5,
//-0.5, 0.5, 0.5,
//// back square vertices
//-0.5, -0.5, -0.5,
//0.5, -0.5, -0.5,
//0.5, 0.5, -0.5,
//-0.5, 0.5, -0.5,
//};
//
//
//
//
//
//static const GLfloat g_normal_buffer_data[] = {
//0, 0, 1,
//0, 0, 1,
//0, 1, 0,
//1, 0, 0,
//0, 1, 0,
//0, 0, 1,
//1, 0, 0,// can be anything, will not be used
//1, 0, 0//  -- " --
//};







////*********************************************************************************************************************
////*********************************************************************************************************************
////*********************************************************************************************************************
////*********************************************************************************************************************
////*********************************************************************************************************************


//
//static const GLfloat g_vertex_buffer_data[] = {
//	// VO
//	-0.5f, 0.5f, 0.5f,
//	// V1
//	-0.5f, -0.5f, 0.5f,
//	// V2
//	0.5f, -0.5f, 0.5f,
//	// V3
//	0.5f, 0.5f, 0.5f,
//	// V4
//	-0.5f, 0.5f, -0.5f,
//	// V5
//	0.5f, 0.5f, -0.5f,
//	// V6
//	-0.5f, -0.5f, -0.5f,
//	// V7
//	0.5f, -0.5f, -0.5f,
//};
//
//
//





//static const GLfloat g_uv_buffer_data[] = {
//	0.0, 0.0,
//	0.0, 0.5,
//
//	0.5, 0.5,
//	0.5, 0.0,
//
//	0.0, 0.5,
//	0.5, 0.5,
//
//	0.0, 1.0,
//	0.5, 1.0,
//};






//static const GLushort g_indexs_buffer_data[] = {
//		// Front face
//		0, 1, 3, 3, 1, 2,
//		// Top Face
//		4, 0, 3, 5, 4, 3,
//		// Right face
//		3, 2, 7, 5, 3, 7,
//		// Left face
//		0, 1, 6, 4, 0, 6,
//		// Bottom face
//		6, 1, 2, 7, 6, 2,
//		// Back face
//		4, 6, 7, 5, 4, 7,
//};
////
////
////
////


//*********************************************************************************************************************
//*********************************************************************************************************************
//*********************************************************************************************************************
//*********************************************************************************************************************
//*********************************************************************************************************************








//static const GLfloat g_vertex_buffer_data[] = {
//	0.5f, 0.5f, 0.5f,	//0
//	0.5f, 0.5f, -0.5f,	//1
//	0.5f, -0.5f, 0.5f,	//2
//	0.5f, -0.5f, -0.5f,	//3
//	-0.5f, 0.5f, 0.5f,	//4
//	-0.5f, 0.5f, -0.5f,	//5
//	-0.5f, -0.5f, 0.5f,	//6
//	-0.5f, -0.5f, -0.5f,//7
//};
//
//static const GLushort g_indexs_buffer_data[] = {
//		0, 4, 5, 1 ,
//		0, 1, 3, 2 ,
//		0, 2, 6, 4 ,
//		7, 3, 1, 5 ,
//		7, 6, 2, 3 ,
//		7, 5, 4, 6 
//};


//static const GLushort		g_uv_buffer_data[] = {
//		0.0, 0.0 , //0
//		0.0, 1.0 , //1
//		1.0, 0.0 , //2
//		1.0, 1.0 , //3	
//};
//
//






//*********************************************************************************************************************
//*********************************************************************************************************************
//*********************************************************************************************************************
//*********************************************************************************************************************
//*********************************************************************************************************************
//	24

static const GLushort g_indexs_buffer_data[] = {
	0, 1, 2, 0, 2, 3,    // Front face
	4, 5, 6, 4, 6, 7,    // Back face
	8, 9, 10, 8, 10, 11,  // Top face
	12, 13, 14, 12, 14, 15, // Bottom face
	16, 17, 18, 16, 18, 19, // Right face
	20, 21, 22, 20, 22, 23  // Left face
};

//

static const GLfloat g_vertex_buffer_data[] = {
	// Front face
	-0.5, -0.5, 0.5,
	0.5, -0.5, 0.5,
	0.5, 0.5, 0.5,
	-0.5, 0.5, 0.5,
	// Back face
	-0.5, -0.5, -0.5,
	-0.5, 0.5, -0.5,
	0.5, 0.5, -0.5,
	0.5, -0.5, -0.5,
	// Top face
	-0.5, 0.5, -0.5,
	-0.5, 0.5, 0.5,
	0.5, 0.5, 0.5,
	0.5, 0.5, -0.5,
	// Bottom face
	-0.5, -0.5, -0.5,
	0.5, -0.5, -0.5,
	0.5, -0.5, 0.5,
	-0.5, -0.5, 0.5,
	// Right face
	0.5, -0.5, -0.5,
	0.5, 0.5, -0.5,
	0.5, 0.5, 0.5,
	0.5, -0.5, 0.5,
	// Left face
	-0.5, -0.5, -0.5,
	-0.5, -0.5, 0.5,
	-0.5, 0.5, 0.5,
	-0.5, 0.5, -0.5
};


static const GLfloat	g_normal_buffer_data[] = {
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
};


static const GLfloat	g_uv_buffer_data[] = {
	// Front face
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,
	// Back face
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,
	0.0, 0.0,
	// Top face
	0.0, 1.0,
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	// Bottom face
	1.0, 1.0,
	0.0, 1.0,
	0.0, 0.0,
	1.0, 0.0,
	// Right face
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,
	0.0, 0.0,
	// Left face
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,

};
























int MOAIVoxelMesh::_glGenBuffers(lua_State* L) {
	MOAI_LUA_SETUP(MOAIVoxelMesh, "U")
	glGenBuffers(1, &voxel_offset); // OFFSET : Generate 1 buffer
	glGenBuffers(1, &voxel_color); //COLOR : Generate 1 buffer
	glGenBuffers(1, &voxel_vert); // ORGINAL : Generate 1 buffer
	glGenBuffers(1, &voxel_uv); //COLOR : Generate 1 buffer
	glGenBuffers(1, &voxel_index); //COLOR : Generate 1 buffer
	glGenBuffers(1, &voxel_normal); //COLOR : Generate 1 buffer

	int cnt = 0;
	for (int x = 0; x < box; x++){
		for (int y = 0; y < box; y++){
		for (int z = 0; z < box; z++){
			offset[cnt * 3 + 0] = x-(x * 3);
			offset[cnt * 3 + 1] = y-(y * 3);
			offset[cnt * 3 + 2] = z-(z * 3);
				int v1 = (rand() % 255 + 1) ;
				//color[cnt] = v1 / 255;
				//color[cnt] = (uint)((255 << 16) |(0 << 8) | (0 << 0));
				//color[cnt] =  256 + 0 * 256.0 + 0 * 256.0 * 256.0;
				//color[cnt] =  60000 + 0 * 256.0 + 0 * 256.0 * 256.0;
				uint pcolor = 0;
				//pcolor |= 0 << 24;
				pcolor |= v1 << 16;
				pcolor |= 0 << 8;
				pcolor |= 0;

				color[cnt] = pcolor;
		

				//printf("%f \n", v1 / 255);
				cnt++;
			
			};
		};
	};

	printf("HIGH CNT %d %d %d\n", INSTANCE_COUNT,cnt,cnt * 4 + 2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, voxel_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indexs_buffer_data), &g_indexs_buffer_data, GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, voxel_vert);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), &g_vertex_buffer_data, GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, voxel_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_normal_buffer_data), &g_normal_buffer_data, GL_STREAM_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, voxel_uv);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), &g_uv_buffer_data, GL_STREAM_DRAW);




	//OFFSETS

	glBindBuffer(GL_ARRAY_BUFFER, voxel_color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), &color, GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, voxel_offset);
	glBufferData(GL_ARRAY_BUFFER, sizeof(offset), &offset, GL_STREAM_DRAW);



	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*INSTANCE_HIGH, offset);



	return 0;
}

//************************************************************************************************
float up = 0.0001;

int MOAIVoxelMesh::_draw(lua_State* L) {
	MOAI_LUA_SETUP(MOAIVoxelMesh, "U")


	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetVertexMtxMode(MOAIGfxDevice::VTX_STAGE_MODEL, MOAIGfxDevice::VTX_STAGE_MODEL);
	gfxDevice.SetUVMtxMode(MOAIGfxDevice::UV_STAGE_MODEL, MOAIGfxDevice::UV_STAGE_TEXTURE);


	gfxDevice.SetGfxState(self->mTexture);
	gfxDevice.SetPenWidth(self->mPenWidth);
	gfxDevice.SetPointSize(self->mPointSize);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);





	//glShadeModel(GL_FLAT);
	//glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
	//glShadeModel(GL_SMOOTH);

	//******************************************************************************************************
	//IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, voxel_index);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indexs_buffer_data), g_indexs_buffer_data, GL_STREAM_DRAW);

	//******************************************************************************************************
	//VERT
	glBindBuffer(GL_ARRAY_BUFFER, voxel_vert);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);



	//******************************************************************************************************
	//NORMAL	
		glBindBuffer(GL_ARRAY_BUFFER, voxel_normal);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(g_normal_buffer_data), g_normal_buffer_data, GL_STREAM_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


	//******************************************************************************************************
	//UV	
	glBindBuffer(GL_ARRAY_BUFFER, voxel_uv);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STREAM_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);





	//glDrawElements(GL_TRIANGLE_STRIP, sizeof(g_vertex_buffer_data), GL_UNSIGNED_SHORT, 0);
	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	//glDrawElements(
	//     GL_TRIANGLES,      // mode
	//	 12,    // count
	//     GL_UNSIGNED_INT,   // type
	//	0           // element array buffer offset
	// );
	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	//******************************************************************************************************
	//glDrawArrays(GL_TRIANGLES,  0,12 * 3);
	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);





	//******************************************************************************************************	
	//OFFSET_COLOR
	glBindBuffer(GL_ARRAY_BUFFER, voxel_color);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*INSTANCE_HIGH, NULL, GL_STREAM_DRAW);
			//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*INSTANCE_HIGH, &offset);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);


	//******************************************************************************************************	
	//OFFSET_POSITION
	glBindBuffer(GL_ARRAY_BUFFER, voxel_offset);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*INSTANCE_HIGH, NULL, GL_STREAM_DRAW);
			//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*INSTANCE_HIGH, &offset);

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);






	////ENABLE
	glVertexAttribDivisor(0, 0);   // ORGINAL
	glVertexAttribDivisor(1, 0);   // UV
	glVertexAttribDivisor(2, 0);   // NORMAL


	glVertexAttribDivisor(3, 1);   // COLOR
	glVertexAttribDivisor(4, 1);   // OFFSET FROM CENTER

	////DRAW
	////glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	////glPolygonMode(GL_FRONT, GL_LINE);
	////glPolygonMode(GL_BACK, GL_LINE);

	//glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 72, INSTANCE_COUNT);

	//glDrawElementsInstanced(GL_TRIANGLE_STRIP, sizeof(g_indexs_buffer_data), GL_UNSIGNED_SHORT, 0, INSTANCE_COUNT);

	glDrawElementsInstanced(GL_TRIANGLES, sizeof(g_indexs_buffer_data), GL_UNSIGNED_SHORT, 0, INSTANCE_COUNT);


	/////DISABLE
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);





	return 0;

}

































//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	setIndexBuffer
	@text	Set the index buffer to render.
	
	@in		MOAIVoxelMesh self
	@in		MOAIIndexBuffer indexBuffer
	@out	nil
*/
int MOAIVoxelMesh::_setIndexBuffer ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelMesh, "U" )
	
	self->mIndexBuffer.Set ( *self, state.GetLuaObject < MOAIIndexBuffer >( 2, true ));

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setPenWidth
	@text	Sets the pen with for drawing prims in this vertex buffer.
			Only valid with prim types GL_LINES, GL_LINE_LOOP, GL_LINE_STRIP.
	
	@in		MOAIVoxelMesh self
	@in		number penWidth
	@out	nil
*/
int MOAIVoxelMesh::_setPenWidth ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelMesh, "UN" )
	
	self->mPenWidth = state.GetValue < float >( 2, 1.0f );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setPointSize
	@text	Sets the point size for drawing prims in this vertex buffer.
			Only valid with prim types GL_POINTS.
	
	@in		MOAIVoxelMesh self
	@in		number pointSize
	@out	nil
*/
int MOAIVoxelMesh::_setPointSize ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelMesh, "UN" )
	
	self->mPointSize = state.GetValue < float >( 2, 1.0f );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setPrimType
	@text	Sets the prim type the buffer represents.
	
	@in		MOAIVoxelMesh self
	@in		number primType		One of MOAIVoxelMesh GL_POINTS, GL_LINES, GL_TRIANGLES, GL_LINE_LOOP,
								GL_LINE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP
	@out	nil
*/
int MOAIVoxelMesh::_setPrimType ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelMesh, "UN" )
	
	self->mPrimType = state.GetValue < u32 >( 2, 0 );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setVertexBuffer
	@text	Set the vertex buffer to render.
	
	@in		MOAIVoxelMesh self
	@in		MOAIVertexBuffer vertexBuffer
	@out	nil
*/
int MOAIVoxelMesh::_setVertexBuffer ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIVoxelMesh, "U" )
	
	self->mVertexBuffer.Set ( *self, state.GetLuaObject < MOAIVertexBuffer >( 2, true ));
	self->SetBoundsDirty ();

	return 0;
}

//================================================================//
// MOAIVoxelMesh
//================================================================//

//----------------------------------------------------------------//
ZLBox MOAIVoxelMesh::ComputeMaxBounds () {
	return this->GetItemBounds ( 0 );
}






//----------------------------------------------------------------//
void MOAIVoxelMesh::DrawIndex ( u32 idx, float xOff, float yOff, float zOff, float xScl, float yScl, float zScl ) {
	UNUSED ( idx );
	UNUSED ( xOff );
	UNUSED ( yOff );
	UNUSED ( zOff );
	UNUSED ( xScl );
	UNUSED ( yScl );
	UNUSED ( zScl );


	//printf("shit \n");

		MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();	
		gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_MODEL, MOAIGfxDevice::VTX_STAGE_MODEL );
		gfxDevice.SetUVMtxMode ( MOAIGfxDevice::UV_STAGE_MODEL, MOAIGfxDevice::UV_STAGE_TEXTURE );
		gfxDevice.SetGfxState(this->mTexture);

		gfxDevice.SetPenWidth(this->mPenWidth);
		gfxDevice.SetPointSize(this->mPointSize);

		




//******************************************************************************************************
//VERT
		glBindBuffer(GL_ARRAY_BUFFER, voxel_vert);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

//******************************************************************************************************
//IBO
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, voxel_index);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indexs_buffer_data), g_indexs_buffer_data, GL_STREAM_DRAW);
//******************************************************************************************************
//UV	
		//glBindBuffer(GL_ARRAY_BUFFER, voxel_uv);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


		//glDrawElements(GL_TRIANGLE_STRIP, sizeof(g_vertex_buffer_data), GL_UNSIGNED_SHORT, 0);
		//glDisableVertexAttribArray(0);
		//glDisableVertexAttribArray(1);



//glDrawElements(
//     GL_TRIANGLES,      // mode
//	 12,    // count
//     GL_UNSIGNED_INT,   // type
//	0           // element array buffer offset
// );
//glDisableVertexAttribArray(0);
//glDisableVertexAttribArray(1);



//******************************************************************************************************
		//glDrawArrays(GL_TRIANGLES,  0,12 * 3);
		//glDisableVertexAttribArray(0);
		//glDisableVertexAttribArray(1);






//******************************************************************************************************	
//OFFSET
		glBindBuffer(GL_ARRAY_BUFFER, voxel_offset);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*INSTANCE_HIGH, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*INSTANCE_HIGH, &offset);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	

//ENABLE
glVertexAttribDivisor(0, 0);   // ORGINAL
glVertexAttribDivisor(1, 0);   // ORGINAL
glVertexAttribDivisor(2, 1);   // OFFSET FROM CENTER

//DRAW
//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//glPolygonMode(GL_FRONT, GL_LINE);
//glPolygonMode(GL_BACK, GL_LINE);

glDrawArraysInstanced(GL_TRIANGLES, 0, 12 * 3, INSTANCE_COUNT);

//glDrawElementsInstanced(GL_TRIANGLE_STRIP, sizeof(g_indexs_buffer_data), GL_UNSIGNED_SHORT, 0, INSTANCE_COUNT);

///DISABLE
glDisableVertexAttribArray(0);
glDisableVertexAttribArray(1);
glDisableVertexAttribArray(2);



				


}

//----------------------------------------------------------------//
ZLBox MOAIVoxelMesh::GetItemBounds ( u32 idx ) {
	UNUSED ( idx );
	
	if ( this->mVertexBuffer ) {
		return this->mVertexBuffer->GetBounds ();
	}
	
	ZLBox bounds;
	bounds.Init ( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );
	return bounds;
}

//----------------------------------------------------------------//
MOAIVoxelMesh::MOAIVoxelMesh () :
	mPrimType ( 0 ),
	mPenWidth ( 1.0f ),
	mPointSize ( 1.0f ) {

	RTTI_BEGIN
		RTTI_EXTEND ( MOAIDeck )
	RTTI_END
	
	this->SetContentMask ( MOAIProp::CAN_DRAW );
	this->mDefaultShaderID = MOAIShaderMgr::MESH_SHADER;
}

//----------------------------------------------------------------//
MOAIVoxelMesh::~MOAIVoxelMesh () {

	this->mIndexBuffer.Set ( *this, 0 );
	this->mTexture.Set ( *this, 0 );
	this->mVertexBuffer.Set ( *this, 0 );
}

//----------------------------------------------------------------//
void MOAIVoxelMesh::RegisterLuaClass ( MOAILuaState& state ) {

	MOAIDeck::RegisterLuaClass ( state );
	
	state.SetField ( -1, "GL_POINTS",			( u32 )ZGL_PRIM_POINTS );
	state.SetField ( -1, "GL_LINES",			( u32 )ZGL_PRIM_LINES );
	state.SetField ( -1, "GL_TRIANGLES",		( u32 )ZGL_PRIM_TRIANGLES );
	state.SetField ( -1, "GL_LINE_LOOP",		( u32 )ZGL_PRIM_LINE_LOOP );
	state.SetField ( -1, "GL_LINE_STRIP",		( u32 )ZGL_PRIM_LINE_STRIP );
	state.SetField ( -1, "GL_TRIANGLE_FAN",		( u32 )ZGL_PRIM_TRIANGLE_FAN );
	state.SetField ( -1, "GL_TRIANGLE_STRIP",	( u32 )ZGL_PRIM_TRIANGLE_STRIP );
}

//----------------------------------------------------------------//
void MOAIVoxelMesh::RegisterLuaFuncs ( MOAILuaState& state ) {

	MOAIDeck::RegisterLuaFuncs ( state );

	luaL_Reg regTable [] = {
		{ "setIndexBuffer",			_setIndexBuffer },
		{ "setPenWidth",			_setPenWidth },
		{ "setPointSize",			_setPointSize },
		{ "setPrimType",			_setPrimType },
		{ "setVertexBuffer",		_setVertexBuffer },
		{ "glGenBuffers",		_glGenBuffers },
		{ "draw", _draw },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}
