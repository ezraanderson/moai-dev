// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com


//FOR MEMORY LEAK

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
	_CrtMemState state;
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <moai-core/host.h>
#include <host-modules/aku_modules.h>
#include <host-sdl/SDLHost.h>

#include <SDL.h>



#define UNUSED(p) (( void )p)

namespace InputDeviceID {
	enum {
		DEVICE,
		TOTAL,
	};
}

namespace InputSensorID {
	enum {
		GAMEBUTTON,
		GAMEANALOG,
		KEYBOARD,
		POINTER,
		MOUSE_LEFT,
		MOUSE_MIDDLE,
		MOUSE_RIGHT,
		TOUCH,
		TOTAL,
	};
}

static SDL_Window* sWindow = 0;

//================================================================//
// aku callbacks
//================================================================//

void	_AKUEnterFullscreenModeFunc		();
void	_AKUExitFullscreenModeFunc		();
void	_AKUHideCursorFunc				();
void	_AKUShowCursorFunc				();

void	_AKUOpenWindowFunc				( const char* title, int width, int height );
void	_AKUResizeWindowFunc			(  int width, int height );
void	_AKUTitleFunc					(  const char* title);


typedef int ( *DisplayModeFunc ) (int, SDL_DisplayMode *);
static void SetScreenSize ( DisplayModeFunc func);

//----------------------------------------------------------------//
void SetScreenSize(DisplayModeFunc func ) {
	SDL_DisplayMode dm;
	if ( func != NULL && func( 0, &dm ) == 0 ) {
		AKUSetScreenSize(dm.w, dm.h);
	}
}
//----------------------------------------------------------------//
void _AKUHideCursorFunc () {
	SDL_ShowCursor(false);
}
//----------------------------------------------------------------//
void _AKUShowCursorFunc () {
	SDL_ShowCursor(true);
}
//----------------------------------------------------------------//
void _AKUEnterFullscreenModeFunc () {
	SDL_SetWindowFullscreen(sWindow, SDL_WINDOW_FULLSCREEN);
	SetScreenSize( SDL_GetCurrentDisplayMode );
}
//----------------------------------------------------------------//
void _AKUExitFullscreenModeFunc () {
	SDL_SetWindowFullscreen(sWindow, 0);
	SetScreenSize( SDL_GetDesktopDisplayMode );
}
//----------------------------------------------------------------//
void _AKUResizeWindowFunc ( int width, int height ) {	
	AKUSetScreenSize ( width,height );	
	AKUSetViewSize ( width,height);	
	SDL_SetWindowSize(sWindow,width,height);
};
//----------------------------------------------------------------//
void _AKUTitleFunc(  const char* title ) {
	SDL_SetWindowTitle(sWindow,title);
};
//----------------------------------------------------------------//
void _AKUOpenWindowFunc ( const char* title, int width, int height ) {

	if ( !sWindow ) {
		sWindow = SDL_CreateWindow ( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |  SDL_WINDOW_RESIZABLE  );
		SDL_GL_CreateContext ( sWindow );
		SDL_GL_SetSwapInterval ( 1 );
		SDL_ShowCursor(true);
		AKUDetectGfxContext ();
		AKUSetScreenSize ( width, height );
	}
}
//================================================================//
// helpers
//================================================================//
static void	Finalize			();
static void	Init				( int argc, char** argv );
static void	MainLoop			();
static void	PrintMoaiVersion	();
//----------------------------------------------------------------//
void Finalize () {
	AKUModulesAppFinalize ();
	AKUAppFinalize ();
	SDL_Quit ();
}
//----------------------------------------------------------------//
void Init ( int argc, char** argv ) {

	SDL_Init ( SDL_INIT_EVERYTHING );

	PrintMoaiVersion ();

	AKUAppInitialize ();
	AKUModulesAppInitialize ();

	AKUCreateContext ();
	AKUModulesContextInitialize ();
	AKUModulesRunLuaAPIWrapper ();

	AKUSetInputConfigurationName ( "SDL" );

	AKUReserveInputDevices			( InputDeviceID::TOTAL );
	AKUSetInputDevice				( InputDeviceID::DEVICE, "device" );

	AKUReserveInputDeviceSensors	( InputDeviceID::DEVICE, InputSensorID::TOTAL );
	AKUSetInputDeviceKeyboard		( InputDeviceID::DEVICE, InputSensorID::KEYBOARD,		"keyboard" );
	AKUSetInputDevicePointer		( InputDeviceID::DEVICE, InputSensorID::POINTER,		"pointer" );
	AKUSetInputDeviceButton			( InputDeviceID::DEVICE, InputSensorID::MOUSE_LEFT,		"mouseLeft" );
	AKUSetInputDeviceButton			( InputDeviceID::DEVICE, InputSensorID::MOUSE_MIDDLE,	"mouseMiddle" );
	AKUSetInputDeviceButton			( InputDeviceID::DEVICE, InputSensorID::MOUSE_RIGHT,	"mouseRight" );

	AKUSetInputDeviceGameAnalog      ( InputDeviceID::DEVICE, InputSensorID::GAMEANALOG,  "gameAnalog" );
	AKUSetInputDeviceGameButton      ( InputDeviceID::DEVICE, InputSensorID::GAMEBUTTON,  "gameButton" );

	AKURunString("MOAISim.setTraceback(function() end)");   


	AKUSetFunc_EnterFullscreenMode ( _AKUEnterFullscreenModeFunc );
	AKUSetFunc_ExitFullscreenMode ( _AKUExitFullscreenModeFunc );

	AKUSetFunc_ShowCursor ( _AKUShowCursorFunc );
	AKUSetFunc_HideCursor ( _AKUHideCursorFunc );

	AKUSetFunc_OpenWindow ( _AKUOpenWindowFunc );

	AKUSetFunc_ResizeWindow ( _AKUResizeWindowFunc );
	AKUSetFunc_Title ( _AKUTitleFunc );

	AKUModulesParseArgs ( argc, argv );




	atexit ( Finalize ); // do this *after* SDL_Init



	//RUN	
	//AKUSetWorkingDirectory("F://moai//MOAI_GAMES//games//deaddark//game//lua//");
	//AKURunScript("F://moai//MOAI_GAMES//games//deaddark//game//lua//main.lua");
	printf("start these files\n");
	AKUSetWorkingDirectory("F://moai//MOAI_GAMES//games//DEADDARK//game//lua//app_tools//");
	AKURunScript("F://moai//MOAI_GAMES//games//DEADDARK//game//lua//app_tools//polygon.lua");

}

//----------------------------------------------------------------//
void MainLoop () {




Uint32 lastFrame = SDL_GetTicks();

	bool running = true;

	while ( running ) {

		SDL_Event sdlEvent;

		while ( SDL_PollEvent ( &sdlEvent )) {  

			switch ( sdlEvent.type )  {	

			case SDL_QUIT:

				running = false;
				break;

			case SDL_KEYDOWN:
			case SDL_KEYUP:	{
				int key = sdlEvent.key.keysym.sym;
				if (key & 0x40000000) key = (key & 0x3FFFFFFF) + 256;

				if ( (key == SDLK_RETURN) && (sdlEvent.key.keysym.mod & KMOD_ALT) && (sdlEvent.key.type == SDL_KEYDOWN) ) 
				{
					Uint32 flags = (SDL_GetWindowFlags(sWindow) ^ SDL_WINDOW_FULLSCREEN_DESKTOP);
					if (SDL_SetWindowFullscreen(sWindow, flags) < 0) 
					{

					}

				} else {		

					AKUEnqueueKeyboardEvent ( InputDeviceID::DEVICE, InputSensorID::KEYBOARD, key, sdlEvent.key.type == SDL_KEYDOWN );

				}; break;	


							} 	break;

			case SDL_WINDOWEVENT: 

				switch (sdlEvent.window.event) {

				case SDL_WINDOWEVENT_RESIZED: 					
					AKUSetScreenSize ( sdlEvent.window.data1,sdlEvent.window.data2 );
					AKUSetViewSize ( sdlEvent.window.data1,  sdlEvent.window.data2);
					break;
				case SDL_WINDOWEVENT_ENTER:			
					AKUSendFocus("MOUSE_ENTER");
					break;
				case SDL_WINDOWEVENT_LEAVE:				
					AKUSendFocus("MOUSE_EXIT");
					break;
				case SDL_WINDOWEVENT_MINIMIZED:				
					AKUSendFocus("WINDOW_MINIMIZED");
					break;
				case SDL_WINDOWEVENT_MAXIMIZED:
					AKUSendFocus("WINDO_MAXIMIZED");
					break;
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					AKUSendFocus("KEYBOARD_FOCUS_GAIN");
					break;
				case SDL_WINDOWEVENT_FOCUS_LOST:
					AKUSendFocus("KEYBOARD_FOCUS_LOST");
					break;			

				}; break;

			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:

				switch ( sdlEvent.button.button ) {

				case SDL_BUTTON_LEFT:
					AKUEnqueueButtonEvent ( InputDeviceID::DEVICE, InputSensorID::MOUSE_LEFT, ( sdlEvent.type == SDL_MOUSEBUTTONDOWN ));
					break;

				case SDL_BUTTON_MIDDLE:
					AKUEnqueueButtonEvent ( InputDeviceID::DEVICE, InputSensorID::MOUSE_MIDDLE, ( sdlEvent.type == SDL_MOUSEBUTTONDOWN ));
					break;

				case SDL_BUTTON_RIGHT:
					AKUEnqueueButtonEvent ( InputDeviceID::DEVICE, InputSensorID::MOUSE_RIGHT, ( sdlEvent.type == SDL_MOUSEBUTTONDOWN ));
					break;
				}

				break;

			case SDL_MOUSEMOTION:

				AKUEnqueuePointerEvent ( InputDeviceID::DEVICE, InputSensorID::POINTER, sdlEvent.motion.x, sdlEvent.motion.y );
				break;


			}
		}

		AKUModulesUpdate ();	
		SDL_GL_SwapWindow ( sWindow );

		Uint32 frameDelta			= ( Uint32 )( AKUGetSimStep () * 1000.0 );
		Uint32 currentFrame			= SDL_GetTicks ();
		Uint32 delta				= currentFrame - lastFrame;

		if ( delta < frameDelta ) {
			//printf("DELAY %d \n ",frameDelta - delta);
			SDL_Delay ( frameDelta - delta );
		}
		lastFrame = SDL_GetTicks();

		//SDL_Delay (1 );
	}
}







//----------------------------------------------------------------//
void PrintMoaiVersion () {
	static const int length = 255;
	char version [ length ];
	AKUGetMoaiVersion ( version, length );
	printf("--------------------------------------------------\n");
	printf ( "MOAI VERSION : %s\n", version );
	printf("---------------------------------------------------\n");
#ifdef _DEBUG
	printf ( "MOAI BUILD : DEBUG\n" );
	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG );
#else
	printf ( "MOAI BUILD : RELEASE\n" );
#endif
	printf("---------------------------------------------------\n");



//_CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );

//printf ( "MEMORY LEAKS :\n" );
//_CrtDumpMemoryLeaks();
//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
//_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );



}

//================================================================//
// SDLHost
//================================================================//

//----------------------------------------------------------------//
int SDLHost ( int argc, char** argv ) {

	Init ( argc, argv );

	if ( sWindow ) {
		MainLoop ();
	}
	#ifdef _DEBUG
	_CrtMemDumpAllObjectsSince(&state);
	//_CrtDumpMemoryLeaks();
	#endif
	
	return 0;
}
