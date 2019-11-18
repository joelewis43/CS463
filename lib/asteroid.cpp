#include "../headers/asteroid.h"
#include <iostream>

void AsteroidLevel::construct()
{
    int minHeight = 4, minWidth = 5, maxHeight = 10, maxWidth = 20;
    int numAsteroids = 12, incrementor = rows / screenHeight;

    // Frame by Frame create the asteroids that will be used for the level
    for (int i = 0; i < rows; i += incrementor)
    {
        // Frame container
        vector<vector<Object *>> frame = vector<vector<Object *>>(screenHeight, vector<Object *>(cols));
        // Add Asteroids to the frame
        for (int j = 0; j < numAsteroids; j++)
        {
            int xc = 0, yc = 0;
            int height = randomInt(minHeight, maxHeight), width = randomInt(minWidth, maxWidth);
            int xCoord = randomInt(0, cols), yCoord = randomInt(0, screenHeight);

            for (int sy = yCoord; sy < screenHeight; sy++)
            {
                if (yc >= height)
                {
                    break;
                }

                for (int sx = xCoord; sx < cols; sx++)
                {
                    if (xc >= width)
                    {
                        xc = 0;
                        break;
                    }

                    frame[sy][sx] = new CollisionObject();
                    xc += 1;
                }
                xc = 0;
                yc += 1;
            }
        }

        for (int j = 0; j < frame.size(); j++)
        {
            level.push_back(frame[j]);
        }

        // Increase difficulty by increasing the number of asteroids per frame
        numAsteroids += 4;
    }
}

AsteroidLevel::~AsteroidLevel()
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
