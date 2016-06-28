#include <cmath>
#include <vector>
using namespace std;

#include <MainState.h>
#include <Constants.h>

MainState::MainState() : GameState("Main") {
}

void MainState::init() {
    GameState::init();
    vector<float> vertices = {
        -1, 1, 0,
        -1, -1, 0,
        1, -1, 0,
        1, 1, 0
    };

    vector<float> colours = {
        1, 0, 0,
        1, 0, 0,
        0, 1, 0,
        0, 1, 0
    };

    vector<int> indices = {
        0, 1, 3,
        3, 1, 2
    };

    mesh = new Mesh(vertices, colours, indices);
    camera = new Camera(4.0f/3, vec3(0, 0, 5), 0, M_PI);
    shader= new ShaderProgram("assets/shaders/SimpleVertexShader.txt","assets/shaders/SimpleFragmentShader.txt");
    matrixID = glGetUniformLocation(shader->getProgramID(), "mvp");
}

MainState::~MainState() {
    delete mesh;
    delete camera;
    delete shader;
}

void MainState::resize(int width, int height) {
    GameState::resize(width, height);
    camera->resize(width, height);
}

void MainState::render(float delta) {

    shader->bind();
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &camera->getProjectionViewMatrix()[0][0]);
    mesh->render();
    shader->unbind();
}
