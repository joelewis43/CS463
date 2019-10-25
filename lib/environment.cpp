#include "environment.h"

Environment::Environment(WINDOW *window, int levelRows)
{
    int height = 0, width = 0;
    this->levelIndex = 0;
    this->levelRows = levelRows;
    this->window = window;

    getmaxyx(window, height, width);
    height = height - 1, width = width - 1;
    matrix = GameMatrix(height, width);

    CityLevel *cityLevel = new CityLevel(levelRows, width);
    levels.push_back(cityLevel);
}

void Environment::seed()
{
    vector<Object *> newRow = currentLevel()->nextRow();
    matrix.updateTop(newRow);
}

void Environment::advance()
{
    matrix.advance();
    seed();
}

void Environment::nextLevel()
{
    if (levelIndex >= levels.size() - 1)
    {
        return;
    }

    levelIndex++;
}

LevelBuilder *Environment::currentLevel()
{
    return levels.at(levelIndex);
}

void Environment::print()
{
    wclear(window);
    mvwprintw(window, 0, 0, matrix.toString().c_str());
    wrefresh(window);
}

Environment::~Environment()
{
    for (LevelBuilder *level : levels)
    {
        delete level;
    }

    matrix.clear();
}