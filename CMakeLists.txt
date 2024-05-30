#
# Mbed CE ESE102 CMake file.
#
cmake_minimum_required(VERSION 3.19)
cmake_policy(VERSION 3.19)

# Initialize Mbed OS build system. 
# Note: This block must be before the project() call.
set(MBED_APP_JSON_PATH mbed_app.json5)
# set(CUSTOM_TARGETS_JSON_PATH custom_targets.json) # If you need a custom target, use this line to specify the custom_targets.json

include(mbed-os/tools/cmake/app.cmake) # Load Mbed CE toolchain file and basic build system

# If you need any custom upload method configuration for your target, do that here
add_subdirectory(mbed-os) # Load Mbed OS build targets.  Must be add ed before any other subdirectories

project(MbedCEESE102)

# Add additional executables for each module and sub-stages within to easily track and allow flashing of that module as needed.
add_executable(M1_4B_LED ./module-1/4b-led/main.cpp)
target_link_libraries(M1_4B_LED mbed-os) # Can also link to mbed-baremetal here
mbed_set_post_build(M1_4B_LED) # Must call this for each target to set up bin file creation, code upload, etc

add_executable(M1_4B_LCD ./module-1/4b-lcd/main.cpp)
target_link_libraries(M1_4B_LCD mbed-os) # Can also link to mbed-baremetal here
mbed_set_post_build(M1_4B_LCD) # Must call this for each target to set up bin file creation, code upload, etc

add_executable(M1_8B_LCD ./module-1/8b-lcd/main.cpp ./drivers/lcd.h)
target_include_directories(M1_8B_LCD PRIVATE "${CMAKE_SOURCE_DIR}/drivers") # Allow the 8B-LCD project to see the drivers folder.
target_link_libraries(M1_8B_LCD mbed-os) # Can also link to mbed-baremetal here
mbed_set_post_build(M1_8B_LCD) # Must call this for each target to set up bin file creation, code upload, etc

mbed_finalize_build() # Make sure this is the last line of the top-level buildscript