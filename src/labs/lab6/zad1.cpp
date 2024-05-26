#include "common/Window.hpp"
#include "common/GLSLProgram.hpp"
#include "common/Model.hpp"
#include "common/Camera.hpp"
#include "common/UniformBuffer.hpp"
#include "common/Light.hpp"
#include "common/Material.hpp"
#include "common/CommonSetups.hpp"
#include "common/Skybox.hpp"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <random>
#include <iostream>
#include <numeric>
#include <fmt/core.h>


constexpr int screenWidth = 800;
constexpr int screenHeight = 600;

template <typename T>
auto makeKeyCallback(Camera& camera, T& swapFunction)
{
    
    return [&camera, &swapFunction](GLFWwindow* window, int key, int scancode, int action, int mods) {

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
                case GLFW_KEY_R:
                    swapFunction();
                    break;
            }   
        }
    };
}


int main(void)
{
    Camera camera{{0.0f, 8.0f, 20.0f}, {0.0f, 1.0f, 0.0f}, -90.0f, -20.0f};

    Window window(screenWidth, screenHeight, "OpenGL");

    window.enable(GL_DEPTH_TEST);
    window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    GLSLProgram reflectionProgram{"vertex_zad2.glsl", "fragment_zad2_reflection.glsl"};
    GLSLProgram refractionProgram{"vertex_zad2.glsl", "fragment_zad2_refraction.glsl"};

    GLSLProgram* currentProgram = &reflectionProgram;

    auto swapPointers = [&reflectionProgram, &refractionProgram, &currentProgram]() {
        if (currentProgram == &reflectionProgram) {
            currentProgram = &refractionProgram;
        } else {
            currentProgram = &reflectionProgram;
        }
    };

    window.setScrollCallback(makeScrollCallback(camera));
    window.setKeyCallback(makeKeyCallback(camera, swapPointers));
    window.setCursorPosCallback(makeCursorPosCallback(camera));


    Skybox skybox{"vertex_skybox.glsl", "fragment_skybox.glsl", {
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg"
    }};

    Model humming{"koliber.obj", {"koliber.jpg"}};

    

    while(!window.shouldClose())
    {
        window.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        window.clearColor(0.1f, 0.1f, 0.1f, 1.0f);

        currentProgram->use();
        setupCameraUniforms(*currentProgram, camera, screenWidth, screenHeight);

        currentProgram->setUniform("model", humming.getModelMatrix());
        currentProgram->setUniform("normalMatrix", humming.getNormalMatrix());
        currentProgram->setUniform("cameraPos", camera.getPosition());
        humming.setTextureUniforms(*currentProgram);
        skybox.bindTexture(4);
        currentProgram->setUniform("skybox", 4);
        humming.draw();

        skybox.draw(camera.getViewMatrix(), camera.getProjectionMatrix(screenWidth, screenHeight));

        window.pollEvents();
        window.swapBuffers();
    }


    return 0;
}
