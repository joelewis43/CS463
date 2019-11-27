#include "../headers/matrix.h"

GameMatrix::GameMatrix()
{
    buffer = deque<vector<char>>();
    playerX = playerY = 0;
}

GameMatrix::GameMatrix(int rows, int cols)
{
    buffer = deque<vector<char>>(rows, vector<char>(cols, NULL_SPRITE));
    playerX = playerY = 0;
}

char GameMatrix::at(int row, int col)
{
    // Bound check the minimum
    if (row < 0)
    {
        row = 0;
    }
    if (col < 0)
    {
        col = 0;
    }
    // Bound check the maximum
    row = std::min(row, rows() - 1);
    col = std::min(col, cols() - 1);

    return buffer.at(row).at(col);
}

void GameMatrix::update(int row, int col, char ch)
{
    // Bound check the minimum
    if (row < 0)
    {
        row = 0;
    }
    if (col < 0)
    {
        col = 0;
    }
    // Bound check the maximum
    row = std::min(row, rows() - 1);
    col = std::min(col, cols() - 1);

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

pair<int, int> GameMatrix::getPlayerCoord()
{
    int row = 0, col = 0;

    for (int r = 0; r < rows(); r++)
    {
        for (int c = 0; c < cols(); c++)
        {
            if (at(r, c) == PLAYER_SPRITE)
            {
                row = r;
                col = c;
                break;
            }
        }
    }

    return make_pair(row, col);
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

void GameMatrix::updatePlayerPosition(int newY, int newX)
{
    // Bound check the minimum
    if (newY < 0)
    {
        newY = 0;
    }
    if (newX < 0)
    {
        newX = 0;
    }
    // Bound check the maximum
    newY = std::min(newY, rows() - 1);
    newX = std::min(newX, cols() - 1);
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

void GameMatrix::print(WINDOW *window, string score, string level)
{
    char ch;
    const char *map = toString().c_str();
    int row = 1, col = 0, clr = 0;
    bool cityLevel = level.find("Skyscraper") != string::npos;


    // print the header info
    std::string scoreString = "Current score: ";
    scoreString.append(score);
    scoreString.append(cols() - scoreString.size() - level.size(), NULL_SPRITE);
    scoreString.append(level);

    mvwprintw(window, 0, 0, scoreString.c_str());

    for (int i = 0; i < strlen(map); i++)
    {
        ch = map[i];

        switch (ch)
        {
        case COLLISION_SPRITE:
            if (cityLevel)
            {
                clr = randomInt(0, 9);
                clr = clr <= 3 ? 2 : 1;

                wattron(window, COLOR_PAIR(clr));
                mvwaddch(window, row, col++, ch);
            } 
            else
            {
                wattron(window, COLOR_PAIR(1));
                mvwaddch(window, row, col++, ch);
            }
            break;
        case PLAYER_SPRITE:
            wattron(window, COLOR_PAIR(2));
            mvwaddch(window, row, col++, ch);
            break;
        case EXPLOSION_SPRITE:
            clr = randomInt(0, 1) ? 1 : 3;
            wattron(window, COLOR_PAIR(clr));
            mvwaddch(window, row, col++, ch);
            break;
        case '\n':
            wattron(window, COLOR_PAIR(1));
            mvwaddch(window, row, col++, ch);

            row += 1;
            col = 0;
            break;
        default:
            wattron(window, COLOR_PAIR(1));
            mvwaddch(window, row, col++, NULL_SPRITE);
            break;
        }
    }
    wrefresh(window);
}

void GameMatrix::triggerExplosion(int row, int col)
{
    bloom(row, col, 3);
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

void GameMatrix::bloom(int c_row, int c_col, int radius)
{
    int cr = c_row - radius, cc = c_col - radius, ccr = c_row + radius, ccc = c_col + radius;

    for (int y = cr; y <= ccr; y++)
    {
        for (int x = cc; x <= ccc; x++)
        {
            if ((pow(x - c_col, 2.0) + pow(y - c_row, 2.0)) <= pow(radius, 2.0))
            {
                update(y, x, EXPLOSION_SPRITE);
            }
        }
    }
}

GameMatrix::~GameMatrix() {}
