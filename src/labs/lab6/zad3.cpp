#include "common/Window.hpp"
#include "common/GLSLProgram.hpp"
#include "common/Model.hpp"
#include "common/Camera.hpp"
#include "common/UniformBuffer.hpp"
#include "common/Light.hpp"
#include "common/Material.hpp"
#include "common/CommonSetups.hpp"
#include "common/Skybox.hpp"
#include "common/InstancedModel.hpp"
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

std::vector<glm::mat4> generateModelMatrices(int size)
{
    std::vector<glm::mat4> modelMatrices(size);
    std::default_random_engine generator;
    std::uniform_real_distribution<float> translationDistribution(-50.0f, 50.0f);
    std::uniform_real_distribution<float> rotationDistribution(0.0f, 360.0f);
    std::uniform_real_distribution<float> scaleDistribution(0.5f, 1.5f);
    for(auto& modelMatrix : modelMatrices)
    {
        modelMatrix = glm::mat4(1.0f); 
        modelMatrix = glm::translate(glm::mat4(1.0f), {translationDistribution(generator), translationDistribution(generator), translationDistribution(generator)});
        // modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationDistribution(generator)), {1.0f, 0.0f, 0.0f});
        // modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationDistribution(generator)), {0.0f, 1.0f, 0.0f});
        // modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationDistribution(generator)), {0.0f, 0.0f, 1.0f});
        // float scale = scaleDistribution(generator);
        // modelMatrix = glm::scale(modelMatrix, {scale, scale, scale});
    }
    return modelMatrices;
}

int main(void)
{
    Camera camera{{0.0f, 8.0f, 20.0f}, {0.0f, 1.0f, 0.0f}, -90.0f, -20.0f};

    Window window(screenWidth, screenHeight, "OpenGL");

    window.enable(GL_DEPTH_TEST);
    window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    window.setScrollCallback(makeScrollCallback(camera));
    window.setKeyCallback(makeKeyCallback(camera));
    window.setCursorPosCallback(makeCursorPosCallback(camera));

    GLSLProgram program{"vertex_zad3.glsl", "fragment_zad3.glsl"};

    Skybox skybox{"vertex_skybox.glsl", "fragment_skybox.glsl", {
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg"
    }};

    Model humming{"koliber.obj", {"koliber.jpg"}};

    humming.bind();
    auto modelMatricies = generateModelMatrices(100);

    // GLuint vInstances;
    // glGenBuffers(1, &vInstances);
    // glBindBuffer(GL_ARRAY_BUFFER, vInstances);
    // glBufferData(GL_ARRAY_BUFFER, modelMatricies.size() * sizeof(glm::mat4), modelMatricies.data(), GL_STATIC_DRAW);



    InstancedModel instancedHumming{std::move(humming), modelMatricies};

    while(!window.shouldClose())
    {
        window.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        window.clearColor(0.1f, 0.1f, 0.1f, 1.0f);

        program.use();
        setupCameraUniforms(program, camera, screenWidth, screenHeight);
        // program.setUniform("model", humming.getModelMatrix());
        instancedHumming.setTextureUniforms(program);
        skybox.bindTexture(4);
        program.setUniform("skybox", 4);
        // humming.draw();
        instancedHumming.draw();



        skybox.draw(camera.getViewMatrix(), camera.getProjectionMatrix(screenWidth, screenHeight));

        window.pollEvents();
        window.swapBuffers();
    }


    return 0;
}
