cmake_minimum_required ( VERSION 2.8.11 )

project ( voxel C )
set ( VOXEL_DIR     	  "${CMAKE_CURRENT_SOURCE_DIR}/../../voxel")
set ( VOXEL_DIR_SOURCE    "${VOXEL_DIR}/PolyVox" )  
set ( VOXEL_DIR_INCLUDE   "${VOXEL_DIR}/PolyVox" )

file ( GLOB_RECURSE VOXEL_SOURCES "${VOXEL_DIR_SOURCE}/*.cpp")

file ( GLOB_RECURSE VOXEL_HEADERS "${VOXEL_DIR_INCLUDE}/*.h"								  
								  "${VOXEL_DIR_INCLUDE}/Impl/*.h"
)



add_library( voxel STATIC ${VOXEL_SOURCES} ${VOXEL_HEADERS} "${VOXEL_DIR}/../.." ) 
target_include_directories ( voxel PUBLIC  ${VOXEL_DIR_SOURCE} )

set_target_properties( voxel PROPERTIES FOLDER Third-Party LINKER_LANGUAGE CXX)
