#ifndef HEIGHTMAP_HPP
#define HEIGHTMAP_HPP

#include "PerlinNoise.hpp"

#include <common/Mesh.hpp>

#include <vector>
#include <tuple>

auto generateHeightMap(int width, int height, float xOffset, float zOffset)
{
    fmt::print("Generating height map\n");
    const siv::PerlinNoise::seed_type seed = 123456u;
    const siv::PerlinNoise perlin{ seed };
    const int octaves = 8;
    const float frequency = 4.0f;

    std::vector<Vertex> verticies(width * height);
    std::vector<int> indices{};
    std::vector<float> heightMap(width * height);

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float x = j / (float)(width - 1);
            float z = i / (float)(height - 1);
            float y = perlin.octave2D_01( (x + xOffset) * frequency, (z + zOffset) * frequency, octaves);
            y = (y < 0.2f) ? 0.0f : y;
            verticies[i * width + j].position = glm::vec3(x, y, z);
            verticies[i * width + j].normal = glm::vec3(0.0f, 0.0f, 0.0f);
            verticies[i * width + j].texCoords = glm::vec2(x, z);
            heightMap[i * width + j] = y;
        }
        
    }

    for(int j = 0; j < height - 1; j++)
    {
        for(int i = 0; i < width - 1; i++)
        {
            indices.push_back(j * width + i);
            indices.push_back((j + 1) * width + i);
        }
        indices.push_back(0xFFFFFFFF);
    }

    for(int i = 2; i < indices.size(); i++)
    {
        if(indices[i] == 0xFFFFFFFF)
        {
            i+=2;
            continue;
        }
        glm::vec3 v0 = verticies[indices[i - 2]].position;
        glm::vec3 v1 = verticies[indices[i - 1]].position;
        glm::vec3 v2 = verticies[indices[i]].position;

        glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

        verticies[indices[i - 2]].normal += normal;
        verticies[indices[i - 1]].normal += normal;
        verticies[indices[i]].normal += normal;
    }

    for(int i = 0; i < verticies.size(); i++)
    {
        verticies[i].normal = glm::normalize(verticies[i].normal);
    }

    return Mesh<Vertex>{std::move(verticies), std::move(indices), PrimitiveType::TRIANGLE_STRIP};
}

#endif