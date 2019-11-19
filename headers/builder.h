#ifndef LEVEL_BUILDER_H
#define LEVEL_BUILDER_H

#include <vector>
#include <deque>
#include "object.h"
#include <iostream>

using std::deque;
using std::vector;

class LevelBuilder
{
protected:
    // Number of rows to generate
    int rows;
    // The width or number of columns that the
    // level should have per row of the level
    int cols;
    // Height of the terminal window
    int screenHeight;
    // Matrix containing the objects of the level
    deque<vector<Object *>> level;

public:
    /**
     * Constructor for a LevelBuilder object
     * 
     * @param rows - Number of rows that should generated for the level
     * @param cols - Number of columns for a row of the level
     **/
    LevelBuilder(int rows, int cols, int screenHeight)
    {
        this->rows = rows;
        this->cols = cols;
        this->screenHeight = screenHeight;
    }

    /**
     * Constructs the entire level and stores the level
     * in the level container
     **/
    virtual void construct() = 0;

    /**
     * Returns the next available row of the level
     * 
     * @returns - A vector or row of Object pointers
     **/
    virtual vector<Object *> nextRow() = 0;

    /**
     * Indicates if a row is available in the level to be
     * retrieved
     * 
     * @returns - True if a row is available
     **/
    virtual bool rowAvailable() = 0;

    /**
     * Clears the contents of the matrix by freeing
     * memory and deleting all cells
     **/
    virtual void clear() = 0;

    /**
     * Destructor for the LevelBuilder
     **/
    virtual ~LevelBuilder() {}
};

#endif // !LEVEL_BUILDER_H
