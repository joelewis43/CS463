#include "../headers/asteroid.h"
#include <iostream>

void AsteroidLevel::construct()
{
    int minHeight = 2, minWidth = 2, maxHeight = 5, maxWidth = 5;
    int numAsteroids = 12, incrementor = screenHeight;
    // Frame container
    // Add Asteroids to the frame
    deque<vector<char>> frame = deque<vector<char>>(screenHeight, vector<char>(cols, NULL_SPRITE));

    std::cout << incrementor << std::endl;

    // Frame by Frame create the asteroids that will be used for the level
    for (int i = 0; i < rows; i += incrementor)
    {
        for (int j = 0; j < numAsteroids; j++)
        {
            int xc = 0, yc = 0;
            int height = randomInt(minHeight, maxHeight), width = randomInt(minWidth, maxWidth);
            int xCoord = randomInt(0, cols - width), yCoord = randomInt(0, screenHeight - height);

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

                    frame[sy][sx] = COLLISION_SPRITE;
                    xc += 1;
                }
                xc = 0;
                yc += 1;
            }
        }

        for (int j = 0; j < frame.size(); j++)
        {
            level.push_back(frame[j]);
            std::fill(frame[j].begin(), frame[j].end(), NULL_SPRITE);
        }

        // Increase difficulty by increasing the number of asteroids per frame
        numAsteroids += 4;
    }
}

AsteroidLevel::~AsteroidLevel() {}
