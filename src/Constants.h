/*
 * Constants for Dungeon Warrior
 * */
#pragma once

#include <glm/glm.hpp>
using namespace glm;

/* Use namespace to make it explicit */
namespace constants {
    
    // Screen constants
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const char* const SCREEN_TITLE = "Dungeon Warrior";

    // Rendering constants
    const float FOV = 60;
    const float NEAR = 0.1f;
    const float FAR = 100;
    const vec3 UP = vec3(0, 1, 0);
}
