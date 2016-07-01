#pragma once

class GameState {

    const char* name;

public:

    GameState(char const* name);
    virtual ~GameState();

    virtual void init();
    virtual void render(float delta) = 0;

    /* Listener functions */
    virtual void resize(int width, int height);
    virtual void keyCallback(int key, int action, int scancode, int mods) {  }
    
    const char* getName() const { return name; }
};
