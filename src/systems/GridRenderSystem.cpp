#include <systems/GridRenderSystem.h>

GridRenderSystem::GridRenderSystem(int width, int height, const char* grid, Mesh* wallMesh, GLuint matrixID) {

    this->wallMesh = wallMesh;
    this->matrixID = matrixID;

    vector<mat4> rotationMatrices(4);
    rotationMatrices[0] = mat4();
    rotationMatrices[1] = rotate(mat4(), pi<float>()/2.0f, vec3(0, 1, 0));
    rotationMatrices[2] = translate(mat4(), vec3(0, 0, -1));
    rotationMatrices[3] = translate(mat4(), vec3(1, 0, 0)) * rotationMatrices[1];

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            if (grid[j*width+i] != '1') continue;

            mat4 transformMatrix = translate(mat4(), vec3(i, 0, -j));
            for (mat4& m: rotationMatrices) modelMatrices.push_back(transformMatrix * m);
        }
    }
}

GridRenderSystem::~GridRenderSystem() { }

void GridRenderSystem::render(float delta, const mat4& projectionViewMatrix) {

    for (mat4& m: modelMatrices) {
        mat4 res = projectionViewMatrix * m;
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &res[0][0]);

        wallMesh->render();
    }
}
