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
        int which_case = drawing_first_menu();
        switch (which_case)
        {
        case 1:
            sign_up_menu();
            break;
        
        case 2:
            sign_in_menu();
            break;

        case 3:
            score_table();
            break;
        }

        refresh();
        break;
    }
    refresh();
    endwin();
    return 0;
}
