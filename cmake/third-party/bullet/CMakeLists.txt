cmake_minimum_required ( VERSION 2.8.11 )
project ( bullet )  
      
set ( CMAKE_CURRENT_SOURCE_DIR "${MOAI_ROOT}/3rdparty/bullet/" )
set ( BULLET_INCLUDES "${MOAI_ROOT}/3rdparty/bullet/src" )

file ( GLOB_RECURSE BULLET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" )
file ( GLOB_RECURSE BULLET_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" )

add_library( bullet STATIC ${BULLET_SOURCES} ${BULLET_HEADERS} )

target_include_directories ( bullet PUBLIC ${BULLET_INCLUDES})
set_target_properties( bullet PROPERTIES FOLDER Third-Party )
