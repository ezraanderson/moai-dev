#ifndef MOAIVOXELAPI_H
#define MOAIVOXELAPI_H

#include <moai-core/MOAILua.h>

//#include <PolyVox/CubicSurfaceExtractorWithNormals.h>
//#include <PolyVox/MarchingCubesSurfaceExtractor.h>
//#include <PolyVox/SurfaceMesh.h>
//#include <PolyVox/SimpleVolume.h>
//#include <PolyVox/LargeVolume.h>
//#include <PolyVox/MaterialDensityPair.h>

#include <moai-sim/MOAIIndexBuffer.h>
#include <moai-sim/MOAIVertexBuffer.h>

class MOAIVoxelApi :
	public virtual MOAILuaObject {
private:	

	bool mEnabled;

	MOAIIndexBuffer* iBuffer;
	MOAIVertexBuffer* vBuffer;
	MOAIShader		* shader;


	static int		_start			( lua_State* L );
	static int		_getVBO			( lua_State* L );
	static int		_setVBO			( lua_State* L );
	static int		_setIBO			( lua_State* L );
	static int		_setShader		(lua_State* L);
	static int		_update			(lua_State* L);
	static int		_static			(lua_State* L);
public:

	DECL_LUA_FACTORY ( MOAIVoxelApi )

	//----------------------------------------------------------------//
					MOAIVoxelApi			();
					~MOAIVoxelApi			();


	//void			setSurfaceMeshToRender(const PolyVox::SurfaceMesh<PositionMaterialNormal>& surfaceMesh);
	//void			createSphereInVolume(PolyVox::SimpleVolume<uint8_t>& volData, float fRadius);
	//void			createSphereInVolumeB(PolyVox::LargeVolume<PolyVox::MaterialDensityPair44>& volData, float fRadius, uint8_t uValues);


	//void            createPerlinVolumeSlow(PolyVox::LargeVolume<PolyVox::MaterialDensityPair44>& volData);
	//void			createSphereInVolumeStream(PolyVox::SimpleVolume<uint8_t>& volData, );


	void			RegisterLuaClass	( MOAILuaState& state );
	void			RegisterLuaFuncs	( MOAILuaState& state );


};




#endif



