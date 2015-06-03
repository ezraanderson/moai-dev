// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.

//precision highp float;
//precision highp int;

// http://getmoai.com

#ifndef	MOAIDISCARDSHADER_FSH_H
#define	MOAIDISCARDSHADER_FSH_H

#define SHADER(str) #str

static cc8* _discardShaderFSH = SHADER (

	//precision highp float;
	varying highp vec4 colorVarying;
	varying highp vec2 uvVarying;
	uniform sampler2D sampler;

	void main () {
		gl_FragColor = texture2D ( sampler, uvVarying ) * colorVarying;


//**************************************************************************
//vec4 color  = texture2D ( sampler, uvVarying ) * colorVarying;
//  if (color.rgb > vec3(0.0,0.0,0.0))
//      discard;    
//   gl_FragColor = color;
//




//EZRA
	//vec4 val = texture2D ( sampler, uvVarying ) * colorVarying;
	//if (val.a > 0.0) {
	//	gl_FragColor = val;
	//} else {
	//	discard;
	//}


	//if (val.a > 0.8) {
	//	gl_FragColor = val;
	//} else {
	//	discard;
	//}


	}
);

#endif
