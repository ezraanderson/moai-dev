cmake_minimum_required ( VERSION 2.8.11 )


#option ( BUILD_LINUX       FALSE )
#option ( BUILD_BLACKBERRY  FALSE )
#option ( BUILD_SERVER      FALSE )
#option ( BUILD_OSX         FALSE )
#option ( BUILD_HTML        FALSE )
#option ( BUILD_ANDROID     FALSE )
#option ( BUILD_WINDOWS     FALSE )

project ( chipmunk7 )
set ( CHIPMUNK7_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../chipmunk7/src/" )
set ( CHIPMUNK7_INCLUDES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../chipmunk7/include/" )

file (GLOB_RECURSE CHIPMUNK7_SOURCES "${CHIPMUNK7_SOURCE_DIR}/*.c")   
file ( GLOB_RECURSE CHIPMUNK7_HEADERS  "${CHIPMUNK7_INCLUDES_DIR}/*.h" )    




if ( BUILD_WINDOWS )
	set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_CRT_SECURE_NO_WARNINGS -DWIN32 -D_DEBUG -D_LIB " )
	list(REMOVE_ITEM CHIPMUNK7_SOURCES "${CHIPMUNK7_SOURCE_DIR}/cpHastySpace.c")
	list(REMOVE_ITEM CHIPMUNK7_HEADERS "${CHIPMUNK7_INCLUDES_DIR}/cpHastySpace.h") 
	list(REMOVE_ITEM CHIPMUNK7_SOURCES "${CHIPMUNK7_SOURCE_DIR}/cpPolyline.c")
endif ( BUILD_WINDOWS )


#if ( BUILD_ANDROID  )
#	set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_CRT_SECURE_NO_WARNINGS -DWIN32 -D_DEBUG -D_LIB " )
#	list(REMOVE_ITEM CHIPMUNK7_SOURCES "${CHIPMUNK7_SOURCE_DIR}/cpSpace.c")
#	list(REMOVE_ITEM CHIPMUNK7_HEADERS "${CHIPMUNK7_INCLUDES_DIR}/cpSpace.h") 
#endif ( BUILD_ANDROID  )





if(NOT MSVC)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99") # always use gnu99
  if(FORCE_CLANG_BLOCKS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fblocks")
  endif()
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffast-math") # extend release-profile with fast-math
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall") # extend debug-profile with -Wall
endif()


add_library( chipmunk7 STATIC ${CHIPMUNK7_SOURCES} ${CHIPMUNK7_HEADERS} "${CHIPMUNK7_SOURCE_DIR}/../.." ) 

target_include_directories ( chipmunk7 PUBLIC ${CHIPMUNK7_INCLUDES})

INCLUDE_DIRECTORIES(${CHIPMUNK7_INCLUDES_DIR})

set_target_properties( chipmunk7 PROPERTIES FOLDER Third-Party )

if ( BUILD_WINDOWS )
set_target_properties ( chipmunk7 PROPERTIES LINKER_LANGUAGE CXX )
SET_SOURCE_FILES_PROPERTIES ( ${CHIPMUNK7_SOURCES} PROPERTIES LANGUAGE CXX )
endif ( BUILD_WINDOWS )

