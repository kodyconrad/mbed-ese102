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
add_executable(ESE102M1LED ./module_1_led/main.cpp)
target_link_libraries(ESE102M1LED mbed-os) # Can also link to mbed-baremetal here
mbed_set_post_build(ESE102M1LED) # Must call this for each target to set up bin file creation, code upload, etc

add_executable(ESE102M1LCD ./module_1_lcd/main.cpp)
target_link_libraries(ESE102M1LCD mbed-os) # Can also link to mbed-baremetal here
mbed_set_post_build(ESE102M1LCD) # Must call this for each target to set up bin file creation, code upload, etc

add_executable(ESE102M1CASCADE ./module_1_cascaded/main.cpp)
target_link_libraries(ESE102M1CASCADE mbed-os) # Can also link to mbed-baremetal here
mbed_set_post_build(ESE102M1CASCADE) # Must call this for each target to set up bin file creation, code upload, etc

add_executable(ESE102M1_CASCADE_LCD ./module_1_cascade_lcd/main.cpp ./module_1_cascade_lcd/lcd.h)
target_link_libraries(ESE102M1_CASCADE_LCD mbed-os) # Can also link to mbed-baremetal here
mbed_set_post_build(ESE102M1_CASCADE_LCD) # Must call this for each target to set up bin file creation, code upload, etc

mbed_finalize_build() # Make sure this is the last line of the top-level buildscript