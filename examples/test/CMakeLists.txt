cmake_minimum_required(VERSION 3.10)

project(example)

file(GLOB_RECURSE SRC ./src/*.cpp)
file(GLOB_RECURSE AGL ../../AGL/src/*.cpp)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
# set (CMAKE_CXX_FLAGS "-fsanitize=address ")

message(STATUS ${CMAKE_CXX_STANDARD})

add_executable(main.out ${SRC} ${AGL})

if(LINUX)
    target_link_libraries(main.out X11 GL GLEW SOIL freetype)
    include_directories("/usr/include/freetype2")    
endif(LINUX)

if(WIN32)
    target_link_libraries(main.out opengl32 gdi32)
    include_directories("C:\\glew\\include")
    include_directories("C:\\freetype\\include")
endif(WIN32)
