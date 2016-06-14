#pragma once

#include <GLFW/glfw3.h>

/*
 * Load the specified shaders into the GL context
 * and return the ID created for them
 * */
GLuint LoadShaders(const char* vertexFilePath, const char* fragmentFilePath);
