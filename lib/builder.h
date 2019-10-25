#include <vector>
#include "object.h"

using std::vector;

#ifndef LEVEL_BUILDER_H
#define LEVEL_BUILDER_H

class LevelBuilder
{
protected:
    // Number of rows to generate
    int rows;
    // The width or number of columns that the
    // level should have per row of the level
    int cols;
    // Matrix containing the objects of the level
    vector<vector<Object *>> level;
public:
    /**
     * Constructor for a LevelBuilder object
     * 
     * @param cols - Number of columns for a row of the level
     **/
    LevelBuilder(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
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
     * Clears the contents of the matrix by freeing
     * memory and deleting all cells
     **/
    virtual void clear() = 0;

    /**
     * Destructor for the LevelBuilder
     **/
    virtual ~LevelBuilder() {};
};

#endif // !LEVEL_BUILDER_H
