print('SHADER : TEST')


local file = assert ( io.open ( 'shaders//default.vsh', mode ))
vsh = file:read ( '*all' )
file:close ()

local file = assert ( io.open ( 'shaders//default.fsh', mode ))
fsh = file:read ( '*all' )
file:close ()

--color = MOAIColor.new ()
--color:setColor ( 0, 0, 0, 0 )
--color:moveColor ( 1, 0, 0, 0, 1.5 )

shader_default = MOAIShader.new ()
shader_default:reserveUniforms ( 1 )
shader_default:declareUniform ( 1, 'maskColor', MOAIShader.UNIFORM_COLOR )

--shader:setAttrLink ( 1, color, MOAIColor.COLOR_TRAIT )

shader_default:setVertexAttribute ( 1, 'v_vertex' )
shader_default:setVertexAttribute ( 2, 'uv' )
shader_default:setVertexAttribute ( 3, 'color' )
shader_default:load ( vsh, fsh )
  
return shader_default  