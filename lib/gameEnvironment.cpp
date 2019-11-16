#include "../headers/gameEnvironment.h"

GameEnvironment::GameEnvironment()
{
}

GameEnvironment::GameEnvironment(WINDOW *window, int levelRows)
{
    int height = 0, width = 0;
    this->levelIndex = 0;
    this->levelRows = levelRows;
    this->window = window;

    getmaxyx(window, height, width);
    height = height - 2, width = width - 3;
    matrix = GameMatrix(height, width);

    AsteroidLevel *asteroidLevel = new AsteroidLevel(levelRows, width, height);
    CityLevel *cityLevel = new CityLevel(levelRows, width, height);

    levels.push_back(asteroidLevel);
    levels.push_back(cityLevel);
}

GameEnvironment::GameEnvironment(int rows, int cols, int levelRows)
{
    int height = rows, width = cols;
    this->levelIndex = 0;
    this->levelRows = levelRows;
    this->window = nullptr;

    matrix = GameMatrix(height, width);

    // AsteroidLevel *asteroidLevel = new AsteroidLevel(levelRows, width, height);
    CityLevel *cityLevel = new CityLevel(levelRows, width, height);

    // levels.push_back(asteroidLevel);
    levels.push_back(cityLevel);
}

void GameEnvironment::seed()
{
    // If there's no more content available, nothing can be seeded
    if (!levelAvailable() && !currentLevel()->rowAvailable())
    {
        return;
    }
    // Advance to the next level, if the current level is complete
    if (!currentLevel()->rowAvailable())
    {
        nextLevel();
    }

    // TODO: Implement method for transition (break or respite)
    // for player in between levels

    vector<Object *> newRow = currentLevel()->nextRow();
    matrix.updateTop(newRow);
}

void GameEnvironment::advance(Player &player)
{
    // Advance all rows in the matrix forward by 1
    matrix.advance();
    // Update the player's position (This will put the player in the row or position
    // they were before advancing the matrix by one)
    updatePlayerPosition(player);
    // Add the next availbale row from the game level
    seed();
}

void GameEnvironment::nextLevel()
{
    if (levelIndex >= levels.size() - 1)
    {
        return;
    }

    levelIndex++;
}

bool GameEnvironment::levelAvailable()
{
    return levelIndex < levels.size() - 1;
}

LevelBuilder *GameEnvironment::currentLevel()
{
    return levels.at(levelIndex);
}

void GameEnvironment::setInitialPlayerPosition(Player &player)
{
    matrix.initPlayerObject(player.GetLocX(), player.GetLocY());
}

void GameEnvironment::updatePlayerPosition(Player &player)
{
    matrix.updatePlayerPosition(player.GetLocY(), player.GetLocX());
}

void GameEnvironment::print()
{
    matrix.print(window);
}

string GameEnvironment::getMap()
{
    return matrix.serialize();
}

void GameEnvironment::updateGameMatrix(string data)
{
    // Load objects into the matrix
    matrix.loadFromStr(data);
}

GameEnvironment::~GameEnvironment()
{
    for (LevelBuilder *level : levels)
    {
        delete level;
    }

    matrix.clear();
}