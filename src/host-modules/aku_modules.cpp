// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <string.h>
#include <host-modules/aku_modules.h>
#include <lua-headers/moai_lua.h>

#include <moai-sim/MOAIBox.h>

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <errno.h>
//#include <libproc.h>
//#include <unistd.h>

//#include <stdio.h>  /* defines FILENAME_MAX */
//#ifdef MOAI_OS_WINDOWS
//    #include <direct.h>
//    #define GetCurrentDir _getcwd
//#else
//    #include <unistd.h>
//    #define GetCurrentDir getcwd
// #endif



 #ifdef MOAI_OS_OSX
      #include <mach-o/dyld.h>
      #include <libgen.h>
 #endif



//================================================================//
// implementation
//================================================================//

//----------------------------------------------------------------//
void AKUModulesAppFinalize () {
	

    printf("\n ******** AKUModulesAppFinalize ***********\n");

//FINILIZE MY TASKS
    MOAIBox::Finalize();





	#if AKU_WITH_BOX2D
		AKUBox2DAppFinalize ();
	#endif

	#if AKU_WITH_CHIPMUNK
		AKUChipmunkAppFinalize ();
	#endif

	#if AKU_WITH_FMOD_DESIGNER
		AKUFmodDesignerAppFinalize ();
	#endif

	#if AKU_WITH_FMOD_EX
		AKUFmodExAppFinalize ();
	#endif

	#if AKU_WITH_HARNESS
		AKUHarnessAppFinalize ();
	#endif

	#if AKU_WITH_HTTP_CLIENT
		AKUHttpClientAppFinalize ();
	#endif

	#if AKU_WITH_HTTP_SERVER
		AKUHttpServerAppFinalize ();
	#endif

	#if AKU_WITH_LUAEXT
		AKULuaExtAppFinalize ();
	#endif

	#if AKU_WITH_SIM
		AKUSimAppFinalize ();
	#endif

	#if AKU_WITH_TEST
		AKUTestAppFinalize ();
	#endif

	#if AKU_WITH_UNTZ
		AKUUntzAppFinalize ();
	#endif

	#if AKU_WITH_UTIL
		AKUUtilAppFinalize ();
	#endif

	#if AKU_WITH_PLUGINS
		AKUPluginsAppFinalize ();
	#endif
}

//----------------------------------------------------------------//
void AKUModulesAppInitialize () {

	#if AKU_WITH_BOX2D
		AKUBox2DAppInitialize ();
	#endif

	#if AKU_WITH_CHIPMUNK
		AKUChipmunkAppInitialize ();
	#endif

	#if AKU_WITH_FMOD_DESIGNER
		AKUFmodDesignerAppInitialize ();
	#endif

	#if AKU_WITH_FMOD_EX
		AKUFmodExAppInitialize ();
	#endif

	#if AKU_WITH_HARNESS
		AKUHarnessAppInitialize ();
	#endif

	#if AKU_WITH_HTTP_CLIENT
		AKUHttpClientAppInitialize ();
	#endif

	#if AKU_WITH_HTTP_SERVER
		AKUHttpServerAppInitialize ();
	#endif

	#if AKU_WITH_LUAEXT
		AKULuaExtAppInitialize ();
	#endif

	#if AKU_WITH_SIM
		AKUSimAppInitialize ();
	#endif

	#if AKU_WITH_TEST
		AKUTestAppInitialize ();
	#endif

	#if AKU_WITH_UNTZ
		AKUUntzAppInitialize ();
	#endif

	#if AKU_WITH_UTIL
		AKUUtilAppInitialize ();
	#endif

	#if AKU_WITH_PLUGINS
		AKUPluginsAppInitialize ();
	#endif
}

//----------------------------------------------------------------//
void AKUModulesContextInitialize () {

	#if AKU_WITH_BOX2D
		AKUBox2DContextInitialize ();
	#endif

	#if AKU_WITH_CHIPMUNK
		AKUChipmunkContextInitialize ();
	#endif

	#if AKU_WITH_FMOD_DESIGNER
		AKUFmodDesignerContextInitialize ();
	#endif

	#if AKU_WITH_FMOD_EX
		AKUFmodExContextInitialize ();
	#endif

	#if AKU_WITH_HARNESS
		AKUHarnessContextInitialize ();
	#endif

	#if AKU_WITH_HTTP_CLIENT
		AKUHttpClientContextInitialize ();
	#endif

	#if AKU_WITH_HTTP_SERVER
		AKUHttpServerContextInitialize ();
	#endif

	#if AKU_WITH_LUAEXT
		AKULuaExtContextInitialize ();
	#endif

	#if AKU_WITH_SIM
		AKUSimContextInitialize ();
	#endif

	#if AKU_WITH_TEST
		AKUTestContextInitialize ();
	#endif

	#if AKU_WITH_UNTZ
		AKUUntzContextInitialize ();
	#endif

	#if AKU_WITH_UTIL
		AKUUtilContextInitialize ();
	#endif

	#if AKU_WITH_PLUGINS
		AKUPluginsContextInitialize ();
	#endif
}

//----------------------------------------------------------------//
void AKUModulesParseArgs ( int argc, char** argv ) {

	#if AKU_WITH_TEST

		int total = argc - 1;
		int i = 1;

		for ( ; i < total; ++i ) {
		
			char* arg = argv [ i ];
		
			if ( arg [ 0 ] != '-' ) break;
		
			// filter file
			if ( strcmp ( arg, "-f" ) == 0 ) {
				AKUTestSetFilterFile ( argv [ ++i ]);
			}
		
			// filter
			if ( strcmp ( arg, "-F" ) == 0 ) {
				AKUTestSetFilter ( argv [ ++i ]);
			}
		
			// results
			if ( strcmp ( arg, "-r" ) == 0 ) {
				AKUTestSetResultsFile ( argv [ ++i ]);
			}
		
			// staging
			if ( strcmp ( arg, "-s" ) == 0 ) {
				AKUTestSetStaging ();
			}
		
			// test
			if ( strcmp ( arg, "-t" ) == 0 ) {
				AKUTestRunTest ( argv [ ++i ]);
			}

			// xml results
			if ( strcmp ( arg, "-x" ) == 0 ) {
				AKUTestSetXmlResultsFile ( argv [ ++i ]);
			}
		}

		for ( ; i < argc; ++i ) {
			AKUTestRunScript ( argv [ i ]);
		}
		
	#else
	printf("\n 1. MODULE ******* LOADING GAME ********** \n");

    if ( argc < 2 ) {




//printf("Arg 0 is %s\n", argv[0]);
//printf("argc  is %s\n", argc);   

////DOESN"T WORK
//char buffer[1024];
//char *answer = getcwd(buffer, sizeof(buffer));
//string s_cwd;
//if (answer)
//{
//    s_cwd = answer;
//}
//
// printf("THE PATH %s \n\n", answer);
//

    //int ret;
    //pid_t pid; 
    //char pathbuf[PROC_PIDPATHINFO_MAXSIZE];

    //pid = getpid();
    //ret = proc_pidpath (pid, pathbuf, sizeof(pathbuf));
    //if ( ret <= 0 ) {
    //    fprintf(stderr, "PID %d: proc_pidpath ();\n", pid);
    //    fprintf(stderr, "    %s\n", strerror(errno));
    //} else {
    //    printf("proc %d: %s\n", pid, pathbuf);
    //}

   //char the_path[1024];

   // getcwd(the_path, 1024);
   // strcat(the_path, "/");
   // strcat(the_path, argv[0]);
   // printf("THE PATH %s \n\n", the_path);

             // printf("\n 2.  MODULE ******* GETTING  PATH ********** \n");
             // AKURunString("print(MOAIFileSystem.getWorkingDirectory())");
             // AKURunString("print(MOAIEnvironment.resourceDirectory) ");
             // AKURunString("require 'main'");



////////////////////////////////
//DOESN"T WORK
 //char cCurrentPath[FILENAME_MAX];

 //if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
 //    {
 //       //return error;
 //    };

 //   cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; 

 //   printf ("The current working directory is %s \n", cCurrentPath);



                    //DOESN'T WORK
                    //STLString result = ZLFileSys::GetCurrentPath ();
                    //string file_to_load = result + "/main.lua";
                   // std::string str;
                    //const char * c = file_to_load.c_str();   
                    //printf("file to path is %s\n", combine);

                   // string file_to_load = "moai.lua";





            #ifdef MOAI_OS_OSX

                char path[1024];

                uint32_t size = sizeof(path);
                if (_NSGetExecutablePath(path, &size) == 0) {
                    printf("executable path is %s\n", path);
                } else {
                    printf("buffer too small; need size %u\n", size);
                }     
                
                char * program_name = dirname(path);
                printf ("The current working directory is %s \n", program_name);  
                ZLFileSys::SetCurrentPath(program_name);

    

            #endif


			 AKURunScript ( "main.lua" );
             AKURunScript ( "main.luac" );


		}
		else {

			AKUSetArgv ( argv );

			for ( int i = 1; i < argc; ++i ) {
				char* arg = argv [ i ];
				if (( strcmp ( arg, "-s" ) == 0 ) && ( ++i < argc )) {
					char* script = argv [ i ];
					AKURunString ( script );
				}
				else {
					AKURunScript ( arg );
				}
			}
		}
	
	#endif
}

//----------------------------------------------------------------//
void AKUModulesRunLuaAPIWrapper () {

	AKURunData ( moai_lua, moai_lua_SIZE, AKU_DATA_STRING, AKU_DATA_ZIPPED );
}

//----------------------------------------------------------------//
void AKUModulesUpdate () {

	#if AKU_WITH_FMOD_DESIGNER
		AKUFmodDesignerUpdate ();
	#endif
	
	#if AKU_WITH_FMOD_EX
		AKUFmodExUpdate ();
	#endif
	
	#if AKU_WITH_HARNESS
		AKUHarnessUpdate ()
	#endif

	#if AKU_WITH_SIM
		AKUUpdate ();
	#endif

	#if AKU_WITH_PLUGINS
		AKUPluginsUpdate ();
	#endif


}

void AKUModulesPause () {
	#if AKU_WITH_UNTZ
		AKUUntzPause ();
	#endif
	
	#if AKU_WITH_SIM
		AKUPause ( true );
	#endif

}

void AKUModulesResume () {
	#if AKU_WITH_UNTZ
		AKUUntzResume ();
	#endif

	#if AKU_WITH_SIM
		AKUPause ( false );
	#endif
}