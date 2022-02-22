#version 330 core
in vec3 aPos;
in vec3 inColor;
in vec2 inTexCoords;

out vec3 fragColor;
out vec2 texCoords;

uniform mat4 pvm;
void main()
{ 
	
	gl_Position = pvm * vec4(aPos, 1.0f);
	fragColor = inColor; 
	texCoords = inTexCoords;
};