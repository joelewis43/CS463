#include "matrix.h"

GameMatrix::GameMatrix()
{
    buffer = vector<vector<Object *>>();
}

GameMatrix::GameMatrix(int rows, int cols)
{
    buffer = vector<vector<Object *>>(rows, vector<Object *>(cols));
}

Object *GameMatrix::at(int row, int col)
{
    return buffer.at(row).at(col);
}

void GameMatrix::update(int row, int col, Object *obj)
{
    // Free memory for objects that are being overwritten
    if (buffer[row][col])
    {
        delete buffer[row][col];
    }

    buffer[row][col] = obj;
}

void GameMatrix::advance()
{
    int r_len = buffer.size(), c_len = buffer.at(0).size();
    int r_offset = r_len - 1;

    // Free memory in the last row (offscreen)
    for (int i = 0; i < c_len; i++)
    {
        if (buffer[r_offset][i])
        {
            delete buffer[r_offset][i];
            buffer[r_offset][i] = nullptr;
        }
    }

    // Move objects from the previous rows to later rows
    // The first row will untouched
    for (int i = r_offset; i > 0; i--)
    {
        int prev = i - 1;
        buffer.at(i).assign(buffer.at(prev).begin(), buffer.at(prev).end());
    }

    // Clear the first row
    for (int i = 0; i < c_len; i++)
    {
        buffer[0][i] = nullptr;
    }
}

void GameMatrix::updateTop(vector<Object *> &row)
{
    buffer.at(0).assign(row.begin(), row.end());
}

string GameMatrix::serialize()
{
    return stringMap([](Object *object) { return object ? object->toID() : ' '; });
}

string GameMatrix::toString()
{
    return stringMap([](Object *object) { return object ? object->toChar() : ' '; });
}

void GameMatrix::loadFromStr(string str)
{
    int row = 0, col = 0;

    for (char c : str)
    {
        // Inicates new row
        if (c == '\n')
        {
            row++;
            col = 0;
            continue;
        }

        switch (c)
        {
        case '1':
            update(row, col, new Characther());
            break;
        case '2':
            update(row, col, new Comet());
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
            if (row[i])
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
}