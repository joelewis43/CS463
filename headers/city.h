#ifndef CITY_LEVEL_H
#define CITY_LEVEL_H

#include "builder.h"
#include "object.h"
#include "random.h"
#include <iostream>


class CityLevel : public LevelBuilder
{
public:
  /**
   * Constructor for a CityLevel object
   * 
   * @param cols - Number of columns for a row of the level
   **/
  CityLevel(int rows, int cols, int screenHeight) : LevelBuilder(rows, cols, screenHeight)
  {
  };

  /**
   * Constructs the entire level and stores the level
   * in the level container
   **/
  void construct();

  /**
   * Returns the new direction of the directional skew
   * based on the passed skew
   * 
   * @param direction - The direction of the skew
   * @param skew - The directional skew
   * 
   * @returns - A new direction (1 = right & 0 = left)
   **/
  int adjustDirection(int direction, double skew);

  /**
   * Returns a new tolerance based on the passed tolerance
   * 
   * @param tolerance - The tolerance percentage
   * 
   * @returns - The new tolerance percentage
   **/
  double adjustTolerance(double tolerance);

  /**
   * Returns a new directional skew based on the passed skew and 
   * direction
   * 
   * @param direction - The directional
   * @param skew - The directional skew
   * 
   * @returns - A new directional skew
   **/
  double adjustSkew(int direction, double skew);

  /**
   * Returns the next available row of the level
   * 
   * @returns - A vector or row of Object pointers
   **/
  vector<Object *> nextRow()
  {
    std::cout << level.size() << std::endl;
    vector<Object *> row = level.at(0);
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
   * Destructor for the CityLevel
   **/
  ~CityLevel();
};

#endif // !CITY_LEVEL_H
