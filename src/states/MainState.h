#pragma once

#include <Camera.h>
#include <states/GameState.h>

#include <graphics/Texture.h>
#include <graphics/Mesh.h>
#include <graphics/ShaderProgram.h>

class MainState : public GameState {

    Mesh* mesh;
    Camera* camera;
    ShaderProgram* shader;
    GLuint matrixID, textureID;
    Texture* texture;

    float currentTime = 0;
    int framesCounted = 0;

public:

    MainState();
    ~MainState();

    void init();
    void render(float delta);

    void resize(int width, int height);
    void keyCallback(int key, int scancode, int action, int mods);

    Camera* getCamera() { return camera; }
};
