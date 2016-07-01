#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <states/GameState.h>

namespace game {

    /* The game entry point */
    int runGame(GameState* startState);

    /* Set the current state of the game */
    void setState(GameState* nextState);

    /* Get the current state of the game */
    GameState* getState();
}
