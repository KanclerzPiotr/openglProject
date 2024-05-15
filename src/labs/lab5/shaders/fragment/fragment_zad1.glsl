#version 420 core

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
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 attenuation;
	vec3 position;
};

struct MaterialParam
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform int lightNumber;
layout (std140, binding = 1) uniform LightBlock
{
    LightParam light[10];
};

// uniform int materialNumber;
// layout (std140) uniform MaterialBlock
// {
//     MaterialParam material[10];
// };

layout (std140) uniform TestBlock
{
	vec3 test;
};


// vec3 calculatePointLight(vec3 fragPos, vec3 normal, LightParam light, MaterialParam material)
// {
// 	vec3 lightDir = normalize(light.position - fragPos);
// 	vec3 viewDir = normalize(cameraPos - fragPos);
// 	vec3 reflectDir = reflect(-lightDir, normal);

// 	float distance = length(light.position - fragPos);
// 	float attenuation = 1.0 / (light.attenuation.x + light.attenuation.y * distance + light.attenuation.z * (distance * distance));

// 	vec3 ambient = light.ambient * material.ambient;
// 	vec3 diffuse = light.diffuse * material.diffuse * max(dot(normal, lightDir), 0.0);
// 	vec3 specular = light.specular * material.specular * pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

// 	ambient *= attenuation;
// 	diffuse *= attenuation;
// 	specular *= attenuation;

// 	return ambient + diffuse + specular;
// }

vec3 calculatePointLight(vec3 fragPos, vec3 normal, LightParam light)
{
	vec3 lightDir = normalize(light.position.xyz - fragPos);
	vec3 viewDir = normalize(cameraPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float distance = length(light.position.xyz - fragPos);
	float attenuation = 1.0 / (light.attenuation.x + light.attenuation.y * distance + light.attenuation.z * (distance * distance));

	vec3 ambient = light.ambient.xyz;
	vec3 diffuse = light.diffuse.xyz * max(dot(normal, lightDir), 0.0);
	vec3 specular = light.specular.xyz * pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return ambient + diffuse + specular;
}

void main() {

    vec4 color = texture(texture1, fragTexCoords);

    vec3 normal = normalize(fragNormal);
	// vec3 result = vec3(1.0);
    vec3 result = calculatePointLight(fragPos, normal, light[0]);
	FragColor = color * vec4(result, 1.0);

}