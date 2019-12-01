#include "../headers/cave.h"

void CaveLevel::construct()
{

  double tolerance = 0.35, playerSpace, playerLeft, playerRight;

  // get initiail level state
  int direction = randomInt(-1, 1);
  int center = cols / 2;

  // build the level
  for (int i = 0; i < rows; i++)
  {

    // init a row with collision characters
    vector<char> row(cols, COLLISION_SPRITE);

    // determine number of cols used for the user
    if (tolerance < 0)
    {
      playerSpace = cols * (-tolerance);
    }
    else
    {
      playerSpace = cols * tolerance;
    }
    
    // determine edges of players space
    playerLeft = center - playerSpace / 2;
    playerRight = center + playerSpace / 2;

    // remove collision sprites from player space
    for (int j = playerLeft; j <= playerRight; j++)
    {
      row[j] = NULL_SPRITE;
    }

    // Add row to the level
    level.push_back(row);

    // Lower the tolerance (gap length for player)
    tolerance = adjustTolerance(tolerance);

    // Update the direction of the center's movement
    direction = adjustDirection(direction);

    // Change the center of the player space
    center = adjustCenter(center, direction);
  }
}

double CaveLevel::adjustTolerance(double tolerance)
{

  /**
   * Positive tolerance shrinks cave
   * Negative expands cave
   * 
   * 8% chance to reverse direction when expanding
   * 2% chance to reverse direction when shrinking
   * 
  **/
  if (tolerance > 0) {
    if (randomInt(1, 50) == 1)
    {
      tolerance = -tolerance;
    }
  }
  else
  {
    if (randomInt(1, 100) <= 8)
    {
      tolerance = -tolerance;
    }
  }
  

  // handle positive tolerance (shrink)
  if (tolerance > 0)
  {
    if (tolerance > 0.1)
    {
      return tolerance * (1 - 0.05); // Decrease by 5%
    }
  }

  // handle negative tolerance (expand)
  else
  {
    if (tolerance > -0.35)
    {
      return tolerance * (1 + 0.05); // Increase by 5%
    }
  }

  return tolerance;
}

int CaveLevel::adjustDirection(int direction)
{
  /**
   * When moving left or right, there is a
   *    90% chance to maintain direction
   *    8% chance to flip directions
   *    2% chance to go straight
   * 
   * When moving straight, there is a
   *    80% chance to stat straight
   *    10% chance to go left
   *    10% chance to go right
  **/

  int roll = randomInt(1, 100);
  
  switch (direction)
  {
  // left
  case -1:
    if (roll <= 90) { break; }
    else if (roll > 98) { direction = 0; }
    else { direction = -direction; }

    break;

  // straight
  case 0:
    if (roll <= 80) { break; }
    else if (roll > 90) { direction = 1; }
    else { direction = -1; }

    break;

  //right
  case 1:
    if (roll <= 90) { break; }
    else if (roll > 98) { direction = 0; }
    else { direction = -direction; }

    break;

  default:
    // std::cout << "Something went very wrong\n";
    std::cout << "DEBUG: " << direction << std::endl;
    break;
  }

  return direction;
}

int CaveLevel::adjustCenter(int center, int direction)
{
  // update center
  center += direction;

  // handle cases where center moves off edge
  if (center < 0) { center = 0; direction = 1; }
  if (center > cols-1) { center = cols-1; direction = -1; }

  return center;
}

CaveLevel::~CaveLevel() {}
