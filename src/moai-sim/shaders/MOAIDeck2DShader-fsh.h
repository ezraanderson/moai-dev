// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.

//precision highp float;
//precision highp int;

// http://getmoai.com

#ifndef	MOAIDECK2DSHADER_FSH_H
#define	MOAIDECK2DSHADER_FSH_H

#define SHADER(str) #str

static cc8* _deck2DShaderFSH = SHADER (

	precision highp float;

	//varying LOWP vec4 colorVarying;	
	//varying MEDP vec2 uvVarying;

	varying highp  vec4 colorVarying;	
	varying highp  vec2 uvVarying;

	uniform sampler2D sampler;

	void main () {
		gl_FragColor = texture2D ( sampler, uvVarying ) * colorVarying;

		//gl_FragColor = texture2D(sampler, uvVarying.rg + 0.5*(1.0 / 4096));




	}
);

#endif
