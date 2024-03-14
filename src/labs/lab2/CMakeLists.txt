set(RESOURCE_FILES shaders/fragment/fragment_zad1.glsl shaders/vertex/vertex_zad1.glsl)
set(SOURCE_FILES zad1.cpp)
add_executable_with_resources(l02z01 "${SOURCE_FILES}" "${RESOURCE_FILES}")

set(RESOURCE_FILES shaders/fragment/fragment_zad2.glsl shaders/vertex/vertex_zad2.glsl)
set(SOURCE_FILES zad2.cpp)
add_executable_with_resources(l02z02 "${SOURCE_FILES}" "${RESOURCE_FILES}")

set(RESOURCE_FILES shaders/fragment/fragment_zad3.glsl shaders/vertex/vertex_zad3.glsl)
set(SOURCE_FILES zad3.cpp)
add_executable_with_resources(l02z03 "${SOURCE_FILES}" "${RESOURCE_FILES}")

set(RESOURCE_FILES shaders/fragment/fragment_zad4.glsl shaders/vertex/vertex_zad4.glsl)
set(SOURCE_FILES zad4.cpp)
add_executable_with_resources(l02z04 "${SOURCE_FILES}" "${RESOURCE_FILES}")