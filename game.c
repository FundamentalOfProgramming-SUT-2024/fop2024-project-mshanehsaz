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
    int color;
    int life_time;
    int hungry_amount;
    int telesm[20];
    int main_selah;
    int selah[20];
    int hardness;
    int level;
    int x;
    int y;
} Player;

int first_life;

Player player;

void clear_and_border2()
{
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(LINES - 1, COLS - 1, "#");
    mvprintw(0, 0, "#");
    mvprintw(LINES -1 , 0, "#");
    mvprintw(0, COLS - 1, "#");
    for (int i =  1 ; i < LINES - 1; i++)
    {
        mvprintw(i, 0, "|");   
    }
    for (int i = 1 ; i < LINES - 1; i++)
    {
        mvprintw(i, COLS - 1, "|");   
    }
    for (int i = 1 ; i < COLS - 1; i++)
    {
        mvprintw(0, i, "*"); 
        mvprintw(4, i, "*");  
    }
    for (int i = 1 ; i < COLS - 1 ; i++)
    {
        mvprintw(LINES - 1, i, "*");  
        mvprintw(LINES - 5, i, "*");  
    }
    refresh();
}

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
            mvprintw(((LINES/2)) + 2, ((COLS/2) - 10) ,"                  ");
            mvprintw(((LINES/2)) + 3, ((COLS/2) - 10) ," PRESS Q TO LEAVE ");
            mvprintw(((LINES/2)) + 4, ((COLS/2) - 10) ,"                  ");
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
            mvprintw(((LINES/2)) + 7, ((COLS/2) - 10) ,"                  ");
            mvprintw(((LINES/2)) + 8, ((COLS/2) - 10) ," PRESS Q TO LEAVE ");
            mvprintw(((LINES/2)) + 9, ((COLS/2) - 10) ,"                  ");
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

int setting()
{
    clear_and_border();
    int which_case = 1;
    while (1)
    {
        if(player.hardness != 0)
        {
            mvprintw(((LINES/2) - 6), (COLS/2) + 28, "%d", player.hardness); 
            refresh();
        }
        if(player.color != 0)
        {
            mvprintw(((LINES/2)) - 2, ((COLS/2) + 28), "%d", player.color); 
            refresh();
        }


        attron(COLOR_PAIR(3));
        mvprintw(((LINES/2) - 6), (COLS/2) - 26," CHOOSE THE HARDNESS: (1: ESAY, 2: NORMAL, 3: HARD)");
        mvprintw(((LINES/2)) - 2, ((COLS/2) - 26) ," CHOOSE THE COLOR: (1: YELLOW, 2: BLUE, 3: GREEN) ");
        mvprintw(((LINES/2)) + 2, ((COLS/2) - 14) ," CHOOSE THE SONG: (1, 2, 3) ");
        mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
        attroff(COLOR_PAIR(3));
        refresh();
        for(int ch = getch(); ch != 10; ch = getch())
        {
            if (ch == KEY_UP)
            {
                which_case --;
                if (which_case == 0)
                {
                    which_case = 4;
                }
            }
            if ((ch == KEY_DOWN))
            {
                which_case ++;
                if (which_case == 5)
                {
                    which_case = 1;
                }
            }

            switch (which_case)
            {
            
            case 1:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 26) ," CHOOSE THE COLOR: (1: YELLOW, 2: BLUE, 3: GREEN) ");
                mvprintw(((LINES/2)) + 2, ((COLS/2) - 14) ," CHOOSE THE SONG: (1, 2, 3) ");
                mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2) - 6), (COLS/2) - 26," CHOOSE THE HARDNESS: (1: ESAY, 2: NORMAL, 3: HARD)");
                attroff(COLOR_PAIR(4));

                break;

            case 2:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2) - 6), (COLS/2) - 26," CHOOSE THE HARDNESS: (1: ESAY, 2: NORMAL, 3: HARD)");
                mvprintw(((LINES/2)) + 2, ((COLS/2) - 14) ," CHOOSE THE SONG: (1, 2, 3) ");
                mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 26) ," CHOOSE THE COLOR: (1: YELLOW, 2: BLUE, 3: GREEN) ");
                attroff(COLOR_PAIR(4));
                break;

            case 3:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2) - 6), (COLS/2) - 26," CHOOSE THE HARDNESS: (1: ESAY, 2: NORMAL, 3: HARD)");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 26) ," CHOOSE THE COLOR: (1: YELLOW, 2: BLUE, 3: GREEN) ");
                mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2)) + 2, ((COLS/2) - 14) ," CHOOSE THE SONG: (1, 2, 3) ");
                attroff(COLOR_PAIR(4));
                break;

            case 4:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2) - 6), (COLS/2) - 26," CHOOSE THE HARDNESS: (1: ESAY, 2: NORMAL, 3: HARD)");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 26) ," CHOOSE THE COLOR: (1: YELLOW, 2: BLUE, 3: GREEN) ");
                mvprintw(((LINES/2)) + 2, ((COLS/2) - 14) ," CHOOSE THE SONG: (1, 2, 3) ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(4));
                break;

            }
        }
        refresh();

        switch (which_case)
        {
            case 1:
                move(((LINES/2) - 6), (COLS/2) + 28);
                curs_set(true);
                echo();
                refresh();
                if (scanw("%d", &player.hardness) == 1 && player.hardness <= 3 && player.hardness >= 1)
                {
                    move(0, 0);
                    curs_set(false);
                    noecho();
                    continue; 
                }
                else
                {
                    player.hardness = 0;
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8) - 1), (COLS/2 - 15), "                            " );
                    mvprintw(((LINES/8)), (COLS/2 - 15), " PLEASE ENTER CORRECT ITEM! " );
                    mvprintw(((LINES/8) + 1), (COLS/2 - 15), "                            " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(3);
                    continue;
                }

            case 2:
                move(((LINES/2) - 2), (COLS/2) + 28);
                curs_set(true);
                echo();
                refresh();
                if (scanw("%d", &player.color) == 1 && player.color <= 3 && player.color >= 1)
                {
                    move(0, 0);
                    curs_set(false);
                    noecho();
                    continue; 
                }
                else
                {
                    player.color = 0;
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8) - 1), (COLS/2 - 15), "                            " );
                    mvprintw(((LINES/8)), (COLS/2 - 15), " PLEASE ENTER CORRECT ITEM! " );
                    mvprintw(((LINES/8) + 1), (COLS/2 - 15), "                            " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(3);
                    continue;
                }

            case 3:
                break;

            case 4:
                return 4;
        }
    }
}

void alert(char *message)
{
    for (int i = 2; i < COLS - 1; i++)
    {
        mvprintw(1, i, " ");
        mvprintw(2, i, " ");
        mvprintw(3, i, " ");
    }

    attron(A_BOLD);
    attron(COLOR_PAIR(11));
    for (int i = 2; i < strlen(message) + 4; i++)
    {
        mvprintw(1, i, " ");
    }
    mvprintw(2, 2, " %s ", message);
    for (int i = 2; i < strlen(message) + 4; i++)
    {
        mvprintw(3, i, " ");
    }
    attroff(COLOR_PAIR(11));
    attroff(A_BOLD);

    refresh();
}

void elemnts_under_board()
{
    attron(A_BOLD);
    attron(COLOR_PAIR(11));
    for (int i = 2; i < COLS - 2; i++)
    {
        mvprintw(LINES - 4, i, " ");
    }
    for (int i = 2; i < COLS - 2; i++)
    {
        mvprintw(LINES - 3, i, " ");
    }

    mvprintw(LINES - 3, 2, " Level: %d ", player.level);
    mvprintw(LINES - 3, (COLS/5) + 2, " Gold: %d ", player.gold);
    mvprintw(LINES - 3, 2*(COLS/5) + 2, " Hit: ");
    attroff(COLOR_PAIR(11));

    attron(COLOR_PAIR(5));
    for (int i = 0; i < first_life; i++)
    {
            mvprintw(LINES - 3, 2*(COLS/5) + 8 + i," ");
    }
    for (int i = 0; i < player.life_time; i++)
    {
        mvprintw(LINES - 3, 2*(COLS/5) + 8 + i,"#");
    }
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(11));
    mvprintw(LINES - 3, 3*(COLS/5) + 2, " Hunger: ");
    attroff(COLOR_PAIR(11));

    attron(COLOR_PAIR(5));
    for (int i = 0; i < 20; i++)
    {
            mvprintw(LINES - 3, 3*(COLS/5) + 12 + i," ");
    }
    for (int i = 0; i < player.hungry_amount; i++)
    {
        mvprintw(LINES - 3, 3*(COLS/5) + 12 + i,"#");
    }
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(11));
    mvprintw(LINES - 3, 4*(COLS/5) + 2, " Weapon: ");
    switch (player.main_selah)
    {
    case 1:
        mvprintw(LINES - 3, 4*(COLS/5) + 11, "Mace");
        break;
    
    case 2:
        mvprintw(LINES - 3, 4*(COLS/5) + 11, "Dagger");
        break;

    case 3:
        mvprintw(LINES - 3, 4*(COLS/5) + 11, "Magic Wand");
        break;

    case 4:
        mvprintw(LINES - 3, 4*(COLS/5) + 11, "Normal Arrow");
        break;

    case 5:
        mvprintw(LINES - 3, 4*(COLS/6) + 11, "Sword");
        break;

    }

    for (int i = 2; i < COLS - 2; i++)
    {
        mvprintw(LINES - 2, i, " ");
    }
    attroff(COLOR_PAIR(11));
    attroff(A_BOLD);

    refresh();
}

int new_game()
{
    if (player.color > 3 || player.color < 1)
    {
        player.color = 1;
    }
    if (player.hardness > 3 || player.hardness < 1)
    {
        player.hardness = 1;
    }
    player.gold = 0;
    player.main_selah = 1;
    if (player.hardness == 1)
    {
        player.life_time = 24;
        player.hungry_amount = 0;
    }
    else if (player.hardness == 2)
    {
        player.life_time = 18;
        player.hungry_amount = 2;
    }
    else if (player.hardness == 3)
    {
        player.life_time = 12; 
        player.hungry_amount = 4;  
    }
    first_life = player.life_time;
    player.level = 1;
    player.selah[0] = 1;

    clear_and_border2();
    elemnts_under_board();
    alert("salamamammslaksdjlakda");
    sleep(3);
    char ch = getch();
    if (ch == 'q')
    {
        return 0;
    }


}