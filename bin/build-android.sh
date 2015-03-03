#!/bin/bash


export PATH=$PATH:/home/ezra/cmake/bin

export ANDROID_NDK=/home/ezra/Desktop/android-ndk-r10/
#export NDK_TOOLCHAIN_VERSION=4.6
##export NDK_TOOLCHAIN_VERSION=4.9
#export PATH=$PATH:$ANDROID_ROOT/toolchains/arm-linux-androideabi-4.8/prebuilt/linux-x86_64/include

source ~/.bash_profile

cd `dirname $0`/..
cd ant/libmoai

#./clean.sh


if [[ $? -ne 0 ]]; then
    exit 1
fi

./build.sh $*
if [[ $? -ne 0 ]]; then
    exit 1
fi


## Create default host
echo "MAKING HOST"

cd ..


#./make-host.sh -p com.getmoai.samples -s $1
if [[ $? -ne 0 ]]; then
    exit 1
fi

cd untitled-host

cd ../..
rm -rf release/android
mkdir -p release/android/lib/
mkdir -p release/android/host/
cp -rf ant/libmoai/libs/** release/android/lib/
cp -rf ant/untitled-host/** release/android/host/

### COPY LIB TO BINRAY
