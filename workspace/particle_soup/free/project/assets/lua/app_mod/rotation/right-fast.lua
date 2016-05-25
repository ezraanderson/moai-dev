print('RIGHT')

--ROT THREAD
local rot_thread = MOAIThread.new ()
--******************************************************************************
--******************************************************************************
--WAIT
local tick = 0
local function func_thread_rot ()

		while true do
				tick = tick + 6	
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
		rot_thread:stop (func_thread_rot)
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
