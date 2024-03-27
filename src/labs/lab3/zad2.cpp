#include "common/Window.hpp"
#include "common/GLSLProgram.hpp"
#include "common/Model.hpp"
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
auto makeScrollCallback(Camera& camera)
{
    return [&camera](GLFWwindow* window, double xoffset, double yoffset) {
        camera.processMouseScroll(yoffset);
    };
}

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

auto makeCursorPosCallback(Camera& camera)
{
    return [&camera](GLFWwindow* window, double xpos, double ypos) {
        static double lastX = xpos, lastY = ypos;
        static bool firstMouse = true;
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        double xoffset = xpos - lastX;
        double yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        camera.processMouseMovement(xoffset, yoffset);
    };
}

float getDeltaTime() {
    static float lastFrame = 0.0f;
    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    return deltaTime;
}

void animateMonkey(Model& monkey, float deltaTime)
{
    monkey.rotateY(deltaTime * 100.0f);
}

int main(void)
{
    Camera camera{{0.0f, 0.0f, 20.0f}, {0.0f, 1.0f, 0.0f}, -90.0f, 0.0f};

    Window window(screenWidth, screenHeight, "OpenGL");
    window.enable(GL_PROGRAM_POINT_SIZE);
    window.enable(GL_DEPTH_TEST);
    window.setScrollCallback(makeScrollCallback(camera));
    window.setKeyCallback(makeKeyCallback(camera));
    window.setCursorPosCallback(makeCursorPosCallback(camera));
    window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    GLSLProgram program{"vertex_zad2.glsl", "fragment_zad2.glsl"};
    
    Model cone{"cone.obj"};
    Model monkeyModel{"monkey.obj"};

    while(!window.shouldClose())
    {
        float deltaTime = getDeltaTime();
        float time = glfwGetTime();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        animateMonkey(monkeyModel, deltaTime);

        program.use();
        program.setUniform("view", camera.getViewMatrix());
        program.setUniform("projection", camera.getProjectionMatrix(screenWidth, screenHeight));

        program.setUniform("model", monkeyModel.getModelMatrix());
        monkeyModel.draw();
        
        time *= 100.0f;
        for(int i = 0; i < 4; i++)
        {
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f * i + time), glm::vec3(0.0f, 0.0f, 1.0f));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 5.0f, 0.0f));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 2.0f, 1.0f));
            program.setUniform("model", modelMatrix);
            cone.draw();
        }

        window.pollEvents();
        window.swapBuffers();
    }
    return 0;
}
