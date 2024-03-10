#include <common/Window.hpp>
#include <fmt/core.h>

void DEFAULT_FRAME_BUFFER_CALLBACK(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
};

Window::Window(int width, int height, std::string_view title) {
    // Initialize GLFW
    if (!glfwInit()) {
        fmt::println("Error initializing GLFW");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(width, height, title.data(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        fmt::println("Error creating GLFW window");
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    setFramebufferSizeCallback(DEFAULT_FRAME_BUFFER_CALLBACK);

    loadGLAD();
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

void Window::loadGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fmt::println("Error initializing GLAD");
        exit(EXIT_FAILURE);
    }
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::setKeyCallback(GLFWkeyfun callback) {
    glfwSetKeyCallback(window, callback);
}

void Window::setMouseButtonCallback(GLFWmousebuttonfun callback) {
    glfwSetMouseButtonCallback(window, callback);
}

void Window::setCursorPosCallback(GLFWcursorposfun callback) {
    glfwSetCursorPosCallback(window, callback);
}

void Window::setScrollCallback(GLFWscrollfun callback) {
    glfwSetScrollCallback(window, callback);
}

void Window::setFramebufferSizeCallback(GLFWframebuffersizefun callback) {
    glfwSetFramebufferSizeCallback(window, callback);
}

void Window::setWindowSizeCallback(GLFWwindowsizefun callback) {
    glfwSetWindowSizeCallback(window, callback);
}

void Window::enable(GLenum cap) {
    glEnable(cap);
}