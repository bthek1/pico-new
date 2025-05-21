cmake_minimum_required(VERSION 3.13)
set(PICO_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/pico-sdk")

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_projects)
pico_sdk_init()

add_subdirectory(main_project)
add_subdirectory(oscilloscope)
