#version 330
in vec3 fragColor;
out vec4 outColor;
uniform float animation;
void main() {
	outColor = vec4(fragColor * animation, 1.0f);
}