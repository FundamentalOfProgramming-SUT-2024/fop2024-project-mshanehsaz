#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "menu.c"


int main()
{
    initscr();
    curs_set(false);
    keypad(stdscr, TRUE);
    noecho();
    int which_menu = 0;
    /*
    which_menu = 0   main & first menu
    which_menu = 1   sign up menu
    which_menu = 2   sign in menu
    which_menu = 3   exit
    which_menu = 4   after sign up menu & sign in menu
    ...
    */
    while (1)
    {
        if (which_menu == 0)
        {
            /*
            which_case = 1   sign up menu
            which_case = 2   sign in menu
            which_case = 3   main and first menu
            ...
            */

            int which_case = drawing_first_menu();
            if (which_case == 1)
            {
                which_menu = 1;
            }

            if (which_case == 2)
            {
                which_menu = 2;
            }

            if (which_case == 3)
            {
                which_menu = 3;
            }

        }

        else if (which_menu == 1)
        {
            int which_case = sign_up_menu();
            if (which_case == 0)
            {
                which_menu = 0;
            }
            else if (which_case == 4)
            {
                which_menu = 4;
            }
        }

        else if (which_menu == 3)
        {
            break;
        }

    }
    refresh();
    endwin();
    return 0;
}
