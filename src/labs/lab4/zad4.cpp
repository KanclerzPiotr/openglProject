#include "common/Window.hpp"
#include "common/GLSLProgram.hpp"
#include "common/Mesh.hpp"
#include "common/Texture.hpp"
#include "common/Camera.hpp"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>
#include <numeric>


constexpr int screenWidth = 800;
constexpr int screenHeight = 600;

int main(void)
{
    Camera camera{{0.0f, 0.0f, 5.0f}};
    Window window(screenWidth, screenHeight, "OpenGL");
    window.enable(GL_DEPTH_TEST);
    window.enable(GL_BLEND);
    window.blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLSLProgram program{"vertex_zad4.glsl", "fragment_zad4.glsl"};

    Texture texture{"background.png"};

    Mesh<Vertex> cube {
        {
            Vertex{{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {0.75f, 0.0f}},
            Vertex{{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {0.5f, 0.0f}},
            Vertex{{1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {0.5f, 1.0f}},
            Vertex{{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {0.75f, 1.0f}},
            Vertex{{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
            Vertex{{1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.25f, 0.0f}},
            Vertex{{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.25f, 1.0f}},
            Vertex{{-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
            Vertex{{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
            Vertex{{-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}}
        },
        {0, 1, 2, 0, 2, 3, //back
         4, 5, 6, 4, 6, 7, //front
         0, 1, 5, 0, 5, 4, //bottom
         3, 2, 6, 3, 6, 7, //top
         1, 2, 6, 1, 6, 5, //right
         0, 3, 9, 0, 9, 8}, //left
        TRIANGLES
    };


    program.use();
    program.setUniform("view", camera.getViewMatrix());
    program.setUniform("projection", camera.getProjectionMatrix(screenWidth, screenHeight));
    program.setUniform("texture1", 0);
    texture.bind(0);

    glm::mat4 modelMatrix = glm::rotate(glm::mat4(1.0), glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    program.setUniform("model", modelMatrix);


    while(!window.shouldClose())
    {
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program.setUniform("time", static_cast<float>(glfwGetTime()) * 0.3f);
        
        cube.draw();

        window.pollEvents();
        window.swapBuffers();
    }
    return 0;
}
