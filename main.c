#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "game.c"


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
    which_menu = 5   forgot pass
    which_menu = 6   game setting
    which_menu = 7   account page
    which_menu = 8   score table
    which_menu = 9   new game
    which_menu = 10  resume
    ...
    */

    while (1)
    {
        if (which_menu == 0)
        {
            /*
            which_case = 1   sign up menu
            which_case = 2   sign in menu
            which_case = 3   exit
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

        else if (which_menu == 2)
        {
            int which_case = sign_in_menu();
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

        else if (which_menu == 4)
        {
            int which_case = before_play_menu(which_line_user);
            if (which_menu == 7)
            {
                profile();
                which_menu = 4;
            }
            else if (which_case == 0)
            {
                which_menu = 0;
            }

        }

    }
    refresh();
    endwin();
    return 0;
}
