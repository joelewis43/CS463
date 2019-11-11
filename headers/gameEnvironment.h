#ifndef GAME_ENVIRONMENT_H
#define GAME_ENVIRONMENT_H

#include "matrix.h"
#include "builder.h"
#include "city.h"
#include "asteroid.h"
#include "Player.h"
#include <ncurses.h>

class GameEnvironment
{
private:
    // The index of the current level
    int levelIndex;
    // Number of rows each level should have
    int levelRows;
    // Matrix used for storing game objects
    GameMatrix matrix;
    // List of levels used to change the game matrix
    vector<LevelBuilder *> levels;
    // The ncurses window used to display the game data
    WINDOW *window = nullptr;
    /**
     * Seeds the top row of the game matrix with the next
     * available row from the current level
     **/
    void seed();

public:
    /**
     * Constructor for an Environment
     **/
    GameEnvironment();

    /**
     * Constructor for an Environment
     * 
     * @param window - A pointer to an ncurses window
     * @param levelRows - Number of rows each level should have
     **/
    GameEnvironment(WINDOW *window, int levelRows);

    /**
     * Constructor for an Environment
     * 
     * @param rows - Number of rows for the gameboard
     * @param cols - Number of cols for the gameboard
     * @param levelRows - Number of rows each level should have
     **/
    GameEnvironment(int rows, int cols, int levelRows);

    /**
     * Advances the game forward one step by moving all rows of the
     * game matrix down one row and adding the next available row for
     * a level to the top row of the game matrix.
     * 
     * @param player - A reference to a player object
     **/
    void advance(Player &player);

    /**
     * Increases the levelIndex pointer by one, so the the next
     * available level will be used.
     **/
    void nextLevel();

    /**
     * Indicates if a level is available
     * 
     * @returns - True if there is a level available
     **/
    bool levelAvailable();

    /**
     * Returns the current level being used for the game
     * 
     * @returns - A pointer to a level
     **/
    LevelBuilder *currentLevel();

    /**
     * Sets the player's initial position on the game board
     * 
     * @param player - A reference to a player object
     **/
    void setInitialPlayerPosition(Player &player);

    /**
     * Updates the player's position on the game matrix
     * 
     * @param player - A reference to a player object
     **/
    void updatePlayerPosition(Player &player);

    /**
     * Prints the contents of the GameMatrix ot the ncurses
     * window
     **/
    void print();

    /**
     * Returns the contents of the game board as a string
     * 
     * @returns - Game board with rows delimited with new line
     * characters
     **/
    string getMap();

    /**
     * Updates the game board based on a blueprint based on
     * the contents of the encoded string
     * 
     * @param data - Encoded string with rows delimited by '\n'
     **/
    void updateGameMatrix(string data);

    /**
     * Destructor for the Environment object
     **/
    ~GameEnvironment();
};

#endif // !GAME_ENVIRONMENT_H
