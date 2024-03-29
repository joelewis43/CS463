//
// Created by Devin Gendron on 2019-10-24.
//

#include "../headers/GameControllerClient.h"
#include "../headers/Player.h"
#include "../headers/clientSocket.h"
#include "../headers/commands.h"

////////////////////////////////
///                          ///
/// Constructors/Destructors ///
///                          ///
////////////////////////////////

// Constructor
GameControllerClient::GameControllerClient() : ClientSocket("127.0.0.1", 7523), board(CONTENT_HEIGHT, CONTENT_WIDTH - 1)
{
}

// Destructor
GameControllerClient::~GameControllerClient()
{
}

////////////////////////////////
///                          ///
/// GameController Functions ///
///                          ///
////////////////////////////////

// Main Game Loop
void GameControllerClient::MainGameLoop()
{
    // Clear Screen
    std::cout << "\033[2J\033[1;1H";

    // Time Seed for Score Keeping
    srand(time(NULL));

    // If Connection Is Made
    ServerConnection();

    bool replay = true;

    while (replay == true)
    {
        // Menus
        MainMenu();

        if (GetQuitGame() == false)
        {
            // Initialize ncurses
            initscr();

            WINDOW *borderWindow = createBorderWindow();
            WINDOW *contentWindow = createContentWindow(borderWindow);

            // Settings
            noecho();

            // Set Arrow Keys to Non-Blocking
            keypad(stdscr, TRUE);
            timeout(1);
            nodelay(stdscr, TRUE);

            start_color();

            init_pair(1, COLOR_WHITE, COLOR_BLACK);
            init_pair(2, COLOR_YELLOW, COLOR_BLACK);
            init_pair(3, COLOR_RED, COLOR_BLACK);

            // Begin Game
            while (GetGameOver() != true && GetServerConnection() == true)
            {
                UpdateGame(contentWindow);
                std::chrono::duration<int, std::milli> timespan(95);
                std::this_thread::sleep_for(timespan);
            }

            GameOverMenu();

            delwin(contentWindow);
            delwin(borderWindow);

            // Quit
            // Clear Screen
            std::cout << "\033[2J\033[1;1H";
            endwin();
            keypad(stdscr, FALSE);
            timeout(1);
            nodelay(stdscr, FALSE);

            // Would you Like to Play Again?
            ReplayMenu(replay);

            if (replay)
            {
                SetCollision(false);
                SetGameOver(false);
            }
            else
            {
                std::cout << "A Replay Could Not Be Established" << std::endl;
                std::cout << "Thanks for playing!" << std::endl;
                sleep(1);
                break;
            }
            sleep(1);
        }
        else
        {
            // Quit
            // Clear Screen
            std::cout << "\033[2J\033[1;1H";
            endwin();
            std::cout << "Thanks for playing!" << std::endl;
            sleep(1);
        }
    }
}

// Main Menu
void GameControllerClient::MainMenu()
{
    // Clear Screen
    std::cout << "\033[2J\033[1;1H";
    int selection = -1;
    std::string msg = "! pReady";

    while (selection == -1)
    {
        std::cout << "\033[2J\033[1;1H";
        while(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
        }
        std::cin.clear();
        std::cin.sync();
        fflush(stdin);
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

        if(!std::cin.fail())
        {
            if (selection > 0 && selection < 4)
            {
                switch (selection)
                {
                    case 1:
                        // Play Game - Set Name
                        // Tell Server Player is Ready to Play
                        ClientSocket.deliver(msg.c_str());
                        AwaitingPlayer();
                        NameMenu();
                        AwaitingPlayer(); // Listening to Server / Tell Server Client is Ready
                        ControlSelection();
                        CountDownScreen();
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
                sleep(1);
            }
        }
        else
        {
            selection = -1;
            std::cout << std::endl;
            std::cout << "Please Select 1, 2, or 3." << std::endl;
            selection = -1;
            sleep(1);

        }

        if (selection == 2)
        {
            // Clear Screen and Let Menu Appear Again
            std::cout << "\033[2J\033[1;1H";
            selection = -1;
        }
    }
}

// Replay Menu
void GameControllerClient::ReplayMenu(bool &replay)
{
    int selection = -1;
    std::string msg1 = "! yes_replay";
    std::string msg2 = "! no_replay";

    while (selection == -1)
    {
        std::cout << "\033[2J\033[1;1H";
        while(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
        }

        std::cin.clear();
        std::cin.sync();
        fflush(stdin);
        std::cout << "1. Replay" << std::endl;
        std::cout << "2. Exit Game" << std::endl;
        std::cout << std::endl;
        std::cout << "*If there are any gameplay artifacts present in the buffer, " << std::endl;
        std::cout << "please press enter to clear them away.*" << std::endl;
        std::cout << std::endl;
        std::cout << "*Enter your menu selection and press Enter" << std::endl;
        std::cout << std::endl;
        std::cout << "Selection: ";
        std::cin >> selection;

        if(!std::cin.fail())
        {
            if (selection > 0 && selection < 3)
            {
                switch (selection)
                {
                    case 1:
                        replay = true;
                        ClientSocket.deliver(msg1.c_str());
                        break;
                    case 2:
                        replay = false;
                        ClientSocket.deliver(msg2.c_str());
                        break;
                    default:
                        std::cout << "Something Went Wrong..." << std::endl;
                        break;
                }
            }
            else
            {
                std::cout << std::endl;
                std::cout << "Please Select 1 or 2." << std::endl;
                sleep(1);
                selection = -1;
            }
        }
        else
        {
            selection = -1;
        }
    }

    char buffer[MAX_BYTES];
    memset(buffer, '\0', MAX_BYTES);
    // Server Response
    ClientSocket.receive(buffer);
    int counter = 0;
    int bytes = 0;
    while (1)
    {
        bytes = ClientSocket.receive(buffer);
        if (bytes)
            std::cout << "Message from Server: " << buffer << std::endl;

        if (strcmp(buffer, "setReplayTrue") == 0)
        {
            replay = true;
            SetGameOver(false);
            counter++;
        }
        else if (strcmp(buffer, "setReplayFalse") == 0)
        {
            replay = false;
            SetGameOver(true);
            counter++;
        }
        if (counter > 0)
        {
            break;
        }
        else
        {
            memset(buffer, '\0', MAX_BYTES);
        }
    }
}

// LeaderBoard Menu
void GameControllerClient::LeaderBoard()
{
    // Open File and View Leader Boards
    // Clear Screen
    std::cout << "\033[2J\033[1;1H";
    //std::cout << "Leader Board Function" << std::endl;
    usleep(500);

    // Ask Server for LeaderBoard
    const char *msg = "? leaderboard";
    ClientSocket.deliver(msg);

    // Wait for server to send leaderboard
    char res[MAX_BYTES];
    memset(res, '\0', MAX_BYTES);
    ClientSocket.receiveBlock(res);

    // Display Leader Board
    std::cout << "\033[2J\033[1;1H";
    //std::cout << "\tLeaderboard" << std::endl;
    std::cout << res << std::endl;

    sleep(5);

    // User Input to Return to Menu
}

// Select Player Name
void GameControllerClient::NameMenu()
{
    std::string name = "";

    while (1)
    {
        // Clear Screen
        std::cout << "\033[2J\033[1;1H";

        // check if name exists
        if (player.GetName() == "")
        {
            // Display Menu to Enter Name
            std::cout << "Enter Your Name" << std::endl;
            std::cout << std::endl;
            std::cout << "3-5 Alphanumeric Characters Required" << std::endl;
            std::cout << "Press Enter to Continue" << std::endl;
            std::cout << std::endl;
            std::cout << "Name: ";
            std::cin >> name;

            if (name.size() >= 3 && name.size() <= 5)
            {
                // Set Name in Player Object
                player.SetName(name);

                // Tell Server the Name
                std::string msg = "! name ";
                msg += name.c_str();
                ClientSocket.deliver(msg.c_str());

                break;
            }
            else
            {
                std::cout << "Please Enter Correct Name Length" << std::endl;
                sleep(1);
            }
        }
        else
        {
            // A Player Name Exists - overwrite or quit?
            std::cout << "Please note - Your current name: " << player.GetName() << " will be overwritten." << std::endl;
            std::cout << "Enter Your Name" << std::endl;
            std::cout << std::endl;
            std::cout << "3-5 Alphanumeric Characters Required" << std::endl;
            std::cout << "Press Enter to Continue" << std::endl;
            std::cout << std::endl;
            std::cout << "Name: ";
            std::cin >> name;

            if (name.size() >= 3 && name.size() <= 5)
            {
                // Set Name in Player Object
                player.SetName(name);

                // Tell Server the Name
                std::string msg = "! name ";
                msg += name.c_str();
                ClientSocket.deliver(msg.c_str());
                break;
            }
            else
            {
                std::cout << "Please Enter Correct Name Length." << std::endl;
                sleep(1);
            }
        }
    }
}

// Checks for Server Connection
void GameControllerClient::ServerConnection()
{
    // Check Server Connection Is Not Interrupted
    if (ClientSocket.getConnection())
    {
        SetServerConnection(true);
    }
    else
    {
        SetServerConnection(false);
    }
}

// Await Player Server Connection
void GameControllerClient::AwaitingPlayer()
{
    bool PlayerJoined2 = false;

    std::cout << "\033[2J\033[1;1H";
    std::cout << "Waiting for your partner..." << std::endl;
    std::cout << "Thank you for your patience" << std::endl;

    char buffer[MAX_BYTES];
    memset(buffer, '\0', MAX_BYTES);

    while (PlayerJoined2 != true)
    {

        int bytes = ClientSocket.receive(buffer);
        if (bytes)
            std::cout << buffer << std::endl;

        if (strstr(buffer, "Matchmaking Completed!"))
        {
            PlayerJoined2 = true;
        }
    }

    memset(buffer, '\0', MAX_BYTES);

    std::cout << "The Other Player Has Joined!" << std::endl;
    sleep(1);
}

// Player Selects Controls
void GameControllerClient::ControlSelection()
{
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Ready for Controls..." << std::endl;

    // Ask the server what controls you are assigned
    char one = '1';
    char two = '2';
    std::string send = "send";

    char buff[MAX_BYTES];
    memset(buff, '\0', MAX_BYTES);

    while (1)
    {
        if (ClientSocket.receive(buff))
            std::cout << "DEBUG: " << buff << std::endl;

        if (strstr(buff, "controls"))
        {
            std::cout << "Beginning Control Reception..." << std::endl;
            ClientSocket.deliver(send.c_str());
            break;
        }
    }

    char buffer[MAX_BYTES];
    memset(buffer, '\0', MAX_BYTES);

    while (ControlType == 0)
    {
        ClientSocket.receiveBlock(buffer);
        std::cout << buffer << std::endl;

        // Logic to Determine Player Controls
        if (buffer[0] == one)
        {
            ControlType = 1;
            break;
        }
        else if (buffer[0] == two)
        {
            ControlType = 2;
            break;
        }
        else
        {
            std::cout << "Failure to Set Controls" << std::endl;
        }
    }

    // Display controls
    std::cout << "\033[2J\033[1;1H";
    if (ControlType == 1)
    {
        std::cout << player.GetName() << "'s controls are:"
                  << " Up/Down" << std::endl;
    }
    else if (ControlType == 2)
    {
        std::cout << player.GetName() << "'s controls are:"
                  << " Left/Right" << std::endl;
    }

    std::string ready = "ready";
    ClientSocket.deliver(ready.c_str());

    sleep(5);
}

// Displayed Before Game Starts
void GameControllerClient::CountDownScreen()
{
    // there should be a main loop constantly listening to the server
    // when that listener observes the countdownscreen command
    // it should call this function
    char buffer[MAX_BYTES];
    memset(buffer, '\0', MAX_BYTES);

    while (!strstr(buffer, "countdown"))
    {
        ClientSocket.receive(buffer);
    }

    std::cout << "\033[2J\033[1;1H";
    std::cout << "Game Starting in..." << std::endl;

    std::cout << "\33[2K\r3" << std::flush;
    sleep(1);
    std::cout << "\33[2K\r2" << std::flush;
    sleep(1);
    std::cout << "\33[2K\r1" << std::flush;
    sleep(1);
    std::cout << "\033[2J\033[1;1H";
}

// Displayed After Player Loses
void GameControllerClient::GameOverMenu()
{
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Game Over!" << std::endl;
    std::cout << "Your final score is:" << std::endl;
    DisplayScore();
    std::cout << "Thanks for playing!\n";
    sleep(2);
}

// Update Player Location
void GameControllerClient::MovePlayer()
{
    // Async Keyboard catch
    int keyboard_input = getch();

    std::string direction = "";
    std::string moved = "";
    std::string movement = "";

    if (ControlType == 1)
    {
        switch (keyboard_input)
        {
        case KEY_UP:
        {
            player.MoveUp();
            direction = "y";
            moved = "1";
            movement = direction + moved;

            // Send to Server
            ClientSocket.deliver(movement.c_str());
            break;
        }
        case KEY_DOWN:
        {
            player.MoveDown();
            direction = "y";
            moved = "2";
            movement = direction + moved;

            // Send to Server
            ClientSocket.deliver(movement.c_str());
            break;
        }
        default:
        {
            direction = "y";
            moved = "0";
            movement = direction + moved;

            // Send to Server
            ClientSocket.deliver(movement.c_str());
            break;
        }
        }
    }
    else if (ControlType == 2)
    {
        switch (keyboard_input)
        {
        case KEY_LEFT:
        {
            player.MoveLeft();
            direction = "x";
            moved = "1";
            movement = direction + moved;

            // Send to Server
            ClientSocket.deliver(movement.c_str());
            break;
        }
        case KEY_RIGHT:
        {
            player.MoveRight();
            direction = "x";
            moved = "2";
            movement = direction + moved;

            // Send to Server
            ClientSocket.deliver(movement.c_str());
            break;
        }
        default:
        {
            direction = "x";
            moved = "0";
            movement = direction + moved;

            // Send to Server
            ClientSocket.deliver(movement.c_str());
            break;
        }
        }
    }
}

//
void GameControllerClient::UpdateGame(WINDOW *window)
{
    char scoreBuffer[MAX_BYTES];
    char levelBuffer[MAX_BYTES];
    char mapBuffer[GAMEBOARD_BUFSIZE];

    memset(scoreBuffer, '\0', MAX_BYTES);
    memset(levelBuffer, '\0', MAX_BYTES);
    memset(mapBuffer, '\0', GAMEBOARD_BUFSIZE);

    // Check Server Connection
    ServerConnection();

    // Receive Data From Server
    ClientSocket.deliver("? map");
    while (!strlen(mapBuffer))
    {
        ClientSocket.receive(mapBuffer, GAMEBOARD_BUFSIZE);
    }

    std::string map = std::string(mapBuffer);

    // Get the score from the server
    ClientSocket.deliver("? score");
    while (!strlen(scoreBuffer))
    {
        ClientSocket.receive(scoreBuffer);
    }

    std::string score = std::string(scoreBuffer);

    // Get Level Infor from Server
    ClientSocket.deliver("? level");
    while (!strlen(levelBuffer))
    {
        ClientSocket.receive(levelBuffer);
    }

    std::string level = std::string(levelBuffer);

    // Print Screen
    board.loadFromStr(map);
    board.print(window, score, level);

    // Movement Selection (handles sending move to server)
    MovePlayer();

    // Check if Collision Occurred
    CheckCollisions();

    // Server say there was a collision
    if (GetCollisionOccur())
    {
        pair<int, int> coord = board.getPlayerCoord();

        board.triggerExplosion(coord.first, coord.second);

        for (int i = 0; i < 30; i++)
        {
            board.print(window, score, level);
            usleep(150);
        }

        SetGameOver(true);
        std::cout << "GAME IS OVER\n";
        return;
    }

    // Check Server Connection
    ServerConnection();
}

// Check Collisions
void GameControllerClient::CheckCollisions()
{
    char buffer[MAX_BYTES];
    memset(buffer, '\0', MAX_BYTES);

    while (!strlen(buffer))
    {
        ClientSocket.receive(buffer);
    }

    if (strstr(buffer, "collision_true"))
    {
        SetCollision(true);
    }
}

////////////////////////////////
///                          ///
///         Getters          ///
///                          ///
////////////////////////////////

// Get GameQuit Bool
bool GameControllerClient::GetQuitGame()
{
    return QuitGame;
}

// Get Player Object
Player GameControllerClient::GetPlayerObject()
{
    return player;
}

// Get ServerConnected Bool
bool GameControllerClient::GetServerConnection()
{
    return ServerConnected;
}

// Get Game Over
bool GameControllerClient::GetGameOver()
{
    return GameOver;
}

// Get Collision
bool GameControllerClient::GetCollisionOccur()
{
    return Collision;
}

////////////////////////////////
///                          ///
///         Setters          ///
///                          ///
////////////////////////////////

// Set GameQuit bool
void GameControllerClient::SetQuitGame(bool QuitGameSet)
{
    QuitGame = QuitGameSet;
}

// Set ServerConnected Bool
void GameControllerClient::SetServerConnection(bool SetServerConnected)
{
    ServerConnected = SetServerConnected;
}

// Set Game Over
void GameControllerClient::SetGameOver(bool GameOverSet)
{
    GameOver = GameOverSet;
}

// Set Collision
void GameControllerClient::SetCollision(bool CollisionBool)
{
    Collision = CollisionBool;
}

void GameControllerClient::DisplayScore()
{
    usleep(300);

    // clear buffer of any old game data
    ClientSocket.clearBuffer();

    // Ask Server for score
    std::string msg = "? score";
    ClientSocket.deliver(msg.c_str());

    // Wait for server to send leaderboard
    char res[MAX_BYTES];
    memset(res, '\0', MAX_BYTES);
    ClientSocket.receiveBlock(res);

    // Display Display the final score
    std::cout << res << std::endl;

    sleep(3);

    // User Input to Return to Menu
}