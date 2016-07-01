#include <graphics/Mesh.h>

#include <cstdio>

Mesh::Mesh(const vector<float>& vertices, const vector<float>& colours, const vector<int>& indices) {

    static int meshId = 0;
    printf("MESH:\t\tCreating new mesh id: %d\n", meshId++);

    /* Save vertex count and create a new VAO for this mesh */
    vertexCount = (int) indices.size();
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    /* Create the index buffer and the attribute buffers */
    indexBufferID = createIndexBuffer(indices);
    vertexBufferID = bindBufferToAttribute(vertices, 0, 3);
    colourBufferID = bindBufferToAttribute(colours, 1, 3);

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

    GLuint vboId;
    glGenBuffers(1, &vboId);

    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, ((int) data.size()) * sizeof(data[0]), &data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(attribPointer, attribSize, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
    glEnableVertexAttribArray(attribPointer);

    return vboId;
}

GLuint Mesh::createIndexBuffer(const vector<int>& indices) {

    GLuint vboId;
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ((int) indices.size()) * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
    
    return vboId;
}

void Mesh::render() {
    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, (GLvoid*) 0);
    glBindVertexArray(0);
}
