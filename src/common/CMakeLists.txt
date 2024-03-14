set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include/common)

set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/GLSLProgram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Window.cpp
)

set(HEADERS
    ${INCLUDE_PATH}/GLSLProgram.hpp
    ${INCLUDE_PATH}/Mesh.hpp
    ${INCLUDE_PATH}/Vertex.hpp
    ${INCLUDE_PATH}/Window.hpp
)

add_library(common ${SRC} ${HEADERS})


target_include_directories(common PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(common glfw glad glm fmt::fmt)

if(WIN32)
    target_link_libraries(common opengl32)
elseif(UNIX)
    target_link_libraries(common GL)
endif()