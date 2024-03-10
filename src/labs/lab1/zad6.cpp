#include "common/Window.hpp"
#include "common/GLSLProgram.hpp"
#include "common/Mesh.hpp"
#include <glm/glm.hpp>
#include <random>
#include <iostream>
#include <numeric>
#include <cmath>


std::vector<ColorVertex> generateVertices(int edges) {
    std::vector<ColorVertex> vertices{};
    vertices.push_back({{0, 0, 0}, {1, 0, 0}});

    float angleIncrement = 2 * M_PI / edges;
    for(int i = 0; i < edges; i++) {
        float angle = i * angleIncrement;
        vertices.push_back({{0.5*cos(angle), 0.5*sin(angle), 0}, {0, 0, 0}});
    }

    return vertices;
}


std::vector<int> generateIndicesCenter(int edges)
{
    std::vector<int> indices(edges + 1);
    std::iota(indices.begin(), indices.end(), 0);
    indices.push_back(1);
    return indices;
}

std::vector<int> generateIndicesEdges(int edges)
{
    std::vector<int> indices(edges);
    std::iota(indices.begin(), indices.end(), 1);
    indices.push_back(1);
    return indices;
}

int main(void)
{
    Window window(800, 600, "OpenGL");

    int n_edges = 8;
    auto verticies = generateVertices(n_edges);
    Mesh center = {
        verticies,
        generateIndicesCenter(n_edges),
        TRIANGLE_FAN
    };

    for(auto& vertex : verticies) {
        vertex.color = {1, 0, 0};
    }

    Mesh edges = {
        verticies,
        generateIndicesEdges(n_edges),
        LINE_STRIP
    };

    GLSLProgram program{"vertex_zad1.glsl", "fragment_zad1.glsl"};
    program.use();

    while(!window.shouldClose())
    {   
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        center.draw();
        edges.draw();

        window.pollEvents();
        window.swapBuffers();
    }
    return 0;
}
