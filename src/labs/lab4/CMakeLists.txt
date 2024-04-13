set(RESOURCE_FILES 
    shaders/fragment/fragment_zad1.glsl 
    shaders/vertex/vertex_zad1.glsl
    textures/fire.jpg
    textures/troll.png
    textures/uvtemplate.jpg)
set(SOURCE_FILES zad1.cpp)
add_executable_with_resources(l04z01 "${SOURCE_FILES}" "${RESOURCE_FILES}")


set(RESOURCE_FILES 
    shaders/fragment/fragment_zad2.glsl 
    shaders/vertex/vertex_zad2.glsl
    models/cube.obj
    textures/paper.png)
set(SOURCE_FILES zad2.cpp)
add_executable_with_resources(l04z02 "${SOURCE_FILES}" "${RESOURCE_FILES}")

set(RESOURCE_FILES 
    shaders/fragment/fragment_zad3.glsl 
    textures/flower32bit.png)
set(SOURCE_FILES zad3.cpp)
add_executable_with_resources(l04z03 "${SOURCE_FILES}" "${RESOURCE_FILES}")

set(RESOURCE_FILES 
    shaders/fragment/fragment_zad4.glsl 
    shaders/vertex/vertex_zad4.glsl
    textures/background.png)
set(SOURCE_FILES zad4.cpp)
add_executable_with_resources(l04z04 "${SOURCE_FILES}" "${RESOURCE_FILES}")