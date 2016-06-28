// Include standard headers
#include <cstdio>
#include <cmath>
#include <cstdlib>
using namespace std;

// Include GLEW and GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//GLM library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

// Project headers
#include <Window.h>
#include <Camera.h>
#include <Constants.h>
#include <MainState.h>

MainState state = MainState();

void keyCallback(GLFWwindow* w, int key, int scancode, int action, int mode) {

    Camera* camera = state.getCamera();

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

void resizeCallback(GLFWwindow* window, int width, int height) {
    state.resize(width, height);
    glViewport(0, 0, width, height);
}

int main( void ) {

    Window window = Window(constants::SCREEN_TITLE, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT);
    glfwSetKeyCallback(window.getWindow(), keyCallback);
    glfwSetFramebufferSizeCallback(window.getWindow(), resizeCallback);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

    state.init();

    while (!window.isClosed()) {
        window.clear();
        state.render(0);
        window.update();
    }

    return 0;
}
