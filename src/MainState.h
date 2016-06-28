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

public:

    MainState();
    ~MainState();

    void init();
    void resize(int width, int height);
    void render(float delta);

    Camera* getCamera() { return camera; }
};
