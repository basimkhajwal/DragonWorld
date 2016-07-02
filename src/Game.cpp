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
#include <graphics/Window.h>
#include <Camera.h>
#include <Constants.h>
#include <states/GameState.h>
#include <Game.h>

namespace game {

    /* Anonymous namespace pattern */
    namespace {
        
        Window *window = nullptr;
        GameState* state = nullptr;

        bool lostFocus = false;

        void keyCallback(GLFWwindow* w, int key, int scancode, int action, int mode) {
            state->keyCallback(key, scancode, action, mode);
        }

        void resizeCallback(GLFWwindow* w, int width, int height) {
            printf("WIDNOW:\t\tResized to %d x %d\n", width, height);
            state->resize(width, height);
            glViewport(0, 0, width, height);
        }

        void focusCallback(GLFWwindow* w, int focused) {
            if (!focused) {
                printf("WINDOW:\t\tLost focus\n");
                state->pause();
                lostFocus = true;
            } else {
                printf("WINDOW:\t\tGained focus\n");
                state->resume();
                lostFocus = false;
            }
        }

        void initGame() {
            /* Create window and attach listeners */
            window = new Window(constants::SCREEN_TITLE, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT);
            glfwSetKeyCallback(window->getWindow(), keyCallback);
            glfwSetFramebufferSizeCallback(window->getWindow(), resizeCallback);
            glfwSetWindowFocusCallback(window->getWindow(), focusCallback);

            /* Enable V-Sync to fix FPS to monitor refresh rate */
            glfwSwapInterval(1);

            /* Set OpenGL flags */
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_CULL_FACE);
            glDepthFunc(GL_LESS);

            /* Set clear colour */
            glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
        }

        void mainLoop() {

            double startTime, delta, currentTime;
            startTime = glfwGetTime();

            while (!window->isClosed()) {
                currentTime = glfwGetTime();
                delta = currentTime - startTime;
                startTime = currentTime;

                while (lostFocus) {
                    printf("WINDOW:\t\tPausing until focus resumed\n");
                    glfwWaitEvents();
                    
                    /* Reset time to prevent huge delta */
                    startTime = glfwGetTime();
                }

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

        destroyGame();
        return 0;
    }

    /* TODO: fix destructor problem with state*/
    void setState(GameState* nextState) {
        if (state != nullptr) delete state;
        state = nextState;
        state->init();
    }

    GameState* getState() { return state; }
}

