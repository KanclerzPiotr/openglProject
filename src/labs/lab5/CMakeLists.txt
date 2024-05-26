set(RESOURCE_FILES 
    shaders/fragment/fragment_zad1.glsl 
    shaders/fragment/fragment_zad1_2.glsl 
    shaders/vertex/vertex_zad1.glsl
    shaders/vertex/vertex_zad1_2.glsl
    textures/fire.jpg
    textures/grass.jpg
    textures/metal.jpg
    textures/troll.png
    models/cube.obj
    models/terrain.obj
    models/cone.obj
    models/monkey.obj
)
set(SOURCE_FILES zad1.cpp)
add_executable_with_resources(l05z01 "${SOURCE_FILES}" "${RESOURCE_FILES}")