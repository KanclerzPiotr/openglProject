#include "common/Window.hpp"
#include "common/GLSLProgram.hpp"
#include "common/Mesh.hpp"
#include <iostream>

int main(void)
{
    Window window(800, 600, "OpenGL");

    Mesh<ColorVertex> mesh = {
        {
            //First Triangle
            {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
            {{0.0f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},

            //Second Triangle
            {{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
            {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
            {{0.0f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}
        },
        {0, 1, 2, 3, 4, 5},
        TRIANGLES
    };

    GLSLProgram program{"vertex_zad1.glsl", "fragment_zad1.glsl"};
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
