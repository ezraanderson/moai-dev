----------------------------------------------------------------
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
----------------------------------------------------------------

MOAISim.openWindow ( "test", 600, 600 )
MOAIGfxDevice.getFrameBuffer ():setClearDepth ( true )
MOAIGfxDevice.getFrameBuffer ():setClearColor ( .1,.1,.1,.1 )

viewport = MOAIViewport.new ()
viewport:setSize ( 600, 600 )
viewport:setScale ( 600, 600 )

layer = MOAILayer.new ()
layer:setViewport ( viewport )
layer:setSortMode ( MOAILayer.SORT_NONE ) -- don't need layer sort
MOAISim.pushRenderPass ( layer )

local mesh = dofile('exported-file.lua')
mesh:setTexture ( "face.png" )

local m_props= MOAIProp.new ();  
m_props:setDeck ( mesh )
m_props:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
m_props:setCullMode ( MOAIProp.CULL_BACK )
m_props:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
m_props:setDepthMask(true)
m_props:setLoc(0,0) 
--RENDER 
layer:insertProp ( m_props ) 












----SPLIT
--function split(str, delim)
--    local result,pat,lastPos = {},"(.-)" .. delim .. "()",1
--    for part, pos in string.gfind(str, pat) do
--        table.insert(result, part); lastPos = pos
--    end
--    table.insert(result, string.sub(str, lastPos))
--    return result
--end


----LOAD
--local buffer = MOAIDataBuffer.new ()
--      buffer:load ( 'face.obj' )
      
----DATA TABLE      
--local obj_data = split(buffer:getString(),'\n')


----I COULD JUST COPY THE LINE DATA INTO NEW TABLE


--local data_verts = {}
--local data_indices  = {}
--local data_uv     = {}
--local data_normal = {}

--for i = 1, #obj_data do
  
--  local check_line    = obj_data[i]
--  local start_letter  = string.sub(check_line,1,2)
--  local current_line  = ''
--  local line_data     = ''

----********************************************************************************************** 
----List of vertices (v) with XYZ coordinates. 
--if      start_letter == 'v '    then      
      
--      current_line = string.sub(check_line,3,string.len(check_line)) --SHIFT RIGHT 3 SPACES
--      line_data    = split(current_line,' ') 
        
--      data_verts[#data_verts+1] = {   
--                                    tonumber(line_data[1]),
--                                    tonumber(line_data[2]),
--                                    tonumber(line_data[3])
--                                  }                           
      
----**********************************************************************************************    
----List of texture coordinates (vt) with UV coordinates.         
--elseif  start_letter == 'vt' then  
      
--      current_line = string.sub(check_line,4,string.len(check_line)) --SHIFT RIGHT 3 SPACES
--      line_data    = split(current_line,' ')       
      
--      data_uv[#data_uv+1] = {
--                              tonumber(line_data[1]),
--                              tonumber(line_data[2]),                         
--                              }  
      
----**********************************************************************************************       
----List of normals (vn) with XYZ coordinates.     
--elseif  start_letter == 'vn' then   
  
--      current_line = string.sub(check_line,4,string.len(check_line)) --SHIFT RIGHT 3 SPACES
--      line_data    = split(current_line,' ')   
  
----********************************************************************************************** 
----List of faces (f) with v, vt, and vn data (three points ABC per face).    
--elseif  start_letter == 'f ' then  
  
--      current_line = string.sub(check_line,3,string.len(check_line)) --SHIFT RIGHT 3 SPACES
--      line_data    = split(current_line,' ')
    
--        for j = 1,3 do
--          local faces = split(line_data[j],'/') 
          
--          if faces[1] ~= nil then
--              data_indices[#data_indices+1] = tonumber(faces[1])
--          end

--          if faces[2] ~= nil then
--              --
--          end    

--          if faces[3] ~= nil then
--              --
--          end   
--        end
    
       
--end  


--end  

----*****************************************************
--local reserveVerts    = #data_verts 
--local reserveIndices  = #data_indices 


--print('--------------------')
--print('reserveVerts',reserveVerts,reserveIndices)
--print('--------------------')
  
----**********************************************************************
----VERTEX_FORMATE
--	local vertexFormat = MOAIVertexFormat.new ()
--	vertexFormat:declareCoord ( 1, MOAIVertexFormat.GL_FLOAT, 3 )
--	vertexFormat:declareUV (    2, MOAIVertexFormat.GL_FLOAT, 2 )
--	vertexFormat:declareColor ( 3, MOAIVertexFormat.GL_UNSIGNED_BYTE )
  
  
----**********************************************************************
----INDEX_BUFFER

--local new_verts = {}



--	local ibo = MOAIIndexBuffer.new ()
--	ibo:reserve ( reserveIndices )
--  for i = 1, #data_indices do  

--      local indices = data_indices[i]
--      local verts   = data_verts[indices]
     
--      new_verts[#new_verts+1] = {verts[1],verts[2],verts[3]}
      
      
--      -- print(i,data_indices[i])
--      -- print(verts[1],verts[2],verts[3])
--      -- ibo:setIndex ( i, tonumber(data_indices[i])  )
--  end



--print('NEW SIZE',#new_verts)




----**********************************************************************
----VERTEX_BUFFER
--	local vbo = MOAIVertexBuffer.new ()
--	vbo:setFormat ( vertexFormat )
--	vbo:reserveVerts ( #new_verts)

--    for i = 1, #new_verts do  
          
          
--        --*********************
--        --VERT   
--        if new_verts[i] ~= nil then    
--              print('VERTS',i,new_verts[i][1], new_verts[i][2], new_verts[i][3])
--              vbo:writeFloat ( (new_verts[i][1]), (new_verts[i][2]), (new_verts[i][3]) )
--        else
--              vbo:writeFloat ( 0, 0, 0 )
--        end
--       --*********************          
--       --UV 
--        if data_uv[i] ~= nil then
--                print('','UV',i,data_uv[i][1], data_uv[i][2])
--                vbo:writeFloat ( data_uv[i][1], data_uv[i][2])
--        else
--                vbo:writeFloat ( 0, 0 )
--        end        
--        --*********************          
--        --UV  
--         --vbo:writeFloat ( 0, 0 )
--         vbo:writeColor32 ( 1, 1, 1 )  
       
--    end     
    
--  --BLEES
--  vbo:bless()
  
  



----**********************************************************************
----MESH
--	local mesh = MOAIMesh.new ()
--	mesh:setTexture ( "face.png" )
--	mesh:setVertexBuffer ( vbo )
--	--mesh:setIndexBuffer ( ibo )
--	mesh:setPrimType ( MOAIMesh.GL_TRIANGLES )  
--  --mesh:setHigh(36)
----**********************************************************************
----PROP
--  local m_props= MOAIProp.new ();  
--  m_props:setDeck ( mesh )
--  m_props:setShader ( MOAIShaderMgr.getShader ( MOAIShaderMgr.MESH_SHADER ))
--  m_props:setCullMode ( MOAIProp.CULL_BACK )
--  m_props:setDepthTest(MOAIProp.DEPTH_TEST_LESS_EQUAL)
--  m_props:setDepthMask(true)
--  m_props:setLoc(0,0) 
--  --RENDER 
--  layer:insertProp ( m_props ) 








--*****************************************************************************************

camera = MOAICamera.new ()
camera:setLoc ( 0, 0, camera:getFocalLength ( 10 ))
layer:setCamera ( camera )

local pausetime = 0
local t = MOAICoroutine.new()
t:run( function()
          while true do
			 pausetime = pausetime + .01
			 
		
			 m_props:setRot( 360*pausetime, 180*pausetime, 90*pausetime )
			 
             coroutine.yield()
          end          
       end)
