cmake_minimum_required ( VERSION 2.8.5 )
project ( moai-steam )    

#option ( BUILD_LINUX       FALSE )
#option ( BUILD_BLACKBERRY  FALSE )
#option ( BUILD_SERVER      FALSE )
#option ( BUILD_OSX         FALSE )
#option ( BUILD_HTML        FALSE )
#option ( BUILD_ANDROID     FALSE )
#option ( BUILD_WINDOWS     FALSE )

if(DEFINED ENV{STEAM_SDK})
MESSAGE( STATUS "STEAM_SDK FOUND: " $ENV{STEAM_SDK})	
else()
MESSAGE( STATUS "STEAM_SDK MISSING: " $ENV{STEAM_SDK})
endif()


#set (STEAM_SDK "F:/steam_sdk/steamworks_sdk_133b/sdk/" )	
  set (STEAM_SDK "$ENV{STEAM_SDK}")	
  set (STEAM_SDK_INCLUDE 		"${STEAM_SDK}/public/steam/" )

#WINDOWS 32bit
if ( BUILD_WINDOWS )
  set (STEAM_SDK_INCLUDE_LIB 		"${STEAM_SDK}/public/steam/lib/win32/sdkencryptedappticket.lib" )
  set (STEAM_SDK_REDIST_LIB 		"${STEAM_SDK}/redistributable_bin/win32/steam_api.lib" )
endif ( BUILD_WINDOWS )

#LINX 32bit
if ( BUILD_LINUX  )
  set (STEAM_SDK_INCLUDE_LIB 		"${STEAM_SDK}/public/steam/lib/linux32/libsdkencryptedappticket.so" )
  set (STEAM_SDK_REDIST_LIB 		"${STEAM_SDK}/redistributable_bin/linux32/libsteam_api.so" )
endif ( BUILD_LINUX  )

#OSX 32bit
if ( BUILD_OSX  )
  set (STEAM_SDK_INCLUDE_LIB 		"${STEAM_SDK}/public/steam/lib/linux32/libsdkencryptedappticket.so" )
  set (STEAM_SDK_REDIST_LIB 		"${STEAM_SDK}/redistributable_bin/linux32/libsteam_api.dylib" )
endif ( BUILD_OSX  )



  set ( MOAI_STEAM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../moai-steam" )  


  file ( GLOB MOAI_STEAM_SRC "${MOAI_STEAM_DIR}/*.cpp" "${MOAI_STEAM_DIR}/*.h" )

  add_library ( moai-steam STATIC ${MOAI_STEAM_SRC} )

  target_include_directories (moai-steam PUBLIC ${STEAM_SDK_INCLUDE} ${MOAI_STEAM_DIR} "${MOAI_STEAM_DIR}/../")


#When you create a .dll there is also a small import lib associated
#with the dll. You link with that and when the application starts it
#searches the path for each dll it needs. 

#REMOVE STEAM FROM HERE "steam" & THE LINKE TO THE LIB & HEADERS HERE
	#target_link_libraries ( moai-steam moai-sim moai-core moai-util steam zlcore )
	#include_directories(${STEAM_SDK_REDIST_LIB} ${STEAM_SDK_INCLUDE_LIB} )
	#link_directories(${STEAM_SDK_REDIST_LIB} ${STEAM_SDK_INCLUDE_LIB} )

  target_link_libraries ( moai-steam moai-sim moai-core moai-util  "${STEAM_SDK_REDIST_LIB}" "${STEAM_SDK_INCLUDE_LIB}" zlcore )
  set_target_properties(moai-steam PROPERTIES FOLDER Modules)


