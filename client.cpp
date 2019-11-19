#define SERVER_PORT 88432

#include <iostream>
#include <stdio.h>

#include "headers/GameControllerClient.h"

int main() {

    GameControllerClient gc;

    gc.MainGameLoop();

    return 0;
}