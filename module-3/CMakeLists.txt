# Create an executable for the main program
add_executable(module-3-rtos
    Src/main.cpp
    # Add other source files here if needed
)

# Link the drivers library to the main executable
target_link_libraries(module-3-rtos PRIVATE drivers mbed-os)
target_include_directories(module-3-rtos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Inc) # Allow the 8B-LCD project to see the drivers folder.
mbed_set_post_build(module-3-rtos) # Must call this for each target to set up bin file creation, code upload, etc
