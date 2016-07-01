#include <Game.h>
#include <MainState.h>

int main( void ) {
    return game::runGame(new MainState());
}
