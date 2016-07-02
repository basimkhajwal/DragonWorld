#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <SOIL.h>

class Texture {

    int width, height;
    GLuint textureId;

public:

    Texture(const char* filePath);
    ~Texture();

    void bind();
    void unbind();
        
    GLuint getTextureId() { return textureId; }
    int getWidth() { return width; }
    int getHeight() { return height; }
};
