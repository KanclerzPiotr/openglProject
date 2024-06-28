#include <common/Window.hpp>
#include <fmt/core.h>

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
    
    glfwSetWindowUserPointer(window, this);

    setFramebufferSizeCallback([](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });
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

void Window::setFramebufferSizeCallback(std::function<void(GLFWwindow*, int, int)>&& callback){
    framebufferSizeCallback = std::move(callback);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
        w->framebufferSizeCallback(window, width, height);
    });
}

void Window::setWindowSizeCallback(std::function<void(GLFWwindow*, int, int)>&& callback) {
    windowSizeCallback = std::move(callback);
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
        w->windowSizeCallback(window, width, height);
    });
}

void Window::setKeyCallback(std::function<void(GLFWwindow*, int, int, int, int)>&& callback) {
    keyCallback = std::move(callback);
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
        w->keyCallback(window, key, scancode, action, mods);
    });
}

void Window::setMouseButtonCallback(std::function<void(GLFWwindow*, int, int, int)>&& callback) {
    mouseButtonCallback = std::move(callback);
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
        w->mouseButtonCallback(window, button, action, mods);
    });
}

void Window::setCursorPosCallback(std::function<void(GLFWwindow*, double, double)>&& callback) {
    cursorPosCallback = std::move(callback);
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
        w->cursorPosCallback(window, xpos, ypos);
    });
}

void Window::setScrollCallback(std::function<void(GLFWwindow*, double, double)>&& callback) {
    scrollCallback = std::move(callback);
    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
        Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
        w->scrollCallback(window, xoffset, yoffset);
    });
}

void Window::enable(GLenum cap) {
    glEnable(cap);
}

void Window::setInputMode(int mode, int value) {
    glfwSetInputMode(window, mode, value);
}

void Window::blendFunc(GLenum sfactor, GLenum dfactor) {
    glBlendFunc(sfactor, dfactor);
}

void Window::blendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) {
    glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void Window::clearColor(float red, float green, float blue, float alpha) {
    glClearColor(red, green, blue, alpha);
}

void Window::clear(GLbitfield mask) {
    glClear(mask);
}

void Window::setPrimitiveRestartIndex(unsigned int index) {
    glPrimitiveRestartIndex(index);
}