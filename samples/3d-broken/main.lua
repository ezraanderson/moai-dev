
print("BORKEN CAMERA")
input = {}
L = {}
F = {}
A = {}
mThread = {}


function math_dist3D(x1,y1,z1, x2,y2,z2) return ((x2-x1)^2+(y2-y1)^2+(z2-z1)^2)^0.5 end


MOAISim.openWindow ( "test", 1280,720 )
viewport = MOAIViewport.new ()
viewport:setSize (   1280,720)
viewport:setScale (   1280,720 )
layer = MOAILayer.new ()
layer:setViewport ( viewport )
layer:setClearColor(1,1,1,1)
layer:setSortMode ( MOAILayer.SORT_PRIORITY_DESCENDING) --ORDER TO SORT BY
MOAIGfxDevice.getFrameBuffer ():setClearDepth ( true )

MOAISim.pushRenderPass ( layer )

local camera = MOAICamera.new ()
layer:setCamera ( camera )
--CAMERA
camera:setRot(0,0,0)
camera:setLoc(0,0,camera:getFocalLength ( 15 ))

local gfxQuad = MOAIGfxQuad2D.new ()
gfxQuad:setTexture ( "fountain.png" )
gfxQuad:setRect ( -2, -2, 2, 2 )

local prop = MOAIProp2D.new ()
prop:setDeck ( gfxQuad )



alpha_texture = MOAITexture.new()
alpha_texture:load( 'fountain.png' , MOAIImage.PREMULTIPLY_ALPHA )

---***********************************************************************
---***********************************************************************
---***********************************************************************
---***********************************************************************

function makeBoxMesh ( xMin, yMin, zMin, xMax, yMax, zMax, texture )
	
  --********************************
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
    
    print('x'..p1.x..","..'y'..p1.y..","..'z'.. p1.z..",".. uv1.x..",".. uv1.y..',r,g,b,a')    

		
		vbo:writeFloat ( p2.x, p2.y, p2.z )
		vbo:writeFloat ( uv2.x, uv2.y )
		vbo:writeColor32 ( 1, 1, 1 )
    
    print('x'..p2.x..",".. 'y'..p2.y..","..'z'.. p2.z..",".. uv2.x..",".. uv2.y..',r,g,b,a')
 

		vbo:writeFloat ( p3.x, p3.y, p3.z )
		vbo:writeFloat ( uv3.x, uv3.y  )
		vbo:writeColor32 ( 1, 1, 1 )
    
    print('x'..p3.x..",".. 'y'..p3.y..",".. 'z'..p3.z..","..uv3.x..",".. uv3.y..',r,g,b,a')
    
    
    
	end
	  --********************************
	local function writeFace ( vbo, p1, p2, p3, p4, uv1, uv2, uv3, uv4 )
		writeTri ( vbo, p1, p2, p4, uv1, uv2, uv4 )
		writeTri ( vbo, p2, p3, p4, uv2, uv3, uv4 )
	end
	
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
	mesh:setTexture ( alpha_texture )
	mesh:setVertexBuffer ( vbo )
	mesh:setPrimType ( MOAIMesh.GL_TRIANGLES )

	return mesh
end

function makeCube ( size, texture )
    size = size * 0.01
    return makeBoxMesh ( -size, -size, -size, size, size, size, texture )
end
local mesh = makeCube ( 100, 'fountain.png' )


--A
prop_meshA = MOAIProp.new ()
prop_meshA:setDeck ( mesh )
prop_meshA:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER )) 
prop_meshA:setCullMode ( MOAIProp.CULL_BACK ) 
prop_meshA:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
prop_meshA:setDepthMask(true)
prop_meshA['sortDistance'] = 0
prop_meshA['idName'] = 'MESHA'
prop_meshA:setLoc(4,0,0)
prop_meshA:setBillboard (true)
layer:insertProp ( prop_meshA )


----B
--prop_meshB = MOAIProp.new ()
--prop_meshB:setDeck ( mesh )
--prop_meshB:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
--prop_meshB:setCullMode ( MOAIProp.CULL_BACK ) 
--prop_meshB:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
--prop_meshB:setDepthMask(true)
--prop_meshB['sortDistance'] = 0
--prop_meshB['idName'] = 'MESHB'
--prop_meshB:setLoc(-4,0,0)
--prop_meshB:setBillboard (true)
--layer:insertProp ( prop_meshB )

--C

--prop_meshC = MOAIProp.new ()
--prop_meshC:setDeck ( mesh )
--prop_meshC:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
--prop_meshC:setCullMode ( MOAIProp.CULL_BACK ) 
--prop_meshC:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
--prop_meshC:setDepthMask(true)
--prop_meshC['sortDistance'] = 0
--prop_meshC['idName'] = 'MESHC'
--prop_meshC:setLoc(-4,0,0)
--layer:insertProp ( prop_meshC )





local props_to_sort = {}
props_to_sort[#props_to_sort+1] = prop_meshA
props_to_sort[#props_to_sort+1] = prop_meshB



local function sort_distance(a,b)
    return a['sortDistance'] < b['sortDistance']
end


--*****************************************************************************
--SORT PROPS
function A._enterFrameSort(delta)    
  while true do      
    
    local cam_x,cam_y,cam_y = camera:getLoc()
    
        --GET DISTANCE
        for i = 1,#props_to_sort do
            local prop_x,prop_y,prop_z = props_to_sort[i]:getLoc()            
            props_to_sort[i]['sortDistance']= math_dist3D(cam_x,cam_y,cam_y,prop_x,prop_y,prop_z)
        end
        --SORT BY DISTANCE
        table.sort(props_to_sort,sort_distance)        
        --UPDATE PRIORITY   
         for i = 1,#props_to_sort do          
           props_to_sort[i]:setPriority(i)
         end          
        
    
    local delta=	coroutine.yield()      
  end  
end

mThread['enterFrameSort'] = MOAICoroutine.new ()
mThread['enterFrameSort']:run ( A._enterFrameSort )




--*****************************************************************************
mTimers = {}
D = {}
function D._FPS()       

      local fps    	  = MOAISim.getPerformance()
      local drawCount = MOAIRenderMgr.getPerformanceDrawCount()     
      --print(fps,drawCount)
      --prop:forceUpdate()
     -- box['body']:sec()
end

mTimers['fps']  = MOAITimer.new()
mTimers['fps']:setSpan(0.001)
mTimers['fps']:setMode(MOAITimer.LOOP)
mTimers['fps']:setListener(MOAITimer.EVENT_TIMER_END_SPAN,D._FPS,0)
	mTimers['fps']:start()

--*****************************************************************************
--IMPUT
local keys  = {  
}





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
    
  local speed       = .2  
  local pitchRadian = math.rad(rot_x) 
  local yawRadian   = math.rad(rot_y)   
  
  
  

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

    local rot = rot_x + 1        
    if rot >= 360 then rot = rot - 360 end
    if rot <= 0 then rot = rot + 360 end          
    camera:setRot ( rot,rot_y,rot_z )  
end    
     
if 	keyboard:keyIsDown ( 'm' ) or (keys[337] == true) then 
  
   local rot = rot_x - 1        
    if rot >= 360 then rot = rot - 360 end
    if rot <= 0 then rot = rot + 360 end          
    camera:setRot ( rot,rot_y,rot_z )      
  end     
     
     
--LOOK LEFT & RIGHT     
if 	keyboard:keyIsDown ( 'k' ) or (keys[336] == true) then   

  local rot = rot_y-1  
  if rot >= 360 then rot = rot - 360 end
  if rot <= 0 then rot = rot + 360 end
  camera:setRot ( rot_x,rot,rot_z )  
          
end   
    
if 	keyboard:keyIsDown ( 'l' ) or (keys[335] == true) then       


    
  local rot = rot_y + 1        
    if rot >= 360 then rot = rot - 360 end
    if rot <= 0 then rot = rot + 360 end          
    camera:setRot ( rot_x,rot,rot_z )      
    
end       
    
  	local delta=	coroutine.yield()
    end
  
end
mThread['enterFrame'] = MOAICoroutine.new ()
mThread['enterFrame']:run ( A._enterFrame )
        
        

function input.mouseMove(isDown)
  local x,y = MOAIInputMgr.device.pointer:getLoc()
end


function input.keyboard ( key, down ) 
    keys[key] = down
    if key == 13 and down == true then
    end
end  

function input.mouseLeft(isDown)
  keyDown['mouseLeft'] = isDown
end

--******************************************************************************
--LOAD INPUTS
function L._load_inputs()

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














































