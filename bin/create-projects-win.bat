@echo off

:: Remember the original working directory
pushd .

:: Move to cmake directory
cd "%~dp0%..\cmake"

:: Determine target directory and cmake generator
 set arg1=vs2013
::set arg1=vs2010

if "%arg1%"=="" set arg1=vs2013
set generator=
if "%arg1%"=="vs2008" set generator=Visual Studio 9 2008
if "%arg1%"=="vs2010" set generator=Visual Studio 10
if "%arg1%"=="vs2012" set generator=Visual Studio 11
if "%arg1%"=="vs2013" set generator=Visual Studio 12
if "%arg1%"=="vs2015" set generator=Visual Studio 14 Win64
if "%generator%"=="" (
	@echo Unknown argument "%1". Valid values are vs2008, vs2010, vs2012, vs2013. Exiting.
	goto end
)

   
::generator=Visual Studio 10
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
-DMOAI_EXPAT=TRUE ^
-DMOAI_FREETYPE=TRUE ^
-DMOAI_JSON=TRUE ^
-DMOAI_JPG=TRUE ^
-DMOAI_LUAEXT=TRUE ^
-DMOAI_MONGOOSE=TRUE ^
-DMOAI_OGG=TRUE ^
-DMOAI_SQLITE3=TRUE ^
-DMOAI_TINYXML=TRUE ^
-DMOAI_PNG=TRUE ^
-DMOAI_SFMT=TRUE ^
-DMOAI_VORBIS=TRUE ^
-DMOAI_UNTZ=TRUE ^
-DMOAI_LUAJIT=FALSE ^
-DSDL_HOST=TRUE ^
-DMOAI_HTTP_CLIENT=TRUE ^
-DPLUGIN_MOAI-MATHUTIL=TRUE ^
-DPLUGIN_MOAI-EZRA=TRUE ^
-DPLUGIN_MOAI-VOXEL=TRUE ^
-DPLUGIN_DIR=F:/moai/pull/moai-dev/plugins ^
..\..\

::-DSDL_JOYSTICK_DINPUT=TRUE ^
::-DSDL_JOYSTICK_DINPUT=TRUE ^

::-DPLUGIN_MOAI-VOXEL=TRUE ^
::-DPLUGIN_MOAI-STEAM=FALSE ^
::-DMOAI_CRYPTO=TRUE ^
::-DMOAI_CHIPMUNK=FALSE ^
::-DMOAI_CURL=FALSE ^
::-DPLUGIN_MOAI-CHIPMUNK7=TRUE ^
::-DPLUGIN_MOAI-BULLET=FALSE ^
::-DMOAI_OPENSSL=FALSE ^


::cmake --build . --config Release  
:: msbuild /p:DXSDK_DIR=Lib\x86

:end



@echo off

:: Restore original working directory
popd
pause
