// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-util/MOAITaskThread.h>

//================================================================//
// MOAITaskThread main
//================================================================//

//----------------------------------------------------------------//
void MOAITaskThread::_main ( void* param, MOAIThreadState& threadState ) {

	MOAITaskThread* taskThread = ( MOAITaskThread* )param;
	
        //printf("\nxxxxx\n");
        //printf("\nxxxxx\n");
        //printf("\nxxxxx\n");
        //printf("\nxxxxx\n");
        //printf("\nxxxxx\n");
        //printf("\nxxxxx\n");

	while ( threadState.IsRunning ()) {         
		taskThread->Process ();
		MOAIThread::Sleep ();
   
	}
}

//================================================================//
// MOAITaskThread
//================================================================//

//----------------------------------------------------------------//
MOAITaskThread::MOAITaskThread () {
	RTTI_SINGLE ( MOAITaskQueue )
		//printf("\n \n **** CREATE CREATE MOAITaskThread --> FIRE DESTRUCTOR  \n\n");
}

//----------------------------------------------------------------//
MOAITaskThread::~MOAITaskThread () {
	// printf("\n \n ****  MOAITaskThread --> FIRE DESTRUCTOR  **** \n\n");
	this->Stop ();
}


//----------------------------------------------------------------//
void MOAITaskThread::PushTask ( MOAITask& task ) {

	MOAITaskQueue::PushTask ( task );
	this->mThread.Start ( _main, this, 0 );
}

//----------------------------------------------------------------//
void MOAITaskThread::RegisterLuaClass ( MOAILuaState& state ) {
	MOAITaskQueue::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAITaskThread::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAITaskQueue::RegisterLuaFuncs ( state );
}

//----------------------------------------------------------------//
void MOAITaskThread::Stop () {

        printf(" \n ******* THREAD IS BEING STOPED IN MOAITASKTHREAD--A ****** \n");	
    this->mThread.Stop ();
        printf(" \n ******* THREAD IS BEING STOPED IN MOAITASKTHREAD--B ****** \n");
	this->mThread.Join ();
        printf(" \n ******* THREAD IS BEING STOPED IN MOAITASKTHREAD--C ****** \n");
}

//----------------------------------------------------------------//
void MOAITaskThread::Join () {
	
	this->mThread.Join ();
}


////----------------------------------------------------------------//
//void MOAITaskThread::Start () {
//	
//	this->mThread->is
//}
