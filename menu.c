#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int email_is_correct(char *);
void clear_and_border();
int drawing_first_menu();
int is_exist(char *, char *, char *);
void write_on_file();
int sign_up_menu();
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
        init_pair(5, COLOR_WHITE, COLOR_RED);    
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

int sign_up_menu()
{
    char name[100];
    char password[100];
    char email[100];
    int user = 0;
    int pass = 0;
    int mail = 0;
    rewrite:
    srand(time(0));
    clear_and_border();
    attron(COLOR_PAIR(2));
    mvprintw(((LINES/2) - 9), ((COLS/2) - 13) ," LET'S CREATE AN ACCOUNT! ");
    mvprintw(((LINES/2) + 6), ((COLS/2) - 10) ," CREAT THE ACCOUNT ");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(3));
    mvprintw(((LINES/2) - 6), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
    mvprintw(((LINES/2) - 3), (COLS/2) - 15 ," ENTER YOUR EMAIL (xxx@yyy.zzz) ");
    mvprintw(((LINES/2)), ((COLS/2) - 22) ," CREATE A PASSWORD (more than 7 characters) ");
    mvprintw(((LINES/2) + 3), ((COLS/2) - 13) ," MAKE A PASSWORD FOR ME! ");
    mvprintw(((LINES/2) + 9), ((COLS/2) - 4) ," BACK ");
    attroff(COLOR_PAIR(3));
    refresh();
    if (user == 1)
    {
       mvprintw(((LINES/2) - 6), (COLS/2) + 12, "%s", name); 
       refresh();
    }
    if (pass == 1)
    {
       mvprintw(((LINES/2) - 6), (COLS/2) + 12, "%s", password); 
       refresh();
    }
    if (mail == 1)
    {
       mvprintw((LINES/2) - 3, (COLS/2) + 20, "%s", email); 
       refresh();
    }

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
            attron(COLOR_PAIR(4));
            mvprintw(((LINES/2) - 6), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(((LINES/2) - 3), (COLS/2) - 15 ," ENTER YOUR EMAIL (xxx@yyy.zzz) ");
            mvprintw(((LINES/2)), ((COLS/2) - 22) ," CREATE A PASSWORD (more than 7 characters) ");
            mvprintw(((LINES/2) + 3), ((COLS/2) - 13) ," MAKE A PASSWORD FOR ME! ");
            mvprintw(((LINES/2) + 9), ((COLS/2) - 4) ," BACK ");
            attroff(COLOR_PAIR(3));
            attron(COLOR_PAIR(2));
            mvprintw(((LINES/2) + 6), ((COLS/2) - 10) ," CREAT THE ACCOUNT ");
            attroff(COLOR_PAIR(2));

            break;

        case 2:
            attron(COLOR_PAIR(4));
            mvprintw(((LINES/2) - 3), (COLS/2) - 15 ," ENTER YOUR EMAIL (xxx@yyy.zzz) ");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(((LINES/2) - 6), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
            mvprintw(((LINES/2)), ((COLS/2) - 22) ," CREATE A PASSWORD (more than 7 characters) ");
            mvprintw(((LINES/2) + 3), ((COLS/2) - 13) ," MAKE A PASSWORD FOR ME! ");
            mvprintw(((LINES/2) + 9), ((COLS/2) - 4) ," BACK ");
            attroff(COLOR_PAIR(3));
            attron(COLOR_PAIR(2));
            mvprintw(((LINES/2) + 6), ((COLS/2) - 10) ," CREAT THE ACCOUNT ");
            attroff(COLOR_PAIR(2));
            break;
        case 3:
            attron(COLOR_PAIR(4));
            mvprintw(((LINES/2)), ((COLS/2) - 22) ," CREATE A PASSWORD (more than 7 characters) ");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(((LINES/2) - 6), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
            mvprintw(((LINES/2) - 3), (COLS/2) - 15 ," ENTER YOUR EMAIL (xxx@yyy.zzz) ");
            mvprintw(((LINES/2) + 3), ((COLS/2) - 13) ," MAKE A PASSWORD FOR ME! ");
            mvprintw(((LINES/2) + 9), ((COLS/2) - 4) ," BACK ");
            attroff(COLOR_PAIR(3));
            attron(COLOR_PAIR(2));
            mvprintw(((LINES/2) + 6), ((COLS/2) - 10) ," CREAT THE ACCOUNT ");
            attroff(COLOR_PAIR(2));
            break;
        case 4:
            attron(COLOR_PAIR(5));
            mvprintw(((LINES/2) + 3), ((COLS/2) - 13) ," MAKE A PASSWORD FOR ME! ");
            attroff(COLOR_PAIR(5));
            attron(COLOR_PAIR(3));
            mvprintw(((LINES/2) - 6), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
            mvprintw(((LINES/2) - 3), (COLS/2) - 15 ," ENTER YOUR EMAIL (xxx@yyy.zzz) ");
            mvprintw(((LINES/2)), ((COLS/2) - 22) ," CREATE A PASSWORD (more than 7 characters) ");
            mvprintw(((LINES/2) + 9), ((COLS/2) - 4) ," BACK ");
            attroff(COLOR_PAIR(3));
            attron(COLOR_PAIR(2));
            mvprintw(((LINES/2) + 6), ((COLS/2) - 10) ," CREAT THE ACCOUNT ");
            attroff(COLOR_PAIR(2));
            break;
        case 5:
            attron(COLOR_PAIR(4));
            mvprintw(((LINES/2) + 6), ((COLS/2) - 10) ," CREAT THE ACCOUNT ");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(((LINES/2) - 6), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
            mvprintw(((LINES/2) - 3), (COLS/2) - 15 ," ENTER YOUR EMAIL (xxx@yyy.zzz) ");
            mvprintw(((LINES/2)), ((COLS/2) - 22) ," CREATE A PASSWORD (more than 7 characters) ");
            mvprintw(((LINES/2) + 3), ((COLS/2) - 13) ," MAKE A PASSWORD FOR ME! ");
            mvprintw(((LINES/2) + 9), ((COLS/2) - 4) ," BACK ");
            attroff(COLOR_PAIR(3));

            break;

        case 6:
            attron(COLOR_PAIR(4));
            mvprintw(((LINES/2) + 9), ((COLS/2) - 4) ," BACK ");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(((LINES/2) - 6), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
            mvprintw(((LINES/2) - 3), (COLS/2) - 15 ," ENTER YOUR EMAIL (xxx@yyy.zzz) ");
            mvprintw(((LINES/2)), ((COLS/2) - 22) ," CREATE A PASSWORD (more than 7 characters) ");
            mvprintw(((LINES/2) + 3), ((COLS/2) - 13) ," MAKE A PASSWORD FOR ME! ");
            attroff(COLOR_PAIR(3));
            attron(COLOR_PAIR(2));
            mvprintw(((LINES/2) + 6), ((COLS/2) - 10) ," CREAT THE ACCOUNT ");
            attroff(COLOR_PAIR(2));
            break;

        }
    }
    refresh();

    switch (which_case)
    {
        case 1:
            move(((LINES/2) - 6), (COLS/2) + 12);
            curs_set(true);
            echo();
            refresh();
            while (1)
            {
                scanw("%s", name);
                move(0, 0);
                if (strlen(name) > 30)
                {
                    user = 0;
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8)), (COLS/2 - 12), " YOUR NAME IS TOO LONG! " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(2);
                    mvprintw(((LINES/8)), (COLS/2 - 21), "                                               " );
                    goto rewrite;
                }
                else
                {
                    user = 1;
                    curs_set(false);
                    noecho();
                    goto menu;
                }
            }    
            break;
        
        case 2:
            move((LINES/2) - 3, (COLS/2) + 20);
            curs_set(true);
            echo();
            refresh();
            while (1)
            {
                scanw("%s", email);
                move(0, 0);
                if (strlen(email) > 40)
                {
                    mail = 0;
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8)), (COLS/2 - 12), " YOUR EMAIL IS TOO LONG! " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(2);
                    mvprintw(((LINES/8)), (COLS/2 - 21), "                                               " );
                    goto rewrite;
                }
                else if (email_is_correct(email) == 0)
                {
                    mail = 0;
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8)), (COLS/2 - 21), " YOUR EMAIL DOES NOT MATCH THE PATTERN! " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(2);
                    mvprintw(((LINES/8)), (COLS/2 - 21), "                                               " );
                    goto rewrite;
                }

                else
                {
                    mail = 1;
                    curs_set(false);
                    noecho();
                    goto menu;
                }
            }
            break;
        
        case 5:
            // اولا فایل ها رو بساز و در فایل نام و ایمیل و رمز را بزار
            printw("%s", name);
            refresh();
            sleep(3);
            break;
        case 6:
            return 0;
    }
}

int is_exist(char *user , char *pass , char *mail)
{
    FILE * file_account_password;
    file_account_password = fopen("account&password.txt", "r");
    char user_name[100], password[100], email[100];

    while (fscanf(file_account_password, "%s %s %s", user_name, password, email) != EOF)
    {
        if (strcmp(user, user_name) == 0)
        {
            fclose(file_account_password);
            return 1;
        }
    }
    fclose(file_account_password);
    return 0;
}

int is_correct(char *user , char *pass , char *mail)
{
    FILE * file_account_password;
    file_account_password = fopen("account&password.txt", "r");
    char user_name[100], password[100], email[100];

    while (fscanf(file_account_password, "%s %s %s", user_name, password, email) != EOF)
    {
        if (strcmp(user, user_name) == 0 && strcmp(pass, password) == 0)
        {
            fclose(file_account_password);
            return 1;
        }
    }
    fclose(file_account_password);
    return 0;
}

void write_on_file()
{

} 

int email_is_correct(char *email)
{

    int at_count = 0;
    int dot_count = 0;
    char *at;
    char *dot;

    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            at_count++;
            at = &email[i];
        }
        else if (email[i] == '.') {
            dot_count++;
            dot = &email[i];
        }
    }

    if (at_count != 1)
        return 0;

    if (dot_count == 0 || dot < at)
        return 0;

    if (at - email < 1)
        return 0;

    if (at[1] == '\0')
        return 0;

    if (dot[1] == '\0')
        return 0;

    return 1;
}

void sign_in_menu()
{
    clear_and_border();

}

