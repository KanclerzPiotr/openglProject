#ifndef COMMON_COMMONSETUPS_HPP
#define COMMON_COMMONSETUPS_HPP

auto makeScrollCallback(Camera& camera)
{
    return [&camera](GLFWwindow* window, double xoffset, double yoffset) {
        camera.processMouseScroll(yoffset);
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
    program.setUniform("cameraPos", camera.getPosition());
}

void drawModel(GLSLProgram& program, Model& model) {
    program.setUniform("model", model.getModelMatrix());
    program.setUniform("normalMatrix", model.getNormalMatrix());
    model.setTextureUniforms(program);
    model.draw();
}
#endif // COMMON_COMMONSETUPS_HPP