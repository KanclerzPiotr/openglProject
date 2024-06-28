#ifndef COMMON_RANDOM_HPP
#define COMMON_RANDOM_HPP

#include <glm/glm.hpp>

namespace my_random {

void seed();
float get(float min, float max);
glm::vec2 getVec2(float min, float max);
glm::vec3 getVec3(float min, float max);

}; // namespace random


#endif // COMMON_RANDOM_HPP