print('***  twilight')

local mask_thread = MOAIThread.new ()
local mask_action = nil

local function wait ( action,idName )

	print('mask : twilight',idName)
	mask_action = action
	while action:isBusy () do 
		coroutine:yield () 
	end
end


local function threadFunc_mask ()
		while true do

				--print('run mask')
				wait(mColor['color']:seekColor(0.1,1,0.1,0.3,4, MOAIEaseType.LINEAR),'twilight_green')
				wait(mColor['color']:seekColor(1,0.1,0.1,0.3,4, MOAIEaseType.LINEAR),'twilight_red')			
				wait(mColor['color']:seekColor(0.1,0.1,1,0.2,4, MOAIEaseType.LINEAR),'twilight_blue')
				wait(mColor['color']:seekColor(1,1,1,0.3,4, MOAIEaseType.LINEAR),'twilight_white')
				coroutine.yield()
		end

end

--******************************************************************************
function F._func_mask_clean()
	print('*** MASK CLEAN **')
	mask_thread:stop ( threadFunc_mask)	
	mask_action:stop()
end

--******************************************************************************
function F._func_mask_start()
	print('*** MASK START **')
	mask_thread:run ( threadFunc_mask )
end