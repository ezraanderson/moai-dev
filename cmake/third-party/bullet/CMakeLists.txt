cmake_minimum_required ( VERSION 2.8.11 )

project ( bullet )
set ( CMAKE_CURRENT_SOURCE_DIR "${MOAI_ROOT}/3rdparty/bullet/" )
set ( BULLET_INCLUDES "${MOAI_ROOT}/3rdparty/bullet/src" )    

file ( GLOB_RECURSE BULLET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/BulletDynamics/*.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/BulletCollision/*.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/BulletSoftBody/*.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/LinearMath/*.cpp"
)
file ( GLOB_RECURSE BULLET_HEADERS  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/src/BulletDynamics/*.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/src/BulletCollision/*.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/src/BulletSoftBody/*.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/src/LinearMath/*.h"
)

include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/src/" )
add_library( bullet STATIC ${BULLET_SOURCES} ${BULLET_HEADERS} ) 

target_include_directories ( bullet PUBLIC ${BULLET_INCLUDES})
set_target_properties( bullet PROPERTIES FOLDER Third-Party )



