cmake_minimum_required ( VERSION 2.8.11 )

project ( math-neon )
set ( MATH_NEON_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../math-neon/" )
set ( MATH_NEON_INCLUDES "${MATH_NEON_SOURCE_DIR}" )    

file ( GLOB_RECURSE MATH_NEON_SOURCES "${MATH_NEON_SOURCE_DIR}/*.c")
file ( GLOB_RECURSE MATH_NEON_HEADERS  "${MATH_NEON_INCLUDES}/*.h")

list(REMOVE_ITEM MATH_NEON_SOURCES "${MATH_NEON_SOURCE_DIR}/math_debug.c")

if(NOT MSVC)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99") # always use gnu99
  if(FORCE_CLANG_BLOCKS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fblocks")
  endif()
  #set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffast-math") # extend release-profile with fast-math
  #set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall") # extend debug-profile with -Wall
endif()


add_library( math-neon STATIC ${MATH_NEON_SOURCES} ${MATH_NEON_HEADERS} "${MATH_NEON_SOURCE_DIR}/../.." ) 
target_include_directories ( math-neon PUBLIC ${MATH_NEON_INCLUDES})
set_target_properties( math-neon PROPERTIES FOLDER Third-Party )

#set( ANDROID_CXX_FLAGS "${ANDROID_CXX_FLAGS} -mfpu=neon -O3 -ftree-vectorize"  )


if ( BUILD_WINDOWS )
set_target_properties ( math-neon PROPERTIES LINKER_LANGUAGE CXX )
SET_SOURCE_FILES_PROPERTIES ( ${MATH_NEON_SOURCES} PROPERTIES LANGUAGE CXX )
endif ( BUILD_WINDOWS )




