//
// Created by Devin Gendron on 2019-10-18.
//

#include "../headers/GameControllerServer.h"
#include "../headers/Player.h"
#include "../headers/serverSocket.h"
#include "../headers/commands.h"

////////////////////////////////
///                          ///
/// Constructors/Destructors ///
///                          ///
////////////////////////////////

// Constructor
GameControllerServer::GameControllerServer() : ServerSocket(6235), player1(), player2(), gameEnvironment(CONTENT_HEIGHT, CONTENT_WIDTH, 1000)
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

    // Setup Timer
    std::clock_t start;
    double duration = 0.0;
    float timer = 0.0;

    // Wait for two clients to connect
    std::cout << "Waiting for clients ..." << std::endl;
    ServerSocket.waitForClients();

    while(1)
    {
        // Clients in Menu
        int ReadyPlayer1 = 0; // good movie
        int ReadyPlayer2 = 0; // the sequel?

        char buffer1[MAX_BYTES];
        char buffer2[MAX_BYTES];
        memset(buffer1, '\0', MAX_BYTES);
        memset(buffer2, '\0', MAX_BYTES);

        int bytes1 = 0;
        int bytes2 = 0;

        // Loop Until Both Players Indicate They Are Ready to Play
        while(!ReadyPlayer1 || !ReadyPlayer2)
        {

            // read from socket 1 if play is not yet ready
            if (!ReadyPlayer1)
            {
                // Receive Client 1 Signal
                bytes1 = ServerSocket.receive1(buffer1);

                if (bytes1) {
                    std::cout << buffer1 << std::endl;
                }

                if(strstr( buffer1, "? leaderboard"))
                {
                    LeaderBoard(1);
                    memset(buffer1, '\0', MAX_BYTES);
                }
                else if(strstr( buffer1, "! pReady"))
                {
                    std::cout << "Player 1 Ready ..." << std::endl;
                    ReadyPlayer1 = 1;
                    memset(buffer1, '\0', MAX_BYTES);
                }
            }

            if (!ReadyPlayer2)
            {
                // Receive Client 2 Signal
                bytes2 = ServerSocket.receive2(buffer2);

                if (bytes2) {
                    std::cout << buffer2 << std::endl;
                }

                if(strstr( buffer2, "? leaderboard"))
                {
                    LeaderBoard(2);
                    memset(buffer2, '\0', MAX_BYTES);
                }
                else if(strstr( buffer2, "! pReady"))
                {
                    std::cout << "Player 2 Ready ..." << std::endl;
                    ReadyPlayer2 = 1;
                    memset(buffer2, '\0', MAX_BYTES);
                }
            }
        }

        std::cout << "Getting Player Names ..." << std::endl;
        // Get Players Names
        AwaitingPlayer();
        NameMenu();

        std::cout << "Sending Players Ready Message ..." << std::endl;
        // Tell Clients connections have been made
        AwaitingPlayer();

        std::cout << "Tell Players their Controls..." << std::endl;
        ControlSelection();

        std::cout << "Tell Clients to Begin Countdown ..." << std::endl;
        // Tell Clients to Start Countdowns
        CountDownScreen();

        // Begin Timer
        start = std::clock();

        std::cout << "Starting Game ..." << std::endl;

        // Initialize the player's position on the gameboard
        int mid = (CONTENT_WIDTH - 1) / 2;
        player1and2.SetLocX(mid);
        player1and2.SetLocY(CONTENT_HEIGHT - 5);

        gameEnvironment.setInitialPlayerPosition(player1and2);

        // Begin Game
        while(!GetGameOver())
        {
            // Update Game
            UpdateGame(duration, timer);
            std::chrono::duration<int, std::milli> timespan(150);
            std::this_thread::sleep_for(timespan);
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
        ServerSocket.deliver1("Server failed to open Leaderboard");
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
            file.append("\n");
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
    std::string filePath = "./data/LeaderBoards.txt";
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

    std::string filePathRewrite = "./data/LeaderBoards.txt";
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
    std::string filePath = "./data/LeaderBoards.txt";
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
void GameControllerServer::UpdateScore(double duration, float timer)
{
    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    timer = floor(((duration / 60.0) / 60.0) * 10000);
    Score = Score + (int)timer + 1;
}

// Select Player Name
void GameControllerServer::NameMenu()
{
    ServerSocket.clearBuffers();

    char name1[6];
    char name2[6];
    memset(name1, '\0', 6);
    memset(name2, '\0', 6);

    std::string player_a = "";
    std::string player_b = "";
    int NameSetCounter = 0;
    int player1Ready = 0;
    int player2Ready = 0;

    char buffer1[MAX_BYTES];
    char buffer2[MAX_BYTES];
    memset(buffer1, '\0', MAX_BYTES);
    memset(buffer2, '\0', MAX_BYTES);

    int bytes = 0;

    // Loop Until Both Players Indicate Their Names Are Set
    while(1)
    {
        if(player1Ready == 0)
        {
            // Receive Client 1 Signal
            ServerSocket.receive1(buffer1);

            if(strstr(buffer1, "! name"))
            {
                std::cout << "Retrieving P1 Name..." << std::endl;
                memset(buffer1, '\0', MAX_BYTES);

                // Set Name
                player_a = name1;
                player1Ready = 1;
                std::cout << "Player 1 Name Received." << std::endl;
            }
        }

        if(player2Ready == 0)
        {
            // Receive Client 1 Signal
            bytes = ServerSocket.receive2(buffer2);
            if (bytes)
                std::cout << buffer2 << std::endl;


            if(strstr(buffer2, "! name"))
            {
                std::cout << "Retrieving P2 Name..." << std::endl;
                memset(buffer2, '\0', MAX_BYTES);

                // Set Name
                player_a = name2;
                player2Ready = 1;
                std::cout << "Player 2 Name Received." << std::endl;
            }
        }
        if(player1Ready && player2Ready )
            break;
    }

    // Concatenate Names
    std::string name = player_a + player_b;
    player1.SetName(player_a);
    player2.SetName(player_b);
    player1and2.SetName(name);

    std::cout << "Player Names Set." << std::endl;
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

    std::cout << "Sending Controls to Players" << std::endl;
    
    // send controls command to let client know it 
    const char* msg = "controls";
    ServerSocket.deliver(msg);


    char buffer1[MAX_BYTES];
    char buffer2[MAX_BYTES];
    memset(buffer1, '\0', MAX_BYTES);
    memset(buffer2, '\0', MAX_BYTES);
    int sendCounter = 0;
    int bytes = 0;
    while(sendCounter != 2)
    {
        ServerSocket.receive1(buffer1);
        if(strcmp( buffer1, "send") == 0)
        {
            sendCounter++;
            std::cout << "player 1 ready\n";
            memset(buffer1, '\0', MAX_BYTES);
        }

        ServerSocket.receive2(buffer2);
        if(strcmp( buffer2, "send") == 0)
        {
            sendCounter++;
            std::cout << "player 2 ready\n";
            memset(buffer2, '\0', MAX_BYTES);
        }
    }

    std::cout << "Delivering Controls" << std::endl;
    if(player1Controls == 1)
    {
        std::string control1 = "1";
        ServerSocket.deliver1(control1.c_str());

        std::string control2 = "2";
        ServerSocket.deliver2(control2.c_str());

        player2Controls = 2;
    }
    else if(player1Controls == 2)
    {
        std::string control1 = "2";
        ServerSocket.deliver1(control1.c_str());

        std::string control2 = "1";
        ServerSocket.deliver2(control2.c_str());

        player2Controls = 1;
    }

    // Clients in Menu
    int ReadyCounter = 0;

    char buf1[MAX_BYTES];
    char buf2[MAX_BYTES];
    memset(buf1, '\0', MAX_BYTES);
    memset(buf2, '\0', MAX_BYTES);

    // Loop Until Both Players Indicate They Are Ready to Play
    while(ReadyCounter != 2)
    {
        // Receive Client 1 Signal
        ServerSocket.receive1(buf1);

        if(strcmp( buf1, "ready") == 0)
        {
            std::cout << "Player 1 Ready ..." << std::endl;
            ReadyCounter++;
            memset(buf1, '\0', MAX_BYTES);
        }

        // Receive Client 2 Signal
        ServerSocket.receive2(buf2);

        if(strcmp( buf2, "ready") == 0)
        {
            std::cout << "Player 2 Ready ..." << std::endl;
            ReadyCounter++;
            memset(buf2, '\0', MAX_BYTES);
        }
    }

    sleep(5);
}

// Displayed Before Game Starts
void GameControllerServer::CountDownScreen()
{
    // Tell Clients to start countdowns
    sleep(1);
    std::cout << "Sending Countdown Code" << std::endl;
    const char* msg = "countdown";
    std::string message = "countdown";
    ServerSocket.deliver(message.c_str());
    sleep(3);
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
    return Collision;
}

// Create Special Game Events
void GameControllerServer::CreateSpecialEvent()
{

}

// Update Player Location
void GameControllerServer::MovePlayer()
{
    char x = 'x';
    char y = 'y';
    int move_x = 0;
    int move_y = 0;
    std::string s = "";
    char buffer1[MAX_BYTES];
    char buffer2[MAX_BYTES];
    memset(buffer1, '\0', MAX_BYTES);
    memset(buffer2, '\0', MAX_BYTES);

    // Receive Data From Client
    ServerSocket.receive1(buffer1);
    ServerSocket.receive2(buffer2);

    // Update Player Location (X|Y) for Player 1
    if(buffer1[0] == x)
    {
        for (int i = 1; i < MAX_BYTES; i++)
        {
            if(buffer1[i] == '\0')
            {
                break;
            }
            s += buffer1[i];
        }
        move_x = stoi(s);
    }
    else if (buffer1[0] == y)
    {
        for (int i = 1; i < MAX_BYTES; i++)
        {
            if(buffer1[i] == '\0')
            {
                break;
            }
            s += buffer1[i];
        }
        move_y = stoi(s);
    }

    // Update Player Location (X|Y) for Player 2
    s = "";
    if(buffer2[0] == x)
    {
        for (int i = 1; i < MAX_BYTES; i++)
        {
            if(buffer2[i] == '\0')
            {
                break;
            }
            s += buffer2[i];
        }
        move_x = stoi(s);
    }
    else if (buffer2[0] == y)
    {
        for (int i = 1; i < MAX_BYTES; i++)
        {
            if(buffer2[i] == '\0')
            {
                break;
            }
            s += buffer2[i];
        }
        move_y = stoi(s);
    }

    // Update Player
    player1and2.SetLocX(move_x);
    player1and2.SetLocY(move_y);

    // Update Map
    gameEnvironment.updatePlayerPosition(player1and2);
    // continue
}

// Update Object Locations
void GameControllerServer::MoveObjects()
{
}

// Move Environment
void GameControllerServer::MoveEnvironment()
{
    gameEnvironment.advance(player1and2);
}

// Sets New Environment
void GameControllerServer::UpdateEnvironment()
{

}

// Send Map to Client/Server
void GameControllerServer::SendMap()
{
    std::string ack = "ack";
    char buffer1[4];
    char buffer2[4];

    memset(buffer1, '\0', 4);
    memset(buffer2, '\0', 4);

    std::cout << "Sending Map Data to Clients" << std::endl;

    std::string serializedMap = gameEnvironment.getMap();

    std::cout << serializedMap << std::endl;

    ServerSocket.deliver(serializedMap.c_str());

    std::cout << "Map Data Sent to Clients" << std::endl;

    ServerSocket.receive1(buffer1, 4);
    ServerSocket.receive2(buffer2, 4);

    if (strcmp(ack.c_str(), buffer1) == 0)
    {
        std::cout << "Client 1 Acknowledged Receipt of Data" << std::endl;
    }
    if (strcmp(ack.c_str(), buffer2) == 0)
    {
        std::cout << "Client 2 Acknowledged Receipt of Data" << std::endl;
    }
}

// Update Game State
void GameControllerServer::UpdateGame(double duration, float timer)
{
    // Check Server Connection
    if(ServerSocket.getConnection())
    {
        // Print Screen

        // Update Player
        // MovePlayer();

        // Clear Screen
        std::cout << "\033[2J\033[1;1H";

        // Create Special Event
        // CreateSpecialEvent();

        // Move Objects
        // MoveObjects();

        // Update Environment
        //if(score > X)
        //    UpdateEnvironment();

        // Move Environment
        MoveEnvironment();

        // Check for Collisions
        CheckCollisions();

        // Update Score
        UpdateScore(duration, timer);

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
