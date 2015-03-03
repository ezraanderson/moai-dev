--In Bullet Physics:
--* yaw = y-axis
--* pitch = x-axis
--* roll = z-axis

--So I believe your angle order should be YXZ. Also, you should use radians, not degrees (multiply your angles by PI/180). 

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

local isFullscreen   = false
local doDebug        = false
local isCar          = true
local slope_angle    = 15 
local collision_list = {}
local state_obj      = {} --OBJ LIST FOR RESTING THE GAME

--********************************************************************
--BUFFER
  MOAIGfxDevice.getFrameBuffer ():setClearDepth ( true )
  
  
  --MOAIGfxDevice.getFrameBuffer ():setClearColor ( .2,.3,.1,.1 )
--********************************************************************
--VIEWPORTS

  --GAME
  MOAISim.openWindow ( "test", 1280,720 )
  viewport_game = MOAIViewport.new ()
  viewport_game:setSize (   1280,720)
  viewport_game:setScale (   1280,720 )

  --HUD
  viewport_hud = MOAIViewport.new ()
  viewport_hud:setSize (   1280,720)
  viewport_hud:setScale (   1280,-720 )
  viewport_hud:setOffset ( -1, 1 )
--********************************************************************
--CAMERA
  local camera = MOAICamera.new ()
    --camera:setOrtho ( false )
  --camera:setNearPlane ( 1 )
  camera:setFarPlane ( 500 )
  camera:setRot(0,0,0)
  camera:setLoc(0,1,camera:getFocalLength ( 10 ))
--********************************************************************
--LAYERS

  --GAME
  --layer = MOAILayerPass.new ()
  layer = MOAILayer.new ()  
  layer:setViewport ( viewport_game )
  layer:setSortMode ( MOAILayer.SORT_NONE )
  layer:setCamera ( camera )
  layer:setClearDepth ( true )
  
  MOAISim.pushRenderPass ( layer )


  --HUD
  layer_hud = MOAILayer.new ()
  layer_hud:setViewport ( viewport_hud )
  MOAISim.pushRenderPass (layer_hud )
  
--********************************************************************
--FONT FOR DISPLAYING COLLISION BODIES
local   font = MOAIFont.new ()
        font:load ( 'sreda.ttf' )

local   textbox = MOAITextBox.new ()
        textbox:setFont ( font )
        textbox:setTextSize ( 18 )
        textbox:setString ( "" )
        textbox:setRect ( 0,0,300,700-30 )
        textbox:setAlignment ( MOAITextBox.LEFT_JUSTIFY, MOAITextBox.LEFT_JUSTIFY )
        textbox:setColor(1,0,0,1)
        textbox:setLoc(50,50)        
        layer_hud:insertProp ( textbox )




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
  mesh:setTexture  ("images/fountain.png")
  
	mesh:setVertexBuffer ( vbo )
	mesh:setPrimType ( MOAIMesh.GL_TRIANGLES )
--	mesh:setHigh(36)
	return mesh
end
--*************************************************************************
function makeCube ( size, texture )
      size = size * 0.01
      return makeBoxMesh ( -size, -size, -size, size, size, size, texture )
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
--*************************************************************************
function makeSide ( width,height,length, texture )
      width = width * 0.01
      height = height * 0.01    
      length = length * 0.01       
      return makeBoxMesh (  -width, -height, -length, 
                            width, height, length, 
                          texture 
                          )
end
--***********************************************************************
--THE : WORLD

  --NEW CLASS
  bWorld = MOAIBulletWorld.new()    
  --MEMORY
  bWorld:defaultMaxCollisionAlgorithmPoolSize(1638)--65536
  bWorld:defaultMaxPersistentManifoldPoolSize(1638)--65536    
  bWorld:create(); 
  --SET
  bWorld:setStep(1/60)
  bWorld:setMaxSubSteps(10)
  bWorld:iterations(1)
  bWorld:splitImpulse(true)
  bWorld:useContinuous(true)    
  bWorld:setForceUpdateAllAabbs(false)  
  bWorld:allowedCcdPenetration(0.001) 
  bWorld:enableSPU(true) --FOR PS3
  bWorld:debugDraw(true)
  bWorld:collisionHandler(true)     
  
  bWorld:setGravity(0,-5,0)  
  --DEBUG
  bWorld:setDrawScale(1)
  bWorld:setDrawJointSize(.1)      
  
  --MOAI ACTION
  bWorld:start()   
  
--***********************************************************************
--DEFAULT RANSFOMRS
local pos_start  = MOAIBulletTransform.new()
local pos_offset = MOAIBulletTransform.new()    

--***********************************************************************
--TEXTURES
local textures = {
  'images/bookshelf.png',  --1
  'images/brick.png',      --2
  'images/clay.png',       --3
  'images/cobble.png',     --4
  'images/cobble.png',     --5
  'images/grass.png',      --6 
  'images/gravel.png',     --7  
  'images/lava.png',       --8
  'images/tree.png',       --9 
  'images/alpha.png',       --10   
  'images/moai.png',       --11  
  }

--***********************************************************************************
--TREE TOP
local m_mesh  = {}
local m_body  = {}
local m_shape = {}
local m_props = {}
local m_vehicle = {}
local m_wheel  = {}

--MESH
m_mesh['tree_top']     = makeCube ( 300, textures[6] )
m_mesh['tree_bottom']  = makeCube ( 100, textures[9] )


--*****************************************************************************************
--REALY UGLE COLLISION CALLBACK SHOULD USE FILTER BEFORE THE CALL TO LUA AS AN IGONER GROUP
local cache_1,cache_2 = 1,2
local cCnt = 0
local function cHandle(state,b1,b2)
  
  if b1['idType'] ~=  b2['idType'] then  
  
    
    if cache_1 ~= b1['idName']..b2['idName'] then    
      --print(state,b1['idName'],b1['idType'],'>>',b2['idName'],b2['idType']) 
      print(state,b1['idName'],'>>',b2['idType']) 
      cCnt = cCnt + 1
      
      --****************************
      --PRINT COLLISION ON SCREEN
      collision_list[#collision_list+1] = cCnt..': '..b1['idName']..' < '..b2['idType']..'\n'      
      for  i = #collision_list, 1,-1 do
        if #collision_list > 10 then
            table.remove(collision_list,1)           
        end
      end         
      
      local cList = ''      
      for i = #collision_list, 1,-1 do
          cList = cList .. collision_list[i]
      end
      
      textbox:setString(cList)
      
      cache_1 = b1['idName']..b2['idName']  
    end 
  end
 
  

 
end  
--************************************************************************
--MAKE TREE ON SLOOP
-- THIS NEEDS TO SHARE SHAPES
-- THIS DOESN"T NEED TO BE A BODY
local function make_tree(pos_x,pos_z)       
        
         -- pos_x = 10            
       
          local point   = {}
          local center  = {}
          local angle   = rad(slope_angle); -- Convert to radians     


          point['x']   = 0+0
          point['y']   = 0-pos_z

          center['x']  = 0
          center['y']  = 0                 
       
          local rotatedX = cos(angle) * (point.x - center.x) - sin(angle) * (point.y - center.y) + center.x;
          local rotatedY = sin(angle) * (point.x - center.x) + cos(angle) * (point.y - center.y) + center.y; 

          z_offset = rotatedY
          y_offset = rotatedX*-1 
     
      
    --**************************************************************
    --**************************************************************
    --TREE TOP

        --START
          pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(pos_x,(y_offset+8),z_offset)
        --BODY
          m_body['tree_top']  = bWorld:newBody (pos_start)
          m_body['tree_top']:setActivationState(4) 
          m_body['tree_top']:setIdName('top')
          m_body['tree_top']:setIdType('tree')             
          m_body['tree_top']:forceUpdate()
          m_body['tree_top']:addToWorld(false)
        --SHAPE  
          pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,0,0)  
          m_shape['tree_top'] = m_body['tree_top']:newShape(pos_start)
          m_shape['tree_top']:makeBox(3,3,3) 
          m_shape['tree_top']:setMass(0,0)
          m_shape['tree_top']:addToBody();      
        --PROP
          m_props['tree_top'] = MOAIProp.new (); 
          m_props['tree_top']:setDeck ( m_mesh['tree_top'] )
          m_props['tree_top']:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
          m_props['tree_top']:setCullMode ( MOAIProp.CULL_BACK )
          m_props['tree_top']:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
          m_props['tree_top']:setDepthMask(true)
          m_props['tree_top']:setLoc(0,0) 
          m_props['tree_top']:setParent( m_body['tree_top'])
        --RENDER
          layer:insertProp ( m_props['tree_top'] )      

      
    --**************************************************************
    --**************************************************************  
    --TREE BOTTOM  
       local root_y = {4,2,0}  
       -- local root_y = {0}
          
        for i = 1, #root_y do 
            --START
            pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(pos_x,tonumber(y_offset+root_y[i]),z_offset)        
            --BODY
            m_body['tree_bodyA']  = bWorld:newBody (pos_start)
            m_body['tree_bodyA']:setActivationState(4) 

            m_body['tree_bodyA']:setIdName('trunk')
            m_body['tree_bodyA']:setIdType('tree')  
            --m_body['tree_bodyA']:setCallback(cHandle) --CALLBACK 
     
            
            
            m_body['tree_bodyA']:forceUpdate()
            m_body['tree_bodyA']:addToWorld(false)  
            --SHAPE
            pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,0,0)        
            m_shape['tree_shapeA'] = m_body['tree_bodyA']:newShape(pos_start)              
            m_shape['tree_shapeA']:makeBox(1,1,1) 
            m_shape['tree_shapeA']:setMass(0,0)
            m_shape['tree_shapeA']:addToBody();           
           --PROP
            m_props['tree_propA'] = MOAIProp.new ();  
            m_props['tree_propA']:setDeck ( m_mesh['tree_bottom'] )
            m_props['tree_propA']:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
            m_props['tree_propA']:setCullMode ( MOAIProp.CULL_BACK )
            m_props['tree_propA']:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
            m_props['tree_propA']:setDepthMask(true)
            m_props['tree_propA']:setLoc(0,0) 
            m_props['tree_propA']:setParent( m_body['tree_bodyA']) 
           --RENDER 
            layer:insertProp ( m_props['tree_propA'] ) 
            
        end
end

--MAKE
for i = 0, 100 do
      make_tree(math.random(-8,8),((i*35)))  
      make_tree(math.random(-8,8),((i*35)*-1))    
end


--***********************************************************************************
--***********************************************************************************
--***********************************************************************************
--***********************************************************************************
--CAR

local	gVehicleSteering		= 0.0;
local	steeringIncrement		= 0.01;
local	steeringClamp			  = 0.1;

local function make_Car()


	local rightIndex = 0
	local upIndex = 1
	local forwardIndex = 2

  --MESH
      m_mesh['car']         =  makeBoard ( 40,5,100, textures[9] )
     
    --BODY
      pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,.1,0)
      m_body['car']  = bWorld:newBody (pos_start)
      m_body['car']:setActivationState(4) --is RAYCAST SET OFF
      m_body['car']:setIdName('car')
      m_body['car']:setIdType('vehicle')       
      m_body['car']:forceUpdate()
      m_body['car']:addToWorld(true) 
      m_body['car']:setRestitution(.3) 
     -- m_body['car']:setCallback(cHandle) --CALLBACK
     
     --RESET
      state_obj[#state_obj+1] = m_body['car']
      
      
      --TEST STUFF
          --m_body['car']:setCcdMotionThreshold(1)
          --m_body['car']:setCcdSweptSphereRadius(1)         
          --m_pBody->setCcdSquareMotionThreshold(0.5f * fMinSize);  
          --m_pBody->setCcdSweptSphereRadius(0.2f * fMinSize);   
          --body->setCcdMotionThreshold(1.0f);
          --body->setCcdSweptSphereRadius(0.2f); 
      
      
    --SHAPE     
      pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,0,0)
      m_shape['car'] = m_body['car']:newShape(pos_start)           
      m_shape['car']:makeBox(.4,0.1,1)        
      m_shape['car']:setMass(800,0)
      m_shape['car']:setMargin(0.01)    
      
      m_shape['car']:addToBody();       
    
    --VEHICLE : ORDER 
        --1 : TUNE
        --2 : ADD
        --3 : CORDINATES
        --4 : WHEELS
        
      --NEW  
          m_vehicle['car'] =  m_body['car']:newVehicle()
      --TUNE IT
      
       -- ADD IT
       m_vehicle['car']:setToWorld()       
       
      --CORDINATES : ORDER
       m_vehicle['car']:setCoordinateSystem(rightIndex,upIndex,forwardIndex)
         

      
--***********************************************************************************
--***********************************************************************************
--***********************************************************************************
--***********************************************************************************
--WHEEL
for i = 1, 4 do      
  m_wheel[i] = m_vehicle['car']:newWheel();
  m_wheel[i]:setWheelDirection(0,-1,0)   
  m_wheel[i]:setWheelAxle(-1,0,0)  
  m_wheel[i]:setFrontWheel(false)
  m_wheel[i]:setWheelRadius(0.3)   
  m_wheel[i]:suspensionRestLength(1) 
end      

      
        local cubeHalfE					= 1.3
        local connectionHeight	= 1
        local wheelRadius				= 0.3
        local wheelWidth				= 1
      
        --CONNECTION_POINT & 
        m_wheel[1]:setConnectionPoint(cubeHalfE-(0.3*wheelWidth),connectionHeight,2*cubeHalfE-wheelRadius)        
        m_wheel[1]:addWheelToVehicle()
        
        m_wheel[2]:setConnectionPoint(-cubeHalfE+(0.3*wheelWidth),connectionHeight,2*cubeHalfE-wheelRadius)        
        m_wheel[2]:addWheelToVehicle()    
        
        m_wheel[3]:setConnectionPoint(-cubeHalfE+(0.3*wheelWidth),connectionHeight,-2*cubeHalfE+wheelRadius)        
        m_wheel[3]:addWheelToVehicle()          
        
        m_wheel[4]:setConnectionPoint(cubeHalfE-(0.3*wheelWidth),connectionHeight,-2*cubeHalfE+wheelRadius)        
        m_wheel[4]:addWheelToVehicle()  


      
         --PROP
        m_wheel['car'] = MOAIProp.new ();  
        m_wheel['car']:setDeck ( m_mesh['car'] )
        m_wheel['car']:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
        m_wheel['car']:setCullMode ( MOAIProp.CULL_BACK )
        m_wheel['car']:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
        m_wheel['car']:setDepthMask(true)
        m_wheel['car']:setLoc(0,0)--OFFSET FORSHAPE  
        m_wheel['car']:setParent( m_body['car'])        
    
        
       --RENDER 
        layer:insertProp ( m_wheel['car'] )     
      
end            
make_Car()

--***********************************************************************************
--PLANE
local function make_plane()
        local plane = {}
print('slope_angle >>>>',slope_angle)
       
        pos_start:setIdentity();pos_start:setEulerZYX(rad(slope_angle)*-1,0,0);pos_start:setOrigin(0,0,0);       
        plane['body']  = bWorld:newBody (pos_start)  
        plane['body']:setRestitution(1)  
        plane['body']:setFriction(1)      
        plane['body']:setActivationState(4)
        plane['body']:setIdName('run')
        plane['body']:setIdType('plane')          
        
        plane['body']:addToWorld(false)
        plane['body']['idName'] = 'plane'

        pos_start:setIdentity();pos_start:setEulerZYX(0.0,0,0);pos_start:setOrigin(0,0,0)
        plane['planeA'] = plane['body']:newShape(pos_start)
        plane['planeA']:makePlane(0,1,0)  --THIS WORKS
        plane['planeA']:setMass(0,0)
        plane['planeA']:addToBody();    
        
            

--**************************************************************************************      
--QUICKLY MAKE 2 MESHS 
-- I NOW I AM USING THE SAME LOCAL VARIBLES THIS IS JUST TESTINg
                
                
                
                
   --**************
   --GRASS             
          
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
                plane_mesh:setTexture ( "images//grass.png" )
                plane_mesh:setVertexBuffer ( plane_vbo )
                plane_mesh:setPrimType ( MOAIMesh.GL_TRIANGLE_FAN )
               -- plane_mesh:setHigh(4)  


                plane_prop = MOAIProp.new ()
                plane_prop:setDeck ( plane_mesh )
                plane_prop:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
                --plane_prop:setCullMode ( MOAIProp.CULL_BACK )
                plane_prop:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
                plane_prop:setDepthMask(true)               
                plane_prop:setLoc(0,-.3)         
                         
                           
                plane_prop:setRot(90-slope_angle,0,0)              
                          
                layer:insertProp ( plane_prop)      
                
                
                      

   --**************
   --SNOW
          local plane_vertexFormat = MOAIVertexFormat.new ()
                plane_vertexFormat:declareCoord ( 1, MOAIVertexFormat.GL_FLOAT, 2 )            
                plane_vertexFormat:declareColor ( 3, MOAIVertexFormat.GL_UNSIGNED_BYTE )

          local plane_vbo = MOAIVertexBuffer.new ()
                plane_vbo:setFormat ( plane_vertexFormat )
                plane_vbo:reserveVerts ( 4 )
                
                
                plane_vbo:writeFloat ( -12, -100000 )
                plane_vbo:writeColor32 ( 1,1,1)

                plane_vbo:writeFloat ( 12, -100000 )
                plane_vbo:writeColor32 ( 1,1,1)

                plane_vbo:writeFloat ( 12, 100000)
                plane_vbo:writeColor32 ( 1,1,1)

                plane_vbo:writeFloat ( -12, 100000 )
                plane_vbo:writeColor32 ( 1,1,1)

                plane_vbo:bless ()      

                
                

                local plane_mesh= MOAIMesh.new ()
                plane_mesh:setTexture ( "images//clay.png" )
                plane_mesh:setVertexBuffer ( plane_vbo )
                plane_mesh:setPrimType ( MOAIMesh.GL_TRIANGLE_FAN )
                -- plane_mesh:setHigh(4)  


                plane_prop = MOAIProp.new ()
                plane_prop:setDeck ( plane_mesh )
                plane_prop:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
                --plane_prop:setCullMode ( MOAIProp.CULL_BACK )
                plane_prop:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
                plane_prop:setDepthMask(true)               
                   
                plane_prop:setLoc(0,0.01)           
                   
                plane_prop:setRot(90-slope_angle,0,0)              
                  
                layer:insertProp ( plane_prop)

                
        
                
end

make_plane()

--***********************************************************************************
--MAKE SIDE RALLIES
local function make_side()

                
 --***************                
 --RIGHT SIDE
        pos_start:setIdentity();pos_start:setEulerZYX(rad(slope_angle)*-1,0,0);pos_start:setOrigin(11,0,0);       
        m_body['right_side']  = bWorld:newBody (pos_start)  
        m_body['right_side']:setRestitution(0)            
        m_body['right_side']:setFriction(0)      
        m_body['right_side']:setActivationState(4)
        m_body['right_side']:setIdName('right_side')
        m_body['right_side']:setIdType('side') 
        
        
        m_body['right_side']:forceUpdate()
        m_body['right_side']:addToWorld(false)
        m_body['right_side']['idName'] = 'left_side'

        pos_start:setIdentity();pos_start:setEulerZYX(0.0,0,0);pos_start:setOrigin(0,0,0)
        m_shape['right_side'] = m_body['right_side']:newShape(pos_start)
        m_shape['right_side']:makeBox(1,1,10000)  --THIS WORKS
        m_shape['right_side']:setMass(0,0)
        m_shape['right_side']:addToBody();         
        
   
  
     --MESH
        m_mesh['right_side']         =  makeBoard ( 100,100,10000000, '' )


    --PROP
        m_props['right_side'] = MOAIProp.new ();  
        m_props['right_side']:setDeck ( m_mesh['right_side'] )
        m_props['right_side']:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
        m_props['right_side']:setCullMode ( MOAIProp.CULL_BACK )
        m_props['right_side']:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
        m_props['right_side']:setDepthMask(true)
        m_props['right_side']:setLoc(0,0)--OFFSET FORSHAPE  
        m_props['right_side']:setParent( m_body['right_side']) 
          
       --RENDER 
        layer:insertProp ( m_props['right_side'] )          
                
         
                
                
--************                
--LEFT SIDE
        pos_start:setIdentity();pos_start:setEulerZYX(rad(slope_angle)*-1,0,0);pos_start:setOrigin(-11,0,0);       
        m_body['left_side']  = bWorld:newBody (pos_start)  
        m_body['left_side']:setRestitution(0)            
        m_body['left_side']:setFriction(0)      
        m_body['left_side']:setActivationState(4)
        m_body['left_side']:setIdName('left_side')
        m_body['left_side']:setIdType('side')        
        
        m_body['left_side']:forceUpdate()
        m_body['left_side']:addToWorld(false)
        m_body['left_side']['idName'] = 'left_side'

        pos_start:setIdentity();pos_start:setEulerZYX(0.0,0,0);pos_start:setOrigin(0,0,0)
        m_shape['left_side'] = m_body['left_side']:newShape(pos_start)
        m_shape['left_side']:makeBox(1,1,10000)  --THIS WORKS
        m_shape['left_side']:setMass(0,0)
        m_shape['left_side']:addToBody();         
        
   
  
     --MESH
        m_mesh['left_side']         =  makeBoard ( 100,100,10000000, '' )


    --PROP
        m_props['left_side'] = MOAIProp.new ();  
        m_props['left_side']:setDeck ( m_mesh['left_side'] )
        m_props['left_side']:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
        m_props['left_side']:setCullMode ( MOAIProp.CULL_BACK )
        m_props['left_side']:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
        m_props['left_side']:setDepthMask(true)
        m_props['left_side']:setLoc(0,0)--OFFSET FORSHAPE  
        m_props['left_side']:setParent( m_body['left_side']) 
          
       --RENDER 
        layer:insertProp ( m_props['left_side'] )               
        
        
        


end
make_side()

--***********************************************************************************
--MAKE RAGDOLL



  local m_shapes = {}
  local m_joints = {}
    
local function rag_doll()

    --local m_body = {}
  

    local mass    = 0.1 --JOINT STRENGTH BASED ON WIEGHT
    local inertia = 0

    local offset_x = 0
    local offset_y = 0
    local offset_z = 0
    --************************************
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,1,0);pos_start:doOffset(offset_x,offset_y,offset_z)
    m_body['BODYPART_PELVIS']	= bWorld:newBody (pos_start)
    m_body['BODYPART_PELVIS']:setActivationState(4)   
    m_body['BODYPART_PELVIS']:setIdName('pelvis')
    m_body['BODYPART_PELVIS']:setIdType('dummy') 
    
          state_obj[#state_obj+1] =  m_body['BODYPART_PELVIS']
    
    
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,0,0)  
    m_shapes['BODYPART_PELVIS']=m_body['BODYPART_PELVIS']:newShape(pos_start)
    m_shapes['BODYPART_PELVIS']:makeCapsule(0.15,0.15)
    m_shapes['BODYPART_PELVIS']:setMass(mass,inertia)
    m_shapes['BODYPART_PELVIS']:addToBody();
    


    --************************************

    pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,1.2,0);pos_start:doOffset(offset_x,offset_y,offset_z)
    
    m_body['BODYPART_SPINE']			  = bWorld:newBody (pos_start)
    m_body['BODYPART_SPINE']:setActivationState(4)    
    m_body['BODYPART_SPINE']:setIdName('spine')
    m_body['BODYPART_SPINE']:setIdType('dummy') 
   
          state_obj[#state_obj+1] =  m_body['BODYPART_SPINE']
       
       
       
    
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,0,0)  
    m_shapes['BODYPART_SPINE']			= m_body['BODYPART_SPINE']:newShape(pos_start)
    m_shapes['BODYPART_SPINE']:makeCapsule(0.15,0.18)
    m_shapes['BODYPART_SPINE']:setMass(mass,inertia)
    m_shapes['BODYPART_SPINE']:addToBody();


    ----************************************
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,1.6,-0.01);pos_start:doOffset(offset_x,offset_y,offset_z)
    m_body['BODYPART_HEAD']				  = bWorld:newBody (pos_start)
    m_body['BODYPART_HEAD']:setActivationState(4)  
    m_body['BODYPART_HEAD']:setIdName('head')
    m_body['BODYPART_HEAD']:setIdType('dummy')  
    
    m_body['BODYPART_HEAD']:setCallback(cHandle) --CALLBACK     
    state_obj[#state_obj+1] =  m_body['BODYPART_HEAD']   
    
    
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,0,0)
    m_shapes['BODYPART_HEAD']				= m_body['BODYPART_HEAD']	:newShape(pos_start)
    m_shapes['BODYPART_HEAD']:makeBox(0.15,0.15,0.15)
    m_shapes['BODYPART_HEAD']:setMass(mass,inertia)

    m_shapes['BODYPART_HEAD']:addToBody();
    

    ---******************************************


    ------************************************
    pos_start:setIdentity();pos_start:setEulerZYX(-M_PI_2,0,0);pos_start:setOrigin(-0.18,0.75,0.2);pos_start:doOffset(offset_x,offset_y,offset_z)
    m_body['BODYPART_LEFT_UPPER_LEG']	  = bWorld:newBody (pos_start)
    m_body['BODYPART_LEFT_UPPER_LEG']:setActivationState(4) 
    m_body['BODYPART_LEFT_UPPER_LEG']:setIdName('leg')
    m_body['BODYPART_LEFT_UPPER_LEG']:setIdType('dummy')     
    
     state_obj[#state_obj+1] =  m_body['BODYPART_LEFT_UPPER_LEG']
    
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,0,0)
    m_shapes['BODYPART_LEFT_UPPER_LEG']	= m_body['BODYPART_LEFT_UPPER_LEG']:newShape(pos_start)
    m_shapes['BODYPART_LEFT_UPPER_LEG']:makeBox(0.07,0.25,0.07)
    m_shapes['BODYPART_LEFT_UPPER_LEG']:setMass(mass,inertia)
    m_shapes['BODYPART_LEFT_UPPER_LEG']:addToBody();
    
 


    --************************************
    pos_start:setIdentity();pos_start:setEulerZYX(-M_PI_2,0,0);pos_start:setOrigin(0.18,0.75,0.2);pos_start:doOffset(offset_x,offset_y,offset_z)
    m_body['BODYPART_RIGHT_UPPER_LEG']	  = bWorld:newBody (pos_start)
    m_body['BODYPART_RIGHT_UPPER_LEG']:setActivationState(4)   
    m_body['BODYPART_RIGHT_UPPER_LEG']:setIdName('leg')
    m_body['BODYPART_RIGHT_UPPER_LEG']:setIdType('dummy')     
    
    state_obj[#state_obj+1] =  m_body['BODYPART_RIGHT_UPPER_LEG']
    
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,0,0)
    m_shapes['BODYPART_RIGHT_UPPER_LEG']	= m_body['BODYPART_RIGHT_UPPER_LEG']:newShape(pos_start)
    m_shapes['BODYPART_RIGHT_UPPER_LEG']:makeBox(0.07,0.25,0.07)
    m_shapes['BODYPART_RIGHT_UPPER_LEG']:setMass(mass,inertia)
    m_shapes['BODYPART_RIGHT_UPPER_LEG']:addToBody();
    




    --************************************
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,M_PI_2);pos_start:setOrigin(-0.35,1.45,0);pos_start:doOffset(offset_x,offset_y,offset_z)
    m_body['BODYPART_LEFT_UPPER_ARM']	  = bWorld:newBody (pos_start)
    m_body['BODYPART_LEFT_UPPER_ARM']:setActivationState(4)   
    m_body['BODYPART_LEFT_UPPER_ARM']:setIdName('arm')
    m_body['BODYPART_LEFT_UPPER_ARM']:setIdType('dummy')        
    
    state_obj[#state_obj+1] =  m_body['BODYPART_LEFT_UPPER_ARM']
    
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,0,0)
    m_shapes['BODYPART_LEFT_UPPER_ARM']	= m_body['BODYPART_LEFT_UPPER_ARM']:newShape(pos_start)
    m_shapes['BODYPART_LEFT_UPPER_ARM']:makeBox(0.05,0.20,0.05)
    m_shapes['BODYPART_LEFT_UPPER_ARM']:setMass(mass,inertia)
    m_shapes['BODYPART_LEFT_UPPER_ARM']:addToBody()
    





    --************************************
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,-M_PI_2);pos_start:setOrigin(0.35,1.45,0);pos_start:doOffset(offset_x,offset_y,offset_z)
    m_body['BODYPART_RIGHT_UPPER_ARM']	  = bWorld:newBody (pos_start)--:addToWorld()
    m_body['BODYPART_RIGHT_UPPER_ARM']:setActivationState(4) 
    m_body['BODYPART_RIGHT_UPPER_ARM']:setIdName('arm')
    m_body['BODYPART_RIGHT_UPPER_ARM']:setIdType('dummy')     
    
      state_obj[#state_obj+1] =  m_body['BODYPART_RIGHT_UPPER_ARM']
    
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,0,0)
    m_shapes['BODYPART_RIGHT_UPPER_ARM']	= m_body['BODYPART_RIGHT_UPPER_ARM']:newShape(pos_start)
    m_shapes['BODYPART_RIGHT_UPPER_ARM']:makeBox(0.05,0.20,0.05)
    m_shapes['BODYPART_RIGHT_UPPER_ARM']:setMass(mass,inertia)
    m_shapes['BODYPART_RIGHT_UPPER_ARM']:addToBody()

    --DAMPING
    for k,v in pairs(m_body) do
      --v:setDamping(0.05, 0.085)
      --v:setDeactivationTime(0.8);
      --v:setSleepingThresholds(0.2, 0.2);  
      --v:setKinematic()
      -- v:setActivationState(1) 
    end

    local btTransformA = MOAIBulletTransform.new();btTransformA:setIdentity();
    local btTransformB = MOAIBulletTransform.new();btTransformA:setIdentity();
    local offsetX = 0
    local offsetY = 0
    local offsetZ = 0



 print('ADDING PARTS TO WORLD')
 
--BODY & HEAD
    m_body['BODYPART_PELVIS']:addToWorld(true)
    m_body['BODYPART_SPINE']:addToWorld(true)
    m_body['BODYPART_HEAD']:addToWorld(true)
    
--LEFS   
    m_body['BODYPART_LEFT_UPPER_LEG']:addToWorld(true)
    m_body['BODYPART_RIGHT_UPPER_LEG']:addToWorld(true)
    
--ARMS    
    m_body['BODYPART_LEFT_UPPER_ARM']:addToWorld(true);
    m_body['BODYPART_RIGHT_UPPER_ARM']:addToWorld(true);


    print('MAKING JOINTS')   
    
    
    --*******************************
    btTransformA:setIdentity();btTransformA:setEulerZYX(0,M_PI_2,0);btTransformA:setOrigin(0,0.15, 0);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,M_PI_2,0);btTransformB:setOrigin(0,-0.15,0);
    m_joints['JOINT_PELVIS_SPINE'] = bWorld:addJointHinge(m_body['BODYPART_PELVIS'],m_body['BODYPART_SPINE'],btTransformA,btTransformB,true)
    m_joints['JOINT_PELVIS_SPINE']:setLimit(-M_PI_4, M_PI_2);
    m_joints['JOINT_PELVIS_SPINE']:setBreakingImpulse(2.0)  
    m_joints['JOINT_PELVIS_SPINE']:addToWorld(true)        

    --*******************************
    btTransformA:setIdentity();btTransformA:setEulerZYX(0,0,M_PI_2);btTransformA:setOrigin(0,0.25,0);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,0,M_PI_2);btTransformB:setOrigin(0,-0.14,0.);
    m_joints['JOINT_SPINE_HEAD'] = bWorld:addJointCone(m_body['BODYPART_SPINE'],m_body['BODYPART_HEAD'],btTransformA,btTransformB,false)
    m_joints['JOINT_SPINE_HEAD']:setLimit(M_PI_4, M_PI_4, M_PI_2); --3 WTF
    m_joints['JOINT_SPINE_HEAD']:setBreakingImpulse(2.0)  
    m_joints['JOINT_SPINE_HEAD']:addToWorld(true)
    
    --*******************************
    btTransformA:setIdentity();btTransformA:setEulerZYX(0,0,-M_PI_4*5);btTransformA:setOrigin(-0.18,-0.10,0.00);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,0,-M_PI_4*5);btTransformB:setOrigin(0.00,0.225,0.00);
    m_joints['JOINT_LEFT_HIP'] = bWorld:addJointCone(m_body['BODYPART_PELVIS'],m_body['BODYPART_LEFT_UPPER_LEG'],btTransformA,btTransformB,false)
    m_joints['JOINT_LEFT_HIP']:setLimit(M_PI_4, M_PI_4, 0); 
    m_joints['JOINT_LEFT_HIP']:setBreakingImpulse(2.0)
    m_joints['JOINT_LEFT_HIP']:addToWorld(true)    
    --*******************************
    btTransformA:setIdentity();btTransformA:setEulerZYX(0,0,M_PI_4);btTransformA:setOrigin(0.18,-0.10,0.00);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,0,M_PI_4);btTransformB:setOrigin(0.00,0.225,0.00);
    m_joints['JOINT_RIGHT_HIP'] = bWorld:addJointCone(m_body['BODYPART_PELVIS'],m_body['BODYPART_RIGHT_UPPER_LEG'],btTransformA,btTransformB,false)
    m_joints['JOINT_RIGHT_HIP']:setLimit(M_PI_4, M_PI_4, 0); 
    m_joints['JOINT_RIGHT_HIP']:setBreakingImpulse(2.0)
    m_joints['JOINT_RIGHT_HIP']:addToWorld(true)   
    ----*******************************
    btTransformA:setIdentity();btTransformA:setEulerZYX(0,0,M_PI);btTransformA:setOrigin(-0.2,0.15,0.0);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,0,M_PI_2);btTransformB:setOrigin(0.0,-0.18,0.0);
    m_joints['JOINT_LEFT_SHOULDER'] = bWorld:addJointCone(m_body['BODYPART_SPINE'],m_body['BODYPART_LEFT_UPPER_ARM'],btTransformA,btTransformB,false)
    m_joints['JOINT_LEFT_SHOULDER']:setLimit(M_PI_2, M_PI_2,0);  
    m_joints['JOINT_LEFT_SHOULDER']:setBreakingImpulse(2.0)
    m_joints['JOINT_LEFT_SHOULDER']:addToWorld(true)      
    --*******************************
    btTransformA:setIdentity();btTransformA:setEulerZYX(0,0,0);btTransformA:setOrigin(0.2,0.15,0.00);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,0,M_PI_2);btTransformB:setOrigin(0.00,-0.18,0.00);
    m_joints['JOINT_RIGHT_SHOULDER'] = bWorld:addJointCone(m_body['BODYPART_SPINE'],m_body['BODYPART_RIGHT_UPPER_ARM'],btTransformA,btTransformB,false)
    m_joints['JOINT_RIGHT_SHOULDER']:setLimit(M_PI_2, M_PI_2,0); 
    m_joints['JOINT_RIGHT_SHOULDER']:setBreakingImpulse(2.0)
    m_joints['JOINT_RIGHT_SHOULDER']:addToWorld(true)      




--************************************************************************************
--************************************************************************************
--HEAD : BLENDER DATA
 m_mesh['head'] = dofile('blender//head.lua')
 m_mesh['head']:setTexture ( "images//face.png" )

m_props['head']= MOAIProp.new ();  
m_props['head']:setDeck (  m_mesh['head'] )
m_props['head']:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
m_props['head']:setCullMode ( MOAIProp.CULL_BACK )
m_props['head']:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
m_props['head']:setDepthMask(true)
m_props['head']:setLoc(0,0) 
m_props['head']:setScl(0.16,0.16,0.16)
--RENDER 
layer:insertProp ( m_props['head'] ) 

m_props['head']:setParent(m_body['BODYPART_HEAD']	)
m_body['BODYPART_HEAD']:forceUpdate();

--************************************************************************************
--leg_left

m_mesh['leg_left'] = dofile('blender//leg.lua')
m_mesh['leg_left'] :setTexture ( "images//leg.png" )

m_props['leg_left']= MOAIProp.new ();  
m_props['leg_left']:setDeck ( m_mesh['leg_left'] )
m_props['leg_left']:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
m_props['leg_left']:setCullMode ( MOAIProp.CULL_BACK )
m_props['leg_left']:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
m_props['leg_left']:setDepthMask(true)
m_props['leg_left']:setLoc(0,0) 
m_props['leg_left']:setRot(90,0,0) --Y UP

--RENDER 
layer:insertProp ( m_props['leg_left'] ) 

m_props['leg_left']:setParent(m_body['BODYPART_LEFT_UPPER_LEG']	)
m_body['BODYPART_LEFT_UPPER_LEG']:forceUpdate();


--************************************************************************************
--leg_right
m_mesh['leg_right'] = dofile('blender//leg.lua')
m_mesh['leg_right'] :setTexture ( "images//leg.png" )

m_props['leg_right']= MOAIProp.new ();  
m_props['leg_right']:setDeck ( m_mesh['leg_right'] )
m_props['leg_right']:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
m_props['leg_right']:setCullMode ( MOAIProp.CULL_BACK )
m_props['leg_right']:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
m_props['leg_right']:setDepthMask(true)
m_props['leg_right']:setLoc(0,0) 
m_props['leg_right']:setRot(90,0,0) --Y UP

--RENDER 
layer:insertProp ( m_props['leg_right'] ) 

m_props['leg_right']:setParent(m_body['BODYPART_RIGHT_UPPER_LEG']	)
m_body['BODYPART_RIGHT_UPPER_LEG']:forceUpdate();

--************************************************************************************
--ARM_RIGHT
m_mesh['arm_right'] = dofile('blender//arm.lua')
m_mesh['arm_right'] :setTexture ( "images//arm.png" )

m_props['arm_right']= MOAIProp.new ();  
m_props['arm_right']:setDeck ( m_mesh['arm_right'] )
m_props['arm_right']:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
m_props['arm_right']:setCullMode ( MOAIProp.CULL_BACK )
m_props['arm_right']:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
m_props['arm_right']:setDepthMask(true)
m_props['arm_right']:setLoc(0,0) 
m_props['arm_right']:setRot(90,0,0) --Y UP

--RENDER 
layer:insertProp ( m_props['arm_right'] ) 

m_props['arm_right']:setParent(m_body['BODYPART_RIGHT_UPPER_ARM']	)
m_body['BODYPART_RIGHT_UPPER_ARM']:forceUpdate();





--************************************************************************************
--ARM_LEFT
m_mesh['arm_left'] = dofile('blender//arm.lua')
m_mesh['arm_left'] :setTexture ( "images//arm.png" )

m_props['arm_left']= MOAIProp.new ();  
m_props['arm_left']:setDeck ( m_mesh['arm_right'] )
m_props['arm_left']:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
m_props['arm_left']:setCullMode ( MOAIProp.CULL_BACK )
m_props['arm_left']:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
m_props['arm_left']:setDepthMask(true)
m_props['arm_left']:setLoc(0,0) 
m_props['arm_left']:setRot(90,0,0) --Y UP

--RENDER 
layer:insertProp ( m_props['arm_left'] ) 

m_props['arm_left']:setParent(m_body['BODYPART_LEFT_UPPER_ARM']	)
m_body['BODYPART_LEFT_UPPER_ARM']:forceUpdate();






--************************************************************************************
--SPINE
m_mesh['spine'] = dofile('blender//spine.lua')
m_mesh['spine'] :setTexture ( "images//spine.png" )

m_props['spine']= MOAIProp.new ();  
m_props['spine']:setDeck ( m_mesh['spine'] )
m_props['spine']:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
m_props['spine']:setCullMode ( MOAIProp.CULL_BACK )
m_props['spine']:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
m_props['spine']:setDepthMask(true)
m_props['spine']:setLoc(0,-.05) 
m_props['spine']:setRot(90,0,0) --Y UP

--RENDER 
layer:insertProp ( m_props['spine'] ) 

m_props['spine']:setParent(m_body['BODYPART_SPINE']	)
m_body['BODYPART_SPINE']:forceUpdate();


  --SET THE STATE OF THE OBJECT
  for k,v in pairs(state_obj) do  
    print('Setting STATE',k,v) 
    v:stateSet()  
  end  
        



end


rag_doll()

--*******************************************************************************************
local function make_joints()
---JOINT RAG TO CAR
    local btTransformA = MOAIBulletTransform.new();btTransformA:setIdentity();
    local btTransformB = MOAIBulletTransform.new();btTransformA:setIdentity();
    local offsetX = 0
    local offsetY = 0
    
    btTransformA:setIdentity();btTransformA:setEulerZYX(0,0,0);btTransformA:setOrigin(0,0.1,0);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,0,0);btTransformB:setOrigin(0,0.1,0);
    m_joints['bum'] = bWorld:addJointCone(m_body['BODYPART_PELVIS'],m_body['car'],btTransformA,btTransformB,true)
    m_joints['bum']:setBreakingImpulse(1.3)
    m_joints['bum']:addToWorld(true) 


    btTransformA:setIdentity();btTransformA:setEulerZYX(0,0,0);btTransformA:setOrigin(0,0,0);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,0,0);btTransformB:setOrigin(0,1,0);
    m_joints['leg_left'] = bWorld:addJointCone(m_body['BODYPART_HEAD'],m_body['car'],btTransformA,btTransformB,true)
    m_joints['leg_left']:setBreakingImpulse(1.3)
    m_joints['leg_left']:addToWorld(true) 
    
    
     m_joints['bum']:setEnabled(true)
     m_joints['bum']:setEnabled(true)
  end

make_joints()


--***********************************************************************************
--***********************************************************************************
--***********************************************************************************
--***********************************************************************************
--ALLOWS YOU DRAW INFRONT OR BEHIND TEXTURES

    local bullet_debug          = {}
          bullet_debug['size']  = 100000  
    local function onDraw_bullet ( index, xOff, yOff, xFlip, yFlip ) 
      
      MOAIDraw.drawLight()
      
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
   -- bullet_debug['prop']:setPriority(-1)
    bullet_debug['prop']:setPriority(10000)   
    
    
  --INSTER
   layer:insertProp ( bullet_debug['prop'] )



--*****************************************************************************
--FPS
mTimers = {}
D = {}
local drawTime = 0;
local cache_time = 0
function D._FPS()       

      local fps    	  = MOAISim.getPerformance()
      local drawCount = MOAIRenderMgr.getPerformanceDrawCount()     
      local drawTime  = MOAIRenderMgr.getDrawTime() - cache_time 
      cache_time      = MOAIRenderMgr.getDrawTime()
      
      print(fps,drawCount,drawTime)
end

mTimers['fps']  = MOAITimer.new()
mTimers['fps']:setSpan(1)
mTimers['fps']:setMode(MOAITimer.LOOP)
mTimers['fps']:setListener(MOAITimer.EVENT_TIMER_END_SPAN,D._FPS,0)
mTimers['fps']:start()

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
     
     
     
 local stop_s = 5

 
if isCar == true then   

if m_body['car'] ~= nil then  

--****************************************
--MOTION
  
    if keyboard:keyIsDown ( 'w' ) then         
   
      m_vehicle['car']:applyGas(-5000,3)
      m_vehicle['car']:applyGas(-5000,4) 

      --NO BRAKES
      m_vehicle['car']:applyBrake(0,4)
      m_vehicle['car']:applyBrake(0,3)  
      
      m_vehicle['car']:applyBrake(0,1)
      m_vehicle['car']:applyBrake(0,2)      
      
    end 

    
    
     
    if keyboard:keyIsDown ( 's' ) then     
  
        m_vehicle['car']:applyGas(0,1)
        m_vehicle['car']:applyGas(0,2)  
        
        m_vehicle['car']:applyGas(5000,3) 
        m_vehicle['car']:applyGas(5000,4)  
 
 
        m_vehicle['car']:applyBrake(50,1)
        m_vehicle['car']:applyBrake(50,2)     
                  
     
    end
     
     
--****************************************
--CAR

local isSteer = false

    if keyboard:keyIsDown ( 'a' ) then 
      isSteer = true
      gVehicleSteering = gVehicleSteering + steeringIncrement
      if gVehicleSteering > steeringClamp then
       gVehicleSteering = steeringClamp
      end 
    end    
        
    
    if keyboard:keyIsDown ( 'd' ) then      
      isSteer = true
      gVehicleSteering = gVehicleSteering - steeringIncrement 
      if gVehicleSteering < -steeringClamp then
        gVehicleSteering = -steeringClamp
      
      end 
    end

    if isSteer == false then
      gVehicleSteering = 0 
    end   
     
     m_vehicle['car']:applySteering(gVehicleSteering,4)
     m_vehicle['car']:applySteering(gVehicleSteering,3)   
     
    
if   m_joints['leg_left'] then  
  if (m_joints['leg_left']:isEnabled())  then   
        local car_x,car_y,car_z = m_body['car']:getPosition()
        camera:setLoc(car_x,car_y+5,car_z+10) 
        camera:setRot(-14,0,0)   
        
        --fog_prop:setLoc(car_x,3,car_z-40)
        if isFullscreen == true then
           camera:setLoc(car_x,car_y+5,car_z+10+2)
           camera:setRot(-14,0,0)   
        end
           
  else
        local dummy_x,dummy_y,dummy_z = m_body['BODYPART_HEAD']:getPosition()
        camera:setLoc(dummy_x,dummy_y+5,dummy_z+10)         
        camera:setRot(-14,0,0)        
        --fog_prop:setLoc(dummy_x,3,dummy_z-40)
        
        if isFullscreen == true then
                  camera:setLoc(dummy_x,dummy_y+5,dummy_z+10+2)         
                  camera:setRot(-14,0,0)  
        end
        
  end
end
    

end
     

 end     

 
 
 
 
 
--***************************************************
--***************************************************
--***************************************************
--FREE CAMERA
 

if isCar == false then
 
          --DEBUG STUFF
        local camera_x,camera_y,camera_z = camera:getLoc() 
        local rot_x,rot_y,rot_z          = camera:getRot()     
          
        local speed       = 0.9
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

end

   
    
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
    
      for k,v in pairs(state_obj) do  
        print('RESET BODY',k,v) 
        v:stateReset()  
      end  
      
      
        for k,v in pairs(m_joints) do  
        print('RESET BODY',k,v) 
        v:setEnabled	(true)  
      end       

      collision_list = {}
      cCnt = 0
      textbox:setString("")
      crash_ang = 14
      
    
  end
    
--*******************************    
--ENTER SHIFT
    if key == 13 and down == true then      
      bWorld:setGravity(0,5,0)            
    end
--*******************************    
--SPACE JUMP
    if key == 32 and down == true then
          m_body['car']:applyImpulse(0,2800,0)  
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
--*******************************
-- FREE CAMERA
if 	keyboard:keyIsDown ( '2' ) then  
   if isCar== true then
    isCar = false
  else
    isCar = true
  end  
end   
    
    
end  

--***************************************************************************
--FULLSCREEN CALLBACK
myDisplay = {}
system    = {}
myDisplay['width'] = 1280
myDisplay['height'] = 720

system['SCREEN_W'] = MOAIEnvironment['horizontalResolution']
system['SCREEN_H'] = MOAIEnvironment['verticalResolution']

--**************************************
--SEEMS TO BE A CAMRA BUG

function F._screenSize(a,b)

  if isFullscreen == false then
  isFullscreen = true
  else
  isFullscreen = false
  end

myDisplay['width']   = a
myDisplay['height']  = b

viewport_game:setSize ( myDisplay['width'], myDisplay['height'])
viewport_game:setScale ( 1280,720)

viewport_hud:setSize ( myDisplay['width'], myDisplay['height'])
viewport_hud:setScale ( 1280,-720)


end
--******************************************************************************
--LOAD INPUTS
function L._load_inputs()
  
  
    MOAIGfxDevice.setListener ( MOAIGfxDevice.EVENT_RESIZE, F._screenSize )
  

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

mThread['enterFrame'] = MOAICoroutine.new ()
mThread['enterFrame']:run ( A._enterFrame )








