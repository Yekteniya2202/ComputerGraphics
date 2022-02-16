#version 330 core
in vec3 aPos;
in vec3 inColor;
out vec3 fragColor;
uniform mat4 pvm;
void main()
{ 
	
	gl_Position = pvm * vec4(aPos, 1.0f);
	fragColor = inColor; 
};