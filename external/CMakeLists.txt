# Manage all the external dependencies
# for the DragonWorld project
#
# Currently Includes:
# - GLFW 3.2
# - GLEW 1.13.0

cmake_minimum_required(VERSION 2.8)


# ------ GLFW ------

# Prevent building of tests/docs/examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Add GLFW subdirectory
add_subdirectory(glfw-3.2)

# Setup all the OpenGL dependencies
include_directories(
    glew-1.13.0/include/
    glfw-3.2/include/GLFW)

set(OPENGL_LIBRARY
    ${OPENGL_LIBRARY}
    ${CMAKE_DL_LIBS}
    ${GLFW_LIBRARIES})

# ------- GLEW --------
# Manually build since it has no CMake
set(GLEW_SOURCES
    glew-1.13.0/src/glew.c)

add_library(GLEW_1130 STATIC ${GLEW_SOURCES})
target_link_libraries(GLEW_1130 ${OPENGL_LIBRARY})
