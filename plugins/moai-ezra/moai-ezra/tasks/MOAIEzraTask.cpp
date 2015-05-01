// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"

#include <moai-ezra/layers/MOAIEzraParticleLayer.h>
#include <moai-ezra/tasks/MOAIEzraTask.h>


#include <moai-sim/MOAISim.h>

//================================================================//
// MOAIEzraTask
//================================================================//


void MOAIEzraTask::capFrameRate(double fps) {

	
    wait = 1 / fps;
    diff = ZLDeviceTime::GetTimeInSeconds () - start;

    if (diff < wait) {
   
		//#ifdef MOAI_OS_ANDROID 
				//usleep(wait - diff);
				//usleep((wait - diff)*1000000);
				// __android_log_print(ANDROID_LOG_INFO, "C++", "sleep %s", "sim");
		//#endif

		//#ifndef MOAI_OS_WINDOWS
		//		Sleep ( wait - diff );
		//		printf(">> sleep %f  %f %f %f \n",wait , diff, USDeviceTime::GetTimeInSeconds (),wait - diff );
		//#endif 



    }
    start = ZLDeviceTime::GetTimeInSeconds ();
}
       

//----------------------------------------------------------------//
void MOAIEzraTask::Execute () {





   //while (this->mLoopState) {
   //     this->mMutex.Lock();
   //     // printf("LOOPING  THREAD\n");
   //      this->mMutex.Unlock();
   // };


  // this->mMutex.Clear();
 // this->mthr

    //if ( this->mLoopState == PAUSED ) {
	//	return;
	//}

    //while (this->mLoopState) {
    //     printf("LOOPING  THREAD\n");
    //};
	
	while (this->mLoopState) {

       //if (this->mLoopState) { return 1; };
	   //printf("C>>>>>>>>>>>>>THREAD--Execute\n");
        //
			//this->mMutex.Lock();	
			   this->mData->Loop();				
			//this->mMutex.Unlock();

			//capFrameRate(60);


           // printf("LOOPING  THREAD\n");

               //#ifndef MOAI_OS_WINDOWS
              //      usleep(1000);
              // #endif

	};



      printf("\n **** 2. MOAIEzraTask -> SHUT DOWN THREAD DONE **** \n");


};



void MOAIEzraTask::threadRunning ( bool isRun ) {

	//this->mMutex.Lock();
         this->mLoopState = isRun;
         printf("----- mLoopState\n");

	//this->mMutex.Unlock();

};


//void MOAIEzraTask::threadStop ( bool isRun ) {
//    this->mLoopState = isRun;
//};




//----------------------------------------------------------------//
void MOAIEzraTask::Init ( MOAIEzraParticleLayer& target, u32 action ) {

	///printf("C>>>>>>>>>>>>>THREAD--INIT\n");
	//this->mPriority = PRIORITY_LOW;
    this->mLoopState = true;
	this->mData.Set ( *this, &target );
	

	//this->mAction = action;


};



//----------------------------------------------------------------//
MOAIEzraTask::MOAIEzraTask () :
mAction      ( NONE ),
	mLoopState   ( false )
{	
	RTTI_SINGLE ( MOAITask )
}


//
////----------------------------------------------------------------//
MOAIEzraTask::~MOAIEzraTask () {   
	// printf("a \n");

	this->mData.Set ( *this, 0 ); 
	this->mLoopState =   false;
	printf("\n \n **** 1. MOAIEzraTask --> FIRE DESTRUCTOR  ****  \n\n");

	// printf("b \n");
}


//----------------------------------------------------------------//
void MOAIEzraTask::Publish () {




	//if ( this->mInflateOnLoad && ( !this->mInflateOnTaskThread )) {
	//	this->mData->Inflate ( this->mWindowBits );
	//}

	//if ( this->mOnFinish ) {
	
			//	MOAILuaStateHandle state = MOAILuaRuntime::Get ().State ();
			//	this->PushLocal ( state, this->mOnFinish );
			//	this->mData->PushLuaUserdata ( state );
			//	state.DebugCall ( 1, 0 );
	//}
}


