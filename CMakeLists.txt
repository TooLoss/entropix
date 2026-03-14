cmake_minimum_required(VERSION 3.20)
project(SandSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(dependencies/sdl3.cmake)

add_subdirectory(src)
