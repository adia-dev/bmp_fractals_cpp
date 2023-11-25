cmake_minimum_required(VERSION 3.26)

set(PROJECT_NAME bmp_fractal)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

project(${PROJECT_NAME})

file(GLOB_RECURSE SOURCES src/*.cpp src/**/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC src/**/ src/ include/)
