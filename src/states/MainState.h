#pragma once

#include <Camera.h>
#include <states/GameState.h>

#include <graphics/Texture.h>
#include <graphics/Mesh.h>
#include <graphics/ShaderProgram.h>
#include <utils/FPSLogger.h>

class MainState : public GameState {

    Mesh* mesh;
    Texture* texture;

    Camera* camera;
    ShaderProgram* shader;

    FPSLogger logger;

    GLuint matrixID, textureID;

public:

    MainState();
    ~MainState();

    void init();
    void render(float delta);

    void resize(int width, int height);
    void keyCallback(int key, int scancode, int action, int mods);

    Camera* getCamera() { return camera; }
};
