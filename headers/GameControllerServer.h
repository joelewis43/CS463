//
// Created by Devin Gendron on 2019-10-18.
//

#ifndef CS463_GAMECONTROLLER_H
#define CS463_GAMECONTROLLER_H

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
#include "serverSocket.h"
#include <ncurses.h>
#include <string.h>
#include "gameEnvironment.h"
#include "window.h"

//enum DIRECTION {UP, DOWN, LEFT, RIGHT};

struct ScoreOrganizer
{
    std::string name = "";
    std::string scoreToBeFormatted = "";
    int score = 0;
};

class GameControllerServer {
    private:
        // GameBoard GameBoard;                                 // Game Board Object
        GameEnvironment gameEnvironment;
        Player player1;
        Player player2;
        Player player1and2;
        int     Score = 0;                                      // Score
        bool    IsRunning = false;                              // isRunning Boolean (Server)
        bool    GameOver = false;                               // GameOver?
        bool    QuitGame = false;                               // player Quit?
        bool    Collision = false;                              // Collision Occurred
        serverSocket ServerSocket;                              // Server Socket
    protected:
    public:
        // Constructor/Destructor
        GameControllerServer();                                 // Constructor
        ~GameControllerServer();                                // Destructor

        // Prep Timer
        std::clock_t start;
        double duration = 0.0;
        float timer = 0.0;

        // GameController Functions
        void MainGameLoop();                                    // Main Game Loop
        void LeaderBoard(int);                                  // LeaderBoard Menu
        void SortLeaderBoard(std::vector<ScoreOrganizer>&);     // Sorts LeaderBoard
        void UpdateLeaderBoards();                              // Updates LeaderBoards
        void SaveScore(std::string, int);                       // Saves Current Game's Score
        void NameMenu();                                        // Select Player Name
        void AwaitingPlayer();                                  // Await Player Server Connection
        void ControlSelection();                                // Player Selects Controls
        void CountDownScreen();                                 // Displayed Before Game Starts
        void GameOverMenu();                                    // Displayed After Player Loses
        bool ServerConnection();                                // Checks for Server Connection
        void CheckCollisions();                                 // Checks for Player/Object Collisions
        void CreateSpecialEvent();                              // Create Special Game Events
        void MovePlayer();                                      // Update Player Location
        void MoveObjects();                                     // Update Object Locations
        void MoveEnvironment();                                 // Move Environment
        void UpdateEnvironment();                               // Sets New Environment
        void UpdateGame(double, float);                                      // Update Game State
        void UpdateScore(double, float);                                     // Update Game's Score
        void SendMap();                                         // Send Map to Client/Server

        // Getters
        int  GetScore();                                        // Get Player Score
        bool GetGameOver();                                     // Get GameOver?
        bool GetIsRunning();                                    // Get IsRunning?
        bool GetQuitGame();                                     // Get QuitGame?
        bool GetCollisionOccur();                               // Get Collision
        Player GetPlayer1();                                     // Get Player Object
        Player GetPlayer2();                                    // Get Player Object
        Player GetPlayer1and2();
        //GameBoard GetGameBoard();

        // Setters
        void SetScore(int);                                     // Set Score
        void SetGameOver(bool);                                 // Set GameOver
        void SetIsRunning(bool);                                // Set IsRunning
        void SetQuitGame(bool);                                 // Set QuitGame
        void SetCollisionOccur(bool);                           // Set Collision
        //GameBoard SetGameBoard();
};


#endif //CS463_GAMECONTROLLER_H
