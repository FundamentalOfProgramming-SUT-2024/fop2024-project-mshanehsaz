#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "menu.c"


int main()
{

    srand(time(0));
    initscr();
    curs_set(false);
    keypad(stdscr, TRUE);
    noecho();

    while (1)
    {
        drawing_first_menu();
        refresh();
        break;
    }
    refresh();
    endwin();
    return 0;
}
