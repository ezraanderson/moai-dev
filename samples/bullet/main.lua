----------------------------------------------------------------
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
----------------------------------------------------------------

MOAISim.openWindow ( "test", 1280,720 )

print("HELLO BULLET")

viewport = MOAIViewport.new ()

viewport:setSize (   1280,720)
viewport:setScale (   1280,720 )
--viewport:setOffset ( -1, 1 )


layer = MOAILayer2D.new ()
layer:setViewport ( viewport )
MOAISim.pushRenderPass ( layer )


local camera = MOAICamera.new ()
camera:setLoc ( 0, 250, camera:getFocalLength ( 4000 ))
layer:setCamera ( camera )
camera:setRot(0,0,0)


layerB = MOAILayer2D.new ()
layerB:setViewport ( viewport )
MOAISim.pushRenderPass ( layerB )


gfxQuad = MOAIGfxQuad2D.new ()
gfxQuad:setTexture ( "moai.png" )
gfxQuad:setRect ( -64, -64, 64, 64 )
--gfxQuad:setUVRect ( 0, 0, 1, 1 )


--**************************
  prop = MOAIProp2D.new ()
  prop:setDeck ( gfxQuad )
  prop:setLoc(-560,250)
  --layerB:insertProp ( prop )

----**************************
----SET WORLD
--  bWorld = MOAIBulletWorld.new()
--  bWorld:setGravity(0,-5,0)
--  bWorld:setStep(60)
--  bWorld:useContinuous(false)
--  bWorld:splitImpulse(false)
--  bWorld:setDrawScale(1)
--  bWorld:start()
  

--DRAW LAYER
 -- layer:setBulletWorld(bWorld);


--*********************************************************
--IS COMMAND SHAPE
--  body = bWorld:addBody (MOAIBulletWorld.COMPOUND_SHAPE)


--CAMERA
camera:setRot(-10,0,0)
camera:setLoc(0,4,camera:getFocalLength ( 10 ))


local function ragDoll()
--camera:setRot(-13,5,0)
--camera:setLoc(0,4,camera:getFocalLength ( 12 ))

      --body:addRag()
      body:addRag(-4,-0.1,0)
      body:addRag(-2,-0.1,-2)
      body:addRag(-2,-0.1,2)

      body:addRag(4,0-0.1,0)
      body:addRag(2,0-0.1,-2)
      body:addRag(2,0-0.1,2)
        --FROM CENTER
         
         
      local height = 0;

       for y = 1 ,12 do
        for x = -3 ,3 do   
          for z = -2, 2 do
         
           body:addBox(x*0.2,y*0.2-0.1,z*0.2,
                        1,1,1,    --ROTX,ROTY,ROTZ
                        0.1,0.1,0.1, --WIDTH,HEIGHT,LENGTH
                        1, --MASS
                        1) --INERTIA
                      
                      
                  height = y*0.2   
                      
            end
          end      
        end
        
        
      body:addCylinder(0,height+.3,0,
                  1,180,1,    --ROTX,ROTY,ROTZ
                  .2,.3,1, --WIDTH,HEIGHT,LENGTH
                  1, --MASS
                  1) --INERTIA    
                
                

      body:addBox(0,height+.6,0,
              1,1,1,    --ROTX,ROTY,ROTZ
              0.1,0.1,0.1, --WIDTH,HEIGHT,LENGTH
              1, --MASS
              1) --INERTIA
            
            


      body:addCone(0,height+0.6+0.4,0,
            1,180,1,    --ROTX,ROTY,ROTZ
            0.4,0.4, --RADIUS,HEIGHT
            1, --MASS
            1) --INERTIA   




      --

      body:addSphere(0,20,0,
            1,1,1, --ROTX,ROTY,ROTZ
            .1, --RADIAS
            100,  --MASS
            10000) --INERTIA        

                
             
      body:addSphere(-4,10,0,
            1,1,1, --ROTX,ROTY,ROTZ
            .1, --RADIAS
            5,  --MASS  
          1) --INERTIA        
            
             

      body:addSphere(4,15,0,
            1,1,1, --ROTX,ROTY,ROTZ
            .1, --RADIAS
            10,  --MASS
            1) --INERTIA                 
                
      --body:addRag(0,25,0)
end


--ragDoll()




--*****************************************************************************

                      
                      
local function blocks()
  
  

for y = 0 ,400 do
        for x = -1 ,1 do   
          for z = -1, 1 do
         
            local new_body = bWorld:addBody () 
            new_body:addBox(x*0.2,y*0.2+0.1,z*0.2,
                        1,1,1,    --ROTX,ROTY,ROTZ
                        0.1,0.1,0.1, --WIDTH,HEIGHT,LENGTH
                        0.001, --MASS
                        0) --INERTIA                     
               
                    new_body:setLinearVelocity(5,0,0)   
            end
          end      
        end
end        


--************************************************************************************
--************************************************************************************
--************************************************************************************
--************************************************************************************

local function crash()
  
  camera:setLoc(5,4,camera:getFocalLength ( 20 ))
   


       local new_body = bWorld:addBody (MOAIBulletWorld.COMPOUND_SHAPE)   
        new_body:addSphere(0,2,0,
              1,1,1, --ROTX,ROTY,ROTZ
              .1, --RADIAS
              1,  --MASS
              1) --INERTIA       
        new_body:setLinearVelocity(5,0,0)

      --*****************************************************************************     
      for y = 0 ,40 do
         for x = 30 ,34 do   
            for z = -1, 1 do
    
                local new_body = bWorld:addBody (MOAIBulletWorld.COMPOUND_SHAPE)         
                new_body:addBox(x*0.2,y*0.2+0.1,z*0.2,
                            1,1,1,    --ROTX,ROTY,ROTZ
                            0.1,0.1,0.1, --WIDTH,HEIGHT,LENGTH
                            0.001, --MASS
                            0) --INERTIA      
                        
              end
            end 
      end          


end




--**********************************************************
  local bWorld 
  
  bWorld = MOAIBulletWorld.new()
  bWorld:setGravity(0,-5,0)
  bWorld:setStep(60)
  bWorld:useContinuous(false)
  bWorld:splitImpulse(false)
  bWorld:setDrawScale(1)
  bWorld:start()
  
  --LAYER
  layer:setBulletWorld(bWorld);


local function demo()

--**********************************************************
local plane = {}


plane['body']  = bWorld:addBody ()
plane['body']:addToWorld()

plane['body']:setRestitution(1)  
plane['body']:setFriction(10) 

plane['body']:setPosition(0,-5,0)
plane['body']:setRotation(0,0,0)


plane['planeA'] = plane['body']:newShape()
plane['planeA']:addPlane(0,1,0)      
plane['planeA']:setPosition(0,0,0)
plane['planeA']:setRotation(0,0,0)
plane['planeA']:setMass(0,0)
plane['planeA']:addToBody(); 



--**********************************************************
local circle = {}

circle['body']  = bWorld:addBody ()
circle['body']:addToWorld()
circle['body']:setRestitution(1)   

circle['body']:setPosition(0,0,0)
circle['body']:setRotation(0,0,0)

circle['body']:setLinearVelocity(5,0,0)   
circle['body']:setAngularVelocity(1,1,10)

--ONE SHAPE TO BODIES
circle['shapeA'] = circle['body']:newShape()
circle['shapeA']:addSphere(1,1)      
circle['shapeA']:setPosition(0,0,0)
circle['shapeA']:setRotation(0,0,0)
circle['shapeA']:setMass(2,1)
--circle['shapeA']:addToBody(); 

circle['shapeB'] = circle['body']:newShape()
circle['shapeB']:addSphere(1,1)      
circle['shapeB']:setPosition(2,2,0)
circle['shapeB']:setRotation(0,0,0)
circle['shapeB']:setMass(2,1)
--circle['shapeB']:addToBody(); 

end




--for i = 1, 1000 do
  
--local newShape = MOAIBulletShape.new()
--newShape:addSphere(.1)  
--local newBody  = bWorld:addBody ()
--newBody:addToWorld()  

--newBody:addToBody(newShape)
--end





print(newShape)

--**********************************************************
--local circle = {}
--circle['body']  = bWorld:addBody ()
--circle['body']:addToWorld()
--circle['body']:setRestitution(1)   

--circle['body']:setPosition(0,0,0)
--circle['body']:setRotation(0,0,0)

--circle['body']:setLinearVelocity(5,0,0)   
--circle['body']:setAngularVelocity(1,1,10)
local circle = {}
for i = 1, 1000 do
  

circle['body']  = bWorld:addBody ()  
circle['body']:addToWorld()

circle['body']:setRestitution(1)   
circle['body']:setPosition(0,0,0)
circle['body']:setRotation(0,0,0)






circle['shapeB'] = circle['body']:newShape()
circle['shapeB']:addSphere(1,1)      
circle['shapeB']:setPosition(2,2,0)
circle['shapeB']:setRotation(0,0,0)
circle['shapeB']:setMass(2,1)
circle['shapeB']:addToBody(); 
end



----ONE SHAPE TO BODIES
--circle['shapeA'] = circle['body']:newShape()
--circle['shapeA']:addSphere(0.05,1)      

--circle['shapeA']:setPosition(0,0,0)
--circle['shapeA']:setRotation(0,0,0)
--circle['shapeA']:setMass(1,1)
--circle['shapeA']:addToBody(); 



camera:setLoc(0,2,camera:getFocalLength ( 20 ))
 
 









--*****************************************************************************
mTimers = {}
D = {}
  function D._FPS()       
     
            local fps    	  = MOAISim.getPerformance()
            local drawCount = MOAIRenderMgr.getPerformanceDrawCount()     
            print(fps,drawCount)
    
		end

			mTimers['fps']  = MOAITimer.new()
			mTimers['fps']:setSpan(0.001)
			mTimers['fps']:setMode(MOAITimer.LOOP)
			mTimers['fps']:setListener(MOAITimer.EVENT_TIMER_END_SPAN,D._FPS,0)
		--	mTimers['fps']:start()








input = {}
L = {}
F = {}
A = {}
mThread = {}
local keyDown = {
    mouseLeft = false,
    forward   = false,
    backward  = false,
    left      = false,
    right     = false,  
  }
  
function A._enterFrame(delta)  
  
  
local keyboard      = MOAIInputMgr.device.keyboard
local mouse         = MOAIInputMgr.device.pointer
local mouse_cache_x = 0 
local mouse_cache_y = 0 

local angleYaw           = 0
local anglePitch         = 0  

local eyeX = 0
local eyeY = 0
local eyeZ = 0

local sin = math.sin
local cos = math.cos


    while true do 
     
 
    --DEBUG STUFF
  local camera_x,camera_y,camera_z = camera:getLoc() 
  local rot_x,rot_y,rot_z          = camera:getRot()     
    
  local speed       = 0.1  
  local pitchRadian = math.rad(rot_x) 
  local yawRadian   = math.rad(rot_y)   
  
  
--*********************************************  
--GRAVITY FORCE  
if 		keyboard:keyIsDown ( 't' ) then 
    bWorld:setGravity(0,1,0)
end

if 		  keyboard:keyIsDown ( 'g' ) then 
     bWorld:setGravity(0,-1,0)
end
--*********************************************    
  
  

if 		  keyboard:keyIsDown ( 'w' ) then 
 
 
    eyeX = sin(yawRadian)   * speed;
    eyeY = sin(pitchRadian) * speed;
    eyeZ = -cos(yawRadian)  * speed; 

    camera:setLoc(camera_x-eyeX,camera_y+eyeY,camera_z+eyeZ) 
end    


if 	keyboard:keyIsDown ( 's' ) then   
  


    eyeX =  sin(yawRadian)   * speed;
    eyeY =  sin(pitchRadian) * speed;
    eyeZ = -cos(yawRadian)   * speed; 

    camera:setLoc(camera_x+eyeX,camera_y-eyeY,camera_z-eyeZ)  
end    

if 	keyboard:keyIsDown ( 'a' ) then              

    eyeX =  sin(yawRadian + 3.14/2) * speed;
    eyeZ =  -cos(yawRadian + 3.14/2) * speed;          
    camera:setLoc(camera_x-eyeX,camera_y,camera_z+eyeZ) 
end    




if 	keyboard:keyIsDown ( 'd' ) then              

    eyeX =  sin(yawRadian + 3.14/2) * speed;
    eyeZ =  -cos(yawRadian + 3.14/2) * speed;          
    camera:setLoc(camera_x+eyeX,camera_y,camera_z-eyeZ) 
end    


--MOVE UP & DOWN
if 	keyboard:keyIsDown ( 'o' ) then 

  eyeY = sin(anglePitch + 3.14/2) * speed;
  eyeZ = -cos(angleYaw + 3.14/2) * speed;

  camera:setLoc(camera_x,camera_y+eyeY,camera_z-eyeZ) 
end  

if 	keyboard:keyIsDown ( 'p' ) then 
    eyeY = sin(anglePitch + 3.14/2) * speed;
    eyeZ = -cos(angleYaw + 3.14/2) * speed;

    camera:setLoc(camera_x,camera_y-eyeY,camera_z-eyeZ) 
end    


--LOOP UP & DOWN
if 	keyboard:keyIsDown ( 'n' ) then      

    local rot = rot_x + 1        
    if rot >= 360 then rot = rot - 360 end
    if rot <= 0 then rot = rot + 360 end          
    camera:setRot ( rot,rot_y,rot_z )  
end    
     
if 	keyboard:keyIsDown ( 'm' ) then 
  
    local rot = rot_x - 1        
    if rot >= 360 then rot = rot - 360 end
    if rot <= 0 then rot = rot + 360 end          
    camera:setRot ( rot,rot_y,rot_z )      
  end     
     
     
--LOOK LEFT & RIGHT     
if 	keyboard:keyIsDown ( 'k' ) then   

  local rot = rot_y-1  
  if rot >= 360 then rot = rot - 360 end
  if rot <= 0 then rot = rot + 360 end
  camera:setRot ( rot_x,rot,rot_z )  
          
end   
    
if 	keyboard:keyIsDown ( 'l' ) then       

--  local rot = rot_y-1  
--  if rot >= 360 then rot = rot - 360 end
--  if rot <= 0 then rot = rot + 360 end
--  camera:setRot ( rot_x,rot,rot_z )  
    
    
   local rot = rot_y + 1        
    if rot >= 360 then rot = rot - 360 end
    if rot <= 0 then rot = rot + 360 end          
    camera:setRot ( rot_x,rot,rot_z )      
    
end      

       
     --  print(rot_x,camera_y) 
  
    
  	local delta=	coroutine.yield()
    end
  
end
mThread['enterFrame'] = MOAICoroutine.new ()
mThread['enterFrame']:run ( A._enterFrame )
        
        

function input.mouseMove(isDown)
  local x,y = MOAIInputMgr.device.pointer:getLoc()
 -- print('MOVE',x,y)
end


function input.keyboard ( key, down )
    if key == 13 and down == true then
      --ragDoll()   
      blocks()
      --crash()
    end
end  

function input.mouseLeft(isDown)

  keyDown['mouseLeft'] = isDown
end

--******************************************************************************
--LOAD INPUTS
function L._load_inputs()
			--RESIZE
        --MOAIGfxDevice.setListener ( MOAIGfxDevice.EVENT_RESIZE, F._screenSize )

			--KEYBOARD
        MOAIInputMgr.device.keyboard:setCallback ( input.keyboard )

			--MOUSE
        MOAIInputMgr.device.pointer:setCallback ( input.mouseMove )

			--LEFT_CLICK
        MOAIInputMgr.device.mouseLeft:setCallback(input.mouseLeft)

			--RIGHT_CLICK
        MOAIInputMgr.device.mouseRight:setCallback(input.mouseRight)

end

L._load_inputs()





