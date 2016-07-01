#// Include standard headers
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
#include <GameState.h>
#include <Game.h>

namespace game {

    /* Anonymous namespace pattern */
    namespace {
        
        Window *window = nullptr;
        GameState* state = nullptr;

        void keyCallback(GLFWwindow* w, int key, int scancode, int action, int mode) {
            state->keyCallback(key, scancode, action, mode);
        }

        void resizeCallback(GLFWwindow* window, int width, int height) {
            state->resize(width, height);
            glViewport(0, 0, width, height);
        }

        void initGame() {
            /* Create window and attach listeners */
            window = new Window(constants::SCREEN_TITLE, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT);
            glfwSetKeyCallback(window->getWindow(), keyCallback);
            glfwSetFramebufferSizeCallback(window->getWindow(), resizeCallback);

            glfwSwapInterval(1);

            /* Set OpenGL flags */
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glDepthFunc(GL_LESS);
            glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
        }

        void mainLoop() {

            double startTime, delta, currentTime;
            startTime = glfwGetTime();

            while (!window->isClosed()) {
                currentTime = glfwGetTime();
                delta = currentTime - startTime;
                startTime = currentTime;

                window->update();
                window->clear();
                state->render(delta);
            }
        }

        void destroyGame() {
            delete state;
            delete window;
        }
    }

    int runGame(GameState* startState) {
        initGame();
        setState(startState);

        mainLoop();

        return 0;
    }

    void setState(GameState* nextState) {
        if (state != nullptr) delete state;
        state = nextState;
        state->init();
    }

    GameState* getState() { return state; }
}

