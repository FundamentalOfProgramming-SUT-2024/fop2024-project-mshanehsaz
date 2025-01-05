#include <stdio.h>
#include <ncurses.h>

int main()
{
    initscr();

    while(1)
    {
        printw("salam");
    }



    refresh();
    endwin();
    return 0;
}