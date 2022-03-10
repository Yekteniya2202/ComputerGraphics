#version 330

in vec3 vertColor;
in vec2 texCoords;
in vec3 vertNormal;
in vec3 FragPos;

out vec4 outColor;

uniform sampler2D ourTexture;
uniform bool wireFrameMode;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 ambientColor;

void main() 
{
	vec3 ambient = ambientColor*0.2f;

    vec3 norm = normalize(vertNormal);
    vec3 lightDir = normalize(FragPos - lightPos);

    float diff_koef = max(dot(norm, -lightDir), 0.0);
    vec3 diffuse = diff_koef * lightColor;

    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 viewDir = normalize(FragPos-viewPos);

    float specularStrength = 2.0f;
    float spec_koef = pow(max(dot(viewDir, reflectDir), 0.0f), 1000);
    vec3 specular = specularStrength * spec_koef * lightColor;

	if(wireFrameMode)
		outColor = vec4(vertColor, 1.0f);
	else
		outColor = texture(ourTexture, texCoords) * vec4(specular + diffuse + ambient, 1.0);
}