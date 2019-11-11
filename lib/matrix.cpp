#include "../headers/matrix.h"

GameMatrix::GameMatrix()
{
    buffer = deque<vector<Object *>>();
    playerObject = nullptr;
    playerX = playerY = 0;
}

GameMatrix::GameMatrix(int rows, int cols) : GameMatrix()
{
    buffer = deque<vector<Object *>>(rows, vector<Object *>(cols));
}

Object *GameMatrix::at(int row, int col)
{
    return buffer.at(row).at(col);
}

void GameMatrix::update(int row, int col, Object *obj)
{
    // Free memory for objects that are being overwritten
    if (row >= rows() || col >= cols())
    {
        return;
    }

    if (buffer[row][col] != nullptr && buffer[row][col] != playerObject)
    {
        delete buffer[row][col];
    }

    buffer[row][col] = obj;
}

void GameMatrix::advance()
{
    int r_len = rows(), c_len = cols();
    int r_offset = r_len - 1;

    // Free memory in the last row (offscreen)
    for (int i = 0; i < c_len; i++)
    {
        Object *obj = buffer[r_offset][i];
        if (obj != nullptr && obj != playerObject)
        {
            delete buffer[r_offset][i];
            buffer[r_offset][i] = nullptr;
        } else if (obj != nullptr && obj == playerObject)
        {
            buffer[r_offset][i] = nullptr;
        }
    }

    // Remove the last row in the matrix
    buffer.pop_back();

    // Add a new row to the beginning
    buffer.push_front(vector<Object *>(c_len, nullptr));

    // Update the Y coordinate for the player
    if (playerY <= rows() - 1)
    {
        if (rows() > 1 && playerY <= rows() - 2)
        {
            update(playerY + 1, playerX, nullptr);
        }

        update(playerY, playerX, playerObject);
    }
}

void GameMatrix::updateTop(vector<Object *> &row)
{
    buffer.at(0).assign(row.begin(), row.end());
}

void GameMatrix::initPlayerObject(int x, int y)
{
    playerX = x;
    playerY = y;
    playerObject = new PlayerObject();
    update(y, x, playerObject);
}

void GameMatrix::updatePlayerPosition(int newX, int newY)
{
    if (newX >= cols() - 1 || newY >= rows() - 1)
    {
        return;
    }
    // Move object ot new position
    Object *obj = at(playerY, playerX);
    // Only set to null if the object is a player object
    if (obj != nullptr && obj == playerObject)
    {
        update(playerY, playerX, nullptr);
    }

    update(newY, newX, playerObject);

    // Update the cache
    playerY = newY;
    playerX = newX;
}

string GameMatrix::serialize()
{
    return stringMap([](Object *object) { return object ? object->toID() : '0'; });
}

string GameMatrix::toString()
{
    return stringMap([](Object *object) { return object ? object->toChar() : ' '; });
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
            continue;
        }

        switch (c)
        {
        case '1':
            update(row, col, playerObject);
            break;
        case '2':
            update(row, col, new CollisionObject());
            break;
        default:
            break;
        }

        col++;
    }
}

void GameMatrix::clear()
{
    for (vector<Object *> &row : buffer)
    {
        for (int i = 0; i < row.size(); i++)
        {
            if (row[i] && row[i] != playerObject)
            {
                delete row[i];
            }

            row[i] = nullptr;
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

vector<Object *> &GameMatrix::operator[](int index)
{
    return buffer.at(index);
}

string GameMatrix::stringMap(std::function<const char(Object *)> func)
{
    std::stringstream stream;

    for (vector<Object *> &row : buffer)
    {
        for (Object *o : row)
        {
            stream << func(o);
        }

        stream << '\n';
    }

    return stream.str();
}

GameMatrix::~GameMatrix()
{
    clear();
    delete playerObject;
}
