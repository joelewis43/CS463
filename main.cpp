#include "headers/GameControllerServer.h"

#include <ncurses.h>

int main()
{
    initscr();

    GameControllerServer game;

    game.MainGameLoop();

    return 0;
}