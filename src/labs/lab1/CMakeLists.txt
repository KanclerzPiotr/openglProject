function(add_executable_with_resources EXECUTABLE_NAME SOURCE_FILES RESOURCE_FILES)
    # Add executable
    add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
    
    # Include directories
    target_include_directories(${EXECUTABLE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
    
    # Link libraries
    target_link_libraries(${EXECUTABLE_NAME} common fmt::fmt)
    
    # Function to copy resource files
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

    # Call the function to copy resource files
    copy_resource_files(${EXECUTABLE_NAME} ${RESOURCE_FILES})
endfunction()

set(RESOURCE_FILES shaders/fragment/fragment_zad1.glsl shaders/vertex/vertex_zad1.glsl)
set(SOURCE_FILES zad1.cpp)
add_executable_with_resources(zad1 "${SOURCE_FILES}" "${RESOURCE_FILES}")

set(RESOURCE_FILES shaders/fragment/fragment_zad2.glsl shaders/vertex/vertex_zad2.glsl)
set(SOURCE_FILES zad2.cpp)
add_executable_with_resources(zad2 "${SOURCE_FILES}" "${RESOURCE_FILES}")

set(RESOURCE_FILES shaders/fragment/fragment_zad3.glsl shaders/vertex/vertex_zad3.glsl)
set(SOURCE_FILES zad3.cpp)
add_executable_with_resources(zad3 "${SOURCE_FILES}" "${RESOURCE_FILES}")

set(RESOURCE_FILES shaders/fragment/fragment_zad4.glsl shaders/vertex/vertex_zad4.glsl shaders/fragment/fragment_zad4-2.glsl shaders/vertex/vertex_zad4-2.glsl)
set(SOURCE_FILES zad4.cpp)
add_executable_with_resources(zad4 "${SOURCE_FILES}" "${RESOURCE_FILES}")

set(RESOURCE_FILES shaders/fragment/fragment_zad5.glsl shaders/vertex/vertex_zad5.glsl)
set(SOURCE_FILES zad5.cpp)
add_executable_with_resources(zad5 "${SOURCE_FILES}" "${RESOURCE_FILES}")

set(RESOURCE_FILES shaders/fragment/fragment_zad1.glsl shaders/vertex/vertex_zad1.glsl)
set(SOURCE_FILES zad6.cpp)
add_executable_with_resources(zad6 "${SOURCE_FILES}" "${RESOURCE_FILES}")
