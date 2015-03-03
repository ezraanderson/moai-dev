// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com
 
uniform mat4  transform;
uniform float uThickness;


attribute vec4  position;
attribute float size;
attribute vec2  uv;
attribute vec4  color;   
                 
varying vec4 colorVarying;
varying vec2 uvVarying;     



void main () {   
       
    colorVarying   = color; 
    uvVarying      = uv; 
         
    gl_PointSize   = 1;      

    gl_Position    =  transform * position; 
    gl_Position    =  transform * vec4(position.xyz, 1.0);;  
    
          
//gl_PointSize   = 2;   
//gl_FrontColor  = gl_Color;      
//uvVarying      = gl_TextureMatrix[0] * gl_MultiTexCoord0;            
//uvVarying      = uv;      	  
//colorVarying   = color;     

  
       
       
}
