#version 430
in vec4 vPosition; 
in vec4 vColor; 
out vec4 color; 
uniform float Theta;
uniform float scale;

void main() { 
	//  shape must not touch the window edges, so declare new position
	vec4 temp = vec4(vPosition.x *0.4, vPosition.y *0.4, 0.0, 1.0);
	
	// Scale matrix
	mat4 sc = mat4(scale, 0.0, 0.0, 0.0, 0.0, scale, 0.0, 0.0, 0.0, 0.0, scale, 0.0, 0.0, 0.0, 0.0, 1.0);
	
	// Compute the sines and cosines of theta
	float x = radians( Theta ); 
	float c = cos(x); 
	float s = sin(x); 

	// Rotation matrix for Z axis
	mat4 rz = mat4( c, -s, 0.0, 0.0, s, c, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 ); 

	color = vColor; 
	gl_Position = rz * sc * temp;
} 