print('SHADER : G_BUFFER')
local file = assert ( io.open ( 'shaders//gbuffer.vert', 'rb' ))
vsh = file:read ( '*all' )
file:close ()

local file = assert ( io.open ( 'shaders//gbuffer.frag', 'rb' ))
fsh = file:read ( '*all' )
file:close ()


shader_gbuffer = MOAIShader.new ()
shader_gbuffer:reserveUniforms ( 1 )
shader_gbuffer:declareUniform ( 1, 'u_farDistance', MOAIShader.UNIFORM_COLOR )

shader_gbuffer:setVertexAttribute ( 1, 'v_cords' )
shader_gbuffer:setVertexAttribute ( 2, 'v_uv' )
shader_gbuffer:setVertexAttribute ( 3, 'v_color' )
shader_gbuffer:setVertexAttribute ( 4, 'v_normal' )
shader_gbuffer:setVertexAttribute ( 5, 'v_depth' )



--vertexFormat:declareCoord(1, MOAIVertexFormat.GL_FLOAT, 3)
--vertexFormat:declareUV(2, MOAIVertexFormat.GL_FLOAT, 2)
--vertexFormat:declareColor(3, MOAIVertexFormat.GL_UNSIGNED_BYTE)
--vertexFormat:declareNormal (4, MOAIVertexFormat.GL_FLOAT, 3)
--vertexFormat:declareAttribute  (5, MOAIVertexFormat.GL_FLOAT, 1)





--shader_default:setVertexAttribute ( 1, 'v_vertex' )
--shader_default:setVertexAttribute ( 2, 'uv' )
--shader_default:setVertexAttribute ( 3, 'color' )


shader_gbuffer:load ( vsh, fsh )


return shader_gbuffer