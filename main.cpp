#include "GameControllerServer.h"

#include <ncurses.h>

int main()
{
    initscr();

    GameController game;

    game.MainGameLoop();

    return 0;
}