#version 420 core

out vec4 FragColor; 

in vec3 fragPos;
in vec2 fragTexCoords;
in vec3 fragNormal;

uniform vec3 cameraPos;
uniform bool blinn;
uniform bool lightning;
uniform int materialId;

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
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

layout (std140, binding = 0) uniform DirectLightBlock
{
    LightParam directLight;
};

uniform int pointLightNumber;
layout (std140, binding = 1) uniform PointLightBlock
{
    LightParam pointLight[10];
};

layout (std140, binding = 2) uniform MaterialBlock
{
    MaterialParam material[10];
};


vec3 calculatePointLight(vec3 fragPos, vec3 normal, LightParam light, MaterialParam material)
{
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 viewDir = normalize(cameraPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.attenuation.x + light.attenuation.y * distance + light.attenuation.z * (distance * distance));

	vec3 ambient = light.ambient * material.ambient;
	vec3 diffuse = light.diffuse * material.diffuse * max(dot(normal, lightDir), 0.0);

	vec3 specular;

	if (!blinn)
		specular = light.specular * material.specular * pow(max(dot(normal, normalize(lightDir + viewDir)), 0.0), material.shininess);
	else
		specular = light.specular * material.specular * pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return ambient + diffuse + specular;
}

vec3 calculateDirectionalLight(vec3 normal, LightParam light, MaterialParam material)
{
	vec3 lightDir = normalize(-light.position);
	vec3 viewDir = normalize(cameraPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	vec3 ambient = light.ambient * material.ambient;
	vec3 diffuse = light.diffuse * material.diffuse * max(dot(normal, lightDir), 0.0);
	vec3 specular = light.specular * material.specular * pow(max(dot(normal, normalize(lightDir + viewDir)), 0.0), material.shininess);

	return ambient + diffuse + specular;
}

void main() {

    vec4 color = texture(texture1, fragTexCoords);

	vec3 normal = normalize(fragNormal);

	color = color * vec4(calculateDirectionalLight(normal, directLight, material[materialId]), 1.0);
    
	if (lightning) {

		vec3 result = vec3(0.0);

		for(int i = 0; i < pointLightNumber; i++)
			result += calculatePointLight(fragPos, normal, pointLight[i], material[materialId]);
	
		FragColor = color * vec4(result, 1.0);
	}
	// else
	// {
	// 	FragColor = color * vec4(calculateDirectionalLight(normal, directLight, material[materialId]), 1.0);
	// }
}