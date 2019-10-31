#define SERVER_PORT 88432

#include <iostream>
#include <stdio.h>
#include <ncurses.h>

#include "headers/GameControllerClient.h"
#include "headers/GameControllerServer.h"
#include "headers/Player.h"
#include "headers/clientSocket.h"
#include "headers/serverSocket.h"

int main() {
  
  initscr();

  GameControllerServer game;

  game.MainGameLoop();

	std::cout << "APP" << std::endl;

	return 0;
}