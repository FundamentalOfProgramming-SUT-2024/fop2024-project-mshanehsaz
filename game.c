#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "menu.c"


char **user;

typedef struct
{
    int line;
    int gold;
    int life_time;
    int hungry_amount;
    int telesm[20];
    int selah[20];
    int hardness;
    int x;
    int y;
} Player;

Player player;

void which_user(int line_user)
{
    FILE *file_account_password;
    file_account_password = fopen("accounts_passwords.txt", "r");
    char line[300];
    player.line = line_user;
    user = (char **) malloc(3 * sizeof(char *));
    for (int j = 0; j < 3; j++)
    {
        *(user + j) = (char *) malloc(100*sizeof(char));
    }

    do
    {
        fgets(line, sizeof(line), file_account_password);
        line[strcspn(line, "\n")] = '\0';
        sscanf(line, "%s %s %s", user[0], user[1], user[2] );
        line_user--;
    } while (line_user != 0);
}

int before_play_menu(int line)
{
    if (line == -1)
    {
        player.line = -1;
    }
    else
    {
        which_user(line);
    }
    clear_and_border();
    int which_case = 1;
    while (1)
    {
        clear_and_border();
        attron(COLOR_PAIR(3));
        mvprintw(((LINES/2) - 8), (COLS/2) - 6," NEW GAME ");
        mvprintw(((LINES/2)) - 5, ((COLS/2) - 5) ," RESUME ");
        mvprintw(((LINES/2)) - 2, ((COLS/2) - 5) ," SETTING ");
        mvprintw(((LINES/2)) + 1, ((COLS/2) - 7) ," SCORE TABLE ");
        mvprintw(((LINES/2) + 4), ((COLS/2) - 5) ," PROFILE ");
        mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
        attroff(COLOR_PAIR(3));
        refresh();
        for(int ch = getch(); ch != 10; ch = getch())
        {
            if (ch == KEY_UP)
            {
                which_case --;
                if (which_case == 0)
                {
                    which_case = 6;
                }
            }
            if ((ch == KEY_DOWN))
            {
                which_case ++;
                if (which_case == 7)
                {
                    which_case = 1;
                }
            }

            switch (which_case)
            {
            
            case 1:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 5) ," RESUME ");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 5) ," SETTING ");
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 7) ," SCORE TABLE ");
                mvprintw(((LINES/2) + 4), ((COLS/2) - 5) ," PROFILE ");
                mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2) - 8), (COLS/2) - 6," NEW GAME ");
                attroff(COLOR_PAIR(4));

                break;

            case 2:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2) - 8), (COLS/2) - 6," NEW GAME ");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 5) ," SETTING ");
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 7) ," SCORE TABLE ");
                mvprintw(((LINES/2) + 4), ((COLS/2) - 5) ," PROFILE ");
                mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 5) ," RESUME ");
                attroff(COLOR_PAIR(4));
                break;

            case 3:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2) - 8), (COLS/2) - 6," NEW GAME ");
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 5) ," RESUME ");
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 7) ," SCORE TABLE ");
                mvprintw(((LINES/2) + 4), ((COLS/2) - 5) ," PROFILE ");
                mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 5) ," SETTING ");
                attroff(COLOR_PAIR(4));
                break;

            case 4:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2) - 8), (COLS/2) - 6," NEW GAME ");
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 5) ," RESUME ");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 5) ," SETTING ");
                mvprintw(((LINES/2) + 4), ((COLS/2) - 5) ," PROFILE ");
                mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 7) ," SCORE TABLE ");
                attroff(COLOR_PAIR(4));
                break;

            case 5:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2) - 8), (COLS/2) - 6," NEW GAME ");
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 5) ," RESUME ");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 5) ," SETTING ");
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 7) ," SCORE TABLE ");
                mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2) + 4), ((COLS/2) - 5) ," PROFILE ");
                attroff(COLOR_PAIR(4));
                break;

            case 6:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2) - 8), (COLS/2) - 6," NEW GAME ");
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 5) ," RESUME ");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 5) ," SETTING ");
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 7) ," SCORE TABLE ");
                mvprintw(((LINES/2) + 4), ((COLS/2) - 5) ," PROFILE ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(4));
                break;

            }
        }
        refresh();

        switch (which_case)
        {
            case 1:
                return 9;

            case 2:
                return 10;

            case 3:
                return 6;

            case 4:
                return 8;
                break;
                
            case 5:
                return 7;

            case 6:
                return 0;
        }
    }
}

void profile()
{
    player.gold = 0;
    clear_and_border();
    while (1)
    {
        if (player.line == -1)
        {
            attron(COLOR_PAIR(11));
            mvprintw(((LINES/2) - 4), (COLS/2) - 5,"        ");
            mvprintw(((LINES/2) - 3), (COLS/2) - 5," GUEST! ");
            mvprintw(((LINES/2)) - 2, (COLS/2) - 5,"        ");
            attroff(COLOR_PAIR(11));
            refresh(); 
            attron(COLOR_PAIR(5));
            mvprintw(((LINES/2)) + 2, ((COLS/2) - 10) ,"                   ");
            mvprintw(((LINES/2)) + 3, ((COLS/2) - 10) ," PRESS Q TO LEAVE: ");
            mvprintw(((LINES/2)) + 4, ((COLS/2) - 10) ,"                   ");
            attroff(COLOR_PAIR(5));
        }
        
        else
        {
            attron(COLOR_PAIR(11));
            mvprintw(((LINES/2) - 8), (COLS/2) - (6 + (strlen(user[0])/2))," USERNAME: %s ", user[0]);
            mvprintw(((LINES/2)) - 4, ((COLS/2) - (6 + (strlen(user[1])/2))) ," PASSWORD: %s ", user[1]);
            mvprintw(((LINES/2)), ((COLS/2) - (5 + (strlen(user[2])/2))) ," EMAIL: %s ", user[2]);
            mvprintw(((LINES/2)) + 4, ((COLS/2) - 9) ," SCORE(GOLD): %d ", player.gold);
            attroff(COLOR_PAIR(11));
            attron(COLOR_PAIR(5));
            mvprintw(((LINES/2)) + 7, ((COLS/2) - 10) ,"                   ");
            mvprintw(((LINES/2)) + 8, ((COLS/2) - 10) ," PRESS Q TO LEAVE ");
            mvprintw(((LINES/2)) + 9, ((COLS/2) - 10) ,"                   ");
            attroff(COLOR_PAIR(5));
            refresh();
        }
        char ch = getch();
        if (ch == 'q')
        {
            break;
        }
    }
}