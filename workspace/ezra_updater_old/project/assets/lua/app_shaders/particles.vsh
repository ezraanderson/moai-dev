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