#include "../headers/random.h"

int randomInt(int low, int high)
{
  return low + rand() % ((high + 1) - low);
}