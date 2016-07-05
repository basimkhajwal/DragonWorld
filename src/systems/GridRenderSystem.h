#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <graphics/Mesh.h>
#include <graphics/ShaderProgram.h>

class GridRenderSystem {

    Mesh *wallMesh;
    vector<mat4> modelMatrices;
    GLuint matrixID;

public:

    GridRenderSystem(int width, int height, const char* grid, Mesh* wallMesh, GLuint matrixID);
    ~GridRenderSystem();

    void render(float delta, const mat4& projectionViewMatrix);
};
