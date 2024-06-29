set(RESOURCE_FILES 
    shaders/fragment/terrain_fragment.glsl 
    shaders/fragment/normal_fragment.glsl 
#     shaders/fragment/fragment_zad2_refraction.glsl 
    shaders/fragment/fragment_skybox.glsl 
    shaders/fragment/fragment_lights.glsl 
    shaders/fragment/fragment_instanced.glsl 
    shaders/vertex/terrain_vertex.glsl
    shaders/vertex/normal_vertex.glsl
    shaders/vertex/vertex_skybox.glsl
    shaders/vertex/vertex_lights.glsl
    shaders/vertex/vertex_instanced.glsl
    tex/koliber.jpg
    tex/grass.jpg
    tex/sand.jpg
    tex/water.jpg
    models/koliber.obj
    models/cube.obj
    models/cone.obj
    skybox/back.jpg
    skybox/front.jpg
    skybox/left.jpg
    skybox/right.jpg
    skybox/top.jpg
    skybox/bottom.jpg
)

set(SOURCE_FILES 
    src/main.cpp
    src/HeightMap.hpp
    src/PerlinNoise.hpp
    src/TileManager.hpp
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