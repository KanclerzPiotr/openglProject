#include "common/Window.hpp"
#include "common/GLSLProgram.hpp"
#include "common/Mesh.hpp"
#include <glm/glm.hpp>
#include <random>
#include <iostream>
#include <numeric>
#include <cmath>


std::vector<SimpleVertex> generateVertices(int arms) {
    std::vector<SimpleVertex> vertices{};
    vertices.push_back({0, 0, 0});

    float angleIncrement = 2 * M_PI / (arms * 2);
    for(int i = 0; i < arms*2; i++) {
        float radius = (i % 2 == 0) ? .9f : .75f;
        float angle = i * angleIncrement;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        vertices.push_back({x, y, 0.0f});
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

int main(void)
{
    Window window(800, 600, "OpenGL");

    int n_edges = 10;
    auto verticies = generateVertices(n_edges);
    Mesh mesh = {
        std::move(verticies),
        generateIndicesCenter(2*n_edges),
        TRIANGLE_FAN
    };

    GLSLProgram program{"vertex_zad4.glsl", "fragment_zad4.glsl"};
    program.use();

    glLineWidth(8);
    glClearColor(0.7f, .7f, .7f, 1.0f);

    while(!window.shouldClose())
    {   
        
        glClear(GL_COLOR_BUFFER_BIT);
        program.setUniform("line", false);
        mesh.draw();
        program.setUniform("line", true);
        mesh.drawArrays(1, 2*n_edges, LINE_STRIP);


        window.pollEvents();
        window.swapBuffers();
    }
    return 0;
}
