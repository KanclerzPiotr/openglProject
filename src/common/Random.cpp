#include <common/Random.hpp>

#include <random>
#include <chrono>

namespace random {

static std::mt19937 gen;

void seed()
{
    gen.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

float get(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

glm::vec2 getVec2(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return {dist(gen), dist(gen)};
}

glm::vec3 getVec3(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return {dist(gen), dist(gen), dist(gen)};
}

}; // namespace random
