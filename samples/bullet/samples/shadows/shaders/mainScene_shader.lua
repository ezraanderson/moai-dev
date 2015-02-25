print('SHADER : MAIN_SCENE')

local file = assert ( io.open ( 'shaders//mainScene.vert', 'rb' ))
vsh = file:read ( '*all' )
file:close ()

local file = assert ( io.open ( 'shaders//mainScene.frag', 'rb' ))
fsh = file:read ( '*all' )
file:close ()


shader_main = MOAIShader.new ()
shader_main:reserveUniforms ( 1 )
shader_main:declareUniform ( 1, 'u_farDistance', MOAIShader.UNIFORM_COLOR )

shader_main:setVertexAttribute ( 1, 'v_normal' )
shader_main:setVertexAttribute ( 2, 'v_texCoord' )
shader_main:setVertexAttribute ( 3, 'v_depth' )
shader_main:load ( vsh, fsh )


return shader_main