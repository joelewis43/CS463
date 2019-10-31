#include <ncurses.h>

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
