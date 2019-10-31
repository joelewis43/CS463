#include "../headers/window.h"

WINDOW *createBorderWindow()
{
    WINDOW *local_win;
    local_win = newwin(LINES, COLS, 0, 0);
    // Add borders to the window
    box(local_win, 0, 0);

    return local_win;
}

WINDOW *createContentWindow(WINDOW *window)
{
    WINDOW *local_win;
    int height = 0, width = 0;
    // Get the max column and row size
    getmaxyx(window, height, width);
    // Get the offset size for the inner winodw
    height = height - 2, width = width - 2;
    // Make a derived window
    local_win = derwin(window, height, width, 1, 1);
    // Both windows need to be refreshed at least once
    wrefresh(window);
    wrefresh(local_win);

    return local_win;
}