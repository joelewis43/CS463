//
// Created by Devin Gendron on 2019-10-18.
//

#include "GameController.h"
#include "Player.h"

// Constructor/Destructor

// Constructor
GameController::GameController()
{

}

//GameController::GameController();             // Overload Constructor
GameController::~GameController()
{

}// Destructor

// GameController Functions

// Main Game Loop
void GameController::MainGameLoop()
{
    // Clear Screen
    std::cout << "\033[2J\033[1;1H";

    // Menus
    MainMenu();

    if(GetQuitGame() == false)
    {
        // Display Game Count Down
        CountDownScreen();

        // Begin Game
        /*while(GetGameOver() != true)
        {

        }*/
    }
    else
    {
        // Quit
        // Clear Screen
        std::cout << "\033[2J\033[1;1H";
        std::cout << "Thanks for playing!" << std::endl;
        sleep(1);
    }
}

// Main Menu
void GameController::MainMenu()
{
    int selection = -1;

    while(selection == -1)
    {
        std::cout << "SpaceRunner" << std::endl;
        std::cout << std::endl;
        std::cout << "1. Play" << std::endl;
        std::cout << "2. LeaderBoard" << std::endl;
        std::cout << "3. Exit Game" << std::endl;
        std::cout << std::endl;
        std::cout << "*Enter your menu selection and press Enter" << std::endl;
        std::cout << std::endl;
        std::cout << "Selection: ";
        std::cin >> selection;

        if(selection > 0 && selection < 4)
        {
            switch(selection)
            {
                case 1:
                    // Play Game - Set Name
                    NameMenu();
                    AwaitingPlayer();
                    ControlSelection();
                    break;
                case 2:
                    // Leader Boards
                    LeaderBoard();
                    break;
                case 3:
                    // Quit Game
                    SetQuitGame(true);
                    break;
                default:
                    std::cout << "Something Went Wrong..." << std::endl;
                    break;
            }
        }
        else
        {
            std::cout << std::endl;
            std::cout << "Please Select 1, 2, or 3." << std::endl;
            selection = -1;
        }

        if (selection == 2)
        {
            // Clear Screen and Let Menu Appear Again
            std::cout << "\033[2J\033[1;1H";
            selection = -1;
        }
    }
}

// LeaderBoard Menu
void GameController::LeaderBoard()
{
    // Open File and View Leader Boards
    // Clear Screen
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Leader Board Function" << std::endl;
    sleep(2);
}

// Select Player Name
void GameController::NameMenu()
{
    std::string name = "";

    // check if name exists
    if(player.GetName() == "")
    {
        // Display Menu to Enter Name
        std::cout << "Enter Your Name" << std::endl;
        std::cout << std::endl;
        std::cout << "3-20 Alphanumeric Characters Required" << std::endl;
        std::cout << "Press Enter to Continue" << std::endl;
        std::cout << std::endl;
        std::cout << "Name: ";
        std::cin >> name;

        // Set Name in Player Object
        player.SetName(name);
    }
    else
    {
        // A Player Name Exists - overwrite or quit?
        std::cout << "Please note - Your current name: " << player.GetName() << " will be overwritten." << std::endl;
        std::cout << "Enter Your Name" << std::endl;
        std::cout << std::endl;
        std::cout << "3-20 Alphanumeric Characters Required" << std::endl;
        std::cout << "Press Enter to Continue" << std::endl;
        std::cout << std::endl;
        std::cout << "Name: ";
        std::cin >> name;
    }
}

// Await Player Server Connection
void GameController::AwaitingPlayer()
{
    bool PlayerJoined = false;

    std::cout << "\033[2J\033[1;1H";
    std::cout << "Waiting for your partner..." << std::endl;
    std::cout << "Thank you for your patience" << std::endl;
    /*while(PlayerJoined == false)
    {
        // Check if Player on Server
        if(true)
        {
            PlayerJoined = true;
        }
    }*/
    sleep(2);
}

// Player Selects Controls
void GameController::ControlSelection()
{
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Player Controls" << std::endl;
    std::cout << "Up/Down: " << /*Rand.layer*/ std::endl;
    std::cout << "Left/Right: " << /*Rand.Player*/ std::endl;
    sleep(5);
}

// Displayed Before Game Starts
void GameController::CountDownScreen()
{
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Game Starting in..." << std::endl;

    std::cout << "3" << std::endl;
    sleep(1);
    std::cout << "\r2" << std::endl;
    sleep(1);
    std::cout << "\r1" << std::endl;
    sleep(1);
    std::cout << "\033[2J\033[1;1H";
}

// Displayed After Player Loses
void GameController::GameOverMenu()
{
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Game Over!" << std::endl;
    std::cout << "Score: " << GetScore() << std::endl;
    std::cout << "Play Game? (y/n)" << std::endl;
}

// Checks for Server Connection
bool GameController::ServerConnection()
{

}

// Checks for Player/Object Collisions
bool GameController::CheckCollisions()
{

}

// Create Special Game Events
void GameController::CreateSpecialEvent()
{

}

// Update Player Location
void GameController::MovePlayer()
{

}

// Update Object Locations
void GameController::MoveObjects()
{

}

// Move Environment
void GameController::MoveEnvironment()
{

}

// Sets New Environment
void GameController::UpdateEnvironment()
{

}

// Update Game State
void GameController::UpdateGame()
{

}

// Send Map to Client/Server
void GameController::SendMap()
{

}

// Getters

// Get Score
int GameController::GetScore()
{
    return Score;
}

// Get GameOver Bool
bool GameController::GetGameOver()
{
    return GameOver;
}

// Get IsRunning Bool
bool GameController::GetIsRunning()
{
    return IsRunning;
}

// Get GameQuit bool
bool GameController::GetQuitGame()
{
    return QuitGame;
}

Player GameController::GetPlayerObject()
{
    return player;
}
//GameBoard GameController::GetGameBoard();

// Setters

// Set Score
void GameController::SetScore(int updateScore)
{
    Score = updateScore;
}

// Set GameOver Bool
void GameController::SetGameOver(bool GameOverState)
{
    GameOver = GameOverState;
}

// Set IsRunning Bool()
void GameController::SetIsRunning(bool IsRunningState)
{
    IsRunning = IsRunningState;
}

// Set GameQuit bool
void GameController::SetQuitGame(bool QuitGameSet)
{
    QuitGame = QuitGameSet;
}

//GameBoard GameController::SetGameBoard();