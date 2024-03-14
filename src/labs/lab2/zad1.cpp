#include "common/Window.hpp"
#include "common/GLSLProgram.hpp"
#include "common/Mesh.hpp"
#include <glm/glm.hpp>
#include <random>
#include <iostream>
#include <numeric>


float getRandom(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

glm::vec2 getRandomVec2(float min, float max)
{
    return {getRandom(min, max), getRandom(min, max)};
}

std::vector<SimpleVertex> generateVertices(int N)
{
    std::vector<SimpleVertex> vertices;
    for (int i = 0; i < N; i++)
    {
        glm::vec2 center = getRandomVec2(-1, 1);
        vertices.push_back({{center + getRandomVec2(-0.1, 0.1), 0.0f}});
        vertices.push_back({{center + getRandomVec2(-0.1, 0.1), 0.0f}});
        vertices.push_back({{center + getRandomVec2(-0.1, 0.1), 0.0f}});
    }
    return vertices;
}

std::vector<int> generateIndices(int N)
{
    std::vector<int> indices(3*N);
    std::iota(indices.begin(), indices.end(), 0);
    return indices;
}

int main(void)
{
    constexpr int N = 100;
    Window window(800, 600, "OpenGL");
    window.enable(GL_PROGRAM_POINT_SIZE);

    Mesh mesh = {
        generateVertices(N),
        generateIndices(N),
        POINTS
    };

    GLSLProgram program{"vertex_zad1.glsl", "fragment_zad1.glsl"};
    program.use();
    program.setUniform("resolution", glm::vec2(800, 600));
    program.setUniform("N", (float)N);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while(!window.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        mesh.drawArrays();

        window.pollEvents();
        window.swapBuffers();
    }
    return 0;
}
