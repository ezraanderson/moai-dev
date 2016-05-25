
uniform sampler2D sampler;
varying vec4 colorVarying;
uniform vec4      maskColor;
void main() {
    gl_FragColor =  texture2D(sampler, gl_PointCoord)*colorVarying;   
 
}