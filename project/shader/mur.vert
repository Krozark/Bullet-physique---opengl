varying vec3 Light, Reflet, Normal,V;

void main() {
	gl_TexCoord[0] = gl_MultiTexCoord0;
	Normal = gl_NormalMatrix*gl_Normal;
	Light = vec3(gl_LightSource[0].position-(gl_ModelViewMatrix*gl_Vertex));
	Reflet = reflect(Light,Normal);
	V = vec3(0.0,0.0,1.0);
	// Set the position of the current vertex
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

