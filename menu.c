#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void clear_and_border();
int drawing_first_menu();
void sign_up_menu();
void sign_in_menu();
void score_table();


void clear_and_border()
{
    if (has_colors())
    {
        start_color();
        init_color(5, 0, 200, 0);
        init_color(6, 304, 355, 202);
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_WHITE, 5);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);
        init_pair(4, COLOR_WHITE, 6);
        init_pair(5, COLOR_BLACK, COLOR_RED);    
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
    refresh();
}

int drawing_first_menu()
{
    drawing_section:
    clear_and_border();
    attron(COLOR_PAIR(2));
    mvprintw(((LINES/2) - 6), ((COLS/2) - 13) ," HELLO, ENJOY THE GAME! ");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(3));
    mvprintw(((LINES/2) - 2), ((COLS/2) - 5) ," SIGN UP ");
    mvprintw(((LINES/2) + 2), (COLS/2) - 5 ," SIGN IN ");
    mvprintw(((LINES/2) + 6), ((COLS/2) - 4) ," EXIT ");
    attroff(COLOR_PAIR(3));
    int which_case = 1;

    for(int c = getch(); c != 10; c = getch())
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
            mvprintw(((LINES/2) + 6), ((COLS/2) - 4) ," EXIT ");
            attroff(COLOR_PAIR(3));
            break;
        
        case 2:
            attron(COLOR_PAIR(4));
            mvprintw(((LINES/2) + 2), (COLS/2) - 5 ," SIGN IN ");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(((LINES/2) - 2), ((COLS/2) - 5) ," SIGN UP ");
            mvprintw(((LINES/2) + 6), ((COLS/2) - 4) ," EXIT ");
            attroff(COLOR_PAIR(3));
            break;

        case 3:
            attron(COLOR_PAIR(4));
            mvprintw(((LINES/2) + 6), ((COLS/2) - 4) ," EXIT ");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(((LINES/2) - 2), ((COLS/2) - 5) ," SIGN UP ");
            mvprintw(((LINES/2) + 2), (COLS/2) - 5 ," SIGN IN ");
            attroff(COLOR_PAIR(3));
            break;
        }
    }
    return which_case;

}
void sign_up_menu()
{
    rewrite:
    clear_and_border();
    attron(COLOR_PAIR(2));
    mvprintw(((LINES/2) - 8), ((COLS/2) - 13) ," LET'S CREATE AN ACCOUNT! ");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(3));
            mvprintw(((LINES/2) - 5), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
    mvprintw(((LINES/2) - 2), (COLS/2) - 15 ," ENTER YOUR EMAIL (xxx@yyy.zzz) ");
    mvprintw(((LINES/2) + 1), ((COLS/2) - 22) ," CREATE A PASSWORD (more than 7 characters) ");
    mvprintw(((LINES/2) + 4), ((COLS/2) - 13) ," MAKE A PASSWORD FOR ME! ");
    mvprintw(((LINES/2) + 7), ((COLS/2) - 4) ," BACK ");

    attroff(COLOR_PAIR(3));
    menu:
    int which_case = 1;
    
    refresh();
    
    for(int ch = getch(); ch != 10; ch = getch())
    {
        if (ch == KEY_UP)
        {
            which_case --;
            if (which_case == 0)
            {
                which_case = 5;
            }
        }
        if ((ch == KEY_DOWN))
        {
            which_case ++;
            if (which_case == 6)
            {
                which_case = 1;
            }
        }
        switch (which_case)
        {
        
        case 1:
            attron(COLOR_PAIR(4));
            mvprintw(((LINES/2) - 5), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(((LINES/2) - 2), (COLS/2) - 15 ," ENTER YOUR EMAIL (xxx@yyy.zzz) ");
            mvprintw(((LINES/2) + 1), ((COLS/2) - 22) ," CREATE A PASSWORD (more than 7 characters) ");
            mvprintw(((LINES/2) + 4), ((COLS/2) - 13) ," MAKE A PASSWORD FOR ME! ");
            mvprintw(((LINES/2) + 7), ((COLS/2) - 4) ," BACK ");
            attroff(COLOR_PAIR(3));
            break;

        case 2:
            attron(COLOR_PAIR(4));
            mvprintw(((LINES/2) - 2), (COLS/2) - 15 ," ENTER YOUR EMAIL (xxx@yyy.zzz) ");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(((LINES/2) - 5), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
            mvprintw(((LINES/2) + 1), ((COLS/2) - 22) ," CREATE A PASSWORD (more than 7 characters) ");
            mvprintw(((LINES/2) + 4), ((COLS/2) - 13) ," MAKE A PASSWORD FOR ME! ");
            mvprintw(((LINES/2) + 7), ((COLS/2) - 4) ," BACK ");
            attroff(COLOR_PAIR(3));
            break;
        case 3:
            attron(COLOR_PAIR(4));
            mvprintw(((LINES/2) + 1), ((COLS/2) - 22) ," CREATE A PASSWORD (more than 7 characters) ");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(((LINES/2) - 5), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
            mvprintw(((LINES/2) - 2), (COLS/2) - 15 ," ENTER YOUR EMAIL (xxx@yyy.zzz) ");
            mvprintw(((LINES/2) + 4), ((COLS/2) - 13) ," MAKE A PASSWORD FOR ME! ");
            mvprintw(((LINES/2) + 7), ((COLS/2) - 4) ," BACK ");
            attroff(COLOR_PAIR(3));
            break;
        case 4:
            attron(COLOR_PAIR(4));
            mvprintw(((LINES/2) + 4), ((COLS/2) - 13) ," MAKE A PASSWORD FOR ME! ");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(((LINES/2) - 5), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
            mvprintw(((LINES/2) - 2), (COLS/2) - 15 ," ENTER YOUR EMAIL (xxx@yyy.zzz) ");
            mvprintw(((LINES/2) + 1), ((COLS/2) - 22) ," CREATE A PASSWORD (more than 7 characters) ");
            mvprintw(((LINES/2) + 7), ((COLS/2) - 4) ," BACK ");
            attroff(COLOR_PAIR(3));
            break;
        case 5:
            attron(COLOR_PAIR(4));
            mvprintw(((LINES/2) + 7), ((COLS/2) - 4) ," BACK ");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(((LINES/2) - 5), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
            mvprintw(((LINES/2) - 2), (COLS/2) - 15 ," ENTER YOUR EMAIL (xxx@yyy.zzz) ");
            mvprintw(((LINES/2) + 1), ((COLS/2) - 22) ," CREATE A PASSWORD (more than 7 characters) ");
            mvprintw(((LINES/2) + 4), ((COLS/2) - 13) ," MAKE A PASSWORD FOR ME! ");
            attroff(COLOR_PAIR(3));
            break;
        }
    }
    
    refresh();

    switch (which_case)
    {
    case 1:
        move(((LINES/2) - 5), (COLS/2) + 12);
        curs_set(true);
        echo();
        refresh();
        clrtoeol();  

        while (1)
        {
            char name[100];
            scanw("%s", name);
            move(0, 0);
            if (strlen(name) > 60)
            {
                clrtoeol(); 
                curs_set(false);
                noecho(); 
                attron(COLOR_PAIR(5));
                mvprintw(((LINES/2) - 5), (COLS/2) + 13, "YOUR NAME IS TOO LONG!" );
                attroff(COLOR_PAIR(5));
                refresh();
                sleep(2);
                clrtoeol(); 
                goto rewrite;
            }
            else
            {
                curs_set(false);
                noecho();
                goto menu;
            }
        }
        break;
    
    case 5:
        break;
    }
}

void sign_in_menu()
{
    clear_and_border();

}


void score_table()
{
    clear_and_border();

}