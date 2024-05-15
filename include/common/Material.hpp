#ifndef COMMON_MATERIAL_HPP
#define COMMON_MATERIAL_HPP

#include <glm/glm.hpp>

constexpr unsigned int MATERIAL_BINDING_POINT = 2;
// vec4 instead of vec3 to ensure alignment
struct Material
{
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	float shininess;
};

#endif // COMMON_MATERIAL_HPP