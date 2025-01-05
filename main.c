#include <stdio.h>
#include <ncurses.h>

int main()
{
    initscr();

    while(1)
    {
        printw("salam");
        char c = getch();
        if (c != 's')
        {
            break;
        }
    }



    refresh();
    endwin();
    return 0;
}