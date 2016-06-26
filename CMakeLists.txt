# Dungeon Warrior
# 
# Test OpenGL program using GLFW
# by Basim Khajwal

cmake_minimum_required(VERSION 2.8)
project(DragonWorld)

# Export compiler_commands.json for YCM vim plugin
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Set C++11 standard
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Project version
set (DragonWorld_VERSION_MAJOR 1)
set (DragonWorld_VERSION_MINOR 0)

# Require the OpenGL package
find_package(OpenGL REQUIRED)

# Add external dependencies
add_subdirectory(external)

# Add source code and headers
add_subdirectory(src)

# Include all necessary directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/external/glfw-3.2/include
    ${CMAKE_SOURCE_DIR}/external/glew-1.13.0/include
    ${CMAKE_SOURCE_DIR}/external/glm
    )

# Create lists for all the sources, headers and libraries needed
set(PROJECT_SOURCES
    src/main.cpp
    src/ShaderProgram.cpp
    src/Window.cpp
    src/Camera.cpp
    src/Mesh.cpp
    )

set(PROJECT_LIBRARIES
    ${OPENGL_LIBRARY}
    glfw
    GLEW_1130)

# Set definitions for Visual Studio
add_definitions(
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS)

# Copy across asset files if any have been changed
file(COPY assets DESTINATION .)

# Create, build and link the one target executable
add_executable(DragonWorld ${PROJECT_SOURCES})
target_link_libraries(DragonWorld ${PROJECT_LIBRARIES})
