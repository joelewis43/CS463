#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>

#include "object.h"
#include "character.h"
#include "comet.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

#ifndef GAMEMATRIX_H
#define GAMEMATRIX_H

class GameMatrix
{
private:
    /**
     * Underlying matrix container
     * 
     * 
     * Increased Performance Opportunity:
     * 
     * 2D vector are simple to understand and use, however performance can be
     * increased by converting the 2D vector to a single vector. This will decrease
     * cache misses and increase cache hits. However, this will require adding a
     * row and column member to the class and  computing the end of a row for each
     * matrix iteration
     **/
    vector<vector<Object *>> buffer;

    /**
     * Applies a function for each cell in the matrix to
     * generate a string
     * 
     * @param func - A function that returns a character
     * 
     * @returns - Returns a string with each character beign a cell
     *            from the matrix and each row delimited by \n characters
     **/
    string stringMap(std::function<const char(Object *)> func);

public:
    /**
     * Constructor for the GameMatrix class
     * 
     * @param row - Number of rows in the matrix
     * @param col - Number of columns in the matrix
     **/
    GameMatrix(int row, int col);

    /*************************
     * Methods
     ************************/

    /**
     * Clears the matrix by setting all indices to null
     **/
    void clear();


    /**
     * Gets an object from a cell in the matrix
     * 
     * @param row - Row in the matrix
     * @param col - Column in the matrix
     * 
     * @returns - A pointer to an object in the matrix
     **/
    Object *at(int row, int col);

    /**
     * Updates an index in the matrix with the passed value
     * 
     * @param row - Row the item should added to
     * @param col - COlumn the item should be added to
     **/
    void update(int row, int col, Object *object);

    /**
     * Advances the board by one-step by moving the contents
     * of the matrix down by one row.
     **/
    void advance();

    /**
     * Initializes or updates the matrix with objects based on
     * the IDs indicated in the input string.
     * 
     * @param input - String encoded with the object IDs and delimited by
     *                \n characters
     **/
    void loadFromStr(string input);

    /**
     * Prints the string representation of the matrix to the terminal
     * in a game board.
     **/
    void printToScreen();

    /**
     * Returns a string representation of the matrix.
     * The string contains the ASCII characters for objects
     * in the matrix. The string is meant to be used for displaying
     * items on the screen.
     * 
     * Each row is delimited by \n characters
     * 
     * @returns - String representation of the matrix
     **/
    string toString();

    /**
     * Returns a string representation of the matrix.
     * The string contains the IDs for characters for objects
     * in the matrix. This string is meant to be sent over
     * network requests.
     * 
     * Each row is delimitted by \n characters
     * 
     * @returns - ID representation of the matrix
     **/
    string serialize();

    /**
     * Overloads the substrict operator
     * 
     * @param index - The row in the matrix
     * 
     * @returns - A reference to a row in the matrix
     **/
    vector<Object *> &operator[](int index);

    /**
     * Descructor for the class
     **/
    ~GameMatrix();
};

#endif // !GAMEMATRIX_H
