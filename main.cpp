#include "headers/gameEnvironment.h"
#include "headers/window.h"
#include <chrono>
#include <thread>

int main()
{
  initscr();

  WINDOW *border = createBorderWindow();
  WINDOW *window = createContentWindow(border);

  Player player;
  GameEnvironment g(window, 1000);

  int mid = (getmaxx(window) - 1) / 2;

  player.SetLocY((getmaxy(window) - 1) - 5);
  player.SetLocX(mid);

  g.setInitialPlayerPosition(player);

  redrawwin(window);

  start_color();

  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);

  for (int i = 0; i < 1000; i++)
  {
    g.print();

    // g.advance(player);
    // g.updatePlayerPosition(player);
    // if (i % 5 == 0)
    // player.SetLocY(player.GetLocY() - 1);
    g.triggerExplosion(player.GetLocY(), player.GetLocX());

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  delwin(window);
  delwin(border);

  return 0;
}
