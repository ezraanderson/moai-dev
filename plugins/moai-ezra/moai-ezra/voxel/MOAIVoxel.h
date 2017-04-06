#ifndef MOAIVOXEL_H
#define MOAIVOXEL_H

#include <moai-core/MOAILua.h>

//**********************************************************************************
//class Vector3D
//{
//private:
//   double x, y, z;
//public:
//   void Display() const;
//};
//
//void Vector3D::Display() const
//{
//   std::cout << x << ", " << y << ", " << z << std::endl;
//}

class vector3D
{
    public:
        int x,y,z;
        vector3D(int xIn, int yIn, int zIn );
       // void print();
        //vector3D crossProduct(vector3D b) const;



};


//**********************************************************************************
enum BlockType
{
	BlockType_Default = 0,
	BlockType_Grass,
	BlockType_Dirt,
	BlockType_Water,
	BlockType_Stone,
	BlockType_Wood,
	BlockType_Sand,
	BlockType_NumTypes,
};
//**********************************************************************************
class Block
{
public:
   // Block();
   // ~Block();
    bool IsActive();
    void SetActive(bool active);
	static const int  BLOCK_RENDER_SIZE = 1;
private:
    bool m_active;
	BlockType m_blockType;
    
};



//**********************************************************************************
class MOAIVoxel :
	public virtual MOAILuaObject {
private:
	
	 Block*** m_pBlocks;
	 static const int CHUNK_SIZE = 16;
	 vector<vector<vector<double> > > noiseArray;

	 MOAIVertexBuffer* mVbo;
	 long gridX;
	 long gridY;
	 long gridZ;

	int cnt;
	int inca;

	float start_x,start_y,start_z;
	float end_x,end_y,end_z;

	//----------------------------------------------------------------//
	static int		_classHello		( lua_State* L );
	static int		_makeChunk		( lua_State* L );
	static int		_makeMesh		( lua_State* L );
	static int		_makeNoise		( lua_State* L );
	static int		_setVbo			( lua_State* L );
	static int		_setGrid		( lua_State* L );

	void		makeCube		(int x,int y,int z,int cnt);


public:

	DECL_LUA_FACTORY ( MOAIVoxel )

	//----------------------------------------------------------------//
					MOAIVoxel				();
					~MOAIVoxel			();
	void			RegisterLuaClass	( MOAILuaState& state );
	void			RegisterLuaFuncs	( MOAILuaState& state );
};

#endif