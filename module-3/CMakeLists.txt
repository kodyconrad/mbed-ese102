# Create an executable for the main program
add_executable(main
    main.cpp
    # Add other source files here if needed
)

# Link the drivers library to the main executable
target_link_libraries(main PRIVATE drivers mbed-os)
# target_include_directories(M2_ENV_MON PRIVATE "${CMAKE_SOURCE_DIR}/drivers") # Allow the 8B-LCD project to see the drivers folder.
# target_link_libraries(M2_ENV_MON mbed-os) # Can also link to mbed-baremetal here
mbed_set_post_build(main) # Must call this for each target to set up bin file creation, code upload, etc
