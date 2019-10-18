//
// Created by Devin Gendron on 2019-10-18.
//

#include "Player.h"

// Constructor
Player::Player()
{

}

//Player();             // Overload Constructor

// Destructor
Player::~Player()
{
    SetName("");
}

// Player Functions

// Move Up
void Player::MoveUp()
{
    int move = (GetLocY() + 1);
    SetLocY(move);
}

// Move Down
void Player::MoveDown()
{
    int move = (GetLocY() - 1);
    SetLocY(move);
}

// Move Left
void Player::MoveLeft()
{
    int move = (GetLocX() - 1);
    SetLocX(move);
}

// Move Right
void Player::MoveRight()
{
    int move = (GetLocX() + 1);
    SetLocX(move);
}

// Getters

// Get X Location of Player
int Player::GetLocX()
{
    return LocX;
}

// Get Y Location of Player
int Player::GetLocY()
{
    return LocY;
}

std::string Player::GetName()
{
    return Name;
}
//getsocket?

// Setters

// Set X Location
void Player::SetLocX(int x)
{
    LocX = x;
}

// Set Y Location
void Player::SetLocY(int y)
{
    LocY = y;
}

// Set Player Name
void Player::SetName(std::string PlayerName)
{
    Name = PlayerName;
}

//set socket?
