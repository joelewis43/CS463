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
#include "matrix.h"
#include "window.h"

class GameControllerClient {
    private:
        clientSocket ClientSocket;                  // Client to Server Connection
        Player       player;                        // Player Object
        bool         QuitGame = false;              // Quit Game
        bool         ServerConnected = false;       // Server Connection
        bool         GameOver = false;              // Game Over
        int          ControlType = 0;               // 1 = Up/Down, 2 = Left/Right
        GameMatrix   board;                         // Game Board
        bool         Collision = false;             // Collision Occurred?
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
        void ServerConnection();                    // Checks for Server Connection
        void MovePlayer();                          // Update Player Location
        void UpdateGame(WINDOW *window);            // Update Game
        void DisplayScore();                        // Display the final score
        void CheckCollisions();                     // Checks if Server Sent Collision True
        void ReplayMenu(bool&);                          // Replay Menu

        // Getters
        //std::string getPlayerName();
        bool    GetQuitGame();                      // Get QuitGame?
        Player  GetPlayerObject();                  // Get Player Object
        bool    GetServerConnection();              // Get Server Connection
        bool    GetGameOver();                      // Get Game Over
        bool    GetCollisionOccur();                // Get Collision

        // Setters
        //void setPlayerName(std::string);
        void    SetQuitGame(bool);                  // Set QuitGame
        void    SetServerConnection(bool);          // Set Server Connection
        void    SetGameOver(bool);                  // Set Game Over
        void    SetCollision(bool);                 // Set Collision
};


#endif //CS463_GAMECONTROLLERCLIENT_H
