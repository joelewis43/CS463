#define SERVER_PORT 88432

#include <iostream>
#include <stdio.h>
#include <ncurses.h>

#include "headers/GameControllerServer.h"

int main() {

  srand(time(NULL));

  initscr();

  GameControllerServer gs;

  gs.MainGameLoop();

  return 0;
}