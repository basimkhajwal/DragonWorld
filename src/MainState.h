#pragma once

#include <GameState.h>
#include <Mesh.h>
#include <Camera.h>
#include <ShaderProgram.h>

class MainState : public GameState {

    Mesh* mesh;
    Camera* camera;
    ShaderProgram* shader;
    GLuint matrixID;

    float currentTime = 0;
    int framesCounted = 0;

public:

    MainState();
    ~MainState();

    void init();
    void render(float delta);

    void resize(int width, int height);
    void keyCallback(int key, int action, int scancode, int mods);

    Camera* getCamera() { return camera; }
};
