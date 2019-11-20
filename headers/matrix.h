#ifndef GAMEMATRIX_H
#define GAMEMATRIX_H

#include <iostream>
#include <sstream>
#include <string>
#include <deque>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <ncurses.h>

#include "object.h"

using std::cout;
using std::endl;
using std::deque;
using std::string;
using std::vector;

class GameMatrix
{
private:
    // Cache Player's X coordinate
    int playerX;
    // Cache Player's Y coordinate
    int playerY;

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
    deque<vector<char>> buffer;

    /**
     * Applies a function for each cell in the matrix to
     * generate a string
     * 
     * @param func - A function that returns a character
     * 
     * @returns - Returns a string with each character beign a cell
     *            from the matrix and each row delimited by \n characters
     **/
    string stringMap(std::function<const char(char)> func);

public:
    /**
     * Default Constructor for the GameMatrix class
     * 
     * @param row - Number of rows in the matrix
     * @param col - Number of columns in the matrix
     **/
    GameMatrix();

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
     * Clears the terminal window
     **/
    void clearScreen();

    /**
     * Gets an object from a cell in the matrix
     * 
     * @param row - Row in the matrix
     * @param col - Column in the matrix
     * 
     * @returns - A character
     **/
    char at(int row, int col);

    /**
     * Updates an index in the matrix with the passed value
     * 
     * @param row - Row the item should added to
     * @param col - Column the item should be added to
     * @param ch - A character
     **/
    void update(int row, int col, char ch);

    /**
     * Advances the board by one-step by moving the contents
     * of the matrix down by one row.
     **/
    void advance();

    /**
     * Updates the top row of the matrix with the contents of the
     * passed vector
     * 
     * @param row - Row of Object pointers
     * 
     **/
    void updateTop(vector<char> &row);

    /**
     * Creates the PlayerObject and places it in the matrix at the
     * specified coordinates
     * 
     * @param x - X Coordinate
     * @param y - Y Coordinate
     **/
    void initPlayerObject(int x, int y);

    /**
     * Updates the player's position on the game matrix
     * 
     * @param newY - Y coordinate
     * @param newX - X Coordinate
     **/
    void updatePlayerPosition(int newY, int newX);

    /**
     * Initializes or updates the matrix with objects based on
     * the IDs indicated in the input string.
     * 
     * @param input - String encoded with the object IDs and delimited by
     *                \n characters
     **/
    void loadFromStr(string input);

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
     * Prints the contents of the GameMatrix ot the ncurses
     * window
     * 
     * @param window - A pointer to an ncurses window object
    **/
    void print(WINDOW *window);

    /**
     * Getter for the number of rows
     * 
     * @returns - The number of rows in the matrix
     **/
    int rows();

    /**
     * Getter for the number of columns
     * 
     * @returns - The numbe of columns in the matrix
     **/
    int cols();

    /**
     * Overloads the substrict operator
     * 
     * @param index - The row in the matrix
     * 
     * @returns - A reference to a row in the matrix
     **/
    vector<char> &operator[](int index);

    /**
     * Descructor for the class
     **/
    ~GameMatrix();
};

#endif // !GAMEMATRIX_H
