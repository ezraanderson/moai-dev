print('ping pong')
--THREAD
local rot_thread = MOAIThread.new ()
--******************************************************************************
--******************************************************************************
--WAIT
local tick = 0
local dir  = 2
local function func_thread_rot ()

		while true do
	
			tick = tick + dir

			if tick > 380 then
				dir = dir * -1
			end

			if tick < -20 then
				dir = dir * -1
			end

			framebuffer['prop']:setRot(tick,0,0)
			coroutine.yield()

		end

end
--*****************************************************************
--*****************************************************************
function F._func_rotation_clean()
	print('*** ROTATION DONE ***')
	framebuffer['prop']:setRot(0,0,0)
	if rot_thread then
		rot_thread:stop ()
	end
end

--*****************************************************************
--*****************************************************************
function F._func_rotation_start()
	print('*** ROTATION START ***')
	framebuffer['prop']:setRot(0,0,0)
	if rot_thread then
		rot_thread:run ( func_thread_rot )
	end
end

