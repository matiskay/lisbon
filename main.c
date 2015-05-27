#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include "graph.h"
#include <unistd.h>

static void finish(int sig);

/* Reference: http://viget.com/extend/game-programming-in-c-with-the-ncurses-library */

/* Add function signatures here */

// gcc main.c -lncurses
int main(int argc, char **argv) {
  /* Start your code here */
  initscr();
  noecho();
  curs_set(FALSE);
  mvprintw(0, 0, "Hello, world!");
  refresh();

  sleep(1);
  endwin();
  return 0;
}
