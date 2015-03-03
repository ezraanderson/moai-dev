#!/bin/bash

#
# Build script for Linux x64
# Usage: Run from Moai SDK's root directory:
#
# build-linux-sdl.sh
#
# You can change the CMake options using -DOPTION=VALUE
# Check moai-dev/cmake/CMakeLists.txt for all the available options.
#

cd `dirname $0`/..

if [$1 = "--fast"]; then

    echo "FAST_________________"       
    cd cmake     
    cd build-linux

else     

echo "REBUILDING_________________"     

cd cmake
rm -rf build-linux
mkdir build-linux
cd build-linux
cmake \
-DBUILD_LINUX=TRUE \
-DSDL_HOST=TRUE \
-DMOAI_BOX2D=TRUE \
-DMOAI_BULLET=TRUE \
-DMOAI_CHIPMUNK=TRUE \
-DMOAI_CURL=TRUE \
-DMOAI_CRYPTO=TRUE \
-DMOAI_EXPAT=TRUE \
-DMOAI_FREETYPE=TRUE \
-DMOAI_JSON=TRUE \
-DMOAI_JPG=TRUE \
-DMOAI_MONGOOSE=TRUE \
-DMOAI_LUAEXT=TRUE \
-DMOAI_OGG=TRUE \
-DMOAI_OPENSSL=TRUE \
-DMOAI_SQLITE3=TRUE \
-DMOAI_TINYXML=TRUE \
-DMOAI_PNG=TRUE \
-DMOAI_SFMT=TRUE \
-DMOAI_VORBIS=TRUE \
-DMOAI_UNTZ=TRUE \
-DMOAI_LUAJIT=TRUE \
-DMOAI_HTTP_CLIENT=TRUE \
-DCMAKE_BUILD_TYPE=Release \
../

fi

make -j8
if [[ $? -ne 0 ]]; then
    exit 1
fi

#
# Copy libs to lib
#
rm -rf ../../release/linux/host-sdl/x64/
mkdir -p ../../release/linux/host-sdl/x64/lib/
mkdir -p ../../release/linux/host-sdl/x64/bin/
for i in * ; do
  if [ -d "$i" ]; then
    if [ -f $i/lib$i.a ]; then
      echo "Copying $i/lib$i.a to release/linux/host-sdl/x64/lib"
      cp $i/lib$i.a ../../release/linux/host-sdl/x64/lib/
    fi
  fi
done
pwd
cp host-sdl/moai ../../release/linux/host-sdl/x64/bin/
