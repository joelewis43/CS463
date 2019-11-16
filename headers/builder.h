#ifndef LEVEL_BUILDER_H
#define LEVEL_BUILDER_H

#include <vector>
#include "object.h"

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
    vector<vector<Object *>> level;

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
    vector<Object *> nextRow()
    {
        vector<Object *> row = level.at(0);
        level.erase(level.begin());

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
        for (vector<Object *> &row : level)
        {
            for (int i = 0; i < row.size(); i++)
            {
                Object *obj = row[i];

                if (obj != nullptr)
                {
                    delete obj;
                }

                row[i] = nullptr;
            }
        }
    }

    /**
     * Destructor for the LevelBuilder
     **/
    virtual ~LevelBuilder(){};
};

#endif // !LEVEL_BUILDER_H
