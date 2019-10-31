#include "builder.h"

class AsteroidLevel : public LevelBuilder {
public:
  AsteroidLevel(int cols) : LevelBuilder(cols) {};
  void construct();
  vector<Object *> build();
};
