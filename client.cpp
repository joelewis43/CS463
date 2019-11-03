#define SERVER_PORT 88432

#include <iostream>
#include <stdio.h>
#include <ncurses.h>

#include "headers/GameControllerClient.h"

int main() {

    initscr();

    GameControllerClient gc;

    gc.MainGameLoop();

    return 0;
}