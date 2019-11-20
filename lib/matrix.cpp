#include "../headers/matrix.h"

GameMatrix::GameMatrix()
{
    buffer = deque<vector<char>>();
    playerX = playerY = 0;
}

GameMatrix::GameMatrix(int rows, int cols)
{
    buffer = deque<vector<char>>(rows, vector<char>(cols));
    playerX = playerY = 0;
}

char GameMatrix::at(int row, int col)
{
    return buffer.at(row).at(col);
}

void GameMatrix::update(int row, int col, char ch)
{
    // Free memory for objects that are being overwritten
    if (row >= rows() || col >= cols())
    {
        return;
    }

    buffer[row][col] = ch;
}

void GameMatrix::advance()
{
    int r_len = rows(), c_len = cols();
    int r_offset = r_len - 1;

    // Remove the last row in the matrix
    buffer.pop_back();

    // Add a new row to the beginning
    buffer.push_front(vector<char>(c_len, NULL_SPRITE));

    // Update the Y coordinate for the player
    if (playerY <= rows() - 1)
    {
        // Set the advanced to position to null
        if (rows() > 1 && playerY <= rows() - 2)
        {
            update(playerY + 1, playerX, NULL_SPRITE);
        }

        // Set the player back to where they were before
        // Environment moved 1 step, player effectively moved forward 1 step
        update(playerY, playerX, PLAYER_SPRITE);
    }
}

void GameMatrix::updateTop(vector<char> &row)
{
    buffer.at(0).assign(row.begin(), row.end());
}

void GameMatrix::initPlayerObject(int x, int y)
{
    playerX = x;
    playerY = y;
    update(y, x, PLAYER_SPRITE);
}

void GameMatrix::updatePlayerPosition(int newX, int newY)
{
    if (newX > cols() - 1 || newY > rows() - 1)
    {
        return;
    }
    // Move object ot new position
    char ch = at(playerY, playerX);
    // Only set to null if the object is a player object
    if (ch == PLAYER_SPRITE)
    {
        update(playerY, playerX, NULL_SPRITE);
    }

    update(newY, newX, PLAYER_SPRITE);

    // Update the cache
    playerY = newY;
    playerX = newX;
}

string GameMatrix::serialize()
{
    return stringMap([](char ch) { return ch; });
}

string GameMatrix::toString()
{
    return stringMap([](char ch) { return ch; });
}

void GameMatrix::loadFromStr(string str)
{
    int row = 0, col = 0;

    // Clear the contents of the matrix
    // Be mindful of memory on the heap
    clear();

    for (char c : str)
    {
        // Indicates new row
        if (c == '\n')
        {
            row++;
            col = 0;
        } else
        {
            update(row, col, c);
            col++;
        }
    }
}

void GameMatrix::clear()
{
    for (vector<char> &row : buffer)
    {
        for (int i = 0; i < row.size(); i++)
        {
            row[i] = NULL_SPRITE;
        }
    }
}

void GameMatrix::clearScreen()
{
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    cout << "\x1B[2J\x1B[H";
}

void GameMatrix::print(WINDOW *window)
{
    wclear(window);
    mvwprintw(window, 0, 0, toString().c_str());
    wrefresh(window);
}

int GameMatrix::rows()
{
    return buffer.size();
}

int GameMatrix::cols()
{
    return buffer.at(0).size();
}

vector<char> &GameMatrix::operator[](int index)
{
    return buffer.at(index);
}

string GameMatrix::stringMap(std::function<const char(char)> func)
{
    std::stringstream stream;

    for (vector<char> &row : buffer)
    {
        for (char c : row)
        {
            stream << func(c);
        }

        stream << '\n';
    }

    return stream.str();
}

GameMatrix::~GameMatrix() {}
