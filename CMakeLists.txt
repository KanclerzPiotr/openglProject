cmake_minimum_required(VERSION 3.10)
project(OpenGL VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

include_directories(extern/headerOnly)

add_subdirectory(extern/glfw)
add_subdirectory(extern/glm)
add_subdirectory(extern/glad)
add_subdirectory(extern/fmt)


add_subdirectory(src)

