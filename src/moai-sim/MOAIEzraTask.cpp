// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIBox.h>
#include <moai-sim/MOAIEzraTask.h>


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

	
	while ( 1) {

	//printf("C>>>>>>>>>>>>>THREAD--Execute\n");	
			this->mMutex.Lock();	
					this->mData->Loop();				
			this->mMutex.Unlock();

			//capFrameRate(30);

		};

};




//----------------------------------------------------------------//
void MOAIEzraTask::Init ( MOAIBox& target, u32 action ) {

	///printf("C>>>>>>>>>>>>>THREAD--INIT\n");
	//this->mPriority = PRIORITY_LOW;
	this->mData.Set ( *this, &target );
	this->mAction = action;
	//this->

};



//----------------------------------------------------------------//
MOAIEzraTask::MOAIEzraTask () :
	mAction ( NONE )
	{	
	RTTI_SINGLE ( MOAITask )
}


//
////----------------------------------------------------------------//
MOAIEzraTask::~MOAIEzraTask () {

	//this->mData.Set ( *this, 0 );
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


