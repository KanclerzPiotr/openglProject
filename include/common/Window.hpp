#ifndef COMMON_WINDOW_HPP
#define COMMON_WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <string_view>
#include <functional>

class Window {
public:
    Window(int width, int height, std::string_view title);
    ~Window();
    bool shouldClose() const;
    void swapBuffers();
    void pollEvents();
    void loadGLAD();
    void setFramebufferSizeCallback(std::function<void(GLFWwindow*, int, int)>&& callback);
    void setWindowSizeCallback(std::function<void(GLFWwindow*, int, int)>&& callback);
    void setKeyCallback(std::function<void(GLFWwindow*, int, int, int, int)>&& callback);
    void setMouseButtonCallback(std::function<void(GLFWwindow*, int, int, int)>&& callback);
    void setCursorPosCallback(std::function<void(GLFWwindow*, double, double)>&& callback);
    void setScrollCallback(std::function<void(GLFWwindow*, double, double)>&& callback);
    void setInputMode(int mode, int value);
    void enable(GLenum cap);
    void blendFunc(GLenum sfactor, GLenum dfactor);
    void blendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
    void clearColor(float red, float green, float blue, float alpha);
    void clear(GLbitfield mask);

private:
    GLFWwindow* window;
    std::function<void(GLFWwindow*, int, int)> framebufferSizeCallback;
    std::function<void(GLFWwindow*, int, int)> windowSizeCallback;
    std::function<void(GLFWwindow*, int, int, int, int)> keyCallback;
    std::function<void(GLFWwindow*, int, int, int)> mouseButtonCallback;
    std::function<void(GLFWwindow*, double, double)> cursorPosCallback;
    std::function<void(GLFWwindow*, double, double)> scrollCallback;
};

#endif // COMMON_WINDOW_HPP
