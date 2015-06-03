cmake_minimum_required ( VERSION 2.8.5 )
project ( moai-mathUtil )


set ( MOAI_MATHUTIL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../moai-mathUtil" )       
file ( GLOB MOAI_MATHUTIL_SRC "${MOAI_MATHUTIL_DIR}/*.cpp" "${MOAI_MATHUTIL_DIR}/*.h" )


set ( MATH_INCLUDES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../chipmunk7/include/" )
INCLUDE_DIRECTORIES(${MATH_INCLUDES_DIR})

add_library ( moai-mathUtil STATIC ${MOAI_MATHUTIL_SRC} )
target_include_directories (moai-mathUtil PUBLIC ${MOAI_MATHUTIL_DIR} "${MOAI_MATHUTIL_DIR}/../")
target_link_libraries ( moai-mathUtil moai-poly2tri moai-sim moai-core moai-util zlcore )
set_target_properties(moai-mathUtil PROPERTIES FOLDER Modules)


