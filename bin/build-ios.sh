## CHARTBOOSTER DOESN"T WORK ON THES     

#./bin/build-ios.sh ./bin/dummy/



#!/bin/bash



#================================================================#
# Copyright (c) 2010-2011 Zipline Games, Inc.
# All Rights Reserved.
# http://getmoai.com
#================================================================#

# Set this to a name which will be valid for "codesign -s", or the build
# will fail.      
SIGN_IDENTITY='iPhone Developer'

codesign_msg=$(codesign -s "$SIGN_IDENTITY" 2>&1)
case $codesign_msg in
*": no identity found"*)
    echo >&2 "Code-signing identity ($SIGN_IDENTITY) is invalid."
    exit 1
    ;;
esac

set -e

# Give more useful feedback rather than aborting silently.
report_error() {
    status=$?
    case $status in
    0)    ;;
    *)    echo >&2 "Aborting due to exit status $status from: $BASH_COMMAND";;
    esac
    exit $status
}

trap 'report_error' 0

APP_NAME='Moai App'
APP_ID='com.getmoai.moaiapp'
APP_VERSION='1.0'

usage() {
    cat >&2 <<EOF
usage: $0
    [--use-untz true | false] [--disable-adcolony] [--disable-billing]
    [--disable-chartboost] [--disable-crittercism] [--disable-facebook]
    [--disable-mobileapptracker] [--disable-playhaven] [--disable-push] [--disable-tapjoy]
    [--disable-twitter] [--simulator] [--release] [--fast]       
    <lua-src-path>
EOF
    exit 1
}


echo "> setting flags"

# check for command line switches
use_untz="true"

adcolony_flags="false"
billing_flags="false"                                                                                                                                                     
chartboost_flags="false" 
crittercism_flags="false"
facebook_flags="false"
playhaven_flags="false"
push_flags="false"  
tapjoy_flags="false"
twitter_flags="false"
buildtype_flags="Release"
windows_flags=
simulator="false"  
mobileapptracker_flags="false"


while [ $# -gt 0 ];	do
    case "$1" in
        --use-untz)  use_untz="$2"; shift;;
        --disable-adcolony)  adcolony_flags="-DDISABLE_ADCOLONY";;
        --disable-billing)  billing_flags="-DDISABLE_BILLING";;
        --disable-chartboost)  chartboost_flags="-DDISABLE_CHARTBOOST";;
        --disable-crittercism)  crittercism_flags="-DDISABLE_CRITTERCISM";;
        --disable-facebook)  facebook_flags="-DDISABLE_FACEBOOK";;
        --disable-mobileapptracker)  mobileapptracker_flags="-DDISABLE_MOBILEAPPTRACKER";;
        --disable-playhaven)  playhaven_flags="-DDISABLE_PLAYHAVEN";;
        --disable-push)  push_flags="-DDISABLE_NOTIFICATIONS";;
        --disable-tapjoy)  tapjoy_flags="-DDISABLE_TAPJOY";;
        --disable-twitter)  twitter_flags="-DDISABLE_TWITTER";;
        --release) buildtype_flags="Release";;
        --simulator) simulator="true";;
        --fast) fast_flags="true";; 
        -*) usage;;
        *)  break;;	# terminate while loop
    esac
    shift
done


echo "> setting usage"

if [ $# != 1 ]; then
    usage
fi


echo "> setting ruby"

LUASRC=$(ruby -e 'puts File.expand_path(ARGV.first)' "$1")


if [ ! -f "${LUASRC}/main.lua" ]; then
    echo -n "Please enter the directory path of the Lua source. > "
    read LUASRC
    LUASRC=$(ruby -e 'puts File.expand_path(ARGV.first)' "$LUASRC")

    if [ ! -f "${LUASRC}/main.lua" ]; then
        echo "Could not find main.lua in specified lua source directory [${LUASRC}]"
        exit 1
    fi
fi

echo "> setting use_untz"
            
if [ x"$use_untz" != xtrue ] && [ x"$use_untz" != xfalse ]; then
    usage
fi


echo "> setting XCODEPATH"

#get some required variables
XCODEPATH=$(xcode-select --print-path)

if [ x"$simulator" == xtrue ]; then
  echo "RUNNING SIMULATOR $simulator"
  
  PLATFORM_PATH=${XCODEPATH}/Platforms/iPhoneSimulator.platform/Developer
  PLATFORM=SIMULATOR
  SDK=iphonesimulator
  ARCH=i386
  
else

  PLATFORM_PATH=${XCODEPATH}/Platforms/iPhoneOS.platform/Developer
  PLATFORM=OS
  SDK=iphoneos
  ARCH=armv7
fi

# echo message about what we are doing
echo "Building moai.app via CMAKE"

###############################################################################

echo ""
echo "---THIRD PARTY---"

disabled_ext=
    
if [ x"$use_untz" != xtrue ]; then
    echo "UNTZ : will be disabled"
    untz_param='-DMOAI_UNTZ=0'
else
    untz_param='-DMOAI_UNTZ=1'
fi 

if [ x"$adcolony_flags" != x ]; then
    echo "AdColony : will be disabled"
    disabled_ext="${disabled_ext}ADCOLONY;"
fi 

if [ x"$billing_flags" != x ]; then
    echo "Billing : will be disabled"
    disabled_ext="${disabled_ext}BILLING;"
fi 

if [ x"$chartboost_flags" != x ]; then
    echo "ChartBoost : will be disabled"
    disabled_ext="${disabled_ext}CHARTBOOST;"
fi 

if [ x"$crittercism_flags" != x ]; then
    echo "Crittercism : will be disabled"
    disabled_ext="${disabled_ext}CRITTERCISM;"
fi 

if [ x"$facebook_flags" != x ]; then
    echo "Facebook : will be disabled"
    disabled_ext="${disabled_ext}FACEBOOK;"
fi 

if [ x"$mobileapptracker_flags" != x ]; then
    echo "Mobile App Tracker : will be disabled"
    disabled_ext="${disabled_ext}MOBILEAPPTRACKER;"
fi 

if [ x"$playhaven_flags" != x ]; then
    echo "PlayHaven : will be disabled"
    disabled_ext="${disabled_ext}PLAYHAVEN;"
fi 

if [ x"$push_flags" != x ]; then
    echo "Push Notifications : will be disabled"
    disabled_ext="${disabled_ext}NOTIFICATIONS;"
fi 

if [ x"$tapjoy_flags" != x ]; then
    echo "Tapjoy : will be disabled"
    disabled_ext="${disabled_ext}TAPJOY;"
fi 

if [ x"$twitter_flags" != x ]; then
    echo "Twitter : will be disabled"
    disabled_ext="${disabled_ext}TWITTER;"
fi 


echo "------------"
echo ""

###############################################################################

build_dir=${PWD}

cd `dirname $0`/..


if [ x"$fast_flags" != x ]; then

  echo "FAST ___________________"
  cd cmake 
  cd build-ios
    
else

 echo "REBUILDING ___________________"



cd cmake
cd /Users/ezra/Desktop/build-drive/

rm -rf build-ios
mkdir build-ios
cd build-ios

echo "Building resource list from ${LUASRC}"

#ruby ../host-ios/build_resources.rb "${LUASRC}"
ruby /Volumes/moai-dev/cmake/host-ios/build_resources.rb "${LUASRC}"

echo "> Creating xcode project"
echo ">>>> PLATFORM_PATH ${PLATFORM_PATH}"
echo "-------------------------------------------"
echo "WHAY WONT IT CHANGE THE DIR"

#create our makefiles
#cmake -DDISABLED_EXT="$disabled_ext" -DMOAI_BOX2D=0 -DMOAI_BULLET=1 \
 
cmake -DDISABLED_EXT="$disabled_ext" -DMOAI_BOX2D=0 -DMOAI_BULLET=1 \
-DMOAI_CHIPMUNK=0 -DMOAI_CURL=1 -DMOAI_CRYPTO=0 -DMOAI_EXPAT=1 -DMOAI_FREETYPE=1 \
-DMOAI_HTTP_CLIENT=1 -DMOAI_JSON=1 -DMOAI_JPG=0 -DMOAI_LUAEXT=1 \
-DMOAI_MONGOOSE=0 -DMOAI_OGG=1 -DMOAI_OPENSSL=0 -DMOAI_SQLITE3=0 \
-DMOAI_TINYXML=1 -DMOAI_PNG=1 -DMOAI_SFMT=1 -DMOAI_VORBIS=1 $untz_param \
-DMOAI_LUAJIT=1 \
-DBUILD_IOS=true \
-DSIGN_IDENTITY="${SIGN_IDENTITY}" \
-DAPP_NAME="${APP_NAME}" \
-DAPP_ID="${APP_ID}" \
-DAPP_VERSION="${APP_VERSION}" \
-DCMAKE_BUILD_TYPE="Release" \
-G "Xcode" \
/Volumes/moai-dev/cmake//



fi

#-DCMAKE_IOS_DEVELOPER_ROOT="${PLATFORM_PATH}" \
#-DCMAKE_TOOLCHAIN_FILE="../host-ios/iOS.cmake" \


#-DCMAKE_IOS_DEVELOPER_ROOT="${PLATFORM_PATH}" \
#-DCMAKE_TOOLCHAIN_FILE="../host-ios/iOS.cmake" \

#-miphoneos-version-min="5.1" \

#-DCMAKE_IOS_DEVELOPER_ROOT="${PLATFORM_PATH}" \
#-DCMAKE_TOOLCHAIN_FILE="../host-ios/iOS.cmake" \

  #OPTIMIZATION_LEVEL=2                                                                                                          
 #GCC_OPTIMIZATION_LEVEL='3'
 #GCC_OPTIMIZATION_LEVEL='3'
   
   
if [ x"$simulator" == xtrue ]; then   

      xcodebuild -target moai -sdk ${SDK} -arch i386 -configuration debug;                                                                                                     
 
else
     xcodebuild -target moai -sdk ${SDK} -arch ${ARCH} -configuration Release IPHONEOS_DEPLOYMENT_TARGET='6.1' GCC_FAST_MATH=YES LLVM_VECTORIZE_LOOPS=YES;

fi




#xcodebuild -target moai -sdk ${SDK} -arch ${ARCH}







echo "Build Directory : ${build_dir}"

# Copy libs
cd "/"
cd "volumes/pull/moai-dev/"

if [ -d "release/ios" ]; then
    rm -fr release/ios
fi

#mkdir -p release/ios/app
mkdir -p release/ios/lib

#find cmake/build-ios -name "*.app" | xargs -J % cp -fRp % release/ios/app
find cmake/build-ios -name "*.a" | xargs -J % cp -fp % release/ios/lib
