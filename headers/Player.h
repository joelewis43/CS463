//
// Created by Devin Gendron on 2019-10-18.
//

#ifndef CS463_PLAYER_H
#define CS463_PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <stdlib.h>

class Player {
private:
    // socket?
    int LocX = 0;
    int LocY = 0;
    std::string Name = "";

protected:
public:
    // Constructor/Destructor
    Player();                   // Constructor
    ~Player();                  // Destructor

    // Player Functions
    void MoveUp();              // Player Moves Up
    void MoveDown();            // Player Moves Down
    void MoveLeft();            // Player Moves Left
    void MoveRight();           // Player Moves Right

    // Getters
    int GetLocX();              // Gets Player's X Location
    int GetLocY();              // Gets Player's Y Location
    std::string GetName();      // Gets Player's Name
    //getsocket?

    // Setters
    void SetLocX(int);          // Sets Player's X Location
    void SetLocY(int);          // Sets Player's Y Location
    void SetName(std::string);  // Sets Player's Name
    //set socket?
};


#endif //CS463_PLAYER_H
