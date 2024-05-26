set(RESOURCE_FILES 
    shaders/fragment/fragment_zad2_reflection.glsl 
    shaders/fragment/fragment_zad2_refraction.glsl 
    shaders/fragment/fragment_skybox.glsl 
    shaders/vertex/vertex_zad2.glsl
    shaders/vertex/vertex_skybox.glsl
    textures/koliber.jpg
    models/koliber.obj
    skybox/back.jpg
    skybox/front.jpg
    skybox/left.jpg
    skybox/right.jpg
    skybox/top.jpg
    skybox/bottom.jpg
)
set(SOURCE_FILES zad1.cpp)
add_executable_with_resources(l06z01 "${SOURCE_FILES}" "${RESOURCE_FILES}")


set(RESOURCE_FILES 
    shaders/fragment/fragment_zad3.glsl 
    shaders/fragment/fragment_skybox.glsl 
    shaders/vertex/vertex_zad3.glsl
    shaders/vertex/vertex_skybox.glsl
    textures/koliber.jpg
    models/koliber.obj
    skybox/back.jpg
    skybox/front.jpg
    skybox/left.jpg
    skybox/right.jpg
    skybox/top.jpg
    skybox/bottom.jpg
)
set(SOURCE_FILES zad3.cpp)
add_executable_with_resources(l06z03 "${SOURCE_FILES}" "${RESOURCE_FILES}")