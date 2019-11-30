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
GameControllerServer::GameControllerServer() : ServerSocket(8542), player1(), player2(), gameEnvironment(CONTENT_HEIGHT, CONTENT_WIDTH - 1, 1000)
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

    while (1)
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
        while (!ReadyPlayer1 || !ReadyPlayer2)
        {

            // read from socket 1 if play is not yet ready
            if (!ReadyPlayer1)
            {
                // Receive Client 1 Signal
                bytes1 = ServerSocket.receive1(buffer1);

                if (bytes1)
                {
                    std::cout << buffer1 << std::endl;
                }

                if (strstr(buffer1, "? leaderboard"))
                {
                    LeaderBoard(1);
                    memset(buffer1, '\0', MAX_BYTES);
                }
                else if (strstr(buffer1, "! pReady"))
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

                if (bytes2)
                {
                    std::cout << buffer2 << std::endl;
                }

                if (strstr(buffer2, "? leaderboard"))
                {
                    LeaderBoard(2);
                    memset(buffer2, '\0', MAX_BYTES);
                }
                else if (strstr(buffer2, "! pReady"))
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
        while (GetGameOver() != true)
        {
            // Update Game
            std::cout << "GAME LOOP" << std::endl;
            UpdateGame(duration, timer);
            std::chrono::duration<int, std::milli> timespan(85);
            std::this_thread::sleep_for(timespan);
        }

        // Send Score and Save it
        SendScore();
        SaveScore(Score);
        std::cout << "Score written!\n";

        // Reset Values
        SetGameOver(false);
        duration = 0.0;
        timer = 0.0;
        // Reset the Game Levels and Board
        gameEnvironment.reset();

        // Play Again?
        if (ReplayCheck() == false)
        {
            std::cout << "At least one player chose to quit - Game/Server Ending" << std::endl;
            break;
        }
    }
}

// LeaderBoard Menu
void GameControllerServer::LeaderBoard(int player)
{
    // Open File and View Leader Boards
    // Clear Screen
    std::cout << "\033[2J\033[1;1H";
    //std::cout << "Leader Board Function" << std::endl;
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
        std::cout << "About to send LeaderBoard" << std::endl;
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

        if (player == 1)
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
    std::cout << "Sorting Leader Board" << std::endl;
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
                std::string nullVal;

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
        std::string tableHeader = "Name\t\tScore";
        fileRewrite << header << std::endl;
        fileRewrite << tableHeader << std::endl;

        //insert sorted scores
        for (int i = 0; i < updateScores.size(); i++)
        {
            fileRewrite << updateScores[i].name << "\t" << updateScores[i].score << std::endl;
        }
    }

    fileRewrite.close();
}

// Save Score
void GameControllerServer::SaveScore(int score)
{
    std::cout << "Writing score to leaderboard\n";

    std::string filePath = "./data/LeaderBoards.txt";
    std::ofstream file;

    file.open(filePath, std::fstream::app);

    if (!file)
    {
        std::cout << "Error Saving Score" << std::endl;
    }
    else
    {
    std:
        cout << "Saving Player's Score" << std::endl;
        std::cout << "Player: " << player1and2.GetName() << std::endl;
        std::cout << "Score: " << score << std::endl;

        // Enter Player Score
        file << player1and2.GetName() << "\t" << score << std::endl;

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

void GameControllerServer::SendScore()
{

    std::cout << "Waiting for players to request score" << std::endl;

    int player1Ready = 0;
    int player2Ready = 0;

    char buffer1[MAX_BYTES];
    char buffer2[MAX_BYTES];
    memset(buffer1, '\0', MAX_BYTES);
    memset(buffer2, '\0', MAX_BYTES);

    // Loop Until Both Players Indicate Their Names Are Set
    while (1)
    {
        if (player1Ready == 0)
        {
            // Receive Client 1 Signal
            ServerSocket.receive1(buffer1);

            if (strstr(buffer1, "? score"))
            {
                std::cout << "Player 1 ready for score" << std::endl;
                player1Ready = 1;
            }
        }

        if (player2Ready == 0)
        {
            // Receive Client 1 Signal
            ServerSocket.receive2(buffer2);

            if (strstr(buffer2, "? score"))
            {
                std::cout << "Player 2 ready for score" << std::endl;
                player2Ready = 1;
            }
        }

        // break when both players are ready
        if (player1Ready && player2Ready)
            break;
    }

    // send score
    std::string score = std::to_string(Score);
    ServerSocket.deliver(score.c_str());

    std::cout << "Score sent " << score << std::endl;
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

    int bytes1 = 0;
    int bytes2 = 0;

    std::cout << "Receiving Names from Clients" << std::endl;

    std::string nulVal;

    int go = 0;

    // Loop Until Both Players Indicate Their Names Are Set
    while (go == 0)
    {
        if (player1Ready == 0)
        {
            // Receive Client 1 Signal
            bytes1 = ServerSocket.receive1(buffer1);
            if (bytes1)
                std::cout << "Client 1 Received Buffer: " << buffer1 << std::endl;

            if (strstr(buffer1, "! name"))
            {
                std::cout << "Retrieving P1 Name..." << std::endl;
                std::istringstream nameCommand1(buffer1);

                while (nameCommand1)
                {
                    // Set Name
                    getline(nameCommand1, nulVal, ' ');
                    getline(nameCommand1, nulVal, ' ');
                    getline(nameCommand1, player_a, ' ');
                }

                player1Ready = 1;
                std::cout << "Player 1 Name Received." << std::endl;
                std::cout << "Player 1 Name: " << player_a << std::endl;
            }
        }

        if (player2Ready == 0)
        {
            // Receive Client 2 Signal
            bytes2 = ServerSocket.receive2(buffer2);
            if (bytes2)
                std::cout << "Client 2 Received Buffer: " << buffer2 << std::endl;

            if (strstr(buffer2, "! name"))
            {
                std::cout << "Retrieving P2 Name..." << std::endl;
                std::istringstream nameCommand2(buffer2);

                while (nameCommand2)
                {
                    // Set Name
                    getline(nameCommand2, nulVal, ' ');
                    getline(nameCommand2, nulVal, ' ');
                    getline(nameCommand2, player_b, ' ');
                }

                player2Ready = 1;
                std::cout << "Player 2 Name Received." << std::endl;
                std::cout << "Player 2 Name: " << player_b << std::endl;
            }
        }

        if(player1Ready == 1 && player2Ready == 1)
        {
            go = 1;
        }
    }

    // Concatenate Names
    std::string seperator = " | ";
    std::string name = player_a + seperator + player_b;

    player1.SetName(player_a);
    player2.SetName(player_b);
    player1and2.SetName(name);

    std::cout << "Player Name: " << player1and2.GetName() << std::endl;
    std::cout << "Player Names Set." << std::endl;
}

// Await Player Server Connection
void GameControllerServer::AwaitingPlayer()
{
    // Deliver message that both clients have connected
    const char *msg = "Matchmaking Completed!";
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
    const char *msg = "controls";
    ServerSocket.deliver(msg);

    char buffer1[MAX_BYTES];
    char buffer2[MAX_BYTES];
    memset(buffer1, '\0', MAX_BYTES);
    memset(buffer2, '\0', MAX_BYTES);
    int sendCounter = 0;
    int bytes = 0;
    while (sendCounter != 2)
    {
        ServerSocket.receive1(buffer1);
        if (strcmp(buffer1, "send") == 0)
        {
            sendCounter++;
            std::cout << "Player 1 Ready\n";
            memset(buffer1, '\0', MAX_BYTES);
        }

        ServerSocket.receive2(buffer2);
        if (strcmp(buffer2, "send") == 0)
        {
            sendCounter++;
            std::cout << "Player 2 Ready\n";
            memset(buffer2, '\0', MAX_BYTES);
        }
    }

    std::cout << "Delivering Controls" << std::endl;
    if (player1Controls == 1)
    {
        std::string control1 = "1";
        ServerSocket.deliver1(control1.c_str());

        std::string control2 = "2";
        ServerSocket.deliver2(control2.c_str());

        player2Controls = 2;
    }
    else if (player1Controls == 2)
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
    while (ReadyCounter != 2)
    {
        // Receive Client 1 Signal
        ServerSocket.receive1(buf1);

        if (strcmp(buf1, "ready") == 0)
        {
            std::cout << "Player 1 Ready ..." << std::endl;
            ReadyCounter++;
            memset(buf1, '\0', MAX_BYTES);
        }

        // Receive Client 2 Signal
        ServerSocket.receive2(buf2);

        if (strcmp(buf2, "ready") == 0)
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
    const char *msg = "countdown";
    std::string message = "countdown";
    // ServerSocket.deliver(message.c_str());
    sleep(3);
}

// Checks for Player/Object Collisions
void GameControllerServer::CheckCollisions(DIRECTION direction) //DIRECTION direction
{
    int playerLocX = 0;
    int playerLocY = 0;
    char boardObject = NULL_SPRITE;

    switch (direction)
    {
    case UP:
        playerLocY = GetPlayer1and2().GetLocY() - 1; // Next Player Location Y
        playerLocX = GetPlayer1and2().GetLocX();     // Player Location X
        break;
    case DOWN:
        playerLocY = GetPlayer1and2().GetLocY() + 1; // Next Player Location Y
        playerLocX = GetPlayer1and2().GetLocX();     // Player Location X
        break;
    case LEFT:
        playerLocY = GetPlayer1and2().GetLocY();     // Player Location Y
        playerLocX = GetPlayer1and2().GetLocX() - 1; // Next Player Location X
        break;
    case RIGHT:
        playerLocY = GetPlayer1and2().GetLocY();     // Player Location Y
        playerLocX = GetPlayer1and2().GetLocX() + 1; // Next Player Location X
        break;
    case NONE:
        playerLocY = GetPlayer1and2().GetLocY() - 1; // Next Player Location Y
        playerLocX = GetPlayer1and2().GetLocX();     // Player Location X
    }

    boardObject = gameEnvironment.getMatrix().at(playerLocY, playerLocX); // Board at Player Location

    if (boardObject == COLLISION_SPRITE)
    {
        std::cout << "Collision Detected" << std::endl;
        std::cout << "LocationY: " << playerLocY << std::endl;
        std::cout << "LocationX: " << playerLocX << std::endl;
        std::cout << "GameBoard: " << boardObject << std::endl;
        SetCollisionOccur(true);
        // Make an explosion on the board to show a collision
        gameEnvironment.triggerExplosion(player1and2.GetLocY(), player1and2.GetLocX());
    }

    // Check Gameboard Boundaries
    if (playerLocX == 196 ||
        playerLocX == 0 ||
        playerLocY > 30 ||
        playerLocY == 0)
    {
        std::cout << "Edge of Gameboard Detected - Block Movement" << std::endl;
        std::cout << "LocationY: " << playerLocY << std::endl;
        std::cout << "LocationX: " << playerLocX << std::endl;
        std::cout << "GameBoard: " << boardObject << std::endl;
        Edge = true;
    }
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

    std::cout << "Movement Function" << std::endl;

    // Receive Data From Client
    while (!strlen(buffer1))
    {
        ServerSocket.receive1(buffer1);
    }
    while (!strlen(buffer2))
    {
        ServerSocket.receive2(buffer2);
    }

    std::cout << "MOVEMENT Buffer 1: " << buffer1 << std::endl;
    std::cout << "MOVEMENT Buffer 2: " << buffer2 << std::endl;

    // Update Player Location (X|Y) for Player 1
    if (buffer1[0] == x)
    {
        std::cout << "Player 1 - X-Axis Movement Detected." << std::endl;
        move_x = (int)buffer1[1] - 48;
        std::cout << "Player 1 Move X: " << move_x << std::endl;
    }
    else if (buffer1[0] == y)
    {
        std::cout << "Player 1 - Y-Axis Movement Detected." << std::endl;
        move_y = (int)buffer1[1] - 48;
        std::cout << "Player 1 Move Y: " << move_x << std::endl;
    }

    // Update Player Location (X|Y) for Player 2
    s = "";
    if (buffer2[0] == x)
    {
        std::cout << "Player 2 - X-Axis Movement Detected." << std::endl;
        move_x = (int)buffer2[1] - 48;
        std::cout << "Player 2 Move X: " << move_x << std::endl;
    }
    else if (buffer2[0] == y)
    {
        move_y = (int)buffer2[1] - 48;
        std::cout << "Player 2 Move Y: " << move_x << std::endl;
    }

    // Movement Based On X-Axis Player
    switch (move_x)
    {
    case 0:
        // Check Collisions
        std::cout << "No Movement - X Switch" << std::endl;
        CheckCollisions(NONE);
        break;
    case 1:
        // Check Collisions
        std::cout << "X-Axis - Left" << std::endl;
        CheckCollisions(LEFT);
        if (Edge == true)
        {
            Edge = false;
        }
        else
        {
            player1and2.MoveLeft();
        }
        break;
    case 2:
        // Check Collisions
        std::cout << "X-Axis - Right" << std::endl;
        CheckCollisions(RIGHT);
        if (Edge == true)
        {
            Edge = false;
        }
        else
        {
            player1and2.MoveRight();
        }
        break;
    default:
        std::cout << "Default - No Movement - X Switch" << std::endl;
        CheckCollisions(NONE);
        break;
    }

    // Movement Based On Y-Axis Player
    switch (move_y)
    {
    case 0:
        // Check Collisions
        std::cout << "No Movement - Y Switch" << std::endl;
        CheckCollisions(NONE);
        break;
    case 1:
        // Check Collisions
        std::cout << "Y-Axis - Up" << std::endl;
        CheckCollisions(UP);
        if (Edge == true)
        {
            Edge = false;
        }
        else
        {
            player1and2.MoveUp();
        }
        break;
    case 2:
        // Check Collisions
        std::cout << "Y-Axis - Down" << std::endl;
        CheckCollisions(DOWN);
        if (Edge == true)
        {
            Edge = false;
        }
        else
        {
            player1and2.MoveDown();
        }
        break;
    default:
        std::cout << "Default - No Movement - Y Switch" << std::endl;
        CheckCollisions(NONE);
        break;
    }

    // Update Game State for Collision
    if (GetCollisionOccur())
    {
        std::cout << "Collision Detected!" << std::endl;

        std::string message = "collision_true";
        usleep(300); // ensure the client has time to read this buffer
        ServerSocket.deliver(message.c_str());
        SetGameOver(true);
    }
    else
    {
        std::string message = "collision_false";
        usleep(300); // ensure the client has time to read this buffer
        ServerSocket.deliver(message.c_str());
    }

    // Update Map
    gameEnvironment.updatePlayerPosition(player1and2);
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
    std::cout << "Waiting for players to request map" << std::endl;

    int player1Ready = 0;
    int player2Ready = 0;

    char buffer1[MAX_BYTES];
    char buffer2[MAX_BYTES];
    memset(buffer1, '\0', MAX_BYTES);
    memset(buffer2, '\0', MAX_BYTES);

    // Loop Until Both Players Indicate They Are Ready
    while (1)
    {
        if (player1Ready == 0)
        {
            // Receive Client 1 Signal
            ServerSocket.receive1(buffer1);

            if (strstr(buffer1, "? map"))
            {
                std::cout << "Player 1 ready for map" << std::endl;
                player1Ready = 1;
            }
        }

        if (player2Ready == 0)
        {
            // Receive Client 1 Signal
            ServerSocket.receive2(buffer2);

            if (strstr(buffer2, "? map"))
            {
                std::cout << "Player 2 ready for map" << std::endl;
                player2Ready = 1;
            }
        }

        // break when both players are ready
        if (player1Ready && player2Ready)
            break;
    }

    // Send Map
    std::string map = gameEnvironment.getMap();
    ServerSocket.deliver(map.c_str());

    std::cout << "Map Sent to Clients" << std::endl;
}

// Send Level Info to Client/Server
void GameControllerServer::SendLevel()
{
    std::cout << "Waiting for players to request Level Info" << std::endl;

    int player1Ready = 0;
    int player2Ready = 0;

    char buffer1[MAX_BYTES];
    char buffer2[MAX_BYTES];
    memset(buffer1, '\0', MAX_BYTES);
    memset(buffer2, '\0', MAX_BYTES);

    // Loop Until Both Players Indicate They Are Ready
    while (1)
    {
        if (player1Ready == 0)
        {
            // Receive Client 1 Signal
            ServerSocket.receive1(buffer1);

            if (strstr(buffer1, "? level"))
            {
                std::cout << "Player 1 ready for Level Info" << std::endl;
                player1Ready = 1;
            }
        }

        if (player2Ready == 0)
        {
            // Receive Client 1 Signal
            ServerSocket.receive2(buffer2);

            if (strstr(buffer2, "? level"))
            {
                std::cout << "Player 2 ready for Level Info" << std::endl;
                player2Ready = 1;
            }
        }

        // break when both players are ready
        if (player1Ready && player2Ready)
            break;
    }

    // Send Map
    std::string name = gameEnvironment.currentLevelName();
    ServerSocket.deliver(name.c_str());

    std::cout << "Level Infor Sent to Clients" << std::endl;
}

// Update Game State
void GameControllerServer::UpdateGame(double duration, float timer)
{
    // Break for New Data
    std::cout << std::endl;

    int playerLocX = 0;
    int playerLocY = 0;
    std::cout << "Outside Connection Check - In Update Game" << std::endl;

    // Check Server Connection
    if (ServerSocket.getConnection())
    {
        // Clear Screen
        std::cout << "\033[2J\033[1;1H";

        // Print Screen
        std::cout << "Connection Good - In Update Game" << std::endl;

        // Send Map to Client
        SendMap();

        // Send current score to Client
        SendScore();

        // Send Level Infor to Clients
        SendLevel();

        // Update Player
        MovePlayer();

        playerLocY = GetPlayer1and2().GetLocY();
        playerLocX = GetPlayer1and2().GetLocX();
        std::cout << "LocationY: " << playerLocY << std::endl;
        std::cout << "LocationX: " << playerLocX << std::endl;

        // Create Special Event
        // CreateSpecialEvent();

        // Move Objects
        MoveObjects();

        // Update Environment
        //if(score > X)
        //    UpdateEnvironment();

        // Move Environment
        MoveEnvironment();

        // Check for Collisions
        //CheckCollisions();

        // Update Score
        UpdateScore(duration, timer);
    }
}

// Replay Check
bool GameControllerServer::ReplayCheck()
{
    bool player1Replay = false;
    bool player2Replay = false;
    bool replayP1 = false;
    bool replayP2 = false;
    char buffer1[MAX_BYTES];
    char buffer2[MAX_BYTES];
    memset(buffer1, '\0', MAX_BYTES);
    memset(buffer2, '\0', MAX_BYTES);

    std::cout << "Replay Function - Check" << std::endl;

    while (1)
    {
        if (!replayP1)
        {
            // Receive Data From Client
            ServerSocket.receive1(buffer1);

            // Check Client Responses
            if (strcmp(buffer1, "! yes_replay") == 0)
            {
                std::cout << "Player 1 Agrees to Replay" << std::endl;
                player1Replay = true;
                replayP1 = true;
            }
            else if (strcmp(buffer1, "! no_replay") == 0)
            {
                std::cout << "Player 1 Disagrees to Replay" << std::endl;
                replayP1 = true;
            }
            else
            {
                memset(buffer1, '\0', MAX_BYTES);
            }
        }

        if (!replayP2)
        {
            // Receive Data From Client
            ServerSocket.receive2(buffer2);

            // Check Client Responses
            if (strcmp(buffer2, "! yes_replay") == 0)
            {
                std::cout << "Player 2 Agrees to Replay" << std::endl;
                player2Replay = true;
                replayP2 = true;
            }
            else if (strcmp(buffer2, "! no_replay") == 0)
            {
                std::cout << "Player 2 Disagrees to Replay" << std::endl;
                replayP2 = true;
            }
            else
            {
                memset(buffer2, '\0', MAX_BYTES);
            }
        }

        if (replayP1 == true && replayP2 == true)
            break;
    }

    std::cout << "Delivering Replay Message to Clients" << std::endl;
    if (player1Replay == true && player2Replay == true)
    {
        std::string reply = "setReplayTrue";
        ServerSocket.deliver(reply.c_str());
        return true;
    }
    else
    {
        std::string reply = "setReplayFalse";
        ServerSocket.deliver(reply.c_str());
        return false;
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
