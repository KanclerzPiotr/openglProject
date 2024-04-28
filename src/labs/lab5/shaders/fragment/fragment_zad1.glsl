#version 330 core

out vec4 FragColor; 

in vec3 fragPos;
in vec2 fragTexCoords;
in vec3 fragNormal;

uniform vec3 cameraPos;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

struct LightParam
{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	vec3 Attenuation;
	vec3 Position;
};

struct MaterialParam
{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	float Shininess;
};

uniform int lightNumber;
layout (std140, binding = 1) uniform LightBlock
{
    LightParam light[10];
};

uniform int materialNumber;
layout (std140, binding = 2) uniform MaterialBlock
{
    MaterialParam material[10];
};

void main() {

    vec4 color = texture(texture1, fragTexCoords);

    vec3 normal = normalize(fragNormal);
    vec3 result = calculatePointLight(fragPos, normal, myLight, myMaterial);
    FragColor = color * vec4(result, 1.0);

}