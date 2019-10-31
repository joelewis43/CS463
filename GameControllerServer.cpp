//
// Created by Devin Gendron on 2019-10-18.
//

#include "GameControllerServer.h"
#include "Player.h"
#include "serverSocket.h"

////////////////////////////////
///                          ///
/// Constructors/Destructors ///
///                          ///
////////////////////////////////

// Constructor
GameControllerServer::GameControllerServer()
{
    // Set Timer Settings Here?
}

// Destructor
GameControllerServer::~GameControllerServer()
{


}

////////////////////////////////
///                          ///
/// GameController Functions ///
///                          ///
////////////////////////////////

// Main Game Loop
void GameControllerServer::MainGameLoop()
{
    // Clear Screen
    std::cout << "\033[2J\033[1;1H";

    // Time Seed for Score Keeping
    srand(time(NULL));

    while(1)
    {
        // Setup Server
        serverSocket ServerSocket(PORT);

        // Connect to Clients ( 1 and 2 )
        ServerSocket.waitForClients();

        ////// Clients in Menu - Not Ready for Gameplay
        //////(Call For Leaderboards here)

        // Tell Clients connections have been made
        AwaitingPlayer(serverSocket ServerSocket);

        // Tell Clients to Start Countdowns
        CountDownScreen(serverSocket ServerSocket);

        // Begin Timer
        start = std::clock();

        // Begin Game
        while(GetGameOver() != true)                        ////////Server connection
        {
            // Update Game
            UpdateGame(serverSocket ServerSocket);
        }
    }
}

// LeaderBoard Menu
void GameControllerServer::LeaderBoard(serverSocket ServerSocket)
{
    // Open File and View Leader Boards
    // Clear Screen
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Leader Board Function" << std::endl;
    sleep(2);

    std::string filePath = "LeaderBoards.txt";
    std::ifstream file;

    file.open(filePath);

    if (!file)
    {
        std::cout << "Error Saving Score" << std::endl;
    }
    else
    {
        std::string line = "";
        while (!file.eof())
        {
            getline(file, line);
            std::cout << line << std::endl;
            ////////////
            /////ServerSocket.deliver(line);
            ////////
        }
        file.close();
    }
}

// Sort Leader Board
void GameControllerServer::SortLeaderBoard(std::vector<ScoreOrganizer> &updateScores)
{
    int i, key, j;
    std::string keyName = "";
    for (i = 1; i < updateScores.size(); i++)
    {
        key = updateScores[i].score;
        keyName = updateScores[i].name;

        j = i - 1;

        while (j >= 0 && updateScores[j].score < key)
        {
            updateScores[j + 1] = updateScores[j];
            j = j - 1;
        }
        updateScores[j + 1].score = key;
        updateScores[j + 1].name = keyName;
    }
}

// Update Leader Board
void GameControllerServer::UpdateLeaderBoards()
{
    std::string filePath = "LeaderBoards.txt";
    std::ifstream file;

    std::vector<ScoreOrganizer> updateScores;

    file.open(filePath);

    if (!file)
    {
        std::cout << "Error Updating Scores" << std::endl;
    }
    else
    {
        // Read Scores into vector
        std::string line = "";
        std::string lineCatcher = "";
        int lineCounter = 0;
        std::string::size_type sz;

        while (!file.eof())
        {
            // Catch Headers to Skip
            if (lineCounter < 2)
            {
                getline(file, lineCatcher);
                lineCounter++;
            }
            else if (lineCounter >= 2)
            {
                ScoreOrganizer newScoreSet;
                getline(file, line);
                std::istringstream ss(line);
                while (ss)
                {
                    getline(ss, newScoreSet.name, '\t');
                    getline(ss, newScoreSet.scoreToBeFormatted, '\t');
                }
                // Format Score
                if (newScoreSet.name != "" && newScoreSet.scoreToBeFormatted != "")
                {
                    newScoreSet.score = std::stoi(newScoreSet.scoreToBeFormatted);
                    updateScores.push_back(newScoreSet);
                }
            }
        }

        // sort
        SortLeaderBoard(updateScores);

        file.close();
    }

    std::string filePathRewrite = "LeaderBoards.txt";
    std::ofstream fileRewrite;

    fileRewrite.open(filePath);

    if (!fileRewrite)
    {
        std::cout << "Error Saving Score" << std::endl;
    }
    else
    {
        // put back in file
        std::string header = "Space Runner High Scores";
        std::string tableHeader = "Name\tScore";
        fileRewrite << header << std::endl;
        fileRewrite << tableHeader << std::endl;

        //insert sorted scores
        for (int i = 0; i < updateScores.size(); i++)
        {
            fileRewrite << updateScores[i].name << '\t' << updateScores[i].score << std::endl;
        }
    }

    fileRewrite.close();
}

// Save Score
void GameControllerServer::SaveScore(std::string playerName, int score)
{
    std::string filePath = "LeaderBoards.txt";
    std::ofstream file;

    file.open(filePath, std::fstream::app);

    if (!file)
    {
        std::cout << "Error Saving Score" << std::endl;
    }
    else
    {
        // Enter Player Score
        file << playerName << "\t" << score << std::endl;

        file.close();

        // Sort Scores
        UpdateLeaderBoards();
    }
}

// Updates Score Based on Timer
void GameControllerServer::UpdateScore()
{
    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    timer = floor(((duration / 60.0) / 60.0) * 10000);
    Score = Score + (int)timer + 1;
}

// Select Player Name
void GameControllerServer::NameMenu()
{
    // Await Client

    // Receive Player 1 Name

    // Receive Player 2 Name

    // Concatenate

    // Continue
}

// Await Player Server Connection
void GameControllerServer::AwaitingPlayer()
{
    //std::cout << "\033[2J\033[1;1H";
    //std::cout << "Waiting for your partner..." << std::endl;
    //std::cout << "Thank you for your patience" << std::endl;
    //ServerSocket.deliver();
    sleep(1);
}

// Player Selects Controls
void GameControllerServer::ControlSelection()
{
    int player1Controls = 0;
    int player2Controls = 0;

    player1Controls = rand() % 2 + 1;

    // 1 = Up/Down
    // 2 = Left/Right

    if(player1Controls == 1)
    {
        player2Controls = 2;
    }
    else if(player1Controls == 2)
    {
        player2Controls = 1;
    }

    // Send Command to Clients
    //ServerSocket.deliver();
    sleep(1);
}

// Displayed Before Game Starts
void GameControllerServer::CountDownScreen()
{
    // Tell Clients to start countdowns
    //ServerSocket.deliver();
}

// Checks for Player/Object Collisions
bool GameControllerServer::CheckCollisions()
{
    // Logic For Collision

    // Set Collision to True if True
    //SetCollisionOccur(true);
}

// Create Special Game Events
void GameControllerServer::CreateSpecialEvent()
{

}

// Update Player Location
void GameControllerServer::MovePlayer()
{
    // Receive Data From Client

    // Update Player Location (X|Y)

    // Update Map
}

// Update Object Locations
void GameControllerServer::MoveObjects()
{

}

// Move Environment
void GameControllerServer::MoveEnvironment()
{

}

// Sets New Environment
void GameControllerServer::UpdateEnvironment()
{

}

// Send Map to Client/Server
void GameControllerServer::SendMap()
{

}

// Update Game State
void GameControllerServer::UpdateGame()
{
    // Check Server Connection
    if(ServerConnection() == true)
    {
        // Print Screen

        // Update Player
        MovePlayer();

        // Clear Screen
        std::cout << "\033[2J\033[1;1H";

        // Create Special Event
        CreateSpecialEvent();

        // Move Objects
        MoveObjects();

        // Update Environment
        //if(score > X)
        //    UpdateEnvironment();

        // Move Environment
        MoveEnvironment();

        // Check for Collisions
        CheckCollisions();

        // Update Score
        UpdateScore();

        // Send Map to Client
        SendMap();
    }
}

////////////////////////////////
///                          ///
///         Getters          ///
///                          ///
////////////////////////////////

// Get Score
int GameControllerServer::GetScore()
{
    return Score;
}

// Get GameOver Bool
bool GameControllerServer::GetGameOver()
{
    return GameOver;
}

// Get IsRunning Bool
bool GameControllerServer::GetIsRunning()
{
    return IsRunning;
}

// Get GameQuit bool
bool GameControllerServer::GetQuitGame()
{
    return QuitGame;
}

// Get Collision Bool
bool GameControllerServer::GetCollisionOccur()
{
    return Collision;
}

Player GameControllerServer::GetPlayerObject()
{
    return player;
}

//GameBoard GameControllerServer::GetGameBoard();

////////////////////////////////
///                          ///
///         Setters          ///
///                          ///
////////////////////////////////

// Set Score
void GameControllerServer::SetScore(int updateScore)
{
    Score = updateScore;
}

// Set GameOver Bool
void GameControllerServer::SetGameOver(bool GameOverState)
{
    GameOver = GameOverState;
}

// Set IsRunning Bool()
void GameControllerServer::SetIsRunning(bool IsRunningState)
{
    IsRunning = IsRunningState;
}

// Set GameQuit bool
void GameControllerServer::SetQuitGame(bool QuitGameSet)
{
    QuitGame = QuitGameSet;
}

// Get Collision Bool
void GameControllerServer::SetCollisionOccur(bool occurrence)
{
    Collision = occurrence;
}

//GameBoard GameControllerServer::SetGameBoard();