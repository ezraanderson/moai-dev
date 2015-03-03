----------------------------------------------------------------
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
----------------------------------------------------------------

MOAISim.openWindow ( "test", 320, 480 )
MOAIGfxDevice.getFrameBuffer ():setClearDepth ( true )
MOAIGfxDevice.getFrameBuffer ():setClearColor ( .5,.1,.1,.1 )

viewport = MOAIViewport.new ()
viewport:setSize ( 320, 480 )
viewport:setScale ( 320, 480 )

layer = MOAILayer.new ()
layer:setViewport ( viewport )
layer:setSortMode ( MOAILayer.SORT_NONE ) -- don't need layer sort
MOAISim.pushRenderPass ( layer )


require "importCollada"
meshCollada = colladaToMesh ( "mayaHelixTestDeindexed.dae", "moai.png" )
propCollada = MOAIProp.new ()
propCollada:setDeck ( meshCollada )
propCollada:setCullMode ( MOAIProp.CULL_NONE )
propCollada:setDepthTest ( MOAIProp.DEPTH_TEST_LESS_EQUAL )
propCollada:setLoc( 0,-100 )
propCollada:setScl( 32,32,32)

layer:insertProp ( propCollada )





camera = MOAICamera.new ()
camera:setLoc ( 0, 0, camera:getFocalLength ( 320 ))
layer:setCamera ( camera )

local pausetime = 0
local t = MOAICoroutine.new()
t:run( function()
          while true do
			 pausetime = pausetime + .01
			 
		
			 propCollada:setRot( 360*pausetime, 180*pausetime, 90*pausetime )
			 
             coroutine.yield()
          end          
       end)
