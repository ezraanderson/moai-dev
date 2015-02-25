MOAISim.openWindow ( "test", 600, 600 )

viewport = MOAIViewport.new ()
viewport:setSize ( 600, 600 )
viewport:setScale ( 600, 600 )
viewport:setOffset ( -1, 1 )

layer = MOAILayer2D.new ()
layer:setViewport ( viewport )
MOAISim.pushRenderPass ( layer )


local cos = math.cos
local sin = math.sin
local rad = math.rad

local start_x     = 0
local start_y     = 0
local slope_angle = 45

function onDraw ( index, xOff, yOff, xFlip, yFlip )  
  
MOAIGfxDevice.setPenColor ( 1, 1, 1, 1 )

          --DRAW_LINE
          local new_x   = start_x+ (2000) * cos(rad(slope_angle))
          local new_y   = start_y+ (2000) * sin(rad(slope_angle))*-1
          MOAIDraw.drawLine (start_x,start_y,new_x,new_y)



          local point   = {}
          local center  = {}
          local angle   = rad(slope_angle); -- Convert to radians       
          
          point['x']   = 0+0
          point['y']   = 0-70

          center['x']  = 0
          center['y']  = 0                 
       
          local rotatedX = cos(angle) * (point.x - center.x) - sin(angle) * (point.y - center.y) + center.x;
          local rotatedY = sin(angle) * (point.x - center.x) + cos(angle) * (point.y - center.y) + center.y;      
       
          MOAIGfxDevice.setPenColor ( 1, 1, 0, 1 )          
          MOAIDraw.fillCircle (start_x,start_y,10,45)          
    
    
    
          MOAIGfxDevice.setPenColor ( 1, 0, 0, 1 )          
          MOAIDraw.fillCircle (rotatedX,rotatedY,3,16)     






          --DRAW_DOTS
--          local dot_y   = start_y
--          local dot_x   = start_x

--            for x = 0, 100 do    
--                MOAIGfxDevice.setPenColor ( 1, 0, 0, 1 )         
--                dot_x   = dot_x+ (20) * math.cos(rad(slope_angle))
--                dot_y   = dot_y+ (20) * math.sin(rad(slope_angle))*-1      
--                MOAIDraw.fillCircle (dot_x,dot_y,3,16)        
--            end
            
  
  
  
  
  
	
end

scriptDeck = MOAIScriptDeck.new ()
scriptDeck:setRect ( -1, -1, 1, 1 )
scriptDeck:setDrawCallback ( onDraw )
prop = MOAIProp2D.new ()
prop:setDeck ( scriptDeck )

layer:insertProp ( prop )

