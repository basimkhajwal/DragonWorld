# Dungeon Warrior
# 
# Test OpenGL program using GLFW
# by Basim Khajwal

cmake_minimum_required(VERSION 2.8)
project(DungeonWarrior)

# Export compiler_commands.json for YCM vim plugin
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Set C++11 standard
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Project version
set (DungeonWarrior_VERSION_MAJOR 1)
set (DungeonWarrior_VERSION_MINOR 0)

# Require the OpenGL package
find_package(OpenGL REQUIRED)

# Add external dependencies
add_subdirectory(external)

# Include all necessary directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/external/glfw-3.2/include
    ${CMAKE_SOURCE_DIR}/external/glew-1.13.0/include
    ${CMAKE_SOURCE_DIR}/external/glm
    ${CMAKE_SOURCE_DIR}/external/soil/src
    )

# Create lists for all the sources, headers and libraries needed
set(PROJECT_SOURCES
    src/main.cpp
    src/Constants.h
    src/Game.cpp
    src/Game.h
    src/Camera.cpp
    src/Camera.h

    src/graphics/ShaderProgram.cpp
    src/graphics/ShaderProgram.h
    src/graphics/Window.cpp
    src/graphics/Window.h
    src/graphics/Mesh.cpp
    src/graphics/Mesh.h
    src/graphics/Texture.cpp
    src/graphics/Texture.h

    src/states/GameState.cpp
    src/states/GameState.h
    src/states/MainState.cpp
    src/states/MainState.h

    src/systems/GridRenderSystem.cpp
    src/systems/GridRenderSystem.h

    src/utils/FPSLogger.cpp
    src/utils/FPSLogger.h
    )

set(PROJECT_LIBRARIES
    ${OPENGL_LIBRARY}
    glfw
    GLEW_1130
    SOIL
    )

# Set definitions for Visual Studio
add_definitions(
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS)

# Create, build and link the one target executable
add_executable(DungeonWarrior ${PROJECT_SOURCES})
target_link_libraries(DungeonWarrior ${PROJECT_LIBRARIES})

# Set source groups for folders in Visual Studio
source_group(src REGULAR_EXPRESSION "src/*")
source_group(src\\graphics\\ REGULAR_EXPRESSION "src/graphics/*")
source_group(src\\states\\ REGULAR_EXPRESSION "src/states/*")
source_group(src\\systems\\ REGULAR_EXPRESSION "src/systems/*")
source_group(src\\utils\\ REGULAR_EXPRESSION "src/utils/*")

# Copy across asset files if any have been changed
add_custom_command(TARGET DungeonWarrior POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets)
