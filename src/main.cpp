#include <Game.h>
#include <states/MainState.h>

int main( void ) {
    return game::runGame(new MainState());
}
