#include "../headers/window.h"

WINDOW *createBorderWindow()
{
    WINDOW *local_win;
    local_win = newwin(GAMEBOARD_WINDOW_HEIGHT, GAMEBOARD_WINDOW_WIDTH, 0, 0);
    // Add borders to the window
    box(local_win, 0, 0);
    touchwin(local_win);

    return local_win;
}

WINDOW *createContentWindow(WINDOW *window)
{
    WINDOW *local_win;
    // Make a derived window
    local_win = subwin(window, CONTENT_HEIGHT, CONTENT_WIDTH, 1, 1);
    // Both windows need to be refreshed at least once
    wrefresh(window);
    wrefresh(local_win);

    return local_win;
}