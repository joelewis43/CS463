#ifndef ASTEROID_LEVEL_H
#define ASTEROID_LEVEL_H

#include "builder.h"
#include "random.h"
#include <math.h>
#include <algorithm>

class AsteroidLevel : public LevelBuilder
{
public:
  /**
   * Constructor for a LevelBuilder object
   * 
   * @param rows - Number of rows that should generated for the level
   * @param cols - Number of columns for a row of the level
   **/
  AsteroidLevel(int rows, int cols, int screenHeight) : LevelBuilder(rows, cols, screenHeight)
  {
  };
  /**
   * Constructs the entire level and stores the level
   * in the level container
   **/
  void construct();

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
      for (vector<char> &row : level)
      {
          for (int i = 0; i < row.size(); i++)
          {
              row[i] = NULL_SPRITE;
          }
      }
  }

  /**
   * Destructor for the AsteroidLevel
   **/
  ~AsteroidLevel();
};

#endif // !ASTEROID_LEVEL_H