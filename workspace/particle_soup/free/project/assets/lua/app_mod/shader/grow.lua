
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
	
	uniform float scale;

	void main() {
	 
	   colorVarying = color;
	   gl_PointSize = size*scale;
	   gl_Position  = vec4(position.xyz, 1) * transform;
	  
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

--SCALE
mTransform['scale'] = MOAITransform.new()
mTransform['scale']:setScl ( 1,1,1 )


	
--SHADER
mShader['particle'] = MOAIShader.new 	()
mShader['particle'] :reserveUniforms 	(3)

--TRANSDORM
	mShader['particle'] :declareUniform 	(1, 'transform', MOAIShader.UNIFORM_WORLD_VIEW_PROJ )


--COLOR
	mShader['particle'] :declareUniform ( 	2, 'maskColor', MOAIShader.UNIFORM_COLOR,1 )
	mShader['particle'] :setAttrLink ( 		2, mColor['color'], MOAIColor.COLOR_TRAIT )



--SCALE
	mShader['particle']:declareUniformFloat ( 	3, 'scale', MOAIShader.UNIFORM_FLOAT,1.0 )
	mShader['particle']:setAttrLink(3, mTransform['scale'], MOAITransform.ATTR_Z_SCL)




mShader['particle']:setVertexAttribute ( 1, 'position' )
mShader['particle']:setVertexAttribute ( 2, 'color' )
mShader['particle']:setVertexAttribute ( 3, 'size' )
mShader['particle'] :load ( default_vsh, default_fsh )






--****************************************************************************

local scale_thread = MOAIThread.new ()
local scale_action = nil

local function wait ( action,idName )

	print('idName',idName)

	scale_action = action

	while action:isBusy () do 
		coroutine:yield () 
	end
end



--****************************************************************************
local function threadFunc_scale ()

print('**********  THREAD RUN')

		while true do

			print('**********  do')
				wait(mTransform['scale']:seekScl(2,2,2,5, MOAIEaseType.LINEAR),'scale_up')
				wait(mTransform['scale']:seekScl(1,1,1,5, MOAIEaseType.LINEAR),'scale_down')			
	
				coroutine.yield()
		end
end


--*****************************************************************
--*****************************************************************
function F._func_shader_clean()

	print('*** SHADER SCALE CLEAN ***')
	scale_thread:stop ( threadFunc_scale)	
	scale_action:stop()
	mTransform['scale']:setScl ( 1,1,1 )
end


--*****************************************************************
--*****************************************************************
function F._func_shader_start()
	print('*** SHADER SCALE START ***')
	scale_thread:run ( threadFunc_scale)	
end

--*****************************************************************
--*****************************************************************
function F._func_return_shader()
	print('*** RETURN SHADER ***')
	return mShader['particle'] 
end





