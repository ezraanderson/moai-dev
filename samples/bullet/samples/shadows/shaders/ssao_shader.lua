print('SHADER : POINT_LIGHT_SSAO')
file = assert ( io.open ( 'shaders//ssao.vert', 'rb' ))
vsh = file:read ( '*all' )
file:close ()

file = assert ( io.open ( 'shaders//ssao.frag', 'rb' ))
fsh = file:read ( '*all' )
file:close ()


shader_ssao = MOAIShader.new ()
shader_ssao:reserveUniforms ( 1 )
shader_ssao:declareUniform ( 1, 'u_farDistance', MOAIShader.UNIFORM_COLOR )

--shader_ssao:setVertexAttribute ( 1, 'v_normal' )
--shader_ssao:setVertexAttribute ( 2, 'v_texCoord' )
--shader_ssao:setVertexAttribute ( 3, 'v_depth' )

shader_default:setVertexAttribute ( 1, 'v_vertex' )
shader_default:setVertexAttribute ( 2, 'uv' )
shader_default:setVertexAttribute ( 3, 'color' )
shader_default:setVertexAttribute ( 4, 'normal' )


shader_ssao:load ( vsh, fsh )




return shader_ssao