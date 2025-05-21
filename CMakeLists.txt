cmake_minimum_required(VERSION 3.13)

# Set SDK path
set(PICO_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../pico-sdk")

# Import the Pico SDK's CMake helpers
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# 👇 Now call project() AFTER importing pico_sdk_import
project(pico_projects C CXX ASM)

# 👇 Now initialize the SDK
pico_sdk_init()

# Add your subproject(s)
add_subdirectory(main_project)
