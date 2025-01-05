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

    while (1)
    {
        drawing_menu();
        refresh();
        if (getch() == 'q')
        {
            break;
        }
        sleep(10);
        break;
    }
    refresh();
    endwin();
    return 0;
}
