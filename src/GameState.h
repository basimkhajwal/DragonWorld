#pragma once

class GameState {

    const char* name;

public:

    GameState(char const* name);
    ~GameState();

    virtual void init();
    virtual void resize(int width, int height);
    virtual void render(float delta) = 0;

    const char* getName() const { return name; }
};
