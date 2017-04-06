--require("config")




--***************************
--this is odd


--	_G.EZSIM = {}
	
--	_G.EZSIM['width'] = 800
--	_G.EZSIM['height'] = 688

	
	
	
	
	
	
	
	


ip_address  =  "192.168.1.6"
--ip_address  = '174.35.247.82'
--ip_address  =  "10.0.0.6"
game_name   = 'soup'
game_mode   = 1
game_user   = 'ezra'





if game_name == 'smash' then
	MOAISim.openWindow ( "test",  1280,720 )
elseif game_name == 'word' then
	MOAISim.openWindow ( "test",  800,600 )
elseif game_name == 'soup' then
--	MOAISim.openWindow ( "test",  1280,720 )
	MOAISim.openWindow ( "test",  1280,720 )
elseif game_name == 'ouya' then
--	MOAISim.openWindow ( "test",  1280,720 )
	MOAISim.openWindow ( "test",  1280,720 )
end




--******************************************************************************
--local ez

local function file_exists(name)

	   local f=io.open(name,"r")
	   if f~=nil then io.close(f) 	   
	   			return true 
	   else 
	   			return false 
	   end
end



function ez_require(filename)

		local path_luac = package.gamepath..'//'..filename..'.luac-back'
		
			if file_exists(path_luac) then
		
			     print('\tLUAC>>',path_luac) 	
			        
			     return loadfile(path_luac)()
			else
			      
				 print('/t/tSHIT>>',filename) 			      

			   	 return require(filename)
			end
                             
end









local ip_address = 'http://'..ip_address..':8080'

--******************************************************************************
--******************************************************************************
--******************************************************************************
--print trace
io.output():setvbuf("no")

--	 local pprint = print
--	 function print(...)
--
--					   --*************************
--					   local debugFlag = false
--					   --*************************
--					   if debugFlag  == true then
--
--                                   local info = debug.getinfo(2, "Sl")
--							       local lineNumber   = info.currentline
--							       local luaFile      = info.short_src
--							       local functionName = debug.getinfo(2, "n").name
--
--								    pprint(lineNumber,luaFile,functionName,...)
--
--						else
--						    pprint(...)
--						end
--
--
--	 end
--
--******************************************************************************
--******************************************************************************
--******************************************************************************



--******************************************************************************
--load systems headers
require("system_update")



--******************************************************************************





--*****************************************************************************
local function indexOf(array, value)
    for i, v in ipairs(array) do
        if v == value then
            return i
        end
    end
    return 0
end

table.indexOf = indexOf







--*************************************************************
--from init and config


--andriod screen size  540, 960

--MOAISim.openWindow ( "test",  320, 480 ) --not need with moai




--MOAISim.openWindow ( "test",  320, 480 ) 
--MOAISim.openWindow ( "test",  480, 320 )
--MOAISim.openWindow ( "test",  800, 600 )
--MOAISim.isFullScreen = false --flag for full screen

--

--MOAISim.clearLoopFlags ()
--MOAISim.setLoopFlags ( MOAISim.SIM_LOOP_ALLOW_BOOST )
--MOAISim.setLoopFlags ( MOAISim.SIM_LOOP_LONG_DELAY )
--MOAISim.setBoostThreshold ( 0 )

--MOAISim.setLoopFlags ( MOAISim.LOOP_FLAGS_FIXED)


--  MOAISim.clearLoopFlags ( )
--  MOAISim.setLoopFlags ( MOAISim.SIM_LOOP_ALLOW_SPIN )
--  MOAISim.setLoopFlags ( MOAISim.SIM_LOOP_ALLOW_SOAK )
--  MOAISim.setLoopFlags ( MOAISim.SIM_LOOP_ALLOW_BOOST )
--  MOAISim.setBoostThreshold ( 10 )
--  MOAISim.setLoopFlags ( MOAISim.SIM_LOOP_LONG_DELAY )
--  MOAISim.setLongDelayThreshold ( 10 )
--  MOAISim.setStep ( 1 / 66 )
--  
  
  
  
  
  
  
  
  
  
  


local update_viewport = MOAIViewport.new ()


		--update_viewport:setSize ( 320, 480 )
		--update_viewport:setScale ( 320, -480 )
		--update_viewport:setOffset ( -1, 1 )




		update_viewport:setSize ( 1280,720 )
		update_viewport:setScale ( 1280,-720)
		update_viewport:setOffset ( -1, 1 )





local update_layer = MOAILayer2D.new ()
		update_layer:setViewport ( update_viewport )
		MOAISim.pushRenderPass ( update_layer )

local charcodes = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 .,:;!?()&/-'
local text = 'The quick <c:f70>brown<c> fox jumps over the <c:7f3>lazy<c> dog.'

local font = MOAIFont.new ()
		font:loadFromTTF ('arialrounded.ttf', charcodes, 8, 163 )





----loading
local  textboxA = MOAITextBox.new ()
		textboxA:setString ( 'loading' )
		textboxA:setWordBreak(MOAITextBox.WORD_BREAK_CHAR)
		textboxA:setFont ( font )
		textboxA:setTextSize ( 10, 163 )
		textboxA:setRect ( 0, 0, 320, 480 )
		textboxA:setLoc (20,100 )
		update_layer:insertProp ( textboxA )



--file
local 	textboxB = MOAITextBox.new ()
		textboxB:setString ( 'file' )
		textboxB:setFont ( font )
		textboxB:setTextSize ( 10, 163 )
		textboxB:setRect ( 0, 0, 320, 480 )
		textboxB:setLoc (20,150 )
		update_layer:insertProp ( textboxB )



 --update
local textboxC = MOAITextBox.new ()
		textboxC:setString ( 'y: update \nn: skip ' )

		textboxC:setFont ( font )
		textboxC:setTextSize ( 10, 163 )
		textboxC:setRect ( 0, 0, 320, 480 )
		textboxC:setLoc (20,10 )
		update_layer:insertProp ( textboxC )
		--












--*************************************************************
--updatecode


--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--******************************************************************************
--netowrk
local network = {}

--local task_post = MOAIHttpTask.new ()
print('MOAIHttpTask',		MOAIHttpTask)
--print('MOAIHttpTaskBase',	MOAIHttpTaskBase)
print('MOAIHttpTaskCurl ',	MOAIHttpTaskCurl )
--print('MOAIHttpTaskNSURL ',	MOAIHttpTaskNSURL )
--print('MOAIHttpTaskNaCl',	MOAIHttpTaskNaCl)

	local task_post = MOAIHttpTask.new()

	  task_post:setVerb ( MOAIHttpTaskCurl.HTTP_POST )
	  task_post:setUserAgent ( "task_smash" )
	  task_post:setVerbose ( false )
	  --task_post:performAsync ()

      

function  network.request(url,get_post,callback,params)

		task_post:setUrl ( url )
		task_post:setBody ( params )
		task_post:setCallback ( callback )
		task_post:performSync () --very fast
		--task_post:performAsync () --very slow
end








--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
 

local task_get = MOAIHttpTask.new ()
	  task_get:setVerb ( MOAIHttpTask.HTTP_GET )
      task_get:setUserAgent ( "task_smash" )
	  task_get:setTimeout ( 5000 )
	  task_get:setVerbose ( false )


function  network.download(url,callback,pathSave,fileName,ttouch)




print('download',url)
		--******************************
		--write file
		local function saveFile(task, responseCode)

						local event = {}
						      event.response = 400

								if responseCode == 200 then

							       event.response = 200


										--write-mode for font
--										local writeMod = "w"
--										
--										--**************************************
--										--font binary
--										print('>>>>>>>>>>>>>>>>>', fileName )
--		           						if  string.find(fileName, '.ttf') ~= nil then
--
--											 	      writeMod = "wb"
--
--											 	      print('***********************shit font**************')
--										end
									 	--**********************************************
									 	
									 	
									 	


										--******************************
										--io write

--							            local path = system.pathForFile( fileName, pathSave )
--										--local file = io.open( path, writeMod )
--										local file = io.open( path, "wb" )
--
--										local string = task:getString ()
--
--													--print(string)
--				                                    print('pathSave:',pathSave)
--
--
--													  if file then
--													        print('\t@ Created file')
--													       -- print(fileName,string)
--													        file:write(string)
--
--
--
--													   else
--													        print('\t@ Create file failed!')
--													   end
--
--
--									       	   file:close()
--									       	   
									       	   
									       	   
									       	   
									       	   
							        local taskData = MOAIDataBuffer.new()

        							taskData:setString(task:getString())

                                    local path =   pathSave .."//"..fileName
                                    
                                    
                                    taskData:save(path)
                                    
									---
										 
                                  
                                   
									if(fileName:match(".lua-back")) then
									
										        print('')
											    print('dump file')
											    local newpath =  string.gsub(path, "/", "//")

										  		print('*******>>>>>>>',newpath)

										  		  print('')
											        --local string = taskData:getString()

												    local file_load =	loadfile(newpath)

												   -- local file_string = loadstring(taskData:getString())

												    	   ---print('file_string',file_string)
												           --print('file_load',file_load)

													local string_dump = string.dump(file_load )
													local newFileName =  string.gsub(fileName, ".lua", ".luac")
													local newPath     =  pathSave .."//"..newFileName


												       local file_write = io.open(newPath,'wb')
												             file_write:write(string_dump)
												             file_write:close()

									  		
									end
									
									       	   
								
									       	   
									       	   
									       	   
									       	   


								end



							--******************
							--cal back
						   	callback(event)

		end
		
		
		


		--print('pathGet:',url)


		task_get:setUrl ( url )
	--	task:setBody ( params )
		task_get:setCallback ( saveFile )
        task_get:performSync ()
       -- task_get:performAsync ()






end






--*******************************************************************************
--*******************************************************************************
--*******************************************************************************
--*******************************************************************************
--*******************************************************************************
--*******************************************************************************
--*******************************************************************************
--*******************************************************************************
--local files

local filesRemote = {}
local filesLocal = {}

local fileCnt = 0

local dirMake = {}


function split(str, pat)
   local t = {}  -- NOTE: use {n = 0} in Lua-5.0
   local fpat = "(.-)" .. pat
   local last_end = 1
   local s, e, cap = str:find(fpat, 1)
   while s do
      if s ~= 1 or cap ~= "" then
	 table.insert(t,cap)
      end
      last_end = e+1
      s, e, cap = str:find(fpat, last_end)
   end
   if last_end <= #str then
      cap = str:sub(last_end)
      table.insert(t, cap)
   end
   return t
end







local function printDir( path )
   -- print( "nFiles in path: " .. tostring( path ) )

    local pathType = ""

    -- Check to see if path exists
    if path and lfs.attributes( path ) then
        pathType = lfs.attributes( path ).mode
    end




   if pathType == "directory" then

        for file in lfs.dir( path ) do
            local str

            -- Skip the current and up-one directories
            if "." ~= file and ".." ~= file then

                str = file

                local fileAtr = lfs.attributes( path .. "/" .. file )
                if fileAtr then

                       if fileAtr.mode =='directory' then

                           	 printDir((path..'/'..str))

                       elseif fileAtr.mode == 'file' then

                           -- print(str)
                            -- fileCnt = fileCnt + 1


                          -- if  fileAtr.size < 100 then
                             --    print(str,fileAtr.size)
	                            local fileCnt = #filesLocal + 1

			                            filesLocal[fileCnt] = {}
			                            filesLocal[fileCnt].name = str
			                            filesLocal[fileCnt].mod = fileAtr.modification
			                           -- print(filesLocal[fileCnt].mod)

		                   --end --end size


                       end






                else

                end


            end
        end
   else
   --     str = "Path is not a directory!"
   --     print( str )
    end
end




   --*******************************************************************
--*******************************************************************
local function StartApp()







         								update_layer:removeProp ( textboxA )
         								update_layer:removeProp ( textboxB )
         								update_layer:removeProp ( textboxC )
         								
                                        textboxA = nil
                                        textboxB = nil
                                        
                                        
                                        update_layer 		= nil
                                        update_viewport 	= nil


                                        MOAISim.forceGarbageCollection()
                                        

									--	print('package.path',package.path)
									--	print('package.gamepath',package.gamepath)
									--	local newGame = require(game_name)
									
									







 --*****************************************************************************
--OLD
--local 	luaPath =  system.cacheDirectory..'//'..game_name
--package.path 	 =  luaPath.."/?.lua"
--package.gamepath =  luaPath
--
--
--
--
--
--
--
----*****************************
----require game      								
----print('start-game')
--require('//app_lua//_globals')
--
--
--
--									
							
                        
                        
 --*****************************************************************************
--WORD
if game_name == 'word' then


			local 	luaPath =  system['cacheDirectory']..'//'..game_name
			package.path 	 =  luaPath.."/?.lua"
			package.gamepath =  luaPath
	
			require('//app_lua//_globals')

end



--*****************************************************************************
--SMASH

if game_name == 'smash' then
	
		local 	luaPath =  system['cacheDirectory']..'//'..game_name..'//app_lua//'
		package.path 	 =  luaPath.."/?.lua"
		package.gamepath =  luaPath
		
		  require('_globals')  

end
                       
                        
    
--*****************************************************************************
--SOUP

if game_name == 'soup' then
	
		local 	luaPath =  system['cacheDirectory']..'//'..game_name
		package.path 	 =  luaPath.."/?.lua"
		package.gamepath =  luaPath
		
		  require('soup')  

end
                       
                        
    


--*****************************************************************************
--SOUP

if game_name == 'ouya' then

print('CAHNAGE TO OUYA')
		local 	luaPath =  system['cacheDirectory']..'//'..game_name
		package.path 	 =  luaPath.."/?.lua"
		package.gamepath =  luaPath

		  require('ouya')

end









                    
                        
                        
                        
                        --require('zHeader')
                        
                        
                        
                        
--                             local  byte_filename    = luaPath..'//zHeader.lua'
--                             local  byte_headername  = '_zHeader_lua'
--                             local  byte_outname     = luaPath..'//zHeader.h'

--                              -- dump the function to Lua bytecode
--                              local byte_compiled = string.dump ( loadfile ( byte_filename ))
                              
--                             -- print('COMPILE',compiled)

--                              -- convert the Lua bytecode to a cpp header called 'bundled_lua' with 12 columns
--                              local byte_header = MOAIDataBuffer.toCppHeader ( byte_compiled, byte_headername, 12 )

--                               --  print('byte_header',byte_header)
--                              -- write the header to a file
--                              local file = io.open ( byte_outname, 'wb' )
--                              file:write ( byte_compiled )
--                              file:close ()
                        
                        
								--***************************
								--Build files instead
								
            						--	require('util_to_c_headers')
										
										
								--***************************
								--PackageFiles
										
										--	require('util_packageFiles')
										
										


								  --****************************
								  --****************************
								  --LOAD C HEADERS
								  
                                        	--MOAISim.loadGame()
                                        
                                        
                                        
                                        
                                        
                                        
--          require('debug_fps')

       
                                        
                                        
                                        





									
										
										
--									--	lua_loadfilse(game_name..'luac')

								--		ez_require(game_name)

									---	loadfile('smash.luac')()

										 
									--	 local string_dump = string.dump(ff)
										  
									--	print(string_dump)
										
									--	local ss = loadstring(string_dump)
										
									--	print(ss)
										
										
									
										

end

--*******************************************************************
--*******************************************************************
--*******************************************************************
--*******************************************************************
--*******************************************************************
--remote files

local fileCnt = 0

   local function sendCallback(task, responseCode)

		if responseCode == 200 then

		 
				print(responseCode)
       	    local string = task:getString ()

                -- print(string)
                 
                 
       	   local tempBase = baseDecode(string)
       	   local tempJson = jsonDecode(tempBase)

       	   local response = tempJson

       	    local exitcnt = 0

       	      	for k,v in pairs(response) do




							local fileCnt = #filesRemote + 1

			                filesRemote[fileCnt] = {}
			                filesRemote[fileCnt].name 		= v.filename
			                filesRemote[fileCnt].ttouch 	= v.mod
			                filesRemote[fileCnt].path 		= ip_address..v.path
			                filesRemote[fileCnt].pathSave 	= v.pathSave


				 end





--for i = 1,#filesRemote do
--  		local file = filesRemote[i]
--	 	print(file.name,file.mod,file.path)
--end




				--**************************************************************
				--temp
		
          		local filesToUpdate = {}



                for i = 1,#filesRemote do

						local file  	= filesRemote[i]

						local fileName 	= file.name
						local ttouch    = file.ttouch
						local filePath  = file.path
						local pathSave  = file.pathSave
						local flag 		= 1 --forces all files to update


				        for j = 1,#filesLocal do

								
		
								    if  fileName == filesLocal[j].name then
		
		
		
								                        if  ttouch ~= filesLocal[j].mod then
		
		          											print('update this file>',fileName,'remote',ttouch , 'local',filesLocal[j].mod )
														 
										
		
		                                flag = 1
		
		
														elseif ttouch == filesLocal[j].mod then
				                                           			flag = 0
														end
		
								                 break
		
								    end --end filename







				        end --end j

                   

                              
								    if (flag == 1) then


												  --***********************************
												  --make directory list
												  

								                  local fileCnt = #filesToUpdate + 1
								                  filesToUpdate[fileCnt] = {}

								                  filesToUpdate[fileCnt].getPath 	= filePath
                                                  filesToUpdate[fileCnt].name 		= fileName
                                                  filesToUpdate[fileCnt].pathSave 	= pathSave
                                                  filesToUpdate[fileCnt].ttouch     = ttouch


												  print('filename>>>>>', #filesToUpdate,fileName)

                                                  local index 	=  table.indexOf(dirMake, pathSave)
                                                  
                                                  
                                                if index == 0 then

													  table.insert(dirMake,pathSave)
                                                end






								    end --end flag


				end --end i




                --**********************************
                --**********************************
				--**********************************
				--make directories
				 table.sort(dirMake)

				  for i = 1, #dirMake do

				 		local dirTable = split(dirMake[i], "/")

						print(system.cacheDirectory)

				       local subNames = system.cacheDirectory

				       for i = 1, #dirTable do
				       
                          subNames =subNames.. '/'..dirTable[i]
				      	  lfs.mkdir(subNames)
				      	  
				       end

           		 end



                 --**********************************
				 --**********************************
				 --download updates and chnage touch
				 local updateCnt = 0


						local function downloadFinished(event)


						  if event then

							   	local fileName = system.cacheDirectory..filesToUpdate[updateCnt].pathSave..filesToUpdate[updateCnt].name
							   	local touchNumber = filesToUpdate[updateCnt].ttouch
							   	lfs.touch (fileName,  touchNumber,touchNumber)
							   	
						   --	print('-----------------')
							 --print('touch to>>>>>>>',fileName,  touchNumber,touchNumber)
						  -- 	print('-----------------')

						  end

                               updateCnt = updateCnt + 1
							   if  filesToUpdate[updateCnt]  then

								     local pathSave = system.cacheDirectory..filesToUpdate[updateCnt].pathSave
								     local getPath 	= filesToUpdate[updateCnt].getPath..filesToUpdate[updateCnt].name
								     local filename = filesToUpdate[updateCnt].name
								     local ttouch   = filesToUpdate[updateCnt].ttouch

									print('filename',filename,#filesToUpdate)
									
									textboxA:setString(tostring(updateCnt)..' of '..tostring(#filesToUpdate))
									textboxB:setString(filename)


									local function downloadNext()
									            --recursive
									     	    network.download(getPath,downloadFinished,pathSave,filename,ttouch)
									end
									


                                             --download timer
   											 local download_timer = MOAITimer.new()
  											 download_timer:setSpan(0.2)
											 download_timer:setMode(MOAITimer.NORMAL)
											 download_timer:setListener(MOAITimer.EVENT_TIMER_END_SPAN,downloadNext,0)
											 download_timer:start()

								    
							   else
							   
							      print('done updating')
                                 --****************
                                        StartApp()

								    

							  end


						end


                  downloadFinished()


       end--moai response

   end
   
   
   


--*********************************
--CHECK CACHE FILES

local function updateApp()

	  print('starting to update>>',ip_address)
		--print(system.CacheDirectory)
		--print(system.ResourceDirectory)

		printDir(system.cacheDirectory)


		-- print(#filesLocal)
		--for i = 1,#filesLocal do
		--  local file =    filesLocal[i]
		--	 print(file.name,file.mod,file.path)
		--end
		--



		--************************
		--GET NEW FILES
		local updateGamePath = ip_address..'/moai/update.php?game='..game_name
		
		--local updateGamePath = 'http://192.168.1.6/moai/update.php'
		
		print(updateGamePath)
		
		network.request(updateGamePath, "POST", sendCallback,'')


end















--
--local tapA  = 0
--local tapB  = 0
--local timerWait = false
--local tapCnt = 0
--


--track counter
--function trackPointer(x, y)
--    mouseX, mouseY = myLayer:wndToWorld(x, y)
--end
--
--


--***********************************
--pc
--function clickScreen(down)
--    if (down) then
--       -- print("Tap detected: DOWN")
--    else
--    
--
--      --     timerWait = true
--			--	print("Tap detected: UP")
--				
--				if tapA == 0 then
--						tapA = 1
--						tapCnt = 0
--				else
--						if tapCnt < 5 then
--							--tapA = 0
--						  --print('doubleTap')
--
--
--						end
--
--				end
--        
--        
--    end
--end
--

--*****************************************************
--gets rewritin in game code
--*************************************
--ios

function onDialogDismissed ( code )

		print(code,MOAIDialog.DIALOG_RESULT_POSITIVE)
	if ( code == MOAIDialog.DIALOG_RESULT_POSITIVE ) then
	    os.exit()
		print ( "dialog result: YES" )
	elseif ( code == MOAIDialog.DIALOG_RESULT_NEUTRAL ) then
		print ( "dialog result: MAYBE" )
	elseif ( code == MOAIDialog.DIALOG_RESULT_NEGATIVE ) then
		print ( "dialog result: NO" )
	elseif ( code == MOAIDialog.DIALOG_RESULT_CANCEL ) then
		print ( "dialog result: CANCELED" )
	else
		print ( "dialog result: UNKNOWN" )
	end
end

function tapScreen(eventType, idx, x, y, tapCount)

	--trackPointer ( x, y )
	--print(tapCount)
	

	--double tap exit call
    if (eventType == MOAITouchSensor.TOUCH_DOWN) then
    elseif (eventType == MOAITouchSensor.TOUCH_UP) then
        	if tapCount == 2 then
        	  	  MOAIDialog.showDialog ( "exit App", "do you want to exit" , "Yes",nil, nil,true, onDialogDismissed )
        	end

    end
    
    
    
end





function startInputs()
    if (MOAIInputMgr.device.pointer) then
        -- Here the app is running on simulator and we use mouse input
        MOAIInputMgr.device.pointer:setCallback(trackPointer)
        MOAIInputMgr.device.mouseLeft:setCallback(clickScreen)
    else
        -- Here the app is running on device and we use touch input
        MOAIInputMgr.device.touch:setCallback(tapScreen)
    end
end







local function runtimeTimer()
	 --print(tapCnt)
      tapCnt = tapCnt + 1
      --print(tapCnt)
    --****************
  if tapCnt > 5 then
		  	tapCnt = 0
		  	tapA = 0
  end 

end




if (system.osType == "ios") or (system.osType == "android")  then
		--start touch
		print('starting ios')
		startInputs()

end






function onUpdateApp ( code )

		print(code,MOAIDialog.DIALOG_RESULT_POSITIVE)
	if ( code == MOAIDialog.DIALOG_RESULT_POSITIVE ) then

		updateApp()
		print ( "dialog result: YES" )
	elseif ( code == MOAIDialog.DIALOG_RESULT_NEUTRAL ) then
	
		print ( "dialog result: MAYBE" )
	elseif ( code == MOAIDialog.DIALOG_RESULT_NEGATIVE ) then
	
	   StartApp()
		print ( "dialog result: NO" )
		
		
		
	elseif ( code == MOAIDialog.DIALOG_RESULT_CANCEL ) then
		print ( "dialog result: CANCELED" )
	else
		print ( "dialog result: UNKNOWN" )
	end
end





---**************************************************************
if (system.osType == "ios") or (system.osType == 'android') then
 		MOAIDialog.showDialog ( "Update App", "Update This App" , "Yes",nil, 'no',true, onUpdateApp )
else



local touch = {}

		----------------------------------------------------------------
		-- keyboard events
if game_user   ~= 'ezra' then
				
--			MOAISim:timerStart()
				
					function touch.keyboardEvent ( key, down )



			      								            if key == 121 and (down == true) then

															   print('UPDATE')

															 				print('')
																			print('> UPDATE APP')
																			print('')
																	       	updateApp()


			      								            end

			                                                if key == 110 and (down == true) then

															   print('SKIP')

															    	print('')
															        print('> STARTING APP')
															        print('')
															 		StartApp()


			      								            end






					                                  print('KEYBOARD: '..key)





					end   --end function



			 MOAIInputMgr.device.keyboard:setCallback ( touch.keyboardEvent )



else

--		MOAISim:timerStart()
    	updateApp()
end







			
  	
  	
  	
end





print("----------------------------")



























--
--charcodes = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 .,:;!?()&/-'
--text = 'The quick <c:f70>brown<c> fox jumps over the <c:7f3>lazy<c> dog.'
--
--font = MOAIFont.new ()
--font:loadFromTTF ( 'loadFont/arial-rounded.TTF', charcodes, 12, 163 )
--
--textbox = MOAITextBox.new ()
--textbox:setString ( 'hello jello' )
--textbox:setFont ( font )
--textbox:setTextSize ( 19, 163 )
--textbox:setRect ( -150, -230, 150, 230 )
--textbox:setYFlip ( true )
--textbox:setColor(1,1,1,0)
--textbox:setLoc(1,1)
--
--myLayer:insertProp ( textbox )




--*******************************************************************************
--*******************************************************************************
--*******************************************************************************
--*******************************************************************************
--*******************************************************************************
--*******************************************************************************
--*******************************************************************************
--*******************************************************************************


