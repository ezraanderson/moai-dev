cmake_minimum_required ( VERSION 2.8.5 )
project ( moai-poly2tri )


set ( MOAI_POLY2TRI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../moai-poly2tri" )  
     
file ( GLOB MOAI_POLY2TRI_SRC "${MOAI_POLY2TRI_DIR}/*.cpp" 
"${MOAI_POLY2TRI_DIR}/sweep/*.cc" 
"${MOAI_POLY2TRI_DIR}/common/*.cc" 
"${MOAI_POLY2TRI_DIR}/*.h" 
"${MOAI_POLY2TRI_DIR}/sweep/*.h" 
"${MOAI_POLY2TRI_DIR}/common/*.h" 
)


set ( MATH_INCLUDES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../moai-poly2tri" )
INCLUDE_DIRECTORIES(${MATH_INCLUDES_DIR})

add_library ( moai-poly2tri STATIC ${MOAI_POLY2TRI_SRC} )

target_include_directories (moai-poly2tri PUBLIC ${MOAI_POLY2TRI_DIR} "${MOAI_POLY2TRI_DIR}/../")

target_link_libraries ( moai-poly2tri moai-sim moai-core moai-util zlcore )

set_target_properties(moai-poly2tri PROPERTIES FOLDER Modules)


