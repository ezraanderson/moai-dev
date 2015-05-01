cmake_minimum_required ( VERSION 2.8.5 )
project ( moai-math )


set ( MOAI_MATH_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../moai-math" )       
file ( GLOB MOAI_MATH_SRC "${MOAI_MATH_DIR}/*.cpp" "${MOAI_MATH_DIR}/*.h" )


set ( MATH_INCLUDES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../chipmunk7/include/" )
INCLUDE_DIRECTORIES(${MATH_INCLUDES_DIR})

add_library ( moai-math STATIC ${MOAI_MATH_SRC} )
target_include_directories (moai-math PUBLIC ${MOAI_MATH_DIR} "${MOAI_MATH_DIR}/../")
target_link_libraries ( moai-math moai-sim moai-core moai-util math-neon zlcore )
set_target_properties(moai-math PROPERTIES FOLDER Modules)


