#version 330 core
in vec3 aPos;
in vec3 inColor;
out vec3 fragColor;
uniform vec3 uniformPos;
void main()
{ 
	vec3 newPos = aPos/2 + uniformPos/2;
	vec3 dir = (newPos - vec3(0,0,0))/distance(vec3(0,0,0), newPos);
	gl_Position = vec4(newPos, 1.0f); 
	fragColor = inColor; 
};