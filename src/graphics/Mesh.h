#pragma once

#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Mesh {

    GLuint vaoID, vertexBufferID, colourBufferID, indexBufferID;
    int vertexCount;

    GLuint bindBufferToAttribute(const vector<float>& data, int attribPointer, int attribSize);

    template <typename T>
    GLuint createStaticVBO(const vector<T>& data, GLenum type);
public:

    Mesh (const vector<float>& vertices, const vector<float>& colours, const vector<int>& indices);
    ~Mesh();

    void render();
    
};
