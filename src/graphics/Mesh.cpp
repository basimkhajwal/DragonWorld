#include <cstdio>
using namespace std;

#include <graphics/Mesh.h>

Mesh::Mesh(const vector<float>& vertices, const vector<float>& colours, const vector<float>& textureCoords, const vector<int>& indices) {

    static int meshId = 0;
    printf("MESH:\t\tCreating new mesh id: %d\n", meshId++);

    /* Save vertex count and create a new VAO for this mesh */
    vertexCount = (int) indices.size();
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    /* Create the index buffer and the attribute buffers */
    indexBufferID = createStaticVBO(indices, GL_ELEMENT_ARRAY_BUFFER);
    vertexBufferID = bindBufferToAttribute(vertices, 0, 3);
    colourBufferID = bindBufferToAttribute(colours, 1, 3);
    textureBufferID = bindBufferToAttribute(textureCoords, 2, 2);

    /* Unbind VAO and VBO's */
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::~Mesh() {
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vaoID);
    
    glDeleteBuffers(1, &indexBufferID);
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteBuffers(1, &colourBufferID);
}

GLuint Mesh::bindBufferToAttribute(const vector<float>& data, int attribPointer, int attribSize) {
    GLuint vboId = createStaticVBO(data, GL_ARRAY_BUFFER);
    glVertexAttribPointer(attribPointer, attribSize, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
    glEnableVertexAttribArray(attribPointer);
    return vboId;
}

template <typename T>
GLuint Mesh::createStaticVBO(const vector<T>& data, GLenum type) {
    GLuint vboId;
    glGenBuffers(1, &vboId);
    glBindBuffer(type, vboId);
    glBufferData(type, ((int) data.size()) * sizeof(data[0]), &data[0], GL_STATIC_DRAW);
    return vboId;
}

void Mesh::render() {
    glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, (GLvoid*) 0);
}
