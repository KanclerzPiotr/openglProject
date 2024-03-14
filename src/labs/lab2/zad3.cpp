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

auto makeKeyCallback(GLSLProgram& program)
{
    return [&program](GLFWwindow* window, int key, int scancode, int action, int mods) {
        static glm::vec2 translation = {0.0f, 0.0f};
        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            switch (key) {
                case GLFW_KEY_W:
                    translation += glm::vec2(0.0f, 0.1f);
                    program.setUniform("translation", translation);
                    break;
                case GLFW_KEY_A:
                    translation += glm::vec2(-0.1f, 0.0f);
                    program.setUniform("translation", translation);
                    break;
                case GLFW_KEY_S:
                    translation += glm::vec2(0.0f, -0.1f);
                    program.setUniform("translation", translation);
                    break;
                case GLFW_KEY_D:
                    translation += glm::vec2(0.1f, 0.0f);
                    program.setUniform("translation", translation);
                    break;
                default:
                    break;
            }
        }   
    };
}

int main(void)
{
    Window window(800, 600, "OpenGL");


    Mesh mesh = {
        vertices,
        generateIndices(vertices.size()),
        TRIANGLES
    };

    GLSLProgram program{"vertex_zad3.glsl", "fragment_zad3.glsl"};
    window.setKeyCallback(makeKeyCallback(program));
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
