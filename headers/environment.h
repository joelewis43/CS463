#include "matrix.h"
#include "builder.h"
#include "city.h"
#include <ncurses.h>

#ifndef GAME_ENVIRONMENT_H
#define GAME_ENVIRONMENT_H

class Environment
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
    WINDOW *window;
    /**
     * Seeds the top row of the game matrix with the next
     * available row from the current level
     **/
    void seed();

public:
    /**
     * Constructor for an Environment
     * 
     * @param window - A pointer to an ncurses window
     * @param levelRows - Number of rows each level should have
     **/
    Environment(WINDOW *window, int levelRows);

    /**
     * Advances the game forward one step by moving all rows of the
     * game matrix down one row and adding the next available row for
     * a level to the top row of the game matrix.
     **/
    void advance();

    /**
     * Increases the levelIndex pointer by one, so the the next
     * available level will be used.
     **/
    void nextLevel();

    /**
     * Returns the current level being used for the game
     * 
     * @returns - A pointer to a level
     **/
    LevelBuilder *currentLevel();


    /**
     * Prints the contents of the GameMatrix ot the ncurses
     * window
     **/
    void print();

    /**
     * Destructor for the Environment object
     **/
    ~Environment();
};

#endif // !GAME_ENVIRONMENT_H
