#ifndef CAVE_LEVEL_H
#define CAVE_LEVEL_H

#include "builder.h"
#include "object.h"
#include "random.h"
#include <algorithm>
#include <iostream>

class CaveLevel : public LevelBuilder
{
public:

    /**
     * Constructor for a CaveLevel object
     * 
     * @param cols - Number of columns for a row of the level
     **/
    CaveLevel(int rows, int cols, int screenHeight) : LevelBuilder(rows, cols, screenHeight){};

    /**
     * Constructs the entire level and stores the level
     * in the level container
     **/
    void construct();

    /**
     * Re-Constructs the entire level and stores the level
     * in the level container
     **/
    void reconstruct()
    {
        clear();
        construct();
    }

    /**
     * Returns the name of the level
     * 
     * @returns - name of the level
     **/
    string name()
    {
        return "Creepy Caves";
    }

    /**
     * Returns a new direction
     * 
     * @param direction - The direction of the center
     * 
     * @returns - The new direction
     **/
    int adjustDirection(int direction);

    /**
     * Returns the new center of the player space
     * 
     * @param center - The current center
     * @param direction - The direction of the center
     * 
     * @returns - The new center
     **/
    int adjustCenter(int center, int direction);

    /**
     * Returns a new tolerance based on the passed tolerance
     * 
     * @param tolerance - The tolerance percentage
     * 
     * @returns - The new tolerance percentage
     **/
    double adjustTolerance(double tolerance);

    /**
     * Returns the next available row of the level
     * 
     * @returns - A vector or row of Object pointers
     **/
    vector<char> nextRow()
    {
        vector<char> row = level.at(0);
        level.pop_front();

        return row;
    }

    /**
     * Indicates if a row is available in the level to be
     * retrieved
     * 
     * @returns - True if a row is available
     **/
    bool rowAvailable()
    {
        return level.size() > 0;
    }

    /**
     * Clears the contents of the matrix by freeing
     * memory and deleting all cells
     **/
    void clear()
    {
        level.clear();
    }

    /**
     * Destructor for the CaveLevel
     **/
    ~CaveLevel();
};

#endif // !CAVE_LEVEL_H
