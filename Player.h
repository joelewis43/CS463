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
    Player();               // Constructor
    //Player();             // Overload Constructor
    ~Player();              // Destructor

    // Player Functions
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

    // Getters
    int GetLocX();
    int GetLocY();
    std::string GetName();
    //getsocket?

    // Setters
    void SetLocX(int);
    void SetLocY(int);
    void SetName(std::string);
    //set socket?
};


#endif //CS463_PLAYER_H
