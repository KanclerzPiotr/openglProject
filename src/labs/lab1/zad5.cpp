#include "common/Window.hpp"
#include "common/GLSLProgram.hpp"
#include "common/Mesh.hpp"
#include <glm/glm.hpp>
#include <random>
#include <iostream>
#include <numeric>


std::vector<SimpleVertex> vertices = {
    {-0.290909, 0.540000, 0.000000}, 
    {-0.650909, 0.000000, 0.0f},
    {-0.290909, -0.540000, 0.0f},

    {0.249091, -0.540000, 0.0f},
    {0.309091, -0.600000,0.0f},
    {0.309091, 0.600000, 0.0f}, 
    
    {0.249091, -0.540000, 0.0f},
    {0.309091, 0.600000, 0.0f},
    {0.249091, 0.540000, 0.0f}, 
    
    {-0.350909, -0.600000, 0.0f},
    {-0.290909, -0.600000, 0.0f},
    {-0.290909, -0.540000,0.0f},    
    
    {-0.290909, -0.540000, 0.0f},
    {0.249091, -0.540000, 0.0f},
    {0.249091, 0.540000, 0.0f}, 
    
    {-0.290909, 0.540000, 0.0f},
    {-0.290909, 0.600000, 0.0f},
    {-0.350909, 0.600000, 0.0f},    
    
    {-0.290909, -0.540000, 0.0f},
    { 0.249091, 0.540000, 0.0f},
    {-0.290909, 0.540000, 0.0f},    
    
    {-0.650909, 0.000000, 0.0f},
    {-0.350909, -0.600000, 0.0f},
    {-0.290909, -0.540000, 0.0f},   
    
    {-0.290909, 0.540000, 0.0f},
    {-0.350909, 0.600000, 0.0f},
    {-0.650909, 0.000000, 0.0f}
};

std::vector<int> generateIndices(int N)
{
    std::vector<int> indices(3*N);
    std::iota(indices.begin(), indices.end(), 0);
    return indices;
}

int main(void)
{
    Window window(800, 600, "OpenGL");

    Mesh mesh = {
        vertices,
        generateIndices(vertices.size()),
        TRIANGLES
    };

    GLSLProgram program{"vertex_zad5.glsl", "fragment_zad5.glsl"};
    program.use();

    while(!window.shouldClose())
    {   
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        mesh.draw();

        window.pollEvents();
        window.swapBuffers();
    }
    return 0;
}
