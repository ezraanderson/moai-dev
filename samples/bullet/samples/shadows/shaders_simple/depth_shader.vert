varying vec4 vpos;
void main()
{
	vpos = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_Position = ftransform();
} 
