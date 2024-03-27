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

add_subdirectory(lab1)
add_subdirectory(lab2)
add_subdirectory(lab3)