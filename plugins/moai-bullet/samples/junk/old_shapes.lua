























--local boxB = {}

----BODY
--  pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(14,0,0)
--  boxB['body']  = bWorld:newBody (pos_start)
--  boxB['body']:setActivationState(2)
--  boxB['body']:forceUpdate(); 
--  boxB['body']:addToWorld(false)

----SHAPE
--  boxB['shapeA'] = boxB['body']:newShape()
--  boxB['shapeA']:addBox(1,1,1) 
--  boxB['shapeA']:setMass(1000,1)
--  boxB['shapeA']:addToBody(); 

----BODY
--prop_meshA = MOAIProp.new ()
--prop_meshA:setDeck ( m_mesh['tree_top']  )
--prop_meshA:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
--prop_meshA:setCullMode ( MOAIProp.CULL_BACK )
--prop_meshA:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
--prop_meshA:setDepthMask(true)

--layer:insertProp ( prop_meshA )
--prop_meshA:setParent(boxB['body'])








--local mesh = makeCube ( 102, textures[4] )




--prop_meshA = MOAIProp.new ()
--prop_meshA:setDeck ( mesh )
----prop_meshA:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
--prop_meshA:setCullMode ( MOAIProp.CULL_BACK )
--prop_meshA:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
--prop_meshA:setDepthMask(true)
----prop_meshA:setLoc(-4,0,0)
--layer:insertProp ( prop_meshA )
--prop_meshA:setBlendMode(MOAIProp.BLEND_ADD)


--prop_meshB = MOAIProp.new ()
--prop_meshB:setDeck ( mesh )
--prop_meshB:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
--prop_meshB:setCullMode ( MOAIProp.CULL_BACK )
--prop_meshB:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
--prop_meshB:setDepthMask(true)

--layer:insertProp ( prop_meshB )


















--***********************************************************
    --local doll = bWorld:newBody (pos_start)
    --doll:addRag(2,0,0)
--***********************************************************
--local floor = 0x0001
--local wall  = 0x0002
--local ball  = 0x0004


--print(floor,wall,ball)
--local cnt = 0

--function doCall(state,b1,b2) 
      
--     -- if b1 ~= b2 then
--         -- print(b1,b2)
--      --end
--      cnt = cnt + 1
--      print(cnt,state,b1['idName'],b2['idName'])
--end  

--local cnt = 0

--for z = -5,5 do
--for y = 1,14 do
--for x = -5, 5 do
--pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(x*2,y*2,z*2)
--cnt = cnt + 1;

--local box = {}
--box['body']  = bWorld:newBody (pos_start)
--box['body']:setFilter(wall,floor+ball+wall)
--box['body']:setActivationState(2) --DISABLE

----box['body']:setCcdMotionThreshold(2) --DISABLE
----box['body']:setCcdSweptSphereRadius(2) --DISABLE


--box['body']['idName'] ='WALL'
--box['body']:addToWorld(true)
--box['body']:forceUpdate()


----box['body']:setDamping(.1,.1)

----box['body']:setCallback(doCall)


--box['body']:setRestitution(0)   
----box['body']:setPosition(0,0,0)
----box['body']:setRotation(0,0,0)

----box['body']:setLinearVelocity(5,0,0)   
----box['body']:setAngularVelocity(1,1,1)
----box['body']:setGravity(0,0,0)

----ONE SHAPE TO BODIES
--box['shapeA'] = box['body']:newShape()
--box['shapeA']:addBox(1,1,1) 
--box['shapeA']:setMass(1,1)
--box['shapeA']:addToBody(); 



--prop_mesh = MOAIProp.new ()
--prop_mesh:setDeck ( mesh )
--prop_mesh:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
----prop_mesh:setCullMode ( MOAIProp.CULL_BACK )
--prop_mesh:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
--prop_mesh:setDepthMask(true)
----prop_mesh:setColor(math.random(255)/255,math.random(255)/255,math.random(255)/255)
----prop_mesh:setColor(math.random(255)/255,math.random(255)/255,math.random(255)/255,math.random(255)/255)
----prop_mesh:setColor(1,0,0,1)
----prop_mesh:setBlendMode(MOAIProp.BLEND_ADD)
--layer:insertProp ( prop_mesh )
--prop_mesh:setParent(box['body'])

--end
--end
--end


--print('-----------')
--print('->OBJ CNT ->',cnt)
--print('-----------')














--local circle = {}
--pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(-25,15,-0.5)
--circle['body']  = bWorld:newBody (pos_start)
--circle['body']:addToWorld()
--circle['body']:setRestitution(1)   

----circle['body']:setPosition(0,0,0)
----circle['body']:setRotation(0,0,0)
----circle['body']:setGravity(0,0,0)

--circle['body']:setLinearVelocity(50,0,0)   
--circle['body']:setAngularVelocity(0,0,0)

----ONE SHAPE TO BODIES
--circle['shapeA'] = circle['body']:newShape()
--circle['shapeA']:addSphere(1,1)      
--circle['shapeA']:setPosition(0,0,0) --OFFSET
--circle['shapeA']:setRotation(0,0,0) --OFFSET
--circle['shapeA']:setMass(20,1)
--circle['shapeA']:addToBody(); 





--pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(-5,5,0.1)
--local boxA = {}

--boxA['body']  = bWorld:newBody (pos_start)
----boxB['body']:setFilter(ball,floor+ball+wall)
--boxA['body']:setCallback(doCall)
--boxA['body']:setActivationState(2)
--boxA['body']:forceUpdate();     --MUST FORCE THE BODY TO UPDATE : for first transform
--boxA['body']:addToWorld(true)
--boxA['body']['idName'] ='A'

----ONE SHAPE TO BODIES
--boxA['shapeA'] = boxA['body']:newShape()
--boxA['shapeA']:addBox(1,1,1) 
--boxA['shapeA']:setMass(1000,1)
--boxA['shapeA']:addToBody(); 

--prop_mesh = MOAIProp.new ()
--prop_mesh:setDeck ( mesh )
--prop_mesh:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
--prop_mesh:setCullMode ( MOAIProp.CULL_BACK )
--prop_mesh:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
--prop_mesh:setDepthMask(true)
--layer:insertProp ( prop_mesh )
--prop_mesh:setParent(boxA['body'])













--pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(-40,2,0.1)
--local boxB = {}

--boxB['body']  = bWorld:newBody (pos_start)
----boxB['body']:setFilter(ball,floor+ball+wall)
----boxB['body']:setCallback(doCall)
--boxB['body']:setActivationState(2)
--boxB['body']:forceUpdate();     --MUST FORCE THE BODY TO UPDATE : for first transform
--boxB['body']:addToWorld(false)
--boxB['body']['idName'] ='BOX'
----ATTTACH MESH
--prop_meshA:setParent(boxB['body'])
----ONE SHAPE TO BODIES
--boxB['shapeA'] = boxB['body']:newShape()
--boxB['shapeA']:addBox(1,1,1) 
--boxB['shapeA']:setMass(1000,1)
--boxB['shapeA']:addToBody(); 







----BODY MESH
--prop_meshA:setParent(box['body'])



--pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(10,0,0)
--local box = {}

--box['body']  = bWorld:newBody (pos_start)
--box['body']:addToWorld()
--box['body']:setRestitution(1)   

----box['body']:setPosition(0,0,0)
----box['body']:setRotation(0,0,0)

----box['body']:setLinearVelocity(5,0,0)   
----box['body']:setAngularVelocity(1,1,1)
----box['body']:setGravity(0,0,0)

----ONE SHAPE TO BODIES
--box['shapeA'] = box['body']:newShape()
--box['shapeA']:addBox(1,1,1)     

--box['shapeA']:setMass(2,1)
--box['shapeA']:addToBody(); 
--prop_meshB:setParent(box['body'])




--**********************************************************
--local plane = {}


--pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,1,0);
--plane['body']  = bWorld:newBody (pos_start)


--plane['body']:setRestitution(1)  
--plane['body']:setFriction(6) 
--plane['body']:setFilter(floor,floor+wall+ball)
--plane['body']:setActivationState(2)
--plane['body']:addToWorld(false)
--plane['body']['idName'] = 'plane'
----plane['body']:setCallback(doCall)

----plane['body']:addCollisionGroup(ball)
----plane['body']:addCollisionMask(ball)


----plane['body']:setPosition(0,0,0) --BODY POS
----plane['body']:setRotation(0,0,0)  --BODY POS
----plane['body']:setGravity(0,0,0)

--plane['planeA'] = plane['body']:newShape()
--plane['planeA']:addPlane(0,1,0)   


----plane['planeA']:setPosition(0,0,0)
----plane['planeA']:setRotation(0,0,0)
--plane['planeA']:setMass(0,0)
--plane['planeA']:addToBody(); 


----**********************************************************
--local circle = {}

--circle['body']  = bWorld:newBody ()
--circle['body']:addToWorld()
--circle['body']:setRestitution(1)   

--circle['body']:setPosition(0,0,0)
--circle['body']:setRotation(0,0,0)
----circle['body']:setGravity(0,0,0)

--circle['body']:setLinearVelocity(0,0,0)   
--circle['body']:setAngularVelocity(0,0,0)

----ONE SHAPE TO BODIES
--circle['shapeA'] = circle['body']:newShape()
--circle['shapeA']:addSphere(1,1)      
--circle['shapeA']:setPosition(0,0,0) --OFFSET
--circle['shapeA']:setRotation(0,0,0) --OFFSET
--circle['shapeA']:setMass(2,1)
----circle['shapeA']:addToBody(); 


----**********************************************************
--local box = {}

--box['body']  = bWorld:newBody ()
--box['body']:addToWorld()
--box['body']:setRestitution(1)   

--box['body']:setPosition(0,0,0)
--box['body']:setRotation(0,0,0)

--box['body']:setLinearVelocity(5,0,0)   
--box['body']:setAngularVelocity(1,1,10)
----box['body']:setGravity(0,0,0)

----ONE SHAPE TO BODIES
--box['shapeA'] = box['body']:newShape()
--box['shapeA']:addBox(1,1,1)      
--box['shapeA']:setPosition(0,0,0) --OFFSET
--box['shapeA']:setRotation(0,0,0) --OFFSET
--box['shapeA']:setMass(2,1)
----box['shapeA']:addToBody(); 


----**********************************************************
--local cone = {}

--cone['body']  = bWorld:newBody ()
--cone['body']:addToWorld()
--cone['body']:setRestitution(1)   

--cone['body']:setPosition(0,0,0)
--cone['body']:setRotation(0,0,0)

--cone['body']:setLinearVelocity(5,0,0)   
--cone['body']:setAngularVelocity(1,1,10)
----cone['body']:setGravity(0,0,0)

----ONE SHAPE TO BODIES
--cone['shapeA'] = cone['body']:newShape()
--cone['shapeA']:addCone(1,1)      
--cone['shapeA']:setPosition(0,0,0) --OFFSET
--cone['shapeA']:setRotation(0,0,0) --OFFSET
--cone['shapeA']:setMass(2,1)
----cone['shapeA']:addToBody(); 


----**********************************************************
--local cylinder = {}

--cylinder['body']  = bWorld:newBody ()
--cylinder['body']:addToWorld()
--cylinder['body']:setRestitution(1)   

--cylinder['body']:setPosition(0,2,0)
--cylinder['body']:setRotation(0,0,0)

--cylinder['body']:setLinearVelocity(4,0,0)   
--cylinder['body']:setAngularVelocity(1,1,10)
----cylinder['body']:setGravity(0,0,0)

----ONE SHAPE TO BODIES
--cylinder['shapeA'] = cylinder['body']:newShape()
--cylinder['shapeA']:addCylinder(1,1)      
--cylinder['shapeA']:setPosition(0,0,0) --OFFSET
--cylinder['shapeA']:setRotation(0,0,0) --OFFSET
--cylinder['shapeA']:setMass(2,1)
----cylinder['shapeA']:addToBody(); 


----**********************************************************
--local capsule = {}

--capsule['body']  = bWorld:newBody ()
--capsule['body']:addToWorld()
--capsule['body']:setRestitution(1)   

--capsule['body']:setPosition(0,2,0)
--capsule['body']:setRotation(0,0,0)

--capsule['body']:setLinearVelocity(-4,0,0)   
--capsule['body']:setAngularVelocity(0,0,0)
----capsule['body']:setGravity(0,0,0)


----ONE SHAPE TO BODIES
--capsule['shapeA'] = capsule['body']:newShape()
--capsule['shapeA']:addCapsule(1,1)      
--capsule['shapeA']:setPosition(0,0,0) --OFFSET
--capsule['shapeA']:setRotation(0,0,0) --OFFSET
--capsule['shapeA']:setMass(1,1)
----capsule['shapeA']:addToBody(); 








--*********************************************************
--*********************************************************
--*********************************************************


--print('>>> REMOVING BODY')
--capsule['body']:removeBodyFromWorld()
--capsule['body'] = nil
--capsule         = nil

--MOAISim:forceGarbageCollection()
--MOAISim:forceGarbageCollection()
--MOAISim:forceGarbageCollection()
--MOAISim:forceGarbageCollection()

--capsule['body']:addToWorld()


--*********************************************************
--JOINTS
  --static int		_addJointHinge			( lua_State* L );
  --static int		_addJointCone			( lua_State* L );
  --static int		_addJointFixed			( lua_State* L );
  --static int		_addJointFreedom		( lua_State* L );
  --static int		_addJointPoint			( lua_State* L );
  --static int		_addJointSlider			( lua_State* L );



--capsule['jointA'] = bWorld:addJointSlider		(capsule['body'],cylinder['body'],2,2,2, 1,1,1)
--capsule['jointA']:setBreakingImpulse(1000)
--capsule['jointA']:setLinLimit(-5,5) --LOWER,UPPER
--capsule['jointA']:setAngLimit(-5,5) --LOWER,UPPER

--print('IMPLUSE',capsule['jointA']:getBreakingImpulse())
--print('BODYA',capsule['jointA']:getBodyA())
--print('BODYB',capsule['jointA']:getBodyB())







--****************************************************************************************

--local rag_body = {
--  BODYPART_PELVIS = 0,
--  BODYPART_SPINE= 0,
--  BODYPART_HEAD= 0,
--  BODYPART_LEFT_UPPER_LEG= 0,
--  BODYPART_LEFT_LOWER_LEG= 0,
--  BODYPART_RIGHT_UPPER_LEG= 0,
--  BODYPART_RIGHT_LOWER_LEG= 0,
--  BODYPART_LEFT_UPPER_ARM= 0,
--  BODYPART_LEFT_LOWER_ARM= 0,
--  BODYPART_RIGHT_UPPER_ARM= 0,
--  BODYPART_RIGHT_LOWER_ARM= 0,
--  BODYPART_COUNT= 0
--}

--local rag_joints = {
--  JOINT_PELVIS_SPINE = 0,
--  JOINT_SPINE_HEAD= 0,
--  JOINT_LEFT_HIP= 0,
--  JOINT_LEFT_KNEE= 0,
--  JOINT_RIGHT_HIP= 0,
--  JOINT_RIGHT_KNEE= 0,
--  JOINT_LEFT_SHOULDER= 0,
--  JOINT_LEFT_ELBOW= 0,
--  JOINT_RIGHT_SHOULDER= 0,
--  JOINT_RIGHT_ELBOW= 0,
--  JOINT_COUNT= 0
--}









local function rag_doll()

    local m_body = {}
    local m_shapes = {}
    local m_joints = {}

    local mass    = 0.1
    local inertia = 0

    local offset_x = 0
    local offset_y = 0
    local offset_z = 0
    --************************************
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,1,0);pos_start:doOffset(offset_x,offset_y,offset_z)
    m_body['BODYPART_PELVIS']	= bWorld:newBody (pos_start)
    --m_body['BODYPART_PELVIS']:setPosition(0,1.0,0)
    m_shapes['BODYPART_PELVIS']=m_body['BODYPART_PELVIS']:newShape()
    m_shapes['BODYPART_PELVIS']:addCapsule(0.15,0.20)
    m_shapes['BODYPART_PELVIS']:setMass(mass,inertia)
    m_shapes['BODYPART_PELVIS']:addToBody();
    --m_body['BODYPART_PELVIS']:addToWorld()

    --************************************

    pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,1.2,0);pos_start:doOffset(offset_x,offset_y,offset_z)
    m_body['BODYPART_SPINE']			  = bWorld:newBody (pos_start)
    --m_body['BODYPART_SPINE']:setPosition(0,1.2,0)

    m_shapes['BODYPART_SPINE']			= m_body['BODYPART_SPINE']:newShape()
    m_shapes['BODYPART_SPINE']:addCapsule(0.15,0.28)
    m_shapes['BODYPART_SPINE']:setMass(mass,inertia)
    m_shapes['BODYPART_SPINE']:addToBody();
    --m_body['BODYPART_SPINE']:addToWorld()

    ----************************************
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0,1.6,0);pos_start:doOffset(offset_x,offset_y,offset_z)
    m_body['BODYPART_HEAD']				  = bWorld:newBody (pos_start)
    --m_body['BODYPART_HEAD']:setPosition(0,1.6,0)

    m_shapes['BODYPART_HEAD']				= m_body['BODYPART_HEAD']	:newShape()
    m_shapes['BODYPART_HEAD']:addCapsule(0.10,0.05)
    m_shapes['BODYPART_HEAD']:setMass(mass,inertia)

    m_shapes['BODYPART_HEAD']:addToBody();
    --m_body['BODYPART_HEAD']:addToWorld()


    ------************************************
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(-0.18,0.65,0);pos_start:doOffset(offset_x,offset_y,offset_z)
    m_body['BODYPART_LEFT_UPPER_LEG']	  = bWorld:newBody (pos_start)
    --m_body['BODYPART_LEFT_UPPER_LEG']:setPosition(-0.18,0.65,0)
    m_shapes['BODYPART_LEFT_UPPER_LEG']	= m_body['BODYPART_LEFT_UPPER_LEG']:newShape()
    m_shapes['BODYPART_LEFT_UPPER_LEG']:addCapsule(0.07,0.45)
    m_shapes['BODYPART_LEFT_UPPER_LEG']:setMass(mass,inertia)
    m_shapes['BODYPART_LEFT_UPPER_LEG']:addToBody();
    --m_body['BODYPART_LEFT_UPPER_LEG']:addToWorld()


    ----************************************
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(-0.18,0.2,0);pos_start:doOffset(offset_x,offset_y,offset_z)
    m_body['BODYPART_LEFT_LOWER_LEG']	  = bWorld:newBody (pos_start)
    --m_body['BODYPART_LEFT_LOWER_LEG']:setPosition(-0.18,0.2,0)
    m_shapes['BODYPART_LEFT_LOWER_LEG']	= m_body['BODYPART_LEFT_LOWER_LEG']:newShape()
    m_shapes['BODYPART_LEFT_LOWER_LEG']:addCapsule(0.05,0.37)
    m_shapes['BODYPART_LEFT_LOWER_LEG']:setMass(mass,inertia)
    m_shapes['BODYPART_LEFT_LOWER_LEG']:addToBody();
    --m_body['BODYPART_LEFT_LOWER_LEG']:addToWorld()

    --************************************
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0.18,0.65,0);pos_start:doOffset(offset_x,offset_y,offset_z)
    m_body['BODYPART_RIGHT_UPPER_LEG']	  = bWorld:newBody (pos_start)
    --m_body['BODYPART_RIGHT_UPPER_LEG']:setPosition(0.18,0.65,0)
    m_shapes['BODYPART_RIGHT_UPPER_LEG']	= m_body['BODYPART_RIGHT_UPPER_LEG']:newShape()
    m_shapes['BODYPART_RIGHT_UPPER_LEG']:addCapsule(0.07,0.45)
    m_shapes['BODYPART_RIGHT_UPPER_LEG']:setMass(mass,inertia)
    m_shapes['BODYPART_RIGHT_UPPER_LEG']:addToBody();
    --m_body['BODYPART_RIGHT_UPPER_LEG']:addToWorld()
    --************************************
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,0);pos_start:setOrigin(0.18,0.2,0);pos_start:doOffset(offset_x,offset_y,offset_z)
    m_body['BODYPART_RIGHT_LOWER_LEG']	  = bWorld:newBody (pos_start)
    --m_body['BODYPART_RIGHT_LOWER_LEG']:setPosition(0.18,0.2,0)
    m_shapes['BODYPART_RIGHT_LOWER_LEG']	= m_body['BODYPART_RIGHT_LOWER_LEG']:newShape()
    m_shapes['BODYPART_RIGHT_LOWER_LEG']:addCapsule(0.05,0.37)
    m_shapes['BODYPART_RIGHT_LOWER_LEG']:setMass(mass,inertia)
    m_shapes['BODYPART_RIGHT_LOWER_LEG']:addToBody();
    --m_body['BODYPART_RIGHT_LOWER_LEG']:addToWorld()

    --************************************
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,M_PI_2);pos_start:setOrigin(-0.35,1.45,0);pos_start:doOffset(offset_x,offset_y,offset_z)
    m_body['BODYPART_LEFT_UPPER_ARM']	  = bWorld:newBody (pos_start)
    --m_body['BODYPART_LEFT_UPPER_ARM']:setPosition(-0.35,1.45,0)
    m_shapes['BODYPART_LEFT_UPPER_ARM']	= m_body['BODYPART_LEFT_UPPER_ARM']:newShape()
    m_shapes['BODYPART_LEFT_UPPER_ARM']:addCapsule(0.05,0.33)
    m_shapes['BODYPART_LEFT_UPPER_ARM']:setMass(mass,inertia)
    m_shapes['BODYPART_LEFT_UPPER_ARM']:addToBody()
    --m_body['BODYPART_LEFT_UPPER_ARM']:addToWorld()


    --************************************
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,M_PI_2);pos_start:setOrigin(-0.7,1.45,0);pos_start:doOffset(offset_x,offset_y,offset_z)
    m_body['BODYPART_LEFT_LOWER_ARM']	  = bWorld:newBody (pos_start)
    --m_body['BODYPART_LEFT_LOWER_ARM']:setPosition(-0.7,1.45,0)

    m_shapes['BODYPART_LEFT_LOWER_ARM']	= m_body['BODYPART_LEFT_LOWER_ARM']:newShape()
    m_shapes['BODYPART_LEFT_LOWER_ARM']:addCapsule(0.04,0.25)
    m_shapes['BODYPART_LEFT_LOWER_ARM']:setMass(mass,inertia)
    m_shapes['BODYPART_LEFT_LOWER_ARM']:addToBody()
    --m_body['BODYPART_LEFT_LOWER_ARM']:addToWorld()


    --************************************
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,-M_PI_2);pos_start:setOrigin(0.35,1.45,0);pos_start:doOffset(offset_x,offset_y,offset_z)
    m_body['BODYPART_RIGHT_UPPER_ARM']	  = bWorld:newBody (pos_start)--:addToWorld()
    --m_body['BODYPART_RIGHT_UPPER_ARM']:setPosition(0.35,1.45,0)
    m_shapes['BODYPART_RIGHT_UPPER_ARM']	= m_body['BODYPART_RIGHT_UPPER_ARM']:newShape()
    m_shapes['BODYPART_RIGHT_UPPER_ARM']:addCapsule(0.05,0.33)
    m_shapes['BODYPART_RIGHT_UPPER_ARM']:setMass(mass,inertia)
    m_shapes['BODYPART_RIGHT_UPPER_ARM']:addToBody()
    --m_body['BODYPART_RIGHT_UPPER_ARM']:addToWorld()



    --************************************
    pos_start:setIdentity();pos_start:setEulerZYX(0,0,-M_PI_2);pos_start:setOrigin(0.7,1.45,0);pos_start:doOffset(offset_x,offset_y,offset_z)
    m_body['BODYPART_RIGHT_LOWER_ARM']	  = bWorld:newBody (pos_start)--:addToWorld()
    --m_body['BODYPART_RIGHT_LOWER_ARM']:setPosition(0.7,1.45,0)
    m_shapes['BODYPART_RIGHT_LOWER_ARM']  = m_body['BODYPART_RIGHT_LOWER_ARM']:newShape()
    m_shapes['BODYPART_RIGHT_LOWER_ARM']:addCapsule(0.04,0.25)
    m_shapes['BODYPART_RIGHT_LOWER_ARM']:setMass(mass,inertia)
    m_shapes['BODYPART_RIGHT_LOWER_ARM']:addToBody()
    --m_body['BODYPART_RIGHT_LOWER_ARM']:addToWorld()



    ----DAMPING
    for k,v in pairs(m_body) do
      --v:setDamping(0.05, 0.085)
      --v:setDeactivationTime(0.8);
      --v:setSleepingThresholds(0.2, 0.2);  
      --v:setKinematic()
    end

    local btTransformA = MOAIBulletTransform.new();btTransformA:setIdentity();
    local btTransformB = MOAIBulletTransform.new();btTransformA:setIdentity();
    local offsetX = 0
    local offsetY = 0
    local offsetZ = 0



    m_body['BODYPART_PELVIS']:addToWorld()
    m_body['BODYPART_SPINE']:addToWorld()
    m_body['BODYPART_HEAD']:addToWorld()

    m_body['BODYPART_LEFT_UPPER_LEG']:addToWorld()
    m_body['BODYPART_LEFT_LOWER_LEG']:addToWorld()

    m_body['BODYPART_RIGHT_UPPER_LEG']:addToWorld()
    m_body['BODYPART_RIGHT_LOWER_LEG']:addToWorld()


    m_body['BODYPART_LEFT_UPPER_ARM']:addToWorld();
    m_body['BODYPART_LEFT_LOWER_ARM']:addToWorld();

    m_body['BODYPART_RIGHT_UPPER_ARM']:addToWorld();
    m_body['BODYPART_RIGHT_LOWER_ARM']:addToWorld();



    --*******************************
    btTransformA:setIdentity();btTransformA:setEulerZYX(0,M_PI_2,0);btTransformA:setOrigin(0,0.15, 0);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,M_PI_2,0);btTransformB:setOrigin(0,-0.15,0);
    m_joints['JOINT_PELVIS_SPINE'] = bWorld:addJointHinge(m_body['BODYPART_PELVIS'],m_body['BODYPART_SPINE'],btTransformA,btTransformB)
    m_joints['JOINT_PELVIS_SPINE']:setLimit(-M_PI_4, M_PI_2);
    --*******************************
    btTransformA:setIdentity();btTransformA:setEulerZYX(0,0,M_PI_2);btTransformA:setOrigin(0,0.30,0);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,0,M_PI_2);btTransformB:setOrigin(0,-0.14,0.);
    m_joints['JOINT_SPINE_HEAD'] = bWorld:addJointCone(m_body['BODYPART_SPINE'],m_body['BODYPART_HEAD'],btTransformA,btTransformB)
    m_joints['JOINT_SPINE_HEAD']:setLimit(M_PI_4, M_PI_4, M_PI_2); --3 WTF
    --*******************************
    btTransformA:setIdentity();btTransformA:setEulerZYX(0,0,-M_PI_4*5);btTransformA:setOrigin(-0.18,-0.10,0.00);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,0,-M_PI_4*5);btTransformB:setOrigin(0.00,0.225,0.00);
    m_joints['JOINT_LEFT_HIP'] = bWorld:addJointCone(m_body['BODYPART_PELVIS'],m_body['BODYPART_LEFT_UPPER_LEG'],btTransformA,btTransformB)
    m_joints['JOINT_LEFT_HIP']:setLimit(M_PI_4, M_PI_4, 0); 
    --*******************************
    btTransformA:setIdentity();btTransformA:setEulerZYX(0,M_PI_2,0);btTransformA:setOrigin(0.00,-0.225,0.00);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,M_PI_2,0);btTransformB:setOrigin(0.00,0.185,0.00);
    m_joints['JOINT_LEFT_KNEE'] = bWorld:addJointHinge(m_body['BODYPART_LEFT_UPPER_LEG'],m_body['BODYPART_LEFT_LOWER_LEG'],btTransformA,btTransformB)
    m_joints['JOINT_LEFT_KNEE']:setLimit(0, M_PI_2); 
    --*******************************
    btTransformA:setIdentity();btTransformA:setEulerZYX(0,0,M_PI_4);btTransformA:setOrigin(0.18,-0.10,0.00);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,0,M_PI_4);btTransformB:setOrigin(0.00,0.225,0.00);
    m_joints['JOINT_RIGHT_HIP'] = bWorld:addJointCone(m_body['BODYPART_PELVIS'],m_body['BODYPART_RIGHT_UPPER_LEG'],btTransformA,btTransformB)
    m_joints['JOINT_RIGHT_HIP']:setLimit(M_PI_4, M_PI_4, 0); 
    ----*******************************
    btTransformA:setIdentity();btTransformA:setEulerZYX(0,M_PI_2,0);btTransformA:setOrigin(0.00,-0.225,0.00);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,M_PI_2,0);btTransformB:setOrigin(0.00,0.185,0.00);
    m_joints['JOINT_RIGHT_KNEE'] = bWorld:addJointHinge(m_body['BODYPART_RIGHT_UPPER_LEG'],m_body['BODYPART_RIGHT_LOWER_LEG'],btTransformA,btTransformB)
    m_joints['JOINT_RIGHT_KNEE']:setLimit(0, M_PI_2); 
    ----*******************************
    btTransformA:setIdentity();btTransformA:setEulerZYX(0,0,M_PI);btTransformA:setOrigin(-0.2,0.15,0.0);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,0,M_PI_2);btTransformB:setOrigin(0.0,-0.18,0.0);
    m_joints['JOINT_LEFT_SHOULDER'] = bWorld:addJointCone(m_body['BODYPART_SPINE'],m_body['BODYPART_LEFT_UPPER_ARM'],btTransformA,btTransformB)
    m_joints['JOINT_LEFT_SHOULDER']:setLimit(M_PI_2, M_PI_2,0);  
    --*******************************
    btTransformA:setIdentity();btTransformA:setEulerZYX(0,M_PI_2,0);btTransformA:setOrigin(-0.0,0.18,0.00);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,M_PI_2,0);btTransformB:setOrigin(0.00,-0.14,0.00);
    m_joints['JOINT_LEFT_ELBOW'] = bWorld:addJointHinge(m_body['BODYPART_LEFT_UPPER_ARM'],m_body['BODYPART_LEFT_LOWER_ARM'],btTransformA,btTransformB)
    m_joints['JOINT_LEFT_ELBOW']:setLimit(0, M_PI_2);
    --*******************************
    btTransformA:setIdentity();btTransformA:setEulerZYX(0,0,0);btTransformA:setOrigin(0.2,0.15,0.00);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,0,M_PI_2);btTransformB:setOrigin(0.00,-0.18,0.00);
    m_joints['JOINT_RIGHT_SHOULDER'] = bWorld:addJointCone(m_body['BODYPART_SPINE'],m_body['BODYPART_RIGHT_UPPER_ARM'],btTransformA,btTransformB)
    m_joints['JOINT_RIGHT_SHOULDER']:setLimit(M_PI_2, M_PI_2,0); 
    --*******************************
    btTransformA:setIdentity();btTransformA:setEulerZYX(0,M_PI_2,0);btTransformA:setOrigin(0,0.18,0);
    btTransformB:setIdentity();btTransformB:setEulerZYX(0,M_PI_2,0);btTransformB:setOrigin(0,-0.14,0);
    m_joints['JOINT_RIGHT_ELBOW'] = bWorld:addJointHinge(m_body['BODYPART_RIGHT_UPPER_ARM'],m_body['BODYPART_RIGHT_LOWER_ARM'],btTransformA,btTransformB)
    m_joints['JOINT_RIGHT_ELBOW']:setLimit(0, M_PI_2); 


end




--***************************************************************
local function share_shape()

  circle['shapeB'] = circle['body']:newShape()
  circle['shapeB']:addSphere(1,1)      
  circle['shapeB']:setPosition(2,2,0)
  circle['shapeB']:setRotation(0,0,0)
  circle['shapeB']:setMass(2,1)
  circle['shapeB']:addToBody(); 

  for i = 1, 1000 do  
      local newShape = MOAIBulletShape.new()
      newShape:addSphere(.1)  
      local newBody  = bWorld:newBody ()
      newBody:addToWorld()  
      newBody:addToBody(newShape)
  end

end



   
--     m_body['BODYPART_HEAD']:setIdName("head")    
--     m_body['BODYPART_HEAD']:setIdType("body_part")        
     
--    print('IDNAME',m_body['BODYPART_HEAD']['idName'])
--    print('IDTYPE',m_body['BODYPART_HEAD']['idType'])
    
    
       
--    print('----')
    
--    m_body['BODYPART_HEAD']['idName'] = 'WTF'
--    m_body['BODYPART_HEAD']['idType'] = 'WTF'
    
    
--    print('IDNAME',m_body['BODYPART_HEAD']['idName'])
--    print('IDTYPE',m_body['BODYPART_HEAD']['idType'])
     
    
    
    
    
--    print('----')
    
--    m_body['BODYPART_HEAD']:setIdName("ezra")    
--    m_body['BODYPART_HEAD']:setIdType("anderson") 
    
    
--    print('IDNAME',m_body['BODYPART_HEAD']['idName'])
--    print('IDTYPE',m_body['BODYPART_HEAD']['idType'])
    
    
--    print('----')
--    m_body['BODYPART_HEAD']:setIdName("head")    
--    m_body['BODYPART_HEAD']:setIdType("body_part")  
    
    
--    print('IDNAME',m_body['BODYPART_HEAD']['idName'])
--    print('IDTYPE',m_body['BODYPART_HEAD']['idType'])
    
    
--       print('--') 
--     m_body['BODYPART_HEAD']['ass'] ='great'    
--      m_body['BODYPART_HEAD']['as'] ='great'  
     
