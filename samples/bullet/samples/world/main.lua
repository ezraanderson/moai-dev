
require('square_mesh')
m_mesh = {}
m_mesh['cube']     = makeCube ( 100, 'moai.png' )

MOAIGfxDevice.getFrameBuffer ():setClearDepth ( true )
MOAIGfxDevice.getFrameBuffer ():setClearColor ( .1,.1,.1,.1 )

MOAISim.openWindow ( "test", 1280,720 )
local viewport_game = MOAIViewport.new ()
viewport_game:setSize (   1280,720)
viewport_game:setScale (   1280,720 )


local camera = MOAICamera.new ()
camera:setRot(0,0,0)
camera:setLoc(0,0,camera:getFocalLength ( 15 ))

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
  bWorld:setStep(60)
  bWorld:setMaxSubSteps(1)
  bWorld:iterations(4)
  bWorld:splitImpulse(true)
  bWorld:useContinuous(true)    
  bWorld:setForceUpdateAllAabbs(true)  
  bWorld:allowedCcdPenetration(1) 
  bWorld:enableSPU(false) --FOR PS3
  bWorld:debugDraw(true)
  bWorld:collisionHandler(true)  
  --GRAVITY
  bWorld:setGravity(0,-3,0)  
  --DEBUG
  bWorld:setDrawScale(1)
  bWorld:setDrawJointSize(.1)      
  
  bWorld:start() 
  
  
--*******************************
--TEST OBJECTS 
--local tObj =  bWorld:testObj()
--      tObj:testRagDoll(1,0,0)
--      tObj:testRagDoll(2,0,0)      
--      tObj:testJoint()
--      tObj:testCar()    
      
   
  
m_body  = {}
m_shape = {}
plane   = {}
m_props = {}
  
--***************************************************
--COLLISION CALLBACK
local function cHandle(state,b1,b2)  
  print(b1['idName'],b2['idName'])
end
  

  --*************************************************
  --TRANSFORMER OBJECT
  local pos_start  = MOAIBulletTransform.new() 
  
  
  --*************************************************
  --BODY A  
          --BODY
          pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(3,0,0)            
          m_body['boxA']  = bWorld:newBody (pos_start)            
          m_body['boxA']:addToWorld(true)          
          m_body['boxA']:setActivationState(1)
          m_body['boxA']:setIdName('boxA')
          m_body['boxA']:setIdType('boxA')   
          m_body['boxA']:setCallback(cHandle) --CALLBACK
         
        --SHAPE  
          pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,0,0)  
          m_shape['boxA'] = m_body['boxA']:newShape(pos_start)
          m_shape['boxA']:makeBox(1,1,1)    
          m_shape['boxA']:setMass(0,0)
          m_shape['boxA']:addToBody(); 
          
          
                
            print(m_mesh['cube'])
      
          m_props['sphere'] = MOAIProp.new (); 
          m_props['sphere']:setDeck ( m_mesh['cube'] )
          m_props['sphere']:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
          m_props['sphere']:setCullMode ( MOAIProp.CULL_BACK )
          m_props['sphere']:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
          m_props['sphere']:setDepthMask(true)
          m_props['sphere']:setLoc(0,0) 
          m_props['sphere']:setParent( m_body['boxA'])  
      
          layer:insertProp ( m_props['sphere'] )      
          
          
          
          
          
          
  --*************************************************
  --BODY B  
          --BODY
          pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(-3,0,0)            
          m_body['boxB']  = bWorld:newBody (pos_start)           
          m_body['boxB']:addToWorld(true)          
          m_body['boxB']:setActivationState(1)          
          m_body['boxB']:setCallback(cHandle) --CALLBACK
          m_body['boxB']:setIdName('boxB')
          m_body['boxB']:setIdType('boxB')           
          --SHAPE  
          pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(1,0,0)  
          m_shape['boxB'] = m_body['boxB']:newShape(pos_start)
          m_shape['boxB']:makeSphereM(.3,.3,1)  
          m_shape['boxB']:setMass(10,0)            
          
          m_shape['boxB']:addToBody();   


--***************************************************
--JOINTS
          
        local btTransformA = MOAIBulletTransform.new();btTransformA:setIdentity();
        local btTransformB = MOAIBulletTransform.new();btTransformA:setIdentity();             
        btTransformA:setIdentity();btTransformA:setEulerZYX(0,0,0);btTransformA:setOrigin(-3,0,0);
        btTransformB:setIdentity();btTransformB:setEulerZYX(0,0,0);btTransformB:setOrigin(3,0,0.);        
        
        
        
        m_joints = bWorld:addJointHinge(m_body['boxA'],m_body['boxB'],btTransformA,btTransformB,false) 
        --m_joints = bWorld:addJointCone(m_body['boxA'],m_body['boxB'],btTransformA,btTransformB,false) 
        --m_joints = bWorld:addJointFixed(m_body['boxA'],m_body['boxB'],btTransformA,btTransformB,false) 
        --m_joints = bWorld:addJointPoint(m_body['boxA'],m_body['boxB'],btTransformA,btTransformB,false)  
        --m_joints = bWorld:addJointSlider(m_body['boxA'],m_body['boxB'],btTransformA,btTransformB,false)  
        --m_joints = bWorld:addJointFreedom(m_body['boxA'],m_body['boxB'],btTransformA,btTransformB,true)     
            
        m_joints:addToWorld(false);
        m_joints:setDebugDrawSize(1);      
 
  --***************************************************
  --PLANE : SHOULDN"T BE ATTACHED TO A BODY ????? FIX IN REFAC
  

        pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,-4,0);       
        plane['body']  = bWorld:newBody (pos_start)  
        plane['body']:setRestitution(1)  
        plane['body']:setFriction(1)      
        plane['body']:setActivationState(MOAIBulletWorld['ISLAND_SLEEPING'])
        plane['body']:setIdName('plane')
        plane['body']:setIdType('plane')        
        
        plane['body']:addToWorld(false)     

        pos_start:setIdentity();pos_start:setEulerZYX(0.0,0,0);pos_start:setOrigin(0,0,0)
        plane['planeA'] = plane['body']:newShape(pos_start)
        plane['planeA']:makePlane(0,1,0)  --THIS WORKS
        plane['planeA']:setMass(0,0)
        plane['planeA']:addToBody();     
        

 
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
      print( m_shape['boxB'], m_shape['boxA'], m_body['boxA'],m_body['boxB'] )
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

        bWorld:drawDebugLua()     
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
        bullet_debug['prop']:setPriority(-1)
        --bullet_debug['prop']:setPriority(10000)   
    
    
  --INSTER
   layer:insertProp ( bullet_debug['prop'] )
 
 
 
 
  