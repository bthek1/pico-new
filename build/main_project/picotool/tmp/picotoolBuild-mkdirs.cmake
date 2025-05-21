# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/proxmox-ml5/Documents/pico/pico-new/build/_deps/picotool-src"
  "/home/proxmox-ml5/Documents/pico/pico-new/build/_deps/picotool-build"
  "/home/proxmox-ml5/Documents/pico/pico-new/build/_deps"
  "/home/proxmox-ml5/Documents/pico/pico-new/build/main_project/picotool/tmp"
  "/home/proxmox-ml5/Documents/pico/pico-new/build/main_project/picotool/src/picotoolBuild-stamp"
  "/home/proxmox-ml5/Documents/pico/pico-new/build/main_project/picotool/src"
  "/home/proxmox-ml5/Documents/pico/pico-new/build/main_project/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/proxmox-ml5/Documents/pico/pico-new/build/main_project/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/proxmox-ml5/Documents/pico/pico-new/build/main_project/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
