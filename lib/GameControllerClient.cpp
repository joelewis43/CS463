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
GameControllerClient::GameControllerClient() : ClientSocket("127.0.0.1", 6235), board(CONTENT_HEIGHT, CONTENT_WIDTH - 1)
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

    // Menus
    MainMenu();

    // Display Game Count Down
    //CountDownScreen();

    if(GetQuitGame() == false)
    {
        // Initialize ncurses
        initscr();

        WINDOW *borderWindow = createBorderWindow();
        WINDOW *contentWindow = createContentWindow(borderWindow);

        // Settings
        noecho();
        // cbreak(void);

        // Set Arrow Keys to Non-Blocking
        keypad(stdscr, TRUE);
        timeout(1);
        nodelay(stdscr, TRUE);

        start_color();

        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_YELLOW, COLOR_BLACK);
        init_pair(3, COLOR_RED, COLOR_BLACK);

        // Begin Game
        while(GetGameOver() != true && GetServerConnection() == true)
        {
            UpdateGame(contentWindow);
            std::chrono::duration<int, std::milli> timespan(150);
            std::this_thread::sleep_for(timespan);
        }

        GameOverMenu();

        delwin(contentWindow);
        delwin(borderWindow);
    }
    else
    {
        // Quit
        // Clear Screen
        std::cout << "\033[2J\033[1;1H";
        std::cout << "Thanks for playing!" << std::endl;
        endwin();
        sleep(1);
    }

    std::cout << "I've made a huge mistake" << std::endl;
    endwin();
}

// Main Menu
void GameControllerClient::MainMenu()
{
    int selection = -1;
    char *msg = "! pReady";

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
                    // Tell Server Player is Ready to Play
                    ClientSocket.deliver(msg);
                    AwaitingPlayer();
                    NameMenu();
                    AwaitingPlayer();   // Listening to Server / Tell Server Client is Ready
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

    while(1)
    {
        // Clear Screen
        std::cout << "\033[2J\033[1;1H";

        // check if name exists
        if(player.GetName() == "")
        {
            // Display Menu to Enter Name
            std::cout << "Enter Your Name" << std::endl;
            std::cout << std::endl;
            std::cout << "3-5 Alphanumeric Characters Required" << std::endl;
            std::cout << "Press Enter to Continue" << std::endl;
            std::cout << std::endl;
            std::cout << "Name: ";
            std::cin >> name;

            if(name.size() >= 3 && name.size() <= 5)
            {
                // Set Name in Player Object
                player.SetName(name);

                // Tell Server the Name is Coming
                std::string msg = "! name";
                ClientSocket.deliver(msg.c_str());

                // Tell it to Server
                ClientSocket.deliver(name.c_str());
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

            if(name.size() >= 3 && name.size() <= 5)
            {
                // Set Name in Player Object
                player.SetName(name);

                // Tell Server the Name is Coming
                const char *msg = "! name";
                ClientSocket.deliver(msg);

                // Tell it to Server
                ClientSocket.deliver(name.c_str());
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
    if(ClientSocket.getConnection())
    {
        SetServerConnection(true);
    } else {
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

    while(PlayerJoined2 != true)
    {

        int bytes = ClientSocket.receive(buffer);
        if (bytes)
            std::cout << buffer << std::endl;

        if(strstr(buffer, "Matchmaking Completed!"))
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
    
    while(1)
    {
        if (ClientSocket.receive(buff))
            std::cout << "DEBUG: " << buff << std::endl;

        if(strstr(buff, "controls") == 0)
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
        if(buffer[0] == one)
        {
            ControlType = 1;
            break;
        }
        else if(buffer[0] == two)
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
    if(ControlType == 1)
    {
        std::cout << player.GetName() <<"'s controls are:" << " Up/Down" << std::endl;
    }
    else if (ControlType == 2)
    {
        std::cout << player.GetName() <<"'s controls are:" << " Left/Right" << std::endl;
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
}

// Update Player Location
void GameControllerClient::MovePlayer()
{
    // Async Keyboard catch
    int keyboard_input = getch();

    std::string direction = "";
    std::string moved = "";
    std::string movement = "";

    if(ControlType == 1)
    {
        switch(keyboard_input)
        {
            case KEY_UP:
            {
                player.MoveUp();
                direction = "yy";
                moved = "1";
                movement = direction + moved;

                // Send to Server
                ClientSocket.deliver(movement.c_str());
                break;
            }
            case KEY_DOWN:
            {
                player.MoveDown();
                direction = "yy";
                moved = "2";
                movement = direction + moved;

                // Send to Server
                ClientSocket.deliver(movement.c_str());
                break;
            }
            default:
            {
                direction = "yy";
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
        switch(keyboard_input)
        {
            case KEY_LEFT:
            {
                player.MoveLeft();
                direction = "xx";
                moved = "1";
                movement = direction + moved;

                // Send to Server
                ClientSocket.deliver(movement.c_str());
                break;
            }
            case KEY_RIGHT:
            {
                player.MoveRight();
                direction = "xx";
                moved = "2";
                movement = direction + moved;

                // Send to Server
                ClientSocket.deliver(movement.c_str());
                break;
            }
            default:
            {
                direction = "xx";
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
    std::string ack = "ack";
    char buffer[GAMEBOARD_BUFSIZE];
    size_t bytes = 0;

    memset(buffer, '\0', GAMEBOARD_BUFSIZE);

    // Check Server Connection
    ServerConnection();

    // Receive Data From Server (blocking)
    bytes = ClientSocket.receive(buffer, GAMEBOARD_BUFSIZE);

    ClientSocket.deliver(ack.c_str());

    /* 
        USE bytes TO DETERMINE IF UPDATE IS NEEDED
    */

    board.loadFromStr(std::string(buffer));

    // Check if Collision Occurred
    CheckCollisions();

    // Server say there was a collision
    if(GetCollisionOccur())
    {
        SetGameOver(true);
        return;
    }

    // Print Screen
    board.print(window);

    // Movement Selection (handles sending move to server)
    MovePlayer();

    // Check Server Connection
    ServerConnection();
}

// Check Collisions
void GameControllerClient::CheckCollisions()
{
    char buffer[MAX_BYTES];
    memset(buffer, '\0', MAX_BYTES);

    ClientSocket.receive(buffer);

    if(strcmp(buffer, "collision_true") == 0)
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
    sleep(3);

    // clear buffer of any old game data
    ClientSocket.clearBuffer();

    // Ask Server for score
    const char *msg = "? score";
    ClientSocket.deliver(msg);

    // Wait for server to send leaderboard
    char res[MAX_BYTES];
    memset(res, '\0', MAX_BYTES);
    ClientSocket.receiveBlock(res);

    // Display Display the final score
    std::cout << res << std::endl;

    sleep(5);

    // User Input to Return to Menu
}