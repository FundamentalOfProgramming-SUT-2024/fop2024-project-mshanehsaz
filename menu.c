#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>


int how_many_line = 0;
int which_line_user = -1;

int pass_is_correct(char *);
int email_is_correct(char *);
void clear_and_border();
int drawing_first_menu();
int is_exist(char *);
void write_on_file(char * , char * , char *);
int sign_up_menu();
int sign_in_menu();

int line_finder(char *username)
{
    FILE *file_account_password;
    file_account_password = fopen("accounts_passwords.txt", "r");
    char line[300];
    char user[100];

    int i = 0;
    do
    {
        fgets(line, sizeof(line), file_account_password);
        line[strcspn(line, "\n")] = '\0';
        sscanf(line, "%s", user);
        i++;
    } while (strcmp(user, username) != 0);
    return i;
}

void clear_and_border()
{
    if (has_colors())
    {
        start_color();
        init_color(5, 0, 200, 0);
        init_color(6, 304, 355, 202);
        init_color(10, 300, 550, 500);
        init_color(12, 600, 700, 900);
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_WHITE, 5);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);
        init_pair(4, COLOR_WHITE, 6);
        init_pair(5, COLOR_WHITE, COLOR_RED); 
        init_pair(11, COLOR_WHITE, 10);
        init_pair(15, 12, COLOR_BLACK);

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
    srand(time(0));
    char name[100];
    char password[100];
    char email[100];
    int user = 0;
    int pass = 0;
    int mail = 0;
    int which_case = 1;
    while (1)
    {
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
            mvprintw(((LINES/2)), (COLS/2) + 25, "%s", password); 
            refresh();
        }
        if (mail == 1)
        {
            mvprintw((LINES/2) - 3, (COLS/2) + 20, "%s", email); 
            refresh();
        }        

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

                    scanw("%s", name);
                    move(0, 0);
                    if (strlen(name) > 30)
                    {
                        user = 0;
                        curs_set(false);
                        noecho(); 
                        attron(COLOR_PAIR(5));
                        mvprintw(((LINES/8) - 1), (COLS/2 - 12), "                        " );
                        mvprintw(((LINES/8)), (COLS/2 - 12), " YOUR NAME IS TOO LONG! " );
                        mvprintw(((LINES/8) + 1), (COLS/2 - 12), "                        " );
                        attroff(COLOR_PAIR(5));
                        refresh();
                        sleep(2);
                        continue;
                    }
                    else
                    {
                        user = 1;
                        curs_set(false);
                        noecho();
                        continue;
                    }    
                break;
            
            case 2:
                move((LINES/2) - 3, (COLS/2) + 20);
                curs_set(true);
                echo();
                refresh();
                scanw("%s", email);
                move(0, 0);
                if (strlen(email) > 40)
                {
                    mail = 0;
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8) - 1), (COLS/2 - 12), "                         " );
                    mvprintw(((LINES/8)), (COLS/2 - 12), " YOUR EMAIL IS TOO LONG! " );
                    mvprintw(((LINES/8) + 1), (COLS/2 - 12), "                         " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(2);
                    continue;
                }
                else if (email_is_correct(email) == 0)
                {
                    mail = 0;
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8) - 1), (COLS/2 - 21), "                                        " );
                    mvprintw(((LINES/8)), (COLS/2 - 21), " YOUR EMAIL DOES NOT MATCH THE PATTERN! " );
                    mvprintw(((LINES/8) + 1), (COLS/2 - 21), "                                        " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(2);
                    continue;
                }

                    else
                    {
                        mail = 1;
                        curs_set(false);
                        noecho();
                        continue;
                    }
                break;

            case 3:
                move(LINES/2, (COLS/2) + 25);
                curs_set(true);
                echo();
                refresh();
                scanw("%s", password);
                move(0, 0);
                if (strlen(password) < 7)
                {
                    pass = 0;
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8) - 1), (COLS/2 - 15), "                             " );
                    mvprintw(((LINES/8)), (COLS/2 - 15), " YOUR PASSWORD IS TOO SHORT! " );
                    mvprintw(((LINES/8) + 1), (COLS/2 - 15), "                             " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(2);
                    continue;
                }

                if (strlen(password) > 40)
                {
                    pass = 0;
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8) - 1), (COLS/2 - 15), "                            " );
                    mvprintw(((LINES/8)), (COLS/2 - 15), " YOUR PASSWORD IS TOO LONG! " );
                    mvprintw(((LINES/8) + 1), (COLS/2 - 15), "                            " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(2);
                    continue;
                }
                else if (pass_is_correct(password) == 0)
                {
                    pass = 0;
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8) - 1), (COLS/2 - 22), "                                           " );
                    mvprintw(((LINES/8)), (COLS/2 - 22), " YOUR PASSWORD DOES NOT MATCH THE PATTERN! " );
                    mvprintw(((LINES/8) + 1), (COLS/2 - 22), "                                           " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(2);
                    continue;
                }

                else
                {
                    pass = 1;
                    curs_set(false);
                    noecho();
                    continue;
                }
                break;

            case 4:
                move(0,0);
                break;
                
            case 5:
                if ((user != 0) && (pass != 0) && (mail != 0) )
                {
                    if (is_exist(name) == 0)
                    {
                        curs_set(false);
                        noecho(); 
                        attron(COLOR_PAIR(11));
                        mvprintw(((LINES/8) - 1), (COLS/2 - 27), "                                                     " );
                        mvprintw(((LINES/8)), (COLS/2 - 27), " YOUR ACCOUNT COMPLETLY CREATED! :) JUST A SECOND... " );
                        mvprintw(((LINES/8) + 1), (COLS/2 - 27), "                                                     " );
                        attroff(COLOR_PAIR(11));
                        refresh();
                        write_on_file(name, password, email);
                        how_many_line ++;
                        which_line_user = how_many_line;
                        sleep(2);
                        return 4;
                    }
                    else
                    {
                        user = 0;
                        curs_set(false);
                        noecho(); 
                        attron(COLOR_PAIR(5));
                        mvprintw(((LINES/8) - 1), (COLS/2 - 23), "                                            " );
                        mvprintw(((LINES/8)), (COLS/2 - 23), " THE USERNAME EXISTS! PLEASE ENTER ANOTHER! " );
                        mvprintw(((LINES/8) + 1), (COLS/2 - 23), "                                            " );
                        attroff(COLOR_PAIR(5));
                        refresh();
                        sleep(2);
                        continue;
                    }
                }
                else
                {
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8) - 1), (COLS/2 - 18), "                                   " );
                    mvprintw(((LINES/8)), (COLS/2 - 18), " PLEASE COMPLETE YOUR INFORMATION! " );
                    mvprintw(((LINES/8) + 1), (COLS/2 - 18), "                                   " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(2);
                    continue;
                }
                break;

            case 6:
                return 0;
        }
    }

}

int is_exist(char *user)
{
    FILE *file_account_password;
    file_account_password = fopen("accounts_passwords.txt", "r");

    char line[300];
    char user_name[100], password[100], email[100];

    while (fgets(line, sizeof(line), file_account_password) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        sscanf(line, "%s %s %s", user_name, password, email);

        if (strcmp(user, user_name) == 0)
        {
            fclose(file_account_password);
            return 1; 
        }
    }

    fclose(file_account_password);
    return 0; 
}

int is_correct(char *user , char *pass)
{
    FILE * file_account_password;
    file_account_password = fopen("accounts_passwords.txt", "r");
     /*
    the user not exist return 0
    the user is exist but the pass is incorrect return 2
    */
    char line[300];
    char user_name[100], password[100], email[100];

    while (fgets(line, sizeof(line), file_account_password) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        sscanf(line, "%s %s %s", user_name, password, email);

        if (strcmp(user, user_name) == 0)
        {
            if (strcmp(password, pass) == 0)
            {
                fclose(file_account_password);
                return 1; 
            }
            fclose(file_account_password);
            return 2;
        }
    }


    fclose(file_account_password);
    return 0;
}

void write_on_file(char *user , char *pass , char *mail)
{
    FILE * file_account_password;
    file_account_password = fopen("accounts_passwords.txt", "a");
    fprintf(file_account_password, "%s %s %s\n", user, pass, mail);
    fclose(file_account_password);
    how_many_line ++;
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

int pass_is_correct(char *pass)
{
    int number = 0;
    int lower = 0;
    int upper = 0;
    for (int i = 0; pass[i] != '\0'; i++)
    {
        if (isdigit(pass[i]))
        {
            number ++;
        }
        if (isupper(pass[i]))
        {
            upper ++;
        }
        if (islower(pass[i]))
        {
            lower ++;
        }
    }

    if (number > 0 && upper > 0 && lower > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int sign_in_menu()
{
    char name[100];
    char password[100];
    int user = 0;
    int pass = 0;
    int which_case = 1;
    while (1)
    {
        clear_and_border();
        attron(COLOR_PAIR(3));
        mvprintw(((LINES/2) - 8), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
        mvprintw(((LINES/2)) - 5, ((COLS/2) - 11) ," ENTER YOUR PASSWORD ");
        mvprintw(((LINES/2)) - 2, ((COLS/2) - 9) ," ENTER THE GAME! ");
        mvprintw(((LINES/2)) + 1, ((COLS/2) - 10) ," I FORGOT MY PASS! ");
        mvprintw(((LINES/2) + 4), ((COLS/2) - 9) ," ENTER AS A GUEST ");
        mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
        attroff(COLOR_PAIR(3));

        if (user == 1)
        {
            mvprintw(((LINES/2) - 8), (COLS/2) + 14, "%s", name); 
            refresh();
        }
        if (pass == 1)
        {
            mvprintw((LINES/2) - 5, (COLS/2) + 14, "%s", password); 
            refresh();
        }
   
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
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 11) ," ENTER YOUR PASSWORD ");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 9) ," ENTER THE GAME! ");
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 10) ," I FORGOT MY PASS! ");
                mvprintw(((LINES/2) + 4), ((COLS/2) - 9) ," ENTER AS A GUEST ");
                mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2) - 8), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
                attroff(COLOR_PAIR(4));

                break;

            case 2:
                mvprintw(((LINES/2) - 8), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 9) ," ENTER THE GAME! ");
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 10) ," I FORGOT MY PASS! ");
                mvprintw(((LINES/2) + 4), ((COLS/2) - 9) ," ENTER AS A GUEST ");
                mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 11) ," ENTER YOUR PASSWORD ");
                attroff(COLOR_PAIR(4));
                break;

            case 3:
                mvprintw(((LINES/2) - 8), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 11) ," ENTER YOUR PASSWORD ");
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 10) ," I FORGOT MY PASS! ");
                mvprintw(((LINES/2) + 4), ((COLS/2) - 9) ," ENTER AS A GUEST ");
                mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(11));
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 9) ," ENTER THE GAME! ");
                attroff(COLOR_PAIR(11));
                break;

            case 4:
                mvprintw(((LINES/2) - 8), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 11) ," ENTER YOUR PASSWORD ");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 9) ," ENTER THE GAME! ");
                mvprintw(((LINES/2) + 4), ((COLS/2) - 9) ," ENTER AS A GUEST ");
                mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(5));
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 10) ," I FORGOT MY PASS! ");
                attroff(COLOR_PAIR(5));
                break;

            case 5:
                mvprintw(((LINES/2) - 8), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 11) ," ENTER YOUR PASSWORD ");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 9) ," ENTER THE GAME! ");
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 10) ," I FORGOT MY PASS! ");
                mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2) + 4), ((COLS/2) - 9) ," ENTER AS A GUEST ");
                attroff(COLOR_PAIR(4));
                break;

            case 6:
                mvprintw(((LINES/2) - 8), (COLS/2) - 11 ," ENTER YOUR USERNAME ");
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 11) ," ENTER YOUR PASSWORD ");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 9) ," ENTER THE GAME! ");
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 10) ," I FORGOT MY PASS! ");
                mvprintw(((LINES/2) + 4), ((COLS/2) - 9) ," ENTER AS A GUEST ");
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
                move(((LINES/2) - 8), (COLS/2) + 14);
                curs_set(true);
                echo();
                refresh();
                scanw("%99s", name);
                move(0, 0);
                user = 1;
                curs_set(false);
                noecho();
                continue;

            case 2:
                move((LINES/2) - 5, (COLS/2) + 14);
                curs_set(true);
                echo();
                refresh();
                scanw("%99s", password);
                move(0, 0);
                pass = 1;
                curs_set(false);
                noecho();
                continue;

            case 3:
                if (user != 0 && pass != 0)
                {
                    if (is_correct(name, password) == 1)
                    {
                        curs_set(false);
                        noecho(); 
                        attron(COLOR_PAIR(11));
                        mvprintw(((LINES/8) - 1), (COLS/2 - 18), "                                 " );
                        mvprintw(((LINES/8)), (COLS/2 - 18), " YES, IT'S YOU! JUST A MOMENT... " );
                        mvprintw(((LINES/8) + 1), (COLS/2 - 18), "                                 " );
                        attroff(COLOR_PAIR(11));
                        refresh();
                        sleep(2); 
                        which_line_user = line_finder(name);
                        return 4;
                    }

                    else if(is_correct(name, password) == 2)
                    {
                        pass = 0;
                        curs_set(false);
                        noecho(); 
                        attron(COLOR_PAIR(5));
                        mvprintw(((LINES/8) - 1), (COLS/2 - 18), "                                    " );
                        mvprintw(((LINES/8)), (COLS/2 - 18), " INCORRECT THE PASSWORD! TRY AGAIN! " );
                        mvprintw(((LINES/8) + 1), (COLS/2 - 18), "                                    " );
                        attroff(COLOR_PAIR(5));
                        refresh();
                        sleep(2);
                        continue;
                    }

                    else
                    {
                        user = 0;
                        pass = 0;
                        curs_set(false);
                        noecho(); 
                        attron(COLOR_PAIR(5));
                        mvprintw(((LINES/8) - 1), (COLS/2 - 18), "                                      " );
                        mvprintw(((LINES/8)), (COLS/2 - 18), " I'M AFRAID, WE DON'T HAVE THIS USER! " );
                        mvprintw(((LINES/8) + 1), (COLS/2 - 18), "                                      " );
                        attroff(COLOR_PAIR(5));
                        refresh();
                        sleep(2);
                        continue;
                    }
                }

                else
                {
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8) - 1), (COLS/2 - 18), "                                   " );
                    mvprintw(((LINES/8)), (COLS/2 - 18), " PLEASE COMPLETE YOUR INFORMATION! " );
                    mvprintw(((LINES/8) + 1), (COLS/2 - 18), "                                   " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(2);
                    continue;
                }

            case 4:
                
                break;
                
            case 5:
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(11));
                    mvprintw(((LINES/8) - 1), (COLS/2 - 16), "                              " );
                    mvprintw(((LINES/8)), (COLS/2 - 16), " AS A GUEST, JUST A MOMENT... " );
                    mvprintw(((LINES/8) + 1), (COLS/2 - 16), "                              " );
                    attroff(COLOR_PAIR(11));
                    refresh();
                    which_line_user = -1;
                    sleep(2); 
                    return 4;

            case 6:
                return 0;

        }
    }

}

