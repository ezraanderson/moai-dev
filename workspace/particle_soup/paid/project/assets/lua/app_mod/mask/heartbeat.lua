

print('***  heartbeat')

local mask_thread = MOAIThread.new ()
local mask_action = nil

local function wait ( action,idName )
	print('mask',idName)

	mask_action = action
	while action:isBusy () do 
		coroutine:yield () 
	end
end


local function threadFunc_mask ()
		while true do

				wait(mColor['color']:seekColor(0.1,1,0.1,1,4, MOAIEaseType.LINEAR),'HeartBeat_green')
				wait(mColor['color']:seekColor(1,0.1,0.1,1,4, MOAIEaseType.LINEAR),'HeartBeat_red')			
				wait(mColor['color']:seekColor(0.1,0.1,1,1,4, MOAIEaseType.LINEAR),'HeartBeat_blue')

				--wait(mColor['color']:seekColor(1,1,0.2,1,4, MOAIEaseType.LINEAR),'HeatBeat_yelow')
				--wait(mColor['color']:seekColor(1,0.2,1,1,4, MOAIEaseType.LINEAR),'HeatBeat_purple')
				--wait(mColor['color']:seekColor(0.2,1,1,1,4, MOAIEaseType.LINEAR),'HeatBeat_something')

				coroutine.yield()
		end

end

--******************************************************************************
function F._func_mask_clean()
	print('*** MASK CLEAN **')
	if mask_thread then 
		mask_thread:stop ( threadFunc_mask)	
	end

	if mask_action then
		mask_action:stop()
	end
end

--******************************************************************************
function F._func_mask_start()
	print('*** MASK START **')
	if mask_thread then 
		mask_thread:run ( threadFunc_mask )
	end
end