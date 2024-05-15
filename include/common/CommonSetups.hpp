#ifndef COMMON_COMMONSETUPS_HPP
#define COMMON_COMMONSETUPS_HPP

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

void setupCameraUniforms(GLSLProgram& program, const Camera& camera, int screenWidth, int screenHeight) {
    program.setUniform("view", camera.getViewMatrix());
    program.setUniform("projection", camera.getProjectionMatrix(screenWidth, screenHeight));
    program.setUniform("viewPos", camera.getPosition());
}

void drawModel(GLSLProgram& program, Model& model) {
    program.setUniform("model", model.getModelMatrix());
    program.setUniform("normalMatrix", model.getNormalMatrix());
    model.setTextureUniforms(program);
    model.draw();
}
#endif // COMMON_COMMONSETUPS_HPP