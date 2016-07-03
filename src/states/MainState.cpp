#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

#include <states/MainState.h>
#include <Constants.h>

MainState::MainState() : GameState("Main") { }

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

    vector<float> textureCoords = {
        0, 0,
        0, 1,
        1, 1,
        1, 0
    };

    vector<int> indices = {
        0, 1, 3,
        3, 1, 2
    };

    mesh = new Mesh(vertices, colours, textureCoords, indices);
    camera = new Camera(4.0f/3, vec3(0, 0, 5), 0, M_PI);
    shader= new ShaderProgram("assets/shaders/SimpleVertexShader.txt","assets/shaders/SimpleFragmentShader.txt");

    texture = new Texture("assets/wall.png");
    textureID = glGetUniformLocation(shader->getProgramID(), "textureSampler");
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


void MainState::keyCallback(int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS) return;

    float x = 0,y = 0,z = 0;
    if (key == GLFW_KEY_Q) x++;
    if (key == GLFW_KEY_W) x--;
    if (key == GLFW_KEY_A) y++;
    if (key == GLFW_KEY_S) y--;
    if (key == GLFW_KEY_Z) z++;
    if (key == GLFW_KEY_X) z--;


    if (x || y || z) {
        camera->translate(x, y, z);
    }

    float v = 0, h = 0;
    if (key == GLFW_KEY_O) v++;
    if (key == GLFW_KEY_P) v--;
    if (key == GLFW_KEY_K) h++;
    if (key == GLFW_KEY_L) h--;

    if (v || h) {
        camera->rotate(v*0.05f*M_PI, h*0.05f*M_PI);
    }

}

void MainState::render(float delta) {

    logger.log(delta);

    shader->bind();
    texture->bind();
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &camera->getProjectionViewMatrix()[0][0]);
    glUniform1i(textureID, 0);

    mesh->render();

    texture->unbind();
    shader->unbind();
}
