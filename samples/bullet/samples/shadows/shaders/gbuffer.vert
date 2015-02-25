

uniform float u_farDistance;

attribute vec3 v_cords;
attribute vec3 v_uv;
attribute vec3 v_color;
attribute vec3 v_normal;
attribute float v_depth;   


void main (void)
{
  vec4 viewSpaceVertex = gl_ModelViewMatrix * gl_Vertex;
  v_normal             = gl_NormalMatrix * gl_Normal;
  v_cords              = gl_MultiTexCoord0.st;
  //v_depth              = -viewSpaceVertex.z / u_farDistance;
	
  gl_Position          = gl_ModelViewProjectionMatrix * gl_Vertex;
}