//
// Created by Devin Gendron on 2019-10-24.
//

#ifndef CS463_GAMECONTROLLERCLIENT_H
#define CS463_GAMECONTROLLERCLIENT_H

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <ctime>
#include <string>
#include <sys/types.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include "Player.h"
#include "clientSocket.h"
#include <ncurses.h>

const int PORT = 88432;
const char* IP = "";

class GameControllerClient {
    private:
        //clientSocket ClientSocket(IP, PORT);        // Client to Server Connection
        Player  player;                             // Player Object
        bool    QuitGame = false;                   // Quit Game
        bool    ServerConnected = false;            // Server Connection
        bool    GameOver = false;                   // Game Over
    protected:
    public:
        // Constructor/Destructor
        GameControllerClient();
        ~GameControllerClient();

        // Functions
        void MainGameLoop();                        // Main Game Loop
        void MainMenu();                            // Main Menu
        void LeaderBoard();                         // LeaderBoard Menu
        void NameMenu();                            // Select Player Name
        void AwaitingPlayer();                      // Await Player Server Connection
        void ControlSelection();                    // Player Selects Controls
        void CountDownScreen();                     // Displayed Before Game Starts
        void GameOverMenu();                        // Displayed After Player Loses
        bool ServerConnection();                    // Checks for Server Connection
        void MovePlayer();                          // Update Player Location
        void UpdateGame();                          // Update Game

        // Getters
        //std::string getPlayerName();
        bool    GetQuitGame();                      // Get QuitGame?
        Player  GetPlayerObject();                  // Get Player Object
        bool    GetServerConnection();              // Get Server Connection
        bool    GetGameOver();                      // Get Game Over

        // Setters
        //void setPlayerName(std::string);
        void    SetQuitGame(bool);                  // Set QuitGame
        void    SetServerConnection(bool);          // Set Server Connection
        void    SetGameOver(bool);                  // Set Game Over
};


#endif //CS463_GAMECONTROLLERCLIENT_H
