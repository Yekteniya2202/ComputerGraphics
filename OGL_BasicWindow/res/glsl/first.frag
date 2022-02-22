#version 330
in vec3 fragColor;
in vec2 texCoords;

out vec4 outColor;
uniform float animation;
uniform sampler2D ourTexture;
void main() {
	outColor = texture(ourTexture, texCoords) * vec4(fragColor, 1.0f);
}