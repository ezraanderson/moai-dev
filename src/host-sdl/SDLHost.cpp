// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com




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

const int CONTROLLERS_DEAD_ZONE = 3200;
#define MAX_CONTROLLERS 4
//SDL_GameController *ControllerHandles[MAX_CONTROLLERS];
SDL_Joystick *ControllerHandles[MAX_CONTROLLERS];

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

 void print_SDL_version(char* preamble, SDL_version* v) {
   printf("%s %u.%u.%u\n", preamble, v->major, v->minor, v->patch);
 }

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

	//SDL_Init ( SDL_INIT_EVERYTHING );
	SDL_Init(SDL_INIT_GAMECONTROLLER);

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











	//SDL_Joystick *joy;
	// 2. Use the first available compatible game controller.

	//for (int i = 0; i < SDL_NumJoysticks(); i++) {


	//		//joy = SDL_JoystickOpen(i);
	//		//if (joy) {

	//		//	printf("Opened Joystick 0\n");
	//		//	printf("Name: %s\n", SDL_JoystickNameForIndex(i));
	//		//	printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joy));
	//		//	printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
	//		//	printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy));

	//	
	//		//}
	//		//else {
	//		//	printf("Couldn't open Joystick 0\n");
	//		//}



	//		char guid[124];
	//		const char *name;
	//		const char *description = "Joystick (not recognized as game controller)";

	//		
	//		if (SDL_IsGameController(i))
	//		{				
	//			printf("YES \n");
	//			name = SDL_GameControllerNameForIndex(i);
	//		}
	//		else {
	//			printf("NO \n");
	//			name = SDL_GameControllerNameForIndex(i);
	//		}


	//		SDL_JoystickGetGUIDString(SDL_JoystickGetDeviceGUID(i), guid, sizeof(guid));
	//		printf("guid %s %s %s\n", description,guid, name);
	//
	//	}	
	
	//SDL_GameControllerEventState(SDL_ENABLE);
	//ControllerHandles[0] = SDL_GameControllerOpen(0);




	ControllerHandles[0] = SDL_JoystickOpen(0);
	int MaxJoysticks = SDL_NumJoysticks();
	int ControllerIndex = 0;
	for (int JoystickIndex = 0; JoystickIndex < MaxJoysticks; ++JoystickIndex)
	{
		if (ControllerIndex >= MAX_CONTROLLERS)
		{
			break;
		}
		ControllerHandles[ControllerIndex] = SDL_JoystickOpen(ControllerIndex);
		ControllerIndex++;
	}





	atexit ( Finalize ); // do this *after* SDL_Init




	//RUN	
	//AKUSetWorkingDirectory("F://moai//MOAI_GAMES//games//deaddark//game//lua//");
	//AKURunScript("F://moai//MOAI_GAMES//games//deaddark//game//lua//main.lua");
	printf("start these files\n");

	//AKUSetWorkingDirectory("F://moai//MOAI_GAMES//games//DEADDARK//game//lua//app_tools//");
	//AKURunScript("F://moai//MOAI_GAMES//games//DEADDARK//game//lua//app_tools//polygon.lua");

}







//void AddController(int id)
//{
//	if (SDL_IsGameController(id)) {
//		SDL_GameController *pad = SDL_GameControllerOpen(id);
//
//		if (pad) {
//			SDL_Joystick *joy = SDL_GameControllerGetJoystick(pad);
//			int instanceID = SDL_JoystickInstanceID(joy);
//
//			// You can add to your own map of joystick IDs to controllers here.
//			YOUR_FUNCTION_THAT_CREATES_A_MAPPING(id, pad);
//		}
//	}
//}
//
//void RemoveController(int id)
//{
//	SDL_GameController *pad = YOUR_FUNCTION_THAT_RETRIEVES_A_MAPPING(id);
//	SDL_GameControllerClose(pad);
//}




void OnControllerButton(const SDL_ControllerButtonEvent sdlEvent)
{
	// Button presses and axis movements both sent here as SDL_ControllerButtonEvent structures
	//AKUEnqueueKeyboardEvent(InputDeviceID::DEVICE, InputSensorID::KEYBOARD, key, sdlEvent.key.type == SDL_KEYDOWN);
}

void OnControllerAxis(const SDL_ControllerAxisEvent sdlEvent)
{
	// Axis movements and button presses both sent here as SDL_ControllerAxisEvent structures

	//AKUEnqueueGameAnalogEvent(sdlEvent.jaxis.which)

	//AKU_API void			AKUEnqueueGameAnalogEvent(int deviceID, int sensorID, int idPlayer, float leftAxisX, float leftAxisY, float rightAxisX, float rightAxisY);
	//AKU_API void			AKUEnqueueGameButtonEvent(int deviceID, int sensorID, int idPlayer, bool isDown, int idKey);

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

			//case SDL_CONTROLLERDEVICEADDED:
				//AddController(sdlEvent.cdevice);
			//	break;

			//case SDL_CONTROLLERDEVICEREMOVED:
				//RemoveController(sdlEvent.cdevice);
			//	break;			

			//case SDL_CONTROLLERAXISMOTION:			

			//case SDL_JOYAXISMOTION:

				//printf("Joystick %d player %d axis %d move\n", sdlEvent.jaxis.which, sdlEvent.jaxis.axis , sdlEvent.jaxis.value);


			case SDL_JOYHATMOTION:

				if (sdlEvent.jhat.value == SDL_HAT_LEFT ) {
					printf("player %d button %d down\n", sdlEvent.jhat.which, 12);
				}
				else if (sdlEvent.jhat.value == SDL_HAT_RIGHT) {
					printf("player %d button %d down\n", sdlEvent.jhat.which, 13);
				}
				else if (sdlEvent.jhat.value == SDL_HAT_UP) {
					printf("Joystick %d button %d down\n", sdlEvent.jhat.which, 14);
				}
				else if (sdlEvent.jhat.value == SDL_HAT_DOWN) {
					printf("player %d button %d down\n", sdlEvent.jhat.which, 15);
				};
				break;
			case SDL_JOYBUTTONDOWN:
			//case SDL_CONTROLLERBUTTONDOWN:

	
				printf("player %d button %d down\n", sdlEvent.jbutton.which, sdlEvent.jbutton.button);




			//	std::cout << (int)sdlEvent.cbutton.button << " controller button up \n";
				//std::cout << "A button: " << (int)SDL_GameControllerGetButton(ControllerHandles[0], SDL_CONTROLLER_BUTTON_A) << " : " << (int)sdlEvent.cbutton.button  << std::endl;
				//std::cout << "B button: " << (int)SDL_GameControllerGetButton(ControllerHandles[0], SDL_CONTROLLER_BUTTON_B) << " : " << (int)sdlEvent.cbutton.button << std::endl;
				//std::cout << "X button: " << (int)SDL_GameControllerGetButton(ControllerHandles[0], SDL_CONTROLLER_BUTTON_X) << " : " << (int)sdlEvent.cbutton.button << std::endl;
				//std::cout << "Y button: " << (int)SDL_GameControllerGetButton(ControllerHandles[0], SDL_CONTROLLER_BUTTON_Y) << " : " << (int)sdlEvent.cbutton.button << std::endl;

				//std::cout << "LEFT_SHOULDER " << (int)SDL_GameControllerGetButton(ControllerHandles[0], SDL_CONTROLLER_BUTTON_LEFTSHOULDER) << std::endl;
				//std::cout << "RIGHT_SHOULDER: " << (int)SDL_GameControllerGetButton(ControllerHandles[0], SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) << std::endl;

				//std::cout << "TRIGGER_LEFT: " << (int)SDL_GameControllerGetButton(ControllerHandles[0], SDL_CONTROLLER_BUTTON_LEFTTRIGGER) << std::endl;
				//std::cout << "TRIGGER_RIGHT: " << (int)SDL_GameControllerGetButton(ControllerHandles[0], SDL_CONTROLLER_BUTTON_RIGHTTRIGGER) << std::endl;


				//std::cout << "STICK_LEFT: " << (int)SDL_GameControllerGetButton(ControllerHandles[0], SDL_CONTROLLER_BUTTON_LEFTSTICK) << std::endl;
				//std::cout << "STICK_RIGHT: " << (int)SDL_GameControllerGetButton(ControllerHandles[0], SDL_CONTROLLER_BUTTON_RIGHTSTICK) << std::endl;

				//std::cout << "D_LEFT: " << (int)SDL_GameControllerGetButton(ControllerHandles[0], SDL_CONTROLLER_BUTTON_DPAD_LEFT) << std::endl;
				//std::cout << "D_RIGHT: " << (int)SDL_GameControllerGetButton(ControllerHandles[0], SDL_CONTROLLER_BUTTON_DPAD_RIGHT) << std::endl;

				//std::cout << "D_UP: " << (int)SDL_GameControllerGetButton(ControllerHandles[0], SDL_CONTROLLER_BUTTON_DPAD_UP) << std::endl;
				//std::cout << "D_DOWN: " << (int)SDL_GameControllerGetButton(ControllerHandles[0], SDL_CONTROLLER_BUTTON_DPAD_DOWN) << std::endl;

				//std::cout << "BACK: " << (int)SDL_GameControllerGetButton(ControllerHandles[0], SDL_CONTROLLER_BUTTON_BACK) << std::endl;
				//std::cout << "START: " << (int)SDL_GameControllerGetButton(ControllerHandles[0], SDL_CONTROLLER_BUTTON_START) << std::endl;

				//std::cout << "GUID: " << (int)SDL_GameControllerGetButton(ControllerHandles[0], SDL_CONTROLLER_BUTTON_GUIDE) << std::endl;

				//printf("which %d", sdlEvent.cbutton.which);
				//event.jbutton.which, event.jbutton.button
				//AKUEnqueueGameButtonEvent(InputDeviceID::DEVICE, InputSensorID::GAMEBUTTON, 1, true, sdlEvent.jbutton.button);
				
				break;
			case SDL_CONTROLLERBUTTONUP:	
			//	AKUEnqueueGameButtonEvent(InputDeviceID::DEVICE, InputSensorID::GAMEBUTTON, 1, false, sdlEvent.cbutton.button);
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




		float left_x = 0;
		float left_y = 0;

		float right_x = 0;
		float right_y = 0;


		left_x = SDL_JoystickGetAxis(ControllerHandles[0], 0);
		left_y = SDL_JoystickGetAxis(ControllerHandles[0], 1);
		right_x = SDL_JoystickGetAxis(ControllerHandles[0], 2);
		right_y = SDL_JoystickGetAxis(ControllerHandles[0], 3);

		if ((left_x > -CONTROLLERS_DEAD_ZONE) && (left_x <  CONTROLLERS_DEAD_ZONE)) { left_x = 0; }
		if ((left_y > -CONTROLLERS_DEAD_ZONE) && (left_y <  CONTROLLERS_DEAD_ZONE)) { left_y = 0; }

		if ((right_x > -CONTROLLERS_DEAD_ZONE) && (right_x <  CONTROLLERS_DEAD_ZONE)) { right_x = 0; }
		if ((right_y > -CONTROLLERS_DEAD_ZONE) && (right_y <  CONTROLLERS_DEAD_ZONE)) { right_y = 0; }


		if (left_x != 0 || left_y != 0 || right_x != 0 || right_y != 0) {
			AKUEnqueueGameAnalogEvent(InputDeviceID::DEVICE, InputSensorID::GAMEANALOG, 1,
				left_x, left_y,
				right_x, right_y
				);
		}




		//********************************************************************************************************************
		//********************************************************************************************************************
		//********************************************************************************************************************
		//********************************************************************************************************************


			
			//left_x = 0;
			//left_y = 0;

			//right_x = 0;
			//right_y = 0;

			//left_x = SDL_GameControllerGetAxis(ControllerHandles[0], (SDL_GameControllerAxis)(0));
			//left_y = SDL_GameControllerGetAxis(ControllerHandles[0], (SDL_GameControllerAxis)(1));

			//right_x = SDL_GameControllerGetAxis(ControllerHandles[0], (SDL_GameControllerAxis)(3));
			//right_y = SDL_GameControllerGetAxis(ControllerHandles[0], (SDL_GameControllerAxis)(2));



			//if ((left_x > -CONTROLLERS_DEAD_ZONE) && (left_x <  CONTROLLERS_DEAD_ZONE)) { left_x = 0; }
			//if ((left_y > -CONTROLLERS_DEAD_ZONE) && (left_y <  CONTROLLERS_DEAD_ZONE)) { left_y = 0; }

			//if ((right_x > -CONTROLLERS_DEAD_ZONE) && (right_x <  CONTROLLERS_DEAD_ZONE)) { right_x = 0; }
			//if ((right_y > -CONTROLLERS_DEAD_ZONE) && (right_y <  CONTROLLERS_DEAD_ZONE)) { right_y = 0; }	


			//if (left_x != 0 || left_y != 0 || right_x != 0 || right_y != 0) {
			//	AKUEnqueueGameAnalogEvent(InputDeviceID::DEVICE, InputSensorID::GAMEANALOG, 1,
			//		left_x, left_y,
			//		right_x, right_y
			//		);
			//}

			//printf("%d %d %d %d\n", left_x, left_y, right_x, right_y);



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

 printf("-----------------------------------------------------------------------------------------\n");	
 SDL_version ver;
 SDL_VERSION(&ver);
 print_SDL_version("SDL VERSION: ", &ver);



static const int length = 255;
char version [ length ];
AKUGetMoaiVersion ( version, length );
 printf("-----------------------------------------------------------------------------------------\n");	
printf ( "MOAI VERSION : %s\n", version );
 printf("-----------------------------------------------------------------------------------------\n");	

#ifdef _DEBUG
	printf ( "MOAI BUILD : DEBUG\n" );
		//_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG );
		//_CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
		//printf ( "MEMORY LEAKS :\n" );
		//_CrtDumpMemoryLeaks();
		//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
		//_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );

#else
	printf ( "MOAI BUILD : RELEASE\n" );
#endif
 printf("-----------------------------------------------------------------------------------------\n");	







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


	//for (int ControllerIndex = 0; ControllerIndex < MAX_CONTROLLERS; ++ControllerIndex)
	//{
	//	if (ControllerHandles[ControllerIndex])
	//	{
	//		SDL_GameControllerClose(ControllerHandles[ControllerIndex]);
	//	}
	//}



	//#ifdef _DEBUG
	//_CrtMemDumpAllObjectsSince(&state);
	////_CrtDumpMemoryLeaks();
	//#endif
	
	return 0;
}
