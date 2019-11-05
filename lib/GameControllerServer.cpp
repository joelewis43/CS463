//
// Created by Devin Gendron on 2019-10-18.
//

#include "../headers/GameControllerServer.h"
#include "../headers/Player.h"
#include "../headers/serverSocket.h"

////////////////////////////////
///                          ///
/// Constructors/Destructors ///
///                          ///
////////////////////////////////

// Constructor
GameControllerServer::GameControllerServer() : ServerSocket(88432), player1(), player2()
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

    // Wait for two clients to connect
    std::cout << "Waiting for clients ..." << std::endl;
    ServerSocket.waitForClients();

    while(1)
    {
        // Clients in Menu
        int ReadyCounter = 0;

        char buffer1[MAX_BYTES];
        char buffer2[MAX_BYTES];
        memset(buffer1, '\0', MAX_BYTES);
        memset(buffer2, '\0', MAX_BYTES);

        // Loop Until Both Players Indicate They Are Ready to Play
        while(ReadyCounter != 2)
        {
            // Receive Client 1 Signal
            ServerSocket.receive1(buffer1);

            if(strcmp( buffer1, "? leaderboard") == 0)
            {
                LeaderBoard(1);
                memset(buffer1, '\0', MAX_BYTES);
            }
            else if(strcmp( buffer1, "! pReady") == 0)
            {
                ReadyCounter++;
            }

            // Receive Client 2 Signal
            ServerSocket.receive2(buffer2);

            if(strcmp( buffer2, "? leaderboard") == 0)
            {
                LeaderBoard(2);
                memset(buffer2, '\0', MAX_BYTES);
            }
            else if(strcmp( buffer1, "! pReady") == 0)
            {
                ReadyCounter++;
            }
        }

        // Wait for two clients to connect
        //std::cout << "Waiting for clients ..." << std::endl;
        //ServerSocket.waitForClients();

        // Get Players Names
        NameMenu();

        // Tell Clients connections have been made
        AwaitingPlayer();

        // Tell Clients to Start Countdowns
        CountDownScreen();

        // Begin Timer
        start = std::clock();

        // Begin Game
        while(!GetGameOver())
        {
            // Update Game
            UpdateGame();
        }
    }
}

// LeaderBoard Menu
void GameControllerServer::LeaderBoard(int player)
{
    // Open File and View Leader Boards
    // Clear Screen
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Leader Board Function" << std::endl;
    sleep(2);

    std::string filePath = "./data/LeaderBoards.txt";
    std::ifstream fp;

    fp.open(filePath);

    if (!fp)
    {
        std::cout << "Failed to Retrieve LeaderBoards" << std::endl;
    }
    else
    {
        std::cout << "About to send LB" << std::endl;
        std::string file;
        std::string line = "";
        while (!fp.eof())
        {
            getline(fp, line);
            std::cout << line << std::endl;
            file.append(line);
        }
        fp.close();

        if(player == 1)
        {
            ServerSocket.deliver1(file.c_str());
        }
        else
        {
            ServerSocket.deliver2(file.c_str());
        }
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
    char name1[6];
    char name2[6];
    std::string player_a = "";
    std::string player_b = "";
    int NameSetCounter = 0;

    char buffer1[MAX_BYTES];
    char buffer2[MAX_BYTES];
    memset(buffer1, '\0', MAX_BYTES);
    memset(buffer2, '\0', MAX_BYTES);

    // Loop Until Both Players Indicate Their Names Are Set
    while(NameSetCounter != 2)
    {
        // Receive Client 1 Signal
        ServerSocket.receive1(buffer1);

        if(strcmp( buffer1, "! name"))
        {
            memset(buffer1, '\0', MAX_BYTES);

            // Get Name
            ServerSocket.receive1(name1);

            // Set Name
            player_a = name1;
        }
        else if(strcmp( buffer1, "! pReady"))
        {
            NameSetCounter++;
        }

        // Receive Client 2 Signal
        ServerSocket.receive2(buffer2);

        if(strcmp( buffer2, "! name"))
        {
            memset(buffer2, '\0', MAX_BYTES);

            // Get Name
            ServerSocket.receive1(name2);

            // Set Name
            player_b = name2;
        }
        else if(strcmp( buffer1, "! pReady"))
        {
            NameSetCounter++;
        }
    }

    // Concatenate Names
    std::string name = player_a + player_b;
    player1.SetName(player_a);
    player2.SetName(player_b);
    player1and2.SetName(name);
}

// Await Player Server Connection
void GameControllerServer::AwaitingPlayer()
{
    // Deliver message that both clients have connected
    const char* msg = "Matchmaking Completed!";
    ServerSocket.deliver(msg);
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

    // Send Command to Clients to indicate control types
    char msg1[64];
    sprintf(msg1, "controls %d", player1Controls);

    char msg2[64];
    sprintf(msg2, "controls %d", player2Controls);

    ServerSocket.deliver(msg1, msg2);

    sleep(1);
}

// Displayed Before Game Starts
void GameControllerServer::CountDownScreen()
{
    // Tell Clients to start countdowns
    const char* msg = "countdown";
    ServerSocket.deliver(msg);
    //// OR
    ///// Have countdown screen in Tevin's game env
}

// Checks for Player/Object Collisions
bool GameControllerServer::CheckCollisions()
{
    // Logic For Collision

    // Set Collision to True if True
    //SetCollisionOccur(true);

    // tell clients
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

    // continue
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
    if(ServerSocket.getConnection())
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

Player GameControllerServer::GetPlayer1()
{
    return player1;
}

Player GameControllerServer::GetPlayer2()
{
    return player2;
}

Player GameControllerServer::GetPlayer1and2()
{
    return player1and2;
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