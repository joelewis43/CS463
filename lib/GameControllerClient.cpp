//
// Created by Devin Gendron on 2019-10-24.
//

#include "../headers/GameControllerClient.h"
#include "../headers/Player.h"
#include "../headers/clientSocket.h"

////////////////////////////////
///                          ///
/// Constructors/Destructors ///
///                          ///
////////////////////////////////

// Constructor
GameControllerClient::GameControllerClient() : ClientSocket("127.0.0.1", 99556)
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

    if(GetQuitGame() == false)
    {
        // Initialize ncurses
        initscr();

        // Settings
        noecho();
        // cbreak(void);

        // Set Arrow Keys to Non-Blocking
        keypad(stdscr, TRUE);
        timeout(1);
        nodelay(stdscr, TRUE);

        // Display Game Count Down
        CountDownScreen();

        // Begin Game
        while(GetGameOver() != true && GetServerConnection() == true)
        {
            UpdateGame();
        }
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

    // Game Ends
    // Clear Screen
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Thanks for playing!" << std::endl;
    endwin();
    sleep(1);
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
                    NameMenu();
                    AwaitingPlayer();   // Listening to Server / Tell Server Client is Ready
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
void GameControllerClient::LeaderBoard()
{
    // Open File and View Leader Boards
    // Clear Screen
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Leader Board Function" << std::endl;
    sleep(0.5);

    // Ask Server for LeaderBoard
    const char *msg = "? leaderboard";
    ClientSocket.deliver(msg);

    // Wait for server to send leaderboard
    char res[MAX_BYTES];
    ClientSocket.receiveBlock(res);

    // Display Leader Board
    std::cout << "\033[2J\033[1;1H";
    std::cout << "\tLeaderboard" << std::endl;
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
                const char *msg = "! name";
                ClientSocket.deliver(msg);

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
    if(!ClientSocket.getConnection())
    {
        SetServerConnection(false);
    }
}

// Await Player Server Connection
void GameControllerClient::AwaitingPlayer()
{
    bool PlayerJoined1 = false;
    bool PlayerJoined2 = false;

    std::cout << "\033[2J\033[1;1H";
    std::cout << "Waiting for your partner..." << std::endl;
    std::cout << "Thank you for your patience" << std::endl;

    PlayerJoined1 = true;
    char buffer[MAX_BYTES];

    while(PlayerJoined1 != true && PlayerJoined2 != true)
    {
        // send a command querying server for other players connection status
        const char *msg = "? otherPlayer";
        ClientSocket.deliver(msg);

        // get the servers response
        ClientSocket.receiveBlock(buffer);

        // if the other player has joined
            // PlayerJoined2 = true
    }

    std::cout << "The Other Player Has Joined!" << std::endl;
    sleep(1);
}

// Player Selects Controls
void GameControllerClient::ControlSelection()
{
    // Ask the server what controls you are assigned
    const char *msg = "? controls";
    ClientSocket.deliver(msg);

    char buffer[MAX_BYTES];
    ClientSocket.receiveBlock(buffer);

    // Logic to Determine Player Controls

    // Display controls
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Your controls are:" << std::endl;
    // one or the other
        // std::cout << "Up/Down: " << /*Rand.Player*/ std::endl;
        // std::cout << "Left/Right: " << /*Rand.Player*/ std::endl;
    sleep(5);
}

// Displayed Before Game Starts
void GameControllerClient::CountDownScreen()
{
    // there should be a main loop constantly listening to the server
    // when that listener observes the countdownscreen command
    // it should call this function


    // Send to clients
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
    // there should be a main loop constantly listening to the server
    // when that listener observes the countdownscreen command
    // it should call this function

    std::cout << "\033[2J\033[1;1H";
    std::cout << "Game Over!" << std::endl;
    std::cout << "Score: " << GetScore() << std::endl;
    std::cout << "Play Game? (y/n)" << std::endl;
}

// Update Player Location
void GameControllerClient::MovePlayer()
{
    // Async Keyboard catch
    int keyboard_input = getch();
    
    // add input to move command
    std::string input = "move ";
    std::string move = std::to_string(keyboard_input);
    input.append(move);

    switch(keyboard_input)
    {
        case KEY_UP:
        {
            CheckCollisions();
            if(GetCollisionOccur() == false)
            {
                player.MoveUp();
                // Send to Server
                ClientSocket.deliver(input.c_str());
                break;
            }
            else
            {
                // Game Over
                SetGameOver(true);
                break;
            }
        }
        case KEY_DOWN:
        {
            CheckCollisions();
            if(GetCollisionOccur() == false)
            {
                player.MoveDown();
                // Send to Server
                ClientSocket.deliver(input.c_str());
                break;
            }
            else
            {
                // Game Over
                SetGameOver(true);
                break;
            }
        }
        case KEY_LEFT:
        {
            CheckCollisions();
            if(GetCollisionOccur() == false)
            {
                player.MoveLeft();
                // Send to Server
                ClientSocket.deliver(input.c_str());
                break;
            }
            else
            {
                // Game Over
                SetGameOver(true);
                break;
            }
        }
        case KEY_RIGHT:
        {
            CheckCollisions();

            if(GetCollisionOccur() == false)
            {
                player.MoveRight();
                // Send to Server
                ClientSocket.deliver(input.c_str());
                break;
            }
            else
            {
                // Game Over
                SetGameOver(true);
                break;
            }
        }
    }
}

//
void GameControllerClient::UpdateGame()
{
    char buffer[MAX_BYTES];
    size_t bytes = 0;

    // Check Server Connection
    ServerConnection();

    // Receive Data From Server (non-blocking)
    bytes = ClientSocket.receive(buffer);

    /* 
        USE bytes TO DETERMINE IF UPDATE IS NEEDED
    */

    // Server say there was a collision
    if(GetCollisionOccur())
    {
        SetGameOver(true);
        return;
    }

    // Print Screen

    // Movement Selection (handles sending move to server)
    MovePlayer();

    // Check Server Connection
    ServerConnection();
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


void GameControllerClient::CheckCollisions() {}

bool GameControllerClient::GetCollisionOccur() {}

size_t GameControllerClient::GetScore() {}