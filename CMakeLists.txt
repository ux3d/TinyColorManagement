cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

project(TinyColorSpace)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(src thirdparty/glm)

add_executable(TinyColorSpace src/main.cpp src/TinyColorSpace.cpp)
