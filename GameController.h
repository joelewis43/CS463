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

class GameController {
    private:
        // GameBoard GameBoard;         // Game Board Object
        // Player Player;               // Player Object
        int     Score = 0;              // Score
        bool    IsRunning = false;      // isRunning Boolean (Server)
        bool    GameOver = false;       // GameOver?
        bool    QuitGame = false;       // player Quit?
        // Timer Settings
    protected:
    public:
        // Constructor/Destructor
        GameController();               // Constructor
        //GameController();             // Overload Constructor
        ~GameController();              // Destructor

        // GameController Functions
        void MainGameLoop();            // Main Game Loop
        void MainMenu();                // Main Menu
        void LeaderBoard();             // LeaderBoard Menu
        void NameMenu();                // Select Player Name
        void AwaitingPlayer();          // Await Player Server Connection
        void ControlSelection();        // Player Selects Controls
        void CountDownScreen();         // Displayed Before Game Starts
        void GameOverMenu();            // Displayed After Player Loses
        bool ServerConnection();        // Checks for Server Connection
        bool CheckCollisions();         // Checks for Player/Object Collisions
        void CreateSpecialEvent();      // Create Special Game Events
        void MovePlayer();              // Update Player Location
        void MoveObjects();             // Update Object Locations
        void MoveEnvironment();         // Move Environment
        void UpdateEnvironment();       // Sets New Environment
        void UpdateGame();              // Update Game State
        void SendMap();                 // Send Map to Client/Server

        // Getters
        int  GetScore();                // Get Player Score
        bool GetGameOver();             // Get GameOver?
        bool GetIsRunning();            // Get IsRunning?
        bool GetQuitGame();             // Get QuitGame?
        //Player GetPlayerObject();
        //GameBoard GetGameBoard();

        // Setters
        void SetScore(int);             // Set Score
        void SetGameOver(bool);         // Set GameOver
        void SetIsRunning(bool);        // Set IsRunning
        void SetQuitGame(bool);         // Set QuitGame
        //Player SetPlayerObject();
        //GameBoard SetGameBoard();

};


#endif //CS463_GAMECONTROLLER_H
