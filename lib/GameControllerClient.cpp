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
GameControllerClient::GameControllerClient() : ClientSocket("", 88432)
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
    sleep(2);

    // Ask Server for LeaderBoard
    //ClientSocket.deliver();

    // Handshake From Server to Recognize

    // Wait for server to send leaderboard
    //ClientSocket.receive();

    // Display Leader Board

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
    std::string buffer;

    while(PlayerJoined1 != true && PlayerJoined2 != true)
    {
        // ClientSocket.receive(buffer.c_str());

        // Logic For Player Connection
            // Set True
    }
    std::cout << "The Other Player Has Joined!" << std::endl;
    sleep(1);
}

// Player Selects Controls
void GameControllerClient::ControlSelection()
{
    std::string buffer;

    // Ask What controls for each player are
    // IO

    // send to server
    // ClientSocket.deliver(buffer.c_str());

    // Logic to Determine Player Controls

    // Display controls
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Player Controls" << std::endl;
    std::cout << "Up/Down: " << /*Rand.Player*/ std::endl;
    std::cout << "Left/Right: " << /*Rand.Player*/ std::endl;
    sleep(5);
}

// Displayed Before Game Starts
void GameControllerClient::CountDownScreen()
{
    // If can start countdown - start
    //ClientSocket.receive();


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
    // Get Score Data
    //ClientSocket.receive();

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

    switch(keyboard_input)
    {
        case KEY_UP:
        {
            CheckCollisions();
            if(GetCollisionOccur() == false)
            {
                player.MoveUp();
                // Send to Server
                //ClientSocket.deliver();
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
                //ClientSocket.deliver();
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
                //ClientSocket.deliver();
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
                //ClientSocket.deliver();
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
    size_t buffer[255];

    // Check Server Connection
    ServerConnection();

    // Receive Data From Server
    //ClientSocket().receive(buffer);

    // Server say there was a collision
    if(GetCollisionOccur())
    {
        SetGameOver(true);
        return;
    }

    // Print Screen

    // Movement Selection
    MovePlayer();

    // Send to Server
    //ClientSocket().deliver();

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