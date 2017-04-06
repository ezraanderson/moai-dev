cmake_minimum_required ( VERSION 2.8.11 )

project ( cubi )
set ( CUBI_DIR     		"${CMAKE_CURRENT_SOURCE_DIR}/../../cubi")
set ( CUBI_DIR_SOURCE   "${CUBI_DIR}" )  
set ( CUBI_DIR_INCLUDE   "${CUBI_DIR}" )
file ( GLOB_RECURSE CUBI_SOURCES "${CUBI_DIR_SOURCE}/*.cpp")
file ( GLOB_RECURSE CUBI_HEADERS "${CUBI_DIR_INCLUDE}/*.h")


set ( VOXEL_DIR     	  "${CMAKE_CURRENT_SOURCE_DIR}/../../voxel")
set ( VOXEL_DIR_SOURCE    "${VOXEL_DIR}/PolyVox" )  
set ( VOXEL_DIR_INCLUDE   "${VOXEL_DIR}/PolyVox" )


add_library( cubi STATIC ${CUBI_SOURCES} ${CUBI_HEADERS} "${CUBI_DIR}/../.." ) 
target_include_directories ( cubi PUBLIC  ${CUBI_DIR_INCLUDE} ${VOXEL_DIR}  "F:/moai/pull/moai-dev/3rdparty/sqlite-3.6.16")
target_link_libraries(cubi sqlite3)


add_definitions( -DMINIZ_NO_STDIO )
add_definitions( -DCUBIQUITYC_EXPORTS )


set_target_properties( cubi PROPERTIES FOLDER Third-Party )

