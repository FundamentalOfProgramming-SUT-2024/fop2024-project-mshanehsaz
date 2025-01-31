#include "menu.c"


char **user;

/*
color 1 = yellow
color 2 = blue
color 3 = green
hardness 1 = easy
hardness 2 = normal
hardness 3 = hard
*/
typedef struct
{
    int line;
    int score;
    int gold;
    int color;
    float life_time;
    float hungry_amount;
    int telesm[20];
    int main_selah;
    int selah[20];
    int hardness;
    int level;
    int room_i;
    int x;
    int y;
} Player;


typedef struct
{
    int x;
    int y;
}pair;


/*
type 1 = mamooli
type 2 = telesm
type 3 = kaboos
type 4 = ganj
*/

/*
door 0 = up
door 1 = right
door 2 = left
door 3 = down
*/
typedef struct
{
        char **map;
        int type;
        pair doors[4];
}room;

room *rooms;

char **all_map;

char **map_whithout_tale;

char **map_that_shown;


int first_life;

Player player;

void updating_map_that_shown(int x, int y)
{
    if (all_map[x][y] == '+')
    {

    }

}

void add_to_main_map(int i)
{
    int row, col;
    switch (i) 
    {
    case 0:
        row = 0;
        col = 0;
        break;

    case 1:
        row = 0;
        col = (COLS - 2) / 4;
        break;

    case 2:
        row = 0;
        col = 2 * (COLS - 2) / 4;
        break;

    case 3:
        row = 0;
        col = 3 * (COLS - 2) / 4;
        break;

    case 4:
        row = ((LINES - 10) / 2);
        col = 0;
        break;

    case 5:
        row = ((LINES - 10) / 2);
        col = (COLS - 2) / 4;
        break;

    case 6:
        row = ((LINES - 10) / 2);
        col = 2 * (COLS - 2) / 4 ;
        break;

    case 7:
        row = (LINES - 10) / 2;
        col = 3 * (COLS - 2) / 4;
        break;

    }

    for (int k = 0; k < ((LINES - 10) / 2); k++) 
    {
        for (int j = 0; j < ((COLS - 2) / 4); j++) 
        {
            all_map[row + k][col + j] = rooms[i].map[k][j];
        }
    }
}

void connect_plus(int x1, int y1, int dir1, int x2, int y2, int dir2)
{
    srand(time(0));

    switch (dir1)
    {
    case 0:
        x1 --;
        break;

    case 1:
        y1 ++;
        break;
        
    case 2:
        y1 --;
        break;

    case 3:
        x1 ++;
        break;
    }

    switch (dir2)
    {
    case 0:
        x2 --;
        break;

    case 1:
        y2 ++;
        break;
        
    case 2:
        y2 --;
        break;

    case 3:
        x2 ++;
        break;
    }

    while (x1 != x2 || y1 != y2) 
    {
        int turn = rand() % 2;

        if (all_map[x1][y1] == ' ')
        {
            all_map[x1][y1] = '#';
        }
        
        if (turn && x1 != x2)
        {
            x1 += (x1 < x2) ? 1 : -1;
        } 
        else if(y1 != y2)
        {
            y1 += (y1 < y2) ? 1 : -1;
        } 
    }
    all_map[x1][y1] = '#';
}

void connect_room()
{
    int which_arr = rand()%4;

    switch (which_arr)
    {
    case 0:
        connect_plus(rooms[0].doors[1].x, rooms[0].doors[1].y, 1,
                    rooms[1].doors[2].x, rooms[1].doors[2].y, 2);

        connect_plus(rooms[0].doors[3].x, rooms[0].doors[3].y, 3,
                    rooms[4].doors[0].x, rooms[4].doors[0].y, 0);  
        
        connect_plus(rooms[1].doors[1].x, rooms[1].doors[1].y, 1,
                    rooms[2].doors[2].x, rooms[2].doors[2].y, 2);
        
        connect_plus(rooms[2].doors[1].x, rooms[2].doors[1].y, 1,
                    rooms[3].doors[2].x, rooms[3].doors[2].y, 2);
        
        connect_plus(rooms[3].doors[3].x, rooms[3].doors[3].y, 3,
                    rooms[7].doors[0].x, rooms[7].doors[0].y, 0);
        
        connect_plus(rooms[5].doors[1].x, rooms[5].doors[1].y, 1,
                    rooms[6].doors[2].x, rooms[6].doors[2].y, 2);
        
        connect_plus(rooms[6].doors[1].x, rooms[6].doors[1].y, 1,
                    rooms[7].doors[2].x, rooms[7].doors[2].y, 2); 
        break;

        case 1:
        connect_plus(rooms[0].doors[1].x, rooms[0].doors[1].y, 1,
                    rooms[1].doors[2].x, rooms[1].doors[2].y, 2); 

        connect_plus(rooms[1].doors[3].x, rooms[1].doors[3].y, 3,
                    rooms[5].doors[0].x, rooms[5].doors[0].y, 0);
        
        connect_plus(rooms[1].doors[1].x, rooms[1].doors[1].y, 1,
                    rooms[2].doors[2].x, rooms[2].doors[2].y, 2);
        
        connect_plus(rooms[2].doors[3].x, rooms[2].doors[3].y, 3,
                    rooms[6].doors[0].x, rooms[6].doors[0].y, 0);
        
        connect_plus(rooms[3].doors[3].x, rooms[3].doors[3].y, 3,
                    rooms[7].doors[0].x, rooms[7].doors[0].y, 0);
        
        connect_plus(rooms[4].doors[1].x, rooms[4].doors[1].y, 1,
                    rooms[5].doors[2].x, rooms[5].doors[2].y, 2);
        
        connect_plus(rooms[6].doors[1].x, rooms[6].doors[1].y, 1,
                    rooms[7].doors[2].x, rooms[7].doors[2].y, 2); 
        break;

        case 2:
        connect_plus(rooms[0].doors[1].x, rooms[0].doors[1].y, 1,
                    rooms[1].doors[2].x, rooms[1].doors[2].y, 2);

        connect_plus(rooms[0].doors[3].x, rooms[0].doors[3].y, 3,
                    rooms[4].doors[0].x, rooms[4].doors[0].y, 0);  

        connect_plus(rooms[1].doors[3].x, rooms[1].doors[3].y, 3,
                    rooms[5].doors[0].x, rooms[5].doors[0].y, 0);
        
        connect_plus(rooms[2].doors[1].x, rooms[2].doors[1].y, 1,
                    rooms[3].doors[2].x, rooms[3].doors[2].y, 2);
        
        connect_plus(rooms[2].doors[3].x, rooms[2].doors[3].y, 3,
                    rooms[6].doors[0].x, rooms[6].doors[0].y, 0);
        
        connect_plus(rooms[3].doors[3].x, rooms[3].doors[3].y, 3,
                    rooms[7].doors[0].x, rooms[7].doors[0].y, 0);
        
        connect_plus(rooms[5].doors[1].x, rooms[5].doors[1].y, 1,
                    rooms[6].doors[2].x, rooms[6].doors[2].y, 2);

        break;
        
        case 3:

        connect_plus(rooms[0].doors[3].x, rooms[0].doors[3].y, 3,
                    rooms[4].doors[0].x, rooms[4].doors[0].y, 0);  

        connect_plus(rooms[1].doors[3].x, rooms[1].doors[3].y, 3,
                    rooms[5].doors[0].x, rooms[5].doors[0].y, 0);
        
        connect_plus(rooms[2].doors[3].x, rooms[2].doors[3].y, 3,
                    rooms[6].doors[0].x, rooms[6].doors[0].y, 0);
        
        connect_plus(rooms[3].doors[3].x, rooms[3].doors[3].y, 3,
                    rooms[7].doors[0].x, rooms[7].doors[0].y, 0);
        
        connect_plus(rooms[4].doors[1].x, rooms[4].doors[1].y, 1,
                    rooms[5].doors[2].x, rooms[5].doors[2].y, 2);
        
        connect_plus(rooms[5].doors[1].x, rooms[5].doors[1].y, 1,
                    rooms[6].doors[2].x, rooms[6].doors[2].y, 2);
        
        connect_plus(rooms[6].doors[1].x, rooms[6].doors[1].y, 1,
                    rooms[7].doors[2].x, rooms[7].doors[2].y, 2); 
        break;
    
    
    }
         
        //connect_plus(rooms[0].doors[1].x, rooms[0].doors[1].y, 1,
        //             rooms[1].doors[2].x, rooms[1].doors[2].y, 2);

        // connect_plus(rooms[0].doors[3].x, rooms[0].doors[3].y, 3,
        //             rooms[4].doors[0].x, rooms[4].doors[0].y, 0);  

        // connect_plus(rooms[1].doors[3].x, rooms[1].doors[3].y, 3,
        //             rooms[5].doors[0].x, rooms[5].doors[0].y, 0);
        
        // connect_plus(rooms[1].doors[1].x, rooms[1].doors[1].y, 1,
        //             rooms[2].doors[2].x, rooms[2].doors[2].y, 2);
        
        // connect_plus(rooms[2].doors[1].x, rooms[2].doors[1].y, 1,
        //             rooms[3].doors[2].x, rooms[3].doors[2].y, 2);
        
        // connect_plus(rooms[2].doors[3].x, rooms[2].doors[3].y, 3,
        //             rooms[6].doors[0].x, rooms[6].doors[0].y, 0);
        
        // connect_plus(rooms[3].doors[3].x, rooms[3].doors[3].y, 3,
        //             rooms[7].doors[0].x, rooms[7].doors[0].y, 0);
        
        // connect_plus(rooms[4].doors[1].x, rooms[4].doors[1].y, 1,
        //             rooms[5].doors[2].x, rooms[5].doors[2].y, 2);
        
        // connect_plus(rooms[5].doors[1].x, rooms[5].doors[1].y, 1,
        //             rooms[6].doors[2].x, rooms[6].doors[2].y, 2);
        
        // connect_plus(rooms[6].doors[1].x, rooms[6].doors[1].y, 1,
        //             rooms[7].doors[2].x, rooms[7].doors[2].y, 2); 
}

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

void adding_doors(int i, int firstx, int firsty, int width, int height)
{
    switch (i)
    {
    case 0:
        rooms[i].doors[1].x = (rand()%(height-3)) + firstx + 1;
        rooms[i].doors[1].y = firsty + width;
        all_map[rooms[i].doors[1].x][rooms[i].doors[1].y] = '+';

        rooms[i].doors[3].y = (rand()%(width-3)) + firsty + 1;
        rooms[i].doors[3].x = firstx + height;
        all_map[rooms[i].doors[3].x][rooms[i].doors[3].y] = '+';
        break;
    
    case 1:
        rooms[i].doors[1].x = (rand()%(height-3)) + firstx + 1;
        rooms[i].doors[1].y = firsty + width + (COLS - 2)/4;
        all_map[rooms[i].doors[1].x][rooms[i].doors[1].y] = '+';

        rooms[i].doors[2].x = (rand()%(height-3)) + firstx + 1;
        rooms[i].doors[2].y = firsty + (COLS - 2)/4;
        all_map[rooms[i].doors[2].x][rooms[i].doors[2].y] = '+';

        rooms[i].doors[3].y = (rand()%(width-3)) + firsty + (COLS - 2)/4 + 1;
        rooms[i].doors[3].x = firstx + height;
        all_map[rooms[i].doors[3].x][rooms[i].doors[3].y] = '+';
        break;

    case 2:
        rooms[i].doors[1].x = (rand()%(height-3)) + firstx + 1;
        rooms[i].doors[1].y = firsty + width + 2*(COLS - 2)/4;
        all_map[rooms[i].doors[1].x][rooms[i].doors[1].y] = '+';

        rooms[i].doors[2].x = (rand()%(height-3)) + firstx + 1;
        rooms[i].doors[2].y = firsty + 2*(COLS - 2)/4;
        all_map[rooms[i].doors[2].x][rooms[i].doors[2].y] = '+';

        rooms[i].doors[3].y = (rand()%(width-3)) + firsty + 1 + 2*(COLS - 2)/4;
        rooms[i].doors[3].x = firstx + height;
        all_map[rooms[i].doors[3].x][rooms[i].doors[3].y] = '+';
        break;
    case 3:

        rooms[i].doors[2].x = (rand()%(height-3)) + firstx + 1;
        rooms[i].doors[2].y = firsty + 3*(COLS - 2)/4;
        all_map[rooms[i].doors[2].x][rooms[i].doors[2].y] = '+';

        rooms[i].doors[3].y = (rand()%(width-3)) + firsty + 1 + 3*(COLS - 2)/4;
        rooms[i].doors[3].x = firstx + height;
        all_map[rooms[i].doors[3].x][rooms[i].doors[3].y] = '+';
        break;
    case 4:
        rooms[i].doors[1].x = (rand()%(height-3)) + firstx + 1 + (LINES - 10)/2;
        rooms[i].doors[1].y = firsty + width;
        all_map[rooms[i].doors[1].x][rooms[i].doors[1].y] = '+';
        rooms[i].doors[0].y = (rand()%(width-3)) + firsty + 1;
        rooms[i].doors[0].x = firstx + (LINES - 10)/2;
        all_map[rooms[i].doors[0].x][rooms[i].doors[0].y] = '+';
        break;
    case 5:
        rooms[i].doors[1].x = (rand()%(height-3)) + firstx + 1 + (LINES - 10)/2;
        rooms[i].doors[1].y = firsty + width + (COLS - 2)/4;
        all_map[rooms[i].doors[1].x][rooms[i].doors[1].y] = '+';

        rooms[i].doors[2].x = (rand()%(height-3)) + firstx + 1 + (LINES - 10)/2;
        rooms[i].doors[2].y = firsty + (COLS - 2)/4;
        all_map[rooms[i].doors[2].x][rooms[i].doors[2].y] = '+';

        rooms[i].doors[0].y = (rand()%(width-3)) + firsty + 1 + (COLS - 2)/4;
        rooms[i].doors[0].x = firstx + (LINES - 10)/2;
        all_map[rooms[i].doors[0].x][rooms[i].doors[0].y] = '+';
        break;
    case 6:
        rooms[i].doors[1].x = (rand()%(height-3)) + firstx + 1 + (LINES - 10)/2;
        rooms[i].doors[1].y = firsty + width + 2*(COLS - 2)/4;
        all_map[rooms[i].doors[1].x][rooms[i].doors[1].y] = '+';

        rooms[i].doors[2].x = (rand()%(height-3)) + firstx + 1 + (LINES - 10)/2;
        rooms[i].doors[2].y = firsty + 2*(COLS - 2)/4;
        all_map[rooms[i].doors[2].x][rooms[i].doors[2].y] = '+';

        rooms[i].doors[0].y = (rand()%(width-3)) + firsty + 1 + 2*(COLS - 2)/4;
        rooms[i].doors[0].x = firstx + (LINES - 10)/2;
        all_map[rooms[i].doors[0].x][rooms[i].doors[0].y] = '+';
        break;
    case 7:
        rooms[i].doors[2].x = (rand()%(height-3)) + firstx + 1 + (LINES - 10)/2;
        rooms[i].doors[2].y = firsty + 3*(COLS - 2)/4;
        all_map[rooms[i].doors[2].x][rooms[i].doors[2].y] = '+';

        rooms[i].doors[0].y = (rand()%(width-3)) + firsty + 1 + 3*(COLS - 2)/4;
        rooms[i].doors[0].x = firstx + (LINES - 10)/2;
        all_map[rooms[i].doors[0].x][rooms[i].doors[0].y] = '+';
        break;
    }
}

void map()
{
    map_whithout_tale = (char **) malloc ((LINES - 10)*sizeof(char *));
    for (int i = 0; i < (LINES - 10); i++)
    {
        map_whithout_tale[i] = (char *) malloc((COLS - 2) * sizeof(char));
        for (int j = 0; j < (COLS - 2); j++)
        {
            map_whithout_tale[i][j] = ' ';
        }
    }  

    map_that_shown = (char **) malloc ((LINES - 10)*sizeof(char *));
    for (int i = 0; i < (LINES - 10); i++)
    {
        map_that_shown[i] = (char *) malloc((COLS - 2) * sizeof(char));
        for (int j = 0; j < (COLS - 2); j++)
        {
            map_that_shown[i][j] = ' ';
        }
    }  

    all_map = (char **) malloc ((LINES - 10)*sizeof(char *));
    for (int i = 0; i < (LINES - 10); i++)
    {
        all_map[i] = (char *) malloc((COLS - 2) * sizeof(char));
        for (int j = 0; j < (COLS - 2); j++)
        {
            all_map[i][j] = ' ';
        }
    }  
    rooms = (room *) malloc(9 * sizeof(room));
    for (int i = 0; i<8; i++)
    {
        if (player.level == 4)
        {
            non_kaboos:
            //دو مورد از ۴ حالتی که میتونه بیاد باید اتاق معمولی باشه یعنی اگه ۰ یا ۱ بود معمولی 
            rooms[i].type = rand()%2;
            if (rooms[i].type == 3)
            {
                goto non_kaboos;
            }
        }
        else 
        {
            non_kaboos1:
            //دو مورد از ۴ حالتی که میتونه بیاد باید اتاق معمولی باشه یعنی اگه ۰ یا ۱ بود معمولی 
            rooms[i].type = rand()%2;
            if (rooms[i].type == 3)
            {
                goto non_kaboos1;
            }
        }
        if (rooms[i].type == 1 || rooms[i].type == 0)
        {
            int height = rand()%7 + 4;
            int width = rand()%13 + 6;

            rooms[i].map = (char **) malloc(((LINES - 10)/2)*sizeof(char *));
            for (int j = 0; j<((LINES - 10)/2); j++)
            {
                rooms[i].map[j] = (char *) malloc(((COLS - 2)/4)*sizeof(char));
                for (int k = 0; k < ((COLS - 2)/4); k++)
                {
                    rooms[i].map[j][k] = ' ';
                }
            }

            int firstx = rand()%((LINES - 10)/8) + 1;
            int firsty = rand()%((COLS - 2)/8) + 1;


            if (firstx + height < ((LINES - 10)/2) && firsty + width < ((COLS - 2)/4)) 
            {
            } 
            else 
            {
                i --;
                continue;
            }


            for (int k = 1; k < width; k++)
            {
                rooms[i].map[firstx][firsty + k] = '-';
            }

            for (int k = 1; k < width; k++)
            {
                rooms[i].map[firstx + height][firsty + k] = '-';
            }

            for (int k = 1; k < height; k++)
            {
                rooms[i].map[firstx + k][firsty] = '|';
            }

            for (int k = 1; k < height; k++)
            {
                rooms[i].map[firstx + k][firsty + width] = '|';
            }   
            rooms[i].map[firstx][firsty] = '$';
            rooms[i].map[firstx + height][firsty] = '$';
            rooms[i].map[firstx][firsty + width] = '$';
            rooms[i].map[firstx + height][firsty + width] = '$';

            for (int k = firstx + 1; k < firstx + height; k++)
            {
                for (int j = firsty + 1; j <  firsty + width; j++)
                {
                    rooms[i].map[k][j] = '.';
                }
            }

            add_to_main_map(i);
            adding_doors(i, firstx, firsty, width, height);
        }

        else if (rooms[i].type == 2)
        {
                        int height = rand()%5 + 4;
            int width = rand()%9 + 8;

            rooms[i].map = (char **) malloc(((LINES - 10)/2)*sizeof(char *));
            for (int j = 0; j<((LINES - 10)/2); j++)
            {
                rooms[i].map[j] = (char *) malloc(((COLS - 2)/4)*sizeof(char));
                for (int k = 0; k < ((COLS - 2)/4); k++)
                {
                    rooms[i].map[j][k] = ' ';
                }
            }

            int firstx = rand()%((LINES - 10)/6) + 2;
            int firsty = rand()%((COLS - 2)/10) + 2;


            if (firstx + height < ((LINES - 10)/2) && firsty + width < ((COLS - 2)/4)) 
            {
            } 
            else 
            {
                i --;
                continue;
            }
            for (int k = 1; k < width; k++)
            {
                rooms[i].map[firstx][firsty + k] = '-';
            }

            for (int k = 1; k < width; k++)
            {
                rooms[i].map[firstx + height][firsty + k] = '-';
            }

            for (int k = 1; k < height; k++)
            {
                rooms[i].map[firstx + k][firsty] = '|';
            }

            for (int k = 1; k < height; k++)
            {
                rooms[i].map[firstx + k][firsty + width] = '|';
            }   
            rooms[i].map[firstx][firsty] = '$';
            rooms[i].map[firstx + height][firsty] = '$';
            rooms[i].map[firstx][firsty + width] = '$';
            rooms[i].map[firstx + height][firsty + width] = '$';
        }
        
        else if (rooms[i].type == 3)
        {
            //kaboos
        }
        else if (rooms[i].type == 4)
        {

        }
    }   
}

// درست بشود...

void print_all_map()
{
    move(6, 2);
    for (int i = 0; i < LINES - 10; i++)
    {
        for (int j = 0; j < COLS - 2; j++)
        {
            if (all_map[i][j] == 'B')
            {
                attron(COLOR_PAIR(40));
                printw("%c", all_map[i][j]);
                attroff(COLOR_PAIR(40));
                refresh();
                continue;
            }

            if (all_map[i][j] == 'C')
            {
                attron(COLOR_PAIR(16));
                printw("%c", all_map[i][j]);
                attroff(COLOR_PAIR(16));
                continue;
            }
            if (all_map[i][j] == 'o')
            {
                printw("%c", all_map[i][j]);
                continue;
            }
            attron(COLOR_PAIR(15));
            printw("%c", all_map[i][j]);
            attroff(COLOR_PAIR(15));
        }
        move(6 + i + 1, 2);
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

void alert(char *message1, char *message2, int number)
{
    for (int i = 2; i < COLS - 1; i++)
    {
        mvprintw(1, i, " ");
        mvprintw(2, i, " ");
        mvprintw(3, i, " ");
    }

    attron(A_BOLD);
    attron(COLOR_PAIR(11));

    char buffer[256];
    if (number == -1)
    {
        snprintf(buffer, sizeof(buffer), "%s", message1);
    }
    else
    {
        snprintf(buffer, sizeof(buffer), "%s %d %s", message1, number, message2);
    }

    for (int i = 2; i < strlen(buffer) + 4; i++)
    {
        mvprintw(1, i, " ");
    }
    mvprintw(2, 2, " %s ", buffer);
    for (int i = 2; i < strlen(buffer) + 4; i++)
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
        wchar_t emoji[] = L"🪓";
        mvaddwstr(LINES - 3, 4*(COLS/5) + 11, emoji);
        break;
    
    case 2:
        wchar_t emoji1[] = L"🗡️";
        mvaddwstr(LINES - 3, 4*(COLS/5) + 11, emoji1);
        break;

    case 3:
        wchar_t emoji2[] = L"🪄";
        mvaddwstr(LINES - 3, 4*(COLS/5) + 11, emoji2);
        break;

    case 4:
        wchar_t emoji3[] = L"🏹";
        mvaddwstr(LINES - 3, 4*(COLS/5) + 11, emoji3);
        break;

    case 5:
        wchar_t emoji4[] = L"⚔️";
        mvaddwstr(LINES - 3, 4*(COLS/5) + 11, emoji4);
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

void copy_map()
{
    for (int i = 0; i < LINES - 10; i++)
    {
        for (int j = 0; j < COLS - 2; j++)
        {
            if (all_map[i][j] != '^')
            {
                map_whithout_tale[i][j] = all_map[i][j];
            }
            else
            {
                map_whithout_tale[i][j] = '.';
            }
        }
    }
}

void elements_on_map()
{
    for (int i = 0; i < LINES - 10; i++)
    {
        for (int j = 0; j < COLS - 2; j++)
        {
            int sotoon_panjereh = rand()%40;
            int gold = rand()%50;
            int black_gold = rand()%160;

            int tale_random;
            switch (player.hardness)
            {
            case 1:
                tale_random = 70;
                break;
            
            case 2:
                tale_random = 60;
                break;

            case 3:
                tale_random = 50;
                break;
            }

            int tale = rand()%tale_random;

            if (all_map[i][j] == '.' && all_map[i + 1][j + 1] != '+' && all_map[i + 1][j] != '+' && all_map[i][j + 1] != '+' && all_map[i][j - 1] != '+' && all_map[i - 1][j] != '+' && all_map[i - 1][j - 1] != '+' && !sotoon_panjereh)
            {
                all_map[i][j] = 'o';
            }

            if (all_map[i][j] == '.' && !gold)
            {
                all_map[i][j] = 'C';
            }

            if (all_map[i][j] == '.' && !tale)
            {
                all_map[i][j] = '^';
            }

            if (all_map[i][j] == '.' && !black_gold)
            {
                all_map[i][j] = 'B';
            }
        }
    }

}

void random_first_map()
{
    int which_map = rand()%8;
    int row, col;
    switch (which_map) 
    {
    case 0:
        row = 0;
        col = 0;
        break;

    case 1:
        row = 0;
        col = (COLS - 2) / 4;
        break;

    case 2:
        row = 0;
        col = 2 * (COLS - 2) / 4;
        break;

    case 3:
        row = 0;
        col = 3 * (COLS - 2) / 4;
        break;

    case 4:
        row = ((LINES - 10) / 2);
        col = 0;
        break;

    case 5:
        row = ((LINES - 10) / 2);
        col = (COLS - 2) / 4;
        break;

    case 6:
        row = ((LINES - 10) / 2);
        col = 2 * (COLS - 2) / 4 ;
        break;

    case 7:
        row = (LINES - 10) / 2;
        col = 3 * (COLS - 2) / 4;
        break;

    }
    int okey = 0;
    for (int i = row; i < row + (LINES - 10)/2; i++)
    {
        for (int j = col; j < col + (COLS - 2)/4; j++)
        {
            if (map_whithout_tale[i][j] != ' ' && map_whithout_tale[i][j] != '#')
            {
                map_that_shown[i][j] = map_whithout_tale[i][j];

                if (!okey && map_whithout_tale[i][j] == '.')
                {
                    player.x = i + 6;
                    player.y = j + 2;
                    okey ++;
                }
            }
        }
    }
}

void print_map()
{
    move(6, 2);
    for (int i = 0; i < LINES - 10; i++)
    {
        for (int j = 0; j < COLS - 2; j++)
        {

            if (map_that_shown[i][j] == 'B')
            {
                attron(COLOR_PAIR(40));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(40));
                continue;
            }

            if (map_that_shown[i][j] == 'C')
            {
                attron(COLOR_PAIR(16));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(16));
                continue;
            }
            if (map_that_shown[i][j] == 'o')
            {
                printw("%c", map_that_shown[i][j]);
                continue;
            }
            attron(COLOR_PAIR(15));
            printw("%c", map_that_shown[i][j]);
            attroff(COLOR_PAIR(15));
        }
        move(6 + i + 1, 2);
    }
    refresh(); 
}

void player_move(int x_pa, int y_pa, int g_on_off)
{
    player.hungry_amount += 0.0675;
    print_map();

    if (g_on_off == 1)
    {
        goto whith_g_key;
    }

    if (all_map[player.x - 6][player.y - 2] == 'o' || all_map[player.x - 6][player.y - 2] == '$' || all_map[player.x - 6][player.y - 2] == '|' || all_map[player.x - 6][player.y - 2] == '-' || all_map[player.x - 6][player.y - 2] == ' ')
    {
        player.x = x_pa;
        player.y = y_pa;
    }
    
    if (all_map[player.x - 6][player.y - 2] == '^')
    {
        map_that_shown[player.x - 6][player.y - 2] = '^';
        player.x = x_pa;
        player.y = y_pa;
        print_map();
        player.life_time --;
    }

    if (map_that_shown[player.x - 6][player.y - 2] == 'C')
    {
        int random;
        switch (player.hardness)
        {
        case 1:
            random = 40;
            break;
        
        case 2:
            random = 30;
            break;

        case 3:
            random = 20;
            break;
        }

        // int random;
        // switch (which_room)
        // {
        // case 1:
        //     random = 40;
        //     break;
        
        // case 2:
        //     random = 30;
        //     break;

        // case 3:
        //     random = 20;
        //     break;
        // }

        int gold = rand()%random;
        alert("You'v got", "Gold!", gold);
        player.gold += gold;
        map_that_shown[player.x - 6][player.y - 2] = '.';
        all_map[player.x - 6][player.y - 2] = '.';
        print_map();
    }

    if (map_that_shown[player.x - 6][player.y - 2] == 'B')
    {
        int random;
        switch (player.hardness)
        {
        case 1:
            random = 120;
            break;
        
        case 2:
            random = 90;
            break;

        case 3:
            random = 60;
            break;
        }

        // int random;
        // switch (which_room)
        // {
        // case 1:
        //     random = 40;
        //     break;
        
        // case 2:
        //     random = 30;
        //     break;

        // case 3:
        //     random = 20;
        //     break;
        // }

        int gold = rand()%random;
        alert("You'v got", "Black Gold!", gold);
        player.gold += gold;
        map_that_shown[player.x - 6][player.y - 2] = '.';
        all_map[player.x - 6][player.y - 2] = '.';

        print_map();
    }

    if (all_map[player.x - 6][player.y - 2] == '+')
    {


    
    }































    whith_g_key:

    int color;
    switch (player.color)
    {
    case 1:
        color = 31;
        break;
    
    case 2:
        color = 32;
        break;

    case 3:
        color = 33;
        break;
    }
    elemnts_under_board();
    attron(COLOR_PAIR(color));
    mvprintw(player.x, player.y, "@");
    attroff(COLOR_PAIR(color));
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
    player.score = 0;
    player.main_selah = 1;
    if (player.hardness == 1)
    {
        player.life_time = 25;
        player.hungry_amount = 0;
    }
    else if (player.hardness == 2)
    {
        player.life_time = 21;
        player.hungry_amount = 2;
    }
    else if (player.hardness == 3)
    {
        player.life_time = 17; 
        player.hungry_amount = 4;  
    }
    first_life = player.life_time;
    player.level = 1;
    player.selah[0] = 1;

    clear_and_border2();
    elemnts_under_board();
    map();
    connect_room();
    elements_on_map();
    copy_map();

    random_first_map();

    player_move(0, 0, 0);

    int m_on_off = 0;
    int g_on_off = 0;
    for(int ch = getch(); ch != 'q'; ch = getch())
    {
        if (player.hungry_amount < 10 && player.life_time < 25)
        {
            player.life_time += 0.25;
        }

        if (player.hungry_amount > 10)
        {
            player.life_time -= 0.125;
        }

        if (player.life_time == 0)
        {
            attron(COLOR_PAIR(5));
            mvprintw((LINES/2) - 2, (COLS/2) - 8, "               ");
            mvprintw((LINES/2) - 1 , (COLS/2) - 8, "   YOU DIED!   ");
            mvprintw((LINES/2), (COLS/2) - 8, "               ");
            mvprintw((LINES/2) + 1, (COLS/2) - 8, " GAME IS OVER! ");
            mvprintw((LINES/2) + 2, (COLS/2) - 8, "               ");
            attroff(COLOR_PAIR(5));
            refresh();
            sleep(3);
            break;
        }
        switch(ch)
        {
            case (56):
                player.x --;
                player_move(player.x + 1, player.y, g_on_off);
                g_on_off = 0;
                break;

            case (54):
                player.y ++;
                player_move(player.x, player.y - 1, g_on_off);
                g_on_off = 0;
                break;

            case (52):
                player.y --;
                player_move(player.x, player.y + 1, g_on_off);
                g_on_off = 0;
                break;

            case (50):
                player.x ++;
                player_move(player.x - 1, player.y, g_on_off);
                g_on_off = 0;
                break;

            case (51):
                player.x ++;
                player.y ++;
                player_move(player.x - 1, player.y - 1, g_on_off);
                g_on_off = 0;
                break;

            case (49):
                player.x ++;
                player.y --;
                player_move(player.x - 1, player.y + 1, g_on_off);
                g_on_off = 0;
                break;

            case (55):
                player.x --;
                player.y --;
                player_move(player.x + 1, player.y + 1, g_on_off);
                g_on_off = 0;
                break;

            case (57):
                player.x --;
                player.y ++;
                player_move(player.x + 1, player.y - 1, g_on_off);
                g_on_off = 0;
                break;

            case ('m'):
                if (m_on_off == 0)
                {
                    print_all_map();
                    m_on_off = 1;
                }
                else
                {
                    clear_and_border2();
                    elemnts_under_board();
                    m_on_off = 0; 
                    player_move(player.x, player.y, g_on_off);
                }
                break;


            case ('g'):
                g_on_off = 1;
                break;



        }
    }


        return 4;


}