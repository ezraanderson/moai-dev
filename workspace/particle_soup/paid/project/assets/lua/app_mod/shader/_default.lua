
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--*****************************************************************************
--DEFUALT

local default_vsh = [[


	uniform mat4 transform;
	
	attribute vec4 position;
	attribute vec4 color;
	attribute float size;
	
	varying vec4 colorVarying;
	

	void main() {
	 
	   colorVarying = color;
	   gl_PointSize = size;
	   gl_Position = vec4(position.xyz, 1) * transform;
	  
	}

]]

	


local default_fsh = [[	

uniform sampler2D sampler;
varying vec4 colorVarying;
uniform vec4      maskColor;
void main() {


    gl_FragColor =  texture2D(sampler, gl_PointCoord)*(colorVarying*maskColor);   
 
}

]]



mThread['rot'] 	    = nil
mTransform['rot']   = nil
mColor['color']     = nil
mShader['particle'] = nil


--COLOR
mColor['color'] = MOAIColor.new ()
mColor['color']:setColor ( 1, 1, 1, 1 )

	
--SHADER
mShader['particle'] = MOAIShader.new 	()
mShader['particle'] :reserveUniforms 	(2)
mShader['particle'] :declareUniform 	(1, 'transform', MOAIShader.UNIFORM_WORLD_VIEW_PROJ )


--COLOR
	mShader['particle'] :declareUniform ( 	2, 'maskColor', MOAIShader.UNIFORM_COLOR,1 )
	mShader['particle'] :setAttrLink ( 		2, mColor['color'], MOAIColor.COLOR_TRAIT )


mShader['particle']:setVertexAttribute ( 1, 'position' )
mShader['particle']:setVertexAttribute ( 2, 'color' )
mShader['particle']:setVertexAttribute ( 3, 'size' )
mShader['particle'] :load ( default_vsh, default_fsh )





--*****************************************************************
--*****************************************************************
function F._func_shader_clean()
print('*** SHADER CLEAN ***')
end


--*****************************************************************
--*****************************************************************
function F._func_shader_start()
print('*** SHADER START ***')
end

--*****************************************************************
--*****************************************************************
function F._func_return_shader()
print('*** RETURN SHADER ***')
	return mShader['particle'] 
end






