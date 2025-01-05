#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void drawing_first_menu()
{
    if (has_colors())
    {
        start_color();
        init_color(5, 0, 200, 0);
        init_color(6, 0, 300, 300);
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_WHITE, 5);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);
        init_pair(4, COLOR_WHITE, 6);    
    }
    clear();

    attron(COLOR_PAIR(1));

    mvprintw(LINES/4, COLS/4, "#");
    mvprintw(3*(LINES/4), COLS/4, "#");
    mvprintw(LINES/4, 3*(COLS/4), "#");
    mvprintw(3*(LINES/4), 3*(COLS/4), "#");
    for (int i = (LINES/4) + 1 ; i < (3*(LINES/4)); i++)
    {
        mvprintw(i, COLS/4, "|");   
    }
    for (int i = (LINES/4) + 1 ; i < (3*(LINES/4)); i++)
    {
        mvprintw(i, 3*(COLS/4), "|");   
    }
    for (int i = (COLS/4) + 1 ; i < 3*(COLS/4); i++)
    {
        mvprintw(LINES/4, i, "*");   
    }
    for (int i = (COLS/4) + 1 ; i < 3*(COLS/4); i++)
    {
        mvprintw(3*(LINES/4), i, "*");   
    }
    attron(COLOR_PAIR(2));
    mvprintw(((LINES/2) - 6), ((COLS/2) - 13) ," HELLO, ENJOY THE GAME! ");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(3));
    mvprintw(((LINES/2) - 2), ((COLS/2) - 5) ," SIGN UP ");
    mvprintw(((LINES/2) + 2), (COLS/2) - 5 ," SIGN IN ");
    mvprintw(((LINES/2) + 6), ((COLS/2) - 8) ," SCORES TABLE ");
    attroff(COLOR_PAIR(3));

    int which_case = 1;

    for(int c; c != 10; c = getch())
    {
        if (c == KEY_UP)
        {
            which_case --;
            if (which_case == 0)
            {
                which_case = 3;
            }
        }
        if ((c == KEY_DOWN))
        {
            which_case ++;
            if (which_case == 4)
            {
                which_case = 1;
            }
        }
        switch (which_case)
        {
        case 1:
            attron(COLOR_PAIR(4));
            mvprintw(((LINES/2) - 2), ((COLS/2) - 5) ," SIGN UP ");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(((LINES/2) + 2), (COLS/2) - 5 ," SIGN IN ");
            mvprintw(((LINES/2) + 6), ((COLS/2) - 8) ," SCORES TABLE ");
            attroff(COLOR_PAIR(3));
            break;
        
        case 2:
            attron(COLOR_PAIR(4));
            mvprintw(((LINES/2) + 2), (COLS/2) - 5 ," SIGN IN ");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(((LINES/2) - 2), ((COLS/2) - 5) ," SIGN UP ");
            mvprintw(((LINES/2) + 6), ((COLS/2) - 8) ," SCORES TABLE ");
            attroff(COLOR_PAIR(3));
            break;

        case 3:
            attron(COLOR_PAIR(4));
            mvprintw(((LINES/2) + 6), ((COLS/2) - 8) ," SCORES TABLE ");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(((LINES/2) - 2), ((COLS/2) - 5) ," SIGN UP ");
            mvprintw(((LINES/2) + 2), (COLS/2) - 5 ," SIGN IN ");
            attroff(COLOR_PAIR(3));
            break;
        }
    }

}

