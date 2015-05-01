# plugin-moai-chimpmunk7
Moai 


Converted a lot of the original moai-chipmunk code to functions before I realized you could include the 
chipmunk_private.h which exposed private variables

```
#include "chipmunk/chipmunk_private.h"
//#include <chipmunk/chipmunk.h>
```


If something doesn't work check the function your calling something may have changed, there for I commented them out.






Add to our builld script
```
-DPLUGIN_MOAI-CHIPMUNK=TRUE ^
-DPLUGIN_DIR=F:/plugins/ ^
```

example: create-windows-bat

```
@echo off

:: Remember the original working directory
pushd .

:: Move to cmake directory
cd "%~dp0%..\cmake"

:: Determine target directory and cmake generator
set arg1=%1
if "%arg1%"=="" set arg1=vs2012
set generator=
if "%arg1%"=="vs2008" set generator=Visual Studio 9 2008
if "%arg1%"=="vs2010" set generator=Visual Studio 10
if "%arg1%"=="vs2012" set generator=Visual Studio 11
if "%arg1%"=="vs2013" set generator=Visual Studio 12
if "%generator%"=="" (
	@echo Unknown argument "%1". Valid values are vs2008, vs2010, vs2012, vs2013. Exiting.
	goto end
)
set targetDir=projects\%arg1%

@echo on

:: Delete and re-create the target directory
if exist %targetDir% rmdir /s /q %targetDir%
md %targetDir%

:: Move to target directory, then call cmake from there
cd %targetDir%
cmake ^
-G "%generator%" ^
-DBUILD_WINDOWS=TRUE ^
-DMOAI_BOX2D=TRUE ^
-DMOAI_CHIPMUNK=FALSE ^
-DMOAI_CURL=TRUE ^
-DMOAI_CRYPTO=TRUE ^
-DMOAI_EXPAT=TRUE ^
-DMOAI_FREETYPE=TRUE ^
-DMOAI_JSON=TRUE ^
-DMOAI_JPG=TRUE ^
-DMOAI_LUAEXT=TRUE ^
-DMOAI_MONGOOSE=TRUE ^
-DMOAI_OGG=TRUE ^
-DMOAI_OPENSSL=TRUE ^
-DMOAI_SQLITE3=TRUE ^
-DMOAI_TINYXML=TRUE ^
-DMOAI_PNG=TRUE ^
-DMOAI_SFMT=TRUE ^
-DMOAI_VORBIS=TRUE ^
-DMOAI_UNTZ=TRUE ^
-DMOAI_LUAJIT=TRUE ^
-DMOAI_HTTP_CLIENT=TRUE ^
-DSDL_HOST=TRUE ^
-DPLUGIN_MOAI-CHIPMUNK7=TRUE ^
-DPLUGIN_DIR=F:/plugins/ ^
..\..\

:end

@echo off

:: Restore original working directory
popd
```



--------------------------------------------------------------------------------

ANDROID

To get neon working you need to include   "-DANDROID_ABI="armeabi-v7a with NEON" \"


```
#!/bin/bash

export PATH=$PATH:/home/ezra/cmake/bin

export ANDROID_NDK=/home/ezra/Desktop/android-ndk-r10/




if [ x$ANDROID_NDK == x ]; then
echo ANDROID_NDK variable was not set. Please set to your ndk path
exit 1
fi





which cmake || (echo Could not find cmake ; exit 1)
if [ x$1 == x ]; then
libprefix=`dirname $0`/../lib/android
else
libprefix=$1
fi
mkdir -p $libprefix
libprefix=$(cd $libprefix; pwd)
cd `dirname $0`/..
moai_root=$(pwd)
if ! [ -d "build" ]
then
mkdir build
fi
cd build
build_folder=$moai_root/build

#ARCHS="armeabi armeabi-v7a x86"
ARCHS="armeabi-v7a"
for ARCH in $ARCHS
do
cd $build_folder
if ! [ -d "build-android-$ARCH" ]
then
mkdir build-android-$ARCH
fi

echo $moai_root

#-DPLUGIN_MOAI-EZRA=TRUE \
#-DANDROID_ABI=$ARCH with NEON \

cd build-android-$ARCH
cmake \
-DBUILD_ANDROID=TRUE \
-DCMAKE_TOOLCHAIN_FILE="$moai_root/cmake/host-android/android.toolchain.cmake" \
-DCMAKE_BUILD_TYPE=Release \
-DMOAI_LUAJIT=False \
-DMOAI_BOX2D=TRUE \
-DMOAI_CURL=TRUE \
-DMOAI_CRYPTO=TRUE \
-DMOAI_EXPAT=TRUE \
-DMOAI_FREETYPE=TRUE \
-DMOAI_JSON=TRUE \
-DMOAI_JPG=TRUE \
-DMOAI_LUAEXT=TRUE \
-DMOAI_MONGOOSE=TRUE \
-DMOAI_OGG=TRUE \
-DMOAI_OPENSSL=TRUE \
-DMOAI_SQLITE3=TRUE \
-DMOAI_TINYXML=TRUE \
-DMOAI_PNG=TRUE \
-DMOAI_SFMT=TRUE \
-DMOAI_VORBIS=TRUE \
-DMOAI_UNTZ=TRUE \
-DMOAI_HTTP_CLIENT=TRUE \
-DPLUGIN_MOAI-CHIPMUNK7=TRUE \
-DPLUGIN_MOAI-MATH=TRUE \
-DPLUGIN_DIR=$moai_root/plugins \
-DANDROID_ABI="armeabi-v7a with NEON" \
-DCMAKE_INSTALL_PREFIX=$libprefix/$ARCH \
-DLIBRARY_OUTPUT_PATH_ROOT=./build-android-$ARCH/ \
$moai_root/cmake || exit 1
cmake --build . --target install
echo Finished building $ARCH
done

```