cmake_minimum_required(VERSION 3.10)

project(Rectangle)

file(GLOB_RECURSE SRC ./src/*.cpp)
file(GLOB_RECURSE AGL ../../AGL/src/*.cpp)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

add_executable(main ${SRC} ${AGL})

if(LINUX)
	target_link_libraries(main glfw GL GLEW SOIL freetype)
    include_directories("/usr/include/freetype2")    
endif(LINUX)

if(WIN32)
    target_link_libraries(main "C:\\glfw\\lib\\glfw3.dll" "C:\\freetype\\objs\\libfreetype.dll" "C:\\glew\\lib\\Release\\x64\\glew32.lib" "C:\\soil\\lib\\libsoil.a" opengl32)
    include_directories("C:\\glew\\include")
    include_directories("C:\\freetype\\include")
    include_directories("C:\\glfw\\include")
    include_directories("C:\\soil\\include")
endif(WIN32)
