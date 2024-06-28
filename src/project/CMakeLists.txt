set(RESOURCE_FILES 
    shaders/fragment/terrain_fragment.glsl 
#     shaders/fragment/fragment_zad2_refraction.glsl 
#     shaders/fragment/fragment_skybox.glsl 
    shaders/vertex/terrain_vertex.glsl
#     shaders/vertex/vertex_skybox.glsl
#     textures/koliber.jpg
    tex/grass.jpg
    tex/sand.jpg
    tex/water.jpg
#     models/koliber.obj
#     skybox/back.jpg
#     skybox/front.jpg
#     skybox/left.jpg
#     skybox/right.jpg
#     skybox/top.jpg
#     skybox/bottom.jpg
)

set(SOURCE_FILES 
    src/main.cpp
    src/HeightMap.hpp
    src/PerlinNoise.hpp
)

set(EXECUTABLE_NAME projekt)


add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
    
# Include directories
target_include_directories(${EXECUTABLE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Link libraries
target_link_libraries(${EXECUTABLE_NAME} common fmt::fmt)


function(copy_resource_files TARGET_NAME)
    foreach(RESOURCE_FILE ${ARGN})
        add_custom_command(
            TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_FILE}
                    $<TARGET_FILE_DIR:${TARGET_NAME}>
            COMMENT "Copying ${RESOURCE_FILE} to build directory ${EXECUTABLE_OUTPUT_DIRECTORY}"
        )
    endforeach()
endfunction()

copy_resource_files(${EXECUTABLE_NAME} ${RESOURCE_FILES})