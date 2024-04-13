#include "common/Window.hpp"
#include "common/GLSLProgram.hpp"
#include "common/Mesh.hpp"
#include "common/Texture.hpp"
#include "common/Camera.hpp"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/constants.hpp>
#include <random>
#include <iostream>
#include <numeric>


constexpr int screenWidth = 800;
constexpr int screenHeight = 600;

int main(void)
{
    Window window(screenWidth, screenHeight, "OpenGL");
    window.enable(GL_DEPTH_TEST);
    window.enable(GL_BLEND);
    window.blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLSLProgram program{"vertex_zad1.glsl", "fragment_zad1.glsl"};
    
    Mesh<Vertex> rectangle{
        {
            Vertex{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
            Vertex{{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
            Vertex{{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
            Vertex{{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}
        },
        {0, 1, 2, 0, 2, 3},
        TRIANGLES
    };
    Texture uv{"uvtemplate.jpg"};
    Texture fire{"fire.jpg"};
    Texture troll{"troll.png"};

    program.use();
    program.setUniform("texture1", 0);
    program.setUniform("texture2", 1);
    program.setUniform("texture3", 2);

    uv.bind(0);
    fire.bind(1);
    troll.bind(2);

    while(!window.shouldClose())
    {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        rectangle.draw();

        window.pollEvents();
        window.swapBuffers();
    }
    return 0;
}
