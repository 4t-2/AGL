cmake_minimum_required(VERSION 3.10)

project(text)

file(GLOB_RECURSE SRC ./src/*.cpp)
file(GLOB_RECURSE AGL ../../AGL/src/*.cpp)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

add_executable(main.out ${SRC} ${AGL})

target_link_libraries(main.out X11 GL GLEW SOIL freetype)
include_directories("/usr/include/freetype2")
