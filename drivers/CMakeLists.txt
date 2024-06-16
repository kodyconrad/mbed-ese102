# Set the drivers library
add_library(drivers
    Src/sensiron.cpp
    Src/util.cpp
    # Add other driver source files here
)

# Include the header files directory
target_include_directories(drivers PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../mbed-os
)
target_link_libraries(drivers mbed-os) # Can also link to mbed-baremetal here

