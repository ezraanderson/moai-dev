print('SHADER : POINT_LIGHT_PASS')
local file = assert ( io.open ( 'shaders//pointLightPass.vert', mode ))
vsh = file:read ( '*all' )
file:close ()

local file = assert ( io.open ( 'shaders//pointLightPass.frag', mode ))
fsh = file:read ( '*all' )
file:close ()


shader_light = MOAIShader.new ()

shader_light:reserveUniforms ( 13 )

shader_light:declareUniformInt    ( 1, 'u_numLights',         MOAIShader.UNIFORM_INT,1 )
shader_light:declareUniformFloat  ( 2, 'u_farDistance',       MOAIShader.UNIFORM_FLOAT,1 )

shader_light:declareUniformFloat  ( 3,  'u_lightIntensity',    MOAIShader.UNIFORM_FLOAT,1 )
shader_light:declareUniformFloat  ( 4,  'u_lightRadius',       MOAIShader.UNIFORM_FLOAT,1 )



shader_light:declareUniform       ( 5, 'u_lightAmbient',      MOAIShader.UNIFORM_COLOR )
shader_light:declareUniform       ( 6, 'u_lightDiffuse',      MOAIShader.UNIFORM_COLOR )
shader_light:declareUniform       ( 7, 'u_lightSpecular',     MOAIShader.UNIFORM_COLOR )


--NEED TO EDIT SHADER
shader_light:declareUniform       ( 8,  'u_lightPosition_x',     MOAIShader.UNIFORM_FLOAT,1 )
shader_light:declareUniform       ( 9,  'u_lightPosition_y',     MOAIShader.UNIFORM_FLOAT,1 )
shader_light:declareUniform       ( 10, 'u_lightPosition_z',     MOAIShader.UNIFORM_FLOAT,1 )

--NEED TO EDIT SHADER
shader_light:declareUniform       ( 11, 'u_lightAttenuation_x',  MOAIShader.UNIFORM_FLOAT,1 )
shader_light:declareUniform       ( 12, 'u_lightAttenuation_y',  MOAIShader.UNIFORM_FLOAT,1 )
shader_light:declareUniform       ( 13, 'u_lightAttenuation_z',  MOAIShader.UNIFORM_FLOAT,1 )



shader_light:setVertexAttribute ( 1, 'v_vertex' ) --IS POSTION
shader_light:setVertexAttribute ( 2, 'uv' )
shader_light:setVertexAttribute ( 3, 'color' )

shader_light:load ( vsh, fsh )

--print('SETTING DUMMY')
--local gfxQuad_dummy = MOAIGfxQuad2D.new ()
--gfxQuad_dummy:setShader(shader);


return shader_light