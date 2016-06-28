#include <cstdio>
using namespace std;

#include <GameState.h>

GameState::GameState(const char* name) : name(name) { }

GameState::~GameState() {
    printf("GAME-STATE:\tDisposing state %s\n", name);
}

void GameState::init() {
    printf("GAME-STATE:\tInitialising state %s\n", name);
}

void GameState::resize(int width, int height) {
    printf("GAME-STATE:\tResizing state %s to %d x %d\n", name, width, height);
}
