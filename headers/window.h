#include <ncurses.h>
#include <chrono>
#include <thread>

#ifndef GAMEBOARD_WINDOW_HEIGHT
#define GAMEBOARD_WINDOW_HEIGHT 36
#endif // !GAMEBOARD_WINDOW_HEIGHT

#ifndef GAMEBOARD_WINDOW_WIDTH
#define GAMEBOARD_WINDOW_WIDTH 200
#endif // !GAMEBOARD_WINDOW_WIDTH

#ifndef CONTENT_HEIGHT
#define CONTENT_HEIGHT (GAMEBOARD_WINDOW_HEIGHT - 2 - 1) // Extra -1 to account for Score
#endif // !CONTENT_HEIGHT

#ifndef CONTENT_WIDTH
#define CONTENT_WIDTH (GAMEBOARD_WINDOW_WIDTH - 2)
#endif // !CONTENT_WIDTH

#ifndef GAMEBOARD_BUFSIZE
// Every cell of the window plus newlines and null terminator minus the row and column offset
#define GAMEBOARD_BUFSIZE (CONTENT_HEIGHT * (CONTENT_WIDTH - 1)) + (CONTENT_HEIGHT - 1) + 1
#endif // !GAMEBOARD_BUFSIZE

/**
 * Creates an ncurses window with borders surrounding the boundaries
 * of the window. The window is the full size of the terminal window
 * 
 * @returns - A pointer to an ncurses window
 **/
WINDOW *createBorderWindow();

/**
 * Creates a subwindow that is meant to be used as the subwindow
 * of a border window.
 * 
 * @param window - A pointer to an ncurses window
 * 
 * @returns - A pointer to an ncurses window
 **/
WINDOW *createContentWindow(WINDOW *window);
