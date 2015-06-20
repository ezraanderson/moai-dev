cmake_minimum_required ( VERSION 2.8.11 )
#DUMY FILES FOR LINKING ERRORS
project ( steam )



set ( STEAM_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../steam/" )
set ( STEAM_INCLUDES "${STEAM_SOURCE_DIR}" ) 

#set (STEAM_SDK "F:/steam_sdk/steamworks_sdk_133b/sdk/public/steam" )	
#set ( STEAM_SOURCE_DIR "${STEAM_SDK}" )
#set ( STEAM_INCLUDES   "${STEAM_SDK}" )   

file ( GLOB_RECURSE STEAM_SOURCES "${STEAM_SOURCE_DIR}/*.cpp")
file ( GLOB_RECURSE STEAM_HEADERS  "${STEAM_INCLUDES}/*.h")


add_library( steam STATIC ${STEAM_SOURCES} ${STEAM_HEADERS} "${STEAM_SOURCE_DIR}/../.." ) 
target_include_directories ( steam PUBLIC ${STEAM_INCLUDES})
set_target_properties( steam PROPERTIES FOLDER Third-Party )


