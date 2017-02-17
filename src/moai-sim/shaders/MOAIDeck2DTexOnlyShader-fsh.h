// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIDECK2DTEXONLYSHADER_FSH_H
#define	MOAIDECK2DTEXONLYSHADER_FSH_H

#define SHADER(str) #str
//#include <moai-sim/MOAIShader.h>

   //static cc8* _deck2DTexOnlyShaderFSH =  MOAI_SHADER (    
   static cc8* _deck2DTexOnlyShaderFSH =  SHADER (    


	varying MEDP vec2 uvVarying;
    //varying mediump vec2 uvVarying;
	
	uniform sampler2D sampler;

	void main () {
		gl_FragColor = texture2D ( sampler, uvVarying );
		//gl_FragColor = texture2D(sampler, uvVarying.rg + 0.5*(1.0 / 4096));
	}
);

#endif
