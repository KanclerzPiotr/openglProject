#include "common/Window.hpp"
#include "common/GLSLProgram.hpp"
#include "common/Model.hpp"
#include "common/Camera.hpp"
#include "common/UniformBuffer.hpp"
#include "common/Light.hpp"
#include "common/Material.hpp"
#include "common/CommonSetups.hpp"
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

void setupModels(Model& cube, Model& cone, Model& monkey, Model& terrain){
    cube.translate({0.0f, 3.0f, 0.0f});
    cone.rotateX(-90.0f);
    cone.translate({5.0f, 0.0f, 5.0f});
    monkey.translate({-5.0f, 3.0f, 0.0f});
    monkey.rotateY(90.0f);
    monkey.rotateX(30.0f);
    terrain.translate({0.0f, -1.0f, 0.0f});
}

glm::vec4 animateLight(float time) {
    float x = 15.0f * glm::sin(time);
    float z = 15.0f * glm::cos(time);
    return {x, 3.0f, z, 1.0f};
}

auto makeKeyCallback(Camera& camera, GLSLProgram& program)
{
    
    return [&camera, &program](GLFWwindow* window, int key, int scancode, int action, int mods) {

        float deltaTime = 0.1f;
        static bool blin = false;
        static bool lightning = true;
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
                    fmt::println("click D");
                    camera.processKeyboard(CameraMovement::RIGHT, deltaTime);
                    break;
                case GLFW_KEY_B:
                    fmt::println("setting blinn to: {}", blin);
                    program.use();
                    program.setUniform("blinn", blin);
                    blin = !blin;
                    break;
                case GLFW_KEY_L:
                    fmt::println("setting lightning to: {}", lightning);
                    program.use();
                    program.setUniform("lightning", lightning);
                    lightning = !lightning;
                    break;
                
            }   
        }
    };
}

int main(void)
{
    Camera camera{{0.0f, 8.0f, 20.0f}, {0.0f, 1.0f, 0.0f}, -90.0f, -20.0f};

    Window window(screenWidth, screenHeight, "OpenGL");
    GLSLProgram program{"vertex_zad1.glsl", "fragment_zad1.glsl"};
    GLSLProgram lightningsProgram{"vertex_zad1_2.glsl", "fragment_zad1_2.glsl"};

    window.enable(GL_DEPTH_TEST);
    window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    window.setScrollCallback(makeScrollCallback(camera));
    window.setKeyCallback(makeKeyCallback(camera, program));
    window.setCursorPosCallback(makeCursorPosCallback(camera));

    Light movingLight{
            {0.2f, 0.2f, 0.2f, 1.0f},
            {1.0f, 1.0f, 1.0f, 1.0f},
            {0.0f, 1.0f, 0.0f, 1.0f},
            {1.0f, 0.0f, 0.01f, 1.0f},
            {0.0f, 5.0f, 0.0f, 1.0f},
    };

    UniformBuffer<Light> lightBuffer{{
        {
            {0.2f, 0.2f, 0.2f, 1.0f},
            {0.5f, 0.5f, 0.5f, 1.0f},
            {1.0f, 0.0f, 0.0f, 1.0f},
            {1.0f, 0.0f, 0.01f, 1.0f},
            {5.0f, 5.0f, 5.0f, 1.0f},
        },
        {
            {0.2f, 0.2f, 0.2f, 1.0f},
            {0.5f, 0.5f, 0.5f, 1.0f},
            {0.0f, 1.0f, 0.0f, 1.0f},
            {1.0f, 0.0f, 0.01f, 1.0f},
            {-5.0f, 5.0f, 5.0f, 1.0f},
        },
        movingLight
    }};
    lightBuffer.bind(POINT_LIGHTS_BINDING_POINT);

    UniformBuffer<Light> directionalLightBuffer{{
        {
            {0.2f, 0.2f, 0.2f, 1.0f},
            {0.5f, 0.5f, 0.5f, 1.0f},
            {0.0f, 0.0f, 1.0f, 1.0f},
            {1.0f, 0.0f, 0.01f, 1.0f},
            {-0.2f, -1.0f, -0.3f, 1.0f},
        }
    }};
    directionalLightBuffer.bind(DIRECTIONAL_LIGHTS_BINDING_POINT);

    UniformBuffer<Material> materialBuffer{{
        // black rubber
        {
            { 0.02f, 0.02f, 0.02f, 1.0f },
            { 0.01f, 0.01f, 0.01f, 1.0f},
            {0.4f, 0.4f, 0.4f, 1.0f },
            10.0f
        },
        // brass 
        {
            { 0.329412f, 0.223529f, 0.027451f, 1.0f },
            { 0.780392f, 0.568627f, 0.113725f, 1.0f },
            { 0.992157f, 0.941176f, 0.807843f, 1.0f },
            27.8974f
        }
    }};
    materialBuffer.bind(MATERIAL_BINDING_POINT);

    Model cubeModel{"cube.obj", {"troll.png"}};
    Model coneModel{"cone.obj", {"fire.jpg"}};
    Model monkeyModel{"monkey.obj", {"metal.jpg"}};
    Model terrainModel{"terrain.obj", {"grass.jpg"}};

    Model lightCube{"cube.obj"};
    
    setupModels(cubeModel, coneModel, monkeyModel, terrainModel);
    constexpr float radius = 5.0f;
    constexpr float circle = 2.0f * radius * glm::pi<float>();

    program.use(); 
    program.setUniform("pointLightNumber", lightBuffer.getSize());
    program.setUniform("blinn", false);
    program.setUniform("lightning", true);



    while(!window.shouldClose())
    {
        program.use();
        float time = glfwGetTime();
        float deltaTime = getDeltaTime();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        animateCube(cubeModel, time);
        animateCone(coneModel, deltaTime, circle);
        animateMonkey(monkeyModel, time);

        auto lightPosition = animateLight(time);
        movingLight.position = lightPosition;
        lightBuffer.updateData(2, movingLight);


        setupCameraUniforms(program, camera, screenWidth, screenHeight);

        program.setUniform("materialId", 0);
        drawModel(program, cubeModel);
        drawModel(program, coneModel);
        drawModel(program, monkeyModel);
        program.setUniform("materialId", 1);
        drawModel(program, terrainModel);

        lightningsProgram.use();
        setupCameraUniforms(lightningsProgram, camera, screenWidth, screenHeight);
        for( const auto& light : lightBuffer.getData())
        {
            lightningsProgram.setUniform("model", glm::translate(glm::mat4(1.0f), glm::vec3(light.position)));
            lightningsProgram.setUniform("color", light.diffuse);
            lightCube.draw();
        }



        window.pollEvents();
        window.swapBuffers();
    }


    return 0;
}
