----------------------------------------------------------------
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
----------------------------------------------------------------

MOAISim.openWindow ( "test", 320, 480 )

viewport = MOAIViewport.new ()
viewport:setSize ( 320, 480 )
viewport:setScale ( 320, -480 )

layer = MOAILayer2D.new ()
layer:setViewport ( viewport )
MOAISim.pushRenderPass ( layer )

gfxQuad = MOAIGfxQuad2D.new ()
gfxQuad:setTexture ( "moai.png" )
gfxQuad:setRect ( -128, -128, 128, 128 )
gfxQuad:setUVRect ( 0, 0, 1, 1 )

prop = MOAIProp2D.new ()
prop:setDeck ( gfxQuad )
layer:insertProp ( prop )






--print('')
--if jit then
--print('>> JIT >>', jit.status())
--end

--local function writeData()
--f = io.open("limited_constants.lua","w")
--f:write("print('>> LOADING >> CONSTANTS' )\n")
--f:write("function f()\n")
--f:write("tt = {\n")  
--  local cnt = 0
--  for x = 1, 300 do
--    for y = 1,300 do
--      cnt = cnt + 1
--      f:write(" {",cnt,"},\n")
--    end
--  end   
--  f:write("}\n")
--  f:write("return tt\nend\n")
--  f:close()
--end
--writeData()

--print('----')
--print('REQUIRE')
--require "limited_constants"
--print('----')





--*************************************
function screenFocus(message)
  print('screenMessage >>',message) 
end
--*************************************
function screenSize(width,height)
  print('screenSize >>',width,height)  
  viewport:setSize ( width, height )
  viewport:setScale ( 320, -480 )  
end
--*************************************
function keyboard ( key, isDown )
   print('keyboard >>',key,isDown) 
end  
--*************************************
function mouseMove ( x, y )
  print('mouseMove >>',x,y) 
end
--*************************************
function mouseLeft(isDown)
   local x,y = MOAIInputMgr.device.pointer:getLoc()
   print('mouseLeft >>',isDown,x,y) 
end  
--*************************************
function mouseRight(isDown)
  local x,y = MOAIInputMgr.device.pointer:getLoc()
  print('mouseRight >>',isDown,x,y)  
end  
--*************************************

--FOCUS_MESSAGE
MOAIGfxDevice.setListener ( MOAIGfxDevice.EVENT_FOCUS, screenFocus)
--RESIZE
MOAIGfxDevice.setListener ( MOAIGfxDevice.EVENT_RESIZE, screenSize )
--KEYBOARD
MOAIInputMgr.device.keyboard:setCallback ( keyboard )
--MOUSE
MOAIInputMgr.device.pointer:setCallback ( mouseMove )
--LEFT_CLICK
MOAIInputMgr.device.mouseLeft:setCallback(mouseLeft)
--RIGHT_CLICK
MOAIInputMgr.device.mouseRight:setCallback(mouseRight)

MOAISim.hideCursor() 
--MOAISim.enterFullscreenMode()
MOAISim.title('NEW_TITLE')
MOAISim.resizeWindow(500,500)

local function runtimeTimer()
  local fps      = MOAISim.getPerformance()
  local drawcall = MOAIRenderMgr.getPerformanceDrawCount()
  MOAISim.title('FPS: '..tostring(math.floor(fps))..' DRAWCALL: '..drawcall)
  MOAISim.resizeWindow(math.random(100,550),math.random(100,550))  
end  

timer = MOAITimer.new()
timer:setSpan(2)
timer:setMode(MOAITimer.LOOP)
timer:setListener(MOAITimer.EVENT_TIMER_END_SPAN,runtimeTimer,0)
timer:start()






--local math   = math
--local random = math.random
--local cos    = math.cos
--local sin    = math.sin
--local pi     = math.pi
--local atan2  = math.atan2
--local rad	   = math.rad
--local sqrt   = math.sqrt
--local floor  = math.floor
--local abs	   = math.abs
--local deg	   = math.deg
--local mod    = math.modf



--	--COUNT
--	local effect_cnt  = 900

	
	
--	--FORMATE
--	effect_vertexFormat = MOAIVertexFormat.new ()
--	effect_vertexFormat:declareCoord(1, MOAIVertexFormat.GL_FLOAT, 3) --LOC X,LOC X
--	effect_vertexFormat:declareColor(2, MOAIVertexFormat.GL_UNSIGNED_BYTE)--COLOR
--	effect_vertexFormat:declareAttribute(3, MOAIVertexFormat.GL_FLOAT,1) --POINT SIZE
--	effect_vertexFormat:declareUV ( 4, MOAIVertexFormat.GL_FLOAT, 2 ) --ROTATION
--	effect_vertexFormat:declareUV ( 5, MOAIVertexFormat.GL_FLOAT, 2 ) --UV
	
	
	
--	--VBO
--	effect_vbo = MOAIEzraVertexBuffer.new ()
--	effect_vbo:setFormat ( effect_vertexFormat )
--	effect_vbo:reserveVerts ( effect_cnt )
	
  

	
	
--	local cnt_tile 		= 0
--	local cnt_effect 	= 0
	
	
	
--	--*************************
--	--TILE AREA
--	for y = 1,30 do
--		for x = 1,30 do
		
	
--	   				--ROTATION
--					local rot  = 0
--					local mCos = cos(rot)
--					local pSin = sin(rot)
	
--					--UV
--					local ux,uy     = 1, 1
	
	
--					--INCREASE
--					cnt_effect=cnt_effect + 1
--					effect_vbo:writeGeo(
--									--LOC : X,Y,Z
--									x*32-16, --WAV TO SET MAX AND MINUS
--									y*32-16,
--									0,
--									--COLOR : R,G,B,A
--									1,
--									1,
--									1,
--									1,
--									--SIZE
--									32,
--									--ROT
--									mCos,
--									pSin,
--									--UV
--									ux,
--									uy
--					)
	
	
--		end--end x
--	end--end y
	
	
	
	
	
	
--	--BLEES
--	effect_vbo:bless()
	

--	--TEXTURE
--	local mTexture = MOAITexture.new()
--	mTexture:setFilter ( MOAITexture.GL_LINEAR ) --smooth
--	mTexture:load( 'moai.png' , MOAIImage.PREMULTIPLY_ALPHA )
  
  
	
--	--MESH
--	effect_mesh = MOAIEzraMesh.new ()
--	effect_mesh:setVertexBuffer ( effect_vbo )  
--	effect_mesh:setPrimType ( MOAIMesh.GL_POINTS) --GL_TRIANGLE_STRIP
--	effect_mesh:setHigh(30*30) --BASED ON VERTIXS
--	effect_mesh:setTexture (mTexture)
  
 
  
--	effect_prop = MOAIProp.new ()
--	effect_prop:setDeck ( effect_mesh )
--	effect_prop:setBlendMode(MOAIProp2D.BLEND_ADD)
  
--  layer:insertProp ( effect_prop )
