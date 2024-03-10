#ifndef COMMON_WINDOW_HPP
#define COMMON_WINDOW_HPP

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <fmt/core.h>
#include <string_view>

void DEFAULT_FRAME_BUFFER_CALLBACK(GLFWwindow* window, int width, int height);

class Window {
public:
    Window(int width, int height, std::string_view title);
    ~Window();
    bool shouldClose() const;
    void swapBuffers();
    void pollEvents();
    void loadGLAD();
    void setKeyCallback(GLFWkeyfun callback);
    void setMouseButtonCallback(GLFWmousebuttonfun callback);
    void setCursorPosCallback(GLFWcursorposfun callback);
    void setScrollCallback(GLFWscrollfun callback);
    void setFramebufferSizeCallback(GLFWframebuffersizefun callback);
    void setWindowSizeCallback(GLFWwindowsizefun callback);
    void enable(GLenum cap);

private:
    GLFWwindow* window;
};

#endif // COMMON_WINDOW_HPP
