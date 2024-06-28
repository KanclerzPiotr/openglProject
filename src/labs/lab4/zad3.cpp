#include "common/Window.hpp"
#include "common/GLSLProgram.hpp"
#include "common/Mesh.hpp"
#include "common/Texture.hpp"
#include "common/Camera.hpp"
#include "common/Random.hpp"

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
    Camera camera{{0.0f, 0.0f, 3.0f}};
    Window window(screenWidth, screenHeight, "OpenGL");
    window.enable(GL_DEPTH_TEST);
    window.enable(GL_BLEND);
    window.blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLSLProgram program{"vertex_zad2.glsl", "fragment_zad3.glsl"};
    
    Texture texture{"flower32bit.png"};

    Mesh<Vertex> rectangles {
        {
            Vertex{{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
            Vertex{{1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
            Vertex{{1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
            Vertex{{-1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
            Vertex{{0.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            Vertex{{0.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            Vertex{{0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
            Vertex{{0.0f, 1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}
        },
        {0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7},
        TRIANGLES
    };

    my_random::seed();
    std::vector<float> scales(10);
    std::vector<glm::vec3> positions(10);
    std::generate(scales.begin(), scales.end(), []() { return my_random::get(0.2f, 1.0f); });
    std::generate(positions.begin(), positions.end(), []() { return my_random::getVec3(-1.0f, 1.0f); });

    program.use();
    program.setUniform("view", camera.getViewMatrix());
    program.setUniform("projection", camera.getProjectionMatrix(screenWidth, screenHeight));
    program.setUniform("texture1", 0);
    texture.bind(0);

    while(!window.shouldClose())
    {

        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        for(int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, positions[i]);
            model = glm::scale(model, glm::vec3(scales[i]));
            program.setUniform("model", model);
            
            rectangles.draw();
        }
        window.pollEvents();
        window.swapBuffers();
    }
    return 0;
}
