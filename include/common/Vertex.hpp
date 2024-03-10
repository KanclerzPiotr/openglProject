#ifndef COMMON_VERTEX_HPP
#define COMMON_VERTEX_HPP

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct SimpleVertex
{
    SimpleVertex(float x, float y, float z) : position(x, y, z) {}
    SimpleVertex(glm::vec3 pos) : position(pos) {}
    glm::vec3 position;

};

struct ColorVertex
{
    glm::vec3 position;
    glm::vec3 color;
};

#endif // COMMON_VERTEX_HPP
