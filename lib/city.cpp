#include "city.h"

void CityLevel::construct() {
  // Determines the free space
  int direction = 1;
  double tolerance = 0.75, skew = 0.50;

  for (int i = 0; i < rows; i++)
  {
    vector<Object *> row(cols);
    // Gives the maximum number of columns that can be used for the skyscrapers
    double usableArea = cols * (1 - tolerance);
    // Left Block area
    int left = static_cast<int>(usableArea * skew);
    // Right Block area
    int right = static_cast<int>(usableArea * (1 - skew));
    
    int leftArea = randomInt(0, left);

    int rightArea = randomInt(cols - right, cols - 1);

    // Setup the row for the city skyscraper
    for (int j = 0; j <= leftArea; j++)
    {
      row[j] = new Comet();
    }
    for (int j = cols - 1; j >= rightArea; j--)
    {
      row[j] = new Comet();
    }
    
    // Add row to the level
    level.push_back(row);

    // Lower the tolerance (gap length for player)
    tolerance = adjustTolerance(tolerance);
    // Adjust the skew percentage to the left or right bounds
    skew = adjustSkew(direction, skew);
    // Change the direction or trajectory of the skew
    direction = adjustDirection(direction, skew);
  }
}

double CityLevel::adjustTolerance(double tolerance)
{
  if (tolerance > 0.20)
  {
    return tolerance * (1 - 0.07); // Decrease by 7%
  }

  return tolerance;
}

double CityLevel::adjustSkew(int direction, double skew)
{
  // Shift the skew to the right
  if (direction == 1)
  {
    return skew * (1 + 0.07);
  }
  // Shift the skew to the left
  return skew * (1 - 0.07);
}

int CityLevel::adjustDirection(int direction, double skew)
{
  if (skew >= 0.85)
  {
    return 0;
  } else if (skew <= 0.15)
  {
    return 1;
  }

  return direction;
}

vector<Object *> CityLevel::nextRow()
{
  vector<Object *> row = level.at(0);
  level.erase(level.begin());

  return row;
}

void CityLevel::clear()
{
  for (vector<Object *> &row : level)
  {
    for (Object *obj : row)
    {
      if (obj != nullptr)
      {
        delete obj;
      }
    }

    row.clear();
  }

  level.clear();
}

CityLevel::~CityLevel()
{
  clear();
}