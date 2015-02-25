

uniform sampler2D sampler;

varying vec3  v_normal;
varying vec2  v_cords;
varying float v_depth;

void main(void)
{
  vec3 diffuse = texture2D(sampler, v_cords.st).rgb;
  gl_FragData[0] = vec4(diffuse, 1.0); // albedo
  gl_FragData[1] = vec4(normalize(v_normal), v_depth); // normals + depth
}