get_directory_property (inc_dirs INCLUDE_DIRECTORIES)
list(TRANSFORM inc_dirs PREPEND "-I ")
list(JOIN inc_dirs " " INCLUDE_STRING)
message(STATUS "INCLUDE_DIRECTORIES: ${INCLUDE_STRING}")

set(RESOURCE_FILES 
    shaders/fragment/fragment_zad1_1.glsl 
    shaders/fragment/fragment_zad1_2.glsl 
    shaders/vertex/vertex_zad1.glsl
    models/cube.obj
    models/terrain.obj
    models/cone.obj
    models/monkey.obj)
set(SOURCE_FILES zad1.cpp)
add_executable_with_resources(l03z01 "${SOURCE_FILES}" "${RESOURCE_FILES}")

set(RESOURCE_FILES 
    shaders/fragment/fragment_zad2.glsl 
    shaders/vertex/vertex_zad2.glsl
    models/cone.obj
    models/monkey.obj)
set(SOURCE_FILES zad2.cpp)
add_executable_with_resources(l03z02 "${SOURCE_FILES}" "${RESOURCE_FILES}")

