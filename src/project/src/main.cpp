#include "HeightMap.hpp"

#include <fmt/core.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include <common/Camera.hpp>
#include <common/Window.hpp>
#include <common/GLSLProgram.hpp>
#include <common/Texture.hpp>
#include <common/Model.hpp>
#include "common/CommonSetups.hpp"

constexpr int screenWidth = 800;
constexpr int screenHeight = 600;


auto makeKeyCallback(Camera& camera)
{    
    return [&camera](GLFWwindow* window, int key, int scancode, int action, int mods) {

        float deltaTime = 0.1f;
        
        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            switch (key) {
                case GLFW_KEY_ESCAPE:
                    glfwSetWindowShouldClose(window, true);
                    break;
                case GLFW_KEY_LEFT_SHIFT:
                    camera.processKeyboard(CameraMovement::UP, deltaTime);
                    break;
                case GLFW_KEY_SPACE:
                    camera.processKeyboard(CameraMovement::DOWN, deltaTime);
                    break;
                case GLFW_KEY_W:
                    camera.processKeyboard(CameraMovement::FORWARD, deltaTime);
                    break;
                case GLFW_KEY_S:
                    camera.processKeyboard(CameraMovement::BACKWARD, deltaTime);
                    break;
                case GLFW_KEY_A:
                    camera.processKeyboard(CameraMovement::LEFT, deltaTime);
                    break;
                case GLFW_KEY_D:
                    camera.processKeyboard(CameraMovement::RIGHT, deltaTime);
                    break;
            }   
        }
    };
}

int main()
{
    Camera camera{{0.0f, 8.0f, 20.0f}, {0.0f, 1.0f, 0.0f}, -90.0f, -20.0f};


    Window window(screenWidth, screenHeight, "OpenGL");
    window.enable(GL_DEPTH_TEST);
    window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    window.enable(GL_PRIMITIVE_RESTART);
    window.setPrimitiveRestartIndex(0xFFFFFFFF);
    window.setKeyCallback(makeKeyCallback(camera));
    window.setScrollCallback(makeScrollCallback(camera));
    window.setCursorPosCallback(makeCursorPosCallback(camera));


    GLSLProgram terrain_program{"terrain_vertex.glsl", "terrain_fragment.glsl"};

    std::vector<Model> terrain_models;
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            terrain_models.emplace_back(Model{generateHeightMap(256, 256, i, j), {"grass.jpg", "sand.jpg", "water.jpg"}});
            terrain_models[i].scaleUp({10.0f, 1.0f, 10.0f});
            terrain_models[i].translate({i * 10.0f, 0.0f, j * 10.0f});
        }
    }


    while(!window.shouldClose())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        terrain_program.use();
        terrain_program.setUniform("view", camera.getViewMatrix());
        terrain_program.setUniform("projection", camera.getProjectionMatrix(screenWidth, screenHeight));

        for(auto& terrain_model : terrain_models)
        {
            terrain_program.setUniform("normalMatrix", terrain_model.getNormalMatrix());
            terrain_program.setUniform("model", terrain_model.getModelMatrix());
            terrain_model.setTextureUniforms(terrain_program);
            terrain_model.draw();
        }
        window.pollEvents();
        window.swapBuffers();
    }


    return 0;
}