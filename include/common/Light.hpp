#ifndef COMMON_LIGHT_HPP
#define COMMON_LIGHT_HPP

#include <glm/glm.hpp>



constexpr unsigned int DIRECTIONAL_LIGHTS_BINDING_POINT = 0;
constexpr unsigned int POINT_LIGHTS_BINDING_POINT = 1;
//vec4 instead of vec3 to ensure alignment
struct Light
{
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::vec4 attenuation;
	glm::vec4 position;
};

#endif // COMMON_LIGHT_HPP