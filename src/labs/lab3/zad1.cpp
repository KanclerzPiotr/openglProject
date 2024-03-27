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

void animateCube(Model& model, float deltaTime) {
    float y = 0.01f * glm::sin(deltaTime);
    model.translate({0.0f, y, 0.0f});
}

void animateCone(Model& model, float deltaTime, float distance) {
    float speed = 3.0f;
    float ratio = 360.0f/distance;
    model.rotateZ(deltaTime * ratio * speed);
    model.translate({0.0f, deltaTime * speed, 0.0f});

}

void animateMonkey(Model& model, float deltaTime) {
    float value = glm::cos(deltaTime) * 0.3f;
    model.rotateX(value);
}


int main(void)
{
    Camera camera{{0.0f, 8.0f, 20.0f}, {0.0f, 1.0f, 0.0f}, -90.0f, -20.0f};

    Window window(screenWidth, screenHeight, "OpenGL");
    window.enable(GL_PROGRAM_POINT_SIZE);
    window.enable(GL_DEPTH_TEST);
    window.setScrollCallback(makeScrollCallback(camera));
    window.setKeyCallback(makeKeyCallback(camera));
    window.setCursorPosCallback(makeCursorPosCallback(camera));
    window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    GLSLProgram objects{"vertex_zad1.glsl", "fragment_zad1_1.glsl"};
    GLSLProgram terrain{"vertex_zad1.glsl", "fragment_zad1_2.glsl"};
    

    Model cubeModel{"cube.obj"};
    Model coneModel{"cone.obj"};
    Model monkeyModel{"monkey.obj"};
    Model terrainModel{"terrain.obj"};
    
    cubeModel.translate({0.0f, 3.0f, 0.0f});
    constexpr float radius = 5.0f;
    constexpr float circle = 2.0f * radius * glm::pi<float>();
    coneModel.rotateX(-90.0f);
    coneModel.translate({5.0f, 0.0f, 5.0f});
    monkeyModel.translate({-5.0f, 3.0f, 0.0f});
    monkeyModel.rotateY(90.0f);
    monkeyModel.rotateX(30.0f);
    terrainModel.translate({0.0f, -1.0f, 0.0f});

    while(!window.shouldClose())
    {
        float time = glfwGetTime();
        float deltaTime = getDeltaTime();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        animateCube(cubeModel, time);
        animateCone(coneModel, deltaTime, circle);
        animateMonkey(monkeyModel, time);

        objects.use();       
        objects.setUniform("projection", camera.getProjectionMatrix(screenWidth, screenHeight));
        objects.setUniform("view", camera.getViewMatrix());

        objects.setUniform("model", cubeModel.getModelMatrix());
        cubeModel.draw();
        objects.setUniform("model", coneModel.getModelMatrix());
        coneModel.draw();
        objects.setUniform("model", monkeyModel.getModelMatrix());
        monkeyModel.draw();

        terrain.use();
        terrain.setUniform("projection", camera.getProjectionMatrix(screenWidth, screenHeight));
        terrain.setUniform("view", camera.getViewMatrix());
        terrain.setUniform("model", terrainModel.getModelMatrix());
        terrainModel.draw();

        window.pollEvents();
        window.swapBuffers();
    }
    return 0;
}
