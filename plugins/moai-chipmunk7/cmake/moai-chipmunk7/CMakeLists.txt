cmake_minimum_required ( VERSION 2.8.5 )
project ( moai-chipmunk7 )


set ( MOAI_CHIPMUNK7_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../moai-chipmunk7" )       
file ( GLOB MOAI_CHIPMUNK7_SRC "${MOAI_CHIPMUNK7_DIR}/*.cpp" "${MOAI_CHIPMUNK7_DIR}/*.h" )


set ( CHIPMUNK7_INCLUDES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../chipmunk7/include/" )
INCLUDE_DIRECTORIES(${CHIPMUNK7_INCLUDES_DIR})

add_library ( moai-chipmunk7 STATIC ${MOAI_CHIPMUNK7_SRC} )
target_include_directories (moai-chipmunk7 PUBLIC ${MOAI_CHIPMUNK7_DIR} "${MOAI_CHIPMUNK7_DIR}/../")
target_link_libraries ( moai-chipmunk7 moai-sim moai-core moai-util chipmunk7 zlcore )
set_target_properties(moai-chipmunk7 PROPERTIES FOLDER Modules)


