# Dragon World
# Originally by Jamie
# Updated to a cross platform Cmake project by Basim

cmake_minimum_required(VERSION 2.8)
project(DragonWorld)

# Export compiler_commands.json for YCM vim plugin
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Project version
set (DragonWorld_VERSION_MAJOR 1)
set (DragonWorld_VERSION_MINOR 0)

# Require the OpenGL package
find_package(OpenGL REQUIRED)

# Add external dependencies
add_subdirectory(external)

# Add source code and headers
add_subdirectory(src)
add_subdirectory(include)

# Include all necessary directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/glfw-3.2/include
    ${CMAKE_SOURCE_DIR}/external/glew-1.13.0/include
    )

# Create lists for all the sources and libraries needed
set(PROJECT_SOURCES
    src/main.cpp # Temporary
    src/utils.cpp
    src/shaders/SimpleVertexShader.txt
    src/shaders/SimpleFragmentShader.txt
    )

set(PROJECT_LIBRARIES
    ${OPENGL_LIBRARY}
    glfw
    GLEW_1130)

# Set definitions for Visual Studio
add_definitions(
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS)

# Create, build and link the one target executable
add_executable(DragonWorld ${PROJECT_SOURCES})
target_link_libraries(DragonWorld ${PROJECT_LIBRARIES})
