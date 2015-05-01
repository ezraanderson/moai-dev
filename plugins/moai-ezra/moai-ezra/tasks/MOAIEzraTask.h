// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAIEZRATHREAD_H
#define MOAIEZRATHREAD_H

#include <moai-util/MOAITask.h>

class MOAIDataBuffer;

//================================================================//
// MOAIEzraTask
//================================================================//
class MOAIEzraTask : 
	public MOAITask {
private:

	STLString								mFilename;
	MOAILuaSharedPtr < MOAIEzraParticleLayer >			mData;
	MOAILuaMemberRef						mOnFinish;
	u32										mAction;
	MOAIMutex								mMutex;
    bool									mLoopState;
	//bool									mInflateOnLoad;
	//bool									mInflateOnTaskThread;
	//int									mWindowBits;

	//THROTTLE
	double wait;  
	double diff;  
	double start;  

	//----------------------------------------------------------------//


public:

	enum {
		NONE,
		LOAD_ACTION,
		SAVE_ACTION,
	};



	DECL_LUA_FACTORY ( MOAIEzraTask )

	//----------------------------------------------------------------//
	void		Init				( MOAIEzraParticleLayer& target, u32 action );
				MOAIEzraTask		();
				~MOAIEzraTask		();

	void	    Execute				();
    void	    threadRunning		(bool isRun);
	void		Publish				();
	void		capFrameRate		(double fps);



	//void		RegisterLuaClass	( MOAILuaState& state );
	//void		RegisterLuaFuncs	( MOAILuaState& state );
	//void		SaveData			( cc8* filename, MOAIDataBuffer& target );
	//void		SetCallback			( lua_State* L, int idx );
	//void		SetInflateOnLoad	( bool inflateOnLoad, bool inflateOnTaskThread, int windowBits );
};

#endif
