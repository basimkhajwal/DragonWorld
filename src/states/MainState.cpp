#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

#include <states/MainState.h>
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


void MainState::keyCallback(int key, int action, int scancode, int mods) {
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

    currentTime += delta;
    framesCounted++;

    if (currentTime >= 1) {
        currentTime = 0;
        printf("FPS-LOG:\t%d\n", framesCounted);
        framesCounted = 0;
    }

    shader->bind();
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &camera->getProjectionViewMatrix()[0][0]);
    mesh->render();
    shader->unbind();
}