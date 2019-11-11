#ifndef ASTEROID_LEVEL_H
#define ASTEROID_LEVEL_H

#include "builder.h"
#include "random.h"
#include <math.h>

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
    construct();
  };
  /**
   * Constructs the entire level and stores the level
   * in the level container
   **/
  void construct();

  /**
   * Destructor for the AsteroidLevel
   **/
  ~AsteroidLevel();
};

#endif // !ASTEROID_LEVEL_H