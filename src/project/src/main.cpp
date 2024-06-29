#include "HeightMap.hpp"
#include "TileManager.hpp"

#include <fmt/core.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include <common/Camera.hpp>
#include <common/Window.hpp>
#include <common/GLSLProgram.hpp>
#include <common/Texture.hpp>
#include <common/Model.hpp>
#include <common/Skybox.hpp>
#include <common/CommonSetups.hpp>
#include <common/UniformBuffer.hpp>
#include <common/Light.hpp>
#include <common/Material.hpp>
#include <common/InstancedModel.hpp>

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

Skybox makeSkybox()
{
    return Skybox{"vertex_skybox.glsl", "fragment_skybox.glsl", {
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg"
    }};
}

void drawLights(GLSLProgram& lightningsProgram, Model& lightCube, const Camera& camera, UniformBuffer<Light>& lightBuffer, int screenWidth, int screenHeight)
{
    Light followingLight{
            {0.2f, 0.2f, 0.2f, 1.0f},
            {0.7f, 0.7f, 0.7f, 1.0f},
            {1.0f, 0.0f, 0.0f, 1.0f},
            {1.0f, 0.0f, 0.01f, 1.0f},
            {1.0f, 1.0f, 1.0f, 1.0f},
    };
    followingLight.position = glm::vec4(camera.getPosition(), 1.0f);
    lightBuffer.updateData(0, followingLight);
    const auto& lightsData = lightBuffer.getData();


    lightningsProgram.use();
    setupCameraUniforms(lightningsProgram, camera, screenWidth, screenHeight);
    
    for (int i = 1; i < lightsData.size(); i++)
    {
        glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.7f));
        model = glm::translate(model, glm::vec3(lightsData[i].position));
        lightningsProgram.setUniform("model", model);
        lightningsProgram.setUniform("color", lightsData[i].diffuse);
        lightCube.draw();
    }
    
}

auto createLightBuffer()
{
    UniformBuffer<Light> lightBuffer{{
        {
            {0.2f, 0.2f, 0.2f, 1.0f},
            {0.5f, 0.5f, 0.5f, 1.0f},
            {1.0f, 0.0f, 0.0f, 1.0f},
            {1.0f, 0.0f, 0.01f, 1.0f},
            {1.0f, 1.0f, 1.0f, 1.0f},
        },
        {
            {0.2f, 0.2f, 0.2f, 1.0f},
            {0.7f, 0.7f, 0.7f, 1.0f},
            {0.0f, 1.0f, 0.0f, 1.0f},
            {1.0f, 0.0f, 0.01f, 1.0f},
            {3.0f, 5.0f, -3.0f, 1.0f},
        },
        {
            {0.2f, 0.2f, 0.2f, 1.0f},
            {0.7f, 0.0f, 0.0f, 1.0f},
            {0.0f, 1.0f, 0.0f, 1.0f},
            {1.0f, 0.0f, 0.01f, 1.0f},
            {3.0f, 5.0f, -6.0f, 1.0f},
        }
    }};
    lightBuffer.bind(POINT_LIGHTS_BINDING_POINT);
    return lightBuffer;
}

void drawTrees(GLSLProgram& program, Model& cone, const Camera& camera, int screenWidth, int screenHeight)
{
    const std::vector<glm::vec3> treePositions = {
        {3.0f, 1.0f, 3.0f},
        {0.0f, 1.0f, 5.0f},
        {0.0f, 1.0f, -5.0f},
        {5.0f, 1.0f, 0.0f},
        {-5.0f, 1.0f, 0.0f},
        {5.0f, 1.0f, 5.0f},
        {5.0f, 1.0f, -5.0f},
        {-5.0f, 1.0f, 5.0f},
        {-5.0f, 1.0f, -5.0f},
    };

    program.use();

    for(const auto& position : treePositions)
    {
        for(int i =0 ; i < 3; i++)
        {
            auto model = glm::translate(glm::mat4(1.0f), position + glm::vec3{0.0f, i * 1.0f, 0.0f});
            setupCameraUniforms(program, camera, screenWidth, screenHeight);
            program.setUniform("model", model);
            program.setUniform("normalMatrix", glm::transpose(glm::inverse(model)));
            cone.setTextureUniforms(program);
            cone.draw();
        }
    }
}


auto createDirectionalLightBuffer()
{
    UniformBuffer<Light> directionalLightBuffer{{
        {
            {0.2f, 0.2f, 0.2f, 1.0f},
            {0.5f, 0.5f, 0.5f, 1.0f},
            {0.0f, 0.1f, 1.0f, 1.0f},
            {1.0f, 0.0f, 0.00f, 1.0f},
            {-0.2f, -1.0f, -0.3f, 1.0f},
        }
    }};
    directionalLightBuffer.bind(DIRECTIONAL_LIGHTS_BINDING_POINT);
    return directionalLightBuffer;
}

auto createMaterialBuffer()
{
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
    return materialBuffer;
}

std::vector<glm::mat4> generateModelMatrices(int size)
{
    std::vector<glm::mat4> modelMatrices(size);
    std::default_random_engine generator;
    std::uniform_real_distribution<float> translationDistribution(-50.0f, 50.0f);
    std::uniform_real_distribution<float> translationDistributionY(2.0f, 5.0f);

    for(auto& modelMatrix : modelMatrices)
    {
        modelMatrix = glm::mat4(1.0f); 
        modelMatrix = glm::translate(glm::mat4(1.0f), {translationDistribution(generator), translationDistributionY(generator), translationDistribution(generator)});
    }
    return modelMatrices;
}

int main()
{
    Camera camera{{0.0f, 8.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, -90.0f, -20.0f};

    Window window(screenWidth, screenHeight, "OpenGL");
    window.enable(GL_DEPTH_TEST);
    window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    window.enable(GL_PRIMITIVE_RESTART);
    window.setPrimitiveRestartIndex(0xFFFFFFFF);
    window.setKeyCallback(makeKeyCallback(camera));
    window.setScrollCallback(makeScrollCallback(camera));
    window.setCursorPosCallback(makeCursorPosCallback(camera));

    auto lightBuffer = createLightBuffer();
    auto directionalLightBuffer = createDirectionalLightBuffer();
    auto materialBuffer = createMaterialBuffer();

    TileManager tileManager{{"terrain_vertex.glsl", "terrain_fragment.glsl"}, camera.getPosition(), 10.0f};
    Skybox skybox = makeSkybox();

    GLSLProgram lightningsProgram{"vertex_lights.glsl", "fragment_lights.glsl"};
    Model lightCube{"cube.obj"};

    
    GLSLProgram instancedProgram{"vertex_instanced.glsl", "fragment_instanced.glsl"};
    Model humming{"koliber.obj", {"koliber.jpg"}};
    humming.bind();
    auto modelMatricies = generateModelMatrices(100);
    InstancedModel instancedHumming{std::move(humming), modelMatricies};

    GLSLProgram normalProgram{"terrain_vertex.glsl", "terrain_fragment.glsl"};
    Model cone{"cone.obj", {"grass.jpg", "sand.jpg", "water.jpg"}};

    while(!window.shouldClose())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawLights(lightningsProgram, lightCube, camera, lightBuffer, screenWidth, screenHeight);
        tileManager.draw(camera, screenWidth, screenHeight);
        tileManager.setUniform("pointLightNumber", lightBuffer.getSize());
        tileManager.setUniform("materialId", 1);
        skybox.draw(camera.getViewMatrix(), camera.getProjectionMatrix(screenWidth, screenHeight));
// 
        instancedProgram.use();
        setupCameraUniforms(instancedProgram, camera, screenWidth, screenHeight);
        instancedProgram.setUniform("time", static_cast<float>(glfwGetTime()));
        instancedProgram.setUniform("pointLightNumber", lightBuffer.getSize());
        instancedProgram.setUniform("materialId", 1);
        instancedHumming.setTextureUniforms(instancedProgram);
        instancedHumming.draw();

        normalProgram.use();
        normalProgram.setUniform("pointLightNumber", lightBuffer.getSize());
        normalProgram.setUniform("materialId", 1);
        drawTrees(normalProgram, cone, camera, screenWidth, screenHeight);

        window.pollEvents();
        window.swapBuffers();
    }





    return 0;
}