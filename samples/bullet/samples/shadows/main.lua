
print ( 'hello, moai!' )
MOAISim.openWindow ( "test", 1280,720 )


  
  
  

--********************************************************************************
--********************************************************************************
--********************************************************************************







--require("square_mesh")



--local viewport_game = MOAIViewport.new ()
--viewport_game:setSize (   1280,720)
--viewport_game:setScale (   1280,720 )


--local bWorld = {}

--  --NEW CLASS
--  bWorld = MOAIBulletWorld.new()    
--  --MEMORY
--  bWorld:defaultMaxCollisionAlgorithmPoolSize(65536)--65536
--  bWorld:defaultMaxPersistentManifoldPoolSize(65536)--65536    
--  --CREATE AFTER MEMORY SET
--  bWorld:create(); 
--  --SET
--  bWorld:setStep(60)
--  bWorld:setMaxSubSteps(1)
--  bWorld:iterations(4)
--  bWorld:splitImpulse(true)
--  bWorld:useContinuous(true)    
--  bWorld:setForceUpdateAllAabbs(true)  
--  bWorld:allowedCcdPenetration(1) 
--  bWorld:enableSPU(false) --FOR PS3
--  bWorld:debugDraw(true)
--  bWorld:collisionHandler(true)  
--  --GRAVITY
--  bWorld:setGravity(0,-3,0)  
--  --DEBUG
--  bWorld:setDrawScale(1)
--  bWorld:setDrawJointSize(.1)      
  
--  bWorld:start() 
  
  
------*******************************
------TEST OBJECTS 
----local tObj =  bWorld:testObj()
----      tObj:testRagDoll(1,0,0)
----      tObj:testRagDoll(2,0,0)      
----      tObj:testJoint()
----      tObj:testCar()    
      
   
  
--m_body  = {}
--m_shape = {}
--plane   = {}
--m_props = {}
--m_mesh = {}

--m_mesh['cube']     = makeCube ( 100, 'moai.png' )


----***************************************************
----COLLISION CALLBACK
--local function cHandle(state,b1,b2)  
--  print(b1['idName'],b2['idName'])
--end
  

----*************************************************
----TRANSFORMER OBJECT
--local pos_start  = MOAIBulletTransform.new() 


      



--function initFrameBuffer ()
  
  
-- --*************************************************
-- --BUFFER  

--      local gfxQuad = MOAIGfxQuad2D.new ()
--      gfxQuad:setTexture ( "moai.png" )
--      gfxQuad:setRect ( 1280*.5*-1,720*.5*-1, 1280*.5,720*.5 )
--      gfxQuad:setUVRect ( 0, 0, 1, 1 )

--      local viewport = MOAIViewport.new ()
--      viewport:setSize ( 1280,720 )
--      viewport:setScale ( 1280,720 )

--      local camera = MOAICamera.new ()
--      camera:setRot(0,0,0)
--      camera:setLoc(0,0,camera:getFocalLength ( 15 ))

--      local layer = MOAILayerPass.new ()
--      layer:setViewport ( viewport )
--      layer:setCamera ( camera ) 
--      layer:enableLights(true)
      

      
--    print(gbuffer_shader);layer:set_gBuffer(gbuffer_shader)   
--    print(mainScene_shader);layer:set_mainScene(mainScene_shader)    
--    print(pointLightPass_shader);layer:set_lightPass(pointLightPass_shader)     
--    print(pointLightStencil_shader);layer:set_lightStencil(pointLightStencil_shader)    
--    print(ssao_shader);layer:set_ssao(ssao_shader)    
--    print(default_shader);layer:set_mainScene(default_shader) 
--    layer:setUp()
      
      
      
  
--      local frameBuffer = MOAIFrameBufferTexture.new ()
      
      
--          --local frameBuffer = MOAIBulletFBO.new ()
--          --layer:setFBO(frameBuffer)
     
--      frameBuffer:setRenderTable ({ layer })
--      frameBuffer:init ( 1280, 720 )
--      --frameBuffer:setClearColor ()
      
--      MOAIRenderMgr.setBufferTable ({ frameBuffer }) 
    
                
----**********************************************************************   
----BODY
--          pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,0,0)            
--          m_body['boxA']  = bWorld:newBody (pos_start)            
--          m_body['boxA']:addToWorld(true)          
--          m_body['boxA']:setActivationState(1)
--          m_body['boxA']:setIdName('boxA')
--          m_body['boxA']:setIdType('boxA')   
--         -- m_body['boxA']:setCallback(cHandle) --CALLBACK
--          m_body['boxA']:forceUpdate()
--          --SHAPE  
--          pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,0,0)  
--          m_shape['boxA'] = m_body['boxA']:newShape(pos_start)
--          m_shape['boxA']:makeBox(1,1,1)    
--          m_shape['boxA']:setMass(0,0)
--          m_shape['boxA']:addToBody();           


--          m_props['boxA'] = MOAIProp.new (); 
--          m_props['boxA']:setDeck ( m_mesh['cube'] )
--          m_props['boxA']:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER )) --SHADER GETS RESET
--          m_props['boxA']:setCullMode ( MOAIProp.CULL_BACK )
--          m_props['boxA']:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
--          m_props['boxA']:setDepthMask(true)
--          m_props['boxA']:setLoc(0,0) 
--          m_props['boxA']:setParent( m_body['boxA'])  

--          layer:insertProp ( m_props['boxA'] )      

         
          
      
----  --*************************************************
----  --LIGHT A  
  
--            --BODY
--            pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(2,0,0)            
--            m_body['sphere']  = bWorld:newBody (pos_start)            
--            m_body['sphere']:addToWorld(true)          
--            m_body['sphere']:setActivationState(1)
--            m_body['sphere']:setIdName('boxA')
--            m_body['sphere']:setIdType('boxA')   
--          --  m_body['sphere']:setCallback(cHandle) --CALLBACK
--            m_body['sphere']:forceUpdate()

--            --SHAPE  
--            pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,0,0)  
--            m_shape['sphere'] = m_body['sphere']:newShape(pos_start)
--            m_shape['sphere']:makeSphere(1,1,1)    
--            m_shape['sphere']:setMass(0,0)
--            m_shape['sphere']:addToBody(); 



--            m_props['sphere'] = MOAIProp.new (); 
--            m_props['sphere']:setDeck ( m_mesh['cube'] )
--            m_props['sphere']:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
--            m_props['sphere']:setCullMode ( MOAIProp.CULL_BACK )
--            m_props['sphere']:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
--            m_props['sphere']:setDepthMask(true)
--            m_props['sphere']:setLoc(0,0) 
--            m_props['sphere']:setParent( m_body['sphere'])  
            
--            --LIGHT LAYER
--            layer:insertLight ( m_props['sphere'] )         

          
          
          
          

      
      
      
      
 
--  --***************************************************
--  --PLANE : SHOULDN"T BE ATTACHED TO A BODY ????? FIX IN REFAC
  

--        pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,-4,0);       
--        plane['body']  = bWorld:newBody (pos_start)  
--        plane['body']:setRestitution(1)  
--        plane['body']:setFriction(1)      
--        plane['body']:setActivationState(MOAIBulletWorld['ISLAND_SLEEPING'])
--        plane['body']:setIdName('plane')
--        plane['body']:setIdType('plane')        
        
--        plane['body']:addToWorld(false)     

--        pos_start:setIdentity();pos_start:setEulerZYX(0.0,0,0);pos_start:setOrigin(0,0,0)
--        plane['planeA'] = plane['body']:newShape(pos_start)
--        plane['planeA']:makePlane(0,1,0)  --THIS WORKS
--        plane['planeA']:setMass(0,0)
--        plane['planeA']:addToBody();       
  
  
----***********************************************************************************
----***********************************************************************************
----***********************************************************************************
----***********************************************************************************
----DEBUG

--    local bullet_debug          = {}
--          bullet_debug['size']  = 100000  
          
--    local function onDraw_bullet ( index, xOff, yOff, xFlip, yFlip ) 
--     -- print('DRAWING')
--        bWorld:drawDebugLua()     
--    end

--    --NEW BOUNDS
--    bullet_debug['bounds'] = MOAIBoundsDeck.new ()
--    bullet_debug['bounds']:reserveBounds ( 1 )
--    bullet_debug['bounds']:reserveIndices ( 1 )  
--    bullet_debug['bounds']:setBounds ( 1, -bullet_debug['size'], -bullet_debug['size'], -bullet_debug['size'], bullet_debug['size'], bullet_debug['size'], bullet_debug['size'] )

--    --DRAWING DECK
--    bullet_debug['deck'] = MOAIScriptDeck.new ()
--    bullet_debug['deck']:setRect ( 1, 1, -1, -1 )
--    bullet_debug['deck']:setDrawCallback ( onDraw_bullet )
--    bullet_debug['deck']:setBoundsDeck ( bullet_debug['bounds'] )

--    --DRAW PROP
--    bullet_debug['prop'] = MOAIProp.new ()
--    bullet_debug['prop']:setDeck ( bullet_debug['deck'] )    
        
--    --SET DEBUG LINES IN FORNT OR BEHIND ALL OBJECTS
--        bullet_debug['prop']:setPriority(-1)
--        --bullet_debug['prop']:setPriority(10000)     

--    --INSTER
--    layer:insertProp ( bullet_debug['prop'] )


----*******************************************
----*******************************************
----*******************************************
----*******************************************
--              local gfxQuad = MOAIGfxQuad2D.new ()
--              gfxQuad:setTexture ( "moai.png" )
--              gfxQuad:setRect ( -1, -1, 1, 1 ) 

--              local prop = MOAIProp2D.new ()
--              prop:setDeck ( gfxQuad )

--              prop:setLoc(3,0)
--              layer:insertProp ( prop )
  
  
  
--  return frameBuffer
  
--end













--************************************************************************************* 
--*************************************************************************************
--*************************************************************************************
--*************************************************************************************

--local frameBuffer = initFrameBuffer ()

--gfxQuad = MOAIGfxQuad2D.new ()
--gfxQuad:setUVRect ( 0, 0, 1, 1 )
--gfxQuad:setTexture ( initFrameBuffer () )
--gfxQuad:setRect ( 1280*.5*-1,720*.5*-1, 1280*.5,720*.5 )
       
   
   
--gfxQuad:setTexture ( 'moai.png' )
--gfxQuad:setRect ( -32,-32,32,32 )
--gfxQuad:setShader(pointLightPass_shader);








MOAIGfxDevice.getFrameBuffer ():setClearDepth ( true )
MOAIGfxDevice.getFrameBuffer ():setClearColor ( .1,.1,.1,.1 )





local camera = MOAICamera.new ()
camera:setRot(0,0,0)
camera:setLoc(0,0,camera:getFocalLength ( 5 ))



local viewport = MOAIViewport.new ()
viewport:setSize ( 1280,720 )
viewport:setScale ( 1280,720 )


--*******************************************
local layer = MOAILayer.new ()
layer:setViewport ( viewport )
layer:setCamera(camera)
MOAISim.pushRenderPass ( layer )
    

--print('------------------')
local gbuffer_shader            = dofile('shaders//gbuffer_shader.lua');
--local mainScene_shader          = dofile('shaders//mainScene_shader.lua');
--local pointLightPass_shader     = dofile('shaders//pointLightPass_shader.lua');
--local pointLightStencil_shader  = dofile('shaders//pointLightStencil_shader.lua');
--local ssao_shader               = dofile('shaders//ssao_shader.lua');

--local default_shader               = dofile('shaders//default_shader.lua'); 
--print('------------------')


--print(gbuffer_shader);layer:set_gBuffer(gbuffer_shader)   
--print(mainScene_shader);layer:set_mainScene(mainScene_shader)    
--print(pointLightPass_shader);layer:set_lightPass(pointLightPass_shader)     
--print(pointLightStencil_shader);layer:set_lightStencil(pointLightStencil_shader)    
--print(ssao_shader);layer:set_ssao(ssao_shader)    
--print(default_shader);layer:set_mainScene(default_shader) 
--layer:setUp()  
    
    
    
    



--local box = MOAIProp.new ()
--box:setDeck ( m_mesh['cube']  )
--    --box:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
--    box:setShader(gbuffer_shader)

--box:setCullMode ( MOAIProp.CULL_BACK )

--layer:insertProp ( box )



--local light = MOAIProp.new ()
--light:setDeck ( dofile("geo//cube.lua") )
--light:setLoc(1,1)
----light:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
--light:setShader(gbuffer_shader)
--light:setCullMode ( MOAIProp.CULL_BACK )
--layer:insertProp ( light )





local light = MOAIProp.new ()
light:setDeck ( dofile("geo//pony.lua") )
light:setLoc(1,1)
--light:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
light:setShader(gbuffer_shader)
light:setCullMode ( MOAIProp.CULL_BACK )
layer:insertProp ( light )








































--***********************************************************************************
--***********************************************************************************
--***********************************************************************************
--***********************************************************************************
--FPS

--mTimers = {}
--D = {}
--function D._FPS()       

--      local fps    	  = MOAISim.getPerformance()
--      local drawCount = MOAIRenderMgr.getPerformanceDrawCount()     
--      print( m_shape['boxB'], m_shape['boxA'], m_body['boxA'],m_body['boxB'] )


--      mTimers['fps']:stop()
--end

--mTimers['fps']  = MOAITimer.new()
--mTimers['fps']:setSpan(5)
--mTimers['fps']:setMode(MOAITimer.LOOP)
--mTimers['fps']:setListener(MOAITimer.EVENT_TIMER_END_SPAN,D._FPS,0)
----mTimers['fps']:start()
 









