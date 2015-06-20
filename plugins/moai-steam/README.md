# plugin-moai-steam
plugin-moai-steam                                                                                            

----------------------------------------------------------------------------------------
1. NO STEAM FILES INCLUDED, FILES MUST BE DOWNLOADED FROM STEAM AFTER SIGING STEAMS NDA

2. ONLY TESTED ON WINDOWS, STEAM RUNS FINE WITH MOAI, HOWEVER THE FOLLOWING METHOD MAYBE INCORRECT.
----------------------------------------------------------------------------------------


1. Make a system varible -> (STEAM_SDK) -> point to download steam files ->  steam path(F:\steam_sdk\steamworks_sdk_133b\sdk) 

2. copy files from root dir -> (F:\steam_sdk\steamworks_sdk_133b\sdk\redistributable_bin\) -> steam_api.dll & steam_api. -> to new folder ->  (F:\steam_sdk\steamworks_sdk_133b\sdk\redistributable_bin\win32\)

3. Add plugins to build scripts

create-projects-win.bat
````
-DPLUGIN_MOAI-STEAM=TRUE ^
-DPLUGIN_DIR=F:/moai/pull/moai-dev/plugins ^
````

build-linux-sdl.sh
```
-DPLUGIN_MOAI-STEAM=TRUE \
-DPLUGIN_DIR=$moai_root/plugins \
```

4. All setting are for 32bit, replace 32 with 64 for 64 bit builds 
   *F:\moai\pull\moai-dev\plugins\moai-steam\cmake\moai-steam\

````
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
````


5. Copy "steam_api.dll" into the directory with moai.exe
6. Make file called "steam_appid.txt" and add the game id. --> http://forums.steampowered.com/forums/showthread.php?t=1290008

7. SteamAPI_Init();	 --> is called from --> MOAISteamAppInitialize () ->   F:\moai\pull\moai-dev\plugins\moai-steam\moai-steam\host.cpp

8. SteamAPI_Shutdown();	 --> is called from --> MOAISteamAppFinalize () ->   F:\moai\pull\moai-dev\plugins\moai-steam\moai-steam\host.cpp

9. Add new api here --> MOAISteamApi.new() -> calls ->    F:\moai\pull\moai-dev\plugins\moai-steam\moai-steam\MOAISteamApi.cpp

10. learn bundling depots & other stuff later :)