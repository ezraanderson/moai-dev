local math   = math
local random = math.random
local cos    = math.cos
local sin    = math.sin
local pi     = math.pi
local atan2  = math.atan2
local rad	   = math.rad
local sqrt   = math.sqrt
local floor  = math.floor
local abs	   = math.abs
local deg	   = math.deg
local rad    = math.rad

local M_E        =2.71828182845904523536
local M_LOG2E    =1.44269504088896340736
local M_LOG10E   =0.434294481903251827651
local M_LN2      =0.693147180559945309417
local M_LN10     =2.30258509299404568402
local M_PI       =3.14159265358979323846
local M_PI_2     =1.57079632679489661923
local M_PI_4     =0.785398163397448309616
local M_1_PI     =0.318309886183790671538
local M_2_PI     =0.636619772367581343076
local M_2_SQRTPI =1.12837916709551257390
local M_SQRT2    =1.41421356237309504880
local M_SQRT1_2  =0.707106781186547524401

local doDebug = false

MOAIGfxDevice.getFrameBuffer ():setClearDepth ( true )
MOAIGfxDevice.getFrameBuffer ():setClearColor ( .0,.0,.1,.1 )

MOAISim.openWindow ( "test", 1280,720 )
local viewport_game = MOAIViewport.new ()
viewport_game:setSize (   1280,720)
viewport_game:setScale (   1280,720 )


local camera = MOAICamera.new ()
camera:setRot(0,0,0)
camera:setLoc(0,20,camera:getFocalLength ( 80 ))

local layer = MOAILayer.new ()
layer:setViewport ( viewport_game )
layer:setCamera ( camera )
MOAISim.pushRenderPass ( layer )

local bWorld = {}

  --NEW CLASS
  bWorld = MOAIBulletWorld.new()    
  --MEMORY
  bWorld:defaultMaxCollisionAlgorithmPoolSize(65536)--65536
  bWorld:defaultMaxPersistentManifoldPoolSize(65536)--65536    
  --CREATE AFTER MEMORY SET
  bWorld:create(); 
  --SET
  bWorld:setStep(30)
  bWorld:setMaxSubSteps(1)
  bWorld:iterations(1)
  bWorld:splitImpulse(false)
  bWorld:useContinuous(false)    
  bWorld:setForceUpdateAllAabbs(true)  
  bWorld:allowedCcdPenetration(0) 
  bWorld:enableSPU(false) --FOR PS3
  bWorld:debugDraw(true)
  bWorld:collisionHandler(false)  
  --GRAVITY
  bWorld:setGravity(0,-0.3,0)  
  --DEBUG
  bWorld:setDrawScale(1)
  bWorld:setDrawJointSize(.1)      
  
  bWorld:start() 
  
  
  
  
  
  
---***********************************************************************
---***********************************************************************
---***********************************************************************
---***********************************************************************
local function pushPoint ( points, x, y, z )	
  local point = {}
  point.x = x
  point.y = y
  point.z = z		
  table.insert ( points, point )
end
--********************************
local function writeTri ( vbo, p1, p2, p3, uv1, uv2, uv3 )		
  vbo:writeFloat ( p1.x, p1.y, p1.z )
  vbo:writeFloat ( uv1.x, uv1.y )
  vbo:writeColor32 ( 1, 1, 1 )

  vbo:writeFloat ( p2.x, p2.y, p2.z )
  vbo:writeFloat ( uv2.x, uv2.y )
  vbo:writeColor32 ( 1, 1, 1 )

  vbo:writeFloat ( p3.x, p3.y, p3.z )
  vbo:writeFloat ( uv3.x, uv3.y  )
  vbo:writeColor32 ( 1, 1, 1 )
end
--********************************
local function writeFace ( vbo, p1, p2, p3, p4, uv1, uv2, uv3, uv4 )
  writeTri ( vbo, p1, p2, p4, uv1, uv2, uv4 )
  writeTri ( vbo, p2, p3, p4, uv2, uv3, uv4 )
end  

function makeBoxMesh ( xMin, yMin, zMin, xMax, yMax, zMax, texture )  
	
	local p = {}
	
	pushPoint ( p, xMin, yMax, zMax ) -- p1
	pushPoint ( p, xMin, yMin, zMax ) -- p2
	pushPoint ( p, xMax, yMin, zMax ) -- p3
	pushPoint ( p, xMax, yMax, zMax ) -- p4
	
	pushPoint ( p, xMin, yMax, zMin ) -- p5
	pushPoint ( p, xMin, yMin, zMin  ) -- p6
	pushPoint ( p, xMax, yMin, zMin  ) -- p7
	pushPoint ( p, xMax, yMax, zMin  ) -- p8

	local uv = {}
	
	pushPoint ( uv, 0, 0, 0 )
	pushPoint ( uv, 0, 1, 0 )
	pushPoint ( uv, 1, 1, 0 )
	pushPoint ( uv, 1, 0, 0 )
	
	local vertexFormat = MOAIVertexFormat.new ()
	vertexFormat:declareCoord ( 1, MOAIVertexFormat.GL_FLOAT, 3 )
	vertexFormat:declareUV ( 2, MOAIVertexFormat.GL_FLOAT, 2 )
	vertexFormat:declareColor ( 3, MOAIVertexFormat.GL_UNSIGNED_BYTE )

	local vbo = MOAIVertexBuffer.new ()
	vbo:setFormat ( vertexFormat )
	vbo:reserveVerts ( 36 )
	
	writeFace ( vbo, p [ 1 ], p [ 2 ], p [ 3 ], p [ 4 ], uv [ 1 ], uv [ 2 ], uv [ 3 ], uv [ 4 ])
	writeFace ( vbo, p [ 4 ], p [ 3 ], p [ 7 ], p [ 8 ], uv [ 1 ], uv [ 2 ], uv [ 3 ], uv [ 4 ])
	writeFace ( vbo, p [ 8 ], p [ 7 ], p [ 6 ], p [ 5 ], uv [ 1 ], uv [ 2 ], uv [ 3 ], uv [ 4 ])
	writeFace ( vbo, p [ 5 ], p [ 6 ], p [ 2 ], p [ 1 ], uv [ 1 ], uv [ 2 ], uv [ 3 ], uv [ 4 ])
	writeFace ( vbo, p [ 5 ], p [ 1 ], p [ 4 ], p [ 8 ], uv [ 1 ], uv [ 2 ], uv [ 3 ], uv [ 4 ])
	writeFace ( vbo, p [ 2 ], p [ 6 ], p [ 7 ], p [ 3 ], uv [ 1 ], uv [ 2 ], uv [ 3 ], uv [ 4 ])

	vbo:bless ()

	local mesh = MOAIMesh.new ()
	mesh:setTexture ( texture )
	mesh:setVertexBuffer ( vbo )
	mesh:setPrimType ( MOAIMesh.GL_TRIANGLES )
--	mesh:setHigh(36)
	return mesh
end

--*************************************************************************
function makeBoard ( width,height,length, texture )
      width = width * 0.01
      height = height * 0.01    
      length = length * 0.01       
      return makeBoxMesh (  -width, -height, -length, 
                            width, height, length, 
                          texture 
                          )
end
  
m_body  = {}
m_shape = {}
plane   = {}
m_props = {}  
m_mesh = {}  

m_mesh['plank']         =  makeBoard ( 100,25,50, 'tree.png' )  
m_mesh['box']          =   makeBoard ( 25,25,25, 'clay.png' )  
m_mesh['lava']          =   makeBoard ( 25,25,25, 'lava.png' )    

--*************************************************
--TRANSFORMER OBJECT
local pos_start  = MOAIBulletTransform.new() 


--local function make_tower()

local index = 0
local height_point = 0.25
local pie_step = 0

local tick = 0
local rAngle = 90 
local tile_cnt = 0


local tHeight = 50
local mass = tHeight*100+100

--for j = 1, tHeight do
  
local x, y, r = 0, 0, 4


local function add_row()
  
--              if index > 10 then
--            local bx,by,bz = m_body[index-1]:getPosition()
--            height_point = by+0.5
--            end
  
         for i = 1, 10 do    
    
          tile_cnt = tile_cnt + 1
          local angle = pie_step * pi / 180
          local ptx = x + r * cos( angle )
          local pty = y + r * sin( angle )
          pie_step = pie_step + 36 
          index = index + 1
            

            
                  --BODY
                  pos_start:setIdentity();pos_start:setEulerZYX(0, (rad(rAngle)*-1),0);pos_start:setOrigin(ptx,height_point,pty-1)            
                  m_body[index]  = bWorld:newBody (pos_start)            
                  m_body[index]:addToWorld(true)          
                  m_body[index]:setActivationState(1)
                  m_body[index]:setRestitution(0)  
                  m_body[index]:setFriction(1) 
                  
                  
                  m_body[index]:setIdName('idName'..index)
                  m_body[index]:setIdType('idType'..index)  
                  m_body[index]:forceUpdate()
                  m_body[index]:setDynamic()
                  m_body[index]:setContactProcessingThreshold(0.03)
                 
                --SHAPE  
                  pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,0,0)  
                  m_shape[index] = m_body[index]:newShape(pos_start)
                  m_shape[index]:makeBox(1,0.25,0.5)    
                  m_shape[index]:setMass(1,0)
                  m_shape[index]:setMargin(0.00)   
                  
                  
                  m_shape[index]:addToBody(); 
                 
                 --IDK                 
                  rAngle = rAngle + 36                         
                  
                  --PROP
                  m_props[index] = MOAIProp.new (); 
                  m_props[index]:setDeck ( m_mesh['plank'] )
                  m_props[index]:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
                  m_props[index]:setCullMode ( MOAIProp.CULL_BACK )
                  m_props[index]:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
                  m_props[index]:setDepthMask(true)
                  m_props[index]:setLoc(0,0) 
                  m_props[index]:setParent( m_body[index])
                --RENDER
                  layer:insertProp ( m_props[index] )   
                  
                  
                  
--      height_point = height_point + 0.5                
                 
                  
          end
        
height_point = height_point + 0.5      
pie_step     = pie_step + 16
rAngle       = rAngle +16
mass = mass - 100

if m_body[index-10] then
local ax,ay,az = m_body[index-10]:getPosition()
local bx,by,bz = m_body[index]:getPosition()
 print('top', index/10,by,ay,height_point)
end
end

--end

--end


--make_tower()
   
 --***********************************************************************************************************
 --***********************************************************************************************************
 --***********************************************************************************************************
  
  
 
 
  --***************************************************
  --PLANE : SHOULDN"T BE ATTACHED TO A BODY ????? FIX IN REFAC
  

        pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,0,0);       
        plane['body']  = bWorld:newBody (pos_start)  
        plane['body']:setRestitution(0)  
        plane['body']:setFriction(100000)      
        plane['body']:setActivationState(MOAIBulletWorld['ISLAND_SLEEPING'])
        plane['body']:setIdName('plane')
        plane['body']:setIdType('plane')        
        
        plane['body']:addToWorld(false)     

        pos_start:setIdentity();pos_start:setEulerZYX(0.0,0,0);pos_start:setOrigin(0,0,0)
        plane['planeA'] = plane['body']:newShape(pos_start)
        plane['planeA']:makePlane(0,1,0)  --THIS WORKS
        plane['planeA']:setMass(0,0)
        plane['planeA']:addToBody();            

           
        local plane_vertexFormat = MOAIVertexFormat.new ()
        plane_vertexFormat:declareCoord ( 1, MOAIVertexFormat.GL_FLOAT, 2 )            
        plane_vertexFormat:declareColor ( 3, MOAIVertexFormat.GL_UNSIGNED_BYTE )

        local plane_vbo = MOAIVertexBuffer.new ()
        plane_vbo:setFormat ( plane_vertexFormat )
        plane_vbo:reserveVerts ( 4 )


        plane_vbo:writeFloat ( -100000, -100000 )
        plane_vbo:writeColor32 ( 1,1,1)

        plane_vbo:writeFloat ( 100000, -100000 )
        plane_vbo:writeColor32 ( 1,1,1)

        plane_vbo:writeFloat ( 100000, 100000)
        plane_vbo:writeColor32 ( 1,1,1)

        plane_vbo:writeFloat ( -100000, 100000 )
        plane_vbo:writeColor32 ( 1,1,1)

        plane_vbo:bless ()      

 
          local plane_mesh= MOAIMesh.new ()
          plane_mesh:setTexture ( "clay.png" )
          plane_mesh:setVertexBuffer ( plane_vbo )
          plane_mesh:setPrimType ( MOAIMesh.GL_TRIANGLE_FAN )
          -- plane_mesh:setHigh(4)  


          plane_prop = MOAIProp.new ()
          plane_prop:setDeck ( plane_mesh )
          plane_prop:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
          --plane_prop:setCullMode ( MOAIProp.CULL_BACK )
          plane_prop:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
          plane_prop:setDepthMask(true)               
          plane_prop:setLoc(0,0)         


          plane_prop:setRot(90,0,0)              

          layer:insertProp ( plane_prop)     
 
 
 
 
 local throw = {}
 
 local function throw_box(x,y,z)
   
  print("throw_box") 
  
 local camera_x,camera_y,camera_z = camera:getLoc() 
 local rot_x,rot_y,rot_z          = camera:getRot()       
     
 local mass         = 1000
 local speed       = mass*1000
 local pitchRadian = math.rad(rot_x) 
 local yawRadian   = math.rad(rot_y)   

 local   eyeX = (sin(yawRadian)   * speed)*-1;
 local   eyeY = (sin(pitchRadian) * speed);
 local   eyeZ = (-cos(yawRadian)  * speed);     
     
     
        
                    --BODY
                  pos_start:setIdentity();pos_start:setEulerZYX(0, 0,0);pos_start:setOrigin(camera_x,camera_y,camera_z)            
                  local m_body = bWorld:newBody (pos_start)            
                  m_body:addToWorld(true)          
                  m_body:setActivationState(1)
                  m_body:setIdName('idName'..1)
                  m_body:setIdType('idType'..1)  
                  m_body:forceUpdate()
                  
                  m_body:setCcdMotionThreshold(.1)
                  m_body:setCcdSweptSphereRadius(.1)  
       
       
                --  m_body:setLinearVelocity(eyeX,eyeY,eyeZ)
                   m_body:setGravity(0,0,0)
                  m_body:applyForce(eyeX,eyeY,eyeZ)
                 
                --SHAPE  
                  pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,0,0)  
                 local  m_shape = m_body:newShape(pos_start)
                  m_shape:makeBox(1,1,1)    
                  m_shape:setMass(mass,0)
                  m_shape:addToBody(); 
                 
                 
                  
                  
                  --PROP
                  local m_props= MOAIProp.new (); 
                  m_props:setDeck ( m_mesh['lava'] )
                  m_props:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
                  m_props:setCullMode ( MOAIProp.CULL_BACK )
                  m_props:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
                  m_props:setDepthMask(true)
                  m_props:setLoc(0,0) 
                  m_props:setParent( m_body)
                --RENDER
                  layer:insertProp ( m_props )   
                  
   throw[#throw+1] = {}
      throw[#throw]['shape']  =m_shape
      throw[#throw]['prop']   =m_props
      throw[#throw]['body']   =m_body
   
   
end
 
 
 
 
--***********************************************************************************
--***********************************************************************************
--***********************************************************************************
--***********************************************************************************
--FPS

mTimers = {}
D = {}
function D._FPS()       

      local fps    	  = MOAISim.getPerformance()
      local drawCount = MOAIRenderMgr.getPerformanceDrawCount()     
     
end

mTimers['fps']  = MOAITimer.new()
mTimers['fps']:setSpan(5)
mTimers['fps']:setMode(MOAITimer.LOOP)
mTimers['fps']:setListener(MOAITimer.EVENT_TIMER_END_SPAN,D._FPS,0)
mTimers['fps']:start()
 
--***********************************************************************************
--***********************************************************************************
--***********************************************************************************
--***********************************************************************************
--DEBUG

    local bullet_debug          = {}
          bullet_debug['size']  = 100000  
          
    local function onDraw_bullet ( index, xOff, yOff, xFlip, yFlip ) 
      if doDebug == true then
        bWorld:drawDebugLua()
      end
    end

  --NEW BOUNDS
    bullet_debug['bounds'] = MOAIBoundsDeck.new ()
    bullet_debug['bounds']:reserveBounds ( 1 )
    bullet_debug['bounds']:reserveIndices ( 1 )  
    bullet_debug['bounds']:setBounds ( 1, -bullet_debug['size'], -bullet_debug['size'], -bullet_debug['size'], bullet_debug['size'], bullet_debug['size'], bullet_debug['size'] )

  --DRAWING DECK
    bullet_debug['deck'] = MOAIScriptDeck.new ()
    bullet_debug['deck']:setRect ( 1, 1, -1, -1 )
    bullet_debug['deck']:setDrawCallback ( onDraw_bullet )
    bullet_debug['deck']:setBoundsDeck ( bullet_debug['bounds'] )

  --DRAW PROP
    bullet_debug['prop'] = MOAIProp.new ()
    bullet_debug['prop']:setDeck ( bullet_debug['deck'] )
    
        
        --SET DEBUG LINES IN FORNT OR BEHIND ALL OBJECTS
       -- bullet_debug['prop']:setPriority(-1)
        bullet_debug['prop']:setPriority(10000)   
    
    
  --INSTER
   layer:insertProp ( bullet_debug['prop'] )
 
 
 
 
 
--***********************************************************************************
--***********************************************************************************
--***********************************************************************************
--***********************************************************************************
--CONTROLS
 
 
 --*****************************************************************************
--ENTER FRAME

input = {}
L = {}
F = {}
A = {}
mThread = {}
keys = {}

local crash_ang  = 14
local crash_max = 24
local crash_inc  = 0.005


local keyDown = {
    mouseLeft = false,
    forward   = false,
    backward  = false,
    left      = false,
    right     = false,  
  }
  
local keyboard      = MOAIInputMgr.device.keyboard
local mouse         = MOAIInputMgr.device.pointer  
  
function A._enterFrame(delta)   
  

local mouse_cache_x = 0 
local mouse_cache_y = 0 

local angleYaw     = 0
local anglePitch   = 0  

local eyeX = 0
local eyeY = 0
local eyeZ = 0




while true do
     
     
  
 
          --DEBUG STUFF
        local camera_x,camera_y,camera_z = camera:getLoc() 
        local rot_x,rot_y,rot_z          = camera:getRot()     
          
        local speed       = 0.25
        local pitchRadian = math.rad(rot_x) 
        local yawRadian   = math.rad(rot_y)   
          
          
        --*********************************************  
        --GRAVITY FORCE  
        if keyboard:keyIsDown ( 't' ) then 
              --    bWorld:setGravity(0,5,0)
        end

        if keyboard:keyIsDown ( 'g' ) then 
              --    bWorld:setGravity(0,-5,0)
        end
        --*********************************************   

        if keyboard:keyIsDown ( 'w' ) then 
         
         
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
        if 	keyboard:keyIsDown ( 'n' ) or (keys[338] == true) then      

            local rot = rot_x + .4        
            if rot >= 360 then rot = rot - 360 end
            if rot <= 0 then rot = rot + 360 end          
            camera:setRot ( rot,rot_y,rot_z )  
        end    
             
        if 	keyboard:keyIsDown ( 'm' ) or (keys[337] == true) then 
          
           local rot = rot_x - .4       
            if rot >= 360 then rot = rot - 360 end
            if rot <= 0 then rot = rot + 360 end          
            camera:setRot ( rot,rot_y,rot_z )      
          end     
             
             
        --LOOK LEFT & RIGHT     
        if 	keyboard:keyIsDown ( 'k' ) or (keys[335] == true) then   

          local rot = rot_y-.4  
          if rot >= 360 then rot = rot - 360 end
          if rot <= 0 then rot = rot + 360 end
          camera:setRot ( rot_x,rot,rot_z )  
                  
        end   
            
        if 	keyboard:keyIsDown ( 'l' ) or (keys[336] == true) then      
          local rot = rot_y + .4
            if rot >= 360 then rot = rot - 360 end
            if rot <= 0 then rot = rot + 360 end          
            camera:setRot ( rot_x,rot,rot_z )      
            
        end    





camera['eyeX'] = eyeX
camera['eyeY'] = eyeY
camera['eyeZ'] = eyeZ



   
    
local delta=	coroutine.yield()
end
  
  
  
  
end

        
--*****************************************************************        
--MOUSE MOVE
function input.mouseMove(isDown)
  local x,y = MOAIInputMgr.device.pointer:getLoc()
end
--*****************************************************************        
--MOUSE LEFT
function input.mouseLeft(isDown)
  keyDown['mouseLeft'] = isDown
end
--*****************************************************************        
--KEYBOARD
function input.keyboard ( key, down ) 
    keys[key] = down
    
    
--ESC    
  if key == 27 and down == true then      
  bWorld:setGravity(0,-3,0)  
      
    
  end
    
--*******************************    
--ENTER SHIFT
    if key == 13 and down == true then      
           add_row()
    end
--*******************************    
--SPACE JUMP
    if key == 32 and down == true then
      throw_box()
    end
    
--*******************************
--DEBUG DRAW
if 	keyboard:keyIsDown ( '1' ) then  
  if doDebug== true then
      doDebug = false
  else
      doDebug = true
  end 
end

    
    
end  
 
 
 
 
 
 --******************************************************************************
--LOAD INPUTS
function L._load_inputs()
  
  
--    MOAIGfxDevice.setListener ( MOAIGfxDevice.EVENT_RESIZE, F._screenSize )
  

  --KEYBOARD
    MOAIInputMgr.device.keyboard:setCallback ( input.keyboard )

--  --MOUSE
--    MOAIInputMgr.device.pointer:setCallback ( input.mouseMove )

--  --LEFT_CLICK
--    MOAIInputMgr.device.mouseLeft:setCallback(input.mouseLeft)

--  --RIGHT_CLICK
--    MOAIInputMgr.device.mouseRight:setCallback(input.mouseRight)

end
L._load_inputs()

mThread['enterFrame'] = MOAICoroutine.new ()
mThread['enterFrame']:run ( A._enterFrame )

 
 
 
  