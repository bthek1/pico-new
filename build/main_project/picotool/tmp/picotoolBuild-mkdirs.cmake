# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/bthek1/Documents/pico-new/build/_deps/picotool-src"
  "/home/bthek1/Documents/pico-new/build/_deps/picotool-build"
  "/home/bthek1/Documents/pico-new/build/_deps"
  "/home/bthek1/Documents/pico-new/build/main_project/picotool/tmp"
  "/home/bthek1/Documents/pico-new/build/main_project/picotool/src/picotoolBuild-stamp"
  "/home/bthek1/Documents/pico-new/build/main_project/picotool/src"
  "/home/bthek1/Documents/pico-new/build/main_project/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/bthek1/Documents/pico-new/build/main_project/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/bthek1/Documents/pico-new/build/main_project/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
