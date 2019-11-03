#define SERVER_PORT 88432

#include <iostream>
#include <stdio.h>
#include <ncurses.h>

#include "headers/GameControllerServer.h"

int main() {

  initscr();

  GameControllerServer gs;

  gs.MainGameLoop();

  return 0;
}