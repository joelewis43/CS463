#include "../headers/gameEnvironment.h"

GameEnvironment::GameEnvironment()
{
}

GameEnvironment::GameEnvironment(int rows, int cols, int levelRows)
{
    int height = rows, width = cols;
    this->levelIndex = 0;
    this->transitionRows = 0;
    this->levelRows = levelRows;
    this->window = nullptr;

    matrix = GameMatrix(height, width);

    AsteroidLevel *asteroidLevel = new AsteroidLevel(levelRows, width, height);
    CaveLevel *caveLevel = new CaveLevel(levelRows, width, height);
    CityLevel *cityLevel = new CityLevel(levelRows, width, height);

    levels.push_back(caveLevel);
    levels.push_back(cityLevel);
    levels.push_back(asteroidLevel);

    for (LevelBuilder *level : levels)
    {
        level->construct();
    }
}

void GameEnvironment::seed()
{
    vector<char> newRow = nextRow();
    matrix.updateTop(newRow);
}

vector<char> GameEnvironment::nextRow()
{
    LevelBuilder *level = currentLevel();
    vector<char> emptyRow = vector<char>(matrix.cols(), NULL_SPRITE);
    // If there's no more content available, nothing can be seeded
    if (level == nullptr || (!levelAvailable() && !level->rowAvailable()))
    {
        levelIndex = 0;
        transitionRows = matrix.rows();

        for (LevelBuilder *level : levels)
        {
            level->reconstruct();
        }
    }
    // Advance to the next level, if the current level is complete
    if (!level->rowAvailable() && !transitionRows)
    {
        transitionRows = matrix.rows();
        nextLevel();
    }
    if (transitionRows)
    {
        transitionRows -= 1;
        return emptyRow;
    }
    if (level->rowAvailable())
    {
        transitionRows = 0;
        return level->nextRow();
    }

    return emptyRow;
}

void GameEnvironment::reset()
{
    matrix.clear();

    for (LevelBuilder *level : levels)
    {
        level->reconstruct();
    }

    levelIndex = 0;
    transitionRows = 0;
}

void GameEnvironment::advance(Player &player)
{
    // Advance all rows in the matrix forward by 1
    matrix.advance();
    // Update the player's position (This will put the player in the row or position
    // specified by the coordinates given by the player object)
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
    if (!levels.size())
    {
        return nullptr;
    }

    return levels.at(levelIndex);
}

string GameEnvironment::currentLevelName()
{
    LevelBuilder *level = currentLevel();

    if (!level)
    {
        return "";
    }

    return level->name();
}

void GameEnvironment::setInitialPlayerPosition(Player &player)
{
    matrix.initPlayerObject(player.GetLocX(), player.GetLocY());
}

void GameEnvironment::updatePlayerPosition(Player &player)
{
    matrix.updatePlayerPosition(player.GetLocY(), player.GetLocX());
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

GameMatrix &GameEnvironment::getMatrix()
{
    return matrix;
}

char GameEnvironment::at(int row, int col)
{
    return matrix.at(row, col);
}

void GameEnvironment::update(int row, int col, char ch)
{
    matrix.update(row, col, ch);
}

void GameEnvironment::triggerExplosion(int row, int col)
{
    matrix.triggerExplosion(row, col);
}

GameEnvironment::~GameEnvironment()
{
    for (LevelBuilder *level : levels)
    {
        delete level;
    }

    matrix.clear();
}