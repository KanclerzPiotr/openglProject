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

int main(void)
{
    Camera camera{{0.0f, 8.0f, 20.0f}, {0.0f, 1.0f, 0.0f}, -90.0f, -20.0f};

    Window window(screenWidth, screenHeight, "OpenGL");
    window.enable(GL_DEPTH_TEST);
    window.setScrollCallback(makeScrollCallback(camera));
    window.setKeyCallback(makeKeyCallback(camera));
    window.setCursorPosCallback(makeCursorPosCallback(camera));

    GLSLProgram program{"vertex_zad1.glsl", "fragment_zad1.glsl"};

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
        }
    }};

    lightBuffer.bind(LIGHTS_BINDING_POINT);

    Model cubeModel{"cube.obj", {"troll.png"}};
    Model coneModel{"cone.obj", {"fire.jpg"}};
    Model monkeyModel{"monkey.obj", {"metal.jpg"}};
    Model terrainModel{"terrain.obj", {"grass.jpg"}};
    
    setupModels(cubeModel, coneModel, monkeyModel, terrainModel);
    constexpr float radius = 5.0f;
    constexpr float circle = 2.0f * radius * glm::pi<float>();

    program.use(); 

    program.setUniform("lightsNumber", lightBuffer.size());

    while(!window.shouldClose())
    {

        float time = glfwGetTime();
        float deltaTime = getDeltaTime();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        animateCube(cubeModel, time);
        animateCone(coneModel, deltaTime, circle);
        animateMonkey(monkeyModel, time);
    
        setupCameraUniforms(program, camera, screenWidth, screenHeight);

        drawModel(program, cubeModel);
        drawModel(program, coneModel);
        drawModel(program, monkeyModel);
        drawModel(program, terrainModel);

        window.pollEvents();
        window.swapBuffers();
    }




    return 0;
}
