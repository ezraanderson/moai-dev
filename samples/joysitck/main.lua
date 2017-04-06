----------------------------------------------------------------
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
----------------------------------------------------------------

MOAISim.openWindow ( "test", 320, 480 )

viewport = MOAIViewport.new ()
viewport:setSize ( 320, 480 )
viewport:setScale ( 320, 480 )

layer = MOAILayer2D.new ()
layer:setViewport ( viewport )
MOAISim.pushRenderPass ( layer )

function onDraw ( index, xOff, yOff, xFlip, yFlip )

	
end

scriptDeck = MOAIScriptDeck.new ()
scriptDeck:setRect ( -64, -64, 64, 64 )
scriptDeck:setDrawCallback ( onDraw )

prop = MOAIProp2D.new ()
prop:setDeck ( scriptDeck )
layer:insertProp ( prop )



local input = {}


function input.analog(player,leftAxisX, leftAxisY, rightAxisX, rightAxisY)
  print('ANALOG',player,leftAxisX, leftAxisY, rightAxisX, rightAxisY)
end


function input.button(player,isDown,keyCode)  
    print('BUTTON',player,isDown,keyCode)
end



MOAIInputMgr.device.gameButton:setCallback (input.button )
MOAIInputMgr.device.gameAnalog:setCallback (input.analog )








