#include "common/Window.hpp"
#include "common/GLSLProgram.hpp"
#include "common/Model.hpp"
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
    Camera camera{{0.0f, 0.0f, 5.0f}};
    Window window(screenWidth, screenHeight, "OpenGL");
    window.enable(GL_DEPTH_TEST);

    GLSLProgram program{"vertex_zad2.glsl", "fragment_zad2.glsl"};
    
    Model cube("cube.obj", {"paper.png"});
    cube.rotateY(30.0f);
    cube.rotateX(-45.0f);

    while(!window.shouldClose())
    {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program.use();
        program.setUniform("view", camera.getViewMatrix());
        program.setUniform("projection", camera.getProjectionMatrix(screenWidth, screenHeight));
        program.setUniform("model", cube.getModelMatrix());
        cube.setTextureUniforms(program);
        cube.draw();

        window.pollEvents();
        window.swapBuffers();
    }
    return 0;
}
