print('SHADER : POINT_LIGHT_STENCIL')
file = assert ( io.open ( 'shaders//pointLightStencil.vert', 'rb' ))
vsh = file:read ( '*all' )
file:close ()

file = assert ( io.open ( 'shaders//pointLightStencil.frag', 'rb' ))
fsh = file:read ( '*all' )
file:close ()


local shader = MOAIShader.new ()
shader:reserveUniforms ( 1 )
shader:declareUniform ( 1, 'u_farDistance', MOAIShader.UNIFORM_COLOR )

shader:setVertexAttribute ( 1, 'v_normal' )
shader:setVertexAttribute ( 2, 'v_texCoord' )
shader:setVertexAttribute ( 3, 'v_depth' )
shader:load ( vsh, fsh )


return shader